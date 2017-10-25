/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GmeInfo.h
 * Author: Professor
 *
 * Created on June 1, 2017, 8:52 PM
 */

#ifndef GMEINFO_H
#define GMEINFO_H

class GmeInfo {
private:
    int totgms;
public:
    //Constructor
    GmeInfo() {
        totgms=0;
    }
    //Member functions
    void setInfo(int);
    int getInfo();
    virtual void operator ++ (int);
};

#endif /* GMEINFO_H */

