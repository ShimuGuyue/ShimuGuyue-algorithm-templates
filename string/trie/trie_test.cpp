#include "trie.h"

#include <iostream>
#include <random>

std::mt19937 rand32(time(nullptr));



int count(std::vector<std::string> &vs, std::string &s);
int count_pre(std::vector<std::string> &vs, std::string &s);
std::vector<std::string> list_pre(std::vector<std::string> &vs, std::string &s);

void check()
{
    Trie trie;

    int n{ static_cast<int>(rand32() % 100) };
    std::vector<std::string> vs(n);
    for (auto &s : vs)
    {
        int m{ static_cast<int>(rand32() % 10) };
        while (m--)
        {
            s.push_back(rand32() % 26 + 'a');
        }
        trie.insert(s);
    }

    int k{ static_cast<int>(rand32() % 10) };

    for (int i = 0; i < k; ++i)
    {
        int m{ static_cast<int>(rand32() % 100) };
        std::string s;
        while (m--)
        {
            s.push_back(rand32() % 26 + 'a');
        }
        int count_trie{ trie.count(s) };
        int count_std{ count(vs, s) };
        if (count_trie != count_std)
        {
            std::cout << "Error! - count\n\n";

            std::cout << "Dictionary:\n";
            for (auto &s : vs)
            {
                std::cout << s << '\n';
            }

            std::cout << "std ans: " <<  count_std << '\n';
            std::cout << "trie ans: " << count_trie << '\n';
            exit(0);
        }
    }

    for (int i = 0; i < k; ++i)
    {
        int m{ static_cast<int>(rand32() % 100) };
        std::string s;
        while (m--)
        {
            s.push_back(rand32() % 26 + 'a');
        }
        int count_trie{ trie.count_pre(s) };
        int count_std{ count_pre(vs, s) };
        if (count_trie != count_std)
        {
            std::cout << "Error! - count_pre\n\n";

            std::cout << "Dictionary:\n";
            for (auto &s : vs)
            {
                std::cout << s << '\n';
            }

            std::cout << "std ans: " <<  count_std << '\n';
            std::cout << "trie ans: " << count_trie << '\n';
            exit(0);
        }
    }

    for (int i = 0; i < k; ++i)
    {
        int m{ static_cast<int>(rand32() % 100) };
        std::string s;
        while (m--)
        {
            s.push_back(rand32() % 26 + 'a');
        }
        auto list_trie{ trie.list_pre(s) };
        auto list_std{ list_pre(vs, s) };
        std::sort(list_trie.begin(), list_trie.end());
        std::sort(list_std.begin(), list_std.end());
        if (list_trie != list_std)
        {
            std::cout << "Error! - list_pre\n\n";

            std::cout << "Dictionary:\n";
            for (auto &s : vs)
            {
                std::cout << s << '\n';
            }

            std::cout << "std ans:\n";
            for (auto &s : list_std)
            {
                std::cout << s << '\n';
            }
            std::cout << "trie ans:\n";
            for (auto &s : list_trie)
            {
                std::cout << s << '\n';
            }
            exit(0);
        }
    }
}

int main()
{
    freopen("trie_test.out", "w", stdout);
    std::ios::sync_with_stdio(false);

    int t = 1000;
    while (t--)
    {
        check();
    }
    std::cout << "No problem!\n";
}

int count(std::vector<std::string> &vs, std::string &s)
{
    int ans{ 0 };
    for (auto &str : vs)
    {
        if (s == str)
            ++ans;
    }
    return ans;
}

int count_pre(std::vector<std::string> &vs, std::string &s)
{
    int ans{ 0 };
    for (auto &str : vs)
    {
        if (str.length() < s.length())
            continue;
        if (s == std::string(str.begin(), str.begin() + s.length()))
            ++ans;
    }
    return ans;
}

std::vector<std::string> list_pre(std::vector<std::string> &vs, std::string &s)
{
    std::vector<std::string> ans;
    for (auto &str : vs)
    {
        if (str.length() < s.length())
            continue;
        if (s == std::string(str.begin(), str.begin() + s.length()))
            ans.push_back(str);
    }
    return ans;
}
