//
//  main.cpp
//  LLTemplate


#include <iostream>
#include <fstream>
#include <cmath> 
#include "slist.h"
#include <cstdlib>
using namespace std;
LinkedList* simpleSortTotal(LinkedList* a, int c);
LinkedList* sort_list(LinkedList* a);
double distanceEarth(double latitude1, double longitude1, double latitude2, double longitude2);
int main(){
    ifstream infile;
    int i = 0;
    char cNum[10];
    LinkedList* airportArr = new LinkedList();
    int airportCount;
    infile.open ("USAirportCodes.csv", ifstream::in);
    if (infile.is_open())
    {
        int c = 0;
        while (infile.good())
        {
            airportArr->add(new Airport());
            infile.getline(airportArr->get(c)->code, 256, ',');
            infile.getline(cNum, 256, ',');
            airportArr->get(c)->longitude = atof(cNum);
            infile.getline(cNum, 256, '\n');
            airportArr->get(c)->latitude = atof(cNum);
            if (!(c % 1000)){
				cout << airportArr->get(c)->code << " long: " << airportArr->get(c)->longitude << " lat: " << airportArr->get(c)->latitude <<  endl;}
            
			i++;
			c++;
        }
        airportCount = c-1;
        infile.close();
		LinkedList* arr = new LinkedList();
		LinkedList* sorted = new LinkedList();

    int lengthofarr = 0;
		for (int i = 0;i<airportCount;i+= 1000){ 
			arr->add(airportArr->get(i));
			lengthofarr ++;
		}
  
			for (int i = 0;i<100;i++){
				arr = sort_list(arr);
			}
	    sorted = simpleSortTotal(arr, lengthofarr);
		cout << endl;
         for (int c=0; c < lengthofarr; c++){
                cout << arr->get(c)->code << " long: " <<  arr->get(c)->longitude << " lat: " <<  arr->get(c)->latitude <<  endl;
                cout <<"Distance between " << arr->get(c)->code << " and AUS is " << distanceEarth(  arr->get(c)->latitude,  arr->get(c)->longitude ,  97.6700,  30.1944) << endl;
		 }



    }
    else
    {
        cout << "Error opening file";
    }
}
#define pi 3.14159265358979323846
#define earthRadiusKm 6371.0

double toradians(double deg) {
  return (deg * pi / 180);
}

double distanceEarth(double latitude1, double longitude1, double latitude2, double longitude2) {
  double latrad1, lonrad1, latrad2, lonrad2, u, v;
  latrad1 = toradians(latitude1);
  lonrad1 = toradians(longitude1);
  latrad2 = toradians(latitude2);
  lonrad2 = toradians(longitude2);
  u = sin((latrad2 - latrad1)/2);
  v = sin((lonrad2 - lonrad1)/2);
  return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(latrad1) * cos(latrad2) * v * v));
}


LinkedList* simpleSortTotal(LinkedList* a, int c){
	double ABlat = 30.1944;
	double ABlong = 97.6700;
	LinkedList* b = new LinkedList();
	Node* largest = a->head;
	Node* tmp = a->head;
	int index = 0;
	int blacklist[] = {
		-1, -1, -1, -1,
		-1, -1, -1, -1,
		-1, -1, -1, -1, -1
	};
	for(int k = 0;k<c;k++){
		for (int i = 1;i<c;i++){
			tmp = tmp->next;
			if (distanceEarth(a->get(i)->latitude, a->get(i)->longitude, ABlat, ABlong) > distanceEarth(largest->data->latitude, largest->data->longitude, ABlat, ABlong)){
				cout<<"bigger found!"<<endl;
				if (blacklist[i] == -1){
					cout<<"not blacklisted!"<<endl;
					if (tmp->data->latitude != a->get(i)->latitude){
						cout << "!!!!!1" << endl;
					}
					largest = tmp;
						index = i;
				}
			}
		}
		b->add(largest->data);
		blacklist[index] = 1;
		cout<<index<<endl;
		tmp = a->head;
		largest = a->head;
	}
	return b;
}

LinkedList* sort_list(LinkedList* a) {
	double ABlat = 30.1944;
	double ABlong = 97.6700;
    Node* n = a->head;
	  Node *top = NULL;
    Node *current = NULL;
    bool sorted = false;
    while (sorted == false) {

        Node *parent = n;
        Node *lowparent = n; 
        Node *low = n; 
        sorted = true;
        do {

            Node* next = parent->next;
            if (distanceEarth(parent->data->latitude, parent->data->longitude, ABlat, ABlong) < distanceEarth(next->data->latitude, next->data->longitude, ABlat, ABlong)){
                lowparent = parent;
                low = next;
                sorted = false;
                }
            parent = parent->next;
            } while (parent->next != NULL);
        if (current != NULL) { 
            current->next = low;
            }
        
        current = low;
        if (current == n){ 
			n = current->next; 
		}
        lowparent->next = low->next;
        current->next = NULL;
        if (top == NULL) {
            top = current;
            }
        };
    current->next = n;
	LinkedList* ret = new LinkedList(top);
    return ret;
    }