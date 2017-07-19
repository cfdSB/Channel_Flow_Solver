/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PhysicsContinuum.cpp
 * Author: cd8qvt
 * 
 * Created on June 1, 2017, 11:16 AM
 */

#include "PhysicsContinuum.h"

PhysicsContinuum::PhysicsContinuum() {
}

PhysicsContinuum::PhysicsContinuum(const PhysicsContinuum& orig) {
}

PhysicsContinuum::~PhysicsContinuum() {
}

double PhysicsContinuum::getThermalConductivity() const {
    return thermalConductivity;
}

double PhysicsContinuum::setThermalConductivity(double conductivity) {
    thermalConductivity = conductivity;
}

double PhysicsContinuum::getDensity() const {
    return density;
}

void PhysicsContinuum::setDensity(double value) {
    this->density = value;
}

double PhysicsContinuum::getDiffusionCoefficient() const {
    return diffusionCoefficient;
}

void PhysicsContinuum::setDiffusionCoefficient(double value) {
    this->diffusionCoefficient = value;
}


