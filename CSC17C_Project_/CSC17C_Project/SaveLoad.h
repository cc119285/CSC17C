/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SaveLoad.h
 * Author: Professor
 *
 * Created on May 29, 2017, 10:28 AM
 */

#ifndef SAVELOAD_H
#define SAVELOAD_H
#include <fstream>
#include "Mode.h"
using namespace std;

class Save {
public:
    void savegm(fstream &, fstream &, int, int, int, int, int);
    Load loadgm(fstream &, fstream &);
    char intochr(int);
    Scores intochr(int, Scores);
    
    //Overloaded = operator
    Scores operator = (const Scores&s) {
        Scores scorert;
        scorert.ones=s.ones;
        scorert.tens=s.tens;
        scorert.hndrds=s.hndrds;
        scorert.thsnds=s.thsnds;
        return scorert;
    }
    
};

#endif /* SAVELOAD_H */

