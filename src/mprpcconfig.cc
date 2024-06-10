#include "mprpcconfig.h"

#include <iostream>
#include <string>
// 负责解析加载配置文件
void MprpcConfig::LoadConfigFile(const char* config_file)
{
    FILE* pf = fopen(config_file, "r");
    if (nullptr == pf)
    {
        std::cout<< config_file << " is not exist!" << std::endl;
        exit(EXIT_FAILURE);
    }
    // 1.注释 2.正确的配置项（键值对） 3.去掉开头多余的空格
    while (!feof(pf))
    {
        char buf[512] = {0};
        fgets(buf, 512, pf);

        // 去掉字符串前后多余的空格
        std::string src_buf(buf);
        Trim(src_buf);

        // 判断#的注释
        if (src_buf[0] == '#' || src_buf.empty())
        {
            continue;
        }

        // 解析配置项
        int idx = src_buf.find('=');
        if (idx == -1)
        {
            // 配置项不合法
            continue;
        }
        std::string key;
        std::string value;
        key = src_buf.substr(0, idx);
        Trim(key);
        // 127.0.0.1\n
        int endidx = src_buf.find('\n', idx); // idx表示查找的起始位置
        value = src_buf.substr(idx+1, endidx-idx-1);
        Trim(value);
        m_configMap.insert({key, value});
    }
}

// 查询配置项信息
std::string MprpcConfig::Load(const std::string& key)
{
    if (m_configMap.find(key) != m_configMap.end())
    {
        return m_configMap[key];
    }
    return "";

}

// 去掉字符串前后的空格
void MprpcConfig::Trim(std::string& src_buf)
{
    int idx = src_buf.find_first_not_of(' ');
    if (idx != -1)
    {
        // 说明字符串前面有空格
        src_buf = src_buf.substr(idx, src_buf.size()-idx);
    }
    // 去掉字符串后面多余的空格
    idx = src_buf.find_last_not_of(' ');
    if (idx != -1)
    {
        // 说明字符串后面有空格
        src_buf = src_buf.substr(0, idx+1);
    }
}