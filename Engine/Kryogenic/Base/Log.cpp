#include "Log.hpp"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks-inl.h>

namespace Kryogenic {
	namespace {
		std::unique_ptr<spdlog::logger> gLogger = {};
	}
} // kryogenic

namespace Kryogenic {
	auto LogInit() -> void {
		gLogger = std::make_unique<spdlog::logger>("kryogenic", std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
		gLogger->set_level(spdlog::level::trace);
		Trace("Greetings and salutations from Kryogenic! Prepare for a frosty reception!");
	}

	auto LogFini() -> void {
		Trace("Kryogenic is shutting down. We hope you enjoyed your stay!");
		gLogger.reset();
	}

	auto Message(LogLevel const pLevel, std::string_view const& pMessage) -> void {
		switch (pLevel) {
			case LogLevel::eTrace:
				gLogger->trace(pMessage);
				break;
			case LogLevel::eDebug:
				gLogger->debug(pMessage);
				break;
			case LogLevel::eInfo:
				gLogger->info(pMessage);
				break;
			case LogLevel::eWarning:
				gLogger->warn(pMessage);
				break;
			case LogLevel::eError:
				gLogger->error(pMessage);
				break;
			case LogLevel::eFatal:
				gLogger->critical(pMessage);
				break;
		}
	}

	auto Trace(std::string_view const& pMessage) -> void {
		Message(LogLevel::eTrace, pMessage);
	}

	auto Debug(std::string_view const& pMessage) -> void {
		Message(LogLevel::eDebug, pMessage);
	}

	auto Info(std::string_view const& pMessage) -> void {
		Message(LogLevel::eInfo, pMessage);
	}

	auto Warn(std::string_view const& pMessage) -> void {
		Message(LogLevel::eWarning, pMessage);
	}

	auto Error(std::string_view const& pMessage) -> void {
		Message(LogLevel::eError, pMessage);
	}

	auto Fatal(std::string_view const& pMessage) -> void {
		Message(LogLevel::eFatal, pMessage);
	}
} // kryogenic
