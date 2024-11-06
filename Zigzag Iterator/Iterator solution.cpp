class ZigzagIterator {
public:
    ZigzagIterator(vector<int>& v1, vector<int>& v2) {
        curr[0] = v1.begin(), curr[1] = v2.begin();
        end[0] = v1.end(), end[1] = v2.end();
    }

    int next() {
        int ans;
        if (curr[p] != end[p]) {
            ans = *curr[p];
            ++curr[p];
            p = 1 - p;
        } else {
            p = 1 - p;
            ans = *curr[p];
            ++curr[p];
        }
        return ans;
    }

    bool hasNext() {
        return curr[0] != end[0] || curr[1] != end[1];
    }

private:
    int p = 1;
    std::vector<int>::iterator curr[2], end[2];
};
