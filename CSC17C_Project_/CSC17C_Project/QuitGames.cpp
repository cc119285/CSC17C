/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "QuitGames.h"

void QuitGIn::setQG(int qg) {
    quitGms=qg;
}

int QuitGIn::getQG() {
    return quitGms;
}

void QuitGIn::operator ++ (int) {
    quitGms++;
}