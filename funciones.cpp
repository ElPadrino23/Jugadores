#include "Jugador.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>  // Para std::swap y std::remove
#include <cctype>     // Para tolower en trim (opcional)

// Auxiliar
std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t");
    return str.substr(first, (last - first + 1));
}

// cargar jugador.txt
std::vector<Jugador> cargar_datos(const std::string& archivo_entrada) {
    std::vector<Jugador> jugadores;
    std::ifstream file(archivo_entrada);
    
    if (!file.is_open()) {
        throw std::runtime_error("Error: No se encontró el archivo " + archivo_entrada);
    }
    
    std::string linea;
    int linea_num = 0;
    while (std::getline(file, linea)) {
        linea_num++;
        linea.erase(std::remove(linea.begin(), linea.end(), '\r'), linea.end());
        linea = trim(linea);
        if (linea.empty()) continue;
        

        std::stringstream ss(linea);
        std::string token;
        std::vector<std::string> partes;
        while (std::getline(ss, token, ',')) {
            partes.push_back(trim(token));  // Trim cada parte
        }
        
        if (partes.size() < 4) {
            std::cerr << "Línea " << linea_num << " ignorada: Formato inválido." << std::endl;
            continue;
        }
        
        try {
            std::string nombre = trim(partes[0]);
            

            int vel = 0, fue = 0, agi = 0;
            

            size_t dos_puntos_vel = partes[1].find(':');
            if (dos_puntos_vel != std::string::npos) {
                std::string vel_str = trim(partes[1].substr(dos_puntos_vel + 1));
                vel = std::stoi(vel_str);
            }
            
            // Fuerza
            size_t dos_puntos_fue = partes[2].find(':');
            if (dos_puntos_fue != std::string::npos) {
                std::string fue_str = trim(partes[2].substr(dos_puntos_fue + 1));
                fue = std::stoi(fue_str);
            }
            
            // Agilidad
            size_t dos_puntos_agi = partes[3].find(':');
            if (dos_puntos_agi != std::string::npos) {
                std::string agi_str = trim(partes[3].substr(dos_puntos_agi + 1));
                agi = std::stoi(agi_str);
            }
            
            // Validación: 1-100
            if (vel < 1 || vel > 100 || fue < 1 || fue > 100 || agi < 1 || agi > 100) {
                std::cerr << "Línea " << linea_num << " ignorada: Puntuación inválida para " << nombre << std::endl;
                continue;
            }
            
            Jugador j(nombre, vel, fue, agi);
            jugadores.push_back(j);
        } catch (const std::exception& e) {
            std::cerr << "Error parseando línea " << linea_num << ": " << linea << " (" << e.what() << ")" << std::endl;
            continue;
        }
    }
    
    file.close();
    std::cout << "Se cargaron " << jugadores.size() << " jugadores." << std::endl;
    return jugadores;
}

//Quick sort visto en clase
int particion(std::vector<Jugador>& jugadores, int bajo, int alto, bool descendente, bool por_promedio) {
    int pivote;
    if (por_promedio) {
        pivote = jugadores[alto].getPromedio();
    } else {
        pivote = jugadores[alto].velocidad;
    }
    
    int i = (bajo - 1);
    
    for (int j = bajo; j <= alto - 1; j++) {
        int valor_actual;
        if (por_promedio) {
            valor_actual = jugadores[j].getPromedio();
        } else {
            valor_actual = jugadores[j].velocidad;
        }
        
        // Si descendente, compara al revés (mayor primero)
        bool es_menor = (descendente) ? (valor_actual > pivote) : (valor_actual < pivote);
        if (es_menor) {
            i++;
            std::swap(jugadores[i], jugadores[j]);
        }
    }
    std::swap(jugadores[i + 1], jugadores[alto]);
    return (i + 1);
}

// Recursion
void quick_sort(std::vector<Jugador>& jugadores, int bajo, int alto, bool descendente, bool por_promedio) {
    if (bajo < alto) {
        int pi = particion(jugadores, bajo, alto, descendente, por_promedio);
        
        quick_sort(jugadores, bajo, pi - 1, descendente, por_promedio);
        quick_sort(jugadores, pi + 1, alto, descendente, por_promedio);
    }
}

// Volver a guardar los datos en el txt
void guardar_datos(const std::vector<Jugador>& jugadores_ordenados, const std::string& archivo_salida) {
    std::ofstream file(archivo_salida);
    if (!file.is_open()) {
        throw std::runtime_error("Error: No se pudo crear el archivo " + archivo_salida);
    }
    
    for (const auto& j : jugadores_ordenados) {
        file << j.toString() << std::endl;
    }
    
    file.close();
    std::cout << "Datos ordenados guardados en " << archivo_salida << std::endl;
}
