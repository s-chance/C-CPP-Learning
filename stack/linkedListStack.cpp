#include <iostream>
using namespace std;

class linkedListStack
{
private:
    struct Node
    {
        char data; //数据域
        Node *next; //指针域
    };
    Node *head; //头节点
    int length; //长度, 用于判断当前是否为空栈
public:
    linkedListStack();
    ~linkedListStack();

    void push(char value); //入栈
    void pop(); //出栈
    char top(); //获取栈顶元素
    bool empty(); //判断是否为空栈, true空 false非空
};

//无参构造函数初始化头节点和长度
linkedListStack::linkedListStack()
{
    head = NULL;
    length = 0;
}

linkedListStack::~linkedListStack()
{
}

//入栈方法实现
void linkedListStack::push(char value)
{
    //创建新节点并赋值
    Node *newNode = new Node;
    newNode->data = value;
    //新节点往后指向头节点
    newNode->next = head;
    //头节点赋值为新节点, 实现头节点存储数据
    head = newNode;
    //每存储一个数据, 更新长度
    length++;
}

//出栈方法实现
void linkedListStack::pop()
{
    //判断长度是否小于等于0, 即是否已经存储了数据
    if (length <= 0)
    {
        //未存储数据, 输出提示信息后直接return终止
        cout << "未存储数据, 无法删除空栈" << endl;
        //return执行, 后面的程序则不执行
        return;
    }

    //创建节点用于存储要删除的节点
    Node *newNode;
    //赋值为头节点, 因为出栈是从栈顶开始删除, 所以删除的是原始的头节点
    newNode = head;
    //头节点赋值为头节点的下一位
    head = head->next;
    //删除节点
    delete newNode;
    //更新长度
    length--;
}

//获取栈顶元素方法实现
char linkedListStack::top()
{
    //判断头节点是否为空
    if (head == NULL)
    {
        //头节点为空, 输出提示信息后return终止
        cout << "此时为空栈" << endl;
        return;
    }

    //输出头节点的数据
    cout << head->data;
    return head->data;
}

//判空方法实现
bool linkedListStack::empty()
{
    //判断长度, 长度为0则返回true, 长度不为0则返回false
    if (length == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//测试一: 依次入栈'A' 'B' 'C' 输出栈顶元素'C'
void test1()
{
    linkedListStack stack;
    stack.push('A');
    stack.push('B');
    stack.push('C');
    stack.top();
}

//测试二: 在测试一的基础上, 执行两次出栈, 再输出栈顶元素
void test2()
{
    linkedListStack stack;
    stack.push('A');
    stack.push('B');
    stack.push('C');

    stack.pop();
    stack.pop();

    stack.top();
}

//测试三: 在测试二的基础上, 入栈'D' 'E' 'F', 再输出栈顶元素
void test3()
{
    linkedListStack stack;
    stack.push('A');
    stack.push('B');
    stack.push('C');

    stack.pop();
    stack.pop();

    stack.push('D');
    stack.push('E');
    stack.push('F');

    stack.top();
}

//测试四: 在测试三的基础上, 执行四次出栈, 再输出栈顶元素
void test4()
{
    linkedListStack stack;
    stack.push('A');
    stack.push('B');
    stack.push('C');

    stack.pop();
    stack.pop();

    stack.push('D');
    stack.push('E');
    stack.push('F');

    stack.pop();
    stack.pop();
    stack.pop();
    stack.pop();

    stack.top();
}


int f[100001];
//选做: 输出一个字符串所有可能的出栈情况
void demo()
{
    f[0] = 1;
    f[1] = 1;
    linkedListStack stack;
    linkedListStack stack2;
    linkedListStack stack3;
    string s;
    cin >> s;
    int len = s.length();

    //全入栈
    for(int i=0;i<len;i++)
    {
        for(int j=0;j<len;j++)
        {
            stack.push(s[j]);
            stack2.push(s[len-1-j]);
        }
            
        for(int k=0;k<i;k++)
        {
            stack.pop();
            // stack.push(s[len-1-k]);
            int t = len - i;
            while (t--)
            {
                stack2.pop();
            }
        }
        
        int size = 0;
            
            while (!stack.empty())
            {
                stack.top();
                stack.pop();
                size++;
            }
            while (!stack2.empty())
            {
                if (size!=len)
                    stack2.top();
                stack2.pop();
                size++;
            }
            cout << endl;
        
    }
    
    cout << endl;
}

// linkedListStack solve(char c)
// {
//     linkedListStack stack;
//     stack.push(c);


//     return solve();
// }

int main()
{
    // test1();
    // test2();
    // test3();
    // test4();

    demo();

}