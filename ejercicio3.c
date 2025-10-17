#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>



/* Incluye las librerias necesarias*/
static void gestion(int numero_de_senhal); /*Declaracion de la funcion de gestion de señales recibidas*/
int main() {
    pid_t padre,hijo;
    /* Declara las variables necesarias*/
    if (signal(SIGUSR1, gestion) == SIG_ERR) printf("Error al crear gestor 1\n");
    if (signal(SIGUSR2, gestion) == SIG_ERR) printf("Error al crear gestor 2\n");
    if (signal(SIGTERM, gestion) == SIG_ERR) printf("Error al crear gestor SIGTERM\n");
    
    padre=getpid();

    if ((hijo = fork()) == 0) { /*Trabajo del hijo*/
        kill(padre,SIGUSR1); /*Envia señal al padre*/
        for (;;); /*Espera señal del padre indefinidamente*/
    }
    else { /*Trabajo del padre*/
        sleep(1); 
        kill(hijo,SIGUSR2);
        sleep(1);
        kill(hijo,SIGTERM);
        wait(NULL);

        printf("Padre %d: hijo %d terminado.\n", getpid(), hijo);
    
    }
    
} 
static void gestion(int numero_de_senhal) { /* Funcion de gestion de señales*/
        switch (numero_de_senhal) {
            case SIGUSR1: /*Entra señal SIGUSR1*/
                printf("Señal tipo 1 recibida. Soy %d\n",getpid()); break;
            
            case SIGUSR2: /*Entra señal SIGUSR2*/
                printf("Señal tipo 2 recibida. Soy %d\n",getpid()); break;

            case SIGTERM:
                printf("Señal tipo SIGTERM recibida. Soy %d\n",getpid()); exit(0); break;
            
            return; 
        }
}  