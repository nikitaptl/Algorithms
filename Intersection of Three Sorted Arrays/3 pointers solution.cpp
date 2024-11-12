class Solution {
public:
    vector<int> arraysIntersection(vector<int> &arr1, vector<int> &arr2, vector<int> &arr3) {
        vector<int> result;
        int m = arr1.size(), n = arr2.size(), d = arr3.size();
        int p1 = 0, p2 = 0, p3 = 0;
        while (p1 < m && p2 < n && p3 < d) {
            if (arr1[p1] == arr2[p2] && arr2[p2] == arr3[p3]) {
                result.push_back(arr1[p1]);
                p1++, p2++, p3++;
            } else {
                int maxVal = max(arr1[p1], max(arr2[p2], arr3[p3]));
                while (p1 < m && arr1[p1] < maxVal) {
                    p1++;
                }
                while (p2 < n && arr2[p2] < maxVal) {
                    p2++;
                }
                while (p3 < d && arr3[p3] < maxVal) {
                    p3++;
                }
            }
        }
        return result;
    }
};