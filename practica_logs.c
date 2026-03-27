/*
 * PRACTICA: Lista Simple - Sistema de Logs de Errores
 * ====================================================
 *
 * Descripcion:
 *   Se simula la recepcion de logs de errores durante un periodo de tiempo.
 *   Cada error tiene un ID que comienza con una letra mayuscula (A-Z):
 *     - Letras A-E: error CRITICO
 *     - Letras F-Z: error NO CRITICO
 *   Cada error tiene ademas una prioridad numerica (float de 0.0 a 10.0).
 *
 * Objetivo:
 *   Implementar las funciones marcadas con TODO para que los errores se
 *   almacenen en una lista simple ordenada por:
 *     1. Letra inicial del ID (orden alfabetico ascendente)
 *     2. Prioridad numerica (de mayor a menor) cuando la letra es la misma
 *
 * Compilacion:
 *   gcc -o practica_logs practica_logs.c -lm
 *
 * Ejecucion:
 *   ./practica_logs
 */

#include "error_log.h"

/* =====================================================================
 * FUNCIONES PROPORCIONADAS (no modificar)
 * =====================================================================*/

ErrorLog *generar_error_aleatorio(void)
{
    ErrorLog *nuevo = (ErrorLog *)malloc(sizeof(ErrorLog));
    if (!nuevo) {
        fprintf(stderr, "Error: no se pudo asignar memoria.\n");
        exit(EXIT_FAILURE);
    }

    char letra = 'A' + (rand() % 26);
    int numero = rand() % 10000;
    sprintf(nuevo->id, "%c%04d", letra, numero);

    nuevo->prioridad = (float)(rand() % 1001) / 100.0f;  /* 0.00 - 10.00 */
    nuevo->es_critico = (letra <= UMBRAL_CRITICO) ? 1 : 0;
    nuevo->sig = NULL;

    return nuevo;
}

void imprimir_lista(ErrorLog *cabeza)
{
    ErrorLog *actual = cabeza;
    int i = 1;

    printf("\n%-4s %-10s %-10s %-10s\n", "#", "ID", "Prioridad", "Tipo");
    printf("--------------------------------------\n");

    while (actual != NULL) {
        printf("%-4d %-10s %-10.2f %-10s\n",
               i++,
               actual->id,
               actual->prioridad,
               actual->es_critico ? "CRITICO" : "normal");
        actual = actual->sig;
    }
    printf("--------------------------------------\n");
}

void liberar_lista(ErrorLog *cabeza)
{
    ErrorLog *tmp;
    while (cabeza != NULL) {
        tmp = cabeza;
        cabeza = cabeza->sig;
        free(tmp);
    }
}

/* =====================================================================
 * FUNCIONES A IMPLEMENTAR
 * =====================================================================*/

/*
 * TODO: Implementar insertar_ordenado
 *
 * Inserta 'nuevo' en la lista apuntada por *cabeza de forma que la lista
 * se mantenga ordenada:
 *   - Primero por la letra inicial del ID (A < B < C < ...)
 *   - Si dos errores comparten la misma letra, el de MAYOR prioridad
 *     va primero.
 *
 * Pista: recorre la lista buscando la posicion correcta. Necesitaras un
 * puntero al nodo anterior para reconectar los enlaces.
 */
