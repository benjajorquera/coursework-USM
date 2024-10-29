#include <sys/types.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wait.h>
#include <signal.h>

#define SIZE 512

struct sigaction sigchld_action = {
  .sa_handler = SIG_DFL,
  .sa_flags = SA_NOCLDWAIT
};

void measure_time(int sig){
    printf("child [%d] received signal %d\n", getpid(), sig);
}

void imprimir_tablero(int *m){	//funcion que imrpime el tablero actual desde la matriz
	printf(" ABCDEFGH\n");
	for(int j=0;j<8;j++){
		int f=0;
		for(int i =0;i<8;i++){
			if(f==0){
				printf("%d", j+1);
				f=1;
			}
			if(m[j*8 +i] == 2) printf("T");
			if(m[j*8 +i] == 3) printf("C");
			if(m[j*8 +i] == 4) printf("A");
			if(m[j*8 +i] == 5) printf("R");
			if(m[j*8 +i] == 6) printf("Q");
			if(m[j*8 +i] == 1) printf("P");
			if(m[j*8 +i] == 0) printf(" ");
			if(m[j*8 +i] == 8) printf("t");
			if(m[j*8 +i] == 9) printf("c");
			if(m[j*8 +i] == 10) printf("a");
			if(m[j*8 +i] == 11) printf("r");
			if(m[j*8 +i] == 12) printf("q");
			if(m[j*8 +i] == 7) printf("p");
		}
	printf("\n");
	}
}

//void jaque(){}
//void jaquemate(){}

