class ZigzagIterator {
public:
    ZigzagIterator(vector<int>& v1, vector<int>& v2) {
        int m = v1.size(), n = v2.size();
        vec.reserve(m + n);
        int i = 0, j = 0;
        while (i < m && j < n) {
            vec.push_back(v1[i++]);
            vec.push_back(v2[j++]);
        }
        while (i < m) {
            vec.push_back(v1[i++]);
        }
        while (j < n) {
            vec.push_back(v2[j++]);
        }
    }

    int next() {
        int result = vec[ptr];
        ptr++;
        return result;
    }

    bool hasNext() {
        return ptr < vec.size();
    }

private:
    vector<int> vec;
    int ptr = 0;
};