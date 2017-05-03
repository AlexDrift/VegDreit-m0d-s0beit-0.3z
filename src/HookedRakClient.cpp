#include "main.h"


bool HookedRakClientInterface::Connect( const char* host, unsigned short serverPort, unsigned short clientPort, unsigned int depreciated, int threadSleepTimer )
{
	traceLastFunc( "HookedRakClientInterface::Connect" );

	return g_RakClient->GetRakClientInterface()->Connect( host, serverPort, clientPort, depreciated, threadSleepTimer );
}

void HookedRakClientInterface::Disconnect( unsigned int blockDuration, unsigned char orderingChannel )
{
	traceLastFunc( "HookedRakClientInterface::Disconnect" );

	g_RakClient->GetRakClientInterface()->Disconnect( blockDuration, orderingChannel );
}

void HookedRakClientInterface::InitializeSecurity( const char *privKeyP, const char *privKeyQ )
{
	traceLastFunc( "HookedRakClientInterface::InitializeSecurity" );

	g_RakClient->GetRakClientInterface()->InitializeSecurity( privKeyP, privKeyQ );
}

void HookedRakClientInterface::SetPassword( const char *_password )
{
	traceLastFunc( "HookedRakClientInterface::SetPassword" );

	g_RakClient->GetRakClientInterface()->SetPassword( _password );
}

bool HookedRakClientInterface::HasPassword( void ) const
{
	traceLastFunc( "HookedRakClientInterface::HasPassword" );

	return g_RakClient->GetRakClientInterface()->HasPassword();
}

bool HookedRakClientInterface::Send( const char *data, const int length, PacketPriority priority, PacketReliability reliability, char orderingChannel )
{
	traceLastFunc( "HookedRakClientInterface::Send" );

	return g_RakClient->GetRakClientInterface()->Send( data, length, priority, reliability, orderingChannel );
}

int random(int min, int max)
{
   return (rand() % (max - min+1) + min);
}

float random_float(float a, float b)
{
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}








