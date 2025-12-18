#include "sparse_table.h"

#include <iostream>
#include <random>

std::mt19937 rand32(time(nullptr));



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

    for (int i = 0; i < n; ++i)
    {
        for (int j = i; j < n; ++j)
        {
            int max{ INT_MIN };
            int index;
            for (int k = i; k <= j; ++k)
            {
                if (as[k] > max)
                {
                    max = as[k];
                    index = k;
                }
            }
            if (index != st.query(i, j))
            {
                std::cout << "Error!\n";
                std::cout << n << '\n';
                for (int i = 0; i < n; ++i)
                {
                    std::cout << as[i] << " \n"[i == n - 1];
                }
                std::cout << "error range: [" << i << "," << j << "]\n";
                std::cout << "std ans: " << index << '\n';
                std::cout << "ST ans: " << st.query(i, j) << '\n';
                exit(0);
            }
        }
    }
    std::cout << "No problem!\n";
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
}
