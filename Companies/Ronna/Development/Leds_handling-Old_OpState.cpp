#include "OpState.h"
#include "OpContext.h"
#include <OperationState.h>
#include <StartupState.h>

using namespace rtkcontrol;


void OpState::OnMoveToTransportPose(GtkWidget* widget, OpContext* ctx)
{
	SPDLOG_LOGGER_DEBUG(ctx->logger_control, "OnMoveToTransportPose.");

	// ctx->transport_pc = std::make_unique<rtkcommon::PopupController>(GTK_WINDOW(ctx->getGobj()),
	// 	"Robot will go to transport pose.", "Ok", "Cancel", false,
	// 	std::bind(&OpState::OnOkMoveToTransportPose, this, ctx, std::placeholders::_1, std::placeholders::_2),
	// 	std::bind(&OpState::OnCancelMoveToTransportPose, this, ctx, std::placeholders::_1, std::placeholders::_2));

	// ctx->transport_pc->show();

	OnOkMoveToTransportPose(ctx);
}

void OpState::OnMoveRobotInTransportPos(OpContext *ctx)
{
	SPDLOG_LOGGER_DEBUG(ctx->logger_control, "OnMoveRobotInTransportPos.");
}

void OpState::OnTranslationMoving(OpContext *ctx)
{
	SPDLOG_LOGGER_DEBUG(ctx->logger_control, "OnTranslationMoving.");
	
	if (ctx->mobile_state == rtkcommunication::JOYSTICK_HALTED)
	{
		ctx->mobile_client->StopJoystick();
		sleep(1);
	}

	ctx->mobile_client->StartJoystickComp();
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ctx->translate_btn), true);
}

void OpState::OnRotationMoving(OpContext *ctx)
{
	SPDLOG_LOGGER_DEBUG(ctx->logger_control, "OnRotationMoving.");

	if (ctx->mobile_state == rtkcommunication::JOYSTICK_HALTED)
	{
		ctx->mobile_client->StopJoystick();
		sleep(1);
	}

	ctx->mobile_client->StartJoystickRot();
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ctx->rotate_btn), true);
}

void OpState::OnCombinedMoving(OpContext *ctx)
{
	SPDLOG_LOGGER_DEBUG(ctx->logger_control, "OnCombinedMoving.");

	if (ctx->mobile_state == rtkcommunication::JOYSTICK_HALTED)
	{
		ctx->mobile_client->StopJoystick();
		sleep(1);
	}

	ctx->mobile_client->StartJoystick();
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ctx->combined_btn), true);
}

void OpState::OnUp(OpContext *ctx)
{
	SPDLOG_LOGGER_DEBUG(ctx->logger_control, "OnUp.");

	ctx->mobile_client->Lift();
}

void OpState::OnDown(OpContext *ctx)
{
	SPDLOG_LOGGER_DEBUG(ctx->logger_control, "OnDown.");

	if (ctx->mobile_state == rtkcommunication::JOYSTICK_HALTED)
	{
		ctx->mobile_client->StopJoystick();
		sleep(1);
	}

	ctx->mobile_client->Lower();
}

void OpState::OnFootswitchPressed(OpContext *ctx)
{
}

void OpState::OnFootswitchReleased(OpContext *ctx)
{
}

void OpState::OnRobotStatusReceived(const rtkcommunication::RobotStatus& status, OpContext *ctx)
{
	if(_robot_status_mutex.try_lock())
	{
		ctx->robot_status = status;

		// std::unique_lock<std::mutex> lock(ctx->robot_status_mtx);
        // ctx->robot_status_count++;
        // ctx->robot_status_cv.notify_one();  

		OpState* state = ctx->GetActiveState();
		if (OperationState* op_state = dynamic_cast<OperationState*>(state); op_state != nullptr)
		{
			if (ctx->active_target_enable && ctx->active_trajectory != nullptr)
			{
				if (ctx->movement_plan != nullptr)
				{
					rtksimulation::ActiveTargetData target_data = ctx->movement_plan->CalculateActiveTargetData(*ctx->active_trajectory, status, ctx->active_guide_tool.value(), ctx->drill_position_enable);
					op_state->UpdateTargetInfo(target_data, ctx);
				}
			}
		}

		if (status.robot_mastered == false && ctx->pc_mastering_shown == false)
		{
			time_t now = time(0);
			SPDLOG_LOGGER_INFO(ctx->logger_control, "{}: Robot is not mastered!", now);

			SPDLOG_LOGGER_DEBUG(ctx->logger_control, "Setting PLC managed leds to RED color.");
			ctx->plc_controller->SetDesignLeds(ctx->GetPlcManagedLedsConf(rtkcommunication::RGBColor::RED));
			ctx->plc_controller->SetFunctionLeds(ctx->GetPlcManagedLedsConf(rtkcommunication::RGBColor::RED));
			if (ctx->server != nullptr && ctx->server->IsMicroControllerConnected)
			{
				SPDLOG_LOGGER_DEBUG(ctx->logger_control, "Setting tool adapter leds to RED color.");
				ctx->server->sessionMicroController->SetLeds(
					ctx->GetToolAdapterLedsConf(rtkcommunication::RGBColor::RED, rtkcommunication::LedMode::CONSTANT));
			}

			if (ctx->plc_controller->IsConnected())
				ctx->plc_controller->EnableSystemCheck();
			else
				return;

			SPDLOG_LOGGER_DEBUG(ctx->logger_control, "{} Current State: {}.", now, status.robot_state);
			
			if (status.robot_state == "ErrorState")
			{
				SPDLOG_LOGGER_WARN(ctx->logger_control, "{}: Robot is in error state!", now);
				ctx->pc_mastering_shown = true;
				ctx->pc_mastering = new rtkcommon::PopupController(GTK_WINDOW(ctx->getGobj()),
					"Mastering is needed. Please remove tool from the robot flange and confirm to start mastering.", "Confirm", false,
					std::bind(&OpState::OnMasteringConfirmed, this, ctx));
				ctx->pc_mastering->Show();
			}
		}

		if (!ctx->system_check_started && ctx->plc_controller->IsConnected() && (!ctx->plc_controller->CheckReferencing() ||
		    !(ctx->robot_status.brake_test_monitor_state == "OK") || (status.time_until_braketest < 3600)))
		{
			gtk_widget_set_visible(GTK_WIDGET(ctx->system_check_btn), true);
			gtk_widget_set_visible(GTK_WIDGET(ctx->next_step_btn), false);
		}
		else if(!ctx->system_check_started)
		{
			gtk_widget_set_visible(GTK_WIDGET(ctx->system_check_btn), false);
			gtk_widget_set_visible(GTK_WIDGET(ctx->next_step_btn), true);
		}

		_robot_status_mutex.unlock();
	}
}

