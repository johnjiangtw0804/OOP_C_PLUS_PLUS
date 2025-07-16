#include <algorithm>
#include <vector>
#include <set>
#include <iostream>

using namespace std;

class Solution {
public:
   vector<bool> findSimilarPasswords(vector<vector<string>> password) {
       vector<bool> res((int)password.size(), false);
       for (int i = 0; i < (int)password.size(); i++)
       {
           string password1 = password[i][0];
           string password2 = password[i][1];
           vector<int> freq1(26, 0);
           vector<int> freq2(26, 0);
           for (char &c : password1)
           {
               freq1[c - 'a']++;
            }
            for (char &c : password2)
            {
                freq2[c - 'a']++;
            }
            int remove_count_1 = 0;
            int remove_count_2 = 0;
            // safddadfs
            // famafmfmss
            // if mismatch => char only exists in one string => remove(char) entirely
            //             => char exists in both string => remove(char) until they are even from that password
            for (int j = 0; j < 26; j++)
            {
                if (freq1[j] != freq2[j])
                {
                    if (freq1[j] > freq2[j])
                    {
                        remove_count_1++;
                    }
                    else
                    {
                        remove_count_2++;
                    }
                }
            }
            if (remove_count_1 <= 1 && remove_count_2 <= 1)
            {
                res[i] = true;
            }
       }
       return res;
   }
};

int main() {
    int n = 1;
    vector<vector<string>> password = {{"safddadfs", "famafmss"}};
    Solution s;
    vector<bool> res = s.findSimilarPasswords(password);
    cout << (res[0] == 0? "false" : "true") << endl;
    vector<vector<string>> password2 = {{"safffff", "saf"}};
    res = s.findSimilarPasswords(password2);
    cout << (res[0] == 0 ? "false" : "true") << endl;
}
