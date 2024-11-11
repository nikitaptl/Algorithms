// Sort in descending order
struct Compare {
    bool operator()(const pair<int, int> &a, const pair<int, int> &b) {
        if (a.first == b.first) {
            return a.second < b.second;
        }
        return a.first < b.first;
    }
};

class MaxStack {
public:
    MaxStack() {
    }

    void push(int x) {
        int index = ++counts[x];
        stack.push({x, index});
        pq.push({x, index});
    }

    int pop() {
        updateStack();
        int result = stack.top().first;
        updateCounts(result);
        return result;
    }

    int top() {
        updateStack();
        return stack.top().first;
    }

    int peekMax() {
        updatePq();
        return pq.top().first;
    }

    int popMax() {
        updatePq();
        int result = pq.top().first;
        updateCounts(result);
        return result;
    }

private:
    unordered_map<int, int> counts;
    stack<pair<int, int>> stack;
    priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq;

    void updateCounts(int x) {
        if (--counts[x] == 0) {
            counts.erase(x);
        }
    }

    void updateStack() {
        auto [x, index] = stack.top();
        while (!counts.contains(x) || counts[x] < index) {
            stack.pop();
            tie(x, index) = stack.top();
        }
    }

    void updatePq() {
        auto [x, index] = pq.top();
        while (!counts.contains(x) || counts[x] < index) {
            pq.pop();
            tie(x, index) = pq.top();
        }
    }
};