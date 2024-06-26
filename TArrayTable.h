#pragma once
#include<exception>
#include"TTable.h"



class TArrayTable :public TTable
{
protected:
	TRecord* arr;
	int size, currentPos;

public:
	TArrayTable(int _size = MAX_SIZE)
	{
		if (_size > MAX_SIZE)
		{
			throw std::exception();
		}
		this->size = _size;
		arr = new TRecord[size];
		currentPos = 0;
	};
	TArrayTable(const TArrayTable& other)
	{
		dataCount = other.dataCount;
		efficiency = other.efficiency;
		size = other.size;
		arr = new TRecord[size];
		for (int i = 0; i < size; i++)
		{
			arr[i] = other.arr[i];
		}
		currentPos = other.currentPos;
	}
	~TArrayTable() { delete[] arr; }

	bool IsFull() const override { return dataCount == size; }

	void GoNext() override { currentPos++; }
	void Reset() override { currentPos = 0; }
	bool IsEnd() override { return currentPos == dataCount; }

	TRecord GetCurrentRecord() override {
		return arr[currentPos];
	}
	void SetCurrentRecord(TRecord record) override { arr[currentPos] = record; }
	virtual int GetSize() { return size; }
	virtual int GetCurrentPos() { return currentPos; }
	virtual void SetCurrentPos(int _curPos)
	{
		if (_curPos < size)
		{
			currentPos = _curPos;
		}
		else {
			throw std::exception();
		}
	}


	friend std::ostream& operator<<(std::ostream& os, TArrayTable& tab)
	{
		os << "Output:" << std::endl;
		std::cout << "Key" << " " << "Value" << std::endl;
		for (tab.Reset(); !tab.IsEnd(); tab.GoNext())
		{
			if (tab.GetCurrentRecord().key <= 9)
			{
				std::cout << tab.GetCurrentRecord().key << "   " << std::left << tab.GetCurrentRecord().value << std::endl;
			}
			else if (tab.GetCurrentRecord().key >= 10 && tab.GetCurrentRecord().key <= 99)
			{
				std::cout << tab.GetCurrentRecord().key << "  " << std::left << tab.GetCurrentRecord().key << std::endl;
			}
			else
			{
				std::cout << tab.GetCurrentRecord().key << " " << std::left << tab.GetCurrentRecord().key << std::endl;
			}
		}
		return os;
	}
};


