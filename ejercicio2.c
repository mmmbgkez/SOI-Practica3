#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



int main(){
    printf("Hola, soy el proceso con PID: %d\n", getpid());
    
    int x;
    scanf("%d", &x);
    
    exit(EXIT_SUCCESS);
    
}
