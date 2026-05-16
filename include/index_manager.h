#ifndef INDEX_MANAGER_H
#define INDEX_MANAGER_H

#include <string>
#include <vector>
#include "registro.h"
#include "indice.h"

using namespace std;

// ============================================
// FUNCIONES DE GESTIÓN DE ÍNDICES
// ============================================

bool crearIndice(const string& binPath, const string& indexPath);
vector<Indice> cargarIndice(const string& indexPath);
bool guardarIndice(const string& indexPath, const vector<Indice>& indice);
Registro* buscarPorId(int id, const string& binPath, const string& indexPath);
long buscarPosicionEnIndice(int id, const vector<Indice>& indice);

#endif
