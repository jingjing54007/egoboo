#pragma once

#include "egolib/Math/Functors/Contains.hpp"
#include "egolib/Math/AxisAlignedCube.hpp"

namespace Ego {
namespace Math {

/**
 * @brief Functor which determines if an axis aligned cube contains another axis aligned cube.
 * @remark An axis aligned cube \$x\f$ does <em>not</em> contain an axis aligned cube \f$y\f$
 * if for at least one axis \$k\f$ at least one of the following conditions is true:
 * - \f$x_{min_k} > y_{min_k}\f$
 * - \$x_{max_k} < y_{max_k}\f$
 * Otherwise \f$x\f$ contains \f$y\f$.
 * This is a variant of the Separating Axis Theorem (aka SAT).
 */
template <typename EuclideanSpaceType>
struct Contains<
    AxisAlignedCube<EuclideanSpaceType>,
    AxisAlignedCube<EuclideanSpaceType>
> {
    using Type = AxisAlignedCube<EuclideanSpaceType>;
    bool operator()(const Type& a, const Type& b) const {
        for (size_t i = 0; i < EuclideanSpaceType::Dimensionality; ++i) {
            // If a is the cube that is supposed to contain the
            // cube b, then a does not contain b if along some axis
            // - the maximum of a is smaller than the maximum of b, or
            if (a.getMax()[i] < b.getMax()[i]) return false;
            // - the minimum of a is greater than the minimum of b.
            if (a.getMin()[i] > b.getMin()[i]) return false;
        }
        return true;	
    }
}; // struct Contains
} // namespace Math
} // namespace Ego
