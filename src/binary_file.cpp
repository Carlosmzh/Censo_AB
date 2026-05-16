#include "binary_file.h"
#include <fstream>
#include <iostream>

using namespace std;

// ============================================
// IMPLEMENTACIÓN - ARCHIVO BINARIO
// ============================================

bool escribirBinario(const string& ruta, const vector<Registro>& registros) {
    ofstream archivo(ruta, ios::binary);
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo " << ruta << " para escritura." << endl;
        return false;
    }
    
    for (const auto& reg : registros) {
        archivo.write((const char*)&reg, sizeof(Registro));
    }
    
    archivo.close();
    
    cout << "\nSe escribieron " << registros.size() << " registros al archivo binario." << endl;
    cout << "Tamaño del archivo: " << (registros.size() * sizeof(Registro)) << " bytes." << endl;
    
    return true;
}

vector<Registro> leerBinario(const string& ruta) {
    vector<Registro> registros;
    
    ifstream archivo(ruta, ios::binary);
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo " << ruta << " para lectura." << endl;
        return registros;
    }
    
    Registro reg;
    while (archivo.read((char*)&reg, sizeof(Registro))) {
        registros.push_back(reg);
    }
    
    archivo.close();
    
    cout << "\nSe leyeron " << registros.size() << " registros del archivo binario." << endl;
    
    return registros;
}

bool escribirRegistro(const string& ruta, const Registro& reg, long posicion) {
    fstream archivo(ruta, ios::binary | ios::in | ios::out);
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo " << ruta << "." << endl;
        return false;
    }
    
    archivo.seekp(posicion);
    archivo.write((const char*)&reg, sizeof(Registro));
    archivo.close();
    
    return true;
}

Registro leerRegistro(const string& ruta, long posicion) {
    Registro reg;
    crearRegistroVacio(reg);
    
    ifstream archivo(ruta, ios::binary);
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo " << ruta << "." << endl;
        return reg;
    }
    
    archivo.seekg(posicion);
    archivo.read((char*)&reg, sizeof(Registro));
    archivo.close();
    
    return reg;
}

long obtenerTamanoArchivo(const string& ruta) {
    ifstream archivo(ruta, ios::binary | ios::ate);
    if (!archivo.is_open()) {
        return 0;
    }
    
    long tamaño = archivo.tellg();
    archivo.close();
    
    return tamaño;
}

int contarRegistrosBinario(const string& ruta) {
    long tamaño = obtenerTamanoArchivo(ruta);
    if (tamaño == 0) return 0;
    
    return tamaño / sizeof(Registro);
}
