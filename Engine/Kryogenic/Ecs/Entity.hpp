#ifndef KRYOGENIC_ECS_ENTITY_HPP
#define KRYOGENIC_ECS_ENTITY_HPP

#include "Kryogenic/Common/Types.hpp"

namespace Kryogenic::Ecs {
	class Registry;

	class Entity final {
	public:
		Entity() noexcept  = default;
		~Entity() noexcept = default;

		Entity(u64 const pId, Registry* pRegistry) noexcept
			: mId(pId)
			, mRegistry(pRegistry) {
		}

		Entity(Entity const& pOther)                        = default;
		Entity(Entity&& pOther) noexcept                    = default;
		auto operator=(Entity const& pOther) -> Entity&     = default;
		auto operator=(Entity&& pOther) noexcept -> Entity& = default;

		[[nodiscard]] auto GetId() const noexcept -> u64 {
			return mId;
		}

		[[nodiscard]] auto GetRegistry() const noexcept -> Registry* {
			return mRegistry;
		}

	private:
		u64       mId       = {};
		Registry* mRegistry = {};
	};

	static constexpr auto kInvalidEntity = std::numeric_limits<u64>::max();
} // Kryogenic

#endif //KRYOGENIC_ECS_ENTITY_HPP
