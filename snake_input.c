#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>

/*
prima lettera del file
0=input deve scrivere
1=output deve eseguire
2=output ha eseguito

3=output deve scrivere
4=input deve eseguire
5=input ha eseguito


comandi
14: -♫-=cambia chi scrive
15: -☼-=chiudi tutto
16: -►-
17: -◄-
18: -↕-
19: -‼-
20: -¶-
21: -§-
22: -▬-
23: -↨-
24: -↑-
25: -↓-
26: -→-
27: -←-
28: -∟-
29: -↔-
30: -▲-
31: -▼-
*/

void op_canc_cl(FILE *a){
	a=fopen("input.txt","w");
	if(a==NULL){
		printf("error: could not load file");
	}
	fclose(a);
}


int main(){
	FILE *a,*a2;
	char comando,cExit;
	int i=0;
	
	//system("START snake_output.exe");//apro l'altro programma
	
	
	a=fopen("input.txt","w");
	if(a==NULL){
		printf("errore");
	}
	fputc('?',a);
	fclose(a);
	
	//aspetto
	printf("execute the other script");
	do{
		a=fopen("input.txt","r");
		comando=fgetc(a);
		fclose(a);
		if(comando!='?'&&comando!='!'){
			a=fopen("input.txt","a");
			fputc('?',a);
			fclose(a);
		}
		//printf("aspetto  ");
		
	}while(comando!='!');
	
	a=fopen("input.txt","w");
	fputc('0',a);
	fclose(a);
	system("CLS");
	
	printf("terminale per i controlli\n");
	//loop invifito di funzionamento
	while(1){
		//printf("ciclo  ");
		a=fopen("input.txt","r");//prendo comando
		comando=fgetc(a);
		fclose(a);
		
		if(comando=='0'){//input deve scrivere -> scrivo e rendo primo carattere '1'
			a=fopen("input.txt","w");
			if(a==NULL){
				printf("errore");
			}
			comando=getch();
			//printf("%d   %c\n",comando,comando);
			//sistemo fseek
			fseek(a,1,SEEK_SET);
			fputc(comando,a);
			//mocifico carattere 1
			fseek(a,0,SEEK_SET);
			fputc('1',a);
			fclose(a);
		}
		
		if(comando=='1'){//output deve eseguire -> non faccio nulla
			
		}
		
		if(comando=='2'){//output ha eseguito -> rendo primo carattere '0' (se il comnado e' cambia chi scrive allora salto questo stato)
				a=fopen("input.txt","w");
				if(a==NULL){
					printf("errore");
				}
				fputc('0',a);
				fclose(a);
		}
		
		
		if(comando=='3'){//output deve scrivere
			//il programma deve solo aspettare
		}
		
		if(comando=='4'){//input deve leggere
			//prendo comando
			a=fopen("input.txt","r");
			comando=fgetc(a);
			comando=fgetc(a);
			fclose(a);
			
			//decifro comando
			if(comando==15){//chiudo tutto
				op_canc_cl(a);
				exit (0);
			}
			
		}
		
		if(comando=='5'){//input ha letto
			
		}
		
		
	}
	
	op_canc_cl(a);
}



/*
if(a==NULL){
	printf("errore");
}
*/









