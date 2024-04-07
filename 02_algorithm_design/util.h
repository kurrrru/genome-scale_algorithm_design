using namespace std;

template <typename T>
struct	double_linked_list
{
	struct	node 
	{
		T		data;
		node	*prev;
		node	*next;
		node(T val)
		{
			data = val;
			prev = NULL;
			next = NULL;
		}
	};
	node	*head;
	node	*tail;
	double_linked_list()
	{
		head = NULL;
		tail = NULL;
	}
	void	push_front(int data)
	{
		node	*new_node = new node(data);
		if (head == NULL)
		{
			head = new_node;
			tail = new_node;
		}
		else
		{
			new_node->next = head;
			head->prev = new_node;
			head = new_node;
		}
	}
	void	push_back(int data)
	{
		node	*new_node = new node(data);
		if (head == NULL)
		{
			head = new_node;
			tail = new_node;
		}
		else
		{
			new_node->prev = tail;
			tail->next = new_node;
			tail = new_node;
		}
	}
	void	pop_front()
	{
		if (head == NULL)
			return ;
		node	*tmp = head;
		head = head->next;
		if (head != NULL)
			head->prev = NULL;
		delete tmp;
	}
	void	pop_back()
	{
		if (head == NULL)
			return ;
		node	*tmp = tail;
		tail = tail->prev;
		if (tail != NULL)
			tail->next = NULL;
		delete tmp;
	}
	T	empty()
	{
		return (head == NULL);
	}
	T	get_front()
	{
		return (head->data);
	}
	T	get_back()
	{
		return (tail->data);
	}
};
