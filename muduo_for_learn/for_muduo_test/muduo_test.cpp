/*
   muduo网络库给用户提供了两个主要的类
   TcpServer：用于编写服务器程序的
   TcpClient：用于编写客户端程序的

   epoll + 线程池
    好处：能够把网络I/O的代码和业务代码区分开
                        用户的连接和断开    用户的可读写事件
   */
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <iostream>
#include <functional>
using namespace std;
// typedef muduo::net net;
using namespace muduo;
using namespace muduo::net;
using namespace placeholders;
// using net = muduo::net;
/*基于muduo网络库开发服务器程序
1.组合TcpServer对象
2.创建EventLoop事件循环对象的指针
3.明确TcpServer构造函数需要什么函数
4.在当前服务器类的构造函数当中，注册处理连接的回调函数和处理读写事件
5.设置合适的服务端线程数量,muduo库会自己分配I/O线程和worker线程
*/
class ChatServer
{
public:
    // 开始初始化列表，追进去TcpServer（ctrl+鼠标左键)的可以知道初始化需要四个参数
    ChatServer(EventLoop *loop,               // 事件循环
               const InetAddress &listenAddr, // IP+port
               const string &nameArg)         // 服务器的名字
        // Option option = kReusePort)//这里要怎么写呢？？？？
        : _server(loop, listenAddr, nameArg), _loop(loop)
    {
        /* 注意只是注册……
           话说在构造函数注册应该还是刚好的，既没有把逻辑放在这里，又进行了注册
           话说为什么要注册来着
           对了是要进行监听*/
        // 给服务器注册用户连接的创建和断开回调
        // 追进去可以发现，这个函数是一个没有返回值，参数只有一个形参变量
        _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, _1));

        // 给服务器注册用户读写事件回调
        _server.setMessageCallback(std::bind(&ChatServer::onMessage,this,_1,_2,_3));
        
        //设置服务器端的线程数量
        //一个做I/O线程，一个做工作线程
        //一般4核可以设置4个线程，一个I/O线程 三个worker线程
        _server.setThreadNum(4);

    }

    //开启时间循环
    void start() {
        _server.start();
    }

private:
    /* 底层都封装了，这里只是注册，回调不在这里
     我们从TcpServer那里把他改成了成员方法，这是为了访问这里的成员变量
     但是成员方法多了一个this指针，所以为了和TcpServer中的一致
     我们决定加入一个绑定器把它进行绑定<funtional> */
     // 专门处理用户的连接创建和断开 epoll listenfd accept
    void onConnection(const TcpConnectionPtr &conn)
    {
        if(conn->connected()) {
            cout << conn->peerAddress().toIpPort() << " -> "
            << conn->localAddress().toIpPort() 
            << " state:online" << endl;
        }
        else {
            cout << conn->peerAddress().toIpPort() << " -> "
            << conn->localAddress().toIpPort() 
            << " state:offline" << endl;
            conn->shutdown(); //close(fd)
            //_loop->quit();//服务器结束，退出epoll
        }

    }
    //专门处理用户的读写事件
    void onMessage(const TcpConnectionPtr &conn,//连接
                   Buffer *buf,//缓冲区（网络库一般都会加个缓冲区增加文件性能）
                   Timestamp time)//接受到数据的时间信息
    {
        string buffer = buf->retrieveAllAsString();
        cout << "recv data:" << buffer << " time:" << time.toString() << endl;
        conn->send(buf);
    }
    TcpServer _server; // #1 //保存传进来的时间循环对象
    EventLoop *_loop;  // #2 epoll
};

int main()
{
    EventLoop loop;//epoll
    InetAddress addr("192.168.31.136", 6000);
    ChatServer server(&loop,addr,"wsw_ChatServer");
    server.start(); //listenfd epoll_ctl=>epoll
    loop.loop();// epoll_wait以阻塞方式等待新用户连接，已连接用户的读写事件等操作
    
    return 0;
}