#include <iostream>
#include <bitset>

using namespace std;

unsigned short int	mask1(short int B, int d)
{
	unsigned short a = B << d;
	return (a >> d);
}

unsigned short int	mask2(short int B, int d)
{
	return (B & ((1 << 16 - d) - 1));
}

int	main(void)
{
	short int	B = 0b1010101010101010;
	int			d = 2;
	cout << bitset<16>(mask1(B, d)) << endl;
	cout << bitset<16>(mask2(B, d)) << endl;
}
