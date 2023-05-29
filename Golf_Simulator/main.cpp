#include <iostream>
#include <GLFW/glfw3.h>
#include "include/Transform.hpp"
#include "include/Pelota.hpp"
#include "include/Simulador.hpp"
#include "include/Object.hpp"
#include "include/Palo.hpp"


using namespace std;

bool detectarColision(Vertex posicionPelota, double radioPelota, Vertex posicionMeta, double radioMeta) {
    double distancia = abs(posicionPelota.getX() - posicionMeta.getX());
    return distancia <= (radioPelota + radioMeta);
}

void dibujarObjeto(Models &modelo, arma::mat &transf,double Ia,double Ip,arma::vec F) {
    vector<Face> faces = modelo.get_faces();

    for (Face f : faces) {
        //if (f.is_visible(0.0, 0.0, -1.0, transf)) {           //Errores en la implementacion de is_visible
        arma::vec v=f.get_edges()[0].get_vf().toArmaVec();
        arma::vec L=F-v;
        double dL=sqrt(powf(L[0],2)+powf(L[1],2)+powf(L[2],2));
        L=arma::normalise(L);
        double fatt= 1/powf(dL,2);
        double I=(Ia*modelo.get_ka())+(fatt * Ip *modelo.get_kd() * arma::dot(f.get_normal(),L));
        double r=modelo.get_r()* I;
        double g=modelo.get_g()* I;
        double b=modelo.get_b()* I;
        glColor3f(r,g,b);

            glBegin(GL_POLYGON);
            for (Edge e : f.get_edges()) {
                arma::Col<double> vp = transf * e.get_vi().toHomogeneous();
                glVertex3f(vp.at(0), vp.at(1), vp.at(2));
            }
            arma::Col<double> vp = transf * f.get_edges().back().get_vf().toHomogeneous();
            glVertex3f(vp.at(0), vp.at(1), vp.at(2));
            glEnd();
        //}
    }
}

