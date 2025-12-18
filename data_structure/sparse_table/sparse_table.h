// ST 表
#include <cmath>
#include <vector>

// 模板示例：区间第一个最大值的位置
class SparseTable
{
private:
    bool is_build_{ false };
    std::vector<int> v_{ };
    std::vector<std::vector<int>> table_{ };

public:
    SparseTable() = default;

    SparseTable(const std::vector<int> &v) : is_build_{ true }
    {
        build(v);
    }

public:
    void build(const std::vector<int> &v)
    {
        if (is_build_)
            clear();
        is_build_ = true;

        v_ = v;

        int n{ static_cast<int>(v_.size()) };
        int m{ static_cast<int>(std::floor(std::log2(n))) + 1 };
        table_.assign(n, std::vector<int>(m));

        for (int i = 0; i < n; ++i)
        {
            table_[i][0] = mark(i);
        }

        for (int j = 1; j < m; ++j)
        {
            int len{ 1 << (j - 1) };
            for (int i = 0; i < n - (1 << j) + 1; ++i)
            {
                table_[i][j] = merge(table_[i][j - 1], table_[i + len][j - 1]);
            }
        }
    }

    int query(int l, int r)
    {
        int power{ static_cast<int>(std::floor(std::log2(r - l + 1))) };
        int len{ 1 << power };
        return merge(table_[l][power], table_[r - len + 1][power]);
    }

    void clear()
    {
        is_build_ = false;
        v_.clear();
        table_.clear();
    }

private:
    // 按需修改：此函数规定贡献结果
    int merge(const int a, const int b)
    {
        if (v_[a] < v_[b])
            return b;
        if (v_[a] > v_[b])
            return a;
        return std::min(a, b);
    }

    // 按需修改：此函数规定初始贡献
    int mark(const int index)
    {
        return index;
    }
};
