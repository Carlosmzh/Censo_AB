#ifndef REGISTRO_H
#define REGISTRO_H

#include "common.h"
#include <cstring>
#include <iostream>

#pragma pack(1)
struct Registro {
    int id;                           // 4 bytes
    char departamento[MAX_DEPARTAMENTO];   // 30 bytes
    char municipio[MAX_MUNICIPIO];         // 30 bytes
    char sexo[MAX_SEXO];                   // 15 bytes
    char grupoEtario[MAX_GRUPO];          // 20 bytes
    int poblacion;                    // 4 bytes
    // Total: 103 bytes
};
#pragma pack()

// ============================================
// FUNCIONES DE VALIDACIÓN Y UTILIDAD
// ============================================

bool esRegistroValido(const Registro& reg);
void mostrarRegistro(const Registro& reg);
void crearRegistroVacio(Registro& reg);

#endif
