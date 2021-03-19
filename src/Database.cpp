//
// Created by Terry on 2020/12/20.
//

#include "../headfile/database-hfile/Database.h"
#include "../headfile/database-hfile/Log.h"

Database::Database(const std::string& dbFilePath) : db_file_path(dbFilePath) {
    if (sqlite3_open(db_file_path.c_str(), &con) != 0) {
        Log::log("unable to open database");
    }
    else {
        Log::log("open database success");
    }
}

/// not work well for '\0'
void Database::findAndReplaceAll(std::string& data, const std::string& toSearch, const std::string& replaceStr) {
    std::size_t pos = 0 - replaceStr.size();
    while (pos = data.find(toSearch, pos + replaceStr.size()), pos != std::string::npos)
    {
        data.replace(pos, toSearch.size(), replaceStr);
    }
}

void
Database::findAndReplaceAll_reverse(std::string& data, const std::string& replaceStr, const std::string& toSearch) {
    findAndReplaceAll(data, toSearch, replaceStr);
}

/// not escape the '\0'
void Database::escape(std::string& text, bool isLike) {
    findAndReplaceAll(text, "\\", "\\\\");
    findAndReplaceAll(text, "'", "''");
    /// not necessary if use '\'' around string
    findAndReplaceAll(text, "\"", "\\\"");
    findAndReplaceAll(text, "\b", "\\b");
    findAndReplaceAll(text, "\n", "\\n");
    findAndReplaceAll(text, "\r", "\\r");
    findAndReplaceAll(text, "\t", "\\t");
    findAndReplaceAll(text, "\032", "\\Z");
    if (isLike) {
        findAndReplaceAll(text, "%", "\\%");
        findAndReplaceAll(text, "_", "\\_");
    }
}

/// not restore the '\0'
void Database::restore(std::string& text, bool isLike) {
    if (isLike) {
        findAndReplaceAll_reverse(text, "_", "\\_");
        findAndReplaceAll_reverse(text, "%", "\\%");
    }
    findAndReplaceAll_reverse(text, "\032", "\\Z");
    findAndReplaceAll_reverse(text, "\t", "\\t");
    findAndReplaceAll_reverse(text, "\r", "\\r");
    findAndReplaceAll_reverse(text, "\n", "\\n");
    findAndReplaceAll_reverse(text, "\b", "\\b");
    /// not necessary if use '\'' around string
    findAndReplaceAll_reverse(text, "\"", "\\\"");
    findAndReplaceAll_reverse(text, "'", "''");
    findAndReplaceAll_reverse(text, "\\", "\\\\");
}

bool Database::add_user(const User& user) {
    std::string NAME("add_user()");

    std::string sno(user.getSno());
    std::string name(user.getName());

    escape(sno, false);
    escape(name, false);

    std::string count_sql("select * from user where sno='" + sno + "'");

    char* error_msg = nullptr;

    int count_aka_next_index = 0;
    if (sqlite3_exec(con, count_sql.c_str(), (sqlite3_callback)sqlite_fill_rows_num_callback, &count_aka_next_index, &error_msg) != SQLITE_OK) {
        Log::log(NAME, error_msg);
        sqlite3_free(error_msg);
    }

    if (sqlite3_exec(con, ("insert into user (sno, name) values ('" + sno + "', '" + name + "')").c_str(), nullptr,
        nullptr, &error_msg) != SQLITE_OK) {
        Log::log(NAME, error_msg);
        sqlite3_free(error_msg);
    }

    int count_after_insert = 0;
    if (sqlite3_exec(con, count_sql.c_str(), (sqlite3_callback)sqlite_fill_rows_num_callback, &count_after_insert, &error_msg) != SQLITE_OK) {
        Log::log(NAME, error_msg);
        sqlite3_free(error_msg);
    }

    bool res = (count_after_insert > count_aka_next_index);

    restore(sno, false);
    restore(name, false);
    Log::log(NAME, "add user " + sno + " " + name + " " + ((res) ? ("success") : ("fail")));
    return res;
}

