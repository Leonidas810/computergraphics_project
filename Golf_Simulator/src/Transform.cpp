#include "../include/Transform.hpp"
#include "../include/Vertex.hpp"
#include <cmath>


arma::Mat<double> Transform::T(double dx, double dy, double dz){
    arma::Mat<double> t ={  {1,0,0,dx},
                            {0,1,0,dy},
                            {0,0,1,dz},
                            {0,0,0,1}
                        };

    return t;
}

arma::Mat<double> Transform::S(double sx, double sy, double sz){
    arma::Mat<double> s ={  {sx,0,0,0},
                            {0,sy,0,0},
                            {0,0,sz,0},
                            {0,0,0 ,1}
                        };
    return s;
}

arma::Mat<double> Transform::Rx(double theta){
    
    double ang=theta*M_PI/180.0;
    arma::Mat<double> r={   {       1,       0,       0 ,0},
                            {       0,cos(ang),-sin(ang),0},
                            {       0,sin(ang),cos(ang) ,0},
                            {       0,       0,       0 ,1}
    };
    return (r);
}

//Terminar
arma::Mat<double> Transform::Ry(double theta){
    
    double ang=theta*M_PI/180.0;
    arma::Mat<double> r={   {cos(ang),       0,sin(ang),0},
                            {       0,       1,       0,0},
                            {-sin(ang),      0,cos(ang),0},
                            {       0,       0,       0,1}
    };
    return (r);
}

arma::Mat<double> Transform::Rz(double theta){
    
    double ang=theta*M_PI/180.0;
    arma::Mat<double> r={   {cos(ang),-sin(ang) ,0  ,0},
                            {sin(ang),cos(ang)  ,0  ,0},
                            {       0,      0   ,1  ,0},
                            {       0,      0   ,0  ,1}
    };
    return (r);
}

arma::Mat<double> Transform::Rp1p2(Vertex P1, Vertex P2,double theta){

    //Paso 1
    arma::Mat<double> T1=this->T(-P1.getX(),-P1.getY(),-P1.getZ());

    //Paso 2
    double H1 =sqrt(pow(P2.getX()-P1.getX(),2)+pow(P2.getZ()-P1.getZ(),2));
    arma::Mat<double> Ry2={ { (P2.getX()-P1.getX())/H1,0,(P2.getZ()-P1.getZ())/H1,     0},
                            {          0,                1,           0,                   0},
                            {-(P2.getZ()-P1.getZ())/H1,0,(P2.getX()-P1.getX())/H1,     0},
                            {          0,                0,           0,                   1}};

    //Paso 3
    double H2 =sqrt(pow(P2.getX()-P1.getX(),2)+pow(P2.getY()-P1.getY(),2)+pow(P2.getZ()-P1.getZ(),2));
    arma::Mat<double> Rz3={ {         H1/H2,        (P2.getY()-P1.getY())/H2,    0,  0},
                            {-(P2.getY()-P1.getY())/H2,                H1/H2,    0,  0},
                            {          0,                                    0,    1,  0},
                            {          0,                                    0,    0,  1}};

    //Paso 4
    arma::Mat<double> Rx4=this->Rx(theta);
    //Paso 5
    arma::Mat<double> iRz3=Rz3.i();
    //Paso 6
    arma::Mat<double> iRy2=Ry2.i();
    //Paso 7
    arma::Mat<double> iT1=T1.i();

    return(iT1 * iRy2 * iRz3*Rx4* Rz3* Ry2* T1);
}