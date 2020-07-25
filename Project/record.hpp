#ifndef RECORD_HPP_INCLUDED
#define RECORD_HPP_INCLUDED

#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstdio>
#include <vector>
#include <iterator>

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
	int delete_record(std::string name);
	int edit_record(std::string *record, std::string name, std::string num);
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
		std::ofstream my_file("phonebook.txt", std::ofstream::app);
		if (my_file.is_open()) {
		    my_file << "\n";
		    my_file << node1->name;
		    my_file << "\n";
		    my_file << std::to_string(node1->num);
		}
		my_file.close();
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
	std::ifstream my_file ("phonebook.txt");
	std::string line;
	if(my_file.is_open()) {
		while(getline(my_file, line)) {
		    std::cout << line << '\n';
		}
	} else {
		std::cout << "Can't open file.";
	}
	my_file.close();
}

int Record::delete_record(std::string name) {
    	std::vector<std::string> buffer;

	std::ifstream my_file ("phonebook.txt");
	std::string line;

	std::ofstream temp("temp.txt");

	if(my_list == NULL)
        	return -1;

	if(temp.is_open()) {
		while(getline(my_file, line)) {
		    if(name == line) {
			buffer.push_back("aha");
		    }
            	buffer.push_back(line);
        	}
        	std::ostream_iterator<std::string> output_iterator(temp, "\n");
        	std::copy(buffer.begin(), buffer.end() - 1, output_iterator);
    	}
    	my_file.close();
    	temp.close();

    	remove("phonebook.txt");
    	rename("temp.txt", "phonebook.txt");

    	return 0;
}

int Record::edit_record(std::string *record, std::string name, std::string num) {
	int rec_exists = 0;
	std::vector<std::string> buffer;

	std::ifstream my_file ("phonebook.txt");
	std::string line;

	std::ofstream temp("temp.txt");

	if(my_list == NULL)
        	return -1;

	if(temp.is_open()) {
		while(getline(my_file, line)) {
		    if(name == line) {
			buffer.push_back("aha");
		    }
		    buffer.push_back(line);
		}
		std::ostream_iterator<std::string> output_iterator(temp, "\n");
		std::copy(buffer.begin(), buffer.end(), output_iterator);
    	}
	my_file.close();
	temp.close();

	 remove("phonebook.txt");
	 rename("temp.txt", "phonebook.txt");

	 if(rec_exists == 0) {
		std::cout << "The record doesn't exist!\n";
		return NULL;
	 }

	 return 0;
}

#endif // RECORD_HPP_INCLUDED
