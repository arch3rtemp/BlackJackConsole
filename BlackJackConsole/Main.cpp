#include "stdafx.h"
#include "Card.h"
#include "Player.h"

enum Move { Hit = 1, Stand, Surrender, Double, Split };
int counter_pl = NULL, counter_cpu = NULL, counter_deck;
int value = NULL;

void line();
void deck_make(Card[]);
void deck_show(Card[]);
void deck_shuffle(Card[]);
Player player_make();
Player cpu_make();
void game(Player&, Player&, Card[]);
void blackjack_check(Player&, Player&);
void blackjack_check(Player&, Player&, int);
void full_display(Player&, Player&);
void select_first(Player&, Player&, Card[]);
void select_split(Player&, Player&, Card[]);
void select(Player&, Player&, Card[]);
void hit(Player&, Player&, Card[]);
void dealer_play(Player&, Player&, Card[]);
inline void surrender();
void double_play(Player&, Player&, Card[]);
void ace_check(Player&, int);
void bust_check(Player&);
void win_check(Player&, Player&);


int main()
{
    srand(time(NULL));
    system("cls");
    Card deck[52];
    deck_make(deck);
    /*cout << "Source deck:\n";
    deck_show(deck);*/
    deck_shuffle(deck);
    /*cout << "Shuffled deck:\n";
    deck_show(deck);*/
    Player pl_1;
    pl_1 = player_make();
    Player cpu;
    cpu = cpu_make();
    game(pl_1, cpu, deck);

    return 0;
}

void line()
{
    cout << "-----------------------------------------" << endl;
}

void deck_make(Card deck[])
{
    int num;
    Suit su;
    for (int i = 0; i < 52; i++)
    {
        num = (i % 13) + 2;
        su = Suit(i / 13);
        deck[i].set(num, su);
    }
}

void deck_show(Card deck[])
{
    for (int i = 0; i < 52; i++)
    {
        deck[i].display();
        cout << "  ";
        if (!((i + 1) % 13))
            cout << endl;
    }
}

void deck_shuffle(Card deck[])
{
    int shuffle;
    Card temp;
    for (int i = 0; i < 52; i++)
    {
        shuffle = rand() % 52;
        temp = deck[i];
        deck[i] = deck[shuffle];
        deck[shuffle] = temp;
    }
}

Player player_make()
{
    Player pl;
    char name[13];
    cout << "Enter player's name: ";
    cin.getline(name, 13);
    pl.set_name(name);
    cout << "Hello, " << name << ". Let's play Blackjack!\n" << endl;
    cout << "Press return to continue..." << endl;
    cin.get();
    return pl;
}

Player cpu_make()
{
    Player cpu;
    char name[13] = "Dealer";
    cpu.set_name(name);
    return cpu;
}

void game(Player& pl, Player& cpu, Card deck[])
{

    //dealing players initial hand
    system("cls");
    cout << pl.get_name() << ": \n" << endl;
    for (counter_deck = 0; counter_deck < 2; counter_deck++)
    {
        pl[counter_pl] = deck[counter_deck];
        value = deck[counter_deck].get_value();
        pl.set_point(value);
        pl[counter_pl++].display();
        cout << "  ";
    }
    cout << '\n' << endl;
    cout << pl.get_name() << "'s hand: " << pl.get_point() << " points\n" << endl;
    line();
    //dealing dealers initial hand
    cout << cpu.get_name() << ": \n" << endl;
    cpu[counter_cpu] = deck[counter_deck];
    value = deck[counter_deck++].get_value();
    cpu.set_point(value);
    cpu[counter_cpu++].display();
    cout << "  ";
    cpu[counter_cpu] = deck[counter_deck];
    value = deck[counter_deck++].get_value();
    cpu.set_point(value);
    cout << " \u25A0\n" << endl;
    line();
    //checking for blackjack    
    blackjack_check(pl, cpu);
    //considering split as an option
    if (pl[0].get_value() == pl[1].get_value())
        select_split(pl, cpu, deck);
    else
        select_first(pl, cpu, deck);
}

void blackjack_check(Player& pl, Player& cpu)
{
    if (pl.isBlackjack())
    {
        full_display(pl, cpu);
        if (pl.get_point() > cpu.get_point())
        {
            cout << "Blackjack!!! " << pl.get_name() << " Won!!!\n" << endl;
            exit(1);
        }
        else
        {
            cout << "Push!\n" << endl;
            exit(1);
        }
    }
}

void blackjack_check(Player& pl, Player& cpu, int t)
{
    if (cpu.isBlackjack())
    {
        full_display(pl, cpu);
        if (cpu.get_point() > pl.get_point())
        {
            cout << "Blackjack!!! " << cpu.get_name() << " Won!!!\n" << endl;
            exit(1);
        }
        else
        {
            cout << "Push!\n" << endl;
            exit(1);
        }
    }
}

void full_display(Player& pl, Player& cpu)
{
    system("cls");
    cout << pl.get_name() << ": \n" << endl;
    for (int i = 0; i < counter_pl; i++)
    {
        pl[i].display();
        cout << "  ";
    }
    cout << '\n' << endl;
    cout << pl.get_name() << "'s hand: " << pl.get_point() << " points\n" << endl;
    line();
    cout << cpu.get_name() << ": \n" << endl;
    for (int i = 0; i < counter_cpu + 1; i++)
    {
        cpu[i].display();
        cout << "  ";
    }
    cout << '\n' << endl;
    cout << cpu.get_name() << "'s hand: " << cpu.get_point() << " points\n" << endl;
    line();
}

