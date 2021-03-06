// global parameters are here

#ifndef __SHARED_FX
#define __SHARED_FX

#include "defines.fx"


// --------------------------------------------------------------------------
// time

shared float	fTime;

// --------------------------------------------------------------------------
// camera

shared float4x4	mView;
shared float4x4	mProjection;
shared float4x4	mViewProj;
shared float3	vEye;

shared float4	vDOF; // x=focalDist, y=1/focalRange, z=blurBias, w=colorfade


// --------------------------------------------------------------------------
//  global params

// cull mode: CW=2 (should be default), CCW=3 (for reflected, etc.)
shared int		iCull = 2;

// x=0.5/width, y=0.5/height
shared float4	vScreenFixUV;


// --------------------------------------------------------------------------
//  shadow maps

static const float fShadowRangeScale = 10.0;
static const float fShadowBias = 0.003;

shared float4x4	mViewTexProj;

shared float4x4	mShadowProj;
shared float4x4	mShadowProj2;


static const int SHADOW_MAP_SIZE = 256;
static const int SHADOW_MAP_SIZE2 = 512;


// --------------------------------------------------------------------------
//  others

shared float fCharTimeBlend;


const static float4x4 mIdentity = float4x4(
	1,0,0,0,
	0,1,0,0,
	0,0,1,0,
	0,0,0,1 );
const static float4x4 mSphereMap = float4x4(
	0.4,0,  0, 0,
	0, -0.4,0, 0,
	0,  0.0,0, 0,
	0.5,0.5,0, 0 );


#endif