void OpState::UpdateTargetInfo(const rtksimulation::ActiveTargetData &target, OpContext *ctx)
{
}

void OpState::OnMobileClientConnected(OpContext *ctx)
{
	SPDLOG_LOGGER_DEBUG(ctx->logger_control, "OnMobileClientConnected.");
}

void OpState::OnMobileClientConnectionError(OpContext *ctx, std::string error)
{
	sleep(1);

	ctx->mobile_client->Connect("172.31.1.40", "2000", 
		std::bind(&OpState::OnMobileClientConnected, ctx->GetActiveState(), ctx),
		std::bind(&OpState::OnMobileClientConnectionError, ctx->GetActiveState(), ctx, std::placeholders::_1));
}

void OpState::OnMobileClientResponseReceived(OpContext *ctx, rtkcommunication::MobileResponse response)
{
	SPDLOG_LOGGER_DEBUG(ctx->logger_control, "OnMobileClientResponseReceived.");
}

void OpState::OnMobileStatusClientConnected(OpContext *ctx)
{
	SPDLOG_LOGGER_DEBUG(ctx->logger_control, "OnMobileStatusClientConnected.");

	ctx->pc_homing =
		std::make_unique<rtkcommon::PopupController>(GTK_WINDOW(ctx->getGobj()),
		"Homing is needed. Please confirm and reactivate the enabling switch.", "Confirm", false, 
		std::bind(&OpState::OnHomingConfirmed, ctx->GetActiveState(), ctx));

	ctx->pc_homing_halted =
		std::make_unique<rtkcommon::PopupController>(GTK_WINDOW(ctx->getGobj()),
		"Please hold the enabling switch to continue homing", "Cancel", false,
		std::bind(&OpState::OnStopMobilePlatformOperation, this, ctx));

	ctx->pc_homing_ready =
		std::make_unique<rtkcommon::PopupController>(GTK_WINDOW(ctx->getGobj()),
		"Please confirm to continue homing", "Confirm", false,
		std::bind(&OpState::OnEnableReset, ctx->GetActiveState(), ctx));

	ctx->pc_homing_in_progress =
		std::make_unique<rtkcommon::PopupController>(GTK_WINDOW(ctx->getGobj()),
		"Homing is in progress, keep holding the enabling switch", false);
	
	ctx->pc_lifting_halted =
		std::make_unique<rtkcommon::PopupController>(GTK_WINDOW(ctx->getGobj()),
		"Please hold the enabling switch to continue lifting", "Cancel", false,
		std::bind(&OpState::OnStopMobilePlatformOperation, this, ctx));

	ctx->pc_lifting_ready =
		std::make_unique<rtkcommon::PopupController>(GTK_WINDOW(ctx->getGobj()),
		"Lifting system is ready. Please confirm to continue lifting.", "Confirm", false,
		std::bind(&OpState::OnEnableReset, this, ctx));

	ctx->pc_positioning_halted =
		std::make_unique<rtkcommon::PopupController>(GTK_WINDOW(ctx->getGobj()),
		"Please hold the enabling switch to continue auto positioning", "Cancel", false,
		std::bind(&OpState::OnStopMobilePlatformOperation, this, ctx));

	ctx->pc_positioning_ready =
		std::make_unique<rtkcommon::PopupController>(GTK_WINDOW(ctx->getGobj()),
		"Positioning system is ready. Please confirm to continue positioning.", "Confirm", false,
		std::bind(&OpState::OnEnableReset, this, ctx));

	ctx->pc_collision_detected =
		std::make_unique<rtkcommon::PopupController>(GTK_WINDOW(ctx->getGobj()),
		"Collision detected, clear the workspace and press confirm to continue.", "Confirm", true,
		std::bind(&OpState::OnEnableReset, this, ctx));

}

void OpState::OnMobileStatusClientConnectionError(OpContext *ctx, std::string error)
{	
	std::cout << "MobileStatusClient reconnect::OnMobileStatusClientConnectionError" << std::endl;
	sleep(1);

	g_idle_add([](gpointer user_data) -> gboolean
	{
		OpContext* ctx = static_cast<OpContext*>(user_data);

		ctx->mobile_status_client->Reset();
		sleep(1);
		ctx->mobile_status_client->Connect("172.31.1.40", "2001",
		std::bind(&OpState::OnMobileStatusClientConnected, ctx->GetActiveState(), ctx),
		std::bind(&OpState::OnMobileStatusClientConnectionError, ctx->GetActiveState(), ctx, std::placeholders::_1));

		return G_SOURCE_REMOVE;
	}, ctx);


}

void OpState::OnMobileStatusClientResponseReceived(OpContext *ctx, rtkcommunication::MobileResponse response)
{	
	bool arm_in_transport = ctx->movement_guide->CheckIfRobotInPose(ctx->robot_status,
								rtkcommunication::RobotPose{"Transport", rtksimulation::C_TRANSPORT_ROTATIONS_DEG_LIST});

	if (rtkcommunication::mobile_state_string.contains(response.mobile_state))
	{
		rtkcommunication::mobile_state_type _m_state = rtkcommunication::mobile_state_string.at(response.mobile_state);
		if (_m_state != ctx->mobile_state || ctx->arm_toggle_transport != arm_in_transport)
		{
			ctx->mobile_state = _m_state;
			ctx->arm_toggle_transport = arm_in_transport;

			RefreshDriveButtons(ctx);
		}
	}
}

