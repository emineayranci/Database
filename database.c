#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
char *intstr(int number)  //int i string e donusturen fonksiyon
{
    int count=0;
    int numbertmp=number;
    while(numbertmp>0)
    {
        int digit= numbertmp%10;
        numbertmp/=10;
        count++;
    }
    char * value= (char * ) calloc (count,sizeof(unsigned char)  );
    numbertmp=number;
    count--;
    while(numbertmp>0)
    {
        int digit= numbertmp%10;
        numbertmp/=10;
        char x=(char) 48+digit;
        *(value+count)=x;
        count--;
    }

    return value;
}
int main(int argc, char *argv[] ) 
{ 
  
 
    char *sorgu=(char*)calloc(100, sizeof(char));
 
    while (1)
    {
	  int npipefd;
    //named pipe adresi
    char * myfifo = "/tmp/myfifo";
    //adresi pipe yapıyoruz 
    mkfifo(myfifo, 0666);
	char **sorguSonucu[100][100]; 
        //bekleme
        printf("Database>>\n");
        //sorguyu okuyor
        npipefd = open(myfifo,O_RDONLY);
        read(npipefd, sorgu, 100);
	 
        printf("sorgu: %s\n", sorgu);
	
	char **parameters[10][10];
		char *word;
		word = strtok(sorgu, " ");   //sorguyu bosluga gore boluyoruz
		int i=0;
			while(word != NULL){
				strcpy(parameters[i],word);
				i++;
				word = strtok(NULL, " ");
	}
	close(npipefd);
     
       int j=0;
	if(strcmp(parameters[1], "")==0 || strcmp(parameters[2], "")==0 || 
strcmp(parameters[3], "")==0 ){
		  strcat(sorguSonucu,"yanlış sorgu girisi");
// select yazıp calistirinca hata vermesin diye yazdım

	}else{
	
	for(j=0;j<8;j++){ // parametleri dönüyorum 
		   char str1[10];
		   char temp[10]=" ";
		   int count;
		   FILE * fp;
	if(strcmp(parameters[1],"*")==0 && strcmp(parameters[5],"name")==0){ 
			// select * from ...... name = ... ise

		  fp = fopen (parameters[3], "r");// dosyayı okumak için açtım  
		  fscanf(fp, "%s %d", str1, &count);
			while(!feof(fp)){// sonuna kadar gidiyorum
			if(strcmp(parameters[7],str1)==0)  { 
			  strcpy(temp,str1);
			  char *number=intstr(count);

			  strcat(sorguSonucu,str1);//sorgusonucu ve str1 birlesiy
			  strcat(sorguSonucu," ");
			  strcat(sorguSonucu,number);
			  strcat(sorguSonucu," ");
			}//end if
			fscanf(fp, "%s %d", str1, &count);	
			}//end while
			if(strcmp(temp," ")==0){
				strcat(sorguSonucu, "bulunamadı");
			   //eger aranan name de biri yoksa bulunamadi yaziyo
			}
			fclose(fp);
			break;		
		}//end if
      else if(strcmp(parameters[1],"*")==0 && strcmp(parameters[5],"number")==0)  {	        // select * from ...... number = ..
		   
		  fp = fopen (parameters[3], "r");// dosyayı okumak için açtım 
		  fscanf(fp, "%s %d", str1, &count);
			while(!feof(fp)){// sonuna kadar gidiyorum
			int deger=atoi(parameters[7]);
			if(deger==count)  {
			  strcpy(temp,str1);
			  char *number=intstr(count);

  			  strcat(sorguSonucu,str1);
			  strcat(sorguSonucu," ");
			  strcat(sorguSonucu,number);
			  strcat(sorguSonucu," ");

			}
			fscanf(fp, "%s %d", str1, &count);
			}
			if(strcmp(temp," ")==0){
				strcat(sorguSonucu, "bulunamadı");
		    //eger aranan number da biri yoksa bulunamadi yaziyo
			}
        		fclose(fp);
			break;
		}//end else if
    else if(strcmp(parameters[1],"name")==0 && strcmp(parameters[5],"number")==0){               // select name from ..... number =
	
		  fp = fopen (parameters[3], "r");// dosyayı okumak için açtım 
		  
		  fscanf(fp, "%s %d", str1, &count);
			while(!feof(fp)){// sonuna kadar gidiyorum
			int deger=atoi(parameters[7]);
			if(deger==count)  { 

  			  strcat(sorguSonucu,str1);
			  strcat(sorguSonucu," ");
			  char *number=intstr(count);
			  strcpy(temp,number);
			}
			fscanf(fp, "%s %d", str1, &count);
			}
			if(strcmp(temp," ")==0){
				strcat(sorguSonucu, "bulunamadı");
			   //eger aranan number da biri yoksa bulunamadi yaziyo
			}
              		fclose(fp);
			break;

		}//end else if 
    else if(strcmp(parameters[1],"number")==0 && strcmp(parameters[5],"name")==0){                 // select number from ...... name = ... ise
		   
		   fp = fopen (parameters[3], "r");// dosyayı okumak için açtım 
		  
		  fscanf(fp, "%s %d", str1, &count);
			while(!feof(fp)){// sonuna kadar gidiyorum
			if(strcmp(parameters[7],str1)==0)  { 
			   char *number=intstr(count);
			   strcpy(temp,str1);
  			   strcat(sorguSonucu,number);
			   strcat(sorguSonucu," ");

			}
			fscanf(fp, "%s %d", str1, &count);
			
			}
			if(strcmp(temp," ")==0){
				strcat(sorguSonucu, "bulunamadı");
			   //eger aranan name de biri yoksa bulunamadi yaziyo
			}
			
			fclose(fp);
			break;		
		}//end else if
		else if(strcmp(parameters[1],"*")==0){ // select * from 
		 
		   fp = fopen (parameters[3], "r"); 
		  
		  fscanf(fp, "%s %d", str1, &count);
			while(!feof(fp)){
			  char *number=intstr(count);
			  strcat(sorguSonucu,str1);
			  strcat(sorguSonucu," ");
			  strcat(sorguSonucu,number);
			  strcat(sorguSonucu," ");
			  fscanf(fp, "%s %d", str1, &count);	
			}
			   fclose(fp);
			break;		
		}//end else if
		else if(strcmp(parameters[1],"name")==0){ // select name from 

		   fp = fopen (parameters[3], "r");
		  
		  fscanf(fp, "%s %d", str1, &count);
			while(!feof(fp)){
			  strcat(sorguSonucu,str1);
			  strcat(sorguSonucu," ");

			fscanf(fp, "%s %d", str1, &count);
			}
			   fclose(fp);
			break;		
		}//end if
		else if(strcmp(parameters[1],"number")==0){ //select number from 
		   char str1[10];
		   int count;
		   FILE * fp;
		   fp = fopen (parameters[3], "r");
		  
		  fscanf(fp, "%s %d", str1, &count);
			while(!feof(fp)){
			  char *number=intstr(count);
			  strcat(sorguSonucu,number);
			  strcat(sorguSonucu," ");
		          fscanf(fp, "%s %d", str1, &count);
			}
			fclose(fp);
			break;		
		}//end else if
}//end for
} // end if
       	strcat(sorguSonucu,"\n");
	//printf("sorgu sonucu = %s\n", sorguSonucu);
        npipefd = open(myfifo, O_WRONLY);  
        write(npipefd, sorguSonucu,strlen(sorguSonucu)+1); 
	// sorguyu programa gönderdim
        close(npipefd);
	strcpy(sorguSonucu," ");
        sleep(2);
    }//sonsuz döngü
    return 0;


}//main
