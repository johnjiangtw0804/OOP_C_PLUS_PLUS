#include <vector>
#include <set>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution
{
public:
    int maximizeOptionalTasks(int dailyTimelimit, vector<int> requiredTaskTimes, vector<int> optionalTasksTimes)
    {
        int res = 0;
        auto comp = [](int a, int b) {
            return a < b;
        };
        multiset<int, decltype(comp)> ms(optionalTasksTimes.begin(), optionalTasksTimes.end(), comp);

        // sort by values
        for (int i = 0; i < (int)requiredTaskTimes.size(); i++)
        {
            int req = requiredTaskTimes[i];
            // 7 - 4 = 3
            // 10
            int target = dailyTimelimit - req;
            // >
            auto it = ms.upper_bound(target);
            if (it == ms.begin())
            {
                continue;
            }
            it = prev(it);
            ms.extract(it);
            res++;
        }
        return res;
    }
};

int main() {
    int limit = 7;
    vector<int> req = {5,6,3,1,3,3};
    vector<int> opt = {4,5,6,2,5,5,2};
    Solution s;
    cout << s.maximizeOptionalTasks(limit, req, opt);
}