void OpState::RefreshDriveButtons(OpContext *ctx)
{	
	switch (ctx->mobile_state)
	{	
		case rtkcommunication::ESTOP_DISABLED:
			SPDLOG_LOGGER_DEBUG(ctx->logger_control, "ESTOP_DISABLED.");

			gtk_widget_set_sensitive(GTK_WIDGET(ctx->up_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->down_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->translate_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->rotate_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->combined_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->system_check_btn), false);
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ctx->translate_btn), false);
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ctx->rotate_btn), false);
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ctx->combined_btn), false);

			SPDLOG_LOGGER_DEBUG(ctx->logger_control, "Setting PLC managed leds to RED color.");
			ctx->plc_controller->SetDesignLeds(ctx->GetPlcManagedLedsConf(rtkcommunication::RGBColor::RED));
			ctx->plc_controller->SetFunctionLeds(ctx->GetPlcManagedLedsConf(rtkcommunication::RGBColor::RED));
			if (ctx->server != nullptr && ctx->server->IsMicroControllerConnected)
			{
				SPDLOG_LOGGER_DEBUG(ctx->logger_control, "Setting tool adapter leds to RED color.");
				ctx->server->sessionMicroController->SetLeds(
					ctx->GetToolAdapterLedsConf(rtkcommunication::RGBColor::RED, rtkcommunication::LedMode::CONSTANT));
			}

			break;

		case rtkcommunication::HOMING_NEEDED:
			SPDLOG_LOGGER_DEBUG(ctx->logger_control, "HOMING_NEEDED.");

			gtk_widget_set_sensitive(GTK_WIDGET(ctx->up_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->down_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->translate_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->rotate_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->combined_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->system_check_btn), false);
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ctx->translate_btn), false);
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ctx->rotate_btn), false);
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ctx->combined_btn), false);

			SPDLOG_LOGGER_DEBUG(ctx->logger_control, "Setting PLC managed leds to RED color.");
			ctx->plc_controller->SetDesignLeds(ctx->GetPlcManagedLedsConf(rtkcommunication::RGBColor::RED));
			ctx->plc_controller->SetFunctionLeds(ctx->GetPlcManagedLedsConf(rtkcommunication::RGBColor::RED));
			if (ctx->server != nullptr && ctx->server->IsMicroControllerConnected)
			{
				SPDLOG_LOGGER_DEBUG(ctx->logger_control, "Setting tool adapter leds to RED color.");
				ctx->server->sessionMicroController->SetLeds(
					ctx->GetToolAdapterLedsConf(rtkcommunication::RGBColor::RED, rtkcommunication::LedMode::CONSTANT));
			}

			g_idle_add([](gpointer data) -> gboolean
			{
				OpContext* ctx = (OpContext*)data;
				OpState* state = static_cast<OpState*>(ctx->GetActiveState());

				ctx->pc_homing->Show();

				return false;
			}, ctx);
			
			break;

		case rtkcommunication::HOMING_CONTROLLER_HALTED:
		// TODO: upiši u status bar Plesase press enabling switch
			SPDLOG_LOGGER_DEBUG(ctx->logger_control, "HOMING_CONTROLLER_HALTED.");

			gtk_widget_set_sensitive(GTK_WIDGET(ctx->up_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->down_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->translate_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->rotate_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->combined_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->system_check_btn), false);
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ctx->translate_btn), false);
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ctx->rotate_btn), false);
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ctx->combined_btn), false);

			SPDLOG_LOGGER_DEBUG(ctx->logger_control, "Setting PLC managed leds to RED color.");
			ctx->plc_controller->SetDesignLeds(ctx->GetPlcManagedLedsConf(rtkcommunication::RGBColor::RED));
			ctx->plc_controller->SetFunctionLeds(ctx->GetPlcManagedLedsConf(rtkcommunication::RGBColor::RED));
			if (ctx->server != nullptr && ctx->server->IsMicroControllerConnected)
			{
				SPDLOG_LOGGER_DEBUG(ctx->logger_control, "Setting tool adapter leds to RED color.");
				ctx->server->sessionMicroController->SetLeds(
					ctx->GetToolAdapterLedsConf(rtkcommunication::RGBColor::RED, rtkcommunication::LedMode::CONSTANT));
			}

			g_idle_add([](gpointer data) -> gboolean
			{
				OpContext* ctx = (OpContext*)data;
				OpState* state = static_cast<OpState*>(ctx->GetActiveState());

				ctx->pc_homing_halted->Show();				

				return false;
			}, ctx);

			break;

		case rtkcommunication::HOMING_CONTROLLER_READY:
			SPDLOG_LOGGER_DEBUG(ctx->logger_control, "HOMING_CONTROLLER_READY.");

			gtk_widget_set_sensitive(GTK_WIDGET(ctx->up_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->down_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->translate_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->rotate_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->combined_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->system_check_btn), false);
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ctx->translate_btn), false);
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ctx->rotate_btn), false);
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ctx->combined_btn), false);

			SPDLOG_LOGGER_DEBUG(ctx->logger_control, "Setting PLC managed leds to YELLOW color.");
			ctx->plc_controller->SetDesignLeds(ctx->GetPlcManagedLedsConf(rtkcommunication::RGBColor::YELLOW));
			ctx->plc_controller->SetFunctionLeds(ctx->GetPlcManagedLedsConf(rtkcommunication::RGBColor::YELLOW));
			if (ctx->server != nullptr && ctx->server->IsMicroControllerConnected)
			{
				SPDLOG_LOGGER_DEBUG(ctx->logger_control, "Setting tool adapter leds to YELLOW color.");
				ctx->server->sessionMicroController->SetLeds(
					ctx->GetToolAdapterLedsConf(rtkcommunication::RGBColor::YELLOW, rtkcommunication::LedMode::CONSTANT));
			}

			g_idle_add([](gpointer data) -> gboolean
			{
				OpContext* ctx = (OpContext*)data;
				OpState* state = static_cast<OpState*>(ctx->GetActiveState());

				ctx->pc_homing_halted->Hide();
				ctx->pc_homing_ready->Show();

				return false;
			}, ctx);

			break;

		case rtkcommunication::HOMING_CONTROLLER_ON:
			SPDLOG_LOGGER_DEBUG(ctx->logger_control, "HOMING_CONTROLLER_ON.");

			gtk_widget_set_sensitive(GTK_WIDGET(ctx->up_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->down_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->translate_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->rotate_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->combined_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->system_check_btn), false);
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ctx->translate_btn), false);
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ctx->rotate_btn), false);
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ctx->combined_btn), false);

			SPDLOG_LOGGER_DEBUG(ctx->logger_control, "Setting PLC managed leds to YELLOW color.");
			ctx->plc_controller->SetDesignLeds(ctx->GetPlcManagedLedsConf(rtkcommunication::RGBColor::YELLOW));
			ctx->plc_controller->SetFunctionLeds(ctx->GetPlcManagedLedsConf(rtkcommunication::RGBColor::YELLOW));
			if (ctx->server != nullptr && ctx->server->IsMicroControllerConnected)
			{
				SPDLOG_LOGGER_DEBUG(ctx->logger_control, "Setting tool adapter leds to YELLOW color.");
				ctx->server->sessionMicroController->SetLeds(
					ctx->GetToolAdapterLedsConf(rtkcommunication::RGBColor::YELLOW, rtkcommunication::LedMode::CONSTANT));
			}

			break;

		case rtkcommunication::IDLE:
			SPDLOG_LOGGER_DEBUG(ctx->logger_control, "IDLE.");

			if (ctx->movement_guide->CheckIfRobotInPose(ctx->robot_status,
					rtkcommunication::RobotPose{"Transport", rtksimulation::C_TRANSPORT_ROTATIONS_DEG_LIST}))
			{
				gtk_widget_set_sensitive(GTK_WIDGET(ctx->up_btn), true);
			}
			else
				gtk_widget_set_sensitive(GTK_WIDGET(ctx->up_btn), false);

			gtk_widget_set_sensitive(GTK_WIDGET(ctx->down_btn), true);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->translate_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->rotate_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->combined_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->system_check_btn), false);
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ctx->translate_btn), false);
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ctx->rotate_btn), false);
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ctx->combined_btn), false);

			SPDLOG_LOGGER_DEBUG(ctx->logger_control, "Setting PLC managed leds to GREEN color.");
			ctx->plc_controller->SetDesignLeds(ctx->GetPlcManagedLedsConf(rtkcommunication::RGBColor::GREEN));
			ctx->plc_controller->SetFunctionLeds(ctx->GetPlcManagedLedsConf(rtkcommunication::RGBColor::GREEN));
			if (ctx->server != nullptr && ctx->server->IsMicroControllerConnected)
			{
				SPDLOG_LOGGER_DEBUG(ctx->logger_control, "Setting tool adapter leds to GREEN color.");
				ctx->server->sessionMicroController->SetLeds(
					ctx->GetToolAdapterLedsConf(rtkcommunication::RGBColor::GREEN, rtkcommunication::LedMode::CONSTANT));
			}

			break;

		case rtkcommunication::LIFTING_CONTROLLER_HALTED:
			SPDLOG_LOGGER_DEBUG(ctx->logger_control, "LIFTING_CONTROLLER_HALTED.");

			// TODO: Write into status bar "Plesase press and hold enabling switch.".
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->up_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->down_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->translate_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->rotate_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->combined_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->system_check_btn), false);
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ctx->translate_btn), false);
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ctx->rotate_btn), false);
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ctx->combined_btn), false);

			SPDLOG_LOGGER_DEBUG(ctx->logger_control, "Setting PLC managed leds to GREEN color.");
			ctx->plc_controller->SetDesignLeds(ctx->GetPlcManagedLedsConf(rtkcommunication::RGBColor::GREEN));
			ctx->plc_controller->SetFunctionLeds(ctx->GetPlcManagedLedsConf(rtkcommunication::RGBColor::GREEN));
			if (ctx->server != nullptr && ctx->server->IsMicroControllerConnected)
			{
				SPDLOG_LOGGER_DEBUG(ctx->logger_control, "Setting tool adapter leds to GREEN color.");
				ctx->server->sessionMicroController->SetLeds(
					ctx->GetToolAdapterLedsConf(rtkcommunication::RGBColor::GREEN, rtkcommunication::LedMode::CONSTANT));
			}

			g_idle_add([](gpointer data) -> gboolean
			{
				OpContext* ctx = (OpContext*)data;
				OpState* state = static_cast<OpState*>(ctx->GetActiveState());

				ctx->pc_lifting_halted->Show();

				sleep(1);
				
				SPDLOG_LOGGER_DEBUG(ctx->logger_control, "LIFTING_CONTROLLER_HALTED distances: {}, {}, {}.", ctx->plc_controller->GetDistanceVariables()[0],
																												 ctx->plc_controller->GetDistanceVariables()[1],
																												 	ctx->plc_controller->GetDistanceVariables()[2]);

				SPDLOG_LOGGER_DEBUG(ctx->logger_ctrl_snapshot, "P/F_9_ROB_LIFTING_UNIT_MOVEMENTS_AFTER_ENABLING_RELEASE {}.", rtkcommunication::JsonObject::JsonSerialize<double>(ctx->plc_controller->GetDistanceVariables()[2]));


				return false;
			}, ctx);

			break;

		case rtkcommunication::LIFTING_CONTROLLER_READY:
			SPDLOG_LOGGER_DEBUG(ctx->logger_control, "LIFTING_CONTROLLER_READY.");

			gtk_widget_set_sensitive(GTK_WIDGET(ctx->up_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->down_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->translate_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->rotate_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->combined_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->system_check_btn), false);
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ctx->translate_btn), false);
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ctx->rotate_btn), false);
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ctx->combined_btn), false);

			SPDLOG_LOGGER_DEBUG(ctx->logger_control, "Setting PLC managed leds to YELLOW color.");
			ctx->plc_controller->SetDesignLeds(ctx->GetPlcManagedLedsConf(rtkcommunication::RGBColor::YELLOW));
			ctx->plc_controller->SetFunctionLeds(ctx->GetPlcManagedLedsConf(rtkcommunication::RGBColor::YELLOW));
			if (ctx->server != nullptr && ctx->server->IsMicroControllerConnected)
			{
				SPDLOG_LOGGER_DEBUG(ctx->logger_control, "Setting tool adapter leds to YELLOW color.");
				ctx->server->sessionMicroController->SetLeds(
					ctx->GetToolAdapterLedsConf(rtkcommunication::RGBColor::YELLOW, rtkcommunication::LedMode::CONSTANT));
			}

			g_idle_add([](gpointer data) -> gboolean
			{
				OpContext* ctx = (OpContext*)data;
				OpState* state = static_cast<OpState*>(ctx->GetActiveState());

				ctx->pc_lifting_halted->Hide();

				if (ctx->plc_controller->GetCollisionState() == false)
					ctx->pc_collision_detected->Show();
				else 
					ctx->pc_lifting_ready->Show();
				
				return false;
			}, ctx);

			break;

		case rtkcommunication::LIFTING_CONTROLLER_ON:
			SPDLOG_LOGGER_DEBUG(ctx->logger_control, "LIFTING_CONTROLLER_ON.");

			gtk_widget_set_sensitive(GTK_WIDGET(ctx->up_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->down_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->translate_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->rotate_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->combined_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->system_check_btn), false);
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ctx->translate_btn), false);
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ctx->rotate_btn), false);
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ctx->combined_btn), false);
			// TODO: pamtiti koja je zadnja pozicija i označiti zeleno

			SPDLOG_LOGGER_DEBUG(ctx->logger_control, "Setting PLC managed leds to YELLOW color.");
			ctx->plc_controller->SetDesignLeds(ctx->GetPlcManagedLedsConf(rtkcommunication::RGBColor::YELLOW));
			ctx->plc_controller->SetFunctionLeds(ctx->GetPlcManagedLedsConf(rtkcommunication::RGBColor::YELLOW));
			if (ctx->server != nullptr && ctx->server->IsMicroControllerConnected)
			{
				SPDLOG_LOGGER_DEBUG(ctx->logger_control, "Setting tool adapter leds to YELLOW color.");
				ctx->server->sessionMicroController->SetLeds(
					ctx->GetToolAdapterLedsConf(rtkcommunication::RGBColor::YELLOW, rtkcommunication::LedMode::CONSTANT));
			}

			break;

		case rtkcommunication::IDLE_LOWERED:
			SPDLOG_LOGGER_DEBUG(ctx->logger_control, "IDLE_LOWERED.");

			if (ctx->movement_guide->CheckIfRobotInPose(ctx->robot_status,
				rtkcommunication::RobotPose{"Transport", rtksimulation::C_TRANSPORT_ROTATIONS_DEG_LIST}) && ctx->system_check_started == false)
			{
				gtk_widget_set_sensitive(GTK_WIDGET(ctx->up_btn), true);
			}
			else
				gtk_widget_set_sensitive(GTK_WIDGET(ctx->up_btn), false);

			gtk_widget_set_sensitive(GTK_WIDGET(ctx->down_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->translate_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->rotate_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->combined_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->system_check_btn), true);
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ctx->translate_btn), false);
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ctx->rotate_btn), false);
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ctx->combined_btn), false);

			SPDLOG_LOGGER_DEBUG(ctx->logger_control, "Setting PLC managed leds to GREEN color.");
			ctx->plc_controller->SetDesignLeds(ctx->GetPlcManagedLedsConf(rtkcommunication::RGBColor::GREEN));
			ctx->plc_controller->SetFunctionLeds(ctx->GetPlcManagedLedsConf(rtkcommunication::RGBColor::GREEN));
			if (ctx->server != nullptr && ctx->server->IsMicroControllerConnected)
			{
				SPDLOG_LOGGER_DEBUG(ctx->logger_control, "Setting tool adapter leds to GREEN color.");
				ctx->server->sessionMicroController->SetLeds(
					ctx->GetToolAdapterLedsConf(rtkcommunication::RGBColor::GREEN, rtkcommunication::LedMode::CONSTANT));
			}

			break;

		case rtkcommunication::IDLE_LIFTED:
			SPDLOG_LOGGER_DEBUG(ctx->logger_control, "IDLE_LIFTED.");

			gtk_widget_set_sensitive(GTK_WIDGET(ctx->up_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->down_btn), true);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->translate_btn), true);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->rotate_btn), true);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->combined_btn), true);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->system_check_btn), false);
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ctx->translate_btn), false);
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ctx->rotate_btn), false);
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ctx->combined_btn), false);

			SPDLOG_LOGGER_DEBUG(ctx->logger_control, "Setting PLC managed leds to GREEN color.");
			ctx->plc_controller->SetDesignLeds(ctx->GetPlcManagedLedsConf(rtkcommunication::RGBColor::GREEN));
			ctx->plc_controller->SetFunctionLeds(ctx->GetPlcManagedLedsConf(rtkcommunication::RGBColor::GREEN));
			if (ctx->server != nullptr && ctx->server->IsMicroControllerConnected)
			{
				SPDLOG_LOGGER_DEBUG(ctx->logger_control, "Setting tool adapter leds to GREEN color.");
				ctx->server->sessionMicroController->SetLeds(
					ctx->GetToolAdapterLedsConf(rtkcommunication::RGBColor::GREEN, rtkcommunication::LedMode::CONSTANT));
			}

			break;

		case rtkcommunication::JOYSTICK_HALTED:
			SPDLOG_LOGGER_DEBUG(ctx->logger_control, "JOYSTICK_HALTED.");

			gtk_widget_set_sensitive(GTK_WIDGET(ctx->up_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->down_btn), true);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->translate_btn), true);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->rotate_btn), true);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->combined_btn), true);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->system_check_btn), false);

			SPDLOG_LOGGER_DEBUG(ctx->logger_control, "Setting PLC managed leds to GREEN color.");
			ctx->plc_controller->SetDesignLeds(ctx->GetPlcManagedLedsConf(rtkcommunication::RGBColor::GREEN));
			ctx->plc_controller->SetFunctionLeds(ctx->GetPlcManagedLedsConf(rtkcommunication::RGBColor::GREEN));
			if (ctx->server != nullptr && ctx->server->IsMicroControllerConnected)
			{
				SPDLOG_LOGGER_DEBUG(ctx->logger_control, "Setting tool adapter leds to GREEN color.");
				ctx->server->sessionMicroController->SetLeds(
					ctx->GetToolAdapterLedsConf(rtkcommunication::RGBColor::GREEN, rtkcommunication::LedMode::CONSTANT));
			}

			g_idle_add([](gpointer data) -> gboolean
			{
				OpContext* ctx = (OpContext*)data;
				OpState* state = static_cast<OpState*>(ctx->GetActiveState());

				sleep(1);
				
				SPDLOG_LOGGER_DEBUG(ctx->logger_control, "JOYSTICK_HALTED distances: {}, {}, {}.", ctx->plc_controller->GetDistanceVariables()[0],
																										ctx->plc_controller->GetDistanceVariables()[1],
																											ctx->plc_controller->GetDistanceVariables()[2]);
				
				SPDLOG_LOGGER_DEBUG(ctx->logger_ctrl_snapshot, "P/F_8_ROB_DRIVE_UNIT_MOVEMENTS_AFTER_ENABLING_RELEASE {}.", rtkcommunication::JsonObject::JsonSerialize<std::array<float,2>>({ctx->plc_controller->GetDistanceVariables()[0], ctx->plc_controller->GetDistanceVariables()[1]}));

				return false;
			}, ctx);

			break;

		case rtkcommunication::JOYSTICK_READY:
			SPDLOG_LOGGER_DEBUG(ctx->logger_control, "JOYSTICK_READY.");

			gtk_widget_set_sensitive(GTK_WIDGET(ctx->up_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->down_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->translate_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->rotate_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->combined_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->system_check_btn), false);

			SPDLOG_LOGGER_DEBUG(ctx->logger_control, "Setting PLC managed leds to YELLOW color.");
			ctx->plc_controller->SetDesignLeds(ctx->GetPlcManagedLedsConf(rtkcommunication::RGBColor::YELLOW));
			ctx->plc_controller->SetFunctionLeds(ctx->GetPlcManagedLedsConf(rtkcommunication::RGBColor::YELLOW));
			if (ctx->server != nullptr && ctx->server->IsMicroControllerConnected)
			{
				SPDLOG_LOGGER_DEBUG(ctx->logger_control, "Setting tool adapter leds to YELLOW color.");
				ctx->server->sessionMicroController->SetLeds(
					ctx->GetToolAdapterLedsConf(rtkcommunication::RGBColor::YELLOW, rtkcommunication::LedMode::CONSTANT));
			}

			if (ctx->plc_controller->GetCollisionState() == false)
				ctx->pc_collision_detected->Show();

			break;

		case rtkcommunication::JOYSTICK_ON:
			SPDLOG_LOGGER_DEBUG(ctx->logger_control, "JOYSTICK_ON.");

			gtk_widget_set_sensitive(GTK_WIDGET(ctx->up_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->down_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->translate_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->rotate_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->combined_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->system_check_btn), false);

			SPDLOG_LOGGER_DEBUG(ctx->logger_control, "Setting PLC managed leds to YELLOW color.");
			ctx->plc_controller->SetDesignLeds(ctx->GetPlcManagedLedsConf(rtkcommunication::RGBColor::YELLOW));
			ctx->plc_controller->SetFunctionLeds(ctx->GetPlcManagedLedsConf(rtkcommunication::RGBColor::YELLOW));
			if (ctx->server != nullptr && ctx->server->IsMicroControllerConnected)
			{
				SPDLOG_LOGGER_DEBUG(ctx->logger_control, "Setting tool adapter leds to YELLOW color.");
				ctx->server->sessionMicroController->SetLeds(
					ctx->GetToolAdapterLedsConf(rtkcommunication::RGBColor::YELLOW, rtkcommunication::LedMode::CONSTANT));
			}

			break;

		case rtkcommunication::ENABLE_WARNING:
			SPDLOG_LOGGER_DEBUG(ctx->logger_control, "ENABLE_WARNING.");

			gtk_widget_set_sensitive(GTK_WIDGET(ctx->up_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->down_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->translate_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->rotate_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->combined_btn), false);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->system_check_btn), false);

			SPDLOG_LOGGER_DEBUG(ctx->logger_control, "Setting PLC managed leds to GREEN color.");
			ctx->plc_controller->SetDesignLeds(ctx->GetPlcManagedLedsConf(rtkcommunication::RGBColor::GREEN));
			ctx->plc_controller->SetFunctionLeds(ctx->GetPlcManagedLedsConf(rtkcommunication::RGBColor::GREEN));
			if (ctx->server != nullptr && ctx->server->IsMicroControllerConnected)
			{
				SPDLOG_LOGGER_DEBUG(ctx->logger_control, "Setting tool adapter leds to GREEN color.");
				ctx->server->sessionMicroController->SetLeds(
					ctx->GetToolAdapterLedsConf(rtkcommunication::RGBColor::GREEN, rtkcommunication::LedMode::CONSTANT));
			}
			
			break;

		case rtkcommunication::POSE_CONTROLLER_HALTED:
			SPDLOG_LOGGER_DEBUG(ctx->logger_control, "POSE_CONTROLLER_HALTED.");
			
			g_idle_add([](gpointer data) -> gboolean
			{
				OpContext* ctx = (OpContext*)data;
				OpState* state = static_cast<OpState*>(ctx->GetActiveState());

				ctx->pc_positioning_halted->Show();
				
				return false;
			}, ctx);

			break;

		case rtkcommunication::POSE_CONTROLLER_READY:
			SPDLOG_LOGGER_DEBUG(ctx->logger_control, "POSE_CONTROLLER_READY.");

			g_idle_add([](gpointer data) -> gboolean
			{
				OpContext* ctx = (OpContext*)data;
				OpState* state = static_cast<OpState*>(ctx->GetActiveState());

				ctx->pc_positioning_halted->Hide();

				if (ctx->plc_controller->GetCollisionState() == false)
					ctx->pc_collision_detected->Show();
				else 
					ctx->pc_positioning_ready->Show();
				
				return false;
			}, ctx);

			break;

		case rtkcommunication::POSE_CONTROLLER_ON:
			SPDLOG_LOGGER_DEBUG(ctx->logger_control, "POSE_CONTROLLER_ON.");

			g_idle_add([](gpointer data) -> gboolean
			{
				OpContext* ctx = (OpContext*)data;
				OpState* state = static_cast<OpState*>(ctx->GetActiveState());

				ctx->pc_positioning_halted->Hide();
				ctx->pc_positioning_ready->Hide();
				
				return false;
			}, ctx);

			break;

		case rtkcommunication::PLC_NOT_CONNECTED:
			SPDLOG_LOGGER_DEBUG(ctx->logger_control, "MOBILE_TO_PLC_DISCONNECTED.");

			if (reconnect_thread != nullptr)
			{
				if (reconnect_thread->joinable())
					reconnect_thread->join();
				
				else
					reconnect_thread->detach();

				delete reconnect_thread;
			}

			reconnect_thread = new std::thread( [ctx] ()
			{
				std::cout << "Disconnection detected " << std::endl;
				sleep(7);

				if (ctx->mobile_state == rtkcommunication::PLC_NOT_CONNECTED)
				{
					ctx->mobile_client->Reconnect();
					sleep(8);

					if (ctx->mobile_state == rtkcommunication::PLC_NOT_CONNECTED)
					{		
						OpState* state = static_cast<OpState*>(ctx->GetActiveState());
						state->MobileRefresh(ctx);
					}
				}

			});	
		

			break;

		default:
			break;
	}
}

