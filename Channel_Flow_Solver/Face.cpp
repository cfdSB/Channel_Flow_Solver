/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Face.h"

Face::Face(Point* centroid, double length, double width):
centroid(centroid), length(length), width(width), cell1(NULL), cell2(NULL){
    
}

Face::~Face(){
    centroid = 0;
    cell1 = 0;
    cell2 = 0;
}

Point* Face::getCentroid() {
    return centroid;
}

double Face::getLength() {
    return length;
}

double Face::getWidth() {
    return width;
}

FvCell* Face::getCell1() {
    return cell1;
}

FvCell* Face::getCell2() {
    return cell2;
}

void Face::setCell1(FvCell* cell1) {
    this->cell1 = cell1;
}

void Face::setCell2(FvCell* cell2) {
    this->cell2 = cell2;
}

std::string Face::toString() {
    std::ostringstream output;
    std::string pointString = centroid->toString();
    output <<"Face Centroid: " << pointString << "\n";
    output<<"Face Size:" << length << "," << width;
    return output.str();
}

FvCell* Face::getConnectingCell(FvCell* cell) {
    if(cell1 != cell){
        return cell1;   //return nonmatching cell
    }else{
        return cell2;
    }
}

double Face::getArea() {
    return length*width;
}




