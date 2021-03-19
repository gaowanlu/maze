//
// Created by Terry on 2020/12/20.
//

#include "../headfile/database-hfile/Log.h"

#include <windows.h>
#include <iostream>

void Log::log(const std::string &msg) {
    std::string s;
    s.append(getTime()).append(" : ").append(msg);
    std::cout << s << std::endl;
}

std::string Log::getTime() {
    SYSTEMTIME st, lt;

    GetSystemTime(&st);
    GetLocalTime(&lt);

    char res[100] = {0};

    sprintf_s(res, "%04d/%02d/%02d %02d:%02d:%02d", lt.wYear, lt.wMonth, lt.wDay, lt.wHour, lt.wMinute, lt.wSecond);

    return std::string(res);
}

void Log::log(const std::string &name, const std::string &msg) {
    log(name + ": " + msg);
}
