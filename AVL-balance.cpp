#include <iostream>
#include <vector>
#include <sstream>

struct Node {
    Node *left;
    Node *right;
    Node *parent;
    int data;
};

struct BinaryTree {
private:
    Node *origin = nullptr;
    bool correctness = true;

    int checking(Node *root) {
        if (correctness == false || root == nullptr) {
            return 0;
        }
        int left_length = checking(root->left);
        int right_length = checking(root->right);
        if (abs(left_length - right_length) > 1) {
            correctness = false;
            return 0;
        }
        return 1 + std::max(left_length, right_length);
    };
public:
    void insert(int data) {
        if (origin == nullptr) {
            origin = new Node{nullptr, nullptr, nullptr, data};
            return;
        }
        Node *parent = origin;

        bool exit_flag = false;
        while (!exit_flag) {
            if (data < parent->data) {
                if (parent->left == nullptr) {
                    parent->left = new Node{nullptr, nullptr, parent, data};
                    exit_flag = true;
                }
                parent = parent->left;
            } else {
                if (parent->right == nullptr) {
                    parent->right = new Node{nullptr, nullptr, parent, data};
                    exit_flag = true;
                }
                parent = parent->right;
            }
        }
    };

    bool checkCorrectness() {
        checking(origin);
        return correctness;
    };

    void print(std::string separator = "") {
        inOrder(origin, separator);
    }

    void inOrder(Node *root, std::string separator = "") {
        if (root != nullptr) {
            inOrder(root->left, separator);
            std::cout << root->data << separator;
            inOrder(root->right, separator);
        }
    }
};

int main() {
    BinaryTree bt;

    std::string inputString;
    std::getline(std::cin, inputString);

    std::istringstream iss(inputString);
    int number;
    while (iss >> number && number != 0) {
        bt.insert(number);
    }
    if (bt.checkCorrectness()) {
        std::cout << "YES";
    } else {
        std::cout << "NO";
    }
    return 0;
}
