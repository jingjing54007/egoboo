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
//*    along with Egoboo.  If not, see <http:// www.gnu.org/licenses/>.
//*
//********************************************************************************************

/* Egoboo - mathstuff.c
 * The name's pretty self explanatory, doncha think?
 */

#include "egoboo_math.h"

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
float turntosin[TRIG_TABLE_SIZE];           // Convert chrturn>>2...  to sine
float turntocos[TRIG_TABLE_SIZE];           // Convert chrturn>>2...  to cosine

//--------------------------------------------------------------------------------------------
void make_turntosin( void )
{
    // ZZ> This function makes the lookup table for chrturn...
    int cnt;
    float ftmp = TWO_PI / (float)TRIG_TABLE_SIZE;

    cnt = 0;

    while ( cnt < 16384 )
    {
        turntosin[cnt] = SIN( cnt * ftmp );
        turntocos[cnt] = COS( cnt * ftmp );
        cnt++;
    }
}

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
// FAKE D3D FUNCTIONS
glVector vsub( glVector A, glVector B )
{
    glVector tmp;

    if (A.w == 0.0f) A.w = 1.0f;
    if (B.w == 0.0f) B.w = 1.0f;

    tmp.x = A.x - B.x;
    tmp.y = A.y - B.y;
    tmp.z = A.z - B.z;
    tmp.w = A.w - B.w;

    return( tmp );
}

glVector Normalize( glVector vec )
{
    glVector tmp = vec;

    if ( ABS(vec.x) + ABS(vec.y) + ABS(vec.z) > 0 )
    {
        float len = SQRT( vec.x * vec.x + vec.y * vec.y + vec.z * vec.z );

        tmp.x /= len;
        tmp.y /= len;
        tmp.z /= len;

        tmp.w = vec.w;
    }

    return tmp ;
}

glVector CrossProduct( glVector A, glVector B )
{
    glVector tmp;
    tmp.x = A.y * B.z - A.z * B.y;
    tmp.y = A.z * B.x - A.x * B.z;
    tmp.z = A.x * B.y - A.y * B.x;
	tmp.w = 1.0f;
    return( tmp );
}

float DotProduct( glVector A, glVector B )
{ return( A.x*B.x + A.y*B.y + A.z*B.z ); }

//---------------------------------------------------------------------------------------------
// Math Stuff-----------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------
// inline D3DMATRIX IdentityMatrix()
glMatrix IdentityMatrix()
{
    glMatrix tmp;

    tmp.CNV( 0, 0 ) = 1; tmp.CNV( 1, 0 ) = 0; tmp.CNV( 2, 0 ) = 0; tmp.CNV( 3, 0 ) = 0;
    tmp.CNV( 0, 1 ) = 0; tmp.CNV( 1, 1 ) = 1; tmp.CNV( 2, 1 ) = 0; tmp.CNV( 3, 1 ) = 0;
    tmp.CNV( 0, 2 ) = 0; tmp.CNV( 1, 2 ) = 0; tmp.CNV( 2, 2 ) = 1; tmp.CNV( 3, 2 ) = 0;
    tmp.CNV( 0, 3 ) = 0; tmp.CNV( 1, 3 ) = 0; tmp.CNV( 2, 3 ) = 0; tmp.CNV( 3, 3 ) = 1;
    return( tmp );
}

//--------------------------------------------------------------------------------------------
// inline D3DMATRIX ZeroMatrix(void)  // initializes matrix to zero
glMatrix ZeroMatrix( void )
{
    glMatrix ret;
    int i, j;

    for ( i = 0; i < 4; i++ )
    {
        for ( j = 0; j < 4; j++ )
        {
            ret.CNV( i, j ) = 0;
        }
    }

    return ret;
}

//--------------------------------------------------------------------------------------------
// inline D3DMATRIX MatrixMult(const D3DMATRIX a, const D3DMATRIX b)
glMatrix MatrixMult( const glMatrix a, const glMatrix b )
{
    glMatrix ret = ZeroMatrix();
    int i, j, k;

    for ( i = 0; i < 4; i++ )
    {
        for ( j = 0; j < 4; j++ )
        {
            for ( k = 0; k < 4; k++ )
            {
                ret.CNV( i, j ) += a.CNV( k, j ) * b.CNV( i, k );
            }
        }
    }

    return ret;
}

//--------------------------------------------------------------------------------------------
// D3DMATRIX Translate(const float dx, const float dy, const float dz)
glMatrix Translate( const float dx, const float dy, const float dz )
{
    glMatrix ret = IdentityMatrix();

    ret.CNV( 3, 0 ) = dx;
    ret.CNV( 3, 1 ) = dy;
    ret.CNV( 3, 2 ) = dz;

    return ret;
}

//--------------------------------------------------------------------------------------------
// D3DMATRIX RotateX(const float rads)
glMatrix RotateX( const float rads )
{
    float cosine = COS( rads );
    float sine = SIN( rads );

    glMatrix ret = IdentityMatrix();

    ret.CNV( 1, 1 ) = cosine;
    ret.CNV( 2, 2 ) = cosine;
    ret.CNV( 1, 2 ) = -sine;
    ret.CNV( 2, 1 ) = sine;

    return ret;
}

