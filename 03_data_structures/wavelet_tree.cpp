// #pragma once
#include "bitvector.hpp"
#include <iostream>


struct s_wavelet_tree
{
private:
	struct node {
		node				*left;
		node				*right;
		std::vector<int>	arr;
		s_bitvector			bit;
		node(node *_left, node *_right, std::vector<int> _arr): left(_left), right(_right), arr(_arr) 
		{
			bit = s_bitvector(arr.size());
		}
	};

	node				*root;
	unsigned int		alphabet_size;

	void	build(node *n, unsigned int l, unsigned int r, unsigned int depth)
	{
		if (l == r)
			return ;
		unsigned int mid = (l + r) >> 1;
		std::vector<int> left_arr, right_arr;
		for (unsigned int i = 0; i < n->arr.size(); i++)
			if (n->arr[i] < mid)
				left_arr.push_back(n->arr[i]);
			else
			{
				right_arr.push_back(n->arr[i]);
				n->bit.set(i);
			}
		n->left = new node(nullptr, nullptr, left_arr);
		n->right = new node(nullptr, nullptr, right_arr);
		build(n->left, l, mid, depth + 1);
		build(n->right, mid + 1, r, depth + 1);
	}

	int rank(node *n, unsigned int i, int c, unsigned int l, unsigned int r)
	{
		if (!n->left && !n->right)
			return (i);
		if (c < (l + r) >> 1)
			if (n->bit.size() > 0)
				return (rank(n->left, i - n->bit.rank(i - 1), c, l, (l + r) >> 1));
			else
				return (0);
		if (n->bit.size() > 0)
			return (rank(n->right, n->bit.rank(i - 1), c, ((l + r) >> 1) + 1, r));
		else
			return (0);
	}

public:
	s_wavelet_tree(std::vector<int> _arr, unsigned int _alphabet_size): alphabet_size(_alphabet_size)
	{
		root = new node(nullptr, nullptr, _arr);
	}

	void	build(void)
	{
		build(root, 0, alphabet_size, 0);
	}

	// count the number of elements equal to c in [0, i]
	int rank(unsigned int i, int c)
	{
		return (rank(root, i, c, 0, alphabet_size));
	}

	// count the number of elements equal to c in [l, r)
	int rank(unsigned int l, unsigned int r, int c)
	{
		return (rank(root, r, c, 0, alphabet_size) - rank(root, l, c, 0, alphabet_size));
	}
};


int	main(void)
{
	std::vector<int> arr = {1, 2, 3, 2, 5, 6, 1, 3, 2, 1};
	s_wavelet_tree wt(arr, 10);
	wt.build();
	std::cout << wt.rank(5, 0) << std::endl;
	std::cout << wt.rank(5, 1) << std::endl;
	std::cout << wt.rank(5, 2) << std::endl;
	std::cout << wt.rank(10, 1) << std::endl;
	std::cout << wt.rank(10, 2) << std::endl;
	return (0);
}