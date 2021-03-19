#pragma once
#ifndef DATABASEMODE_H
#define DATABASEMODE_H
#include<iostream>
#include"database-hfile/Database.h"
#include"DataBaseMode.h"
#include"DataBaseUnitil.h"
class DataBaseMode {
    Database* db;
private:
    struct UserData* beauty(const std::vector<std::vector<std::string>>& vector);
    void PrintUserList(struct UserData* headNode);
    void PrintRecordList(const std::vector<std::vector<std::string>>& vector);
public:
    DataBaseMode();
    ~DataBaseMode();
    void AddUser(std::string& id, std::string& password);
    void DelUser(std::string& id);
    void PrintAllUser(void);
    void AddRecord(std::string& id, int level, int timeCost, int score);
    void DelRecord(std::string& id, int level, size_t index);
    void PrintAllRecord();
};
#endif