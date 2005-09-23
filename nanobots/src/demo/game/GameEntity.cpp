#include "stdafx.h"
#include "GameEntity.h"
#include "../GameInfo.h"
#include "GameDesc.h"
#include "../map/LevelMesh.h"



static const char* ENT_TYPE_NAMES[ENTITYCOUNT] = {
	"Needle",
	"Explorer",
	"Collector",
	"AI",
	"WhiteCell", // TBD: Container
	"BlackCell", // TBD: NeuroCtrl
	"Blocker",
};

CGameEntity::CGameEntity( unsigned short eid, eEntityType type, int owner, int bornTurn )
:	mLastUpdateTurn( bornTurn-1 )
,	mID( eid )
,	mType( type )
,	mOwner( owner )
,	mMaxHealth( -1 )
,	mBornTurn( bornTurn )
{
	assert( type >= 0 && type < ENTITYCOUNT );
	assert( bornTurn >= 0 );

	mTypeName = ENT_TYPE_NAMES[type];

	mOnGround = (type==ENTITY_NEEDLE) || (type==ENTITY_NEUROC);
	mOnAir = (type!=ENTITY_COLLECTOR) && (type!=ENTITY_CONTAINER);
	mOnSine = (type==ENTITY_BLOCKER);

	if( mOnSine )
		mBaseAltitude = -0.6f;
	else if( mOnAir )
		mBaseAltitude = gRandom.getFloat( -0.2f, 0.2f );
	else
		mBaseAltitude = gRandom.getFloat( -0.6f, -0.4f );
}

CGameEntity::~CGameEntity()
{
}


void CGameEntity::updateState( int turn, SState& state )
{
	if( turn == mLastUpdateTurn )
		return; // already updated this turn

	// compute 3D position from 2D position
	const float RADIUS = 0.7f;
	const CGameMap& gmap = CGameInfo::getInstance().getGameDesc().getMap();
	const CLevelMesh& levelMesh = CGameInfo::getInstance().getLevelMesh();

	const CGameMap::SCell& cell = gmap.getCell( state.posx, state.posy );
	float hgt = cell.height;
	if( (turn != mBornTurn) || mOnGround || mOnSine )
		hgt *= mBaseAltitude;
	
	state.pos.set( float(state.posx), hgt, float(-state.posy) );
	if( !mOnGround ) {
		float phi = turn * 0.05f;
		state.pos.x += cosf(phi) * 0.03f;
		state.pos.z += sinf(phi) * 0.03f;
	}
	if( cell.nearBone )
		levelMesh.fitSphere( state.pos, RADIUS );
	if( mOnGround )
		state.pos.y = -cell.height;


	// this is a very first update, remember max. health
	// and fill entire history with current state
	if( mLastUpdateTurn == mBornTurn-1 ) {
		mMaxHealth = state.health;

		assert( mStates.empty() );
		for( int i = 0; i < HISTORY_SIZE; ++i )
			mStates.push_front( state );
	}

	if( mStates.full() )
		mStates.pop_back();
	mStates.push_front( state );

	mLastUpdateTurn = turn;
}

void CGameEntity::markDead()
{
	int n = mStates.size();
	for( int i = 0; i < n; ++i )
		mStates[i].state = ENTSTATE_DEAD;
}
