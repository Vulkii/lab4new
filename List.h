#pragma once
#ifndef __LIST_H_INCLUDED__
#define __LIST_H_INCLUDED__
#include <iostream>
#include<stdexcept>

namespace best_list {

	/*!
	\brief Actually an element of the container class.

	A regular node template that is used to create a doubly linked list .
	*/
	template <class T>
	struct Node {

		T val_;//!data
		Node* next;//!Just the pointer to next node
		Node* prev;//!Just the pointer to previous node
		// metods
			/*!
		\brief Default constructor for Node
		*/
		Node() :next(nullptr), prev(nullptr) {}
		Node(T val) :Node() {
			val_ = val;
		}
		/*!
		\brief Defualt destructor. Why? See in detail ->

		We store a static memory element and pointers that are cleared when the container class itself is cleared.
		*/
		~Node() = default;
	};

	/*!
	\brief My cool double-linked list. Used for implementing the effects table
	\warning Attention! There is no constant iterator, which does not allow you to work in the mode of reading constant references.
	*/
	template <class T>
	class List
	{
	public:
		typedef Node<T> Node;
		class IterList;
		friend class IterList;
	private:
		friend struct Node;
		Node* head; //! The pointer to head element of list
		Node* last;//! The pointer to last element of list
		int sz; 
	public:

		//!A non-const iterator of container class list
		class IterList
		{
			friend class List<T>;
		private:
			Node* curr; //!points to the current element

		public:
			IterList() : curr() {}
			/*!
			\brief Initializing constructor, very often used to create an iterator->
			\param list link to the list template
			Sets the value to the beginning of the list	
			*/
			IterList(const List<T>& list) :curr(list.head) { }
			/*!
			\brief Overloaded prefix increment operator
			*/
			IterList& operator++() { curr = curr->next; return *this; }
			/*!
			\brief Overloaded postfix increment operator
			*/
			IterList& operator++(int) { List<T>::IterList res(*this); curr = curr->next; return res; }
			/*!
			\brief Overloaded prefix decrement operator
			*/
			IterList& operator--() { curr = curr->prev; return *this; }
			/*!
			\brief Overloaded  postfix decrement operator
			*/
			IterList& operator--(int) { List<T>::IterList res(*this); curr = curr->prev; return res; }
			/*!
			\brief checking whether two parameters are equal*/
			bool operator==(const IterList& it) { return curr == it.curr; }
			/*!
			\brief checking the inequality of two parameters
			*/
			bool operator!=(const IterList& it) { return curr != it.curr; }
			/*!
			\brief Shows info in node
			\return copy of object
			*/
			T& operator*() { return curr->val_; } 
			T* operator->() { return &curr->val_; } //! It shows pointer in info
			~IterList() = default;
		};

		/*!
		\brief This method determines the size of the list
		\return number of integer - size of list
		*/
		int size()const { return sz; }

		/*!
		\brief The method determines whether the list is empty
		\return copy of object
		*/
		int empty()const { return sz == 0; }

		/*!
		\brief Default constructor*/
		List() :head(nullptr), last(nullptr), sz(0) {}

		/*!
		\brief Initializing constructor from parameter of object 
		\param val - Data type for keeping
		*/
		List(T val) : List()
		{

			head = new Node(val);
			last = head;
			sz++;
		}
		/*!
		\brief Copy constructor
		\param list - copyable list
		*/
		List(List<T>& list)
		{
			head = new Node(list.head->val_);
			IterList it = list.begin();
			sz++;
			Node* tmp = head;
			Node* prev = nullptr;
			++it;
			for (it; it != list.end(); ++it)
			{
				if (prev)
					tmp->prev = prev;
				Node* curr = new Node(*it);
				tmp->next = curr;
				prev = tmp;
				tmp = tmp->next;
				sz++;
			}
			last = tmp;
			last->prev = prev;
		}
		/*!
		\brief Overloaded assignment operator
		\param a - copyable list
		\return Link to the list
		*/
		List<T>& operator = (List<T>& a) {
			if (&a != this) {
				this->clear();
				head = new Node(a.head->val_);
				auto it = a.begin();
				sz++;
				++it;
				Node* tmp = head;
				Node* prev = nullptr;
				for (it; it != a.end(); ++it)
				{
					if (prev)
						tmp->prev = prev;
					Node* curr = new Node(*it);
					tmp->next = curr;
					prev = tmp;
					tmp = tmp->next;
					sz++;
				}
				last = tmp;
				last->prev = prev;
			}
			return *this;
		}

