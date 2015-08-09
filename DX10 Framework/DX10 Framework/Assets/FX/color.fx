////////////////////////////////////////////////////////////////////////////////
// Filename: color.fx
////////////////////////////////////////////////////////////////////////////////

cbuffer cbPerObject
{
	float4x4 matColorWorld;
	float4x4 matColorView;  
	float4x4 matColorProj; 	
};

////////////////////////////////////////////////////////////////////////////////
// Struct Declarations
////////////////////////////////////////////////////////////////////////////////
struct VertexShaderInput
{
	float4 position : POSITION;
	float4 color : COLOR;
};

struct PixelShaderInput
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
PixelShaderInput ColorVertexShader(VertexShaderInput inputVS)
{
	PixelShaderInput outputPS;

	// Change the position vector to be 4 units for proper matrix calculations.
	inputVS.position.w = 1.0f;

	// Calculate the position of the vertex against the world, view, and projection matrices.
	outputPS.position = mul(inputVS.position, matColorWorld);
	outputPS.position = mul(outputPS.position, matColorView);
	outputPS.position = mul(outputPS.position, matColorProj);

	// Store the input color for the pixel shader to use.
	outputPS.color = inputVS.color;

	return outputPS;
}

////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float4 ColorPixelShader(PixelShaderInput inputPS) : SV_Target
{
	return inputPS.color;
}

////////////////////////////////////////////////////////////////////////////////
// Technique
////////////////////////////////////////////////////////////////////////////////
technique10 ColorTechnique
{
	pass pass0
	{
		SetVertexShader(CompileShader(vs_4_0, ColorVertexShader()));
		SetPixelShader(CompileShader(ps_4_0, ColorPixelShader()));
		SetGeometryShader(NULL);
	}
}