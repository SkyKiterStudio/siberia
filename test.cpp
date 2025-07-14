#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>  // 因为 tree 定义在这里 所以需要包含这个头文件
#include <ext/pb_ds/tree_policy.hpp>

#include "base.h"
using namespace siberia::base;

#define count 10000000

Exception ex;

int main()
{
    TreeMap<int, int> t;
    t[1] = 1;
    t.erase(1);
    __gnu_pbds::tree<std::pair<int, int>, __gnu_pbds::null_type,
                 std::less<std::pair<int, int>>, __gnu_pbds::rb_tree_tag,
                 __gnu_pbds::tree_order_statistics_node_update>
    mp;
    vector<int> vec;
    for (int i = 0; i < count; i++) {
        vec.push_back(rand());
    }
    //sort(vec.begin(), vec.end());
    //reverse(vec.begin(), vec.end());

    double start = clock();
    for (int i = 0; i < count; i++) {
        t[vec[i]] = vec[i];
    }
    double end = clock();
    printf("handmade AVL insert 10,000,000 random elements cost time: %lfs\n", (double) ((end - start) / CLOCKS_PER_SEC));

    start = clock();
    for (int i = 0; i < count; i++) {
        mp.insert(make_pair(vec[i], vec[i]));
    }
    end = clock();
    printf("std::map insert 10,000,000 random elements cost time: %lfs\n", (double) ((end - start) / CLOCKS_PER_SEC));

    start = clock();
    for (int i = 0; i < count; i++) {
        t[vec[i]];
    }
    end = clock();
    printf("handmade AVL search for 10,000,000 random elements cost time: %lfs\n", (double) ((end - start) / CLOCKS_PER_SEC));

    start = clock();
    for (int i = 0; i < count; i++) {
        mp.order_of_key(make_pair(vec[i], vec[i]));
    }
    end = clock();
    printf("std::map search for 10,000,000 random elements cost time: %lfs\n", (double) ((end - start) / CLOCKS_PER_SEC));

    start = clock();
    for (int i = 0; i < count; i++) {
        t.erase(vec[i]);
    }
    end = clock();
    printf("handmade AVL remove 10,000,000 random elements cost time: %lfs\n", (double) ((end - start) / CLOCKS_PER_SEC));

    start = clock();
    for (int i = 0; i < count; i++) {
        mp.erase(make_pair(vec[i], vec[i]));
    }
    end = clock();
    printf("std::map remove 10,000,000 random elements cost time: %lfs\n", (double) ((end - start) / CLOCKS_PER_SEC));
    //*/
    return 0;
}