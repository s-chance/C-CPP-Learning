#include <iostream>
using namespace std;

class miniVector
{
    public:
        miniVector(int size); //构造函数
        ~miniVector(); //析构函数
        void push_back(int item); //添加
        void pop_back(); //删除
        void search(int item); //查询
        void traverse(); //遍历
        int IsSortedVector(); //判断数据是否从小到大排序

    private:
        int vCapacity; //最大容量
        int vSize; //实际大小
        int *vArr; //指针地址
        void reserve(int n, bool copy); //扩容
};

miniVector::miniVector(int size = 0)
{
    //初始化
    vSize = 0;
    vCapacity = 0;
    vArr = NULL;

    //根据传入的size对vector的最大容量进行初始化
    //相应地进行扩容
    reserve(size, false);

    for(int i=0;i<vSize;i++)
    {
        //初始化指针
        vArr[i] = 0;
    }
}

miniVector::~miniVector()
{
    //释放指针数组
    if(vArr!=NULL)
    {
        delete[] vArr;
    }
}

//添加方法实现
void miniVector::push_back(int item)
{
    //如果当前实际大小超过了最大容量, 进行扩容
    if(vSize == vCapacity)
    {
        //首次添加数据时, vCapacity默认为0, 则进行扩容
        if (vCapacity == 0)
            reserve(1, false);
        else
            //扩容两倍
            reserve(2*vCapacity, true);
    }

    //添加数据
    vArr[vSize] = item;
    vSize++;
}

//删除方法实现
void miniVector::pop_back()
{
    //只需要将当前的vSize-1即可
    //因为后面的新增, 遍历等操作都是基于vSize来实现的
    //新增时最后的数据会被覆盖, 遍历时不会遍历到最后的数据
    //本质上是根据vSize在程序中是表示当前实际大小的定义而实现
    vSize--;
}

//查询方法实现
void miniVector::search(int item)
{
    //循环查找
    for(int i=0;i<vSize;i++)
    {
        //查找到数据
        if (*(vArr+i) == item)
        {
            cout << "地址: " << vArr+i << endl;
            cout << "数据: " << *(vArr+i) << endl;
            return;
        }
    }
    cout << "查询的数据不存在" << endl;
}

//扩容方法实现
void miniVector::reserve(int n, bool copy)
{
    //创建新指针
    int *newArr;
    //根据传入的n值创建指定大小的数组
    newArr = new int[n];
    //判断是否要复制原有的数据
    if (copy)
    {
        for(int i=0;i<vSize;i++)
            newArr[i] = vArr[i];
        //赋值完后释放原有的指针
        if(vArr!=NULL)
            delete[] vArr;
    }
    //重新将新指针赋值给vArr
    vArr = newArr;
    //更新vCapacity的值
    vCapacity = n;
}

//遍历方法实现
void miniVector::traverse()
{
    for(int i=0;i<vSize;i++)
    {
        cout << *(vArr + i)  << " ";
    }
}

//判断是否从小到大排序方法实现
int miniVector::IsSortedVector()
{
    
    //比较大小
    for(int i=0;i<vSize-1;i++)
    {
        //出现逆序, 返回0
        if (*vArr>*(vArr+1))
            return 0;
        //每次比较完后更新vArr的地址
        vArr = vArr + 1;
    }

    //全部有序, 返回1
    return 1;
}

//新增方法测试
void testPush()
{
    miniVector *vec = new miniVector();
    cout << "新增数据方法" << endl;
    vec->push_back(1);
    vec->push_back(2);
    vec->push_back(3);
    vec->push_back(4);
    vec->traverse();
}

//删除方法测试
void testPop()
{
    miniVector *vec = new miniVector();
    cout << "删除数据方法" << endl;
    vec->push_back(1);
    vec->push_back(2);
    vec->push_back(3);
    vec->push_back(4);
    cout << "原始数据: ";
    vec->traverse();
    //删除尾部的数据
    vec->pop_back();
    cout << "删除操作后的数据: ";
    vec->traverse();
}

//查询方法测试
void testSearch()
{
    miniVector *vec = new miniVector();
    cout << "查询数据方法" << endl;
    vec->push_back(1);
    vec->push_back(2);
    vec->push_back(3);
    vec->push_back(4);
    cout << "请输入需要查找的数据: ";
    int target;
    cin >> target;
    vec->search(target);
}

//判断是否升序方法测试(升序数据)
void testIsSortedOK()
{
    miniVector *vec = new miniVector();
    cout << "升序判断方法(升序返回1, 逆序返回0)" << endl;
    cout << "升序测试数据" << endl;
    vec->push_back(1);
    vec->push_back(2);
    vec->push_back(3);
    vec->push_back(4);
    vec->traverse();
    cout << endl;
    cout << "结果: " << vec->IsSortedVector() << endl;
}

//判断是否升序方法测试(乱序数据)
void testIsSortedFail()
{
    miniVector *vec = new miniVector();
    cout << "升序判断方法(升序返回1, 逆序返回0)" << endl;
    cout << "乱序测试数据" << endl;
    vec->push_back(4);
    vec->push_back(5);
    vec->push_back(2);
    vec->push_back(1);
    vec->traverse();
    cout << endl;
    cout << "结果: " << vec->IsSortedVector() << endl;
}

int main()
{
    
    // testPush();
    // testPop();
    // testSearch();
    testIsSortedOK();
    testIsSortedFail();
}