#include <iostream>
using namespace std;

#define AN 5

struct queue
{
    char Arr[AN]; //队列存储空间
    int sz; //队列存储元素个数（初始化为0）
    int qback; //新插入位置
    int qfront; //队首元素位置


    queue()
    {
        sz=0;
        qback=0;
        qfront=0;
    }
    ~queue()
    {
    }
};

class Queue
{
    private:
        queue *q;

    public:
        void DeQueue(); //队列元素的删除
        void EnQueue(char value); //队列元素的插入
        bool IsEmpty(); //判空
        bool IsFull(); //判满
        char Front(); //得到队首元素

        void PrintQueueElems(); //打印当前循环队列的元素存储状况
};

//删除方法实现
void Queue::DeQueue()
{
    //未存储数据, 直接返回
    if(IsEmpty())
    {
        cout << "未存储数据" << endl;
        return;
    }
        
    //队首位置指向后一个, 更新长度, 原位置的数据相当于被删除
    q->qfront = (q->qfront + 1) % AN;
    //更新长度
    q->sz--;
}

//插入方法实现
void Queue::EnQueue(char value)
{
    if(q==0)q = new queue(); //若q为空, 则分配一个地址

    //存储的数据过多, 直接返回
    if(IsFull())
    {
        cout << "数据量超过上限" << endl;
        return;
    }
    q->Arr[q->qback] = value;
    //新插入的位置指向后一个, 防止新插入的数据覆盖掉原来的数据
    q->qback = (q->qback + 1) % AN;
    q->sz++;
}

//判空方法实现
bool Queue::IsEmpty()
{
    return (q->sz<=0); //直接判断sz是否小于等于零
}

//判满方法实现
bool Queue::IsFull()
{
    return (q->sz>=AN); //直接判断sz是否大于等于AN
}

//获取队首元素
char Queue::Front()
{
    if(IsEmpty())
    {
        cout << "未存储数据" << endl;
        return 0;
    }
    return q->Arr[q->qfront];
}

//打印当前循环队列的元素存储情况
void Queue::PrintQueueElems()
{
    for(int i=q->qfront;i<q->qfront+q->sz;i++)
    {
        cout << i%5 << "--" << q->Arr[i%AN] << endl;
    }
    cout << "qfront=" << q->qfront << ", qback=" << q->qback << endl;
}

//测试
void test()
{
    Queue q;
    q.EnQueue('A');
    q.EnQueue('B');
    q.EnQueue('C');
    cout << "------测试一-------" << endl;
    cout << q.Front() << endl;
    q.PrintQueueElems();
    cout << "------测试二-------" << endl;
    q.DeQueue();
    cout << q.Front() << endl;
    q.PrintQueueElems();
    cout << "------测试三-------" << endl;
    q.EnQueue('D');
    q.EnQueue('E');
    cout << q.Front() << endl;
    q.PrintQueueElems();
    cout << "------测试四-------" << endl;
    q.DeQueue();
    q.EnQueue('F');
    cout << q.Front() << endl;
    q.PrintQueueElems();
}

int main()
{
    test();
}