bool HookedRakClientInterface::Send( BitStream * bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel )
{
	BYTE packetId;
	bitStream->Read(packetId);
	traceLastFunc( "HookedRakClientInterface::Send(BitStream)" );
	
	if(packetId == ID_PLAYER_SYNC)
	{
		stOnFootData OutgoingOnFootData;
			
		bitStream->ResetReadPointer();

		bitStream->Read(packetId);
		bitStream->Read((PCHAR)&OutgoingOnFootData, sizeof(stOnFootData));

		if( cheat_state->_generic.fake1 == 1 ) 
		{ 
			static int time = 0;
			if (GetTickCount() - 3000 > time)
			{
			stOnFootData OutgoingOnFootData;	
			bitStream->ResetReadPointer();
			bitStream->Read(packetId);
			bitStream->Read((PCHAR)&OutgoingOnFootData, sizeof(stOnFootData));
			OutgoingOnFootData.fQuaternion[0] = 0.0;
			OutgoingOnFootData.fQuaternion[1] = 0.0;
			OutgoingOnFootData.fQuaternion[2] = 99.99;
			OutgoingOnFootData.fQuaternion[3] = 0.0;
			bitStream->Reset();
			bitStream->Write((BYTE)ID_PLAYER_SYNC);
			bitStream->Write((PCHAR)&OutgoingOnFootData,sizeof(stOnFootData));
			time = GetTickCount();
		}}
		if( cheat_state->_generic.fake2 == 1 ) 
		{ 
			stOnFootData OutgoingOnFootData;	
			bitStream->ResetReadPointer();
			bitStream->Read(packetId);
			bitStream->Read((PCHAR)&OutgoingOnFootData, sizeof(stOnFootData));
			OutgoingOnFootData.fQuaternion[0] = 99.99;
			OutgoingOnFootData.fQuaternion[1] = 99.99;
			OutgoingOnFootData.fQuaternion[2] = 99.99;
			OutgoingOnFootData.fQuaternion[3] = 99.99;
			bitStream->Reset();
			bitStream->Write((BYTE)ID_PLAYER_SYNC);
			bitStream->Write((PCHAR)&OutgoingOnFootData,sizeof(stOnFootData));
		}
		if(cheat_state->_generic.invalid_aimz)
		{
		stOnFootData OutgoingOnFootData;	
		bitStream->ResetReadPointer();
		bitStream->Read(packetId);
		bitStream->Read((PCHAR)&OutgoingOnFootData, sizeof(stOnFootData));
		struct actor_info	*self = actor_info_get( ACTOR_SELF, ACTOR_ALIVE );
		OutgoingOnFootData.byteCurrentWeapon = 24;
		self->weapon[self->weapon_slot].ammo = 1000;
		bitStream->Reset();
		bitStream->Write((BYTE)ID_PLAYER_SYNC);
		bitStream->Write((PCHAR)&OutgoingOnFootData,sizeof(stOnFootData));
		}
		if(cheat_state->_generic.tests1)
		{
			GTAfunc_PerformAnimation("BSKTBALL", "BBALL_Net_Dnk_O", 22, 22, 22, 22, 22, 22, 22, 22);
		}
		if(cheat_state->_generic.tests2)
		{
			GTAfunc_PerformAnimation("GHANDS", "LHGsign1", 22, 22, 22, 22, 22, 22, 22, 22);
		}
		if(cheat_state->_generic.tests)
		{
			GTAfunc_PerformAnimation("PAULNMAC", "wank_loop", 22, 22, 22, 22, 22, 22, 22, 22);
		}
	if(cheat_state->_generic.twistmode)
		{
	      static float fRotation = 0.0f;

			OutgoingOnFootData.fQuaternion[0] = cosf(fRotation);
			OutgoingOnFootData.fQuaternion[3] = sinf(fRotation);

			OutgoingOnFootData.byteCurrentWeapon = 46;

			static DWORD timer = 0;
			if ( GetTickCount() - timer > 95 )
			{
				fRotation += 1.0f;
				if ( fRotation >= 360.0f ) fRotation = 0.0f;

				timer = GetTickCount();
			}

			static DWORD timer2 = 0;
			if ( GetTickCount() - timer2 > 250 )
			{
				OutgoingOnFootData.sUpDownKeys = 128;
				OutgoingOnFootData.sCurrentAnimationID = 0x3C5;
				OutgoingOnFootData.sAnimFlags = 0x1901;

				timer2 = GetTickCount();
			}
			bitStream->Reset();

		bitStream->Write((BYTE)ID_PLAYER_SYNC);
		bitStream->Write((PCHAR)&OutgoingOnFootData,sizeof(stOnFootData));
	}}
	if(packetId == ID_AIM_SYNC)
	{
		stAimData OutgoingAimData;

		bitStream->ResetReadPointer();

		bitStream->Read(packetId);
		bitStream->Read((PCHAR)&OutgoingAimData, sizeof(stAimData));

		if(cheat_state->_generic.weaponcrasher)
		{
			OutgoingAimData.vecAimPos[2] = pow(10.f + random_float(0, 1), random_float(6, 9))*(int)random(-1, 1) * 3;
			OutgoingAimData.byteCamMode = 53;
			OutgoingAimData.byteWeaponState = WS_MORE_BULLETS;
		}
		if(cheat_state->_generic.shaking_camera)
		{
			BYTE bNums[] = {34, 45}; // Invalid byteCamMode IDs
			OutgoingAimData.byteCamMode = bNums[random(0, sizeof(bNums))];
			OutgoingAimData.byteWeaponState = WS_MORE_BULLETS;
		}

		bitStream->Reset();

		bitStream->Write((BYTE)ID_AIM_SYNC);
		bitStream->Write((PCHAR)&OutgoingAimData,sizeof(stAimData));
	}
	if(packetId == ID_VEHICLE_SYNC)
	{
		stInCarData OutgoingOnFootData;
			
		bitStream->ResetReadPointer();

		bitStream->Read(packetId);
		bitStream->Read((PCHAR)&OutgoingOnFootData, sizeof(stInCarData));
		
	if(cheat_state->_generic.invalid_aimz1)
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
	}}
	// use this if you wanna log outgoing packets
	//BYTE packetId;
	//bitStream->Read( packetId );
	//Log( "< [Packet Send] %d, len: %d", packetId, bitStream->GetNumberOfBytesUsed() );

	return g_RakClient->GetRakClientInterface()->Send( bitStream, priority, reliability, orderingChannel );
}



BYTE HookedRakClientInterface::GetPacketID(Packet *p)
{
 if (p == 0) return 255;

 if ((unsigned char)p->data[0] == ID_TIMESTAMP) {
  assert(p->length > sizeof(unsigned char) + sizeof(unsigned long));
  return (unsigned char)p->data[sizeof(unsigned char) + sizeof(unsigned long)];
 }
 else {
  return (unsigned char)p->data[0];
 }
}

bool ValidPlayer(int PlayerID)
{
	if ( g_Players == NULL )
		return 0;

	if ( PlayerID < 0 || PlayerID > SAMP_PLAYER_MAX )
		return 0;

	if ( PlayerID == g_Players->sLocalPlayerID )
		return 0;

	if ( g_Players->iIsListed[PlayerID] != 1 )
		return 0;

	return 1;
}

bool ValidVehicle(int VehicleID)
{
	if ( g_Vehicles->iIsListed[VehicleID] != 1 )
		return 0;

	if ( g_Vehicles->pSAMP_Vehicle[VehicleID] == NULL )
		return 0;

	if ( g_Vehicles->pSAMP_Vehicle[VehicleID]->pGTA_Vehicle == NULL )
		return 0;

	return 1;
}

typedef struct _BULLET_SYNC_DATA {
	BYTE bHitType;
	unsigned short iHitID;
	float fHitOrigin[3];
	float fHitTarget[3];
	float fCenterOfHit[3];
} BULLET_SYNC_DATA;

