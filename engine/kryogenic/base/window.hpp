#ifndef KRYOGENIC_BASE_WINDOW_HPP
#define KRYOGENIC_BASE_WINDOW_HPP

#include <string>
#include <string_view>

#include "kryogenic/common/types.hpp"

namespace kryogenic {
	class window {
	public:
		window() noexcept  = delete;
		~window() noexcept = default;

		explicit window(std::string_view title, u16 width, u16 height);

		window(window const& other)                        = delete;
		window(window&& other) noexcept                    = delete;
		auto operator=(window const& other) -> window&     = delete;
		auto operator=(window&& other) noexcept -> window& = delete;

		auto poll_events() -> void;

		[[nodiscard]] auto get_native() const -> void*;
		[[nodiscard]] auto get_width() const -> u16;
		[[nodiscard]] auto get_height() const -> u16;
		[[nodiscard]] auto get_title() const -> std::string;
		[[nodiscard]] auto is_closed() const -> b8;
		[[nodiscard]] auto is_resized() const -> b8;
		[[nodiscard]] auto is_minimized() const -> b8;
		[[nodiscard]] auto is_focused() const -> b8;

	private:
		void*       m_native = {};
		u16         m_width  = {};
		u16         m_height = {};
		std::string m_title  = {};

		b8 m_is_closed    = {};
		b8 m_is_resized   = {};
		b8 m_is_minimized = {};
		b8 m_is_focused   = {};
	};
} // kryogenic

#endif //KRYOGENIC_BASE_WINDOW_HPP
