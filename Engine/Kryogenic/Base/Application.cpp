#include "Application.hpp"

#include "Kryogenic/Base/Window.hpp"
#include "Kryogenic/Ecs/Registry.hpp"
#include "Kryogenic/Graphics/Renderer.hpp"
#include "Kryogenic/Graphics/TextureManager.hpp"

namespace Kryogenic {
	namespace {
		Application* gInstance = nullptr;
	} // <anonymous>
}     // kryogenic

namespace Kryogenic {
	Application::Application() noexcept {
		gInstance = this;

		mWindow      = std::make_unique<Window>("Kryogenic", 800, 600);
		mEcs         = std::make_unique<EcsRegistry>();
		mRenderer    = std::make_unique<Renderer>();
		mTextureMngr = std::make_unique<TextureManager>();
	}

	Application::~Application() noexcept {
		mRenderer.reset();
		mEcs.reset();
		mWindow.reset();
	}

	auto Application::Instance() noexcept -> Application& {
		return *gInstance;
	}

	auto Application::Execute() -> void {
		while (false == mWindow->IsClosed()) {
			mWindow->PollEvents();
			mRenderer->RenderFrame();
		}
	}

	auto Application::Shutdown() -> void {
	}

	auto Application::GetWindow() const -> Window& {
		return *mWindow;
	}

	auto Application::GetEcs() const -> EcsRegistry& {
		return *mEcs;
	}

	auto Application::GetRenderer() const -> Renderer& {
		return *mRenderer;
	}

	auto Application::GetTextureMngr() const -> TextureManager& {
		return *mTextureMngr;
	}
} // kryogenic
