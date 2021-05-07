#pragma once
#include "stdafx.h"

enum Suit { clubs, diamonds, hearts, spades };
const int jack = 11;
const int queen = 12;
const int king = 13;
const int ace = 14;

class Card
{
private:
    int number;
    Suit suit;
    int value;

public:
    void set(int, Suit);
    void set(int);
    int get_value();
    int get_number();
    void display();
};