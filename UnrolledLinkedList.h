

#pragma once
#include <stdio.h>
#include <math.h>
#include <fstream>
#include <string.h>

#include"Node.h"

using namespace std;

class UnrolledLinkedList {
private:
	Node* head;
	Node* tail;
	int size1;
	int numOfNodes;
	int nodeSize;
public:

	// Your tasks: complete the implementation of the below methods in UnrolledLinkedList.h
	void add(int val); // add Tail
	bool contains(int val); // Find value = val
	int getAt(int pos);
	void setAt(int pos, int val);
	int firstIndexOf(int val); // add head
	int lastIndexOf(int val); // add tail
	void insertAt(int pos, int val);
	void deleteAt(int pos);
	void reverse1();
	

	UnrolledLinkedList(int capacity) {
		nodeSize = capacity;
		head = tail = NULL;
		size1 = numOfNodes = 0;
	}

	~UnrolledLinkedList() {
		Node* p;
		while (p = head) {
			head = head->next;
			delete p;
		}
		size1 = numOfNodes = 0;
		head = tail = NULL;
	}

	int getSize() { return size1; }
	int getHalfNodeSize() {return (int)ceil(nodeSize / 2.0);}

	void print(ofstream &ofs) {
        char str[80];
		Node* p = head;
		if (p == NULL) {
            strcpy(str, "NULL\n");
			ofs << str;
			return;
		}

		while (p != NULL) {
			strcpy(str, "[");
			ofs << str;
            for (int i = 0; i < p->numElements; i++)
            {
                sprintf(str, "%3d ", p->elements[i]);
                ofs << str;
            }

			ofs << "]";
			ofs << "\n";

			p = p->next;
		}
	}
};

