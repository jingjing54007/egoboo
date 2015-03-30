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

/// @file  egolib/math/Math.hpp
/// @brief Math utility functions
/// @author Johan Jansen
#pragma once

namespace Math
{
    /**
     * @brief
     *  Constrain a value within a specified range (same as clamping or clipping).
     * @param n
     *  the value
     * @param lower
     *  the minimum
     * @param upper
     *  the maximum
     * @return
     *  the constrained value
     */
    template <typename T>
    T constrain(const T& n, const T& lower, const T& upper)
    {
        return std::max(lower, std::min(n, upper));
    }

    /**
     * @brief
     *  Calculates the square of a number, this is same as X^2.
     *  This is much faster than using pow(val, 2)
     * @param val
     *  the number to square
     **/
    template <typename T>
    T sq(const T &value)
    {
        return value * value;
    }
}

namespace Ego
{
    namespace Math
    {
        /**
        * @brief
        *  Convert an angle from degree to radian.
        * @param x
        *  the angle in degree
        * @return
        *  the angle in radian
        */
        inline float degToRad(float x)
        {
            return x * 0.017453292519943295769236907684886f;
        }

        /**
        * @brief
        *  Convert an angle from degree to radian.
        * @param x
        *  the angle in degree
        * @return
        *  the angle in radian
        */
        inline double degToRad(double x)
        {
            return x * 0.017453292519943295769236907684886;
        }

        /**
        * @brief
        *  Convert an angle from radian to degree.
        * @param x
        *  the angle in radian
        * @return
        *  the angle in degree
        */
        inline float radToDeg(float x)
        {
            return x * 57.295779513082320876798154814105f;
        }

        /**
        * @brief
        *  Convert an angle from radian to degree.
        * @param x
        *  the angle in radian
        * @return
        *  the angle in degree
        */
        inline double radToDeg(double x)
        {
            return x * 57.295779513082320876798154814105;
        }
    }
}

namespace Ego
{
    namespace Math
    {
        /**
        * @brief
        *  Get \f$\sqrt{2}\f$.
        * @return
        *  \f$\sqrt{2}\f$
        * @remark
        *  Specializations for @a float and @a double are provided.
        */
        template <typename Type>
        Type sqrtTwo();

        template <>
        inline float sqrtTwo<float>()
        {
            return 1.4142135623730950488016887242097f;
        }

        template <>
        inline double sqrtTwo<double>()
        {
            return 1.4142135623730950488016887242097;
        }

        /**
        * @brief
        *  Get \f$\frac{1}{\sqrt{2}}\f$.
        * @return
        *  \f$\frac{1}{\sqrt{2}}\f$
        * @remark
        *  Specializations for @a float and @a double are provided.
        */
        template <typename Type>
        Type invSqrtTwo();

        template <>
        inline float invSqrtTwo()
        {
            return 0.70710678118654752440084436210485f;
        }

        template <>
        inline double invSqrtTwo()
        {
            // 		.70710678118654757
            //      .70710678118654752440
            return 0.70710678118654752440084436210485;
        }
    }
}

namespace Ego
{
    namespace Math
    {
        /**
        * @brief
        *  Get \f$\pi\f$.
        * @return
        *  \f$\pi\f$
        * @remark
        *  Overloads for @a float and @a double are provided.
        */
        template <typename Type>
        Type pi();

        template <>
        inline float pi<float>()
        {
            return 3.1415926535897932384626433832795f;
        }

        template <>
        inline double pi<double>()
        {
            return 3.1415926535897932384626433832795;
        }

        /**
        * @brief
        *  Get \f$\frac{1}{\pi}\f$.
        * @return
        *  \f$\frac{1}{\pi}\f$
        * @remark
        *  Specializations for @a float and @a double are provided.
        */
        template <typename Type>
        Type invPi();

        template <>
        inline float invPi<float>()
        {
            return 0.31830988618379067153776752674503f;
        }

        template <>
        inline double invPi<double>()
        {
            return 0.31830988618379067153776752674503;
        }

        /**
        * @brief
        *  Get \f$2 \cdot \pi\f$.
        * @return
        *  \f$2 \cdot \pi\f$
        * @remark
        *  Specializations for @a float and @a double are provided.
        */
        template <typename Type>
        Type twoPi();

        template <>
        inline float twoPi<float>()
        {
            return 6.283185307179586476925286766559f;
        }

        template <>
        inline double twoPi<double>()
        {
            return 6.283185307179586476925286766559;
        }

        /**
        * @brief
        *  Get \f$\frac{1}{2 \cdot \pi}\f$.
        * @return
        *  \f$\frac{1}{2 \cdot \pi}\f$
        * @remark
        *  Specializations for @a float and @a double are provided.
        */
        template <typename Type>
        Type invTwoPi();

        template <>
        inline float invTwoPi<float>()
        {
            return 0.15915494309189533576888376337251f;
        }

        template <>
        inline double invTwoPi<double>()
        {
            return 0.15915494309189533576888376337251;
        }

        /**
        * @brief
        *  Get \f$\frac{\pi}{2}\f$.
        * @return
        *  \f$\frac{\pi}{2}\f$
        */
        template <typename Type>
        Type piOverTwo();

        /**
        * @brief
        *  Get \f$\frac{\pi}{2}\f$.
        * @return
        *  \f$\frac{\pi}{2}\f$
        */
        template <>
        inline float piOverTwo<float>()
        {
            return 1.5707963267948966192313216916398f;
        }

        /**
        * @brief
        *  Get \f$\frac{\pi}{2}\f$.
        * @return
        *  \f$\frac{\pi}{2}\f$
        */
        template <>
        inline double piOverTwo<double>()
        {
            return 1.5707963267948966192313216916398;
        }

        /**
        * @brief
        *  Get \f$\frac{\pi}{4}\f$.
        * @return
        *  \f$\frac{\pi}{4}\f$
        */
        template <typename Type>
        Type piOverFour();

        /**
        * @brief
        *  Get \f$\frac{\pi}{4}\f$.
        * @return
        *  \f$\frac{\pi}{4}\f$
        */
        template <>
        inline float piOverFour<float>()
        {
            return 0.78539816339744830961566084581988f;
        }

        /**
        * @brief
        *  Get \f$\frac{\pi}{4}\f$.
        * @return
        *  \f$\frac{\pi}{4}\f$
        */
        template <>
        inline double piOverFour<double>()
        {
            return 0.78539816339744830961566084581988;
        }
    }
}