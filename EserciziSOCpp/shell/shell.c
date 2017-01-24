#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>


int main() {
	char buffer[128];
	pid_t pid;
	int n;
	char* args[10];
	char* token;
	int stat;

	while(1){

		printf("Shell> ");
		//scanf("%127s\n", buffer); // scanf non legge l'intera stringa se contiene spazi
		fgets(buffer, 127, stdin);
		buffer[strlen(buffer) - 1] = '\0';



		token = strtok(buffer, " ");

		args[0] = token;
		n = 1;
		while(token != NULL && n<10) {

			token = strtok(NULL, " ");//strtok ha memoria di quello che gli è stato buttato dentro

			args[n] = token;
			n++;
		}
		args[9] = (char *)0;
		if(!strcmp(args[0], "exit")){
			return 0;//exit(0);
		}
		pid = fork();
		if(pid == -1){
			//printf("Errore: fork non riuscita!\n");
			perror("Errore: fork non riuscita!");
			return 0;//exit(0);
		}
		else if(pid == 0){
				if(!strcmp(args[n-2],"&"))
					{
					args[n-2]=NULL;
					int pidbk=fork();
					wait(&stat);
						if(pidbk==0){
						}
						else if (pidbk<0){
							printf("errore: fork non riuscita");
						}
						else{
							printf("processo [%d] in background",pidbk);
							execvp(args[0],args);
							printf("errore exec non riuscita");
						}
					}
				else
					{
					printf("processo in esecuzione ... \n");
					execvp(args[0], args);
					//printf("Errore: exec non riuscita!\n");
					perror("Errore: exec non riuscita!");
					}
		}
		else{
			pid = wait(NULL);
		}
	}

	return 0;
}
