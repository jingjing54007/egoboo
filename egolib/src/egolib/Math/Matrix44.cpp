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

/// @file   egolib/Math/Matrix44.cpp
/// @brief  4x4 matrices.
/// @author Michael Heilmann et al.

#include "egolib/Math/Matrix44.hpp"

//--------------------------------------------------------------------------------------------
float * mat_ScaleXYZ_RotateXYZ_TranslateXYZ_SpaceFixed(fmat_4x4_base_t DST, const fvec3_t& scale, const TURN_T turn_z, const TURN_T turn_x, const TURN_T turn_y, const fvec3_t& translate)
{
    float cx = turntocos[turn_x & TRIG_TABLE_MASK];
    float sx = turntosin[turn_x & TRIG_TABLE_MASK];
    float cy = turntocos[turn_y & TRIG_TABLE_MASK];
    float sy = turntosin[turn_y & TRIG_TABLE_MASK];
    float cz = turntocos[turn_z & TRIG_TABLE_MASK];
    float sz = turntosin[turn_z & TRIG_TABLE_MASK];

    if (NULL == DST) return NULL;

    DST[MAT_IDX(0, 0)] = scale[kX] * (cz * cy);
    DST[MAT_IDX(0, 1)] = scale[kX] * (cz * sy * sx + sz * cx);
    DST[MAT_IDX(0, 2)] = scale[kX] * (sz * sx - cz * sy * cx);
    DST[MAT_IDX(0, 3)] = 0.0f;

    DST[MAT_IDX(1, 0)] = scale[kY] * (-sz * cy);
    DST[MAT_IDX(1, 1)] = scale[kY] * (-sz * sy * sx + cz * cx);
    DST[MAT_IDX(1, 2)] = scale[kY] * (sz * sy * cx + cz * sx);
    DST[MAT_IDX(1, 3)] = 0.0f;

    DST[MAT_IDX(2, 0)] = scale[kZ] * (sy);
    DST[MAT_IDX(2, 1)] = scale[kZ] * (-cy * sx);
    DST[MAT_IDX(2, 2)] = scale[kZ] * (cy * cx);
    DST[MAT_IDX(2, 3)] = 0.0f;

    DST[MAT_IDX(3, 0)] = translate[kX];
    DST[MAT_IDX(3, 1)] = translate[kY];
    DST[MAT_IDX(3, 2)] = translate[kZ];
    DST[MAT_IDX(3, 3)] = 1.0f;

    return DST;
}

//--------------------------------------------------------------------------------------------
float * mat_ScaleXYZ_RotateXYZ_TranslateXYZ_BodyFixed(fmat_4x4_base_t DST, const fvec3_t& scale, const TURN_T turn_z, const TURN_T turn_x, const TURN_T turn_y, const fvec3_t& translate)
{
    /// @author BB
    /// @details Transpose the SpaceFixed representation and invert the angles to get the BodyFixed representation

    float cx = turntocos[turn_x & TRIG_TABLE_MASK];
    float sx = turntosin[turn_x & TRIG_TABLE_MASK];
    float cy = turntocos[turn_y & TRIG_TABLE_MASK];
    float sy = turntosin[turn_y & TRIG_TABLE_MASK];
    float cz = turntocos[turn_z & TRIG_TABLE_MASK];
    float sz = turntosin[turn_z & TRIG_TABLE_MASK];

    if (NULL == DST) return NULL;

    DST[MAT_IDX(0, 0)] = scale[kX] * (cz * cy - sz * sy * sx);
    DST[MAT_IDX(0, 1)] = scale[kX] * (sz * cy + cz * sy * sx);
    DST[MAT_IDX(0, 2)] = scale[kX] * (-cx * sy);
    DST[MAT_IDX(0, 3)] = 0.0f;

    DST[MAT_IDX(1, 0)] = scale[kY] * (-sz * cx);
    DST[MAT_IDX(1, 1)] = scale[kY] * (cz * cx);
    DST[MAT_IDX(1, 2)] = scale[kY] * (sx);
    DST[MAT_IDX(1, 3)] = 0.0f;

    DST[MAT_IDX(2, 0)] = scale[kZ] * (cz * sy + sz * sx * cy);
    DST[MAT_IDX(2, 1)] = scale[kZ] * (sz * sy - cz * sx * cy);
    DST[MAT_IDX(2, 2)] = scale[kZ] * (cy * cx);
    DST[MAT_IDX(2, 3)] = 0.0f;

    DST[MAT_IDX(3, 0)] = translate[kX];
    DST[MAT_IDX(3, 1)] = translate[kY];
    DST[MAT_IDX(3, 2)] = translate[kZ];
    DST[MAT_IDX(3, 3)] = 1.0f;

    return DST;
}

