RWStructuredBuffer<uint> BUF : register(u0);

[numthreads(1, 1, 1)]
void main()
{
	uint o;
	InterlockedAdd(BUF[0], 1, o);
}
