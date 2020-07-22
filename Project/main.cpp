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
Record* Record::my_list;

int main()
{
    int choice = 0, for_delete = 0, val = 0;
    Record* my_list = Record::get_my_list();
    std::string chosen_record;

    std::string line;
    int fl = 0;

    system("cls");

    std::ifstream my_file ("phonebook.txt");
    if(!my_file.is_open()) {
        cout << "The file can't be opened!";
        cin.get();
        exit(1);
    }

    try {
        use_me = node1->get_node();
        Record::set_my_list(use_me->name, use_me->num);
    } catch(Record* use_me) {
        cout << "Nesto ne valja" << use_me;
    }

    my_file.close();

    do {
        system("cls");
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
                    cout << "Record successfully stored.";
                break;
            case 2:
                //deleting a record
                cout << "Enter the phone number you wish to delete: ";
                cin >> val;
                for_delete = use_me->delete_record(val);

                if(for_delete == -1)
                    cout << "This record doesn't exist! Try again: ";
                else if(for_delete == 0)
                    cout << "Record successfully deleted";
            case 3:
                //displaying all records
                use_me->show_records();
                break;
            case 4:
                //editing a record
                cout << "Enter the name or the phone number of the record you wish to edit: ";
                cin >> chosen_record;

                //check if a number was entered
                for(std::string::iterator it = chosen_record.begin(); it != chosen_record.end(); it++)
                {
                    if(std::isdigit(*it))
                        fl = 1;
                }
                node2 = use_me->query(&chosen_record, fl);

                //after the query
                if(node2)
                {
                    cout << "Enter the new name: ";
                    cin >> node2->name;
                    cout << "Enter the new phone number: ";
                    cin >> node2->num;
                }
                break;
            case 5:
                //exiting
                cout << "Exiting, writing back to file...";
                use_me->save_to_file();
                cin.get();
                exit(1);
                break;
        }
        cin.get();
    }
    while(true);

    return 0;
}
