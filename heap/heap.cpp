#include <iostream>
#include <vector>
using namespace std;

// 堆插入实现
void pushHeap(vector<int> &v)
{
    int currentPos, parentPos; // 当前位置，父节点位置
    int target, last = v.size();
    currentPos = last - 1;
    parentPos = (currentPos - 1) / 2;
    target = v[last - 1];   // 获取插入的值
    while (currentPos != 0) // 完成插入节点时最大堆的调整
    {
        if (target > v[parentPos]) // 值大于父节点，上调
        {
            v[currentPos] = v[parentPos];     // 当前位置赋值为父节点的值
            currentPos = parentPos;           // 当前位置从插入位置指向父节点位置
            parentPos = (currentPos - 1) / 2; // 获取上一级父节点位置
        }
        else
            break;
    }
    v[currentPos] = target; // 将上调的值赋给合适的位置
}

// 堆删除后调整为最大堆实现
template <typename Compare>
void adjustHeap(vector<int> &v, int first, int last, Compare comp)
{
    int currentPos, childPos; // 当前位置，子节点位置
    int target;
    currentPos = first;
    target = v[first]; // 获取要下调的值
    childPos = 2 * currentPos + 1;
    while (childPos <= last - 1) // 完成删除节点时最大堆的调整
    {
        if ((childPos + 1 <= last - 1) && comp(v[childPos + 1], v[childPos])) // 找到两个子节点中较大的节点
            childPos = childPos + 1;
        if (comp(v[childPos], target))
        {
            v[currentPos] = v[childPos];   // 当前位置赋值为较大的子节点的值
            currentPos = childPos;         // 当前位置指向较大的子节点
            childPos = 2 * currentPos + 1; // 获取下一级左子节点位置
        }
        else
            break;
    }
    v[currentPos] = target; // 将下调的值赋给合适的位置
}

// 堆删除实现
template <typename Compare>
void popHeap(vector<int> &v, int last, Compare comp)
{
    // 直接交换根节点与叶子节点的值
    int temp;
    temp = v[0];
    v[0] = v[last - 1];
    v[last - 1] = temp;

    adjustHeap(v, 0, last - 1, comp); // 重新调整为最大堆
}

// 创建堆实现(未使用)
template <typename Compare>
void makeHeap(vector<int> &v, Compare comp)
{
    int headPos, lastPos;
    lastPos = v.size();
    headPos = (lastPos - 2) / 2;
    while (headPos >= 0)
    {
        adjustHeap(v, headPos, lastPos, comp);
        headPos--;
    }
}

// 堆排序实现(未使用)
template <typename Compare>
void heapSort(vector<int> &v, Compare comp)
{
    makeHeap(v, comp);
    int i, n = v.size();
    for (i = n; i > 1; i--)
        popHeap(v, i, comp);
}

void test()
{
    int arr[] = {5, 3, 12, 1, 9, 10};
    int i, arrSize = sizeof(arr) / sizeof(int);
    vector<int> vA;
    for (i = 0; i < arrSize; i++)
    {
        vA.push_back(arr[i]);
        if (vA[i] == 12) // 测试插入12前后的向量值
        {
            int target = vA[i];
            cout << "插入 " << target << " 前: ";
            for (int j = 0; j < i; j++)
                cout << vA[j] << " ";
            cout << "\n";
            pushHeap(vA);
            cout << "插入 " << target << " 后: ";
            for (int j = 0; j < vA.size(); j++)
                cout << vA[j] << " ";
            cout << "\n";
            continue;
        }
        if (vA[i] == 10) // 测试插入10前后的向量值
        {
            int target = vA[i];
            cout << "插入 " << target << " 前: ";
            for (int j = 0; j < i; j++)
                cout << vA[j] << " ";
            cout << "\n";
            pushHeap(vA);
            cout << "插入 " << target << " 后: ";
            for (int j = 0; j < vA.size(); j++)
                cout << vA[j] << " ";
            cout << "\n";
            continue;
        }
        pushHeap(vA);
    }
    for (int i = 0; i < vA.size(); i++)
    {
        if (vA[i] != 12)
            continue;
        // 测试删除12前后的向量值
        int target = vA[i];
        cout << "删除 " << target << " 前: ";

        for (int i = 0; i < vA.size(); i++)
            cout << vA[i] << " ";
        cout << "\n";
        popHeap(vA, vA.size(), greater<int>());

        cout << "删除 " << target << " 后: ";
        for (int i = 0; i < vA.size() - 1; i++)
            cout << vA[i] << " ";
        cout << "\n";
        break;
    }
}

void testSort()
{
    int arr[] = {5, 3, 12, 1, 9, 10};
    int i, arrSize = sizeof(arr) / sizeof(int);
    vector<int> vA;
    for (i = 0; i < arrSize; i++)
    {
        vA.push_back(arr[i]);
        pushHeap(vA);
    }

    cout << "最大堆化: ";
    for (int i = 0; i < vA.size(); i++)
        cout << vA[i] << " ";
}

int main()
{
    test();
    testSort();
}