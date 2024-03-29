// g++ -o log_daily -I/home/leegs/com_vender/spdlog/include -L/home/leegs/com_vender/spdlog/lib -l spdlog log_daily.cpp

#include <iostream>
#include <memory>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/daily_file_sink.h"

int main(int, char **)
{
	try
	{
        // Create a daily logger - a new file is created every day on 2:30am
        //auto daily_logger = spd::daily_logger_mt("daily_logger", "logs/daily.txt", 2, 30);
		auto daily_logger = spdlog::daily_logger_mt("daily_logger", "logs/daily.txt");
        // trigger flush if the log severity is error or higher
        daily_logger->flush_on(spdlog::level::err);
        daily_logger->info(123.44);
	}
	catch (const spdlog::spdlog_ex &ex)
    {
        std::cout << "Log init failed: " << ex.what() << std::endl;
        return 1;
    }
};
