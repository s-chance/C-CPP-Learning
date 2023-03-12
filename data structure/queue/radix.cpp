#include <iostream>
#include <queue>
#include <vector>
using namespace std;

vector<int> radixSort(vector<int> arr, int len)
{

    int *tmp = new int[len]; //用于临时存储排序结果
    int *count = new int[10]; //计数器用于记录含有0-9数字的个数

    //统计最大值的最高位数
    int max = arr[0];
    for(int h=1;h<len;h++)
    {
        if(max<arr[h])max = arr[h];
    }
    int t = 1; //用于记录最大的最高位数, 同时用于基数排序最外层循环次数
    while (max>=10)
    {
        max/=10;
        t++;
    }
    
    int cmp; //用于记录数字中某一位数
    int d = 1; //用于依次计算获取数字中的某一位数
    for(int i=0;i<t;i++)
    {
        for(int j=0;j<10;j++)
            count[j]=0; //每次排序进行初始化
        for(int k=0;k<len;k++)
        {
            cmp = arr[k]/d % 10; //取出某一位数, 找到对应编号的“桶”计数
            count[cmp]++; //count相当于一个“桶”, 下标就是编号
        }
        for(int l=1;l<10;l++)
            count[l]+=count[l-1]; //更新每不同位数对应于结果数组的下标
        for(int m=len-1;m>=0;m--)
        {
            cmp = arr[m]/d%10; //取出某一位数
            tmp[count[cmp]-1] = arr[m]; //将数据存入tmp
            count[cmp]--; //更新计数, 防止下一次被某一位数相同的数据覆盖
        }
        

        while(!arr.empty())
                arr.pop_back();

        for(int n=0;n<len;n++)
            arr.push_back(tmp[n]); //将数据存入到arr中
            

        d*=10; //更新除数, 用于下次循环
    }
    delete []tmp;
    delete []count;
    return arr;
}

int main()
{
    vector<int> vector;
    int arr[] = {38, 102, 45, 89, 67};
    int len = sizeof(arr)/sizeof(arr[0]);
    for(int i=0;i<len;i++)
    {
        vector.push_back(arr[i]);
    }
    vector = radixSort(vector, vector.size());

    for(int i=0;i<len;i++)
        cout << vector[i] << " ";
}