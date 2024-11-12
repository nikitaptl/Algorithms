class Solution {
public:
    vector<int> arraysIntersection(vector<int>& arr1, vector<int>& arr2, vector<int>& arr3) {
        map<int, bool[3]> occurs;
        for (auto num : arr1) {
            occurs[num][0] = true;
        }
        for (auto num : arr2) {
            occurs[num][1] = true;
        }
        for (auto num : arr3) {
            occurs[num][2] = true;
        }
        vector<int> result;
        for (auto [key, num] : occurs) {
            if (num[0] && num[1] && num[2]) {
                result.push_back(key);
            }
        }
        return result;
    }
};