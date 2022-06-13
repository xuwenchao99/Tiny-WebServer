#ifndef HTTP_CONN_H
#define HTTP_CONN_H

#include <sys/types.h>
#include <sys/uio.h>     // readv/writev
#include <arpa/inet.h>   // sockaddr_in
#include <stdlib.h>      // atoi()
#include <errno.h>      

#include "../log/log.h"
#include "../pool/sqlconnRAII.h"
#include "../buffer/buffer.h"
#include "httprequest.h"
#include "httpresponse.h"

// Http连接类，其中封装了请求和响应对象
class HttpConn {
public:
    HttpConn();

    ~HttpConn();

    void init(int sockFd, const sockaddr_in& addr);

    ssize_t read(int* saveErrno);

    ssize_t write(int* saveErrno);

    void Close();

    int GetFd() const;

    int GetPort() const;

    const char* GetIP() const;
    
    sockaddr_in GetAddr() const;
    
    bool process();

    int ToWriteBytes() { 
        return iov_[0].iov_len + iov_[1].iov_len; 
    }

    bool IsKeepAlive() const {
        return request_.IsKeepAlive();
    }

    static bool isET;
    static const char* srcDir;  // 资源的目录
    static std::atomic<int> userCount; // 总共的客户单的连接数
    
private:
   
    int fd_;
    struct  sockaddr_in addr_;

    bool isClose_;
    
    int iovCnt_;    // 分散内存的数量
    struct iovec iov_[2];   // 分散内存
    
    Buffer readBuff_;   // 读(请求)缓冲区，保存请求数据的内容
    Buffer writeBuff_;  // 写(响应)缓冲区，保存响应数据的内容

    HttpRequest request_;   // 请求对象
    HttpResponse response_; // 响应对象
};


#endif //HTTP_CONN_H