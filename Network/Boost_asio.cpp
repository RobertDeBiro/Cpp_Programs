#include "rtkcommunication/Common/Session.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>

using namespace rtkcommunication;


Session::Session() 
	: _io_service(new boost::asio::io_service()),
	_socket(new boost::asio::ip::tcp::socket(*_io_service)),
	_strand(new boost::asio::io_service::strand(*_io_service)),
	OnReceiveUpdate(nullptr), 
	OnSendUpdate(nullptr), 
	OnSendComplete(nullptr),
	_write_msgs_size(0),
	_total_write_size(0),
	_read_msgs_size(0),
	_total_read_size(0),
	OnConnectionError(nullptr)
{	
}

Session::Session(boost::asio::io_service* io_service, boost::asio::io_service::strand* strand)
	: _io_service(io_service), 
	_socket(new boost::asio::ip::tcp::socket(*_io_service)), 
	_strand(strand),
	OnReceiveUpdate(nullptr),
	OnSendUpdate(nullptr), 
	OnSendComplete(nullptr),
	_write_msgs_size(0),
	_total_write_size(0),
	_read_msgs_size(0),
	_total_read_size(0),
	OnConnectionError(nullptr)
{	
}

rtkcommunication::Session::Session(boost::asio::io_service *io_service, boost::asio::io_service::strand *strand, std::function<void(std::string)> OnConnectionError)
	: _io_service(io_service), 
	_socket(new boost::asio::ip::tcp::socket(*_io_service)), 
	_strand(strand),
	OnReceiveUpdate(nullptr),
	OnSendUpdate(nullptr), 
	OnSendComplete(nullptr),
	_write_msgs_size(0),
	_total_write_size(0),
	_read_msgs_size(0),
	_total_read_size(0),
	OnConnectionError(OnConnectionError)
{
}

Session::~Session()
{
}

boost::asio::ip::tcp::socket& Session::GetSocket()
{
	return *_socket;
}

void Session::Start()
{
}

void Session::Connect(std::string ip, std::string port, std::function<void()> OnConnected, std::function<void(std::string)> OnConnectionError)
{
	this->OnConnected = OnConnected;
	this->OnConnectionError = OnConnectionError;

	boost::asio::ip::tcp::resolver *resolver = new boost::asio::ip::tcp::resolver(*_io_service);
	boost::asio::ip::tcp::resolver::query query(ip, port);
	boost::asio::ip::tcp::resolver::iterator iterator = resolver->resolve(query);

	boost::asio::async_connect(*_socket, iterator,
		_strand->wrap(boost::bind(&Session::HandleConnect, this,
			boost::asio::placeholders::error)));

	_com_thread = new boost::thread(boost::bind(&boost::asio::io_service::run, _io_service));
}

void Session::HandleConnect(const boost::system::error_code& error)
{
	if (!error)
	{
		int yes = 1;
		setsockopt(_socket->native_handle(), SOL_SOCKET, SO_KEEPALIVE, &yes, sizeof(int));

		int idle = 10;
		setsockopt(_socket->native_handle(), IPPROTO_TCP, TCP_KEEPIDLE, &idle, sizeof(int));

		int interval = 10;
		setsockopt(_socket->native_handle(), IPPROTO_TCP, TCP_KEEPINTVL, &interval, sizeof(int));

		int maxpkt = 1000000;
		setsockopt(_socket->native_handle(), IPPROTO_TCP, TCP_KEEPCNT, &maxpkt, sizeof(int));
		
		if (OnConnected)
		{
			OnConnected();
		}

		boost::asio::async_read(*_socket, boost::asio::buffer(_read_msg, MAX_IP_PACK_SIZE),
			boost::asio::transfer_exactly(sizeof(size_t)),
			_strand->wrap(boost::bind(&Session::HandleRead, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred,
				std::function<void(const char*, size_t)>(std::bind(&Session::HandleRequests, this, std::placeholders::_1, std::placeholders::_2)))));

	}
	else
	{
		std::cerr << error.message() << std::endl;

		if (OnConnectionError)
		{
			OnConnectionError(error.message());
		}
	}
}

void Session::HandleRequests(const char* data, size_t size)
{
	std::string msg(data, data + size);

	SPDLOG_LOGGER_DEBUG(spdlog::get("rtkcommunication"), "Session received: {}.", msg);

	boost::asio::async_read(*_socket, boost::asio::buffer(_read_msg, MAX_IP_PACK_SIZE),
			boost::asio::transfer_exactly(sizeof(size_t)),
			_strand->wrap(boost::bind(&Session::HandleRead, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred,
				std::function<void(const char*, size_t)>(std::bind(&Session::HandleRequests, this, std::placeholders::_1, std::placeholders::_2)))));
}

