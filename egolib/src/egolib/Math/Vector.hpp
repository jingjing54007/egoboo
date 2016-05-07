//********************************************************************************************
//*
//*    This file is part of Egoboo.
//*
//*    Egoboo is free software: you can redistribute it and/or modify it
//*    under the terms of the GNU General Public License as published by
//*    the Free Software Foundation, either version 3 of the License, or
//*    (at your option) any later version.
//*
//*    Egoboo is distributed in the hope that it will be useful, but
//*    WITHOUT ANY WARRANTY; without even the implied warranty of
//*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//*    General Public License for more details.
//*
//*    You should have received a copy of the GNU General Public License
//*    along with Egoboo.  If not, see <http://www.gnu.org/licenses/>.
//*
//********************************************************************************************

/// @file   egolib/Math/Vector.hpp
/// @brief  Vectors.
/// @author Michael Heilmann

#pragma once

#include "egolib/Math/_Tuple.hpp"
#include "egolib/Math/_Generator.hpp"

namespace Ego {
namespace Math {

/**
 * @brief
 *  A vector of a vector space.
 * @tparam _ScalarFieldType
 *	the scalar field type
 * @tparam _Dimensionality
 *  the dimensionality
 * @author
 *  Michael Heilmann
 */
template <typename _ScalarFieldType, size_t _Dimensionality>
struct Vector : public Tuple<typename _ScalarFieldType::ScalarType, _Dimensionality> {
public:
    /// @brief The scalar field type.
    typedef _ScalarFieldType ScalarFieldType;
    /// @brief The scalar type (of the scalar field).
	typedef typename ScalarFieldType::ScalarType ScalarType;

public:
    /// @brief The dimensionality.
    static constexpr size_t dimensionality() {
        return _Dimensionality;
    }
public:
    /// @brief The tuple type.
    typedef Tuple<ScalarType, _Dimensionality> TupleType;
    /// @brief The type of this template/template specialization.
    typedef Vector<ScalarFieldType, _Dimensionality> MyType;

    typedef std::make_index_sequence<MyType::dimensionality()> IndexSequence;

public:
	/**
	 * @brief Construct this vector with the specified element values.
	 * @param first, ... rest the element values
     * @pre The number of specified element values must be equal to the dimensionality of the vector type.
     * @pre Each specified element value must be convertible into the element type of the vector type.
	 */
    template<
        typename ... ArgumentTypes, 
        typename =
            std::enable_if_t<
                ((sizeof...(ArgumentTypes)) + 1) == MyType::dimensionality() &&
                Core::AllTrue<std::is_convertible<ArgumentTypes, ScalarType>::value ...>::value
            >
    >
    Vector(ScalarType first, ArgumentTypes&& ... rest) 
		: TupleType(std::forward<ScalarType>(first), rest ...) {
        static_assert(dimensionality() == 1 + sizeof ... (rest), "wrong number of arguments");
    }

    /**
     * @brief
     *  Copy-construct this vector with the values of another vector.
     * @param other
     *  the other vector
     */
    Vector(const MyType& other)
		: TupleType(other) {
		/* Intentionally empty. */
    }

public:
    /**
     * @brief
     *  Construct this vector with the values generated by a sequence generator.
     * @tparam _GeneratorType
     *  the generator type
     * @tparam ... Index
     *  indices 0, 1, ..., dimensionality() - 1
     */
    template <typename _GeneratorType, size_t ... Index>
    Vector(const _GeneratorType& generator, std::index_sequence<Index ...> indexSequence)
        : TupleType(generator, indexSequence) {
    }

public:
    /**
     * @brief
     *  Default-construct this vector.
     */
    Vector()
        : Vector(ConstantGenerator<ScalarType>(ScalarFieldType::additiveNeutral()), 
                 IndexSequence{}) {
        /* Intentionally empty. */
    }

public:
    /**
     * @brief
     *  Get a unit vector in which the component of the specified index is @a 1.
     * @return
     *  the unit vector
     */
    static MyType unit(size_t index) {
        ConditionalGenerator<ScalarType> g(index, ScalarFieldType::multiplicativeNeutral(), ScalarFieldType::additiveNeutral());
        return Vector(g, IndexSequence{});
    }

public:

