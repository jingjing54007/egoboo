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

/* Egoboo - cap_file.h
 * routines for reading and writing the character profile file data.txt
 */

#include "egoboo_typedef.h"

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
#define MAXCAPNAMESIZE      32                      // Character class names

//Levels
#define MAXBASELEVEL            6                 // Basic Levels 0-5
#define MAXLEVEL               20                 // Absolute max level

enum e_idsz_type
{
    IDSZ_PARENT = 0,                             // Parent index
    IDSZ_TYPE,                                   // Self index
    IDSZ_SKILL,                                  // Skill index
    IDSZ_SPECIAL,                                // Special index
    IDSZ_HATE,                                   // Hate index
    IDSZ_VULNERABILITY,                          // Vulnerability index
    IDSZ_COUNT                                   // ID strings per character
};

enum e_damage_type
{
    DAMAGE_SLASH = 0,
    DAMAGE_CRUSH,
    DAMAGE_POKE,
    DAMAGE_HOLY,                             // (Most invert Holy damage )
    DAMAGE_EVIL,
    DAMAGE_FIRE,
    DAMAGE_ICE,
    DAMAGE_ZAP,
    DAMAGE_COUNT,

    DAMAGE_NONE      = 255
};

// XP stuff
enum e_xp_type
{
    XP_FINDSECRET = 0,                          // Finding a secret
    XP_WINQUEST,                                // Beating a module or a subquest
    XP_USEDUNKOWN,                              // Used an unknown item
    XP_KILLENEMY,                               // Killed an enemy
    XP_KILLSLEEPY,                              // Killed a sleeping enemy
    XP_KILLHATED,                               // Killed a hated enemy
    XP_TEAMKILL,                                // Team has killed an enemy
    XP_TALKGOOD,                                // Talk good, er...  I mean well
    XP_COUNT,                                   // Number of ways to get experience

    XP_DIRECT     = 255                         // No modification
};

// BB > enumerated "speech" sounds, so that we COULD ge the scripts to classify which
// sound to use for the "ouch", the "too much baggage", etc.
// also some left-over sounds from the RTS days, but they might be useful if an NPC
// uses messages to control his minions.

// for example:
// necromancer sends message to all minions "attack blah"
// zombie minion responds with "moooooaaaaannn" automatically because that is the sound
// registered as his SPEECH_ATTACK sound.
// It seems to have a lot of potential to me. It *could* be done completely in the scripts,
// but the idea of having registered sounds for certain actions makes a lot of sense to me! :)

enum e_sound_types
{
    SOUND_FOOTFALL = 0,
    SOUND_JUMP,
    SOUND_SPAWN,
    SOUND_DEATH,

    // old "RTS" stuff
    SPEECH_MOVE,
    SPEECH_MOVEALT,
    SPEECH_ATTACK,
    SPEECH_ASSIST,
    SPEECH_TERRAIN,
    SPEECH_SELECT,

    SOUND_COUNT,

    SPEECH_BEGIN = SPEECH_MOVE,
    SPEECH_END   = SPEECH_SELECT
};

// Object positions
enum e_slots
{
    SLOT_LEFT  = 0,
    SLOT_RIGHT,
    SLOT_COUNT
};
typedef enum e_slots slot_t;

enum e_inventory
{
    INVEN_PACK = 0,
    INVEN_NECK,
    INVEN_WRIS,
    INVEN_FOOT,
    INVEN_COUNT
};
typedef enum e_inventory inventory_t;

// Geneder stuff
enum e_chr_gender
{
    GENDER_FEMALE = 0,
    GENDER_MALE,
    GENDER_OTHER,
    GENDER_RANDOM,
    GENDER_COUNT
};

#define ULTRABLUDY           2          // This makes any damage draw blud

//Damage shifts
#define DAMAGEMANA          16                      // 000x0000 Deals damage to mana
#define DAMAGECHARGE        8                       // 0000x000 Converts damage to mana
#define DAMAGEINVERT        4                       // 00000x00 Makes damage heal
#define DAMAGESHIFT         3                       // 000000xx Resistance ( 1 is common )

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
struct s_cap_stat
{
    IPair val;
    IPair perlevel;
};
typedef struct s_cap_stat cap_stat_t;

//--------------------------------------------------------------------------------------------
struct s_cap
{
    EGO_PROFILE_STUFF;

    // naming
    char         classname[MAXCAPNAMESIZE];     // Class name

    // skins
    char         skinname[MAX_SKIN][MAXCAPNAMESIZE];   // Skin name
    Uint16       skincost[MAX_SKIN];                   // Store prices
    float        maxaccel[MAX_SKIN];                   // Acceleration for each skin
    Uint8        skindressy;                         // Dressy

    // overrides
    Sint8        skinoverride;                  // -1 or 0-3.. For import
    Uint8        leveloverride;                 // 0 for normal
    int          stateoverride;                 // 0 for normal
    int          contentoverride;               // 0 for normal

    IDSZ         idsz[IDSZ_COUNT];                 // ID strings

    float        strengthdampen;                // Strength damage factor
    Uint8        stoppedby;                     // Collision Mask

    // inventory
    Uint8        ammomax;                       // Ammo stuff
    Uint8        ammo;
    Sint16       money;                         // Money

    // characer stats

    Uint8        gender;                        // Gender

    cap_stat_t   life_stat;                     // Life
    Sint16       lifereturn;
    Uint16       lifeheal;

    cap_stat_t   mana_stat;                     // Mana
    cap_stat_t   manareturn_stat;
    cap_stat_t   manaflow_stat;
    Sint16       manacost;