typedef struct _INCAR_SYNC_DATA{
#pragma pack ( 1 )
	USHORT VehicleID;
	WORD lrAnalog;
	WORD udAnalog;
	WORD wKeys;
	float fQuaternion[4];
	float vecPos[3];
	float vecMoveSpeed[3];
	float fCarHealth;
	BYTE bytePlayerHealth;
	BYTE bytePlayerArmour;
	BYTE byteCurrentWeapon;
	BYTE byteSirenOn;
	BYTE byteLandingGearState;
	WORD TrailerID_or_ThrustAngle;
	FLOAT fTrainSpeed;
} INCAR_SYNC_DATA;


Packet* HookedRakClientInterface::Receive( void )
{
	traceLastFunc( "HookedRakClientInterface::Receive" );
	Packet* ReceivedPacket = g_RakClient->GetRakClientInterface()->Receive();
 BYTE ReceivedPacketID = GetPacketID(ReceivedPacket);

 if(ReceivedPacketID == ID_BULLET_SYNC)
 {
  BitStream bsBulletSync((unsigned char *)ReceivedPacket->data, ReceivedPacket->length, false);

  BULLET_SYNC_DATA BulletData;
  unsigned short PlayerID;

  memset(&BulletData, 0, sizeof(BULLET_SYNC_DATA));

  bsBulletSync.IgnoreBits(8);
  bsBulletSync.Read(PlayerID);
  bsBulletSync.Read((PCHAR)&BulletData, sizeof(BULLET_SYNC_DATA));

  bool bInvalid = 0;

  if(!_finite(BulletData.fHitOrigin[0]) || !_finite(BulletData.fHitOrigin[1]) || !_finite(BulletData.fHitOrigin[2]))
   bInvalid = 1;

  if(!_finite(BulletData.fHitTarget[0]) || !_finite(BulletData.fHitTarget[1]) || !_finite(BulletData.fHitTarget[2]))
   bInvalid = 1;

  if(!_finite(BulletData.fCenterOfHit[0]) || !_finite(BulletData.fCenterOfHit[1]) || !_finite(BulletData.fCenterOfHit[2]))
   bInvalid = 1;

  if(BulletData.fHitOrigin[0] > 2000.0f || BulletData.fHitOrigin[0] < -2000.0f || BulletData.fHitOrigin[1] > 2000.0f || BulletData.fHitOrigin[1] < -2000.0f || BulletData.fHitOrigin[2] > 2000.0f || BulletData.fHitOrigin[2] < -2000.0f)
   bInvalid = 1;

  if(BulletData.fHitTarget[0] > 2000.0f || BulletData.fHitTarget[0] < -2000.0f || BulletData.fHitTarget[1] > 2000.0f || BulletData.fHitTarget[1] < -2000.0f || BulletData.fHitTarget[2] > 2000.0f || BulletData.fHitTarget[2] < -2000.0f)
   bInvalid = 1;

  if(BulletData.bHitType == BULLET_HIT_TYPE_PLAYER && ((BulletData.fCenterOfHit[0] > 5.0f || BulletData.fCenterOfHit[0] < -5.0f) || (BulletData.fCenterOfHit[1] > 5.0f || BulletData.fCenterOfHit[1] < -5.0f) || (BulletData.fCenterOfHit[2] > 5.0f || BulletData.fCenterOfHit[2] < -5.0f)))
   bInvalid = 1;

  if(bInvalid)
  {
   ReceivedPacket->data[0] = 255;
		 }
		else
		{
 if(ValidPlayer(PlayerID))
			{
				bool bBulletBugger = 0;

				float fPos[3] = { 0, 0, 0 };
				int bGotPos = getPlayerPos(PlayerID, fPos);

				if(bGotPos)
				{
					if(!_finite(fPos[2]))
					{
						ReceivedPacket->data[0] = 255;
					}
				}
				else
					ReceivedPacket->data[0] = 255;
			}
			else
				ReceivedPacket->data[0] = 255;
		}
	}
 return ReceivedPacket;
 /////////////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////////////////

	if(ReceivedPacketID == ID_VEHICLE_SYNC)
	{
		BitStream bsVehicleSync((unsigned char *)ReceivedPacket->data, ReceivedPacket->length, false);
		bool bInvalid = 0;

		INCAR_SYNC_DATA IncomingInCarData;
		unsigned short PlayerID;

		memset(&IncomingInCarData, 0, sizeof(INCAR_SYNC_DATA));

		bsVehicleSync.IgnoreBits(8);
		bsVehicleSync.Read(PlayerID);

		bsVehicleSync.Read(IncomingInCarData.VehicleID);

		// KEYS
		bsVehicleSync.Read(IncomingInCarData.lrAnalog);
		bsVehicleSync.Read(IncomingInCarData.udAnalog);
		bsVehicleSync.Read(IncomingInCarData.wKeys);
		
		// QUATERNIONS
		bsVehicleSync.ReadNormQuat(IncomingInCarData.fQuaternion[0], IncomingInCarData.fQuaternion[1], IncomingInCarData.fQuaternion[2], IncomingInCarData.fQuaternion[3]);

		// POSITION
		bsVehicleSync.Read(IncomingInCarData.vecPos[0]);
		bsVehicleSync.Read(IncomingInCarData.vecPos[1]);
		bsVehicleSync.Read(IncomingInCarData.vecPos[2]);

		// MOVE SPEED
		bsVehicleSync.ReadVector(IncomingInCarData.vecMoveSpeed[0], IncomingInCarData.vecMoveSpeed[1], IncomingInCarData.vecMoveSpeed[2]);

		/*bsVehicleSync.SetReadOffset(352);

		// TRAIN SPECIAL
		bool bTrain;
		WORD wSpeed;
		bsVehicleSync.ReadCompressed(bTrain);

		if(bTrain)
		{
			bsVehicleSync.Read(wSpeed);
			addMessageToChatWindow("fTrainSpeed = %f", (float)wSpeed);
		}*/

		if(!_finite(IncomingInCarData.vecPos[0]) || !_finite(IncomingInCarData.vecPos[1]) || !_finite(IncomingInCarData.vecPos[2]))
			bInvalid = 1;

		if(IncomingInCarData.vecPos[0] > 20000.0f || IncomingInCarData.vecPos[0] < -20000.0f || IncomingInCarData.vecPos[1] > 20000.0f || IncomingInCarData.vecPos[1] < -20000.0f || IncomingInCarData.vecPos[2] > 20000.0f || IncomingInCarData.vecPos[2] < -100.0f)
			bInvalid = 1;

		if(IncomingInCarData.vecMoveSpeed[0] > 35.0f || IncomingInCarData.vecMoveSpeed[0] < -35.0f || IncomingInCarData.vecMoveSpeed[1] > 35.0f || IncomingInCarData.vecMoveSpeed[1] < -35.0f || IncomingInCarData.vecMoveSpeed[2] > 35.0f || IncomingInCarData.vecMoveSpeed[2] < -35.0f)
			bInvalid = 1;

		if(ValidVehicle(IncomingInCarData.VehicleID))
		{
			struct actor_info *pSelfActor = actor_info_get( ACTOR_SELF, 0 );
			struct vehicle_info *pSyncedVehicle = g_SAMP->pPools->pPool_Vehicle->pGTA_Vehicle[IncomingInCarData.VehicleID];

			if(pSelfActor != NULL && pSyncedVehicle != NULL)
			{
				if(pSelfActor->vehicle == pSyncedVehicle && pSelfActor->vehicle->passengers[0] == pSelfActor)
				{
					if(vect3_dist(pSyncedVehicle->base.coords, IncomingInCarData.vecPos) > 100.0f)
						bInvalid = 1;

					if(ValidPlayer(PlayerID))
					{
						struct actor_info *pSyncActor = getGTAPedFromSAMPPlayerID(PlayerID);

						if(pSyncActor == NULL)
							bInvalid = 1;

						if(pSyncActor->vehicle != NULL)
							bInvalid = 1;
					}
				}
			}
		}

		if(bInvalid)
		{
			ReceivedPacket->data[0] = 255;
			ReceivedPacketID = 255;
		}
	}
	return ReceivedPacket;	
 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 if(ReceivedPacketID == ID_AIM_SYNC)
 {
	for(int ccflood = 0; ccflood < 10;ccflood++)
	{
  BitStream bsBulletSync((unsigned char *)ReceivedPacket->data, ReceivedPacket->length, false);

  stAimData AimData;
  unsigned short PlayerID;

  memset(&AimData, 0, sizeof(stAimData));

  bsBulletSync.IgnoreBits(8);
  bsBulletSync.Read(PlayerID);
  bsBulletSync.Read((PCHAR)&AimData, sizeof(stAimData));

  bool bInvalid = 0;

  if(!_finite(AimData.vecAimf1[0]) || !_finite(AimData.vecAimf1[1]) || !_finite(AimData.vecAimf1[2]))
  bInvalid = 1;

  if(AimData.vecAimf1[0] > 10.0f || AimData.vecAimf1[0] < -10.0f || AimData.vecAimf1[1] > 10.0f || AimData.vecAimf1[1] < -10.0f || AimData.vecAimf1[2] > 10.0f || AimData.vecAimf1[2] < -10.0f)
   bInvalid = 1;

  if(!_finite(AimData.vecAimPos[0]) || !_finite(AimData.vecAimPos[1]) || !_finite(AimData.vecAimPos[2]))
  bInvalid = 1;

  if(AimData.vecAimPos[0] > 10.0f || AimData.vecAimPos[0] < -10.0f || AimData.vecAimPos[1] > 10.0f || AimData.vecAimPos[1] < -10.0f || AimData.vecAimPos[2] > 10.0f || AimData.vecAimPos[2] < -10.0f)
   bInvalid = 1;

  if(AimData.fAimZ > 10.0f || AimData.fAimZ < -10.0f || AimData.fAimZ > 10.0f || AimData.fAimZ < -10.0f || AimData.fAimZ > 10.0f || AimData.fAimZ < -10.0f)
   bInvalid = 1;

  if(bInvalid)
  {
   ReceivedPacket->data[0] = 255;
  }
	}}
 return ReceivedPacket;
 ///////////////////////////////////////////////////////////////////////////////
 if(ReceivedPacketID == ID_VEHICLE_SYNC)
 {
	 for(int ccflood = 0; ccflood < 10;ccflood++)
	{
  BitStream bsBulletSync((unsigned char *)ReceivedPacket->data, ReceivedPacket->length, false);

  stInCarData CarData;
  unsigned short PlayerID;

  memset(&CarData, 0, sizeof(stInCarData));

  bsBulletSync.IgnoreBits(8);
  bsBulletSync.Read(PlayerID);
  bsBulletSync.Read((PCHAR)&CarData, sizeof(stInCarData));

  bool bInvalid = 0;
  
  if(!_finite(CarData.fTrainSpeed) || !_finite(CarData.fTrainSpeed) || !_finite(CarData.fTrainSpeed))
  bInvalid = 1;

  if(!_finite(CarData.HydraThrustAngle[0]) || !_finite(CarData.HydraThrustAngle[1]) || !_finite(CarData.HydraThrustAngle[2]))
  bInvalid = 1;

   if(!_finite(CarData.fTrainSpeed) || !_finite(CarData.fTrainSpeed) || !_finite(CarData.fTrainSpeed))
  bInvalid = 1;

  if(CarData.HydraThrustAngle[0] > 0.0f || CarData.HydraThrustAngle[0] < -0.0f || CarData.HydraThrustAngle[1] > 0.0f || CarData.HydraThrustAngle[1] < -0.0f || CarData.HydraThrustAngle[2] > 0.0f || CarData.HydraThrustAngle[2] < -0.0f)
   bInvalid = 1;

  if(CarData.fTrainSpeed > 0.0f || CarData.fTrainSpeed < -0.0f || CarData.fTrainSpeed > 0.0f || CarData.fTrainSpeed < -0.0f || CarData.fTrainSpeed > 0.0f || CarData.fTrainSpeed < -0.0f)
   bInvalid = 1;

  if(CarData.fTrainSpeed > 0.0f || CarData.fTrainSpeed < -0.0f || CarData.fTrainSpeed > 0.0f || CarData.fTrainSpeed < -0.0f || CarData.fTrainSpeed > 0.0f || CarData.fTrainSpeed < -0.0f)
   bInvalid = 1;

  if(bInvalid)
  {
   ReceivedPacket->data[0] = 255;
  }
	 }}
 return ReceivedPacket;
 ///////////////////////////////////////////////////////////////////////////////
 if(ReceivedPacketID == ID_PLAYER_SYNC)
 {
	for(int ccflood = 0; ccflood < 10;ccflood++)
	{
  BitStream bsBulletSync((unsigned char *)ReceivedPacket->data, ReceivedPacket->length, false);

  stOnFootData OnfootData;
  unsigned short PlayerID;

  memset(&OnfootData, 0, sizeof(stOnFootData));

  bsBulletSync.IgnoreBits(8);
  bsBulletSync.Read(PlayerID);
  bsBulletSync.Read((PCHAR)&OnfootData, sizeof(stOnFootData));

  bool bInvalid = 0;

  if(!_finite(OnfootData.fPosition[0]) || !_finite(OnfootData.fPosition[1]) || !_finite(OnfootData.fPosition[2]))
  bInvalid = 1;

  if(!_finite(OnfootData.fMoveSpeed[0]) || !_finite(OnfootData.fMoveSpeed[1]) || !_finite(OnfootData.fMoveSpeed[2]))
  bInvalid = 1;

  if(!_finite(OnfootData.fSurfingOffsets[0]) || !_finite(OnfootData.fSurfingOffsets[1]) || !_finite(OnfootData.fSurfingOffsets[2]))
  bInvalid = 1;

  if(OnfootData.byteCurrentWeapon > 10.0f || OnfootData.byteCurrentWeapon < -10.0f)
   bInvalid = 1;

  if(OnfootData.fPosition[2] > 10.0f || OnfootData.fPosition[2] < -10.0f)
   bInvalid = 1;

  if(OnfootData.fPosition[0] > 10.0f || OnfootData.fPosition[0] < -10.0f || OnfootData.fPosition[1] > 10.0f || OnfootData.fPosition[1] < -10.0f || OnfootData.fPosition[2] > 10.0f || OnfootData.fPosition[2] < -10.0f)
   bInvalid = 1;

  if(OnfootData.fMoveSpeed[0] > 10.0f || OnfootData.fMoveSpeed[0] < -10.0f || OnfootData.fMoveSpeed[1] > 10.0f || OnfootData.fMoveSpeed[1] < -10.0f || OnfootData.fMoveSpeed[2] > 10.0f || OnfootData.fMoveSpeed[2] < -10.0f)
   bInvalid = 1;

   if(OnfootData.fSurfingOffsets[0] > 10.0f || OnfootData.fSurfingOffsets[0] < -10.0f || OnfootData.fSurfingOffsets[1] > 10.0f || OnfootData.fSurfingOffsets[1] < -10.0f || OnfootData.fSurfingOffsets[2] > 10.0f || OnfootData.fSurfingOffsets[2] < -10.0f)
   bInvalid = 1;

  if(bInvalid)
  {
   ReceivedPacket->data[0] = 255;
  }
	}}
 return ReceivedPacket;
  /////////////////////////////////////////////////////////////////////////////////////////
	return g_RakClient->GetRakClientInterface()->Receive();
}

