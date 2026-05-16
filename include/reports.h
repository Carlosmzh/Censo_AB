#ifndef REPORTS_H
#define REPORTS_H

#include <string>
#include <vector>
#include <map>
#include "registro.h"

using namespace std;

// ============================================
// FUNCIONES DE GENERACIÓN DE REPORTES
// ============================================

bool generarReporte(const string& binPath, const string& reportPath);
map<string, map<string, int>> sumarPorDepartamentoMunicipio(const vector<Registro>& registros);
map<string, map<string, int>> sumarPorDepartamentoSexo(const vector<Registro>& registros);
map<string, int> sumarPorDepartamento(const vector<Registro>& registros);

#endif
