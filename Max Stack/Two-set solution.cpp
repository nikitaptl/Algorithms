class MaxStack {
public:
    MaxStack() {
    }
    
    void push(int x) {
        ch = stack.empty() ? 0 : stack.rbegin()->first + 1;
        stack.insert({ch, x});
        maxStack.insert({x, ch});
    }
    
    int pop() {
        auto [index, x] = *stack.rbegin();
        maxStack.erase({x, index});
        stack.erase({index, x});
        return x;
    }
    
    int top() {
        return stack.rbegin()->second;
    }
    
    int peekMax() {
        return maxStack.rbegin()->first;
    }
    
    int popMax() {
        auto [x, index] = *maxStack.rbegin();
        stack.erase({index, x});
        maxStack.erase({x, index});
        return x;
    }
private:
    set<pair<int, int>> stack;
    set<pair<int, int>> maxStack;
    int ch = 0;
};