    inline ScalarType& x() {
        static_assert(MyType::dimensionality() >= 1, "cannot call for member x() with dimensionality less than 1");
        return this->at(0);
    }

    inline ScalarType& y() {
        static_assert(MyType::dimensionality() >= 2, "cannot call for member y() with dimensionality less than 2");
        return this->at(1);
    }

    inline ScalarType& z() {
        static_assert(MyType::dimensionality() >= 3, "cannot call for member z() with dimensionality less than 3");
        return this->at(2);
    }

    inline const ScalarType& x() const {
        static_assert(MyType::dimensionality() >= 1, "cannot call for member x() with dimensionality less than 1");
        return this->at(0);
    }

    inline const ScalarType& y() const {
        static_assert(MyType::dimensionality() >= 2, "cannot call for member y() with dimensionality less than 2");
        return this->at(1);
    }

    inline const ScalarType& z() const {
        static_assert(MyType::dimensionality() >= 3, "cannot call for member z() with dimensionality less than 3");
        return this->at(2);
    }

private:
    // TupleUtilities::foldT-compatible functor for the dot product.
    struct DotProductFunctor {
        typedef ScalarType ResultType;
        ScalarType operator()(ScalarType a, ScalarType x, ScalarType y) const {
            static const typename ScalarFieldType::SumFunctor sumFunctor;
            static const typename ScalarFieldType::ProductFunctor productFunctor;
            return sumFunctor(a, productFunctor(x, y));
        }
    };
    // TupleUtilities::foldT-compatible functor for the squared Euclidean length.
    struct EuclideanLengthSquaredFunctor {
        typedef ScalarType ResultType;
        ScalarType operator()(ScalarType a, ScalarType x) const {
            static const typename ScalarFieldType::SumFunctor sumFunctor;
            static const typename ScalarFieldType::ProductFunctor productFunctor;
            return sumFunctor(a, productFunctor(x, x));
        }
    };
    // TupleUtilities::foldT-compatible functor for the absolute length.
    struct AbsoluteLengthFunctor {
        typedef ScalarType ResultType;
        ScalarType operator()(ScalarType a, ScalarType x) const {
            static const typename ScalarFieldType::SumFunctor sumFunctor;
            return sumFunctor(a, std::abs(x));
        }
    };

public:
    /**
     * @brief
     *  Compute the dot product of this vector and another vector.
     * @param other
     *  the other vector
     * @return
     *  the dot product <tt>(*this) * other</tt> of this vector and the other vector
     */
    ScalarType dot(const MyType& other) const {
        return TupleUtilities::foldTT(DotProductFunctor(), *this, other);
    }

    /**
     * @brief
     *  Get the squared length of this vector
     *  (using the Euclidean metric).
     * @return
     *  the squared length of this vector
     */
    ScalarType length_2() const {
        return TupleUtilities::foldT(EuclideanLengthSquaredFunctor(), *this);
    }

    /**
     * @brief
     *  Get the length of this vector
     *  (using the Manhattan metric).
     * @return
     *  the length of this vector
     */
    ScalarType length_abs() const {
        return TupleUtilities::foldT(AbsoluteLengthFunctor(), *this);
    }
    
public:

    /** 
     * @brief
     *  Assign this vector with the values of another vector.
     * @param other
     *  the other vector
     */
    void assign(const MyType& other) {
		TupleType::assign(other);
    }

    /** 
     * @brief
     *  Set all elements in this point to zero.
     * @todo
     *  Remove this.
     */
    void setZero() {
        (*this) = MyType();
    }

public:
    /**
     * @brief
     *  Normalize this vector to the specified length.
     * @param length
     *  the length
     * @post
     *  If <tt>*this</tt> is the null/zero vector, then <tt>*this</tt> was assigned the null/zero vector
     *  and is assigned <tt>length * (*this) / |(*this)|</tt> otherwise.
     */
    void normalize(ScalarType length) {
        ScalarType l = this->length();
        if (ScalarFieldType::isPositive(l)) {
            *this = *this * ScalarFieldType::quotient(length, l);
        }
    }

