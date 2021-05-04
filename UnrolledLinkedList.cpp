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
    if (numOfNodes == 1)
	{
		head->removeAt(pos);
		if (head->numElements == 0)
		{
			delete head;
			head = tail = NULL;
			--numOfNodes;
		}
	}

	int iIndex = 0;
	for (Node* i = head; i != NULL; i = i->next)
	{
		for (size_t j = 0; j < i->numElements; j++)
		{
			if (iIndex == pos)
			{
				if (i->numElements > i->getHalfNodeSize())
				{
					i->removeAt(j);
					return;
				}
				else
				{
					if (i == head)
					{
						if (head->next->numElements > head->getHalfNodeSize())
						{
							head->removeAt(j);
							head->add(head->next->elements[0]);
							head->next->removeAt(0);
							return;
						}
						else
						{
							head->removeAt(j);
							for (size_t k = 0; k < head->next->getHalfNodeSize(); k++)
							{
								head->add(head->next->elements[k]);
							}
							Node* pDeleteNode = head->next;
							if (pDeleteNode->next)
							{
								pDeleteNode->next->prev = head;
							}
							else
							{
								tail = head;
							}
							head->next = pDeleteNode->next;
							delete pDeleteNode;
							numOfNodes--;
							return;
						}
						
					}
					else if (i == tail)
					{
						if (tail->prev->numElements > tail->getHalfNodeSize())
						{
							tail->removeAt(j);
							tail->insertAt(0, tail->prev->elements[tail->prev->numElements - 1]);
							tail->prev->removeAt(tail->prev->numElements - 1);
							return;
						}
						else
						{
							tail->removeAt(j);
							for (size_t g = 0; g < tail->numElements; g++)
							{
								tail->prev->add(tail->elements[g]);
							}
							Node* pDeleteNode = tail;
							tail = tail->prev;
							tail->next = NULL;
							delete pDeleteNode;
							numOfNodes--;
							return;
						}
					}
					else
					{
						if (i->next->numElements > i->next->getHalfNodeSize())
						{
							i->removeAt(j);
							if (i->prev->numElements == i->prev->getHalfNodeSize())
							{
								for (size_t g = 0; g < i->numElements; g++)
								{
									i->prev->add(i->elements[g]);
								}

								Node* pDeleteNode = i;
								if (pDeleteNode->next)
								{
									pDeleteNode->next->prev = pDeleteNode->prev;
								}
								else
								{
									tail = pDeleteNode->prev;
								}
								
								if (pDeleteNode->prev)
								{
									pDeleteNode->prev->next = pDeleteNode->next;
								}
								delete pDeleteNode;
								numOfNodes--;
								return;
							}
							else
							{
								i->add(i->next->elements[0]);
								i->next->removeAt(0);
								return;
							}
						}
						else
						{
							i->removeAt(j);
							for (size_t h = 0; h < i->next->getHalfNodeSize(); h++)
							{
								i->add(i->next->elements[h]);
							}
							
							Node* pNodeTemp = i->next;
							if (pNodeTemp->next)
							{
								pNodeTemp->next->prev = pNodeTemp->prev;
							}
							else
							{
								tail = pNodeTemp->prev;
							}
							
							if (pNodeTemp->prev)
							{
								pNodeTemp->prev->next = pNodeTemp->next;
							}
							delete pNodeTemp;
							numOfNodes--;
							return;
						}
					}
				}
			}
		}
	}
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

