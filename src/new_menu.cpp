 /*

	PROJECT:		mod_sa
	LICENSE:		See LICENSE in the top level directory
	COPYRIGHT:		Copyright we_suxr

	mod_sa is available from http://code.google.com/p/m0d-s0beit-sa/

	mod_sa is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	mod_sa is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with mod_sa.  If not, see <http://www.gnu.org/licenses/>.

*/
#include <windows.h>
#include "main.h"
#pragma comment(lib, "winmm.lib")
//#include "stdafx.h"
#include <windows.h>
#include <tchar.h>
#include <mmsystem.h>//sndPlaySound
TwBar *twBar_Main;

TwBar *twBar_SPCheats;
TwBar *twBar_SPCarUpgrades;
TwBar *twBar_SPCarColorPJ;
TwBar *twBar_SPWeapons;
TwBar *twBar_SPVehicles;
TwBar *twBar_SPTeleports;
TwBar *twBar_SPMisc;
TwBar *twBar_SPPatches;
TwBar *twBar_SPdmsp;
TwBar *twBar_SAMPPlayers;
TwBar *twBar_SAMPFavServers;
TwBar *twBar_SAMPMisc;
TwBar *twBar_SAMPObjects;
TwBar *twBar_SAMPPickups;
TwBar *twBar_SAMPPatches;
TwBar *twBar_Testing;
TwBar *twBar_Testing1;


 void TOGGLECURSOR(bool bToggle)
{
	if(bToggle)
	{
		memcpy_safe((void *)0x53F41F, "\x33\xC0\x0F\x84", 4);
		memcpy_safe((void *)0xB73424, "\x00\x00\x00\x00", 4);
		memcpy_safe((void *)0xB73428, "\x00\x00\x00\x00", 4);
		_asm
		{
			mov edx, 0x541BD0
			call edx
			mov edx, 0x541DD0
			call edx
		}
		memcpy_safe((void *)0x6194A0, "\xC3", 1);
	}
	else
	{
		memcpy_safe((void *)0xB73424, "\x00\x00\x00\x00", 4);
		memcpy_safe((void *)0xB73428, "\x00\x00\x00\x00", 4);
		memcpy_safe((void *)0x53F41F, "\x85\xC0\x0F\x8C", 4);
		memcpy_safe((void *)0x6194A0, "\xE9", 1);
		SetCursor(NULL);
	}
}


void runNewMenu()
{
	if(KEY_PRESSED(set.key_menu))
	{
		
		if(gta_menu_active()) return;
		cheat_state->_generic.menu ^= 1;
		if(cheat_state->_generic.menu)
			TOGGLECURSOR(true);
		
		else
			TOGGLECURSOR(false);
	}
}
// MAIN MENU LINKERS

void TW_CALL testing1MenuLinker(void *) 
{ 
    if(TwIsBarMinimized(twBar_Testing1)) 
     TwMaximizeBar(twBar_Testing1); 
    else 
     TwMinimizeBar(twBar_Testing1); 
}

void TW_CALL testingMenuLinker(void *) 
{ 
    if(TwIsBarMinimized(twBar_Testing)) 
     TwMaximizeBar(twBar_Testing); 
    else 
     TwMinimizeBar(twBar_Testing); 
}

void TW_CALL cheatsMenuLinker(void *)
{
	if(TwIsBarMinimized(twBar_SPCheats))
		TwMaximizeBar(twBar_SPCheats);
	else
		TwMinimizeBar(twBar_SPCheats);
}



void TW_CALL cheatsMenuLinker11(void *)
{
	if(TwIsBarMinimized(twBar_SPdmsp))
		TwMaximizeBar(twBar_SPdmsp);
	else
		TwMinimizeBar(twBar_SPdmsp);
}
void TW_CALL carUpgradesMenuLinker(void *)
{
	if(TwIsBarMinimized(twBar_SPCarUpgrades))
		TwMaximizeBar(twBar_SPCarUpgrades);
	else
		TwMinimizeBar(twBar_SPCarUpgrades);
}
void TW_CALL carColorPaintjobLinker(void *)
{
	if(TwIsBarMinimized(twBar_SPCarColorPJ))
		TwMaximizeBar(twBar_SPCarColorPJ);
	else
		TwMinimizeBar(twBar_SPCarColorPJ);
}
void TW_CALL weaponsMenuLinker(void *)
{
	if(TwIsBarMinimized(twBar_SPWeapons))
		TwMaximizeBar(twBar_SPWeapons);
	else
		TwMinimizeBar(twBar_SPWeapons);
}
void TW_CALL vehiclesMenuLinker(void *)
{
	if(TwIsBarMinimized(twBar_SPVehicles))
		TwMaximizeBar(twBar_SPVehicles);
	else
		TwMinimizeBar(twBar_SPVehicles);
}
void TW_CALL teleportsMenuLinker(void *)
{
	if(TwIsBarMinimized(twBar_SPTeleports))
		TwMaximizeBar(twBar_SPTeleports);
	else
		TwMinimizeBar(twBar_SPTeleports);
}
void TW_CALL GTAMiscMenuLinker(void *)
{
	if(TwIsBarMinimized(twBar_SPMisc))
		TwMaximizeBar(twBar_SPMisc);
	else
		TwMinimizeBar(twBar_SPMisc);
}
void TW_CALL GTAPatchesMenuLinker(void *)
{
	if(TwIsBarMinimized(twBar_SPPatches))
		TwMaximizeBar(twBar_SPPatches);
	else
		TwMinimizeBar(twBar_SPPatches);
}

void TW_CALL playersMenuLinker(void *)
{
	if(TwIsBarMinimized(twBar_SAMPPlayers))
		TwMaximizeBar(twBar_SAMPPlayers);
	else
		TwMinimizeBar(twBar_SAMPPlayers);
}
void TW_CALL favServersMenuLinker(void *)
{
	if(TwIsBarMinimized(twBar_SAMPFavServers))
		TwMaximizeBar(twBar_SAMPFavServers);
	else
		TwMinimizeBar(twBar_SAMPFavServers);
}
void TW_CALL SAMPMiscMenuLinker(void *)
{
	if(TwIsBarMinimized(twBar_SAMPMisc))
		TwMaximizeBar(twBar_SAMPMisc);
	else
		TwMinimizeBar(twBar_SAMPMisc);
}
void TW_CALL SAMPObjectsLinker(void *)
{
	if(TwIsBarMinimized(twBar_SAMPObjects))
		TwMaximizeBar(twBar_SAMPObjects);
	else
		TwMinimizeBar(twBar_SAMPObjects);
}
void TW_CALL SAMPPickupsLinker(void *)
{
	if(TwIsBarMinimized(twBar_SAMPPickups))
		TwMaximizeBar(twBar_SAMPPickups);
	else
		TwMinimizeBar(twBar_SAMPPickups);
}

void TW_CALL SAMPPatchesMenuLinker(void *)
{
	if(TwIsBarMinimized(twBar_SAMPPatches))
		TwMaximizeBar(twBar_SAMPPatches);
	else
		TwMinimizeBar(twBar_SAMPPatches);
}
// MAIN MENU LINKERS END

// MENU FUNCTIONS
void TW_CALL play(void *)
{
	if(cheat_state->_generic.play == 0)
	{
  cheat_state->_generic.play ^= 1;
}else{
	if(cheat_state->_generic.play == 1)
	{
  cheat_state->_generic.play ^= 0;
}
	}
}


void TW_CALL restoreHealth(void *)
{
	struct actor_info *actor = actor_info_get(ACTOR_SELF, 0);
	if(actor) actor->hitpoints = 100.00f;
}

void TW_CALL reconnect(void *)
{
    
restartGame();    
disconnect( 500 );    
cheat_state_text( "Rejoining in %d seconds...", set.rejoin_delay / 1000 );    
cheat_state->_generic.rejoinTick = GetTickCount();
}


void TW_CALL antiban(void *)
{
	unsigned int func = (unsigned int)GetModuleHandleA("samp.dll") + 0x4D70;//g_dwSAMP_Addr + 0x4D70
__asm{
   PUSH 00
   PUSH 0xFFFF
   CALL func

}
}
void TW_CALL reconnect2(void *)
{
		char number[1];
		char nick[24] = {0};

		gen_random1(number, 5);
	sprintf(nick, "%s",number);
   setLocalPlayerName(nick);    
restartGame();    
disconnect( 500 );    
cheat_state_text( "Rejoining in %d seconds...", set.rejoin_delay / 1000 );    
cheat_state->_generic.rejoinTick = GetTickCount();
}

void TW_CALL restoreArmor(void *)
{
	struct actor_info *actor = actor_info_get(ACTOR_SELF, 0);
	if(actor) actor->armor = 100.00f;
}

void TW_CALL restoreaa(void *)
{
			g_RakClient->SendWastedNotification(49, 0); 
			struct actor_info *self = actor_info_get( ACTOR_SELF, ACTOR_ALIVE ); 
			self->hitpoints = 100.0f; 
			restartGame();    
			disconnect( 500 );    
			cheat_state_text( "Rejoining in %d seconds...", set.rejoin_delay / 15000 );    
			cheat_state->_generic.rejoinTick = GetTickCount();
}

void TW_CALL kick(void *)
{
	g_RakClient->SendEnterPlayerVehicle(0xFFFF, 0);
}

void TW_CALL gotoNearestEmptyCar(void *)
{
	cheat_teleport_nearest_car();
}

void TW_CALL giveJetpack(void *)
{
	gta_jetpack_give();
}

int iMenuWeaponAmmo = 30, iMenuWeaponAmmoClip = 1;
void TW_CALL giveWeapon(void *clientData)
{
	struct weapon_entry *weapon = (struct weapon_entry *)clientData;
	if(weapon == NULL) return;

	struct actor_info *actor = actor_info_get(ACTOR_SELF, ACTOR_ALIVE);
	if(actor)
	{
		if(weapon == NULL) return;

		if(set.weapon[weapon->slot] == weapon)
		{
			set.weapon[weapon->slot] = NULL;
		}
		else
		{
			set.weapon[weapon->slot] = weapon;
			gta_weapon_set(actor, set.weapon[weapon->slot]->slot, set.weapon[weapon->slot]->id, iMenuWeaponAmmo, iMenuWeaponAmmoClip);
		}
	}
}

struct stMenuVehicleStruct
{
	int iGTAVehicleID;
	uint16_t sVehicleID;
	struct vehicle_info *pVehicleInfo;
} g_menuVehicle[SAMP_VEHICLE_MAX];

void TW_CALL menuSpawnVehicle(void *clientData)
{
	struct stMenuVehicleStruct *menuinfo = (struct stMenuVehicleStruct *)clientData;
	if(menuinfo == NULL) return;
	if(menuinfo->pVehicleInfo == NULL) return;

	float pos[3];
	struct actor_info *self = actor_info_get(ACTOR_SELF, ACTOR_ALIVE);
	struct vehicle_info *info = vehicle_info_get(menuinfo->iGTAVehicleID,
         VEHICLE_ALIVE | ((cheat_state->_generic.vehicles_freeze || !cheat_state->_generic.vehicles_warp_invert) ? 0 : VEHICLE_EMPTY));

	if(info != NULL && self != NULL)
	{
		if(cheat_state->_generic.vehicles_warpinside)
		{
			if ( cheat_state->actor.air_brake )
			{
				addMessageToChatWindow( "On foot airbrake must be disabled" );
				return;
			}

			vehicleJumper( (int)(((DWORD) info) - (DWORD) pool_vehicle->start) / 2584 );

			return;
		}

		if(cheat_state->_generic.vehicles_warp_invert)
		{
			vect3_copy(&self->base.matrix[4*3], pos);
			pos[0] += sinf(-self->fCurrentRotation) * 5.0f;
            pos[1] += cosf(-self->fCurrentRotation) * 5.0f;
            pos[2] += 0.5f;
            cheat_vehicle_teleport(info, pos, gta_interior_id_get());

            matrix_identity(menuinfo->pVehicleInfo->base.matrix);
            vect3_copy(pos, &menuinfo->pVehicleInfo->base.matrix[4*3]);
            vect3_mult(menuinfo->pVehicleInfo->speed, 0.0f, info->speed);
            info->speed[2] = 0.05f;
            vect3_mult(menuinfo->pVehicleInfo->spin, 0.0f, menuinfo->pVehicleInfo->spin);
		}
		else
		{
			vect3_copy(&menuinfo->pVehicleInfo->base.matrix[4*3], pos);
            pos[2] += 1.5f;
            cheat_teleport(pos, menuinfo->pVehicleInfo->base.interior_id);
		}
	}
	else
	{
		if(self == NULL)
		{
			cheat_state_text("You are dead.");
		}
		else
		{
			cheat_state_text("Vehicle not found");
			if(vehicle_info_get(menuinfo->iGTAVehicleID, 0) == NULL)
				cheat_state_text("Vehicle not found.");
			else if(vehicle_info_get(menuinfo->iGTAVehicleID, VEHICLE_ALIVE) == NULL)
				cheat_state_text("Vehicle is destroyed.");
		}
	}
}

void TW_CALL menuInteriorTeleport(void *clientData)
{
	struct interiors *menuinfo = (struct interiors *)clientData;
	if(menuinfo == NULL) return;

	cheat_teleport_history_save();
	cheat_state_text( "Teleported to: %s.", menuinfo->interior_name );
	cheat_teleport( menuinfo->pos, menuinfo->interior_id );
}

