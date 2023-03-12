#include <iostream>
#include <vector>
#include <stack>
using namespace std;

template <typename T>
class tnode
{
public:
    T nodeValue;
    tnode<T> *left, *right;
    // 构造函数初始化
    tnode() {}
    tnode(const T &item, tnode<T> *lptr = NULL, tnode<T> *rptr = NULL) : nodeValue(item), left(lptr), right(rptr) {}

    // 遍历
    void Fun(tnode<char> *root, vector<tnode<char> *> &vec)
    {
        stack<tnode *> s;
        while (root || !s.empty())
        {
            while (root) // 这里是为了找到所有的左子节点
            {
                vec.push_back(root); // 存储根节点或父节点
                s.push(root);        // 暂存根节点或父节点
                root = root->left;   // 指向左子节点
            }
            if (!s.empty()) //这里是为了找到所有的右子节点
            {
                root = s.top();     // 找到根节点或父节点
                s.pop();            // 弹出根节点或父节点
                root = root->right; // 指向右子节点
            }
        }

        stack<char> res;
        while (!vec.empty())
        {
            res.push(vec.back()->nodeValue);
            vec.pop_back();
        }
        while (!res.empty())
        {
            cout << res.top();
            res.pop();
        }
    }

    // 插入
    tnode<char> *buildTree(int n)
    {
        tnode<char> *root, *b, *c, *d, *e, *f, *g, *h, *i;
        switch (n)
        {
        case 0:
            d = new tnode<char>('D');
            e = new tnode<char>('E');
            b = new tnode<char>('B', (tnode<char> *)NULL, d);
            c = new tnode<char>('C', e, (tnode<char> *)NULL);
            root = new tnode<char>('A', b, c);
            break;

        case 1:
            g = new tnode<char>('G');
            h = new tnode<char>('H');
            i = new tnode<char>('I');
            d = new tnode<char>('D');
            e = new tnode<char>('E', g, (tnode<char> *)NULL);
            f = new tnode<char>('F', h, i);
            b = new tnode<char>('B', d, e);
            c = new tnode<char>('C', (tnode<char> *)NULL, f);
            root = new tnode<char>('A', b, c);
            break;
        case 2:
            g = new tnode<char>('G');
            h = new tnode<char>('H');
            i = new tnode<char>('I');
            d = new tnode<char>('D', (tnode<char> *)NULL, g);
            e = new tnode<char>('E', h, i);
            f = new tnode<char>('F');
            b = new tnode<char>('B', d, (tnode<char> *)NULL);
            c = new tnode<char>('C', e, f);
            root = new tnode<char>('A', b, c);
            break;
        }
        return root;
    }
};

int main()
{
    tnode<char> *t;
    t = t->buildTree(1);
    vector<tnode<char> *> v;
    t->Fun(t, v);
}