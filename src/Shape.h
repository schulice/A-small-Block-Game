#ifndef _SHAPE_H_
#define _SHAPE_H_
#include <SDL2/SDL_stdinc.h>
#include <vector>

struct ShapeItem
{
    int style;
    Uint32 color; 
};
class Shape
{
protected:
    //int width;
    //int length;
    std::vector<std::vector<std::vector<bool>>> a;
    Uint32 color;
    int status;
public:
    int edge = 0;
    int x;
    int y;
public:
    Shape(int _x, int _y, int _status, Uint32 _color);
    Uint32 GetColor();
    bool Check(bool play_ground[][200]);//if OK return 1
    bool Move(int delta_x, int delta_y, bool play_ground[][200]);
    bool Change(bool play_ground[][200]);
    bool Stick(bool play_pool[][200], Uint32 color_pool[][200]);
    bool GetBool(int _x, int _y){
        return a[status][_x][_y];
    }
};
class Shape_I : public Shape
{
protected:
public:
    Shape_I(int _x, int _y, int _status, Uint32 _color) : Shape(_x, _y, _status,_color){
        edge = 4;
        a = {{{0, 0, 0, 0},
                {1, 1, 1, 1},
                {0, 0, 0, 0},
                {0, 0, 0, 0}},
            {{0, 0, 1, 0},
                {0, 0, 1, 0},
                {0, 0, 1, 0},
                {0, 0, 1, 0}},
            {{0, 0, 0, 0},
                {0, 0, 0, 0},
                {1, 1, 1, 1},
                {0, 0, 0, 0}},
            {{0, 1, 0, 0},
                {0, 1, 0, 0},
                {0, 1, 0, 0},
                {0, 1, 0, 0}}};
    };
};

class Shape_J : public Shape
{
protected:
public:
    Shape_J(int _x, int _y, int _status, Uint32 _color) : Shape(_x, _y, _status,_color){
        edge = 3;
        a = {{{1, 0, 0},
                {1, 1, 1},
                {0, 0, 0}},
            {{0, 1, 1},
                {0, 1, 0},
                {0, 1, 0}},
            {{0, 0, 0},
                {1, 1, 1},
                {0, 0, 1}},
            {{0, 1, 0},
                {0, 1, 0},
                {1, 1, 0}}};
    };
};

class Shape_L : public Shape
{
protected:
public:
    Shape_L(int _x, int _y, int _status, Uint32 _color) : Shape(_x, _y, _status,_color){
        edge = 3;
        a = {{{0, 0, 1},
                {1, 1, 1},
                {0, 0, 0}},
            {{0, 1, 0},
                {0, 1, 0},
                {0, 1, 1}},
            {{0, 0, 0},
                {1, 1, 1},
                {1, 0, 0}},
            {{1, 1, 0},
                {0, 1, 0},
                {0, 1, 0}}};
    };
};

class Shape_O : public Shape
{
protected:
public:
    Shape_O(int _x, int _y, int _status, Uint32 _color) : Shape(_x, _y, _status,_color){
        edge = 4;
        a = {{{0,1, 1, 0},
                {0,1, 1, 0},
                {0,0, 0, 0},
                {0,0, 0, 0}},
            {{0,1, 1, 0},
                {0,1, 1, 0},
                {0,0, 0, 0},
                {0,0, 0, 0}},
            {{0,1, 1, 0},
                {0,1, 1, 0},
                {0,0, 0, 0},
                {0,0, 0, 0}},
            {{0,1, 1, 0},
                {0,1, 1, 0},
                {0,0, 0, 0},
                {0,0, 0, 0}}};
    };
};

class Shape_S : public Shape
{
protected:
public:
    Shape_S(int _x, int _y, int _status, Uint32 _color) : Shape(_x, _y, _status,_color){
        edge = 3;
        a = {{{0, 1, 1},
                {1, 1, 0},
                {0, 0, 0}},
            {{0, 1, 0},
                {0, 1, 1},
                {0, 0, 1}},
            {{0, 0, 0},
                {0, 1, 1},
                {1, 1, 0}},
            {{1, 0, 0},
                {1, 1, 0},
                {0, 1, 0}}};
    };
};

class Shape_T : public Shape
{
protected:
public:
    Shape_T(int _x, int _y, int _status, Uint32 _color) : Shape(_x, _y, _status,_color){
        edge = 3;
        a = {{{0, 1, 0},
                {1, 1, 1},
                {0, 0, 0}},
            {{0, 1, 0},
                {0, 1, 1},
                {0, 1, 0}},
            {{0, 0, 0},
                {1, 1, 1},
                {0, 1, 0}},
            {{0, 1, 0},
                {1, 1, 0},
                {0, 1, 0}}};
    };
};

class Shape_Z : public Shape
{
protected:
public:
    Shape_Z(int _x, int _y, int _status, Uint32 _color) : Shape(_x, _y, _status,_color){
        edge = 3;
        a = {{{1, 1, 0},
                {0, 1, 1},
                {0, 0, 0}},
            {{0, 0, 1},
                {0, 1, 1},
                {0, 1, 0}},
            {{0, 0, 0},
                {1, 1, 0},
                {0, 1, 1}},
            {{0, 1, 0},
                {1, 1, 0},
                {1, 0, 0}}};
    };
};

#endif // SHAPE_H