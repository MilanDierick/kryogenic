#include "SparseSet.hpp"

namespace Kryogenic {
	EcsSparseSet::~EcsSparseSet() noexcept {
		free(Sparse);
		free(Dense);
	}

	EcsSparseSet::EcsSparseSet(u8 const pDenseElemSize) noexcept
		: DenseElemSize(pDenseElemSize) {
	}

	auto EcsSparseSet::size() const -> usize {
		return DenseSize;
	}

	auto EcsSparseSet::Empty() const -> b8 {
		return 0 == DenseSize;
	}

	auto EcsSparseSet::Clear() -> void {
		DenseSize = 0;
	}

	auto EcsSparseSet::Trim() -> void {
		auto last = SparseCap;
		for (auto i = SparseCap; i-- > 0;) {
			if (Sparse[i] != kNullEnt) {
				last = i;
				break;
			}
		}

		if (last < SparseCap) {
			SparseCap = last + 1;
			Sparse    = static_cast<Entity*>(realloc(Sparse, SparseCap));
		}

		if (DenseSize < DenseCap) {
			DenseCap = DenseSize;
			Dense    = static_cast<byte*>(realloc(Dense, DenseCap * DenseElemSize));
		}
	}

	auto EcsSparseSet::Contains(Entity const pEntity) const -> b8 {
		return pEntity < SparseCap && Sparse[pEntity] != kNullEnt;
	}

	auto EcsSparseSet::ResizeSparse(usize const pSize) -> void {
		if (pSize <= SparseCap) {
			return;
		}

		SparseCap = pSize;
		Sparse    = static_cast<Entity*>(realloc(Sparse, SparseCap * sizeof(Entity)));
	}

	auto EcsSparseSet::ResizeDense(usize const pSize) -> void {
		if (pSize <= DenseCap) {
			return;
		}

		DenseCap = pSize;
		Dense    = static_cast<byte*>(realloc(Dense, DenseCap * DenseElemSize));

		// new elements of m_sparse are set to null_ent
		for (auto i = DenseSize; i < DenseCap; ++i) {
			Sparse[i] = kNullEnt;
		}
	}

	auto EcsSparseSet::Insert(Entity const pEntity, void const* pData) -> b8 {
		if (Contains(pEntity)) {
			return false;
		}

		if (SparseCap <= pEntity) {
			ResizeSparse(pEntity + 1);
		}

		if (DenseSize >= DenseCap) {
			ResizeDense(DenseCap == 0 ? 1 : DenseCap * 2);
		}

		auto const denseIdx = DenseSize++;
		Sparse[pEntity]     = denseIdx;
		memcpy(Dense + denseIdx * DenseElemSize, pData, DenseElemSize);

		return true;
	}

	auto EcsSparseSet::Remove(Entity const pEnt) -> b8 {
		if (false == Contains(pEnt)) {
			return false;
		}

		auto const denseIdx = Sparse[pEnt];
		Sparse[pEnt]        = kNullEnt;

		if (denseIdx != DenseSize - 1) {
			memcpy(Dense + denseIdx * DenseElemSize, Dense + (DenseSize - 1) * DenseElemSize, DenseElemSize);
			Sparse[*reinterpret_cast<Entity*>(Dense + denseIdx * DenseElemSize)] = denseIdx;
		}

		--DenseSize;

		return true;
	}

	auto EcsSparseSet::Get(Entity const pEntity) const -> byte* {
		if (false == Contains(pEntity)) {
			return nullptr;
		}

		return Dense + Sparse[pEntity] * DenseElemSize;
	}

	auto EcsSparseSet::begin() const -> byte* {
		return Dense;
	}

	auto EcsSparseSet::end() const -> byte* {
		return Dense + DenseSize * DenseElemSize;
	}

	auto EcsSparseSet::cbegin() const -> byte const* {
		return Dense;
	}

	auto EcsSparseSet::cend() const -> byte const* {
		return Dense + DenseSize * DenseElemSize;
	}

	auto EcsSparseSet::rbegin() const -> byte* {
		return Dense + (DenseSize - 1) * DenseElemSize;
	}

	auto EcsSparseSet::rend() const -> byte* {
		return Dense - DenseElemSize;
	}

	auto EcsSparseSet::crbegin() const -> byte const* {
		return Dense + (DenseSize - 1) * DenseElemSize;
	}

	auto EcsSparseSet::crend() const -> byte const* {
		return Dense - DenseElemSize;
	}
} // kryogenic
