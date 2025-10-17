#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main(){

    pid_t H1, H2;

    if (H1 > 0 && H2 > 0){
        waitpid(H1,NULL,WNOHANG);
        printf("\n¿Quieres que el hijo 2 mate al hijo 1?\n");
        char respuesta;
        scanf(" %c", &respuesta);
        if (respuesta == 's' || respuesta == 'S') {
            kill(H1, SIGTERM);
            printf("Hijo 2 ha matado al hijo 1\n");
        } else {
            printf("Hijo 2 no ha matado al hijo 1\n");
        }

        waitpid(H2,NULL,0);
    }
    
    if( (H1 = fork()) == 0) {
        printf("Soy el hijo 1 con PID: %d\n", getpid());
        while (1) {
            sleep(1); // Mantener al hijo 1 vivo
        }
    } else if (H1 < 0) {
        perror("Error al crear el primer hijo");
        exit(EXIT_FAILURE);
    }

    if( (H2 = fork()) == 0) {
        printf("Soy el hijo 2 con PID: %d\n", getpid());
        while (1) {
            sleep(1); // Mantener al hijo 1 vivo
        }
        
    } else if (H2 < 0) {
        perror("Error al crear el segundo hijo");
        exit(EXIT_FAILURE);
    }

    

    return 0; 
}