#include "EO_Main.h"

EO_CAimbot EO_Aimbot;

float *ViewAngleX = ( float* )0xF6B318;
float *ViewAngleY = ( float* )0xF6B314;
float *DeltaAngles = ( float* )0x9E2B30;

typedef struct
{
	Vector viewAngles;
}viewAngles_t;
viewAngles_t *local = ( viewAngles_t* )0xF6B314;


void GetPlayerTag( unsigned short Bone, centity_t * pEnt, Vector* vOut )
{
	_asm push	vOut
	_asm movzx	esi, Bone
	_asm mov	ecx, pEnt
	_asm movzx	eax, byte ptr [ecx+4]
	_asm mov	edi, 0x402260
	_asm call	edi
	_asm add	esp, 0x4
}
/*
void EO_CAimbot::InitializeAimbot()
{
	Vector vTarget, vAngles, vTemp, vVelocity;
	Vector vDelta[ 64 ];
	iTarget = -1;
	float fTemp;
	float fDistance = 0xFFFFFFFF;
	float aX,aY;

	for( int i = 0;i<cgs->MaxClients;i++ )
	{
		if((cg_entities[i].isAlive) && (cg->clientNum != i))
		{
			if(client[i].iTeam != client[cg->clientNum].iTeam || client[i].iTeam == TEAM_FREE)
			{
				GetPlayerTag(tags->j_head,&cg_entities[i],&vTarget);

				VectorSubtract( cg_entities->newOrigin,cg_entities->oldOrigin,vDelta[ i ] );
				VectorScale( vVelocity,(int)50/1000.0f,vVelocity );
				VectorCopy( vDelta[ i ],vVelocity );
				VectorAdd( vTarget,vVelocity,vTarget );
				
				if(EO_Utils.IsVisible(vTarget))
				{
					fTemp = VectorDistance( refdef->Vieworg,vTarget );

					if( fTemp<fDistance )
					{
						iTarget=i;
						fDistance = VectorDistance(refdef->refdefViewAngles,vTarget);
						VectorCopy( vTarget,vTemp );
						
					}
				}
			}
		}
	}
	if(iTarget == -1)
		return;

	
	EO_Utils.VectorAngles((vTemp-refdef->Vieworg),vAngles);

	vAngles[ 0 ] -= DeltaAngles[ 0 ];
	vAngles[ 1 ] -= DeltaAngles[ 1 ];

	*ViewAngleX = vAngles[ 1 ];
	*ViewAngleY = vAngles[ 0 ];

	local->viewAngles.x+=vAngles.x;
	local->viewAngles.y+=vAngles.y;
	local->viewAngles.z+=vAngles.z;
}*/

void EO_CAimbot::InitializeAimbot()
{
	m_iTargetID = -1;
	float fDistance,fClosest=999999.9f;
	Vector vBonePos,vTmp,vAimAngles;
	Vector vDelta[ 64 ];
	Vector vVelocity;

	for( int i = 0;i<cgs->MaxClients;i++ )
	{
		centity_t*pEnt = &cg_entities[ i ];

		GetPlayerTag( *(WORD*)0x221AA24,pEnt,&vBonePos );

		if( !EO_Utils.isValidEnt( pEnt ) || !EO_Utils.GetTeam( pEnt ) )
			continue;

		VectorSubtract( pEnt->newOrigin,pEnt->oldOrigin,vDelta[ i ] );
		VectorScale( vVelocity,(int)50/1000.0f,vVelocity );
		VectorCopy( vDelta[ i ],vVelocity );
		VectorAdd( vBonePos,vVelocity,vBonePos );

		if( !EO_Utils.NormalTrace(vBonePos,pEnt ) )
			continue;

		fDistance=VectorDistance( refdef->Vieworg,vBonePos );

		if( fDistance<fClosest )
		{
			fClosest=fDistance;
			m_iTargetID=i;
			VectorCopy( vBonePos,vTmp );
		}
	}

	if( m_iTargetID==-1 )
		return;

	EO_Utils.VectorAngles( ( vTmp-refdef->Vieworg ),vAimAngles );
	
	vAimAngles[ 0 ] -= DeltaAngles[ 0 ];
	vAimAngles[ 1 ] -= DeltaAngles[ 1 ];

	*ViewAngleX = vAimAngles[ 1 ];
	*ViewAngleY = vAimAngles[ 0 ];
}
