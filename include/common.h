#ifndef COMMON_H
#define COMMON_H

#include <string>
using namespace std;

// ============================================
// RUTAS DE ARCHIVOS
// ============================================
const string CSV_PATH = "datos/censo.csv";
const string BIN_PATH = "datos/censo.bin";
const string INDEX_PATH = "datos/indice.bin";
const string REPORT_PATH = "datos/reporte.txt";

// ============================================
// TAMAÑOS MÁXIMOS DE CAMPOS
// ============================================
const int MAX_DEPARTAMENTO = 30;
const int MAX_MUNICIPIO = 30;
const int MAX_SEXO = 15;
const int MAX_GRUPO = 20;

// ============================================
// CONFIGURACIÓN DEL SISTEMA
// ============================================
const int BUFFER_SIZE = 4096;
const int PREVIEW_LINES = 10;

#endif
