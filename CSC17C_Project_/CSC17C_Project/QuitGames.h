/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   QuitGames.h
 * Author: Professor
 *
 * Created on June 1, 2017, 9:10 PM
 */

#ifndef QUITGAMES_H
#define QUITGAMES_H
#include "GmeInfo.h"

class QuitGIn : public GmeInfo {
private:
    int quitGms;
public:
    //Constructor
    QuitGIn() {
        quitGms=0;
    }
    //Member functions
    void setQG(int);
    int getQG();
    void operator ++ (int);
};

#endif /* QUITGAMES_H */

