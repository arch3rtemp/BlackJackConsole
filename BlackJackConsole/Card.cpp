#pragma once
#include "Card.h"

void Card::set(int n, Suit s)
{
    number = n;
    suit = s;

    if (n >= 11 && n <= 13)
        value = 10;
    else if (n == 14)
        value = 11;
    else
        value = n;
}

int Card::get_value()
{
    return value;
}

void Card::set(int v)
{
    value = v;
}

int Card::get_number()
{
    return number;
}

void Card::display()
{
    if (number >= 2 && number <= 10)
        if (number >= 2 && number <= 9)
            cout << setw(2) << number;
        else
            cout << number;
    else
    {
        switch (number)
        {
        case jack: cout << setw(2) << 'J'; break;
        case queen: cout << setw(2) << 'Q'; break;
        case king: cout << setw(2) << 'K'; break;
        case ace: cout << setw(2) << 'A'; break;
        }
    }
    switch (suit)
    {
    case clubs: cout << "\u2663"; break;
    case diamonds: cout << "\u2666"; break;
    case hearts: cout << "\u2665"; break;
    case spades: cout << "\u2660"; break;
    }
}