std::vector<std::vector<std::string>> Database::select_all_users() {
    std::string NAME("select_all_users()");
    std::string sql("select * from user");
    char* errmsg = nullptr;
    std::vector<std::vector<std::string>> res;
    if (sqlite3_exec(con, sql.c_str(), (sqlite3_callback)sqlite_fill_data_callback, &res, &errmsg) != SQLITE_OK) {
        Log::log(NAME, errmsg);
        sqlite3_free(errmsg);
    }
    return std::move(res);
}

bool Database::delete_user(const std::string& sno) {
    std::string NAME("delete_user()");

    std::string sno_e(sno);
    escape(sno_e, false);

    std::string count_sql = std::string("select * from user where sno='") + sno_e + "'";

    char* errmsg = nullptr;

    std::string sql = count_sql;
    int num_before = 0;
    if (sqlite3_exec(con, sql.c_str(), (sqlite3_callback)sqlite_fill_rows_num_callback, &num_before, &errmsg) != SQLITE_OK) {
        Log::log(NAME, errmsg);
        sqlite3_free(errmsg);
    }

    sql = std::string("delete from user where sno='") + sno_e + "'";
    if (sqlite3_exec(con, sql.c_str(), nullptr, nullptr, &errmsg) != SQLITE_OK) {
        Log::log(NAME, errmsg);
        sqlite3_free(errmsg);
    }

    sql = count_sql;
    int num_after = 0;
    if (sqlite3_exec(con, sql.c_str(), (sqlite3_callback)sqlite_fill_rows_num_callback, &num_after, &errmsg) != SQLITE_OK) {
        Log::log(NAME, errmsg);
        sqlite3_free(errmsg);
    }

    bool res = (num_before > num_after);

    Log::log(NAME, "delete user " + sno + " " + ((res) ? ("success") : ("fail")));
    return res;
}

bool Database::add_record(const Record& record) {
    std::string NAME("add_record()");

    std::string sno(record.getSno());
    std::string level(std::to_string(record.getLevel()));
    std::string time_cost_s(std::to_string(record.getTimeCostS()));
    std::string score(std::to_string(record.getScore()));

    escape(sno, false);
    escape(level, false);
    escape(time_cost_s, false);
    escape(score, false);

    std::string count_sql = std::string("select * from record where sno='") + sno + "' and level=" + level;

    char* error_msg = nullptr;

    int count_aka_next_index = 0;
    if (sqlite3_exec(con, count_sql.c_str(), (sqlite3_callback)sqlite_fill_rows_num_callback, &count_aka_next_index, &error_msg) != SQLITE_OK) {
        Log::log(NAME, error_msg);
        sqlite3_free(error_msg);
    }

    std::string insert_sql = "insert into record (sno, level, idx, time_cost_s, score) values ('" + sno + "', " + level + ", " + std::to_string(count_aka_next_index) + ", " + time_cost_s + ", " + score + ")";

    if (sqlite3_exec(con, insert_sql.c_str(), nullptr, nullptr, &error_msg) != SQLITE_OK) {
        Log::log(NAME, error_msg);
        sqlite3_free(error_msg);
    }

    int count_after_insert = 0;
    if (sqlite3_exec(con, count_sql.c_str(), (sqlite3_callback)sqlite_fill_rows_num_callback, &count_after_insert, &error_msg) != SQLITE_OK) {
        Log::log(NAME, error_msg);
        sqlite3_free(error_msg);
    }

    bool res = (count_after_insert > count_aka_next_index);

    restore(sno, false);
    restore(level, false);
    restore(time_cost_s, false);
    restore(score, false);
    Log::log(NAME, "add record { sno: " + sno + ", level: " + level + ", time_cost_s: " + time_cost_s + ", score: " + score + " } " + ((res) ? ("success") : ("fail")));
    return res;
}

