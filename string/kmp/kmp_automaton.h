// KMP自动机
#include <array>
#include <string>
#include <vector>

class KMPAutomaton
{
private:
    struct Data
    {
        int fail{ 0 };
        std::array<int, 26> nexts{ };
    };

    bool is_build_{ false };
    std::string pattern_;
    std::vector<Data> automaton_;

public:
    KMPAutomaton() = default;

    KMPAutomaton(const std::string &s)
    {
        build(s);
    }

public:
    void build(const std::string &s)
    {
        if (is_build_)
            clear();
        is_build_ = true;

        pattern_ = s;
        int n{ static_cast<int>(s.length()) };
        automaton_.assign(n + 1, { });

        for (int i = 1; i < n; ++i)
        {
            int fail{ automaton_[i - 1].fail };
            while (fail > 0 && s[fail] != s[i])
            {
                fail = automaton_[fail - 1].fail;
            }
            if (s[fail] == s[i])
                ++fail;
            automaton_[i].fail = fail;
        }

        for (int i = 0; i <= n; ++i)
        {
            for (int index = 0; index < 26; ++index)
            {
                if (i < n && index + 'a' == s[i])
                    automaton_[i].nexts[index] = i + 1;
                else
                    if (i == 0)
                        automaton_[i].nexts[index] = 0;
                    else
                        automaton_[i].nexts[index] = automaton_[automaton_[i - 1].fail].nexts[index];
            }
        }
    }

    int match(const std::string &text)
    {
        int n{ static_cast<int>(text.length()) };
        int m{ static_cast<int>(pattern_.length()) };

        int index = 0;
        for (int i = 0; i < n; ++i)
        {
            index = automaton_[index].nexts[text[i] - 'a'];
            if (index == m)
                return i - m + 1;
        }
        return -1;
    }

    std::vector<int> match_all(const std::string &text)
    {
        std::vector<int> indexs;

        int n{ static_cast<int>(text.length()) };
        int m{ static_cast<int>(pattern_.length()) };

        int index = 0;
        for (int i = 0; i < n; ++i)
        {
            index = automaton_[index].nexts[text[i] - 'a'];
            if (index == m)
                indexs.push_back(i - m + 1);
        }
        return indexs;
    }

    void clear()
    {
        is_build_ = false;
        pattern_.clear();
        automaton_.clear();
    }
};