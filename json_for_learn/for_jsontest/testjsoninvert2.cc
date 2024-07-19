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
using std::pair;

//json容器反序列化示例4（序列化容器）
string test6() {
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

    return js4.dump();
    //json数据对象=>序列化 json字符串


}

int main(){
    //3.接收
    string recvBuf = test6();
    //4. 数据的反序列化 json=> 反序列化成数据对象(看做容器，方便访问)
    json jsbuf = json::parse(recvBuf);
    //5.反序列化
    vector<int> vec = jsbuf["list"];
    for(int &v:vec) {
        cout << v << " ";
    }
    cout << endl;
    map<int,string> path_js = jsbuf["path"];
    //**注意:**这种写法不行，只能接收到第一部分
    //auto path_js = jsbuf["path"];
    //for(auto &p:path_js) {
    //for(const pair<int,string> p:path_js) {
    //for(const pair<const int,const string&> &p:path_js) {
    for(const auto &p:path_js) {
    //for(pair<const int,string>& p:path_js) {
        //cout << p.first << " " << p.second << endl;
        p.second = "hello";
        cout << p.second<< endl;
    }
    for(std::pair<int,string> x:path_js) {
        cout <<"--";
    cout <<x.second<<endl;    
    }
    return 0;
}

