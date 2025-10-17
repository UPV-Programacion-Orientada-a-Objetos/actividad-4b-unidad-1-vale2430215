#ifndef SIMULADOR2D_H
#define SIMULADOR2D_H

#include <iostream>
using namespace std;

template <typename T>
class Simulador2D {
private:
    // Matriz de la cuadrícula (Dinámica y Genérica)
    T **_grid;
    int _filas;
    int _columnas;

    // Vector de Fuentes (Dinámico y Genérico)
    T *_fuentes;
    int _numFuentes;
    int _capacidadFuentes;

    // Vector de Constantes (Estático)
    float _constantes[3]; // [0] = Coeficiente de Difusión, [1] = DeltaX, [2] = DeltaT

public:
    // MÉTODOS PÚBLICOS OBLIGATORIOS:
    Simulador2D(int f, int c); // Constructor
    ~Simulador2D(); // Destructor
    void redimensionarGrid(int nuevaF, int nuevaC);
    void agregarFuente(T valor); // Expansión manual del vector dinámico si es necesario
    void simularPaso(); // Implementación del algoritmo
    // ... otros métodos de acceso y visualización
    void mostrarGrid() const;
};

// Constructor
template <typename T>
Simulador2D<T>::Simulador2D(int f, int c) {
    _filas = f;
    _columnas = c;

    // Crear matriz 2D
    _grid = new T*[f];
    for (int i = 0; i < f; i++) {
        _grid[i] = new T[c];
        for (int j = 0; j < c; j++)
            _grid[i][j] = 0; // iniciar en 0
    }

    // Inicializar vector dinámico de fuentes
    _capacidadFuentes = 2;
    _numFuentes = 0;
    _fuentes = new T[_capacidadFuentes];

    // Inicializar constantes
    _constantes[0] = 1.0f;
    _constantes[1] = 1.0f;
    _constantes[2] = 1.0f;
}

// Destructor
template <typename T>
Simulador2D<T>::~Simulador2D() {
    for (int i = 0; i < _filas; i++)
        delete[] _grid[i];
    delete[] _grid;
    delete[] _fuentes;
}

// Mostrar matriz
template <typename T>
void Simulador2D<T>::mostrarGrid() const {
    for (int i = 0; i < _filas; i++) {
        for (int j = 0; j < _columnas; j++)
            cout << _grid[i][j] << "\t";
        cout << endl;
    }
}

#endif