void Session::HandleRead(const boost::system::error_code& error, size_t bytes_transferred, std::function<void(const char*, size_t)> callback)
{
	if (!error)
	{
		if (_read_msgs.size() == 0)
		{
			std::memcpy(&_read_msgs_size, _read_msg.data(), sizeof(_read_msgs_size));
		}

		_read_msgs.push_back(_read_msg);
		_total_read_size += bytes_transferred;


		if (_total_read_size < _read_msgs_size)
		{
			size_t read_size = _read_msgs_size - _total_read_size > MAX_IP_PACK_SIZE ? MAX_IP_PACK_SIZE : _read_msgs_size - _total_read_size;

			boost::asio::async_read(*_socket, boost::asio::buffer(_read_msg, MAX_IP_PACK_SIZE),
				boost::asio::transfer_exactly(read_size),
				_strand->wrap(boost::bind(&Session::HandleRead, this,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred,
					callback)));
		}
		else
		{
			char* msg = new char[_total_read_size];

			int offset = 0;
			for (int i = 0; i < _read_msgs.size() - 1; i++)
			{
				int copy_size = _total_read_size - offset > MAX_IP_PACK_SIZE ? MAX_IP_PACK_SIZE : _total_read_size - offset;

				memcpy(msg + offset, _read_msgs[i + 1].data(), copy_size);
				offset += copy_size;
			}

			_read_msgs.clear();

			callback(msg, _total_read_size - sizeof(_read_msgs_size));
			_total_read_size = 0;
			delete[] msg;
		}
	}
	else
	{
		std::cerr << error.message() << std::endl;
		if (OnConnectionError != nullptr)
		{
			OnConnectionError(error.message());
		}
	}
}

void Session::HandleReadFolder(const boost::system::error_code& error, size_t bytes_transferred, Folder& folder, std::function<void()> callback)
{
	if (!error)
	{
		if (folder.rcvd_files < folder.files.size())
		{
			File& file = folder.files[folder.rcvd_files];
			if (file.rcvd_size < file.size)
			{
				std::string filepath = TEMP_FOLDER + folder.GetFolderName() + "/" + file.file_name;
				std::filesystem::create_directories(std::filesystem::path(filepath).parent_path());

				std::ofstream output_file(filepath, std::ios::binary | std::ios::app);

				if (file.size - file.rcvd_size < MAX_IP_PACK_SIZE)
				{
					output_file.write(_read_msg.data(), file.size - file.rcvd_size);
					_read_msgs_size += file.size - file.rcvd_size;
					file.rcvd_size += file.size - file.rcvd_size;

					if (OnReceiveUpdate)
						OnReceiveUpdate((float)_read_msgs_size / (float)folder.GetTotalSize() * 100);

					folder.rcvd_files++;

					if (folder.rcvd_files == folder.files.size())
					{
						callback();
						return;
					}
				}
				else
				{
					output_file.write(_read_msg.data(), bytes_transferred);
					file.rcvd_size += bytes_transferred;
					_read_msgs_size += bytes_transferred;

					if (OnReceiveUpdate)
						OnReceiveUpdate((float)_read_msgs_size / (float)folder.GetTotalSize() * 100);
				}

				output_file.close();
			}
			else
			{
				folder.rcvd_files++;
			}

			boost::asio::async_read(*_socket, boost::asio::buffer(_read_msg, MAX_IP_PACK_SIZE),
				boost::asio::transfer_all(),
				_strand->wrap(boost::bind(&Session::HandleReadFolder, this,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred,
					folder,
					callback)));
		}
		else 
		{
			callback();
		}
	}
	else
	{
		std::cerr << error.message() << std::endl;
	}	
}

void Session::HandleWrite(const boost::system::error_code& error, size_t bytes_transferred)
{
	if (!error)
	{
		_write_msgs.pop_front();
		_write_msgs_size -= bytes_transferred;

		if (!_write_msgs.empty())
		{
			size_t msg_size = _write_msgs_size > MAX_IP_PACK_SIZE ? MAX_IP_PACK_SIZE : _write_msgs_size;

			boost::asio::async_write(*_socket, boost::asio::buffer(_write_msgs.front().data(), msg_size),
				boost::asio::transfer_exactly(msg_size),
				_strand->wrap(boost::bind(&Session::HandleWrite, this,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred)));
		}
		else
		{
			_total_write_size = 0;
			_mutex_write.unlock();
		}
	}
	else
	{
		std::cerr << error.message() << std::endl;

		if (OnConnectionError != nullptr)
		{
			OnConnectionError(error.message());
		}
	}
}

