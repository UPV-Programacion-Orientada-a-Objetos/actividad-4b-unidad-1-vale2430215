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
    void setValor(int f, int c, T valor); // Asignar valor manualmente
    void mostrarGrid() const; // Mostrar el grid
};

// -------------------------------------------------------
// IMPLEMENTACIONES
// -------------------------------------------------------

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

// Redimensionar matriz
template <typename T>
void Simulador2D<T>::redimensionarGrid(int nuevaF, int nuevaC) {
    T **nuevo = new T*[nuevaF];
    for (int i = 0; i < nuevaF; i++) {
        nuevo[i] = new T[nuevaC];
        for (int j = 0; j < nuevaC; j++)
            nuevo[i][j] = 0;
    }

    int minF = (nuevaF < _filas) ? nuevaF : _filas;
    int minC = (nuevaC < _columnas) ? nuevaC : _columnas;

    for (int i = 0; i < minF; i++)
        for (int j = 0; j < minC; j++)
            nuevo[i][j] = _grid[i][j];

    for (int i = 0; i < _filas; i++)
        delete[] _grid[i];
    delete[] _grid;

    _grid = nuevo;
    _filas = nuevaF;
    _columnas = nuevaC;
}

// Agregar fuente dinámica
template <typename T>
void Simulador2D<T>::agregarFuente(T valor) {
    if (_numFuentes >= _capacidadFuentes) {
        _capacidadFuentes *= 2;
        T *nuevo = new T[_capacidadFuentes];
        for (int i = 0; i < _numFuentes; i++)
            nuevo[i] = _fuentes[i];
        delete[] _fuentes;
        _fuentes = nuevo;
    }
    _fuentes[_numFuentes++] = valor;
}

// Simular un paso
template <typename T>
void Simulador2D<T>::simularPaso() {
    T **nuevo = new T*[_filas];
    for (int i = 0; i < _filas; i++)
        nuevo[i] = new T[_columnas];

    for (int i = 0; i < _filas; i++) {
        for (int j = 0; j < _columnas; j++) {
            if (i == 0 || j == 0 || i == _filas - 1 || j == _columnas - 1)
                nuevo[i][j] = _grid[i][j];
            else
                nuevo[i][j] = (_grid[i-1][j] + _grid[i+1][j] +
                               _grid[i][j-1] + _grid[i][j+1]) / 4.0;
        }
    }

    for (int i = 0; i < _filas; i++)
        for (int j = 0; j < _columnas; j++)
            _grid[i][j] = nuevo[i][j];

    for (int i = 0; i < _filas; i++)
        delete[] nuevo[i];
    delete[] nuevo;
}

// Asignar un valor manual a una celda
template <typename T>
void Simulador2D<T>::setValor(int f, int c, T valor) {
    if (f >= 0 && f < _filas && c >= 0 && c < _columnas)
        _grid[f][c] = valor;
}

// Mostrar el grid con formato del README
template <typename T>
void Simulador2D<T>::mostrarGrid() const {
    for (int i = 0; i < _filas; i++) {
        cout << "| ";
        for (int j = 0; j < _columnas; j++) {
            cout << _grid[i][j];
            if (j < _columnas - 1) cout << "\t";
        }
        cout << " |" << endl;
    }
}

#endif
