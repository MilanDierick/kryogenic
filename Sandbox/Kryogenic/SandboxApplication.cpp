#include "SandboxApplication.hpp"

#include "Kryogenic/Ecs/EcsRegistry.hpp"
#include "Kryogenic/Ecs/Components/Sprite.hpp"
#include "Kryogenic/Ecs/Components/Transform.hpp"
#include "Kryogenic/Graphics/RenderContext.hpp"

namespace Kryogenic {
	SandboxApplication::SandboxApplication() noexcept {
		auto const& application = Instance();
		auto&       registry    = application.GetEcsRegistry();
		auto&       renderCtx   = application.GetRenderContext();

		auto const texture = renderCtx.CreateTexture("Assets/Textures/Sample.png");

		auto const entity  = registry.CreateEntity();
		auto const entity2 = registry.CreateEntity();
		auto const entity3 = registry.CreateEntity();
		registry.AddComponent<Transform>(entity, Transform(fvec1{1.0F}));
		registry.AddComponent<Transform>(entity2, Transform(fvec1{2.0F}));
		registry.AddComponent<Transform>(entity3, Transform(fvec1{3.0F}));
		registry.AddComponent<Sprite>(entity, Sprite{texture});
		registry.AddComponent<Sprite>(entity3, Sprite{texture});

		registry.ForEach<Transform>([](auto const pEntity, auto const* pTransform) {
			Debug("Entity: {} | Transform: {};{}", pEntity.GetId(), pTransform->GetPosition().x, pTransform->GetPosition().y);
		});

		registry.ForEach<Sprite>([](auto const pEntity, auto const* pSprite) {
			Debug("Entity: {} | Sprite: {}", pEntity.GetId(), pSprite->GetTexture().GetId());
		});
	}
} // kryogenic
