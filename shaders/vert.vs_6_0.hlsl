cbuffer CBVVert : register(b0)
{
	float2 offset;
	float scale;
};

struct VOut
{
	uint iid : IID;
	float4 pos : SV_Position;
};

VOut main(uint vid : SV_VertexID, uint iid : SV_InstanceID)
{
	VOut vout;
	float x = float(vid & 1);	
	float y = float(vid & 2) * 0.5;	
	x = x * scale + offset.x;
	y = y * scale + offset.y;
	x -= float(iid) * 0.25 * scale;
	y -= float(iid) * 0.25 * scale;
	vout.iid = iid;
	vout.pos = float4(x, y, 0.0, 1.0);
	return vout;
}

