#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>

struct Node {
    char sym;
    int freq;
    Node *left;
    Node *right;
};

std::map<char, int> getFrequency(std::string &str) {
    std::map<char, int> frequency;
    for (auto &sym: str) {
        frequency[sym] += 1;
    }
    return frequency;
}

Node *buildTree(std::map<char, int> frequency) {
    auto comparator = [](const Node *a, const Node *b) {
        return a->freq > b->freq;
    };
    std::priority_queue<Node *, std::vector<Node *>, decltype(comparator)> pq(comparator);
    for (auto &[sym, freq]: frequency) {
        pq.push(new Node{sym, freq, nullptr, nullptr});
    }
    while (pq.size() > 1) {
        Node *x = pq.top();
        pq.pop();
        Node *y = pq.top();
        pq.pop();
        Node *parent = new Node{'\0', x->freq + y->freq, x, y};
        pq.push(parent);
    }
    return pq.top();
}

void findCode(Node *node, std::map<char, std::string> &map, std::string code) {
    if (node == nullptr) {
        return;
    }
    if (node->sym != '\0') {
        map[node->sym] = code;
        return;
    }
    findCode(node->left, map, code + "0");
    findCode(node->right, map, code + "1");
}

void deleteTree(Node* node) {
    if(node != nullptr) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

int main() {
    std::string str;
    std::getline(std::cin, str);
    std::map<char, std::string> result_map;

    auto frequency = getFrequency(str);
    Node *tree = buildTree(frequency);

    if (tree->left == nullptr && tree->right == nullptr) {
        result_map[tree->sym] = "0";
    } else {
        findCode(tree, result_map, "");
    }

    std::string result = "";
    for (auto sym: str) {
        result += result_map[sym];
    }

    std::cout << frequency.size() << " " << result.size() << std::endl;
    for (auto &[sym, code]: result_map) {
        std::cout << sym << ": " << code << std::endl;
    }
    std::cout << result;
    deleteTree(tree);
    return 0;
}