// 字典树
#include <array>
#include <memory>
using std::make_unique;
using std::unique_ptr;
#include <string>
#include <vector>

class Trie
{
private:
    struct Node
    {
        std::array<Node*, 26> nexts{ }; // 指向的子节点
        int count_end{ 0 };             // 在当前节点处结束的字符串个数
        int count_pass{ 0 };            // 以当前节点为前缀的字符串个数
    };

    bool is_init{ false };
    Node* root{ nullptr };
    std::vector<unique_ptr<Node>> tree;

public:
    Trie()
    {
        init();
    }

public:
    void insert(const std::string &s)
    {
        if (!is_init)
            init();

        Node* node{ root };
        ++root->count_pass;

        for (char c : s)
        {
            int index{ c - 'a' };
            if (node->nexts[index] == nullptr)
            {
                tree.emplace_back(make_unique<Node>());
                node->nexts[index] = tree.back().get();
            }
            node = node->nexts[index];
            ++node->count_pass;
        }
        ++node->count_end;
    }

    int count(const std::string &s)
    {
        Node* node{ find_endnode(s) };
        if (node == nullptr)
            return 0;
        return node->count_end;
    }

    int count_pre(const std::string &s)
    {
        Node* node{ find_endnode(s) };
        if (node == nullptr)
            return 0;
        return node->count_pass;
    }

    std::vector<std::string> list_pre(const std::string &s)
    {
        Node* node{ find_endnode(s) };
        if (node == nullptr)
            return { };

        std::vector<std::string> ans;
        std::string str = s;
        auto dfs = [&ans, &str](auto &&dfs, Node* n) -> void
        {
            for (int i = 0; i < n->count_end; ++i)
            {
                ans.emplace_back(str);
            }
            for (int index = 0; index < 26; ++index)
            {
                if (n->nexts[index] == nullptr || n->nexts[index]->count_pass == 0)
                    continue;
                str.push_back('a' + index);
                dfs(dfs, n->nexts[index]);
                str.pop_back();
            }
        };
        dfs(dfs, node);
        return ans;
    }

    void erase(const std::string &s)
    {
        if (count(s) == 0)
            return;

        Node* node{ root };
        --root->count_pass;
        for (char c : s)
        {
            int index = c - 'a';
            node = node->nexts[index];
            --node->count_pass;
        }
        --node->count_end;
    }

    void clear()
    {
        is_init = false;
        root = nullptr;
        tree.clear();
    }

private:
    void init()
    {
        clear();
        tree.emplace_back(make_unique<Node>());
        root = tree.front().get();
        is_init = true;
    }

    Node* find_endnode(const std::string &s)
    {
        Node *node{ root };
        for (char c : s)
        {
            int index{ c - 'a' };
            if (node->nexts[index] == nullptr || node->nexts[index]->count_pass == 0)
                return nullptr;
            node = node->nexts[index];
        }
        return node;
    }
};
