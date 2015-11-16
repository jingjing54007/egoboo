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

/// @file game/GUI/CharacterStatus.hpp
/// @author Johan Jansen

#include "CharacterStatus.hpp"
#include "game/Entities/_Include.hpp"
#include "game/renderer_2d.h"
#include "game/player.h"
#include "game/GUI/ProgressBar.hpp"
#include "game/game.h" //for update_wld

CharacterStatus::CharacterStatus(const std::shared_ptr<Object> &object) :
    _object(object),
    _chargeBar(std::make_shared<GUI::ProgressBar>())
{
    //ctor
}



void CharacterStatus::draw_one_character_icon(const CHR_REF item, float x, float y, bool draw_ammo, Uint8 draw_sparkle)
{
	/// @author BB
	/// @details Draw an icon for the given item at the position <x,y>.
	///     If the object is invalid, draw the null icon instead of failing
	///     If NOSPARKLE is specified the default item sparkle will be used (default behaviour)

	Object * pitem = !_currentModule->getObjectHandler().exists(item) ? NULL : _currentModule->getObjectHandler().get(item);

	// grab the icon reference
	const oglx_texture_t* icon_ref = chr_get_txtexture_icon_ref(item);

	// draw the icon
	if (draw_sparkle == NOSPARKLE) draw_sparkle = (NULL == pitem) ? NOSPARKLE : pitem->sparkle;
	draw_game_icon(icon_ref, x, y, draw_sparkle, update_wld, -1);

	// draw the ammo, if requested
	if (draw_ammo && (NULL != pitem))
	{
		if (0 != pitem->ammomax && pitem->ammoknown)
		{
			if ((!pitem->getProfile()->isStackable()) || pitem->ammo > 1)
			{
				// Show amount of ammo left
				draw_string_raw(x, y - 8, "%2d", pitem->ammo);
			}
		}
	}
}

