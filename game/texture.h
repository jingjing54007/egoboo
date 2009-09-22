#pragma once

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

#include "egoboo_typedef.h"
#include "ogl_texture.h"

//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------
// Special Textures
enum e_global_tx_type
{
    TX_PARTICLE_TRANS = 0,
    TX_PARTICLE_LIGHT,
    TX_TILE_0,
    TX_TILE_1,
    TX_TILE_2,
    TX_TILE_3,
    TX_WATER_TOP,
    TX_WATER_LOW,
    TX_PHONG,
    TX_FONT,
    TX_BARS,
    TX_BLIP,
    TX_MAP,
    TX_XP_BAR,
    ICON_NULL,
    ICON_KEYB,
    ICON_MOUS,
    ICON_JOYA,
    ICON_JOYB,
    TX_LAST
};

//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------

#define TEXTURE_COUNT   (2*(MAX_TEXTURE + MAX_ICON))
#define INVALID_TEXTURE TEXTURE_COUNT

// declare special arrays of textures
DEFINE_LIST_EXTERN( oglx_texture, TxTexture, TEXTURE_COUNT );

//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------
void           TxTexture_init_all();
void           TxTexture_delete_all();
void           TxTexture_release_all();
int            TxTexture_get_free( int itex );
bool_t         TxTexture_free_one( int itex );
int            TxTexture_load_one( const char *filename, int itex_src, Uint32 key );
oglx_texture * TxTexture_get_ptr( int itex );