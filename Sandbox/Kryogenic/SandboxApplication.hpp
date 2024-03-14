#ifndef KRYOGENIC_SANDBOX_APPLICATION_HPP
#define KRYOGENIC_SANDBOX_APPLICATION_HPP

#include "Kryogenic/Base/Application.hpp"
#include "Kryogenic/Base/Entrypoint.hpp"

namespace Kryogenic {
	class SandboxApplication : public Application {
	public:
		SandboxApplication() noexcept;
		~SandboxApplication() noexcept = default;

		SandboxApplication(SandboxApplication const& pOthe)                        = delete;
		SandboxApplication(SandboxApplication&& pOthe) noexcept                    = delete;
		auto operator=(SandboxApplication const& pOthe) -> SandboxApplication&     = delete;
		auto operator=(SandboxApplication&& pOthe) noexcept -> SandboxApplication& = delete;
	};

	[[nodiscard]] inline auto CreateApplication() -> std::unique_ptr<Application> {
		return std::make_unique<SandboxApplication>();
	}
} // kryogenic

#endif //KRYOGENIC_SANDBOX_APPLICATION_HPP
