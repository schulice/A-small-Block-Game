#ifndef SHAPE_H
#define SHAPE_H

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
    bool Check(std::vector<std::vector<bool> > &play_ground);//if OK return 1
    bool Move(int delta_x, int delta_y, std::vector<std::vector<bool> > &play_ground);
    bool Change(std::vector<std::vector<bool> > &play_ground);
    bool Stick(std::vector<std::vector<bool> > &play_pool, std::vector<std::vector<Uint32> > &color_pool);
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

#endif