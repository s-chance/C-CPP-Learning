#include <iostream>
#include <string>
#include <cstring>
using namespace std;

class reload
{
private:
    string info;
public:
    reload(string str);
    reload(const reload& r);
    reload& operator=(const reload&);
    void show();
    ~reload();
};

reload::reload(string s)
{
    info = s;
}

//深拷贝构造函数
reload::reload(const reload& r)
{
    //调用重载操作符=
    *this = r;
}

//实现深拷贝
reload& reload::operator=(const reload  &obj)
{
    info = obj.info.substr(0, obj.info.length());
    return *this;
}
void reload::show()
{
    cout << this->info << endl;
}
reload::~reload()
{}

int main()
{
    reload obj1("live");
    //重载操作符=实现复杂类型深拷贝
    reload obj2 = obj1;
    reload obj3("boat");
    obj1.show();
    obj2.show();
    obj3.show();
    return 0;
}
