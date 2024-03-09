#include "application.hpp"

#include "kryogenic/base/window.hpp"
#include "kryogenic/ecs/entity.hpp"

namespace kryogenic {
	application::application() noexcept {
		m_window = std::make_unique<window>("Kryogenic", 800, 600);
		m_ecs    = std::make_unique<ecs_registry>();
	}

	application::~application() noexcept {
		m_ecs.reset();
		m_window.reset();
	}

	auto application::execute() -> void {
		while (false == m_window->is_closed()) {
			m_window->poll_events();
		}
	}

	auto application::shutdown() -> void {
	}

	auto application::get_window() const -> window& {
		return *m_window;
	}

	auto application::get_ecs() const -> ecs_registry& {
		return *m_ecs;
	}
} // kryogenic
