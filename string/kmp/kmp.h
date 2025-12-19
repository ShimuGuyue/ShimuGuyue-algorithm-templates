// KMP
#include <string>
#include <vector>

class KMP
{
private:
    bool is_build_{ false };
    std::string pattern_;
    std::vector<int> fail_;

public:
    KMP() = default;

    KMP(const std::string &s)
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
        fail_.assign(n, 0);

        for (int i = 1; i < n; ++i)
        {
            fail_[i] = fail_[i - 1];
            while (fail_[i] > 0 && s[fail_[i]] != s[i])
            {
                fail_[i] = fail_[fail_[i] - 1];
            }
            if (s[fail_[i]] == s[i])
                ++fail_[i];
        }
    }

    int match(std::string &text)
    {
        int n{ static_cast<int>(text.length()) };
        int m{ static_cast<int>(pattern_.length()) };

        int i{ 0 }, j{ 0 };
        while (i < n)
        {
            if (text[i] == pattern_[j])
            {
                ++i;
                ++j;
                if (j == m)
                {
                    return i - m;
                    j = fail_[j - 1];
                }
            }
            else
            {
                if (j != 0)
                    j = fail_[j - 1];
                else
                    ++i;
            }
        }
        return -1;
    }

    std::vector<int> match_all(std::string &text)
    {
        std::vector<int> indexs;

        int n{ static_cast<int>(text.length()) };
        int m{ static_cast<int>(pattern_.length()) };
        int i{ 0 }, j{ 0 };
        while (i < n)
        {
            if (text[i] == pattern_[j])
            {
                ++i;
                ++j;
                if (j == m)
                {
                    indexs.push_back(i - m);
                    j = fail_[j - 1];
                }
            }
            else
            {
                if (j != 0)
                    j = fail_[j - 1];
                else
                    ++i;
            }
        }
        return indexs;
    }

    void clear()
    {
        is_build_ = false;
        pattern_.clear();
        fail_.clear();
    }
};