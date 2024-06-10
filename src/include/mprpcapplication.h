#pragma once

#include "mprpcconfig.h"
#include "mprpcchannel.h"
#include "mprpccontroller.h"

// mprpc框架的基础类，负责框架的一些初始化操作
class MprpcApplication
{
public:
    static void Init(int argc, char** argv);
    static MprpcApplication& GetInstance();
    static MprpcConfig& GetConfig();
private:
    static MprpcConfig m_config;

    MprpcApplication(){} // 私有构造函数，防止外部创建实例
    MprpcApplication(const MprpcApplication&) = delete; // 禁用拷贝构造函数
    MprpcApplication(MprpcApplication&&) = delete; // 禁止移动构造函数
    MprpcApplication& operator=(const MprpcApplication&) = delete; // 禁用拷贝赋值运算符
};