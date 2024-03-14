#ifndef KRYOGENIC_GRAPHICS_TEXTURE_HPP
#define KRYOGENIC_GRAPHICS_TEXTURE_HPP

#include <SDL2/SDL.h>

#include "Kryogenic/Common/Types.hpp"

namespace Kryogenic {
	using Texture = u64;

	struct TextureWrapped {
		SDL_Texture* Native = nullptr;

		TextureWrapped(SDL_Texture* pNative) noexcept
			: Native(pNative) {
		}
	};
} // kryogenic

#endif //KRYOGENIC_GRAPHICS_TEXTURE_HPP
