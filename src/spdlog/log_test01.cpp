// g++ -o log_test01 -I/home/leegs/com_vender/spdlog/include -L/home/leegs/com_vender/spdlog/lib -l spdlog log_test01.cpp

#include <cstdio>
#include <chrono>

#include "spdlog/spdlog.h"
#include "spdlog/cfg/env.h"
#include "spdlog/fmt/ostr.h"

int main(int, char **)
{
	spdlog::cfg::load_env_levels();
	
	spdlog::info("Welcome to spdlog version {}.{}.{} !", 
			SPDLOG_VER_MAJOR, SPDLOG_VER_MINOR, SPDLOG_VER_PATCH);
			
    spdlog::warn("Easy padding in numbers like {:08d}", 12);
    spdlog::critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
    spdlog::info("Support for floats {:03.2f}", 1.23456);
    spdlog::info("Positional args are {1} {0}..", "too", "supported");
    spdlog::info("{:>8} aligned, {:<8} aligned", "right", "left");
	spdlog::info("");
	
    // Runtime log levels
    spdlog::set_level(spdlog::level::info); // Set global log level to info
    spdlog::debug("This message should not be displayed!");
    spdlog::set_level(spdlog::level::trace); // Set specific logger's log level
    spdlog::debug("This message should be displayed..");
	spdlog::info("");
	
	// Customize msg format for all loggers
    spdlog::set_pattern("[%H:%M:%S %z] [%^%L%$] [thread %t] %v");
    spdlog::info("This an info message with custom format");
    spdlog::set_pattern("%+"); // back to default format
    spdlog::set_level(spdlog::level::info);
};