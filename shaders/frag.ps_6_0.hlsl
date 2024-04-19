cbuffer CBVFrag : register(b1)
{
	float3 col;
};

float4 main() : SV_Target
{
	return float4(col, 1.0);
}
