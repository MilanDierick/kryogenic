#include "Window.hpp"

#include <SDL2/SDL.h>

#include "Kryogenic/Base/Log.hpp"

namespace Kryogenic {
	Window::Window(std::string_view const pTitle, u16 const pWidth, u16 const pHeight)
		: mWidth(pWidth)
		, mHeight(pHeight)
		, mTitle(pTitle) {
		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			Fatal("Failed to initialize SDL: {}", SDL_GetError());
			throw std::runtime_error("Failed to initialize SDL.");
		}

		mNative = SDL_CreateWindow(
			mTitle.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			mWidth,
			mHeight,
			SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI
			);

		if (nullptr == mNative) {
			Fatal("Failed to create window: {}", SDL_GetError());
			throw std::runtime_error("Failed to create window.");
		}

		Info("Window created with title: {}, width: {}, height: {}.", mTitle, mWidth, mHeight);
	}

	auto Window::PollEvents() -> void {
		SDL_Event event = {};
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					mIsClosed = true;
					break;
				case SDL_WINDOWEVENT:
					switch (event.window.event) {
						case SDL_WINDOWEVENT_RESIZED:
							mWidth = static_cast<u16>(event.window.data1);
							mHeight    = static_cast<u16>(event.window.data2);
							mIsResized = true;
							break;
						case SDL_WINDOWEVENT_MINIMIZED:
							mIsMinimized = true;
							break;
						case SDL_WINDOWEVENT_RESTORED:
							mIsMinimized = false;
							break;
						case SDL_WINDOWEVENT_FOCUS_GAINED:
							mIsFocused = true;
							break;
						case SDL_WINDOWEVENT_FOCUS_LOST:
							mIsFocused = false;
							break;
						default: ;
					}
					break;
				default: ;
			}
		}
	}

	auto Window::GetNative() const -> void* {
		return mNative;
	}

	auto Window::GetWidth() const -> u16 {
		return mWidth;
	}

	auto Window::GetHeight() const -> u16 {
		return mHeight;
	}

	auto Window::GetTitle() const -> std::string {
		return mTitle;
	}

	auto Window::IsClosed() const -> b8 {
		return mIsClosed;
	}

	auto Window::IsResized() const -> b8 {
		return mIsResized;
	}

	auto Window::IsMinimized() const -> b8 {
		return mIsMinimized;
	}

	auto Window::IsFocused() const -> b8 {
		return mIsFocused;
	}
} // kryogenic
