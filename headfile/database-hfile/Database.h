//
// Created by Terry on 2020/12/20.
//

#ifndef MAZEDATABASE_DATABASE_H
#define MAZEDATABASE_DATABASE_H

#include <sqlite3.h>
#include <string>
#include <vector>

#include "User.h"
#include "Record.h"

class Database {
    sqlite3* con = nullptr;
    std::string db_file_path;
public:
    constexpr static const char* const utf8 = "utf8";
    constexpr static const char* const gbk = "gbk";

    Database(const std::string& dbFilePath);

    virtual ~Database();

    bool add_user(const User& user);
    bool add_record(const Record& record);
    std::vector<std::vector<std::string>> select_all_users();
    std::vector<std::vector<std::string>> select_all_records();
    bool delete_user(const std::string& sno);
    bool delete_record(const std::string& sno, const int& level, const int& index);

private:
    static void findAndReplaceAll(std::string& data, const std::string& toSearch, const std::string& replaceStr);
    static void findAndReplaceAll_reverse(std::string& data, const std::string& replaceStr, const std::string& toSearch);
    static void escape(std::string& text, bool isLike);
    static void restore(std::string& text, bool isLike);
    static int sqlite_fill_data_callback(std::vector<std::vector<std::string>>* data_to_fill, int fields_num, char** field_values, char** field_names);
    static int sqlite_fill_rows_num_callback(int* row_num_to_fill, int fields_num, char** field_values, char** field_names);
};


#endif //MAZEDATABASE_DATABASE_H
