/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Link.h
 * Author: Professor
 *
 * Created on October 24, 2017, 11:56 AM
 */

#ifndef LINK_H
#define LINK_H

//Composition of a Link
template<class T>
struct Link{
    T data;		//Any integer data, to be changed any class with templates later
    Link *linkPtr;  //Self Reference which when utilized forms a linked list
};


#endif /* LINK_H */

