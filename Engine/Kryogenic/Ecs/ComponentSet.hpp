#ifndef KRYOGENIC_COMPONENT_SET_HPP
#define KRYOGENIC_COMPONENT_SET_HPP

#include <vector>

#include "Kryogenic/Common/Types.hpp"
#include "Kryogenic/Ecs/Entity.hpp"
#include "Kryogenic/Ecs/SparseSet.hpp"

namespace Kryogenic::Ecs {
	class IComponentSet {
	public:
		IComponentSet() noexcept          = default;
		virtual ~IComponentSet() noexcept = default;

		IComponentSet(IComponentSet const& pOther)                        = default;
		IComponentSet(IComponentSet&& pOther) noexcept                    = default;
		auto operator=(IComponentSet const& pOther) -> IComponentSet&     = default;
		auto operator=(IComponentSet&& pOther) noexcept -> IComponentSet& = default;

		virtual auto Remove(u64 pIndex) -> void = 0;

		virtual auto Clear() -> void = 0;

		[[nodiscard]] virtual auto Size() const -> usize = 0;

		[[nodiscard]] virtual auto Has(u64 pIndex) const -> bool = 0;

		virtual auto GetSparse() const -> std::vector<u64> const& = 0;
		virtual auto GetDense() const -> std::vector<u64> const& = 0;
	};

	template<class TYPE>
	class ComponentSet final : public IComponentSet {
	public:
		ComponentSet() noexcept           = default;
		~ComponentSet() noexcept override = default;

		ComponentSet(ComponentSet const& pOther)                        = default;
		ComponentSet(ComponentSet&& pOther) noexcept                    = default;
		auto operator=(ComponentSet const& pOther) -> ComponentSet&     = default;
		auto operator=(ComponentSet&& pOther) noexcept -> ComponentSet& = default;

		auto Insert(u64 const pIndex, TYPE const* pValue) -> void {
			mSparse.Insert(pIndex, pIndex);
			mComponents.push_back(*pValue);
		}

		auto Remove(u64 const pIndex) -> void override {
			auto const denseIndex = mSparse.Get(pIndex);
			mSparse.Remove(pIndex);
			mComponents[denseIndex] = mComponents.back();
			mComponents.pop_back();
		}

		auto Clear() -> void override {
			mSparse.Clear();
			mComponents.clear();
		}

		[[nodiscard]] auto Size() const -> usize override {
			return mComponents.size();
		}

		[[nodiscard]] auto Get(u64 const pIndex) -> TYPE* {
			return &mComponents[mSparse.Get(pIndex)];
		}

		[[nodiscard]] auto Get(u64 const pIndex) const -> TYPE const* {
			return &mComponents[mSparse.Get(pIndex)];
		}

		[[nodiscard]] auto Has(u64 const pIndex) const -> bool override {
			return mSparse.Get(pIndex) != kInvalidEntity;
		}

		[[nodiscard]] auto GetSparse() const -> std::vector<u64> const& override {
			return mSparse.GetSparse();
		}

		[[nodiscard]] auto GetDense() const -> std::vector<u64> const& override {
			return mSparse.GetDense();
		}

	private:
		SparseSet         mSparse     = {};
		std::vector<TYPE> mComponents = {};
	};
} // kryogenic

#endif //KRYOGENIC_COMPONENT_SET_HPP
