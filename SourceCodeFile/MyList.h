#include<iostream>
using namespace std;

#ifndef MYLIST_H
#define MYLIST_H

//node to wrap T class element and pointer to next
template <class T>
struct Node {
	T element;
	Node* next;
};

/*
*				MyList class definition
======================================================
*	MyList class is used for creating list of classes
*	and organizing these classes
*/
template <class T>
class MyList {
private:

	//private attribute of MyList class
	//head of the list
	Node<T> *head;

	//current pointer of the list
	Node<T> *current;

	//tail of the list
	Node<T> *tail;

	//length of the list
	int length = 0;

public:

	//constructor of MyList
	MyList();

	//constructor to start with first element in list
	MyList(T firstElement);

	//setters and getters for pointer
	void setHead(T head);
	void setHead(Node<T>* headNode);
	void setCurrent(Node<T>* currentNode);
	void setTail(Node<T>* tailNode);
	Node<T>* getHead();
	Node<T>* getCurrent();
	Node<T>* getTail();

	//getter for element and attributes
	T getHeadElement();
	T getCurrentElement();
	T getTailElement();
	void setLength(int length);
	int getLength();

	//Methods
	void moveToNext();
	void addToHead(T head);
	void addToList(T newItem);
	T pop();
	void displayList();
	boolean isEmpty();
	Node<T>* createNewNode(T element);
	T removeFromList(int index);
	void goToHead();

};

//empty constructor for MyList class
template <class T>
MyList<T>::MyList() {};

//constructor for start with first element in list
template <class T>
MyList<T>::MyList(T firstElement) {

	//create new node and set the pointers to the node
	Node<T> *temp = createNewNode(firstElement);
	this->current = temp;
	this->tail = temp;
	this->length = 1;

}

//function to set head pointer with element
template <class T>
void MyList<T>::setHead(T headElement) {

	//create new Node to store element and pointer
	Node<T> *temp = createNewNode(headElement);
	temp->next = NULL;

	//set pointer to current node for head, current, and tail
	this->head = temp;
	this->current = temp;
	this->tail = temp;

	//increase the length of this list
	this->length = 1;

}

//function to set head pointer with Node pointer
template <class T>
void MyList<T>::setHead(Node<T>* headNode) {

	headNode->next = NULL;

	//set head of the list to headNode
	this->head = headNode;
	this->length = 1;

}

//function to set current pointer with Node pointer
template <class T>
void MyList<T>::setCurrent(Node<T>* currentNode) {

	//set current of the list to currentNode
	this->current = currentNode;

}

//function to set tail pointer with Node pointer
template <class T>
void MyList<T>::setTail(Node<T>* tailNode) {

	//set tail of the list to tailNode
	this->tail = tailNode;

}

//function to get head pointer
template <class T>
Node<T>* MyList<T>::getHead() {

	//return the head pointer
	return this->head;

}

//function to get current pointer
template <class T>
Node<T>* MyList<T>::getCurrent() {

	//return the current pointer
	return this->current;

}

//function to get tail pointer
template <class T>
Node<T>* MyList<T>::getTail() {


	//return the tail pointer
	return this->tail;

}

//function to get head element
template <class T>
T MyList<T>::getHeadElement() {

	//return the head element
	return this->head->element;

}

//function to get current element
template <class T>
T MyList<T>::getCurrentElement() {

	//return the current element
	return this->current->element;

}

//function to get tail element
template <class T>
T MyList<T>::getTailElement() {

	//return the tail element
	return this->tail->element;

}

//function to set length of list
template <class T>
void MyList<T>::setLength(int length) {

	//set the length of the list
	this->length = length;

}

//function to get length of list
template <class T>
int MyList<T>::getLength() {

	//return the length of the list
	return this->length;

}

//function to move current to the next element
template <class T>
void MyList<T>::moveToNext() {

	//move current to the next element
	current = current->next;

}

