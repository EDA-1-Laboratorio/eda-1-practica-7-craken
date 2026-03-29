#include "error_log.h"
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

void insertar_ordenado(ErrorLog **cabeza, ErrorLog *nuevo)
{
    ErrorLog *actual = *cabeza;
    ErrorLog *anterior = NULL;

    while (actual != NULL) {

        if (nuevo->id[0] < actual->id[0])
            break;

        if (nuevo->id[0] == actual->id[0] &&
            nuevo->prioridad > actual->prioridad)
            break;

        anterior = actual;
        actual = actual->sig;
    }

    if (anterior == NULL) {
        nuevo->sig = *cabeza;
        *cabeza = nuevo;
    } else {
        anterior->sig = nuevo;
        nuevo->sig = actual;
    }
}

int contar_criticos(ErrorLog *cabeza)
{
	 int criticos=0;
	 ErrorLog *i;
	 for(i = cabeza; i != NULL; i = i->sig) {
        if(i->es_critico==1)
        criticos++;
      }
    return criticos;
}

int contar_no_criticos(ErrorLog *cabeza)
{
    int nocriticos=0;
	 ErrorLog *i;
	 for(i = cabeza; i != NULL; i = i->sig) {
        if(i->es_critico==0)
        nocriticos++;
      }
    return nocriticos;
}

ErrorLog *eliminar_por_prioridad(ErrorLog *cabeza, float umbral)
{
	ErrorLog *actual=cabeza;
	ErrorLog *anterior=NULL;
	while(actual) {
        if(actual->prioridad<umbral) {
            ErrorLog *borrar = actual;

            if(anterior == NULL) {
                cabeza = actual->sig;
                actual = cabeza;
            } else {
                anterior->sig = actual->sig;
                actual = actual->sig;
            }

            free(borrar);
        } else {
            anterior = actual;
            actual = actual->sig;
        }
    }
    return cabeza;
}

ErrorLog *conservar_mayor_no_critico(ErrorLog *cabeza)
{
    if (!cabeza) return cabeza;

    ErrorLog *actual = cabeza;
    ErrorLog *mayor = NULL;

    while (actual) {
        if (!actual->es_critico) {
            if (!mayor ||actual->prioridad > mayor->prioridad)
                mayor = actual;
        }
        actual = actual->sig;
    }

    actual = cabeza;
    ErrorLog *anterior = NULL;

    while (actual) {
        if (!actual->es_critico && actual != mayor) {

            ErrorLog *borrar = actual;

            if (anterior == NULL) {
                cabeza = actual->sig;
                actual = cabeza;
            } else {
                anterior->sig = actual->sig;
                actual = actual->sig;
            }

            free(borrar);
        } else {
            anterior = actual;
            actual = actual->sig;
        }
    }

    return cabeza;
}

int main(void)
{
    ErrorLog *lista = NULL;
    int total_errores;
    int i;

    srand((unsigned)time(NULL));

    total_errores = 10 + rand() % 16;

    printf("=== SISTEMA DE LOGS DE ERRORES ===\n");
    printf("Simulando recepcion de %d errores...\n\n", total_errores);

    for (i = 0; i < total_errores; i++) {
        ErrorLog *nuevo = generar_error_aleatorio();
        printf("  Recibido: [%s] prioridad=%.2f (%s)\n",
               nuevo->id, nuevo->prioridad,
               nuevo->es_critico ? "CRITICO" : "normal");

        insertar_ordenado(&lista, nuevo);
    }

    printf("\n=== LISTA ORDENADA DE ERRORES ===");
    imprimir_lista(lista);

    printf("\nEstadisticas:\n");
    printf("  Errores criticos    (A-E): %d\n", contar_criticos(lista));
    printf("  Errores no criticos (F-Z): %d\n", contar_no_criticos(lista));
    total_errores=contar_criticos(lista)+contar_no_criticos(lista);
    printf("  Total:                     %d\n", total_errores);

    float umbral = 3.0f;
    printf("\n=== ELIMINANDO ERRORES CON PRIORIDAD < %.1f ===\n", umbral);
    lista = eliminar_por_prioridad(lista, umbral);

    printf("\n=== LISTA DESPUES DEL FILTRADO ===");
    imprimir_lista(lista);

    printf("\nEstadisticas post-filtrado:\n");
    printf("  Errores criticos    (A-E): %d\n", contar_criticos(lista));
    printf("  Errores no criticos (F-Z): %d\n", contar_no_criticos(lista));

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
