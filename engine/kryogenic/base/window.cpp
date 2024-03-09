#include "window.hpp"

#include <SDL2/SDL.h>

#include "kryogenic/base/log.hpp"

namespace kryogenic {
	window::window(std::string_view const title, u16 const width, u16 const height)
		: m_width(width)
		, m_height(height)
		, m_title(title) {
		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			fatal("Failed to initialize SDL: {}", SDL_GetError());
			throw std::runtime_error("Failed to initialize SDL.");
		}

		m_native = SDL_CreateWindow(
			m_title.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			m_width,
			m_height,
			SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI
			);

		if (nullptr == m_native) {
			fatal("Failed to create window: {}", SDL_GetError());
			throw std::runtime_error("Failed to create window.");
		}

		info("Window created with title: {}, width: {}, height: {}.", m_title, m_width, m_height);
	}

	auto window::poll_events() -> void {
		SDL_Event event = {};
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					m_is_closed = true;
					break;
				case SDL_WINDOWEVENT:
					switch (event.window.event) {
						case SDL_WINDOWEVENT_RESIZED:
							m_width = event.window.data1;
							m_height     = event.window.data2;
							m_is_resized = true;
							break;
						case SDL_WINDOWEVENT_MINIMIZED:
							m_is_minimized = true;
							break;
						case SDL_WINDOWEVENT_RESTORED:
							m_is_minimized = false;
							break;
						case SDL_WINDOWEVENT_FOCUS_GAINED:
							m_is_focused = true;
							break;
						case SDL_WINDOWEVENT_FOCUS_LOST:
							m_is_focused = false;
							break;
						default: ;
					}
					break;
				default: ;
			}
		}
	}

	auto window::get_native() const -> void* {
		return m_native;
	}

	auto window::get_width() const -> u16 {
		return m_width;
	}

	auto window::get_height() const -> u16 {
		return m_height;
	}

	auto window::get_title() const -> std::string {
		return m_title;
	}

	auto window::is_closed() const -> b8 {
		return m_is_closed;
	}

	auto window::is_resized() const -> b8 {
		return m_is_resized;
	}

	auto window::is_minimized() const -> b8 {
		return m_is_minimized;
	}

	auto window::is_focused() const -> b8 {
		return m_is_focused;
	}
} // kryogenic
