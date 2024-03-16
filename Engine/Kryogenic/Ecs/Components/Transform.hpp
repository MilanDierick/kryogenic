#ifndef KRYOGENIC_ECS_COMPONENTS_TRANSFORM_HPP
#define KRYOGENIC_ECS_COMPONENTS_TRANSFORM_HPP

#include "Kryogenic/Common/Types.hpp"

namespace Kryogenic {
	struct Transform final {
		fvec3 Position = {};
		fvec3 Rotation = {};
		fvec3 Scale    = {};

		Transform() noexcept  = default;
		~Transform() noexcept = default;

		explicit Transform(fvec1 const& pScalar) noexcept
			: Position(pScalar)
			, Rotation(pScalar)
			, Scale(pScalar) {
		}

		explicit Transform(fvec3 const& pPosition, fvec3 const& pRotation, fvec3 const& pScale) noexcept
			: Position(pPosition)
			, Rotation(pRotation)
			, Scale(pScale) {
		}
	};
} // kryogenic

#endif //KRYOGENIC_ECS_COMPONENTS_TRANSFORM_HPP
