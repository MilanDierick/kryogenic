#ifndef KRYOGENIC_ECS_COMPONENTS_SPRITE_HPP
#define KRYOGENIC_ECS_COMPONENTS_SPRITE_HPP

#include "Kryogenic/Graphics/Texture.hpp"

namespace Kryogenic {
	struct Sprite final {
		Texture Tex = {};

		Sprite() noexcept  = default;
		~Sprite() noexcept = default;

		explicit Sprite(Texture const pTexture) noexcept
			: Tex(pTexture) {
		}
	};
} // kryogenic

#endif //KRYOGENIC_ECS_COMPONENTS_SPRITE_HPP