//--------------------------------------------------------------------------------------------
float * mat_FourPoints(fmat_4x4_base_t DST, const fvec4_t& ori, const fvec4_t& wid, const fvec4_t& frw, const fvec4_t& up, const float scale)
{
    fvec3_t vWid, vFor, vUp;

    if (NULL == DST) return NULL;

    vWid[kX] = wid[kX] - ori[kX];
    vWid[kY] = wid[kY] - ori[kY];
    vWid[kZ] = wid[kZ] - ori[kZ];

    vUp[kX] = up[kX] - ori[kX];
    vUp[kY] = up[kY] - ori[kY];
    vUp[kZ] = up[kZ] - ori[kZ];

    vFor[kX] = frw[kX] - ori[kX];
    vFor[kY] = frw[kY] - ori[kY];
    vFor[kZ] = frw[kZ] - ori[kZ];

    vWid.normalize();
    vUp.normalize();
    vFor.normalize();

    DST[MAT_IDX(0, 0)] = -scale * vWid[kX];  // HUK
    DST[MAT_IDX(0, 1)] = -scale * vWid[kY];  // HUK
    DST[MAT_IDX(0, 2)] = -scale * vWid[kZ];  // HUK
    DST[MAT_IDX(0, 3)] = 0.0f;

    DST[MAT_IDX(1, 0)] = scale * vFor[kX];
    DST[MAT_IDX(1, 1)] = scale * vFor[kY];
    DST[MAT_IDX(1, 2)] = scale * vFor[kZ];
    DST[MAT_IDX(1, 3)] = 0.0f;

    DST[MAT_IDX(2, 0)] = scale * vUp[kX];
    DST[MAT_IDX(2, 1)] = scale * vUp[kY];
    DST[MAT_IDX(2, 2)] = scale * vUp[kZ];
    DST[MAT_IDX(2, 3)] = 0.0f;

    DST[MAT_IDX(3, 0)] = ori[kX];
    DST[MAT_IDX(3, 1)] = ori[kY];
    DST[MAT_IDX(3, 2)] = ori[kZ];
    DST[MAT_IDX(3, 3)] = 1.0f;

    return DST;
}

//--------------------------------------------------------------------------------------------
void mat_View(fmat_4x4_t& DST,const fvec3_t& from,const fvec3_t& at,const fvec3_t& world_up,const float roll)
{
    DST = fmat_4x4_t::identity();
    fvec3_t view_dir = at - from;
    view_dir.normalize();
    fvec3_t right = world_up.cross(view_dir);
    fvec3_t up = view_dir.cross(right);
    right.normalize();
    up.normalize();

    // 0th row.
    DST(0, 0) = right[kX];
    DST(0, 1) = right[kY];
    DST(0, 2) = right[kZ];

    // 1st row.
    DST(1, 0) = up[kX];
    DST(1, 1) = up[kY];
    DST(1, 2) = up[kZ];

    // 2nd row.
    DST(2,0) = view_dir[kX];
    DST(2,1) = view_dir[kY];
    DST(2,2) = view_dir[kZ];

    // 3rd row.
    DST(3,0) = -right.dot(from);
    DST(3,1) = -up.dot(from);
    DST(3,2) = -view_dir.dot(from);

    if (roll != 0.0f)
    {
        DST = fmat_4x4_t::rotationZ(-roll) * DST;
    }
}
//--------------------------------------------------------------------------------------------
fvec3_t mat_getTranslate(const fmat_4x4_t& mat)
{
    return fvec3_t(mat(0, 3), mat(1, 3), mat(2, 3));
}
//--------------------------------------------------------------------------------------------
fvec3_t mat_getChrUp(const fmat_4x4_t& mat)
{
    return fvec3_t(mat(0, 2), mat(1, 2), mat(2, 2));
}

