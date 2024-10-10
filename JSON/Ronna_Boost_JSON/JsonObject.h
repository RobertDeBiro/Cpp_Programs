#pragma once

#include "rtkcommunication/Common/BoostReflection.h"

#include <boost/describe/class.hpp>

namespace rtkcommunication
{
class JsonObject
{
public:
	template<typename T> static std::string JsonSerialize(T obj)
	{
		return boost::json::serialize(boost::json::value_from(obj));
	}

	template<typename T> static T JsonDeserialize(std::string json)
	{
		boost::json::value v = boost::json::parse(json);
		T op = boost::json::value_to<T>(v);
		return op;
	}
};

}