#pragma once
#include "stdafx.h"
#include "Card.h"

const int LIMIT = 10;

class Player
{
private:
    Card dealt[LIMIT];
    char name[15];
    int point;
public:
    Player();
    void set_name(char[]);
    char* get_name();
    Card& operator[](int n);
    void set_point(int);
    int get_point();
    void ace_point();
    bool isBlackjack();
    bool isBusted();
};