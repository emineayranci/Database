#include <stdio.h>
// dosya oluşturma ve yazma kesin çalışıyor 
int main(int argc,char *argv[]){
	
	char **sonuc[100][100];
	read(3, &sonuc, sizeof(sonuc));
 	FILE *file = fopen("sonuc.txt", "a"); // yazmak için dosya oluşturdum 
	fprintf(file,"%s\n",sonuc);// terminalden geleni dosyaya yazdım // ödevde programdan geleni yazıcam 
  	fclose(file);

  return 0;
}
