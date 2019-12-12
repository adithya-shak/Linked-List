#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

class Airport
{
	public:
		char     code[5];
		double   latitude;
		double   longitude;
};

class Node
{
	public:
	    Node* next;
	    Airport* data;
	    Node();
	    Node(Airport* a);
	    Node(Airport* a, Node* b);
};

class LinkedList{
	public:
		int length;
		Node* head;
		LinkedList();
		LinkedList(Node* h);
		~LinkedList(); 
		void add(Airport* value);
		void clear();
		bool equals(LinkedList* list);
		Airport* get(int index);
		void insert(int index, Airport* value);
		void exchg(int index1, int index2);
		void swap(int index1, int index2);
		bool isEmpty();
		void remove(int index);
		void set(int index, Airport* value);
		int size();
		LinkedList subList(int start, int len);	
		string toString();
};