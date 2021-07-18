#pragma once
template <typename T>
class List
{
private:
	struct Node
	{
		Node* pNext;
		Node* pPrev;
		T data;
		Node(T data = T(), Node* pNext = nullptr, Node* pPrev = nullptr)
		{
			this->data = data;
			this->pNext = pNext;
			this->pPrev = pPrev;
		}
	};
	int size;
	Node* head;
	Node* last;
public:
	List();
	~List();
	//void push(T data);
	void push_front(T data);
	void push_back(T data);
	void push(T data, int index);
	void pop_front();
	void pop_back();
	void pop(int index);
	void sort();
	T top();
	T down();
	bool isEmpty();
	void clear();
	int GetSize();
	T parse(T data);
	T& operator[](const int index);

	typedef Node* iterator;
	iterator GetBegin() { return head; }
	iterator GetNext(iterator it) { if (it) return it->pNext; }
	iterator GetLast() { return last; }
	iterator GetPrev(iterator it) { if (it) return it->pPrev; }
	T GetValue(iterator it)
	{
		if (it) return it->data;
	}

};

template<typename T>
inline List<T>::List()
{
	size = 0;
	head = nullptr;
	last = nullptr;
}

template<typename T>
inline List<T>::~List() { clear(); }

template<typename T>
inline void List<T>::push_front(T data)
{
	if (head == nullptr)
	{
		Node* current = new Node(data);
		last = current;
		head = current;
	}
	else
	{
		Node* current = new Node(data, this->head);
		head->pPrev = current;
		head = current;
	}
	++size;
}

template<typename T>
inline void List<T>::push_back(T data)
{
	if (last == nullptr)
	{
		Node* current = new Node(data);
		last = current;
		head = current;
	}
	else
	{
		Node* current = new Node(data, nullptr, this->last);
		last->pNext = current;
		last = current;
	}
	++size;
}

template<typename T>
inline void List<T>::push(T data, int index)
{
	if (index <= 0) push_front(data);
	else if (index >= GetSize() - 1) push_back(data);
	else
	{
		int counter = 0;
		Node* temp = head;
		Node* tempNext;
		while (temp != nullptr)
		{
			if (counter == index - 1)
			{
				tempNext = temp->pNext;
				Node* current = new Node(data, temp->pNext, temp);
				temp->pNext = current;
				tempNext->pPrev = current;
			}
			temp = temp->pNext;
			++counter;
		}
	}
	++size;
}

template<typename T>
inline void List<T>::pop_front()
{
	if (head == nullptr) return;
	if (head->pNext == nullptr)
	{
		Node* temp = head;
		head = nullptr;
		last = nullptr;
		delete temp;
	}
	else
	{
		Node* temp = head;
		head = head->pNext;
		head->pPrev = nullptr;
		delete temp;
	}
	--size;
}

template<typename T>
inline void List<T>::pop_back()
{
	if (last == nullptr) return; //list empty
	if (last->pPrev == nullptr) //one element
	{
		Node* temp = last;
		head = nullptr;
		last = nullptr;
		delete temp;
	}
	else //When > one elements
	{
		Node* temp = last;
		Node* prevTemp = last->pPrev;
		prevTemp->pNext = nullptr;
		last = prevTemp;
		delete temp;
	}
	--size;
}

template<typename T>
inline void List<T>::pop(int index)
{
	if (index <= 0) pop_front();
	else if (index >= GetSize() - 1) pop_back();
	else
	{
		int counter = 0;
		Node* temp = head;
		Node* tempNext;
		Node* tempPrev;
		while (temp != nullptr)
		{
			if (counter == index)
			{
				tempPrev = temp->pPrev;
				tempNext = temp->pNext;
				tempPrev->pNext = tempNext;
				tempNext->pPrev = tempPrev;
				delete temp;
				--size;
				break;
			}
			temp = temp->pNext;
			++counter;
		}
	}
	--size;
}

template<typename T>
inline void List<T>::sort()
{
	if (isEmpty()) return;
	Node* current = head->pNext;
	bool check = false;
	while (current != nullptr)
	{
		if (current->data < current->pPrev->data)
		{
			if (current->pNext == nullptr)
			{
				current->pPrev->pNext = nullptr;
				last = current->pPrev;
			}
			else
			{
				current->pPrev->pNext = current->pNext;
				current->pNext->pPrev = current->pPrev;
			}
			Node* temp = current;
			while (temp->pPrev != NULL)
			{
				temp = temp->pPrev;
				if (temp->data == current->data)
				{
					if (temp->pPrev != nullptr)
					{
						temp->pPrev->pNext = current;
						current->pPrev = temp->pPrev;
						temp->pPrev = current;
						current->pNext = temp;
						check = true;
						break;
					}
					else
					{
						temp->pPrev = current;
						current->pNext = temp;
						current->pPrev = nullptr;
						head = current;
						current = current->pNext;
						check = true;
						break;
					}
				}
				else if (temp->data < current->data)
				{
					current->pNext = temp->pNext;
					temp->pNext->pPrev = current;
					temp->pNext = current;
					current->pPrev = temp;
					check = true;
					break;
				}
			}
			if (check == false)
			{
				temp->pPrev = current;
				current->pNext = temp;
				current->pPrev = nullptr;
				head = current;
				check = true;
			}
		}
		current = current->pNext;
 		check = false;
	}
}

template<typename T>
inline T List<T>::top()
{
	if (head != nullptr) return head->data;
}

template<typename T>
inline T List<T>::down() 
{ 
	if (last != nullptr) return last->data; 
}

template<typename T>
inline bool List<T>::isEmpty()
{
	if (head == nullptr) return true;
	else return false;
}

template<typename T>
inline void List<T>::clear() { while (size) pop_front(); }

template<typename T>
inline int List<T>::GetSize() { return size; }

template<typename T>
inline T List<T>::parse(T data) //findValue
{
	int counter = 0;
	Node* current = head;
	while (current != nullptr)
	{
		if (current->data == data) return counter;
		current = current->pNext;
		++counter;
	}
	return -1;
}

template<typename T>
inline T& List<T>::operator[](const int index)
{
	int counter = 0;
	Node* current = head;
	while (current != nullptr)
	{
		if (counter == index)
		{
			return current->data;
		}
		current = current->pNext;
		++counter;
	}
}