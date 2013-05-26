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


sampler2D smpCaustics	: register(s1);
sampler2D smpTileSand	: register(s0);
sampler2D smpTileGrass	: register(s2);


//Structs
struct VS_TO_PS
{
	float4 Pos		: POSITION;

	float4 TexCoord: TEXCOORD0;
	float3 Normal	: TEXCOORD1;
	float Fog	: TEXCOORD2;
};

//Vertexshader
VS_TO_PS mainVS(float4 inPos : POSITION, float3 inNorm : NORMAL, float2 inTex0 : TEXCOORD0)
{
	VS_TO_PS Out = (VS_TO_PS)0;

	//Calculate the final vertexposition
	Out.Pos = mul(inPos, matWorld);

	Out.TexCoord.xy = inTex0*100;
	Out.TexCoord.z = -Out.Pos.y/20;
	Out.TexCoord.w = (Out.Pos.y+1.0*ClipFac)*ClipFac;
	Out.Fog = saturate(distance(vecViewPos,Out.Pos.xyz)/200);

	Out.Pos = mul(Out.Pos,matViewProj);

	Out.Normal = normalize(mul(inNorm,matWorld));

	return Out;
}

//Pixelshader
float4 mainPS(VS_TO_PS In) : COLOR
{
	clip(In.TexCoord.w);

	float3 Color = tex2D(smpTileGrass,In.TexCoord).rgb;
	Color = lerp(Color,tex2D(smpTileSand,In.TexCoord).rgb,saturate(In.TexCoord.z*20+2));

	float3 Caustic1 = tex2D(smpCaustics,In.TexCoord.xy+float2(Time*0.2,0)).rgb;
	float3 Caustic2 = tex2D(smpCaustics,In.TexCoord.yx+float2(-Time*0.2,0)).rgb;

	float Diffuse = dot(In.Normal,normalize(float3(-1.0,1.0,-1.0)))*0.5+0.5;
	float3 Light = Caustic1*Caustic2*2.0*Diffuse;
	Light *= saturate(In.TexCoord.z*20)*0.3;
	Light += Diffuse;

	Color *= Light;

	Color = lerp(Color,vecDistFogColor,In.Fog);

	return float4(Color,In.TexCoord.z);
}
