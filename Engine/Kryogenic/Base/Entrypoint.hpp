#ifndef KRYOGENIC_BASE_ENTRYPOINT_HPP
#define KRYOGENIC_BASE_ENTRYPOINT_HPP

#include "Kryogenic/Base/Application.hpp"
#include "Kryogenic/Base/Log.hpp"

// ReSharper disable once CppNonInlineFunctionDefinitionInHeaderFile
auto main() -> int {
	using namespace Kryogenic;

	try {
		LogInit();

		auto const application = CreateApplication();
		application->Execute();
		application->Shutdown();

		LogFini();
	} catch (std::exception const& e) {
		Fatal("Unhandled exception: {}", e.what());
	} catch (...) {
		Fatal("Unhandled exception");
	}
}

#endif // KRYOGENIC_BASE_ENTRYPOINT_HPP
