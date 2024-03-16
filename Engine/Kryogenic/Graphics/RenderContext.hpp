#ifndef KRYOGENIC_GRAPHICS_RENDER_DEVICE_HPP
#define KRYOGENIC_GRAPHICS_RENDER_DEVICE_HPP

#include "Kryogenic/Base/Resource.hpp"
#include "Kryogenic/Common/Types.hpp"

namespace Kryogenic {
	class RenderContext {
	public:
		RenderContext() noexcept;
		~RenderContext() noexcept = default;

		RenderContext(RenderContext const& pOther)                        = delete;
		RenderContext(RenderContext&& pOther) noexcept                    = delete;
		auto operator=(RenderContext const& pOther) -> RenderContext&     = delete;
		auto operator=(RenderContext&& pOther) noexcept -> RenderContext& = delete;

		[[nodiscard]] auto CreateTexture(std::string_view const& pPath) noexcept -> ResourceHandle;
		auto               DestroyTexture(ResourceHandle pTexture) noexcept -> void;

	private:
		SDL_Window*                    mWindow        = {};
		SDL_Renderer*                  mRenderer      = {};
		std::unique_ptr<ResourceStore> mResourceStore = {};

		std::unordered_map<stringv, ResourceHandle> mTextureCache = {};

		friend class Renderer;
	};
} // Kryogenic

#endif //KRYOGENIC_GRAPHICS_RENDER_DEVICE_HPP