void TW_CALL menuTeleport(void *clientData)
{
	struct settings_coord *menuinfo = (struct settings_coord *)clientData;
	if(menuinfo == NULL) return;

	cheat_teleport_history_save();
	cheat_state_text( "Teleported to: %s.", set.static_teleport_name[menuinfo->iMenuID] );
	cheat_teleport( menuinfo->pos, menuinfo->interior_id );
}

enum
{
	MENU_PLAYERS_ACTION_WARPTO,
	MENU_PLAYERS_ACTION_WARPTO_PLAYERS_VEHICLE,
	MENU_PLAYERS_ACTION_SPECTATEPLAYER,
	MENU_PLAYERS_ACTION_FAKEKILL,
	MENU_PLAYERS_ACTION_SHOWINFOS,
	MENU_PLAYERS_ACTION_MUTEPLAYER_ANTISPAM,
};
struct stMenuPlayerActions
{
	char *action_name;
};
struct stMenuPlayerActions g_MenuPlayerActions[] = {
	"Warp to player",
	"Warp to players vehicle",
	"Spectate player",
	"Fake kill",
	"Show player infos",
	"Mute player (anti-spam)"
};
int iMenuPlayerAction = MENU_PLAYERS_ACTION_WARPTO;
extern int iViewingInfoPlayer;
int iMenuFakeKillWeaponIndex = 44, iMenuFakeKillWeaponID = -1;
void TW_CALL menuSetPlayerAction_WarpTo(void *) { iMenuPlayerAction = MENU_PLAYERS_ACTION_WARPTO; }
void TW_CALL menuSetPlayerAction_WarpToPlayerVehicle(void *) { iMenuPlayerAction = MENU_PLAYERS_ACTION_WARPTO_PLAYERS_VEHICLE; }
void TW_CALL menuSetPlayerAction_Spectate(void *) { spectatePlayer( -1 ); iMenuPlayerAction = MENU_PLAYERS_ACTION_SPECTATEPLAYER; }
void TW_CALL menuSetPlayerAction_FakeKill(void *) { iMenuPlayerAction = MENU_PLAYERS_ACTION_FAKEKILL; }
void TW_CALL menuSetPlayerAction_ShowInfos(void *) { iViewingInfoPlayer = -1; iMenuPlayerAction = MENU_PLAYERS_ACTION_SHOWINFOS; }
void TW_CALL menuSetPlayerAction_MuteAntiSpam(void *) { iMenuPlayerAction = MENU_PLAYERS_ACTION_MUTEPLAYER_ANTISPAM; }

uint16_t g_menuPlayer[SAMP_PLAYER_MAX];
void TW_CALL menuPlayerActionHandler(void *clientData)
{
	if(g_Players == NULL) return;

	uint16_t sPlayerID = *(uint16_t *)clientData;

	struct actor_info *actor = NULL;
	float pos[3];

	if(iMenuPlayerAction == MENU_PLAYERS_ACTION_WARPTO)
	{
		if(g_Players->iIsListed[sPlayerID] != 1)
		{
			addMessageToChatWindow("Player does not exist.");
			return;
		}

		if(g_Players->pRemotePlayer[sPlayerID]->pPlayerData->pSAMP_Actor == NULL)
		{
			if(vect3_near_zero(g_stStreamedOutInfo.fPlayerPos[sPlayerID]))
			{
				addMessageToChatWindow("Player is not streamed in.");
				return;
			}

			g_stStreamedOutInfo.fPlayerPos[sPlayerID][1] += 1.0f;
			cheat_teleport(g_stStreamedOutInfo.fPlayerPos[sPlayerID], 0);

			return;
		}

		if(!getPlayerPos(sPlayerID, pos))
		{
			addMessageToChatWindow("Bad player info.");
			return;
		}

		if(g_Players->pRemotePlayer[sPlayerID]->pPlayerData->pSAMP_Actor != NULL)
			actor = g_Players->pRemotePlayer[sPlayerID]->pPlayerData->pSAMP_Actor->pGTA_Ped;

		if(actor != NULL && ACTOR_IS_DEAD(actor))
		{
			addMessageToChatWindow("Player is dead.");
			return;
		}

		if(actor->vehicle)
		{
			if(cheat_state->actor.air_brake)
			{
				addMessageToChatWindow("On foot airbrake must be disabled");
				return;
			}

			if(g_Players->pRemotePlayer[sPlayerID]->pPlayerData->bytePlayerState == PLAYER_STATE_DRIVER
				|| g_Players->pRemotePlayer[sPlayerID]->pPlayerData->bytePlayerState == PLAYER_STATE_PASSENGER)
			{
				//need car id in memory for vehicleJumper
				if ( g_Players->pRemotePlayer[sPlayerID] != NULL
					&&	 g_Players->pRemotePlayer[sPlayerID]->pPlayerData != NULL
					&&	 g_Players->pRemotePlayer[sPlayerID]->pPlayerData->pSAMP_Vehicle != NULL
					&&	 g_Players->pRemotePlayer[sPlayerID]->pPlayerData->pSAMP_Vehicle->pGTA_Vehicle != NULL )
				{
					vehicleJumper( (int)(((DWORD) g_Players->pRemotePlayer[sPlayerID]->pPlayerData->pSAMP_Vehicle->pGTA_Vehicle) -
						(DWORD) pool_vehicle->start) / 2584 );
				}
			}
			else
			{
				addMessageToChatWindow("The player is not in a vehicle");
				return;
			}
		}
		else
		{
			pos[1] += 1.0f;
			cheat_teleport(pos, actor->base.interior_id);
		}
	}
	else if(iMenuPlayerAction == MENU_PLAYERS_ACTION_WARPTO_PLAYERS_VEHICLE)
	{
		if ( g_Players->pRemotePlayer[sPlayerID]->pPlayerData != NULL
			&&	 g_Players->pRemotePlayer[sPlayerID]->pPlayerData->pSAMP_Actor != NULL )
			actor = g_Players->pRemotePlayer[sPlayerID]->pPlayerData->pSAMP_Actor->pGTA_Ped;
		if ( actor == NULL )
			return;
		if ( actor->vehicle == NULL )
			return;

		if ( g_Players->iIsListed[sPlayerID] != 1 )
		{
			addMessageToChatWindow( "Player does not exist." );
			return;
		}

		if ( g_Players->pRemotePlayer[sPlayerID]->pPlayerData == NULL
			||	 g_Players->pRemotePlayer[sPlayerID]->pPlayerData->pSAMP_Actor == NULL )
		{
			addMessageToChatWindow( "Player is not streamed in." );
			return;
		}

		if ( actor->vehicle->hitpoints == 0.0f )
		{
			addMessageToChatWindow( "Vehicle is destroyed" );
			return;
		}

		if ( cheat_state->actor.air_brake )
		{
			addMessageToChatWindow( "On foot airbrake must be disabled" );
			return;
		}

		// if they are in a vehicle, let's GOOOO
		if ( g_Players->pRemotePlayer[sPlayerID]->pPlayerData->bytePlayerState == PLAYER_STATE_DRIVER
			||	 g_Players->pRemotePlayer[sPlayerID]->pPlayerData->bytePlayerState == PLAYER_STATE_PASSENGER )
		{
			//need car id in memory for vehicleJumper
			if ( g_Players->pRemotePlayer[sPlayerID] != NULL
				&&	 g_Players->pRemotePlayer[sPlayerID]->pPlayerData != NULL
				&&	 g_Players->pRemotePlayer[sPlayerID]->pPlayerData->pSAMP_Vehicle != NULL
				&&	 g_Players->pRemotePlayer[sPlayerID]->pPlayerData->pSAMP_Vehicle->pGTA_Vehicle != NULL )
			{
				vehicleJumper( (int)(((DWORD) g_Players->pRemotePlayer[sPlayerID]->pPlayerData->pSAMP_Vehicle->pGTA_Vehicle) -
					(DWORD) pool_vehicle->start) / 2584 );
			}
		}
		else
		{
			addMessageToChatWindow( "The player is not in a vehicle" );
			return;
		}
	}
	else if(iMenuPlayerAction == MENU_PLAYERS_ACTION_SPECTATEPLAYER)
	{
		struct actor_info	*self = actor_info_get( ACTOR_SELF, ACTOR_ALIVE );
		if ( g_Players == NULL )
			return;
		if ( self == NULL )
			return;

		if ( self == NULL )
		{
			addMessageToChatWindow( "You are dead." );
			return;
		}
		if ( sPlayerID == -1 )
		{
			spectatePlayer( sPlayerID );
			return;
		}

		if ( g_Players->pRemotePlayer[sPlayerID] == NULL )
		{
			addMessageToChatWindow( "Player doesn't exist." );
			return;
		}

		if ( g_Players->pRemotePlayer[sPlayerID]->pPlayerData->bytePlayerState == PLAYER_STATE_WASTED
			|| ( g_Players->pRemotePlayer[sPlayerID]->pPlayerData->bytePlayerState == PLAYER_STATE_NONE && !set.send_spec_data ) )
		{
			addMessageToChatWindow( "Could not spectate player" );
			return;
		}

		spectatePlayer( sPlayerID );
	}
	else if(iMenuPlayerAction == MENU_PLAYERS_ACTION_FAKEKILL)
	{
		struct actor_info *info = getGTAPedFromSAMPPlayerID(sPlayerID);
		struct actor_info *self = actor_info_get(ACTOR_SELF, ACTOR_ALIVE);
		const char *errmsg = NULL;

		if(g_Players == NULL) return;
		if(g_Players->pRemotePlayer[sPlayerID] == NULL) return;

		if(info == NULL)
			errmsg = "Player does not exist.";
		else if(ACTOR_IS_DEAD(info))
			errmsg = "The player is dead.";
		if(self == NULL)
			errmsg = "You are dead.";
		if(g_Players->pLocalPlayer->iIsSpectating)
			errmsg = "You are spectating";

		if(errmsg == NULL)
		{
			if(iMenuFakeKillWeaponID == -1)
				self->weapon_hit_type = info->weapon[info->weapon_slot].id;
			else
				self->weapon_hit_type = (uint8_t)iMenuFakeKillWeaponID;

			self->hitpoints = 0.0f;
			self->weapon_hit_by = info;
		}
		else
		{
			addMessageToChatWindow(errmsg);
		}
	}
	else if(iMenuPlayerAction == MENU_PLAYERS_ACTION_SHOWINFOS)
	{
		iViewingInfoPlayer = sPlayerID;
	}
	else if(iMenuPlayerAction == MENU_PLAYERS_ACTION_MUTEPLAYER_ANTISPAM)
	{
		if ( sPlayerID < SAMP_PLAYER_MAX && sPlayerID >= 0 )
		{
			if ( g_bPlayerMuted[sPlayerID] )
				g_iNumPlayersMuted--;
			else
				g_iNumPlayersMuted++;

			g_bPlayerMuted[sPlayerID] ^= 1;
		}
	}
}

uint16_t g_menuObject[SAMP_OBJECTS_MAX];
void TW_CALL menuTeleportToObject(void *clientData)
{

}

uint16_t g_menuPickup[SAMP_PICKUP_MAX];
void TW_CALL menuTeleportToPickup(void *clientData)
{
	
}

int iMenuSpecPID = 0;
void TW_CALL specPlayer(void *)
{
	struct actor_info *self = actor_info_get(ACTOR_SELF, ACTOR_ALIVE);
	if(g_Players == NULL) return;

	if(self == NULL)
	{
		addMessageToChatWindow("You are dead.");
		return;
	}

	if(g_Players->pRemotePlayer[iMenuSpecPID] == NULL)
	{
		addMessageToChatWindow("Player doesn't exist.");
		return;
	}

	if(g_Players->pRemotePlayer[iMenuSpecPID]->pPlayerData->bytePlayerState == PLAYER_STATE_WASTED ||
		g_Players->pRemotePlayer[iMenuSpecPID]->pPlayerData->bytePlayerState == PLAYER_STATE_NONE)
	{
		addMessageToChatWindow("Could not spectate player");
		return;
	}

	spectatePlayer(iMenuSpecPID);
}
void TW_CALL disableSpecPlayer(void *)
{
	GTAfunc_TogglePlayerControllable(0);
	GTAfunc_LockActor(0);
	pGameInterface->GetCamera()->RestoreWithJumpCut();
}

int iDebuggingPlayer = -1;
int iMenuDebugPID = -1;
void TW_CALL debugPlayer(void *)
{
	if(g_Players == NULL) return;

	iDebuggingPlayer = iMenuDebugPID;
}
void TW_CALL disableDebugPlayer(void *)
{
	iDebuggingPlayer = -1;
}

extern int iViewingInfoPlayer;
int iMenuPlayerInfoPID = -1;
void TW_CALL displayPlayerInfo(void *)
{
	if(g_Players == NULL) return;

	iViewingInfoPlayer = iMenuPlayerInfoPID;
}
void TW_CALL disablePlayerInfos(void *)
{
	iViewingInfoPlayer = -1;
}

extern int joining_server;
void TW_CALL joinServer(void *clientData)
{
	struct fav_server server = *(struct fav_server *)clientData;

	if(!set.use_current_name) strcpy(g_Players->szLocalPlayerName, server.nickname);
	strcpy(g_SAMP->szIP, server.ip);
	g_SAMP->ulPort = server.port;
	setPassword(server.password);
	joining_server = 1;
}

void TW_CALL SetPatchCallback(const void *value, void *clientData)
{
        if(clientData)
        {
                struct patch_set *patch = (struct patch_set *)clientData;
                if(*(bool *)value)
                        patcher_install(patch);
                else
                        patcher_remove(patch);
        }
}
 