//--------------------------------------------------------------------------------------------
// D3DMATRIX RotateY(const float rads)
glMatrix RotateY( const float rads )
{
    float cosine = COS( rads );
    float sine = SIN( rads );

    glMatrix ret = IdentityMatrix();

    ret.CNV( 0, 0 ) = cosine; //0,0
    ret.CNV( 2, 2 ) = cosine; //2,2
    ret.CNV( 0, 2 ) = sine; //0,2
    ret.CNV( 2, 0 ) = -sine; //2,0

    return ret;
}

//--------------------------------------------------------------------------------------------
// D3DMATRIX RotateZ(const float rads)
glMatrix RotateZ( const float rads )
{
    float cosine = COS( rads );
    float sine = SIN( rads );

    glMatrix ret = IdentityMatrix();

    ret.CNV( 0, 0 ) = cosine; //0,0
    ret.CNV( 1, 1 ) = cosine; //1,1
    ret.CNV( 0, 1 ) = -sine; //0,1
    ret.CNV( 1, 0 ) = sine; //1,0

    return ret;
}

//--------------------------------------------------------------------------------------------
// D3DMATRIX ScaleXYZ(const float sizex, const float sizey, const float sizez)
glMatrix ScaleXYZ( const float sizex, const float sizey, const float sizez )
{
    glMatrix ret = IdentityMatrix();

    ret.CNV( 0, 0 ) = sizex; //0,0
    ret.CNV( 1, 1 ) = sizey; //1,1
    ret.CNV( 2, 2 ) = sizez; //2,2

    return ret;
}

//--------------------------------------------------------------------------------------------
/*D3DMATRIX ScaleXYZRotateXYZTranslate(const float sizex, const float sizey, const float sizez,
   Uint16 turnz, Uint16 turnx, Uint16 turny,
   float tx, float ty, float tz)*/
glMatrix ScaleXYZRotateXYZTranslate( const float sizex, const float sizey, const float sizez, Uint16 turnz, Uint16 turnx, Uint16 turny, float tx, float ty, float tz )
{
    float cx = turntocos[turnx];
    float sx = turntosin[turnx];
    float cy = turntocos[turny];
    float sy = turntosin[turny];
    float cz = turntocos[turnz];
    float sz = turntosin[turnz];

    float sxsy = sx * sy;
    float cxsy = cx * sy;
    float sxcy = sx * cy;
    float cxcy = cx * cy;

    glMatrix ret;

    ret.CNV( 0, 0 ) = sizex * ( cy * cz ); //0,0
    ret.CNV( 0, 1 ) = sizex * ( sxsy * cz + cx * sz );  //0,1
    ret.CNV( 0, 2 ) = sizex * ( -cxsy * cz + sx * sz );  //0,2
    ret.CNV( 0, 3 ) = 0;       //0,3

    ret.CNV( 1, 0 ) = sizey * ( -cy * sz ); //1,0
    ret.CNV( 1, 1 ) = sizey * ( -sxsy * sz + cx * cz );  //1,1
    ret.CNV( 1, 2 ) = sizey * ( cxsy * sz + sx * cz );  //1,2
    ret.CNV( 1, 3 ) = 0;       //1,3

    ret.CNV( 2, 0 ) = sizez * ( sy );  //2,0
    ret.CNV( 2, 1 ) = sizez * ( -sxcy );   //2,1
    ret.CNV( 2, 2 ) = sizez * ( cxcy );   //2,2
    ret.CNV( 2, 3 ) = 0;       //2,3

    ret.CNV( 3, 0 ) = tx;       //3,0
    ret.CNV( 3, 1 ) = ty;       //3,1
    ret.CNV( 3, 2 ) = tz;       //3,2
    ret.CNV( 3, 3 ) = 1;       //3,3

    return ret;
}

//--------------------------------------------------------------------------------------------
// D3DMATRIX FourPoints(float orix, float oriy, float oriz,
glMatrix FourPoints( float orix, float oriy, float oriz,
                     float widx, float widy, float widz,
                     float forx, float fory, float forz,
                     float upx,  float upy,  float upz,
                     float scale )
{
    glMatrix tmp;

    glVector vWid, vFor, vUp;

    vWid.x = widx - orix;
    vWid.y = widy - oriy;
    vWid.z = widz - oriz;

    vUp.x = upx - orix;
    vUp.y = upy - oriy;
    vUp.z = upz - oriz;

    vFor.x = forx - orix;
    vFor.y = fory - oriy;
    vFor.z = forz - oriz;

    // assume that the length of the grip edges if 16
    //scale *= 0.0f;
    vWid = Normalize(vWid);
    vUp  = Normalize(vUp );
    vFor = Normalize(vFor);

    tmp.CNV( 0, 0 ) = -scale * vWid.x;  // HUK
    tmp.CNV( 0, 1 ) = -scale * vWid.y;  // HUK
    tmp.CNV( 0, 2 ) = -scale * vWid.z;  // HUK
    tmp.CNV( 0, 3 ) = 0.0f;

    tmp.CNV( 1, 0 ) = scale * vFor.x;
    tmp.CNV( 1, 1 ) = scale * vFor.y;
    tmp.CNV( 1, 2 ) = scale * vFor.z;
    tmp.CNV( 1, 3 ) = 0.0f;

    tmp.CNV( 2, 0 ) = scale * vUp.x;
    tmp.CNV( 2, 1 ) = scale * vUp.y;
    tmp.CNV( 2, 2 ) = scale * vUp.z;
    tmp.CNV( 2, 3 ) = 0.0f;

    tmp.CNV( 3, 0 ) = orix;
    tmp.CNV( 3, 1 ) = oriy;
    tmp.CNV( 3, 2 ) = oriz;
    tmp.CNV( 3, 3 ) = 1.0f;

    return( tmp );
}

