/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "SaveLoad.h"
#include "Mode.h"
#include <fstream>
#include <iostream>
using namespace std;

char Save::intochr(int pos) {
    char a;
    //Coverts an int to a char
    if (pos==0) {
        a='0';
    } else if (pos==1) {
        a='1';
    } else if (pos==2) {
        a='2';
    } else if (pos==3) {
        a='3';
    } else if (pos==4) {
        a='4';
    } else if (pos==5) {
        a='5';
    } else if (pos==6) {
        a='6';
    } else if (pos==7) {
        a='7';
    } else if (pos==8) {
        a='8';
    } else {
        a='9';
    }
    return a;
}

//Overloaded intochr, for the score
Scores Save::intochr(int score, Scores test) {
    Scores scrs;
    
    //Separate score
    scrs.thsnds=score%1000;
    score-=(scrs.thsnds*1000);
    scrs.hndrds=score%100;
    score-=(scrs.hndrds*100);
    scrs.tens=score%10;
    scrs.ones=score-(scrs.tens*10);
    
    //return scrs
    return scrs;
}

void Save::savegm(fstream &pzzlFil, fstream &savload, int r, int c, int cpr, int cpc, int score) {
    char ch; //Stores a character from the file
    char row;
    char col;
    Scores test;
    Scores stored;
    int scrleng=4;
    
    //Store Mode
    if (r==3 && c==5) {
        savload.put('e');
    } else if (r==5 && c==5) {
        savload.put('m');
    } else {
        savload.put('h');
    }
    //Store puzzle
    for (int i=0; i<r; i++) {
		for (int j=0; j<c; j++) {
			if (i==r-1 && j==c-1) {
                            savload.put('f');
                        } else {
                            pzzlFil.get(ch);
                            savload.put(ch);
			}
		}
	}
    savload.put('&');
    //Set position of 'c'
    row=intochr(cpr); //Change row position to a char
    col=intochr(cpc); //Change col position to a char
    savload.put(row);
    savload.put(col);
    savload.put('&');
    //Store score
    stored=intochr(score, test);
    ch=intochr(stored.thsnds);
    savload.put(ch);
    ch=intochr(stored.hndrds);
    savload.put(ch);
    ch=intochr(stored.tens);
    savload.put(ch);
    ch=intochr(stored.ones);
    savload.put(ch);
    
}

Load Save::loadgm(fstream &pzzlfil,fstream &savload) {
    Load gme;
    char ch; //Inputs character values
    int mode;
    string input;
    //Get mode
    savload.get(ch);
    if (ch=='e') {
        mode=1;
    } else if (ch=='m') {
        mode=2;
    } else if (ch=='h') {
        mode=3;
    }
    gme.mode=mode;
    //skip to after first & symbol
    getline(savload, input, '&');
    //Get row position of c 
    savload.get(ch);
    gme.rowpos=ch-48;
    savload.get(ch);
    gme.colpos=ch-48;
    //Skip next &
    savload.get(ch);
    //Get score
    savload.get(ch);
    gme.scoreth=ch-48;
    savload.get(ch);
    gme.scorehn=ch-48;
    savload.get(ch);
    gme.scorete=ch-48;
    savload.get(ch);
    gme.scoreon=ch-48;
    
    //return info
    return gme;
}