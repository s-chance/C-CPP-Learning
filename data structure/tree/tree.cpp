#include <iostream>
#include <vector>
#include <stack>
using namespace std;

template <typename T>
class tnode
{
private:
    tnode *myRoot; // 根节点

public:
    bool search(const T &item) const; // 查询(只读)

    void insert(const T &item); // 插入

    void InsertAux(tnode *&CurNode, T &item); // 递归插入(未使用)

    void remove(const T &item); // 删除

    T nodeValue;            // 数据值
    tnode<T> *left, *right; // 当前节点，左子节点，右子节点

    // 构造函数初始化
    tnode() : myRoot(0), left(0), right(0) {}
    tnode(const T &item, tnode<T> *ptr = NULL, tnode<T> *lptr = NULL, tnode<T> *rptr = NULL) : nodeValue(item), myRoot(ptr), left(lptr), right(rptr) {}

    // 中序遍历(左-中-右)
    // 先把最左边的边缘节点及根节点存入向量，再往上找父节点(父节点已存储)，将父节点的右子节点及其二级子节点按左中右的顺序存入向量
    void Fun(vector<tnode<T> *> &vec)
    {
        tnode<T> *root = myRoot;
        stack<tnode *> s;
        while (root || !s.empty())
        {
            while (root) // 这里是为了找到所有的左子节点
            {
                s.push(root);      // 暂存节点(一开始存储了所有的最左边缘子节点及根节点，然后是子树中的左-中-右节点)
                root = root->left; // 指向左子节点
            }
            if (!s.empty()) //这里是为了找到所有的右子节点
            {
                root = s.top();      // 找到根节点或父节点
                vec.push_back(root); // 将栈中的数据存入，栈顶从上往下就是左中右顺序节点的
                s.pop();             // 弹出根节点或父节点
                root = root->right;  // 指向右子节点
            }
        }
    }
};

// 插入函数实现
template <typename T>
void tnode<T>::insert(const T &item)
{
    tnode *locptr = myRoot, *parent = 0;
    bool found = false;
    while (!found && locptr != 0) // 查找是否存在重复的数据，原理和查找函数基本一致，只是引入了parent用来初始化根节点
    {
        parent = locptr;
        if (item < locptr->nodeValue)
            locptr = locptr->left;
        else if (locptr->nodeValue < item)
            locptr = locptr->right;
        else
            found = true;
    }

    if (!found)
    {
        locptr = new tnode(item);
        if (parent == 0) // 根节点未存储数据，初始化根节点
            myRoot = locptr;
        else if (item < parent->nodeValue) // 子节点存储数据
            parent->left = locptr;         // 小的数据存储在左子节点

        else
            parent->right = locptr; // 大的数据存储在右子节点
    }
    else
        cout << "The value " << locptr->nodeValue << " is already exists\n"; // 已经存在的数据不重复存储
};
// 查找函数实现
template <typename T>
bool tnode<T>::search(const T &item) const
{
    tnode<T> *locptr = myRoot; // 指向根节点
    bool found = false;
    while (!found && locptr != 0)
    {
        if (item < locptr->nodeValue) // 小的数据往左边寻找
            locptr = locptr->left;
        else if (locptr->nodeValue < item) // 大的数据往右边寻找
            locptr = locptr->right;
        else
            found = true;
    }
    return found;
};

// 递归插入
template <typename T>
void tnode<T>::InsertAux(tnode *&CurNode, T &item)
{
    if (CurNode == NULL)
    {
        CurNode = new tnode(item);
        return;
    }
    if (CurNode->nodeValue > item)
        InsertAux(CurNode->left, item);
    else if (CurNode->nodeValue < item)
        InsertAux(CurNode->right, item);
    else
    {
        cout << "The value is already exists\n";
        return;
    }
};

