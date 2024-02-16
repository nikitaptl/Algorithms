#include <iostream>
#include <string>
#include <set>
#include <vector>

class BloomFilter {
public:
    BloomFilter(size_t hashes, size_t bits) : hashes_(hashes), bits_(bits),
                                              bloom_filter(std::vector<bool>(bits, false)),
                                              false_requests(0), amount_requests(0) {
    }

    ~BloomFilter() {
    }

    void add(const std::string &obj) {
        if (hashes_ == 0) {
            return;
        }
        for (int i = 0; i < hashes_; i++) {
            bloom_filter[function_index(obj, i) % bits_] = true;
        }
        storage.insert(obj);
    }

    bool verify(const std::string &obj) {
        amount_requests += 1;
        if (hashes_ == 0) {
            return false;
        }
        for (int i = 0; i < hashes_; i++) {
            if (!bloom_filter[function_index(obj, i) % bits_]) {
                return false;
            }
        }
        if (storage.find(obj) == storage.end()) {
            false_requests += 1;
        }
        return true;
    }

    double getFPRate() const {
        if (amount_requests == 0) {
            return 0;
        }
        return static_cast<double>(false_requests) / amount_requests;
    }

    size_t numberOfHashFunctions() const {
        return hashes_;
    }

    size_t numberOfBits() const {
        return bits_;
    }

private:
    size_t hashes_;
    size_t bits_;
    std::vector<bool> bloom_filter;
    std::set<std::string> storage;
    size_t amount_requests;
    size_t false_requests;

    size_t function_index(std::string str, size_t index) {
        if (index == 0) {
            return std::hash<std::string>{}(str);
        }
        return std::hash<std::string>{}(str + std::to_string(index));
    }
};
