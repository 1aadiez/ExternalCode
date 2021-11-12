#ifndef HASHTABLE_H
#define HASHTABLE_H


#include <iostream>
#include <cmath>
#include <string>
#include <stdio.h>


namespace htable
{

	class Element
	{
	private:
		long int key;
		bool busy;
		std::string data;

	public:
		explicit Element(): key(0), busy(false), data("NULL") {};
		explicit Element(long int k, bool b, std::string(d)): key(k), busy(b), data(d) {};
		

		void set_key(long int arg);
		void set_busy(bool arg);
		void set_data(std::string arg);

		const int get_key() { return key; }
		const bool get_busy() { return busy; }
		const std::string get_data() { return data; }


	};


	class HTable
	{
	private:
		int size;
		int capacity;
		Element* arr;
		

		int hash(int k);


	public:
		explicit HTable();
		explicit HTable(int arg) : size(arg), capacity(0) { arr = new Element[size]; };
		
		const int get_size() { return size; }
		const int get_capacity() { return capacity; }

		HTable& add (int k, std::string d);
		const std::string print();
		HTable& garbage_cleaner();
		HTable& remove(int k);
		HTable& resize(int value);
		Element& get(int k);

		HTable& operator+(std::string d);
		HTable& operator-(int k);
		Element& operator^(int k);
		~HTable() {
			delete[] arr;
		}
	};

}


#endif 
