#pragma once
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
	s_bitvector(void) = default;
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
