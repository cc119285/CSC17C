/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "GmeInfo.h"

void GmeInfo::setInfo(int gms) {
    totgms=gms;
}

int GmeInfo::getInfo() {
    return totgms;
}

void GmeInfo::operator ++ (int incrgms) {
    totgms++;
}