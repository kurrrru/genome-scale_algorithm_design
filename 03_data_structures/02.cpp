#include <iostream>
#include <cassert>

using namespace std;

template <typename T>
struct bst_rmq
{
private:
	struct node
	{
		int		key_leftmost;
		int		key_rightmost;
		T		value;
		node	*left;
		node	*right;
		T		min;
		T		INF;
		node(int key_leftmost, int key_rightmost, T value) : key_leftmost(key_leftmost), key_rightmost(key_rightmost), value(value), left(nullptr), right(nullptr), min(value) {}
	};

	node	*root;
	T		INF;
	int		size;

	node*	build(T *a, int l, int r)
	{
		assert(l < r);
		if (l >= size)
			return (nullptr);
		if (l == r - 1 && l < size)
			return (new node(l, r, a[l]));
		node	*t = new node(l, r, INF);
		t->left = build(a, l, (l + r) / 2);
		t->right = build(a, (l + r) / 2, r);
		t->min = t->left->min;
		if (t->right)
			t->min = min(t->min, t->right->min);
		return (t);
	}

	T		query(node *t, int l, int r)
	{
		assert(t);
		if (l <= t->key_leftmost && t->key_rightmost <= r)
			return t->min;
		T	ret = INF;		
		if (l < (t->key_leftmost + t->key_rightmost) / 2)
			ret = min(ret, query(t->left, l, r));
		if (r > (t->key_leftmost + t->key_rightmost) / 2 && t->right)
			ret = min(ret, query(t->right, l, r));
		return ret;
	}

	void	update(node *t, int i, T x)
	{
		if (!t || i < t->key_leftmost || i >= t->key_rightmost)
			return ;
		if (t->key_leftmost == i && t->key_rightmost == i + 1)
		{
			t->value = x;
			t->min = x;
			return ;
		}
		if (i < (t->key_leftmost + t->key_rightmost) / 2)
			update(t->left, i, x);
		else
			if (!t->right)
				return ;
			update(t->right, i, x);
		if (t->right)
			t->min = min(t->left->min, t->right->min);
		else
			t->min = t->left->min;
		return ;
	}

public:
	bst_rmq(T *a, int size, T INF): INF(INF), size(size), root(nullptr)
	{
		int r = 1;
		while (r < size)
			r <<= 1;
		root = build(a, 0, r);
	}

	T	RMQ(int l, int r)
	{
		assert(l < r);
		assert(l >= 0);
		assert(r <= size);
		return query(root, l, r);
	}

	void	update(int i, T x)
	{
		assert(i >= 0);
		assert(i < size);
		update(root, i, x);
	}
};

int	main(void)
{
	int		n = 10;
	int		a[] = {32, 3, 8, 4, 2, 1, 9, 7, 6, 5};
	bst_rmq<int>	bst(a, n, 1e9);
	std::cout << bst.RMQ(0, 10) << endl;
	std::cout << bst.RMQ(0, 5) << endl;
	std::cout << bst.RMQ(0, 1) << endl;
	std::cout << bst.RMQ(5, 10) << endl;
	std::cout << bst.RMQ(3, 7) << endl;
	bst.update(5, 0);
	std::cout << bst.RMQ(0, 10) << endl;
	return (0);
}
