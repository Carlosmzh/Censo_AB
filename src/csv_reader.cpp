#include "csv_reader.h"
#include "utilities.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>

using namespace std;

// ============================================
// IMPLEMENTACIÓN - LECTURA CSV
// ============================================

bool validarLineaCSV(const string& linea) {
    int commas = 0;
    for (char c : linea) {
        if (c == ',') commas++;
    }
    return commas == 4;  // Debe haber exactamente 4 comas (5 campos)
}

Registro parsearLinea(const string& linea, int id) {
    Registro reg;
    crearRegistroVacio(reg);
    
    reg.id = id;
    
    stringstream ss(linea);
    string field;
    int fieldNum = 0;
    
    while (getline(ss, field, ',') && fieldNum < 5) {
        field = trim(field);
        
        switch (fieldNum) {
            case 0:  // departamento
                strncpy(reg.departamento, field.c_str(), MAX_DEPARTAMENTO - 1);
                break;
            case 1:  // municipio
                strncpy(reg.municipio, field.c_str(), MAX_MUNICIPIO - 1);
                break;
            case 2:  // sexo
                strncpy(reg.sexo, field.c_str(), MAX_SEXO - 1);
                break;
            case 3:  // grupoEtario
                strncpy(reg.grupoEtario, field.c_str(), MAX_GRUPO - 1);
                break;
            case 4:  // poblacion
                reg.poblacion = stringToInt(field);
                break;
        }
        fieldNum++;
    }
    
    return reg;
}

int contarLineasCSV(const string& ruta) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        return 0;
    }
    
    int lineas = 0;
    string linea;
    
    while (getline(archivo, linea)) {
        lineas++;
    }
    
    archivo.close();
    return lineas;
}

vector<Registro> cargarCSV(const string& ruta) {
    vector<Registro> registros;
    
    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo " << ruta << endl;
        return registros;
    }
    
    string linea;
    int id = 1;
    int lineaNum = 0;
    
    // Saltar encabezado
    getline(archivo, linea);
    lineaNum++;
    
    while (getline(archivo, linea)) {
        lineaNum++;
        
        // Ignorar líneas vacías
        if (trim(linea).empty()) continue;
        
        // Validar formato
        if (!validarLineaCSV(linea)) {
            cerr << "Advertencia: Línea " << lineaNum << " tiene formato incorrecto, ignorando." << endl;
            continue;
        }
        
        Registro reg = parsearLinea(linea, id);
        
        // Validar registro
        if (!esRegistroValido(reg)) {
            cerr << "Advertencia: Línea " << lineaNum << " contiene datos inválidos, ignorando." << endl;
            continue;
        }
        
        registros.push_back(reg);
        id++;
    }
    
    archivo.close();
    
    cout << "\nSe cargaron " << registros.size() << " registros del archivo CSV." << endl;
    
    return registros;
}

void mostrarPreview(const vector<Registro>& registros, int cantidad) {
    if (registros.empty()) {
        cout << "No hay registros para mostrar." << endl;
        return;
    }
    
    int mostrar = (cantidad > registros.size()) ? registros.size() : cantidad;
    
    cout << "\n";
    cout << "===============================================\n";
    cout << "VISTA PREVIA DE REGISTROS (Primeros " << mostrar << ")\n";
    cout << "===============================================\n";
    
    for (int i = 0; i < mostrar; i++) {
        mostrarRegistro(registros[i]);
    }
    
    cout << "Total de registros cargados: " << registros.size() << endl;
}
