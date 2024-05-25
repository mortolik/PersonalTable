#pragma once
#include<string>
#include<iostream>
using namespace std;
typedef int TKey;
typedef std::string TValue;
constexpr auto MAX_SIZE = 999;
struct TRecord
{
	TKey key;     
	TValue value; 

	TRecord()
	{
		key = 0;
		value = "";
	}

	TRecord(TKey key, TValue value)
	{
		this->key = key;
		this->value = value;
	}

	TRecord& operator=(const TRecord& other)
	{
		key = other.key;
		value = other.value;
		return *this;
	}
	bool operator == (TRecord other)
	{
		if (this->value == other.value)
			return true;
		else
			return false;
	}

	void output()
	{
		std::cout << "( " << key << "  " << value << " )" << std::endl;
	}
	bool operator != (const TRecord& other)
	{
		return !(*this == other);
	}
	void Print(ostream& os) { os << key << " " << value; }
};

class TTable
{
protected:
	int dataCount;   
	int efficiency;

public:
	TTable() { dataCount = 0; efficiency = 0; };
	virtual ~TTable() { };

	int GetDataCount() const { return dataCount; }
	int GetEfficiency() const { return efficiency; }
	void ClearEfficiency() { efficiency = 0; }

	bool IsEmpty() const { return dataCount == 0; }
	virtual bool Find(TKey) = 0;
	virtual bool IsEnd() = 0;
	virtual bool Insert(TRecord record) = 0;
	virtual bool IsFull() const = 0;
	virtual void Reset() = 0;
	virtual bool Delete(TKey key) = 0; 
	virtual void GoNext() = 0;
	virtual TRecord GetCurrentRecord() = 0;

	virtual void SetCurrentRecord(TRecord record) = 0;   
	friend ostream& operator<<(ostream& os, TTable& tab) {
		cout << "Table printing" << endl;
		for (tab.Reset(); !tab.IsEnd(); tab.GoNext()) {
			os << " Key: " << tab.GetCurrentRecord().key << " Val: " << tab.GetCurrentRecord().value << endl;
			tab.efficiency++;
		}
		return os;
	}
};

