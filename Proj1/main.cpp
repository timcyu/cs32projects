//
//  main.cpp
//  CS32Project1
//
//  Created by Tim Yu on 4/4/18.
//  Copyright © 2018 CS32. All rights reserved.
//

///////////////////////////////////////////////////////////////////////////
//  main()
///////////////////////////////////////////////////////////////////////////

#include "Game.h"

int main()
{
    // Create a game
    // Use this instead to create a mini-game:   Game g(3, 4, 2);
    Game g(7, 8, 25);
    
    // Play the game
    g.play();
}


/*
// TEST CASESSSS
#include "City.h"
int main()
{}
*/

/*
#include "Game.h"

int main()
{
    // Create a game
    // Use this instead to create a mini-game:   Game g(3, 4, 2);
    Game g(7, 8, 15);
    
    // Play the game
    g.play();
}
*/


// TEST CASE 1
/*
#include "Game.h"
#include "Game.h"
#include "City.h"
#include "City.h"
#include "History.h"
#include "History.h"
#include "Player.h"
#include "Player.h"
#include "Flatulan.h"
#include "Flatulan.h"
#include "globals.h"
#include "globals.h"
int main()
{
}
*/

// TEST CASE 2

/*
#include "History.h"
int main()
{
    History h(2, 2);
    h.record(1, 1);
    h.display();
}
*/

// TEST CASE 3

/*
#include "Flatulan.h"
int main()
{
    Flatulan f(nullptr, 1, 1);
}
*/

// TEST CASE 4

/*
#include "Player.h"
int main()
{
    Player p(nullptr, 1, 1);
}
*/

// TEST CASE 5

/*
#include "City.h"
int main()
{
    City c(10, 18);
    c.addPlayer(2, 2);
}
*/

// TEST CASE 6

/*
#include "globals.h"
#include "Player.h"
#include "City.h"
int main()
{
    City c(10, 20);
    Player p(&c, 2, 3);
}
*/

// TEST CASE 7

/*
#include "City.h"
#include "Player.h"
int main()
{
    City c(10, 20);
    Player p(&c, 2, 3);
}
*/

// TEST CASE 8

/*
#include "Player.h"
#include "City.h"
int main()
{
    City c(10, 20);
    Player p(&c, 2, 3);
}
*/

// TEST CASE 9

/*
#include "City.h"
#include "History.h"
#include <iostream>
using namespace std;

int main()
{
    City c(2, 3);
    c.addPlayer(1, 2);
    c.addFlatulan(2, 1);
    c.addFlatulan(2, 1);
    c.addFlatulan(2, 3);
    while (c.flatulanCount() != 0)
        c.preachToFlatulansAroundPlayer();
    c.history().display();
 cout << "===" << endl;
}
*/

// TEST CASE 10

/*
#include "Flatulan.h"
#include "City.h"
int main()
{
    City a(10, 20);
    Player p(&a, 2, 3);
    Flatulan f(&a, 1, 1);
}
*/

// TEST CASE 11

/*
#include "Player.h"
#include "City.h"
int main()
{
    City a(10, 20);
    Player p(&a, 2, 3);
    Flatulan f(&a, 1, 1);
}
*/

// TEST CASE 12

/*
#include "globals.h"
#include "Flatulan.h"
#include "Player.h"
int main()
{
    City a(10, 10);
}
*/

// TEST CASE 13

/*
#include "History.h"
int main()
{
    History h;
}
*/






