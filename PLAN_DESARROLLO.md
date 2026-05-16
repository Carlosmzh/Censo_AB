# PLAN DE DESARROLLO COMPLETO
## Sistema de Procesamiento de Población - CENSO 2024

---

## 1. ANÁLISIS GENERAL DEL PROYECTO

### 1.1 Objetivo del Sistema
Desarrollar un programa en C++ que procese datos del censo 2024, permitiendo:
- Cargar datos desde CSV
- Convertir a formato binario para acceso eficiente
- Crear índices para búsquedas rápidas
- Ordenar registros usando Merge Sort
- Generar reportes con sumatorias por departamento/municipio/sexo

### 1.2 Problema Detectado con los Datos
**CRÍTICO**: El archivo `datos.csv` proporcionado NO es un CSV válido.
- Actualmente tiene extensión `.csv` pero es un archivo **XLSX** (Excel)
- Comienza con firma "PK" (formato ZIP de Excel moderno)
- **Acción requerida**: Convertir el XLSX original a CSV manualmente

### 1.3 Flujo de Datos del Sistema
```
[XLSX Original] → (Convertir manualmente) → [censo.csv]
                                                ↓
                                        [censo.bin]
                                                ↓
                              ┌─────────────────┴─────────────────┐
                              ↓                                   ↓
                      [indice.bin]                         [registros ordenados]
                              ↓                                   ↓
                      [Búsquedas]                        [reporte.txt]
```

---

## 2. ESTRUCTURA DEL PROYECTO

### 2.1 Directorios y Archivos

```
CENSO/
├── src/                          # Código fuente (.cpp)
│   ├── main.cpp                 # Punto de entrada y menú
│   ├── csv_reader.cpp           # Lectura y parsing de CSV
│   ├── binary_file.cpp          # Lectura/escritura binaria
│   ├── index_manager.cpp        # Creación y gestión de índices
│   ├── merge_sort.cpp           # Algoritmo de ordenamiento
│   ├── reports.cpp              # Generación de reportes
│   └── utilities.cpp            # Funciones auxiliares
│
├── include/                      # Cabeceras (.h)
│   ├── common.h                 # Constantes y configuraciones
│   ├── registro.h              # Struct Registro y validaciones
│   ├── indice.h                # Struct Indice y funciones
│   ├── csv_reader.h
│   ├── binary_file.h
│   ├── index_manager.h
│   ├── merge_sort.h
│   ├── reports.h
│   └── utilities.h
│
├── datos/                        # Archivos de datos
│   ├── censo.csv               # INPUT: Datos del censo (convertir de XLSX)
│   ├── censo.bin               # OUTPUT: Archivo binario con registros
│   ├── indice.bin              # OUTPUT: Índice para búsquedas rápidas
│   └── reporte.txt             # OUTPUT: Reporte de sumatorias
│
├── docs/                         # Documentación técnica
│   └── casos_prueba.md         # Casos de prueba y validación
│
├── build/                        # Archivos de compilación (generado)
│
├── Makefile                      # Archivo de compilación
├── compile.bat                   # Script de compilación (Windows)
└── README.md                     # Guía de uso del proyecto
```

---

## 3. ESPECIFICACIONES TÉCNICAS

### 3.1 Estructura de Datos - Registro

```cpp
struct Registro {
    int id;                      // Identificador único (4 bytes)
    char departamento[30];       // Nombre del departamento (30 bytes)
    char municipio[30];          // Nombre del municipio (30 bytes)
    char sexo[15];              // "Hombre" o "Mujer" (15 bytes)
    char grupoEtario[20];       // Grupo de edad (20 bytes)
    int poblacion;              // Cantidad de personas (4 bytes)
};
// Tamaño total: 103 bytes por registro
```

### 3.2 Estructura de Datos - Índice

```cpp
struct Indice {
    int id;                      // ID del registro (4 bytes)
    long posicion;               // Posición en bytes en census.bin (8 bytes)
};
// Tamaño total: 12 bytes por entrada de índice
```

### 3.3 Constantes del Sistema

```cpp
// En include/common.h
const string CSV_PATH = "datos/censo.csv";
const string BIN_PATH = "datos/censo.bin";
const string INDEX_PATH = "datos/indice.bin";
const string REPORT_PATH = "datos/reporte.txt";

const int MAX_DEPARTAMENTO = 30;
const int MAX_MUNICIPIO = 30;
const int MAX_SEXO = 15;
const int MAX_GRUPO = 20;
const int BUFFER_SIZE = 4096;
```

---

## 4. MÓDULOS DEL SISTEMA

### 4.1 Módulo: CSV Reader (csv_reader.cpp/h)

**Responsabilidad**: Leer y parsear archivos CSV

