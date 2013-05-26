//Variables
float4x4 matWorld;
float4x4 matWorldViewProj;
float3x3 matTangent;

float3 vecViewPos;
float4 vecFog;
float4 vecLight;

float4 vecLightPos[8];
float4 vecLightColor[8];

float4 vecAmbient;
float4 vecDiffuse;
float4 vecEmissive;
float4 vecSpecular;
float Shininess;


sampler2D Texture0 : register(s0);
sampler2D Texture1 : register(s1);



//Structs
struct VS_TO_PS
{
	float4 Pos  : POSITION;
	float Fog : FOG;

	float2 Tex : TEXCOORD0;
	float3 View : TEXCOORD1;
	float4 Light1 : TEXCOORD2;
};


//Vertexshader
VS_TO_PS main(	float4 inPos : POSITION,
					float2 inTex : TEXCOORD0,
					float3 inNormal : NORMAL,
					float3 inTangent : TEXCOORD2 )
{
	VS_TO_PS Out = (VS_TO_PS)0;

	//Calculate the final vertexposition
	Out.Pos = mul(inPos, matWorldViewProj);

	//Get the vertexposition in worldspace
	float3 PosWorld = mul(inPos, matWorld);

	//Create matTangent
	matTangent[0] = inTangent*matWorld;
	matTangent[1] = mul(cross(inTangent, inNormal), matWorld;
	matTangent[2] = mul(inNormal, matWorld);

	//Pass the TexCoords
	Out.Tex = inTex;

	//Viewdir to tangent space
	Out.View = mul(matTangent, vecViewPos.xyz-PosWorld.xyz);

	float3 LightDir = 0;

	//Light1
	LightDir = vecLightPos[0].xyz-PosWorld;
	Out.Light1.xyz = normalize(mul(matTangent,LightDir));
	Out.Light1.w = saturate(1.0f - length(LightDir/vecLightPos[0].w));

	//Fog
	//Out.Fog = 1 - (distance(PosWorld,vecViewPos)-vecFog.x) * vecFog.z;

	return Out;
}