    /**
     * @brief
     *  Normalize this vector.
     * @return
     *  the old length of this vector
     * @post
     *  If <tt>*this</tt> is the null/zero vector, then <tt>*this</tt> was assigned the null/zero vector
     *  and is assigned <tt>(*this) / l</tt> (where @a l is the old length of <tt>(*this)</tt>) otherwise.
     */
    ScalarType normalize() {
        ScalarType l = length();
        if (ScalarFieldType::isPositive(l)) {
            *this = *this * ScalarFieldType::quotient(1.0, l);
        }
        return l;
    }

public:
    /**
     * @brief
     *  Get if this vector equals another vector.
     * @param other
     *  the other vector
     * @return
     *  @a true if this vector equals the other vector
     */
    bool equals(const MyType& other) const {
		for (size_t i = 0; i < MyType::dimensionality(); ++i) {
            if (ScalarFieldType::notEqualTo(this->at(i), other.at(i))) {
                return false;
            }
        }
        return true;
    }

    /**
     * @brief
     *  Get if this vector equals another vector.
     * @param other
     *  the other vector
     * @param ulp
     *  see ScalarFieldType::notEqualUlp
     * @return
     *  @a true if this vector equals the other vector
     */
    bool equalsUlp(const MyType& other, const size_t& ulp) const {
		for (size_t i = 0; i < MyType::dimensionality(); ++i) {
            if (ScalarFieldType::notEqualUlp(this->at(i), other.at(i), ulp)) {
                return false;
            }
        }
        return true;
    }

    /**
     * @brief
     *  Get if this vector equals another vector.
     * @param other
     *  the other vector
     * @param tolerance
     *  see ScalarFieldType::notEqualTolerance
     * @return
     *  @a true if this vector equals the other vector
     */
    bool equalsTolerance(const MyType& other, const ScalarType& tolerance) const {
		for (size_t i = 0; i < MyType::dimensionality(); ++i) {
            if (ScalarFieldType::notEqualToTolerance(this->at(i), other.at(i), tolerance)) {
                return false;
            }
        }
        return true;
    }

private:

    /** @internal */
    template <size_t ... Index>
    MyType abs(std::index_sequence<Index ...>) const {
        return MyType(std::abs(this->at(Index)) ...);
    }

public:

    /**
     * @brief
     *  Get the component-wise absolute of this vector.
     * @return
     *  the component-wise absolute of this vector
     * @remark
     *  The component-wise absolute of a vector \f$v\in\mathbb{R}^n,n>0\f$ is defined as
     *  \f[
     *  abs(\vec{v}) = (abs(v_1),\ldots,abs(v_n))
     *  \f]
     */
    MyType abs() const {
        return abs(IndexSequence{});
    }

private:
    /** @internal */
    template <size_t ... Index>
    MyType max(std::index_sequence<Index ...>, const MyType& other) const {
        return MyType(std::max(this->at(Index), other.at(Index)) ...);
    }

    /** @internal */
    template <size_t ... Index>
    MyType min(std::index_sequence<Index ...>, const MyType& other) const {
        return MyType(std::min(this->at(Index),other.at(Index)) ...);
    }

public:
    // The superclass methods max and min are removed from overload resolution by the overloads of
    // methods of the same names in this class below. A using statement brings the superclass methods
    // back into overload resolution. However, I have troubles "using" only a particular overload like
    // I can do with creating wrappers invoking the superclass method.
    ScalarType max() const { return this->TupleType::max(); }
    ScalarType min() const { return this->TupleType::min(); }
    /**
     * @brief
     *	Get the component-wise maximum of this vector and another vector.
     * @param other
     *	the other vector
     * @return
     *	the component-wise maximum
     * @remark
     *	For two vectors \f$\vec{u},\vec{v}\in\mathbb{R}^n,n>0\f$ the component-wise maximum is defined as
     *  \f[
     *  max\left(\vec{u},\vec{v}\right)=left(max(u_1,v_1),\ldots,max(u_n,v_n)\right)
     *  \f]
     */
    MyType max(const MyType& other) const {
        return max(IndexSequence{},other);
    }
    /**
     * @brief
     *	Get the component-wise minimum of this vector and another vector.
     * @param other
     *	the other vector
     * @return
     *	the component-wise minimum
     * @remark
     *	For two vectors \f$\vec{u},\vec{v}\in\mathbb{R}^n,n>0\f$ the component-wise minimum is defined as
     *	\f[
     *	min\left(\vec{u},\vec{v}\right)=left(min(u_1,v_1),\ldots,min(u_n,v_n)\right)
     *	\f]
     */
    MyType min(const MyType& other) const {
        return min(IndexSequence{}, other);
    }


public:

