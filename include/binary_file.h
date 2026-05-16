#ifndef BINARY_FILE_H
#define BINARY_FILE_H

#include <string>
#include <vector>
#include "registro.h"

using namespace std;

// ============================================
// FUNCIONES DE ARCHIVO BINARIO
// ============================================

bool escribirBinario(const string& ruta, const vector<Registro>& registros);
vector<Registro> leerBinario(const string& ruta);
bool escribirRegistro(const string& ruta, const Registro& reg, long posicion);
Registro leerRegistro(const string& ruta, long posicion);
long obtenerTamanoArchivo(const string& ruta);
int contarRegistrosBinario(const string& ruta);

#endif
