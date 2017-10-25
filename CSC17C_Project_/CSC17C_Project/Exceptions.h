/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Exceptions.h
 * Author: rcc
 *
 * Created on May 30, 2017, 1:40 PM
 */

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

class Exeptns {
private: 
    
public:
    class quitgm {
    private:
     int quitgs;
    public:
        quitgm() {
            quitgs++;
        }
    };
    
    void quit();
};

#endif /* EXCEPTIONS_H */

