#ifndef KRYOGENIC_ECS_COMPONENTS_SPRITE_HPP
#define KRYOGENIC_ECS_COMPONENTS_SPRITE_HPP

#include "Kryogenic/Base/Resource.hpp"

namespace Kryogenic {
	struct Sprite final {
		ResourceHandle Texture = {};

		Sprite() noexcept  = delete;
		~Sprite() noexcept = default;

		explicit Sprite(ResourceHandle const pTexture) noexcept
			: Texture(pTexture) {
		}
	};
} // kryogenic

#endif //KRYOGENIC_ECS_COMPONENTS_SPRITE_HPP