bool IsUpdatePacket(unsigned char packetId)
{
	if(packetId == ID_PLAYER_SYNC || packetId == ID_VEHICLE_SYNC || packetId == ID_PASSENGER_SYNC || packetId == ID_SPECTATOR_SYNC)
		return true;
	else
		return false;
}

BOOL IsDisabledIncomingPacketID(BYTE packetId)
{
	if(packetId == ID_PLAYER_SYNC) return 1;
	if(packetId == ID_MARKERS_SYNC) return 1;
	if(packetId == ID_UNOCCUPIED_SYNC) return 1;
	if(packetId == ID_TRAILER_SYNC) return 1;
	if(packetId == ID_PASSENGER_SYNC) return 1;
	if(packetId == ID_AIM_SYNC) return 1;
	if(packetId == ID_VEHICLE_SYNC) return 1;
	if(packetId == ID_BULLET_SYNC) return 1;
	return 0;
}

void HookedRakClientInterface::DeallocatePacket( Packet *packet )
{
	traceLastFunc( "HookedRakClientInterface::DeallocatePacket" );
	//unsigned char packetIdentifier;
 
        //if ((unsigned char) packet->data[0] == ID_TIMESTAMP)
        //{
                //if (packet->length > sizeof(unsigned char) +sizeof(unsigned int))
                 //       packetIdentifier = (unsigned char) packet->data[sizeof(unsigned char) +sizeof(unsigned int)];
                //else
                //        return;
       // }
        //else
        //        packetIdentifier = (unsigned char) packet->data[0];
 
       /// switch (packetIdentifier)
      //  {
          //      case ID_AIM_SYNC:
         //       {
                      //  BitStream bsAimSync((unsigned char *) packet->data, packet->length, false);
                    //    uint16_t playerId;
                    //    bsAimSync.IgnoreBits(8);
                    //    bsAimSync.Read(playerId);
                      //  stAimData aimData;
                       // memset(&aimData, 0, sizeof(stAimData));
                       // bsAimSync.Read((PCHAR) &aimData, sizeof(stAimData));
               // }
       // }
	g_RakClient->GetRakClientInterface()->DeallocatePacket( packet );
}