void Session::HandleWriteFolder(const boost::system::error_code& error, size_t bytes_transferred)
{
	if (!error)
	{
		_write_msgs.pop_front();
		_write_msgs_size -= bytes_transferred;

		if (OnSendUpdate)
			OnSendUpdate((1 - (float)_write_msgs_size / (float)_total_write_size) * 100);

		if (!_write_msgs.empty())
		{
			size_t msg_size = _write_msgs_size > MAX_IP_PACK_SIZE ? MAX_IP_PACK_SIZE : _write_msgs_size;

			boost::asio::async_write(*_socket, boost::asio::buffer(_write_msgs.front().data(), msg_size),
				boost::asio::transfer_exactly(msg_size),
				_strand->wrap(boost::bind(&Session::HandleWriteFolder, this,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred)));
		}
		else
		{
			if (OnSendComplete)
			{
				OnSendComplete();
				OnSendComplete = nullptr;
			}
			OnSendUpdate = nullptr;
			_total_write_size = 0;
		}
	}
	else
	{
		std::cerr << error.message() << std::endl;
	}
}

void Session::Write(const char* msg, size_t size)
{
	_mutex_write.lock();
	_write_msgs_size = size + sizeof(size);
	_total_write_size = size + sizeof(size);

	std::array<char, MAX_IP_PACK_SIZE> write_msg;
	char* _total_size = static_cast<char*>(static_cast<void*>(&_total_write_size));
	std::copy(_total_size, _total_size + sizeof(_total_write_size), write_msg.begin());
	_write_msgs.push_back(write_msg);

	for (size_t i = 0; i < size; i += MAX_IP_PACK_SIZE)
	{
		std::array<char, MAX_IP_PACK_SIZE> write_msg;
		size_t msg_size = (size - i) > MAX_IP_PACK_SIZE ? MAX_IP_PACK_SIZE : size - i;

		std::copy(msg + i, msg + i + msg_size, write_msg.begin());

		_write_msgs.push_back(write_msg);
	}

	if (_write_msgs.size() > 0)
	{
		size_t msg_size = sizeof(size);

		boost::asio::async_write(*_socket, boost::asio::buffer(_write_msgs.front().data(), msg_size),
			boost::asio::transfer_exactly(msg_size),
			_strand->wrap(boost::bind(&Session::HandleWrite, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred)));
	}
}

void Session::WriteFolder(Folder& folder)
{
	_write_msgs_size = 0;

	for (File fileDescr : folder.files)
	{
		// Make full file path
		std::string filepath = folder.folder_path + "/";
		filepath += fileDescr.file_name;

		std::ifstream file;
		file.open(filepath, std::ios::in | std::ios::binary | std::ios::ate);

		if (file.is_open())
		{
			size_t size = fileDescr.size;

			for (size_t i = 0; i <= size; i += MAX_IP_PACK_SIZE) // Send empty message at the end if size % MAX_IP_PACK_SIZE == 0
			{
				std::array<char, MAX_IP_PACK_SIZE> write_msg;
				size_t msg_size = (size - i) > MAX_IP_PACK_SIZE ? MAX_IP_PACK_SIZE : size - i;
				file.seekg(i, std::ios::beg);
				file.read(write_msg.data(), msg_size);
				_write_msgs_size += MAX_IP_PACK_SIZE;
				_write_msgs.push_back(write_msg);
			}

			file.close();
		}
		else
		{
			std::cerr << "File not found" << std::endl;
		}
	}
	
	if (_write_msgs.size() > 0)
	{
		_total_write_size = _write_msgs_size;
		boost::asio::async_write(*_socket, boost::asio::buffer(_write_msgs.front().data(), MAX_IP_PACK_SIZE),
			boost::asio::transfer_exactly(MAX_IP_PACK_SIZE),
			_strand->wrap(boost::bind(&Session::HandleWriteFolder, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred)));
	}
}

void Session::Stop()
{
	_socket->close();

	if (_socket != nullptr)
		delete _socket;
	
	_socket = new boost::asio::ip::tcp::socket(*_io_service);
}

void Session::Reset()
{
	_socket->close();

	if (_socket != nullptr)
    {
		delete _socket;
        _socket = nullptr;
    }

    if (_strand != nullptr)
    {
        delete _strand;
        _strand = nullptr;
    }

    _io_service->stop();
    if (_io_service != nullptr)
    {
		delete _io_service;
        _io_service = nullptr;
    }
    
    while (true)
    {
        if (_com_thread->joinable())
        {
            _com_thread->join();
            delete _com_thread;
            break;
        }
    }

    _io_service = new boost::asio::io_service();
	_socket = new boost::asio::ip::tcp::socket(*_io_service);
	_strand = new boost::asio::io_service::strand(*_io_service);
}
