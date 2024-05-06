#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;

void init()
{
    logging::add_file_log
    (
        keywords::file_name = "sample_%N.log",                                        /*< file name pattern >*/
        keywords::rotation_size = 10 * 1024 * 1024,                                   /*< rotate files every 10 MiB... >*/
        keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0), /*< ...or at midnight >*/
        keywords::format = "[%TimeStamp%]: %Message%"                                 /*< log record format >*/
    );

    /**
     ** Setting globally filter in the library core
     *  - 'logging::core::get()' - returns logging core instance, i.e., pointer to the core singleton
     */
    logging::core::get()->set_filter(logging::trivial::severity >= logging::trivial::info);
}

int main(int, char*[])
{
    init();

    //* Add commonly used attributes, such as: record counter and time stamp
    logging::add_common_attributes();

    /**
     ** Trivial logging
     *  - The BOOST_LOG_TRIVIAL macro accepts a severity level and results in a stream-like object that supports insertion operator
     *  - as a result of this code, the log messages will be printed on the console
     *  - the library offers a few advantages:
     *      - besides the record message, each log record in the output contains a timestamp, the current thread identifier and severity level
     *      - it is safe to write logs from different threads concurrently, log messages will not be corrupted
     *      - filtering can be applied.
     */
    BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
    BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
    BOOST_LOG_TRIVIAL(info) << "An informational severity message";
    BOOST_LOG_TRIVIAL(warning) << "A warning severity message";
    BOOST_LOG_TRIVIAL(error) << "An error severity message";
    BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";

    return 0;
}