float CharacterStatus::draw_one_bar(Uint8 bartype, float x_stt, float y_stt, int ticks, int maxticks)
{
	/// @author ZZ
	/// @details This function draws a bar and returns the y position for the next one

	const float scale = 1.0f;

	float       width, height;
	ego_frect_t tx_rect, sc_rect;

	float tx_width, tx_height, img_width;
	float tab_width, tick_width, tick_height;

	int total_ticks = maxticks;
	int tmp_bartype = bartype;

	float x_left = x_stt;
	float x = x_stt;
	float y = y_stt;

	if (maxticks <= 0 || ticks < 0 || bartype > NUMBAR) return y;

	// limit the values to reasonable ones
	if (total_ticks > MAXTICK) total_ticks = MAXTICK;
	if (ticks > total_ticks) ticks = total_ticks;

	// grab a pointer to the bar texture
	const std::shared_ptr<oglx_texture_t> &tx_ptr = TextureManager::get().getTexture("mp_data/bars");

	// allow the bitmap to be scaled to arbitrary size
	tx_width = 128.0f;
	tx_height = 128.0f;
	img_width = 112.0f;
	if (NULL != tx_ptr)
	{
		tx_width = tx_ptr->getWidth();
		tx_height = tx_ptr->getHeight();
		img_width = tx_ptr->getSourceWidth();
	}

	// calculate the bar parameters
	tick_width = img_width / 14.0f;
	tick_height = img_width / 7.0f;
	tab_width = img_width / 3.5f;

	//---- Draw the tab
	tmp_bartype = bartype;

	tx_rect.xmin = 0.0f / tx_width;
	tx_rect.xmax = tab_width / tx_width;
	tx_rect.ymin = tick_height * (tmp_bartype + 0) / tx_height;
	tx_rect.ymax = tick_height * (tmp_bartype + 1) / tx_height;

	width = (tx_rect.xmax - tx_rect.xmin) * scale * tx_width;
	height = (tx_rect.ymax - tx_rect.ymin) * scale * tx_height;

	sc_rect.xmin = x;
	sc_rect.xmax = x + width;
	sc_rect.ymin = y;
	sc_rect.ymax = y + height;

	draw_quad_2d(tx_ptr.get(), sc_rect, tx_rect, true);

	// make the new left-hand margin after the tab
	x_left = x_stt + width;
	x = x_left;

	//---- Draw the full rows of ticks
	while (ticks >= NUMTICK)
	{
		tmp_bartype = bartype;

		tx_rect.xmin = tab_width / tx_width;
		tx_rect.xmax = img_width / tx_width;
		tx_rect.ymin = tick_height * (tmp_bartype + 0) / tx_height;
		tx_rect.ymax = tick_height * (tmp_bartype + 1) / tx_height;

		width = (tx_rect.xmax - tx_rect.xmin) * scale * tx_width;
		height = (tx_rect.ymax - tx_rect.ymin) * scale * tx_height;

		sc_rect.xmin = x;
		sc_rect.xmax = x + width;
		sc_rect.ymin = y;
		sc_rect.ymax = y + height;

		draw_quad_2d(tx_ptr.get(), sc_rect, tx_rect, true);

		y += height;
		ticks -= NUMTICK;
		total_ticks -= NUMTICK;
	}

	if (ticks > 0)
	{
		int full_ticks = NUMTICK - ticks;
		int empty_ticks = NUMTICK - (std::min(NUMTICK, total_ticks) - ticks);

		//---- draw a partial row of full ticks
		tx_rect.xmin = tab_width / tx_width;
		tx_rect.xmax = (img_width - tick_width * full_ticks) / tx_width;
		tx_rect.ymin = tick_height * (tmp_bartype + 0) / tx_height;
		tx_rect.ymax = tick_height * (tmp_bartype + 1) / tx_height;

		width = (tx_rect.xmax - tx_rect.xmin) * scale * tx_width;
		height = (tx_rect.ymax - tx_rect.ymin) * scale * tx_height;

		sc_rect.xmin = x;
		sc_rect.xmax = x + width;
		sc_rect.ymin = y;
		sc_rect.ymax = y + height;

		draw_quad_2d(tx_ptr.get(), sc_rect, tx_rect, true);

		// move to the right after drawing the full ticks
		x += width;

		//---- draw a partial row of empty ticks
		tmp_bartype = 0;

		tx_rect.xmin = tab_width / tx_width;
		tx_rect.xmax = (img_width - tick_width * empty_ticks) / tx_width;
		tx_rect.ymin = tick_height * (tmp_bartype + 0) / tx_height;
		tx_rect.ymax = tick_height * (tmp_bartype + 1) / tx_height;

		width = (tx_rect.xmax - tx_rect.xmin) * scale * tx_width;
		height = (tx_rect.ymax - tx_rect.ymin) * scale * tx_height;

		sc_rect.xmin = x;
		sc_rect.xmax = x + width;
		sc_rect.ymin = y;
		sc_rect.ymax = y + height;

		draw_quad_2d(tx_ptr.get(), sc_rect, tx_rect, true);

		y += height;
		ticks = 0;
		total_ticks -= NUMTICK;
	}

	// reset the x position
	x = x_left;

	// Draw full rows of empty ticks
	while (total_ticks >= NUMTICK)
	{
		tmp_bartype = 0;

		tx_rect.xmin = tab_width / tx_width;
		tx_rect.xmax = img_width / tx_width;
		tx_rect.ymin = tick_height * (tmp_bartype + 0) / tx_height;
		tx_rect.ymax = tick_height * (tmp_bartype + 1) / tx_height;

		width = (tx_rect.xmax - tx_rect.xmin) * scale * tx_width;
		height = (tx_rect.ymax - tx_rect.ymin) * scale * tx_height;

		sc_rect.xmin = x;
		sc_rect.xmax = x + width;
		sc_rect.ymin = y;
		sc_rect.ymax = y + height;

		draw_quad_2d(tx_ptr.get(), sc_rect, tx_rect, true);

		y += height;
		total_ticks -= NUMTICK;
	}

	// Draw the last of the empty ones
	if (total_ticks > 0)
	{
		int remaining = NUMTICK - total_ticks;

		//---- draw a partial row of empty ticks
		tmp_bartype = 0;

		tx_rect.xmin = tab_width / tx_width;
		tx_rect.xmax = (img_width - tick_width * remaining) / tx_width;
		tx_rect.ymin = tick_height * (tmp_bartype + 0) / tx_height;
		tx_rect.ymax = tick_height * (tmp_bartype + 1) / tx_height;

		width = (tx_rect.xmax - tx_rect.xmin) * scale * tx_width;
		height = (tx_rect.ymax - tx_rect.ymin) * scale * tx_height;

		sc_rect.xmin = x;
		sc_rect.xmax = x + width;
		sc_rect.ymin = y;
		sc_rect.ymax = y + height;

		draw_quad_2d(tx_ptr.get(), sc_rect, tx_rect, true);

		y += height;
	}

	return y;
}

