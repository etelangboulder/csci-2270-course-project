// CPP program to implement hashing with chaining
#include <iostream>
#include "hash.hpp"
#include <sstream>

using namespace std;

node* HashTable::createNode(string restaurantName, node* next)
{
    node* newNode = new node();
    newNode->restaurantName = restaurantName;
    newNode->next = next;
    newNode->pq = *(new PriorityQ(50));

    return newNode;
}

HashTable::HashTable(int bsize)
{
    numCollision = 0;
    tableSize = bsize;
    table = new node*[tableSize];
}

HashTable::~HashTable()
{
    for(int i = 0; i < tableSize; i++){
        node* current = table[i];
        node* temp = nullptr;

        while(current != nullptr){
            temp = current;
            current = current->next;
            delete temp;
            temp = nullptr;
        }
    }
}

void HashTable::displayTable()
{
    for(int i = 0; i < tableSize; i++){
        node* current = table[i];

        cout << i << " | ";
        while(current != nullptr){
            cout << current->restaurantName << "-->";
            current = current->next;
        }
        cout << "NULL" << endl;
    }
}

unsigned int HashTable::hashFunction(string restaurantName)
{
    int hashValue = 0;
    for(int i = 0; i < restaurantName.size(); i++){
        hashValue += int(restaurantName[i]);
    }
    hashValue %= tableSize;
    return hashValue;
}

node* HashTable::searchItem(string restaurantName)
{
    int hashValue = hashFunction(restaurantName);
    node* current = table[hashValue];
    while(current != nullptr){
        if(current->restaurantName == restaurantName){
            return current;
        }
        current = current->next;
    }

    return current;
}

void HashTable::insertItem(ReviewInfo restaurant)
{
    string name = restaurant.restaurantName;
    node* res = searchItem(name);

    if(res != nullptr){
        res->pq.insertElement(restaurant);
    }
    else{
        int hashValue = hashFunction(name);
        node* temp = table[hashValue];

        if(temp != nullptr){
            numCollision++;
        }
        table[hashValue] = createNode(name, temp);
        table[hashValue]->pq.insertElement(restaurant);
    }
}


void HashTable::setup(string fname)
{
    ifstream input(fname);
    string line;

    string restaurantName;
    string review;
    string customer;
    string time;

    if (input.is_open())
    {
        while (getline(input, line))
        {
            stringstream ss(line);
            getline(ss, restaurantName, ';');
            getline(ss, review, ';');
            getline(ss, customer, ';');
            getline(ss, time);
            
            ReviewInfo info = {restaurantName, review, customer, stoi(time)};
            insertItem(info);
        }
    }
}