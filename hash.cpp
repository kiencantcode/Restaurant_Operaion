	#include "iostream"

	using namespace std;
	const int MAXSIZE = 32;

	class HashTable {
	private:
		struct NodeHash {
			int result;
			int ID;
		};

		NodeHash* table;
		int size;

	public:
		HashTable() {
			table = new NodeHash[MAXSIZE/2];
			size = MAXSIZE/2;
			for (int i = 0; i < size; i++) {
				table[i].ID = -1;
				table[i].result = -1;
			}
		}

		int hashFunction(int result) {
			return result % size;
		}

		void insert(int result, int ID) {
			int index = hashFunction(result);
			int startIndex = index;
			if (table[index].ID == -1) {
				table[index].ID = ID;
				table[index].result = result;
			}
			else {
				while (table[index].ID != -1)
				{
					index = (index + 1) % size;
					if(index == startIndex){
						return;
					}
				}
				table[index].ID = ID;
				table[index].result = result;
			}
		}

		void deleteNodeHash(int ID){
			int index = 0;
			int startIndex = index;
			if (table[index].ID == ID) {
				table[index].ID = -1;
				table[index].result = -1;
				return;
			}
			index++;
			while (index != startIndex)
			{
				if (table[index].ID == ID) {
					table[index].ID = -1;
					table[index].result = -1;
					return;
				}
				index = (index + 1) % size;
			}
		}

		int countSpace(){
			int count = 0;
			for (int i = 0; i < size; i++) {
				if (table[i].ID != -1) {
					count++;
				}
			}
			return count;
		}

		bool search(int ID) {
			int index = 0;
			int startIndex = index;
			if (table[index].ID == ID) {
				return true;
			}
			index++;
			while (index != startIndex)
			{
				if (table[index].ID == ID) {
					return true;
				}
				index = (index + 1) % size;
			}
			return false;
		}

		void display() {
			for (int i = 0; i < size; i++) {
				if (table[i].ID != -1) {
					cout << "Result: " << table[i].result << ", ID: " << table[i].ID << endl;
				}
			}
		}

		~HashTable() {
			delete[] table;
		}
	};

	int main() {
		
		HashTable ht;

		ht.insert(2, 10);
		ht.insert(2, 20);
		ht.insert(18, 30);
		ht.insert(7, 40);
		ht.insert(9, 50);
		ht.insert(9, 50);
		int count = ht.countSpace();
		cout << "Count: " << count << endl;

		cout << "Before: " << endl;
		ht.display();
	
		ht.deleteNodeHash(30);
		cout << "After: " << endl;
		ht.display();

		return 0;
	}
