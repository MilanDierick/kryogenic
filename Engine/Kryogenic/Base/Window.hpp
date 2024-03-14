#ifndef KRYOGENIC_BASE_WINDOW_HPP
#define KRYOGENIC_BASE_WINDOW_HPP

#include <string>

#include "Kryogenic/Common/Types.hpp"

namespace Kryogenic {
	class Window {
	public:
		Window() noexcept  = delete;
		~Window() noexcept = default;

		explicit Window(std::string_view pTitle, u16 pWidth, u16 pHeight);

		Window(Window const& pOther)                        = delete;
		Window(Window&& pOther) noexcept                    = delete;
		auto operator=(Window const& pOther) -> Window&     = delete;
		auto operator=(Window&& pOther) noexcept -> Window& = delete;

		auto PollEvents() -> void;

		[[nodiscard]] auto GetNative() const -> void*;
		[[nodiscard]] auto GetWidth() const -> u16;
		[[nodiscard]] auto GetHeight() const -> u16;
		[[nodiscard]] auto GetTitle() const -> std::string;
		[[nodiscard]] auto IsClosed() const -> b8;
		[[nodiscard]] auto IsResized() const -> b8;
		[[nodiscard]] auto IsMinimized() const -> b8;
		[[nodiscard]] auto IsFocused() const -> b8;

	private:
		void*       mNative = {};
		u16         mWidth  = {};
		u16         mHeight = {};
		std::string mTitle  = {};

		b8 mIsClosed    = {};
		b8 mIsResized   = {};
		b8 mIsMinimized = {};
		b8 mIsFocused   = {};
	};
} // kryogenic

#endif //KRYOGENIC_BASE_WINDOW_HPP
