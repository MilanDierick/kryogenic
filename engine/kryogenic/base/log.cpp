#include "log.hpp"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks-inl.h>

namespace kryogenic {
	namespace {
		std::unique_ptr<spdlog::logger> g_logger = {};
	}
} // kryogenic

namespace kryogenic {
	auto log_init() -> void {
		g_logger = std::make_unique<spdlog::logger>("kryogenic", std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
		g_logger->set_level(spdlog::level::trace);
		trace("Greetings and salutations from Kryogenic! Prepare for a frosty reception!");
	}

	auto log_fini() -> void {
		trace("Kryogenic is shutting down. We hope you enjoyed your stay!");
		g_logger.reset();
	}

	auto message(log_lvl const level, std::string_view const& msg) -> void {
		switch (level) {
			case log_lvl::trace:
				g_logger->trace(msg);
				break;
			case log_lvl::debug:
				g_logger->debug(msg);
				break;
			case log_lvl::info:
				g_logger->info(msg);
				break;
			case log_lvl::warning:
				g_logger->warn(msg);
				break;
			case log_lvl::error:
				g_logger->error(msg);
				break;
			case log_lvl::fatal:
				g_logger->critical(msg);
				break;
		}
	}

	auto trace(std::string_view const& msg) -> void {
		message(log_lvl::trace, msg);
	}

	auto debug(std::string_view const& msg) -> void {
		message(log_lvl::debug, msg);
	}

	auto info(std::string_view const& msg) -> void {
		message(log_lvl::info, msg);
	}

	auto warn(std::string_view const& msg) -> void {
		message(log_lvl::warning, msg);
	}

	auto error(std::string_view const& msg) -> void {
		message(log_lvl::error, msg);
	}

	auto fatal(std::string_view const& msg) -> void {
		message(log_lvl::fatal, msg);
	}
} // kryogenic
