#pragma once

#include <cstddef>

template <typename T>
class ForwardList
{
private:

	struct Node
	{
		T _val;
		Node* _next;

		//???
		Node(const T& val, Node* next = nullptr);

	};

	Node* _head;

public:
	ForwardList(size_t size = 0, const T& val = T{});
	~ForwardList();

	bool empty() const;
	T& front();
	const T& front() const;

	void push_front(const T& val);
	void pop_front() noexcept;
};

#pragma region Ctors


template<typename T>
ForwardList<T>::Node::Node(const T& val, Node* next) : _val(val), _next(next) { }

template<typename T>
ForwardList<T>::ForwardList(size_t size, const T& val)
{
	//TODO change logic to lection

	if (size == 0)
		return;

	_head = new Node(val, nullptr);
	Node* curr = _head;
	for (size_t i = 1; i < size; i++)
	{
		curr->_next = new Node(val);
		curr = curr->_next;
	}
}

template<typename T>
ForwardList<T>::~ForwardList()
{
	while (_head != nullptr)
	{
		Node* temp = _head->_next;
		delete _head;
		_head = temp;
	}
}


#pragma endregion

#pragma region Temp


template<typename T>
bool ForwardList<T>::empty() const
{
	return _head == nullptr;
}

template<typename T>
T& ForwardList<T>::front()
{
	return _head->_val;
}

template<typename T>
const T& ForwardList<T>::front() const
{
	return _head->_val;
}

template<typename T>
void ForwardList<T>::push_front(const T& val)
{
	_head = new Node(val, _head);
}

template<typename T>
void ForwardList<T>::pop_front() noexcept
{
	Node* temp = _head;
	_head = _head->_next;

	delete temp;
}

#pragma endregion