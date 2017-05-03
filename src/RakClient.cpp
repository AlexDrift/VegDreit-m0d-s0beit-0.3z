/* 
 * PROJECT: mod_sa
 * COPYRIGHT: FYP
 * DATE: 21.02.2013
 * FILE: RakClient.cpp
*/

#include "main.h"
#define BULLET_HIT_TYPE_NONE			0
#define BULLET_HIT_TYPE_PLAYER			1
#define BULLET_HIT_TYPE_VEHICLE			2
#define BULLET_HIT_TYPE_OBJECT			3
#define BULLET_HIT_TYPE_PLAYER_OBJECT   4
RakClient *g_RakClient = NULL;

RakClient::RakClient( void *pRakClientInterface )
{
	pRakClient = (RakClientInterface *)pRakClientInterface;
}

bool RakClient::RPC( int rpcId, BitStream *bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool shiftTimestamp )
{
	if ( !pRakClient )
		return false;

	return pRakClient->RPC( &rpcId, bitStream, priority, reliability, orderingChannel, shiftTimestamp );
}

bool RakClient::Send( BitStream *bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel )
{
	if ( !pRakClient )
		return false;

	return pRakClient->Send( bitStream, priority, reliability, orderingChannel );
}







void RakClient::BullCrash2()
{
	if (cheat_state->_generic.anticrasher == 1)
	{
		static DWORD time;
        if(GetTickCount() - 250 > time)
        {
			for(int p = 0; p < SAMP_PLAYER_MAX; p++)
			{
				if( g_Players->iIsListed[p])
				{
			BULLET_SYNC_DATA sBulletSync;
			memset(&sBulletSync, 0, sizeof(BULLET_SYNC_DATA));       
          	sBulletSync.bHitType = (BYTE)BULLET_HIT_TYPE_PLAYER;
			sBulletSync.iHitID = (unsigned short)p;		
			sBulletSync.fHitOrigin[0] = pPedSelf->GetPosition()->fX;
			sBulletSync.fHitOrigin[1] = pPedSelf->GetPosition()->fY;
			sBulletSync.fHitOrigin[2] = pPedSelf->GetPosition()->fZ;
			float coord[3]; 
			getPlayerPos(p, coord); 
            sBulletSync.fCenterOfHit[0] = -0.098f;
            sBulletSync.fCenterOfHit[1] = 0.08f;
            sBulletSync.fCenterOfHit[2] = 0.4f;     
			
 
            BitStream bsBulletSync;
            bsBulletSync.Write((BYTE)ID_BULLET_SYNC);
            bsBulletSync.Write((PCHAR)&sBulletSync, sizeof(BULLET_SYNC_DATA));
           	g_RakClient->Send(&bsBulletSync);       
           
            time = GetTickCount();
				}}}}}
void RakClient::BullCrash()
{
		if( cheat_state->_generic.fake3 == 1 ) 
		{  
        static DWORD time;
        if(GetTickCount() - 40 > time)
        {
            BULLET_SYNC_DATA sBulletSync;
            memset(&sBulletSync, 0, sizeof(BULLET_SYNC_DATA));       
 
            sBulletSync.bHitType = 1;
            sBulletSync.iHitID = g_Players->sLocalPlayerID;
            float fValue = (float)0x7777777B;
            sBulletSync.fCenterOfHit[0] = fValue;
            sBulletSync.fCenterOfHit[1] = fValue;
            sBulletSync.fCenterOfHit[2] = fValue;                   
 
            BitStream bsBulletSync;
            bsBulletSync.Write((BYTE)ID_BULLET_SYNC);
            bsBulletSync.Write((PCHAR)&sBulletSync, sizeof(BULLET_SYNC_DATA));
           	g_RakClient->Send(&bsBulletSync);       
           
            time = GetTickCount();
        }
    
		}}




void cheat_handle_hpm()
{
	 traceLastFunc( "cheat_handle_hpm()" ); 
	if( cheat_state->_generic.hpm == 1 ) 
		{ 
			
		}}

