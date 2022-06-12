#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

//rozmiar ramki
const int wiersze=25; //tylko 25, bo pod snake znajduja sie wyniki
const int kolumny=80;
//deklaracje
int i,j,x,y,pole[wiersze][kolumny],glowa,ogon,gloway,gra,buzia,klawisz,kierunek,ramka,wynik,maxwynik;
FILE *plik;

//snejk rusza sie nawet bez wciskania klawiszy, pobiera jeden char z klawiatury)
int getch_noblock(){
	if(_kbhit()){
		return _getch();
	} else return -1;
}

//funkcja tworzaca gre
void setup(){
	//pobieramy wyniki
	plik=fopen("maxwynik.txt","r");
	fscanf(plik,"%d",&maxwynik);
	fclose(plik);
	//ustawianie pierwszej pozycji snejka - w centrum mapy
	x=wiersze/2;
	y=kolumny/2-5;
	//snejk na start ma 5 segmentow
	glowa=5;
	ogon=1;
	//pozycja glowy
	gloway=y;
	//gra=1 - czyli gra trwa
	//gra=1;
	//zaczynamy bez buzi (w klasycznym snake - jablko)
	buzia=0;
	//snejk skierowany w prawo gdy rozpoczniemy gre
	kierunek='d';
	//najpierw nie mamy punktow, wiec wynik=0
	wynik=0;
	//pole w ktorym snejk sie porusza
	for(j=0;j<wiersze;j++){
		for(i=0;i<kolumny;i++){
			pole[j][i]=0;
		}
	}
	//koordy glowy snejka
	for(i=0;i<glowa;i++){
		gloway++;
		pole[x][gloway]=i+1;
	}
}

//czekamy az gracz zacznie gre
void start(){
    printf("\n\n\t\t\t\tNacisnij [enter] by zagrac w gre");
	printf("\n\n\t\t\t\tNacisnij [escape] by zakonczyc gre");
	//dopóki gra jest "wylaczona"
	while(1){
		klawisz=getch_noblock();
		//enter - gramy
		if(klawisz==13){
			gra=1;
			setup();
			break;
		}
		//esc - koniec
		else if(klawisz==27){
			gra=0;
			break;
		}
	}
	system("cls");
}

//ta funkcja sprawia, ze ekran nie ucieka
void reset(){
	HANDLE hOut;
	COORD Position;
	hOut=GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X=0;
	Position.Y=0;
	SetConsoleCursorPosition(hOut,Position);
}
//funkcja rysujaca to, co widzimy
void widok(){
	//ramka,snejk,buzie i wyniki
	for(j=0;j<=wiersze;j++){
		if(j==0){
			for(i=0;i<=kolumny;i++){
				//ramka góra
				if(i==0){
					printf("%c",218);
				}else if(i==kolumny){
					printf("%c\n",191);
				}else{
					printf("%c",196);
				}
			}
		}else if(j==wiersze){
			for(i=0;i<=kolumny;i++){
				//ramka dol
				if(i==0){
					printf("%c",192);
				}else if(i==kolumny){
					printf("%c\n",217);
				}else{
					printf("%c",196);
				}
			}
		}else{
			for(i=0;i<=kolumny;i++){
				//ramka srodek
				if(i==0){
					printf("%c",179);
				}else if(i==kolumny){
					printf("%c\n",179);
				}else if(pole[j][i]==0){
					printf(" ");
				}
				//cialo snejka
				else if(pole[j][i]>0 && pole[j][i]!=glowa){
					printf("%c",177);
				}else if(pole[j][i]==glowa){
					printf("%c",178);
				}
				//buzia
				else if(pole[j][i]==-1){
					printf("%c",1);
				}
			}
		}
	}
	printf("Twoj wynik:%d\n",wynik);
	printf("Twoj najwyzszy wynik:%d",maxwynik);
}
//pozycja buzi
struct buzia{
	int a;
	int b;
};
//funkcja od buzi, generujaca ja w losowym miejscu
void random(){
	//srand, aby za kazdym razem byly inne seedy jablka, time(0), zeby seed sie nie powtarzal
	srand(time(0));
	struct buzia punkt;
	//generuje losowo pozycje jablka w ramkach
	punkt.a +rand()%(wiersze - 2);
	punkt.b=1+rand()%(kolumny - 2);
	//buzia moze sie pojawic tylko wtedy gdy nie ma innych buzi i miejsce jest puste(nie ma w nim np snejka)
	if(buzia==0 && pole[punkt.a][punkt.b]==0){
		pole[punkt.a][punkt.b]=-1;
		buzia=1;
	}
}