void OpState::MobileRefresh(OpContext *ctx)
{	
	if (mobile_reconnect_thread != nullptr)
	{
		if (mobile_reconnect_thread->joinable())
			mobile_reconnect_thread->join();
		
		else
			mobile_reconnect_thread->detach();

		delete mobile_reconnect_thread;
	}

	mobile_reconnect_thread = new std::thread( [ctx] ()
	{	
		OpState* state = static_cast<OpState*>(ctx->GetActiveState());
		std::cout << "RefreshDriveButtons called_2 " << std::endl;

		state->RefreshDriveButtons(ctx);
		
	});			

}

void OpState::OnHomingConfirmed(OpContext *ctx)
{
	ctx->mobile_client->StartHoming();

	ctx->pc_homing_in_progress->Show();
	ctx->pc_homing_in_progress->ShowSpinner();

	while (ctx->mobile_state == rtkcommunication::mobile_state_type::HOMING_NEEDED)
		usleep(100000);
	
	SPDLOG_LOGGER_DEBUG(ctx->logger_control, "OnHomingFinished start.");

	g_idle_add(G_SOURCE_FUNC(OpState::OnHomingFinished), ctx);	

}

gboolean OpState::OnHomingFinished(OpContext *ctx)
{	
	if (ctx->mobile_state == rtkcommunication::mobile_state_type::IDLE_LOWERED)
	{	
		ctx->pc_homing_in_progress->Hide();
		ctx->pc_homing_in_progress->HideSpinner();

		// OpState* state = ctx->GetActiveState();
		// if (StartupState* start_state = dynamic_cast<StartupState*>(state); start_state != nullptr)
		// {	
		// 	if (ctx->plc_controller->CheckReferencing() == false)
		// 	{
		// 		ctx->pc_system_check = std::make_unique<rtkcommon::PopupController>(GTK_WINDOW(ctx->getGobj()),
		// 				"Press OK to proceed with robot arm system check", "Ok", "Cancel", false,
		// 			std::bind(&OpState::OnOkStartSystemCheck, ctx),
		// 			std::bind(&OpState::OnCancelSystemCheck, ctx));
				
		// 		ctx->pc_system_check->Show();
		// 	}
		// }

		return G_SOURCE_REMOVE;
	}
	else if (ctx->mobile_state == rtkcommunication::mobile_state_type::ESTOP_DISABLED)
	{	
		ctx->pc_homing_in_progress->Hide();
		ctx->pc_homing_in_progress->HideSpinner();

		ctx->pc_homing_halted->Hide();
		ctx->pc_homing_ready->Hide();
		
		ctx->mobile_client->StopHoming();
		return G_SOURCE_REMOVE;

	}	

	return G_SOURCE_CONTINUE;
}

