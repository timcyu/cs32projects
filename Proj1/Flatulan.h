//
//  Flatulan.h
//  CS32Project1
//
//  Created by Tim Yu on 4/5/18.
//  Copyright © 2018 CS32. All rights reserved.
//

#ifndef Flatulan_h
#define Flatulan_h

class City;

class Flatulan
{
public:
    // Constructor
    Flatulan(City* cp, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    
    // Mutators
    void move();
    bool possiblyGetConverted();
    
private:
    City* m_city;
    int   m_row;
    int   m_col;
};

#endif /* Flatulan_h */
