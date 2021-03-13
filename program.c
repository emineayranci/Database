#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int main(int argc,char *argv[]){

char *console[200];
	while(1){
		printf("Program>>");
		printf("\n%s " ,"sorgu : ");
		gets(console);
		

	int npipefd;
    	//named pipe adresi
   	 char * myfifo = "/tmp/myfifo";
    	//adresi pipe yapıyoruz 0666 rwx-rwx-rwx >0-110-110-110
    	mkfifo(myfifo, 0666);
        npipefd = open(myfifo, O_WRONLY);
        write(npipefd, console, sizeof(console)); // sorguyu database e gönderdim
        close(npipefd);

       	char **sonuc[100][100];
   	sleep(2);
        npipefd = open(myfifo, O_RDONLY);
	//char dene[10];
 	//read(npipefd, dene, sizeof(dene));
        read(npipefd, sonuc, sizeof(sonuc));
	
        close(npipefd);

	printf("Databaseden gelen sorgu sonucu= %s\n" ,sonuc);

	//burdan sonrası commentlenirse program sonsuz bir sekilde calisiyor
	// surekli sorgu alıyor ve sonucu donduruyor
	// ama kaydedilsin mi diye sorunca kullanıcı;
	// e yazarsa sonucu sonuc.txt'e kaydederek programı bitriyor
	// h yazarsa kaydetmeden programı bitiriyor
	int pipefd[2];
	if(pipe(pipefd)<0){
		perror("pipe");
		exit(1);
	}
	printf("Sorgu sonucu kaydedilsin mi? e/h");
	char answer[10];
	scanf("%s", answer);

	int pid = fork();
	int c;
	if(strcmp(answer,"e")==0){  //e harfi yazılırsa 
		if(pid==0){
			write(pipefd[1], sonuc, sizeof(sonuc));
			c= execv("kaydet", NULL);
			perror("");
			close(pipefd[1]);
		}else{
			wait(&c);
			printf("kaydedildi\n");
			break;
		}
	}//end if
	else if(strcmp(answer,"h")==0){
		break;
	}
	}//end while
}//main