float CharacterStatus::draw_one_xp_bar(float x, float y, Uint8 ticks)
{
	/// @author ZF
	/// @details This function draws a xp bar and returns the y position for the next one

	const std::shared_ptr<oglx_texture_t> &texture = TextureManager::get().getTexture("mp_data/xpbar");

	int width, height;
	Uint8 cnt;
	ego_frect_t tx_rect, sc_rect;

	ticks = std::min(ticks, (Uint8)NUMTICK);

	Ego::Renderer::get().setColour(Ego::Math::Colour4f::white());

	//---- Draw the tab (always colored)

	width = 16;
	height = XPTICK;

	tx_rect.xmin = 0;
	tx_rect.xmax = 32.00f / 128;
	tx_rect.ymin = XPTICK / 16;
	tx_rect.ymax = XPTICK * 2 / 16;

	sc_rect.xmin = x;
	sc_rect.xmax = x + width;
	sc_rect.ymin = y;
	sc_rect.ymax = y + height;

	draw_quad_2d(texture.get(), sc_rect, tx_rect, true);

	x += width;

	//---- Draw the filled ones
	tx_rect.xmin = 0.0f;
	tx_rect.xmax = 32 / 128.0f;
	tx_rect.ymin = XPTICK / 16.0f;
	tx_rect.ymax = 2 * XPTICK / 16.0f;

	width = XPTICK;
	height = XPTICK;

	for (cnt = 0; cnt < ticks; cnt++)
	{
		sc_rect.xmin = x + (cnt * width);
		sc_rect.xmax = x + (cnt * width) + width;
		sc_rect.ymin = y;
		sc_rect.ymax = y + height;

		draw_quad_2d(texture.get(), sc_rect, tx_rect, true);
	}

	//---- Draw the remaining empty ones
	tx_rect.xmin = 0;
	tx_rect.xmax = 32 / 128.0f;
	tx_rect.ymin = 0;
	tx_rect.ymax = XPTICK / 16.0f;

	for ( /*nothing*/; cnt < NUMTICK; cnt++)
	{
		sc_rect.xmin = x + (cnt * width);
		sc_rect.xmax = x + (cnt * width) + width;
		sc_rect.ymin = y;
		sc_rect.ymax = y + height;

		draw_quad_2d(texture.get(), sc_rect, tx_rect, true);
	}

	return y + height;
}