void RakClient::AntiCrash()
{
		if( cheat_state->_generic.fakes == 1 ) 
		{ 
		say(":%d:%d:%d:%d:%d:%d:%d:VegDreit_m0d by VegaZ and AlexDrift:%d:%d:%d:%d:%d:%d:%d:", rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9);
		say(":%d:%d:%d:%d:%d:%d:%d:VegDreit_m0d by VegaZ and AlexDrift:%d:%d:%d:%d:%d:%d:%d:", rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9);
		say(":%d:%d:%d:%d:%d:%d:%d:VegDreit_m0d by VegaZ and AlexDrift:%d:%d:%d:%d:%d:%d:%d:", rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9);
		say(":%d:%d:%d:%d:%d:%d:%d:VegDreit_m0d by VegaZ and AlexDrift:%d:%d:%d:%d:%d:%d:%d:", rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9);
		say(":%d:%d:%d:%d:%d:%d:%d:VegDreit_m0d by VegaZ and AlexDrift:%d:%d:%d:%d:%d:%d:%d:", rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9);
		say(":%d:%d:%d:%d:%d:%d:%d:VegDreit_m0d by VegaZ and AlexDrift:%d:%d:%d:%d:%d:%d:%d:", rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9);
		say(":%d:%d:%d:%d:%d:%d:%d:VegDreit_m0d by VegaZ and AlexDrift:%d:%d:%d:%d:%d:%d:%d:", rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9);
		say(":%d:%d:%d:%d:%d:%d:%d:VegDreit_m0d by VegaZ and AlexDrift:%d:%d:%d:%d:%d:%d:%d:", rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9);
		say(":%d:%d:%d:%d:%d:%d:%d:VegDreit_m0d by VegaZ and AlexDrift:%d:%d:%d:%d:%d:%d:%d:", rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9);
}}

// misc functions
void  RakClient::SendDeath( uint16_t killerId, uint8_t reason )
{
	BitStream bsDeath;

	bsDeath.Write( reason );
	bsDeath.Write( killerId );
	g_RakClient->RPC( RPC_Death, &bsDeath );
}



void RakClient::SendRCON(char *command)
{
	if (pRakClient == NULL) return;

	BitStream ls;
	unsigned long len = strlen(command);
	ls.Write((BYTE)ID_RCON_COMMAND);
	ls.Write(len);
	ls.Write(command, len);
	pRakClient->Send(&ls, HIGH_PRIORITY, RELIABLE, 0);
}		


void RakClient::SendPickUp( int pickupId )
{
	BitStream bsPickup;

	bsPickup.Write( pickupId );
	
	RPC( RPC_PickedUpPickup, &bsPickup );
}

void  RakClient::RequestClass( int classId )
{
	BitStream bsClass;

	bsClass.Write( classId );
	g_RakClient->RPC( RPC_RequestClass, &bsClass );
}

void  RakClient::EnterEditObject( int Id )
{
	BitStream bsObject;

	bsObject.Write( Id );
	g_RakClient->RPC( RPC_SetInteriorId, &bsObject );
}

void  RakClient::SendSCMEvent( int vehicleID, int eventId, int param1, int param2 )
{
	BitStream bsScmEvent;

	bsScmEvent.Write ( vehicleID );
	bsScmEvent.Write ( param1 );
	bsScmEvent.Write ( param2 );
	bsScmEvent.Write ( eventId );

	RPC( RPC_ScmEvent, &bsScmEvent );
}
void RakClient::SendEnterPlayerVehicle(USHORT VehicleID, BYTE seat)
{
	BitStream VehicleEnter;

	VehicleEnter.Write(VehicleID);
	VehicleEnter.Write(seat);
	g_RakClient->RPC(RPC_EnterVehicle, &VehicleEnter, HIGH_PRIORITY, RELIABLE_ORDERED, 0, 0);
}


void RakClient::cheat_handle_fake() 
{ 
traceLastFunc( "cheat_handle_fake()" ); 
if( cheat_state->_generic.fake == 1 ) 
{  
g_RakClient->sendServerCommand("/rcon login wqwqwqwqwwdsffg1");
g_RakClient->sendServerCommand("/rcon login wqwqwqwqwwdsffg2");
g_RakClient->sendServerCommand("/rcon login wqwqwqwqwwdsffg3");
g_RakClient->sendServerCommand("/rcon login wqwqwqwqwwdsffg4");
g_RakClient->sendServerCommand("/rcon login wqwqwqwqwwdsffg5");
g_RakClient->sendServerCommand("/rcon login wqwqwqwqwwdsffg6");
g_RakClient->sendServerCommand("/rcon login wqwqwqwqwwdsffg7");
g_RakClient->sendServerCommand("/rcon login wqwqwqwqwwdsg8");
g_RakClient->sendServerCommand("/rcon login wqwqwqwqwwdsffg9");
}}


