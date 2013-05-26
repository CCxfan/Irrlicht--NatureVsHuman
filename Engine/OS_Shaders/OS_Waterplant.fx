//Variables
float4x4 matWorld;
float4x4 matViewProj;

float3 vecViewPos;
float4 vecFog;

float Time;

float4 vecAmbient;
float4 vecDiffuse;
float4 vecEmissive;
float4 vecSpecular;
float Shininess;

float ClipFac;


sampler2D smpTexture	: register(s0);


//Structs
struct VS_TO_PS
{
	float4 Pos		: POSITION;

	float4 TexCoord: TEXCOORD0;
	float Fog	: TEXCOORD2;
};

//Vertexshader
VS_TO_PS mainVS(float4 inPos : POSITION, float2 inTex0 : TEXCOORD0)
{
	VS_TO_PS Out = (VS_TO_PS)0;

	//Calculate the final vertexposition
	Out.Pos = mul(inPos, matWorld);

	Out.TexCoord.xy = inTex0;
	Out.TexCoord.z = -Out.Pos.y/20;
	Out.TexCoord.w = (Out.Pos.y+1.0*ClipFac)*ClipFac;
	Out.Fog = saturate(distance(vecViewPos,Out.Pos.xyz)/200);

	Out.Pos.x += sin(inPos.y*10+Time*2.0)*inPos.y*0.05;
	Out.Pos.z += cos(inPos.y*10+Time*2.0)*inPos.y*0.05;
	Out.Pos.x += sin(inPos.y+Time)*inPos.y*0.1;
	Out.Pos.z += cos(inPos.y+Time)*inPos.y*0.1;

	Out.Pos = mul(Out.Pos,matViewProj);

	return Out;
}

//Pixelshader
float4 mainPS(VS_TO_PS In) : COLOR
{
	clip(In.TexCoord.w);

	float4 Color = tex2D(smpTexture,In.TexCoord);

	clip(Color.a-0.9);

	Color.rgb = lerp(Color.rgb,float3(0.85,0.95,1.0),In.Fog);
	Color.a = In.TexCoord.z;

	return Color;
}
