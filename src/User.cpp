#include "../headfile/database-hfile/User.h"

std::string User::toString()
{
    return std::string().append("学号：").append(this->sno).append(" 姓名：").append(this->name).append(" 加入时间：").append(this->join_date_time);
}

User::User(const std::string &sno, const std::string &name, const std::string &joinDateTime) : sno(sno), name(name),join_date_time(joinDateTime) {

}

const std::string &User::getSno() const {
    return sno;
}

void User::setSno(const std::string &sno) {
    User::sno = sno;
}

const std::string &User::getName() const {
    return name;
}

void User::setName(const std::string &name) {
    User::name = name;
}

const std::string &User::getJoinDateTime() const {
    return join_date_time;
}

void User::setJoinDateTime(const std::string &joinDateTime) {
    join_date_time = joinDateTime;
}

User::User(const std::string &sno, const std::string &name) : sno(sno), name(name) {}