    /**
     * @brief
     *  Get the length of this vector
     *  (using the Euclidean metric).
     * @return
     *  the length of this vector
     */
    ScalarType length() const {
        return std::sqrt(length_2());
    }

    /**
     * @brief
     *  Get the length of this vector
     *  (using the Maximum metric).
     * @return
     *  the length of this vector
     */
    ScalarType length_max() const {
        return *std::max_element(this->_elements, this->_elements + MyType::dimensionality());
    }

public:
    bool operator==(const MyType& other) const {
        return equals(other);
    }

    bool operator!=(const MyType& other) const {
        return !equals(other);
    }

public:
    // As always, return non-const reference in order to allow chaining for the sake of orthogonality.
    MyType& operator=(const MyType& other) {
        assign(other);
        return *this;
    }

public:
    ScalarType& operator[](size_t const& index) {
        return this->at(index);
    }

    const ScalarType& operator[](size_t const& index) const {
        return this->at(index);
    }

public:
    // Core operators.
    MyType operator+(const MyType& other) const {
        static const typename ScalarFieldType::SumFunctor functor;
        return TupleUtilities::mapTT<MyType>(functor, *this, other, IndexSequence{});
    }
    
    MyType operator-(const MyType& other) const {
        static const typename ScalarFieldType::DifferenceFunctor functor;
        return TupleUtilities::mapTT<MyType>(functor, *this, other, IndexSequence{});
    }

    MyType operator*(ScalarType other) const {
        static const typename ScalarFieldType::ProductFunctor functor;
        return TupleUtilities::mapTe<MyType>(functor, *this, other, IndexSequence{});
    }

    MyType operator/(ScalarType other) const {
        static const typename ScalarFieldType::QuotientFunctor functor;
        return TupleUtilities::mapTe<MyType>(functor, *this, other, IndexSequence{});
    }

    MyType operator-() const {
        static const typename ScalarFieldType::AdditiveInverseFunctor functor;
        return TupleUtilities::mapT<MyType>(functor, *this, IndexSequence{});
    }

public:
    // Derived operators.
    MyType& operator+=(const MyType& other) {
        *this = *this + other;
        return *this;
    }

    MyType& operator-=(const MyType& other) {
        *this = *this - other;
        return *this;
    }

    MyType& operator*=(ScalarType scalar) {
        *this = *this * scalar;
        return *this;
    }

    MyType& operator/=(ScalarType scalar) {
        *this = *this / scalar;
        return *this;
    }


public:
    /**
     * @brief
     *  Get if this vector is a unit vector.
     * @return
     *  @a true if this vector is a unit vector, @a false otherwise
     */
    bool isUnit() const {
        ScalarType t = length_2();
        return 0.99 < t && t < 1.01;
    }

