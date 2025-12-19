#include "sparse_table.h"

#include <iostream>
#include <random>

std::mt19937 rand32(time(nullptr));



int query(const std::vector<int> &v, int l, int r);

void check()
{
    int n{ static_cast<int>(rand32() % 100 + 1) };
    std::vector<int> as(n);
    for (auto &a : as)
    {
        a = rand32() % 10;
    }

    // SparseTable st(as);
    SparseTable st;
    st.build(as);

    int m{ static_cast<int>(rand32() % 10000 + 1) };
    while (m--)
    {
        int l{ static_cast<int>(rand32() % n) };
        int r{ static_cast<int>(rand32() % n) };
        if (l > r)
            std::swap(l, r);

        int ans_std{ query(as, l, r) };
        int ans_st{ st.query(l, r) };
        if (ans_std != ans_st)
        {
            std::cout << "Error!\n\n";

            std::cout << n << '\n';
            for (int i = 0; i < n; ++i)
            {
                std::cout << as[i] << " \n"[i == n - 1];
            }

            std::cout << "error range: [" << l << "," << r << "]\n";
            std::cout << "std ans: " << ans_std << '\n';
            std::cout << "ST ans: " << ans_st << '\n';
            exit(0);
        }
    }
}

int main()
{
    freopen("sparse_table_test.out", "w", stdout);
    std::ios::sync_with_stdio(false);

    int t = 10000;
    while (t--)
    {
        check();
    }
    std::cout << "No problem!\n";
}

int query(const std::vector<int> &v, int l, int r)
{
    int index;
    int max{ INT_MIN };
    for (int i = l; i <= r; ++i)
    {
        if (v[i] > max)
        {
            max = v[i];
            index = i;
        }
    }
    return index;
}
