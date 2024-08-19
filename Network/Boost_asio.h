#pragma once

#include <deque>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <mutex>

#include "rtkcommunication/Common/Data/Folder.h"
#include "rtkcommunication/Common/Data/Request.h"
#include "rtkcommunication/Common/JsonObject.h"

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/thread/thread.hpp>

#define MAX_IP_PACK_SIZE 300000
#define TEMP_FOLDER "temp/"  // WARNING: This folder will be deleted if it exists when the program starts


namespace rtkcommunication

{
	class Session
	{

	public:
		Session();
		Session(boost::asio::io_service* io_service, boost::asio::io_service::strand* strand);
		Session(boost::asio::io_service* io_service, boost::asio::io_service::strand* strand, std::function<void(std::string)> OnConnectionError);
		~Session();

		boost::asio::ip::tcp::socket& GetSocket();

		virtual void Start();

		void Connect(std::string ip, std::string port, std::function<void()> OnConnected = nullptr, std::function<void(std::string)> OnConnectionError = nullptr);
		virtual void HandleConnect(const boost::system::error_code& error);

		virtual void HandleRequests(const char* data, size_t size);
		virtual void HandleRead(const boost::system::error_code& error, size_t bytes_transferred, std::function<void(const char*, size_t)> callback);
		void HandleReadFolder(const boost::system::error_code& error, size_t bytes_transferred, Folder& folder, std::function<void()> callback);
		
		void HandleWrite(const boost::system::error_code& error, size_t bytes_transferred);
		void HandleWriteFolder(const boost::system::error_code& error, size_t bytes_transferred);
		virtual void Write(const char* msg, size_t size);
		void WriteFolder(Folder& folder);

		void Stop();
		void Reset();

	protected:
		boost::asio::io_service *_io_service;
		boost::asio::io_service::strand *_strand;
		boost::asio::ip::tcp::socket *_socket;

		std::array<char, MAX_IP_PACK_SIZE> _read_msg;
		std::deque<std::array<char, MAX_IP_PACK_SIZE> > _write_msgs;
		size_t _write_msgs_size;
		size_t _total_write_size;

		std::deque<std::array<char, MAX_IP_PACK_SIZE> > _read_msgs;
		size_t _read_msgs_size;
		size_t _total_read_size;

		Folder *_folder;

		std::function<void()> OnConnected;
		std::function<void(std::string)> OnConnectionError;
		std::function<void(float)> OnReceiveUpdate;
		std::function<void(float)> OnSendUpdate;
		std::function<void()> OnSendComplete;

		std::mutex _mutex_write;

        boost::thread *_com_thread;
	};
}