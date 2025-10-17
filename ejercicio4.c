#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int contador = 0;  // contador de Ctrl+C recibidos

void gestion(int sig) {
    contador++;
    
    if (contador <= 3) {
        printf("\nSeñal SIGINT atrapada y desactivada (%d/3)\n", contador);
    } else {
        char respuesta;
        printf("\nHas presionado Ctrl+C más de 3 veces.¿Deseas restaurar la acción habitual de Ctrl+C? (s/n):\n");
        scanf(" %c", &respuesta);

        if (respuesta == 's' || respuesta == 'S') {
            printf("Restaurando acción habitual de Ctrl+C.\n");
            signal(SIGINT, SIG_DFL); // restaurar comportamiento por defecto
        } else {
            printf("Continuando con Ctrl+C desactivado.\n");
        }
    }
}

int main() {
    // Asociar SIGINT al manejador personalizado
    if (signal(SIGINT, gestion) == SIG_ERR) {
        printf("Error al crear gestor SIGINT\n");
        exit(1);
    }

    printf("Programa en bucle infinito. Presiona Ctrl+C para probar.\n");

    // Bucle infinito
    while (1) {
        sleep(1); // esperar 1 segundo
    }

    return 0;
}
