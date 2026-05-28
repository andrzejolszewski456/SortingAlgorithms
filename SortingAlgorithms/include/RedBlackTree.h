#pragma once
#include <string>
#include <utility>

enum Color { RED, BLACK };

struct Node {
    double rating;
    std::string title;
    Color color;
    Node* left, * right, * parent;

    Node(double r, std::string t);
};

class RedBlackTree {
private:
    Node* root;
    Node* NIL;

    void rotateLeft(Node* x);
    void rotateRight(Node* x);
    void fixInsert(Node* k);
    void deleteTree(Node* w);

public:
    RedBlackTree();
    ~RedBlackTree();

    void insert(std::pair<double, std::string> data);

    class Iterator {
        Node* current;
        Node* nil_ref;
    public:
        Iterator(Node* start, Node* n) : current(start), nil_ref(n) {}
        bool operator!=(const Iterator& other) const { return current != other.current; }
        std::pair<double, std::string> operator*() const { return { current->rating, current->title }; }
        Iterator& operator++();
    };

    Iterator begin();
    Iterator end() { return Iterator(NIL, NIL); }
};