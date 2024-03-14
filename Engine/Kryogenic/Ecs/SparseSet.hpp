#ifndef KRYOGENIC_ECS_SPARSE_SET_HPP
#define KRYOGENIC_ECS_SPARSE_SET_HPP

#include <limits>

#include "Kryogenic/Common/Types.hpp"
#include "Kryogenic/Ecs/Entity.hpp"

namespace Kryogenic {
	struct EcsSparseSet final {
		constexpr static auto kNullEnt = std::numeric_limits<Entity>::max();

		Entity* Sparse    = {};
		usize   SparseCap = {};

		byte* Dense         = {};
		usize DenseCap      = {};
		usize DenseSize     = {};
		u8    DenseElemSize = {};

		EcsSparseSet() noexcept = default;
		~EcsSparseSet() noexcept;

		explicit EcsSparseSet(u8 pDenseElemSize) noexcept;

		[[nodiscard]] auto size() const -> usize;
		[[nodiscard]] auto Empty() const -> b8;

		auto Clear() -> void;
		auto Trim() -> void;

		[[nodiscard]] auto Contains(Entity pEntity) const -> b8;

		auto ResizeSparse(usize pSize) -> void;
		auto ResizeDense(usize pSize) -> void;

		auto Insert(Entity pEntity, void const* pData) -> b8;
		auto Remove(Entity pEnt) -> b8;

		[[nodiscard]] auto Get(Entity pEntity) const -> byte*;

		[[nodiscard]] auto begin() const -> byte*;
		[[nodiscard]] auto end() const -> byte*;
		[[nodiscard]] auto cbegin() const -> byte const*;
		[[nodiscard]] auto cend() const -> byte const*;
		[[nodiscard]] auto rbegin() const -> byte*;
		[[nodiscard]] auto rend() const -> byte*;
		[[nodiscard]] auto crbegin() const -> byte const*;
		[[nodiscard]] auto crend() const -> byte const*;
	};
} // kryogenic

#endif //KRYOGENIC_ECS_SPARSE_SET_HPP
