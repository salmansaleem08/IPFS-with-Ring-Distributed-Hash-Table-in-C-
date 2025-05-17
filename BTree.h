#pragma once
#include<iostream>
using namespace std;

void bubbleSort1(int* Array, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++) {
			if (Array[i] > Array[j]) {
				int temp = Array[i]; Array[i] = Array[j]; Array[j] = temp;
			}
		}
	}
}
struct KeyValuePairNode {
	int key;
	int Value;
	int Hash;
	KeyValuePairNode* Next;
	KeyValuePairNode(int key=0, int Value=0, int hash=0) {
		this->key = key; this->Value = Value; this->Hash = hash;
		this->Next = nullptr;
	}
};
struct Node {
	KeyValuePairNode**head;
	int noOfKeys;
	int* Keys;
	bool leaf;
	Node** Children;
	int Order;
	Node* Parent;
	Node(int Order ) {
		this->Order = Order;
		Keys = new int[Order - 1];
		noOfKeys = 0;
		Children = new Node * [Order];
		for (int i = 0; i < Order; i++)
			Children[i] = nullptr;
		leaf = true;
		Parent = nullptr;
		head = new KeyValuePairNode*[Order - 1];
		for (int i = 0; i < Order - 1; i++) {
			head[i] = nullptr;
		}
	}
	bool isMax() {
		if (noOfKeys == Order - 1)
			return true;
		return false;
	}
	void insertInKeys(int data) {
		Keys[noOfKeys++] = data;
		bubbleSort();
	}
	void removeFromKeys(int idx) {
		for (int i = idx; i < noOfKeys; i++)
			Keys[i] = Keys[i + 1];
		noOfKeys--;
	}
	void bubbleSort() {
		for (int i = 0; i < noOfKeys; i++) {
			for (int j = i + 1; j < noOfKeys; j++) {
				if (Keys[i] > Keys[j]) {
					int temp = Keys[i]; Keys[i] = Keys[j]; Keys[j] = temp;
				}
			}
		}
	}
	void print(int spaces) {
		for (int i = noOfKeys - 1; i >= 0; --i) {
			if (!leaf) {
				Children[i + 1]->print(spaces + 4);
			}
			for (int j = 0; j < spaces; ++j) {
				std::cout << " ";
			}
			std::cout << Keys[i] << "\n";
		}
		if (!leaf) {
			Children[0]->print(spaces + 4);
		}
	}
	void SpiltInto(Node* Current, int key) {

		int* temp = new int[Order];
		for (int i = 0; i < Order - 1; i++) {
			temp[i] = Current->Keys[i];
		}
		temp[Order - 1] = key;
		bubbleSort1(temp, Order);

		Node* tempLeft = new Node(Order);
		Node* tempRight = new Node(Order);
		for (int i = 0; i < Order - 1; i++) {
			Current->removeFromKeys(i);
		}

		int dumy = ((Order + 1) / 2) - 1;

		Current->insertInKeys(temp[dumy]);

		for (int i = 0; i < dumy; i++) {
			tempLeft->insertInKeys(temp[i]);
		}
		for (int i = dumy + 1; i < Order; i++) {
			tempRight->insertInKeys(temp[i]);
		}
		Current->leaf = false;
		Current->Children[Current->noOfKeys - 1] = tempLeft;
		tempLeft->Parent = Current;
		Current->Children[Current->noOfKeys] = tempRight;
		tempRight->Parent = Current;

	}
	void SpiltInto1(Node* Current, int key, Node*& root) {

		if (!Current->Parent->isMax()) {
			int* temp = new int[Order];
			for (int i = 0; i < Order - 1; i++) {
				temp[i] = Current->Keys[i];
			}
			temp[Order - 1] = key;
			bubbleSort1(temp, Order);

			Node* tempLeft = new Node(Order);
			Node* tempRight = new Node(Order);

			int dumy = ((Order + 1) / 2) - 1;

			Current->Parent->insertInKeys(temp[dumy]);

			for (int i = 0; i < dumy; i++) {
				tempLeft->insertInKeys(temp[i]);
			}
			for (int i = dumy + 1; i < Order; i++) {
				tempRight->insertInKeys(temp[i]);
			}
			Current->Parent->bubbleSort();

			for (int i = 0; i < Current->Parent->noOfKeys; i++) {
				if (Current == Current->Parent->Children[i]) {
					for (int j = Current->Parent->noOfKeys + 1; j > i; j--) {
						Current->Parent->Children[j] = Current->Parent->Children[j - 1];
					}
					Current->Parent->Children[i] = tempLeft;
					tempLeft->Parent = Current->Parent;
					Current->Parent->Children[i + 1] = tempRight;
					tempRight->Parent = Current->Parent;
				}
			}
			Node* temp1 = Current;
			Current = Current->Parent;
			delete temp1;
		}
		else {
			if (Current->Parent != root) {
				int* tempArray = new int[Order];
				for (int i = 0; i < Order - 1; i++) {
					tempArray[i] = Current->Keys[i];
				}
				tempArray[Order - 1] = key;
				bubbleSort1(tempArray, Order);

				int tempKey = tempArray[((Order + 1) / 2) - 1];

				Node* leftSub = new Node(Order);
				Node* rightSub = new Node(Order);

				int dumy = ((Order + 1) / 2) - 1;
				for (int i = 0; i < dumy; i++) {
					leftSub->insertInKeys(tempArray[i]);
				}
				for (int i = dumy + 1; i < Order; i++) {
					rightSub->insertInKeys(tempArray[i]);
				}

				Node** ChildrenDummy = new Node * [Order + 1];

				for (int i = 0, k = 0; i < Order + 1; i++, k++) {

					if (Current == Current->Parent->Children[i]) {

						ChildrenDummy[i] = leftSub;
						ChildrenDummy[i + 1] = rightSub;
						i += 2; k++;
					}
					ChildrenDummy[i] = Current->Parent->Children[k];
				}

				Node* tempPtr = Current->Parent;
				SpiltInto1(tempPtr, tempKey, root);
				Node* tempPtr1 = root;
				Node* lefter = root;
				while (!lefter->leaf) {
					bool flag = true;
					for (int i = 0; i < lefter->noOfKeys; i++) {
						if (ChildrenDummy[0]->Keys[0] < lefter->Keys[i]) {
							lefter = lefter->Children[i];
							flag = false;
							break;
						}
					}
					if (flag) {
						lefter = lefter->Children[lefter->noOfKeys];
					}

				}
				lefter->leaf = false;

				int j = 0;
				for (int i = 0; i <= lefter->noOfKeys; i++) {

					lefter->Children[i] = ChildrenDummy[j];
					ChildrenDummy[j]->Parent = lefter;
					j++;

				}

				Node* righter = root;
				while (!righter->leaf) {
					bool flag = true;
					for (int i = 0; i < righter->noOfKeys; i++) {
						if (ChildrenDummy[j]->Keys[0] < righter->Keys[i]) {
							righter = righter->Children[i];
							flag = false;
							break;
						}
					}
					if (flag) {
						righter = righter->Children[righter->noOfKeys];
					}

				}
				righter->leaf = false;

				for (int i = 0; i <= righter->noOfKeys; i++) {
					righter->Children[i] = ChildrenDummy[j];
					ChildrenDummy[j]->Parent = righter;

					j++;

				}

			}

			else {
				int* tempArray = new int[Order];
				for (int i = 0; i < Order - 1; i++) {
					tempArray[i] = Current->Keys[i];
				}
				tempArray[Order - 1] = key;
				bubbleSort1(tempArray, Order);

				int tempKey = tempArray[((Order + 1) / 2) - 1];

				Node* leftSub = new Node(Order);
				Node* rightSub = new Node(Order);

				int dumy = ((Order + 1) / 2) - 1;
				for (int i = 0; i < dumy; i++) {
					leftSub->insertInKeys(tempArray[i]);
				}
				for (int i = dumy + 1; i < Order; i++) {
					rightSub->insertInKeys(tempArray[i]);
				}

				Node** ChildrenDummy = new Node * [Order + 1];

				for (int i = 0, k = 0; i < Order + 1; i++, k++) {

					if (Current == Current->Parent->Children[i]) {
						ChildrenDummy[i] = leftSub;
						ChildrenDummy[i + 1] = rightSub;
						i += 2; k++;
					}
					ChildrenDummy[i] = Current->Parent->Children[k];


				}


				Node* tempPtr = Current->Parent;
				SpiltInto(tempPtr, tempKey);

				int index = 0;
				for (int i = 0; i < tempPtr->noOfKeys; i++) {
					if (Current == tempPtr->Children[i]) {
						for (int j = tempPtr->noOfKeys + 1; j >= i; j--) {
							tempPtr->Children[j] = tempPtr->Children[j - 1];
						}
						index = i;

					}
				}
				Node* lefter = tempPtr->Children[index];
				lefter->Parent = tempPtr;
				root->leaf = false;
				lefter->leaf = false;


				int j = 0;
				for (int i = 0; i <= lefter->noOfKeys; i++) {

					lefter->Children[i] = ChildrenDummy[j];
					ChildrenDummy[j]->Parent = lefter;
					j++;
				}

				Node* righter = tempPtr->Children[index + 1];
				righter->Parent = tempPtr;
				righter->leaf = false;

				for (int i = 0; i <= righter->noOfKeys; i++) {
					righter->Children[i] = ChildrenDummy[j];
					ChildrenDummy[j]->Parent = righter;
					j++;
				}

			}
		}
	}

};
class BTree {
public:
	Node* root;
	int order;
	int MinimumKey;
	int TotalInsertions;
	BTree(int order) {
		root = nullptr;
		this->order = order;
		if (order % 2 == 0)
			MinimumKey = (order / 2) - 1;
		else
			MinimumKey = (order / 2);
		TotalInsertions = 0;
	}
	void insertInBtree(int Hash ,int Key , int Value) {
		Node* Current = CheckIfHashExsist(Hash);
		if (Current) {
			for (int i = 0; i < Current->noOfKeys; i++) {
				if (Hash == Current->Keys[i]) {
					KeyValuePairNode* temp = Current->head[i];
					while (temp->Next) {
						temp = temp->Next;
					}
					temp->Next = new KeyValuePairNode(Key, Value, Hash);
				}
			}
		}
		else {
			insert(Hash);
			Current = CheckIfHashExsist(Hash);
			for (int i = 0; i < Current->noOfKeys; i++) {
				if (Current->Keys[i] == Hash) {
					Current->head[i] = new KeyValuePairNode(Key, Value, Hash);
				}
			}
		}
	}
	void PrintWholeHashValuePair(Node* Current , int Hash) {
		if (!Current) return;
		int index = 0;
		for(int i =0; i<Current->noOfKeys; i++){
			if (Current->Keys[i] == Hash) {
				index = i;
			}
		}
		KeyValuePairNode* temp = Current->head[index];
		cout << "\nKeys : " << endl;
		while (temp) {
			if (temp->Next)
				cout << temp->key << " -> ";
			else
				cout << temp->key;
			temp = temp->Next;
		}
		cout << endl;
		cout << "Value : " << endl;
		temp = Current->head[index];
		while (temp) {
			if (temp->Next)
				cout << temp->Value << " -> ";
			else
				cout << temp->Value;
			temp = temp->Next;
		}
		cout << endl << endl;
	}
	Node* CheckIfHashExsist(int Hash) {
		Node* Current = root;
		while (Current) {
			for (int i = 0; i < Current->noOfKeys; i++) {
				if (Hash == Current->Keys[i]) {
					return Current;
				}
			}
			bool flag = false;
			for (int i = 0; i < Current->noOfKeys; i++) {
				if (Hash < Current->Keys[i]) {
					Current = Current->Children[i];
					flag = true;
					break;
				}
			}
			if (!flag) {
				Current = Current->Children[Current->noOfKeys];
			}
		}
		return nullptr;
	}
	void insert(int key) {
		if (root == nullptr) {
			root = new Node(order);
			root->insertInKeys(key);
		}
		else if (!root->isMax() && root->leaf) {
			root->insertInKeys(key);
			root->bubbleSort();
		}
		else if (root->leaf && root->isMax()) {
			root->SpiltInto(root, key);
		}
		else {
			Node* Current = SearchForInsertion(key);
			if (!Current->isMax()) {
				Current->insertInKeys(key);
				Current->bubbleSort();
			}
			else if (Current->isMax()) {

				Current->SpiltInto1(Current, key, root);
			}
		}
		TotalInsertions++;
	}
	Node* SearchForInsertion(int data) {
		Node* Current = root;
		while (!Current->leaf) {
			bool flag = false;
			for (int i = 0; i < Current->noOfKeys; i++) {
				if (data < Current->Keys[i]) {
					Current = Current->Children[i];
					flag = true; break;
				}
			}
			if (!flag) {
				Current = Current->Children[Current->noOfKeys];
			}
		}
		return Current;
	}
	void print() {
		cout << "So the Btree is \n\n\n";
		if (root != nullptr) {
			root->print(0);
		}
		else
			cout << "NULL PTR \n";
	}
	void deleteFromBtree(int hash, int key) {
		Node * Current = CheckIfHashExsist(hash);
		if (Current) {
			for (int i = 0; i < Current->noOfKeys; i++) {
				if (hash == Current->Keys[i]) {
					KeyValuePairNode* temp = Current->head[i];
					while (temp) {
						if (temp->key == key) {
							KeyValuePairNode* temp1 = temp;
							temp = temp->Next;
							delete temp1;
							temp1 = NULL;
							break;
						}
						temp = temp->Next;
					}
					if (Current->head == NULL) {
						remove1(hash);
					}
				}
			}
		}
		else
			cout << "Hash Doesnot Exsist \n";
	}
	Node* FindImediateLeft(Node* Current) {
		Node* Parent = Current->Parent;
		for (int i = 1; i < Parent->noOfKeys + 1; i++) {
			if (Current == Parent->Children[i]) {
				return Parent->Children[i - 1];
			}
		}
		return nullptr;
	}
	Node* FindImediateRight(Node* Current) {
		Node* Parent = Current->Parent;
		for (int i = 0; i < Parent->noOfKeys; i++) {
			if (Current == Parent->Children[i]) {
				return Parent->Children[i + 1];
			}
		}
		return nullptr;
	}
	int IndexReturner(Node* Parent, Node* Current) {
		for (int i = 1; i < Parent->noOfKeys + 1; i++) {
			if (Parent->Children[i] == Current)
				return i - 1;
		}
	}
	int IndexReturner1(Node* Parent, Node* Current) {
		for (int i = 0; i < Parent->noOfKeys + 1; i++) {
			if (Parent->Children[i] == Current)
				return i;
		}
	}
	Node* GetPredecessor(Node* root, int data) {
		Node* Current = root;
		int index = 0;
		for (int i = 0; i < root->noOfKeys; i++) {
			if (data == Current->Keys[i]) {
				index = i;
			}
		}
		Current = Current->Children[index];
		while (!Current->leaf) {
			Current = Current->Children[Current->noOfKeys];
		}
		return Current;
	}
	Node* GetSuccessor(Node* root, int data) {
		Node* Current = root;
		int index = 0;
		for (int i = 0; i < root->noOfKeys; i++) {
			if (data == Current->Keys[i]) {
				index = i;
			}
		}
		Current = Current->Children[index + 1];
		while (!Current->leaf) {
			Current = Current->Children[0];
		}
		return Current;
	}
	Node* SearchForDeletion(int data) {
		Node* Current = root;
		while (1) {
			for (int i = 0; i < Current->noOfKeys; i++) {
				if (data == Current->Keys[i]) {
					return Current;
				}
			}
			bool flag = false;
			for (int i = 0; i < Current->noOfKeys; i++) {
				if (data < Current->Keys[i]) {
					Current = Current->Children[i];
					flag = true;
					break;
				}
			}
			if (!flag) {
				Current = Current->Children[Current->noOfKeys];
			}

		}
	}
	void SearchAndReplace(int data, int var) {
		Node* Current = root;
		while (1) {
			for (int i = 0; i < Current->noOfKeys; i++) {
				if (data == Current->Keys[i]) {
					Current->Keys[i] = var;
					return;
				}
			}
			bool flag = false;
			for (int i = 0; i < Current->noOfKeys; i++) {
				if (data < Current->Keys[i]) {
					Current = Current->Children[i];
					flag = true;
					break;
				}
			}
			if (!flag) {
				Current = Current->Children[Current->noOfKeys];
			}

		}
	}
	void remove1(int data) {
		Node* Current = SearchForDeletion(data);
		if (Current->leaf == true) {
			// Case 1
			if (Current->noOfKeys > MinimumKey) {
				for (int i = 0; i < Current->noOfKeys; i++) {
					if (data == Current->Keys[i]) {
						Current->removeFromKeys(i);
						Current->bubbleSort();
					}
				}
				return;
			}
			// Case 2
			else if (Current->noOfKeys <= MinimumKey) {
				Node* Parent = Current->Parent;
				Node* leftSibling = FindImediateLeft(Current);
				Node* rightSibling = FindImediateRight(Current);
				// Case 2 (A)
				if (leftSibling != NULL && leftSibling->noOfKeys > MinimumKey) {
					int Var = Parent->Keys[IndexReturner(Parent, Current)];
					Parent->removeFromKeys(IndexReturner(Parent, Current));
					int Var1 = leftSibling->Keys[leftSibling->noOfKeys - 1];
					leftSibling->removeFromKeys(leftSibling->noOfKeys - 1);
					Parent->insertInKeys(Var1);
					Parent->bubbleSort();
					for (int i = 0; i < Current->noOfKeys; i++)
						if (data == Current->Keys[i])
							Current->removeFromKeys(i);
					Current->insertInKeys(Var);
					Current->bubbleSort();
					return;
				}
				// Case 2 (B)
				else if (rightSibling != NULL && rightSibling->noOfKeys > MinimumKey) {
					int Var = Parent->Keys[IndexReturner1(Parent, Current)];
					Parent->removeFromKeys(IndexReturner1(Parent, Current));
					int Var1 = rightSibling->Keys[0];
					rightSibling->removeFromKeys(0);
					Parent->insertInKeys(Var1);
					Parent->bubbleSort();
					for (int i = 0; i < Current->noOfKeys; i++)
						if (data == Current->Keys[i])
							Current->removeFromKeys(i);
					Current->insertInKeys(Var);
					Current->bubbleSort();
					return;
				}
				// Case 2 (C)
				else {
					// Case 2 (1 C)
					if (Parent->noOfKeys > MinimumKey) {
						// Case 2 (1 C i)
						if (leftSibling != NULL) {
							for (int i = 0; i < Current->noOfKeys; i++) {
								if (data == Current->Keys[i]) {
									Current->removeFromKeys(i);
								}
							}
							int Var = Parent->Keys[IndexReturner(Parent, Current)];
							Parent->removeFromKeys(IndexReturner(Parent, Current));
							leftSibling->insertInKeys(Var);

							while (Current->noOfKeys != 0) {
								int Var1 = Current->Keys[0];
								Current->removeFromKeys(0);
								leftSibling->insertInKeys(Var1);
							}
							for (int i = IndexReturner(Parent, Current) + 1; i < Parent->noOfKeys + 1; i++) {
								Parent->Children[i] = Parent->Children[i + 1];
								Parent->Children[i]->bubbleSort();
							}
							Parent->Children[Parent->noOfKeys + 1] = nullptr;
							Current->bubbleSort();
							return;
						}
						// Case 2 (1 C ii)
						else if (rightSibling != NULL) {
							for (int i = 0; i < Current->noOfKeys; i++)
								if (data == Current->Keys[i])
									Current->removeFromKeys(i);

							int Var = Parent->Keys[IndexReturner1(Parent, Current)];
							Parent->removeFromKeys(IndexReturner1(Parent, Current));
							rightSibling->insertInKeys(Var);

							while (Current->noOfKeys != 0) {
								int Var1 = Current->Keys[0];
								Current->removeFromKeys(0);
								rightSibling->insertInKeys(Var1);
							}
							for (int i = IndexReturner1(Parent, Current); i < Parent->noOfKeys + 1; i++) {
								Parent->Children[i] = Parent->Children[i + 1];
								Parent->Children[i]->bubbleSort();
							}
							Parent->Children[Parent->noOfKeys + 1] = nullptr;
							Current->bubbleSort();
							return;
						}
					}
					// Case 2 (2 C)
					else if (Parent->noOfKeys <= MinimumKey) {
						for (int i = 0; i < Current->noOfKeys; i++) {
							if (data == Current->Keys[i]) {
								Current->removeFromKeys(i);
							}
						}
						// Case 2 (2 C i)
						if (leftSibling != NULL) {
							int Var = Parent->Keys[IndexReturner(Parent, Current)];
							Parent->removeFromKeys(IndexReturner(Parent, Current));
							leftSibling->insertInKeys(Var);

							while (Current->noOfKeys != 0) {
								int Var = Current->Keys[0];
								leftSibling->insertInKeys(Var);
								Current->removeFromKeys(0);
							}
							for (int i = IndexReturner(Parent, Current) + 1; i < Parent->noOfKeys + 1; i++) {
								Parent->Children[i] = Parent->Children[i + 1];
							}
							Parent->Children[Parent->noOfKeys + 1] = nullptr;
							Balancer(Current->Parent);
						}
						else if (rightSibling != NULL) {
							int Var = Parent->Keys[IndexReturner1(Parent, Current)];
							Parent->removeFromKeys(IndexReturner1(Parent, Current));
							rightSibling->insertInKeys(Var);
							while (Current->noOfKeys != 0) {
								int Var = Current->Keys[0];
								rightSibling->insertInKeys(Var);
								Current->removeFromKeys(0);
							}
							for (int i = IndexReturner1(Parent, Current); i < Parent->noOfKeys + 1; i++) {
								Parent->Children[i] = Parent->Children[i + 1];
							}
							Parent->Children[Parent->noOfKeys + 1] = NULL;

							Balancer(Current->Parent);
						}
					}

				}
			}
		}
		else if (Current == root) {
			Node* Predecessor = GetPredecessor(root, data);
			int Var = Predecessor->Keys[Predecessor->noOfKeys - 1];
			remove1(Var);
			SearchAndReplace(data, Var);
			return;
		}
		else if (Current->leaf == false && Current != root) {

			Node* Predecessor = GetPredecessor(Current, data);
			int Var = Predecessor->Keys[Predecessor->noOfKeys - 1];

			remove1(Var);
			SearchAndReplace(data, Var);
			return;


		}
	}
	void Balancer(Node* Current) {
		if (Current == root) {
			if (Current->noOfKeys >= 1) {
				return;
			}
			else {
				root = root->Children[root->noOfKeys];
				root->Parent = nullptr;
				return;
			}
		}


		Node* Parent = Current->Parent;
		Node* leftSibling = FindImediateLeft(Current);
		Node* rightSibling = FindImediateRight(Current);
		// Case 3 (A)
		if (leftSibling != NULL && leftSibling->noOfKeys > MinimumKey) {
			int Var = Parent->Keys[IndexReturner(Parent, Current)];
			Parent->removeFromKeys(IndexReturner(Parent, Current));
			Current->insertInKeys(Var);
			int Var1 = leftSibling->Keys[leftSibling->noOfKeys - 1];
			Parent->insertInKeys(Var1);

			for (int i = Current->noOfKeys; i > 0; i--) {
				Current->Children[i] = Current->Children[i - 1];
			}
			Current->Children[0] = leftSibling->Children[leftSibling->noOfKeys];
			Current->Children[0]->Parent = Current;

			leftSibling->Children[leftSibling->noOfKeys] = nullptr;
			leftSibling->removeFromKeys(leftSibling->noOfKeys - 1);
			return;
		}
		// Case 3 (B)
		else if (rightSibling != NULL && rightSibling->noOfKeys > MinimumKey) {
			int Var = Parent->Keys[IndexReturner1(Parent, Current)];
			Parent->removeFromKeys(IndexReturner1(Parent, Current));
			Current->insertInKeys(Var);
			int Var1 = rightSibling->Keys[0];
			Parent->insertInKeys(Var1);

			Current->Children[Current->noOfKeys] = rightSibling->Children[0];
			Current->Children[Current->noOfKeys]->Parent = Current;
			rightSibling->removeFromKeys(0);

			for (int i = 0; i < rightSibling->noOfKeys + 1; i++) {
				rightSibling->Children[i] = rightSibling->Children[i + 1];
			}
			rightSibling->Children[rightSibling->noOfKeys + 1] = nullptr;
			return;
		}
		// Case 3 (C)
		else if (Parent->noOfKeys > MinimumKey) {
			// Case 3 (C.1)
			if (leftSibling != NULL) {
				int Var = Parent->Keys[IndexReturner(Parent, Current)];
				Parent->removeFromKeys(IndexReturner(Parent, Current));
				leftSibling->insertInKeys(Var);
				int index = 0;

				while (Current->noOfKeys != 0) {
					int Var = Current->Keys[0];

					leftSibling->Children[leftSibling->noOfKeys] = Current->Children[index++];
					leftSibling->Children[leftSibling->noOfKeys]->Parent = leftSibling;
					leftSibling->insertInKeys(Var);
					Current->removeFromKeys(0);
				}
				leftSibling->Children[leftSibling->noOfKeys] = Current->Children[index++];
				leftSibling->Children[leftSibling->noOfKeys]->Parent = leftSibling;

				for (int i = IndexReturner(Parent, Current) + 1; i < Parent->noOfKeys + 1; i++) {
					Parent->Children[i] = Parent->Children[i + 1];
				}
				Parent->Children[Parent->noOfKeys + 1] = nullptr;
				return;
			}
			// Case 3 (C.1)
			else if (rightSibling != NULL) {
				int Var = Parent->Keys[IndexReturner1(Parent, Current)];
				Parent->removeFromKeys(IndexReturner1(Parent, Current));
				rightSibling->insertInKeys(Var);
				int index = 0;

				while (Current->noOfKeys != 0) {
					for (int i = rightSibling->noOfKeys; i > 0; i--) {
						rightSibling->Children[i] = rightSibling->Children[i - 1];
					}

					int Var = Current->Keys[0];
					rightSibling->Children[0] = Current->Children[Current->noOfKeys];
					rightSibling->Children[0]->Parent = rightSibling;
					rightSibling->insertInKeys(Var);
					Current->removeFromKeys(0);
				}

				for (int i = rightSibling->noOfKeys; i > 0; i--) {
					rightSibling->Children[i] = rightSibling->Children[i - 1];
				}
				rightSibling->Children[0] = Current->Children[Current->noOfKeys];
				rightSibling->Children[0]->Parent = rightSibling;

				for (int i = 0; i < Parent->noOfKeys + 1; i++) {
					Parent->Children[i] = Parent->Children[i + 1];
				}
				Parent->Children[Parent->noOfKeys + 1] = nullptr;
				return;
			}
		}
		// Case 3 (D)
		else if (Parent->noOfKeys <= MinimumKey) {

			if (leftSibling != NULL) {
				int Var = Parent->Keys[IndexReturner(Parent, Current)];
				Parent->removeFromKeys(IndexReturner(Parent, Current));
				leftSibling->insertInKeys(Var);
				int index = 0;

				while (Current->noOfKeys != 0) {
					int Var = Current->Keys[0];

					leftSibling->Children[leftSibling->noOfKeys] = Current->Children[index++];
					leftSibling->Children[leftSibling->noOfKeys]->Parent = leftSibling;
					leftSibling->insertInKeys(Var);
					Current->removeFromKeys(0);
				}
				leftSibling->Children[leftSibling->noOfKeys] = Current->Children[index++];
				leftSibling->Children[leftSibling->noOfKeys]->Parent = leftSibling;
				
				for (int i = IndexReturner(Parent, Current) + 1; i < Parent->noOfKeys + 1; i++) {
					Parent->Children[i] = Parent->Children[i + 1];
				}
				Parent->Children[Parent->noOfKeys + 1] = nullptr;
				print();
				Balancer(leftSibling->Parent);

				return;
			}
			else if (rightSibling != NULL) {
				int Var = Parent->Keys[IndexReturner1(Parent, Current)];
				Parent->removeFromKeys(IndexReturner1(Parent, Current));
				rightSibling->insertInKeys(Var);
				int index = 0;

				while (Current->noOfKeys != 0) {
					for (int i = rightSibling->noOfKeys; i > 0; i--) {
						rightSibling->Children[i] = rightSibling->Children[i - 1];
					}
					int Var = Current->Keys[0];
					rightSibling->Children[0] = Current->Children[Current->noOfKeys];
					rightSibling->Children[0]->Parent = rightSibling;
					rightSibling->insertInKeys(Var);
					Current->removeFromKeys(0);
				}

				for (int i = rightSibling->noOfKeys; i > 0; i--) {
					rightSibling->Children[i] = rightSibling->Children[i - 1];
				}
				rightSibling->Children[0] = Current->Children[Current->noOfKeys];
				rightSibling->Children[0]->Parent = rightSibling;

				for (int i = IndexReturner1(Parent, Current); i < Parent->noOfKeys + 1; i++) {
					Parent->Children[i] = Parent->Children[i + 1];
				}
				Parent->Children[Parent->noOfKeys + 1] = NULL;

				Balancer(rightSibling->Parent);
				return;
			}
		}

	}
};
