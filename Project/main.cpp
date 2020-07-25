
#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdlib.h>
#include <string>
#include <iterator>
#include "record.hpp"

using std::cout;
using std::cin;
using std::endl;

Record *node1, *node2, *use_me;
Record *my_list = node1->get_node();

int main()
{
    int choice = 0, val = 0;
    std::string chosen_record_name, chosen_record_num;
    std::string name, num;

    std::string line;

    system("cls");

    std::ifstream my_file ("phonebook.txt");
    if(!my_file.is_open()) {
        cout << "The file can't be opened!";
        cin.get();
        exit(1);
    }
    my_file.close();

    do {
        cout << "Menu:" << endl;
        cout << "1. Add a new phone record." << endl;
        cout << "2. Delete an existing record." << endl;
        cout << "3. Show all records." << endl;
        cout << "4. Edit a record." << endl;
        cout << "5. Exit." << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                //adding a record
                node1 = use_me->get_record();
                val = use_me->insert_record(node1);
                if(val == -1)
                    cout << "This record already exists! Try again: ";
                else
                    cout << "Record successfully stored.\n";
                break;
            case 2:
                //deleting a record
                cout << "Enter the phone number you wish to delete: \n";
                cin >> num;
                cout << "Enter the name: \n";
                cin >> name;
                val = use_me->delete_record(name, num);

                if(val == -1)
                    cout << "This record doesn't exist! Try again: ";
                else if(val == 0)
                    cout << "Record successfully deleted\n";
            case 3:
                //displaying all records
                use_me->show_records();
                break;
            case 4:
                //editing a record
                cout << "Enter the name of the record you wish to edit: \n";
                cin >> chosen_record_name;
                cout << "Enter the  phone number of the record you wish to edit: \n";
                cin >> chosen_record_num;
                cout << "Enter the new name: \n";
                cin >> name;
                cout << "Enter the new phone number: \n";
                cin >> num;

                //check if a number was entered
                for(std::string::iterator it = chosen_record_num.begin(); it != chosen_record_num.end(); it++) {
                    if(std::isdigit(*it))
                        val = use_me->edit_record(chosen_record_name, chosen_record_num, name, num);
                }

                if(val == -1)
                    cout << "This record doesn't exist! Try again: ";
                else if(val == 0)
                    cout << "Record successfully edited\n";

                use_me->show_records();
                break;
            case 5:
                //exiting
                exit(1);
                break;
        }
        cin.get();
    }
    while(true);

    return 0;
}