**Funciones requeridas**:
```cpp
// Cargar todos los registros desde CSV
vector<Registro> cargarCSV(const string& ruta);

// Validar formato de una línea CSV
bool validarLineaCSV(const string& linea);

// Parsear una línea CSV a struct Registro
Registro parsearLinea(const string& linea, int id);

// Mostrar vista previa de los primeros N registros
void mostrarPreview(const vector<Registro>& registros, int cantidad);

// Contar líneas totales en archivo CSV
int contarLineasCSV(const string& ruta);
```

**Algoritmo de parsing**:
1. Abrir archivo con ifstream
2. Leer línea por línea usando getline()
3. Usar stringstream para separar por comas
4. Validar cantidad de campos (debe haber 5 campos)
5. Limpiar espacios en blanco
6. Convertir a struct Registro

### 4.2 Módulo: Binary File (binary_file.cpp/h)

**Responsabilidad**: Gestionar lectura/escritura de archivos binarios

**Funciones requeridas**:
```cpp
// Escribir vector de registros a archivo binario
bool escribirBinario(const string& ruta, const vector<Registro>& registros);

// Leer todos los registros desde archivo binario
vector<Registro> leerBinario(const string& ruta);

// Escribir un solo registro en posición específica
bool escribirRegistro(const string& ruta, const Registro& reg, long posicion);

// Leer un registro desde posición específica
Registro leerRegistro(const string& ruta, long posicion);

// Obtener tamaño del archivo binario
long obtenerTamanoArchivo(const string& ruta);

// Contar cantidad de registros en archivo binario
int contarRegistrosBinario(const string& ruta);
```

**Formato binario**:
- Sin headers
- Registros escritos secuencialmente
- Tamaño fijo por registro: 103 bytes

### 4.3 Módulo: Index Manager (index_manager.cpp/h)

**Responsabilidad**: Crear y mantener índices para búsquedas rápidas

**Funciones requeridas**:
```cpp
// Crear índice a partir de archivo binario
bool crearIndice(const string& binPath, const string& indexPath);

// Cargar índice en memoria
vector<Indice> cargarIndice(const string& indexPath);

// Buscar registro por ID usando índice
Registro* buscarPorId(int id, const string& binPath, const string& indexPath);

// Guardar índice a archivo
bool guardarIndice(const string& indexPath, const vector<Indice>& indice);

// Buscar posición en índice (búsqueda binaria)
long buscarPosicionEnIndice(int id, const vector<Indice>& indice);
```

**Algoritmo de creación de índice**:
1. Abrir archivo binario en modo lectura
2. Posicionarse al inicio (seekg(0))
3. Para cada registro:
   - Guardar ID
   - Guardar posición actual del archivo
   - Avanzar 103 bytes
4. Escribir vector de índices a archivo binario

### 4.4 Módulo: Merge Sort (merge_sort.cpp/h)

**Responsabilidad**: Ordenar registros por población (descendente)

**Funciones requeridas**:
```cpp
// Ordenar vector de registros por población (descendente)
void mergeSort(vector<Registro>& registros);

// Función merge: combinar dos subarrays ordenados
void merge(vector<Registro>& registros, int izquierda, int medio, int derecha);

// Ordenar archivo binario directamente
bool ordenarArchivoBinario(const string& binPath);

// Reemplazar archivo original con archivo ordenado
bool reemplazarArchivo(const string& original, const string& ordenado);
```

**Algoritmo Merge Sort**:
```
mergeSort(arr, izq, der):
    if izq < der:
        medio = (izq + der) / 2
        mergeSort(arr, izq, medio)
        mergeSort(arr, medio+1, der)
        merge(arr, izq, medio, der)

merge(arr, izq, medio, der):
    Crear arrays temporales izquierda y derecha
    Copiar datos a arrays temporales
    Comparar y mezclar en orden descendente por población
    Copiar de vuelta al array original
```

**Complejidad**: O(n log n) en todos los casos

### 4.5 Módulo: Reports (reports.cpp/h)

**Responsabilidad**: Generar reportes con sumatorias

**Funciones requeridas**:
```cpp
// Generar reporte completo con todas las sumatorias
bool generarReporte(const string& binPath, const string& reportPath);

// Sumar población por departamento y municipio
map<string, map<string, int>> sumarPorDepartamentoMunicipio(
    const vector<Registro>& registros);

// Sumar población por departamento y sexo
map<string, map<string, int>> sumarPorDepartamentoSexo(
    const vector<Registro>& registros);

// Sumar población por departamento
map<string, int> sumarPorDepartamento(
    const vector<Registro>& registros);

// Escribir sección de reporte
void escribirSeccion(ofstream& archivo, const string& titulo);

// Escribir línea de reporte con formato
void escribirLinea(ofstream& archivo, const string& clave, int valor);
```

