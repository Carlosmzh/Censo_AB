#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <vector>
#include "registro.h"

using namespace std;

// ============================================
// FUNCIONES DE ORDENAMIENTO MERGE SORT
// ============================================

void mergeSort(vector<Registro>& registros, int izquierda, int derecha);
void merge(vector<Registro>& registros, int izquierda, int medio, int derecha);
bool ordenarArchivoBinario(const string& binPath);

#endif
