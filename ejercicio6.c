#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void gestion(int senhal){
    printf("Señal recibida.\n");
}
int main(){
    pid_t hijo;
    if( (hijo = fork()) == 0) {
        printf("Soy el hijo 1 con PID %d: Me voy a bloquear con pause\n", getpid());

        signal(SIGUSR1, gestion);
        
        pause(); // Esperar una señal

        printf("Hijo 1: Señal recibida, terminando.\n");
        exit(0);
    }else if( hijo < 0) {
        perror("Error al crear el primer hijo");
        exit(EXIT_FAILURE);
    }
    if (hijo > 0){
        printf("Padre, espero 5 segundos:\n");
        sleep(5);

        kill(hijo, SIGUSR1);
        printf("Señal enviada al hijo con PID : %d\n", hijo);

        wait(NULL);
        printf("El hijo ha terminado.\n");
    }
    return 0; 
}