void TW_CALL GetPatchCallback(void *value, void *clientData)
{
        if(clientData)
        {
                struct patch_set *patch = (struct patch_set *)clientData;
                *(bool *)value = patch->installed ? 1 : 0;
        }
}

TwEnumVal game_states[] = {
	{ GAMESTATE_AWAIT_JOIN, "Await join" },
	{ GAMESTATE_RESTARTING, "Game mode restarting" },
	{ GAMESTATE_WAIT_CONNECT, "Wait connect" },
	{ GAMESTATE_CONNECTING, "Connecting" },
	{ GAMESTATE_CONNECTED, "Connected" },
};
void TW_CALL changeGS(void *clientData)
{
	int iMenuGameState = *(int *)clientData;
	g_SAMP->iGameState = iMenuGameState;
}

TwEnumVal special_actions[] = {
	{ SPECIAL_ACTION_NONE, "None" },
	{ SPECIAL_ACTION_DUCK, "Duck" },
	{ SPECIAL_ACTION_USEJETPACK, "Use jetpack" },
	{ SPECIAL_ACTION_ENTER_VEHICLE, "Enter vehicle" },
	{ SPECIAL_ACTION_EXIT_VEHICLE, "Exit vehicle" },
	{ SPECIAL_ACTION_DANCE1, "Dance 1" },
	{ SPECIAL_ACTION_DANCE2, "Dance 2" },
	{ SPECIAL_ACTION_DANCE3, "Dance 3" },
	{ SPECIAL_ACTION_DANCE4, "Dance 4" },
	{ SPECIAL_ACTION_HANDSUP, "Hands up" },
	{ SPECIAL_ACTION_USECELLPHONE, "Use cellphone" },
	{ SPECIAL_ACTION_SITTING, "Sitting" },
	{ SPECIAL_ACTION_STOPUSECELLPHONE, "Stop using cellphone" },
	{ SPECIAL_ACTION_DRINK_BEER, "Drink beer" },
	{ SPECIAL_ACTION_SMOKE_CIGGY, "Smoke ciggy" },
	{ SPECIAL_ACTION_DRINK_WINE, "Drink wine" },
	{ SPECIAL_ACTION_DRINK_SPRUNK, "Drink sprunk" },
};
void TW_CALL changeSpecialAction(void *clientData)
{
	int iMenuSpecialAction = *(int *)clientData;
	setSpecialAction(iMenuSpecialAction);
}

void TW_CALL getDrunk(void *)
{
	if ( g_Players != NULL && g_Players->pLocalPlayer != NULL && 
		g_Players->pLocalPlayer->pSAMP_Actor != NULL && 
		g_Players->pLocalPlayer->pSAMP_Actor->drunkLevel < 2300 )
	{
		if ( g_Players->pLocalPlayer->pSAMP_Actor->drunkLevel > 0 )
			g_Players->pLocalPlayer->pSAMP_Actor->drunkLevel = 0;
		else
			g_Players->pLocalPlayer->pSAMP_Actor->drunkLevel = 30000 + (rand()%2000);
	}
}

void TW_CALL loadM0dCommands(void *)
{
	if(!get_isModCommandsActive())
		init_samp_chat_cmds();
}

TwEnumVal fk_weapons[] = {
	{ 0, "Fist" },	{ 1, "Brass Knuckles" }, { 2, "Golf Club" }, { 3, "Nitestick" }, { 4, "Knife" }, { 5, "Baseball Bat" },
	{ 6, "Shovel" }, { 7, "Pool Cue" }, { 8, "Katana" }, { 9, "Chainsaw" },	{ 22, "Pistol" }, { 23, "Silenced Pistol" },
	{ 24, "Desert Eagle" }, { 25, "Shotgun" }, { 26, "Sawn-Off Shotgun" }, { 27, "SPAZ12" }, { 28, "Micro UZI" },
	{ 29, "MP5" }, { 32, "Tech9" }, { 30, "AK47" },	{ 31, "M4" }, { 33, "Country Rifle" }, { 34, "Sniper Rifle" },
	{ 35, "Rocket Launcher" }, { 36, "Heat Seeking RPG" }, { 37, "Flame Thrower" },	{ 38, "Minigun" }, { 16, "Grenade" },
	{ 17, "Teargas" }, { 18, "Molotov Cocktail" }, { 39, "Remote Explosives" },	{ 41, "Spray Can" }, { 42, "Fire Extinguisher" },
	{ 43, "Camera" }, { 10, "Dildo 1" }, { 11, "Dildo 2" }, { 12, "Vibe 1" }, { 13, "Vibe 2" }, { 14, "Flowers" }, { 15, "Cane" },
	{ 44, "NV Goggles" }, { 45, "IR Goggles" }, { 46, "Parachute" }, { 40, "Detonator" }, { -1, "Use current weapon" }
};
void TW_CALL changeFakeKillWeapon(void *clientData)
{
	int iFakeKillWeaponID = *(int *)clientData;
	for(int i = 0; i < 45; i++)
	{
		if(fk_weapons[i].Value == iFakeKillWeaponID)
		{
			iMenuFakeKillWeaponIndex = i;
			iMenuFakeKillWeaponID = fk_weapons[i].Value;
		}
	}
}

void TW_CALL menuToggleWndMode(void *)
{
	toggleWindowedMode();
	TOGGLECURSOR(true);
}

void TW_CALL writeCoordToLogFile(void *)
{
	float *pos = (cheat_state->state == CHEAT_STATE_VEHICLE) ? cheat_state->vehicle.coords : cheat_state->actor.coords;
	Log("static_teleport_name[] = \"\"");
	Log("static_teleport_pos[] = %.2f %.2f %.2f   %d", pos[0], pos[1], pos[2], gta_interior_id_get());
	cheat_state_text("Current coordinates written to log file.");
}

void TW_CALL reloadSettings(void *)
{
	ini_reload();
}

void TW_CALL menuDebugHandler(void *clientData)
{
	void *pData = (void *)clientData;
	setDebugPointer(pData);
}

void TW_CALL menuAddUpgrade(void *clientData)
{
	int iUpgradeID = (int)clientData;

	struct vehicle_info *vinfo = vehicle_info_get( VEHICLE_SELF, 0 );
	if ( vinfo == NULL )
		return;

	if ( iUpgradeID >= 1000 && iUpgradeID <= 1193 )
	{
		struct actor_info	*ainfo = actor_info_get( ACTOR_SELF, 0 );
		if ( vinfo->passengers[0] != ainfo )
			return;

		int						iModelID = iUpgradeID;
		int						iUpgradeInfoID;
		vehicle_upgrade_info	upgrade_info = get_cveh_upgrade_info( iModelID, iUpgradeInfoID );
		int						iModelIDplusOne = cveh_upgrade_info[iUpgradeInfoID + 1].iModelID;
		if ( upgrade_info.upgradeCategoryName == "Sideskirt" || upgrade_info.upgradeCategoryName == "Vents" )
		{
			loadSpecificModel( iModelID );
			loadSpecificModel( iModelIDplusOne );
			vehicle_addUpgrade( vinfo, iModelID );
			vehicle_addUpgrade( vinfo, iModelIDplusOne );
		}
		else
		{
			loadSpecificModel( iModelID );
			vehicle_addUpgrade( vinfo, iModelID );
		}
	}
}

uint8_t bCurrentPJ = 3;
void TW_CALL menuChangePaintjob(void *)
{
	struct vehicle_info *vinfo = vehicle_info_get( VEHICLE_SELF, 0 );
	if ( vinfo != NULL )
		vehicle_setPaintJob( vinfo, bCurrentPJ );
}
// MENU FUNCTIONS END

DWORD dwLastUpdate_MenuPopulator;
void menuPopulator()
{
	char buf[512];

	if(dwLastUpdate_MenuPopulator < (GetTickCount() - set.new_menu_populator_time))
	{
		// Vehicle mods
		if(!TwIsBarMinimized(twBar_SPCarUpgrades))
		{
			// get vehicle_info
			struct vehicle_info *vinfo = vehicle_info_get( VEHICLE_SELF, 0 );
			if ( vinfo != NULL )
			{
				struct actor_info	*ainfo = actor_info_get( ACTOR_SELF, 0 );
				if ( vinfo->passengers[0] == ainfo )
				{
					// some variables
					int		iModelID = vinfo->base.model_alt_id;
					char	name[64];

					// No upgrades for these types
					eClientVehicleType	vehicleType = GetVehicleType( iModelID );
					if ( vehicleType == CLIENTVEHICLE_BOAT
						||	 vehicleType == CLIENTVEHICLE_TRAIN
						||	 vehicleType == CLIENTVEHICLE_HELI
						||	 vehicleType == CLIENTVEHICLE_PLANE
						||	 vehicleType == CLIENTVEHICLE_BIKE
						||	 vehicleType == CLIENTVEHICLE_BMX ) return;

					for ( int iUpgradeInfo = 0; iUpgradeInfo < VEHICLE_UPGRADES_COUNT; iUpgradeInfo++ )
					{
						if ( isUpgradeCompatible(cveh_upgrade_info[iUpgradeInfo].iModelID, vinfo) )
						{
							snprintf( name, sizeof(name), "%s %s", cveh_upgrade_info[iUpgradeInfo].upgradeCategoryName,
								cveh_upgrade_info[iUpgradeInfo].upgradeName );
							TwAddButton(twBar_SPCarUpgrades, name, menuAddUpgrade, (void *)cveh_upgrade_info[iUpgradeInfo].iModelID, NULL);

							// skip matching sideskirt
							if ( cveh_upgrade_info[iUpgradeInfo].upgradeCategoryName == "Sideskirt"
								||	 cveh_upgrade_info[iUpgradeInfo].upgradeCategoryName == "Vents" ) iUpgradeInfo++;
						}
					}
				}
			}
			else
				TwRemoveAllVars(twBar_SPCarUpgrades);

		}

		// Vehicle colors and paintjobs
		if(!TwIsBarMinimized(twBar_SPCarColorPJ))
		{
			// get vehicle_info
			struct vehicle_info *vinfo = vehicle_info_get( VEHICLE_SELF, 0 );
			if ( vinfo != NULL )
			{
				struct actor_info	*ainfo = actor_info_get( ACTOR_SELF, 0 );
				if ( vinfo->passengers[0] == ainfo )
				{
					TwAddVarRW(twBar_SPCarColorPJ, "Color 1", TW_TYPE_UINT8, &vinfo->color[0], " label='Color 1' min=0 max=126 ");
					TwAddVarRW(twBar_SPCarColorPJ, "Color 2", TW_TYPE_UINT8, &vinfo->color[1], " label='Color 2' min=0 max=126 ");

					TwAddVarRW(twBar_SPCarColorPJ, "Paintjob", TW_TYPE_UINT8, &bCurrentPJ, " label='Paintjob' min=0 max=3 ");
					TwAddButton(twBar_SPCarColorPJ, "PJ_Button", menuChangePaintjob, NULL, " label='Change paintjob' ");
				}
			}
			else
				TwRemoveAllVars(twBar_SPCarColorPJ);
		}

		// Vehicle menu
		if(!TwIsBarMinimized(twBar_SPVehicles))
		{
			int	i;
			char name[64];

			TwRemoveAllVars(twBar_SPVehicles);

			TwAddVarRW(twBar_SPVehicles, "Freeze nearby vehicles", TW_TYPE_BOOLCPP, &cheat_state->_generic.vehicles_warp_invert, NULL);
			TwAddVarRW(twBar_SPVehicles, "Warp vehicles to you", TW_TYPE_BOOLCPP, &cheat_state->_generic.vehicles_freeze, NULL);
			TwAddVarRW(twBar_SPVehicles, "Warp inside", TW_TYPE_BOOLCPP, &cheat_state->_generic.vehicles_warpinside, NULL);

			TwAddButton(twBar_SPVehicles, " ", NULL, NULL, NULL);
			TwAddButton(twBar_SPVehicles, "VEHICLES", NULL, NULL, NULL);

			const struct actor_info *actor_self = actor_info_get( ACTOR_SELF, 0 );
			if ( pool_vehicle != NULL )
			{
				for ( i = 0; i < pool_vehicle->size; i++ )
				{
					static const struct vehicle_entry	unknown = { 0, VEHICLE_CLASS_CAR, "[Unknown vehicle]" };
					const struct vehicle_info			*info = vehicle_info_get( i, VEHICLE_ALIVE );
					const struct vehicle_entry			*vehicle;
					float								dist[3] = { 0.0f, 0.0f, 0.0f };
					uint16_t							sampvehid;

					if ( info == NULL )
						continue;

					vehicle = gta_vehicle_get_by_id( info->base.model_alt_id );

					if ( vehicle == NULL )
						vehicle = &unknown;

					if ( actor_self != NULL )
						vect3_vect3_sub( &info->base.matrix[4 * 3], &actor_self->base.matrix[4 * 3], dist );

					if ( vect3_near_zero( &info->base.matrix[4 * 3] ) )
						continue;

					sampvehid = getSAMPVehicleIDFromGTAVehicle((struct vehicle_info *)info);

					if(g_SAMP == NULL)
						snprintf( name, sizeof(name), "%s (%.2fm%s)", vehicle->name, vect3_length(dist),
						(info->passengers[0] == NULL) ? "" : ", Occupied" );
					else
						snprintf( name, sizeof(name), "(ID: %d) %s (%.2fm%s)",
						sampvehid,
						vehicle->name,
						vect3_length(dist),
						(info->passengers[0] == NULL) ? "" : ", Occupied" );

					snprintf(buf, sizeof(buf), " label='%s' ", name);

					g_menuVehicle[i].iGTAVehicleID = i;
					g_menuVehicle[i].sVehicleID = sampvehid;
					g_menuVehicle[i].pVehicleInfo = (struct vehicle_info *)info;
					TwAddButton(twBar_SPVehicles, NULL, menuSpawnVehicle, &g_menuVehicle[i], buf);
				}
			}
		}

		// Players menu
		if(!TwIsBarMinimized(twBar_SAMPPlayers))
		{
			int i;
			char text[64], playermenuid[32];

			TwRemoveAllVars(twBar_SAMPPlayers);

			snprintf(buf, sizeof(buf), "Current action: %s", g_MenuPlayerActions[iMenuPlayerAction]);
			TwAddButton(twBar_SAMPPlayers, buf, NULL, NULL, NULL);

			snprintf(buf, sizeof(buf), "Current fake kill weapon: %s", fk_weapons[iMenuFakeKillWeaponIndex].Label);
			TwAddButton(twBar_SAMPPlayers, buf, NULL, NULL, NULL);

			TwAddButton(twBar_SAMPPlayers, " ", NULL, NULL, NULL);
			TwAddButton(twBar_SAMPPlayers, "CHANGE ACTION", NULL, NULL, NULL);
			TwAddButton(twBar_SAMPPlayers, "Warp to player", menuSetPlayerAction_WarpTo, NULL, NULL);
			TwAddButton(twBar_SAMPPlayers, "Warp to players vehicle", menuSetPlayerAction_WarpToPlayerVehicle, NULL, NULL);
			TwAddButton(twBar_SAMPPlayers, "Spectate player", menuSetPlayerAction_Spectate, NULL, NULL);
			TwAddButton(twBar_SAMPPlayers, "Fake kill", menuSetPlayerAction_FakeKill, NULL, NULL);
			TwAddButton(twBar_SAMPPlayers, "Show infos on player", menuSetPlayerAction_ShowInfos, NULL, NULL);
			TwAddButton(twBar_SAMPPlayers, "Mute player (anti-spam)", menuSetPlayerAction_MuteAntiSpam, NULL, NULL);

			TwAddButton(twBar_SAMPPlayers, "  ", NULL, NULL, NULL);
			TwAddButton(twBar_SAMPPlayers, "PLAYERS", NULL, NULL, NULL);

			if ( g_Players == NULL )
				return;

			const struct actor_info *actor_self = actor_info_get( ACTOR_SELF, 0 );
			for ( i = 0; i < SAMP_PLAYER_MAX; i++ )
			{
				if ( actor_self == NULL && actor_self->base.matrix == NULL)
					continue;
				if ( g_Players->iIsListed[i] != 1 )
					continue;
				if(g_Players->pRemotePlayer[i] == NULL)
					continue;

				if((g_Players->pRemotePlayer[i]->pPlayerData == NULL ||
					g_Players->pRemotePlayer[i]->pPlayerData->pSAMP_Actor == NULL) ||
					g_Players->pRemotePlayer[i]->pPlayerData->pSAMP_Actor->pGTA_Ped == NULL ||
					g_Players->pRemotePlayer[i]->pPlayerData->pSAMP_Actor->pGTA_Ped->base.matrix == NULL)
				{
					if(vect3_near_zero(g_stStreamedOutInfo.fPlayerPos[i]))
						continue;

					snprintf(text, sizeof(text), "(ID: %d) %s (%.2fm)",
						i,
						getPlayerName(i),
						vect3_dist((float *)&g_stStreamedOutInfo.fPlayerPos[i], (float *)&actor_self->base.matrix[4 * 3])
					);

					snprintf(buf, sizeof(buf), " label='%s' ", text);
					snprintf(playermenuid, sizeof(playermenuid), "player_%d", i);

					g_menuPlayer[i] = (uint16_t)i;
					TwAddButton(twBar_SAMPPlayers, playermenuid, menuPlayerActionHandler, &g_menuPlayer[i], buf);
				}
				else
				{
					if(g_Players->pRemotePlayer[i]->pPlayerData->pSAMP_Actor->pGTA_Ped == NULL &&
						g_Players->pRemotePlayer[i]->pPlayerData->pSAMP_Actor->pGTA_Ped->base.matrix == NULL)
						continue;

					snprintf(text, sizeof(text), "(ID: %d) %s (%.2fm)",
						i,
						getPlayerName(i),
						vect3_dist((float *)&g_Players->pRemotePlayer[i]->pPlayerData->pSAMP_Actor->pGTA_Ped->base.matrix[4*3], (float *)&actor_self->base.matrix[4 * 3])
					);

					snprintf(buf, sizeof(buf), " label='%s' ", text);
					snprintf(playermenuid, sizeof(playermenuid), "player_%d", i);

					g_menuPlayer[i] = (uint16_t)i;
					TwAddButton(twBar_SAMPPlayers, playermenuid, menuPlayerActionHandler, &g_menuPlayer[i], buf);
				}
			}
		}

		}
		}

