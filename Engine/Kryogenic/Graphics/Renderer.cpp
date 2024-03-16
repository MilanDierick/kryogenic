#include "Renderer.hpp"

#include "Kryogenic/Base/Application.hpp"
#include "Kryogenic/Base/Window.hpp"

namespace Kryogenic {
	Renderer::Renderer() noexcept {
		auto const& application = Application::Instance();
		auto const& window      = application.GetWindow();
		auto const  sdlWindow   = static_cast<SDL_Window*>(window.GetNative());
		mNative                 = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED);
	}

	Renderer::~Renderer() noexcept {
		SDL_DestroyRenderer(mNative);
	}

	auto Renderer::RenderFrame() -> void {
		SDL_RenderClear(mNative);
		RenderTextures();
		SDL_RenderPresent(mNative);
	}

	auto Renderer::GetNative() const -> SDL_Renderer* {
		return mNative;
	}

	auto Renderer::RenderTextures() -> void {
	}
} // kryogenic
