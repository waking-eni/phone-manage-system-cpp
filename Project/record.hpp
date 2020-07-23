#ifndef RECORD_HPP_INCLUDED
#define RECORD_HPP_INCLUDED

#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstdio>

class Record {
    public:
	    int num;
        std::string name;
		Record *next;
		Record() { num = 0; name = ""; }
		Record* get_node();
		Record* get_record();
		Record* searh_node(int id, int *flag);
		int insert_record(Record *node1);
		void show_records();
		int delete_record(int id);
		Record* query(std::string *record, int flag);
		void save_to_file();
};

extern Record *my_list;

Record* Record::get_node() {
	Record *temp;
	temp = (Record*)malloc(sizeof(Record));
	std::string name;
	std::string num;

	//std::cin.get();
    std::ifstream my_file ("phonebook.txt");
    std::getline(my_file, name);
    std::getline(my_file, num);
    temp->name = name;
    temp->num = std::stoi(num);
    //std::cout << temp->num << " " << temp->name;
    //std::cin.get();

	temp->next = NULL;
    return temp;
}

Record* Record::get_record() {
	Record *temp;
	temp = (Record*)malloc(sizeof(Record));

	std::cout << "Enter the phone number: ";
    std::cin >> temp->num;
    std::cout << "Enter the name: ";
    std::cin >> temp->name;

    temp->next = NULL;
    return temp;
}

Record* Record::searh_node(int id, int *flag) {
	Record *curr, *prev;

	*flag = 0;

	if(my_list == NULL)
		return NULL;
	for(prev = NULL, curr = my_list; (curr); prev = curr, curr = curr->next) {
        if(curr->num == id) {
            *flag = 1;
            break;
        }
    }
    return prev;
}

int Record::insert_record(Record *node1) {
	Record *prev;
	int flag;

	prev = Record::searh_node(node1->num, &flag);

	if(my_list == NULL) {
        my_list = node1; //first node
        return -1;
    } else {
        node1->next = prev->next;
        prev->next = node1; //insert in the middle or end
    }

    return 0;
}

void Record::show_records() {
	Record *curr;

	if(my_list == NULL) {
        std::cout << "The list is empty!";
        return;
    }

    std::cout << "The records: " << std::endl;
    curr = my_list;
    for(curr = my_list; (curr); curr = curr->next) {
        std::cout << "*" << "\t";
        std::cout << curr->name << ", ";
        std::cout << curr->num << "." << std::endl;
    }
}

int Record::delete_record(int id) {
	Record *prev, *temp;
	int flag = 0;

	if(my_list == NULL)
        return -1;

	Record::searh_node(id, &flag);

	if(flag == 0)
        return -1;

    if(prev == NULL) {
        temp = my_list;
        my_list = my_list->next;
        free(temp);
    } else {
        temp = prev->next;
        prev->next = temp->next;
        free(temp);
    }

    return 0;
}

Record* Record::query(std::string *record, int flag) {
	Record *curr, *prev;
	int rec_exists = 0;

	if(my_list == NULL)
        return NULL;

    if(flag == 1) {
        for(prev = NULL, curr = my_list; (curr); prev = curr, curr = curr->next) {
            if((std::to_string(curr->num) == *record) || (curr->name == *record)) {
                rec_exists = 1;
                break;
            }
        }
    }

    if(rec_exists == 0) {
        std::cout << "The record doesn't exist!";
        return NULL;
    }

    return curr;
}

void Record::save_to_file() {
	Record *curr;
	std::ofstream my_file ("phonebook.txt");

    curr = my_list;
    if(curr == NULL) {
        std::cout << "Nothing to write.";
        return;
    }

    for(curr = my_list; (curr); curr = curr->next) {
        if(my_file.is_open()) {
            my_file << curr->name;
            my_file << curr->num;
        }
    }
    my_file.close();
}

#endif // RECORD_HPP_INCLUDED
