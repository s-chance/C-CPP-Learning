#include <iostream>
#include <algorithm>
#include <stack>
#include <list>
using namespace std;

list<string> transfer(string s)
{
    int len = s.length(); //记录长度
    list<string> listIn;  //存储中缀表达式
    list<string> listOut; //存储后缀表达式
    stack<char> symbol;   //符号栈
    stack<char> ans;      //结果表达式

    listIn.push_back(s);
    for (int i = 0; i < len; i++)
    {
        //思路
        //数字直接存入ans
        //运算符:
        //如果是'('直接存入symbol
        //如果是')'依次出栈symbol中的运算符并存入ans, 直到遇到'(', '('不存入ans
        //其他符号, 依次出栈symbol中的运算符并存入ans, 直到遇到优先级更低的运算符或'('时, 将当前符号存入symbol
        //字符串遍历完成后, 依次出栈符号栈中剩余的运算符并存入ans
        if (listIn.back()[i] >= '0' && listIn.back()[i] <= '9')
            ans.push(listIn.back()[i]);
        else if (listIn.back()[i] == '(')
            symbol.push(listIn.back()[i]);
        else if (listIn.back()[i] == ')')
        {
            while (symbol.top() != '(')
            {
                ans.push(symbol.top());
                symbol.pop();
            }
            symbol.pop(); //将'('出栈
        }
        else
        {
            //这里手动优先考虑乘除的优先级高于加减
            if (listIn.back()[i] == '+' || listIn.back()[i] == '-') //加减符号优先级最低
            {
                while (!symbol.empty() && symbol.top() != '(')
                {
                    ans.push(symbol.top()); //直接存入symbol中的运算符
                    symbol.pop();
                }
                symbol.push(listIn.back()[i]); //符号栈存入当前从listIn中获取的符号
            }
            else //乘除符号优先级高直接存入符号栈
            {
                symbol.push(listIn.back()[i]);
            }
        }
    }

    while (!symbol.empty())
    {
        ans.push(symbol.top());
        symbol.pop();
    }

    //将结果表达式的值存入listOut
    //先利用已经清空的symbol实现反转
    while (!ans.empty())
    {
        symbol.push(ans.top());
        ans.pop();
    }

    string res = ""; //字符串拼接成最终结果
    while (!symbol.empty())
    {
        res += symbol.top();
        symbol.pop();
    }
    listOut.push_back(res);

    return listOut;
}

int main()
{
    string s;
    while (cin >> s)
    {
        list<string> res = transfer(s);
        cout << res.front() << "\n";
    }
}