//--------------------------------------------------------------------------------------------
// MN This probably should be replaced by a call to gluLookAt, don't see why we need to make our own...
//
// inline D3DMATRIX ViewMatrix(const D3DVECTOR from,      // camera location
glMatrix ViewMatrix( const glVector from,     // camera location
                     const glVector at,        // camera look-at target
                     const glVector world_up,  // world�s up, usually 0, 0, 1
                     const float roll )         // clockwise roll around
//    viewing direction,
//    in radians
{
    glMatrix view = IdentityMatrix();
    glVector up, right, view_dir;

    view_dir = Normalize( vsub( at, from ) );
    right = CrossProduct( world_up, view_dir );
    up = CrossProduct( view_dir, right );
    right = Normalize( right );
    up = Normalize( up );

    view.CNV( 0, 0 ) = right.x;       //0,0
    view.CNV( 1, 0 ) = right.y;       //1,0
    view.CNV( 2, 0 ) = right.z;       //2,0
    view.CNV( 0, 1 ) = up.x;         //0,1
    view.CNV( 1, 1 ) = up.y;         //1,1
    view.CNV( 2, 1 ) = up.z;         //2,1
    view.CNV( 0, 2 ) = view_dir.x;       //0,2
    view.CNV( 1, 2 ) = view_dir.y;       //1,2
    view.CNV( 2, 2 ) = view_dir.z;     //2,2
    view.CNV( 3, 0 ) = -DotProduct( right, from );   //3,0
    view.CNV( 3, 1 ) = -DotProduct( up, from );     //3,1
    view.CNV( 3, 2 ) = -DotProduct( view_dir, from ); //3,2

    if ( roll != 0.0f )
    {
        // MatrixMult function shown above
        view = MatrixMult( RotateZ( -roll ), view );
    }

    return view;
}

//--------------------------------------------------------------------------------------------
// MN Again, there is a gl function for this, glFrustum or gluPerspective... does this account for viewport ratio?
//
// inline D3DMATRIX ProjectionMatrix(const float near_plane,     // distance to near clipping plane
glMatrix ProjectionMatrix( const float near_plane,    // distance to near clipping plane
                           const float far_plane,      // distance to far clipping plane
                           const float fov )           // field of view angle, in radians
{
    float c = COS( fov * 0.5f );
    float s = SIN( fov * 0.5f );
    float Q = s / ( 1.0f - near_plane / far_plane );

    glMatrix ret = ZeroMatrix();

    ret.CNV( 0, 0 ) = c;         //0,0
    ret.CNV( 1, 1 ) = c;         //1,1
    ret.CNV( 2, 2 ) = Q;         //2,2
    ret.CNV( 3, 2 ) = -Q * near_plane; //3,2
    ret.CNV( 2, 3 ) = s;         //2,3

    return ret;
}

//----------------------------------------------------
// GS - Normally we souldn't this function but I found it in the rendering of the particules.
//
// This is just a MulVectorMatrix for now. The W division and screen size multiplication
// must be done afterward.
// Isn't tested!!!!
void  TransformVertices( glMatrix *pMatrix, glVector *pSourceV, glVector *pDestV, Uint32  pNumVertor )
{
    while ( pNumVertor-- )
    {
        pDestV->x = pSourceV->x * pMatrix->v[0] + pSourceV->y * pMatrix->v[4] + pSourceV->z * pMatrix->v[8] + pSourceV->w * pMatrix->v[12];
        pDestV->y = pSourceV->x * pMatrix->v[1] + pSourceV->y * pMatrix->v[5] + pSourceV->z * pMatrix->v[9] + pSourceV->w * pMatrix->v[13];
        pDestV->z = pSourceV->x * pMatrix->v[2] + pSourceV->y * pMatrix->v[6] + pSourceV->z * pMatrix->v[10] + pSourceV->w * pMatrix->v[14];
        pDestV->w = pSourceV->x * pMatrix->v[3] + pSourceV->y * pMatrix->v[7] + pSourceV->z * pMatrix->v[11] + pSourceV->w * pMatrix->v[15];
        pDestV++;
        pSourceV++;
    }
}
