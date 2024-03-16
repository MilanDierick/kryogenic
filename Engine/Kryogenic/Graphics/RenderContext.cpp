#include "RenderContext.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Kryogenic/Base/Application.hpp"
#include "Kryogenic/Base/Resource.hpp"
#include "Kryogenic/Base/Window.hpp"
#include "Kryogenic/Graphics/Renderer.hpp"
#include "Kryogenic/Graphics/Texture.hpp"

namespace Kryogenic {
	RenderContext::RenderContext() noexcept
		: mResourceStore(std::make_unique<ResourceStore>()) {
		auto const& application = Application::Instance();
		auto const& window      = application.GetWindow();
		auto const& renderer    = application.GetRenderer();

		mWindow   = static_cast<SDL_Window*>(window.GetNative());
		mRenderer = renderer.GetNative();
	}

	auto RenderContext::CreateTexture(stringv const& pPath) noexcept -> ResourceHandle {
		auto const result = mTextureCache.find(pPath);
		if (result != mTextureCache.end()) {
			return result->second;
		}

		auto const sdlSurface = IMG_Load(pPath.data());
		auto const sdlTexture = SDL_CreateTextureFromSurface(mRenderer, sdlSurface);
		SDL_FreeSurface(sdlSurface);

		auto const handle = mResourceStore->Acquire<Texture2D>(sdlTexture);
		mTextureCache.emplace(pPath, handle);
		return handle;
	}

	auto RenderContext::DestroyTexture(ResourceHandle pTexture) noexcept -> void {
		mResourceStore->Release<Texture2D>(pTexture);
		std::erase_if(mTextureCache, [pTexture](auto const& pPair) {
			return pPair.second == pTexture;
		});
	}
} // Kryogenic
