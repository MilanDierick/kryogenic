#ifndef KRYOGENIC_BASE_SINGLETON_HPP
#define KRYOGENIC_BASE_SINGLETON_HPP

namespace kryogenic {
	template<class T>
	class singleton {
	public:
		singleton() noexcept  = default;
		~singleton() noexcept = default;

		singleton(singleton const& other)                        = delete;
		singleton(singleton&& other) noexcept                    = delete;
		auto operator=(singleton const& other) -> singleton&     = delete;
		auto operator=(singleton&& other) noexcept -> singleton& = delete;

		[[nodiscard]] static auto instance() -> T& {
			static T instance;
			return instance;
		}
	};
} // kryogenic

#endif //KRYOGENIC_BASE_SINGLETON_HPP
