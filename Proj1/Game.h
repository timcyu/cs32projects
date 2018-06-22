//
//  Game.h
//  CS32Project1
//
//  Created by Tim Yu on 4/5/18.
//  Copyright © 2018 CS32. All rights reserved.
//

#ifndef Game_h
#define Game_h

class City;

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nFlatulans);
    ~Game();
    
    // Mutators
    void play();
    
    int decodeDirection(char dir);

    
private:
    City* m_city;
};

#endif /* Game_h */
