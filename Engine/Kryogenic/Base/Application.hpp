#ifndef KRYOGENIC_APPLICATION_HPP
#define KRYOGENIC_APPLICATION_HPP

#include <memory>

namespace Kryogenic {
	class EcsRegistry;
	class Renderer;
	class TextureManager;
	class Window;
} // kryogenic

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
		[[nodiscard]] auto GetEcs() const -> EcsRegistry&;
		[[nodiscard]] auto GetRenderer() const -> Renderer&;
		[[nodiscard]] auto GetTextureMngr() const -> TextureManager&;

	private:
		std::unique_ptr<Window>         mWindow      = {};
		std::unique_ptr<EcsRegistry>    mEcs         = {};
		std::unique_ptr<Renderer>       mRenderer    = {};
		std::unique_ptr<TextureManager> mTextureMngr = {};
	};

	[[nodiscard]] auto CreateApplication() -> std::unique_ptr<Application>;
} // kryogenic

#endif //KRYOGENIC_APPLICATION_HPP