void OpState::OnOkStartSystemCheck(OpContext *ctx)
{	
	OpState* state = ctx->GetActiveState();

	if (StartupState* start_state = dynamic_cast<StartupState*>(state); start_state != nullptr)
	{
		start_state->OnSystemCheck(GTK_WIDGET(ctx->system_check_btn), ctx);
	}

}

void OpState::OnCancelSystemCheck(OpContext *ctx)
{
	
}

void OpState::OnEnableReset(OpContext *ctx)
{
	ctx->mobile_client->EnableReset();

	SPDLOG_LOGGER_DEBUG(ctx->logger_control, "Setting PLC managed leds to YELLOW color.");
	ctx->plc_controller->SetDesignLeds(ctx->GetPlcManagedLedsConf(rtkcommunication::RGBColor::YELLOW));
	ctx->plc_controller->SetFunctionLeds(ctx->GetPlcManagedLedsConf(rtkcommunication::RGBColor::YELLOW));
	if (ctx->server != nullptr && ctx->server->IsMicroControllerConnected)
	{
		SPDLOG_LOGGER_DEBUG(ctx->logger_control, "Setting tool adapter leds to YELLOW color.");
		ctx->server->sessionMicroController->SetLeds(
			ctx->GetToolAdapterLedsConf(rtkcommunication::RGBColor::YELLOW, rtkcommunication::LedMode::CONSTANT));
	}
}

