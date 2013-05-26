//Variables
float4x4 matWorld;
float4x4 matViewProj;

float3 vecViewPos;
float3 vecDistFogColor;
float3 vecSkyColor;

float Time;

float4 vecAmbient;
float4 vecDiffuse;
float4 vecEmissive;
float4 vecSpecular;
float Shininess;

sampler2D smpSun : register(s0);

//Structs
struct VS_TO_PS
{
	float4 Pos		: POSITION;
	float3 TexCoords : TEXCOORD0;
};

//Vertexshader
VS_TO_PS mainVS(float4 inPos : POSITION, float3 inNorm : NORMAL, float2 inTex0 : TEXCOORD0)
{
	VS_TO_PS Out = (VS_TO_PS)0;

	//Calculate the final vertexposition
	Out.Pos = mul(inPos, matWorld);

	Out.TexCoords.xy = inTex0;//*float2(10.0,5.0)+sin(float2(Time*0.2,0.0))*20.0-float2(0,1.0);
	Out.TexCoords.z = inPos.y/500;

	Out.Pos = mul(Out.Pos,matViewProj);

	return Out;
}

//Pixelshader
float4 mainPS(VS_TO_PS In) : COLOR
{
	float3 Color = lerp(vecDistFogColor,vecSkyColor,In.TexCoords.z);
	float3 Sun = tex2D(smpSun,In.TexCoords.xy).rgb;
	Color += Sun;

	return float4(Color,1.0);
}
