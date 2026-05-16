#include "merge_sort.h"
#include "binary_file.h"
#include <iostream>
#include <fstream>

using namespace std;

// ============================================
// IMPLEMENTACIÓN - MERGE SORT
// ============================================

void merge(vector<Registro>& registros, int izquierda, int medio, int derecha) {
    vector<Registro> izq(registros.begin() + izquierda, registros.begin() + medio + 1);
    vector<Registro> der(registros.begin() + medio + 1, registros.begin() + derecha + 1);
    
    int i = 0, j = 0, k = izquierda;
    
    while (i < izq.size() && j < der.size()) {
        // Orden descendente por población
        if (izq[i].poblacion >= der[j].poblacion) {
            registros[k++] = izq[i++];
        } else {
            registros[k++] = der[j++];
        }
    }
    
    while (i < izq.size()) {
        registros[k++] = izq[i++];
    }
    
    while (j < der.size()) {
        registros[k++] = der[j++];
    }
}

void mergeSort(vector<Registro>& registros, int izquierda, int derecha) {
    if (izquierda < derecha) {
        int medio = (izquierda + derecha) / 2;
        
        mergeSort(registros, izquierda, medio);
        mergeSort(registros, medio + 1, derecha);
        merge(registros, izquierda, medio, derecha);
    }
}

bool ordenarArchivoBinario(const string& binPath) {
    cout << "\nCargando archivo binario..." << endl;
    vector<Registro> registros = leerBinario(binPath);
    
    if (registros.empty()) {
        cerr << "Error: El archivo binario está vacío." << endl;
        return false;
    }
    
    cout << "Ordenando " << registros.size() << " registros por población (descendente)..." << endl;
    
    mergeSort(registros, 0, registros.size() - 1);
    
    cout << "Escribiendo archivo ordenado..." << endl;
    
    return escribirBinario(binPath, registros);
}