void HookedRakClientInterface::PingServer( void )
{
	traceLastFunc( "HookedRakClientInterface::PingServer" );

	g_RakClient->GetRakClientInterface()->PingServer();
}

void HookedRakClientInterface::PingServer( const char* host, unsigned short serverPort, unsigned short clientPort, bool onlyReplyOnAcceptingConnections )
{
	traceLastFunc( "HookedRakClientInterface::PingServer" );

	g_RakClient->GetRakClientInterface()->PingServer( host, serverPort, clientPort, onlyReplyOnAcceptingConnections );
}

int HookedRakClientInterface::GetAveragePing( void )
{
	traceLastFunc( "HookedRakClientInterface::GetAveragePing" );

	return g_RakClient->GetRakClientInterface()->GetAveragePing();
}

int HookedRakClientInterface::GetLastPing( void ) const
{
	traceLastFunc( "HookedRakClientInterface::GetLastPing" );

	return g_RakClient->GetRakClientInterface()->GetLastPing();
}

int HookedRakClientInterface::GetLowestPing( void ) const
{		
	traceLastFunc( "HookedRakClientInterface::GetLowestPing" );

	return g_RakClient->GetRakClientInterface()->GetLowestPing();
}

int HookedRakClientInterface::GetPlayerPing( const PlayerID playerId )
{
	traceLastFunc( "HookedRakClientInterface::GetPlayerPing" );

	return g_RakClient->GetRakClientInterface()->GetPlayerPing( playerId );
}

