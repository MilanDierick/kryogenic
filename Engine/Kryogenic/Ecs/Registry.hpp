#ifndef KRYOGENIC_ECS_REGISTRY_HPP
#define KRYOGENIC_ECS_REGISTRY_HPP

#include <ranges>
#include <typeindex>
#include <unordered_map>
#include <vector>

#include "Kryogenic/Ecs/Entity.hpp"
#include "Kryogenic/Ecs/SparseSet.hpp"

namespace Kryogenic {
	class EcsRegistry final {
	public:
		EcsRegistry() noexcept  = default;
		~EcsRegistry() noexcept = default;

		EcsRegistry(EcsRegistry const& pOther)                        = delete;
		EcsRegistry(EcsRegistry&& pOther) noexcept                    = delete;
		auto operator=(EcsRegistry const& pOther) -> EcsRegistry&     = delete;
		auto operator=(EcsRegistry&& pOther) noexcept -> EcsRegistry& = delete;

		auto CreateEntity() -> Entity {
			if (mFreeList.empty()) {
				mEntities.push_back(mNextId);
				return mNextId++;
			}

			auto const id = mFreeList.back();
			mFreeList.pop_back();
			mEntities.push_back(id);
			return id;
		}

		auto DestroyEntity(Entity const pEntity) -> void {
			mFreeList.push_back(pEntity);
			std::erase(mEntities, pEntity);
		}

		auto DestroyAllEntities() -> void {
			mFreeList.clear();
			mNextId = 0;

			for (auto& comp: mComponents | std::views::values) {
				comp.Clear();
			}

			mEntities.clear();
		}

		template<class T>
		auto AddComponent(Entity const pEntity, T const& pComp) -> void {
			GetOrCreateComp<T>().Insert(pEntity, &pComp);
		}

		template<class T>
		[[nodiscard]] auto GetComponent(Entity const pEntity) -> T* {
			return reinterpret_cast<T*>(GetOrCreateComp<T>().Get(pEntity));
		}

		template<class T>
		[[nodiscard]] auto GetComponent(Entity const pEntity) const -> T const* {
			return GetOrCreateComp<T>().get(pEntity);
		}

		template<class T>
		auto RemoveComponent(Entity const pEntity) -> void {
			GetOrCreateComp<T>().Remove(pEntity);
		}

		template<class T>
		[[nodiscard]] auto Contains(Entity const pEntity) -> b8 {
			return GetOrCreateComp<T>().Contains(pEntity);
		}

		template<class... COMPS, class FUNC>
		auto ForEach(FUNC&& pFunc) -> void {
			for (auto const entity: mEntities) {
				if ((Contains<COMPS>(entity) && ...)) {
					pFunc(entity, *GetComponent<COMPS>(entity)...);
				}
			}
		}

	private:
		std::vector<Entity> mEntities = {};
		std::vector<Entity> mFreeList = {};
		Entity              mNextId   = 0;

		std::unordered_map<std::type_index, EcsSparseSet> mComponents = {};

		template<class T>
		auto GetOrCreateComp() -> EcsSparseSet& {
			auto const type = std::type_index(typeid(T));
			auto const it   = mComponents.find(type);
			if (it != mComponents.end()) {
				return it->second;
			}

			auto& comp = mComponents[type];
			comp       = EcsSparseSet(sizeof(T));
			return comp;
		}
	};
} // kryogenic

#endif //KRYOGENIC_ECS_REGISTRY_HPP
