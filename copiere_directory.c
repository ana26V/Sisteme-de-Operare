#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 8192

void copiere_FIS(char* sursa,char* dest) 
{
	struct stat st; 
	int sur,dst,continut; 
	char buffer[100]; 

	sur=open(sursa, O_RDONLY); 

	stat(sursa,&st);

	dst=open(dest, O_CREAT|O_WRONLY,st.st_mode); 

	continut=read(sur, buffer, strlen(buffer)); 

	write(dst, buffer, continut); 

	close(sur); 
	close(dst);
}


int skipPct(char *ceva)
{
	return (strcmp(ceva, "..") && strcmp(ceva, "."));
}
void addPath(char* Sursa, char* Destinatie,char* pathSursa, char* pathDestinatie)
{
	int n,n2;
		strcpy(pathSursa, Sursa);
		strcpy(pathDestinatie, Destinatie);
		
		n=strlen(pathSursa);
		n2=strlen(pathDestinatie);
		
		if (pathSursa[n - 1] != '/')
			strcat(pathSursa, "/");
		if (pathDestinatie[n2 - 1] != '/')
			strcat(pathDestinatie, "/");
					
}
void addAux(char* Sursa,char *pathSursa,char *aux)
{
	strcpy(pathSursa, aux);	
	strcat(pathSursa, "/");
	strcat(pathSursa, Sursa);
	if (pathSursa[strlen(pathSursa) - 1] != '/')
		strcat(pathSursa, "/");
}

void copiereToate(char* Sursa, char* Destinatie)
{
	struct stat stare;
	DIR* sur1;
	struct dirent* entryData ;
	char pathSursa[BUF_SIZE], pathDestinatie[BUF_SIZE], aux[BUF_SIZE];
	long int res;
	getcwd(aux, sizeof(aux)); 

	sur1 = opendir(Sursa);
	
	if (sur1)
	{
		stat(Sursa, &stare); 
		mkdir(Destinatie, stare.st_mode); 
		
		while ((entryData = readdir(sur1))!=NULL) {
			if (skipPct(entryData->d_name)) {
			
				addPath(Sursa,Destinatie,pathSursa,pathDestinatie);
				
				strcat(pathSursa, entryData->d_name);
				strcat(pathDestinatie, entryData->d_name);
				
				lstat(pathSursa, &stare);
				
				if (S_ISDIR(stare.st_mode))
					copiereToate(pathSursa, pathDestinatie);
				 if (S_ISREG(stare.st_mode))
					{

						if (stare.st_size >= 500){
							copiere_FIS(pathSursa, pathDestinatie); 
  					chmod(pathDestinatie, stare.st_mode | S_IWGRP+S_IWOTH+S_IWUSR );
							}
						else if (stare.st_size >= 300 && stare.st_size < 500)
						{
							addAux(Sursa,pathSursa,aux);
							strcat(pathSursa, entryData->d_name);
							link(pathSursa, pathDestinatie);
						}
						else if (stare.st_size < 300)
						{
							addAux(Sursa,pathSursa,aux);
								
							strcat(pathSursa, entryData->d_name);
							symlink(pathSursa, pathDestinatie);
						}
				}
				
				if(S_ISLNK(stare.st_mode)) continue;
				
			}
		}
	}

}


void eroare(int argc)
{
	
	if(argc!=3){
		printf("Nu sunt destule argumente...\n");
		return;
	}
	else printf("Executat cu succes\n");
}

int main (int argc, char **argv)
{
	printf("-----------------------------------------------\n");
	eroare(argc);
	copiereToate(argv[1],argv[2]);
	printf("-----------------------------------------------\n");
	return 0;
}
