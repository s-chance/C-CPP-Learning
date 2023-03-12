#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
using namespace std;

void out(vector<double> v)
{
    for (int i = 0; i < v.size(); i++)
        cout << v[i] << " ";
    cout << "\n";
}

void BubbleSort(vector<double> &v)
{
    int n = v.size();
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = n - 1; j > i; j--)
        {
            if (v[j] < v[j - 1])
            {
                double t = v[j];
                v[j] = v[j - 1];
                v[j - 1] = t;
            }
        }
        // cout << "第" << (i + 1) << "次遍历: ";
        // out(v);
    }
}

int split(vector<double> &v, int first, int last)
{
    double pivot = v[first];        // 由于是随机乱序的数据集, 这里直接以第一个元素作为基准
    int left = first, right = last; // 左指针初始指向第一个元素, 右指针初始指向最后一个元素
    while (left < right)
    {
        // 直到右指针找到小于等于基准的值
        while (pivot < v[right])
            right--;
        // 直到左指针找到大于基准的值
        while (left < right && (v[left] < pivot || v[left] == pivot))
            left++;
        if (left < right)
            swap(v[left], v[right]); // 左右指针未碰头时交换两个值
    }
    // 查找结束找到基准位置, 此时左右指针指向同一个位置
    int pos = right;
    v[first] = v[pos]; // 基准位置上的值移到前面
    v[pos] = pivot;    // 基准值移到基准位置上
    // out(v);
    return pos; // 返回基准位置
}

void QuickSort(vector<double> &v, int first, int last)
{
    int pos;
    if (first < last)
    {
        pos = split(v, first, last);
        QuickSort(v, first, pos - 1);
        QuickSort(v, pos + 1, last);
    }
}

// 创建100000个数据
vector<double> data()
{
    vector<double> v;
    for (int i = 0; i < 100000; i++)
        v.push_back(rand());
    return v;
}

void bigDataBubble(vector<double> v)
{
    float x, y;
    clock_t time_req;

    srand((int)time(0));

    time_req = clock();

    BubbleSort(v);

    time_req = clock() - time_req;
    time_req = (float)time_req / CLOCKS_PER_SEC;
    cout << "Using BubbleSort function, it took " << time_req << " seconds\n";
}

void bigDataQuick(vector<double> v)
{
    float x, y;
    clock_t time_req;

    srand((int)time(0));

    time_req = clock();

    QuickSort(v, 0, v.size() - 1);

    time_req = clock() - time_req;
    time_req = (float)time_req;
    cout << "Using QuickSort function, it took " << time_req << " Milliseconds\n";
}

int main()
{

    // vector<double> v = {0.5, 2.3, 4.0, 6.0, 7.0, 8.9, 1.5, 0.8};
    // cout << "初始数据: ";
    // out(v);

    // BubbleSort(v);
    // QuickSort(v, 0, v.size() - 1);
    // out(v);

    vector<double> v = data();

    for (int i = 0; i < 5; i++)
    {
        cout << "第" << (i + 1) << "组数据: \n";
        bigDataBubble(v);
        bigDataQuick(v);
    }
}