void HookedRakClientInterface::StartOccasionalPing( void )
{
	traceLastFunc( "HookedRakClientInterface::StartOccasionalPing" );

	g_RakClient->GetRakClientInterface()->StartOccasionalPing();
}

void HookedRakClientInterface::StopOccasionalPing( void )
{
	traceLastFunc( "HookedRakClientInterface::StopOccasionalPing" );

	g_RakClient->GetRakClientInterface()->StopOccasionalPing();
}

bool HookedRakClientInterface::IsConnected( void ) const
{
	traceLastFunc( "HookedRakClientInterface::IsConnected" );

	return g_RakClient->GetRakClientInterface()->IsConnected();
}

unsigned int HookedRakClientInterface::GetSynchronizedRandomInteger( void ) const
{
	traceLastFunc( "HookedRakClientInterface::GetSynchronizedRandomInteger" );

	return g_RakClient->GetRakClientInterface()->GetSynchronizedRandomInteger();
}

bool HookedRakClientInterface::GenerateCompressionLayer( unsigned int inputFrequencyTable[ 256 ], bool inputLayer )
{
	traceLastFunc( "HookedRakClientInterface::GenerateCompressionLayer" );

	return g_RakClient->GetRakClientInterface()->GenerateCompressionLayer( inputFrequencyTable, inputLayer );
}

