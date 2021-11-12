#include "hashtable.h"


namespace htable
{

	void Element::set_key(long int arg) { key = arg; }
	void Element::set_busy(bool arg) { busy = arg; }
	void Element::set_data(std::string arg) {data = arg; }


	int HTable::hash(int k)
	{
		std::size_t h = std::hash<int>{}(k);
		return h % size;
	}


	HTable& HTable::add(int k, std::string d)
	{
		if (capacity >= 0.5 * size) resize(2);
		bool used = false;
		int index = hash(k);

		while(arr[index].get_busy() != false)
		{
			if (capacity == size) break;
			if (arr[index].get_key() == k) {used = true; break;}
			index++;
		}
		arr[index].set_key(k);
		arr[index].set_busy(true);
		arr[index].set_data(d);
		if (used){}
		else capacity++;
		return *this;
	}


	const std::string HTable::print()
	{
		std::string s = "\n";
		for (int i = 0; i < size; ++i)
		{
			if (arr[i].get_busy() != false)
			{
				s = s + "[" + std::to_string(i) + "] " + std::to_string(arr[i].get_key()) + " => " + arr[i].get_data() + "\n";
			}
		}
		return s;
	}
	HTable& HTable::garbage_cleaner()
	{
		for (int i = 0; i < size; ++i)
		{
			if (arr[i].get_busy() == false)
			{
				arr[i].set_key(0);
				arr[i].set_data("NULL");
				arr[i].set_busy(false);
			}
		}
		return *this;
	}


	Element& HTable::get(int k)
	{
		int index = hash(k);
		int att = 0;
		bool nf = false;
		while(arr[index].get_key() != k)
		{
			index++;
			att++;
			if (index == size) index = 0;
			if (att == size - 1)
			{
				nf = true;
				break;
			}
		}
		if ((nf) || (arr[index].get_busy()==false))
			throw std::invalid_argument("Nothing was found");
		else 
			return arr[index];
	}


	HTable& HTable::remove(int k)
	{
		get(k).set_busy(false);
		capacity--;
		if (capacity <= size/4 && size != 4) resize(1);
		return *this;
	}


	HTable& HTable::resize(int value)
	{
		int current_size = size;
		garbage_cleaner();
		capacity = 0;

		Element* tmp = arr;
		if (value == 2) size = size * 2;
		if (value == 1) size = size/2;
		Element* new_arr = new Element[size];
		arr = new_arr;
		
		for (int i = 0; i < current_size; ++i) if (tmp[i].get_busy()) add(tmp[i].get_key(),tmp[i].get_data());
		delete[] tmp;

		return *this;
	}


	HTable& HTable::operator+(std::string d)
	{
		add(d.length(), d);
		return *this;
	}


	HTable& HTable::operator-(int k)
	{
		remove(k);
		return *this;
	}


	Element& HTable::operator^(int k)
	{
		return get(k);
	}
}