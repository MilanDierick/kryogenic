#ifndef KRYOGENIC_BASE_RESOURCE_HPP
#define KRYOGENIC_BASE_RESOURCE_HPP

#include <limits>

#include "Kryogenic/Common/Ensure.hpp"
#include "Kryogenic/Common/Types.hpp"

namespace Kryogenic {
	struct ResourceHandle final {
		u64 Index: 32      = std::numeric_limits<u64>::max();
		u64 Generation: 24 = std::numeric_limits<u64>::max();
		u64 Type: 8        = std::numeric_limits<u64>::max();

		friend auto operator==(ResourceHandle const& pLhs, ResourceHandle const& pRhs) -> bool {
			return pLhs.Index == pRhs.Index
			       && pLhs.Generation == pRhs.Generation
			       && pLhs.Type == pRhs.Type;
		}

		friend auto operator!=(ResourceHandle const& pLhs, ResourceHandle const& pRhs) -> bool {
			return !(pLhs == pRhs);
		}
	};

	class ResourceStore final {
	public:
		struct Node final {
			ResourceHandle Handle   = {};
			void*          Resource = nullptr;
		};

		ResourceStore() noexcept  = default;
		~ResourceStore() noexcept = default;

		ResourceStore(ResourceStore const& pOther)                        = delete;
		ResourceStore(ResourceStore&& pOther) noexcept                    = delete;
		auto operator=(ResourceStore const& pOther) -> ResourceStore&     = delete;
		auto operator=(ResourceStore&& pOther) noexcept -> ResourceStore& = delete;

		template<class T, typename... ARGS>
		[[nodiscard]] auto Acquire(ARGS&&... pArgs) -> ResourceHandle {
			auto const type  = GetOrCreateType<T>();
			auto       index = std::numeric_limits<u64>::max();
			if (!mFree.empty()) {
				index = mFree.back();
				mFree.pop_back();
			} else {
				index = mNodes.size();
				mNodes.push_back({});
			}

			auto& [Handle, Resource] = mNodes[index];
			Handle.Index             = index;
			Handle.Generation        = Handle.Generation + 1;
			Handle.Type              = type;
			Resource                 = new T{std::forward<ARGS>(pArgs)...};
			return Handle;
		}

		template<class T>
		auto Release(ResourceHandle const& pHandle) noexcept -> T {
			Validate<T>(pHandle);
			auto&      [Handle, Resource] = mNodes[pHandle.Index];
			auto const resource           = std::move(Resource);
			mFree.push_back(pHandle.Index);
			return *static_cast<T*>(resource);
		}

		template<class T>
		[[nodiscard]] auto Resolve(ResourceHandle const& pHandle) noexcept -> T& {
			Validate<T>(pHandle);
			return *static_cast<T*>(mNodes[pHandle.Index].Resource);
		}

		template<class T>
		[[nodiscard]] auto Resolve(ResourceHandle const& pHandle) const noexcept -> T const& {
			Validate<T>(pHandle);
			return *static_cast<T*>(mNodes[pHandle.Index].Resource);
		}

		[[nodiscard]] auto IsValid(ResourceHandle const& pHandle) const noexcept -> bool {
			return pHandle.Index < mNodes.size() && pHandle.Generation == mNodes[pHandle.Index].Handle.Generation;
		}

		[[nodiscard]] auto GetResourceCount(u64 const pType) const noexcept -> u64 {
			Ensure(pType < mTypes.size(), "Invalid resource type.");
			auto count = u64{};
			for (auto const& [Handle, Resource]: mNodes) {
				if (Handle.Type == pType) {
					++count;
				}
			}
			return count;
		}

		template<class T>
		[[nodiscard]] auto GetResourcesForType() const noexcept -> std::vector<T&> {
			auto const type   = GetOrCreateType<T>();
			auto       result = std::vector<T&>{};
			for (auto const& [Handle, Resource]: mNodes) {
				if (Handle.Type == type) {
					result.push_back(*static_cast<T*>(Resource));
				}
			}
			return result;
		}

	private:
		std::vector<Node>           mNodes = {};
		std::vector<u64>            mFree  = {};
		std::unordered_map<u64, u8> mTypes = {};

		template<class T>
		auto GetOrCreateType() noexcept -> u8 {
			auto const type = typeid(T).hash_code();
			if (!mTypes.contains(type)) {
				mTypes[type] = static_cast<u8>(mTypes.size());
			}
			return mTypes[type];
		}

		template<class T>
		auto Validate(ResourceHandle const& pHandle) const noexcept -> void {
			Ensure(pHandle.Index < mNodes.size(), "Invalid resource handle index.");
			Ensure(pHandle.Generation == mNodes[pHandle.Index].Handle.Generation, "Invalid resource handle generation.");
			Ensure(pHandle.Type < mTypes.size(), "Invalid resource handle type.");
		}
	};
} // Kryogenic

#endif //KRYOGENIC_BASE_RESOURCE_HPP
