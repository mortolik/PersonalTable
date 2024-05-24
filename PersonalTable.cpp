#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<iomanip>
#include "TSortTable.h"
#include "TTreeTable.h"
#include "TArrayHash.h"
#include "TListHash.h"
#include "TBalTreeTable.h"
#include <string>
#include <random>

using namespace std;

enum TTabMode { SCAN_TABLE = 1, SORT_TABLE = 2, TREE_TABLE = 3, HASH_TABLE = 4, LIST_TABLE = 5, BALL_TREE_TABLE = 6 };
TTable* pTab = NULL;
int* pKeys = NULL;
string* pVals = NULL;
int DataCount = 0, MemSize;

void TableGenerator(TTabMode mode) {
	int  MaxKey;
	char Line[100];
	cout << "Input the record's number - ";
	cin >> DataCount;
	cout << "Input the Maximum Key  - ";
	cin >> MaxKey;
	MemSize = DataCount * 3;
	switch (mode) {
	case SCAN_TABLE:
		pTab = new TScanTable(MemSize);
		break;
	case SORT_TABLE:
		pTab = new TSortTable(MemSize);
		break;
	case TREE_TABLE:
		pTab = new TTreeTable();
		break;
	case HASH_TABLE:
		pTab = new TArrayHash(MemSize);
		break;
	case LIST_TABLE:
		pTab = new TListHash(MemSize);
		break;
	case BALL_TREE_TABLE:
		pTab = new TBalTreeTable();
	}
	pKeys = new int[MemSize];
	pVals = new string[MemSize];
	for (int i = 0; i < DataCount; i++) {
		pKeys[i] = rand() % MaxKey;
		pVals[i] = "rec" + to_string(pKeys[i]);
		TRecord tmp(pKeys[i], pVals[i]);
		pTab->Insert(tmp);
	}
	pTab->ClearEfficiency();
}

int TableProcessor(TTabMode mode) {
	int com;
	int key;
	string rec;
	while (1) {
		cout << "0 - New Table, 1 - Find, 2 - Insert, 3 - Delete, 4 - Print, 5 - Exit  ";
		cin >> com;
		if (com == 0)
			return 0;
		if (com == 2) {
			cout << "Input the key of record - ";
			cin >> key;
			cout << "Input the record - ";
			cin >> rec;
		}
		if (com == 1 || com == 3) {
			cout << "Input the key of record - ";
			cin >> key;
		}
		if (com == 1) {
			pTab->ClearEfficiency();
			cout << " Find " << pTab->Find(key) << endl;
			cout << " Efficiency  = " << pTab->GetEfficiency() << endl;
		}
		if (com == 2) {
			pTab->ClearEfficiency();
			if (DataCount >= MemSize)
				cout << "MemBuffer is full" << endl;
			else {
				pKeys[DataCount] = key;
				pVals[DataCount] = rec;
				TRecord tmp(key, pVals[DataCount]);
				pTab->Insert(tmp);
				DataCount++;
			}
		}
		if (com == 3) {
			pTab->ClearEfficiency();
			pTab->Delete(key);
			cout << " Efficiency  = " << pTab->GetEfficiency() << endl;
		}
		if (com == 4)
		{
			pTab->ClearEfficiency();
			if ((mode != TREE_TABLE) && (mode != BALL_TREE_TABLE))
			{
				cout << *pTab; // Table printing
			}
			else
				((TTreeTable*)pTab)->Draw();
		}
		if (com == 5)
		{
			return 1;
		}
	}

}

int main() {
	int TableType;
	int sw = 0;
	cout << "Test for the table" << endl;
	while (!sw)
	{
		cout << "1-Scan, 2-Sort, 3-Tree, 4-Hash, 5-List, 6-BalTree: ";
		cin >> TableType;
		TableGenerator((TTabMode)TableType);
		sw = TableProcessor((TTabMode)TableType);
	}
}