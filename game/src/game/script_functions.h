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

/// @file game/script_functions.h
/// @details functions called by scr_run_function()

#pragma once

#include "game/egoboo.h"

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------

struct script_state_t;
struct ai_state_t;
class Object;

//--------------------------------------------------------------------------------------------
// helper functions
//--------------------------------------------------------------------------------------------

uint8_t scr_SetAlertBit( script_state_t& state, ai_state_t& self );
uint8_t scr_ClearAlertBit( script_state_t& state, ai_state_t& self );
uint8_t scr_TestAlertBit( script_state_t& state, ai_state_t& self );
uint8_t scr_SetAlert( script_state_t& state, ai_state_t& self );
uint8_t scr_ClearAlert( script_state_t& state, ai_state_t& self );
uint8_t scr_TestAlert( script_state_t& state, ai_state_t& self );
uint8_t scr_SetBit( script_state_t& state, ai_state_t& self );
uint8_t scr_ClearBit( script_state_t& state, ai_state_t& self );
uint8_t scr_TestBit( script_state_t& state, ai_state_t& self );
uint8_t scr_SetBits( script_state_t& state, ai_state_t& self );
uint8_t scr_ClearBits( script_state_t& state, ai_state_t& self );
uint8_t scr_TestBits( script_state_t& state, ai_state_t& self );
uint8_t scr_IfSpawned( script_state_t& state, ai_state_t& self );
uint8_t scr_IfTimeOut( script_state_t& state, ai_state_t& self );
uint8_t scr_IfAtWaypoint( script_state_t& state, ai_state_t& self );
uint8_t scr_IfAtLastWaypoint( script_state_t& state, ai_state_t& self );
uint8_t scr_IfAttacked( script_state_t& state, ai_state_t& self );
uint8_t scr_IfBumped( script_state_t& state, ai_state_t& self );
uint8_t scr_IfOrdered( script_state_t& state, ai_state_t& self );
uint8_t scr_IfCalledForHelp( script_state_t& state, ai_state_t& self );
uint8_t scr_SetContent( script_state_t& state, ai_state_t& self );
uint8_t scr_IfKilled( script_state_t& state, ai_state_t& self );
uint8_t scr_IfTargetKilled( script_state_t& state, ai_state_t& self );
uint8_t scr_ClearWaypoints( script_state_t& state, ai_state_t& self );
uint8_t scr_AddWaypoint( script_state_t& state, ai_state_t& self );
uint8_t scr_FindPath( script_state_t& state, ai_state_t& self );
uint8_t scr_Compass( script_state_t& state, ai_state_t& self );
uint8_t scr_GetTargetArmorPrice( script_state_t& state, ai_state_t& self );
uint8_t scr_SetTime( script_state_t& state, ai_state_t& self );
uint8_t scr_GetContent( script_state_t& state, ai_state_t& self );
uint8_t scr_JoinTargetTeam( script_state_t& state, ai_state_t& self );
uint8_t scr_SetTargetToNearbyEnemy( script_state_t& state, ai_state_t& self );
uint8_t scr_SetTargetToTargetLeftHand( script_state_t& state, ai_state_t& self );
uint8_t scr_SetTargetToTargetRightHand( script_state_t& state, ai_state_t& self );
uint8_t scr_SetTargetToWhoeverAttacked( script_state_t& state, ai_state_t& self );
uint8_t scr_SetTargetToWhoeverBumped( script_state_t& state, ai_state_t& self );
uint8_t scr_SetTargetToWhoeverCalledForHelp( script_state_t& state, ai_state_t& self );
uint8_t scr_SetTargetToOldTarget( script_state_t& state, ai_state_t& self );
uint8_t scr_SetTurnModeToVelocity( script_state_t& state, ai_state_t& self );
uint8_t scr_SetTurnModeToWatch( script_state_t& state, ai_state_t& self );
uint8_t scr_SetTurnModeToSpin( script_state_t& state, ai_state_t& self );
uint8_t scr_SetBumpHeight( script_state_t& state, ai_state_t& self );
uint8_t scr_IfTargetHasID( script_state_t& state, ai_state_t& self );
uint8_t scr_IfTargetHasItemID( script_state_t& state, ai_state_t& self );
uint8_t scr_IfTargetHoldingItemID( script_state_t& state, ai_state_t& self );
uint8_t scr_IfTargetHasSkillID( script_state_t& state, ai_state_t& self );
uint8_t scr_Else( script_state_t& state, ai_state_t& self );
uint8_t scr_Run( script_state_t& state, ai_state_t& self );
uint8_t scr_Walk( script_state_t& state, ai_state_t& self );
uint8_t scr_Sneak( script_state_t& state, ai_state_t& self );
uint8_t scr_DoAction( script_state_t& state, ai_state_t& self );
uint8_t scr_KeepAction( script_state_t& state, ai_state_t& self );
uint8_t scr_IssueOrder( script_state_t& state, ai_state_t& self );
uint8_t scr_DropWeapons( script_state_t& state, ai_state_t& self );
uint8_t scr_TargetDoAction( script_state_t& state, ai_state_t& self );
uint8_t scr_OpenPassage( script_state_t&  state, ai_state_t& self );
uint8_t scr_ClosePassage( script_state_t& state, ai_state_t& self );
uint8_t scr_IfPassageOpen( script_state_t& state, ai_state_t& self );
uint8_t scr_GoPoof( script_state_t& state, ai_state_t& self );
uint8_t scr_CostTargetItemID( script_state_t& state, ai_state_t& self );
uint8_t scr_DoActionOverride( script_state_t& state, ai_state_t& self );
uint8_t scr_IfHealed( script_state_t& state, ai_state_t& self );
uint8_t scr_SendMessage( script_state_t& state, ai_state_t& self );
uint8_t scr_CallForHelp( script_state_t& state, ai_state_t& self );
uint8_t scr_AddIDSZ( script_state_t& state, ai_state_t& self );
uint8_t scr_SetState( script_state_t& state, ai_state_t& self );
uint8_t scr_GetState( script_state_t& state, ai_state_t& self );
uint8_t scr_IfStateIs( script_state_t& state, ai_state_t& self );
uint8_t scr_IfTargetCanOpenStuff( script_state_t& state, ai_state_t& self );
uint8_t scr_IfGrabbed( script_state_t& state, ai_state_t& self );
uint8_t scr_IfDropped( script_state_t& state, ai_state_t& self );
uint8_t scr_SetTargetToWhoeverIsHolding( script_state_t& state, ai_state_t& self );
uint8_t scr_DamageTarget( script_state_t& state, ai_state_t& self );
uint8_t scr_IfXIsLessThanY( script_state_t& state, ai_state_t& self );
uint8_t scr_SetWeatherTime( script_state_t& state, ai_state_t& self );
uint8_t scr_GetBumpHeight( script_state_t& state, ai_state_t& self );
uint8_t scr_IfReaffirmed( script_state_t& state, ai_state_t& self );
uint8_t scr_UnkeepAction( script_state_t& state, ai_state_t& self );
uint8_t scr_IfTargetIsOnOtherTeam( script_state_t& state, ai_state_t& self );
uint8_t scr_IfTargetIsOnHatedTeam( script_state_t& state, ai_state_t& self );
uint8_t scr_PressLatchButton( script_state_t& state, ai_state_t& self );
uint8_t scr_SetTargetToTargetOfLeader( script_state_t& state, ai_state_t& self );
uint8_t scr_IfLeaderKilled( script_state_t& state, ai_state_t& self );
uint8_t scr_BecomeLeader( script_state_t& state, ai_state_t& self );
uint8_t scr_ChangeTargetArmor( script_state_t& state, ai_state_t& self );
uint8_t scr_GiveMoneyToTarget( script_state_t& state, ai_state_t& self );
uint8_t scr_DropKeys( script_state_t& state, ai_state_t& self );
uint8_t scr_IfLeaderIsAlive( script_state_t& state, ai_state_t& self );
uint8_t scr_IfTargetIsOldTarget( script_state_t& state, ai_state_t& self );
uint8_t scr_SetTargetToLeader( script_state_t& state, ai_state_t& self );
uint8_t scr_SpawnCharacter( script_state_t& state, ai_state_t& self );
uint8_t scr_RespawnCharacter( script_state_t& state, ai_state_t& self );
uint8_t scr_ChangeTile( script_state_t& state, ai_state_t& self );
uint8_t scr_IfUsed( script_state_t& state, ai_state_t& self );
uint8_t scr_DropMoney( script_state_t& state, ai_state_t& self );
uint8_t scr_SetOldTarget( script_state_t& state, ai_state_t& self );
uint8_t scr_DetachFromHolder( script_state_t& state, ai_state_t& self );
uint8_t scr_IfTargetHasVulnerabilityID( script_state_t& state, ai_state_t& self );
uint8_t scr_CleanUp( script_state_t& state, ai_state_t& self );
uint8_t scr_IfCleanedUp( script_state_t& state, ai_state_t& self );
uint8_t scr_IfSitting( script_state_t& state, ai_state_t& self );
uint8_t scr_IfTargetIsHurt( script_state_t& state, ai_state_t& self );
uint8_t scr_IfTargetIsAPlayer( script_state_t& state, ai_state_t& self );
uint8_t scr_PlaySound( script_state_t& state, ai_state_t& self );
uint8_t scr_SpawnParticle( script_state_t& state, ai_state_t& self );
uint8_t scr_IfTargetIsAlive( script_state_t& state, ai_state_t& self );
uint8_t scr_Stop( script_state_t& state, ai_state_t& self );
uint8_t scr_DisaffirmCharacter( script_state_t& state, ai_state_t& self );
uint8_t scr_ReaffirmCharacter( script_state_t& state, ai_state_t& self );
uint8_t scr_IfTargetIsSelf( script_state_t& state, ai_state_t& self );
uint8_t scr_IfTargetIsMale( script_state_t& state, ai_state_t& self );
uint8_t scr_IfTargetIsFemale( script_state_t& state, ai_state_t& self );
uint8_t scr_SetTargetToSelf( script_state_t& state, ai_state_t& self );
uint8_t scr_SetTargetToRider( script_state_t& state, ai_state_t& self );
uint8_t scr_GetAttackTurn( script_state_t& state, ai_state_t& self );
uint8_t scr_GetDamageType( script_state_t& state, ai_state_t& self );
uint8_t scr_BecomeSpell( script_state_t& state, ai_state_t& self );
uint8_t scr_BecomeSpellbook( script_state_t& state, ai_state_t& self );
uint8_t scr_IfScoredAHit( script_state_t& state, ai_state_t& self );
uint8_t scr_IfDisaffirmed( script_state_t& state, ai_state_t& self );
uint8_t scr_TranslateOrder( script_state_t& state, ai_state_t& self );
uint8_t scr_SetTargetToWhoeverWasHit( script_state_t& state, ai_state_t& self );
uint8_t scr_SetTargetToWideEnemy( script_state_t& state, ai_state_t& self );
uint8_t scr_IfChanged( script_state_t& state, ai_state_t& self );
uint8_t scr_IfInWater( script_state_t& state, ai_state_t& self );
uint8_t scr_IfBored( script_state_t& state, ai_state_t& self );
uint8_t scr_IfTooMuchBaggage( script_state_t& state, ai_state_t& self );
uint8_t scr_IfGrogged( script_state_t& state, ai_state_t& self );
uint8_t scr_IfDazed( script_state_t& state, ai_state_t& self );
uint8_t scr_IfTargetHasSpecialID( script_state_t& state, ai_state_t& self );
uint8_t scr_PressTargetLatchButton( script_state_t& state, ai_state_t& self );
uint8_t scr_IfInvisible( script_state_t& state, ai_state_t& self );
uint8_t scr_IfArmorIs( script_state_t& state, ai_state_t& self );
uint8_t scr_GetTargetGrogTime( script_state_t& state, ai_state_t& self );
uint8_t scr_GetTargetDazeTime( script_state_t& state, ai_state_t& self );
uint8_t scr_SetDamageType( script_state_t& state, ai_state_t& self );
uint8_t scr_SetWaterLevel( script_state_t& state, ai_state_t& self );
uint8_t scr_EnchantTarget( script_state_t& state, ai_state_t& self );
uint8_t scr_EnchantChild( script_state_t& state, ai_state_t& self );
uint8_t scr_TeleportTarget( script_state_t& state, ai_state_t& self );
uint8_t scr_GiveExperienceToTarget( script_state_t& state, ai_state_t& self );
uint8_t scr_IncreaseAmmo( script_state_t& state, ai_state_t& self );
uint8_t scr_UnkurseTarget( script_state_t& state, ai_state_t& self );
uint8_t scr_GiveExperienceToTargetTeam( script_state_t& state, ai_state_t& self );
uint8_t scr_IfUnarmed( script_state_t& state, ai_state_t& self );
uint8_t scr_RestockTargetAmmoIDAll( script_state_t& state, ai_state_t& self );
uint8_t scr_RestockTargetAmmoIDFirst( script_state_t& state, ai_state_t& self );
uint8_t scr_FlashTarget( script_state_t& state, ai_state_t& self );
uint8_t scr_SetRedShift( script_state_t& state, ai_state_t& self );
uint8_t scr_SetGreenShift( script_state_t& state, ai_state_t& self );
uint8_t scr_SetBlueShift( script_state_t& state, ai_state_t& self );
uint8_t scr_SetLight( script_state_t& state, ai_state_t& self );
uint8_t scr_SetAlpha( script_state_t& state, ai_state_t& self );
uint8_t scr_IfHitFromBehind( script_state_t& state, ai_state_t& self );
uint8_t scr_IfHitFromFront( script_state_t& state, ai_state_t& self );
uint8_t scr_IfHitFromLeft( script_state_t& state, ai_state_t& self );
uint8_t scr_IfHitFromRight( script_state_t& state, ai_state_t& self );
uint8_t scr_IfTargetIsOnSameTeam( script_state_t& state, ai_state_t& self );
uint8_t scr_KillTarget( script_state_t& state, ai_state_t& self );
uint8_t scr_UndoEnchant( script_state_t& state, ai_state_t& self );
uint8_t scr_GetWaterLevel( script_state_t& state, ai_state_t& self );
uint8_t scr_CostTargetMana( script_state_t& state, ai_state_t& self );
uint8_t scr_IfTargetHasAnyID( script_state_t& state, ai_state_t& self );
uint8_t scr_SetBumpSize( script_state_t& state, ai_state_t& self );
uint8_t scr_IfNotDropped( script_state_t& state, ai_state_t& self );
uint8_t scr_IfYIsLessThanX( script_state_t& state, ai_state_t& self );
uint8_t scr_SetFlyHeight( script_state_t& state, ai_state_t& self );
uint8_t scr_IfBlocked( script_state_t& state, ai_state_t& self );
uint8_t scr_IfTargetIsDefending( script_state_t& state, ai_state_t& self );
uint8_t scr_IfTargetIsAttacking( script_state_t& state, ai_state_t& self );
uint8_t scr_IfStateIs0( script_state_t& state, ai_state_t& self );
uint8_t scr_IfStateIs1( script_state_t& state, ai_state_t& self );
uint8_t scr_IfStateIs2( script_state_t& state, ai_state_t& self );
uint8_t scr_IfStateIs3( script_state_t& state, ai_state_t& self );
uint8_t scr_IfStateIs4( script_state_t& state, ai_state_t& self );
uint8_t scr_IfStateIs5( script_state_t& state, ai_state_t& self );
uint8_t scr_IfStateIs6( script_state_t& state, ai_state_t& self );
uint8_t scr_IfStateIs7( script_state_t& state, ai_state_t& self );
uint8_t scr_IfContentIs( script_state_t& state, ai_state_t& self );
uint8_t scr_SetTurnModeToWatchTarget( script_state_t& state, ai_state_t& self );
uint8_t scr_IfStateIsNot( script_state_t& state, ai_state_t& self );
uint8_t scr_IfXIsEqualToY( script_state_t& state, ai_state_t& self );
uint8_t scr_DebugMessage( script_state_t& state, ai_state_t& self );
uint8_t scr_BlackTarget( script_state_t& state, ai_state_t& self );
uint8_t scr_SendMessageNear( script_state_t& state, ai_state_t& self );
uint8_t scr_IfHitGround( script_state_t& state, ai_state_t& self );
uint8_t scr_IfNameIsKnown( script_state_t& state, ai_state_t& self );
uint8_t scr_IfUsageIsKnown( script_state_t& state, ai_state_t& self );
uint8_t scr_IfHoldingItemID( script_state_t& state, ai_state_t& self );
uint8_t scr_IfHoldingRangedWeapon( script_state_t& state, ai_state_t& self );
uint8_t scr_IfHoldingMeleeWeapon( script_state_t& state, ai_state_t& self );
uint8_t scr_IfHoldingShield( script_state_t& state, ai_state_t& self );
uint8_t scr_IfKursed( script_state_t& state, ai_state_t& self );
uint8_t scr_IfTargetIsKursed( script_state_t& state, ai_state_t& self );
uint8_t scr_IfTargetIsDressedUp( script_state_t& state, ai_state_t& self );
uint8_t scr_IfOverWater( script_state_t& state, ai_state_t& self );
uint8_t scr_IfThrown( script_state_t& state, ai_state_t& self );
uint8_t scr_MakeNameKnown( script_state_t& state, ai_state_t& self );
uint8_t scr_MakeUsageKnown( script_state_t& state, ai_state_t& self );
uint8_t scr_StopTargetMovement( script_state_t& state, ai_state_t& self );
uint8_t scr_SetXY( script_state_t& state, ai_state_t& self );
uint8_t scr_GetXY( script_state_t& state, ai_state_t& self );
uint8_t scr_AddXY( script_state_t& state, ai_state_t& self );
uint8_t scr_MakeAmmoKnown( script_state_t& state, ai_state_t& self );
uint8_t scr_SpawnAttachedParticle( script_state_t& state, ai_state_t& self );
uint8_t scr_SpawnExactParticle( script_state_t& state, ai_state_t& self );
uint8_t scr_AccelerateTarget( script_state_t& state, ai_state_t& self );
uint8_t scr_IfDistanceIsMoreThanTurn( script_state_t& state, ai_state_t& self );
uint8_t scr_IfCrushed( script_state_t& state, ai_state_t& self );
uint8_t scr_MakeCrushValid( script_state_t& state, ai_state_t& self );
uint8_t scr_SetTargetToLowestTarget( script_state_t& state, ai_state_t& self );
uint8_t scr_IfNotPutAway( script_state_t& state, ai_state_t& self );
uint8_t scr_IfTakenOut( script_state_t& state, ai_state_t& self );
uint8_t scr_IfAmmoOut( script_state_t& state, ai_state_t& self );
uint8_t scr_PlaySoundLooped( script_state_t& state, ai_state_t& self );
uint8_t scr_StopSound( script_state_t& state, ai_state_t& self );
uint8_t scr_HealSelf( script_state_t& state, ai_state_t& self );
uint8_t scr_Equip( script_state_t& state, ai_state_t& self );
uint8_t scr_IfTargetHasItemIDEquipped( script_state_t& state, ai_state_t& self );
uint8_t scr_SetOwnerToTarget( script_state_t& state, ai_state_t& self );
uint8_t scr_SetTargetToOwner( script_state_t& state, ai_state_t& self );
uint8_t scr_SetFrame( script_state_t& state, ai_state_t& self );
uint8_t scr_BreakPassage( script_state_t& state, ai_state_t& self );
uint8_t scr_SetReloadTime( script_state_t& state, ai_state_t& self );
uint8_t scr_SetTargetToWideBlahID( script_state_t& state, ai_state_t& self );
uint8_t scr_PoofTarget( script_state_t& state, ai_state_t& self );
uint8_t scr_ChildDoActionOverride( script_state_t& state, ai_state_t& self );
uint8_t scr_SpawnPoof( script_state_t& state, ai_state_t& self );
uint8_t scr_SetSpeedPercent( script_state_t& state, ai_state_t& self );
uint8_t scr_SetChildState( script_state_t& state, ai_state_t& self );
uint8_t scr_SpawnAttachedSizedParticle( script_state_t& state, ai_state_t& self );
uint8_t scr_ChangeArmor( script_state_t& state, ai_state_t& self );
uint8_t scr_ShowTimer( script_state_t& state, ai_state_t& self );
uint8_t scr_IfFacingTarget( script_state_t& state, ai_state_t& self );
uint8_t scr_PlaySoundVolume( script_state_t& state, ai_state_t& self );
uint8_t scr_SpawnAttachedFacedParticle( script_state_t& state, ai_state_t& self );
uint8_t scr_IfStateIsOdd( script_state_t& state, ai_state_t& self );
uint8_t scr_SetTargetToDistantEnemy( script_state_t& state, ai_state_t& self );
uint8_t scr_Teleport( script_state_t& state, ai_state_t& self );
uint8_t scr_GiveStrengthToTarget( script_state_t& state, ai_state_t& self );
uint8_t scr_GiveIntelligenceToTarget( script_state_t& state, ai_state_t& self );
uint8_t scr_GiveDexterityToTarget( script_state_t& state, ai_state_t& self );
uint8_t scr_GiveLifeToTarget( script_state_t& state, ai_state_t& self );
uint8_t scr_GiveManaToTarget( script_state_t& state, ai_state_t& self );
uint8_t scr_ShowMap( script_state_t& state, ai_state_t& self );
uint8_t scr_ShowYouAreHere( script_state_t& state, ai_state_t& self );
uint8_t scr_ShowBlipXY( script_state_t& state, ai_state_t& self );
uint8_t scr_HealTarget( script_state_t& state, ai_state_t& self );
uint8_t scr_PumpTarget( script_state_t& state, ai_state_t& self );
uint8_t scr_CostAmmo( script_state_t& state, ai_state_t& self );
uint8_t scr_MakeSimilarNamesKnown( script_state_t& state, ai_state_t& self );
uint8_t scr_SpawnAttachedHolderParticle( script_state_t& state, ai_state_t& self );
uint8_t scr_SetTargetReloadTime( script_state_t& state, ai_state_t& self );
uint8_t scr_SetFogLevel( script_state_t& state, ai_state_t& self );
uint8_t scr_GetFogLevel( script_state_t& state, ai_state_t& self );
uint8_t scr_SetFogTAD( script_state_t& state, ai_state_t& self );
uint8_t scr_SetFogBottomLevel( script_state_t& state, ai_state_t& self );
uint8_t scr_GetFogBottomLevel( script_state_t& state, ai_state_t& self );
uint8_t scr_CorrectActionForHand( script_state_t& state, ai_state_t& self );
uint8_t scr_IfTargetIsMounted( script_state_t& state, ai_state_t& self );
uint8_t scr_SparkleIcon( script_state_t& state, ai_state_t& self );
uint8_t scr_UnsparkleIcon( script_state_t& state, ai_state_t& self );
uint8_t scr_GetTileXY( script_state_t& state, ai_state_t& self );
uint8_t scr_SetTileXY( script_state_t& state, ai_state_t& self );
uint8_t scr_SetShadowSize( script_state_t& state, ai_state_t& self );
uint8_t scr_OrderTarget( script_state_t& state, ai_state_t& self );
uint8_t scr_SetTargetToWhoeverIsInPassage( script_state_t& state, ai_state_t& self );
uint8_t scr_IfCharacterWasABook( script_state_t& state, ai_state_t& self );
uint8_t scr_SetEnchantBoostValues( script_state_t& state, ai_state_t& self );
uint8_t scr_SpawnCharacterXYZ( script_state_t& state, ai_state_t& self );
uint8_t scr_SpawnExactCharacterXYZ( script_state_t& state, ai_state_t& self );
uint8_t scr_ChangeTargetClass( script_state_t& state, ai_state_t& self );
uint8_t scr_PlayFullSound( script_state_t& state, ai_state_t& self );
uint8_t scr_SpawnExactChaseParticle( script_state_t& state, ai_state_t& self );
uint8_t scr_CreateOrder( script_state_t& state, ai_state_t& self );
uint8_t scr_OrderSpecialID( script_state_t& state, ai_state_t& self );
uint8_t scr_UnkurseTargetInventory( script_state_t& state, ai_state_t& self );
uint8_t scr_IfTargetIsSneaking( script_state_t& state, ai_state_t& self );
uint8_t scr_DropItems( script_state_t& state, ai_state_t& self );
uint8_t scr_RespawnTarget( script_state_t& state, ai_state_t& self );
uint8_t scr_TargetDoActionSetFrame( script_state_t& state, ai_state_t& self );
uint8_t scr_IfTargetCanSeeInvisible( script_state_t& state, ai_state_t& self );
uint8_t scr_SetTargetToNearestBlahID( script_state_t& state, ai_state_t& self );
uint8_t scr_SetTargetToNearestEnemy( script_state_t& state, ai_state_t& self );
uint8_t scr_SetTargetToNearestFriend( script_state_t& state, ai_state_t& self );
uint8_t scr_SetTargetToNearestLifeform( script_state_t& state, ai_state_t& self );
uint8_t scr_FlashPassage( script_state_t& state, ai_state_t& self );
uint8_t scr_FindTileInPassage( script_state_t& state, ai_state_t& self );
uint8_t scr_IfHeldInLeftHand( script_state_t& state, ai_state_t& self );
uint8_t scr_NotAnItem( script_state_t& state, ai_state_t& self );
uint8_t scr_SetChildAmmo( script_state_t& state, ai_state_t& self );
uint8_t scr_IfHitVulnerable( script_state_t& state, ai_state_t& self );
uint8_t scr_IfTargetIsFlying( script_state_t& state, ai_state_t& self );
uint8_t scr_IdentifyTarget( script_state_t& state, ai_state_t& self );
uint8_t scr_BeatModule( script_state_t& state, ai_state_t& self );
uint8_t scr_EndModule( script_state_t& state, ai_state_t& self );
uint8_t scr_DisableExport( script_state_t& state, ai_state_t& self );
uint8_t scr_EnableExport( script_state_t& state, ai_state_t& self );
uint8_t scr_GetTargetState( script_state_t& state, ai_state_t& self );
uint8_t scr_IfEquipped( script_state_t& state, ai_state_t& self );
uint8_t scr_DropTargetMoney( script_state_t& state, ai_state_t& self );
uint8_t scr_GetTargetContent( script_state_t& state, ai_state_t& self );
uint8_t scr_DropTargetKeys( script_state_t& state, ai_state_t& self );
uint8_t scr_JoinTeam( script_state_t& state, ai_state_t& self );
uint8_t scr_TargetJoinTeam( script_state_t& state, ai_state_t& self );
uint8_t scr_ClearMusicPassage( script_state_t& state, ai_state_t& self );
uint8_t scr_ClearEndMessage( script_state_t& state, ai_state_t& self );
uint8_t scr_AddEndMessage( script_state_t& state, ai_state_t& self );
uint8_t scr_PlayMusic( script_state_t& state, ai_state_t& self );
uint8_t scr_SetMusicPassage( script_state_t& state, ai_state_t& self );
uint8_t scr_MakeCrushInvalid( script_state_t& state, ai_state_t& self );
uint8_t scr_StopMusic( script_state_t& state, ai_state_t& self );
uint8_t scr_FlashVariable( script_state_t& state, ai_state_t& self );
uint8_t scr_AccelerateUp( script_state_t& state, ai_state_t& self );
uint8_t scr_FlashVariableHeight( script_state_t& state, ai_state_t& self );
uint8_t scr_SetDamageTime( script_state_t& state, ai_state_t& self );
uint8_t scr_IfStateIs8( script_state_t& state, ai_state_t& self );
uint8_t scr_IfStateIs9( script_state_t& state, ai_state_t& self );
uint8_t scr_IfStateIs10( script_state_t& state, ai_state_t& self );
uint8_t scr_IfStateIs11( script_state_t& state, ai_state_t& self );
uint8_t scr_IfStateIs12( script_state_t& state, ai_state_t& self );
uint8_t scr_IfStateIs13( script_state_t& state, ai_state_t& self );
uint8_t scr_IfStateIs14( script_state_t& state, ai_state_t& self );
uint8_t scr_IfStateIs15( script_state_t& state, ai_state_t& self );
uint8_t scr_IfTargetIsAMount( script_state_t& state, ai_state_t& self );
uint8_t scr_IfTargetIsAPlatform( script_state_t& state, ai_state_t& self );
uint8_t scr_AddStat( script_state_t& state, ai_state_t& self );
uint8_t scr_DisenchantTarget( script_state_t& state, ai_state_t& self );
uint8_t scr_DisenchantAll( script_state_t& state, ai_state_t& self );
uint8_t scr_SetVolumeNearestTeammate( script_state_t& state, ai_state_t& self );
uint8_t scr_AddShopPassage( script_state_t& state, ai_state_t& self );
uint8_t scr_TargetPayForArmor( script_state_t& state, ai_state_t& self );
uint8_t scr_JoinEvilTeam( script_state_t& state, ai_state_t& self );
uint8_t scr_JoinNullTeam( script_state_t& state, ai_state_t& self );
uint8_t scr_JoinGoodTeam( script_state_t& state, ai_state_t& self );
uint8_t scr_PitsKill( script_state_t& state, ai_state_t& self );
uint8_t scr_SetTargetToPassageID( script_state_t& state, ai_state_t& self );
uint8_t scr_MakeNameUnknown( script_state_t& state, ai_state_t& self );
uint8_t scr_SpawnExactParticleEndSpawn( script_state_t& state, ai_state_t& self );
uint8_t scr_SpawnPoofSpeedSpacingDamage( script_state_t& state, ai_state_t& self );
uint8_t scr_GiveExperienceToGoodTeam( script_state_t& state, ai_state_t& self );
uint8_t scr_DoNothing( script_state_t& state, ai_state_t& self );
uint8_t scr_GrogTarget( script_state_t& state, ai_state_t& self );
uint8_t scr_DazeTarget( script_state_t& state, ai_state_t& self );
uint8_t scr_EnableRespawn( script_state_t& state, ai_state_t& self );
uint8_t scr_DisableRespawn( script_state_t& state, ai_state_t& self );
uint8_t scr_DispelTargetEnchantID( script_state_t& state, ai_state_t& self );
uint8_t scr_IfHolderBlocked( script_state_t& state, ai_state_t& self );
uint8_t scr_IfTargetHasNotFullMana( script_state_t& state, ai_state_t& self );
uint8_t scr_EnableListenSkill( script_state_t& state, ai_state_t& self );
uint8_t scr_SetTargetToLastItemUsed( script_state_t& state, ai_state_t& self );
uint8_t scr_FollowLink( script_state_t& state, ai_state_t& self );
uint8_t scr_IfOperatorIsLinux( script_state_t& state, ai_state_t& self );
uint8_t scr_IfTargetIsAWeapon( script_state_t& state, ai_state_t& self );
uint8_t scr_IfSomeoneIsStealing( script_state_t& state, ai_state_t& self );
uint8_t scr_IfTargetIsASpell( script_state_t& state, ai_state_t& self );
uint8_t scr_IfBackstabbed( script_state_t& state, ai_state_t& self );
uint8_t scr_GetTargetDamageType( script_state_t& state, ai_state_t& self );
uint8_t scr_AddQuest( script_state_t& state, ai_state_t& self );
uint8_t scr_BeatQuestAllPlayers( script_state_t& state, ai_state_t& self );
uint8_t scr_IfTargetHasQuest( script_state_t& state, ai_state_t& self );
uint8_t scr_SetQuestLevel( script_state_t& state, ai_state_t& self );
uint8_t scr_AddQuestAllPlayers( script_state_t& state, ai_state_t& self );
uint8_t scr_AddBlipAllEnemies( script_state_t& state, ai_state_t& self );
uint8_t scr_PitsFall( script_state_t& state, ai_state_t& self );
uint8_t scr_IfTargetIsOwner( script_state_t& state, ai_state_t& self );
uint8_t scr_End( script_state_t& state, ai_state_t& self );
uint8_t scr_TakePicture( script_state_t& state, ai_state_t& self );
uint8_t scr_SetSpeech( script_state_t& state, ai_state_t& self );
uint8_t scr_SetMoveSpeech( script_state_t& state, ai_state_t& self );
uint8_t scr_SetSecondMoveSpeech( script_state_t& state, ai_state_t& self );
uint8_t scr_SetAttackSpeech( script_state_t& state, ai_state_t& self );
uint8_t scr_SetAssistSpeech( script_state_t& state, ai_state_t& self );
uint8_t scr_SetTerrainSpeech( script_state_t& state, ai_state_t& self );
uint8_t scr_SetSelectSpeech( script_state_t& state, ai_state_t& self );
uint8_t scr_IfOperatorIsMacintosh( script_state_t& state, ai_state_t& self );
uint8_t scr_IfModuleHasIDSZ( script_state_t& state, ai_state_t& self );
uint8_t scr_MorphToTarget( script_state_t& state, ai_state_t& self );
uint8_t scr_GiveManaFlowToTarget( script_state_t& state, ai_state_t& self );
uint8_t scr_GiveManaReturnToTarget( script_state_t& state, ai_state_t& self );
uint8_t scr_SetMoney( script_state_t& state, ai_state_t& self );
uint8_t scr_IfTargetCanSeeKurses( script_state_t& state, ai_state_t& self );
uint8_t scr_SpawnAttachedCharacter( script_state_t& state, ai_state_t& self );
uint8_t scr_KurseTarget( script_state_t& state, ai_state_t& self );
uint8_t scr_SetChildContent( script_state_t& state, ai_state_t& self );
uint8_t scr_SetTargetToChild( script_state_t& state, ai_state_t& self );
uint8_t scr_SetDamageThreshold( script_state_t& state, ai_state_t& self );
uint8_t scr_AccelerateTargetUp( script_state_t& state, ai_state_t& self );
uint8_t scr_SetTargetAmmo( script_state_t& state, ai_state_t& self );
uint8_t scr_EnableInvictus( script_state_t& state, ai_state_t& self );
uint8_t scr_DisableInvictus( script_state_t& state, ai_state_t& self );
uint8_t scr_TargetDamageSelf( script_state_t& state, ai_state_t& self );
uint8_t scr_SetTargetSize( script_state_t& state, ai_state_t& self );
uint8_t scr_DrawBillboard( script_state_t& state, ai_state_t& self );
uint8_t scr_SetTargetToBlahInPassage( script_state_t& state, ai_state_t& self );
uint8_t scr_IfTargetIsFacingSelf( script_state_t& state, ai_state_t& self );
uint8_t scr_IfLevelUp( script_state_t& state, ai_state_t& self );
uint8_t scr_GiveSkillToTarget( script_state_t& state, ai_state_t& self );
uint8_t scr_SetTargetToNearbyMeleeWeapon( script_state_t& state, ai_state_t& self );
uint8_t scr_EnableStealth(script_state_t& state, ai_state_t& self);
uint8_t scr_DisableStealth(script_state_t& state, ai_state_t& self);
uint8_t scr_IfStealthed(script_state_t& state, ai_state_t& self);
uint8_t scr_SetTargetToDistantFriend(script_state_t& state, ai_state_t& self);
uint8_t scr_DisplayCharge(script_state_t& state, ai_state_t& self);
