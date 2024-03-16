#include "Application.hpp"

#include "Kryogenic/Base/Window.hpp"
#include "Kryogenic/Ecs/EcsRegistry.hpp"
#include "Kryogenic/Graphics/RenderContext.hpp"
#include "Kryogenic/Graphics/Renderer.hpp"

namespace Kryogenic {
	namespace {
		Application* gInstance = nullptr;
	} // <anonymous>
}     // Kryogenic

namespace Kryogenic {
	Application::Application() noexcept {
		gInstance = this;

		mWindow      = std::make_unique<Window>("Kryogenic", 800, 600);
		mRenderer    = std::make_unique<Renderer>();
		mEcsRegistry = std::make_unique<Ecs::Registry>();
		mRenderCtx   = std::make_unique<RenderContext>();
	}

	Application::~Application() noexcept {
		mRenderer.reset();
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

	auto Application::GetRenderer() const -> Renderer& {
		return *mRenderer;
	}

	auto Application::GetEcsRegistry() const -> Ecs::Registry& {
		return *mEcsRegistry;
	}

	auto Application::GetRenderContext() const -> RenderContext& {
		return *mRenderCtx;
	}
} // Kryogenic
