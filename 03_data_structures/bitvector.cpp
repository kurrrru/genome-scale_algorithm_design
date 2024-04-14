#include <iostream>
#include <vector>
#include <cassert>

unsigned int	popcount(unsigned int x)
{
	x = (x & 0b01010101010101010101010101010101) + ((x >> 1) & 0b01010101010101010101010101010101);
	x = (x & 0b00110011001100110011001100110011) + ((x >> 2) & 0b00110011001100110011001100110011);
	x = (x & 0b00001111000011110000111100001111) + ((x >> 4) & 0b00001111000011110000111100001111);
	x = (x & 0b00000000111111110000000011111111) + ((x >> 8) & 0b00000000111111110000000011111111);
	x = (x & 0b00000000000000001111111111111111) + ((x >> 16) & 0b00000000000000001111111111111111);
	return (x);
}

struct	s_bitvector
{
private:
	std::vector<unsigned int>	bit;
	std::vector<unsigned int>	sum;
	std::size_t					size;
	std::size_t					len;

public:
	s_bitvector(std::size_t n)
	{
		len = n;
		size = (n + 0b11111) >> 5;
		bit.assign(size, 0u);
		sum.assign(size, 0u);
	}

	void	set(std::size_t i)
	{
		assert(i < len);
		bit[i >> 5] |= 1u << (i & 0b11111);
	}

	void	reset(std::size_t i)
	{
		assert(i < len);
		bit[i >> 5] &= ~(1u << (i & 0b11111));
	}

	bool	operator[](std::size_t i)
	{
		assert(i < len);
		return (bit[i >> 5] & (1u << (i & 0b11111)));
	}

	void	build(void)
	{
		sum[0] = 0;
		for (std::size_t i = 1; i < size; i++)
			sum[i] = sum[i - 1] +  popcount(bit[i - 1]);
	}

	int	rank(std::size_t i)
	{
		assert(i < len);
		return (sum[i >> 5] + popcount(bit[i >> 5] & ((1u << ((i + 1) & 0b11111)) - 1)));
	}
};

int main(void)
{
	s_bitvector	bit(50);
	// std::cout << "Hello, World!" << std::endl;
	bit.set(0);
	bit.set(1);
	bit.set(3);
	bit.set(4);
	bit.set(6);
	bit.set(9);
	bit.set(40);
	bit.build();
	std::cout << bit.rank(0) << std::endl;
	std::cout << bit.rank(1) << std::endl;
	std::cout << bit.rank(2) << std::endl;
	std::cout << bit.rank(3) << std::endl;
	std::cout << bit.rank(4) << std::endl;
	std::cout << bit.rank(5) << std::endl;
	std::cout << bit.rank(6) << std::endl;
	std::cout << bit.rank(7) << std::endl;
	std::cout << bit.rank(8) << std::endl;
	std::cout << bit.rank(9) << std::endl;
	std::cout << bit.rank(39) << std::endl;
	std::cout << bit.rank(40) << std::endl;
	return (0);
}