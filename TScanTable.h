#pragma once
#include"TArrayTable.h"

class TScanTable :public TArrayTable
{
public:
	TScanTable(int _size = MAX_SIZE) : TArrayTable(_size) {};

	bool Find(TKey key)
	{
		for (int i = 0; i < dataCount; i++)
		{
			efficiency++;
			if (arr[i].key == key)
			{
				currentPos = i;
				return true;
			}
		}
		currentPos = dataCount;
		return false;
	}
	bool Insert(TRecord record) {
		if (IsFull() || Find(record.key)) return false;
		this->arr[this->dataCount] = record;
		efficiency++;
		this->dataCount++;
		return true;
	}

	bool Delete(TKey key) {
		if (!Find(key)) return false;
		arr[currentPos] = arr[dataCount - 1];
		dataCount--;
		efficiency++;
		return true;
	};

	TScanTable operator=(const TScanTable& other)
	{
		this->dataCount = other.dataCount;
		this->efficiency = other.efficiency;
		delete[] this->arr;
		this->size = other.size;
		this->arr = new TRecord[this->size];
		for (int i = 0; i < this->size; i++)
		{
			this->arr[i] = other.arr[i];
		}
		this->currentPos = other.currentPos;
		return *this;
	}
};