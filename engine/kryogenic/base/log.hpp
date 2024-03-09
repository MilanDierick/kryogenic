#ifndef KRYOGENIC_BASE_LOG_HPP
#define KRYOGENIC_BASE_LOG_HPP

#include <format>

#include "kryogenic/common/types.hpp"

namespace kryogenic {
	enum class log_lvl : u8 {
		trace,
		debug,
		info,
		warning,
		error,
		fatal
	};

	auto log_init() -> void;
	auto log_fini() -> void;

	auto message(log_lvl level, std::string_view const& msg) -> void;

	auto trace(std::string_view const& msg) -> void;
	auto debug(std::string_view const& msg) -> void;
	auto info(std::string_view const& msg) -> void;
	auto warn(std::string_view const& msg) -> void;
	auto error(std::string_view const& msg) -> void;
	auto fatal(std::string_view const& msg) -> void;

	template<typename... Args, typename = std::enable_if_t<(sizeof...(Args) > 0)>>
	auto trace(std::format_string<Args...> msg, Args&&... args) -> void {
		trace(std::format(msg, std::forward<Args>(args)...));
	}

	template<typename... Args, typename = std::enable_if_t<(sizeof...(Args) > 0)>>
	auto debug(std::format_string<Args...> msg, Args&&... args) -> void {
		debug(std::format(msg, std::forward<Args>(args)...));
	}

	template<typename... Args, typename = std::enable_if_t<(sizeof...(Args) > 0)>>
	auto info(std::format_string<Args...> msg, Args&&... args) -> void {
		info(std::format(msg, std::forward<Args>(args)...));
	}

	template<typename... Args, typename = std::enable_if_t<(sizeof...(Args) > 0)>>
	auto warn(std::format_string<Args...> msg, Args&&... args) -> void {
		warn(std::format(msg, std::forward<Args>(args)...));
	}

	template<typename... Args, typename = std::enable_if_t<(sizeof...(Args) > 0)>>
	auto error(std::format_string<Args...> msg, Args&&... args) -> void {
		error(std::format(msg, std::forward<Args>(args)...));
	}

	template<typename... Args, typename = std::enable_if_t<(sizeof...(Args) > 0)>>
	auto fatal(std::format_string<Args...> msg, Args&&... args) -> void {
		fatal(std::format(msg, std::forward<Args>(args)...));
	}
} // kryogenic

#endif //KRYOGENIC_BASE_LOG_HPP