int main() {

    // Carga el modelo de la esfera
    Object<Ply> esferaModel("models/rock.ply");
    esferaModel.set_material(1.0,0.0,1.0,1.0,0.9);
    // Carga el modelo del palo de golf
    Object<Obj> paloGolfModel("models/golf_palo1.obj");
    paloGolfModel.set_material(0.0,0.5,0.0,1.0,0.5);
    // Carga el modelo de la meta
    Object<Obj> metaModel("models/meta.obj");
    metaModel.set_material(1.0,0.0,0.0,1.0,0.5);

    // Inicializar GLFW
    if (!glfwInit()) {
        cerr << "Error al inicializar GLFW." << endl;
        return -1;
    }

    // Crear ventana
    GLFWwindow *window = glfwCreateWindow(1400, 800, "Simulación de Golf", NULL, NULL);
    if (!window) {
        cerr << "Error al crear ventana GLFW." << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // Crear una variable para verificar si el golpe ya ha sido realizado
    bool golpeRealizado = false;

    // Inicializar la pelota
    Vertex posicionInicialPelota(-1.0, 0.0, 0.0);
    double radio = 0.04267; // Radio de una pelota de golf estándar en metros
    Pelota pelota(posicionInicialPelota, 0.04267);

    // Inicializar la palo
    Vertex posicionInicialPalo(-1.0, 0.5, 0.0);
    Palo palo(posicionInicialPalo);

    // Variables para controlar el tiempo de presionado de la tecla espacio
    double tiempoPresionado = 0.0;
    double maxTiempoPresionado = 3.0;  // Tiempo máximo de presionado en segundos
    bool espacioPresionadoPrevio = false;  // Estado previo de la tecla espacio
    
    // Variables para controlar el progreso del golpe
    bool mostrarBarraProgreso = false;
    float progresoPresionado = 0.0f;

    //Deteccion de colison pelota-meta
    bool colisionDetectada = false;
    double amplitud = 0.3;  // Ajusta la amplitud del movimiento vertical de la meta
    double velocidad = 4.0;  // Ajusta la velocidad de oscilación de la meta

    // Inicializar el simulador
     double tiempoActual = 0.0; // Inicializar el tiempo
    double tiempoTotal = 100.0; // Duración de la simulación en segundos
    double deltaTime = 0.01;  // Intervalo de tiempo entre actualizaciones
    Simulador simulador(pelota,palo, tiempoTotal, deltaTime);

    //Intensidad de luz ambiente
    double Ia=0.8;
    double Ip=0.7;
    arma::vec F {1.0,1.0,1.0};

    Transform tr;
    
    //Angulo del palo de Golf
    double anguloP = 135.0;

    //Angulo del meta de Golf
    double anguloM = 0.0;

    // Bucle principal
    while (!glfwWindowShouldClose(window)) {
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    float aspect_ratio = static_cast<float>(width) / static_cast<float>(height);
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-aspect_ratio, aspect_ratio, -1.0, 1.0, -20.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Dibujar el palo de golf
    if (!golpeRealizado) {

        // Comprobar si la tecla espacio se soltó después de ser presionada
        if (espacioPresionadoPrevio && glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE){
            golpeRealizado = true;
            Vertex velocidadInicial(tiempoPresionado, tiempoPresionado, 0.0);
            pelota.setVelocidad(velocidadInicial);
        }

        // Si se presiona la tecla espacio, incrementar el tiempo de presionado
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            tiempoPresionado += deltaTime;
            if (tiempoPresionado > maxTiempoPresionado) {
                tiempoPresionado=maxTiempoPresionado;
                progresoPresionado=maxTiempoPresionado;
            }else{
                progresoPresionado = tiempoPresionado;
            }
            mostrarBarraProgreso = true;
        }else{
            mostrarBarraProgreso = false;
        }
        // Actualizar el estado previo de la tecla espacio
        espacioPresionadoPrevio = (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS);

        // Obtener la posición actual de la pelota y aplicar la transformación
        arma::vec::fixed<3> posicionPelota = pelota.getPosicion().toArmaVec();
        arma::mat transfPelota = tr.T(posicionPelota.at(0), posicionPelota.at(1), posicionPelota.at(2)) * tr.S(radio, radio, radio);

        // Dibujar la pelota en la posición actualizada
        dibujarObjeto(esferaModel, transfPelota,Ia,Ip,F);

        // Obtener la posición actual del palo y aplicar la transformación
        arma::vec::fixed<3> posicionPalo = palo.getPosicion().toArmaVec();
        arma::mat transfPalo = tr.T(posicionPalo.at(0), posicionPalo.at(1), posicionPalo.at(2)) * tr.Rz(anguloP) *tr.S(1, 1, 1);

        // Dibujar el palo en la posición actualizada
        dibujarObjeto(paloGolfModel, transfPalo,Ia,Ip,F);

        // Aplicar la transformación a la meta
        arma::mat transMeta = tr.T(1.0, 0.0, 0.0) * tr.Ry(anguloM) * tr.S(0.5, 0.5, 0.5);

        // Dibujar la meta
        dibujarObjeto(metaModel, transMeta, Ia, Ip, F);

        // Actualizar el ángulo
        anguloM += 0.8;

        // Dibujar la barra de progreso
        if (mostrarBarraProgreso) {
            glPushMatrix();
            glTranslatef(-1.5f, -0.9f, 0.0f); // Posición de la barra de progreso
            glScalef(progresoPresionado, 1.0f, 1.0f); // Escalar según el progreso
            glBegin(GL_QUADS);
            glVertex2f(0.0f, 0.0f);
            glVertex2f(1.0f, 0.0f);
            glVertex2f(1.0f, 0.1f);
            glVertex2f(0.0f, 0.1f);
            glEnd();
            glPopMatrix();
        }
    }else{

        if(anguloP < 180){
            //Transformaciones al palo
            anguloP=anguloP+2;
        }else{
            // Actualizar la posición de la pelota
            if (tiempoActual < tiempoTotal) {
                pelota.actualizar(deltaTime);
                tiempoActual += deltaTime;
            }
        }

        if (!colisionDetectada && detectarColision(pelota.getPosicion(), radio, Vertex(1.0, 0.0, 0.0), 0.04267)) {
            cout << "Ganaste" << endl;
            colisionDetectada = true;
        }

        if (colisionDetectada) {
            // Obtener la posición actual de la pelota y aplicar la transformación
            arma::vec::fixed<3> posicionPelota = pelota.getPosicion().toArmaVec();
            arma::mat transfPelota = tr.T(posicionPelota.at(0), posicionPelota.at(1), posicionPelota.at(2))* tr.S(radio, radio, radio);

            // Dibujar la pelota en la posición actualizada
            dibujarObjeto(esferaModel, transfPelota,Ia,Ip,F);
        }else {
           // Obtener la posición actual de la pelota y aplicar la transformación
            arma::vec::fixed<3> posicionPelota = pelota.getPosicion().toArmaVec();
            arma::mat transfPelota = tr.T(posicionPelota.at(0), posicionPelota.at(1), posicionPelota.at(2))* tr.Rz(-anguloM*4) * tr.S(radio, radio, radio);

            // Dibujar la pelota en la posición actualizada
            dibujarObjeto(esferaModel, transfPelota,Ia,Ip,F);
        }

        if (colisionDetectada) {
            // Obtener la posición actual del palo y aplicar la transformación
            arma::vec::fixed<3> posicionPalo = palo.getPosicion().toArmaVec();
            arma::mat transfPalo = tr.T(posicionPalo.at(0), posicionPalo.at(1), posicionPalo.at(2))* tr.Rx(anguloM) * tr.Rz(anguloP) * tr.Ry(anguloM)* tr.S(1, 1, 1);

            // Dibujar el palo en la posición actualizada
            dibujarObjeto(paloGolfModel, transfPalo,Ia,Ip,F);
        }else {
           // Obtener la posición actual del palo y aplicar la transformación
            arma::vec::fixed<3> posicionPalo = palo.getPosicion().toArmaVec();
            arma::mat transfPalo = tr.T(posicionPalo.at(0), posicionPalo.at(1), posicionPalo.at(2)) * tr.Rz(anguloP) * tr.S(1, 1, 1);

            // Dibujar el palo en la posición actualizada
            dibujarObjeto(paloGolfModel, transfPalo,Ia,Ip,F);
        }

        if (colisionDetectada) {
            double desplazamientoY = amplitud * sin(velocidad * tiempoActual);
            desplazamientoY=abs(desplazamientoY);
            // Aplicar la transformación a la meta con el desplazamiento vertical
            arma::mat transMeta = tr.T(1.0, 0.0, 0.0) * tr.T(0.0, desplazamientoY, 0.0) * tr.Ry(anguloM) * tr.S(0.5, 0.5, 0.5);

            // Dibujar la meta
            dibujarObjeto(metaModel, transMeta, Ia, Ip, F);
        }else {
            // Aplicar la transformación normal a la meta
            arma::mat transMeta = tr.T(1.0, 0.0, 0.0) * tr.Ry(anguloM) * tr.S(0.5, 0.5, 0.5);

            // Dibujar la meta
            dibujarObjeto(metaModel, transMeta, Ia, Ip, F);
        }

        // Actualizar el ángulo
        anguloM += 0.8;
    }
    glfwSwapBuffers(window);
    glfwPollEvents();
    }   
    glfwTerminate();
    return 0;
}