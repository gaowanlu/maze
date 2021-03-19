
#pragma once

#include <string>

class User {
    std::string sno;
    std::string name;
    std::string join_date_time;
public:
    const std::string &getSno() const;

    void setSno(const std::string &sno);

    const std::string &getName() const;

    void setName(const std::string &name);

    const std::string &getJoinDateTime() const;

    void setJoinDateTime(const std::string &joinDateTime);

public:
    User(const std::string &sno, const std::string &name, const std::string &joinDateTime);

    User(const std::string &sno, const std::string &name);

public:
    std::string toString();
};