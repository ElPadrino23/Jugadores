#include "Jugador.h"
#include <iostream>
#include <vector>
#include <string>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Uso: " << argv[0] << " <archivo_entrada.txt> <archivo_salida.txt>" << std::endl;
        std::cerr << "Ejemplo: ./programa jugadores.txt jugadores_ordenados.txt" << std::endl;
        return 1;
    }
    
    std::string archivo_entrada = argv[1];
    std::string archivo_salida = argv[2];
    
    try {
        // cargamos los datos
        std::vector<Jugador> jugadores = cargar_datos(archivo_entrada);
        
        if (jugadores.empty()) {
            std::cout << "No hay datos para ordenar." << std::endl;
            return 0;
        }
        
        //Configuracion de como se ordenara 
        bool por_promedio = false;  // Promedio
        bool descendente = true;    // Mayor a menor
        
        quick_sort(jugadores, 0, static_cast<int>(jugadores.size()) - 1, descendente, por_promedio);
        
        // Mostrar
        std::cout << "Jugadores de mayor a menor:" << std::endl;
        if (por_promedio) {
            std::cout << "Promedio de habilidades << std::endl;
        } else {
            std::cout << "Velocidad" << std::endl;
        }
        for (const auto& j : jugadores) {
            std::cout << j.toString() << " (Promedio: " << j.getPromedio() << ")" << std::endl;
        }
        
        // Aqui se guarda en el archivo
        guardar_datos(jugadores, archivo_salida);
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