**Estructura del reporte**:
```
===============================================
        REPORTE CENSO 2024 - BOLIVIA
===============================================

===============================================
DEPARTAMENTO: LA PAZ
===============================================

--- Por Municipio ---
Municipio: El Alto
Población Total: 850000

Municipio: La Paz
Población Total: 800000

--- Por Sexo ---
Sexo: Hombre
Total: 900000

Sexo: Mujer
Total: 750000

--- Total Departamento ---
Total La Paz: 1650000

[Repetir para cada departamento]

===============================================
RESUMEN GENERAL
===============================================
Total Nacional: [suma de todos]
```

### 4.6 Módulo: Utilities (utilities.cpp/h)

**Funciones auxiliares**:
```cpp
// Limpiar espacios en blanco de string
string trim(const string& str);

// Convertir string a entero
int stringToInt(const string& str);

// Convertir entero a string
string intToString(int num);

// Mostrar un registro formateado
void mostrarRegistro(const Registro& reg);

// Mostrar menú principal
void mostrarMenu();

// Pausar ejecución y esperar Enter
void pausar();

// Limpiar pantalla
void limpiarPantalla();
```

---

## 5. MENÚ PRINCIPAL DEL SISTEMA

```
===============================================
       SISTEMA CENSO 2024 - MENÚ PRINCIPAL
===============================================

1. Cargar archivo CSV
2. Convertir CSV a binario
3. Crear índice
4. Buscar registro por ID
5. Listar todos los registros
6. Ordenar por población (Merge Sort)
7. Generar reporte de sumatorias
8. Salir

===============================================
Seleccione una opción [1-8]:
```

### 5.1 Flujo de Uso Recomendado

```
PASO 1: Convertir XLSX → CSV manualmente
        (Abrir Excel → Guardar como → CSV)

PASO 2: Ejecutar programa

PASO 3: Opción 1 - Cargar CSV (verificar datos)

PASO 4: Opción 2 - Convertir a binario

PASO 5: Opción 3 - Crear índice

PASO 6: Opciones 4, 5 - Búsquedas y listados

PASO 7: Opción 6 - Ordenar por población

PASO 8: Opción 7 - Generar reporte final
```

---

## 6. IMPLEMENTACIÓN - DETALLE POR MÓDULO

### 6.1 Fase 1: Estructura Base (Días 1-2)

**Objetivo**: Crear estructura de directorios y archivos base

**Tareas**:
1. Crear estructura de directorios (src, include, datos, docs, build)
2. Crear common.h con constantes
3. Crear registro.h con struct y validaciones básicas
4. Crear indice.h con struct y validaciones
5. Crear Makefile o compile.bat

**Criterio de aceptación**:
- Proyecto compila sin errores
- Estructura de directorios creada

### 6.2 Fase 2: Lectura CSV (Días 3-4)

**Objetivo**: Implementar lectura de archivos CSV

**Tareas**:
1. Implementar csv_reader.h y csv_reader.cpp
2. Implementar trim() y stringToInt() en utilities
3. Probar con archivo CSV de ejemplo

**Prueba**:
- Cargar CSV y mostrar preview de 10 registros

### 6.3 Fase 3: Archivo Binario (Días 5-6)

**Objetivo**: Implementar conversión CSV → Binario

**Tareas**:
1. Implementar binary_file.h y binary_file.cpp
2. Integrar con csv_reader
3. Crear función de escritura completa

**Prueba**:
- Convertir CSV a binario
- Verificar tamaño de archivo (n_registros * 103 bytes)

### 6.4 Fase 4: Índice (Días 7-8)

**Objetivo**: Implementar sistema de índices

**Tareas**:
1. Implementar index_manager.h y index_manager.cpp
2. Crear función de búsqueda binaria
3. Integrar lectura de binario con índice

**Prueba**:
- Crear índice
- Buscar registro por ID y verificar datos

### 6.5 Fase 5: Merge Sort (Días 9-10)

**Objetivo**: Implementar ordenamiento

**Tareas**:
1. Implementar merge_sort.h y merge_sort.cpp
2. Implementar merge y mergeSort
3. Ordenar archivo binario

**Prueba**:
- Ordenar por población (descendente)
- Verificar que está ordenado correctamente

### 6.6 Fase 6: Reportes (Días 11-12)

**Objetivo**: Generar reportes de sumatorias

**Tareas**:
1. Implementar reports.h y reports.cpp
2. Implementar grouping por departamento/municipio/sexo
3. Generar archivo TXT formateado

**Prueba**:
- Generar reporte completo
- Verificar sumas correcto

### 6.7 Fase 7: Integración y Testing (Días 13-14)

**Objetivo**: Integrar todo y probar

