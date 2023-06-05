#ifndef USER_H
#define USER_H
#include <string>
struct User
{
    std::string name;
    std::string data_path;
    int score;
    int best_score;
    int sum_score;
};
#endif