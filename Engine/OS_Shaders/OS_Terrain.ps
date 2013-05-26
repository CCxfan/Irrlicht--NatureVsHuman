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


sampler2D smpReflection	: register(s0);
sampler2D smpRefraction	: register(s1);
sampler2D smpBump			: register(s2);
sampler2D smpShore		: register(s3);



//Structs
struct VS_TO_PS
{
	float4 Pos		: POSITION;
	float3 Heights	: TEXCOORD0;
	float3 EyeDir	: TEXCOORD1;
	
	float2 TexCoord: TEXCOORD2;
	float3 ProjCoord : TEXCOORD3;
};



float createWave(float2 Pos, float Speed, float Height, float Frequency)
{
//	return sin( Pos.x*15 + Time*Speed)*Height*2 + Height*cos(Time*Speed*2)+cos( Pos.y*15 + Time*Speed*2.0)*Height*2 + Height*sin(Time*Speed);
	
	float Height_ = sin(Pos.x*Frequency+Time*Speed)*cos(Pos.x*Frequency*0.5+Time*Speed*0.1)*sin(Pos.x*Frequency*0.3+Time*Speed)*cos(Pos.y*Frequency*0.2+Time*Speed*0.1)*Height;
	Height_ += sin(Pos.x*Frequency*0.5+Time*Speed*0.5)*cos(Pos.x*Frequency*0.25+Time*Speed*0.05)*sin(Pos.x*Frequency*0.15+Time*Speed*0.15)*cos(Pos.y*Frequency*0.1+Time*Speed*0.05)*Height*2;
	return Height_/3;
}


//Vertexshader
VS_TO_PS mainVS(float4 inPos : POSITION)
{
	VS_TO_PS Out = (VS_TO_PS)0;
	
	//Calculate the final vertexposition
	Out.Pos = mul(inPos, matWorld);

	Out.Pos.y += createWave(Out.Pos.xz,3,2,1);
	
	float2 heightaround = 0;
	heightaround.x += createWave(float2(Out.Pos.x-1.0,Out.Pos.z),3,2,1);
	heightaround.y += createWave(float2(Out.Pos.x,Out.Pos.z-1.0),3,2,1);
	
	Out.Heights = float3(Out.Pos.y,heightaround);
	Out.EyeDir = normalize(vecViewPos-Out.Pos);
	Out.TexCoord = Out.Pos.xz*0.001;
	
	Out.Pos = mul(Out.Pos, matViewProj);
	
	Out.ProjCoord = Out.Pos.xyw;
	
	return Out;
}

//Pixelshader
float4 mainPS(VS_TO_PS In) : COLOR
{
	In.ProjCoord.xy = In.ProjCoord.xy/In.ProjCoord.z;
	In.ProjCoord.xy = In.ProjCoord.xy*0.5+0.5;
	
	float3 Normal = normalize(float3(In.Heights.x-In.Heights.y,1.0,In.Heights.x-In.Heights.z));
	
	Normal += (tex2D(smpBump,In.TexCoord*100+float2(Time*0.1,0)).rbg*2.0-1.0)*0.5;
	Normal += (tex2D(smpBump,In.TexCoord*200+float2(Time*0.2,0)).rbg*2.0-1.0)*0.3;
	Normal = normalize(Normal);
	
	float Diffuse = dot(Normal,normalize(float3(-1.0,1.0,-1.0)));
	float Fresnel = dot(In.EyeDir,Normal);
	
	float3 reflectionVector = -reflect(normalize(float3(-1.0,1.0,-1.0)), Normal);
	float specular = dot(normalize(reflectionVector), normalize(In.EyeDir));
	specular = pow(specular, 256);
	
	float2 disortion = Normal.xz*In.EyeDir.y;
	
	float3 Reflection = tex2D(smpReflection,In.ProjCoord.xy+disortion*0.5).rgb;
	float3 Refraction = tex2D(smpRefraction,float2(In.ProjCoord.x,1-In.ProjCoord.y)+disortion*0.5).rgb;
	float4 Shore = tex2D(smpShore,In.TexCoord*50);
	Shore.a = saturate(Shore.a-(1-In.Heights.x/2));
	
	
	return float4(lerp(lerp(Reflection,Refraction,Fresnel),Shore.rgb,Shore.a)*(0.5+Diffuse*0.5)+specular*(1.0-Shore.a),1.0);
}