void OpState::OnStopMobilePlatformOperation(OpContext *ctx)
{
	switch (ctx->mobile_state)
	{	
		case rtkcommunication::HOMING_CONTROLLER_HALTED:
			SPDLOG_LOGGER_DEBUG(ctx->logger_control, "HOMING_STOPPED.");
			ctx->mobile_client->StopHoming();
			break;

		case rtkcommunication::LIFTING_CONTROLLER_HALTED:
			SPDLOG_LOGGER_DEBUG(ctx->logger_control, "LIFTING_STOPPED.");
			ctx->mobile_client->StopLiftSystem();
			break;

		case rtkcommunication::POSE_CONTROLLER_HALTED:
			SPDLOG_LOGGER_DEBUG(ctx->logger_control, "POSITIONING_STOPPED.");
			ctx->mobile_client->StopPositioning();
			break;

		default:
			break;
	}
}

void OpState::OnMasteringConfirmed(OpContext *ctx)
{
	if (ctx->plc_controller->IsToolMounted())
	{
		ctx->pc_mastering->Show();
	}
	else
	{
		ctx->server->sessionRobotController->StartMastering(ctx->GetOperationPlan(), std::bind(&OpState::OnMasteringDone, this, ctx));
		ctx->pc_mastering_shown = false;
	}
}