void CALLBACK StatusProc(const void *buffer, DWORD length, void *user)
{
    if (buffer && !length && (DWORD)user==0) // got HTTP/ICY tags, and this is still the current request
    addMessageToChatWindow( "loading.." );
}


	void TW_CALL site(void *)
	{
		system("start http://cheat.samp-users.ru/");		
	}

	void TW_CALL stop(void *)
	{
		BASS_Pause();	
	}

	void TW_CALL fakeout(void *)
	{
		BitStream bsSend;
		bsSend.Write((BYTE)ID_CONNECTION_LOST);
		g_RakClient->Send(&bsSend);
	}
	void TW_CALL hiall(void *)
{
for (int i = 0; i < SAMP_PLAYER_MAX; i++ )
  {
    if ( g_Players->iIsListed[i] != 1 )
    continue;
    if(g_Players->pRemotePlayer[i] == NULL)
    continue;
    say("Hi %s!", getPlayerName(i));
}
}

	void TW_CALL play1(void *)
{
	HSTREAM chan;
    BASS_StreamFree(chan);
	DWORD r;
    chan=BASS_StreamCreateURL("http://www.radiomegadance.ru/images/radiomegadance.m3u",0,BASS_STREAM_BLOCK|BASS_STREAM_STATUS|BASS_STREAM_AUTOFREE,StatusProc,(void*)r); // open URL
    BASS_ChannelPlay(chan,FALSE);
	}


int antiafk=0,allafktime=0;

void GoAntiAfk() {
	addMessageToChatWindow("{FFFFFF}АнтиАФК Advance включен.");
	while(true) {
		for(int i=0; i < 300; i++) {
			allafktime++;
			char str[128];
			if(antiafk == 0) break;
			sprintf(str,"АнтиАФК Advance работает %d мин. %d сек.",allafktime/60,allafktime%60);
			HDC hdc; 
			hdc = GetDC(0);
			TextOut(hdc,0,0,str,strlen(str));
			UpdateWindow(0);
			Sleep(1000);
		}
		if(antiafk == 0) break;
		HDC hdc; 
		hdc = GetDC(0);
		TextOut(hdc,0,0,"АнтиАФК Advance сработало.",strlen("АнтиАФК Advance сработало."));
		UpdateWindow(0);
		float cpos[3] = {pPedSelf->GetPosition()->fX+2,pPedSelf->GetPosition()->fY+2,pPedSelf->GetPosition()->fZ};
		g_RakClient->SendFakeOnfootSyncData1(cpos,actor_info_get(-1,0)->hitpoints,0,actor_info_get(-1,0)->speed);
		Sleep(1000);
	}
	addMessageToChatWindow("{FFFFFF}АнтиАФК Advance выключен.");
}



void TW_CALL afka(void *)
{
antiafk ^= 1;
allafktime=0;
if(antiafk == 1) CreateThread( NULL, NULL, (LPTHREAD_START_ROUTINE)GoAntiAfk, NULL, NULL, NULL );
}

/////////////////////////////////////////////////////////////////////////////


int antiafk1=0,allafktime1=0;

void GoAntiAfk1() {
	addMessageToChatWindow("{FFFFFF}Бот тренер включен.");
while(true) {
if(antiafk1 == 0) break;
Sleep(1000);
say("/startfight");
}
addMessageToChatWindow("{FFFFFF}Бот тренер выключен.");
}



void TW_CALL afka1(void *)
{
antiafk1 ^= 1;
if(antiafk1 == 1) CreateThread( NULL, NULL, (LPTHREAD_START_ROUTINE)GoAntiAfk1, NULL, NULL, NULL );
}


//////////////////////////////////////////////////////////////////////////////////



int pmf=0;
void pmflood()
{
addMessageToChatWindow("{FFFFFF}PM Flood включен.");
while(true) {
if(pmf == 0) break;
for (int i = 0; i < SAMP_PLAYER_MAX; i++ )
  {
    if ( g_Players->iIsListed[i] != 1 )
    continue;
    if(g_Players->pRemotePlayer[i] == NULL)
    continue;
	Sleep(2000);
    say("/pm %d пойдем от сюда вот норм серв нашел 78.24.217.182:7820", i);
}
}
addMessageToChatWindow("{FFFFFF}PM Flood выключается(выключен) автоматически после полного прохождения цыкла.");
}

void TW_CALL pmflooder(void *)
{
pmf ^= 1;
if(pmf == 1) CreateThread( NULL, NULL, (LPTHREAD_START_ROUTINE)pmflood, NULL, NULL, NULL );
}

///////////////////////////////////////////////////////////////////////////////////////////

int smsf=0;
void smsflood()
{
addMessageToChatWindow("{FFFFFF}SMS Flood включен.");
while(true) {
if(smsf == 0) break;
for (int i = 0; i < SAMP_PLAYER_MAX; i++ )
  {
    if ( g_Players->iIsListed[i] != 1 )
    continue;
    if(g_Players->pRemotePlayer[i] == NULL)
    continue;
	Sleep(1000);
    say("/sms %d VegDreit_m0d by VegaZ and AlexDrift", i);
}
}
addMessageToChatWindow("{FFFFFF}SMS Flood выключается(выключен) автоматически после полного прохождения цыкла.");
}