float CharacterStatus::draw_character_xp_bar(const CHR_REF character, float x, float y)
{
	Object * pchr;

	if (!_currentModule->getObjectHandler().exists(character)) return y;
	pchr = _currentModule->getObjectHandler().get(character);

	//Draw the small XP progress bar
	if (pchr->experiencelevel < MAXLEVEL - 1)
	{
		uint8_t  curlevel = pchr->experiencelevel + 1;
		uint32_t xplastlevel = pchr->getProfile()->getXPNeededForLevel(curlevel - 1);
		uint32_t xpneed = pchr->getProfile()->getXPNeededForLevel(curlevel);

		while (pchr->experience < xplastlevel && curlevel > 1) {
			curlevel--;
			xplastlevel = pchr->getProfile()->getXPNeededForLevel(curlevel - 1);
		}

		float fraction = ((float)(pchr->experience - xplastlevel)) / (float)std::max<uint32_t>(xpneed - xplastlevel, 1);
		int   numticks = fraction * NUMTICK;

		y = draw_one_xp_bar(x, y, CLIP(numticks, 0, NUMTICK));
	}

	return y;
}


void CharacterStatus::draw()
{
    //If object we are monitoring no longer exist, then destroy this GUI component
    const std::shared_ptr<Object> pchr = _object.lock();
    if(!pchr) {
        destroy();
        return;
    }

    int life_pips = pchr->getLife();
    int life_pips_max = pchr->getAttribute(Ego::Attribute::MAX_LIFE);
    int mana_pips = pchr->getMana();
    int mana_pips_max = pchr->getAttribute(Ego::Attribute::MAX_MANA);
    int yOffset = getY();

    // draw the name
    yOffset = draw_string_raw(getX() + 8, yOffset, "%s", pchr->getName(false, false, true).c_str());

    // draw the character's money
    yOffset = draw_string_raw(getX() + 8, yOffset, "$%4d", pchr->getMoney()) + 8;

    bool levelUp = false;
    if(pchr->isPlayer()) {
        levelUp = PlaStack.get_ptr(pchr->is_which_player)->_unspentLevelUp;
    }

    // draw the character's main icon
    draw_one_character_icon(pchr->getObjRef().get(), getX() + 40, yOffset, false, levelUp ? COLOR_YELLOW : NOSPARKLE);

    // draw the left hand item icon
    draw_one_character_icon(pchr->holdingwhich[SLOT_LEFT].get(), getX() + 8, yOffset, true, NOSPARKLE);

    // draw the right hand item icon
    draw_one_character_icon(pchr->holdingwhich[SLOT_RIGHT].get(), getX() + 72, yOffset, true, NOSPARKLE);

    // skip to the next row
    yOffset += 32;

    //Draw the small XP progress bar
    yOffset = draw_character_xp_bar(pchr->getObjRef().get(), getX() + 16, yOffset);

    // Draw the life bar
    if (pchr->isAlive())
    {
        yOffset = draw_one_bar(pchr->getAttribute(Ego::Attribute::LIFE_BARCOLOR), getX(), yOffset, life_pips, life_pips_max);
    }
    else
    {
        // Draw a black bar
        yOffset = draw_one_bar(0, getX(), yOffset, 0, life_pips_max);
    }

    // Draw the mana bar
    if (mana_pips_max > 0)
    {
        yOffset = draw_one_bar(pchr->getAttribute(Ego::Attribute::MANA_BARCOLOR), getX(), yOffset, mana_pips, mana_pips_max);
    }

    //After rendering we know how high this GUI component actually is
    setHeight(yOffset - getY());

    //Finally draw charge bar if applicable
    if(pchr->isPlayer()) {
        const player_t *ppla = PlaStack.get_ptr(pchr->is_which_player);
        if(ppla->_chargeBarFrame >= update_wld) {
            _chargeBar->setVisible(true);
            _chargeBar->setMaxValue(ppla->_maxCharge);
            _chargeBar->setValue(ppla->_currentCharge);
            _chargeBar->setTickWidth(ppla->_chargeTick);
            _chargeBar->setSize(getWidth(), 16);
            _chargeBar->setPosition(getX() - _chargeBar->getWidth() - 5, getY() + getHeight() / 2 - _chargeBar->getHeight()/2);
            _chargeBar->draw();
        }
        else {
            _chargeBar->setVisible(false);
        }
    }
}