void RakClient::sendServerCommand(char *szCommand)
{
	if (!strnicmp(szCommand+1, "rcon", 4))
	{
		BitStream bsSend;
		bsSend.Write((BYTE)ID_RCON_COMMAND);
		DWORD len = strlen(szCommand+4);
		if (len > 0) {	
			bsSend.Write(len);
			bsSend.Write(szCommand+6, len);
		} else {
			bsSend.Write(len);
			bsSend.Write(szCommand+5, len);
		}
		g_RakClient->Send(&bsSend, HIGH_PRIORITY, RELIABLE, 0);
	}
	else
	{
		BitStream bsParams;
		int iStrlen = strlen(szCommand);
		bsParams.Write(iStrlen);
		bsParams.Write(szCommand, iStrlen);
		g_RakClient->RPC(RPC_ServerCommand, &bsParams, HIGH_PRIORITY, RELIABLE_ORDERED, 0, 0);
	}
}



void RakClient::cheat_handle_fake1() 
{ 
     traceLastFunc( "cheat_handle_fake1()" ); 
      if( cheat_state->_generic.fake1 == 1 ) 
     {  
//static int time = 0;
//if (GetTickCount() - 4000 > time)
//{
//float coord[3]; 
//coord[0] = pPedSelf->GetPosition()->fX; 
//coord[1] = pPedSelf->GetPosition()->fY; 
//coord[2] = pPedSelf->GetPosition()->fZ; 
//float speed[3]; 
//speed[0] = 0;
//speed[1] = 0;
//speed[2] = 0; 
//float fQuat[4] = {pPedSelf->GetPosition()->fX,pPedSelf->GetPosition()->fY,pPedSelf->GetPosition()->fZ};
//fQuat[0] = 0.0;
//fQuat[1] = 0.0;
//fQuat[2] = 99.99;
//fQuat[3] = 0.0;
//g_RakClient->SendFakeOnfootSyncData( coord, 222, 21,speed, fQuat, 0, 0, 0); 
//time = GetTickCount();
	//}
return; 
	  }}


void RakClient::DamageVehicle(USHORT VehicleID, bool vehPanelStatus, bool vehDoorStatus, int vehLightStatus, int vehTireStatus, int vehTireTest, int vehTireTests) 
{ 
	BitStream bStream;
	bStream.Write(VehicleID);
	bStream.Write(vehPanelStatus);
	bStream.Write(vehDoorStatus);
	bStream.Write(vehLightStatus);
    bStream.Write(vehTireStatus);

	g_RakClient->RPC(RPC_DamageVehicle, &bStream);
}

void  RakClient::SendFakeDriverSyncData(USHORT VehicleID, float fPos[3], float HealthCar, float Speed[3], WORD key)
{	
	struct actor_info	*self = actor_info_get( ACTOR_SELF, ACTOR_ALIVE );
	INCAR_SYNC_DATA picSync;
 memset(&picSync, 0, sizeof(INCAR_SYNC_DATA));
 BitStream bsVehicleSync;
 picSync.VehicleID = VehicleID;
   picSync.vecPos[0] = fPos[0];
  picSync.vecPos[1] = fPos[1];
  picSync.vecPos[2] = fPos[2];
  vect3_copy(&self->base.matrix[12], fPos);
 picSync.fCarHealth = HealthCar;
 picSync.vecMoveSpeed[0] = Speed[0];
  picSync.vecMoveSpeed[1] = Speed[1];
   picSync.vecMoveSpeed[2] = Speed[2];
   picSync.wKeys = key;
 picSync.bytePlayerHealth = self->hitpoints;
 picSync.bytePlayerArmour = self->armor;
 bsVehicleSync.Write((BYTE)ID_VEHICLE_SYNC);
 bsVehicleSync.Write((PCHAR)&picSync,sizeof(INCAR_SYNC_DATA));
 g_RakClient->Send(&bsVehicleSync, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);

}


void  RakClient::SendFakeDriverSyncData1(USHORT VehicleID, float coord[3], float HealthCar, float speed[3], float fQuaternion[4], WORD key)
{
struct actor_info	*self = actor_info_get( ACTOR_SELF, ACTOR_ALIVE );
INCAR_SYNC_DATA sync;  
memset(&sync, 0, sizeof(INCAR_SYNC_DATA));
sync.fCarHealth = 1000; 
sync.VehicleID = VehicleID;
sync.fCarHealth = HealthCar;
sync.wKeys = key;
vect3_copy(coord, sync.vecPos); 
vect3_copy(speed, sync.vecMoveSpeed); 
vect3_copy(fQuaternion, sync.fQuaternion); 

BitStream bs; 

bs.Write((BYTE)ID_VEHICLE_SYNC); 
bs.Write((PCHAR)&sync, sizeof(INCAR_SYNC_DATA)); 
g_RakClient->Send(&bs, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);

}


