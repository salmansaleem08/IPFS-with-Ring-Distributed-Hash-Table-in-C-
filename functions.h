#pragma once
void bubbleSort(int* Array , int size , int *Array2) {
	for (int i = 0; i < size; i++) {
		for (int j = i+1; j < size; j++) {
			if (Array[i] > Array[j]) {
				int temp = Array[i]; Array[i] = Array[j]; Array[j] = temp;
				temp = Array2[i]; Array2[i] = Array2[j]; Array2[j] = temp;
			}
		}
	}
}
void MachineArrayIdAssigner(int*& MachineArray, int machines , int totalKeys) {
	cout << "Option : \n";
	cout << "(1) Manually Assign Id to each machine \n";
	cout << "(2) Randomly Assign Id to each machine \n";
	cout << "Enter :";
	int option = 0; cin >> option;
	while (option < 0 || option>2) {
		cout << "Invalid Enter Again ";
		cin >> option;
	}
	if (option == 1) {
		for (int i = 0; i < machines; ) {
			cout << "Id for Machine " << i + 1 << " : ";
			cin >> MachineArray[i];
			if (MachineArray[i] > totalKeys) continue;
			bool flag = false;
			for (int j = 0; j < i; j++) {
				if (MachineArray[j] == MachineArray[i]) {
					cout << "Enter Again \n";
					flag = true;
				}
			}
			if (!flag) i++;
		}
	}
	else {
		for (int i = 0; i < machines; ) {
			MachineArray[i] = rand() % totalKeys;
			bool flag = false;
			for (int j = 0; j < i; j++) {
				if (MachineArray[j] == MachineArray[i]) {
					flag = true;
				}
			}
			if (!flag) i++;

		}
	}
}
void BTreeMenuDisplay(int*& MachineArray, int*& BTreeOrder , int machines) {
	cout << "Order To the BTree :\n";
	cout << "(1) Same BTree Order Assign to Every Node of RingDht \n";
	cout << "(2) Different Order Assign to Every Node of RingDht \n";
	cout << "Enter : ";
	int OptionBtree = 0; cin >> OptionBtree;
	while (OptionBtree < 1 || OptionBtree>2) {
		cout << "Enter Again :";
		cin >> OptionBtree;
	}
	if (OptionBtree == 1) {
		cout << "Enter The Order of BTree : ";
		int Order = 0;
		cin >> Order;
		for (int i = 0; i < machines; i++) {
			BTreeOrder[i] = Order;
		}
	}
	else if (OptionBtree == 2) {
		for (int i = 0; i < machines; i++) {
			cout << "Enter the Order of BTree for Machine " << MachineArray[i] << " : ";
			cin >> BTreeOrder[i];
		}
	}

}
void insertFileinFormofKeyValuePair(int & MachineIdToEnterKey , int * MachineArray , int machines, RingDht & System , int totalKeys) {
	cout << "Option To Insert File in the form of Key value Pair from any Machine. \n";
	cout << "Enter The Machine Id From which you Want to Enter Key \n";
	cout << "Available Machine Id's\n";
	for (int i = 0; i < machines; i++)
		cout << MachineArray[i] << "  ";
	cout << endl;
	cout << "Enter : ";
	cin >> MachineIdToEnterKey;
	bool flag = false;
	while (!flag) {
		for (int i = 0; i < machines; i++) {
			if (MachineIdToEnterKey == MachineArray[i]) {
				flag = true; break;
			}
		}
		if (!flag) {
			cout << "Id Key Not Available !\n";
			cout << "Enter Again : ";
			cin >> MachineIdToEnterKey;
		}
	}

	MachineNode* Current = System.PrintPathWhileFindingId(MachineIdToEnterKey, System.head);
	cout << "So You are Now At Machine with Id " << Current->Data.Id << endl;
	cout << "Enter the Key Value Pair \n";
	cout << "Enter Key :";
	int key; cin >> key;
	cout << "Enter the Value : ";
	int value; cin >> value;
	int Hash = key % totalKeys;
	cout << "So the Hash Generated is : " << Hash << endl;
	Current = System.PrintPathWhileFindingId(Hash, Current);
	Current->BtreeVar.insertInBtree(Hash, key, value);
	Current->BtreeVar.print();
	cout << "Options Do you Want To View B tree Single Node in Depth \n";
	cout << "(1) Yes \n";
	cout << "(2) No \n";
	cout << "Enter : ";
	int OptionsforBTreeView;
	cin >> OptionsforBTreeView;
	while (!(OptionsforBTreeView > 0 && OptionsforBTreeView < 3)) {
		cout << "Enter Again : ";
		cin >> OptionsforBTreeView;
	}
	if (OptionsforBTreeView == 1) {
		cout << "Enter the Hash Value : ";
		int Hash; cin >> Hash;
		Node* BtreeCurrent = Current->BtreeVar.CheckIfHashExsist(Hash);
		while (!BtreeCurrent) {
			cout << "Hash Value Not Found \n";
			cout << "Enter Again : ";
			cin >> Hash;
			BtreeCurrent = Current->BtreeVar.CheckIfHashExsist(Hash);
		}
		Current->BtreeVar.PrintWholeHashValuePair(BtreeCurrent , Hash);
	}
	return;
}
void deleteFileFromKeys(int& MachineIdToRemoveKey, int* MachineArray, int machines, RingDht& System, int totalKeys) {
	
	cout << "Option to remove data by specifying the key from any machine \n";
	cout << "Enter The Machine Id from which You want to delete Key :\n";
	cout << "Available Machine Id's\n";
	for (int i = 0; i < machines; i++)
		cout << MachineArray[i] << "  ";
	cout << endl;
	cout << "Enter : ";
	cin >> MachineIdToRemoveKey;
	bool flag = false;
	while (!flag) {
		for (int i = 0; i < machines; i++) {
			if (MachineIdToRemoveKey == MachineArray[i]) {
				flag = true; break;
			}
		}
		if (!flag) {
			cout << "Id Key Not Available !\n";
			cout << "Enter Again : ";
			cin >> MachineIdToRemoveKey;
		}
	}

	MachineNode* Current = System.PrintPathWhileFindingId(MachineIdToRemoveKey, System.head);
	cout << "So You are Now At Machine with Id " << Current->Data.Id << endl;
	cout << "Enter Key :";
	int key; cin >> key;
	int Hash = key % totalKeys;
	cout << "So the Hash Generated is : " << Hash << endl;
	Current = System.PrintPathWhileFindingId(Hash, Current);
	Current->BtreeVar.deleteFromBtree(Hash, key);
	Current->BtreeVar.print();

	cout << "Options Do you Want To View B tree Single Node in Depth \n";
	cout << "(1) Yes \n";
	cout << "(2) No \n";
	cout << "Enter : ";
	int OptionsforBTreeView;
	cin >> OptionsforBTreeView;
	while (!(OptionsforBTreeView > 0 && OptionsforBTreeView < 3)) {
		cout << "Enter Again : ";
		cin >> OptionsforBTreeView;
	}
	if (OptionsforBTreeView == 1) {
		cout << "Enter the Hash Value : ";
		int Hash; cin >> Hash;
		Node* BtreeCurrent = Current->BtreeVar.CheckIfHashExsist(Hash);
		while (!BtreeCurrent) {
			cout << "Hash Value Not Found \n";
			cout << "Enter Again : ";
			cin >> Hash;
			if (Hash == -1) break;
			BtreeCurrent = Current->BtreeVar.CheckIfHashExsist(Hash);
		}
		if(Hash !=-1)
		Current->BtreeVar.PrintWholeHashValuePair(BtreeCurrent ,Hash);
	}
}
void PrintRoutingTable(int& MachineIdToPrintTable, int* MachineArray, int machines, RingDht& System, int totalKeys) {
	cout << "Option To Print Routing Table of any machine \n";
	cout << "Enter The Machine Id for which you want to see Routing table :\n";
	cout << "Available Machine Id's\n";
	for (int i = 0; i < machines; i++)
		cout << MachineArray[i] << "  ";
	cout << endl;
	cout << "Enter : ";
	cin >> MachineIdToPrintTable;
	bool flag = false;
	while (!flag) {
		for (int i = 0; i < machines; i++) {
			if (MachineIdToPrintTable == MachineArray[i]) {
				flag = true; break;
			}
		}
		if (!flag) {
			cout << "Id Key Not Available !\n";
			cout << "Enter Again : ";
			cin >> MachineIdToPrintTable;
		}
	}
	MachineNode* Current = System.PrintPathWhileFindingId(MachineIdToPrintTable, System.head);
	cout << "So You are Now At Machine with Id " << Current->Data.Id << endl;
	System.PrintRoutingTable(Current);
}
void OptionToAddnewMachine(int* BtreeOrder, int* MachineArray, int machines, RingDht& System, int totalKeys) {
	cout << "Option to add new machines on the fly without disrupting the functionality of Ring DHT\n";
	cout << "Enter Machine :";
	int newMachine;
	cin >> newMachine;
	while (1) {
		bool flag = true;
		for (int i = 0; i < machines; i++) {
			if (newMachine == MachineArray[i]) {
				flag = false;
				break;
			}
		}
		if (!flag) {
			cout << "Machine Already exsist Enter Again : ";
			cout << "Enter Again : ";
			cin >> newMachine;
		}
		if (flag) {
			if (newMachine > totalKeys) {
				cout << "Enter Again";
				cin >> newMachine;
			}
			else
				break;
		}
	}
	cout << "Enter the Order of Btree for new Machine: ";
	int newOrder;
	cin >> newOrder;
	int* MachineArrayCopy = new int[machines];
	int* BtreeOrderCopy = new int[machines];

	for (int i = 0; i < machines; i++) {
		MachineArrayCopy[i] = MachineArray[i];
		BtreeOrderCopy[i] = BtreeOrder[i];
	}
	delete[]MachineArray;
	delete[]BtreeOrder;
	MachineArray = new int[++machines];
	BtreeOrder = new int[machines];
	for (int i = 0; i < machines - 1; i++) {
		MachineArray[i] = MachineArrayCopy[i];
		BtreeOrder[i] = BtreeOrderCopy[i];
	}
	MachineArray[machines - 1] = newMachine;
	BtreeOrder[machines - 1] = newOrder;
	delete[] MachineArrayCopy;
	delete[] BtreeOrderCopy;
	MachineArrayCopy = nullptr;
	BtreeOrderCopy = nullptr;

	bubbleSort(MachineArray, machines, BtreeOrder);

	MachineNode* Current = System.insertnewMachine(newMachine, newOrder);
}