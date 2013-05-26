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


sampler2D smpReflection	: register(s0);
sampler2D smpRefraction	: register(s1);
sampler2D smpBump		: register(s2);
sampler2D smpShore		: register(s3);



//Structs
struct VS_TO_PS
{
	float4 Pos			: POSITION;
	float4 Heights		: TEXCOORD0;
	float4 EyeDir		: TEXCOORD1;

	float4 TexCoord1	: TEXCOORD2;
	float2 TexCoord2	: TEXCOORD3;
	float3 ProjCoord	: TEXCOORD4;
};



float createWave(float2 Pos, float Speed, float Height, float Frequency)
{
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

	Out.Pos.y += createWave(Out.Pos.xz,2,0.5,1)*saturate(1.0-distance(vecViewPos,Out.Pos.xyz)/100);

	float2 heightaround = 0;
	heightaround.x += createWave(float2(Out.Pos.x-1.0,Out.Pos.z),2,0.5,1)*saturate(1.0-distance(vecViewPos,Out.Pos.xyz)/100);
	heightaround.y += createWave(float2(Out.Pos.x,Out.Pos.z-1.0),2,0.5,1)*saturate(1.0-distance(vecViewPos,Out.Pos.xyz)/100);

	Out.Heights.xyz = float3(Out.Pos.y,heightaround);

	//Fog
	Out.Heights.w = saturate(distance(vecViewPos,Out.Pos.xyz)/200);

	Out.EyeDir.xyz = normalize(vecViewPos-Out.Pos);
	Out.EyeDir.w = Out.Pos.y-vecViewPos.y;

	Out.TexCoord1.xy = Out.Pos.xz*0.001;
	Out.TexCoord2.xy = Out.TexCoord1.xy*50;
	Out.TexCoord1.zw = Out.TexCoord1.xy*200+float2(Time*0.2,0);
	Out.TexCoord1.xy = Out.TexCoord1.xy*100+float2(Time*0.1,0);

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

	Normal += (tex2D(smpBump,In.TexCoord1.xy).rbg*2.0-1.0)*0.5;
	Normal += (tex2D(smpBump,In.TexCoord1.zw).rbg*2.0-1.0)*0.3;
	Normal.y *= 0.25;
	Normal = normalize(Normal);
	
	float3 reflectionVector = -reflect(normalize(float3(-1.0,1.0,-1.0)), Normal);
	float specular = dot(normalize(reflectionVector), normalize(In.EyeDir.xyz));
	specular = pow(specular, 100);
	
//	float Depth = tex2D(smpRefraction,float2(In.ProjCoord.x,1-In.ProjCoord.y)).a;
	float2 disortion = Normal.xz*In.EyeDir.y*0.5;	//*Depth;
	In.ProjCoord.xy += disortion;

	float3 Reflection = tex2D(smpReflection,In.ProjCoord.xy).rgb;
	float4 Refraction = tex2D(smpRefraction,float2(In.ProjCoord.x,1-In.ProjCoord.y));
	float4 Shore = tex2D(smpShore,In.TexCoord2.xy);
	Shore.a = saturate(Shore.a+In.Heights.x-0.95);

	float Diffuse = dot(Normal,normalize(float3(-1.0,1.0,-1.0)));
	float Fresnel = 1.0-dot(In.EyeDir,Normal);
	if(In.EyeDir.w > 0)
	{
		Fresnel = 0.0;
	}else
	{
		//Watercolor
		Refraction.rgb = lerp(Refraction.rgb,/*0.5*/float3(0.157, 0.351, 0.586),Refraction.a);
	}

	float3 Color = lerp(lerp(Refraction.rgb,Reflection,Fresnel*Refraction.a),Shore.rgb,Shore.a)*(0.5+Diffuse*0.5)+specular*(1.0-Shore.a);

	//Fog
	Color = lerp(Color,vecDistFogColor,In.Heights.w);

	return float4(Color,1.0);
}