void select_first(Player& pl, Player& cpu, Card deck[])
{
    int action;
    cout << "\nchoose: Hit[1], Stand[2], Surrender[3], Double[4]: ";
    cin >> action;
    switch (action)
    {
    case Hit:
        hit(pl, cpu, deck);
        break;
    case Stand:
        dealer_play(pl, cpu, deck);
        break;
    case Surrender:
        surrender();
        break;
    case Double:
        double_play(pl, cpu, deck);
        break;
    }
}

void select_split(Player& pl, Player& cpu, Card deck[])
{
    int action;
    cout << "\nchoose: Hit[1], Stand[2], Surrender[3], Double[4], Split[5]: ";
    cin >> action;
    switch (action)
    {
    case Hit:
        hit(pl, cpu, deck);
        break;
    case Stand:
        dealer_play(pl, cpu, deck);
        break;
    case Surrender:
        surrender();
        break;
    case Double:
        double_play(pl, cpu, deck);
        break;
    case Split:
        break;
    }
}

void select(Player& pl, Player& cpu, Card deck[])
{
    int action;

    while (true)
    {
        cout << "\nchoose: Hit[1], Stand[2], Surrender[3]: ";
        cin >> action;
        switch (action)
        {
        case Hit:
            hit(pl, cpu, deck);
            break;
        case Stand:
            dealer_play(pl, cpu, deck);
            break;
        case Surrender:
            surrender();
            break;
        }
    }
}

void hit(Player& pl, Player& cpu, Card deck[])
{
    system("cls");
    cout << pl.get_name() << ": \n" << endl;
    pl[counter_pl++] = deck[counter_deck];
    value = deck[counter_deck++].get_value();
    pl.set_point(value);
    for (int i = 0; i < counter_pl; i++)
    {
        pl[i].display();
        cout << "  ";
    }
    cout << '\n' << endl;
    ace_check(pl, counter_pl);
    cout << pl.get_name() << "'s hand: " << pl.get_point() << " points\n" << endl;
    line();
    cout << cpu.get_name() << ": \n" << endl;
    cpu[counter_cpu - 1].display();
    cout << "   \u25A0\n" << endl;
    line();
    bust_check(pl);
    select(pl, cpu, deck);
}

void dealer_play(Player& pl, Player& cpu, Card deck[])
{
    system("cls");
    cout << pl.get_name() << ": \n" << endl;
    for (int i = 0; i < counter_pl; i++)
    {
        pl[i].display();
        cout << "  ";
    }
    cout << '\n' << endl;
    cout << pl.get_name() << "'s hand: " << pl.get_point() << " points\n" << endl;
    line();
    cout << cpu.get_name() << ": \n" << endl;
    blackjack_check(pl, cpu, 1); //test1
    counter_cpu++;
    if (pl.get_point() <= 15)
    {
        while (pl.get_point() >= cpu.get_point())
        {
            cpu[counter_cpu++] = deck[counter_deck];
            value = deck[counter_deck++].get_value();
            cpu.set_point(value);
            ace_check(cpu, counter_cpu);
        }
    }
    else if (pl.get_point() > 15)
    {
        while (pl.get_point() > cpu.get_point())
        {
            cpu[counter_cpu++] = deck[counter_deck];
            value = deck[counter_deck++].get_value();
            cpu.set_point(value);
            ace_check(cpu, counter_cpu);
        }
    }
    for (int i = 0; i < counter_cpu; i++)
    {
        cpu[i].display();
        cout << "  ";
    }
    cout << '\n' << endl;

    cout << cpu.get_name() << "'s hand: " << cpu.get_point() << " points\n" << endl;
    line();
    bust_check(cpu);
    win_check(pl, cpu);
}

inline void surrender()
{
    cout << "\nYou surrendered!\n" << endl;
    exit(1);
}

void double_play(Player& pl, Player& cpu, Card deck[])
{
    system("cls");
    cout << pl.get_name() << ": \n" << endl;
    pl[counter_pl++] = deck[counter_deck];
    value = deck[counter_deck++].get_value();
    pl.set_point(value);
    for (int i = 0; i < counter_pl; i++)
    {
        pl[i].display();
        cout << "  ";
    }
    cout << '\n' << endl;
    cout << pl.get_name() << "'s hand: " << pl.get_point() << " points\n" << endl;
    line();
    cout << cpu.get_name() << ": \n" << endl;
    cpu[counter_cpu - 1].display();
    cout << "   \u25A0\n" << endl;
    bust_check(pl);
    dealer_play(pl, cpu, deck);
}

void ace_check(Player& x, int counter)
{
    if (x.isBusted())
    {
        for (int i = 0; i < counter; i++)
        {
            if (x[i].get_value() == 11)
            {
                x[i].set(1);
                x.ace_point();
            }
        }
    }
}

void bust_check(Player& x)
{
    if (x.isBusted())
    {
        cout << "Busted!!! " << x.get_name() << " Lost!!!\n" << endl;
        exit(1);
    }
}

void win_check(Player& pl, Player& cpu)
{
    if (cpu.get_point() > pl.get_point())
    {
        cout << cpu.get_name() << " Won!!!\n" << endl;
        exit(1);
    }
    else
    {
        cout << "Push!\n" << endl;
        exit(1);
    }
}