    cap_stat_t   strength_stat;                 // Strength
    cap_stat_t   wisdom_stat;                   // Wisdom
    cap_stat_t   intelligence_stat;             // Intlligence
    cap_stat_t   dexterity_stat;                // Dexterity

    // physics
    Uint8        weight;                        // Weight
    float        dampen;                        // Bounciness
    float        bumpdampen;                    // Mass

    float        size;                          // Scale of model
    float        sizeperlevel;                  // Scale increases
    Uint32       shadowsize;                    // Shadow size
    Uint32       bumpsize;                      // Bounding octagon
    Uint32       bumpsizebig;                   // For octagonal bumpers
    Uint32       bumpheight;

    // movement
    float        jump;                          // Jump power
    Uint8        jumpnumber;                    // Number of jumps ( Ninja )
    Uint8        sneakspd;                      // Sneak threshold
    Uint8        walkspd;                       // Walk threshold
    Uint8        runspd;                        // Run threshold
    Uint8        flyheight;                     // Fly height

    // graphics
    Uint8        flashand;                      // Flashing rate
    Uint8        alpha;                         // Transparency
    Uint8        light;                         // Light blending
    bool_t       transferblend;                 // Transfer blending to rider/weapons
    bool_t       sheen;                         // How shiny it is ( 0-15 )
    bool_t       enviro;                        // Phong map this baby?
    Uint16       uoffvel;                       // Texture movement rates
    Uint16       voffvel;
    bool_t       uniformlit;                    // Bad lighting?
    Uint8        lifecolor;                     // Bar colors
    Uint8        manacolor;

    // random stuff
    bool_t       stickybutt;                    // Stick to the ground?

    Uint16       iframefacing;                  // Invincibility frame
    Uint16       iframeangle;
    Uint16       nframefacing;                  // Normal frame
    Uint16       nframeangle;

    // defense
    Uint8        resistbumpspawn;               // Don't catch fire
    Uint8        defense[MAX_SKIN];                    // Defense for each skin
    Uint8        damagemodifier[DAMAGE_COUNT][MAX_SKIN];

    // xp
    Uint32       experienceforlevel[MAXLEVEL];  // Experience needed for next level
    IPair        experience;                // Starting experience
    Uint16       experienceworth;               // Amount given to killer/user
    float        experienceexchange;            // Adds to worth
    float        experiencerate[XP_COUNT];

    // sound
    Sint8        soundindex[SOUND_COUNT];       // a map for soundX.wav to sound types

    // flags
    bool_t       is_spelleffect;                // is the object that a spellbook generates
    bool_t       isitem;                        // Is it an item?
    bool_t       invictus;                      // Is it invincible?
    bool_t       ismount;                       // Can you ride it?
    bool_t       isstackable;                   // Is it arrowlike?
    bool_t       nameknown;                     // Is the class name known?
    bool_t       usageknown;                    // Is its usage known
    bool_t       cancarrytonextmodule;          // Take it with you?
    bool_t       needskillidtouse;              // Check IDSZ first?
    bool_t       waterwalk;                     // Walk on water?
    bool_t       platform;                      // Can be stood on?
    bool_t       canuseplatforms;               // Can use platforms?
    bool_t       cangrabmoney;                  // Collect money?
    bool_t       canopenstuff;                  // Open chests/doors?
    bool_t       icon;                          // Draw icon
    bool_t       forceshadow;                   // Draw a shadow?
    bool_t       ripple;                        // Spawn ripples?
    Uint8        damagetargettype;              // For AI DamageTarget
    Uint8        weaponaction;                  // Animation needed to swing
    bool_t       slotvalid[SLOT_COUNT];            // Left/Right hands valid
    Uint8        attackattached;
    Sint8        attackprttype;
    Uint8        attachedprt_amount;             // Sticky particles
    Uint8        attachedprt_reaffirmdamagetype; // Relight that torch...
    Uint16       attachedprt_pip;
    Uint8        gopoofprtamount;               // Poof effect
    Sint16       gopoofprtfacingadd;
    Uint16       gopoofprttype;
    Uint8        bludvalid;                    // Blud ( yuck )
    Uint8        bludprttype;
    bool_t       ridercanattack;                // Rider attack?
    bool_t       canbedazed;                    // Can it be dazed?
    bool_t       canbegrogged;                  // Can it be grogged?
    Uint8        kursechance;                   // Chance of being kursed
    bool_t       istoobig;                      // Can't be put in pack
    bool_t       reflect;                       // Draw the reflection
    bool_t       alwaysdraw;                    // Always render
    bool_t       isranged;                      // Flag for ranged weapon
    Sint8        hidestate;                       // Don't draw when...
    bool_t       isequipment;                     // Behave in silly ways
    Sint8        isvaluable;                      // Force to be valuable
    Uint16       spawnlife;                      // Life left from last module
    Uint16       spawnmana;                      // Life left from last module

    // skill system
    Sint8        shieldproficiency;               // Can it use shields?
    bool_t       canjoust;                        // Can it use advanced weapons?
    bool_t       canuseadvancedweapons;           // Can it use advanced weapons?
    bool_t       canseeinvisible;                 // Can it see invisible?
    bool_t       canseekurse;                     // Can it see kurses?
    bool_t       canusedivine;
    bool_t       canusearcane;
    bool_t       canusetech;
    bool_t       candisarm;
    bool_t       canbackstab;
    bool_t       canusepoison;
    bool_t       canread;
};

typedef struct s_cap cap_t;

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
cap_t * load_one_cap_file( const char * tmploadname, cap_t * pcap );
//bool_t save_one_cap_file( const char * tmploadname, cap_t * pcap );