#ifndef KRYOGENIC_ECS_SPARSE_SET_HPP
#define KRYOGENIC_ECS_SPARSE_SET_HPP

#include <vector>

#include "Kryogenic/Common/Types.hpp"
#include "Kryogenic/Ecs/Entity.hpp"

namespace Kryogenic::Ecs {
	class SparseSet final {
	public:
		SparseSet() noexcept  = default;
		~SparseSet() noexcept = default;

		SparseSet(SparseSet const& pOther)                        = default;
		SparseSet(SparseSet&& pOther) noexcept                    = default;
		auto operator=(SparseSet const& pOther) -> SparseSet&     = default;
		auto operator=(SparseSet&& pOther) noexcept -> SparseSet& = default;

		auto Insert(u64 const pIndex, u64 const pValue) -> void {
			if (pIndex >= mSparse.size()) {
				mSparse.resize(pIndex + 1, kInvalidEntity);
			}

			mSparse[pIndex] = mDense.size();
			mDense.push_back(pValue);
		}

		auto Remove(u64 const pIndex) -> void {
			auto const denseIndex = mSparse[pIndex];
			mSparse[pIndex]       = kInvalidEntity;
			mDense[denseIndex]    = mDense.back();
			mDense.pop_back();
		}

		auto Clear() -> void {
			mSparse.clear();
			mDense.clear();
		}

		[[nodiscard]] auto Size() const -> usize {
			return mDense.size();
		}

		[[nodiscard]] auto Get(u64 const pIndex) const -> u64 {
			if (pIndex >= mSparse.size()) {
				return kInvalidEntity;
			}

			return mSparse[pIndex];
		}

		[[nodiscard]] auto GetSparse() const -> std::vector<u64> const& {
			return mSparse;
		}

		[[nodiscard]] auto GetDense() const -> std::vector<u64> const& {
			return mDense;
		}

	private:
		std::vector<u64> mSparse = {};
		std::vector<u64> mDense  = {};
	};
} // Kryogenic

#endif //KRYOGENIC_ECS_SPARSE_SET_HPP
