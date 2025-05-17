#include<iostream>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include"Header.h"
#include"functions.h"
using namespace std;
int main() {
	srand(time(0));
	int bits = 0;
	cout << "Enter The Number of Bits : ";
	cin >> bits;
	while(bits < 4 || bits>160) {
		cout << "Enter Again :";
		cin >> bits;
	}
	int totalKeys = pow(2, bits);
	cout << "So TotalKeys Are :" << totalKeys << endl;
	cout << "Enter the Total Number of Machines : ";
	int machines; 
	cin >> machines;
	while (machines > totalKeys) {
		cout << "Enter Again :";
		cin >> machines;
	}
	int* MachineArray = new int[machines];
	int* BtreeOrder = new int[machines];
	MachineArrayIdAssigner(MachineArray, machines, totalKeys);
	BTreeMenuDisplay(MachineArray, BtreeOrder, machines);
	bubbleSort(MachineArray, machines ,BtreeOrder);

	RingDht System(bits, totalKeys);
	for (int i = 0; i < machines; i++) {
		int temp = 0;
		if (i == 0)
		{
			temp = totalKeys - MachineArray[machines - 1] + MachineArray[i];
			System.insertMachine(MachineArray[i],temp,BtreeOrder[i]);
		}
		else
		{
			temp = MachineArray[i] - MachineArray[i - 1];
			System.insertMachine(MachineArray[i],temp,BtreeOrder[i]);
		}
	}
	System.PrintRingDht();

	while (1) {
		int menuvar = 0;
		cout << "Enter :";
		cout << "(1) Insert File in Form of key Pair \n";
		cout << "(2) Delete File using Key \n";
		cout << "(3) Print Routing Table \n";
		cout << "(4) Option To add New Machine \n";
		cin >> menuvar;
		
		if (menuvar == 1) {
			int MachineIdToEnterKey;
			insertFileinFormofKeyValuePair(MachineIdToEnterKey, MachineArray, machines, System, totalKeys);
		}
		if (menuvar == 2) {
			int MachineIdToRemoveKey;
			deleteFileFromKeys(MachineIdToRemoveKey, MachineArray, machines, System, totalKeys);
		}
		if (menuvar == 3) {
			int MachineIdToPrintTable;
			PrintRoutingTable(MachineIdToPrintTable, MachineArray, machines, System, totalKeys);
		}
		if (menuvar == 4) {

			OptionToAddnewMachine(BtreeOrder, MachineArray, machines, System, totalKeys);
		}

	}
	
	
	

	

}

