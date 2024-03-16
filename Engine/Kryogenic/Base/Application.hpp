#ifndef KRYOGENIC_APPLICATION_HPP
#define KRYOGENIC_APPLICATION_HPP

#include <memory>

namespace Kryogenic {
	namespace Ecs {
		class Registry;
	} // Ecs

	class EcsRegistry;
	class RenderContext;
	class Renderer;
	class Window;
} // Kryogenic

namespace Kryogenic {
	class Application {
	public:
		Application() noexcept;
		~Application() noexcept;

		Application(Application const& pOther)                        = delete;
		Application(Application&& pOther) noexcept                    = delete;
		auto operator=(Application const& pOther) -> Application&     = delete;
		auto operator=(Application&& pOther) noexcept -> Application& = delete;

		[[nodiscard]] static auto Instance() noexcept -> Application&;

		auto Execute() -> void;
		auto Shutdown() -> void;

		[[nodiscard]] auto GetWindow() const -> Window&;
		[[nodiscard]] auto GetRenderer() const -> Renderer&;
		[[nodiscard]] auto GetEcsRegistry() const -> Ecs::Registry&;
		[[nodiscard]] auto GetRenderContext() const -> RenderContext&;

	private:
		std::unique_ptr<Window>        mWindow      = {};
		std::unique_ptr<Renderer>      mRenderer    = {};
		std::unique_ptr<Ecs::Registry> mEcsRegistry = {};
		std::unique_ptr<RenderContext> mRenderCtx   = {};
	};

	[[nodiscard]] auto CreateApplication() -> std::unique_ptr<Application>;
} // kryogenic

#endif //KRYOGENIC_APPLICATION_HPP