int main(int argc, char **argv){
	
	pid_t pid;
	int a[2], b[2], readbytes;
	char buffer[SIZE];	//buffers de msjes para los pipes
	char buffer2[SIZE];
	int nfila=8;
	int ncol=8;
	key_t key;
	key = 99;
	int juego=10;	//estado de juego
	int *matrix;

	int id_shmem = shmget(key, sizeof(int)*nfila*ncol, IPC_CREAT|0777);
	matrix = (int *)shmat(id_shmem,0,0); //creacion matriz memoria compartida para el tablero
										//en teoria es una matriz de arrays implementada en funcion 2D
	
	for(int i =0;i<8;i++){	//peones (1 para jugador1, 7 para jugador2)
		matrix[ncol + i] = 1;	//0 para espacios en blanco
		matrix[2*ncol + i] = 0;
		matrix[3*ncol + i] = 0;
		matrix[4*ncol + i] = 0;
		matrix[5*ncol + i] = 0;
		matrix[6*ncol + i] = 7;
	}
	
	matrix[0] = 2, matrix[7] = 2; //torres jugador1
	matrix[1] = 3, matrix[6] = 3; //caballos jugador1
	matrix[2] = 4, matrix[5] = 4; //alfiles jugador1
	matrix[3] = 5; //rey jugador1
	matrix[4] = 6; //reina jugador1
	
	matrix[7*ncol] = 8, matrix[7*ncol + 7] = 8; //torres jugador2
	matrix[7*ncol + 1] = 9, matrix[7*ncol + 6] = 9; //caballos jugador2
	matrix[7*ncol + 2] = 10, matrix[7*ncol + 5] = 10; //alfiles jugador2
	matrix[7*ncol + 3] = 11; //rey jugador2
	matrix[7*ncol + 4] = 12; //reina jugador2

	pipe(a); //creaciones de pipes
	pipe(b);
	
	pid = fork();

	while(juego){ //entran al juego proceso padre e hijo

	if(pid!=0){	//padre
		
		char jugada[SIZE];
		printf("Jugando Jugador: 1\n");
		imprimir_tablero(matrix);
		
		while(1){
			fgets (jugada, SIZE, stdin);
			int columna1 = jugada[0]-65;
			int fila1 = jugada[1]-49;
			int columna2 = jugada[5]-65;
			int fila2 = jugada[6]-49;
			int f = 0;
			int u = 0;
			
			if(matrix[fila1*ncol + columna1] ==1){	//jugadas peon
				if((columna1==columna2 && fila1+1 == fila2) && matrix[fila2*ncol + columna2] == 0){
					matrix[fila1*ncol + columna1] = 0;
					matrix[fila2*ncol + columna2] = 1;
					break;
				}
				else if(((columna1+1 == columna2 || columna1-1 == columna2) && fila1+1 ==fila2) && matrix[fila2*ncol + columna2] >=7){
					if (matrix[fila2*ncol + columna2]==11){
						printf("Ganador jugador 1\n");
						juego=0;
					}
					matrix[fila1*ncol + columna1] = 0;
					matrix[fila2*ncol + columna2] = 1;	//pieza tomada
					break;
				}
				else printf("Jugada invalida, movimiento invalido del peon\n");
			}
			
			
			else if(matrix[fila1*ncol + columna1] ==2){	//jugadas torre
				if(fila1==fila2){
					u = abs(columna1-columna2);
					if(columna2<columna1){
						for(int i=0;i<u;i++)
							if(matrix[fila2*ncol + columna2 +i] !=0) f=1;
					}
					else{
						for(int i=0;i<u;i++)
							if(matrix[fila1*ncol + columna1 +i] !=0) f=1;
					}
					if(f!=1){
						if(matrix[fila2*ncol + columna2]>=7 || matrix[fila2*ncol + columna2]==0){
							if (matrix[fila2*ncol + columna2]==11){
								printf("Ganador jugador 1\n");
								juego=0;
							}
							matrix[fila1*ncol + columna1] = 0;
							matrix[fila2*ncol + columna2] = 2;	//pieza tomada
							break;
						}
						else printf("Jugada invalida, movimiento invalido de la torre\n");	
					}
				}
				else if(columna1==columna2){
					u = abs(fila1-fila2);
					if(fila2<fila1){
						for(int i=0;i<u;i++)
							if(matrix[(fila2+i)*ncol + columna2] !=0) f=1;
					}
					else{
						for(int i=0;i<u;i++)
							if(matrix[(fila1+i)*ncol + columna1] !=0) f=1;
					}
					if(f!=1){
						if(matrix[fila2*ncol + columna2]>=7){
							if (matrix[fila2*ncol + columna2]==11){
								printf("Ganador jugador 1\n");
								juego=0;
							}
							matrix[fila1*ncol + columna1] = 0;
							matrix[fila2*ncol + columna2] = 2;	//pieza tomada
							break;
						}
						else printf("Jugada invalida, movimiento invalido de la torre\n");
					}
				}
				else printf("Jugada invalida, movimiento invalido de la torre\n");
			}
			
			
			else if(matrix[fila1*ncol + columna1] == 3){	//jugadas caballo
				if((fila2 == fila1+2 && columna2 == columna1+1) || (fila2==fila1-2 && columna2 == columna1-1)){
					if(matrix[fila2*ncol + columna2]>=7 || matrix[fila2*ncol + columna2]==0){
						if (matrix[fila2*ncol + columna2]==11){
							printf("Ganador jugador 1\n");
							juego=0;
						}
						matrix[fila1*ncol + columna1] = 0;
						matrix[fila2*ncol + columna2] = 3;	//pieza tomada
						break;
					}
					else printf("Jugada invalida, movimiento invalido del caballo\n");
				}
				else if((fila2 == fila1+1 && columna2 == columna1+2) || (fila2==fila1-1 && columna2 == columna1-2)){
					if(matrix[fila2*ncol + columna2]>=7 || matrix[fila2*ncol + columna2]==0){
						if (matrix[fila2*ncol + columna2]==11){
							printf("Ganador jugador 1\n");
							juego=0;
						}
						matrix[fila1*ncol + columna1] = 0;
						matrix[fila2*ncol + columna2] = 3;	//pieza tomada
						break;
					}
					else printf("Jugada invalida, movimiento invalido del caballo\n");
				}
				else printf("Jugada invalida, movimiento invalido del caballo\n");
			}
			
			
			else if(matrix[fila1*ncol + columna1] == 4){	//jugadas alfil
				if(abs(fila1-fila2) == abs(columna1 - columna2)){
					u = abs(fila1-fila2);
					if(fila2<fila1 && columna2<columna1){
						for(int i = 0;i<u;i++)
							if(matrix[(fila2+i)*ncol + columna2 +i] !=0) f=1;
					}
					if(fila2<fila1 && columna1<columna2){
						for(int i = 0;i<u;i++)
							if(matrix[(fila2+i)*ncol + columna2 -i] !=0) f=1;
					}
					if(fila1<fila2 && columna2<columna1){
						for(int i = 0;i<u;i++)
							if(matrix[(fila1+i)*ncol + columna1 -i] !=0) f=1;
					}
					if(fila1<fila2 && columna1<columna2){
						for(int i = 0;i<u;i++)
							if(matrix[(fila1+i)*ncol + columna1 +i] !=0) f=1;
					}
				}
				if (f==1) printf("Jugada invalida, movimiento invalido del alfil\n");
				else{
						if(matrix[fila2*ncol + columna2]>=7 || matrix[fila2*ncol + columna2]==0){
							if (matrix[fila2*ncol + columna2]==11){
								printf("Ganador jugador 1\n");
								juego=0;
							}
							matrix[fila1*ncol + columna1] = 0;
							matrix[fila2*ncol + columna2] = 4;	//pieza tomada
							break;
						}
						else printf("Jugada invalida, movimiento invalido del alfil\n");
				}
			}
			
			
			else if(matrix[fila1*ncol + columna1] == 5){ 	//jugadas del rey
				if((abs(fila1-fila2)==fila1+1 && abs(columna1-columna2)==columna1+1) || (abs(columna1-columna2)==columna1+1 || abs(fila1-fila2)==fila1+1)) /*&& !jaque() )*/{
					if(matrix[fila2*ncol + columna2]>=7 || matrix[fila2*ncol + columna2]==0){
							if (matrix[fila2*ncol + columna2]==11){
								printf("Ganador jugador 1\n");
								juego=0;
							}
							matrix[fila1*ncol + columna1] = 0;
							matrix[fila2*ncol + columna2] = 5;	//pieza tomada
							break;
					}
					else printf("Jugada invalida, movimiento invalido del rey\n");
				}
				else printf("Jugada invalida, movimiento invalido del rey\n");
			}
			
			
			else if(matrix[fila1*ncol + columna1] == 6){
				if(abs(fila1-fila2) == abs(columna1 - columna2)){
					u = abs(fila1-fila2);
					if(fila2<fila1 && columna2<columna1){
						for(int i = 0;i<u;i++)
							if(matrix[(fila2+i)*ncol + columna2 +i] !=0) f=1;
					}
					if(fila2<fila1 && columna1<columna2){
						for(int i = 0;i<u;i++)
							if(matrix[(fila2+i)*ncol + columna2 -i] !=0) f=1;
					}
					if(fila1<fila2 && columna2<columna1){
						for(int i = 0;i<u;i++)
							if(matrix[(fila1+i)*ncol + columna1 -i] !=0) f=1;
					}
					if(fila1<fila2 && columna1<columna2){
						for(int i = 0;i<u;i++)
							if(matrix[(fila1+i)*ncol + columna1 +i] !=0) f=1;
					}
				}
				if(fila1==fila2){
					u = abs(columna1-columna2);
					if(columna2<columna1){
						for(int i=0;i<u;i++)
							if(matrix[fila2*ncol + columna2 +i] !=0) f=1;
					}
					else{
						for(int i=0;i<u;i++)
							if(matrix[fila1*ncol + columna1 +i] !=0) f=1;
					}
				}
				else if(columna1==columna2){
					u = abs(fila1-fila2);
					if(fila2<fila1){
						for(int i=0;i<u;i++)
							if(matrix[(fila2+i)*ncol + columna2] !=0) f=1;
					}
					else{
						for(int i=0;i<u;i++)
							if(matrix[(fila1+i)*ncol + columna1] !=0) f=1;
					}
				}
				if (f==1) printf("Jugada invalida, movimiento invalido de la reina\n");
				else{
					if(matrix[fila2*ncol + columna2]>=7 || matrix[fila2*ncol + columna2]==0){
						if (matrix[fila2*ncol + columna2]==11){
							printf("Ganador jugador 1\n");
							juego=0;
						}
						matrix[fila1*ncol + columna1] = 0;
						matrix[fila2*ncol + columna2] = 4;	//pieza tomada
						break;
					}
					else printf("Jugada invalida, movimiento invalido de la reina\n");
				}
			}
			
		}
		
		strcpy(buffer, jugada);
		close(b[0]);
		write(b[1], buffer, strlen(buffer));	//padre esribe al hijo su jugada, cerrando los extremos de la pipe correspondientes
		close(b[1]);
	
		close(a[1]);
		while((readbytes=read(a[0],buffer2,SIZE))>0)	//padre recibe la jugada del hijo, cerrando los extremos de la pipe correspondientes
			write(1,buffer2,readbytes);
		close(a[0]);
		 
		//signal(SIGUSR1, measure_time);
		//signal(SIGCHLD, SIG_IGN);
		}
		
	else if (pid==0){	//hijo
		
		char jugada2[SIZE];
		
		close(b[1]);
		while((readbytes=read(b[0],buffer,SIZE))>0) //hijo recibe la jugada del padre, cerrando los extremos de la pipe correspondientes
			write(1,buffer,readbytes);
		close(b[0]);
		
		printf("Jugando Jugador: 2\n");
		imprimir_tablero(matrix);
		
		while(1){
			fgets (jugada2, SIZE, stdin);
			int columna1 = jugada2[0]-65;
			int fila1 = jugada2[1]-49;
			int columna2 = jugada2[5]-65;
			int fila2 = jugada2[6]-49;
			//int f = 0;
			//int u = 0;
			
			if(matrix[fila1*ncol + columna1] ==7){	//jugadas peon
				if((columna1==columna2 && fila1 == fila2+1) && matrix[fila2*ncol + columna2] == 0){
					matrix[fila1*ncol + columna1] = 0;
					matrix[fila2*ncol + columna2] = 7;
					break;
				}
				else if(((columna1+1 == columna2 || columna1-1 == columna2) && fila1 ==fila2+1) && matrix[fila2*ncol + columna2] <7){
					if (matrix[fila2*ncol + columna2]==5){
						printf("Ganador jugador 2\n");
						juego=0;
					}
					matrix[fila1*ncol + columna1] = 0;
					matrix[fila2*ncol + columna2] = 7;	//pieza tomada
					break;
				}
				else printf("Jugada invalida, movimiento invalido del peon\n");
			}
		}
			
			
		strcpy(buffer2, jugada2);
		
		close(a[0]);
		write(a[1],buffer2,strlen(buffer2));	//hijo esribe al padre su jugada, cerrando los extremos de la pipe correspondientes
		close(a[1]);
		sleep(1);
		}
	
	juego = juego-1;	// un contador del juego que en este caso empieza en 10, 
						// aqui es donde deberian entrar al while los 2 procesos
	}					// (padre e hijo) simultaneamente. 
	
	printf("proceso %d", pid);
	exit(0);
}
