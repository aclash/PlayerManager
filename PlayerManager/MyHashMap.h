#pragma once
#include "MyVector.h"

//check prime
bool IsPrime(unsigned long long num)
{
	if (num <= 3) {
		return num > 1;
	}
	else if (num % 2 == 0 || num % 3 == 0) {
		return false;
	}
	else {
		for (int i = 5; i * i <= num; i += 6) {
			if (num % i == 0 || num % (i + 2) == 0) {
				return false;
			}
		}
		return true;
	}
}

//next Prim
unsigned long long nextPrime(unsigned long long num)
{
	if (num % 2 == 0)
		num++;
	for (unsigned long long i = num; num += 2;)
		if (IsPrime(num))
			return i;
	return -1;
}

template <typename Key, typename HashedObj>
class MyHashMap
{
public:
	explicit MyHashMap(int size = 101) : array(nextPrime(size)) { makeEmpty(); }
	~MyHashMap(){
	}
	void makeEmpty() {
		currentSize = 0;
		for (auto & entry : array)
			entry.info = EMPTY;
	}
	void clear() {
		makeEmpty();
	}
	bool contains(const Key & x) const { return isActive(findPos(x)); }
	HashedObj& find(const Key& x) {
		int pos = findPos(x);
		auto pp = array[pos].element;
		if (isActive(pos))
			return array[pos].element.second;
	}
	bool insert(const std::pair<Key, HashedObj>& x) {
		int currentPos = findPos(x.first);
		if (isActive(currentPos))
			return false;
		array[currentPos].element = x;
		array[currentPos].info = ACTIVE;
		if (++currentSize > array.size() / 2)
			rehash();
		return true;
	}
	bool insert(const std::pair<Key, HashedObj>&& x) {
		int currentPos = findPos(x.first);
		if (isActive(currentPos))
			return false;
		array[currentPos].element = x;
		array[currentPos].info = ACTIVE;
		auto pp = array[currentPos].element;
		if (++currentSize > array.size() / 2)
			rehash();
		return true;
	}
	bool remove(const Key & x) {
		int currentPos = findPos(x);
		if (!isActive(currentPos))
			return false;
		array[currentPos].info = DELETED;
		return true;
	}
	enum EntryType { ACTIVE, EMPTY, DELETED };
private:
	struct HashEntry
	{
		std::pair<Key, HashedObj> element;
		EntryType info;
		HashEntry(const std::pair<Key, HashedObj> & e = {}, EntryType i = EMPTY)
			: element{ e }, info{ i } { }
		HashEntry(const std::pair<Key, HashedObj> && e, EntryType i = EMPTY)
			: element{ std::move(e) }, info{ i } { }
	};
	MyVector<HashEntry> array;
	int currentSize;
	bool isActive(int currentPos) const { return array[currentPos].info == ACTIVE; }
	int findPos(const Key & x) const {
		int offset = 1;
		int currentPos = myhash(x);
		while (array[currentPos].info != EMPTY &&
			array[currentPos].element.first != x){
			currentPos += offset;				// Compute ith probe
			offset += 2;
			if (currentPos >= array.size())
				currentPos -= array.size();
		}
		return currentPos;
	}
	void rehash(){
		MyVector<HashEntry> oldArray = array;
		array.resize(nextPrime(2 * oldArray.size()));
		for (auto & entry : array)
			entry.info = EMPTY;
		currentSize = 0;
		for (auto & entry : oldArray)
			if (entry.info == ACTIVE)
				insert(std::move(entry.element));
	}
	size_t myhash(const Key & x) const {
		return hash<Key>()(x) % array.size();
	}
};
