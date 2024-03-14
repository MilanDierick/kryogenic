#ifndef KRYOGENIC_BASE_LOG_HPP
#define KRYOGENIC_BASE_LOG_HPP

#include <format>

#include "Kryogenic/Common/Types.hpp"

namespace Kryogenic {
	enum class LogLevel : u8 {
		eTrace,
		eDebug,
		eInfo,
		eWarning,
		eError,
		eFatal
	};

	auto LogInit() -> void;
	auto LogFini() -> void;

	auto Message(LogLevel pLevel, std::string_view const& pMessage) -> void;

	auto Trace(std::string_view const& pMessage) -> void;
	auto Debug(std::string_view const& pMessage) -> void;
	auto Info(std::string_view const& pMessage) -> void;
	auto Warn(std::string_view const& pMessage) -> void;
	auto Error(std::string_view const& pMessage) -> void;
	auto Fatal(std::string_view const& pMessage) -> void;

	template<typename... ARGS, typename = std::enable_if_t<(sizeof...(ARGS) > 0)>>
	auto Trace(std::format_string<ARGS...> pMessage, ARGS&&... pArgs) -> void {
		Trace(std::format(pMessage, std::forward<ARGS>(pArgs)...));
	}

	template<typename... ARGS, typename = std::enable_if_t<(sizeof...(ARGS) > 0)>>
	auto Debug(std::format_string<ARGS...> pMessage, ARGS&&... pArgs) -> void {
		Debug(std::format(pMessage, std::forward<ARGS>(pArgs)...));
	}

	template<typename... ARGS, typename = std::enable_if_t<(sizeof...(ARGS) > 0)>>
	auto Info(std::format_string<ARGS...> pMessage, ARGS&&... pArgs) -> void {
		Info(std::format(pMessage, std::forward<ARGS>(pArgs)...));
	}

	template<typename... ARGS, typename = std::enable_if_t<(sizeof...(ARGS) > 0)>>
	auto Warn(std::format_string<ARGS...> pMessage, ARGS&&... pArgs) -> void {
		Warn(std::format(pMessage, std::forward<ARGS>(pArgs)...));
	}

	template<typename... ARGS, typename = std::enable_if_t<(sizeof...(ARGS) > 0)>>
	auto Error(std::format_string<ARGS...> pMessage, ARGS&&... pArgs) -> void {
		Error(std::format(pMessage, std::forward<ARGS>(pArgs)...));
	}

	template<typename... ARGS, typename = std::enable_if_t<(sizeof...(ARGS) > 0)>>
	auto Fatal(std::format_string<ARGS...> pMessage, ARGS&&... pArgs) -> void {
		Fatal(std::format(pMessage, std::forward<ARGS>(pArgs)...));
	}
} // kryogenic

#endif //KRYOGENIC_BASE_LOG_HPP