void OpState::OnMasteringDone(OpContext *ctx)
{
	ctx->server->sessionRobotController->StartSystemCheck(ctx->GetOperationPlan(),
		std::bind(&OpState::OnMasteringSystemCheckDone, this, ctx),
		std::bind(&OpState::OnMasteringSystemCheckInitialized, this, ctx),
		std::bind(&OpState::OnMasteringSystemCheckError, this, ctx, std::placeholders::_1));
}

void OpState::OnMasteringSystemCheckDone(OpContext *ctx)
{
	ctx->plc_controller->DisableSystemCheck();
}

void OpState::OnMasteringSystemCheckInitialized(OpContext *ctx)
{
	ctx->server->sessionRobotController->StartReferencing(std::bind(&OpState::OnMasteringReferencingDone, this, ctx));
}

void OpState::OnMasteringSystemCheckError(OpContext *ctx, int error_code)
{
	SPDLOG_LOGGER_ERROR(ctx->logger_control, "Mastering system check error: {}.", error_code);
}

void OpState::OnMasteringReferencingDone(OpContext *ctx)
{
	ctx->server->sessionRobotController->EndSystemCheck();
}

bool OpState::OnRecoveryRobotStartRequest(OpContext *ctx)
{
	rtkcommon::PopupController pc(GTK_WINDOW(ctx->getGobj()), "Recovery needed. Do you want to start recovery process?", "Ok", "Cancel", false);
	int response = pc.GetResult();

	if (response == 1)
	{
		ctx->plc_controller->ResumeRobot();
		return ctx->plc_controller->IsFootswitchActive();
	}
	else
		return false;
}

