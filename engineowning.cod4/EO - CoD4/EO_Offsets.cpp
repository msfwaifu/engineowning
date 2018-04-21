#include "EO_Main.h"

refdef_t				*					refdef							= ( refdef_t* )				OFFS_REFDEF;
clientInfo_t			*					clientInfo						= ( clientInfo_t* )			OFFS_CLIENTINFO;
entity_t				*					cg_entities						= ( entity_t* )				OFFS_ENTITY;
cgs_t					*					cgs								= ( cgs_t* )				OFFS_CGS;
cg_t					*					cg								= ( cg_t* )					OFFS_CG;
viewMatrix_t			*					viewMatrix						= ( viewMatrix_t* )			OFFS_VIEWMATRIX;
scoreInfo_t				*					cg_scores						= ( scoreInfo_t* )			OFFS_SCOREINFO;