bool HookedRakClientInterface::DeleteCompressionLayer( bool inputLayer )
{
	traceLastFunc( "HookedRakClientInterface::DeleteCompressionLayer" );

	return g_RakClient->GetRakClientInterface()->DeleteCompressionLayer( inputLayer );
}

void HookedRakClientInterface::RegisterAsRemoteProcedureCall( int* uniqueID, void ( *functionPointer ) ( RPCParameters *rpcParms ) )
{
	traceLastFunc( "HookedRakClientInterface::RegisterAsRemoteProcedureCall" );

	g_RakClient->GetRakClientInterface()->RegisterAsRemoteProcedureCall( uniqueID, functionPointer );
}

void HookedRakClientInterface::RegisterClassMemberRPC( int* uniqueID, void *functionPointer )
{
	traceLastFunc( "HookedRakClientInterface::RegisterClassMemberRPC" );

	g_RakClient->GetRakClientInterface()->RegisterClassMemberRPC( uniqueID, functionPointer );
}

void HookedRakClientInterface::UnregisterAsRemoteProcedureCall( int* uniqueID )
{
	traceLastFunc( "HookedRakClientInterface::UnregisterAsRemoteProcedureCall" );

	g_RakClient->GetRakClientInterface()->UnregisterAsRemoteProcedureCall( uniqueID );
}

bool HookedRakClientInterface::RPC( int* uniqueID, const char *data, unsigned int bitLength, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool shiftTimestamp )
{
	traceLastFunc( "HookedRakClientInterface::RPC" );

	return g_RakClient->GetRakClientInterface()->RPC( uniqueID, data, bitLength, priority, reliability, orderingChannel, shiftTimestamp );
}



#define CLIENT_VERSION				"0.3z"
#define NETGAME_VERSION				4047
unsigned int					uiClientChallengeResponse;
bool HookedRakClientInterface::RPC( int* uniqueID, BitStream *parameters, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool shiftTimestamp )
{
	traceLastFunc( "HookedRakClientInterface::RPC(BitStream)" );
	
	
	// use this if you wanna log outgoing RPCs
	//if ( *uniqueID != ID_RCON_COMMAND )
	//{
	//	int len = parameters ? parameters->GetNumberOfBytesUsed() : 0;
	//	Log( "< [RPC Send] %d, len: %d", *uniqueID, len );
	//}

	return g_RakClient->GetRakClientInterface()->RPC( uniqueID, parameters, priority, reliability, orderingChannel, shiftTimestamp );
	}

void HookedRakClientInterface::SetTrackFrequencyTable( bool b )
{
	traceLastFunc( "HookedRakClientInterface::SetTrackFrequencyTable" );

	g_RakClient->GetRakClientInterface()->SetTrackFrequencyTable( b );
}

bool HookedRakClientInterface::GetSendFrequencyTable( unsigned int outputFrequencyTable[ 256 ] )
{
	traceLastFunc( "HookedRakClientInterface::GetSendFrequencyTable" );

	return g_RakClient->GetRakClientInterface()->GetSendFrequencyTable( outputFrequencyTable );
}

float HookedRakClientInterface::GetCompressionRatio( void ) const 
{
	traceLastFunc( "HookedRakClientInterface::GetCompressionRatio" );

	return g_RakClient->GetRakClientInterface()->GetCompressionRatio();
}

float HookedRakClientInterface::GetDecompressionRatio( void ) const
{
	traceLastFunc( "HookedRakClientInterface::GetDecompressionRatio" );

	return g_RakClient->GetRakClientInterface()->GetDecompressionRatio();
}

void HookedRakClientInterface::AttachPlugin( void *messageHandler )
{
	traceLastFunc( "HookedRakClientInterface::AttachPlugin" );

	g_RakClient->GetRakClientInterface()->AttachPlugin(messageHandler);
}

void HookedRakClientInterface::DetachPlugin( void *messageHandler )
{
	traceLastFunc( "HookedRakClientInterface::DetachPlugin" );

	g_RakClient->GetRakClientInterface()->DetachPlugin(messageHandler);
}

BitStream * HookedRakClientInterface::GetStaticServerData( void )
{
	traceLastFunc( "HookedRakClientInterface::GetStaticServerData" );

	return g_RakClient->GetRakClientInterface()->GetStaticServerData();
}

void HookedRakClientInterface::SetStaticServerData( const char *data, const int length )
{
	traceLastFunc( "HookedRakClientInterface::SetStaticServerData" );

	g_RakClient->GetRakClientInterface()->SetStaticServerData( data, length );
}

BitStream * HookedRakClientInterface::GetStaticClientData( const PlayerID playerId )
{	
	traceLastFunc( "HookedRakClientInterface::GetStaticClientData" );

	return g_RakClient->GetRakClientInterface()->GetStaticClientData( playerId );
}

