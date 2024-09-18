#include <iostream>
#include "hash.hpp"
#include "PriorityQueue.hpp"
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

void displayMenu() // do not modify
{
    cout << "------------------" << endl;
    cout << "1: Build the data structure (execute this option one time)" << endl;
    cout << "2: Add a review" << endl;
    cout << "3: Retrieve most recent review for a restaurant" << endl;
    cout << "4: Pop most recent review for a restaurant" << endl;
    cout << "5: Print reviews for a restaurant" << endl;
    cout << "6: Display number of collisions" << endl;
    cout << "7: Display table results" << endl;
    cout << "8: Exit" << endl;
    cout << "------------------" << endl;
}

int main(int argc, char* argv[])
{
    if (argc <3)
    {
        cout<<"need correct number of arguments"<<endl;
    }
	
    string fname = argv[1];
    int tableSize = stoi(argv[2]);
    int ch = 0;
    string chs;
    HashTable ht(5);
	
    while(ch!=8)
    {
        displayMenu();
        cout << "Enter your choice >>";
        getline(cin, chs);
        ch = stoi(chs);
        switch (ch)
        {
            case 1:
			{
				ht.setup("test.txt");

				break;
            }
            case 2:
			{
                string restaurantName;
                string review;
                string customer;
                string time;

                cout << "Restaurant Name: " << endl;
                getline(cin, restaurantName);
                cout << "Customer: " << endl;
                getline(cin, review);
                cout << "Review: " << endl;
                getline(cin, customer);
                cout << "Time " << endl;
                getline(cin, time);

                ReviewInfo info = {restaurantName, review, customer, stoi(time)};
                ht.insertItem(info);

				break;
            }
            case 3:
			{
                string restaurantName;

                cout << "Restaurant Name: " << endl;
                getline(cin, restaurantName);
                node* currentNode = ht.searchItem(restaurantName);
                if(currentNode == nullptr){
                    cout << "no record found for peek." << endl;
                }
                else{
                    currentNode->pq.peek();
                }
                
				break;
            }
            case 4:
			{
                string restaurantName;

                cout << "Restaurant Name: " << endl;
                getline(cin, restaurantName);
                node* currentNode = ht.searchItem(restaurantName);
                if(currentNode == nullptr){
                    cout << "no record found for pop." << endl;
                }
                else{
                    currentNode->pq.pop();
                }

				break;
            }
            case 5:
			{
				string restaurantName;

                cout << "Restaurant Name: " << endl;
                getline(cin, restaurantName);
                node* currentNode = ht.searchItem(restaurantName);
                if(currentNode == nullptr){
                    cout << "no record found for print." << endl;
                }
                else{
                    cout << "Restaurant Name: " << restaurantName << endl;
                    currentNode->pq.print();
                }

				break;
			}
            case 6:
                cout << "Number of Collisions: " << ht.getNumCollision() << endl;

                break;
            case 7:
                ht.displayTable();
                
                break;
            case 8:
                return 0;

				break;
            default:
                cout << "Enter a valid option." << endl;

                break;
        }
    }
}
