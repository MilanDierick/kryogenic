#include "Renderer.hpp"

#include "Kryogenic/Base/Application.hpp"
#include "Kryogenic/Base/Window.hpp"
#include "Kryogenic/Ecs/Registry.hpp"
#include "Kryogenic/Ecs/Components/Sprite.hpp"
#include "Kryogenic/Ecs/Components/Transform.hpp"
#include "Kryogenic/Graphics/TextureManager.hpp"

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
		auto const& application = Application::Instance();
		auto&       registry    = application.GetEcs();

		registry.ForEach<Transform, Sprite>([&, this](auto, auto& pTransform, auto& pSprite) {
			auto const texture = registry.GetComponent<TextureWrapped>(pSprite.Tex);

			SDL_Rect dest;
			dest.x = static_cast<i32>(pTransform.Position.x);
			dest.y = static_cast<i32>(pTransform.Position.y);
			dest.w = static_cast<i32>(pTransform.Scale.x);
			dest.h = static_cast<i32>(pTransform.Scale.y);

			SDL_RenderCopy(mNative, texture->Native, nullptr, &dest);
		});
	}
} // kryogenic