void OpState::OnWithoutRecovery(OpContext *ctx)
{
	SPDLOG_LOGGER_DEBUG(ctx->logger_control, "Recovery not needed.");

	ctx->plc_controller->ResumeRobot();
}

void OpState::OnRecoveryDone(OpContext *ctx)
{
	SPDLOG_LOGGER_DEBUG(ctx->logger_control, "Recovery done.");

	ctx->plc_controller->ResumeRobot();
}

void OpState::OnRecoveryError(OpContext *ctx)
{
	SPDLOG_LOGGER_ERROR(ctx->logger_control, "Recovery error!");

	ctx->plc_controller->AbortRobot();
	ctx->robot_initialized = false;
}

void OpState::UpdatePlayTimeline(GtkRange* timeline, int frame, OpContext *ctx)
{
	if (timeline != nullptr)
		gtk_range_set_value(timeline, frame);
	else
		SPDLOG_LOGGER_DEBUG(ctx->logger_control, "Timeline is null!");
}

void OpState::WaitFootswitchRelease(OpContext *ctx)
{
	if (ctx->plc_controller->IsFootswitchActive())
	{
		auto pc = std::make_unique<rtkcommon::PopupController>(GTK_WINDOW(ctx->getGobj()), "Reactivate footswitch to continue...", true);
		pc->Show();

		while(ctx->plc_controller->IsFootswitchActive())
		{
			usleep(100000);
		}

		pc->Hide();
	}
}

void OpState::OnOkMoveToTransportPose(OpContext* ctx)
{
	SPDLOG_LOGGER_DEBUG(ctx->logger_control, "OnTransport.");

	OpState* state = dynamic_cast<OpState*>(ctx->GetActiveState());

	// ctx->GetActiveState()->WaitFootswitchRelease(ctx);
	ctx->movement_guide->GuideArmToTransport(ctx->GetOperationPlan(), ctx->server, ctx->robot_status, std::bind(&OpState::OnTransportReached, state, ctx));
	
}

void OpState::OnTransportReached(OpContext *ctx)
{	

	std::cout << "OnTransportReached" << std::endl;

	OpState* state = dynamic_cast<OpState*>(ctx->GetActiveState());

	g_idle_add([](gpointer data) -> gboolean
		{
			OpContext* ctx = (OpContext*)data;

			gtk_label_set_text(ctx->hint_bar_label, "The robot arrived in transport pose");
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->transport_position_btn), true);
			gtk_widget_set_sensitive(GTK_WIDGET(ctx->back_btn), true);

			if (ctx->robot_operation_cancelled && ctx->current_state == 0)
			{
				ctx->robot_operation_cancelled = false;
				gtk_widget_set_sensitive(GTK_WIDGET(ctx->system_check_btn), true);
			}

			if (ctx->robot_operation_cancelled && ctx->current_state == 6)
			{
				ctx->robot_operation_cancelled = false;
				gtk_widget_set_sensitive(GTK_WIDGET(ctx->start_localization_btn), true);
			}

			if (OperationState* op_state = dynamic_cast<OperationState*>(ctx->GetActiveState());
					ctx->robot_operation_cancelled && op_state != nullptr)
			{
				gtk_widget_set_sensitive(GTK_WIDGET(ctx->start_traj_btn), true);
				gtk_widget_remove_css_class(GTK_WIDGET(ctx->start_traj_btn), "round_button_style");
				gtk_widget_add_css_class(GTK_WIDGET(ctx->start_traj_btn), "round_button_style_suggested");
			}
			return false;
		}, ctx);
}

void OpState::OnCancelMoveToTransportPose(OpContext* ctx)
{
	gtk_label_set_label(ctx->hint_bar_label, "Robot movement cancelled.");
}
