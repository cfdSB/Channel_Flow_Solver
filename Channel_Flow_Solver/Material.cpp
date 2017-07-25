/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Material.cpp
 * Author: cd8qvt
 * 
 * Created on July 24, 2017, 4:51 PM
 */

#include "Material.h"

Material::Material() {
}

Material::Material(const Material& orig) {
}

Material::~Material() {
}

double Material::getDensity() const {
    return density;
}

void Material::setDensity(double value) {
    this->density = value;
}

double Material::getDiffusionCoefficient() const {
    return diffusionCoefficient;
}

void Material::setDiffusionCoefficient(double value) {
    this->diffusionCoefficient = value;
}


