#include <iostream>
#include <functional>
#include <cstdint>

const size_t base_capacity = 100;

template<class KeyType, class ValueType>
struct Node {
    KeyType key_;
    ValueType value_;
    Node *next_;

    Node() = default;

    Node(KeyType key, ValueType value) : key_(key), value_(value), next_(nullptr) {
    }
};

template<class KeyType, class ValueType, class Func = std::hash<KeyType>>
class HashTable {
public:
    static void fillArrayWithNulls(Node<KeyType, ValueType> **arr_, size_t num) {
        for (int i = 0; i < num; i++) {
            arr_[i] = nullptr;
        }
    }

    HashTable() : rate_occupancy_(0.5), size_(0), capacity_(base_capacity),
                  arr_(new Node<KeyType, ValueType> *[base_capacity]), function_(Func()) {
        fillArrayWithNulls(arr_, base_capacity);
    }

    explicit HashTable(Func function) : rate_occupancy_(0.5), size_(0), capacity_(base_capacity),
                                        arr_(new Node<KeyType, ValueType> *[base_capacity]), function_(function) {
        fillArrayWithNulls(arr_, base_capacity);
    }

    HashTable(size_t capacity, double rate_occupancy, Func function = std::hash<KeyType>())
            : rate_occupancy_(0.5),
              capacity_(capacity),
              size_(0),
              arr_(new Node<KeyType, ValueType> *[capacity]),
              function_(function) {
        fillArrayWithNulls(arr_, capacity);
        if (rate_occupancy > 0 && rate_occupancy <= 1) {
            rate_occupancy_ = rate_occupancy;
        }
    }

    ~HashTable() {
        if (arr_ != nullptr) {
            for (int i = 0; i < capacity_; i++) {
                if (arr_[i] == nullptr) {
                    continue;
                } else {
                    Node<KeyType, ValueType> *next = arr_[i];
                    while (next != nullptr) {
                        arr_[i] = next->next_;
                        delete next;
                        next = arr_[i];
                    }
                }
            }
            delete[] arr_;
        }
    }

    void insert(KeyType key, ValueType value) {
        size_t hash = function_(key) % capacity_;
        Node<KeyType, ValueType> *node = arr_[hash];
        Node<KeyType, ValueType> *prev = nullptr;

        while (node != nullptr) {
            if (node->key_ == key) {
                node->value_ = value;
                return;
            }
            prev = node;
            node = node->next_;
        }

        if (prev) {
            prev->next_ = new Node<KeyType, ValueType>(key, value);
        } else {
            arr_[hash] = new Node<KeyType, ValueType>(key, value);
        }

        ++size_;
        if (static_cast<double>(size_) / capacity_ > rate_occupancy_) {
            rehash(capacity_ * 2);
        }
    }

    ValueType *find(KeyType key) {
        size_t num_hash = function_(key) % capacity_;
        if (arr_[num_hash] == nullptr) {
            return nullptr;
        }

        Node<KeyType, ValueType> *node = arr_[num_hash];
        while (node != nullptr) {
            if (node->key_ == key) {
                return &node->value_;
            }
            node = node->next_;
        }
        return nullptr;
    }

    void erase(KeyType key) {
        size_t num_hash = function_(key) % capacity_;
        auto node = arr_[num_hash];
        if (node == nullptr) {
            return;
        }

        // Случай, когда в List только один элемент
        if (node->next_ == nullptr && node->key_ != key) {
            return;
        }

        // Случай, когда в первом node хранится ключ
        if (node->key_ == key) {
            arr_[num_hash] = node->next_;
            delete node;
            size_--;
            return;
        }

        // node = arr_[num_hash]
        auto node_nextt = node->next_;
        // Случаи, когда node единственный в листе или он является искомым ключом, уже исключены
        while (node_nextt != nullptr) {
            if (node_nextt->key_ == key) {
                auto node_double_next = node_nextt->next_;
                delete node_nextt;
                node->next_ = node_double_next;
                size_--;
                return;
            }
            node = node->next_;
            node_nextt = node_nextt->next_;
        }
    }

    Node<KeyType, ValueType> &operator[](uint64_t index) {
        if (index > capacity_) {
            throw std::out_of_range("");
        }
        if (arr_[index] == nullptr) {
            throw std::runtime_error("");
        }
        return *arr_[index];
    }

    Node<KeyType, ValueType> at(uint64_t hash) {
        if (hash > capacity_) {
            throw std::out_of_range("");
        }
        if (arr_[hash] == nullptr) {
            throw std::runtime_error("");
        }
        return *arr_[hash];
    }

    size_t size() const {
        return size_;
    }

    size_t capacity() const {
        return capacity_;
    }

private:
    void rehash(size_t new_capacity) {
        HashTable<KeyType, ValueType, Func> new_hash_table(new_capacity, rate_occupancy_, function_);

        for (int i = 0; i < capacity_; i++) {
            if (arr_[i] != nullptr) {
                Node<KeyType, ValueType> *node = arr_[i];
                while (node != nullptr) {
                    new_hash_table.insert(node->key_, node->value_);
                    auto old_node = node;
                    node = node->next_;
                    delete old_node;
                }
            }
        }
        delete[] arr_;
        size_ = new_hash_table.size_;
        capacity_ = new_hash_table.capacity_;
        arr_ = new_hash_table.arr_;
        new_hash_table.arr_ = nullptr;  // Чтобы избежать удаления массива при уничтожении новой таблицы
    }

    double rate_occupancy_;
    size_t size_;
    size_t capacity_;
    Node<KeyType, ValueType> **arr_;

    Func function_;
};