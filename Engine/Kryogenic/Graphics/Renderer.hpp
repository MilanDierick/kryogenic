#ifndef KRYOGENIC_GRAPHICS_RENDERER_HPP
#define KRYOGENIC_GRAPHICS_RENDERER_HPP

namespace Kryogenic {
	class Renderer {
	public:
		Renderer() noexcept;
		~Renderer() noexcept;

		Renderer(Renderer const& pOther)                        = delete;
		Renderer(Renderer&& pOther) noexcept                    = delete;
		auto operator=(Renderer const& pOther) -> Renderer&     = delete;
		auto operator=(Renderer&& pOther) noexcept -> Renderer& = delete;

		auto RenderFrame() -> void;

		[[nodiscard]] auto GetNative() const -> SDL_Renderer*;

	private:
		SDL_Renderer* mNative = nullptr;

		auto RenderTextures() -> void;
	};
} // kryogenic

#endif //KRYOGENIC_GRAPHICS_RENDERER_HPP
