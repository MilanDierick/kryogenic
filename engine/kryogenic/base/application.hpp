#ifndef KRYOGENIC_APPLICATION_HPP
#define KRYOGENIC_APPLICATION_HPP

#include <memory>

#include "kryogenic/base/singleton.hpp"

namespace kryogenic {
	class ecs_registry;
	class window;
}

namespace kryogenic {
	class application : public singleton<application> {
	public:
		application() noexcept;
		~application() noexcept;

		application(application const& other)                        = delete;
		application(application&& other) noexcept                    = delete;
		auto operator=(application const& other) -> application&     = delete;
		auto operator=(application&& other) noexcept -> application& = delete;

		auto execute() -> void;
		auto shutdown() -> void;

		[[nodiscard]] auto get_window() const -> window&;
		[[nodiscard]] auto get_ecs() const -> ecs_registry&;

	private:
		std::unique_ptr<window>       m_window = {};
		std::unique_ptr<ecs_registry> m_ecs    = {};
	};

	[[nodiscard]] auto create_application() -> std::unique_ptr<application>;
} // kryogenic

#endif //KRYOGENIC_APPLICATION_HPP
