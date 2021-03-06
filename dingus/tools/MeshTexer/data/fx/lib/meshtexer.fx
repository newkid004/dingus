#ifndef __MESH_TEXER_FX
#define __MESH_TEXER_FX

#include "shared.fx"


half3 gMapTexture( float3 pos, float scale, sampler2D smp, half3 scales )
{
	half3 texX = tex2D( smp, float2(pos.y,pos.z)*scale ).rgb;
	half3 texY = tex2D( smp, float2(pos.x,pos.z)*scale ).rgb;
	half3 texZ = tex2D( smp, float2(pos.x,pos.y)*scale ).rgb;
	return texX * scales.x + texY * scales.y + texZ * scales.z;
}

half3 gMapDiffuse( float3 pos, sampler2D smp, half3 scales )
{
	return gMapTexture( pos, fTexerScale, smp, scales );
}



#endif
