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

/// @file  egolib/Math/Vector.hpp
/// @brief 2-,3- and 4-dimensional vectors.

#pragma once

#include "egolib/typedef.h"
#include "egolib/log.h"
#include "egolib/Float.hpp"
#include "egolib/Debug.hpp"
#include "egolib/Math/Math.hpp"

namespace Ego
{
    namespace Math
    {
        /**
         * @brief
         *  Vectors with compile-time dimensionality.
         * @param ScalarType
         *  the scalar type
         * @param Dimensionality
         *  the dimensionality of the vector
         * @pre
         *  the scalar type must be a floating point type
         * @pre
         *  The dimensionality must be a positive integral constant
         * @details
         *  The efficiency of this template depends on the optimization
         *  capabilities of your compiler  (in particular, loop unrolling).
         */
        template <typename ScalarType,size_t Dimensionality>
        struct AbstractVector
        {
            static_assert(std::is_floating_point<ScalarType>::value, "ScalarType must be a floating point type");
            static_assert(std::integral_constant<size_t, Dimensionality>::value > 0, "Dimensionality must be positive");
        };
    }
}

/**
 * @brief
 *	Enumerated indices for the elements of vectors.
 */
enum { kX = 0, kY, kZ, kW };


typedef float fvec2_base_t[2];           ///< the basic floating point 2-vector type
typedef float fvec3_base_t[3];           ///< the basic floating point 3-vector type
typedef float fvec4_base_t[4];           ///< the basic floating point 4-vector type

/// A 2-vector type that allows more than one form of access.
struct fvec2_t
{

	union
	{
		fvec2_base_t v;
		struct { float x, y; };
		struct { float s, t; };
	};

	const static fvec2_t zero;

	fvec2_t() :
        x(), y()
	{
	}

	fvec2_t(const fvec2_t& other) : x(other.x), y(other.y)
	{
	}

