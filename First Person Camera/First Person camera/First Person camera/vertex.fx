//"vertex.fx" file


cbuffer cbPerObject
{
	float4x4 WVP;
};

struct VS_OUTPUT	//output structure for vertex shader
{
	float4 Pos : SV_POSITION;
	float4 Color : COLOR;
};

// Vertex Shader
VS_OUTPUT VS(float4 inPos : POSITION, float4 inColor : COLOR)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	output.Pos = mul(inPos, WVP);

	output.Color = inColor;

	return output;		//send color and position to pixel shader
}

// Pixel Shader
float4 PS(VS_OUTPUT input) : SV_Target
{
	return input.Color;
}

technique10 Tech
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_4_0, VS()));
		SetPixelShader(CompileShader(ps_4_0, PS()));
	}
}