//funkcja na koniec gry
void gameover(){
	printf("\a"); //alert dzwiekowy
	system("cls");
	//wyœwietlanie wyniku
	printf("\n\n\t\t\t                                                        __\n");
	printf("\t\t\t .-----.---.-.--------.-----.   .-----.--.--.-----.----|  |\n");
	printf("\t\t\t |  _  |  _  |        |  -__|   |  _  |  |  |  -__|   _|__|\n");
	printf("\t\t\t |___  |___._|__|__|__|_____|   |_____|\\___/|_____|__| |__|\n"); // "\\", bo \ neguje nastepny znak (\n, \t, etc)
	printf("\t\t\t |_____| \n"); //z https://www.coolgenerator.com/ascii-text-generator
	//zapisujemy wynik
	if(wynik>maxwynik){
		printf("\n\n\t\t\t\tGratulacje! Najwyzszy wynik!");
		plik=fopen("maxwynik.txt","w");
		fprintf(plik,"%d",wynik);
		fclose(plik);
	}
	if(wynik>=100){
	printf("\n\n\t\t\t\tWynik: %d. Gratulacje",wynik);}
	else{
	printf("\n\n\t\t\t\tWynik: %d",wynik);}

	printf("\n\n\t\t\t\tNacisnij [enter] by zagrac znowu");
	printf("\n\n\t\t\t\tNacisnij [escape] by zakonczyc gre");
	//dopóki gra jest "wylaczona"
	while(1){
		klawisz=getch_noblock();
		//enter - gramy ponownie
		if(klawisz==13){
			gra=1;
			setup();
			break;
		}
		//esc - koniec
		else if(klawisz==27){
			gra=0;
			break;
		}
	}
	system("cls");
}
//funkcja ruchu snejka
void ruch(){
	//pobieranie z klawiatury
	klawisz=getch_noblock();
	//tolower sprawia, ze zadziala gdy uzyjemy duzych liter
	klawisz=tolower(klawisz);
	//jesli klikniemy awsd to w te strone bedzie isc snejk
	//funkcja abs mówi, ze snejk nie moze isc z prawej do lewej ani z góry na dol
	if(((klawisz=='d'||klawisz=='a')||(klawisz=='s'||klawisz=='w'))&&(abs(kierunek-klawisz)>5)){
		//klawisz ktory klikniemy jest kierunkiem
		kierunek=klawisz;
	}
	//kierunki
	if(kierunek=='d'){
		//jezli kierunek==d to snejk idzie w prawo
		y++;
		//jezli snejk udezy w siebie to gameover
		if(pole[x][y+5]!=0&&pole[x][y+5]!=-1){
			gameover();
		}
		//jezli snejk udezy w sciane to gameover
		if(y+5==kolumny){
			gameover();
		}
		//jeœli snejk trafi w buzie to ogon zwieksza sie o jeden i wynik zwieksza sie o 5
		if(pole[x][y+5]==-1){
			buzia=0;
			ogon--;
			wynik+=5;
		}
		glowa++;
		pole[x][y+5]=glowa;
		}
	//to samo co u góry tylko w lewo
	if(kierunek=='a'){
		y--;
		if(pole[x][y+5]!=0&&pole[x][y+5]!=-1){
			gameover();
		}
		if(y+5==0){
			gameover();
		}
		if(pole[x][y+5]==-1){
			buzia=0;
			ogon--;
			wynik+=5;
		}
		glowa++;
		pole[x][y+5]=glowa;
	}
	//to samo co u góry tylko w dól
	if(kierunek=='s'){
		x++;
		if(pole[x][y+5]!=0&&pole[x][y+5]!=-1){
			gameover();
		}
		if(x==wiersze){
			gameover();
		}
		if(pole[x][y+5]==-1){
			buzia=0;
			ogon--;
			wynik+=5;
		}
		glowa++;
		pole[x][y+5]=glowa;
	}
	//to samo co u góry tylko w góre
	if(kierunek=='w'){
		x--;
		if(pole[x][y+5]!=0  &&pole[x][y+5]!=-1){
			gameover();
		}
		if(x==0){
			gameover();
		}
		if(pole[x][y+5]==-1){
			buzia=0;
			ogon--;
			wynik+=5;
		}
		glowa++;
		pole[x][y+5]=glowa;
	}
}
//funckja sprawia ze ogon sie porusza
void ogonek(){
	for(j=0;j<wiersze;j++){
		for(i=0;i<kolumny;i++){
			if(pole[j][i]==ogon){
				pole[j][i]=0;
			}
		}
	}
	ogon++;
}

int main() {
    system("color F0"); //zmienia kolor konsoli
    start();
	setup();
	while(gra){
		widok();
		reset();
		random();
		ruch();
		ogonek();
		//sleep spowalnia snejka, upraszczajac gre
		Sleep(5);
	}
	return 0;
}
