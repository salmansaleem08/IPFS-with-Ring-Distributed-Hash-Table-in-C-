#include<iostream>
#include<cmath>
#include"BTree.h"
using namespace std;
struct Machine
{
	int Id;
	int NoOfKeysAssociated;
	Machine(int a = 0, int b = 0) {
		Id = a;
		NoOfKeysAssociated = b;
	}
};
struct RoutingTable {
	int* indexArray;
	int* machineIdArray;
	RoutingTable(int Size =0) {
		if (Size != 0) {
			indexArray = new int[Size]; machineIdArray = new int[Size];
		}
		else {
			indexArray = nullptr; machineIdArray = nullptr;
		}
	}
};
struct MachineNode
{
	RoutingTable fingerTable;
	Machine Data;
	BTree BtreeVar;
	MachineNode* Next;
	int BTreeOrder;
	MachineNode** RoutingArray;
	MachineNode(Machine d, int a): BtreeVar (a){
		Data = d;
		Next = nullptr;
		BTreeOrder = a;
		RoutingArray = nullptr;
	}
};
class RingDht
{
public:
	MachineNode* head;
	int NoOfMachines;
	int NoOfBits;
	int TotalKeys;
	int* MachineArray;
	int StaticVar;
	RingDht(int b , int a) {
		head = nullptr;
		NoOfMachines = 0;
		NoOfBits = b;
		TotalKeys = a;
		MachineArray = new int[TotalKeys];
		StaticVar = 0;
	}
	void insertMachine(int id , int noofKeys, int Order) {
		Machine Data(id,noofKeys);
		MachineNode* temp = new MachineNode(Data , Order);
		if (head == nullptr) {
			head = temp;
			temp->Next = head;
		}
		else {
			MachineNode* Current = head;
			while (Current->Next!=head) {
				Current = Current->Next;
			}
			Current->Next = temp;
			temp->Next = head;
		}
		MachineArray[NoOfMachines++] = id;
		SetRoutingPointersNULL();
		SetRoutingTable();
		PointRoutingPointers();

	}
	void PrintRingDht() {
		cout << "So the Ring Dht Created with the Id's and Order Are As Follow : \n";
		MachineNode* temp = head;
		cout << "\nPrint \n";
		cout << "Id          : ";
		do {
			if (temp->Next != head)
				cout << temp->Data.Id << " -> ";
			else
				cout << temp->Data.Id;
			temp = temp->Next;
		} while (temp != head);
		cout << endl;
		temp = head;
		cout << "Keys        : ";
		do {
			if (temp->Next != head)
				cout << temp->Data.NoOfKeysAssociated << " -> ";
			else
				cout << temp->Data.NoOfKeysAssociated;
			temp = temp->Next;
		} while (temp!= head);
		cout << endl;
		temp = head;
		cout << "Btree Order : ";
		do {
			if (temp->Next != head)
				cout << temp->BTreeOrder << " -> ";
			else
				cout << temp->BTreeOrder;
			temp = temp->Next;
		} while (temp != head);
		cout << endl<<endl<<endl<<endl;
	}
	void SetRoutingTable() {
		
		int Size = NoOfBits;
		MachineNode* tempPtr = head;
		do {
			tempPtr->fingerTable.indexArray = new int[Size];
			for (int i = 0; i < Size; i++)
				tempPtr->fingerTable.indexArray[i] = i + 1;
			tempPtr = tempPtr->Next;
		} while (tempPtr != head);

		tempPtr = head; 
		do {
			tempPtr->fingerTable.machineIdArray = new int[Size];
			for (int i = 0; i < Size; i++) {
				int Var = (tempPtr->Data.Id + pow(2, tempPtr->fingerTable.indexArray[i] - 1));
				Var %= TotalKeys;
				int j = NoOfMachines - 1; int j1 = 0;
				for (int k =0; k < NoOfMachines; k++) {
					if (j1 != 0 && j != NoOfMachines - 1) {
						if (Var > MachineArray[j] && Var <=MachineArray[j1]) {
							tempPtr->fingerTable.machineIdArray[i] = MachineArray[j1];
						}
					}
					else if (Var > MachineArray[j] || Var <= MachineArray[j1]) {
						tempPtr->fingerTable.machineIdArray[i] = MachineArray[j1];
					}
					j = j1;
					j1++;
					if (j1 == NoOfMachines) j1 = 0;
				}
			}
			tempPtr = tempPtr->Next;
		} while (tempPtr != head);
		
	}
	void SetRoutingPointersNULL() {
		MachineNode* TempPtr = head;
		if (TempPtr->RoutingArray) {
			int i = 0;
			while (i < NoOfBits) {
				TempPtr->RoutingArray[i] = nullptr;
				i++;
			}
		}
	}
	void PointRoutingPointers() {
		MachineNode* TempPtr = head;
		do {
			TempPtr->RoutingArray = new MachineNode*[NoOfBits];
			for (int i = 0; i < NoOfBits; i++) {
				MachineNode* Current = head;
				do {
					if (TempPtr->fingerTable.machineIdArray[i] == Current->Data.Id) {
						TempPtr->RoutingArray[i] = Current;
					}
					Current = Current->Next;
				} while (Current != head);
			}
			TempPtr = TempPtr->Next;
		} while (TempPtr != head);
	}
	void PrintRoutingTable() {
		MachineNode* TempPtr = head;
		do {
			PrintRoutingTable(TempPtr);
			TempPtr = TempPtr->Next;
		} while (TempPtr != head);
	}
	void PrintRoutingTable(MachineNode* TempPtr) {
		cout << "Routing Table For Machine : " << TempPtr->Data.Id << endl<<endl;
		for (int i = 0; i < NoOfBits; i++) {
			cout << TempPtr->fingerTable.indexArray[i] << " ... " << TempPtr->fingerTable.machineIdArray[i] << "  Pointed To "<<TempPtr->RoutingArray[i]->Data.Id<<endl;
		}
		cout << endl << endl;
	}
	MachineNode* PrintPathWhileFindingId(int key, MachineNode* TempPtr) {

		int Hash = key;
		cout << "\n\nPath Taken To reach Your Desired Machine \n";
		while (1) {
			TempPtr = SearchUsingRoutingTable(TempPtr, Hash);
			cout << "Jumped To Machine : " << TempPtr->Data.Id << endl;
			if (TempPtr->Data.Id - TempPtr->Data.NoOfKeysAssociated < Hash && TempPtr->Data.Id>=Hash)
				break;
		}
		cout << endl<<endl;
		return TempPtr;
	}
	MachineNode* SearchUsingRoutingTable(MachineNode* Current , int HashValue) {
		if (Current->Data.Id == HashValue) {
			return Current;
		}
		else if (Current->Data.Id < HashValue && HashValue <= Current->fingerTable.machineIdArray[0]) {
			return Current->RoutingArray[0];
		}
		else {
			for (int i = 0; i < NoOfBits-1; i++) {
				if (HashValue > Current->fingerTable.machineIdArray[i] &&
					HashValue <= Current->fingerTable.machineIdArray[i + 1]) {
					return Current->RoutingArray[i];
				}
			}
		}
		return Current->RoutingArray[NoOfBits-1];
	}
	MachineNode* insertnewMachine(int NewMachine , int NewOrder) {
		
		MachineNode* Current = head;
		MachineNode* Previous = head;
		do {
			Previous = Previous->Next;
		} while (Previous->Next != head);

		Machine Var(NewMachine, 0);

		do {
			if (Current == head) {
				if (NewMachine < Current->Data.Id) {
					MachineNode* TempPtr = new MachineNode(Var, NewOrder);
					Previous->Next = TempPtr;
					TempPtr->Next = Current;
					head = TempPtr;
					SetnoOfKeysAssociated();
					return Current;
				}
			}
			else if (NewMachine > Previous->Data.Id && NewMachine < Current->Data.Id) {
				MachineNode* TempPtr = new MachineNode(Var, NewOrder);
				Previous->Next = TempPtr;
				TempPtr->Next = Current;
				SetnoOfKeysAssociated();
				return Current;
			}
			Previous = Current;
			Current = Current->Next;
		} while (Current!= head);
	}
	void SetnoOfKeysAssociated() {
		MachineNode* Current = head;
		MachineNode* Previous = head;
		do {
			Previous = Previous->Next;
		} while (Previous->Next != head);

		do {
			if (Current == head) {
				int Var = TotalKeys - Previous->Data.Id;
				int Var1 = Current->Data.Id;
				Current->Data.NoOfKeysAssociated = Var + Var1;
			}
			else {
				 int Var = Current->Data.Id - Previous->Data.Id;
				 Current->Data.NoOfKeysAssociated = Var;
			}
			Previous = Current;
			Current = Current->Next;
		} while (Current != head);
	}
	
	void inorderTraversal(Node* current , KeyValuePairNode ** Array) {
		if (current == nullptr) {
			return;
		}
		for (int i = 0; i < current->noOfKeys; ++i) {
			
			if (!current->leaf) {
				inorderTraversal(current->Children[i] , Array);
			}
			Array[StaticVar++] = current->head[i];
		}
		if (!current->leaf) {
			inorderTraversal(current->Children[current->noOfKeys] , Array);
		}
	}
};