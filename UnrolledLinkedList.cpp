#include"UnrolledLinkedList.h"

void UnrolledLinkedList::add(int val) {
	// TODO
	if (!head)
	{
		head = tail = new Node(nodeSize);
		numOfNodes++;
		head->add(val);
		size1++;
		return;
	}
	if (tail->isFull())
	{
		Node* pNewNode = new Node(nodeSize);
		numOfNodes++;
		for (size_t i = tail->getHalfNodeSize(); i < nodeSize; i++)
		{
			pNewNode->add(tail->elements[i]);
		}
		tail->numElements = tail->getHalfNodeSize();
		pNewNode->add(val);
		size1++;

		tail->next = pNewNode;
		pNewNode->prev = tail;

		return;
	}
	else
	{
		tail->add(val);
		size1++;
		return;
	}
}

int UnrolledLinkedList::getAt(int pos) {
	if (pos < 0 || pos >= size1)
		throw "IndexOutOfBoundsException"; // check whether pos is valid or not
	for (Node* i = head; i != NULL; i = i->next)
	{
		pos -= i->numElements;
		if (pos < 0)
		{
			return (i->elements[i->numElements + pos]);
		}
	}
}

void UnrolledLinkedList::setAt(int pos, int val) {
	if (pos < 0 || pos >= size1)
		throw "IndexOutOfBoundsException"; // check whether pos is valid or not
	// TODO
    for (Node* i = head; i != NULL; i = i->next)
	{
		pos -= i->numElements;
		if (pos < 0)
		{
			i->elements[i->numElements + pos] = val;
			return;
		}
	}
}

void UnrolledLinkedList::insertAt(int pos, int val) {
	if (pos < 0 || pos > size1)
		throw "IndexOutOfBoundsException"; // check whether pos is valid or not
	// TODO
	if (pos == size1)
	{
		this->add(val);
		return;
	}
	
	for (Node* i = head; i != NULL; i = i->next)
	{
		pos -= i->numElements;
		if (pos < 0)
		{
			int iIndex = i->numElements + pos;
			if (!i->isFull())
			{
				i->insertAt(iIndex, val);
				size1++;
				return;
			}
			else
			{
				size1++;
				int itemp = i->elements[i->numElements - 1];
				i->removeAt(i->numElements - 1);
				i->insertAt(iIndex, val);
				
				Node* pNewNode = new Node(nodeSize);
				numOfNodes++;

				for (size_t j = i->getHalfNodeSize(); j < nodeSize; j++)
				{
					pNewNode->add(i->elements[j]);
					for (size_t k = i->numElements; k >= i->getHalfNodeSize(); k--)
					{
						i->removeAt(k);
					}
					pNewNode->add(itemp);

					pNewNode->next = i->next;
					i->next = pNewNode;
					pNewNode->prev = i;

					if (pNewNode->next)
					{
						pNewNode->next->prev = pNewNode;
					}
					if (i == tail)
					{
						tail = pNewNode;
					}
					return;
				}
			}
		}
	}
}

void UnrolledLinkedList::deleteAt(int pos)
{
	if (pos < 0 || pos >= size1)
		throw "IndexOutOfBoundsException"; // check whether pos is valid or not
	// TODO
    
}

int UnrolledLinkedList::firstIndexOf(int val) {
	// TODO
    int iIndexFirst = 0;
	for (Node* i = head; i != NULL; i = i->next)
	{
		for (size_t j = 0; j < i->numElements; j++)
		{
			if (i->elements[j] == val)
			{
				return iIndexFirst;
			}
			iIndexFirst++;
		}
	}

    return -1;
}

int UnrolledLinkedList::lastIndexOf(int val) {
	// TODO
    int iIndexLast = size1 - 1;
	for (Node* i = tail; i != NULL; i = i->prev)
	{
		for (size_t j = i->numElements; j >= 0; j--)
		{
			if (i->elements[j] == val)
			{
				return iIndexLast;
			}
			iIndexLast++;
		}
	}

    return -1;
}

bool UnrolledLinkedList::contains(int val) {
	// TODO
    for (Node* i = head; i != NULL; i = i->next)
	{
		for (size_t j = 0; j < i->numElements; j++)
		{
			if (i->elements[j] == val)
			{
				return true;
			}
		}
	}

    return false;
}

void UnrolledLinkedList::reverse1() {
	// TODO
	if (!head)
	{
		return;
	}
	
	for (Node* i = tail; i != NULL; i = i->prev)
	{
		swap(i->next, i->prev);
		i->reverse();
	}
}

