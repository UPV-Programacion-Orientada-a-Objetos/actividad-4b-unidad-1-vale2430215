#include <iostream>
#include "Simulador2D.h"
using namespace std;

int main() {

    cout << ">> Inicializando Sistema (Tipo FLOAT) <<\n";
    cout << "Creando Grid (FLOAT) de 5x5...\n";

    // Crear el simulador tipo float de 5x5
    Simulador2D<float> sim(5, 5);

    cout << "\n>> Agregando Fuentes de Concentracion <<\n";
    sim.agregarFuente(100.0f);
    cout << "Agregar Fuente 1 (Valor 100.0): exito.\n";
    sim.agregarFuente(50.0f);
    cout << "Agregar Fuente 2 (Valor 50.0): exito.\n";

    cout << "\n>> Aplicando Valores Iniciales <<\n";
    sim.setValor(2, 2, 100.0f); // Fuente 1
    cout << "Grid[2,2] = 100.0 (Fuente 1)\n";
    sim.setValor(4, 0, 50.0f); // Fuente 2
    cout << "Grid[4,0] = 50.0 (Fuente 2)\n";

    cout << "\n--- Grid Inicial (Paso 0) ---\n";
    sim.mostrarGrid();

    cout << "\nOpci0n: Simular 1 Paso\n";
    sim.simularPaso();

    cout << "\nGrid Después del Paso 1\n";
    sim.mostrarGrid();

    cout << "\nOpción: Redimensionar\n";
    cout << "Redimensionando Grid a 6x6. Datos copiados.\n";
    sim.redimensionarGrid(6, 6);

    cout << "\nGrid Redimensionado (6x6)\n";
    sim.mostrarGrid();

    cout << "\nOpcion: Salir\n";
    cout << "Liberando memoria del Grid y Fuentes... Sistema cerrado.\n";

    return 0;
}
