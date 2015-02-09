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

/// @file game/gui/UIManager.hpp
/// @details The UIManager contains utilities for the GUI system and stores various shared resources
///		     and properties for GUIComponents.
/// @author Johan Jansen
#pragma once

#include "game/egoboo_typedef.h"

struct Font;

class UIManager
{
public:
	UIManager();

	~UIManager();

	/**
	* @return
	*	The default rendering Font for the GUI system
	**/
	Font* getDefaultFont() const;

	/**
	* @return
	*	Current screen resolution width
	**/
	int getScreenWidth() const;

	/**
	* @return
	*	Current screen resolution height
	**/
	int getScreenHeight() const;

	/**
	* @brief
	*	Used by the ComponentContainer before rendering GUI components
	**/
	void beginRenderUI();

	/**
	* @brief
	* 	Tell the rendering system we are finished drawing GUI components
	**/
	void endRenderUI();

	/**
	* @brief
	*	Convinience function to draw a 2D image
	**/
	void drawImage(oglx_texture_t &img, float x, float y, float width, float height, const Ego::Colour4f& tint = Ego::Colour4f::WHITE);

private:
	Font *_defaultFont;
	int _renderSemaphore;
};