//function to add element to head of list
template <class T>
void MyList<T>::addToHead(T head) {

	//create new head node and link to current head
	Node<T>* newHead = createNewNode(head);
	newHead.next = getHead();
	
	//set head to the new head node
	this->head = &newHead;

}

//function to add element to tail of list
template <class T>
void MyList<T>::addToList(T newItem) {

	//create new Node to store element and pointer
	Node<T> *temp = new Node<T>();
	temp->element = newItem;
	temp->next = NULL;

	//set current tail to point to this new Node element
	this->tail->next = temp;

	//set current tail to this new node
	tail = temp;

	//set current to this new tail
	current = tail;

	//increase the length of this list
	this->length++;

}

//function to display entire list
template <class T>
void MyList<T>::displayList() {

	//set current to point towards head of list
	setCurrent(getHead());

	//if head is NULL, empty list
	if (isEmpty()) {

		//display message
		cout << "empty list";

	}

	//if list is not empty
	else {

		//loop through the whole list
		for (int i = 0; i < length; i++) {

			//call the displayAsRow() function in each class
			getCurrentElement().displayAsRow();

			//if not at the end of the list
			if (i != length - 1) {

				//move to the next element in the list
				moveToNext();

			}

		}

	}

}

//function to pop the last element out of list
template <class T>
T MyList<T>::pop() {

	//set current pointer to head
	current = head;

	//check if the list is empty
	if (isEmpty()) {

		//display mesage
		cout << "Empty list" << endl;

	}

	//if list is not empty and has more than 1 element
	else if(getCurrent()->next != NULL) {
		
		//while current is not the element before tail
		while (true) {
			
			//if current is not the element before tail
			if (getCurrent()->next != getTail()) {

				//move to next element
				moveToNext();

			}

			//if current is the last element before tail
			else {

				//break out of the loop
				break;
			
			}

		}

		//create temp T object and initialize with tail element
		T temp = getTailElement();

		getCurrent()->next = NULL;

		//move tail to current element
		tail = getCurrent();
		
		this->length--;

		//return the temp object
		return temp;
	
	}

	else {

		//create temp T object and initialize with tail element
		T temp = getTailElement();

		//set list back to empty list
		this->head = NULL;
		this->current = NULL;
		this->tail = NULL;

		this->length = 0;

		return temp;
	
	}


}

//function to check if the list is empty
template <class T>
boolean MyList<T>::isEmpty() {

	//if head is null
	if (getHead() == NULL) {
	
		//return true
		return true;
	
	}

	//if head is not null
	else {
		
		//return false
		return false;

	}

}

//function to create new Node pointer
template <class T>
Node<T>* MyList<T>::createNewNode(T element) {

	//create a new Node and return it
	Node<T> *temp = new Node<T>();
	temp->element = element;
	temp->next = NULL;

	//return the created node pointer
	return temp;

}

//function to remove item from list
template <class T>
T MyList<T>::removeFromList(int index) {

	T temp;

	this->current = getHead();

	//if this is the first element
	if (index == 1 && getLength() > 1) {

		temp = getCurrentElement();

		moveToNext();
		this->head = getCurrent();
		this->length--;
	}

	//if this is not the first or last element
	else if (index > 1 && index < getLength()) {

		//move from head to the element before the element to delete
		for (int i = 1; i < index-1; i++) {
		
			moveToNext();

		}

		Node<T>* before = getCurrent();
		moveToNext();
		Node<T>* toDelete = getCurrent();

		before->next = toDelete->next;
		this->length--;

		temp = toDelete->element;
			
	}

	//if this is the last element
	else if (index == getLength()) {

		temp = pop();

	}

	//if this is not within this list (wrong input)
	else {

		cout << "Wrong input - Out of Bound";
		cout << endl;

	}

	return temp;
	
}

//function to go to head
template <class T>
void MyList<T>::goToHead() {

	this->current = getHead();

}

#endif