#pragma once
#ifndef DATABASEUNTIL_H
#define DATABASEUNTIL_H
#include<iostream>
    struct UserData {
        std::string* id ;
        std::string* password;
        struct UserData* next;
    };
    struct RecordData {
        std::string* id ;
        std::string *level ;
        std::string* frequency;
        std::string* score ;
        std::string* cost;
        struct RecordData* next;
    };
#endif