// 删除函数实现：先查询再删除
template <typename T>
void tnode<T>::remove(const T &item)
{
    tnode<T> *locptr = myRoot;
    tnode<T> *root = locptr;
    tnode<T> *parent = root; // 存储要删除节点的父节点
    bool found = false;
    while (!found && locptr != 0)
    {
        if (item < locptr->nodeValue)
        {
            parent = locptr;
            locptr = locptr->left;
        }
        else if (locptr->nodeValue < item)
        {
            parent = locptr;
            locptr = locptr->right;
        }
        else
            found = true;
    }
    if (!found)
        cout << "Can't delete, because the value " << item << " is not exists\n";
    else if (locptr == root) // 要删除的是根节点，因为没有父节点所以单独处理
    {
        // 寻找最接近根数据的叶子节点，从右边寻找
        // 右子树中最接近根节点的数据基本都是左子节点
        // 根节点一定小于它的右子树，所以只需要在右子树往左寻找最接近根节点数据的左子节点即可
        tnode<T> *target = root->right;
        while (target->left)
        {
            parent = target;       // 存储新一个根节点在交换前的父节点
            target = target->left; // 往左寻找子节点
        }
        // 特殊情况，右子树中最接近根节点数据的就是根节点的右子节点，这个时候右子节点自身不可能存在更加接近根节点数据的左子节点，但可能存在右子节点
        if (target == root->right)
        {
            target->left = root->left; // 右子节点往左直接指向根的左子节点
            root = target;             // 根赋值为它的右子节点
            myRoot = root;             // 更新树的状态
        }
        else
        {
            if (target->right) // 判断新根节点交换前是否还有右子节点需要处理
                parent->left = target->right;
            else
                parent->left = 0;
            target->left = root->left;   // 新根节点连接左子树
            target->right = root->right; //新根节点连接右子树
            root = target;
            myRoot = root;
        }
    }
    else // 四种情况
    {
        if (locptr->nodeValue < parent->nodeValue) // 位于父节点左边
        {
            if (!locptr->left && !locptr->right) // 没有子节点
                parent->left = 0;
            else if (locptr->left && !locptr->right) // 有左子节点
                parent->left = locptr->left;
            else if (!locptr->left && locptr->right) // 有右子节点
                parent->left = locptr->right;
            else if (locptr->left && locptr->right) // 左右两个子节点都有
            {
                locptr->right->left = locptr->left; // 右子节点往左指向左子节点
                parent->left = locptr->right;       // 父节点往左指向二级右子节点
                // 实现了右子节点与要删除的节点的替换
            }
        }
        else if (locptr->nodeValue > parent->nodeValue) // 位于父节点右边
        {
            if (!locptr->left && !locptr->right) // 没有子节点
                parent->right = 0;
            else if (locptr->left && !locptr->right) // 有左子节点
                parent->right = locptr->left;
            else if (!locptr->left && locptr->right) // 有右子节点
                parent->right = locptr->right;
            else if (locptr->left && locptr->right) // 左右两个子节点都有
            {
                locptr->right->left = locptr->left; // 右子节点往左指向左子节点
                parent->right = locptr->right;      // 父节点指向二级右子节点
            }
        }
        myRoot = root; // 将删除完成的树状态进行同步
    }
};

// 测试数据
void testOrder()
{
    tnode<int> *t = new tnode<int>();
    t->insert(3);
    t->insert(2);
    t->insert(5);
    t->insert(4);
    t->insert(1);
    t->insert(6);
    t->insert(7);

    cout << "中序遍历结果: ";
    vector<tnode<int> *> vec;
    t->Fun(vec);
    for (int i = 0; i < vec.size(); i++)
        cout << vec[i]->nodeValue << " ";
    cout << "\n";
    delete t;
}
// 删除操作验证
void testRemove()
{
    tnode<int> *t = new tnode<int>();
    t->insert(6);
    t->insert(4);
    t->insert(1);
    t->insert(5);
    t->insert(2);
    t->insert(9);
    t->insert(7);
    t->insert(8);
    t->insert(10);
    cout << "删除前: ";
    vector<tnode<int> *> vec;
    t->Fun(vec);
    for (int i = 0; i < vec.size(); i++)
        cout << vec[i]->nodeValue << " ";

    int n;
    cout << "\n请输入需要删除的节点值\n";
    cin >> n;
    t->remove(n);
    cout << "\n删除后: ";
    vector<tnode<int> *> removeRes;
    t->Fun(removeRes);
    for (int i = 0; i < removeRes.size(); i++)
        cout << removeRes[i]->nodeValue << " ";
    delete t;
}

int main()
{
    testOrder(); // 中序遍历测试

    testRemove(); // 删除测试
}