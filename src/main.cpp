#include <iostream>
#include <vector>
#include <cstring>
#include "utilities.h"
#include "csv_reader.h"
#include "binary_file.h"
#include "index_manager.h"
#include "merge_sort.h"
#include "reports.h"
#include "common.h"

using namespace std;

vector<Registro> registrosCargados;
bool csvCargado = false;
bool binarioCargado = false;
bool indiceCreado = false;

void opcion1() {
    cout << "\n================================================\n";
    cout << "1. CARGAR ARCHIVO CSV\n";
    cout << "================================================\n";
    
    if (!archivoExiste(CSV_PATH)) {
        cerr << "\nError: El archivo " << CSV_PATH << " no existe." << endl;
        cerr << "Por favor, convierta primero el XLSX a CSV y colóquelo en la carpeta 'datos'." << endl;
        pausar();
        return;
    }
    
    registrosCargados = cargarCSV(CSV_PATH);
    csvCargado = !registrosCargados.empty();
    
    if (csvCargado) {
        mostrarPreview(registrosCargados, PREVIEW_LINES);
    }
    
    pausar();
}

void opcion2() {
    cout << "\n================================================\n";
    cout << "2. CONVERTIR CSV A BINARIO\n";
    cout << "================================================\n";
    
    if (!csvCargado) {
        cerr << "\nError: Primero debe cargar el archivo CSV (opción 1)." << endl;
        pausar();
        return;
    }
    
    if (escribirBinario(BIN_PATH, registrosCargados)) {
        binarioCargado = true;
    }
    
    pausar();
}

void opcion3() {
    cout << "\n================================================\n";
    cout << "3. CREAR ÍNDICE\n";
    cout << "================================================\n";
    
    if (!archivoExiste(BIN_PATH)) {
        cerr << "\nError: Primero debe convertir CSV a binario (opción 2)." << endl;
        pausar();
        return;
    }
    
    if (crearIndice(BIN_PATH, INDEX_PATH)) {
        indiceCreado = true;
    }
    
    pausar();
}

void opcion4() {
    cout << "\n================================================\n";
    cout << "4. BUSCAR REGISTRO POR ID\n";
    cout << "================================================\n";
    
    if (!indiceCreado) {
        cerr << "\nError: Primero debe crear el índice (opción 3)." << endl;
        pausar();
        return;
    }
    
    int id;
    cout << "\nIngrese el ID del registro a buscar: ";
    cin >> id;
    
    Registro* reg = buscarPorId(id, BIN_PATH, INDEX_PATH);
    
    if (reg != nullptr) {
        cout << "\n================================================\n";
        cout << "REGISTRO ENCONTRADO:\n";
        cout << "================================================\n";
        mostrarRegistro(*reg);
        delete reg;
    }
    
    pausar();
}

void opcion5() {
    cout << "\n================================================\n";
    cout << "5. LISTAR TODOS LOS REGISTROS\n";
    cout << "================================================\n";
    
    if (!archivoExiste(BIN_PATH)) {
        cerr << "\nError: Primero debe convertir CSV a binario (opción 2)." << endl;
        pausar();
        return;
    }
    
    vector<Registro> registros = leerBinario(BIN_PATH);
    
    cout << "\n";
    cout << "Total de registros: " << registros.size() << endl;
    cout << "\n";
    
    for (int i = 0; i < registros.size(); i++) {
        cout << "Registro " << (i + 1) << ":\n";
        mostrarRegistro(registros[i]);
    }
    
    pausar();
}

void opcion6() {
    cout << "\n================================================\n";
    cout << "6. ORDENAR POR POBLACIÓN (MERGE SORT)\n";
    cout << "================================================\n";
    
    if (!archivoExiste(BIN_PATH)) {
        cerr << "\nError: Primero debe convertir CSV a binario (opción 2)." << endl;
        pausar();
        return;
    }
    
    cout << "\nAdvertencia: Esta operación sobrescribirá el archivo binario." << endl;
    cout << "Los registros se ordenarán por población en orden DESCENDENTE." << endl;
    
    if (ordenarArchivoBinario(BIN_PATH)) {
        cout << "\nArchivo ordenado exitosamente." << endl;
        cout << "Nota: El índice debe recrearse (opción 3) para una búsqueda correcta." << endl;
        indiceCreado = false;
    }
    
    pausar();
}

void opcion7() {
    cout << "\n================================================\n";
    cout << "7. GENERAR REPORTE DE SUMATORIAS\n";
    cout << "================================================\n";
    
    if (!archivoExiste(BIN_PATH)) {
        cerr << "\nError: Primero debe convertir CSV a binario (opción 2)." << endl;
        pausar();
        return;
    }
    
    if (generarReporte(BIN_PATH, REPORT_PATH)) {
        cout << "\nReporte guardado en: " << REPORT_PATH << endl;
    }
    
    pausar();
}

int main() {
    setlocale(LC_ALL, "es_ES.UTF-8");
    
    int opcion;
    bool salir = false;
    
    while (!salir) {
        limpiarPantalla();
        mostrarMenu();
        cin >> opcion;
        cin.ignore();
        
        switch (opcion) {
            case 1:
                opcion1();
                break;
            case 2:
                opcion2();
                break;
            case 3:
                opcion3();
                break;
            case 4:
                opcion4();
                break;
            case 5:
                opcion5();
                break;
            case 6:
                opcion6();
                break;
            case 7:
                opcion7();
                break;
            case 8:
                salir = true;
                cout << "\n¡Hasta luego!\n" << endl;
                break;
            default:
                cerr << "Opción inválida. Por favor, seleccione una opción entre 1 y 8." << endl;
                pausar();
        }
    }
    
    return 0;
}
