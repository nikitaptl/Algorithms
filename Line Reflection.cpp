class Solution {
public:
    bool isReflected(vector<vector<int>>& points) {
        // key = x, values = y
        unordered_map<int, unordered_set<int>> occurs;
        int minX = INT_MAX, maxX = INT_MIN;
        for (auto& point : points) {
            int x = point[0], y = point[1];
            occurs[x].insert(y);
            minX = min(minX, x);
            maxX = max(maxX, x);
        }
        double middle = (minX + maxX) / 2.0;
        for (auto& point : points) {
            int x = point[0], y = point[1];
            double refl = 2 * middle - x;
            if (!occurs.contains(refl) || !occurs[refl].contains(y)) {
                return false;
            }
        }
        return true;
    }
};
