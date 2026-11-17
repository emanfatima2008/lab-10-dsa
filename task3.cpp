#include <iostream>
using namespace std;

// BST Node
struct Node {

    int serviceID;
    int cost;

    Node* left;
    Node* right;

    Node(int id, int c) {

        serviceID = id;
        cost = c;

        left = nullptr;
        right = nullptr;
    }
};

// Custom Linked List Node for paths and subsets
struct ListNode {

    Node* data;
    ListNode* next;
};

// Inserting into BST
Node* insert(Node* root, int id, int cost) {

    if (root == nullptr) {
        return new Node(id, cost);
    }

    if (cost < root->cost) {
        root->left = insert(root->left, id, cost);
    }
    else {
        root->right = insert(root->right, id, cost);
    }

    return root;
}

// CUSTOM LINKED LIST OPERATIONS
void push(ListNode*& head, Node* value) {
    ListNode* newNode = new ListNode;
    newNode->data = value;
    newNode->next = head;

    head = newNode;
}

void pop(ListNode*& head) {

    if (head == nullptr) {
        return;
    }
    ListNode* temp = head;

    head = head->next;

    delete temp;
}


// PART A: DOWNWARD PATH BACKTRACKING

// Print a path in root-to-leaf direction
void printPath(ListNode* head, int startIndex, int currentIndex) {

    if (head == nullptr) {
        return;
    }
    printPath(head->next, startIndex, currentIndex - 1);
    if (currentIndex >= startIndex) {
        cout << head->data->serviceID
             << "(" << head->data->cost << ") -> ";
    }
}


// Count linked list nodes
int countNodes(ListNode* head) {

    int count = 0;

    while (head != nullptr) {

        count++;

        head = head->next;
    }

    return count;
}


// Finding paths
void findPaths(Node* root, ListNode*& path, int target) {

    if (root == nullptr) {
        return;
    }

    // PUSH current node
    push(path, root);

    int sum = 0;
    ListNode* temp = path;
    int count = 0;

    while (temp != nullptr) {

        sum += temp->data->cost;

        if (sum == target) {

            cout << "Path found: ";

            // Path is stored in reverse order.
            // Print it from its oldest node to newest.
            printPath(path, 0, count);

            cout << endl;
        }

        temp = temp->next;

        count++;
    }

    // Exploring left
    findPaths(root->left, path, target);

    // Exploring right
    findPaths(root->right, path, target);

    // POP (BACKTRACKING)
    pop(path);
}


// PART B: BST BOUNDED SUBSET PRUNING


// Counting BST nodes
int countTreeNodes(Node* root) {

    if (root == nullptr) {
        return 0;
    }

    return 1 + countTreeNodes(root->left)
             + countTreeNodes(root->right);
}


// Inorder traversal into manually allocated array
void inorder(Node* root, Node** arr, int& index) {

    if (root == nullptr) {
        return;
    }

    inorder(root->left, arr, index);

    arr[index] = root;
    index++;

    inorder(root->right, arr, index);
}


// Printing selected subset
void printSubset(ListNode* subset) {

    if (subset == nullptr) {
        return;
    }

    printSubset(subset->next);

    cout << subset->data->serviceID
         << "(" << subset->data->cost << ") ";
}


// Finding subsets using backtracking
void findSubsets(Node** arr, int n, int index, int currentSum, int target,
                 ListNode*& subset) {

    if (currentSum == target) {

        cout << "Subset found: ";

        printSubset(subset);

        cout << endl;

        // Continuing searching for other subsets.
    }

    if (index == n) {
        return;
    }

    int nextSum = currentSum + arr[index]->cost;

    // Including current node if it does not exceed target
    if (nextSum <= target) {

        // PUSH
        push(subset, arr[index]);

        findSubsets(arr, n, index + 1,
                    nextSum, target, subset);

        // POP
        pop(subset);
    }

    // Excluding current node
    findSubsets(arr, n, index + 1, currentSum, target, subset);
}


// MAIN FUNCTION

int main() {

    Node* root = nullptr;

    int n;

    cout << "Enter number of microservices: ";
    cin >> n;

    // Build BST
    for (int i = 0; i < n; i++) {

        int id, cost;

        cout << "Enter service ID and cost: ";

        cin >> id >> cost;

        root = insert(root, id, cost);
    }


    // PART A

    int pathTarget;

    cout << "\nEnter target for Part A: ";
    cin >> pathTarget;

    ListNode* path = nullptr;

    cout << "\nPART A: Downward Paths\n";

    findPaths(root, path, pathTarget);


    // PART B
    int subsetTarget;

    cout << "\nEnter target for Part B: ";
    cin >> subsetTarget;

    int totalNodes = countTreeNodes(root);

    Node** arr = new Node*[totalNodes];

    int index = 0;

    inorder(root, arr, index);

    ListNode* subset = nullptr;

    cout << "\nPART B: Valid Subsets\n";

    findSubsets(arr, totalNodes, 0, 0, subsetTarget, subset);

    delete[] arr;

    return 0;
}