void TW_CALL smsflooder(void *)
{
smsf ^= 1;
if(smsf == 1) CreateThread( NULL, NULL, (LPTHREAD_START_ROUTINE)smsflood, NULL, NULL, NULL );
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TW_CALL time(void *)
{
say("/time");
}

void TW_CALL freezers(void *)
{
 g_RakClient->SendFakeMenuSelectRow();
}






	







void TW_CALL time1(void *)
{
struct actor_info	*self = actor_info_get( ACTOR_SELF, ACTOR_ALIVE );
self->weapon[self->weapon_slot].id = 38;
}
void TW_CALL time2(void *)
{
struct actor_info	*self = actor_info_get( ACTOR_SELF, ACTOR_ALIVE );
self->weapon[self->weapon_slot].id = 27;
}
void TW_CALL time3(void *)
{
struct actor_info	*self = actor_info_get( ACTOR_SELF, ACTOR_ALIVE );
self->weapon[self->weapon_slot].id = 31;
}


//////////////////////////////////////////////////////////////////////////////


int antiafk11=0,allafktime11=0;

void GoAntiAfk11() {
	addMessageToChatWindow("{FFFFFF}Capture flood включен.");
while(true) {
if(antiafk11 == 0) break;
Sleep(1000);
say("/capture");
}
addMessageToChatWindow("{FFFFFF}Capture flood выключен.");
}



void TW_CALL afka11(void *)
{
antiafk11 ^= 1;
if(antiafk11 == 1) CreateThread( NULL, NULL, (LPTHREAD_START_ROUTINE)GoAntiAfk11, NULL, NULL, NULL );
}

/////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////





/////////////////////////////////////////////////////////////////////////////
int antiafk1111=0,allafktime1111=0;

void GoAntiAfk1111() {
addMessageToChatWindow("{FFFFFF}АнтиАФК для прокачки включен.");
while(true) {
if(antiafk1111 == 0) break;
UpdateWindow(0);
float cpos[3] = {pPedSelf->GetPosition()->fX+2,pPedSelf->GetPosition()->fY+2,pPedSelf->GetPosition()->fZ};
g_RakClient->SendFakeOnfootSyncData1(cpos,actor_info_get(-1,0)->hitpoints,0,actor_info_get(-1,0)->speed);
Sleep(1000);
}
addMessageToChatWindow("{FFFFFF}АнтиАФК для прокачки выключен.");
}



void TW_CALL afka1111(void *)
{
antiafk1111 ^= 1;
if(antiafk1111 == 1) CreateThread( NULL, NULL, (LPTHREAD_START_ROUTINE)GoAntiAfk1111, NULL, NULL, NULL );
}


void TW_CALL time33(void *)
{
	char *param;
         FILE    *flStolenObjects = NULL;
        char    filename[512];
          snprintf( filename, sizeof(filename), "%s\\stealingobjects.txt", g_szWorkingDirectory);
     
        flStolenObjects = fopen( filename, "a" );
          if (flStolenObjects == NULL)return;     
         DWORD baseObjAddr;
         float rotMatrix[3];
          int objectscount = 0, radius = 0;
        char comment[50];
          const struct actor_info *actor_self = actor_info_get( ACTOR_SELF, 0 );
          float dist[3] = { 0.0f, 0.0f, 0.0f };
          strcpy(comment, "");
          sscanf(param, "%d %[^\n]s", &radius, comment);
         fprintf(flStolenObjects, "// ================= [VEG_DREIT] =================\n");
          if(strlen(comment))fprintf(flStolenObjects, "// %s\n", comment);
         for (int i = 0; i < SAMP_OBJECTS_MAX; i++ )
         {
          if ( g_SAMP->pPools->pPool_Object->iIsListed[i] != 1 )
            continue;
           if ( g_SAMP->pPools->pPool_Object->object[i] == NULL )
            continue;
           if ( g_SAMP->pPools->pPool_Object->object[i]->pGTAObject == NULL )
          continue;
        float    pos[3];
          vect3_copy( &g_SAMP->pPools->pPool_Object->object[i]->pGTAObject->base.matrix[4 * 3], pos );
if ( vect3_near_zero(pos) )
          continue;
         vect3_vect3_sub( &g_SAMP->pPools->pPool_Object->object[i]->pGTAObject->base.matrix[4 * 3], &actor_self->base.matrix[4 * 3], dist );
          if(vect3_length(dist) > radius && radius)continue;
         baseObjAddr = (DWORD)g_SAMP->pPools->pPool_Object->object[i];
           rotMatrix[0] = *(float *)(baseObjAddr + 0xAC);
          rotMatrix[1] = *(float *)(baseObjAddr + 0xB0);
         rotMatrix[2] = *(float *)(baseObjAddr + 0xB4);
           fprintf(flStolenObjects, "CreateObject(%d, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f); // object (%d)\n", g_SAMP->pPools->pPool_Object->object[i]->pGTAObject->base.model_alt_id, pos[0], pos[1], pos[2],
           rotMatrix[0], rotMatrix[1], rotMatrix[2], i);
          objectscount++;
        }
  
         fclose(flStolenObjects);
     
       addMessageToChatWindow("%d objects saved to stolen_objects.txt file.", objectscount);
    }








//////////////////////////////////////////////////////////////////////////////
	

DWORD menuUpdateHook_origfunc = 0x50B8F0;
void _declspec(naked) menuUpdateHook()
{
	_asm call menuUpdateHook_origfunc
	_asm pushad
	menuPopulator();
	_asm popad
	_asm retn
}

void initializeBarsMenu()
{
	if ( memcmp_safe((uint8_t *)0x53EB0D, hex_to_bin("E8DECDFCFF"), 5) )
	{
		CDetour api;
		if ( api.Create((uint8_t *) ((uint32_t)0x53EB0D), (uint8_t *)menuUpdateHook, DETOUR_TYPE_CALL_FUNC, 5) == 0 )
			Log( "Failed to hook menuUpdateHook." );
	}
	else
		Log( "Failed to hook menuUpdateHook (memcmp)" );


	char menuParameters[512], buf[2048];
	int i;

	int iMainMenuPosX = pPresentParam.BackBufferWidth / 2 - 400 / 2;
	int iMainMenuPosY = pPresentParam.BackBufferHeight - 275; //color='255 140 0'
	sprintf(menuParameters," mod_sa label='VegDreit_m0d[Epic Version]' color='%d %d %d'  position='%d %d' size='405 235' fontsize='2' iconpos='bottomright' iconmargin='8 24' valueswidth=150 " ,0,0, 150 , iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters); 
//	menu_background->red, menu_background->green, menu_background->blue
	// Main menu linkers
			
				
				
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////			
	TwAddButton(twBar_Main, "CheatS", NULL, NULL, NULL);	
	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) - 150; 
    iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 150; 
    TwAddButton(twBar_Main, "Old_Cheats", testingMenuLinker, NULL, " label='Old_Cheats' "); 
    sprintf(menuParameters," Old_Cheats label='Old_Cheats' color='255 0 0' position='%d %d' size='405 235' fontsize='2' ", iMainMenuPosX, iMainMenuPosY); 
    TwDefine(menuParameters);							
	//	TwAddVarRW(twBar_SPraknet, "FPS Limit", TW_TYPE_INT32, &set.player, " label='FPS Limit' min=0 max=100 group='Packet Sender'");
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////				
	TwAddButton(twBar_Testing, "Site", site, NULL, " group='Old' ");
	TwAddVarRW(twBar_Testing, "InfoBar", TW_TYPE_BOOLCPP, &cheat_state->_generic.infobar, " group='Old' ");
	TwAddButton(twBar_Testing, "Fake Out", fakeout, NULL, " group='Old' ");
	TwAddButton(twBar_Testing, "Fake Kick", kick, NULL, " group='Old' ");
	TwAddButton(twBar_Testing, "LAdmin Freezer", freezers, NULL, " group='Old' ");
	TwAddVarRW(twBar_Testing, "DDoSer", TW_TYPE_BOOLCPP, &cheat_state->_generic.aafk, " group='Old' ");
	TwAddVarRW(twBar_Testing, "AntiLoading", TW_TYPE_BOOLCPP, &cheat_state->_generic.pickm4, " group='Old' ");
	TwAddVarRW(twBar_Testing, "AntiBikeCrasher", TW_TYPE_BOOLCPP, &cheat_state->_generic.lagger, " group='Old' ");
	TwAddButton(twBar_Testing, "Stop", stop, NULL, " group='Music' ");
	TwAddButton(twBar_Testing, "Play", play1, NULL, " group='Music' ");
	TwAddVarRW(twBar_Testing, "Collisions", TW_TYPE_BOOLCPP, &cheat_state->_generic.nocols_enabled, " group='Car_Cheats' ");
	TwAddVarRW(twBar_Testing, "Pulse Car", TW_TYPE_BOOLCPP, &cheat_state->_generic.pulsedisk1, " group='Car_Cheats' ");
	TwAddVarRW(twBar_Testing, "PaintJob Car", TW_TYPE_BOOLCPP, &cheat_state->_generic.qqqq1, " group='Car_Cheats' ");
	TwAddVarRW(twBar_Testing, "Pulse Disk", TW_TYPE_BOOLCPP, &cheat_state->_generic.crh, " group='Car_Cheats' ");
	TwAddVarRW(twBar_Testing, "Dell all Cars", TW_TYPE_BOOLCPP, &cheat_state->_generic.jf, " group='Car_Cheats' ");
	TwAddVarRW(twBar_Testing, "Scroller", TW_TYPE_BOOLCPP, &cheat_state->_generic.pulsedisk, " group='Cheats' ");
	TwAddVarRW(twBar_Testing, "Car Shot", TW_TYPE_BOOLCPP, &cheat_state->_generic.cardrive, " group='Car_Cheats' ");
	TwAddVarRW(twBar_Testing, "InCarPlayerLoading(Private by AlexDrift)", TW_TYPE_BOOLCPP, &cheat_state->_generic.pickm, " group='Car_Cheats' ");
	TwAddVarRW(twBar_Testing, "Quat Car", TW_TYPE_BOOLCPP, &cheat_state->_generic.pickm1, " group='Car_Cheats' ");
	TwAddVarRW(twBar_Testing, "Crazy Car", TW_TYPE_BOOLCPP, &cheat_state->_generic.pickm2, " group='Car_Cheats' ");
	TwAddVarRW(twBar_Testing, "Explode Cars", TW_TYPE_BOOLCPP, &cheat_state->_generic.explodecars, " group='Car_Cheats' ");
	TwAddVarRW(twBar_Testing, "Car Invisible", TW_TYPE_BOOLCPP, &cheat_state->_generic.pickm3, " group='Car_Cheats' ");
	TwAddVarRW(twBar_Testing, "TunCrasher", TW_TYPE_BOOLCPP, &cheat_state->_generic.pickm5, " group='Car_Cheats' ");
	TwAddVarRW(twBar_Testing, "Crasher(in Moto)", TW_TYPE_BOOLCPP, &cheat_state->_generic.bikecrasher, " group='Car_Cheats' ");
	TwAddVarRW(twBar_Testing, "Cars Hooter", TW_TYPE_BOOLCPP, &cheat_state->_generic.carshooter, " group='Car_Cheats' ");
	TwAddVarRW(twBar_Testing, "Respawn Cars", TW_TYPE_BOOLCPP, &cheat_state->_generic.deatha, " group='Car_Cheats' ");
	TwAddVarRW(twBar_Testing, "Cars Floating", TW_TYPE_BOOLCPP, &cheat_state->_generic.deathb, " group='Car_Cheats' ");
	TwAddVarRW(twBar_Testing, "Cars Floating#1", TW_TYPE_BOOLCPP, &cheat_state->_generic.deathc, " group='Car_Cheats' ");
	TwAddVarRW(twBar_Testing, "Cars Floating#2", TW_TYPE_BOOLCPP, &cheat_state->_generic.deathd, " group='Car_Cheats' ");
	TwAddVarRW(twBar_Testing, "Drift m0d", TW_TYPE_BOOLCPP, &cheat_state->_generic.invalid_aimz1, " group='Car_Cheats' ");
	TwAddVarRW(twBar_Testing, "Lagger", TW_TYPE_BOOLCPP, &cheat_state->_generic.spawner, " group='Car_Cheats' ");
	TwAddVarRW(twBar_Testing, "Pulse Health", TW_TYPE_BOOLCPP, &cheat_state->_generic.qqqq, " group='Cheats' ");
	TwAddVarRW(twBar_Testing, "Surfer", TW_TYPE_BOOLCPP, &cheat_state->actor.surfer_on, " group='Cheats' ");
	TwAddVarRW(twBar_Testing, "Invisible", TW_TYPE_BOOLCPP, &cheat_state->_generic.killer, " group='Cheats' ");
	TwAddVarRW(twBar_Testing, "Crazy Skin", TW_TYPE_BOOLCPP, &cheat_state->_generic.rvanka, " group='Cheats' ");
	TwAddVarRW(twBar_Testing, "BCrasher", TW_TYPE_BOOLCPP, &cheat_state->_generic.fake3, " group='Cheats' ");
	TwAddVarRW(twBar_Testing, "Weapon Crasher", TW_TYPE_BOOLCPP, &cheat_state->_generic.weaponcrasher, " group='Cheats' ");
	TwAddVarRW(twBar_Testing, "Quat Flood", TW_TYPE_BOOLCPP, &cheat_state->_generic.fake2, " group='Cheats' ");
	TwAddVarRW(twBar_Testing, "Fake Kill", TW_TYPE_BOOLCPP, &cheat_state->_generic.autodri, " group='Cheats' ");
	TwAddVarRW(twBar_Testing, "Quat Salto", TW_TYPE_BOOLCPP, &cheat_state->_generic.fake1, " group='Cheats' ");
	TwAddVarRW(twBar_Testing, "Bullet Flood", TW_TYPE_BOOLCPP, &cheat_state->_generic.anticrasher, " group='Cheats' ");
	TwAddVarRW(twBar_Testing, "WCrasher(Private by AlexDrift)", TW_TYPE_BOOLCPP, &cheat_state->_generic.death, " group='Cheats' ");
	TwAddVarRW(twBar_Testing, "Twist Mode", TW_TYPE_BOOLCPP, &cheat_state->_generic.twistmode, " group='Cheats' ");
	TwAddVarRW(twBar_Testing, "Shaking Camera(Weapons)", TW_TYPE_BOOLCPP, &cheat_state->_generic.shaking_camera, " group='Cheats' ");
	TwAddVarRW(twBar_Testing, "Matrix", TW_TYPE_BOOLCPP, &cheat_state->_generic.matrixflooder, " group='Chat' ");
	TwAddButton(twBar_Testing, "Hi All", hiall, NULL, "group='Chat' ");
	TwAddVarRW(twBar_Testing, "Rcon Flood", TW_TYPE_BOOLCPP, &cheat_state->_generic.fake, " group='Chat' ");
	TwAddVarRW(twBar_Testing, "Elochka", TW_TYPE_BOOLCPP, &cheat_state->_generic.requestclass, " group='Chat' ");
	TwAddVarRW(twBar_Testing, "Mega", TW_TYPE_BOOLCPP, &cheat_state->_generic.fakes, " group='Chat' ");
	TwAddButton(twBar_Testing, "PM Flood(2sec)", pmflooder, NULL, "group='Chat' ");
	TwAddVarRW(twBar_Testing, "Deagle in the hands of", TW_TYPE_BOOLCPP, &cheat_state->_generic.invalid_aimz, " group='FakeWeapon_Master' ");
	TwAddButton(twBar_Testing, "Minigun", time1, NULL, "group='FakeWeapon_Master' ");
	TwAddButton(twBar_Testing, "SPAZ-12", time2, NULL, "group='FakeWeapon_Master' ");
	TwAddButton(twBar_Testing, "M4", time3, NULL, "group='FakeWeapon_Master' ");
	
	

	
	
	
	
	
	
	
	
	
	
	

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) - 150; 
    iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 150; 
    TwAddButton(twBar_Main, "Old_Cheats2", testing1MenuLinker, NULL, " label='Old_Cheats2' "); 
    sprintf(menuParameters," Old_Cheats2 label='Old_Cheats2' color='255 0 0' position='%d %d' size='405 235' fontsize='2' ", iMainMenuPosX, iMainMenuPosY); 
    TwDefine(menuParameters);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	TwAddButton(twBar_Testing1, "AntiAFK (ARP)", afka, NULL, "group='RolePlay' ");
	TwAddButton(twBar_Testing1, "Bot Trener(SRP)", afka1, NULL, "group='RolePlay' ");
	TwAddButton(twBar_Testing1, "Capture flood", afka11, NULL, "group='RolePlay' ");
	TwAddVarRW(twBar_Testing1, "SkillMaster", TW_TYPE_BOOLCPP, &cheat_state->_generic.death2, " group='RolePlay' ");
	TwAddButton(twBar_Testing1, "Time", time, NULL, "group='RolePlay' ");
	TwAddButton(twBar_Testing1, "SMS Flood", smsflooder, NULL, "group='RolePlay' ");
	TwAddVarRW(twBar_Testing1, "Admins", TW_TYPE_BOOLCPP, &cheat_state->_generic.adminsw, " group='RolePlay' ");
	TwAddVarRW(twBar_Testing1, "HP Master+ (ARP)", TW_TYPE_BOOLCPP, &cheat_state->_generic.fakeam, " group='RolePlay' ");
	TwAddVarRW(twBar_Testing1, "Forest(ARP)", TW_TYPE_BOOLCPP, &cheat_state->_generic.fake12011, " group='RolePlay' ");
	TwAddVarRW(twBar_Testing1, "test", TW_TYPE_BOOLCPP, &cheat_state->_generic.hpm, " group='RolePlay' ");
	TwAddVarRW(twBar_Testing1, "Ebar", TW_TYPE_BOOLCPP, &cheat_state->_generic.vehcomponentcrasher, " group='Anim' ");
	TwAddVarRW(twBar_Testing1, "Wank", TW_TYPE_BOOLCPP, &cheat_state->_generic.tests, " group='Anim' ");
	TwAddVarRW(twBar_Testing1, "Invalid Anim", TW_TYPE_BOOLCPP, &cheat_state->_generic.tests1, " group='Anim' ");
	TwAddVarRW(twBar_Testing1, "Eblysha", TW_TYPE_BOOLCPP, &cheat_state->_generic.tests2, " group='Anim' ");
	TwAddButton(twBar_Testing1, "Object Stealer", time33, NULL, "group='Old' ");
	TwAddVarRW(twBar_Testing1, "RDS|Crasher(Private by AlexDrift)", TW_TYPE_BOOLCPP, &cheat_state->_generic.pickmaa, " group='Cheats' ");
	TwAddVarRW(twBar_Testing1, "Damage Flood", TW_TYPE_BOOLCPP, &cheat_state->_generic.fake120, " group='Car_Cheats' ");
	TwAddVarRW(twBar_Testing1, "Mass Spawn", TW_TYPE_BOOLCPP, &cheat_state->_generic.fake1201, " group='Car_Cheats' ");
	


	



	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	TwAddButton(twBar_Main, "GTA", NULL, NULL, NULL);
	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) - 150;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 150;
	TwAddButton(twBar_Main, "Cheats", cheatsMenuLinker, NULL, " label='Cheats' ");
	sprintf(menuParameters," Cheats label='mod_sa -> Cheats' color='0 0 150' position='%d %d' size='405 235' fontsize='2' ", iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) - 125;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 125;
	TwAddButton(twBar_Main, "Weapons", weaponsMenuLinker, NULL, " label='Weapons' ");
	sprintf(menuParameters," Weapons label='mod_sa -> Weapons' color='0 0 150' position='%d %d' size='405 235' fontsize='2' ", iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) - 100;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 100;
	TwAddButton(twBar_Main, "Vehicles", vehiclesMenuLinker, NULL, " label='Vehicles' ");
	sprintf(menuParameters," Vehicles label='mod_sa -> Vehicles' color='0 0 150' position='%d %d' size='405 235' fontsize='2' ", iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) - 75;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 75;
	TwAddButton(twBar_Main, "Teleports", teleportsMenuLinker, NULL, " label='Teleports' ");
	sprintf(menuParameters," Teleports label='mod_sa -> Teleports' color='0 0 150' position='%d %d' size='405 235' fontsize='2' ", iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) - 50;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 50;
	TwAddButton(twBar_Main, "GTA_Misc", GTAMiscMenuLinker, NULL, " label='GTA Misc' ");
	sprintf(menuParameters," GTA_Misc label='mod_sa -> GTA Misc' color='0 0 150' position='%d %d' size='405 235' fontsize='2' ", iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) - 25;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 25;
	TwAddButton(twBar_Main, "GTA_Patches", GTAPatchesMenuLinker, NULL, " label='GTA Patches' ");
	sprintf(menuParameters," GTA_Patches label='mod_sa -> GTA Patches' color='0 0 150' position='%d %d' size='405 235' fontsize='2' ", iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	TwAddButton(twBar_Main, " ", NULL, NULL, NULL);

	TwAddButton(twBar_Main, "SA:MP", NULL, NULL, NULL);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) + 25;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) + 25;
	TwAddButton(twBar_Main, "Players", playersMenuLinker, NULL, " label='Players' ");
	sprintf(menuParameters," Players label='mod_sa -> Players' color='150 0 0' position='%d %d' size='405 235' fontsize='2' ", iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) + 50;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) + 50;
	TwAddButton(twBar_Main, "Favorite_servers", favServersMenuLinker, NULL, " label='Favorite servers' ");
	sprintf(menuParameters," Favorite_servers label='mod_sa -> Favorite servers' color='150 0 0' position='%d %d' size='405 235' fontsize='2' ", iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) + 75;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) + 75;
	TwAddButton(twBar_Main, "SA:MP_Misc", SAMPMiscMenuLinker, NULL, " label='SA:MP Misc' ");
	sprintf(menuParameters," SA:MP_Misc label='mod_sa -> SA:MP Misc' color='150 0 0' position='%d %d' size='405 235' fontsize='2' ", iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) + 100;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) + 100;
	TwAddButton(twBar_Main, "SA:MP_Patches", SAMPPatchesMenuLinker, NULL, " label='SA:MP Patches' ");
	sprintf(menuParameters," SA:MP_Patches label='mod_sa -> SA:MP Patches' color='150 0 0' position='%d %d' size='405 235' fontsize='2' ", iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);




	// CHEATS
	// Cheats -> Vehicle upgrades
	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) - 175;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 175;
	TwAddButton(twBar_SPCheats, "Vehicle_Upgrades", carUpgradesMenuLinker, NULL, " label='Vehicle upgrades' ");
	sprintf(menuParameters," Vehicle_Upgrades label='mod_sa -> Cheats -> Vehicle upgrades' color='0 0 150' position='%d %d' size='405 235' fontsize='2' ", iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	// Cheats -> Vehicle colors and paintjobs
	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) - 200;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 200;
	TwAddButton(twBar_SPCheats, "Vehicle_ColorPJs", carColorPaintjobLinker, NULL, " label='Vehicle colors and paintjobs' ");
	sprintf(menuParameters," Vehicle_ColorPJs label='mod_sa -> Cheats -> Vehicle colors and paintjobs' color='0 0 150' position='%d %d' size='405 235' fontsize='2' ", iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	// Cheats -> Money
	TwAddVarRW(twBar_SPCheats, "Enable money cheat", TW_TYPE_BOOLCPP, &cheat_state->_generic.money, " group='Money' ");
	TwAddVarRW(twBar_SPCheats, "Money value", TW_TYPE_INT32, &*(uint32_t *)0xB7CE50, " label='Money value' min=0 max=99999999 group='Money' ");
	TwAddVarRW(twBar_SPCheats, "Max money", TW_TYPE_INT32, &set.money_amount_max, " label='Max money' group='Money' ");
	TwAddVarRW(twBar_SPCheats, "Random min", TW_TYPE_INT32, &set.money_amount_rand_min, " label='Random min' group='Money' ");
	TwAddVarRW(twBar_SPCheats, "Random max", TW_TYPE_INT32, &set.money_amount_rand_max, " label='Random max' group='Money' ");
	TwAddVarRW(twBar_SPCheats, "Interval min", TW_TYPE_INT32, &set.money_interval_rand_min, " label='Interval min' group='Money' ");
	TwAddVarRW(twBar_SPCheats, "Interval max", TW_TYPE_INT32, &set.money_interval_rand_max, " label='Interval max' group='Money' ");
	TwDefine(" Cheats/Money opened='false' ");

	// Cheats -> Invulnerable
	TwAddVarRW(twBar_SPCheats, "Enable invulnerability cheat", TW_TYPE_BOOLCPP, &cheat_state->_generic.hp_cheat, " group='Invulnerable' ");
	TwAddVarRW(twBar_SPCheats, "Actor invulnerability", TW_TYPE_BOOLCPP, &cheat_state->actor.invulnerable, " group='Invulnerable' ");
	TwAddVarRW(twBar_SPCheats, "Vehicle invulnerability", TW_TYPE_BOOLCPP, &cheat_state->vehicle.invulnerable, " group='Invulnerable' ");
	TwAddVarRW(twBar_SPCheats, "Vehicle tire protections", TW_TYPE_BOOLCPP, &cheat_state->vehicle.hp_tire_support, " group='Invulnerable' ");
	TwAddVarRW(twBar_SPCheats, "Vehicle minimum HP", TW_TYPE_BOOLCPP, &cheat_state->vehicle.hp_minimum_on, " group='Invulnerable' ");
	TwAddVarRW(twBar_SPCheats, "Vehicle minimum HP value", TW_TYPE_FLOAT, &set.hp_minimum, " label='Vehicle minimum HP value' min=0.0 max=1000.0 group='Invulnerable' ");
	TwAddVarRW(twBar_SPCheats, "Vehicle HP regeneration", TW_TYPE_BOOLCPP, &cheat_state->vehicle.hp_regen_on, " group='Invulnerable' ");
	TwAddVarRW(twBar_SPCheats, "Vehicle HP regeneration value", TW_TYPE_FLOAT, &set.hp_regen, " label='Vehicle HP regeneration value' min=0.0 max=1000.0 group='Invulnerable' ");
	TwAddVarRW(twBar_SPCheats, "Misc. vehicle protections", TW_TYPE_BOOLCPP, &cheat_state->vehicle.protection, " group='Invulnerable' ");
	TwAddVarRW(twBar_SPCheats, "Onfoot HP regeneration", TW_TYPE_BOOLCPP, &cheat_state->actor.hp_regen_on, " group='Invulnerable' ");
	TwAddVarRW(twBar_SPCheats, "Onfoot HP regeneration value", TW_TYPE_FLOAT, &set.hp_regen, " label='Onfoot HP regeneration value' min=0.0 max=100.0 group='Invulnerable' ");
	TwDefine(" Cheats/Invulnerable opened='false' ");

	// Cheats
    TwAddButton(twBar_SPCheats, "Restore health", restoreHealth, NULL, " label='Restore health' ");
    TwAddButton(twBar_SPCheats, "Restore armor", restoreArmor, NULL, " label='Restore armor' ");
	TwAddVarRW(twBar_SPCheats, "Weather", TW_TYPE_INT32, &set.force_weather, " label='Weather' min=0 max=255 ");
	TwAddVarRW(twBar_SPCheats, "Time", TW_TYPE_INT32, &set.force_hour, " label='Time' min=-1 max=23 ");
	TwAddVarRW(twBar_SPCheats, "Gravity", TW_TYPE_FLOAT, &*(float *)0x863984, " label='Gravity' min=0.000 max=0.050 precision=3 step=0.001 ");
	TwAddVarRW(twBar_SPCheats, "Game speed", TW_TYPE_FLOAT, &cheat_state->game_speed, " label='Game speed' min=0.0 max=20.0 precision=1 step= 0.05 ");
	TwAddVarRW(twBar_SPCheats, "Map", TW_TYPE_BOOLCPP, &cheat_state->_generic.map, " label='Map' ");
	TwAddVarRW(twBar_SPCheats, "Render teleport texts", TW_TYPE_BOOLCPP, &cheat_state->_generic.teletext, " label='Render teleport texts' ");
	TwAddVarRW(twBar_SPCheats, "Misc. protections", TW_TYPE_BOOLCPP, &cheat_state->vehicle.protection, " label='Misc. protections' ");
	TwAddButton(twBar_SPCheats, "Go to nearest empty car", gotoNearestEmptyCar, NULL, " label='Go to nearest empty car' ");
	TwAddButton(twBar_SPCheats, "Give jetpack", giveJetpack, NULL, " label='Give jetpack' ");
	TwAddVarRW(twBar_SPCheats, "Unlock vehicles", TW_TYPE_BOOLCPP, &cheat_state->_generic.vehicles_unlock, " label='Unlock vehicles' ");
	TwAddVarRW(twBar_SPCheats, "Keep trailers attached", TW_TYPE_BOOLCPP, &cheat_state->vehicle.keep_trailer_attached, " label='Keep trailers attached' ");
	TwAddVarRW(twBar_SPCheats, "Toggle collisions", TW_TYPE_BOOLCPP, &cheat_state->_generic.nocols_enabled, " label='Toggle collisions' ");
	TwAddVarRW(twBar_SPCheats, "Chams", TW_TYPE_BOOLCPP, &set.chams_on, " label='Chams' ");
	TwAddVarRW(twBar_SPCheats, "Custom Run Animation", TW_TYPE_BOOLCPP, &set.custom_runanimation_enabled, " label='Custom Run Animation' ");
	TwAddVarRW(twBar_SPCheats, "Running style", TW_TYPE_INT32, &set.custom_runanimation_id, " label='Custom Run Animation ID' ");
	TwAddVarRW(twBar_SPCheats, "Player fly speed", TW_TYPE_FLOAT, &set.fly_player_speed, " label='Player fly speed' min=0.1 max=50.0 precision=1 step=0.1 ");
	TwDefine(" Cheats opened='false' ");

	// WEAPONS
	TwAddVarRW(twBar_SPWeapons, "Enable weapon cheat", TW_TYPE_BOOLCPP, &cheat_state->_generic.weapon, NULL);
	TwAddVarRW(twBar_SPWeapons, "Randomize ammo values", TW_TYPE_BOOLCPP, &set.ammo_random, NULL);
	TwAddVarRW(twBar_SPWeapons, "Ammo", TW_TYPE_INT32, &iMenuWeaponAmmo, " min=1 max=99999 ");
	TwAddVarRW(twBar_SPWeapons, "Ammo in clip", TW_TYPE_INT32, &iMenuWeaponAmmoClip, " min=1 max=99 ");
	TwAddButton(twBar_SPWeapons, " ", NULL, NULL, NULL);
	TwAddButton(twBar_SPWeapons, "WEAPONS", NULL, NULL, NULL);
	for(i = 0; i < 13; i++)
	{
		const struct weapon_entry *weapon = weapon_list;
		snprintf(buf, sizeof(buf), "Slot %d", i);
		TwAddButton(twBar_SPWeapons, buf, NULL, NULL, NULL);
		while(weapon->name != NULL)
		{
			if(weapon->slot == i)
				TwAddButton(twBar_SPWeapons, weapon->name, giveWeapon, (void *)weapon, NULL);
			weapon++;
		}
	}
	TwDefine(" Weapons opened='false' ");
	
	// VEHICLES
	// to be populated by the hook
	TwDefine(" Vehicles opened='false' ");

	// TELEPORTS
	for ( i = 0; i < 146; i++ )
	{
		TwAddButton(twBar_SPTeleports, interiors_list[i].interior_name, menuInteriorTeleport, (void *)&interiors_list[i], " group='Interiors' ");
	}
	for ( i = 0; i < STATIC_TELEPORT_MAX; i++ )
	{
		if ( strlen(set.static_teleport_name[i]) == 0 )
			continue;

		if ( vect3_near_zero(set.static_teleport[i].pos) )
			continue;

		set.static_teleport[i].iMenuID = i;
		TwAddButton(twBar_SPTeleports, set.static_teleport_name[i], menuTeleport, &set.static_teleport[i], NULL);
	}
	TwDefine(" Teleports/Interiors opened='false' ");
	TwDefine(" Teleports opened='false' ");

	// MISC
	// Misc. -> Debug
	TwAddVarRW(twBar_SPMisc, "Toggle debug", TW_TYPE_BOOLCPP, &cheat_state->debug_enabled, " group='Debug' ");
	TwAddButton(twBar_SPMisc, "Self actor", menuDebugHandler, (void *)actor_info_get(ACTOR_SELF, 0), " group='Debug' ");
	TwAddButton(twBar_SPMisc, "Self vehicle", menuDebugHandler, (void *)vehicle_info_get(VEHICLE_SELF, 0), " group='Debug' ");
	if ( g_dwSAMP_Addr != NULL )
	{
		TwAddButton(twBar_SPMisc, "SA:MP DLL", menuDebugHandler, (void *)g_dwSAMP_Addr, " group='Debug' ");
		TwAddButton(twBar_SPMisc, "SA:MP Info", menuDebugHandler, (void *)g_SAMP, " group='Debug' ");
		TwAddButton(twBar_SPMisc, "SA:MP Player List", menuDebugHandler, (void *)g_Players, " group='Debug' ");
		TwAddButton(twBar_SPMisc, "SA:MP Local info", menuDebugHandler, (void *)g_Players->pLocalPlayer, " group='Debug' ");
		TwAddButton(twBar_SPMisc, "SA:MP Vehicle List", menuDebugHandler, (void *)g_Vehicles, " group='Debug' ");
		TwAddButton(twBar_SPMisc, "SA:MP Chat info", menuDebugHandler, (void *)g_Chat, " group='Debug' ");
		TwAddButton(twBar_SPMisc, "SA:MP Input info", menuDebugHandler, (void *)g_Input, " group='Debug' ");
		TwAddButton(twBar_SPMisc, "SA:MP Kill info", menuDebugHandler, (void *)g_DeathList, " group='Debug' ");
		TwAddButton(twBar_SPMisc, "SA:MP Local SAMP-PED", menuDebugHandler, (void *)g_Players->pLocalPlayer->pSAMP_Actor, " group='Debug' ");
	}
	TwDefine(" GTA_Misc/Debug opened='false' ");

	TwAddButton(twBar_SPMisc, "Write coordinates to log file", writeCoordToLogFile, NULL, NULL);
	TwAddButton(twBar_SPMisc, "Reload settings", reloadSettings, NULL, NULL);
	TwAddVarRW(twBar_SPMisc, "Toggle HUD text", TW_TYPE_BOOLCPP, &set.d3dtext_hud, NULL);
	TwAddVarRW(twBar_SPMisc, "Disable bad weapons", TW_TYPE_BOOLCPP, &cheat_state->_generic.weapon_disable, NULL);
	TwAddVarRW(twBar_SPMisc, "Trailer support", TW_TYPE_BOOLCPP, &set.trailer_support, NULL);

	// Misc. -> HUD
	TwAddVarRW(twBar_SPMisc, "HUD Draw bottom bar", TW_TYPE_BOOLCPP, &set.hud_draw_bar, " group='HUD' ");
	TwAddVarRW(twBar_SPMisc, "HUD Render text shadows", TW_TYPE_BOOLCPP, &set.render_text_shadows, " group='HUD' ");
	TwAddVarRW(twBar_SPMisc, "HUD Inv", TW_TYPE_BOOLCPP, &set.hud_indicator_inv, " group='HUD' ");
	TwAddVarRW(twBar_SPMisc, "HUD Weapon", TW_TYPE_BOOLCPP, &set.hud_indicator_weapon, " group='HUD' ");
	TwAddVarRW(twBar_SPMisc, "HUD Money", TW_TYPE_BOOLCPP, &set.hud_indicator_money, " group='HUD' ");
	TwAddVarRW(twBar_SPMisc, "HUD Freeze", TW_TYPE_BOOLCPP, &set.hud_indicator_freeze, " group='HUD' ");
	TwAddVarRW(twBar_SPMisc, "HUD In vehicle AirBrk", TW_TYPE_BOOLCPP, &set.hud_indicator_inveh_airbrk, " group='HUD' ");
	TwAddVarRW(twBar_SPMisc, "HUD In vehicle Stick", TW_TYPE_BOOLCPP, &set.hud_indicator_inveh_stick, " group='HUD' ");
	TwAddVarRW(twBar_SPMisc, "HUD In vehicle BrkDance", TW_TYPE_BOOLCPP, &set.hud_indicator_inveh_brkdance, " group='HUD' ");
	TwAddVarRW(twBar_SPMisc, "HUD In vehicle Spider", TW_TYPE_BOOLCPP, &set.hud_indicator_inveh_spider, " group='HUD' ");
	TwAddVarRW(twBar_SPMisc, "HUD In vehicle Fly", TW_TYPE_BOOLCPP, &set.hud_indicator_inveh_fly, " group='HUD' ");
	TwAddVarRW(twBar_SPMisc, "HUD On foot AirBrk", TW_TYPE_BOOLCPP, &set.hud_indicator_onfoot_airbrk, " group='HUD' ");
	TwAddVarRW(twBar_SPMisc, "HUD On foot Stick", TW_TYPE_BOOLCPP, &set.hud_indicator_onfoot_stick, " group='HUD' ");
	TwAddVarRW(twBar_SPMisc, "HUD On foot Fly", TW_TYPE_BOOLCPP, &set.hud_indicator_onfoot_fly, " group='HUD' ");
	TwAddVarRW(twBar_SPMisc, "HUD Aim", TW_TYPE_BOOLCPP, &set.hud_indicator_onfoot_aim, " group='HUD' ");
	TwAddVarRW(twBar_SPMisc, "HUD Position", TW_TYPE_BOOLCPP, &set.hud_indicator_pos, " group='HUD' ");
	TwAddVarRW(twBar_SPMisc, "HUD FPS", TW_TYPE_BOOLCPP, &set.hud_fps_draw, " group='HUD' ");
	TwAddVarRW(twBar_SPMisc, "HUD Toggle left bottom bars", TW_TYPE_BOOLCPP, &set.left_bottom_bars_enable, " group='HUD' ");
	TwDefine(" GTA_Misc/HUD opened='false' ");
			
//		 TwAddVarRW(twBar_SPsamprp, "Spec ID:", TW_TYPE_INT32, &set.idplayer2," group='Main' ");
//		TwAddVarRW(twBar_SPsamprp, "Spec Player", TW_TYPE_BOOLCPP, &cheat_state->_generic.infobar, " group='Main' ");
//		TwAddVarRW(twBar_SPsamprp, "CarGun Master [J]", TW_TYPE_BOOLCPP, &cheat_state->_generic.cargunmaster, " group='Main' ");
//		
//		TwAddVarRW(twBar_SPsamprp, "AntiSlapGM", TW_TYPE_BOOLCPP, &cheat_state->_generic.antispal, " group='Main' ");
//		TwAddVarRW(twBar_SPsamprp, "AFi", TW_TYPE_BOOLCPP, &cheat_state->_generic.antispal1, " group='Main' ");
//		TwAddVarRW(twBar_SPsamprp, "Damager", TW_TYPE_BOOLCPP, &cheat_state->_generic.autokicks1, " group='Main' ");
//			TwAddVarRW(twBar_SPsamprp, "Freeze All Players", TW_TYPE_BOOLCPP, &cheat_state->_generic.autokicks1, " group='Main' ");
//		TwAddVarRW(twBar_SPsamprp, "SuperGun", TW_TYPE_BOOLCPP, &cheat_state->_generic.infobar1," group='Main' ");
//		TwAddVarRW(twBar_SPsamprp, "Slot: 1", TW_TYPE_INT32, &set.eweaponslot_2, " group='Main' ");
//			TwAddVarRW(twBar_SPsamprp, "Slot: 2",TW_TYPE_INT32, &set.eweaponslot_3, " group='Main' ");
//			   TwAddButton(twBar_SPsamprp, "RepairVehicle", restoreHealth1, NULL, " group='Main' ");
//			TwAddVarRW(twBar_SPsamprp, "AutoKicker (inCar)", TW_TYPE_BOOLCPP, &cheat_state->_generic.autokicks," group='Main' ");
//			TwAddVarRW(twBar_SPsamprp, "CarShot", TW_TYPE_BOOLCPP, &cheat_state->_generic. cardrive," group='Main' ");
//			TwAddVarRW(twBar_SPsamprp, "House Cheker", TW_TYPE_BOOLCPP, &cheat_state->_generic. house," group='Main' ");
//					TwAddVarRW(twBar_SPsamprp, "Lagger [inRun]", TW_TYPE_BOOLCPP, &cheat_state->_generic. lagger," group='Main' ");
//					TwAddVarRW(twBar_SPsamprp, "CordMaster", TW_TYPE_BOOLCPP, &cheat_state->_generic. coordmaster," group='Main' ");
//					TwAddVarRW(twBar_SPsamprp, "NoDeath", TW_TYPE_BOOLCPP, &cheat_state->_generic. nodeath," group='Main' ");
//					TwAddVarRW(twBar_SPsamprp, "Crazy Vehicle", TW_TYPE_BOOLCPP, &cheat_state->_generic. crazycar," group='Main' ");
//		
//			TwAddVarRW(twBar_SPsamprp, "Pizdarvanka (inCar)", TW_TYPE_BOOLCPP, &cheat_state->_generic.doublegun," group='Main' ");
//			TwAddVarRW(twBar_SPsamprp, "Pizdarvanka (inRun)", TW_TYPE_BOOLCPP, &cheat_state->_generic.doublegun228," group='Main' ");
//			
//		
//			
//			/*	TwAddVarRW(twBar_SPsamprp, "Cargun 1", TW_TYPE_BOOLCPP, &cheat_state->_generic.cargun1," group='Main' ");	
//				TwAddVarRW(twBar_SPsamprp, "Cargun 2", TW_TYPE_BOOLCPP, &cheat_state->_generic.cargun2," group='Main' ");*/
//			TwAddVarRW(twBar_SPsamprp, "Vehicle: ",TW_TYPE_INT32, &set.curet, " group='Inviseble' ");
//			TwAddVarRW(twBar_SPsamprp, "Spawn Vehicle", TW_TYPE_BOOLCPP, &cheat_state->_generic.dtext1," group='Inviseble' ");
//			TwAddVarRW(twBar_SPsamprp, "Invesible (inPed)", TW_TYPE_BOOLCPP, &cheat_state->_generic.dtext," group='Inviseble' ");
//			TwAddVarRW(twBar_SPsamprp, "Invesible (inCar)", TW_TYPE_BOOLCPP, &cheat_state->_generic.massinosht," group='Inviseble' ");
//			TwAddVarRW(twBar_SPsamprp, "Ferma (inTP)", TW_TYPE_BOOLCPP, &cheat_state->_generic.botferma," group='Bots' ");
//				TwAddVarRW(twBar_SPsamprp, "Ferma (inRun)", TW_TYPE_BOOLCPP, &cheat_state->_generic.botferma1," group='Bots' ");
//					TwAddVarRW(twBar_SPsamprp, "Boxer ", TW_TYPE_BOOLCPP, &cheat_state->_generic.cfffff," group='Bots' ");
//					TwAddVarRW(twBar_SPsamprp, "Loader Run", TW_TYPE_BOOLCPP, &cheat_state->_generic.gruzchik228," group='Bots' ");
////						TwAddButton(twBar_SPsamprp, "Loader", loader, NULL, " group='Bots' ");
//					 TwAddVarRW(twBar_SPsamprp, "Loader Meshkov:", TW_TYPE_INT32, &set.meshok," group='Bots' ");
//						TwAddVarRW(twBar_SPsamprp, "Gribsik ", TW_TYPE_BOOLCPP, &cheat_state->_generic.antispal11," group='Bots' ");
//								//TwAddVarRW(twBar_SPsamprp, "Loader", TW_TYPE_BOOLCPP, &cheat_state->_generic.	bot," group='Bots' ");
//									
//				TwAddVarRW(twBar_SPsamprp, "Shaxter", TW_TYPE_BOOLCPP, &cheat_state->_generic.	shaxter," group='Bots' ");
//					TwAddVarRW(twBar_SPsamprp, "SkillMaster", TW_TYPE_BOOLCPP, &cheat_state->_generic.skillmaster," group='Skill' ");
//					TwAddVarRW(twBar_SPsamprp, "SM Delay:", TW_TYPE_INT32, &set.smdelay, " group='Skill' ");
//					
//			/*		TwAddButton(twBar_SPsamprp, "WeaponUpdate", restoreHealth11, NULL, " group='WeaponUpdateSync' ");
//					TwAddVarRW(twBar_SPsamprp, "Slot:", TW_TYPE_INT32, &set.slot, " group='WeaponUpdateSync' ");
//					TwAddVarRW(twBar_SPsamprp, "Ammo:", TW_TYPE_INT32, &set.ammoff, " group='WeaponUpdateSync' ");
//					TwAddVarRW(twBar_SPsamprp, "Weaponid:", TW_TYPE_INT32, &set.weponid, " group='WeaponUpdateSync' ");*/
//						TwAddVarRW(twBar_SPsamprp, "Pizdarvanka (inCar)", TW_TYPE_BOOLCPP, &cheat_state->_generic.doublegun," group='Pizdarvankacar' ");
//						TwAddVarRW(twBar_SPsamprp, "PizdarvankaCar Speed: ",TW_TYPE_INT32, &set.florizspedpiz, " group='Pizdarvankacar' ");
//						
//			TwAddVarRW(twBar_SPsamprp, "Pizdarvanka (inRun)", TW_TYPE_BOOLCPP, &cheat_state->_generic.doublegun228," group='Pizdarvankarun' ");
//						TwAddVarRW(twBar_SPsamprp, "PizdarvankaRun Time: ",TW_TYPE_INT32, &set.flotirsetime, " group='Pizdarvankarun' ");
//							TwAddVarRW(twBar_SPsamprp, "PizdarvankaRun Speed: ",TW_TYPE_INT32, &set.flotirse, " group='Pizdarvankarun' ");
//							TwAddVarRW(twBar_SPsamprp, "OnfootSyncRun", TW_TYPE_BOOLCPP, &cheat_state->_generic.massinosht," group='Pizdarvankarun' ");
//							TwAddButton(twBar_SPsamprp, "thrw_barl_thrw", restoreHealth11, NULL, " group='NewAnim' ");
//							TwAddButton(twBar_SPsamprp, "dnce_M_e", dancing, NULL, " group='NewAnim' ");
//							TwAddButton(twBar_SPsamprp, "EAT_Vomit_P", food, NULL, " group='NewAnim' ");
//							TwAddButton(twBar_SPsamprp, "Barcustom_order", bar, NULL, " group='NewAnim' ");
//							TwAddButton(twBar_SPsamprp, "Barserve_order", bar1, NULL, " group='NewAnim' ");
//							TwAddButton(twBar_SPsamprp, "Bat_1", baseball, NULL, " group='NewAnim' ");
//
//							TwAddButton(twBar_SPsamprp, "Bat_2", baseball1, NULL, " group='NewAnim' ");
//
//								TwAddButton(twBar_SPsamprp, "Bat_3", baseball2, NULL, " group='NewAnim' ");
//								TwAddButton(twBar_SPsamprp, "Scratchballs_01", misc, NULL, " group='NewAnim' ");
//								TwAddButton(twBar_SPsamprp, "KAT_Throw_K", misc1, NULL, " group='NewAnim' ");
//								TwAddButton(twBar_SPsamprp, "Plane_hijack", misc2, NULL, " group='NewAnim' ");
//								TwAddButton(twBar_SPsamprp, "plyr_shkhead", misc3, NULL, " group='NewAnim' ");
//								TwAddButton(twBar_SPsamprp, "Door_Kick", police, NULL, " group='NewAnim' ");
//								TwAddVarRW(twBar_SPsamprp, "Autodriver", TW_TYPE_BOOLCPP, &cheat_state->_generic.autodriver,NULL);
//									TwAddVarRW(twBar_SPsamprp, "Autodriver", TW_TYPE_BOOLCPP, &cheat_state->_generic.autodriver,NULL);
//									TwAddVarRW(twBar_SPsamprp, "VertoMats", TW_TYPE_BOOLCPP, &cheat_state->_generic.vertomats,NULL);
//									TwAddVarRW(twBar_SPsamprp, "Matsbot", TW_TYPE_BOOLCPP, &cheat_state->_generic.	matsbot,NULL);
//								TwAddVarRW(twBar_SPsamprp, "Fisher", TW_TYPE_BOOLCPP, &cheat_state->_generic.	fisher,NULL);
//								TwAddVarRW(twBar_SPsamprp, "No Reload", TW_TYPE_BOOLCPP, &cheat_state->_generic.noreload,NULL);
//								TwAddVarRW(twBar_SPsamprp, "Tank Mode", TW_TYPE_BOOLCPP, &cheat_state->_generic.tankmode,NULL);
//							TwAddVarRW(twBar_SPsamprp, "BanyHop", TW_TYPE_BOOLCPP, &cheat_state->_generic.bany,NULL);
//							
//								TwAddButton(twBar_SPsamprp, "USE OLD MENU", loader2, NULL, NULL);
							/*	TwAddVarRW(twBar_SPsamprp, "DamageAmplifier", TW_TYPE_BOOLCPP, &cheat_state->_generic.damageamplifer," group='DamageAmplifier' ");
			TwAddVarRW(twBar_SPsamprp, "AK-47:", TW_TYPE_INT32, &set.weponid, " group='DamageAmplifier' ");
				TwAddVarRW(twBar_SPsamprp, "M4:", TW_TYPE_INT32, &set.weponid, " group='DamageAmplifier' ");*/
			/*	TwDefine("samprp/Pizdarvankarun opened='false' ");
				TwDefine("samprp/Pizdarvankacar opened='false' ");
					TwDefine("samprp/NewAnim opened='false' ");
					TwDefine("samprp/Skill opened='false' ");
						TwDefine("samprp/Bots opened='false' ");
						TwDefine("samprp/Inviseble opened='false' ");
						TwDefine("samprp/Main opened='false' ");*/
					
			          /////////////////////////////////////////////////////////////////////////////////////////////
				/*		TwAddVarRW(twBar_SPdmsp, "Invert Fly",TW_TYPE_BOOLCPP, &cheat_state->_generic.spdhack2, " group='Main' ");
					TwAddVarRW(twBar_SPdmsp, "CarSpam Delay:", TW_TYPE_INT32, &set.smdelay, " group='Main' ");
						TwAddVarRW(twBar_SPdmsp, "CarSpam [ Sync ]",TW_TYPE_BOOLCPP, &cheat_state->_generic.carspam, " group='Main' ");
					TwAddVarRW(twBar_SPdmsp, "CarFucker",TW_TYPE_BOOLCPP, &cheat_state->_generic.carfucker, " group='Main' "); 
					TwAddVarRW(twBar_SPdmsp, "CarFolow Delay: ",TW_TYPE_INT32, &set.florizspedpiz, " group='Main' ");
					TwAddVarRW(twBar_SPdmsp, "CarFolow",TW_TYPE_BOOLCPP, &cheat_state->_generic.colorice1, " group='Main' "); 
					TwAddVarRW(twBar_SPdmsp, "CarBhide Delay:", TW_TYPE_INT32, &set.meshok," group='Main' ");
					TwAddVarRW(twBar_SPdmsp, "CarBhide",TW_TYPE_BOOLCPP, &cheat_state->_generic.colorice2, " group='Main' "); 
					TwAddVarRW(twBar_SPdmsp, "CarBlueGas Delay:", TW_TYPE_INT32, &set.slot, " group='Main' ");
					TwAddVarRW(twBar_SPdmsp, "CarBlueGas",TW_TYPE_BOOLCPP, &cheat_state->_generic.colorice3, " group='Main' "); 
					
					TwAddVarRW(twBar_SPdmsp, "CarDestroad All",TW_TYPE_BOOLCPP, &cheat_state->_generic.colorice, " group='Main' "); 
					TwAddVarRW(twBar_SPdmsp, "Colorice all color",TW_TYPE_BOOLCPP, &cheat_state->_generic.destroyand, " group='Main' "); 
						TwAddVarRW(twBar_SPdmsp, "CarGun Master", TW_TYPE_BOOLCPP, &cheat_state->_generic.cargunmaster, " group='Main' ");*/
					//////////////////////////////////////////////////////////////////////////////////////////////////
				TwAddVarRW(twBar_SPMisc, "FPS Limit", TW_TYPE_INT32, &set.fps_limit, " label='FPS Limit' min=10 max=100 ");
				
	TwAddButton(twBar_SPMisc, "Toggle windowed mode", menuToggleWndMode, NULL, NULL);	
	TwDefine(" GTA_Misc/Misc opened='false' ");
	
	// GTA Patches
	for(i = 0; i < INI_PATCHES_MAX; i++)
	{
		if(set.patch[i].name == NULL) continue;
		TwAddVarCB(twBar_SPPatches, set.patch[i].name, TW_TYPE_BOOLCPP, SetPatchCallback, GetPatchCallback, (void *)&set.patch[i], NULL);
	}
	TwDefine(" GTA_Patches opened='false' ");

	// SAMP
	if(g_dwSAMP_Addr != NULL)
	{
		// Players
		// to be populated by the hook
		TwDefine(" Players valueswidth=140 opened='false' ");

		// Servers
		TwAddVarRW(twBar_SAMPFavServers, "Keep your current nickname", TW_TYPE_BOOLCPP, &set.use_current_name, NULL);
		TwAddVarRW(twBar_SAMPFavServers, "Rejoin delay (ms)", TW_TYPE_INT32, &set.rejoin_delay, " min=25 max=999999999 ");
		TwAddButton(twBar_SAMPFavServers, " ", NULL, NULL, NULL);
		for(i = 0; i < INI_SERVERS_MAX; i++)
		{
			if(set.server[i].server_name == NULL) continue;
			TwAddButton(twBar_SAMPFavServers, set.server[i].server_name, joinServer, (void *)&set.server[i], NULL);
		}
		TwDefine(" Favorite_servers opened='false' ");
	}

	if(g_dwSAMP_Addr != NULL)
	{
		for(i = 0; i < 45; i++)
		{
			snprintf(buf, sizeof(buf), " label='%s' group='Fake_Kill_Weapon' ", fk_weapons[i].Label);
			TwAddButton(twBar_SAMPMisc, NULL, changeFakeKillWeapon, &fk_weapons[i].Value, buf);
		}
		TwDefine(" SA:MP_Misc/Fake_Kill_Weapon label='Fake kill weapon' opened='false' ");

		TwAddVarRW(twBar_SAMPMisc, "Chat lines", TW_TYPE_INT32, &set.d3dtext_chat_lines, " min=0 max=100 ");

		for(i = 0; i < 5; i++)
		{
			snprintf(buf, sizeof(buf), " label='%s' group='Game_states' ", game_states[i].Label);
			TwAddButton(twBar_SAMPMisc, NULL, changeGS, &game_states[i].Value, buf);
		}
		TwDefine(" SA:MP_Misc/Game_states label='Game states' opened='false' ");

		for(i = 0; i < 17; i++)
		{
			snprintf(buf, sizeof(buf), " label='%s' group='Special_actions' ", special_actions[i].Label);
			TwAddButton(twBar_SAMPMisc, NULL, changeSpecialAction, &special_actions[i].Value, buf);
		}
		TwDefine(" SA:MP_Misc/Special_actions label='Special actions' opened='false' ");

		TwAddButton(twBar_SAMPMisc, "Drunk", getDrunk, NULL, NULL);

		iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) + 100;
		iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) + 100;
		TwAddButton(twBar_SAMPMisc, "SA:MP_Objects", SAMPObjectsLinker, NULL, " label='SA:MP objects' ");
		sprintf(menuParameters," SA:MP_Objects label='mod_sa -> SA:MP Objects' color='150 0 0' position='%d %d' size='405 235' fontsize='2' ", iMainMenuPosX, iMainMenuPosY);
		TwDefine(menuParameters);

		iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) + 125;
		iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) + 125;
		TwAddButton(twBar_SAMPMisc, "SA:MP_Pickups", SAMPPickupsLinker, NULL, " label='SA:MP pickups' ");
		sprintf(menuParameters," SA:MP_Pickups label='mod_sa -> SA:MP Pickups' color='150 0 0' position='%d %d' size='405 235' fontsize='2' ", iMainMenuPosX, iMainMenuPosY);
		TwDefine(menuParameters);

		TwAddButton(twBar_SAMPMisc, "Load M0D-commands", loadM0dCommands, NULL, NULL);


		TwDefine(" SA:MP_Misc valueswidth=140 ");
		
		// SA:MP Patches
		for(i = 0; i < INI_SAMPPATCHES_MAX; i++)
		{
			if(set.sampPatch[i].name == NULL) continue;
			TwAddVarCB(twBar_SAMPPatches, set.sampPatch[i].name, TW_TYPE_BOOLCPP, SetPatchCallback, GetPatchCallback, (void *)&set.sampPatch[i], NULL);
		}
		
	}
}
