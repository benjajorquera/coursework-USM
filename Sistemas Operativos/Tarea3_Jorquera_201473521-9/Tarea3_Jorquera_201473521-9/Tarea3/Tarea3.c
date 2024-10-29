#include <semaphore.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int k=1;
void* funcion1(void* val);
void* funcion2(void* val);

// Archivo compartido.
FILE *fp;

// Declaracion de semaforos.
sem_t s1;
sem_t s2;

int main(){

	fp = fopen("Archivo.txt","w");
	fclose(fp);
	void* status;
	
	// Declaracion de hebras.
	pthread_t thread1;
	pthread_t thread2;

	// Inicializar semaforos en 0.
	sem_init(&s1, 0, 0);
	sem_init(&s2, 0, 0);

	/*Se hace trabajar a los procesos dentro de funcion1 y funcion2 en
	   multihebra, para que trabajen de forma paralela atravez de los
	   semaforos. */
	   
	printf("Bienvenido a tus subprocesos!. Para salir pulsa 0.\n");
	
	// Se inician los subprocesos.
	pthread_create(&thread1, NULL, funcion1, NULL);
	pthread_create(&thread2, NULL, funcion2, NULL);
	
	// Se espera a que terminen los subprocesos.
	pthread_join(thread1, &status);
	pthread_join(thread2, &status);

	// Destruccion de semaforos.
	sem_destroy(&s1);
	sem_destroy(&s2);
	
	return 0;
}

/*funcion1, es la que tiene prioridad, el subproceso que la llama accede
	a escanear por pantalla lo que el usuario desee, luego lo reescribe
	en el archivo compartido.*/
	
void* funcion1(void* val){
	while(1){
		char X[1001];
		printf("\nPorfavor escribe algo:\n");
		fgets(X, 1001, stdin);
		if(*X==48){
			printf("Adios!\n");
			sem_post(&s1); // señal!
			k = 0;
			break;
		}
		printf("\n[Subproceso1] Escribiendo..\n");
		fp = fopen("Archivo.txt","a");
		fprintf(fp, "%s", X); // escribe..
		fclose(fp);
		sleep(3);
		sem_post(&s1); // señal!
		sem_wait(&s2); // wait
		sleep(1);
   }  
   return 0;
}

/* funcion2, el subproceso que la llama accede a leer el archivo compartido
   luego imprime por pantalla cada linea de este.*/
	
void* funcion2(void* val){
	while(1){
		sem_wait(&s1); // wait
		if(k==0) break;
		fp = fopen("Archivo.txt","rb");
		char X[1001];
		printf("\n[Subproceso2] Leyendo.. : \n");
		while(fgets( X, 1001, fp)){ // lee..
			printf("%s", X); 
		}
    fclose(fp);
    sem_post(&s2); // señal!
    sleep(1);
	}
	return 0;
}
