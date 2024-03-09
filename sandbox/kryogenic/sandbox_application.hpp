#ifndef KRYOGENIC_SANDBOX_APPLICATION_HPP
#define KRYOGENIC_SANDBOX_APPLICATION_HPP

#include "kryogenic/base/entrypoint.hpp"
#include "kryogenic/base/application.hpp"

namespace kryogenic {
	class sandbox_application : public application {
	public:
		sandbox_application() noexcept;
		~sandbox_application() noexcept = default;

		sandbox_application(sandbox_application const& other)                        = delete;
		sandbox_application(sandbox_application&& other) noexcept                    = delete;
		auto operator=(sandbox_application const& other) -> sandbox_application&     = delete;
		auto operator=(sandbox_application&& other) noexcept -> sandbox_application& = delete;
	};

	[[nodiscard]] auto create_application() -> std::unique_ptr<application> {
		return std::make_unique<sandbox_application>();
	}
} // kryogenic

#endif //KRYOGENIC_SANDBOX_APPLICATION_HPP
