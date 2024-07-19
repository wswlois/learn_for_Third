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

//json序列化示例1
void test1(){
    //1.首先用json创建一个对象
    json js;
    //把js看成容器，然后键值
    js["msg_type"] = 2;
    js["from"] = "zhang san";
    js["id"] = {1,2,3,4,5};
    js["to"] = "li si";
    js["msg"] = "hello, what are you doing now?";
    //2.相当于重载了输出流<<运算符
    cout << js << endl;
    //会输出
    //{"from":"zhang san",
    //"id":[1,2,3,4,5],"msg":"hello, what are you doing now?",
    //"msg_type":2,"to":"li si"}
    //3.注意！
    //出来的数据并不是有序的，可以理解成底层是链式hash
}
//json序列化示例2
void test2() {
    json js;
    js["msg_type"] = 2;
    js["from"] = "zhang san";
    js["id"] = {1,2,3,4,5};
    js["to"] = "li si";
    //4.dump本身就是输出的意思，相当于把json转成了字符串
    string sendBuf = js.dump();
    //5.感觉和原来没什么区别，但是這样就可以通过网络发送了
    //因为转成了c_str()就是char[]这种了，就可以网络传输
    cout << sendBuf.c_str() <<endl;
}
//json序列化示例3
void test3() {
    json js3;
    js3["id"] = {1,2,3,4,5};
    js3["msg"]["zhang san"] = "hello world";
    js3["msg"]["liu shuo"] = "hello china";
    //6.上面这两句话等同于下面这句一次性添加数组对象
    js3["msg"] = {{"zhangsan","hello world"},{"liu shuo","hello chinese"}};
    cout << js3 << endl;
    //会输出
    //{"id":[1,2,3,4,5],"msg":{"liu shuo":"hello chinese","zhangsan":"hello world"}}
    //可以看到键的值可以是一个新的json
    //注意！只输出了一次msg，可以看出来相当于map，键值对不能重复，值被覆盖成了新的值


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
    test4();
    cout <<"test"<<std::endl;

}




