#ifndef SHAPE_CPP
#define SHAPE_CPP
#include "Shape.h"
#include "constant.cpp"
Shape::Shape(int _x, int _y, int _status, Uint32 _color){
    x = _x;
    y = _y;
    status = _status;
    color = _color;
}
Uint32 Shape::GetColor(){
    return color;
}
bool Shape::Check(bool play_ground[][200]){
    bool is_empty = 1;
    for (int i = 0; i < edge; i++){
        for (int j = 0; j < edge; j++)
            if (a[status][i][j] && play_ground[x+i][y+j]) {is_empty = 0; break;}
    }
    return is_empty;
}
bool Shape::Move(int _x, int _y, bool play_ground[][200]){
    bool sucess = 1;
    x += _x;
    y += _y;
    if (!Check(play_ground)){
        x -= _x;
        y -= _y;
        sucess = 0;
    }
    return sucess;
}
bool Shape::Change(bool play_ground[][200]){
    bool sucess = 1;
    int status_before = status;
    status++;
    if (status == 4) status = 0;
    if (!Check(play_ground)) status = status_before, sucess = 0;
    return sucess;
}
bool Shape::Stick(bool play_pool[][200], Uint32 color_pool[][200]){
    bool sucess = 1;
    for (int i = 0; i < edge; i++)
        for (int j = 0; j < edge; j++)
            if (a[status][i][j]){
                play_pool[x+i][y+j] = 1;
                color_pool[x+i][y+j] = color;
            }
    return sucess;
}
#endif