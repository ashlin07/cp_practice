#include <bits/stdc++.h>
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
         int last=m;
        for(int i=0;i<n;i++){
            nums1[last]=nums2[i];
            last++;
        }
        sort(nums1.begin(),nums1.end());

    }
};