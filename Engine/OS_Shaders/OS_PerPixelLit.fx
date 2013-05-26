//Variables
float4x4 matWorld;
float4x4 matViewProj;

float3 vecViewPos;
float3 vecDistFogColor;

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

	float3 TexCoord : TEXCOORD0;
	float3 Normal	 : TEXCOORD1;
	float Fog	: TEXCOORD2;
};

//Vertexshader
VS_TO_PS mainVS(float4 inPos : POSITION, float3 inNorm : NORMAL, float2 inTex0 : TEXCOORD0)
{
	VS_TO_PS Out = (VS_TO_PS)0;

	//Calculate the final vertexposition
	Out.Pos = mul(inPos, matWorld);

	Out.TexCoord.xy = inTex0;
	Out.TexCoord.z = (Out.Pos.y+1.0*ClipFac)*ClipFac;
	Out.Fog = saturate(distance(vecViewPos,Out.Pos.xyz)/200);

	Out.Pos = mul(Out.Pos,matViewProj);

	Out.Normal = normalize(mul(inNorm,matWorld));

	return Out;
}

//Pixelshader
float4 mainPS(VS_TO_PS In) : COLOR
{
	clip(In.TexCoord.z);

	float4 Color = tex2D(smpTexture,In.TexCoord);

	clip(Color.a-0.5);

	Color *= dot(In.Normal,normalize(float3(-1.0,1.0,-1.0)))*0.5+0.5;

	Color.rgb = lerp(Color.rgb,vecDistFogColor,In.Fog);
	Color.a = 1.0;

	return Color;
}
