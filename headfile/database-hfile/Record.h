
#pragma once

#include <string>

class Record {
    std::string sno;
    int level;
    int index; // 'idx' in the database
    int time_cost_s;
    int score;
    std::string record_time;

public:
    std::string toString();
public:
    const std::string &getSno() const;

    void setSno(const std::string &sno);

    int getLevel() const;

    void setLevel(int level);

    int getIndex() const;

    void setIndex(int index);

    int getTimeCostS() const;

    void setTimeCostS(int timeCostS);

    int getScore() const;

    void setScore(int score);

    const std::string &getRecordTime() const;

    void setRecordTime(const std::string &recordTime);

public:
    Record(const std::string &sno, int level, int index, int timeCostS, int score, const std::string &recordTime);

    Record(const std::string &sno, int level, int timeCostS, int score);
};