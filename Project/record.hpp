#ifndef RECORD_HPP_INCLUDED
#define RECORD_HPP_INCLUDED

#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstdio>

class Record {
        static Record *my_list;
    public:
	    int num;
        std::string name;
		Record *next;
		Record() { num = 0; name = ""; }
		static void set_my_list(std::string _name, int _num) { my_list->name = _name; my_list->num = _num; }
		static Record* get_my_list() { return my_list;}
		Record* get_node();
		Record* get_record();
		Record* searh_node(int id, int *flag);
		int insert_record(Record *node1);
		void show_records();
		int delete_record(int id);
		Record* query(std::string *record, int flag);
		void save_to_file();
};

Record* Record::get_node() {
	Record *temp;
	temp = (Record*)malloc(sizeof(Record));
	std::string name;
	std::string num;

	std::cin.get();
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
	Record *curr, *prev, *listt;
	listt = listt->get_my_list();

	*flag = 0;

	if(listt == NULL)
		return NULL;
	for(prev = NULL, curr = listt; (curr); prev = curr, curr = curr->next) {
        if(curr->num == id) {
            *flag = 1;
            break;
        }
    }
    return prev;
}

int Record::insert_record(Record *node1) {
	Record *prev, *listt;
	listt = listt->get_my_list();
	int flag;

	prev = Record::searh_node(node1->num, &flag);

	if(listt == NULL) {
        listt = node1; //first node
        return -1;
    } else {
        node1->next = prev->next;
        prev->next = node1; //insert in the middle or end
    }

    return 0;
}

void Record::show_records() {
	Record *curr, *listt;
	listt = listt->get_my_list();
	int record_number;

	if(listt == NULL) {
        std::cout << "The list is empty!";
        return;
    }

    std::cout << "The records: " << std::endl;
    curr = listt;
    for(curr = listt; (curr); curr = curr->next) {
        std::cout << record_number+1 << ".\t";
        std::cout << curr->name << ", ";
        std::cout << curr->num << ".";
        record_number++;
    }
}

int Record::delete_record(int id) {
	Record *prev, *temp, *listt;
	listt = listt->get_my_list();
	int flag = 0;

	if(listt == NULL)
        return -1;

	Record::searh_node(id, &flag);

	if(flag == 0)
        return -1;

    if(prev == NULL) {
        temp = listt;
        listt = listt->next;
        free(temp);
    } else {
        temp = prev->next;
        prev->next = temp->next;
        free(temp);
    }

    return 0;
}

Record* Record::query(std::string *record, int flag) {
	Record *curr, *prev, *listt;
	listt = listt->get_my_list();
	int rec_exists = 0;

	if(listt == NULL)
        return NULL;

    if(flag == 1) {
        for(prev = NULL, curr = listt; (curr); prev = curr, curr = curr->next) {
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
	Record *curr, *listt;
	listt = listt->get_my_list();
	std::ofstream my_file ("phonebook.txt");

    curr = listt;
    if(curr == NULL) {
        std::cout << "Nothing to write.";
        return;
    }

    for(curr = listt; (curr); curr = curr->next) {
        if(my_file.is_open()) {
            my_file << curr->name;
            my_file << curr->num;
        }
    }
    my_file.close();
}

#endif // RECORD_HPP_INCLUDED
