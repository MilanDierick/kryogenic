#ifndef KRYOGENIC_BASE_ENTRYPOINT_HPP
#define KRYOGENIC_BASE_ENTRYPOINT_HPP

#include "kryogenic/base/application.hpp"
#include "kryogenic/base/log.hpp"

auto main() -> int {
	using namespace kryogenic;

	try {
		log_init();

		auto const application = create_application();
		application->execute();
		application->shutdown();

		log_fini();
	} catch (std::exception const& e) {
		fatal("Unhandled exception: {}", e.what());
	} catch (...) {
		fatal("Unhandled exception");
	}
}

#endif // KRYOGENIC_BASE_ENTRYPOINT_HPP