fvec3_t mat_getChrForward(const fmat_4x4_t& mat)
{
    return fvec3_t(-mat(0, 0), -mat(1, 0), -mat(2, 0));
}

fvec3_t mat_getChrRight(const fmat_4x4_t& mat)
{
    return fvec3_t(mat(0, 1), mat(1, 1), mat(2, 1));
}

//--------------------------------------------------------------------------------------------
bool mat_getCamUp(const fmat_4x4_t& mat, fvec3_t& up)
{
    // for the camera
    up[kX] = mat.v[MAT_IDX(0, 1)]; // m(1,0)
    up[kY] = mat.v[MAT_IDX(1, 1)]; // m(1,1)
    up[kZ] = mat.v[MAT_IDX(2, 1)]; // m(1,2)

    return true;
}

bool mat_getCamRight(const fmat_4x4_t& mat, fvec3_t& right)
{
    // for the camera
    right[kX] = -mat.v[MAT_IDX(0, 0)]; // -m(0,0)
    right[kY] = -mat.v[MAT_IDX(1, 0)]; // -m(0,1)
    right[kZ] = -mat.v[MAT_IDX(2, 0)]; // -m(0,2)

    return true;
}

bool mat_getCamForward(const fmat_4x4_t& mat, fvec3_t& forward)
{
    // for the camera
    forward[kX] = -mat.v[MAT_IDX(0, 2)];
    forward[kY] = -mat.v[MAT_IDX(1, 2)];
    forward[kZ] = -mat.v[MAT_IDX(2, 2)];

    return true;
}

//--------------------------------------------------------------------------------------------

void mat_gluLookAt(fmat_4x4_t &dst, const fmat_4x4_t &src, const fvec3_t& eye, const fvec3_t& center, const fvec3_t& up)
{
    dst = src * fmat_4x4_t::lookAt(eye, center, up);
}

void mat_glRotate(fmat_4x4_t &dst, const fmat_4x4_t &src, const float angle, const fvec3_t& axis)
{
    fmat_4x4_t R;
    float s = std::sin(Ego::Math::degToRad(angle));
    float c = std::cos(Ego::Math::degToRad(angle));
    
    fvec3_t axis_ = axis;
    axis_.normalize();

    // First row.
    R(0, 0) = axis_[kX] * axis_[kX] * (1 - c) + c;
    R(0, 1) = axis_[kX] * axis_[kY] * (1 - c) - axis_[kZ] * s;
    R(0, 2) = axis_[kX] * axis_[kZ] * (1 - c) + axis_[kY] * s;
    R(0, 3) = 0.0f;
    
    // 2nd row.
    R(1, 0) = axis_[kY] * axis_[kX] * (1 - c) + axis_[kZ] * s;
    R(1, 1) = axis_[kY] * axis_[kY] * (1 - c) + c;
    R(1, 2) = axis_[kY] * axis_[kZ] * (1 - c) - axis_[kX] * s;
    R(1, 3) = 0.0f;
    
    // 3rd row.
    R(2, 0) = axis_[kZ] * axis_[kX] * (1 - c) - axis_[kY] * s;
    R(2, 1) = axis_[kZ] * axis_[kY] * (1 - c) + axis_[kX] * s;
    R(2, 2) = axis_[kZ] * axis_[kZ] * (1 - c) + c;
    R(2, 3) = 0.0f;
    
    R(3, 0) = 0;
    R(3, 1) = 0;
    R(3, 2) = 0;
    R(3, 3) = 1;
    
    dst = src * R;
}

void dump_matrix(const fmat_4x4_base_t a)
{
    if (NULL == a) return;

    for (size_t j = 0; j < 4; j++)
    {
        printf("  ");

        for (size_t i = 0; i < 4; i++)
        {
            printf("%f ", a[MAT_IDX(i, j)]);
        }
        printf("\n");
    }
}
