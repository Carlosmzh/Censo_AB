#include "index_manager.h"
#include "binary_file.h"
#include <fstream>
#include <iostream>

using namespace std;

// ============================================
// IMPLEMENTACIÓN - GESTIÓN DE ÍNDICES
// ============================================

bool crearIndice(const string& binPath, const string& indexPath) {
    ifstream binFile(binPath, ios::binary);
    if (!binFile.is_open()) {
        cerr << "Error: No se pudo abrir el archivo binario " << binPath << "." << endl;
        return false;
    }
    
    vector<Indice> indices;
    Registro reg;
    long posicion = 0;
    
    while (binFile.read((char*)&reg, sizeof(Registro))) {
        Indice idx;
        idx.id = reg.id;
        idx.posicion = posicion;
        indices.push_back(idx);
        posicion += sizeof(Registro);
    }
    
    binFile.close();
    
    return guardarIndice(indexPath, indices);
}

bool guardarIndice(const string& indexPath, const vector<Indice>& indice) {
    ofstream archivo(indexPath, ios::binary);
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo de índice " << indexPath << " para escritura." << endl;
        return false;
    }
    
    for (const auto& idx : indice) {
        archivo.write((const char*)&idx, sizeof(Indice));
    }
    
    archivo.close();
    
    cout << "\nSe crearon " << indice.size() << " índices." << endl;
    cout << "Tamaño del archivo de índice: " << (indice.size() * sizeof(Indice)) << " bytes." << endl;
    
    return true;
}

vector<Indice> cargarIndice(const string& indexPath) {
    vector<Indice> indices;
    
    ifstream archivo(indexPath, ios::binary);
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo de índice " << indexPath << "." << endl;
        return indices;
    }
    
    Indice idx;
    while (archivo.read((char*)&idx, sizeof(Indice))) {
        indices.push_back(idx);
    }
    
    archivo.close();
    
    return indices;
}

long buscarPosicionEnIndice(int id, const vector<Indice>& indice) {
    // Búsqueda binaria
    int izquierda = 0;
    int derecha = indice.size() - 1;
    
    while (izquierda <= derecha) {
        int medio = (izquierda + derecha) / 2;
        
        if (indice[medio].id == id) {
            return indice[medio].posicion;
        } else if (indice[medio].id < id) {
            izquierda = medio + 1;
        } else {
            derecha = medio - 1;
        }
    }
    
    return -1;  // No encontrado
}

Registro* buscarPorId(int id, const string& binPath, const string& indexPath) {
    vector<Indice> indices = cargarIndice(indexPath);
    
    if (indices.empty()) {
        cerr << "Error: El índice está vacío." << endl;
        return nullptr;
    }
    
    long posicion = buscarPosicionEnIndice(id, indices);
    
    if (posicion == -1) {
        cerr << "Error: Registro con ID " << id << " no encontrado." << endl;
        return nullptr;
    }
    
    Registro* reg = new Registro();
    *reg = leerRegistro(binPath, posicion);
    
    return reg;
}
