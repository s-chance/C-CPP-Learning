#include <iostream>
using namespace std;

struct Node
{
    int data;   //数据域
    Node *next; //指针域

    // struct构造函数 指针默认初始化为0
    Node(int dat, Node *p = 0)
    {
        data = dat;
        next = p;
    }
    ~Node()
    {
       delete next; //析构函数释放next         
        // cout << "释放Node" << endl;
    }
};
class LinkedList
{
public:
    //链表的基本操作
    int IsEmpty();              //判空
    void traverse();            //遍历输出
    void Insert(int value);     //插入节点
    void DeleteNode(int value); //删除节点
    Node *find(int value);      //查询节点

    void sort();                //链表排序

public:
    LinkedList(Node *p = 0)
    {
        pHead = p; //默认初始化pHead=0
    }
    ~LinkedList()
    {
        
        delete pHead; //析构函数释放pHead
        // cout << "释放LinkedList" << endl;
    }

private:
    Node *pHead;
};

//判空函数实现
int LinkedList::IsEmpty()
{
    //直接判断头节点是否为0,即可知道当前链表是否为空
    //为空返回1,不为空返回0
    return pHead == 0 ? 1 : 0;
}

//遍历函数实现
void LinkedList::traverse()
{
    //为防止遍历改变pHead的指向,使用临时节点遍历
    Node *tmp = pHead;
    for (;;)
    {
        if (tmp != 0)
        {
            cout << "具体值: " << tmp->data << "\n地址值: " << tmp << endl;
            tmp = tmp->next;
            //这里主要是为了方便观察,对输出格式进行优化
            if(tmp)
                cout << "->\n";
        }
        else
            break;
    }
}

//插入函数实现:要求插入的节点成为头节点
void LinkedList::Insert(int value)
{
    //创建新的节点: value数据 0指针初始化
    Node *newNode = new Node(value);
    //判断头节点是否未初始化为0
    //如果已初始化为0则直接指向新节点
    //如果已经保存了数据则先让新节点指向头节点,再将新节点赋值给头节点
    if (pHead)
    {
        //将已经保存的头节点数据存入新节点的下一个节点
        newNode->next = pHead;
    }

    //头节点赋值新节点
    pHead = newNode;
}

//删除函数实现
void LinkedList::DeleteNode(int value)
{
    //创建临时的节点now用于遍历,初始指向头节点
    Node *now = pHead;
    //创建临时的空节点用于移动节点的数据
    Node *prev = NULL;
    //当now已经超出目前链表的最大长度后退出循环
    while (now)
    {
        //找到对应要删除的值
        if (now->data==value)
        {
            //临时节点在这里的作用就是为了应对删除的节点位于特殊位置的情况
            //删除的是第一个节点,即头节点
           if (now==pHead)
           {
            //头节点直接指向后一个节点
            //从数据上看是后一个节点的数据移到了头节点,而原本的头节点就被覆盖
            pHead = pHead->next;
           }
           //循环到这里时,一般prev要么为空,要么为上一个now节点的数据
           //prev为空时,说明要删除的是头节点,则不需要执行
           //prev为上一个now节点的数据时,说明要删除的是中间或者最后一个节点数据
           if (prev)
           {
            //prev的下一个节点又指向了now的下一个节点,跳过了now在本次循环的当前节点的数据
            //当要删除的节点是最后一个节点时,prev的下一个节点直接初始化为NULL
            prev->next = now->next;
           }
           //释放临时节点
           free(now);
           //由于只需要删除符合条件的第一个值,这里删除完后直接跳出循环
           break;       
        }
        //用prev记录now的数据
        prev = now;
        //更新遍历的节点状态,遍历的节点后移,用于下一次循环
        now = now->next;
    }
}

//查询函数实现
Node* LinkedList::find(int value)
{
    while (pHead)
    {
        if (pHead->data == value)
        {
            //找到对应节点,返回地址
            return pHead;
        } 
        else
        {
            //未找到对应节点,头节点指向后移,为下一次循环做准备
            pHead = pHead->next;
        }
    }
    return NULL;
}

