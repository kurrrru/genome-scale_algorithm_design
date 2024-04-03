#include <iostream>
#include <cassert>
#include "util.h"

using namespace std;

template <typename T>
struct	stack
{
	double_linked_list<T>	list;
	void	push(T data)
	{
		list.push_back(data);
	}
	void	pop()
	{
		list.pop_back();
	}
	T	top()
	{
		assert(!list.empty());
		return (list.get_back());
	}
};

template <typename T>
struct	queue
{
	double_linked_list<T>	list;
	void	push(T data)
	{
		list.push_back(data);
	}
	void	pop()
	{
		list.pop_front();
	}
	T	front()
	{
		assert(!list.empty());
		return (list.get_front());
	}
};

template <typename T>
struct	deque
{
	double_linked_list<T>	list;
	void	push_front(T data)
	{
		list.push_front(data);
	}
	void	push_back(T data)
	{
		list.push_back(data);
	}
	void	pop_front()
	{
		list.pop_front();
	}
	void	pop_back()
	{
		list.pop_back();
	}
	T	front()
	{
		assert(!list.empty());
		return (list.get_front());
	}
	T	back()
	{
		assert(!list.empty());
		return (list.get_back());
	}
};

int	main(void)
{
	stack<int>	s;
	queue<int>	q;
	deque<int>	d;

	s.push(1);
	s.push(2);
	s.push(3);
	cout << s.top() << endl;
	s.pop();
	cout << s.top() << endl;
	s.pop();
	cout << s.top() << endl;
	s.pop();
	cout << s.top() << endl;

	q.push(1);
	q.push(2);
	q.push(3);
	cout << q.front() << endl;
	q.pop();
	cout << q.front() << endl;
	q.pop();
	cout << q.front() << endl;
	q.pop();
	cout << q.front() << endl;

	d.push_front(1);
	d.push_front(2);
	d.push_front(3);
	cout << d.front() << " " << d.back() << endl;
	d.pop_front();
	cout << d.front() << " " << d.back() << endl;
	d.pop_front();
	cout << d.front() << " " << d.back() << endl;
	d.pop_front();
	cout << d.front() << " " << d.back() << endl;

	d.push_back(1);
	d.push_back(2);
	d.push_back(3);
	cout << d.front() << " " << d.back() << endl;
	d.pop_back();
	cout << d.front() << " " << d.back() << endl;
	d.pop_back();
	cout << d.front() << " " << d.back() << endl;
	d.pop_back();
	cout << d.front() << " " << d.back() << endl;
}