    /**
     * @brief
     *  Get if this vector is a zero vector.
     * @return
     *  @a true if this vector is a zero vector, @a false otherwise
     */
    bool isZero() const {
        ScalarType t = length();
        return t < 0.01f;
    }


public:
    /**
     * @brief
     *  Get the zero vector.
     * @return
     *  the zero vector
     */
    static const MyType& zero() {
		static const ConstantGenerator<ScalarType> g(ScalarFieldType::additiveNeutral());
        static const auto v = MyType(g, IndexSequence{});
		return v;
	}

public:
    /**
     * @brief
     *  Compute the cross product of this vector and another vector.
     * @param other
     *  the other vector
     * @return
     *  the cross product <tt>(*this) x other</tt> of this vector and the other vector
     * @remark
     *  For any two vectors \f$\vec{u},\vec{v}\in\mathbb{R}^3\f$ the cross product is defined as
     *  \f[
     *  \vec{u} \times \vec{v} =
     *  \left[\begin{matrix}
     *  u_y v_z - u_z v_y\\
     *  u_z v_x - u_x v_z\\
     *  u_x v_y - u_y v_x
     *  \end{matrix}\right]
     *  \f]
     * @remark
     *  The cross product is distributive of vector addition i.e.
     *  \f[
     *  \vec{u} \times \left(\vec{v} + \vec{w}\right) = \vec{u} \times \vec{v} + \vec{u} \times \vec{w}
     *  \f]
     *  holds for any three vector \f$\vec{u},\vec{v},\vec{w}\in\mathbb{R}^3\f$.
     *  This follows from
     *  \f[
     *  &\vec{u} \times (\vec{v} + \vec{w})\\
     * =&\left[\begin{matrix}
     *   u_y (v_z + w_z) - u_z (v_y + w_y)\\
     *   u_z (v_x + w_x) - u_x (v_z + w_z)\\
     *   u_x (v_y + w_y) - u_y (v_x + w_x)
     *   \end{matrix}\right]\\
     * =&\left[\begin{matrix}
     *   (u_y v_z - u_z v_y) + (u_y w_z - u_z w_y)\\
     *   (u_z v_x - u_x v_z) + (u_z w_x - u_x w_z)\\
     *   (u_x v_y - u_y v_x) + (u_x w_y - u_y w_x)
     *   \end{matrix}\right]\\
     * =&\left[\begin{matrix}
     *   u_y v_z - u_z v_y\\
     *   u_z v_x - u_x v_z\\
     *   u_x v_y - u_y v_x
     *   \end{matrix}\right]
     *  +
     *   \left[\begin{matrix}
     *   u_y w_z - u_z w_y\\
     *   u_z w_x - u_x w_z\\
     *   u_x w_y - u_y w_x
     *   \end{matrix}\right]\\
     * =&\vec{u} \times \vec{v} + \vec{u} \times \vec{w}
     *  \f]
     * @remark
     *  The cross product is compatible with scalar multiplication i.e.
     *  \f[
     *  \left(s\vec{u}\right) \times \vec{v} = \vec{u} \times \left(s\vec{v}\right) = s \left(\vec{u} \times \vec{v}\right)
     *  \f]
     *  holds for any two vectors \f$\vec{u},\vec{v}\in\mathbb{R}^3\f$ and any scalar \f$s\in\mathbb{R}\f$.
     *  This follows from
     *  \f[
     *  \left(s\vec{u}\right) \times \vec{v}
     * =\left[\begin{matrix}
     *  (s u_y) v_z - (s u_z) v_y\\
     *  (s u_z) v_x - (s u_x) v_z\\
     *  (s u_x) v_y - (s u_y) v_x
     *  \end{matrix}\right]
     * =\left[\begin{matrix}
     *  u_y (s v_z) - u_z (s v_y)\\
     *  u_z (s v_x) - u_x (s v_z)\\
     *  u_x (s v_y) - u_y (s v_x)
     *  \end{matrix}\right]
     *  =\vec{u} \times (s \vec{v})
     *  \f]
     *  and
     *  \f[
     *  \left(s\vec{u}\right) \times \vec{v}
     * =\left[\begin{matrix}
     *  (s u_y) v_z - (s u_z) v_y\\
     *  (s u_z) v_x - (s u_x) v_z\\
     *  (s u_x) v_y - (s u_y) v_x
     *  \end{matrix}\right]
     * =s \left[\begin{matrix}
     *  u_y v_z - u_z v_y\\
     *  u_z v_x - u_x v_z\\
     *  u_x v_y - u_y v_x
     *  \end{matrix}\right]
     * = s (\vec{u} \times \vec{v})
     * @remark
     *  \f[
     *  \vec{v} \times \vec{v} = \vec{0}
     *  \f]
     *  holds by
     *  \f[
     *  \vec{v} \times \vec{v} =
     *  \left[\begin{matrix}
     *  v_y v_z - v_z v_y\\
     *  v_z v_x - v_x v_z\\
     *  v_x v_y - v_y v_x
     *  \end{matrix}\right]
     *  = \vec{0}
     *  \f]
     */
    template<size_t _Dummy = MyType::dimensionality()>
	std::enable_if_t<_Dummy == 3 && MyType::dimensionality() == 3, MyType>
    cross(const MyType& other) const {
        return
            MyType
            (
                this->at(1) * other.at(2) - this->at(2) * other.at(1),
                this->at(2) * other.at(0) - this->at(0) * other.at(2),
                this->at(0) * other.at(1) - this->at(1) * other.at(0)
            );
    }
};

} // namespace Math
} // namespace Ego
