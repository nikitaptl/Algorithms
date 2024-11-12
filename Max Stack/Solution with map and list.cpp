class MaxStack {
public:
    MaxStack() {
    }

    void push(int x) {
        list.push_back(x);
        map[x].push(--list.end());
    }

    int pop() {
        auto iter = --list.end();
        int x = *iter;
        map[x].pop();
        list.pop_back();
        if (map[x].empty()) {
            map.erase(x);
        }
        return x;
    }

    int top() {
        return list.back();
    }

    int peekMax() {
        return map.begin()->first;
    }

    int popMax() {
        int x = map.begin()->first;
        auto& stack = map.begin()->second;
        list.erase(stack.top());
        stack.pop();
        if (stack.empty()) {
            map.erase(x);
        }
        return x;
    }
private:
    map<int, stack<list<int>::iterator>, greater<int>> map;
    list<int> list;
};