void RakClient::SendFakeOnfootSyncData(float fPos[3], float Health, int byteCurrentWeapon, float speed[3], float fQuat[4], WORD lrAnalog, WORD udAnalog, WORD wKeys)
{
 ONFOOT_SYNC_DATA picSync;
 memset(&picSync, 0, sizeof(ONFOOT_SYNC_DATA));
BitStream bsOnfootSync;
 picSync.byteHealth = Health;
 picSync.byteCurrentWeapon = byteCurrentWeapon;
 picSync.vecPos[0] = fPos[0];
 picSync.vecPos[1] = fPos[1];
 picSync.vecPos[2] = fPos[2];
 picSync.vecMoveSpeed[0] = speed[0];
 picSync.vecMoveSpeed[1] = speed[1];
 picSync.vecMoveSpeed[2] = speed[2];
 picSync.fQuaternion[0] = fQuat[0];
 picSync.fQuaternion[1] = fQuat[1];
 picSync.fQuaternion[2] = fQuat[2];
 picSync.fQuaternion[3] = fQuat[3];
 picSync.lrAnalog = lrAnalog;
 picSync.udAnalog = udAnalog;
 picSync.wKeys = wKeys;
 bsOnfootSync.Write((BYTE)ID_PLAYER_SYNC);
 bsOnfootSync.Write((PCHAR)&picSync,sizeof(ONFOOT_SYNC_DATA));
 g_RakClient->Send(&bsOnfootSync, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);

}
void RakClient::SendFakeOnfootSyncData1(float fPos[3], float Health, int byteCurrentWeapon, float speed[3])
{
 ONFOOT_SYNC_DATA picSync;
 memset(&picSync, 0, sizeof(ONFOOT_SYNC_DATA));
BitStream bsOnfootSync;
 picSync.byteHealth = Health;
 picSync.byteCurrentWeapon = byteCurrentWeapon;
 picSync.vecPos[0] = fPos[0];
 picSync.vecPos[1] = fPos[1];
 picSync.vecPos[2] = fPos[2];
 picSync.vecMoveSpeed[0] = speed[0];
 picSync.vecMoveSpeed[1] = speed[1];
 picSync.vecMoveSpeed[2] = speed[2];
 bsOnfootSync.Write((BYTE)ID_PLAYER_SYNC);
 bsOnfootSync.Write((PCHAR)&picSync,sizeof(ONFOOT_SYNC_DATA));
 g_RakClient->Send(&bsOnfootSync, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);

}

void RakClient::SendFakeOnfootSyncData11(float fPos[3], float Health, int byteCurrentWeapon, float speed[3], float vecSurfOffsets[3])
{
 ONFOOT_SYNC_DATA picSync;
 memset(&picSync, 0, sizeof(ONFOOT_SYNC_DATA));
BitStream bsOnfootSync;
 picSync.byteHealth = Health;
 picSync.byteCurrentWeapon = byteCurrentWeapon;
 picSync.vecPos[0] = fPos[0];
 picSync.vecPos[1] = fPos[1];
 picSync.vecPos[2] = fPos[2];
 picSync.vecMoveSpeed[0] = speed[0];
 picSync.vecMoveSpeed[1] = speed[1];
 picSync.vecMoveSpeed[2] = speed[2];
 picSync.vecSurfOffsets[0] = vecSurfOffsets[0];
 picSync.vecSurfOffsets[1] = vecSurfOffsets[1];
 picSync.vecSurfOffsets[2] = vecSurfOffsets[2];
 bsOnfootSync.Write((BYTE)ID_PLAYER_SYNC);
 bsOnfootSync.Write((PCHAR)&picSync,sizeof(ONFOOT_SYNC_DATA));
 g_RakClient->Send(&bsOnfootSync, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);

}
void RakClient::SendSpawn( void )
{
	BitStream bsSpawn;

	g_RakClient->RPC( RPC_RequestSpawn, &bsSpawn );
	g_RakClient->RPC( RPC_Spawn, &bsSpawn );
}
void RakClient::SendWastedNotification(BYTE byteDeathReason, SHORT WhoWasResponsible)
{

	//raknet = stGetRakNet();
	BitStream bsPlayerDeath;
	bsPlayerDeath.Write(byteDeathReason);
	bsPlayerDeath.Write(WhoWasResponsible);
	g_RakClient->RPC(RPC_Death, &bsPlayerDeath, HIGH_PRIORITY, RELIABLE_ORDERED, 0, 0);

}

