#include "reports.h"
#include "binary_file.h"
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

// ============================================
// IMPLEMENTACIÓN - REPORTES
// ============================================

map<string, map<string, int>> sumarPorDepartamentoMunicipio(const vector<Registro>& registros) {
    map<string, map<string, int>> sumas;
    
    for (const auto& reg : registros) {
        string dept = reg.departamento;
        string mun = reg.municipio;
        sumas[dept][mun] += reg.poblacion;
    }
    
    return sumas;
}

map<string, map<string, int>> sumarPorDepartamentoSexo(const vector<Registro>& registros) {
    map<string, map<string, int>> sumas;
    
    for (const auto& reg : registros) {
        string dept = reg.departamento;
        string sexo = reg.sexo;
        sumas[dept][sexo] += reg.poblacion;
    }
    
    return sumas;
}

map<string, int> sumarPorDepartamento(const vector<Registro>& registros) {
    map<string, int> sumas;
    
    for (const auto& reg : registros) {
        string dept = reg.departamento;
        sumas[dept] += reg.poblacion;
    }
    
    return sumas;
}

bool generarReporte(const string& binPath, const string& reportPath) {
    cout << "\nCargando archivo binario para generar reporte..." << endl;
    vector<Registro> registros = leerBinario(binPath);
    
    if (registros.empty()) {
        cerr << "Error: No hay registros para generar el reporte." << endl;
        return false;
    }
    
    ofstream reporte(reportPath);
    if (!reporte.is_open()) {
        cerr << "Error: No se pudo crear el archivo de reporte " << reportPath << "." << endl;
        return false;
    }
    
    // Encabezado
    reporte << "================================================\n";
    reporte << "        REPORTE CENSO 2024 - BOLIVIA\n";
    reporte << "================================================\n\n";
    
    // Obtener datos por departamento
    auto sumDept = sumarPorDepartamento(registros);
    auto sumDeptMun = sumarPorDepartamentoMunicipio(registros);
    auto sumDeptSexo = sumarPorDepartamentoSexo(registros);
    
    long totalNacional = 0;
    
    // Por cada departamento
    for (const auto& [dept, totalDept] : sumDept) {
        totalNacional += totalDept;
        
        reporte << "================================================\n";
        reporte << "DEPARTAMENTO: " << dept << "\n";
        reporte << "================================================\n\n";
        
        // Por municipio
        reporte << "--- Por Municipio ---\n";
        if (sumDeptMun.find(dept) != sumDeptMun.end()) {
            for (const auto& [mun, poblacion] : sumDeptMun[dept]) {
                reporte << "Municipio: " << mun << "\n";
                reporte << "Población Total: " << poblacion << "\n\n";
            }
        }
        
        // Por sexo
        reporte << "--- Por Sexo ---\n";
        if (sumDeptSexo.find(dept) != sumDeptSexo.end()) {
            for (const auto& [sexo, poblacion] : sumDeptSexo[dept]) {
                reporte << "Sexo: " << sexo << "\n";
                reporte << "Total: " << poblacion << "\n\n";
            }
        }
        
        // Total departamento
        reporte << "--- Total Departamento ---\n";
        reporte << "Total " << dept << ": " << totalDept << "\n";
        reporte << "\n";
    }
    
    // Resumen general
    reporte << "================================================\n";
    reporte << "RESUMEN GENERAL\n";
    reporte << "================================================\n";
    reporte << "Total Nacional: " << totalNacional << "\n";
    reporte << "Registros Procesados: " << registros.size() << "\n";
    
    reporte.close();
    
    cout << "Reporte generado exitosamente en " << reportPath << endl;
    cout << "Total Nacional: " << totalNacional << endl;
    
    return true;
}
