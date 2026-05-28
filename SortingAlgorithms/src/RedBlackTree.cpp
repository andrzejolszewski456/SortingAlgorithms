#include "RedBlackTree.h"

Node::Node(double r, std::string t)
    : rating(r), title(t), color(RED), left(nullptr), right(nullptr), parent(nullptr) {
}

RedBlackTree::RedBlackTree() {
    NIL = new Node(0, "");
    NIL->color = BLACK;
    NIL->left = NIL->right = NIL;
    root = NIL;
}

RedBlackTree::~RedBlackTree() {
    deleteTree(root);
    delete NIL;
}

void RedBlackTree::deleteTree(Node* w) {
    if (w != NIL && w != nullptr) {
        deleteTree(w->left);
        deleteTree(w->right);
        delete w;
    }
}

void RedBlackTree::rotateLeft(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != NIL) y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == nullptr) root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void RedBlackTree::rotateRight(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    if (y->right != NIL) y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == nullptr) root = y;
    else if (x == x->parent->right) x->parent->right = y;
    else x->parent->left = y;
    y->right = x;
    x->parent = y;
}

void RedBlackTree::fixInsert(Node* k) {
    while (k != root && k->parent->color == RED) {
        if (k->parent == k->parent->parent->left) {
            Node* uncle = k->parent->parent->right;
            if (uncle->color == RED) {
                k->parent->color = BLACK;
                uncle->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            }
            else {
                if (k == k->parent->right) {
                    k = k->parent;
                    rotateLeft(k);
                }
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                rotateRight(k->parent->parent);
            }
        }
        else {
            Node* uncle = k->parent->parent->left;
            if (uncle->color == RED) {
                k->parent->color = BLACK;
                uncle->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            }
            else {
                if (k == k->parent->left) {
                    k = k->parent;
                    rotateRight(k);
                }
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                rotateLeft(k->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

void RedBlackTree::insert(std::pair<double, std::string> data) {
    Node* node = new Node(data.first, data.second);
    node->left = node->right = NIL;

    Node* temp_parent = nullptr;
    Node* current = root;

    while (current != NIL) {
        temp_parent = current;
        if (node->rating < current->rating) current = current->left;
        else current = current->right;
    }

    node->parent = temp_parent;

    if (temp_parent == nullptr) root = node;
    else if (node->rating < temp_parent->rating) temp_parent->left = node;
    else temp_parent->right = node;

    if (node->parent == nullptr) {
        node->color = BLACK;
        return;
    }
    if (node->parent->parent == nullptr) return;

    fixInsert(node);
}

RedBlackTree::Iterator& RedBlackTree::Iterator::operator++() {
    if (current->right != nil_ref) {
        current = current->right;
        while (current->left != nil_ref) current = current->left;
    }
    else {
        Node* p = current->parent;
        while (p != nullptr && current == p->right) {
            current = p;
            p = p->parent;
        }
        current = (p == nullptr) ? nil_ref : p;
    }
    return *this;
}

RedBlackTree::Iterator RedBlackTree::begin() {
    Node* x = root;
    if (x != NIL) while (x->left != NIL) x = x->left;
    return Iterator(x, NIL);
}