		/*!
		\brief Overloaded move operator
		\param a - moveable list
		\return Link to the list
		*/
		List<T>& operator = (List<T>&& a) {
			if (&a != this) {
				this->clear();
				sz = a.sz;
				head = a.head;
				last = a.last;
				a.head = nullptr;
				a.last = nullptr;
			}
			return*this;
		}

		/*!
		\brief Method of the class that inserts an element at the end of the list
		\return Link to the list
		*/
		List<T>& push_back(const T& fresh)
		{
			Node* tmp = new Node(fresh);
			tmp->prev = last;
			if (head != nullptr)
			{
				last->next = tmp;
				last = tmp;
				sz++;
			}
			else
			{
				last = tmp;
				head = tmp;
				sz++;
			}
			return *this;
		}

		/*!
		\brief Method of the class that returns an element from the end of the list
		\return  link to data type of object
		*/
		const T& pop_back()
		{
			if (!this->empty())
			{
				T res = last->val_;
				Node* tmp = last;
				last = last->prev;
				delete tmp;
				sz--;
				if (last == nullptr)
				{
					head = nullptr;
					return res;
				}
				last->next = nullptr;
				return res;
			}
			else
				throw std::out_of_range("list is empty");
		}

		/*!
		\brief Cleaning method for the iterator
		\param it - An iterator with the current pointer to the object that you want to remove
		\return Link to the list
		*/
		List<T>& erase(IterList it)
		{
			if (sz == 0)
				throw std::out_of_range("list is empty");
			sz--;
			if (sz == 0)
			{
				delete head;
				last = nullptr;
				head = nullptr;
				return *this;
			}
			Node* left = it.curr->prev;
			Node* right = it.curr->next;
			if (!(left && right))
			{
				//handle of end
				if (!left)
				{
					auto tmp = head;
					head = head->next;
					head->prev = nullptr;
					delete tmp;
				}
				else
				{
					auto tmp = last;
					last = last->prev;
					last->next = nullptr;
					delete tmp;
				}
			}
			else
			{
				//default
				left->next = right;
				right->prev = left;
				delete it.curr;
			}
			return *this;
		}

		/*!
		\brief The method returns an iterator to the end of the list*/
		IterList end()
		{
			IterList  it;
			if (head != nullptr)
			{
				it.curr = last->next;
			}
			return it;
		}
		/*!
		\brief The method returns an iterator to the beginning of the list */
		IterList begin()
		{
			return IterList(*this);
		}

		/*!
		\brief Method required to clear the list*/
		void clear()
		{

			List<T>::IterList it = this->begin();
			while (it != this->end())
			{
				auto prevIt = it;
				it++;
				erase(prevIt);
			}
			sz = 0;
		}

		/*!
		\brief Destructor: cleans up the memory occupied by the list*/
		~List()
		{
			while (head != nullptr)
			{
				auto tmp = head;
				head = head->next;
				delete tmp;
			}
			sz = 0;
		}
	};


	/*template <class T>
	class IterList
	{
		friend class List<T>;
		typedef Node<T> Node;
	private:
		Node* first;
		Node* curr;
	public:
		IterList() :first(), curr() {}
		IterList(List<T> list) :first(list.head), curr(first) { }
		IterList<T>& operator++() { curr = curr->next; return *this; }
		IterList<T>& operator++(int) { IterList<T> res(this); curr = curr->next; return res; }
		bool operator==(const IterList& it) { return curr == it.curr; }
		bool operator!=(const IterList& it) { return curr != it.curr; }
		T& operator*() { return curr->val_; }
		T* operator->() { return &curr->val_; }
		~IterList() = default;
	};*/


	//List(T* pVal)//Copy list pVal - begin
	//{
	//	try {
	//		int i = _msize(pVal) / _msize(T);
	//		if (i > 1)
	//		{
	//			head = new Node(*pVal);
	//			sz++;
	//			Node* tmp = head;
	//			for (int  j = 1; j < i; j++)
	//			{
	//				Node* curr = new Node(pVal[j]);
	//				tmp->next = curr;
	//				tmp = tmp->next;
	//				sz++;

	//			}
	//		}
	//		else
	//		{
	//			head = new Node(*pVal);
	//			sz++;
	//		}
	//	}
	//	catch(...){
	//		std::cout << " nullptr" << std::endl;
	//	}
	//}


	//List(List<T>& list):sz(list.sz)
	//{
	//	head = new Node(list.pop_back());
	//	auto it = list.begin();
	//	sz++;
	//	Node* tmp = head;
	//	for (it; it!= list.end(); ++it)
	//	{
	//		Node* curr = new Node(*it);
	//		tmp->next = curr;
	//		tmp = tmp->next;
	//		sz++;
	//	}
	//}
}
#endif