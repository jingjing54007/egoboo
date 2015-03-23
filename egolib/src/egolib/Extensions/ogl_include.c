//********************************************************************************************
//*
//*    This file is part of the opengl extensions library. This library is
//*    distributed with Egoboo.
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

/// @file egolib/Extensions/ogl_include.c
/// @ingroup _ogl_extensions_
/// @brief Base implementation of the OpenGL extensions
/// @details

#include "egolib/Extensions/ogl_include.h"
#include "egolib/Extensions/ogl_debug.h"

#if 0
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
#define LOCAL_STDERR ((NULL == _ogl_include_stderr) ? stderr : _ogl_include_stderr)

//--------------------------------------------------------------------------------------------
static FILE * _ogl_include_stderr = NULL;

//--------------------------------------------------------------------------------------------
GLboolean handle_opengl_error( void )
{
    GLboolean error = GL_TRUE;

    switch ( glGetError() )
    {
        case GL_INVALID_ENUM:      fprintf( LOCAL_STDERR, "GLenum argument out of range" ); break;
        case GL_INVALID_VALUE:     fprintf( LOCAL_STDERR, "Numeric argument out of range" ); break;
        case GL_INVALID_OPERATION: fprintf( LOCAL_STDERR, "Operation illegal in current state" ); break;
        case GL_STACK_OVERFLOW:    fprintf( LOCAL_STDERR, "Command would cause a stack overflow" ); break;
        case GL_STACK_UNDERFLOW:   fprintf( LOCAL_STDERR, "Command would cause a stack underflow" ); break;
        case GL_OUT_OF_MEMORY:     fprintf( LOCAL_STDERR, "Not enough memory left to execute command" ); break;
        default: error = GL_FALSE; break;
    };

    if ( error ) fflush( LOCAL_STDERR );

    return error;
}
#endif

#if 0
//--------------------------------------------------------------------------------------------
void oglx_ViewMatrix( GLXmatrix view,
                      const GLXvector3f from,     // camera location
                      const GLXvector3f at,        // camera look-at target
                      const GLXvector3f world_up,  // world�s up, usually 0, 0, 1
                      const GLfloat roll )     // clockwise roll around viewing direction, in radians
{
    ATTRIB_PUSH( __FUNCTION__, GL_TRANSFORM_BIT );
    {
        GLint matrix_mode[1];

        // save the matrix mode
        GL_DEBUG( glGetIntegerv )( GL_MATRIX_MODE, matrix_mode );

        // store the GL_MODELVIEW matrix (this stack has a finite depth, minimum of 32)
        GL_DEBUG( glMatrixMode )( GL_MODELVIEW );
        GL_DEBUG( glPushMatrix )();
        GL_DEBUG( glLoadIdentity )();

        GL_DEBUG( glScalef )( -1, 1, 1 );

        if ( roll > .001 )
        {
            // GLXmatrix stupid_intermediate_matrix = mat_RotateZ( roll );
            // GL_DEBUG(glMultMatrixf)(stupid_intermediate_matrix );
        }

        GL_DEBUG( gluLookAt )( from[0], from[1], from[2], at[0], at[1], at[2], world_up[0], world_up[1], world_up[2] );

        GL_DEBUG( glGetFloatv )( GL_MODELVIEW_MATRIX, view );

        GL_DEBUG( glPopMatrix )();

        // restore the matrix mode
        GL_DEBUG( glMatrixMode )( matrix_mode[0] );
    }
    ATTRIB_POP( __FUNCTION__ );
}

//--------------------------------------------------------------------------------------------
void oglx_ProjectionMatrix( GLXmatrix proj,
                            const GLfloat near_plane,    // distance to near clipping plane
                            const GLfloat far_plane,      // distance to far clipping plane
                            const GLfloat fov )           // field of view angle, in radians
{
    ATTRIB_PUSH( __FUNCTION__, GL_TRANSFORM_BIT );
    {
        GLint matrix_mode[1];
        GLint viewport[ 4 ];

        // save the matrix mode
        GL_DEBUG( glGetIntegerv )( GL_MATRIX_MODE, matrix_mode );

        // use OpenGl to create our projection matrix
        GL_DEBUG( glGetIntegerv )( GL_VIEWPORT, viewport );

        // store the GL_PROJECTION matrix (this stack has a finite depth, minimum of 32)
        GL_DEBUG( glMatrixMode )( GL_PROJECTION );
        GL_DEBUG( glPushMatrix )();
        GL_DEBUG( glLoadIdentity )();

        GL_DEBUG( gluPerspective )( fov, ( GLfloat )( viewport[ 2 ] - viewport[ 0 ] ) / ( GLfloat )( viewport[ 3 ] - viewport[ 1 ] ), near_plane, far_plane );
        GL_DEBUG( glGetFloatv )( GL_PROJECTION_MATRIX, proj );

        // restore the GL_PROJECTION matrix
        GL_DEBUG( glMatrixMode )( GL_PROJECTION );
        GL_DEBUG( glPopMatrix )();

        // restore the matrix mode
        GL_DEBUG( glMatrixMode )( matrix_mode[0] );
    }
    ATTRIB_POP( __FUNCTION__ );
}

//--------------------------------------------------------------------------------------------
GLboolean oglx_ProjectionMatrix_2( GLXmatrix proj, GLfloat frustum_near, GLfloat frustum_far, GLfloat fov_rad, GLfloat screen[] )
{
    // check for bad pointers
    if ( NULL == proj ||  NULL == screen ) return GL_FALSE;

    // check for stupod fov_rad values
    if ( 0.0f == fov_rad || fov_rad < -1.570796f || fov_rad > 1.570796f ) return GL_FALSE;

    ATTRIB_PUSH( __FUNCTION__, GL_TRANSFORM_BIT );
    {
        GLfloat frustum_width, frustum_height;
        GLfloat aspect_ratio;
        GLint matrix_mode[1];

        aspect_ratio = ( screen[2] - screen[0] ) / ( screen[3] - screen[1] );

        // set the frustum height based of the given FOV
        frustum_height = frustum_near * tan( 0.5f * fov_rad );

        // keep the same aspect ratio as the camera's visible area
        frustum_width  = frustum_height * aspect_ratio;

        // grab the current matrix mode
        GL_DEBUG( glGetIntegerv )( GL_MATRIX_MODE, matrix_mode );

        // switch to the projection mode
        GL_DEBUG( glMatrixMode )( GL_PROJECTION );

        // save the old projection matrix
        GL_DEBUG( glPushMatrix )();

        // use glFrustum to set the projection mode
        // assume an on-axis projection
        GL_DEBUG( glLoadIdentity )();
        GL_DEBUG( glFrustum )( -frustum_width, frustum_width, -frustum_height, frustum_height, frustum_near, frustum_far );
        GL_DEBUG( glGetFloatv )( GL_PROJECTION_MATRIX, proj );

        // restore the old matrix
        GL_DEBUG( glPopMatrix )();

        // restore the old matrix mode
        GL_DEBUG( glMatrixMode )( matrix_mode[0] );
    }
    ATTRIB_POP( __FUNCTION__ );

    return GL_TRUE;
}
#endif

#if 0
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
FILE * set_ogl_include_stderr( FILE * pfile )
{
    FILE * pfile_old = _ogl_include_stderr;

    if ( NULL == pfile )
    {
        _ogl_include_stderr  = stdout;
    }
    else
    {
        _ogl_include_stderr  = pfile;
    }

    return pfile_old;
}
#endif