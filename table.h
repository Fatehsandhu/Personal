#include <string>
#include <utility>
#include <iostream>
using namespace std;

template <class TYPE>

class Table {
public:
	Table() {}
	virtual bool update(const string& key, const TYPE& value) = 0;
	virtual bool remove(const string& key) = 0;
	virtual bool find(const string& key, TYPE& value) = 0;
	virtual ~Table() {}
};



template <class TYPE>

class SimpleTable : public Table<TYPE> {

	struct Record {
		TYPE data_;
		string key_;
		Record(const string& key, const TYPE& data) {
			key_ = key;
			data_ = data;
		}

	};

	Record** records_;   //the table
	int max_;           //capacity of the array
	size_t size_;          //current number of records held
	int search(const string& key);
	void sort(Record *rec);
	void grow(Record *rec);

public:
	SimpleTable(int maxExpected);
	SimpleTable(const SimpleTable& other);
	SimpleTable(SimpleTable&& other);
	virtual bool update(const string& key, const TYPE& value);
	virtual bool remove(const string& key);
	virtual bool find(const string& key, TYPE& value);
	virtual const SimpleTable& operator=(const SimpleTable& other);
	virtual const SimpleTable& operator=(SimpleTable&& other);
	virtual ~SimpleTable();
};


//returns index of where key is found.
template <class TYPE>
int SimpleTable<TYPE>::search(const string& key) {
	int rc=-1;
	int low=0;

	int high=size_-1;
	int mid;

	while(low<=high && rc==-1){

	mid=(low+high)/2;

	if(records_[mid]->key_ > key){
	high=mid-1;
	}
	else if(records_[mid]->key_ < key){
	low= mid+1;
	}
	else{
	rc=mid;
	}
	}
	return rc;

	
}



//sort the according to key in table
template <class TYPE>
void SimpleTable<TYPE>::sort(Record *rec) {
	if (size_ == 0)
		records_[0] = rec;
	else {
		for (int i = size_ - 1; i != -1; i--) {
			if (rec->key_ < records_[i]->key_) {
				records_[i + 1] = records_[i];
			}
			else {
				records_[i + 1] = rec;
				break;
			}
		}
	}
	if (rec->key_ <= records_[0]->key_) {
		records_[0] = rec;
	}
}

//grow the array by one element
template <class TYPE>
void SimpleTable<TYPE>::grow(Record *rec) {
	max_ *= 2;      

	Record** newArray = new Record*[max_];

	if (size_ > 0) {
		int i = 0;

		for (i = size_ - 1; i > 0; i--) {
			if (rec->key_ < records_[i]->key_) {
				newArray[i + 1] = records_[i];
			}
			else {
				newArray[i + 1] = rec;
				break;
			}
		}

		for (; i > -1; i--) {
			newArray[i] = records_[i];
		}
	}

	if (size_ == 0) {
		newArray[0] = rec;
		//records_ = newArray;
	}

	delete[] records_;
	records_ = newArray;
}

/* none of the code in the function definitions below are correct.  You can replace what you need
*/
template <class TYPE>
SimpleTable<TYPE>::SimpleTable(int maxExpected) : Table<TYPE>() {
	records_ = new Record*[maxExpected];
	max_ = maxExpected;
	size_ = 0;
}

template <class TYPE>
SimpleTable<TYPE>::SimpleTable(const SimpleTable<TYPE>& other) {
	records_ = new Record*[other.max_];
	max_ = other.max_;
	size_ = 0;
	for (int i = 0; i<other.size_; i++) {
		update(other.records_[i]->key_, other.records_[i]->data_);
	}
}
template <class TYPE>
SimpleTable<TYPE>::SimpleTable(SimpleTable<TYPE>&& other) {
	size_ = other.size_;
	max_ = other.max_;
	records_ = other.records_;
	other.records_ = nullptr;
	other.size_ = 0;
	other.max_ = 0;
}

template <class TYPE>
bool SimpleTable<TYPE>::update(const string& key, const TYPE& value) {
	int idx = search(key); // Search if the key exists.

	//Doesn't exist.
	if (idx == -1) {

		Record* rec = new Record(key, value);
		if (size_ == max_) {
			grow(rec);
		}
		else {
			sort(rec);
		}

		size_++;
	}
	else {//key already exists, replace the data
		records_[idx]->data_ = value;
	}

	return true;
}

template <class TYPE>
bool SimpleTable<TYPE>::remove(const string& key) {
	int idx = search(key);
	if (idx != -1) {
		delete records_[idx];
		for (int i = idx; i<size_ - 1; i++) {
			records_[i] = records_[i + 1];
		}
		size_--;
		return true;
	}
	else {
		return false;
	}
}

template <class TYPE>
bool SimpleTable<TYPE>::find(const string& key, TYPE& value) {
	int idx = search(key);
	if (idx == -1)
		return false;
	else {
		value = records_[idx]->data_;
		return true;
	}
}

template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(const SimpleTable<TYPE>& other) {
	if (this != &other) {
		if (records_) {
			int sz = size_;
			for (int i = 0; i<sz; i++) {
				remove(records_[0]->key_);
			}
			delete[] records_;
		}
		records_ = new Record*[other.max_];
		max_ = other.max_;
		size_ = 0;
		for (int i = 0; i<other.size_; i++) {
			update(other.records_[i]->key_, other.records_[i]->data_);
		}

	}
	return *this;
}

template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(SimpleTable<TYPE>&& other) {
	swap(records_, other.records_);
	swap(size_, other.size_);
	swap(max_, other.max_);
	return *this;
}
template <class TYPE>
SimpleTable<TYPE>::~SimpleTable() {
	if (records_) {
		int sz = size_;
		for (int i = 0; i<sz; i++) {
			remove(records_[0]->key_);
		}
		delete[] records_;
	}
}

template <class TYPE>
class HashTable :public Table<TYPE> {

public:
	HashTable(int maxExpected);
	HashTable(const HashTable& other);
	HashTable(HashTable&& other);
	virtual bool update(const string& key, const TYPE& value);
	virtual bool remove(const string& key);
	virtual bool find(const string& key, TYPE& value);
	virtual const HashTable& operator=(const HashTable& other);
	virtual const HashTable& operator=(HashTable&& other);
	virtual ~HashTable();
};

/* none of the code in the function definitions below are correct.  You can replace what you need
*/
template <class TYPE>
HashTable<TYPE>::HashTable(int maxExpected) : Table<TYPE>() {

}

template <class TYPE>
HashTable<TYPE>::HashTable(const HashTable<TYPE>& other) {

}

template <class TYPE>
HashTable<TYPE>::HashTable(HashTable<TYPE>&& other) {

}

template <class TYPE>
bool HashTable<TYPE>::update(const string& key, const TYPE& value) {
	return true;
}

template <class TYPE>
bool HashTable<TYPE>::remove(const string& key) {
	return true;
}

template <class TYPE>
bool HashTable<TYPE>::find(const string& key, TYPE& value) {
	return true;
}

template <class TYPE>
const HashTable<TYPE>& HashTable<TYPE>::operator=(const HashTable<TYPE>& other) {
	return *this;

}

template <class TYPE>
const HashTable<TYPE>& HashTable<TYPE>::operator=(HashTable<TYPE>&& other) {
	return *this;

}

template <class TYPE>
HashTable<TYPE>::~HashTable() {

}