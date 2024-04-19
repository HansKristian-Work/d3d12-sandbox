cbuffer CBVFrag : register(b1)
{
	float3 col;
};

struct VOut
{
	uint iid : IID;
	float4 pos : SV_Position;
};

float4 main(VOut vin) : SV_Target
{
	float i = exp2(-float(vin.iid));
	return float4(col * i, 1.0);
}
