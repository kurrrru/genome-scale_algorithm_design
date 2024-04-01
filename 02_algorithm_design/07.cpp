#include <iostream>

using namespace std;

struct bit_field
{
	unsigned int	*A;
	unsigned int	n;
	unsigned int	k;
	bit_field(unsigned n, unsigned k): n(n), k(k)
	{
		A = new unsigned[n * k / 32 + 1];
	}
	void	setField(unsigned i, unsigned x)
	{
		for (int j = 0; j < n; j++)
		{
			if (x & (1 << j))
			{
				A[(i * n + j) / 32] |= 1 << ((i * n + j) % 32);
			}
			else
			{
				A[(i * n + j) / 32] &= ~(1 << ((i * n + j) % 32));
			}
		}
	}
	unsigned int	getField(unsigned i)
	{
		unsigned int x = 0;
		for (int j = 0; j < n; j++)
		{
			if (A[(i * n + j) / 32] & (1 << ((i * n + j) % 32)))
			{
				x |= 1 << j;
			}
		}
		return (x);
	}
	~bit_field()
	{
		delete[] A;
	}
};

int	main(void)
{
	bit_field B(7, 4);
	B.setField(0, 40);
	B.setField(1, 25);
	B.setField(2, 120);
	B.setField(3, 110);
	cout << B.getField(0) << endl;
	cout << B.getField(1) << endl;
	cout << B.getField(2) << endl;
	cout << B.getField(3) << endl;
}
