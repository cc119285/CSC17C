/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Mode.h
 * Author: Professor
 *
 * Created on April 13, 2017, 10:13 AM
 */

#ifndef MODE_H
#define MODE_H

struct Mode {
    int row; //Size of rows
    int col; //Size of columns
};

struct UsrInfo {
    char name[81]; //Array to store name
    int totScor; //Stores total score
};

struct Scores {
    char ones;
    char tens;
    char hndrds;
    char thsnds;
};

struct Load {
    int mode;
    int rowpos;
    int colpos;
    int scoreth;
    int scorehn;
    int scorete;
    int scoreon;
};

#endif /* MODE_H */

