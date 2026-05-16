#include "utilities.h"
#include "registro.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include <sstream>

using namespace std;

// ============================================
// IMPLEMENTACIÓN - FUNCIONES DE STRING
// ============================================

string trim(const string& str) {
    size_t inicio = str.find_first_not_of(" \t\r\n");
    if (inicio == string::npos) return "";
    
    size_t fin = str.find_last_not_of(" \t\r\n");
    return str.substr(inicio, fin - inicio + 1);
}

int stringToInt(const string& str) {
    try {
        return stoi(str);
    } catch (...) {
        return 0;
    }
}

string intToString(int num) {
    return to_string(num);
}

// ============================================
// IMPLEMENTACIÓN - FUNCIONES DE INTERFAZ
// ============================================

void mostrarMenu() {
    cout << "\n";
    cout << "===============================================\n";
    cout << "       SISTEMA CENSO 2024 - MENÚ PRINCIPAL\n";
    cout << "===============================================\n";
    cout << "\n";
    cout << "1. Cargar archivo CSV\n";
    cout << "2. Convertir CSV a binario\n";
    cout << "3. Crear índice\n";
    cout << "4. Buscar registro por ID\n";
    cout << "5. Listar todos los registros\n";
    cout << "6. Ordenar por población (Merge Sort)\n";
    cout << "7. Generar reporte de sumatorias\n";
    cout << "8. Salir\n";
    cout << "\n";
    cout << "===============================================\n";
    cout << "Seleccione una opción [1-8]: ";
}

void limpiarPantalla() {
    system("cls");
}

void pausar() {
    cout << "\nPresione ENTER para continuar...";
    cin.ignore();
    cin.get();
}

bool archivoExiste(const string& ruta) {
    ifstream archivo(ruta);
    return archivo.good();
}

// ============================================
// IMPLEMENTACIÓN - FUNCIONES DE REGISTRO
// ============================================

void mostrarRegistro(const Registro& reg) {
    cout << "\nID: " << reg.id << endl;
    cout << "Departamento: " << reg.departamento << endl;
    cout << "Municipio: " << reg.municipio << endl;
    cout << "Sexo: " << reg.sexo << endl;
    cout << "Grupo Etario: " << reg.grupoEtario << endl;
    cout << "Población: " << reg.poblacion << endl;
    cout << "-------------------------------------------\n";
}

bool esRegistroValido(const Registro& reg) {
    if (reg.id <= 0) return false;
    if (strlen(reg.departamento) == 0) return false;
    if (strlen(reg.municipio) == 0) return false;
    if (strlen(reg.sexo) == 0) return false;
    if (reg.poblacion < 0) return false;
    return true;
}

void crearRegistroVacio(Registro& reg) {
    reg.id = 0;
    memset(reg.departamento, 0, MAX_DEPARTAMENTO);
    memset(reg.municipio, 0, MAX_MUNICIPIO);
    memset(reg.sexo, 0, MAX_SEXO);
    memset(reg.grupoEtario, 0, MAX_GRUPO);
    reg.poblacion = 0;
}
