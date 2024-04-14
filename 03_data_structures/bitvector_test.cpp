#include "bitvector.hpp"
#include <iostream>

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