void insertar_ordenado(ErrorLog **cabeza, ErrorLog *nuevo)
{
   Errorlog *auxiliar;
   char letra;
   nuevo=*cabeza;
   letra= *nuevo.id;

   while(letra>=
}

/*
 * TODO: Implementar contar_criticos
 *
 * Recorre la lista y cuenta los nodos cuyo campo es_critico sea 1.
 */
int contar_criticos(ErrorLog *cabeza)
{
	ErrorLog *nuevo;
	int criticos=0;
	nuevo.es_critico=cabeza.es_critico;
	while(nuevo != NULL){
		if(nuevo.es_critico==1){
			criticos++;
		}
		nuevo=cabeza.siguiente;
	}	
    return criticos;
}

/*
 * TODO: Implementar contar_no_criticos
 *
 * Recorre la lista y cuenta los nodos cuyo campo es_critico sea 0.
 */
int contar_no_criticos(ErrorLog *cabeza)
{
    ErrorLog *nuevo;     
        int nocriticos=0;
        nuevo.es_critico=cabeza.es_critico;
        while(nuevo != NULL){
                if(nuevo.es_critico==0){
                        criticos++;
                }   
                nuevo=cabeza.siguiente;               
        }
    return nocriticos;
}

/*
 * TODO: Implementar eliminar_por_prioridad
 *
 * Elimina de la lista todos los nodos cuya prioridad sea estrictamente
 * menor que 'umbral'. Libera la memoria de cada nodo eliminado.
 * Retorna la nueva cabeza de la lista (puede cambiar si se eliminan
 * nodos al inicio).
 */
ErrorLog *eliminar_por_prioridad(ErrorLog *cabeza, float umbral)
{
    /* ESCRIBE TU CODIGO AQUI */
    return cabeza;
}

/*
 * TODO: Implementar conservar_mayor_no_critico
 *
 * Conserva todos los errores criticos (A-E) y unicamente el error
 * no critico (F-Z) que tenga la mayor prioridad numerica.
 * Elimina y libera todos los demas errores no criticos.
 * Retorna la nueva cabeza de la lista.
 *
 * Pista: primero encuentra cual es el nodo no critico con mayor
 * prioridad, y luego recorre la lista eliminando los demas no criticos.
 */
ErrorLog *conservar_mayor_no_critico(ErrorLog *cabeza)
{
    /* ESCRIBE TU CODIGO AQUI */
    return cabeza;
}

/* =====================================================================
 * PROGRAMA PRINCIPAL
 * =====================================================================*/

int main(void)
{
    ErrorLog *lista = NULL;
    int total_errores;
    int i;

    srand((unsigned)time(NULL));

    /* Numero aleatorio de errores entre 10 y 25 */
    total_errores = 10 + rand() % 16;

    printf("=== SISTEMA DE LOGS DE ERRORES ===\n");
    printf("Simulando recepcion de %d errores...\n\n", total_errores);

    /* Simular la llegada de errores uno por uno */
    for (i = 0; i < total_errores; i++) {
        ErrorLog *nuevo = generar_error_aleatorio();
        printf("  Recibido: [%s] prioridad=%.2f (%s)\n",
               nuevo->id, nuevo->prioridad,
               nuevo->es_critico ? "CRITICO" : "normal");

        insertar_ordenado(&lista, nuevo);
    }

    /* Mostrar la lista ordenada */
    printf("\n=== LISTA ORDENADA DE ERRORES ===");
    imprimir_lista(lista);

    /* Estadisticas */
    printf("\nEstadisticas:\n");
    printf("  Errores criticos    (A-E): %d\n", contar_criticos(lista));
    printf("  Errores no criticos (F-Z): %d\n", contar_no_criticos(lista));
    total_errores=contar_criticos(lista)+contar_no_criticos(lista);
    printf("  Total:                     %d\n", total_errores);

    /* Filtrar errores de baja prioridad */
    float umbral = 3.0f;
    printf("\n=== ELIMINANDO ERRORES CON PRIORIDAD < %.1f ===\n", umbral);
    lista = eliminar_por_prioridad(lista, umbral);

    printf("\n=== LISTA DESPUES DEL FILTRADO ===");
    imprimir_lista(lista);

    printf("\nEstadisticas post-filtrado:\n");
    printf("  Errores criticos    (A-E): %d\n", contar_criticos(lista));
    printf("  Errores no criticos (F-Z): %d\n", contar_no_criticos(lista));

    /* Conservar solo el error no critico de mayor prioridad */
    printf("\n=== CONSERVANDO SOLO EL MAYOR ERROR NO CRITICO ===\n");
    lista = conservar_mayor_no_critico(lista);

    printf("\n=== LISTA FINAL ===");
    imprimir_lista(lista);

    printf("\nEstadisticas finales:\n");
    printf("  Errores criticos    (A-E): %d\n", contar_criticos(lista));
    printf("  Errores no criticos (F-Z): %d\n", contar_no_criticos(lista));

    liberar_lista(lista);

    return 0;
}
