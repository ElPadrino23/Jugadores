#include "Jugador.h"
#include <sstream>

// Constructor por defecto
Jugador::Jugador() : nombre(""), velocidad(0), fuerza(0), agilidad(0) {}

// constructor
Jugador::Jugador(const std::string& n, int v, int f, int a) 
    : nombre(n), velocidad(v), fuerza(f), agilidad(a) {}

// Formula de promedio
int Jugador::getPromedio() const {
    return (velocidad + fuerza + agilidad) / 3;
}

// Eliminar jugador
std::string Jugador::toString() const {
    std::stringstream ss;
    ss << nombre << ", Velocidad:" << velocidad 
       << ", Fuerza:" << fuerza 
       << ", Agilidad:" << agilidad;
    return ss.str();
}
