#pragma once

#include <cstddef>
#include <utility>
#include <initializer_list>
#include <iterator>

template <typename T>
class ForwardList
{
private:

#pragma region Node

	struct Node
	{
		T _val;
		Node* _next;

		//???
		Node(const T& val, Node* next = nullptr);
	};

#pragma endregion

	Node* _head;

public:

#pragma region Iterator

	class iterator
	{
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using pointer = T*;
		using reference = T&;
		using iterator_category = std::forward_iterator_tag;

	private:
		Node* _current;

	public:
		iterator(Node* ptr);

		reference operator*() const;
		iterator& operator++();
		iterator operator++(int);
		bool operator==(const iterator& other) const;
		bool operator!=(const iterator& other) const;
		
	};

	class const_iterator
	{
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using pointer = const T*;
		using reference = const T&;
		using iterator_category = std::forward_iterator_tag;

	private:
		const Node * _current;

	public:
		const_iterator(const Node* ptr);

		reference  operator*() const;
		iterator& operator++();
		iterator operator++(int);
		bool operator==(const iterator& other) const;
		bool operator!=(const iterator& other) const;
	};

#pragma endregion


	ForwardList(size_t size = 0, const T& val = T());
	ForwardList(const ForwardList& source);
	ForwardList(std::initializer_list<T> initList);
	~ForwardList();

	bool empty() const;

	T& front();
	const T& front() const;
	void push_front(const T& val);
	void pop_front() noexcept;
	void clear();
	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;


	template <typename... Args>
	void emplace_front(Args&&... args);

	ForwardList& operator=(const ForwardList& source);

	template <typename U>
	friend bool operator==(const ForwardList<U>& lhs, const ForwardList<U>& rhs);
};

#pragma region CtorsAndDestructors


template<typename T>
ForwardList<T>::Node::Node(const T& val, Node* next) : _val(val), _next(next) { }

template<typename T>
ForwardList<T>::ForwardList(size_t size, const T& val)
{
	_head = nullptr;

	Node** curNode = &_head;
	for (std::size_t i = 0; i < size; i++)
	{
		*curNode = new Node(val);
		curNode = &(*curNode)->_next;
	}

}

template<typename T>
ForwardList<T>::ForwardList(const ForwardList& source)
{
	_head = nullptr;

	Node** curNode = &_head;
	Node* sourceNode = source._head;

	while (sourceNode != nullptr)
	{
		*curNode = new Node(sourceNode->_val);
		curNode = &(*curNode)->_next;
		sourceNode = sourceNode->_next;
	}

}

template <typename T>
ForwardList<T>::ForwardList(std::initializer_list<T> initList)
{
	_head = nullptr;

	Node** curNode = &_head;
	for (auto iter = initList.begin(); iter != initList.end(); ++iter)
	{
		*curNode = new Node(*iter);
		curNode = &(*curNode)->_next;
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

template<typename T>
ForwardList<T>::iterator::iterator(Node* ptr) : _current(ptr) {}

template<typename T>
ForwardList<T>::const_iterator::const_iterator(const Node* ptr) : _current(ptr) {}


#pragma endregion

#pragma region Iterator

template<typename T>
ForwardList<T>::iterator ForwardList<T>::begin()
{
	return iterator(_head);
}

template<typename T>
ForwardList<T>::iterator ForwardList<T>::end()
{
	return iterator(nullptr);
}

template<typename T>
ForwardList<T>::iterator::reference ForwardList<T>::iterator::operator*() const
{
	return _current->_val;
}

template<typename T>
ForwardList<T>::iterator& ForwardList<T>::iterator::operator++()
{
	_current = _current->_next;
	return *this;
}

template<typename T>
ForwardList<T>::iterator ForwardList<T>::iterator::operator++(int)
{
	iterator result(*this);
	++(*this);
	return result;
}


template<typename T>
bool ForwardList<T>::iterator::operator==(const ForwardList<T>::iterator& other) const
{
	return this->_current == other._current;
}

template<typename T>
bool ForwardList<T>::iterator::operator!=(const ForwardList<T>::iterator& other) const
{
	return this->_current != other._current;
}


#pragma endregion

#pragma region ConstIterator


template<typename T>
ForwardList<T>::const_iterator ForwardList<T>::begin() const
{
	return const_iterator(_head);
}

template<typename T>
ForwardList<T>::const_iterator ForwardList<T>::end() const
{
	return const_iterator(nullptr);
}

template<typename T>
ForwardList<T>::const_iterator::reference ForwardList<T>::const_iterator::operator*() const
{
	return _current->_val;
}

template<typename T>
ForwardList<T>::iterator& ForwardList<T>::const_iterator::operator++() 
{
	_current = _current->_next;
	return *this;
}

template<typename T>
ForwardList<T>::iterator ForwardList<T>::const_iterator::operator++(int)
{
	iterator result(*this);
	++(*this);
	return result;
}

template<typename T>
bool ForwardList<T>::const_iterator::operator==(const iterator& other) const
{
	return this->_current == other._current;
}

template<typename T>
bool ForwardList<T>::const_iterator::operator!=(const iterator& other) const
{
	return this->_current != other._current;
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

template<typename T>
void ForwardList<T>::clear()
{
	this->~ForwardList();
}

template<typename T>
template<typename ...Args>
void ForwardList<T>::emplace_front(Args && ...args)
{
	push_front(T(std::forward<Args>(args)...));
}

#pragma endregion

#pragma region Operators

template<typename T>
bool operator==(const ForwardList<T>& lhs, const ForwardList<T>& rhs)
{
	typename ForwardList<T>::Node* lhsP = lhs._head;
	typename ForwardList<T>::Node* rhsP = rhs._head;

	while (lhsP != nullptr && rhsP != nullptr)
	{
		if (lhsP->_val != rhsP->_val)
			return false;

		lhsP = lhsP->_next;
		rhsP = rhsP->_next;
	}

	return lhsP == rhsP;
}

template<typename T>
bool operator!=(const ForwardList<T>& lhs, const ForwardList<T>& rhs)
{
	return !(lhs == rhs);
}

template<typename T>
ForwardList<T>& ForwardList<T>::operator=(const ForwardList& source)
{
	this->~ForwardList();

	Node** curNode = &_head;
	Node* sourceNode = source._head;

	while (sourceNode != nullptr)
	{
		*curNode = new Node(sourceNode->_val);
		curNode = &(*curNode)->_next;
		sourceNode = sourceNode->_next;
	}

	return *this;
}

#pragma endregion
