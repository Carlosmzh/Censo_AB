========================================================
PROYECTO: INE - CENSO 2024
Sistema de procesamiento de población por municipio
Lenguaje: C++
Interfaz: Consola
========================================================

OBJETIVO GENERAL
--------------------------------------------------------
Desarrollar un sistema en C++ que permita:

1. Leer datos del Censo 2024 desde un archivo CSV
   (obtenido previamente desde XLSX).
2. Convertir los registros a un archivo binario.
3. Crear índices para acceso rápido.
4. Ordenar registros usando Merge Sort.
5. Generar reportes de sumatorias.
6. Manejar todo mediante un menú en consola.

========================================================
FLUJO GENERAL DEL SISTEMA
========================================================

Archivo XLSX
    ↓
Conversión manual a CSV
    ↓
Lectura del CSV
    ↓
Conversión a archivo BINARIO
    ↓
Creación de índices
    ↓
Búsquedas rápidas
    ↓
Ordenamiento Merge Sort
    ↓
Generación de reportes TXT

========================================================
JUSTIFICACIÓN DEL USO DE CSV
========================================================

El formato original del archivo no fue especificado
claramente en el enunciado.

Por motivos de compatibilidad y simplicidad en el
procesamiento de datos con C++, el sistema utilizará
CSV como formato estándar de entrada.

El archivo XLSX será convertido previamente a CSV.

Esto permite:

- Lectura secuencial sencilla.
- Procesamiento eficiente.
- Conversión directa a binario.
- Independencia de librerías externas.

========================================================
ESTRUCTURA DEL PROYECTO
========================================================

proyecto/
│
├── main.cpp
├── lector_csv.cpp
├── binario.cpp
├── indice.cpp
├── ordenamiento.cpp
├── reportes.cpp
├── utilidades.cpp
│
├── include/
│   ├── registro.h
│   ├── indice.h
│   └── funciones.h
│
├── datos/
│   ├── censo.csv
│   ├── censo.bin
│   ├── indice.bin
│   └── reporte.txt
│
└── README.txt

========================================================
ESTRUCTURA DE DATOS
========================================================

----------------------------------------
STRUCT PRINCIPAL
----------------------------------------

struct Registro {
    int id;
    char departamento[30];
    char municipio[30];
    char sexo[15];
    char grupoEtario[20];
    int poblacion;
};

----------------------------------------
STRUCT DEL ÍNDICE
----------------------------------------

struct Indice {
    int id;
    long posicion;
};

========================================================
FUNCIONALIDADES DEL SISTEMA
========================================================

--------------------------------------------------------
1. CARGAR CSV
--------------------------------------------------------

Objetivo:
Leer el archivo CSV y mostrar una vista previa.

Proceso:
- Abrir archivo CSV.
- Leer línea por línea.
- Separar columnas.
- Convertir datos al struct Registro.

Funciones posibles:

void cargarCSV();

--------------------------------------------------------
2. CONVERTIR A BINARIO
--------------------------------------------------------

Objetivo:
Guardar todos los registros en un archivo binario.

Proceso:
- Leer registros del CSV.
- Crear archivo .bin.
- Escribir structs en binario.

Funciones posibles:

void convertirABinario();

Archivo generado:
datos/censo.bin

--------------------------------------------------------
3. CREAR ÍNDICE
--------------------------------------------------------

Objetivo:
Generar un índice para búsquedas rápidas.

Proceso:
- Leer archivo binario.
- Obtener posición de cada registro.
- Guardar:
    ID → posición byte

Funciones posibles:

void crearIndice();

Archivo generado:
datos/indice.bin

--------------------------------------------------------
4. BUSCAR REGISTRO
--------------------------------------------------------

Objetivo:
Encontrar rápidamente un registro usando el índice.

Proceso:
- Leer índice.
- Buscar ID.
- Obtener posición.
- Acceder directamente al binario.
- Mostrar registro.

Funciones posibles:

void buscarRegistro();

--------------------------------------------------------
5. LISTAR REGISTROS
--------------------------------------------------------

Objetivo:
Mostrar todos los registros almacenados.

Funciones posibles:

void listarRegistros();

--------------------------------------------------------
6. ORDENAMIENTO MERGE SORT
--------------------------------------------------------

Objetivo:
Ordenar registros por población total
en orden descendente.

Método:
Merge Sort

Criterio:
poblacion DESCENDENTE

Funciones posibles:

void mergeSort();
void merge();
void ordenarPorPoblacion();

Complejidad:

O(n log n)

--------------------------------------------------------
7. GENERAR REPORTES
--------------------------------------------------------

Objetivo:
Generar sumatorias agrupadas por:

- Departamento y municipio
- Departamento y sexo
- Departamento

Salida:
Archivo TXT

Ejemplo:

================================
DEPARTAMENTO: LA PAZ
================================

Municipio: El Alto
Población Total: 850000

Sexo: Hombre
Total: 400000

Sexo: Mujer
Total: 450000

Funciones posibles:

void generarReporte();

Archivo generado:
datos/reporte.txt

========================================================
MENÚ PRINCIPAL
========================================================

=============== MENU PRINCIPAL ===============

1. Cargar archivo CSV
2. Convertir CSV a binario
3. Crear índice
4. Buscar registro
5. Listar registros
6. Ordenar por población (Merge Sort)
7. Generar reporte TXT
8. Salir

Seleccione una opción:

========================================================
FLUJO RECOMENDADO DE USO
========================================================

PASO 1
Convertir XLSX → CSV

PASO 2
Colocar:
datos/censo.csv

PASO 3
Ejecutar programa

PASO 4
Convertir CSV → BINARIO

PASO 5
Crear índice

PASO 6
Realizar búsquedas y ordenamientos

PASO 7
Generar reporte TXT

========================================================
ARCHIVOS GENERADOS
========================================================

----------------------------------------
censo.csv
----------------------------------------

Archivo fuente en texto plano.

----------------------------------------
censo.bin
----------------------------------------

Archivo binario principal.

Contiene registros serializados.

----------------------------------------
indice.bin
----------------------------------------

Archivo de índices.

Permite acceso rápido.

----------------------------------------
reporte.txt
----------------------------------------

Archivo de reportes y sumatorias.

========================================================
ALGORITMOS IMPORTANTES
========================================================

----------------------------------------
LECTURA CSV
----------------------------------------

getline()
stringstream

----------------------------------------
ARCHIVOS BINARIOS
----------------------------------------

write()
read()
seekg()
seekp()

----------------------------------------
ORDENAMIENTO
----------------------------------------

Merge Sort

----------------------------------------
BÚSQUEDA
----------------------------------------

Búsqueda secuencial o binaria
(según implementación del índice)

========================================================
POSIBLES MEJORAS FUTURAS
========================================================

- Validación automática de CSV
- Detección automática de columnas
- Interfaz gráfica
- Índices múltiples
- Ordenamiento externo
- Soporte directo XLSX

========================================================
CONCLUSIÓN
========================================================

El sistema estará enfocado principalmente en:

- Manejo de archivos binarios
- Índices
- Ordenamiento
- Búsqueda eficiente
- Estructuras lineales

El uso de CSV simplifica la entrada de datos
sin afectar los objetivos académicos del proyecto.