void HookedRakClientInterface::SetStaticClientData( const PlayerID playerId, const char *data, const int length )
{
	traceLastFunc( "HookedRakClientInterface::SetStaticClientData" );

	g_RakClient->GetRakClientInterface()->SetStaticClientData( playerId, data, length );
}

void HookedRakClientInterface::SendStaticClientDataToServer( void )
{
	traceLastFunc( "HookedRakClientInterface::SendStaticClientDataToServer" );

	g_RakClient->GetRakClientInterface()->SendStaticClientDataToServer();
}

PlayerID HookedRakClientInterface::GetServerID( void ) const
{
	traceLastFunc( "HookedRakClientInterface::GetServerID" );

	return g_RakClient->GetRakClientInterface()->GetServerID();
}

PlayerID HookedRakClientInterface::GetPlayerID( void ) const
{
	traceLastFunc( "HookedRakClientInterface::GetPlayerID" );

	return g_RakClient->GetRakClientInterface()->GetPlayerID();
}

PlayerID HookedRakClientInterface::GetInternalID( void ) const
{
	traceLastFunc( "HookedRakClientInterface::GetInternalID" );

	return g_RakClient->GetRakClientInterface()->GetInternalID();
}

const char* HookedRakClientInterface::PlayerIDToDottedIP( const PlayerID playerId ) const
{
	traceLastFunc( "HookedRakClientInterface::PlayerIDToDottedIP" );

	return g_RakClient->GetRakClientInterface()->PlayerIDToDottedIP( playerId );
}

void HookedRakClientInterface::PushBackPacket( Packet *packet, bool pushAtHead )
{
	traceLastFunc( "HookedRakClientInterface::PushBackPacket" );

	g_RakClient->GetRakClientInterface()->PushBackPacket(packet, pushAtHead);
}

void HookedRakClientInterface::SetRouterInterface( void *routerInterface )
{
	traceLastFunc( "HookedRakClientInterface::SetRouterInterface" );

	g_RakClient->GetRakClientInterface()->SetRouterInterface(routerInterface);
}
void HookedRakClientInterface::RemoveRouterInterface( void *routerInterface )
{
	traceLastFunc( "HookedRakClientInterface::RemoveRouterInterface" );

	g_RakClient->GetRakClientInterface()->RemoveRouterInterface(routerInterface);
}

void HookedRakClientInterface::SetTimeoutTime( RakNetTime timeMS )
{
	traceLastFunc( "HookedRakClientInterface::SetTimeoutTime" );

	g_RakClient->GetRakClientInterface()->SetTimeoutTime( timeMS );
}

bool HookedRakClientInterface::SetMTUSize( int size )
{
	traceLastFunc( "HookedRakClientInterface::SetMTUSize" );

	return g_RakClient->GetRakClientInterface()->SetMTUSize( size );
}

int HookedRakClientInterface::GetMTUSize( void ) const
{
	traceLastFunc( "HookedRakClientInterface::GetMTUSize" );

	return g_RakClient->GetRakClientInterface()->GetMTUSize();
}

void HookedRakClientInterface::AllowConnectionResponseIPMigration( bool allow )
{
	traceLastFunc( "HookedRakClientInterface::AllowConnectionResponseIPMigration" );
	
	g_RakClient->GetRakClientInterface()->AllowConnectionResponseIPMigration( allow );
}

void HookedRakClientInterface::AdvertiseSystem( const char *host, unsigned short remotePort, const char *data, int dataLength )
{
	traceLastFunc( "HookedRakClientInterface::AdvertiseSystem" );

	g_RakClient->GetRakClientInterface()->AdvertiseSystem( host, remotePort, data, dataLength );
}

RakNetStatisticsStruct* const HookedRakClientInterface::GetStatistics( void )
{
	traceLastFunc( "HookedRakClientInterface::GetStatistics" );

	return g_RakClient->GetRakClientInterface()->GetStatistics();
}

void HookedRakClientInterface::ApplyNetworkSimulator( double maxSendBPS, unsigned short minExtraPing, unsigned short extraPingVariance)
{
	traceLastFunc( "HookedRakClientInterface::ApplyNetworkSimulator" );
	
	g_RakClient->GetRakClientInterface()->ApplyNetworkSimulator( maxSendBPS, minExtraPing, extraPingVariance );
	}

bool HookedRakClientInterface::IsNetworkSimulatorActive( void )
{
	traceLastFunc( "HookedRakClientInterface::IsNetworkSimulatorActive" );

	return g_RakClient->GetRakClientInterface()->IsNetworkSimulatorActive();
}

PlayerIndex HookedRakClientInterface::GetPlayerIndex( void )
{
	traceLastFunc( "HookedRakClientInterface::GetPlayerIndex" );

	return g_RakClient->GetRakClientInterface()->GetPlayerIndex();
}

void HookedRakClientInterface::Pad( void )
{
	DWORD at = (DWORD)_ReturnAddress();
	Log( "HookedRakClientInterface::Pad has been called. Return address: %p", at );
}

