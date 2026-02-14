#include <iostream>
#include <iomanip> 
using namespace std;
class CuckooHashTable {
private:
    int* table1;
    int* table2;
    int m;
    int size;
    const int EMPTY = -1;

    int hash1(int key) const {
        return key % m;
    }
    int hash2(int key) const {
        int delta = 3; 
        return (hash1(key) ^ delta) % m;  
    }
    void rehash() {
        cout << "Rehashing due to cycle ..." << endl;
        int oldSize = m;
        m *= 2;
        int* oldTable1 = table1;
        int* oldTable2 = table2;
        table1 = new int[m];
        table2 = new int[m];
        for (int i = 0; i < m; i++) {
            table1[i] = EMPTY;
            table2[i] = EMPTY;
        }
        size = 0;
        for (int i = 0; i < oldSize; i++) {
            if (oldTable1[i] != EMPTY) {
                insert(oldTable1[i]);
            }
            if (oldTable2[i] != EMPTY) {
                insert(oldTable2[i]);
            }
        }
        delete[] oldTable1;
        delete[] oldTable2;
    }
public:
    CuckooHashTable(int initial_size) {
        if (initial_size <= 0 || (initial_size & (initial_size - 1)) != 0) {
            cout << "Error: Initial size must be a perfect positive power of two." << endl;
            exit(1);
        }
        m = initial_size;
        size = 0;
        table1 = new int[m];
        table2 = new int[m];
        for (int i = 0; i < m; i++) {
            table1[i] = EMPTY;
            table2[i] = EMPTY;
        }
    }
    ~CuckooHashTable() {
        delete[] table1;
        delete[] table2;
    }
    void insert(int key) {
        if (size >= m / 2) {
            rehash();
        }
        int pos1 = hash1(key);
        if (table1[pos1] == EMPTY) {
            table1[pos1] = key;
            size++;
            return;
        }
        while (true) {
            int temp = table1[pos1];
            table1[pos1] = key;
            key = temp;
            pos1 = hash1(key);
            if (table1[pos1] == EMPTY) {
                table1[pos1] = key;
                size++;
                return;
            }
            int pos2 = hash2(key);
            temp = table2[pos2];
            table2[pos2] = key;
            key = temp;
            if (temp == EMPTY) {
                size++;
                return;
            }
        }
    }
    bool search(int key) const {
        return table1[hash1(key)] == key || table2[hash2(key)] == key;
    }
    void display() {
        cout << "\nTable 1 :\n";
        cout << "Indices: ";
        for (int i = 0; i < m; i++) {
            cout << setw(6) << i;
        }
        cout << "\nValues:  ";
        for (int i = 0; i < m; i++) {
            if (table1[i] != EMPTY)
                cout << setw(6) << table1[i];
            else
                cout << setw(6) << ".";
        }
        cout << "\n";
        cout << "\nTable 2 :\n";
        cout << "Indices: ";
        for (int i = 0; i < m; i++) {
            cout << setw(6) << i;
        }
        cout << "\nValues:  ";
        for (int i = 0; i < m; i++) {
            if (table2[i] != EMPTY)
                cout << setw(6) << table2[i];
            else
                cout << setw(6) << ".";
        }
        cout << "\n";

        cout << "\nCurrent load factor: " << fixed << setprecision(2) << (1.0 * size / m) << endl;
    }
    void checkPairwiseUncorrelation(int index1, int index2, int tableNum1, int tableNum2) const {
        int X, Y;
        if (tableNum1 == 1 && index1 >= 0 && index1 < m && table1[index1] != EMPTY) {
            X = hash1(table1[index1]) * hash2(table1[index1]);
        } else if (tableNum1 == 2 && index1 >= 0 && index1 < m && table2[index1] != EMPTY) {
            X = hash1(table2[index1]) * hash2(table2[index1]);
        } else {
            cout << "Invalid index or table number for the first input." << endl;
            return;
        }
        if (tableNum2 == 1 && index2 >= 0 && index2 < m && table1[index2] != EMPTY) {
            Y = hash1(table1[index2]) * hash2(table1[index2]);
        } else if (tableNum2 == 2 && index2 >= 0 && index2 < m && table2[index2] != EMPTY) {
            Y = hash1(table2[index2]) * hash2(table2[index2]);
        } else {
            cout << "Invalid index or table number for the second input." << endl;
            return;
        }
        double expectationX = X;
        double expectationY = Y;
        double expectationXY = X * Y;
        cout << "E[X]: " << expectationX << ", E[Y]: " << expectationY << ", E[XY]: " << expectationXY << endl;
        if (expectationXY == expectationX * expectationY) {
            cout << "The variables at indices are pairwise uncorrelated." << endl;
        } else {
            cout << "The variables at indices are not pairwise uncorrelated." << endl;
        }
    }
};
int main() {
    int initial_size;
    cout << "Enter the initial size of the hash table (must be a power of 2): ";
    cin >> initial_size;
    if (initial_size <= 0 || (initial_size & (initial_size - 1)) != 0) {
        cout << "Error: Initial size must be a perfect positive power of two." << endl;
        return 1;
    }
    CuckooHashTable table(initial_size);
    cout << "Enter keys to insert into the cuckoo hash table (enter -1 to stop):" << endl;
    while (true) {
        int key;
        cout << "Key: ";
        cin >> key;
        if (key == -1) break;
        table.insert(key);
    }
    table.display();
    int index1, index2, tableNum1, tableNum2;
    cout << "Enter two indices to check pairwise uncorrelation : ";
    cin >> tableNum1 >> index1 >> tableNum2 >> index2;
    table.checkPairwiseUncorrelation(index1, index2, tableNum1, tableNum2);
    return 0;
}

