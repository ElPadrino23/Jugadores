#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include <vector>

// FOrma en la que se representara
struct Jugador {
    std::string nombre;
    int velocidad;
    int fuerza;
    int agilidad;
    
    // cons
    Jugador();
    Jugador(const std::string& n, int v, int f, int a);
    
    // metod
    int getPromedio() const;
    std::string toString() const;
};

//mini prototipo
std::vector<Jugador> cargar_datos(const std::string& archivo_entrada);
void quick_sort(std::vector<Jugador>& jugadores, int bajo, int alto, bool descendente = true, bool por_promedio = false);
int particion(std::vector<Jugador>& jugadores, int bajo, int alto, bool descendente, bool por_promedio);
void guardar_datos(const std::vector<Jugador>& jugadores_ordenados, const std::string& archivo_salida);

#endif // JUGADOR_H
