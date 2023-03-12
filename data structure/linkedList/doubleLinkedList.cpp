#include <iostream>
using namespace std;

struct Node
{
    int data; //数据域

    //指针域
    Node *prev; //前置节点
    
    Node *next; //后置节点

    //构造函数, 初始化数据和指针
    Node()
    {
        prev = 0;
        next = 0;
    }
    Node(int data)
    {
        this->data = data;
        prev = 0;
        next = 0;
    }
    ~Node()
    {
    }
};

class doubleLinkedList
{
private:
    //头节点
    Node *head;
public:
    //构造函数
    doubleLinkedList()
    {
        head = new Node;
        head->next = 0;
    }
    //析构函数
    ~doubleLinkedList()
    {
        delete head;
    }

    //方法
    void InsertNode(int value); //插入节点
    void DeleteNode(int value); //删除节点
    void traverse(); //遍历输出节点

    void problem(int n, int m); //约瑟夫问题
};


//插入节点函数实现
void doubleLinkedList::InsertNode(int value)
{
    //创建新节点
    Node *newNode = new Node(value);

    //初始设置新节点自我指向, 主要是针对只存储一个节点的情况
    newNode->next = newNode;
    newNode->prev = newNode;

    //创建前置节点, 当链表中已经存储数据时使用
    Node *prevNode = 0;
    // //创建后置节点, 当链表中已经存储数据时使用
    // Node *nextNode = 0;
    //创建尾节点, 用于首尾连接
    Node *tailNode = 0;

    //判断是否已经存储数据
    if (head->next)
    {
        //找到尾节点
        Node *tmp = head->next;
        do
        {
            tailNode = tmp;
            tmp = tmp->next;
        } while (tmp != head->next);

        
        //前置节点保存哑元头节点指向的有数据的地址
        //这一步使得prevNode每次新增节点之前都是第一个节点
        prevNode = head->next;
        if (prevNode->next)
        {
            //当链表至少已经存在两个数据时使用尾节点
            //在以上条件下新增加的就是第三个数据
            newNode->next = prevNode;
            prevNode->prev = newNode;
            newNode->prev = tailNode;
            tailNode->next = newNode;

        } else 
        {
            //以下操作使得两个节点双向指向
            //新节点往后指向前置节点保存的地址
            newNode->next = prevNode;
            //前置节点保存的地址往前指向新节点
            prevNode->prev = newNode;
            //新节点往前指向前置节点保存的地址
            newNode->prev = prevNode;
            //前置节点保存的地址往后指向新节点
            prevNode->next = newNode;

            //形成环
        }
    }
    
    //头节点指向新节点
    head->next = newNode;
}


//删除节点函数实现
void doubleLinkedList::DeleteNode(int value)
{

    //创建前置节点, 初始为0
    Node *prevNode = 0;
    //创建一个当前比较的节点
    Node *currNode = head->next;
    //创建一个后置节点, 初始为0
    Node *nextNode = 0;
    do
    {
        if (currNode->data == value)
        {
            //考虑链表只有一个节点数据的情况
            if (currNode->next == currNode)
            {
                //链表中剩余的最后一个数据节点删除
                //相当于初始化头节点的指向为0
                head->next = 0;
                return;
            }
            
            //使用后置节点指向目标节点后一个地址
            nextNode = currNode->next;
            //使用前置节点指向目标节点前一个地址
            prevNode = currNode->prev;
            //前置节点指向删除节点的下一位
            prevNode->next = nextNode;
            //后置节点再往前指向前置节点, 实现双向
            nextNode->prev = prevNode;

            break;
        }

        // //下一次循环前置节点指向本次的比较节点
        // prevNode->next = currNode;
        //本次参与比较的节点后移, 为下一次循环准备
        currNode = currNode->next;
    } while (currNode!=head->next);
}

//遍历函数实现
void doubleLinkedList::traverse()
{
    //如果链表并未保存任何数据, 直接返回
    if (!head->next)
    {
        cout << "还未存储任何数据" << endl;
        return;
    }

    //临时节点指向头节点的下一位
    Node *tmp = head->next;
    //双向循环链表完成遍历的依据是当前节点是否重新指向哑元头节点下一位
    do
    {
        cout << "数据: " << tmp->data << " 地址: " << tmp << endl;
        cout << "prev地址: " << tmp->prev << " " << "next地址: " << tmp->next << endl;
        tmp = tmp->next;
    } while (tmp!=head->next);
    
    //释放节点
    delete tmp;
}

//约瑟夫问题实现
void doubleLinkedList::problem(int n, int m)
{
    //创建指针用于访问链表
    Node *curr;
    //总人数n, 对每个人进行编号
    for(int i=1;i<=n;i++)
        InsertNode(i);
    
    //此时head指向最后的数据, 这里使用的是头插法
    //获取第一个数据则往前指向尾节点(第一个数据节点)
    curr = head->next->prev;

    //具体逻辑实现
    for(int i=1;i<n;i++)
    {
        //每隔两位进行输出
        for(int j=1;j<=m-1;j++)
        {
            curr = curr->prev;
        }
        cout << curr->data << " ";
        //对于输出的数据直接删除
        DeleteNode(curr->data);
        //删除完后重新赋值下一个节点的地址
        curr = curr->prev;
    }
    //最后的序号即为胜利者
    cout << "winner: " << curr->data;
}

//测试插入函数
void testInsert()
{
    doubleLinkedList list;
    list.InsertNode(1);
    list.InsertNode(2);
    list.InsertNode(3);
    list.InsertNode(5);
    list.InsertNode(6);

    list.traverse();
}

//测试删除函数
void testDelete()
{
    doubleLinkedList list;
    list.InsertNode(1);
    list.InsertNode(2);
    list.InsertNode(3);
    list.InsertNode(4);
    list.DeleteNode(3);
    list.traverse();
}

//约瑟夫问题测试
void testProblem()
{
    doubleLinkedList list;
    list.problem(41, 3);
}

int main()
{
    // testInsert();
    // testDelete();
    testProblem();
}
