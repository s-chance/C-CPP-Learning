#include <iostream>
#include <stack>
using namespace std;



int main()
{
    stack<int> stack;
    int sum = 0;
    for (int i = 0; i <= 10; i++)
    {
        stack.push(i);
    }
    cout << "size is " << stack.size() << endl;
    while (!stack.empty())
    {
        cout << " " << stack.top();
        stack.pop();
    }
    cout << endl;
}