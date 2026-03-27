/*
 * PRACTICA: Lista Circular - Arrakis Kernel: El Ciclo de Shai-Hulud
 * ===================================================================
 *
 * Descripcion:
 *   Se simula la supervivencia de las Grandes Casas en el desierto de
 *   Dune. Las casas forman un anillo (lista circular) y un gusano de
 *   arena (Shai-Hulud) avanza por el anillo devorando soldados.
 *
 * Reglas del desierto:
 *   - Cada turno se lanza un dado (1-6) y el gusano avanza esa cantidad.
 *   - Al detenerse, devora el 20% de los soldados de esa casa.
 *   - Las casas no atacadas cosechan +10 de especia.
 *   - Si una casa baja de 50 soldados, es consumida (se elimina del anillo).
 *   - Si una casa alcanza 200 de especia, invoca refuerzos (nodo nuevo).
 *
 * Objetivo:
 *   Implementar las funciones marcadas con TODO.
 *
 * Compilacion:
 *   gcc -o arrakis arrakis.c -lm
 *
 * Ejecucion:
 *   ./arrakis
 */

#include "arrakis.h"

/* =====================================================================
 * FUNCIONES PROPORCIONADAS (no modificar)
 * =====================================================================*/

Casa *crear_casa(const char *nombre, int soldados)
{
    Casa *nueva = (Casa *)malloc(sizeof(Casa));
    if (!nueva) {
        fprintf(stderr, "Error: no se pudo asignar memoria.\n");
        exit(EXIT_FAILURE);
    }
    strncpy(nueva->nombre, nombre, MAX_NOMBRE - 1);
    nueva->nombre[MAX_NOMBRE - 1] = '\0';
    nueva->soldados = soldados;
    nueva->especia = 0;
    nueva->siguiente = NULL;
    return nueva;
}

int lanzar_dado(void)
{
    return 1 + rand() % 6;
}

void mostrar_anillo(Casa *cualquiera)
{
    Casa *p;
    int i = 1;

    if (cualquiera == NULL) {
        printf("\n  (anillo vacio)\n");
        return;
    }

    printf("\n  %-4s %-25s %-12s %-10s\n", "#", "Casa", "Soldados", "Especia");
    printf("  -------------------------------------------------------\n");

    p = cualquiera;
    do {
        printf("  %-4d %-25s %-12d %-10d\n",
               i++, p->nombre, p->soldados, p->especia);
        p = p->siguiente;
    } while (p != cualquiera);

    printf("  -------------------------------------------------------\n");
}

void liberar_anillo(Casa *cualquiera)
{
    Casa *p, *tmp;
    if (cualquiera == NULL) return;

    p = cualquiera->siguiente;
    while (p != cualquiera) {
        tmp = p;
        p = p->siguiente;
        free(tmp);
    }
    free(cualquiera);
}

int contar_casas(Casa *cualquiera)
{
    Casa *p;
    int n = 0;
    if (cualquiera == NULL) return 0;

    p = cualquiera;
    do {
        n++;
        p = p->siguiente;
    } while (p != cualquiera);

    return n;
}

/* =====================================================================
 * FUNCIONES A IMPLEMENTAR
 * =====================================================================*/

/*
 * TODO: Implementar insertar_casa
 *
 * Inserta 'nueva' al final del anillo circular.
 *   - Si *anillo == NULL: el nodo apunta a si mismo y *anillo = nueva.
 *   - Si ya hay nodos: inserta 'nueva' justo antes de *anillo
 *     (es decir, al "final" del anillo). *anillo no cambia.
 *
 * Pista: necesitas encontrar el ultimo nodo (el que apunta a *anillo)
 * para reconectar los punteros.
 */
void insertar_casa(Casa **anillo, Casa *nueva)
{
    /* ESCRIBE TU CODIGO AQUI */
    Casa *p = *anillo -> siguiente;
    
    if (*anillo == NULL) {
        *anillo = nueva;
        nueva -> siguiente = nueva;
        return;
    }
    
    nueva -> siguiente = *anillo;

    while ((p!=NULL) && (p!=*anillo)) {
        if (p -> siguiente == *anillo) break;
        p = p -> siguiente;
    }
    if (p == NULL) return;
    p -> siguiente = nueva;
}

/*
 * TODO: Implementar avanzar_gusano
 *
 * Avanza 'pasos' posiciones desde 'actual' siguiendo los punteros
 * de la lista circular.
 * Retorna el nodo donde se detiene.
 *
 * Pista: es un simple recorrido con un ciclo for.
 */
Casa *avanzar_gusano(Casa *actual, int pasos)
{
    
    for (int i= pasos, i > 0, i --) {
        if (actual->siguiente == NULL) break;
        actual = actual->siguiente;
    }
    
    return actual;
}

/*
 * TODO: Implementar atacar_asentamiento
 *
 * 1. Reducir el 20% de los soldados de la casa apuntada por *gusano.
 *    (soldados = soldados - soldados * 20 / 100)
 * 2. Recorrer el anillo: todas las casas DISTINTAS a *gusano ganan
 *    +10 de especia.
 * 3. Si los soldados de *gusano quedan < 50:
 *    a. Encontrar el nodo anterior (el que apunta a *gusano).
 *    b. Reconectar: anterior->siguiente = (*gusano)->siguiente.
 *    c. Si *gusano == *anillo, actualizar *anillo.
 *    d. Si *gusano apunta a si mismo (ultima casa), poner ambos a NULL.
 *    e. Mover *gusano al nodo siguiente antes de liberar.
 *    f. Liberar el nodo eliminado.
 *    g. Retornar 1.
 * 4. Si sobrevive, retornar 0.
 */
