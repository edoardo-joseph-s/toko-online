#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <stack>
#include <map>

using namespace std;

struct User {
    string username;
    string password;
};

struct MenuItem {
    int id;
    string name;
    double price;
};

vector<User> users;
vector<MenuItem> menuItems;
map<int, MenuItem*> menuMap;
stack<MenuItem> menuStack;
queue<MenuItem> menuQueue;

// Sign-up and Sign-in functions
bool signUp(string username, string password) {
    for (auto &user : users) {
        if (user.username == username) {
            return false;
        }
    }
    users.push_back({username, password});
    return true;
}

bool signIn(string username, string password) {
    for (auto &user : users) {
        if (user.username == username && user.password == password) {
            return true;
        }
    }
    return false;
}

// CRUD Operations
void createMenuItem(int id, string name, double price) {
    MenuItem newItem = {id, name, price};
    menuItems.push_back(newItem);
    menuMap[id] = &menuItems.back();
}

void readMenuItems() {
    for (auto &item : menuItems) {
        cout << "ID: " << item.id << ", Name: " << item.name << ", Price: $" << item.price << endl;
    }
}

void updateMenuItem(int id, string newName, double newPrice) {
    if (menuMap.find(id) != menuMap.end()) {
        menuMap[id]->name = newName;
        menuMap[id]->price = newPrice;
    }
}

void deleteMenuItem(int id) {
    auto it = remove_if(menuItems.begin(), menuItems.end(), [id](MenuItem &item) {
        return item.id == id;
    });
    menuItems.erase(it, menuItems.end());
    menuMap.erase(id);
}

// Searching and Sorting
MenuItem* searchMenuItem(int id) {
    if (menuMap.find(id) != menuMap.end()) {
        return menuMap[id];
    }
    return nullptr;
}

void sortMenuItems() {
    sort(menuItems.begin(), menuItems.end(), [](MenuItem &a, MenuItem &b) {
        return a.id < b.id;
    });
}

// Linked List Node
struct Node {
    MenuItem data;
    Node* next;
};

Node* head = nullptr;

void insertLinkedList(MenuItem data) {
    Node* newNode = new Node{data, nullptr};
    if (!head) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void displayLinkedList() {
    Node* temp = head;
    while (temp) {
        cout << "ID: " << temp->data.id << ", Name: " << temp->data.name << ", Price: $" << temp->data.price << endl;
        temp = temp->next;
    }
}

// Tree Node
struct TreeNode {
    MenuItem data;
    TreeNode* left;
    TreeNode* right;
};

TreeNode* newTreeNode(MenuItem data) {
    TreeNode* node = new TreeNode();
    node->data = data;
    node->left = node->right = nullptr;
    return node;
}

TreeNode* insertTree(TreeNode* node, MenuItem data) {
    if (!node) return newTreeNode(data);

    if (data.id < node->data.id)
        node->left = insertTree(node->left, data);
    else if (data.id > node->data.id)
        node->right = insertTree(node->right, data);

    return node;
}

void inorder(TreeNode* root) {
    if (root) {
        inorder(root->left);
        cout << "ID: " << root->data.id << ", Name: " << root->data.name << ", Price: $" << root->data.price << endl;
        inorder(root->right);
    }
}

TreeNode* root = nullptr;

// Graph representation
class Graph {
    map<int, vector<int>> adjList;
public:
    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    void displayGraph() {
        for (auto &pair : adjList) {
            cout << pair.first << " -> ";
            for (int v : pair.second) {
                cout << v << " ";
            }
            cout << endl;
        }
    }
};

void menu() {
    cout << "1. Sign Up" << endl;
    cout << "2. Sign In" << endl;
    cout << "3. Create Menu Item" << endl;
    cout << "4. Read Menu Items" << endl;
    cout << "5. Update Menu Item" << endl;
    cout << "6. Delete Menu Item" << endl;
    cout << "7. Search Menu Item" << endl;
    cout << "8. Sort Menu Items" << endl;
    cout << "9. Display Linked List" << endl;
    cout << "10. Display Tree" << endl;
    cout << "11. Display Graph" << endl;
    cout << "12. Exit" << endl;
}

int main() {
    int choice, id;
    string username, password, name;
    double price;
    Graph graph;

    while (true) {
        menu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;
                if (signUp(username, password)) {
                    cout << "Sign up successful!" << endl;
                } else {
                    cout << "Username already exists." << endl;
                }
                break;
            case 2:
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;
                if (signIn(username, password)) {
                    cout << "Sign in successful!" << endl;
                } else {
                    cout << "Invalid username or password." << endl;
                }
                break;
            case 3:
                cout << "Enter item ID: ";
                cin >> id;
                cout << "Enter item name: ";
                cin >> name;
                cout << "Enter item price: ";
                cin >> price;
                createMenuItem(id, name, price);
                insertLinkedList({id, name, price});
                root = insertTree(root, {id, name, price});
                graph.addEdge(id, id + 1); // Example edge for graph
                break;
            case 4:
                readMenuItems();
                break;
            case 5:
                cout << "Enter item ID to update: ";
                cin >> id;
                cout << "Enter new item name: ";
                cin >> name;
                cout << "Enter new item price: ";
                cin >> price;
                updateMenuItem(id, name, price);
                break;
            case 6:
                cout << "Enter item ID to delete: ";
                cin >> id;
                deleteMenuItem(id);
                break;
            case 7:
                cout << "Enter item ID to search: ";
                cin >> id;
                if (searchMenuItem(id)) {
                    cout << "ID: " << searchMenuItem(id)->id << ", Name: " << searchMenuItem(id)->name << ", Price: $" << searchMenuItem(id)->price << endl;
                } else {
                    cout << "Item not found." << endl;
                }
                break;
            case 8:
                sortMenuItems();
                break;
            case 9:
                displayLinkedList();
                break;
            case 10:
                inorder(root);
                break;
            case 11:
                graph.displayGraph();
                break;
            case 12:
                exit(0);
            default:
                cout << "Invalid choice." << endl;
        }
    }

    return 0;
}
