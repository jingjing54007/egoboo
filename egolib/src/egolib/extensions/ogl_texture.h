#pragma once
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

/// @defgroup _ogl_extensions_ Extensions to OpenGL

/// @file egolib/extensions/ogl_texture.h
/// @ingroup _ogl_extensions_
/// @brief Definitions for OpenGL texture loading using SDL_image
/// @details

#include <SDL.h>

#include "egolib/extensions/ogl_include.h"
#include "egolib/extensions/ogl_debug.h"
#include "egolib/extensions/ogl_extensions.h"

#include "egolib/typedef.h"

#if defined(__cplusplus)
extern "C"
{
#endif

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------

    struct s_oglx_texture_parameters;
    typedef struct s_oglx_texture_parameters oglx_texture_parameters_t;

    struct s_oglx_texture;
    typedef struct s_oglx_texture oglx_texture_t;

    typedef GLfloat oglx_frect_t[4];

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------

#define INVALID_KEY    ( (Uint32) (~0) )

#define VALID_BINDING( BIND ) ( (0 != (BIND)) && (INVALID_GL_ID != (BIND)) )
#define ERROR_IMAGE_BINDING( BIND ) ( ErrorImage_get_binding() == (BIND) )

#if 0
/// OpenGL Texture filtering methods
    enum e_tx_filters
    {
        TX_UNFILTERED,
        TX_LINEAR,
        TX_MIPMAP,
        TX_BILINEAR,
        TX_TRILINEAR_1,
        TX_TRILINEAR_2,
        TX_ANISOTROPIC,
        TX_FILTER_COUNT
    };
#endif

// this typedef must be after the enum definition or gcc has a fit
    typedef enum e_tx_filters TX_FILTERS;

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------

    struct s_oglx_texture
    {
        GLboolean    base_valid;
        gl_texture_t base;

        GLuint        valid;           ///< whether or not the texture has been initialized
        char          name[256];       ///< the name of the original file
        int           imgW, imgH;      ///< the height & width of the texture data

        SDL_Surface * surface;         ///< the original texture data
        SDL_bool      has_alpha;       ///< the alpha for the texture
    };

    oglx_texture_t * oglx_texture_ctor( oglx_texture_t * texture );
    void             oglx_texture_dtor( oglx_texture_t * texture );

    GLuint  oglx_texture_Convert( oglx_texture_t *texture, SDL_Surface * pimage, Uint32 key );
    GLuint  oglx_texture_Load( oglx_texture_t *texture, const char *filename, Uint32 key );
    void    oglx_texture_Release( oglx_texture_t *texture );
    void    oglx_texture_Bind( oglx_texture_t * texture );

    GLuint    oglx_texture_getTextureID( const oglx_texture_t *texture );
    GLsizei   oglx_texture_getImageHeight( const oglx_texture_t *texture );
    GLsizei   oglx_texture_getImageWidth( const oglx_texture_t *texture );
    GLsizei   oglx_texture_getTextureWidth( const oglx_texture_t *texture );
    GLsizei   oglx_texture_getTextureHeight( const oglx_texture_t *texture );
    void      oglx_texture_setAlpha( oglx_texture_t *texture, GLfloat alpha );
    GLfloat   oglx_texture_getAlpha( const oglx_texture_t *texture );
    GLboolean oglx_texture_getSize( const oglx_texture_t *texture, oglx_frect_t tx_rect, oglx_frect_t img_rect );

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------

    struct s_oglx_texture_parameters
    {
        TX_FILTERS texturefilter;
        GLfloat    userAnisotropy;
    };

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------

    extern oglx_texture_parameters_t tex_params;

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------

    void      oglx_grab_texture_state( GLenum target, GLint level, oglx_texture_t * texture );
    GLboolean oglx_texture_Valid( oglx_texture_t *ptex );

    GLuint    oglx_bind_to_tex_params( GLuint binding, GLenum target, GLint wrap_s, GLint wrap_t );

    void      ErrorImage_bind( GLenum target, GLuint id );
    GLuint    ErrorImage_get_binding( void );

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------

#if defined(__cplusplus)
}

#endif

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------

#define _extensions_ogl_texture_h