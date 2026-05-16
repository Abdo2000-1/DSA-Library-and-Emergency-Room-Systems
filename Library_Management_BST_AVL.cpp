#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

struct Book {
    int id;
    string title;
    string author;
};

struct Node {
    Book book;
    Node* left;
    Node* right;
    int height;

    Node(Book b) {
        book = b;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

class BST {
private:
    Node* root;

    Node* insertBook(Node* node, Book newBook) {
        if (node == nullptr) return new Node(newBook);

        if (newBook.id < node->book.id)
            node->left = insertBook(node->left, newBook);
        else if (newBook.id > node->book.id)
            node->right = insertBook(node->right, newBook);

        return node;
    }

    void printInOrder(Node* node) {
        if (node == nullptr) return;

        printInOrder(node->left);
        cout << "ID: " << node->book.id << " | Title: " << node->book.title << endl;
        printInOrder(node->right);
    }

    void findBooksInRange(Node* node, int minID, int maxID) {
        if (node == nullptr) return;

        if (minID < node->book.id) findBooksInRange(node->left, minID, maxID);

        if (node->book.id >= minID && node->book.id <= maxID) {
            cout << "ID: " << node->book.id << " | Title: " << node->book.title << endl;
        }

        if (maxID > node->book.id) findBooksInRange(node->right, minID, maxID);
    }

    void getClosestBook(Node* node, int targetID, Node*& closestNode, int& smallestDifference) {
        if (node == nullptr) return;

        int currentDifference = abs(node->book.id - targetID);

        if (currentDifference < smallestDifference) {
            smallestDifference = currentDifference;
            closestNode = node;
        }

        if (targetID < node->book.id)
            getClosestBook(node->left, targetID, closestNode, smallestDifference);
        else if (targetID > node->book.id)
            getClosestBook(node->right, targetID, closestNode, smallestDifference);
    }

public:
    BST() { root = nullptr; }

    void add(Book b) { root = insertBook(root, b); }
    void showAll() { printInOrder(root); }
    void searchRange(int minID, int maxID) { findBooksInRange(root, minID, maxID); }

    void printClosest(int targetID) {
        if (root == nullptr) return;

        Node* closestNode = root;
        int smallestDifference = 1000000;

        getClosestBook(root, targetID, closestNode, smallestDifference);

        cout << "Closest Book ID: " << closestNode->book.id << " (" << closestNode->book.title << ")\n";
    }
};

class AVL {
private:
    Node* root;

    int getHeight(Node* node) {
        if (node == nullptr) return 0;
        return node->height;
    }

    int getBalance(Node* node) {
        if (node == nullptr) return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    Node* rotateRight(Node* oldRoot) {
        Node* newRoot = oldRoot->left;
        Node* middleBranch = newRoot->right;

        newRoot->right = oldRoot;
        oldRoot->left = middleBranch;

        oldRoot->height = max(getHeight(oldRoot->left), getHeight(oldRoot->right)) + 1;
        newRoot->height = max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

        return newRoot;
    }

    Node* rotateLeft(Node* oldRoot) {
        Node* newRoot = oldRoot->right;
        Node* middleBranch = newRoot->left;

        newRoot->left = oldRoot;
        oldRoot->right = middleBranch;

        oldRoot->height = max(getHeight(oldRoot->left), getHeight(oldRoot->right)) + 1;
        newRoot->height = max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

        return newRoot;
    }

    Node* insertBook(Node* node, Book newBook) {
        if (node == nullptr)
            return new Node(newBook);

        if (newBook.id < node->book.id)
            node->left = insertBook(node->left, newBook);
        else if (newBook.id > node->book.id)
            node->right = insertBook(node->right, newBook);
        else
            return node;

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        int balance = getBalance(node);

        if (balance > 1 && newBook.id < node->left->book.id)
            return rotateRight(node);

        if (balance < -1 && newBook.id > node->right->book.id)
            return rotateLeft(node);

        if (balance > 1 && newBook.id > node->left->book.id) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && newBook.id < node->right->book.id) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

public:
    AVL() 
    {
        root = nullptr; 
    }
    void add(Book b) { root = insertBook(root, b); }
};

int main() {
    BST myBSTLibrary;
    AVL myAVLLibrary;

    for (int i = 1; i <= 20; i++) {
        Book newBook;
        newBook.id = i * 10;
        newBook.title = "Book Title " + to_string(i);
        newBook.author = "Author " + to_string(i);

        myBSTLibrary.add(newBook);
        myAVLLibrary.add(newBook);
    }

    cout << "--- BST Inorder Traversal ---\n";
    myBSTLibrary.showAll();

    cout << "\n--- Functional Features ---\n";

    cout << "Books between ID 50 and 100:\n";
    myBSTLibrary.searchRange(50, 100);

    cout << "\nSearching closest match to ID 45:\n";
    myBSTLibrary.printClosest(45);

    return 0;
}