std::vector<std::vector<std::string>> Database::select_all_records() {
    std::string NAME("select_all_records()");
    std::string sql("select * from record");
    char* errmsg = nullptr;
    std::vector<std::vector<std::string>> res;
    if (sqlite3_exec(con, sql.c_str(), (sqlite3_callback)sqlite_fill_data_callback, &res, &errmsg) != SQLITE_OK) {
        Log::log(NAME, errmsg);
        sqlite3_free(errmsg);
    }
    return std::move(res);
}

bool Database::delete_record(const std::string& sno, const int& level, const int& index) {
    std::string NAME("delete_record()");

    std::string sno_e(sno);
    std::string level_e(std::to_string(level));
    std::string index_e(std::to_string(index));
    escape(sno_e, false);
    escape(level_e, false);
    escape(index_e, false);

    std::string count_sql = std::string("select * from record where sno='") + sno_e + "' and level=" + level_e + " and idx=" + index_e;

    char* errmsg = nullptr;

    std::string sql = count_sql;
    int num_before = 0;
    if (sqlite3_exec(con, sql.c_str(), (sqlite3_callback)sqlite_fill_rows_num_callback, &num_before, &errmsg) != SQLITE_OK) {
        Log::log(NAME, errmsg);
        sqlite3_free(errmsg);
    }

    sql = std::string("delete from record where sno='") + sno_e + "' and level=" + level_e + " and idx=" + index_e;
    if (sqlite3_exec(con, sql.c_str(), nullptr, nullptr, &errmsg) != SQLITE_OK) {
        Log::log(NAME, errmsg);
        sqlite3_free(errmsg);
    }

    sql = count_sql;
    int num_after = 0;
    if (sqlite3_exec(con, sql.c_str(), (sqlite3_callback)sqlite_fill_rows_num_callback, &num_after, &errmsg) != SQLITE_OK) {
        Log::log(NAME, errmsg);
        sqlite3_free(errmsg);
    }

    bool res = (num_before > num_after);

    Log::log(NAME, "delete record { sno: " + sno + ", level: " + std::to_string(level) + ", index: " + std::to_string(index) + " } " + ((res) ? ("success") : ("fail")));

    // Error prone.

    if (res) {
        std::string count_level_sql = "select * from record where sno='" + sno_e + "' and level=" + level_e;
        int level_row_num = 0;
        if (sqlite3_exec(con, count_level_sql.c_str(), (sqlite3_callback)sqlite_fill_rows_num_callback, &level_row_num, &errmsg) != SQLITE_OK) {
            Log::log(NAME, errmsg);
            sqlite3_free(errmsg);
        }
        for (int i = index + 1; i <= level_row_num; ++i) {
            std::string update_idx_sql = std::string()
                .append("update record set idx=idx-1 where idx=").append(std::to_string(i))
                .append(" and sno ='").append(sno_e).append("'")
                .append(" and level=").append(level_e);
            if (sqlite3_exec(con, update_idx_sql.c_str(), nullptr, nullptr, &errmsg) != SQLITE_OK) {
                Log::log(NAME, errmsg);
                sqlite3_free(errmsg);
            }
        }
    }

    return res;
}

int Database::sqlite_fill_data_callback(std::vector<std::vector<std::string>>* data_to_fill, int fields_num, char** field_values,
    char** field_names) {
    auto& res = *data_to_fill;
    std::vector<std::string> a_row;
    a_row.reserve(fields_num);
    for (int column_index = 0; column_index < fields_num; ++column_index) {
        a_row.emplace_back(field_values[column_index]);
    }
    res.emplace_back(std::move(a_row));
    return 0;
}

int Database::sqlite_fill_rows_num_callback(int* row_num_to_fill, int fields_num, char** field_values, char** field_names) {
    (*row_num_to_fill)++;
    return 0;
}

Database::~Database() {
    sqlite3_close(con);
}

