#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxNumberOfItems(vector<vector<int>>& items, int budget) {
        int n = items.size();

        vector<int> value(n);

        // Step 1: Calculate value of each item
        for (int i = 0; i < n; i++) {
            int freeCount = 0;

            for (int j = 0; j < n; j++) {
                if (i != j &&
                    items[j][0] % items[i][0] == 0) {
                    freeCount++;
                }
            }

            value[i] = 1 + freeCount;
        }

        // Step 2: Group items by price
        vector<vector<int>> groups(1501);

        for (int i = 0; i < n; i++) {
            int price = items[i][1];
            groups[price].push_back(i);
        }

        // dp[c] = maximum value using items
        // whose prices are greater than current price
        const int NEG = -1000000000;

        vector<int> dp(budget + 1, NEG);
        dp[0] = 0;

        int ans = 0;

        // Step 3: Process prices from high to low
        for (int p = 1500; p >= 1; p--) {

            // Must select at least one item costing p
            vector<int> take(budget + 1, NEG);

            for (int i : groups[p]) {
                for (int c = budget; c >= p; c--) {

                    if (dp[c - p] != NEG) {
                        take[c] = max(
                            take[c],
                            dp[c - p] + value[i]
                        );
                    }

                    if (take[c - p] != NEG) {
                        take[c] = max(
                            take[c],
                            take[c - p] + value[i]
                        );
                    }
                }
            }

            // Step 4: Calculate maximum answer
            for (int c = 0; c <= budget; c++) {
                if (take[c] != NEG) {
                    int extra = (budget - c) / p;

                    ans = max(ans, take[c] + extra);
                }
            }

            // Step 5: Add current price items to normal DP
            for (int i : groups[p]) {
                for (int c = budget; c >= p; c--) {
                    if (dp[c - p] != NEG) {
                        dp[c] = max(
                            dp[c],
                            dp[c - p] + value[i]
                        );
                    }
                }
            }
        }

        return ans;
    }
};