int atacar_asentamiento(Casa **gusano, Casa **anillo)
{
    /* ESCRIBE TU CODIGO AQUI */
    if (*gusano == NULL) return;
    
    *gusano -> soldados = soldados - soldados * DANIO_PORCENTAJE /100;
    
    
    Casa *tmp = *gusano->siguiente;
    while ((tmp != *gusano) && (tmp != NULL)) {
        tmp -> especia += ESPECIA_COSECHA;
    }
    
    if (*gusano -> soldados < SOLDADOS_MIN) {
        tmp = *gusano -> siguiente;
        while ((tmp != *gusano) && (tmp != NULL)) {
            if (tmp -> siguiente == *gusano) {
                *gusano = *gusano -> siguiente;
                free(tmp -> siguiente);
                tmp -> siguiente = *gusano;
                
                if (*gusano -> siguiente == *gusano){
                    *gusano = NULL;
                }
                
                return 1;
            }
        }
        
        
        
    }
    
    return 0;
}

/*
 * TODO (Boss Final): Implementar invocar_refuerzos
 *
 * Si actual->especia >= 200:
 *   1. Crear un nuevo nodo con nombre = nombre_actual + " II",
 *      250 soldados, 0 especia.
 *   2. Insertar el nuevo nodo JUSTO ANTES de 'actual' en el anillo.
 *      (Necesitas encontrar quien apunta a 'actual' y reconectar.)
 *   3. Poner actual->especia = 0.
 *   4. Retornar 1.
 * Si no tiene suficiente especia, retornar 0.
 */
int invocar_refuerzos(Casa *actual, Casa **anillo)
{
    /* ESCRIBE TU CODIGO AQUI */
    if (actual -> especia < ESPECIA_REFUERZOS) return 0;
    
    Casa *tmp = actual -> siguiente, *nueva;
    char nombre[MAX_NOMBRE] = actual -> nombre;
    while ((tmp!=NULL)&&(tmp!=actual)){
        if (tmp -> siguiente == actual) break;
    }
    tmp -> siguiente = nueva;
    nueva->siguiente = actual;
    nueva->soldados = 250;
    nueva->especia = 0;
    strcat(nombre, "II");
    nueva->nombre = nombre;
    
    
    return 1;
}

/* =====================================================================
 * PROGRAMA PRINCIPAL
 * =====================================================================*/

int main(void)
{
    Casa *anillo = NULL;
    Casa *gusano = NULL;
    int turno = 0;
    int dado;
    int max_turnos = 30;

    srand((unsigned)time(NULL));

    printf("==========================================================\n");
    printf("   ARRAKIS KERNEL - El Ciclo de Shai-Hulud\n");
    printf("==========================================================\n");

    /* Armar el anillo inicial con las Grandes Casas */
    insertar_casa(&anillo, crear_casa("Atreides", SOLDADOS_INICIAL));
    insertar_casa(&anillo, crear_casa("Harkonnen", SOLDADOS_INICIAL));
    insertar_casa(&anillo, crear_casa("Fremen", SOLDADOS_INICIAL));
    insertar_casa(&anillo, crear_casa("Corrino", SOLDADOS_INICIAL));
    insertar_casa(&anillo, crear_casa("Ordos", SOLDADOS_INICIAL));
    insertar_casa(&anillo, crear_casa("Tleilaxu", SOLDADOS_INICIAL));

    printf("\n>>> Estado inicial del anillo:");
    mostrar_anillo(anillo);

    /* El gusano comienza en la primera casa */
    gusano = anillo;

    /* Bucle de simulacion */
    while (contar_casas(anillo) > 1 && turno < max_turnos) {
        turno++;
        printf("\n--- TURNO %d ---\n", turno);

        /* A. Lanzar dado y avanzar */
        dado = lanzar_dado();
        gusano = avanzar_gusano(gusano, dado);
        printf("  Dado: %d -> Shai-Hulud se detiene en: %s\n",
               dado, gusano->nombre);

        /* B. Atacar */
        if (atacar_asentamiento(&gusano, &anillo)) {
            printf("  >> Una casa ha sido consumida por el desierto!\n");
        }

        /* Verificar si queda alguien */
        if (contar_casas(anillo) <= 1)
            break;

        /* C. Boss Final: verificar refuerzos en todas las casas */
        {
            Casa *p = anillo;
            do {
                if (invocar_refuerzos(p, &anillo)) {
                    printf("  >> %s invoca Refuerzos de la Cofradia Espacial!\n",
                           p->nombre);
                }
                p = p->siguiente;
            } while (p != anillo);
        }

        /* Mostrar estado */
        printf("\n  Estado del anillo (%d casas):", contar_casas(anillo));
        mostrar_anillo(anillo);
    }

    /* Resultado final */
    printf("\n==========================================================\n");
    if (contar_casas(anillo) == 1) {
        printf("  VICTORIA: %s domina Arrakis!\n", anillo->nombre);
    } else {
        printf("  Fin de la simulacion tras %d turnos.\n", max_turnos);
        printf("  Casas sobrevivientes: %d\n", contar_casas(anillo));
    }
    printf("==========================================================\n");

    liberar_anillo(anillo);

    return 0;
}
