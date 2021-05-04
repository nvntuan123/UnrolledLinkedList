#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

#include "Node.h"
#include "UnrolledLinkedList.h"

using namespace std;

void parseFile(string filename)
{
	UnrolledLinkedList *list1 = NULL;
	ofstream ofs("output.txt", ofstream::out);
	ifstream ifs;
	ifs.open(filename);
	char command;
	int pos, val;
	char str[4084];

	try
	{
		while (ifs >> command)
		{
			switch (command)
			{
			case 'u': // create an object of UnrolledLinkedList
				ifs >> val;
				if (list1 != NULL)
					delete list1;
				list1 = new UnrolledLinkedList(val);
				break;
			case 'a': // append an element the the end of the list
				ifs >> val;
				list1->add(val);
				break;
			case 'c': // check if an element is in the list or not
				ifs >> val;
				sprintf(str, "The list contains %d: %s\n", val, list1->contains(val) ? "yes" : "no");
				ofs << str;
				break;
			case 'd': // delete an element at pos position in the list
				ifs >> pos;
				list1->deleteAt(pos);
				break;
			case 'f': // return the index of the first occurence of a specific element in the list
				ifs >> val;
				//sprintf(str,"The list contains %d: %s\n", val, list1->contains(val)?"yes":"no");
				sprintf(str, "First occurrence of %d is at %d\n", val, list1->firstIndexOf(val));
				ofs << str;
				break;
			case 'g': // returns the element at the specified position in this list.
				ifs >> pos;
				sprintf(str, "The element at position %d is %d\n", pos, list1->getAt(pos));
				ofs << str;
				break;
			case 'i': // insert a new element to pos position in the list
				ifs >> pos >> val;
				list1->insertAt(pos, val);
				break;
			case 'l': // return the index of the last occurence of a specific element in the list
				ifs >> val;
				sprintf(str, "Last occurrence of %d is at %d\n", val, list1->lastIndexOf(val));
				ofs << str;
				break;
			case 'p': // print the content of the list
				list1->print(ofs);
				break;
			case 'r': // reverse the list
				list1->reverse1();
				break;
			case 's': // replaces the element at the specified position in this list with the specified element.
				ifs >> pos >> val;
				list1->setAt(pos, val);
				break;

			default:
				throw "Wrong input format!";
			}
		}
	}
	catch (char const *s)
	{
		sprintf(str, "An exception occurred. Exception type: %s\n", s);
		ofs << str;
	}

	if (list1 != NULL)
		delete list1;
	ifs.close();
	ofs.close();
}

int main()
{
    parseFile("input.txt");
    return 0;
}
