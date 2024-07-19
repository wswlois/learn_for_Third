#include "json.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <string>

using json = nlohmann::json;
using std::cout;
using std::endl;
using std::vector;
using std::map;
using std::string;

//json反序列化示例1
string test5(){
    //1.首先用json创建一个对象
    json js;
    //把js看成容器，然后键值
    js["msg_type"] = 2;
    js["from"] = "zhang san";
    js["id"] = {1,2,3,4,5};
    js["to"] = "li si";
    js["msg"] = "hello, what are you doing now?";
    js["msg"] = {{"zhangsan","hello world"},{"liu shuo","hello chinese"}};
    //2.序列化
    //传输的两种方式
    //方式一(1)
    string sendBuf = js.dump();
    //{"from":"zhang san","id":[1,2,3,4,5],"msg":"hello, what are you doing now?","msg_type":2,"to":"li si"}
    return sendBuf;
    //方式二(2)
    //return js.dump();
}
//json容器序列化示例4（序列化容器）
void test4() {
    json js4;
    vector<int> vec;
    vec.push_back(1);
    vec.emplace_back(2);
    vec.push_back(5);
    js4["list"] = vec;

    map<int,string> m;
    //注意下，map的主要是insert
    //insert的键值对，可以是pair<,>(),可以是make_pair()，也可以是{,}
    m.insert({1,"黄山"});
    m.insert({2,"华山"});
    m.insert({3,"泰山"});
    js4["path"] = m;
    //也可以
    //string sendBuf = js.dump();
    //json数据对象=>序列化 json字符串

    cout << js4 << endl;
    //输出
    //{"list":[1,2,5],"path":[[1,"黄山"],[2,"华山"],[3,"泰山"]]}

}

int main(){
    //3.接收
    string recvBuf = test5();
    //4. 数据的反序列化 json=> 反序列化成数据对象(看做容器，方便访问)
    json jsbuf = json::parse(recvBuf);
    //对于json传送，
    //1.建立json对象
    //2.插入键值对(值可以是各种比如容器).从而进行序列化成json
    //3.使用dump()转换成string
    //4.进行传送（可以使用.c_str()就是char[]进行传送)
    //5.使用string（char[]）进行接收
    //6.建立json对象，使用json::parse将string接收成json
    //7.使用json[]进行键值对输出，从而反序列化
    //3.1接收并输出的方式一
    cout << jsbuf["msg_type"] <<endl;
    cout << jsbuf["from"] <<endl;
    cout << jsbuf["id"] <<endl;
    cout << jsbuf["to"] <<endl;
    cout << jsbuf["msg"] <<endl;
    //3.2接收方式二
    auto arr = jsbuf["id"];
    cout << arr[2] <<endl;
    auto msgjs = jsbuf["msg"];
    auto msgjs_z = jsbuf["msg"]["zhangsan"];
    cout << msgjs["liu shuo"]<<endl;
    cout << msgjs_z << endl;
}

