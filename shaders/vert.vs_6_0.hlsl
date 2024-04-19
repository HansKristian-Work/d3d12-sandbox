cbuffer CBVVert : register(b0)
{
	float2 offset;
	float scale;
};

float4 main(uint vid : SV_VertexID, uint iid : SV_InstanceID) : SV_Position
{
	float x = float(vid & 1);	
	float y = float(vid & 2) * 0.5;	
	x = x * scale + offset.x;
	y = y * scale + offset.y;
	x -= float(iid) * 0.05;
	y -= float(iid) * 0.05;
	return float4(x, y, 0.0, 1.0);
}

