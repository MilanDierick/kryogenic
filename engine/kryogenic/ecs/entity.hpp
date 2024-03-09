#ifndef KRYOGENIC_ECS_ENTITY_HPP
#define KRYOGENIC_ECS_ENTITY_HPP

#include <ranges>
#include <typeindex>
#include <unordered_map>
#include <vector>

#include "kryogenic/common/types.hpp"

namespace kryogenic {
	using entity = u64;

	struct ecs_sparse_set final {
		constexpr static auto null_ent = std::numeric_limits<entity>::max();

		entity* m_sparse     = {};
		usize   m_sparse_cap = {};

		byte* m_dense           = {};
		usize m_dense_cap       = {};
		usize m_dense_size      = {};
		u8    m_dense_elem_size = {};

		ecs_sparse_set() noexcept = default;
		~ecs_sparse_set() noexcept;

		explicit ecs_sparse_set(u8 dense_elem_size) noexcept;

		[[nodiscard]] auto size() const -> usize;
		[[nodiscard]] auto empty() const -> b8;

		auto clear() -> void;
		auto trim() -> void;

		[[nodiscard]] auto contains(entity entity) const -> b8;

		auto resize_sparse(usize size) -> void;
		auto resize_dense(usize size) -> void;

		auto insert(entity entity, void const* data) -> b8;
		auto remove(entity ent) -> b8;

		[[nodiscard]] auto get(entity entity) const -> byte*;

		[[nodiscard]] auto begin() const -> byte*;
		[[nodiscard]] auto end() const -> byte*;
		[[nodiscard]] auto cbegin() const -> byte const*;
		[[nodiscard]] auto cend() const -> byte const*;
		[[nodiscard]] auto rbegin() const -> byte*;
		[[nodiscard]] auto rend() const -> byte*;
		[[nodiscard]] auto crbegin() const -> byte const*;
		[[nodiscard]] auto crend() const -> byte const*;
	};

	class ecs_registry final {
	public:
		ecs_registry() noexcept  = default;
		~ecs_registry() noexcept = default;

		ecs_registry(ecs_registry const& other)                        = delete;
		ecs_registry(ecs_registry&& other) noexcept                    = delete;
		auto operator=(ecs_registry const& other) -> ecs_registry&     = delete;
		auto operator=(ecs_registry&& other) noexcept -> ecs_registry& = delete;

		auto create_entity() -> entity {
			if (m_free_list.empty()) {
				return m_next_id++;
			}

			auto const id = m_free_list.back();
			m_free_list.pop_back();
			return id;
		}

		auto destroy_entity(entity const entity) -> void {
			m_free_list.push_back(entity);
		}

		auto destroy_all_entities() -> void {
			m_free_list.clear();
			m_next_id = 0;

			for (auto& comp: m_comps | std::views::values) {
				comp.clear();
			}
		}

		template<class T>
		auto add_component(entity const entity, T const& comp) -> void {
			get_or_create_comp<T>().insert(entity, &comp);
		}

		template<class T>
		[[nodiscard]] auto get_component(entity const entity) -> T* {
			return reinterpret_cast<T*>(get_or_create_comp<T>().get(entity));
		}

		template<class T>
		[[nodiscard]] auto get_component(entity const entity) const -> T const* {
			return get_or_create_comp<T>().get(entity);
		}

		template<class T>
		auto remove_component(entity const entity) -> void {
			get_or_create_comp<T>().remove(entity);
		}

	private:
		std::vector<entity> m_free_list = {};
		entity              m_next_id   = 0;

		std::unordered_map<std::type_index, ecs_sparse_set> m_comps = {};

		template<class T>
		auto get_or_create_comp() -> ecs_sparse_set& {
			auto const type = std::type_index(typeid(T));
			auto const it   = m_comps.find(type);
			if (it != m_comps.end()) {
				return it->second;
			}

			auto& comp = m_comps[type];
			comp       = ecs_sparse_set(sizeof(T));
			return comp;
		}
	};
} // kryogenic

#endif //KRYOGENIC_ECS_ENTITY_HPP
