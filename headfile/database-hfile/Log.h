//
// Created by Terry on 2020/12/20.
//

#ifndef MAZEDATABASE_LOG_H
#define MAZEDATABASE_LOG_H

#include <string>

class Log {
public:
    static void log(const std::string &msg);
    static void log(const std::string &name, const std::string &msg);

private:
    static std::string getTime();
};


#endif //MAZEDATABASE_LOG_H
