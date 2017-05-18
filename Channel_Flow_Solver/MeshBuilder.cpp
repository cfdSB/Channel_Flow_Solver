/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "MeshBuilder.h"

MeshBuilder::MeshBuilder() {
    allPoints = new std::vector<Point*>();
    allFaces = new std::vector<Face*>();
    allCells = new std::vector<FvCell*>();
}

MeshBuilder::~MeshBuilder() {
    //delete all point objects
    for(int i=0; i<allPoints->size(); i++) {
        Point* p = (*allPoints)[i];
        delete p;
    }
    delete allPoints;   //delete vector object

    //delete all face objects
    for (int i = 0; i < allFaces->size(); i++) {
        Face* p = (*allFaces)[i];
        delete p;
    }
    delete allFaces;    //delete vector object
    
    //delete all cell objects
    for (int i = 0; i < allCells->size(); i++) {
        FvCell* p = (*allCells)[i];
        delete p;
    }
    delete allCells;    //delete vector object
    
}

void MeshBuilder::buildMesh(double xMin, double xMax, double yMin, double yMax, double zMin, double zMax, int xCells, int yCells, int zCells){    
    
    double dx = (xMax - xMin)/xCells;
    double dy = (yMax - yMin)/yCells;
    double dz = (zMax - zMin)/zCells;
    
    double currentX = 0.0;
    for(int i =0; i< xCells; i++){
        
        if(i==0){
            currentX = currentX + dx/2.0;
        }else{
            currentX = currentX + dx;
        }
        double currentY = 0.0;
        for(int j = 0; j< yCells; j++){
            
            if (j == 0) {
                currentY = currentY + dy / 2.0;
            } else {
                currentY = currentY + dy;
            }

            double currentZ = 0.0;
            for (int k = 0; k < zCells; k++) {
                
                if (k == 0) {
                    currentZ = currentZ + dz / 2.0;
                } else {
                    currentZ = currentZ + dz;
                }
                
                //create cell
                Point* cellCenter = createPoint(currentX, currentY, currentZ);
                FvCell* cell = createCell(cellCenter, dx, dy, dz);
                std::vector<Face*> faces = buildFaces(cell);
                cell->setFaces(faces);
                                        
            }
        }
    }    
}

Point* MeshBuilder::createPoint(double x, double y, double z) {
    Point* p = new Point(x, y, z);
    allPoints->push_back(p);
    return p;
}

FvCell* MeshBuilder::createCell(Point* centroid, double length, double width, double height) {
    FvCell* c = new FvCell(centroid, length, width, height);
    allCells->push_back(c);
    return c;
}

Face* MeshBuilder::createFace(Point* centroid, double length, double width) {
    Face* f = new Face(centroid, length, width);
    allFaces->push_back(f);
    return f;
}

void MeshBuilder::printCell(FvCell* cell){
    std::cout<<"-----------------"<<std::endl;
    double* centroid = cell->getCentroid()->getCoordinates();
    std::cout<<centroid[0]<<","<<centroid[1]<<","<<centroid[2]<<","<<cell->getDx()<<","<<cell->getDy()<<","<<cell->getDz()<<std::endl;
    
    //print faces
    for(int i=0; i<6; i++){
        Face* face = (cell->getFaces())[i];
        double* centroidF = face->getCentroid()->getCoordinates();
        std::cout<<centroidF[0]<<","<<centroidF[1]<<","<<centroidF[2]<<","<<face->getLength()<<","<<face->getWidth()<<std::endl;
    
        
    }
}


std::vector<Face*> MeshBuilder:: buildFaces(FvCell* cell){
    std::vector<Face*> faces;
    double* cellCentroid = cell->getCentroid()->getCoordinates();
    //x- face
    double xm_x = cellCentroid[0] - cell->getDx()/2.0;
    double xm_y = cellCentroid[1];
    double xm_z = cellCentroid[2];
    
    Point* xmCentroid = createPoint(xm_x, xm_y, xm_z);
    Face* xmFace = createFace(xmCentroid, cell->getDy(), cell->getDz());
    faces.push_back(xmFace);
    
    //x+ face
    double xp_x = cellCentroid[0] + cell->getDx()/2.0;
    double xp_y = cellCentroid[1];
    double xp_z = cellCentroid[2];
    Point* xpCentroid = createPoint(xp_x, xp_y, xp_z);
    Face* xpFace = createFace(xpCentroid, cell->getDy(), cell->getDz());
    faces.push_back(xpFace);
    
    //y- face
    double ym_x = cellCentroid[0];
    double ym_y = cellCentroid[1] - cell->getDy()/2.0;
    double ym_z = cellCentroid[2];
    Point* ymCentroid = createPoint(ym_x, ym_y, ym_z);
    Face* ymFace = createFace(ymCentroid, cell->getDx(), cell->getDz());
    faces.push_back(ymFace);
    
    //y+ face
    double yp_x = cellCentroid[0];
    double yp_y = cellCentroid[1] + cell->getDy()/2.0;
    double yp_z = cellCentroid[2];    
    Point* ypCentroid = createPoint(yp_x, yp_y, yp_z);
    Face* ypFace = createFace(ypCentroid, cell->getDx(), cell->getDz());
    faces.push_back(ypFace);
    
    //z- face
    double zm_x = cellCentroid[0];
    double zm_y = cellCentroid[1];
    double zm_z = cellCentroid[2] - cell->getDz()/2.0;
    Point* zmCentroid = createPoint(zm_x, zm_y, zm_z);
    Face* zmFace = createFace(zmCentroid, cell->getDx(), cell->getDy());
    faces.push_back(zmFace);
    
    //z+ face
    double zp_x = cellCentroid[0];
    double zp_y = cellCentroid[1];
    double zp_z = cellCentroid[2] + cell->getDy()/2.0;  
    Point* zpCentroid = createPoint(zp_x, zp_y, zp_z);
    Face* zpFace = createFace(zpCentroid, cell->getDx(), cell->getDy());
    faces.push_back(zpFace);
    
    return faces;
}

void MeshBuilder::printCells() {
      for (int i = 0; i < allCells->size(); i++) {
        printCell((*allCells)[i]);
    }
}
   





