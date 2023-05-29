#include "../include/Pelota.hpp"

Pelota::Pelota(Vertex posicion, double radio) {
    this->posicion = posicion;
    this->radio = radio;
    this->friccion = 0.98;  // Valor de fricción (ajusta según sea necesario)
    this->gravedad = -9.81;  // Valor de gravedad (en m/s^2)
    this->masa = 0.045; // Valor de la masa (en kg)
}


void Pelota::actualizar(double dt) {
    // Calcula el peso de la pelota (Fuerza debida a la gravedad)
    double peso = masa * gravedad;

    // Calcula la fuerza de fricción (F = -μ * N, donde N es el peso normal)
    double fuerza_friccion_x = friccion * masa * velocidad.getX();
    double fuerza_friccion_y = friccion * masa * velocidad.getY(); //0.98*0.045*2.0=0.0882

    // Calcula la aceleración en x y y debido a la fricción
    double ax_friccion = (velocidad.getX() > 0 ? -1 : 1) * fuerza_friccion_x / masa;
    double ay_friccion = (velocidad.getY() > 0 ? -1 : 1) * fuerza_friccion_y / masa; //1*0.0882/0.045=1.96

    // Aplica la aceleración debida a la fricción en la velocidad en x
    velocidad.setX(velocidad.getX() + ax_friccion * dt);

    // Si la velocidad en x es lo suficientemente pequeña, detén la pelota en x
    if (velocidad.getX() < 0.001) {
        velocidad.setX(0);
    }
    // Aplica la aceleración debida a la gravedad en la velocidad en y
    velocidad.setY(velocidad.getY() + gravedad * dt); //2+(-9.81x0.01)=1.9019

    // Aplica la aceleración debida a la fricción en la velocidad en y
    velocidad.setY(velocidad.getY() - ay_friccion * dt); //1.9019-(1.96x0.01)=1.8823


    // Si la posición en y es menor que el radio (tocando el "suelo") y la velocidad en y es negativa, aplica el efecto de rebote
    double coeficiente_restitucion_max = 0.9;
    double umbral_velocidad = 2.5;
    if (posicion.getY() <= radio && velocidad.getY() < 0) {
        double factor_velocidad = abs(velocidad.getY()) / umbral_velocidad;
        if (factor_velocidad < 1) {
            double coeficiente_restitucion = coeficiente_restitucion_max * factor_velocidad;
            velocidad.setY(-coeficiente_restitucion * velocidad.getY());
        } else {
            velocidad.setY(-coeficiente_restitucion_max * velocidad.getY());
        }
        posicion.setY(radio);
    }



    // Actualiza la posición de la pelota según su velocidad
    posicion.setX(posicion.getX() + velocidad.getX() * dt);
    posicion.setY(posicion.getY() + velocidad.getY() * dt);
}



void Pelota::setVelocidad( Vertex& velocidad) {
    this->velocidad = velocidad;
}

Vertex Pelota::getPosicion()  {
    return this->posicion;
}

double Pelota::getRadio()  {
    return this->radio;
}
