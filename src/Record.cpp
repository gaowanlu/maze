#include "../headfile/database-hfile/Record.h"

Record::Record(const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &sno, int level, int index,
               int timeCostS, int score,
               const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &recordTime) : sno(sno),
                                                                                                          level(level),
                                                                                                          index(index),
                                                                                                          time_cost_s(
                                                                                                                  timeCostS),
                                                                                                          score(score),
                                                                                                          record_time(
                                                                                                                  recordTime) {}

const std::string &Record::getSno() const {
    return sno;
}

void Record::setSno(const std::string &sno) {
    Record::sno = sno;
}

int Record::getLevel() const {
    return level;
}

void Record::setLevel(int level) {
    Record::level = level;
}

int Record::getIndex() const {
    return index;
}

void Record::setIndex(int index) {
    Record::index = index;
}

int Record::getTimeCostS() const {
    return time_cost_s;
}

void Record::setTimeCostS(int timeCostS) {
    time_cost_s = timeCostS;
}

int Record::getScore() const {
    return score;
}

void Record::setScore(int score) {
    Record::score = score;
}

const std::string &Record::getRecordTime() const {
    return record_time;
}

void Record::setRecordTime(const std::string &recordTime) {
    record_time = recordTime;
}

std::string Record::toString() {
    return std::string().append("学号：").append(this->sno).append(" 通关等级：").append(std::to_string(this->level)).append(" 记录序号：").append(std::to_string(this->index)).append(" 通关用时：").append(std::to_string(this->time_cost_s)).append(" 得分：").append(std::to_string(this->score)).append(" 记录时间：").append(this->record_time);
}

Record::Record(const std::string &sno, int level, int timeCostS, int score) : sno(sno), level(level),
                                                                              time_cost_s(timeCostS), score(score) {}
