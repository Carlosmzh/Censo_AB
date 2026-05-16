#ifndef CSV_READER_H
#define CSV_READER_H

#include <string>
#include <vector>
#include "registro.h"

using namespace std;

// ============================================
// FUNCIONES DE LECTURA CSV
// ============================================

vector<Registro> cargarCSV(const string& ruta);
bool validarLineaCSV(const string& linea);
Registro parsearLinea(const string& linea, int id);
void mostrarPreview(const vector<Registro>& registros, int cantidad);
int contarLineasCSV(const string& ruta);

#endif
