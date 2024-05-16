#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

int levenstein(const std::string &word1, const std::string &word2) {
    int M = word1.size();
    int N = word2.size();
    if (M == 0) {
        return N;
    }
    if (N == 0) {
        return M;
    }
    std::vector<int> dp1(N + 1, 0), dp2(N + 1, 0);

    for (int i = 1; i <= N; i++) {
        dp1[i] = i;
    }
    for (int i = 1; i <= M; i++) {
        dp2[0] = i;
        for (int j = 1; j <= N; j++) {
            int cost = word1[i - 1] == word2[j - 1] ? 0 : 1;
            dp2[j] = std::min(dp1[j] + 1, std::min(dp2[j - 1] + 1, dp1[j - 1] + cost));
        }
        dp1.swap(dp2);
    }
    return dp1[N];
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string str;
    getline(std::cin, str);
    int num = std::stoi(str);

    while (num) {
        std::string word1, word2;
        std::getline(std::cin, word1);
        std::getline(std::cin, word2);
        std::cout << levenstein(word1, word2) << " ";
        num--;
    }

    return 0;
}