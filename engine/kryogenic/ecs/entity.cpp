#include "entity.hpp"

#include <cstdlib>

namespace kryogenic {
	ecs_sparse_set::~ecs_sparse_set() noexcept {
		free(m_sparse);
		free(m_dense);
	}

	ecs_sparse_set::ecs_sparse_set(u8 const dense_elem_size) noexcept
		: m_dense_elem_size(dense_elem_size) {
	}

	auto ecs_sparse_set::size() const -> usize {
		return m_dense_size;
	}

	auto ecs_sparse_set::empty() const -> b8 {
		return 0 == m_dense_size;
	}

	auto ecs_sparse_set::clear() -> void {
		m_dense_size = 0;
	}

	auto ecs_sparse_set::trim() -> void {
		auto last = m_sparse_cap;
		for (auto i = m_sparse_cap; i-- > 0;) {
			if (m_sparse[i] != null_ent) {
				last = i;
				break;
			}
		}

		if (last < m_sparse_cap) {
			m_sparse_cap = last + 1;
			m_sparse     = static_cast<entity*>(realloc(m_sparse, m_sparse_cap));
		}

		if (m_dense_size < m_dense_cap) {
			m_dense_cap = m_dense_size;
			m_dense     = static_cast<byte*>(realloc(m_dense, m_dense_cap * m_dense_elem_size));
		}
	}

	auto ecs_sparse_set::contains(entity const entity) const -> b8 {
		return entity < m_sparse_cap && m_sparse[entity] != null_ent;
	}

	auto ecs_sparse_set::resize_sparse(usize const size) -> void {
		if (size <= m_sparse_cap) {
			return;
		}

		m_sparse_cap = size;
		m_sparse     = static_cast<entity*>(realloc(m_sparse, m_sparse_cap * sizeof(entity)));
	}

	auto ecs_sparse_set::resize_dense(usize const size) -> void {
		if (size <= m_dense_cap) {
			return;
		}

		m_dense_cap = size;
		m_dense     = static_cast<byte*>(realloc(m_dense, m_dense_cap * m_dense_elem_size));
	}

	auto ecs_sparse_set::insert(entity const entity, void const* data) -> b8 {
		if (contains(entity)) {
			return false;
		}

		if (m_sparse_cap <= entity) {
			resize_sparse(entity + 1);
		}

		if (m_dense_size >= m_dense_cap) {
			resize_dense(m_dense_cap == 0 ? 1 : m_dense_cap * 2);
		}

		auto const dense_idx = m_dense_size++;
		m_sparse[entity]     = dense_idx;
		memcpy(m_dense + dense_idx * m_dense_elem_size, data, m_dense_elem_size);

		return true;
	}

	auto ecs_sparse_set::remove(entity const ent) -> b8 {
		if (false == contains(ent)) {
			return false;
		}

		auto const dense_idx = m_sparse[ent];
		m_sparse[ent]        = null_ent;

		if (dense_idx != m_dense_size - 1) {
			memcpy(m_dense + dense_idx * m_dense_elem_size, m_dense + (m_dense_size - 1) * m_dense_elem_size, m_dense_elem_size);
			m_sparse[*reinterpret_cast<entity*>(m_dense + dense_idx * m_dense_elem_size)] = dense_idx;
		}

		--m_dense_size;

		return true;
	}

	auto ecs_sparse_set::get(entity const entity) const -> byte* {
		if (false == contains(entity)) {
			return nullptr;
		}

		return m_dense + m_sparse[entity] * m_dense_elem_size;
	}

	auto ecs_sparse_set::begin() const -> byte* {
		return m_dense;
	}

	auto ecs_sparse_set::end() const -> byte* {
		return m_dense + m_dense_size * m_dense_elem_size;
	}

	auto ecs_sparse_set::cbegin() const -> byte const* {
		return m_dense;
	}

	auto ecs_sparse_set::cend() const -> byte const* {
		return m_dense + m_dense_size * m_dense_elem_size;
	}

	auto ecs_sparse_set::rbegin() const -> byte* {
		return m_dense + (m_dense_size - 1) * m_dense_elem_size;
	}

	auto ecs_sparse_set::rend() const -> byte* {
		return m_dense - m_dense_elem_size;
	}

	auto ecs_sparse_set::crbegin() const -> byte const* {
		return m_dense + (m_dense_size - 1) * m_dense_elem_size;
	}

	auto ecs_sparse_set::crend() const -> byte const* {
		return m_dense - m_dense_elem_size;
	}
} // kryogenic
