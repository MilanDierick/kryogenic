#include "sandbox_application.hpp"

#include "kryogenic/ecs/entity.hpp"

namespace kryogenic {
	struct position final {
		u64 x = 0;
		u64 y = 0;
	};

	sandbox_application::sandbox_application() noexcept {
		auto& ecs = get_ecs();

		auto const entity = ecs.create_entity();
		ecs.add_component<position>(entity, position{5, 10});
		auto const pos = ecs.get_component<position>(entity);
		debug("Position: {0}, {1}", pos->x, pos->y);
	}
} // kryogenic
