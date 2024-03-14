#ifndef KRYOGENIC_GRAPHICS_TEXTURE_MNGR_HPP
#define KRYOGENIC_GRAPHICS_TEXTURE_MNGR_HPP

#include "Kryogenic/Common/Types.hpp"
#include "Kryogenic/Graphics/Texture.hpp"

namespace Kryogenic {
	class TextureManager {
	public:
		TextureManager() noexcept  = default;
		~TextureManager() noexcept = default;

		TextureManager(TextureManager const& pOther)                        = delete;
		TextureManager(TextureManager&& pOther) noexcept                    = delete;
		auto operator=(TextureManager const& pOther) -> TextureManager&     = delete;
		auto operator=(TextureManager&& pOther) noexcept -> TextureManager& = delete;

		[[nodiscard]] auto LoadTexture(stringv const& pPath) noexcept -> Texture;

	private:
		std::unordered_map<stringv, Texture> mTextures = {};
	};
} // kryogenic

#endif //KRYOGENIC_GRAPHICS_TEXTURE_MNGR_HPP