	fvec2_t(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	/**
	 * @brief
	 *	Compute the dot product of this vector and another vector.
	 * @param other
	 *	the other vector
	 * @return
	 *	the dot product <tt>(*this) * other</tt> of this vector and the other vector
	 */
	float dot(const fvec2_t& other) const
	{
		return v[kX] * other.v[kX]
			 + v[kY] * other.v[kY]
			 ;
	}

	/**
	 * @brief
	 *	Multiply this vector by a scalar.
	 * @param scalar
	 *	the scalar
	 * @post
	 *	The product <tt>scalar * (*this)</tt> was assigned to <tt>*this</tt>.
	 */
	void multiply(float scalar)
	{
		v[kX] *= scalar;
		v[kY] *= scalar;
	}

	/**
	* @brief
	*	Normalize this vector to the specified length.
	* @param length
	*	the length
	* @post
	*	If <tt>*this</tt> is the null/zero vector, then <tt>*this</tt> was assigned the null/zero vector
	*	and is assigned <tt>length * (*this) / |(*this)|</tt> otherwise.
	*/
	void normalize(float length)
	{
		float l = this->length();
		if (l > 0.0f)
		{
			multiply(length / l);
		}
	}

	/**
	 * @brief
	 *	Normalize this vector.
	 * @return
	 *	the old length of this vector
	 * @post
	 *	If <tt>*this</tt> is the null/zero vector, then <tt>*this</tt> was assigned the null/zero vector
	 *	and is assigned <tt>(*this) / l</tt> (where @a l is the old length of <tt>(*this)</tt>) otherwise.
	 */
	float normalize()
	{
		float l = length();
		if (l > 0.0f)
		{
			multiply(1.0f / l);
		}
		return l;
	}

	/**
	 * @brief
	 *	Get if this vector equals another vectors.
	 * @param other
	 *	the other vector
	 * @return
	 *	@a true if this vector equals the other vector
	 */
	bool equals(const fvec2_t& other) const
	{
		return x == other.x
			&& y == other.y;
	}

	/**
	 * @brief
	 *  Get the squared length of this vector
	 *  (using the Euclidian metric).
	 * @return
	 *	the squared length of this vector
	 */
	float length_2() const
	{
		return v[kX] * v[kX]
             + v[kY] * v[kY]
			 ;
	}

	/**
	 * @brief
	 *  Get the length of this vector
	 *  (using the Euclidian metric).
	 * @return
	 *  the length of this vector
	 */
	float length() const
	{
		return std::sqrt(length_2());
	}

	/**
	 * @brief
	 *  Get the length of this vector
	 *  (using the Manhattan metric).
	 * @return
	 *  the length of this vector
	 */
	float length_abs() const
	{
		return std::abs(v[kX])
             + std::abs(v[kY]);
	}

    /**
     * @brief
     *  Get the length of this vector
     *  (using the Maximum metric).
     * @return
     *  the length of this vector
     */
    float length_max() const
    {
        return std::max({std::abs(v[kX]),std::abs(v[kY])});
    }

	const fvec2_t& operator=(const fvec2_t& other)
	{
		x = other.x;
		y = other.y;
		return *this;
	}

	fvec2_t operator+(const fvec2_t& other) const
	{
		return fvec2_t(x + other.x, y + other.y);
	}

	fvec2_t& operator+=(const fvec2_t& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	fvec2_t operator-(const fvec2_t& other) const
	{
		return fvec2_t(x - other.x, y - other.y);
	}

	fvec2_t& operator-=(const fvec2_t& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	fvec2_t operator*(const float other) const
	{
		return fvec2_t(other * v[kX], other * v[kY]);
	}

	fvec2_t& operator*=(float scalar)
	{
		multiply(scalar);
		return *this;
	}

	float& operator[](size_t const& index)
	{
#ifdef _DEBUG
		EGOBOO_ASSERT(index < 2);
#endif
		return v[index];
	}

	const float &operator[](size_t const& index) const
	{
#ifdef _DEBUG
		EGOBOO_ASSERT(index < 2);
#endif
		return v[index];
	}

    /**
     * @brief
     *  Get if this vector is a unit vector.
     * @return
     *  @a true if this vector is a unit vector, @a false otherwise
     */
    bool isUnit() const
    {
        float t = length_2();
        return 0.99f < t && t < 1.01f;
    }


};

fvec2_t operator-(const fvec2_t& v);


#ifdef _DEBUG
namespace Ego
{
    namespace Debug
    {
        template <>
        void validate<::fvec2_t>(const char *file, int line, const ::fvec2_t& object);
    }
}
#endif

/// A 3-vector type that allows more than one form of access.
struct fvec3_t
{

	union
	{
		fvec3_base_t v;
		struct { float x, y, z; };
		struct { float r, g, b; };
	};

	const static fvec3_t zero;

	fvec3_t() :
        x(), y(), z()
	{
	}

	fvec3_t(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	fvec3_t(const fvec3_t& other) : x(other.x), y(other.y), z(other.z)
	{
	}

	/**
	 * @brief
	 *	Get the component-wise absolute of this vector.
	 * @return
	 *	the component-wise absolute of this vector
	 * @remark
	 *	The component-wise absolute of a vector \f$v\in\mathbb{R}^n,n>0\f$ is defined as
	 *	\f[
	 *	abs(\vec{v}) = (abs(v_1),\ldots,abs(v_n))
	 *	\f]
	 */
	fvec3_t abs() const
	{
		return
			fvec3_t
			(
				std::abs(v[kX]),
				std::abs(v[kY]),
				std::abs(v[kZ])
			);
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
	fvec3_t min(const fvec3_t& other) const
	{
		return
			fvec3_t
				(
					std::min(this->v[kX],other.v[kX]),
					std::min(this->v[kY],other.v[kY]),
					std::min(this->v[kZ],other.v[kZ])
				);
	}

	/**
	 * @brief
	 *	Get the component-wise maximum of this vector and another vector.
	 * @param other
	 *	the other vector
	 * @return
	 *	the component-wise maximum
	 * @remark
	 *	For two vectors \f$\vec{u},\vec{v}\in\mathbb{R}^n,n>0\f$ the component-wise maximum is defined as
	 *	\f[
	 *	max\left(\vec{u},\vec{v}\right)=left(max(u_1,v_1),\ldots,max(u_n,v_n)\right)
	 *	\f]
	 */
	fvec3_t max(const fvec3_t& other) const
	{
		return
			fvec3_t
			(
				std::max(this->v[kX], other.v[kX]),
				std::max(this->v[kY], other.v[kY]),
				std::max(this->v[kZ], other.v[kZ])
			);
	}

	/**
	 * @brief
	 *	Compute the cross product of this vector and another vector.
	 * @param other
	 *	the other vector
	 * @return
	 *	the cross product <tt>(*this) x other</tt> of this vector and the other vector
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
	fvec3_t cross(const fvec3_t& other) const
	{
		return
			fvec3_t
			(
				this->v[kY] * other.v[kZ] - this->v[kZ] * other.v[kY],
				this->v[kZ] * other.v[kX] - this->v[kX] * other.v[kZ],
				this->v[kX] * other.v[kY] - this->v[kY] * other.v[kX]
			);
	}

	/**
	 * @brief
	 *	Compute the dot product of this vector and another vector.
	 * @param other
	 *	the other vector
	 * @return
	 *	the dot product <tt>(*this) * other</tt> of this vector and the other vector
	 */
	float dot(const fvec3_t& other) const
	{
        float dot = v[0] * other.v[0];
        for (size_t i = 1; i < 3; ++i)
        {
            dot += v[i] * other.v[i];
        }
        return dot;
	}

	/**
	 * @brief
	 *	Multiply this vector by a scalar.
	 * @param scalar
	 *	the scalar
	 * @post
	 *	The product <tt>scalar * (*this)</tt> was assigned to <tt>*this</tt>.
	 */
	void multiply(float scalar)
	{
        for (size_t i = 0; i < 3; ++i)
        {
            v[i] *= scalar;
        }
	}

	/**
	 * @brief
	 *	Normalize this vector to the specified length.
	 * @param length
	 *	the length
	 * @post
	 *	If <tt>*this</tt> is the null/zero vector, then <tt>*this</tt> was assigned the null/zero vector
	 *	and is assigned <tt>length * (*this) / |(*this)|</tt> otherwise.
	 */
	void normalize(float length)
	{
		float l = this->length();
		if (l > 0.0f)
		{
			multiply(length / l);
		}
	}

	/**
	 * @brief
	 *	Normalize this vector.
	 * @return
	 *	the <em>old</em> length of the vector
	 * @post
	 *	If <tt>*this</tt> is the null/zero vector, then <tt>*this</tt> was assigned the null/zero vector
	 *	and is assigned <tt>(*this) / |(*this)|</tt> otherwise.
	 */
	float normalize()
	{
		float l = this->length();
		if (l > 0.0f)
		{
			multiply(1.0f / l);
		}
		return l;
	}

	/**
	 * @brief
	 *	Get if this vector equals another vectors.
	 * @param other
	 *	the other vector
	 * @return
	 *	@a true if this vector equals the other vector
	 */
	bool equals(const fvec3_t& other) const
	{
        for (size_t i = 0; i < 3; ++i)
        {
            if (v[i] != other.v[i])
            {
                return false;
            }
        }
        return true;
	}

	/**
 	 * @brief
	 *  Get the squared length of this vector
	 *  (using the Euclidian metric).
	 * @return
	 *  the squared length of this vector
	 */
	float length_2() const
	{
        float length = v[0] * v[0];
        for (size_t i = 1; i < 3; ++i)
        {
            length += v[i] * v[i];
        }
        return length;
	}

	/**
	 * @brief
	 *  Get the length of this vector
	 *  (using the Euclidian metric).
	 * @return
	 *  the length of this vector
	 */
	float length() const
	{
		return std::sqrt(length_2());
	}

	/**
	* @brief
	* 	Get XY euclidian distance between two vectors
	**/
	float xy_distance(const fvec3_t &other) const
	{
		return std::sqrt( Math::sq(x-other.x) + Math::sq(y-other.y) );
	}

	/**
	 * @brief
	 *  Get the length of this vector
	 *  (using the Manhattan metric).
	 * @return
	 *  the length of this vector
	 */
	float length_abs() const
	{
        float length = std::abs(v[0]);
        for (size_t i = 1; i < 3; ++i)
        {
            length += std::abs(v[i]);
        }
        return length;
	}

    /**
     * @brief
     *  Get the length of this vector
     *  (using the Maximum metric).
     * @return
     *  the length of this vector
     */
    float length_max() const
    {
        float length = std::abs(v[0]);
        for (size_t i = 1; i < 3; ++i)
        {
            length = std::max(length, std::abs(v[i]));
        }
        return length;
    }

	const fvec3_t& operator=(const fvec3_t& other)
	{
        for (size_t i = 0; i < 3; ++i)
        {
            v[i] = other.v[i];
        }
		return *this;
	}

	fvec3_t operator+(const fvec3_t& other) const
	{
		return fvec3_t(x + other.x, y + other.y, z + other.z);
	}

	fvec3_t& operator+=(const fvec3_t& other)
	{
        for (size_t i = 0; i < 3; ++i)
        {
            v[i] += other.v[i];
        }
		return *this;
	}

	fvec3_t operator-(const fvec3_t& other) const
	{
		return fvec3_t(x - other.x, y - other.y, z - other.z);
	}

	fvec3_t& operator-=(const fvec3_t& other)
	{
        for (size_t i = 0; i < 3; ++i)
        {
            v[i] -= other.v[i];
        }
		return *this;
	}

	fvec3_t operator*(const float other) const
	{
		return fvec3_t(other * v[kX], other * v[kY], other * v[kZ]);
	}

	fvec3_t& operator*=(float scalar)
	{
		multiply(scalar);
		return *this;
	}

	bool operator==(const fvec3_t& other) const
	{
		return equals(other);
	}

	bool operator!=(const fvec3_t& other) const
	{
		return !equals(other);
	}

	float& operator[](size_t const& index)
	{
#ifdef _DEBUG
		EGOBOO_ASSERT(index < 3);
#endif
		return v[index];
	}

	const float &operator[](size_t const& index) const
	{
#ifdef _DEBUG
		EGOBOO_ASSERT(index < 3);
#endif
		return v[index];
	}

    /**
     * @brief
     *  Get if this vector is a unit vector.
     * @return
     *  @a true if this vector is a unit vector, @a false otherwise
     */
    bool isUnit() const
    {
        float t = length();
        return 0.9f < t && t < 1.1f;
    }

    /**
     * @brief
     *  Get if this vector is a zero vector.
     * @return
     *  @a true if this vector is a zero vector, @a false otherwise
     */
    bool isZero() const
    {
        float t = length();
        return t < 0.01f;
    }

};

fvec3_t operator-(const fvec3_t& v);

#ifdef _DEBUG
namespace Ego
{
    namespace Debug
    {
        template <>
        void validate<::fvec3_t>(const char *file, int line, const ::fvec3_t& object);
    }
}
#endif

/// A 4-vector type that allows more than one form of access.
struct fvec4_t
{

	union
	{
		fvec4_base_t v;
		struct { float x, y, z, w; };
		struct { float r, g, b, a; };
	};
	
	const static fvec4_t zero;
	
	fvec4_t() : x(), y(), z(), w()
	{
	}

	fvec4_t(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	fvec4_t(const fvec4_t& other) :
        x(other.x), y(other.y), z(other.z), w(other.w)
	{
	}

	const fvec4_t& operator=(const fvec4_t& other)
	{
        for (size_t i = 0; i < 4; ++i)
        {
            v[i] = other.v[i];
        }
		return *this;
	}

	float& operator[](size_t const& index)
	{
#ifdef _DEBUG
		EGOBOO_ASSERT(index < 4);
#endif
		return v[index];
	}

	const float &operator[](size_t const& index) const
	{
#ifdef _DEBUG
		EGOBOO_ASSERT(index < 4);
#endif
		return v[index];
	}

	/**
	 * @brief
	 *	Multiply this vector by a scalar.
	 * @param scalar
	 *	the scalar
	 * @post
	 *	The product <tt>scalar * (*this)</tt> was assigned to <tt>*this</tt>.
	 */
	void multiply(float scalar)
	{
        for (size_t i = 0; i < 4; ++i)
        {
            v[i] *= scalar;
        }
	}

	/**
	 * @brief
	 *	Normalize this vector.
	 * @return
	 *	the old length of this vector
	 * @post
	 *	If <tt>*this</tt> is the null/zero vector, then <tt>*this</tt> was assigned the null/zero vector
	 *	and is assigned <tt>(*this) / l</tt> (where @a l is the old length of <tt>(*this)</tt>) otherwise.
	 */
	float normalize()
	{
		float l = length();
		if (l > 0.0f)
		{
			multiply(1.0f / l);
		}
		return l;
	}

	/**
	 * @brief
	 *	Get if this vector equals another vectors.
	 * @param other
	 *	the other vector
	 * @return
	 *	@a true if this vector equals the other vector
	 */
	bool equals(const fvec4_t& other) const
	{
        for (size_t i = 0; i < 4; ++i)
        {
            if (v[i] != other.v[i])
            {
                return false;
            }
        }
        return true;
	}
	/**
	 * @brief
	 *  Get the squared length of this vector
	 *  (using the Euclidian metric).
	 * @return
	 *  the squared length of this vector
	 */
	float length_2() const
	{
        float length = v[0] * v[0];
        for (size_t i = 1; i < 4; ++i)
        {
            length += v[i] * v[i];
        }
        return length;
	}

	/**
	 * @brief
	 *	Get the length of this vector
	 *	(using the Euclidian metric).
	 * @return
	 *	the length of this vector
	 */
	float length() const
	{
		return std::sqrt(length_2());
	}

	/**
	 * @brief
	 *  Get the length of this vector
	 *  (using the Manhattan metric).
	 * @return
	 *  the length of this vector
	 */
	float length_abs() const
	{
        float length = std::abs(v[0]);
        for (size_t i = 1; i < 4; ++i)
        {
            length += std::abs(v[i]);
        }
        return length;
	}

    /**
     * @brief
     *  Get the length of this vector
     *  (using the Maximum metric).
     * @return
     *  the length of this vector
     */
    float length_max() const
    {
        float length = std::abs(v[0]);
        for (size_t i = 1; i < 4; ++i)
        {
            length = std::max(length, std::abs(v[i]));
        }
        return length;
    }

    /**
     * @brief
     *  Get if this vector is a unit vector.
     * @return
     *  @a true if this vector is a unit vector, @a false otherwise
     */
    bool isUnit() const
    {
        float t = length_2();
        return 0.99f < t && t < 1.01f;
    }

};

fvec4_t operator-(const fvec4_t& v);

#ifdef _DEBUG
namespace Ego
{
    namespace Debug
    {
        template <>
        void validate<::fvec4_t>(const char *file, int line, const ::fvec4_t& object);
    }
}
#endif

/**
* @brief
*	Construct a vector.
* @param v
*	the vector
* @post
*	the vector represents the null vector
*/
void fvec3_ctor(fvec3_t& v);

/**
* @brief
*	Destruct a vector.
* @param v
*	the vector
*/
void fvec3_dtor(fvec3_t& v);

/**
 * @brief
 *	Get the distance between to points
 *	(using the taxicab metric).
 * @param x,y
 *	the points
 * @return
 *	the distance between the points
 */
float fvec3_dist_abs(const fvec3_t& u, const fvec3_t& v);

/**
 * @brief
 *	Get the squared distance between two points.
 *	(using the Euclidian metric).
 * @param u,v
 *	the vectors
 * @return
 *	the squared distance between the vectors
 */
float fvec3_dist_2(const fvec3_t& u, const fvec3_t& v);
float fvec3_decompose(const fvec3_t& src, const fvec3_t& vnrm, fvec3_t& vpara, fvec3_t& vperp);
bool fvec4_self_clear(fvec4_base_t v);
bool fvec4_self_scale(fvec4_base_t A, const float B);