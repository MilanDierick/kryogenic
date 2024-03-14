#include "TextureManager.hpp"

#include <filesystem>
#include <SDL2/SDL_image.h>

#include "Kryogenic/Base/Application.hpp"
#include "Kryogenic/Ecs/Registry.hpp"
#include "Kryogenic/Graphics/Renderer.hpp"

namespace Kryogenic {
	auto TextureManager::LoadTexture(stringv const& pPath) noexcept -> Texture {
		auto const result = mTextures.find(pPath);
		if (result != mTextures.end()) {
			return result->second;
		}

		auto const& application = Application::Instance();
		auto const& renderer    = application.GetRenderer();
		auto const  native      = renderer.GetNative();

		auto const sdlSurface = IMG_Load(pPath.data());
		auto const sdlTexture = SDL_CreateTextureFromSurface(native, sdlSurface);
		SDL_FreeSurface(sdlSurface);

		auto&      registry = application.GetEcs();
		auto const texture  = registry.CreateEntity();
		registry.AddComponent<TextureWrapped>(texture, sdlTexture);

		mTextures[pPath] = texture;
		return texture;
	}
} // kryogenic
