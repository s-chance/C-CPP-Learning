#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data; //数据域
    struct node *next; //链
} Node, *LinkList;

void process(LinkList L, int x, int *count)
{
    LinkList tmp = L; //缓存变量
    LinkList head = L; //头节点
    int len = 0; //长度
    while (tmp&&tmp->data != x) //统计小于x的数据的长度
    {
        tmp = tmp->next; //后移
        len++;
    }
    
    int front; //前置值
    LinkList prev; //前置节点
    while (tmp&&tmp->data == x)
    {
        prev = tmp; //记录数据值等于x的最后一个节点
        front = tmp->data; //记录值
        tmp = tmp->next; //后移
    }

    while (tmp&&tmp->data > x)
    {
        
        if(tmp->data != front)++(*count); //统计大于x的数据数量, 前置值用于避免相同整数重复统计
        
        if(tmp->data > x && tmp->data % 2 ==0) //找到大于x且为偶数的数据
        {
            prev->next = tmp->next; //删除数据
            --(*count); //更新统计数
            tmp = prev->next; //移到已删除数据的后一个地址
            continue; //直接跳过本次循环, 进入下一次循环
        }
        //删除了数据的情况下, prev的下一个位置就是下次循环需要用于判断的节点, 
        //但prev是前置节点, 需要始终保持它在tmp的前一个地址, 
        //因此在删除了数据的情况下prev不进行后移操作

        //本次循环未删除任何数据的情况
        prev = prev->next; //前置节点后移
        front = prev->data; //更新前置值
        tmp = prev->next; //用于判断的节点后移
    }
    

    LinkList t = head;
    for(int i=len-2;i>=0;i--)
    {
        for(int j=0;j<=i;j++)
        {
            if(t->data <= t->next->data)
            {
                int tmp = t->data;
                t->data = t->next->data;
                t->next->data = tmp;
                t = t->next;
            }
        }
        t = head;
    }
}

int main()
{

    // int arr[] = {1, 2, 3, 4, 4, 5, 6, 7};
    // int arr[] = {2, 4, 6, 8, 10, 12, 14};
    // int arr[] = {1, 3, 5, 7, 9, 11, 13};
    int arr[] = {0, 1, 4, 5, 5, 7, 7, 8, 8, 8, 9};
    int len = sizeof(arr)/sizeof(arr[0]);
    LinkList L = (LinkList)malloc(sizeof(LinkList));
    LinkList head = L;

    int x = 4;
    int count = 0;

    for(int i=0;i<len;i++)
    {
        L->data = arr[i];
        L->next = (struct node *)malloc(sizeof(struct node));
        if(i==len-1)L->next = 0;
        L = L->next;
    }

    process(head, x, &count);

    while(head)
    {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");

    printf("比%d大的数有%d位(相同整数算1位)\n", x, count);

    free(head);
    free(L);
}