#pragma once
#include "Player.h"

Player::Player() : point(NULL)
{}

void Player::set_name(char s[])
{
    int length = strlen(s);
    if (length > 12)
        cout << "Name too long:" << endl;
    else
        strcpy(name, s);
}

char* Player::get_name()
{
    return name;
}

Card& Player::operator[](int n)
{
    if (n < 0 || n >= LIMIT)
    {
        cout << "\nErroneous index!"; exit(1);
    }
    return dealt[n];
}

void Player::set_point(int p)
{
    point += p;
}

void Player::ace_point()
{
    point -= 10;
}

int Player::get_point()
{
    return point;
}

bool Player::isBlackjack()
{
    return point == 21;
}

bool Player::isBusted()
{
    return point > 21;
}