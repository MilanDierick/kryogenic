#ifndef KRYOGENIC_ECS_ECS_REGISTRY_HPP
#define KRYOGENIC_ECS_ECS_REGISTRY_HPP

#include <algorithm>
#include <ranges>
#include <typeindex>
#include <unordered_map>

#include "Kryogenic/Common/Types.hpp"
#include "Kryogenic/Ecs/ComponentSet.hpp"
#include "Kryogenic/Ecs/Entity.hpp"

namespace Kryogenic::Ecs {
	class Registry;

	class Registry final {
	public:
		Registry() noexcept  = default;
		~Registry() noexcept = default;

		Registry(Registry const& pOther)                        = delete;
		Registry(Registry&& pOther) noexcept                    = delete;
		auto operator=(Registry const& pOther) -> Registry&     = delete;
		auto operator=(Registry&& pOther) noexcept -> Registry& = delete;

		auto CreateEntity() -> Entity {
			if (mFreeList.empty()) {
				mEntities.push_back(mNextId);
				return {mNextId++, this};
			}

			auto const id = mFreeList.back();
			mFreeList.pop_back();
			mEntities.push_back(id);
			return {id, this};
		}

		auto DestroyEntity(Entity const pEntity) -> void {
			auto const id = pEntity.GetId();

			std::ranges::for_each(mComponents | std::views::values, [id](auto& pComp) {
				pComp->Remove(id);
			});

			mFreeList.push_back(id);
			std::erase(mEntities, id);
		}

		auto DestroyAllEntities() -> void {
			mFreeList.clear();
			mNextId = 0;

			std::ranges::for_each(mComponents | std::views::values, [](auto& pComp) {
				pComp->Clear();
			});

			mEntities.clear();
		}

		template<class COMPONENT>
		auto AddComponent(Entity const pEntity, COMPONENT const& pComp) -> void {
			GetOrCreateCompSet<COMPONENT>().Insert(pEntity.GetId(), &pComp);
		}

		template<class COMPONENT>
		[[nodiscard]] auto GetComponent(Entity const pEntity) -> COMPONENT* {
			return GetOrCreateCompSet<COMPONENT>().Get(pEntity.GetId());
		}

		template<class COMPONENT>
		[[nodiscard]] auto GetComponent(Entity const pEntity) const -> COMPONENT const* {
			return GetOrCreateCompSet<COMPONENT>().Get(pEntity.GetId());
		}

		template<class COMPONENT>
		auto RemoveComponent(Entity const pEntity) -> void {
			GetOrCreateCompSet<COMPONENT>().Remove(pEntity.GetId());
		}

		template<class COMPONENT>
		[[nodiscard]] auto HasComponent(Entity const pEntity) const -> bool {
			return GetOrCreateCompSet<COMPONENT>().Has(pEntity.GetId());
		}

		template<class... COMPONENTS, class FUNC>
		auto ForEach(FUNC&& pFunc) -> void {
			auto const smallest = std::min({mComponents.at(typeid(COMPONENTS)).get()...}, [](auto const& pLhs, auto const& pRhs) {
				return pLhs->Size() < pRhs->Size();
			});

			auto const& dense  = smallest->GetDense();

			for (auto const entity: dense) {
				if ((mComponents.contains(typeid(COMPONENTS)) && ...)) {
					pFunc(Entity{entity, this}, GetComponent<COMPONENTS>(Entity{entity, this})...);
				}
			}
		}

	private:
		u64              mNextId   = {};
		std::vector<u64> mEntities = {};
		std::vector<u64> mFreeList = {};

		std::unordered_map<std::type_index, std::unique_ptr<IComponentSet>> mComponents = {};

		template<class COMPONENT>
		[[nodiscard]] auto GetOrCreateCompSet() -> ComponentSet<COMPONENT>& {
			auto const type = std::type_index(typeid(COMPONENT));

			if (auto const it = mComponents.find(type); it != mComponents.end()) {
				return *static_cast<ComponentSet<COMPONENT>*>(it->second.get());
			}

			auto& comp = mComponents[type];
			comp       = std::make_unique<ComponentSet<COMPONENT>>();
			return *static_cast<ComponentSet<COMPONENT>*>(comp.get());
		}
	};
} // Kyrogenic::Ecs

#endif //KRYOGENIC_ECS_ECS_REGISTRY_HPP
