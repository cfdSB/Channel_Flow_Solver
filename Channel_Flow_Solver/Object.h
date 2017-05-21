/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Object.h
 * Author: cd8qvt
 *
 * Created on May 20, 2017, 5:29 PM
 */

#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
class Object {
public:
    Object();
    Object(const Object& orig);
    virtual ~Object();
    virtual std::string toString()=0;
private:

};

#endif /* OBJECT_H */

