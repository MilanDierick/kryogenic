#ifndef KRYOGENIC_COMMON_ASSERT_HPP
#define KRYOGENIC_COMMON_ASSERT_HPP

#include <stdexcept>

namespace Kryogenic {
	constexpr auto Ensure(bool const pCondition, char const* const pMessage) -> void {
		if (!pCondition) {
			throw std::runtime_error(pMessage);
		}
	}
} // kryogenic

#endif //KRYOGENIC_COMMON_ASSERT_HPP
