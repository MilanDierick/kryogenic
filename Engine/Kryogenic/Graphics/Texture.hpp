#ifndef KRYOGENIC_GRAPHICS_TEXTURE_HPP
#define KRYOGENIC_GRAPHICS_TEXTURE_HPP

#include <SDL2/SDL.h>

#include "Kryogenic/Common/Types.hpp"

namespace Kryogenic {
	class Texture2D final {
	public:
		Texture2D() noexcept  = delete;
		~Texture2D() noexcept = default;

		explicit Texture2D(SDL_Texture* pTexture) noexcept
			: mTexture(pTexture) {
		}

		Texture2D(Texture2D const& pOther)                        = default;
		Texture2D(Texture2D&& pOther) noexcept                    = default;
		auto operator=(Texture2D const& pOther) -> Texture2D&     = default;
		auto operator=(Texture2D&& pOther) noexcept -> Texture2D& = default;

		[[nodiscard]] auto GetWidth() const noexcept -> u16;
		[[nodiscard]] auto GetHeight() const noexcept -> u16;

	private:
		SDL_Texture* mTexture = nullptr;
	};
} // kryogenic

#endif //KRYOGENIC_GRAPHICS_TEXTURE_HPP
