#include "Logger.hpp"

Logger::Logger(const std::string& prefix) : prefix_(prefix)
{
    const std::string testName = getTestName();
    file_.open(testName + ".log", std::ios::trunc);
}

Logger::~Logger()
{
    file_.close();
}

void Logger::log(const Severity severity, const std::string& message)
{
    auto currentTime = std::chrono::system_clock::now();
    auto timePoint = std::chrono::system_clock::to_time_t(currentTime);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&timePoint), "%Y-%m-%d %H:%M:%S") << " [" << severityVec_.at(static_cast<int>(severity)) << "] " << prefix_ << ": " << message << std::endl;
    file_ << ss.str();
}

std::string Logger::getTestName()
{
    const char* testName = std::getenv("TEST_NAME");
    if (testName) return testName;
    return "default_test_name";
}