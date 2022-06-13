#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#include <unordered_map>
#include <fcntl.h>       // open
#include <unistd.h>      // close
#include <sys/stat.h>    // stat
#include <sys/mman.h>    // mmap, munmap

#include "../buffer/buffer.h"
#include "../log/log.h"

class HttpResponse {
public:
    HttpResponse();
    ~HttpResponse();

    void Init(const std::string& srcDir, std::string& path, bool isKeepAlive = false, int code = -1);
    void MakeResponse(Buffer& buff);
    void UnmapFile();
    char* File();
    size_t FileLen() const;
    void ErrorContent(Buffer& buff, std::string message);
    int Code() const { return code_; }

private:
    void AddStateLine_(Buffer &buff);
    void AddHeader_(Buffer &buff);
    void AddContent_(Buffer &buff);

    void ErrorHtml_();
    std::string GetFileType_();

    int code_;  // 响应状态码
    bool isKeepAlive_;  // 是否保持连接

    std::string path_;  // 资源的路径
    std::string srcDir_;    // 资源的目录
    
    char* mmFile_;  // 文件内存映射的指针
    struct stat mmFileStat_;    // 文件的状态信息

    static const std::unordered_map<std::string, std::string> SUFFIX_TYPE;  // 后缀 - 类型
    static const std::unordered_map<int, std::string> CODE_STATUS;    // 状态码 - 描述 
    static const std::unordered_map<int, std::string> CODE_PATH;      // 状态码 - 路径
};


#endif //HTTP_RESPONSE_H