**Tareas**:
1. Conectar main.cpp con todos los módulos
2. Probar flujo completo
3. Manejar errores y edge cases
4. Crear documentación

**Prueba final**:
- Ejecutar todas las opciones del menú
- Verificar que todo funciona correctamente

---

## 7. CASOS DE PRUEBA

### 7.1 Datos de Prueba (CSV de ejemplo)

```csv
id,departamento,municipio,sexo,grupo_etario,poblacion
1,La Paz,El Alto,Hombre,0-14,150000
2,La Paz,El Alto,Mujer,0-14,145000
3,La Paz,El Alto,Hombre,15-64,250000
4,La Paz,El Alto,Mujer,15-64,255000
5,La Paz,La Paz,Hombre,0-14,80000
6,La Paz,La Paz,Mujer,0-14,75000
7,La Paz,La Paz,Hombre,15-64,200000
8,La Paz,La Paz,Mujer,15-64,195000
9,Santa Cruz,Santa Cruz de la Sierra,Hombre,0-14,200000
10,Santa Cruz,Santa Cruz de la Sierra,Mujer,0-14,190000
11,Cochabamba,Cochabamba,Hombre,0-14,120000
12,Cochabamba,Cochabamba,Mujer,0-14,115000
```

### 7.2 Casos de Prueba Esperados

| Caso | Descripción | Resultado esperado |
|------|-------------|---------------------|
| CP-01 | Cargar CSV vacío | Mostrar error "Archivo no encontrado" |
| CP-02 | Cargar CSV válido | Mostrar preview de 10 registros |
| CP-03 | Convertir CSV a binario | Crear census.bin con tamaño correcto |
| CP-04 | Crear índice | Crear indice.bin con N entradas |
| CP-05 | Buscar ID existente | Mostrar registro encontrado |
| CP-06 | Buscar ID no existente | Mostrar "Registro no encontrado" |
| CP-07 | Listar registros | Mostrar todos los registros |
| CP-08 | Ordenar por población | Archivo ordenado descendente |
| CP-09 | Generar reporte | Archivo reporte.txt con sumas correctas |
| CP-10 | Datos inválidos en CSV | Ignorar línea y continuar |

---

## 8. ERRORES COMUNES Y SOLUCIONES

### 8.1 Problemas de Lectura CSV
- **Problema**: Líneas con comas dentro de campos
- **Solución**: Usar parsing robusto o verificar comillas

### 8.2 Problemas de Binario
- **Problema**: Tamaño de struct diferente en memoria
- **Solución**: Usar `pragma pack(1)` o campos de tamaño fijo con arrays

### 8.3 Problemas de Índice
- **Problema**: Índice desactualizado después de ordenamiento
- **Solución**: Recrear índice después de cada ordenamiento

### 8.4 Problemas de Memoria
- **Problema**: Archivos muy grandes no caben en memoria
- **Solución**: Procesar en chunks o usar ordenamiento externo

---

## 9. COMPILACIÓN Y EJECUCIÓN

### 9.1 En Windows con g++

```batch
compile.bat:
@echo off
g++ -std=c++17 -Wall -Wextra -I include -o build/app.exe src\*.cpp
if %errorlevel% equ 0 (
    echo Compilacion exitosa!
    build\app.exe
) else (
    echo Error en compilacion
)
```

### 9.2 En Linux/Mac con g++

```bash
Makefile:
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I include
TARGET = build/app
SRC = src/*.cpp

$(TARGET): $(SRC)
    $(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
    ./$(TARGET)

clean:
    rm -f $(TARGET)
```

---

## 10. CHECKLIST DE IMPLEMENTACIÓN

- [ ] Estructura de directorios creada
- [ ] common.h implementado
- [ ] registro.h/.cpp implementado
- [ ] indice.h/.cpp implementado
- [ ] csv_reader.h/.cpp implementado
- [ ] binary_file.h/.cpp implementado
- [ ] index_manager.h/.cpp implementado
- [ ] merge_sort.h/.cpp implementado
- [ ] reports.h/.cpp implementado
- [ ] utilities.h/.cpp implementado
- [ ] main.cpp con menú implementado
- [ ] Makefile/compile.bat creado
- [ ] Pruebas de todas las funciones
- [ ] Documentación completa

---

## 11. NOTAS IMPORTANTES

1. **El archivo datos.csv debe convertirse de XLSX a CSV primero**
2. **El tamaño del struct Registro debe ser exactamente 103 bytes**
3. **Usar mode binary (ios::binary) para archivos binarios**
4. **El índice debe recrearse después de ordenar**
5. **Validar entrada del usuario en todo momento**
6. **Manejar errores gracefully (no crashes)**

---

*Documento generado para desarrollo del proyecto CENSO 2024*
*Lenguaje: C++ | Entorno: Consola*