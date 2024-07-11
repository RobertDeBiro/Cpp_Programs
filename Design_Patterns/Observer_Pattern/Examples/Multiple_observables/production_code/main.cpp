#include "PLController.h"
#include "RobotController.h"
#include "AlarmManager.h"

int main()
{
    PLController plController;
    RobotController robotController;
    AlarmManager alarmManager;

    plController.add(&alarmManager);
    robotController.add(&alarmManager);

    plController.setState();
    robotController.setState();
    plController.setState();

    return 0;
}