//链表排序实现
void LinkedList::sort()
{

    //尾节点的后一位, 用于循环判断
    Node *tail = 0;

    //外层循环判断循环过程是否已经达到头节点的下一位
    //当tail指向头节点的下一位说明排序已经完成
    while (tail != pHead->next)
    {
        //下面的变量放外层循环内, 内层循环外, 每完成一次内循环初始化位置

        //前一个节点, 初始置空
        Node *prev = 0;
        //当前比较的节点1, 从头节点开始
        Node *curr = pHead;
        //当前比较的节点2, 设置为比较节点1的后一位
        Node *currnext = curr->next;

        //判断循环是否到达尾节点
        while (currnext != tail)
        {
            if (curr->data > currnext->data)
            {
                //如果是头节点交换, 做特殊处理
                if (curr == pHead)
                {
                    //临时记录比较节点2, 防止节点2数据丢失
                    Node *tmp = curr->next;
                    //头节点指向比较节点2的下一位
                    curr->next = currnext->next;
                    //下一位回过来指向最初的头节点
                    currnext->next = curr;

                    //这样涉及到3个节点的二条"链"的指向就发生了变化

                    //重新设置头节点的位置
                    pHead = tmp;
                    Node *temp = curr;
                    curr = currnext;
                    currnext = temp;

                } else if (curr != pHead) 
                {
                    //非头节点交换
                    //前一位节点(prev)指向比较节点2
                    prev->next = currnext;
                    //curr指向两个比较节点的后一位
                    curr->next = currnext->next;
                    //prev所指向的比较节点2再指向最初的比较节点1
                    currnext->next = curr;
                    
                    //这样涉及到4个节点的三条"链"的指向就发生了变化

                    //重新设置curr的位置
                    Node *tmp = currnext;
                    currnext = curr;
                    curr = tmp;
                }

            }
                    
            //更新节点状态
            prev = curr;
            curr = curr->next;
            currnext = currnext->next;
        }
        //这里实际上是冒泡循环, tail从尾节点起往前记录, tail记录的节点以及tail后的节点表示已经完成排序
        tail = curr;
    }
}

//测试判空
void testEmpty()
{
    LinkedList list;
    //插入数据前执行,判断为空,返回1
    cout << "测试判空(1空 0非空)" << endl;
    list.traverse();
    cout << "未插入数据时" << endl;
    cout << "当前链表元素是否为空(1空 0非空):" << list.IsEmpty() << endl;
    //插入数据
    cout << "插入数据后" << endl;
    list.Insert(1);
    list.Insert(2);
    list.Insert(3);
    list.Insert(4);
    //插入数据后执行,判断为非空,返回0
    cout << "当前链表元素是否为空(1空 0非空):" << list.IsEmpty() << endl;
    //遍历
    cout << "遍历:";
    list.traverse();
}
//测试插入节点
void testInsert()
{
    LinkedList list;
    cout << "测试插入节点" << endl;
    cout << "初始数据:";
    list.Insert(1);
    list.Insert(2);

    list.traverse();
    list.Insert(3);
    cout << "\n插入数据后:";
    list.traverse();
}

//测试删除第一个节点
void testDeleteFirst()
{
    LinkedList list;
    cout << "测试删除第一个节点" << endl;
    cout << "初始数据:";
    list.Insert(1);
    list.Insert(2);
    list.Insert(3);
    list.Insert(4);

    list.traverse();
    //由于插入节点是从头节点插入,因此第一个节点是最后一个插入的节点
    list.DeleteNode(4);
    cout << "\n删除数据后:";
    //遍历
    list.traverse();
}
//测试删除最后一个节点
void testDeleteLast()
{
    LinkedList list;
    cout << "测试删除最后一个节点" << endl;
    cout << "初始数据:";
    list.Insert(1);
    list.Insert(2);
    list.Insert(3);
    list.Insert(4);

    list.traverse();
    //由于插入节点是从头节点插入,因此最后一个节点是第一个插入的节点
    list.DeleteNode(1);
    cout << "\n删除数据后:";
    //遍历
    list.traverse();
}
//测试查询节点
void testFind()
{
    LinkedList list;
    int value = 0;
    cout << "请输入要查询的数据:";
    cin >> value; 
    cout << "测试查询数据为" << value << "的节点" << endl;
    list.Insert(1);
    list.Insert(2);
    list.Insert(3);
    list.Insert(4);

    cout << "地址:" << list.find(value) << endl;
    //用于验证得到的地址指向的是否为查询的内容
    cout << "对应的数据:" << list.find(value)->data << endl;
}

//测试链表排序
void testSort()
{
    LinkedList list;
    list.Insert(32);
    list.Insert(3);
    list.Insert(12);
    list.Insert(19);
    cout << "排序前: \n";
    list.traverse();

    list.sort();

    cout << "\n排序后: \n";
    list.traverse();
}

int main()
{    
    // testEmpty();
    // testInsert();
    
    // testDeleteFirst();
    // testDeleteLast();
    // testFind();
    
    testSort();
    return 0;
}