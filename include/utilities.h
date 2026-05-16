#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <vector>
#include "registro.h"

using namespace std;

// ============================================
// FUNCIONES DE STRING
// ============================================

string trim(const string& str);
int stringToInt(const string& str);
string intToString(int num);

// ============================================
// FUNCIONES DE INTERFAZ
// ============================================

void mostrarMenu();
void limpiarPantalla();
void pausar();

// ============================================
// FUNCIONES DE VALIDACIÓN
// ============================================

bool archivoExiste(const string& ruta);

#endif
