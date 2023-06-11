// 测试程序：
#include <iostream>
using namespace std;

#include "linkedList.hpp"

linked_list mergeSortedList(const linked_list& L1, const linked_list& L2);
int main() {
  linked_list a1, a2, b,
      c;  // 若设计的类为模板，则采用linked_list<int>  a1,a2,b,c;
  DataType data;  // 若设计为模板类，这此处直接使用int data;
  // 正向和逆向建链测试
  // 输入2 ,6, 7, 3, 5, 9,12, 4 ,0
  while (cin >> data) {
    if (data == 0) break;  // 输入0结束
    a1.add_front(data);
    a2.add_tail(data);
  }
  a1.display();  // 逆向链 4，12，9，5，3，7，6，2
  a2.display();  // 正向链2，6，7，3，5，9，12，4
  // 链表转置测试
  // 输入2 ,16, 3, 8, 15, 4, 9, 7 ,0
  while (cin >> data) {
    if (data == 0) break;  // 输入0结束
    b.add_tail(data);
  }
  b.display();  // 原始链表2,16,3,8,15,4,9,7
  b.reverse();
  b.display();  // 转置结果7,9,4,15,8,3,16,2
  c = a1 + b;   // 测试集合并
  c.display();  // 4,12,9,5,3,7,6,2,15,8,16
  c = a1 - b;   // 测试集合差（属于a1且不属于b的数据）
  c.display();  // 12，5，6
  c = a1.intersectionSet(b);  // 测试集合交
  c.display();                // 4,9,3,7,2
  a1.sort();                  // 测试升序排序
  a1.display();               // 2,3,4,5,6,7,9,12
  // 思考需要降序排序如何做？
  b.add_tail(8);
  b.add_tail(16);
  b.add_tail(3);
  b.add_front(3);
  b.add_front(16);
  b.display();  // 16,3,7,9,4,15,8,3,16,2,8,16,3

  b.delete_all(16);   // 删除所有的16
  b.display();        // 3,7,9,4,15,8,3,2,8,3
  b.delete_repeat();  // 将b调整为无重复集合
  b.display();        // 3,7,9,4,15,8,2

  node* pos = b.find(15);
  b.add_pos_after(18, pos);
  b.display();  // 3,7,9,4,15,18,8,2

  b.add_pos_before(23, pos);
  b.display();  // 3,7,9,4,23,15,18,8,2
  b.delete_pos_after(pos);
  b.display();  // 3,7,9,4,23,15,8,2

  b.delete_pos_before(pos);
  b.display();  // 3,7,9,4,15,8,2

  b.Delete(7);
  b.display();  // 3,9,4,15,8,2
  b.Delete(8);
  b.display();  // 3,9,4,15,2

  b.sort();
  b.display();  // 2,3,4,9,15

  a2 = mergeSortedList(a1, b);
  a2.display();  // 2,3,4,5,6,7,9,12,15

  return 0;
}
