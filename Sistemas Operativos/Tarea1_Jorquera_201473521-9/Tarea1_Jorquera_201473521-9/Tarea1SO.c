#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <dirent.h>

/*funcion ls: recorre el directorio imprime archivos, tipo y fecha*/

void ls() {
	DIR *dirp;
    struct dirent *dp;
    struct stat file;
    dirp = opendir(".");                   
    while ((dp = readdir(dirp)) != NULL){
		if (dp->d_ino == 0)               /* ignora archivos borrados    */
			continue;
		else {
			if(strcmp(dp->d_name,".")!=0 && strcmp(dp->d_name,"..")!=0){
				stat(dp->d_name, &file);
				time_t tiempo = file.st_mtime;
				struct tm t;
				gmtime_r(&tiempo, &t); 
				char date[50];
				strftime(date, sizeof(date), "%c", &t);
				printf("%s	%d	%s\n",dp->d_name,dp->d_type,date);
			}       
        }
     }
}

/*retorna ruta actual*/

char* real_path() {
	char actualpath [PATH_MAX+1];
	return realpath(".", actualpath);
}

int main() {
	char *act = real_path();
	char s[10];
	printf("%s\\$ ", act);
	while(1){
		scanf("%s", s); /*procesa comando*/
		if (!(strcmp(s, "open"))){
			char f[99];
			scanf("%s", f);
			FILE *fo = fopen(f, "r");
			if(fo!=NULL){
				char linea[1000];
				while(fgets(linea, 1000, fo) != NULL) /*abre archivo lee linea por linea*/
					printf("\\%s", linea);
				printf("$ ");
			}
			else printf("No existe el archivo"); /*cierra el archivo*/
		}
		else if(!(strcmp(s, "close")))
			printf("%s\\$ ", act);
		else if (!(strcmp(s, "cd"))){ /*ruta absoluta y ruta relativa*/
			char a[99];
			scanf("%s", a);
			int dr = chdir(a);
			if (dr==0) act = real_path();
			else printf("No existe la ruta\n");
			printf("%s\\$ ", act);
		}
		else if (!(strcmp(s, "ls\0n"))){
			ls();
			printf("%s\\$ ", act);
		}
	}
}
