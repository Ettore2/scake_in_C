#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <time.h>

#define nPulsantiM1 3
#define nPulsantiM2 5
#define nPulsantiMP 3 
#define nPulsantiMWL 2 
#define dMaxCampo 31


void op_canc_cl(FILE *a){
	a=fopen("input.txt","w");
	if(a==NULL){
		printf("error: could not load file");
	}
	fclose(a);
}
/*
prima lettera del file
0=input deve scrivere
1=output deve eseguire
2=output ha eseguito

3=output deve scrivere
4=input deve eseguire
5=input ha eseguito


comandiì
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


file fuoto=-1
invio=10
cancello=8


stato 0=menu 1=inizio gioco 2=menu tasti 3=esci 4=sto giocando 5=gioco in pausa


-77: -│-
-70: -║-
-69: -╗-
-68: -╝-
-65: -┐-
-64: -└-
-60: -─-
-56: -╚-
-55: -╔-
-51: -═-
-39: -┘-
-38: -┌-
-61: -├-
-76: -┤-


gioco
-80: -░- bordo
-37: -█- serpente
40: -(- mela     (40 e 41->()   )

statoGioco
0=devo iniziare    1=nel gioco    2=in pausa
*/


int main(){
	srand(time(NULL));
	FILE *a,*a2;
	int stato=0,     finito=0;
	char scritteM1[nPulsantiM1]/*n pulsanti*/[2]/*0->of 1->on*/[24]/*stringa*/={ {{-38,-60,-60,-60,-60,-60,-65,10,-77,'S','T','A','R','T',-77,10,-64,-60,-60,-60,-60,-60,-39,0},{-55,-51,-51,-51,-51,-51,-69,10,-70,'S','T','A','R','T',-70,10,-56,-51,-51,-51,-51,-51,-68,0}}, {{-38,-60,-60,-60,-60,-60,-65,10,-77,'M','E','N','U',' ',-77,10,-64,-60,-60,-60,-60,-60,-39,0},{-55,-51,-51,-51,-51,-51,-69,10,-70,'M','E','N','U',' ',-70,10,-56,-51,-51,-51,-51,-51,-68,0}}, {{-38,-60,-60,-60,-60,-60,-65,10,-77,'E','X','I','T',' ',-77,10,-64,-60,-60,-60,-60,-60,-39,0},{-55,-51,-51,-51,-51,-51,-69,10,-70,'E','X','I','T',' ',-70,10,-56,-51,-51,-51,-51,-51,-68,0}} };
	int direzioni2[4]={'8','0','4','6'};/*su giu sinistra destra*/
	int pMenu1=0,pMenu2=0;
	int comando,comando2,comandoT,scelto=0;
	int tastoOccup;
	//variabili per gioco
	int giocando,campo[dMaxCampo][dMaxCampo],dCampo=17,serpente[2][dMaxCampo*dMaxCampo],lSerpente,lSerpenteTeorica,ingrandire,punteggio,direzione,dImp,pMenup;
	int scritta=0,pMenuwl;
	//variabili indice
	int i,j,k;
	/* stampo tutte le scritte
	printf("\n\n");
	printf("start on\n%s\n",scritteM1[0][0]);
	printf("start of\n%s\n",scritteM1[0][1]);	
	printf("menu on\n%s\n",scritteM1[1][0]);
	printf("menu of\n%s\n",scritteM1[1][1]);	
	printf("exit on\n%s\n",scritteM1[2][0]);
	printf("exit of\n%s\n",scritteM1[2][1]);
	*/
	
	
	//resetto file
	a=fopen("input.txt","w");
	if(a==NULL){
		printf("errore");
	}
	fclose(a);
	
	//aspetto apertura entrambi file
	printf("execute the other script");
	a=fopen("input.txt","r");
	do{
		a2=a;
		comando=fgetc(a2);
		//printf("aspetto comando:%c",comando);
	}while(comando!='?');
	fclose(a);
	a=fopen("input.txt","w");
	fputc('!',a);
	fclose(a);
	system("CLS");
	
	
	
	
	//stampo primo menu 1
	printf("\n%s\n\n",scritteM1[0][1]);	
	printf("%s\n\n",scritteM1[1][0]);	
	printf("%s\n",scritteM1[2][0]);
	
	
	while(1){//ciclo infinito di scrittura/lettura
		//printf("ciclo ");
		//prendo comando (carattere 1)
		a=fopen("input.txt","r");
		comando=fgetc(a);
		fclose(a);
		//printf("  %c  ",comando);
		if(comando!=-1){//se ho preso qualcosa
			//printf(" comando!=-1 -> %c ",comando);
			
			if(comando=='0'){//input deve scrivere -> non faccio nulla
				
			}
			
			if(comando=='1'){//output deve eseguire -> eseguo il comando e modifico prima cifra
				//prendo comando 2
				a=fopen("input.txt","r");
				if(a==NULL){
					printf("errore");
				}
				comando2=fgetc(a);
				comando2=fgetc(a);
				//printf("\ncomanod2:%d->%c\n",comando2,comando2);
				fclose(a);
				//eseguo il comando
				scelto=0;
				if(stato==0&&scelto==0){//sono nel menu
				scelto=1;
					//printf("su %d giu %d sinistra %d destra %d comando2 %d\n",direzioni2[0],direzioni2[1],direzioni2[2],direzioni2[3],comando2);
					//printf("su %c giu %c sinistra %c destra %c comando2 %c\n",direzioni2[0],direzioni2[1],direzioni2[2],direzioni2[3],comando2);
					if(comando2==13){//invio
						//printf("invio");
						switch (pMenu1){
							case 0:
								stato=1;//play
							break;
							case 1:
								stato=2;//menu
							break;
							case 2:
								stato=3;//exit
							break;
						}
					}
					
					//mi sposto
					if(comando2==direzioni2[0]||comando2=='w'){
						pMenu1=(pMenu1+nPulsantiM1-1)%nPulsantiM1;
					}
					if(comando2==direzioni2[1]||comando2=='s'){
						pMenu1=(pMenu1+1)%nPulsantiM1;
					}
					
					//faccio cose di avvio stati
					if(stato==2){//menu2
						pMenu2=0;
					}
					if(stato==3){//exit
						a=fopen("input.txt","w");
						fseek(a,1,SEEK_SET);
						fputc(15,a);
						fseek(a,0,SEEK_SET);
						fputc('4',a);
						fclose(a);
						exit (0);
					}
					if(stato==1){//play
						//inposto variabili per giocare
						giocando=0;
						punteggio=0;
						//inizializzo campo
						//riempio campo con tutti spazzi
						for(i=0;i<dCampo;i++){//X
							for(j=0;j<dCampo+2;j++){//Y
								campo[i][j]=' ';
							}
						}
						//piazzo serpente
						campo[(dCampo-1)/2][(dCampo-1)/2]=-37;
						//imposto prima posizione del serpente
						serpente[0][0]=(dCampo-1)/2;
						serpente[1][0]=(dCampo-1)/2;
						//piazzo mele
						for(i=0;i<4;i++){
							do{
								j=rand()%dCampo;
								k=rand()%dCampo;
							}while(campo[j][k]!=' ');
							campo[j][k]=40;
						}
					}
				}
				
				if(stato==1&&scelto==0){//devo iniziare il gioco
					//printf("dentro start");
					scelto=1;
					if(comando2==13){//torno al menu 1
						//printf("  dentro if di invio  ");
						stato=0;
						pMenu1=0;
						//printf("  stato=0  ");
					}
					//printf("prima di leggere direzione");
					if(comando2=='w'||comando2==direzioni2[0]||comando2=='s'||comando2==direzioni2[1]||comando2=='a'||comando2==direzioni2[2]||comando2=='d'||comando2==direzioni2[3]){
						giocando=1;
						punteggio=0;
						lSerpente=1;
						lSerpenteTeorica=4;
						ingrandire=3;
						stato=4;
						dImp=-1;
						//decifro direzione
						if(comando2=='w'||comando2==direzioni2[0]){//direzione su
						direzione=0;
						}
						if(comando2=='s'||comando2==direzioni2[1]){//direzione giu
						direzione=1;
						}
						if(comando2=='a'||comando2==direzioni2[2]){//direzione sinistra
						direzione=2;
						}
						if(comando2=='d'||comando2==direzioni2[3]){//direzione destra
						direzione=3;
						}
						//printf("\n  decisione decifrata in s1: %d  \n",direzione);
					}
				}
				
				if(stato==2&&scelto==0){//sono nel menu 2
					//printf("invio su menu");
					scelto=1;
					if(comando2=='w'||comando2=='s'||comando2=='a'||comando2=='d'||comando2==13||pMenu2==4){
						if(comando2==13){//invio (torno al menu 1)
							pMenu1=0;
							stato=0;
						}
						if(comando2=='w'){
							pMenu2=(pMenu2+nPulsantiM2-1)%nPulsantiM2;
						}
						if(comando2=='s'){
							pMenu2=(pMenu2+1)%nPulsantiM2;
						}
						if(comando2=='a'&&pMenu2==4&&dCampo>3){
							dCampo=dCampo-2;
						}
						if(comando2=='d'&&pMenu2==4&&dCampo<dMaxCampo){
							dCampo=dCampo+2;
						}
					
					}else{//modifico i tasti secondari
						if(comando2!='2'){
							tastoOccup=-1;
							for(i=0;i<nPulsantiM2;i++){//trovo se il nuovo pulsante e' gia usato
								if(i!=4&&comando2==direzioni2[i]){
									tastoOccup=i;
								}
							}
							if(tastoOccup==-1){//cambio tasti secondari
								direzioni2[pMenu2]=comando2;
							}else{
								i=direzioni2[tastoOccup];
								direzioni2[tastoOccup]=direzioni2[pMenu2];
								direzioni2[pMenu2]=i;
							}
						}
					}
				}
				
				if(stato==3&&scelto==0){//exit inutile, eseguo l'exit in stato 0
					//printf("invio su exit");
					scelto=1;
					
				}
				
				if(stato==4&&scelto==0){//sto giocando
					//printf("dentro sto giocando");
					scelto=1;
					giocando=1;
					if(comando2==13){//metto in pausa
						stato=5;
						giocando=0;
						pMenup=0;
					}
					if((comando2=='w'||comando2==direzioni2[0])&&dImp!=0){//direzione su
						direzione=0;
					}
					if((comando2=='s'||comando2==direzioni2[1])&&dImp!=1){//direzione giu
						direzione=1;
					}
					if((comando2=='a'||comando2==direzioni2[2])&&dImp!=2){//direzione sinistra
						direzione=2;
					}
					if((comando2=='d'||comando2==direzioni2[3])&&dImp!=3){//direzione destra
						direzione=3;
					}
					//printf("\n\n  Decisione decifrata in s4: %d (comando2:%c)\n",direzione,comando2);
				}
				
				if(stato==5&&scelto==0){//sono in pausa
					scelto=1;
					if(comando2==13){//invio
						//printf("invio");
						switch (pMenup){
							case 0:
								stato=4;//continue
								giocando=1;
							break;
							case 1:
								stato=1;//restart
								
							break;
							case 2:
								stato=0;//quit
							break;
						}
					}
					
					//mi sposto
					if(comando2==direzioni2[0]||comando2=='w'){
						pMenup=(pMenup+nPulsantiMP-1)%nPulsantiMP;
					}
					if(comando2==direzioni2[1]||comando2=='s'){
						pMenup=(pMenup+1)%nPulsantiMP;
					}
					
					//sistemo campo per restart
					if(stato==1){//play (restart)
						//inposto variabili per giocare
						giocando=0;
						punteggio=0;
						//inizializzo campo
						//riempio campo con tutti spazzi
						for(i=0;i<dCampo;i++){//X
							for(j=0;j<dCampo+2;j++){//Y
								campo[i][j]=' ';
							}
						}
						//piazzo serpente
						campo[(dCampo-1)/2][(dCampo-1)/2]=-37;
						//imposto prima posizione del serpente
						serpente[0][0]=(dCampo-1)/2;
						serpente[1][0]=(dCampo-1)/2;
						//piazzo mele
						for(i=0;i<4;i++){
							do{
								j=rand()%dCampo;
								k=rand()%dCampo;
							}while(campo[j][k]!=' ');
							campo[j][k]=40;
						}
					}
				}
				
				if((stato==6||stato==7)&&scelto==0){//menu sconfitta e vittoria
					scelto=1;
					if(comando2==13){//invio
						//printf("invio");
						switch (pMenuwl){
							case 0:
								stato=1;//restart
							break;
							case 1:
								stato=0;//quit
								pMenu1=0;
							break;
						}
					}
					
					//mi sposto
					if(comando2==direzioni2[0]||comando2=='w'){
						pMenuwl=(pMenuwl+nPulsantiMWL-1)%nPulsantiMWL;
					}
					if(comando2==direzioni2[1]||comando2=='s'){
						pMenuwl=(pMenuwl+1)%nPulsantiMWL;
					}
					
					//sistemo variabili per start
					if(stato==1){//play (restart)
						//inposto variabili per giocare
						giocando=0;
						punteggio=0;
						//inizializzo campo
						//riempio campo con tutti spazzi
						for(i=0;i<dCampo;i++){//X
							for(j=0;j<dCampo+2;j++){//Y
								campo[i][j]=' ';
							}
						}
						//piazzo serpente
						campo[(dCampo-1)/2][(dCampo-1)/2]=-37;
						//imposto prima posizione del serpente
						serpente[0][0]=(dCampo-1)/2;
						serpente[1][0]=(dCampo-1)/2;
						//piazzo mele
						for(i=0;i<4;i++){
							do{
								j=rand()%dCampo;
								k=rand()%dCampo;
							}while(campo[j][k]!=' ');
							campo[j][k]=40;
						}
					}
					
				}
				
				//stampa schermate (apparte schermata di gioco)
				//printf("\nprima system cls ");
				system("cls");
				//printf(" dopo system cls\n");
				if(stato==0){//stampo il nuovo menu
					if(pMenu1==0){
						printf("\n%s\n",scritteM1[0][1]);
					}else{
						printf("\n%s\n",scritteM1[0][0]);
					}
					if(pMenu1==1){	
						printf("\n%s\n",scritteM1[1][1]);	
					}else{
						printf("\n%s\n",scritteM1[1][0]);
					}
					if(pMenu1==2){
					printf("\n%s\n",scritteM1[2][1]);
					}else{
						printf("\n%s\n",scritteM1[2][0]);
					}
					//printf("\npMenu1=%d",pMenu1);
				}
				if(stato==1){//stampo campo 0
					//stampo cose a cima schermo
					printf("choose a direction to start    chose enter to quit\n\n");
					
					for(i=0;i<dCampo+2;i++){//stampo bordo superiore
						printf("%c%c",-80,-80);
					}
					printf("\n");
					//stampo campo e bordi laterali
					for(j=0;j<dCampo;j++){//Y
						printf("%c%c",-80,-80);//bordo sinistro
						for(i=0;i<dCampo;i++){//X
							if(campo[i][j]==40){//campo
								printf("()");
							}else{
								printf("%c%c",campo[i][j],campo[i][j]);
							}
						}
						printf("%c%c\n",-80,-80);//bordo destro
					}
					for(i=0;i<dCampo+2;i++){//stampo bord inferiore
						printf("%c%c",-80,-80);
					}
					printf("\n");
				}
				if(stato==2){//stampo menu2 aggiornato
						printf("primary buttons: w s a d\n");
						
						if(pMenu2==0){
							printf("-> up        %c\n\n",direzioni2[0]);
						}else{
							printf("  up        %c\n\n",direzioni2[0]);
						}
						if(pMenu2==1){
							printf("-> down      %c\n\n",direzioni2[1]);
						}else{
							printf("  down      %c\n\n",direzioni2[1]);
						}
						if(pMenu2==2){
							printf("-> left      %c\n\n",direzioni2[2]);
						}else{
							printf("  left      %c\n\n",direzioni2[2]);
						}
						if(pMenu2==3){
							printf("-> right     %c\n\n",direzioni2[3]);
						}else{
							printf("  right     %c\n\n",direzioni2[3]);
						}
						if(pMenu2==4){
							printf("-> feald     %dx%d\n",dCampo,dCampo);
						}else{
							printf("  feald     %dx%d\n",dCampo,dCampo);
						}
						if(pMenu2==0||pMenu2==1||pMenu2==2||pMenu2==3){
							printf("choose a key except '2'\n");
						}else{
							printf("\n");
						}
						printf("press enter for giong back");
						//printf("pMenu2=%d",pMenu2);
					}
				//(stato==3)inutile
				//(stato==4)fatto fuori da if(comando!=0)
				if(stato==5){//menu pausa
					//stampo punteggio e informazioni pausa coi giusti spazzi
					i=punteggio;
					j=0;
					while(punteggio>0){//calcolo cifre punteggio
						j++;
						punteggio/=10;
					}
					printf("score: %d",punteggio);
					for(i=0;i<19-j;i++){//stampo spazzi necessari
						printf(" ");
					}
					printf("press enter to pause\n\n");
					
					//stampo menu pausa sopra partita
					for(j=0;j<dCampo+2||j<=10;j++){//12=altezza menu  Y
						for(i=0;i<dCampo+2||i<=5;i++){//10=lunghezza menu  X (ogni i stampa 2 caratteri)
							//stampo menu (skippo parte di campo sovrascritta da lettere menu)
							if(i==0&&j==0){//riga 1 pulsante continue
								if(pMenup==0){
									printf("%c%c%c%c%c%c%c%c%c%c",-55,-51,-51,-51,-51,-51,-51,-51,-51,-69);
								}else{
									printf("%c%c%c%c%c%c%c%c%c%c",-38,-60,-60,-60,-60,-60,-60,-60,-60,-65);
								}
								i+=5;
							}
							if(i==0&&j==1){//riga 2 pulsante continue
								if(pMenup==0){
									printf("%cCONTINUE%c",-70,-70);
								}else{
									printf("%cCONTINUE%c",-77,-77);
								}
									i+=5;
							}
							if(i==0&&j==2){//riga 3 pulsante continue
								if(pMenup==0){
									printf("%c%c%c%c%c%c%c%c%c%c",-56,-51,-51,-51,-51,-51,-51,-51,-51,-68);
									i+=5;
								}else{
									printf("%c%c%c%c%c%c%c%c%c%c",-64,-60,-60,-60,-60,-60,-60,-60,-60,-39);
									i+=5;
								}
							}
							
							if(i==0&&j==4){//riga 1 pulsante continue
								if(pMenup==1){
									printf("%c%c%c%c%c%c%c%c%c%c",-55,-51,-51,-51,-51,-51,-51,-51,-51,-69);
								}else{
									printf("%c%c%c%c%c%c%c%c%c%c",-38,-60,-60,-60,-60,-60,-60,-60,-60,-65);
								}
								i+=5;
							}
							if(i==0&&j==5){//riga 2 pulsante continue
								if(pMenup==1){
									printf("%cRESTART %c",-70,-70);
								}else{
									printf("%cRESTART %c",-77,-77);
								}
								i+=5;
							}
							if(i==0&&j==6){//riga 3 pulsante restart
								if(pMenup==1){
									printf("%c%c%c%c%c%c%c%c%c%c",-56,-51,-51,-51,-51,-51,-51,-51,-51,-68);
								}else{
									printf("%c%c%c%c%c%c%c%c%c%c",-64,-60,-60,-60,-60,-60,-60,-60,-60,-39);
								}
								i+=5;
							}
							
							if(i==0&&j==8){//riga 1 pulsante restart
								if(pMenup==2){
									printf("%c%c%c%c%c%c%c%c%c%c",-55,-51,-51,-51,-51,-51,-51,-51,-51,-69);
								}else{
									printf("%c%c%c%c%c%c%c%c%c%c",-38,-60,-60,-60,-60,-60,-60,-60,-60,-65);
								}
								i+=5;
							}
							if(i==0&&j==9){//riga 2 pulsante quit
								if(pMenup==2){
									printf("%c  QUIT  %c",-70,-70);
								}else{
									printf("%c  QUIT  %c",-77,-77);
								}
								i+=5;
							}
							if(i==0&&j==10){//riga 3 pulsante quit
								if(pMenup==2){
									printf("%c%c%c%c%c%c%c%c%c%c",-56,-51,-51,-51,-51,-51,-51,-51,-51,-68);
								}else{
									printf("%c%c%c%c%c%c%c%c%c%c",-64,-60,-60,-60,-60,-60,-60,-60,-60,-39);
								}
								i+=5;
							}
							
							if(i<dCampo+2&&j<dCampo+2){//campo
								if(i==0){//bordo sinistro
									printf("%c%c",-80,-80);
								}
								if(i==dCampo+1){//bordo destro
									printf("%c%c",-80,-80);
								}
								if(j==0&&i!=0&&i!=dCampo+1){//bordo alto
									printf("%c%c",-80,-80);
								}
								if(j==dCampo+1&&i!=0&&i!=dCampo+1){//bordo basso
									printf("%c%c",-80,-80);
								}
								if(i>0&&i<dCampo+1&&j>0&&j<dCampo+1){//campo effettivo
									if(campo[i-1][j-1]==40){
										printf("()");
									}else{
										printf("%c%c",campo[i-1][j-1],campo[i-1][j-1]);
									}
								}
							}
							
						}
						printf("\n");
					}
					
				}
				if(stato==6||stato==7){//stampo schermata di vittoria/sconfitta
					system("CLS");
					//scritta vittoria/sconfitta
					printf("\n%c%c%c",-60,-60,-76);
					if(stato==7){
					printf("YOU WON");
					}else{
					printf("DEFEAT");
					}
					printf("%c%c%c\n\n",-61,-60,-60);
					
					//stampo pulsanti
					if(pMenuwl==0){// su restart
						printf("%c%c%c%c%c%c%c%c%c\n%cRESTART%c\n%c%c%c%c%c%c%c%c%c",-55,-51,-51,-51,-51,-51,-51,-51,-69,-70,-70,-56,-51,-51,-51,-51,-51,-51,-51,-68);
					printf("\n\n");
						printf("%c%c%c%c%c%c%c%c%c\n%c QUIT  %c\n%c%c%c%c%c%c%c%c%c",-38,-60,-60,-60,-60,-60,-60,-60,-65,-77,-77,-64,-60,-60,-60,-60,-60,-60,-60,-39);
					}else{//su quit
						printf("%c%c%c%c%c%c%c%c%c\n%cRESTART%c\n%c%c%c%c%c%c%c%c%c",-38,-60,-60,-60,-60,-60,-60,-60,-65,-77,-77,-64,-60,-60,-60,-60,-60,-60,-60,-39);
					printf("\n\n");
						printf("%c%c%c%c%c%c%c%c%c\n%c QUIT  %c\n%c%c%c%c%c%c%c%c%c",-55,-51,-51,-51,-51,-51,-51,-51,-69,-70,-70,-56,-51,-51,-51,-51,-51,-51,-51,-68);
					}
					printf("\n\nPUNTEGGIO: %d/%d",punteggio,dCampo*dCampo-4);
				}
			
				//segnalo che ho letto
				a=fopen("input.txt","w");
				if(a==NULL){
					printf("error");
				}
				fputc('2',a);
				fclose(a);
			}//fine comando==1
			//printf("fine comando 1");	
			if(comando=='2'){//output ha eseguito -> non faccio nulla
				//printf("comando==2");
			}
			
			//comandi per comunicazione inversa (inutili)
			if(comando=='3'){//output deve scrivere
				
			}
			if(comando=='4'){//input deve leggere
				
			}
			if(comando=='5'){//input ha letto
				
			}
		}//fine comando !='1
		
		//stampa schermo mentre sto giocando
		
		
		
		
		if(giocando==1){//gioco effettivo
			//printf("\ndentro giocando");
			//printf("sto giocando");
			//campo[dMaxCampo][dMaxCampo], dCampo=17, serpente[2]/*0=x 1=Y*/[dMaxCampo*dMaxCampo], lSerpente, lSerpenteTeorica, ingrandire, punteggio, direzione, dImp
			//in serpente salvo le coordinate
			
			for(i=lSerpente+1;i>0;i--){//retrocedo le parti del serpente (ho una parte in piu che vedro dopo se cancellare)
				//printf("\ni=%d",i);
				serpente[0][i]=serpente[0][i-1];
				serpente[1][i]=serpente[1][i-1];
			}
			//printf("\n1 parti serpente retrocesse");
			//creo nuova testa
			if(direzione==0){//su
				serpente[0][0]=serpente[0][1];
				serpente[1][0]=serpente[1][1]-1;
				dImp=1;
			}
			if(direzione==1){//giu
				serpente[0][0]=serpente[0][1];
				serpente[1][0]=serpente[1][1]+1;
				dImp=0;
			}
			if(direzione==2){//sinistra
				serpente[0][0]=serpente[0][1]-1;
				serpente[1][0]=serpente[1][1];
				dImp=3;
			}
			if(direzione==3){//destra
				serpente[0][0]=serpente[0][1]+1;
				serpente[1][0]=serpente[1][1];
				dImp=2;
			}
			//printf("\ntesta: %d %d    corpo1: %d %d",serpente[0][0],serpente[1][0],serpente[0][1],serpente[1][1]);
			//printf("\n2 nuova testa creata");
			
			if(serpente[0][0]<0||serpente[0][0]>=dCampo||serpente[1][0]<0||serpente[1][0]>=dCampo){//controllo se sono fuori dal campo (guardo coordinate)
				stato=6;
				giocando=0;
				pMenuwl=0;
			}
			//printf("\n3 controllato se sono fuori dal campo");
			if(campo[serpente[0][0]][serpente[1][0]]==40){//controllo se ho mangiato una mela
				punteggio++;
				ingrandire++;
				lSerpenteTeorica++;
				if(lSerpenteTeorica+3<dCampo*dCampo){//se non ho vinto prendendo la mela
					do{
					j=rand()%dCampo;
					k=rand()%dCampo;
					}while(campo[j][k]!=' ');
					campo[j][k]=40;
				}
			}
			//printf("\n4 controllato se ho mangiato una mela");
			if(ingrandire){//ingrandisco serpente
				ingrandire--;
				lSerpente++;
			}else{
				//cancello ultima parte serpente
				campo[serpente[0][lSerpente]][serpente[1][lSerpente]]=' ';
			}
			//printf("\n5 serpente ingrandito");
			if(campo[serpente[0][0]][serpente[1][0]]==-37){//controllo di non essermi scnotrato
				stato=6;
				giocando=0;
				pMenuwl=0;
				//printf("\nscontrato");
			}
			//printf("\n6 controllato scontro");
			if(giocando==1){//posiziono su campo nuova testa
				campo[serpente[0][0]][serpente[1][0]]=-37;
			}
			//printf("\n7 posizionato nuova testa");
			//printf("\n\ngiocando a fine if giocando:%d\ndirezione:%d   dImp:%d\ncomando2:%c",giocando,direzione,dImp,comando2);
			//printf("\n");
			
			if(lSerpente==dCampo*dCampo){//controllo di non aver vinto
				stato=7;
				giocando=0;
				pMenuwl=0;
			}
			
			//stampa schermate
			system("CLS");
			
			if(stato==4){//stampo schermo+campo durante partita
			//printf("chose a direction to start    press enter to quit\n\n");
			//stampo punteggio e informazioni pausa coi giusti spazzi
			//printf("schermo stato 4\n");
			i=punteggio;
			j=0;
			while(i>0){//calcolo cifre punteggio
				j++;
				i/=10;
			}
			printf("score: %d",punteggio);
			for(i=0;i<19-j;i++){//stampo spazzi necessari
				printf(" ");
			}
			printf("press enter to pause\n\n");
			
			//stampo gioco
			for(i=0;i<dCampo+2;i++){//stampo bordo superiore
				printf("%c%c",-80,-80);
			}
			printf("\n");
			//stampo campo e bordi laterali
			for(j=0;j<dCampo;j++){//Y
				printf("%c%c",-80,-80);//bordo sinistro
				for(i=0;i<dCampo;i++){//X
					if(campo[i][j]==40){//campo
						printf("()");
					}else{
						printf("%c%c",campo[i][j],campo[i][j]);
					}
				}
				printf("%c%c\n",-80,-80);//bordo destro
			}
			for(i=0;i<dCampo+2;i++){//stampo bord inferiore
				printf("%c%c",-80,-80);
			}
			printf("\n");
			}
			if(stato==7||stato==6){//stampo prima schermata di vittoria/sconfitta
				system("CLS");
				//scritta vittoria/sconfitta
				printf("\n%c%c%c",-60,-60,-76);
				if(stato==7){
				printf("VICTORY");
				}else{
				printf("DEFEAT");
				}
				printf("%c%c%c\n\n",-61,-60,-60);
				
				//stampo pulsanti
				if(pMenuwl==0){// su restart
					printf("%c%c%c%c%c%c%c%c%c\n%cRESTART%c\n%c%c%c%c%c%c%c%c%c",-55,-51,-51,-51,-51,-51,-51,-51,-69,-70,-70,-56,-51,-51,-51,-51,-51,-51,-51,-68);
					printf("\n\n");
					printf("%c%c%c%c%c%c%c%c%c\n%c QUIT  %c\n%c%c%c%c%c%c%c%c%c",-38,-60,-60,-60,-60,-60,-60,-60,-65,-77,-77,-64,-60,-60,-60,-60,-60,-60,-60,-39);
				}else{//su quit
					printf("%c%c%c%c%c%c%c%c%c\n%cRESTART%c\n%c%c%c%c%c%c%c%c%c",-38,-60,-60,-60,-60,-60,-60,-60,-65,-77,-77,-64,-60,-60,-60,-60,-60,-60,-60,-39);
					printf("\n\n");
					printf("%c%c%c%c%c%c%c%c%c\n%c QUIT  %c\n%c%c%c%c%c%c%c%c%c",-55,-51,-51,-51,-51,-51,-51,-51,-69,-70,-70,-56,-51,-51,-51,-51,-51,-51,-51,-68);
				}
				printf("\n\nSCORE: %d/%d",punteggio,dCampo*dCampo-4);
			}
			
			if(giocando){//sleep
				sleep(1);
			}
		}//fine giocando==1
		
		
		
	}//fine loop infinito di funzionamento
}

/*
if(a==NULL){
	printf("errore");
}
*/








