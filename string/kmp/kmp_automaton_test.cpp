#include "kmp_automaton.h"

#include <iostream>
#include <random>

std::mt19937 rand32(time(nullptr));



int match(const std::string &pattern, const std::string &text);
std::vector<int> match_all(const std::string &pattern, const std::string &text);

void check()
{
    int n{ static_cast<int>(rand32() % 10 + 1) };
    std::string pattern;
    for (int i = 0; i < n; ++i)
    {
        pattern.push_back(rand32() % 26 + 'a');
    }

    // KMPAutomaton kmp(pattern);
    KMPAutomaton kmp;
    kmp.build(pattern);

    int k{ static_cast<int>(rand32() % 10000) };
    while (k--)
    {
        int m{static_cast<int>(rand32() % 100 + 1)};
        std::string text;
        for (int i = 0; i < n; ++i)
        {
            text.push_back(rand32() % 26 + 'a');
        }

        {
            int ans_std{ match(pattern, text) };
            int ans_kmp{ kmp.match(text) };
            if (ans_std != ans_kmp)
            {
                std::cout << "Error! - match\n\n";

                std::cout << "pattern: " << pattern << '\n';
                std::cout << "text: " << text << '\n';

                std::cout << "std ans: " << ans_std << '\n';
                std::cout << "kmp ans: " << ans_kmp << '\n';
                exit(0);
            }
        }

        {
            auto ans_std{match_all(pattern, text)};
            auto ans_kmp{kmp.match_all(text)};
            if (ans_std != ans_kmp)
            {
                std::cout << "Error! - match_all\n\n";

                std::cout << "pattern: " << pattern << '\n';
                std::cout << "text: " << text << '\n';

                std::cout << "std ans:\n";
                for (int i : ans_std)
                {
                    std::cout << i << ' ';
                }
                std::cout << '\n';
                std::cout << "kmp ans:\n";
                for (int i : ans_kmp)
                {
                    std::cout << i << ' ';
                }
                std::cout << '\n';
                exit(0);
            }
        }
    }
}

int main()
{
    freopen("kmp_automaton_test.out", "w", stdout);
    std::ios::sync_with_stdio(false);

    int t = 10000;
    while (t--)
    {
        check();
    }
    std::cout << "No problem!\n";
}

int match(const std::string &pattern, const std::string &text)
{
    int n{ static_cast<int>(pattern.length()) };
    int m{ static_cast<int>(text.length()) };
    for (int i = 0; i + n - 1 < m; ++i)
    {
        bool find{ true };
        for (int j = 0; j < n; ++j)
        {
            if (pattern[j] != text[i + j])
            {
                find = false;
                break;
            }
        }
        if (find)
            return i;
    }
    return -1;
}

std::vector<int> match_all(const std::string &pattern, const std::string &text)
{
    std::vector<int> ans;

    int n{ static_cast<int>(pattern.length()) };
    int m{ static_cast<int>(text.length()) };
    for (int i = 0; i + n - 1 < m; ++i)
    {
        bool find{ true };
        for (int j = 0; j < n; ++j)
        {
            if (pattern[j] != text[i + j])
            {
                find = false;
                break;
            }
        }
        if (find)
            ans.push_back(i);
    }
    return ans;
}