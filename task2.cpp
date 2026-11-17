#include <iostream>
#include <string>
using namespace std;

// Custom Stack Node
struct StackNode {
    string operation;
    StackNode* next;
};

// Custom Stack
class Stack {
private:
    StackNode* top;

public:
    Stack() {
        top = nullptr;
    }
    void push(string op) {
        StackNode* newNode = new StackNode;

        newNode->operation = op;
        newNode->next = top;

        top = newNode;
    }
    void pop() {
        if (top == nullptr) {
            return;
        }
        StackNode* temp = top;
        top = top->next;

        delete temp;
    }

    bool isEmpty() {
        return top == nullptr;
    }

    void print() {
        printReverse(top);
    }
    void printReverse(StackNode* current) {
        if (current == nullptr) {
            return;
        }

        printReverse(current->next);
        cout << current->operation << " ";
    }
};


// Backtracking Function
void findSequences(int current, int target,int maxOperations, int overflowBound,string operations[], int n, 
    Stack& s, int depth) {

    if (current == target) {

        cout << "Valid Sequence: ";

        if (s.isEmpty()) {
            cout << "No operations needed";
        }
        else {
            s.print();
        }

        cout << endl;
    }

    if (depth == maxOperations) {
        return;
    }

    for (int i = 0; i < n; i++) {

        int next = current;

        if (operations[i] == "+3") {
            next = current + 3;
        }
        else if (operations[i] == "*2") {
            next = current * 2;
        }
        else if (operations[i] == "-5") {
            next = current - 5;
        }
        else if (operations[i] == "/2") {

            if (current % 2 != 0) {
                continue;
            }

            next = current / 2;
        }

        if (next < 0 || next > overflowBound) {
            continue;
        }

        // Push
        s.push(operations[i]);

        // Recursion
        findSequences(next, target,maxOperations, overflowBound, operations, n, s, depth + 1);

        // POP (BACKTRACKING)
        s.pop();
    }
}
//main function
int main() {

    int initialState, target;
    int maxOperations, overflowBound;

    cout << "Enter initial state: ";
    cin >> initialState;

    cout << "Enter target state: ";
    cin >> target;

    cout << "Enter maximum operations: ";
    cin >> maxOperations;

    cout << "Enter overflow bound: ";
    cin >> overflowBound;

    int n;

    cout << "Enter number of operations: ";
    cin >> n;

    string* operations = new string[n];

    cout << "Enter operations (+3, *2, -5, /2):\n";

    for (int i = 0; i < n; i++) {
        cin >> operations[i];
    }

    Stack s;
    cout << "\nValid Sequences:\n";
    findSequences(initialState, target,maxOperations, overflowBound, operations, n, s, 0);
    delete[] operations;

    return 0;
}