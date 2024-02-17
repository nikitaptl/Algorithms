#include <iostream>

const size_t base_capacity = 100;

struct Value {
    bool isNull = true;
    int value;

    Value() = default;

    Value(int num) {
        value = num;
        isNull = false;
    }
};

template<class Func = std::hash<int>>
class HashLPTable {
public:
    HashLPTable() : rate_occupancy_(0.5), size_(0), capacity_(base_capacity),
                    arr_(new Value[base_capacity]), function_(Func()) {
    }

    explicit HashLPTable(Func function) : rate_occupancy_(0.5), size_(0), capacity_(base_capacity),
                                          arr_(new Value[base_capacity]), function_(function) {
    };

    HashLPTable(size_t capacity, double rate_occupancy, Func function = std::hash<int>()) : rate_occupancy_(0.5),
                                                                                            capacity_(capacity),
                                                                                            size_(0),
                                                                                            arr_(new Value[capacity]),
                                                                                            function_(function) {
        if (rate_occupancy > 0 && rate_occupancy <= 1) {
            rate_occupancy_ = rate_occupancy;
        }
    }

    ~HashLPTable() {
    }

    void insert(int value) {
        size_t index = function_(value) % capacity_;

        while (!arr_[index].isNull) {
            if (arr_[index].value == value) {
                return;
            }
            index = (index + 1) % capacity_;
        }
        arr_[index] = Value(value);

        size_++;
        if (static_cast<double>(size_) / capacity_ > rate_occupancy_) {
            rehash(capacity_ * 2);
        }
    }

    int *find(int value) {
        size_t index = function_(value) % capacity_;
        while (!arr_[index].isNull) {
            if (arr_[index].value == value) {
                return &arr_[index].value;
            }
            index = (index + 1) % capacity_;
        }
        return nullptr;
    }

    void erase(int value) {
        size_t index = function_(value) % capacity_;
        while (!arr_[index].isNull) {
            if (arr_[index].value == value) {
                size_t index_erasing = (index + 1) % capacity_;
                bool isMoved = false;
                while (!arr_[index_erasing].isNull) {
                    size_t hash = function_(arr_[index_erasing].value) % capacity_;
                    if (hash != index_erasing) {
                        isMoved = true;
                        arr_[index] = arr_[index_erasing];
                        index = index_erasing;
                    }
                    index_erasing = (index_erasing + 1) % capacity_;
                }
                if(isMoved) {
                    arr_[index_erasing].isNull = false;
                }
                else {
                    arr_[index_erasing].isNull = false;
                }
                size_--;
                return;
            }
            index = (index + 1) % capacity_;
        }
    }

    size_t size() const {
        return size_;
    }

    size_t capacity() const {
        return capacity_;
    }

private:
    double rate_occupancy_;
    size_t size_;
    size_t capacity_;
    Value *arr_;

    void rehash(size_t new_capacity) {
        HashLPTable new_hash_table(new_capacity, rate_occupancy_, function_);
        for (int i = 0; i < capacity_; i++) {
            if (!arr_[i].isNull) {
                new_hash_table.insert(arr_[i].value);
            }
        }
        delete[] arr_;
        size_ = new_hash_table.size_;
        capacity_ = new_hash_table.capacity_;
        arr_ = new_hash_table.arr_;
        new_hash_table.arr_ = nullptr;
    }

    Func function_;
};
