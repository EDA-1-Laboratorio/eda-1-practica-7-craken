[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/x3N5ta_J)
[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-2e0aaae1b6195c2367325f4f02e2d04e9abb55f0b24a779b69b11b9e10269abc.svg)](https://classroom.github.com/online_ide?assignment_repo_id=23314076&assignment_repo_type=AssignmentRepo)
# EDA I - Práctica 7. Listas

## Ejercicio 1. Sistema de Logs de Errores

### Descripción

Se simula un sistema que recibe **logs de errores** durante un período de tiempo. Cada error que llega al sistema tiene las siguientes características:

- **ID**: una cadena que comienza con una letra mayúscula (`A`–`Z`) seguida de 4 dígitos (e.g. `C0472`, `M8301`).
- **Prioridad**: un valor `float` entre `0.0` y `10.0` que indica la urgencia del error dentro de su categoría.
- **Tipo de error**:
  - Si la letra inicial está entre **A y E**, el error se clasifica como **CRÍTICO**.
  - Si la letra inicial está entre **F y Z**, el error se clasifica como **no crítico**.

Los errores se generan de forma aleatoria y llegan uno a uno. Tu tarea es almacenarlos en una **lista simple enlazada** manteniéndola **ordenada** en todo momento.

### Criterio de ordenamiento

La lista debe estar ordenada bajo el siguiente criterio (de mayor a menor importancia):

1. **Letra inicial del ID** — orden alfabético ascendente (`A` antes que `B`, `B` antes que `C`, etc.).
2. **Prioridad numérica** — cuando dos errores comparten la misma letra inicial, el de **mayor prioridad** va primero (orden descendente).

#### Ejemplo

| # | ID     | Prioridad | Tipo    |
|---|--------|-----------|---------|
| 1 | A8139  | 8.51      | CRITICO |
| 2 | A9308  | 5.70      | CRITICO |
| 3 | B2851  | 6.68      | CRITICO |
| 4 | E0769  | 4.63      | CRITICO |
| 5 | E8188  | 1.51      | CRITICO |
| 6 | F6386  | 1.81      | normal  |
| 7 | H5261  | 9.30      | normal  |
| 8 | N6726  | 7.28      | normal  |

Observa que los errores con letra `A` van primero, ordenados por prioridad de mayor a menor (8.51 > 5.70). Los de letra `E` le siguen a los de letra `B`, etc.

### Estructura de datos

La estructura `ErrorLog` está definida en `error_log.h`:

```c
typedef struct error_log {
    char id[MAX_ID];         /* ID del error, inicia con una letra */
    float prioridad;         /* Prioridad numérica dentro de su categoría */
    int es_critico;          /* 1 si la letra inicial es A-E, 0 en otro caso */
    struct error_log *sig;   /* Puntero al siguiente nodo */
} ErrorLog;
```

### Archivos proporcionados

| Archivo           | Descripción |
|-------------------|-------------|
| `error_log.h`     | Header con la definición de la estructura y prototipos de funciones. |
| `practica_logs.c` | Archivo principal. Contiene el `main`, las funciones auxiliares ya implementadas, y los **stubs vacíos** de las funciones que debes completar. |

### Funciones a implementar

Debes completar las siguientes 5 funciones en `practica_logs.c`:

#### 1. `void insertar_ordenado(ErrorLog **cabeza, ErrorLog *nuevo)`

Inserta el nodo `nuevo` en la lista apuntada por `*cabeza` de forma que la lista se mantenga ordenada según el criterio descrito arriba.

**Pistas:**
- Recorre la lista buscando la posición correcta de inserción.
- Necesitarás un puntero al nodo anterior para reconectar los enlaces.
- Considera los casos especiales: lista vacía y cuando el nuevo nodo va al inicio.

#### 2. `int contar_criticos(ErrorLog *cabeza)`

Recorre la lista y retorna el número de errores cuyo campo `es_critico` sea `1`.

#### 3. `int contar_no_criticos(ErrorLog *cabeza)`

Recorre la lista y retorna el número de errores cuyo campo `es_critico` sea `0`.

#### 4. `ErrorLog *eliminar_por_prioridad(ErrorLog *cabeza, float umbral)`

Elimina de la lista todos los nodos cuya prioridad sea **estrictamente menor** que `umbral`. Debe liberar la memoria de cada nodo eliminado con `free()`. Retorna la nueva cabeza de la lista (que puede cambiar si se eliminan nodos al inicio).

**Pistas:**
- Ten cuidado al eliminar nodos al inicio de la lista.
- Al eliminar un nodo intermedio, debes reconectar el nodo anterior con el nodo siguiente.
- No olvides liberar la memoria del nodo eliminado.

#### 5. `ErrorLog *conservar_mayor_no_critico(ErrorLog *cabeza)`

Conserva **todos los errores críticos** (A-E) y **únicamente el error no crítico con la mayor prioridad numérica**. Elimina y libera todos los demás errores no críticos. Retorna la nueva cabeza de la lista.

**Pistas:**
- Primero recorre la lista para identificar cuál es el nodo no crítico con mayor prioridad.
- Luego recorre la lista una segunda vez eliminando todos los nodos no críticos que no sean ese nodo.
- Recuerda liberar la memoria de cada nodo eliminado.
- Si no hay errores no críticos, la lista no cambia.

### Compilación y ejecución

```bash
gcc -o practica_logs practica_logs.c -lm
./practica_logs
```

### Salida esperada

Al ejecutar el programa, deberás ver algo similar a:

```
=== SISTEMA DE LOGS DE ERRORES ===
Simulando recepcion de 17 errores...

  Recibido: [N6726] prioridad=7.28 (normal)
  Recibido: [A9308] prioridad=5.70 (CRITICO)
  ...

=== LISTA ORDENADA DE ERRORES ===
#    ID         Prioridad  Tipo
--------------------------------------
1    A8139      8.51       CRITICO
2    A9308      5.70       CRITICO
3    B2851      6.68       CRITICO
...
--------------------------------------

Estadisticas:
  Errores criticos    (A-E): 5
  Errores no criticos (F-Z): 12
  Total:                     17

=== ELIMINANDO ERRORES CON PRIORIDAD < 3.0 ===

=== LISTA DESPUES DEL FILTRADO ===
#    ID         Prioridad  Tipo
--------------------------------------
1    A8139      8.51       CRITICO
2    A9308      5.70       CRITICO
...
--------------------------------------

Estadisticas post-filtrado:
  Errores criticos    (A-E): 4
  Errores no criticos (F-Z): 7

=== CONSERVANDO SOLO EL MAYOR ERROR NO CRITICO ===

=== LISTA FINAL ===
#    ID         Prioridad  Tipo
--------------------------------------
1    A8139      8.51       CRITICO
2    A9308      5.70       CRITICO
3    B2851      6.68       CRITICO
4    E0769      4.63       CRITICO
5    H5261      9.30       normal
--------------------------------------

Estadisticas finales:
  Errores criticos    (A-E): 4
  Errores no criticos (F-Z): 1
```

### Puntos a evaluar

- Inserción ordenada correcta (letra + prioridad).
- Conteo correcto de errores críticos y no críticos.
- Eliminación correcta de nodos por umbral de prioridad, sin fugas de memoria.
- Conservación correcta del único error no crítico de mayor prioridad, eliminando los demás.
- El programa compila sin errores ni warnings.

### Reporte
En el reporte, además del código, den una descripción de las funciones que definieron.


## Ejercicio 2: Arrakis Kernel: El Ciclo de Shai-Hulud

### Descripción

Simularás la supervivencia de las **Grandes Casas** en el desierto de **Dune**. Los asentamientos fortificados forman un **anillo** (lista circular simple) y un gusano de arena — **Shai-Hulud** — recorre el anillo devorando soldados turno a turno.

Tu tarea es implementar las operaciones fundamentales sobre la lista circular que hacen funcionar la simulación.

### Estructura de datos

Cada nodo del anillo representa un asentamiento. La estructura `Casa` está definida en `arrakis.h`:

```c
typedef struct casa {
    char nombre[30];       /* Nombre de la casa (Atreides, Harkonnen, ...) */
    int soldados;          /* Cantidad de soldados (inicial: 500) */
    int especia;           /* Especia acumulada (inicial: 0) */
    struct casa *siguiente; /* Puntero al siguiente asentamiento */
} Casa;
```

El **último nodo** del anillo apunta de vuelta al **primero**, formando un ciclo.

### Reglas del desierto

#### A. El avance de Shai-Hulud

Cada turno se lanza un **dado** (número aleatorio de 1 a 6). El puntero del gusano avanza esa cantidad de nodos a través del anillo.

> Como la lista es circular, si el dado es 6 y solo quedan 3 casas, el gusano dará dos vueltas completas.

#### B. El ataque del gusano

Al detenerse en una casa:

- **Daño:** se reduce el **20%** de los soldados actuales de esa casa.
- **Cosecha:** todas las casas que **no** fueron atacadas incrementan su especia en **+10** unidades.

#### C. La caída de una casa (borrado)

Si una casa queda con **menos de 50 soldados**, es consumida por el desierto:

- Se debe **eliminar el nodo** del anillo circular, encontrando el nodo anterior para reconectar el ciclo.
- **Caso especial:** si solo queda una casa, su puntero `siguiente` debe apuntar a sí misma (o el anillo queda vacío si esa casa también cae).

#### D. Refuerzos de la Cofradía Espacial (Boss Final)

Si una casa acumula **200 o más unidades de especia**, puede invocar refuerzos:

- Se inserta un **nuevo nodo** (con el mismo nombre + " II") **justo antes** del nodo actual en el anillo.
- El nuevo asentamiento tiene **250 soldados** y **0 especia**.
- Se descuenta toda la especia de la casa que invocó los refuerzos.
- Esto requiere recorrer el anillo para encontrar quién apunta al nodo actual.

### Archivos proporcionados

| Archivo      | Descripción |
|--------------|-------------|
| `arrakis.h`  | Header con la estructura `Casa`, constantes y prototipos. |
| `arrakis.c`  | Archivo principal con funciones auxiliares y stubs vacíos. |

### Funciones a implementar

Debes completar las siguientes 4 funciones en `arrakis.c`:

#### 1. `void insertar_casa(Casa **anillo, Casa *nueva)`

Inserta un nodo al **final** del anillo circular.

- Si `*anillo == NULL`: el nuevo nodo apunta a sí mismo y se convierte en el anillo.
- Si ya hay nodos: insertar `nueva` justo antes de `*anillo` (al "final" del ciclo). `*anillo` no cambia.

**Pistas:**
- Necesitas encontrar el último nodo (el que apunta a `*anillo`) para reconectar.
- Después de insertar: `ultimo->siguiente = nueva` y `nueva->siguiente = *anillo`.

#### 2. `Casa *avanzar_gusano(Casa *actual, int pasos)`

Avanza `pasos` posiciones en la lista circular desde `actual`. Retorna el nodo donde se detiene.

**Pista:** Es un recorrido simple con un ciclo `for`.

#### 3. `int atacar_asentamiento(Casa **gusano, Casa **anillo)`

Aplica el ataque del gusano al nodo `*gusano`:

1. Reducir soldados: `soldados -= soldados * 20 / 100`.
2. Todas las **demás** casas del anillo ganan `+10` de especia.
3. Si `soldados < 50`:
   - Encontrar el nodo anterior (el que apunta a `*gusano`).
   - Reconectar: `anterior->siguiente = (*gusano)->siguiente`.
   - Si `*gusano == *anillo`, actualizar `*anillo`.
   - Si es la **última casa** (apunta a sí misma), ambos punteros quedan `NULL`.
   - Mover `*gusano` al siguiente **antes** de liberar la memoria.
   - Retornar `1`.
4. Si sobrevive, retornar `0`.

**Pistas:**
- Cuidado con el caso de una sola casa en el anillo.
- No olvides liberar la memoria del nodo eliminado.

#### 4. `int invocar_refuerzos(Casa *actual, Casa **anillo)` *(Boss Final)*

Si `actual->especia >= 200`:

1. Crear un nuevo nodo con nombre `"NombreActual II"`, 250 soldados, 0 especia.
2. Insertar el nuevo nodo **justo antes** de `actual` en el anillo.
3. Poner `actual->especia = 0`.
4. Retornar `1`.

Si no tiene suficiente especia, retornar `0`.

**Pista:** Debes recorrer todo el anillo para encontrar quién apunta a `actual` y reconectar.

### Anillo inicial

La simulación comienza con 6 casas:

```
Atreides -> Harkonnen -> Fremen -> Corrino -> Ordos -> Tleilaxu -> (Atreides)
```

Cada una con **500 soldados** y **0 especia**.

### Compilación y ejecución

```bash
gcc -o arrakis arrakis.c -lm
./arrakis
```

### Salida esperada (ejemplo)

```
==========================================================
   ARRAKIS KERNEL - El Ciclo de Shai-Hulud
==========================================================

>>> Estado inicial del anillo:
  #    Casa                      Soldados     Especia
  -------------------------------------------------------
  1    Atreides                  500          0
  2    Harkonnen                 500          0
  3    Fremen                    500          0
  4    Corrino                   500          0
  5    Ordos                     500          0
  6    Tleilaxu                  500          0
  -------------------------------------------------------

--- TURNO 1 ---
  Dado: 4 -> Shai-Hulud se detiene en: Ordos

  Estado del anillo (6 casas):
  #    Casa                      Soldados     Especia
  -------------------------------------------------------
  1    Atreides                  500          10
  2    Harkonnen                 500          10
  3    Fremen                    500          10
  4    Corrino                   500          10
  5    Ordos                     400          0
  6    Tleilaxu                  500          10
  -------------------------------------------------------

...

==========================================================
  VICTORIA: Fremen domina Arrakis!
==========================================================
```

### Puntos a evaluar

- Construcción correcta del anillo circular (el último apunta al primero).
- Avance del gusano respetando la circularidad.
- Ataque con reducción de soldados y cosecha de especia.
- Eliminación correcta de nodos del anillo, sin fugas de memoria.
- Inserción de refuerzos "antes" de un nodo dado en el anillo circular.
- El programa compila sin errores ni warnings.


### Reporte
En el reporte, además del código, den una descripción de las funciones que definieron.