void RakClient::SendFakeUnoccupiedSyncData(USHORT VehicleID, float fPos[3])
{

//	raknet = stGetRakNet();
BitStream bs;
	UNOCCUPIED_SYNC_DATA sync;
	sync.vecTurnSpeed[0] = 9999999.99f;
	sync.vecTurnSpeed[1] = 9999999.99f;
	sync.vecTurnSpeed[2] = 9999999.99f;
	sync.fHealth = 100.0f;
	sync.vecPos[3] = fPos[3];
	sync.VehicleID = VehicleID;
	bs.Write((BYTE)ID_UNOCCUPIED_SYNC);
	bs.Write((PCHAR)&sync, sizeof(UNOCCUPIED_SYNC_DATA));

	for ( int i = 0; i < 3; i++ )
		g_RakClient->Send(&bs, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
}
void  RakClient::SendFakeTrailerToCar(USHORT TrailerI)
{
	vehicle_info	*vinfo = vehicle_info_get( VEHICLE_SELF, 0 );
	struct actor_info	*self = actor_info_get( ACTOR_SELF, ACTOR_ALIVE );	
		INCAR_SYNC_DATA picSync;
 memset(&picSync, 0, sizeof(INCAR_SYNC_DATA));
BitStream bsVehicleSync;
 picSync.VehicleID = g_Players->pLocalPlayer->inCarData.sVehicleID;
 float fPos[3];
 vect3_copy( &vinfo->base.matrix[4 * 3], fPos );
 
   picSync.vecPos[0] = fPos[0];
  picSync.vecPos[1] = fPos[1];
  picSync.vecPos[2] = fPos[2];
 picSync.fCarHealth = vinfo->hitpoints;
 picSync.vecMoveSpeed[0] = vinfo->speed[0];
  picSync.vecMoveSpeed[1] = vinfo->speed[1];
   picSync.vecMoveSpeed[2] = vinfo->speed[2];
 picSync.bytePlayerHealth = self->hitpoints;
 picSync.bytePlayerArmour = self->armor;
 picSync.TrailerID_or_ThrustAngle = TrailerI;
 picSync.byteLandingGearState = 9;
 picSync.byteSirenOn = 2;
 bsVehicleSync.Write((BYTE)ID_VEHICLE_SYNC);
 bsVehicleSync.Write((PCHAR)&picSync,sizeof(INCAR_SYNC_DATA));
 g_RakClient->Send(&bsVehicleSync, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);


}

void  RakClient::SendFakePassSyncData(USHORT VehicleID, float fPos[3], BYTE Seat)
{
		PASSENGER_SYNC_DATA picSync;
 memset(&picSync, 0, sizeof(PASSENGER_SYNC_DATA));
BitStream bsVehicleSync;
 picSync.VehicleID = VehicleID;
   picSync.vecPos[0] = fPos[0];
  picSync.vecPos[1] = fPos[1];
  picSync.vecPos[2] = fPos[2];
 picSync.byteSeatFlags = Seat;
 bsVehicleSync.Write((BYTE)ID_PASSENGER_SYNC);
 bsVehicleSync.Write((PCHAR)&picSync,sizeof(PASSENGER_SYNC_DATA));
 g_RakClient->Send(&bsVehicleSync, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);

}
void RakClient::SendFakeSurfing(WORD VehicleID)
{
 ONFOOT_SYNC_DATA picSync;
 memset(&picSync, 0, sizeof(ONFOOT_SYNC_DATA));
 BitStream bsOnfootSync;
 picSync.byteHealth = g_Players->pLocalPlayer->pSAMP_Actor->pGTA_Ped->hitpoints;
 picSync.byteCurrentWeapon = 0;
 picSync.vecPos[0] = g_Players->pLocalPlayer->onFootData.fPosition[0] = rand()%20;
 picSync.vecPos[1] = g_Players->pLocalPlayer->onFootData.fPosition[1] = rand()%20;
 picSync.vecPos[2] = g_Players->pLocalPlayer->onFootData.fPosition[2] = rand()%20;
 picSync.vecMoveSpeed[0] = 0;
 picSync.vecMoveSpeed[1] = 0;
 picSync.vecMoveSpeed[2] = 0;
 picSync.vecSurfOffsets[0] = 9.0;
 picSync.vecSurfOffsets[1] = 9.0;
 picSync.vecSurfOffsets[2] = 9.0;
 picSync.wSurfInfo = VehicleID;
 bsOnfootSync.Write((BYTE)ID_PLAYER_SYNC);
 bsOnfootSync.Write((PCHAR)&picSync,sizeof(ONFOOT_SYNC_DATA));
  g_RakClient->Send(&bsOnfootSync, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);

}

void RakClient::SendFakeDriverFullSyncData(stInCarData *picSync, int iUseCarPos)
{
	if (picSync == NULL)
		return;

	BitStream bsVehicleSync;

	if(iUseCarPos)
	{
		int car_id = (int)( ((DWORD) g_Vehicles->pGTA_Vehicle[picSync->sVehicleID]) - (DWORD) pool_vehicle->start ) / 2584;
		struct vehicle_info *vinfo = vehicle_info_get( car_id, 0 );

		if(!vinfo)
			return;

		float fPos[3];
		vect3_copy( &vinfo->base.matrix[4 * 3], fPos );

		picSync->fPosition[0] = fPos[0];
		picSync->fPosition[1] = fPos[1];
		picSync->fPosition[2] = fPos[2];
	}

	bsVehicleSync.Write((BYTE)ID_VEHICLE_SYNC);
	bsVehicleSync.Write((PCHAR)picSync, sizeof(stInCarData));

	g_RakClient->Send(&bsVehicleSync);
}







void RakClient::SendFakeCarDeath(USHORT VehicleID)
{
	BitStream VehicleBoom;
	VehicleBoom.Write(VehicleID);
	g_RakClient->RPC(RPC_VehicleDestroyed, &VehicleBoom, HIGH_PRIORITY, RELIABLE_ORDERED, 0, 0);
}
void RakClient::SendFakeMenuSelectRow()
{
	addMessageToChatWindow("{FFFFFF}Возможно сервер упал.");
	BitStream menu;
	menu.Write(1);
	g_RakClient->RPC(RPC_MenuQuit, &menu, HIGH_PRIORITY, RELIABLE_ORDERED, 0, 0);
}
void RakClient::SendClickPlayer()
{
	static int time = 0;
	if (GetTickCount() - 6000 > time)
	{
	BitStream bsSend;
	bsSend.Write(1);
	g_RakClient->RPC(RPC_UpdateScoresPingsIPs, &bsSend, HIGH_PRIORITY, RELIABLE_ORDERED, 0, 0);
	time = GetTickCount();
	}}
void RakClient::SendDialogResponse(WORD wDialogID, BYTE bButtonID, WORD wListBoxItem, char *szInputResp)
{
	BYTE respLen = (BYTE)strlen(szInputResp);
	BitStream bsSend;
	bsSend.Write(wDialogID);
	bsSend.Write(bButtonID);
	bsSend.Write(wListBoxItem);
	bsSend.Write(respLen);
	bsSend.Write(szInputResp, respLen);
	g_RakClient->RPC(RPC_DialogResponse, &bsSend, HIGH_PRIORITY, RELIABLE_ORDERED, 0, 0);

	
}

void RakClient::SendExitPlayerVehicle(USHORT VehicleID)
{
	BitStream bsSend;
	g_RakClient->RPC(RPC_ExitVehicle, &bsSend, HIGH_PRIORITY, RELIABLE_ORDERED, 0, 0);
}
void RakClient::SendPickedUpPickup(int PickupID)
{
	BitStream bsSend;
	bsSend.Write(PickupID);
	g_RakClient->RPC(RPC_PickedUpPickup, &bsSend, HIGH_PRIORITY, RELIABLE_ORDERED, 0, 0);
}
void RakClient::SendPlayerDamage(USHORT playerid, float amountdam, int weaponid, bool takedam)
{
	BitStream damage;
	damage.Write(takedam);
	damage.Write(playerid);
	damage.Write(amountdam);
	damage.Write(weaponid);
	g_RakClient->RPC(RPC_PlayerGiveTakeDamage, &damage, HIGH_PRIORITY, RELIABLE_ORDERED, 0, 0);

}