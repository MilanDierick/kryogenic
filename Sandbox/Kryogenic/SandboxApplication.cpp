#include "SandboxApplication.hpp"

#include "Kryogenic/Ecs/Registry.hpp"
#include "Kryogenic/Ecs/Components/Sprite.hpp"
#include "Kryogenic/Ecs/Components/Transform.hpp"
#include "Kryogenic/Graphics/TextureManager.hpp"

namespace Kryogenic {
	SandboxApplication::SandboxApplication() noexcept {
		auto const& application = Instance();
		auto&       textureMngr = application.GetTextureMngr();
		auto&       registry    = application.GetEcs();

		auto const texture = textureMngr.LoadTexture("Assets/Textures/sample.png");

		auto const entity = registry.CreateEntity();
		registry.AddComponent(entity, Transform{fvec3{0.0f, 0.0f, 0.0f}, fvec3{0.0f, 0.0f, 0.0f}, fvec3{800.0f, 600.0f, 1.0f}});
		registry.AddComponent(entity, Sprite{texture});
	}
} // kryogenic
