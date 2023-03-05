/*

Proyecto Programacion: BINGO
Integrantes : Jose Antonio, Andrea Calendario, Luis Navarrete, Angel Ramirez

*/

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <iomanip> 
#include <ctime>
#include <conio.h>
#include <fstream>
#include <unistd.h>
#include <ctype.h>
#include <windows.h>
#define REN 28
#define COL 61

using namespace std;

struct jugadorGanador
{
	char alias[12];
	char modoJuego[20];
	int puntos;
	int contHorizontal;
	int contDiagonal;
	int contCuadrado;
	int contAbierto;
	char timeString[10];
	char dateString[12];
};

enum Colors { 
	BLACK = 0,
	BLUE = 1,
	GREEN = 2,
	CYAN = 3,
	RED = 4,
	MAGENTA = 5,
	BROWN = 6,
	LGREY = 7,
	DGREY = 8,
	LBLUE = 9,
	LGREEN = 10,
	LCYAN = 11,
	LRED = 12,
	LMAGENTA = 13,
	YELLOW = 14,
	WHITE = 15
};

void gotoxy(int x,int y);  
void textcolor(int n);
void portada();
void menu();
void submenu();
void dibujarCuadro(int x1,int y1,int x2,int y2);
void Color(int Background, int Text);
char * captura(string texto);
void validarAlias(char*);
int menuMenu();
//Cuadrado
bool revisar(int *v, int tam, int num);
void mostrarCuadrado(int **tablero1, int **tablero2, int ren, int col, string titulo, string alias1, string alias2,int,int,int,int,int*,int*);
void llenarTableroCuadrado(int **matriz,int ren, int col);
int **pedirEspacio(int ren, int col);
bool revisarTableroCuadrado(int numero,int **m,int ren,int col,int *vector,int & indice, int &acum);
bool revisarSiGanaCuadrado(int **m, int ren, int col);
void shuffle(int *array, int n);
int Cuadrado(int**,int**,string,string,string);
int *unir(int*,int,int*,int);
// Diagonal Principal
void mostrarDiagonal(int**,int**,int,string,string,string,int,int,int,int,int,int*,int*,int,int);
void diagonalPrincipal(char*,char*);
bool revisarTableroDiagonal(int, int**, int, int*, int&,int&);
bool revisarGanadorDiagonal(int** m, int n);
bool revisarDiagonal(int**, int, int);
void llenarMatrizDiagonal(int**, int);
int** asignaEspacioDiagonal(int);
void estadisticasJugador(char *, char*);
void modoEstadisticas(string);
void maxGanador();
// linea horizontal
void lineahorizontal(char*,char*);
void mostrarhorizontal(int**, int**, int ren ,int col, string, string, string, int,int,int,int,int,int,int,int*,int*);
void shufflehorizontal(int *array,int n);
int **pedirespaciohorizontal(int ren, int col);
void llenartablerohorizontal(int **mat,int ren, int col);
void dibujarCuadrohorizontal(int x1, int y1, int x2, int y2);
void Colorhorizontal(int Background, int Text);
void gotoxyhorizontal(int x, int y);
bool revisartablerohorizontal(int numero,int **m,int ren,int col,int *v,int  &indice,int &acum);
bool revisarsiganahorizontal(int **m,int ren, int col);
// carta completa
int **pedirespacioCartaCompleta(int ren,int col);
void llenarCartaCompleta(int **matriz, int ren,int col);
void imprimirCartaCompleta(int **tablero1,int **,int ren,int col, string,string, int, int, int,int,int *,int *);
bool revisarsiganaCartaCompleta(int **m,int ren, int col);
bool revisarCartaCompleta(int numero,int **m,int ren, int col, int *vector, int &indice1,int &);
void dibujarCuadroCartaCompleta(int x1, int y1, int x2, int y2);
void CuadradoCartaCompleta(string alias1, string alias2);
int *unirCartaCompleta(int*v1 ,int t1, int* v2, int t2);
bool revisarCC(int *v, int tam, int num);

int main()
{
	srand ( time(NULL) );
	system("title BINGO");
	portada();
	system("mode con: cols=80 lines=25"); // se reduce el tamaño 80x25
	menuMenu();
}

// funcion que manda a llamar a los otros menus
int menuMenu()
{
	jugadorGanador jugador;
	fstream archivo;
	int op, opc;
	char *alias1, *alias2;
	int **tablero1;
	int **tablero2;
	string titulo = "Bingo Cuadrado";
	tablero1 = pedirEspacio(5,5);
	tablero2 = pedirEspacio(5,5);
	
	alias1 = "pedro";
	do
	{
		do
		{
			menu();
			cin >>op;
		}while(op < 1  || op > 7);
		
		switch(op)
		{
			case 1: system("cls");cout << endl << "Seleccionaste Agregar alias" << endl; 
				alias1 = captura("Dame el primer alias: ");
				alias2 = captura("Dame el segundo alias: ");
				cout << endl << alias1;
				cout << endl << alias2 << endl;
				system("pause");  break;
			case 2: validarAlias(alias1);system("cls");Beep(600,400);cout << endl << "Seleccionaste modo horizontal"<< endl;
					system("mode con: cols=120 lines=28");
					lineahorizontal(alias1,alias2);
					break;
			case 3: validarAlias(alias1);system("cls");Beep(900,400);cout << endl << "Seleccionaste modo carta diagonal"<< endl; 
					system("mode con: cols=120 lines=28");
					diagonalPrincipal(alias1,alias2);
					break;
			case 4: validarAlias(alias1);system("cls");Beep(800,400);cout << endl << "Seleccionaste modo carta completa"<< endl;
					system("mode con: cols=122 lines=28");
					CuadradoCartaCompleta(alias1,alias2);
					//system("pause");
					break;
			case 5: validarAlias(alias1);system("cls");Beep(700,400);cout << endl << "Seleccionaste modo Cuadrado"<< endl;
					llenarTableroCuadrado(tablero1,5,5);
					llenarTableroCuadrado(tablero1,5,5);
					llenarTableroCuadrado(tablero2,5,5);
					llenarTableroCuadrado(tablero2,5,5);
					// se reduce el tamaño 120x28
					system("mode con: cols=120 lines=28");
					Cuadrado(tablero1,tablero2,titulo,alias1,alias2);
					//system("pause"); 
				break;
			case 6 :validarAlias(alias1);Beep(550,400);
		do
		{
			do
			{
				submenu();
				cin >> opc;
				
			}while(op < 1 || op > 7);
			switch(opc)
			{
				case 1: system("cls");Beep(600,400);cout << endl << "Seleccionaste Estadisticas registradas" << endl;
				system("mode con: cols=120 lines=300");
				archivo.open("ganadores.dat",ios::binary|ios::in);
				if(!archivo)
				{
					cerr << "No se pudo abrir el archivo " << endl;
					cin.get();
					return 1;
				}
				while(archivo.read((char *)(& jugador), sizeof (jugadorGanador)))
				{	
					cout << endl;
					cout << endl << "Nombre del jugador: " << jugador.alias;
					cout << endl << "Modo de juego: " << jugador.modoJuego;
					cout << endl << "Puntos: "<< jugador.puntos;
					cout << endl << "Hora: "<< jugador.timeString;
					cout << endl << "Fecha: " << jugador.dateString;
					cout<< endl;
				}
				archivo.close();
				system("pause");break;
				
				case 2: system("cls");Beep(900,400);cout << endl << "Seleccionaste Estadisticas por jugador" << endl; 
				system("mode con: cols=120 lines=180");
				estadisticasJugador(alias1,alias2);
				system("pause");break;
				case 3: system("cls");Beep(800,400);modoEstadisticas("Horizontal"); system("pause");break;
				case 4: system("cls");Beep(700,400);modoEstadisticas("Abierto");  system("pause");break;
				case 5: system("cls");Beep(300,200);modoEstadisticas("Diagonal");  system("pause");break;
				case 6: system("cls");Beep(800,100);modoEstadisticas("Cuadrado");system("pause");break;
				case 7: system("cls");Beep(500,400);
				maxGanador();
				system("pause");
				break;
			}
			
		}while(opc != 8);
		case 7: system("cls");Beep(250,500); cout << endl << "Fin del juego ..."; break;
		}
		
	}while(op != 7);
}

//funcion que decide cual es el maximo ganador de los modos
void maxGanador()
{
	
	
	//struct para guardar datos de los ganadores por modo
	struct maxJugador
	{
		string nombre;
		int veces=0;
		int modo2;
		char modo1;
	}max[100];
	
	system("mode con: cols=100 lines=25");
	fstream archivo;
	int cont = 0;
	char modo[20];
	int mejorhorizontal=0, mejorcompleta=0, mejordiagonal=0, mejorvertical=0;
	int poshorizontal=0, poscompleta=0, posdiagonal=0, posvertical=0;
	int n=0;
	jugadorGanador jugador;
	archivo.open("ganadores.dat",ios::binary|ios::in);
	if(!archivo)
	{
		cerr << "No se pudo abrir el archivo " << endl;
		cin.get();
	}else
	{
		while(archivo.read((char *)(& jugador), sizeof (jugadorGanador)))
		{
			bool x = false;
			for(int i = 0; i<=cont; i++)
			{
				strcpy(modo, jugador.modoJuego);
				//cout<<endl<<modo[0];
				if(!strcmp(jugador.alias,max[i].nombre.c_str()) && modo[0]==max[i].modo1)
				{
					max[i].veces++;
					x = true;
				}
			}
			if(!x)
			{
				max[cont].nombre = jugador.alias;
				max[cont].veces++;
				if(modo[0]=='H')
				{
					max[cont].modo1=modo[0];
					max[cont].modo2=1;
				}
				else if(modo[0]=='A')
				{
					max[cont].modo1=modo[0];
					max[cont].modo2=2;
				}
				else if(modo[0]=='D')
				{
					max[cont].modo1=modo[0];
					max[cont].modo2=3;
				}
				else if(modo[0]=='C')
				{
					max[cont].modo1=modo[0];
					max[cont].modo2=4;
				}
				cont++;
			}
		}
		
		for(int i=0;i<=cont;i++)
		{
			switch(max[i].modo2)
			{
				case 1:
					if(max[i].veces>mejorhorizontal){
						mejorhorizontal=max[i].veces;
						poshorizontal=i;
					}
					break;
				case 2:
					if(max[i].veces>mejorcompleta){
						mejorcompleta=max[i].veces;
						poscompleta=i;
					}
					break;
				case 3:
					if(max[i].veces>mejordiagonal){
						mejordiagonal=max[i].veces;
						posdiagonal=i;
					}
					break;
				case 4:
					if(max[i].veces>mejorvertical){
						mejorvertical=max[i].veces;
						posvertical=i;
					}
					break;
			}
		}
		
	}
	
	if(mejorhorizontal>0)
	{

		cout << endl << "\tEl jugador " << max[poshorizontal].nombre << " es el que mas a ganado en Horizontal con un total de " << max[poshorizontal].veces << " victorias!" << endl;
	} 
	else 
	{

		cout << endl << "No hay ganador en este modo Horizontal :c!" << endl;
	}

	if(mejorcompleta>0)
	{
		cout << endl << "\tEl jugador " << max[poscompleta].nombre << " es el que mas a ganado en Carta Abierta con un total de " << max[poscompleta].veces << " victorias! " << endl;
		
	} 
	else 
	{
		cout << endl << "No hay ganador en este modo Carta Abierta :c!" << endl;
	} 
	
	if(mejordiagonal>0)
	{

		cout << endl << "\tEl jugador " << max[posdiagonal].nombre << " es el que mas a ganado en Diagonal con un total de " << max[posdiagonal].veces << " victorias!" << endl;
		
	} 
	else 
	{

		cout << endl << "No hay ganador en este modo Diagonal :c!" << endl;
	}

	if(mejorvertical>0)
	{

		cout << endl << "\tEl jugador " << max[posvertical].nombre << " es el que mas a ganado en Cuadrado con un total de " << max[posvertical].veces << " victorias!" << endl << endl;

	} 
	else 
	{

		cout << endl << "No hay ganador en este modo Cuadrado :c!" << endl;
	}
	archivo.close();
}

//funcion de estadisticas de los modos de juego
void modoEstadisticas(string texto)
{
	system("mode con: cols=120 lines=90");
	fstream archivo;
	
	bool bandera = false;
	jugadorGanador jugador;
	archivo.open("ganadores.dat",ios::binary|ios::in);
	if(!archivo)
	{
		cerr << "No se pudo abrir el archivo " << endl;
		cin.get();
	}else
	{
		while(archivo.read((char *)(& jugador), sizeof (jugadorGanador)))
		{
				if(!strcmp(texto.c_str(),jugador.modoJuego) )
				{
					cout << endl;
					cout << endl << "Nombre del jugador: " << jugador.alias;
					cout << endl << "Modo de juego: " << jugador.modoJuego;
					cout << endl << "Puntos: "<< jugador.puntos;
					cout << endl << "Hora: "<< jugador.timeString;
					cout << endl << "Fecha: " << jugador.dateString;
					cout<< endl;		
					bandera = true;
				}
		}
	}
	if(bandera == false)
	{
		cout << endl << "Nadia a ganado en " << texto << " aun :c" << endl;
	}
	archivo.close();
	
}

//funcion de estadisticas por jugador
void estadisticasJugador(char *alias1, char*alias2)
{
	fstream archivo;
	bool bandera = false;
	jugadorGanador jugador;
	archivo.open("ganadores.dat",ios::binary|ios::in);
	char *alias3 = new char[15];
	cout << endl << "Dame el alias que deseas buscar: ";
	fflush(stdin);
	cin.getline(alias3,15);
	if(!archivo)
	{
		cerr << "No se pudo abrir el archivo " << endl;
		cin.get();
	}else
	{
		while(archivo.read((char *)(& jugador), sizeof (jugadorGanador)))
		{
				if(!strcmp(alias3,jugador.alias) )
				{
					cout << endl;
					cout << endl << "Nombre del jugador: " << jugador.alias;
					cout << endl << "Modo de juego: " << jugador.modoJuego;
					cout << endl << "Puntos: "<< jugador.puntos;
					cout << endl << "Hora: "<< jugador.timeString;
					cout << endl << "Fecha: " << jugador.dateString;
					cout<< endl;		
					bandera = true;
				}
		}
	}
	if(bandera == false)
	{
		cout << endl << "Su alias no esta registrado :c" << endl;
	}
	archivo.close();
}

//funcion que crea la portada
void portada()
{
	//system("title BINGO");
	// 80 col y 24 ren
	Color(BLACK,YELLOW);
	for(int x=1; x < 118; x++)
	{
		gotoxy(x,1);cout << "-";
		gotoxy(x,28);cout << "-";
		
		if ( x <= 28)
		{
			gotoxy(1,x); cout << "-";
			gotoxy(118,x); cout << "-";
		}
	}

		
gotoxy(32,5);cout << " ________  ___  ________   ________  ________";     
gotoxy(32,6);cout <<"|" << char(92)<<"   __  "<<char(92)<<"|"<<char(92)<<"  "<<char(92)<<"|"<<char(92)<<"   ___  "<<char(92)<<"|"<<char(92)<<"   ____"<<char(92)<<"|"<<char(92)<<"   __  "<<char(92);Sleep(100);
gotoxy(32,7);cout <<""<<char(92)<<" "<<char(92)<<"  "<<char(92)<<"|"<<char(92)<<" /"<<char(92)<<" "<<char(92)<<"  "<<char(92)<<" "<<char(92)<<"  "<<char(92)<<char(92)<<" "<<char(92)<<"  "<<char(92)<<" "<<char(92)<<" "<<char(92)<<"___| "<<char(92)<<" "<<char(92)<<"  "<<char(92)<<"|"<<char(92)<<"  "<<char(92);Sleep(100);
 gotoxy(32,8);cout <<" "<<char(92)<<" "<<char(92)<<"   __  "<<char(92)<<" "<<char(92)<<"  "<<char(92)<<" "<<char(92)<<"  "<<char(92)<<char(92)<<" "<<char(92)<<"  "<<char(92)<<" "<<char(92)<<"  "<<char(92)<<"  __"<<char(92)<<" "<<char(92)<<"  "<<char(92)<<char(92)<<char(92)<<"  "<<char(92);Sleep(100);  
  gotoxy(32,9);cout<<"  "<<char(92)<<" "<<char(92)<<"  "<<char(92)<<"|"<<char(92)<<"  "<<char(92)<<" "<<char(92)<<"  "<<char(92)<<" "<<char(92)<<"  "<<char(92)<<char(92)<<" "<<char(92)<<"  "<<char(92)<<" "<<char(92)<<"  "<<char(92)<<"|"<<char(92)<<"  "<<char(92)<<" "<<char(92)<<"  "<<char(92)<<char(92)<<char(92)<<"  "<<char(92);Sleep(100); 
   gotoxy(32,10);cout <<"   "<<char(92)<<" "<<char(92)<<"_______"<<char(92)<<" "<<char(92)<<"__"<<char(92)<<" "<<char(92)<<"__"<<char(92)<<char(92)<<" "<<char(92)<<"__"<<char(92)<<" "<<char(92)<<"_______"<<char(92)<<" "<<char(92)<<"_______"<<char(92);Sleep(100);
    gotoxy(32,11);cout <<"    "<<char(92)<<"|_______|"<<char(92)<<"|__|"<<char(92)<<"|__| "<<char(92)<<"|__|"<<char(92)<<"|_______|"<<char(92)<<"|_______|";
                                                                                 
	Color(BLACK,WHITE);
	gotoxy(41,15);cout << "UNIVERSIDAD AUTONOMA DE AGUASCALIENTES";Sleep(100);
	Color(YELLOW,RED);
	gotoxy(57,16);cout << "BINGO";Sleep(100);
	Color(BLACK,WHITE);
	gotoxy(49,17);cout << "INGENIERIA EN SISTEMAS";Sleep(100);
	gotoxy(53,18);cout << "PROGRAMACION I";Sleep(100);
	gotoxy(42,19);cout << "PROFESORA : GEORGINA SALAZAR PARTIDA";Sleep(100);
	gotoxy(55,20);printf("0");Sleep(100);
	gotoxy(56,20);printf("5");Sleep(100);
	gotoxy(57,20);printf("/");Sleep(100);
	gotoxy(58,20);printf("1");Sleep(100);
	gotoxy(59,20);printf("3");Sleep(100);
	gotoxy(60,20);printf("/");Sleep(100);
	gotoxy(61,20);printf("2");Sleep(100);
	gotoxy(62,20);printf("0");Sleep(100);
	gotoxy(63,20);printf("2");Sleep(100);
	gotoxy(64,20);printf("1");Sleep(100);
	gotoxy(54,21);cout << "PROYECTO C++";Sleep(100);
	gotoxy(22,22);cout << "INTEGRANTES: JOSE ANTONIO, ANDREA CANDELARIO, ANGEL RAMIREZ, LUIS NAVARRETE" << endl;Sleep(100);
	
	
	Beep(400,500);
	system("pause");
	
	system("cls");
	
	
	int x = 219; //caracter cuadrado
	
	for(int i = 1; i < 18; i++)
	{
		Sleep(20);
		gotoxy(55,8);cout <<  "    _________";		 
		gotoxy(55,9);cout <<  "  /  =======  "<<char(92);  
		gotoxy(55,10);cout << " /  __________ "<<char(92);   
		gotoxy(55,11);cout << " | ___________  |";  
		gotoxy(55,12);cout << " | | -        | |";
		gotoxy(55,13);cout << " | |          | |";  
		gotoxy(55,14);cout << " | |__________| |"; 
		gotoxy(55,15);cout <<" " <<char(92) << "=____________/";
		gotoxy(55,16);cout << "  / ********** "<<char(92);                     
		gotoxy(55,17);cout << " /  ::::::::::: "<<char(92);                 
		gotoxy(55,18);cout << "(________________)";
		
	}
	gotoxy(62,13);cout << " 8%" << endl;Sleep(150);
	
	system("cls");
	
	for(int i = 1; i < 18; i++)
	{
		Sleep(20);
		gotoxy(55,8);cout <<  "    _________";		 
		gotoxy(55,9);cout <<  "  /  =======  "<<char(92);  
		gotoxy(55,10);cout << " /  __________ "<<char(92);   
		gotoxy(55,11);cout << " | ___________  |";  
		gotoxy(55,12);cout << " | | -        | |";
		gotoxy(55,13);cout << " | |          | |";  
		gotoxy(55,14);cout << " | |__________| |"; 
		gotoxy(55,15);cout <<" " <<char(92) << "=____________/";
		gotoxy(55,16);cout << "  / ********** "<<char(92);                     
		gotoxy(55,17);cout << " /  ::::::::::: "<<char(92);                 
		gotoxy(55,18);cout << "(________________)";
		
	}
	gotoxy(62,13);cout << " 25%" << endl;Sleep(150);
	
	system("cls");
	
	for(int i = 1; i < 18; i++)
	{
		Sleep(20);
		gotoxy(55,8);cout <<  "    _________";		 
		gotoxy(55,9);cout <<  "  /  =======  "<<char(92);  
		gotoxy(55,10);cout << " /  __________ "<<char(92);   
		gotoxy(55,11);cout << " | ___________  |";  
		gotoxy(55,12);cout << " | | -        | |";
		gotoxy(55,13);cout << " | |          | |";  
		gotoxy(55,14);cout << " | |__________| |"; 
		gotoxy(55,15);cout <<" " <<char(92) << "=____________/";
		gotoxy(55,16);cout << "  / ********** "<<char(92);                     
		gotoxy(55,17);cout << " /  ::::::::::: "<<char(92);                 
		gotoxy(55,18);cout << "(________________)";
		
	}
	gotoxy(62,13);cout << " 45%" << endl;Sleep(150);
	
	system("cls");
	
	for(int i = 1; i < 18; i++)
	{
		Sleep(20);
		gotoxy(55,8);cout <<  "    _________";		 
		gotoxy(55,9);cout <<  "  /  =======  "<<char(92);  
		gotoxy(55,10);cout << " /  __________ "<<char(92);   
		gotoxy(55,11);cout << " | ___________  |";  
		gotoxy(55,12);cout << " | | -        | |";
		gotoxy(55,13);cout << " | |          | |";  
		gotoxy(55,14);cout << " | |__________| |"; 
		gotoxy(55,15);cout <<" " <<char(92) << "=____________/";
		gotoxy(55,16);cout << "  / ********** "<<char(92);                     
		gotoxy(55,17);cout << " /  ::::::::::: "<<char(92);                 
		gotoxy(55,18);cout << "(________________)";
		
	}
	gotoxy(62,13);cout << " 55%" << endl;Sleep(150);
	
	system("cls");
	
	for(int i = 1; i < 18; i++)
	{
		Sleep(20);
		gotoxy(55,8);cout <<  "    _________";		 
		gotoxy(55,9);cout <<  "  /  =======  "<<char(92);  
		gotoxy(55,10);cout << " /  __________ "<<char(92);   
		gotoxy(55,11);cout << " | ___________  |";  
		gotoxy(55,12);cout << " | | -        | |";
		gotoxy(55,13);cout << " | |          | |";  
		gotoxy(55,14);cout << " | |__________| |"; 
		gotoxy(55,15);cout <<" " <<char(92) << "=____________/";
		gotoxy(55,16);cout << "  / ********** "<<char(92);                     
		gotoxy(55,17);cout << " /  ::::::::::: "<<char(92);                 
		gotoxy(55,18);cout << "(________________)";
	
	}
	gotoxy(62,13);cout << " 65%" << endl;Sleep(150);
	
	system("cls");
	
	for(int i = 1; i < 18; i++)
	{
		Sleep(20);
		gotoxy(55,8);cout <<  "    _________";		 
		gotoxy(55,9);cout <<  "  /  =======  "<<char(92);  
		gotoxy(55,10);cout << " /  __________ "<<char(92);   
		gotoxy(55,11);cout << " | ___________  |";  
		gotoxy(55,12);cout << " | | -        | |";
		gotoxy(55,13);cout << " | |          | |";  
		gotoxy(55,14);cout << " | |__________| |"; 
		gotoxy(55,15);cout <<" " <<char(92) << "=____________/";
		gotoxy(55,16);cout << "  / ********** "<<char(92);                     
		gotoxy(55,17);cout << " /  ::::::::::: "<<char(92);                 
		gotoxy(55,18);cout << "(________________)";
		
	}
	gotoxy(62,13);cout << " 95%" << endl;Sleep(150);
	
	system("cls");
	
	for(int i = 1; i < 18; i++)
	{
		Sleep(20);
		gotoxy(55,8);cout <<  "    _________";		 
		gotoxy(55,9);cout <<  "  /  =======  "<<char(92);  
		gotoxy(55,10);cout << " /  __________ "<<char(92);   
		gotoxy(55,11);cout << " | ___________  |";  
		gotoxy(55,12);cout << " | | -        | |";
		gotoxy(55,13);cout << " | |          | |";  
		gotoxy(55,14);cout << " | |__________| |"; 
		gotoxy(55,15);cout <<" " <<char(92) << "=____________/";
		gotoxy(55,16);cout << "  / ********** "<<char(92);                     
		gotoxy(55,17);cout << " /  ::::::::::: "<<char(92);                 
		gotoxy(55,18);cout << "(________________)";
		
	}
	gotoxy(62,13);cout << " 100%" << endl;Sleep(150);
}

//funcion que imprime el menu principal
void menu()
{
	system("mode con: cols=80 lines=25"); // 80x25
	system("cls");
	// mandarle las filas y las columnas
	Color(BLACK,DGREY);
	dibujarCuadro(25,5,51,7); // cuadro del titulo 
	dibujarCuadro(0,0,78,24); // cuadro de fondo
	dibujarCuadro(20,8,56,16); // cuadro del menu
	dibujarCuadro(20,17,56,19); // cuadro de la opc
	Color(BLACK,WHITE);
	gotoxy(36,6);cout << "BINGO";
	gotoxy(22,9);cout << "1.- 	Ingresar alias";
	gotoxy(22,10);cout << "2.- 	Modo horizontal";
	gotoxy(22,11);cout << "3.- 	Modo diagonal horizontal";
	gotoxy(22,12);cout << "4.- 	Modo carta completa";
	gotoxy(22,13);cout << "5.- 	Modo Cuadrado";
	gotoxy(22,14);cout << "6.- 	Estadistcias";
	gotoxy(22,15);cout << "7.- 	Salir";
	
	gotoxy(29,18);cout << "Cual opcion deseas? ";
}

//funcion que imprime el submenu
void submenu()
{
	system("mode con: cols=80 lines=25");//80x25
	system("cls");
	// mandarle las filas y las columnas
	Color(BLACK,DGREY);
	dibujarCuadro(28,5,50,7); // cuadro del titulo 
	dibujarCuadro(0,0,78,24); // cuadro de fondo
	dibujarCuadro(15,9,64,18); // cuadro del menu
	dibujarCuadro(20,19,56,21); // cuadro de la opc
	Color(BLACK,WHITE);
	gotoxy(33,6);cout << "ESTADISTICAS";
	gotoxy(20,10);cout << "1.- Estadisticas registradas";
	gotoxy(20,11);cout << "2.- Estadisticas por jugador";
	gotoxy(20,12);cout << "3.- Estadisticas por modo horizontal";
	gotoxy(20,13);cout << "4.- Estadisticas por modo carta completa";
	gotoxy(20,14);cout << "5.- Estadisticas por diagonal principal";
	gotoxy(20,15);cout << "6.- Estadisticas por modo cuadrado";
	gotoxy(20,16);cout << "7.- Maximo ganador por modo";
	gotoxy(20,17);cout << "8.- Regresar al Menu";
	gotoxy(28,20);cout << "Cual opcion deseas? ";
}

//funcion para capturar el alias
char * captura(string texto)
{
	char *alias = new char[100];
	bool band = false;
	int i;
	do
	{
		Beep(250,400);
		cout << endl << texto;
		fflush(stdin);
		cin.getline(alias,100);
		if(strlen(alias) >= 4 && strlen(alias) <= 12)
		{
			if(isalpha(alias[0]) != 0)
			{
				for(i=1; i < strlen(alias); i++)
				{
					if(isalpha(alias[i]) != 0 || isdigit(alias[i]) != 0 || alias[i] == '_')
					{
						
					}else
					{
						cout << endl << "Error el caracter " << alias[i] << " No esta permitido";
						break;
					}
				}
				if (i == strlen(alias))
				{
					band = true;
					cout << endl << "alias correcto!";
				}
			}else
			{
				cout << endl << "Tu primer caracter NO es una letra";
			}
		}else
		{
			cout << endl << "La longitud del alias es incorrecta";
		}
	}while(band == false);
	return alias;
}

// Funciones de Cuadrado

//funcion para modaldiad cuadrado
int Cuadrado(int **tablero1, int **tablero2,string titulo, string alias1, string alias2)
{
	jugadorGanador cuadrado;
	struct tm * time_info;
	struct tm date_info;
	time_t current_time;
	time_t current_date;
	fstream archivo;
	int sum1=0, sum2=0;
	char tipojuego[20]  = {"Cuadrado"};
	int *bolsa = new int[100];
	
	for(int i=0; i < 99; i++)
	{
		bolsa[i] = i + 1;
	}
	shuffle(bolsa,100);
	
	bool tabla1 = false, tabla2 = false;
	int numOk_Tablero1[16], indice1 = 0;
	int numOk_Tablero2[16], indice2 = 0;
	int c=0;
	
	mostrarCuadrado(tablero1,tablero2,5,5,titulo,alias1,alias2,0,0,indice1,indice2,0,0);
	Color(BLACK,RED);
	gotoxy(53,3);cout<<"B"; Sleep(100);
	Color(BLACK,BLUE);
	gotoxy(54,3);cout<<"i"; Sleep(100);
	Color(BLACK,CYAN);
	gotoxy(55,3);cout<<"n"; Sleep(100);
	Color(BLACK,YELLOW);
	gotoxy(56,3);cout<<"g"; Sleep(100);
	Color(BLACK,MAGENTA);
	gotoxy(57,3);cout<<"o"; Sleep(100);
	Color(BLACK,WHITE);
	gotoxy(58,3);cout<<" "; Sleep(100);
	Color(BLACK,GREEN);
	gotoxy(59,3);cout<<"C"; Sleep(100);
	Color(BLACK,RED);
	gotoxy(60,3);cout<<"u"; Sleep(100);
	Color(BLACK,LBLUE);
	gotoxy(61,3);cout<<"a"; Sleep(100);
	Color(BLACK,LCYAN);
	gotoxy(62,3);cout<<"d"; Sleep(100);
	Color(BLACK,LGREEN);
	gotoxy(63,3);cout<<"r"; Sleep(100);
	Color(BLACK,RED);
	gotoxy(64,3);cout<<"a"; Sleep(100);
	Color(BLACK,YELLOW);
	gotoxy(65,3);cout<<"d"; Sleep(100);
	Color(BLACK,BLUE);
	gotoxy(66,3);cout<<"o"; Sleep(100);
	Color(BLACK,WHITE);
	
	
	int *v3;
	v3 = new int[24];
	
	int startX = 40;
	int startY = 23;
	int x = startX;
	int y = startY;
	
	int maxRow = 16;
	int spaceX = 5;
	
	for(int i=0; i < 99; i++)
	{
		Sleep(200);	
		tabla1 = revisarTableroCuadrado(bolsa[i],tablero1,5,5,numOk_Tablero1,indice1,sum1);	
		tabla2 = revisarTableroCuadrado(bolsa[i],tablero2,5,5,numOk_Tablero2,indice2,sum2);
		
		v3 = unir(numOk_Tablero1,indice1,numOk_Tablero2,indice2);
		
		mostrarCuadrado(tablero1,tablero2,5,5,titulo,alias1,alias2,c++,bolsa[i],indice1,indice2,numOk_Tablero1,numOk_Tablero2);
		
		
					
		if (tabla1 == true)
		{
			Color(BLACK,LCYAN);
			gotoxy(3,21);cout << "Felicidades!!! "<< "<"<< alias1 << ">";
			gotoxy(62,21);cout << "Acumulaste: "<< sum1;
			Color(BLACK,WHITE);
			cout << endl << endl << endl;		
				for(int j=0;j < indice1 + indice2; j++)
				{
					gotoxy(x, y);
					cout << v3[j];
					x += spaceX;
					if (x >= startX + maxRow*spaceX) 
					{
						x = startX;
						y++;
					}
				}
			archivo.open("ganadores.dat", ios::binary|ios::out|ios::app);
				if(!archivo)
				{
					cerr << "No se puede abrir el archivo " << endl;
					cin.get();
					return 1;
				}else
				{
					cuadrado.contCuadrado++;
					if(strcmp(alias1.c_str(),cuadrado.alias) && strcmp(tipojuego,cuadrado.modoJuego))
					{
						cuadrado.contCuadrado++;
					}
					strcpy(cuadrado.alias, alias1.c_str());
					strcpy(cuadrado.modoJuego, tipojuego);
					cuadrado.puntos = sum1;	
					time(&current_time);
					time(&current_date);
						
					time_info = localtime(&current_time);
					date_info = * localtime(&current_time);
						
					strftime(cuadrado.timeString, sizeof(cuadrado.timeString), "%H:%M:%S", time_info);
					strftime(cuadrado.dateString, sizeof(cuadrado.dateString), "%d/%m/%Y", &date_info);
						
					archivo.write((char *)(& cuadrado), sizeof(jugadorGanador));
					archivo.close();
					cout << "\t\t" <<endl;
					gotoxy(3,25);system("pause");
					break;	
				}
		}
		
		if (tabla2 == true)
		{
			Color(BLACK,LCYAN);
			gotoxy(3,21);cout << "Felicidades!!! "<< "<"<< alias2 << ">";
			gotoxy(62,21);cout << "Acumulaste: "<< sum2;
			Color(BLACK,WHITE);
			cout << endl << endl << endl;
				for(int j=0;j < indice1 + indice2; j++)
				{
					gotoxy(x, y);
					cout << v3[j];
					x += spaceX;
					if (x >= startX + maxRow*spaceX) 
					{
						x = startX;
						y++;
					}
				}
			archivo.open("ganadores.dat", ios::binary|ios::out|ios::app);
				if(!archivo)
				{
					cerr << "No se puede abrir el archivo " << endl;
					cin.get();
					return 1;
				}else
				{
					
					cuadrado.contCuadrado++;
					if(strcmp(alias1.c_str(),cuadrado.alias) && strcmp(tipojuego,cuadrado.modoJuego))
					{
						cuadrado.contCuadrado++;
					}
					strcpy(cuadrado.alias, alias2.c_str());
					strcpy(cuadrado.modoJuego, tipojuego);
					cuadrado.puntos = sum2;
					time(&current_time);
					time(&current_date);
						
					time_info = localtime(&current_time);
					date_info = * localtime(&current_time);
						
					strftime(cuadrado.timeString, sizeof(cuadrado.timeString), "%H:%M:%S", time_info);
					strftime(cuadrado.dateString, sizeof(cuadrado.dateString), "%d/%m/%Y", &date_info);
					archivo.write((char *)(& cuadrado), sizeof(jugadorGanador));
					archivo.close();
					cout << "\t\t" <<endl;
					gotoxy(3,25);system("pause");
					break;
				}
			
		}
		
	}
}

//funcion que revisa el tablero de modalidad cuadrada
bool revisarTableroCuadrado(int numero,int **m,int ren,int col,int *vector,int & indice, int &sum)
{
	bool exito = false;
	
	for(int i=0; i < ren; i++)
	{
		for(int j=0; j < col; j++)
		{
			if(m[i][j] == numero)
			{
				if(m[4][0] == numero && m[4][0] != 0 )
				{
					vector[indice++] = numero;
					sum += numero;
					m[i][j] = 0;
				}
				if(m[i][0] == numero && m[i][0] != 0 && i != 0 && i != 4 )
				{
					vector[indice++] = numero;
					sum += numero;
					m[i][j] = 0;
				}
				if(m[i][4] == numero && m[i][4] != 0 )
				{
					vector[indice++] = numero;
					sum += numero;
					m[i][j] = 0;
				}
				if(m[0][j] == numero && m[0][j] != 0)
				{
					vector[indice++] = numero;
					sum += numero;
					m[i][j] = 0;
				}
				if(m[4][j] == numero && m[4][j] != 0 && j != 4 && j != 0)
				{
					vector[indice++] = numero;
					sum += numero;
					m[i][j] = 0;
				}
				
				//cout << m[i][j] << "yeah";
				m[i][j] = 0;
				//cout << "yeah2: "<< m[i][j];
				exito = revisarSiGanaCuadrado(m,5,5);
				if ( exito == true)
				{
					return true;
					break;
				}
			}
		}
	}
	
	for(int i=0; i < indice; i++)
	{
		for(int j= i + 1; j < indice; j++)
		{
			if(vector[i] == vector[j] && vector != 0)
			{
				vector[j] = j;
			}
		}
	}
	
	return false;
}

//funcion que revuelve numeros
void shuffle (int *array, int n)
{
	if (n > 1)
	{
		int i;
		for(i = 0; i < n - 1; i++)
		{
			int j = i + rand() / (RAND_MAX / (n - i) + 1);
			int t = array[j];
			array[j] = array[i];
			array[i] = t;
		}
	}
}

//funcion que revisa si gana el tablero de modalidad Cuadrada
bool revisarSiGanaCuadrado(int** m, int ren, int col)
{
    int cont1 = 0;
    bool bandera = false;
    for (int i = 0; i < ren; i++)
    {
            if (i == 0|| i == 4) {
                //revisar toda la fila
                for (int j = 0; j < ren;j++) {
                    if (m[i][j] == 0) {
                        cont1++;
                    }
                }
            }
            else {
                //revisar solo j = 0 y j = 4
                if (m[i][0] == 0) {
                    cont1++;
                }
                if (m[i][4] == 0) {
                    cont1++;
                }
            }
    }
    if (cont1 == 16)
    {
        bandera = true;
    }
    
    return bandera;
}

//funcion que valida si el usuario a entrado a un modo sin ingresar su alias
void validarAlias(char*alias)
{
	if(alias == "pedro")
	{
		system("cls");
		cout << endl << "Ingrese un alias antes de entrar a cualquier modo!"<< endl;
		system("pause");
		menuMenu();
	}
}


//funcion que une vectores
int *unir(int*v1 ,int t1, int* v2, int t2)
{
	int *aux;
	aux = new int [t1 + t2];
	for(int i=0; i < t1; i++)
	{
		aux[i] = v1[i];
	}
	
	for(int i = t1; i < t2 + t1; i++)
	{
		aux[i] = v2[i - t1];
	}
	return aux;
}

//funcion para mostrar el tablero de cualquier modo
void mostrarCuadrado(int **tablero1, int **tablero2, int ren, int col, string titulo, string alias1, string alias2,int cont,int num, int indice1, int indice2,int*vector1, int * vector2)
{
	Color(BLACK,DGREY);
	dibujarCuadro(1,5,118,7); // sub titulos
	dibujarCuadro(1,20,118,22); // sub titulos2
	dibujarCuadro(60,5,60,22); // linea del centro
	dibujarCuadro(1,1,118,26);// marco 
	dibujarCuadro(51,2,68,4); // titulo		
	
	Color(BLACK,WHITE);
	//gotoxy(53,3);cout << titulo;
	gotoxy(3,23);cout << "Todos los numeros que han salido: ";
	
	gotoxy(62,9);cout << "Jugador 2: " << alias2;
	gotoxy(3,11);cout << "Lista de numeros: ";
	
	int startX = 3;
	int startY = 12;
	int x = startX;
	int y = startY;
	
	int maxRow = 8;
	int spaceX = 5;
	for(int j=0;j < indice1; j++)
	{
		gotoxy(x, y);
		cout << vector1[j];
		x += spaceX;
		if (x >= startX + maxRow*spaceX) 
		{
			x = startX;
			y++;
		}
	}
	
	gotoxy(62,11);cout << "Lista de numeros: ";
	
	startX = 62;
	x= startX;
	startY = 12;
	y = startY;
	
	for(int j=0;j < indice2; j++)
	{
		gotoxy(x, y);
		cout << vector2[j];
		x += spaceX;
		if (x >= startX + maxRow*spaceX) 
		{
			x = startX;
			y++;
		}
	}

	gotoxy(62,10);cout << "Aciertos: " << indice2;
	gotoxy(3,9);cout << "Jugador 1: " << alias1;
	gotoxy(3,10);cout << "Aciertos: " << indice1;
	gotoxy(3,6);cout << "Numero generado:"<< setw(3)<< num;
	gotoxy(62,6);cout << "Contador de numeros: " << cont;
	
	for(int i=0; i < ren; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if(tablero1[i][j] == 0)
			{
				Color(RED,WHITE);
			}else
			{
				Color(BLACK,WHITE);
			}
			gotoxy(20 + j * 5,14 + i);	printf(" %d ", tablero1[i][j]);Sleep(15);
		}
		cout << endl;
	}
	Color(BLACK,WHITE);
	
	for(int i=0; i < ren; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if(tablero2[i][j] == 0)
			{
				Color(RED,WHITE);
			}else
			{
				Color(BLACK,WHITE);
			}
			gotoxy(80 + j * 5,14 + i);printf(" %d ", tablero2[i][j]);Sleep(15);
		}
		cout << endl;
	}
	Color(BLACK,WHITE);
}

//funcion para llenar el tablero Cuadrado
void llenarTableroCuadrado(int **matriz,int ren, int col)
{
	int *vec = new int[99];
	int num=0;
	bool exito = true;
	for(int i=0; i < 25; i++)
	{
		while(exito == true)
		{
			num = 1 + rand() % (98 - 1 + 1);
			exito = revisar(vec,i,num);
		}

		vec[i] = num;
		exito = true;
	}
	
	int k=0;
	for(int i=0; i < ren; i++)
	{
		for(int j=0; j < col; j++)
		{
			matriz[i][j] = vec[k++];
		}
	}	
}

//funcion que revisa que no se repitan los numeros aleatorios
bool revisar(int *v, int tam, int num)
{
	bool band = false;
	if(tam == 0 && num !=0 )
	{
		return false;
	}
	
	for(int i=0; i < tam; i++)
	{
		if(v[i] == num || num == 0)
		{
			band = true;
			break;
		}
	}
	return band;
}

void diagonalPrincipal(char* alias1, char* alias2)
{
	srand(time(0));
	string titulo = "Diagonal Principal";
	int indice1 = 0, indice2 = 0, acum1= 0, acum2 = 0;
	bool tabla1 = false, tabla2 = false;
	int* bolsa = new int[100];
	int numOk_tablero1[100];
	int numOk_tablero2[100];
	struct tm * time_info;
	struct tm date_info;
	time_t current_time;
	time_t current_date;
	fstream archivo;
	int c = 1;
	int x = 0;
	int** m1;
	int** m2;
	int n;
	int numerosFinales[40];
	int j;
	char tipojuego[20]  = {"Diagonal"};
	//generar tamaño de matriz
	n = rand()%(6-3+1)+3;

	m1 = asignaEspacioDiagonal(n);
	m2 = asignaEspacioDiagonal(n);

	llenarMatrizDiagonal(m1, n);
	llenarMatrizDiagonal(m2, n);
	
	mostrarDiagonal(m1,m2,n,titulo,alias1,alias2,0,0,0,0,0,0,0,0,0);
	Color(BLACK, RED);
	gotoxy(53, 3); cout << "B"; Sleep(100);
	Color(BLACK, BLUE);
	gotoxy(54, 3); cout << "i"; Sleep(100);
	Color(BLACK, CYAN);
	gotoxy(55, 3); cout << "n"; Sleep(100);
	Color(BLACK, YELLOW);
	gotoxy(56, 3); cout << "g"; Sleep(100);
	Color(BLACK, MAGENTA);
	gotoxy(57, 3); cout << "o"; Sleep(100);
	Color(BLACK, WHITE);
	gotoxy(58, 3); cout << " "; Sleep(100);
	Color(BLACK, GREEN);
	gotoxy(59, 3); cout << "D"; Sleep(100);
	Color(BLACK, RED);
	gotoxy(60, 3); cout << "i"; Sleep(100);
	Color(BLACK, LBLUE);
	gotoxy(61, 3); cout << "a"; Sleep(100);
	Color(BLACK, LCYAN);
	gotoxy(62, 3); cout << "g"; Sleep(100);
	Color(BLACK, LGREEN);
	gotoxy(63, 3); cout << "o"; Sleep(100);
	Color(BLACK, RED);
	gotoxy(64, 3); cout << "n"; Sleep(100);
	Color(BLACK, YELLOW);
	gotoxy(65, 3); cout << "a"; Sleep(100);
	Color(BLACK, BLUE);
	gotoxy(66, 3); cout << "l"; Sleep(100);
	Color(BLACK, WHITE);
	
	//numeros a salir
	for (int i = 0; i < 100; i++)
	{
		bolsa[i] = i + 1;
	}
	
	shuffle(bolsa, 100);
	
	jugadorGanador jugador;
	for (int i = 0; i < 100; i++)
	{
		tabla1 = revisarTableroDiagonal(bolsa[i], m1, n, numOk_tablero1, indice1, acum1);
		tabla2 = revisarTableroDiagonal(bolsa[i], m2, n, numOk_tablero2, indice2, acum2);

		mostrarDiagonal(m1, m2, n, titulo, alias1, alias2, bolsa[i], c++,x,acum1,acum2,numOk_tablero1,numOk_tablero2,indice1,indice2);

		if (tabla1 == true)
		{
			gotoxy(3,24);
			//unir vectores en uno
			for (int i = 0; i<indice1; i++)
			{
				numerosFinales[i] = numOk_tablero1[i];
			}
			for (int i = indice1, j = 0; j<indice2; i++,j++)
			{
				numerosFinales[i] = numOk_tablero2[j];
			}
			//mostrar numeros que han salido
			for(int i = 0; i<(indice1+indice2); i++)
			{
				cout<<setw(3)<<numerosFinales[i];
			}
			
			archivo.open("ganadores.dat", ios::binary|ios::out|ios::app);
			if(!archivo)
			{
				cerr<<"no se puede abrir el archivo "<<endl;
				cin.get();
			}
			else
			{
				
				jugador.contDiagonal++;
				if(strcmp(alias1,jugador.alias) && strcmp(tipojuego,jugador.modoJuego))
				{
					jugador.contDiagonal++;
				}
				strcpy(jugador.alias, alias1);
				strcpy(jugador.modoJuego, tipojuego);
				jugador.puntos=acum1;
				
				time(&current_time);
				time(&current_date);
				
				time_info = localtime(&current_time);
				date_info = * localtime(&current_time);
				
				strftime(jugador.timeString, sizeof(jugador.timeString), "%H:%M:%S", time_info);
				strftime(jugador.dateString, sizeof(jugador.dateString), "%d/%m/%Y", &date_info);
				
				archivo.write((char *)(&jugador), sizeof(jugadorGanador));
			}
			x = 1;
			archivo.close();
			break;
		}
		if (tabla2 == true)
		{
			gotoxy(3,24);
			//unir vectores en uno
			for (int i = 0; i<indice1; i++)
			{
				numerosFinales[i] = numOk_tablero1[i];
			}
			for (int i = indice1, j = 0; j<indice2; i++,j++)
			{
				numerosFinales[i] = numOk_tablero2[j];
			}
			//mostrar numeros que han salido
			for(int i = 0; i<(indice1+indice2); i++)
			{
				cout<<setw(3)<<numerosFinales[i];
			}
			
			archivo.open("ganadores.dat", ios::binary|ios::out|ios::app);
			if(!archivo)
			{
				cerr<<"no se puede abrir el archivo "<<endl;
				cin.get();
			}
			else
			{
				
				jugador.contDiagonal++;
				if(strcmp(alias1,jugador.alias) && strcmp(tipojuego,jugador.modoJuego))
				{
					jugador.contDiagonal++;
				}
				strcpy(jugador.alias, alias2);
				strcpy(jugador.modoJuego, tipojuego);
				jugador.puntos=acum2;
				time(&current_time);
				time(&current_date);
				
				time_info = localtime(&current_time);
				date_info = * localtime(&current_time);
				
				strftime(jugador.timeString, sizeof(jugador.timeString), "%H:%M:%S", time_info);
				strftime(jugador.dateString, sizeof(jugador.dateString), "%d/%m/%Y", &date_info);
				
				archivo.write((char *)(&jugador), sizeof(jugadorGanador));
			}
			x = 2;
			archivo.close();
			
			break;
		}
	}
	mostrarDiagonal(m1, m2, n, titulo, alias1, alias2, bolsa[c-1], c,x,acum1,acum2,numOk_tablero1,numOk_tablero2,indice1,indice2);
	gotoxy(3,25);system("pause");
}

bool revisarTableroDiagonal(int numero, int** m, int n, int* vector, int& indice, int& acum)
{
	bool exito = false;
	bool bandera = false;
	//3x3
	if (n == 3)
	{
		//primer diagonal
		if (m[0][0] == numero)
		{
			vector[indice] = numero;
			indice++;
			acum = acum + numero;
			m[0][0] = 0;
			exito = revisarGanadorDiagonal(m, n);
			if (exito == true)
			{
				bandera = true;
			}
		}
		else if (m[1][1] == numero)
		{
			vector[indice] = numero;
			indice++;
			acum = acum + numero;
			m[1][1] = 0;
			exito = revisarGanadorDiagonal(m, n);
			if (exito == true)
			{
				bandera = true;
			}
		}
		else if (m[2][2] == numero)
		{
			vector[indice] = numero;
			indice++;
			acum = acum + numero;
			m[2][2] = 0;
			exito = revisarGanadorDiagonal(m, n);
			if (exito == true)
			{
				bandera = true;
			}
		}
		//segunda diagonal
		else if (m[0][2] == numero)
		{
			vector[indice] = numero;
			indice++;
			acum = acum + numero;
			m[0][2] = 0;
			exito = revisarGanadorDiagonal(m, n);
			if (exito == true)
			{
				bandera = true;
			}
		}
		else if (m[2][0] == numero)
		{
			vector[indice] = numero;
			indice++;
			acum = acum + numero;
			m[2][0] = 0;
			exito = revisarGanadorDiagonal(m, n);
			if (exito == true)
			{
				bandera = true;
			}
		}
	}
	//4x4
	else if (n == 4)
	{
		//primer diagonal
		if (m[0][0] == numero)
		{
			vector[indice] = numero;
			indice++;
			acum = acum + numero;
			m[0][0] = 0;
			exito = revisarGanadorDiagonal(m, n);
			if (exito == true)
			{
				bandera = true;
			}
		}
		else if (m[1][1] == numero)
		{
			vector[indice] = numero;
			indice++;
			acum = acum + numero;
			m[1][1] = 0;
			exito = revisarGanadorDiagonal(m, n);
			if (exito == true)
			{
				bandera = true;
			}
		}
		else if (m[2][2] == numero)
		{
			vector[indice] = numero;
			indice++;
			acum = acum + numero;
			m[2][2] = 0;
			exito = revisarGanadorDiagonal(m, n);
			if (exito == true)
			{
				bandera = true;
			}
		}
		else if (m[3][3] == numero)
		{
			vector[indice] = numero;
			indice++;
			acum = acum + numero;
			m[3][3] = 0;
			exito = revisarGanadorDiagonal(m, n);
			if (exito == true)
			{
				bandera = true;
			}
		}
		//segunda diagonal
		else if (m[0][3] == numero)
		{
			vector[indice] = numero;
			indice++;
			acum = acum + numero;
			m[0][3] = 0;
			exito = revisarGanadorDiagonal(m, n);
			if (exito == true)
			{
				bandera = true;
			}
		}
		else if (m[1][2] == numero)
		{
			vector[indice] = numero;
			indice++;
			acum = acum + numero;
			m[1][2] = 0;
			exito = revisarGanadorDiagonal(m, n);
			if (exito == true)
			{
				bandera = true;
			}
		}
		else if (m[2][1] == numero)
		{
			vector[indice] = numero;
			indice++;
			acum = acum + numero;
			m[2][1] = 0;
			exito = revisarGanadorDiagonal(m, n);
			if (exito == true)
			{
				bandera = true;
			}
		}
		else if (m[3][0] == numero)
		{
			vector[indice] = numero;
			indice++;
			acum = acum + numero;
			m[3][0] = 0;
			exito = revisarGanadorDiagonal(m, n);
			if (exito == true)
			{
				bandera = true;
			}
		}
	}
	//5x5
	else if (n == 5)
	{
		//primer diagonal
		if (m[0][0] == numero)
		{
			vector[indice] = numero;
			indice++;
			acum = acum + numero;
			m[0][0] = 0;
			exito = revisarGanadorDiagonal(m, n);
			if (exito == true)
			{
				bandera = true;
			}
		}
		else if (m[1][1] == numero)
		{
			vector[indice] = numero;
			indice++;
			acum = acum + numero;
			m[1][1] = 0;
			exito = revisarGanadorDiagonal(m, n);
			if (exito == true)
			{
				bandera = true;
			}
		}
		else if (m[2][2] == numero)
		{
			vector[indice] = numero;
			indice++;
			acum = acum + numero;
			m[2][2] = 0;
			exito = revisarGanadorDiagonal(m, n);
			if (exito == true)
			{
				bandera = true;
			}
		}
		else if (m[3][3] == numero)
		{
			vector[indice] = numero;
			indice++;
			acum = acum + numero;
			m[3][3] = 0;
			exito = revisarGanadorDiagonal(m, n);
			if (exito == true)
			{
				bandera = true;
			}
		}
		else if (m[4][4] == numero)
		{
			vector[indice] = numero;
			indice++;
			acum = acum + numero;
			m[4][4] = 0;
			exito = revisarGanadorDiagonal(m, n);
			if (exito == true)
			{
				bandera = true;
			}
		}
		//segunda diagonal
		else if (m[0][4] == numero)
		{
			vector[indice] = numero;
			indice++;
			acum = acum + numero;
			m[0][4] = 0;
			exito = revisarGanadorDiagonal(m, n);
			if (exito == true)
			{
				bandera = true;
			}
		}
		else if (m[1][3] == numero)
		{
			vector[indice] = numero;
			indice++;
			acum = acum + numero;
			m[1][3] = 0;
			exito = revisarGanadorDiagonal(m, n);
			if (exito == true)
			{
				bandera = true;
			}
		}
		else if (m[2][2] == numero)
		{
			vector[indice] = numero;
			indice++;
			acum = acum + numero;
			m[2][2] = 0;
			exito = revisarGanadorDiagonal(m, n);
			if (exito == true)
			{
				bandera = true;
			}
		}
		else if (m[3][1] == numero)
		{
			vector[indice] = numero;
			indice++;
			acum = acum + numero;
			m[3][1] = 0;
			exito = revisarGanadorDiagonal(m, n);
			if (exito == true)
			{
				bandera = true;
			}
		}
		else if (m[4][0] == numero)
		{
			vector[indice] = numero;
			indice++;
			acum = acum + numero;
			m[4][0] = 0;
			exito = revisarGanadorDiagonal(m, n);
			if (exito == true)
			{
				bandera = true;
			}
		}
	}
	//6x6
	else if (n == 6)
	{
		//primer diagonal
		if (m[0][0] == numero)
		{
			vector[indice] = numero;
			indice++;
			acum = acum + numero;
			m[0][0] = 0;
			exito = revisarGanadorDiagonal(m, n);
			if (exito == true)
			{
				bandera = true;
			}
		}
		else if (m[1][1] == numero)
		{
			vector[indice] = numero;
			indice++;
			acum = acum + numero;
			m[1][1] = 0;
			exito = revisarGanadorDiagonal(m, n);
			if (exito == true)
			{
				bandera = true;
			}
		}
		else if (m[2][2] == numero)
		{
			vector[indice] = numero;
			indice++;
			acum = acum + numero;
			m[2][2] = 0;
			exito = revisarGanadorDiagonal(m, n);
			if (exito == true)
			{
				bandera = true;
			}
		}
		else if (m[3][3] == numero)
		{
			vector[indice] = numero;
			indice++;
			acum = acum + numero;
			m[3][3] = 0;
			exito = revisarGanadorDiagonal(m, n);
			if (exito == true)
			{
				bandera = true;
			}
		}
		else if (m[4][4] == numero)
		{
			vector[indice] = numero;
			indice++;
			acum = acum + numero;
			m[4][4] = 0;
			exito = revisarGanadorDiagonal(m, n);
			if (exito == true)
			{
				bandera = true;
			}
		}
		else if (m[5][5] == numero)
		{
			vector[indice] = numero;
			indice++;
			acum = acum + numero;
			m[5][5] = 0;
			exito = revisarGanadorDiagonal(m, n);
			if (exito == true)
			{
				bandera = true;
			}
		}
		//segunda diagonal
		else if (m[0][5] == numero)
		{
			vector[indice] = numero;
			indice++;
			acum = acum + numero;
			m[0][5] = 0;
			exito = revisarGanadorDiagonal(m, n);
			if (exito == true)
			{
				bandera = true;
			}
		}
		else if (m[1][4] == numero)
		{
			vector[indice] = numero;
			indice++;
			acum = acum + numero;
			m[1][4] = 0;
			exito = revisarGanadorDiagonal(m, n);
			if (exito == true)
			{
				bandera = true;
			}
		}
		else if (m[2][3] == numero)
		{
			vector[indice] = numero;
			indice++;
			acum = acum + numero;
			m[2][3] = 0;
			exito = revisarGanadorDiagonal(m, n);
			if (exito == true)
			{
				bandera = true;
			}
		}
		else if (m[3][2] == numero)
		{
			vector[indice] = numero;
			indice++;
			acum = acum + numero;
			m[3][2] = 0;
			exito = revisarGanadorDiagonal(m, n);
			if (exito == true)
			{
				bandera = true;
			}
		}
		else if (m[4][1] == numero)
		{
			vector[indice] = numero;
			indice++;
			acum = acum + numero;
			m[4][1] = 0;
			exito = revisarGanadorDiagonal(m, n);
			if (exito == true)
			{
				bandera = true;
			}
		}
		else if (m[5][0] == numero)
		{
			vector[indice] = numero;
			indice++;
			acum = acum + numero;
			m[5][0] = 0;
			exito = revisarGanadorDiagonal(m, n);
			if (exito == true)
			{
				bandera = true;
			}
		}
	}
	return bandera;
}
bool revisarGanadorDiagonal(int** m, int n)
{
	bool bandera = false;
	int contador = 0;
	int contador2 = 0;
	if(n==3)
	{
		//primer diagonal
		if (m[0][0] == 0)
		{
			contador++;
		}
		if (m[1][1] == 0)
		{
			contador++;
			contador2++;
		}
		if (m[2][2] == 0)
		{
			contador++;
		}
		//segunda diagonal
		if (m[0][2] == 0)
		{
			contador2++;
		}
		if (m[2][0] == 0)
		{
			contador2++;
		}
		if (contador == 3 || contador2 == 3)
		{
			bandera = true;
		}
		else
		{
			contador = 0;
			contador2 = 0;
		}
	}
	//4x4
	else if (n == 4)
	{
		//primer diagonal
		if (m[0][0] == 0)
		{
			contador++;
		}
		if (m[1][1] == 0)
		{
			contador++;
		}
		 if (m[2][2] == 0)
		{
			contador++;
		}
		 if (m[3][3] == 0)
		{
			contador++;
		}
		//segunda diagonal
		 if (m[0][3] == 0)
		{
			contador2++;
		}
		 if (m[1][2] == 0)
		{
			contador2++;
		}
		 if (m[2][1] == 0)
		{
			contador2++;
		}
		 if (m[3][0] == 0)
		{
			contador2++;
		}
		if (contador == 4 || contador2 == 4)
		{
			bandera = true;
		}
		else
		{
			contador = 0;
			contador2 = 0;
		}
	}
	//5x5
	else if (n == 5)
	{
		//primer diagonal
		if (m[0][0] == 0)
		{
			contador++;
		}
		 if (m[1][1] == 0)
		{
			contador++;
		}
		 if (m[2][2] == 0)
		{
			contador++;
			contador2++;
		}
		 if (m[3][3] == 0)
		{
			contador++;
		}
		 if (m[4][4] == 0)
		{
			contador++;
		}
		//segunda diagonal
		 if (m[0][4] == 0)
		{
			contador2++;
		}
		 if (m[1][3] == 0)
		{
			contador2++;
		}
		 if (m[3][1] == 0)
		{
			contador2++;
		}
		 if (m[4][0] == 0)
		{
			contador2++;
		}
		if (contador == 5 || contador2 == 5)
		{
			bandera = true;
		}
		else
		{
			contador = 0;
			contador2 = 0;
		}
	}
	//6x6
	else if (n == 6)
	{
		//primer diagonal
		if (m[0][0] == 0)
		{
			contador++;
		}
		 if (m[1][1] == 0)
		{
			contador++;
		}
		 if (m[2][2] == 0)
		{
			contador++;
		}
		 if (m[3][3] == 0)
		{
			contador++;
		}
		 if (m[4][4] == 0)
		{
			contador++;
		}
		 if (m[5][5] == 0)
		{
			contador++;
		}
		//segunda diagonal
		 if (m[0][5] == 0)
		{
			contador2++;
		}
		 if (m[1][4] == 0)
		{
			contador2++;
		}
		 if (m[2][3] == 0)
		{
			contador2++;
		}
		 if (m[3][2] == 0)
		{
			contador2++;
		}
		  if (m[4][1] == 0)
		{
			contador2++;
		}
		  if (m[5][0] == 0)
		{
			contador2++;
		}
		if (contador == 6 || contador2 == 6)
		{
			bandera = true;
		}
		else
		{
			contador = 0;
			contador2 = 0;
		}
	}
	return bandera;
}

//funcion que pide espacio a la memoria dinamica
int **pedirEspacio(int ren, int col)
{
	int **aux;
	aux = new int *[ren];
	for(int i=0; i < ren; i++)
		aux[i] = new int[col];
	return aux;
}

int** asignaEspacioDiagonal(int n)
{
	int** m;
	//asignar tamaño a matriz
	m = new int* [n];
	for (int i = 0; i < n; i++)
	{
		m[i] = new int[n];
	}
	return m;
}

void llenarMatrizDiagonal(int** m, int n)
{
	bool band;
	int num;
	//generar valores para matriz
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n;)
		{
			num = 1 + rand() % (99 - 1 + 1);
			band = revisarDiagonal(m, n, num);

			if (band == false)
			{
				m[i][j] = num;
				j++;
			}
		}
	}
}

bool revisarDiagonal(int** m, int n, int num)
{
	bool band = false;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (m[i][j] == num)
			{
				band = true;
				break;
			}
		}
	}
	return band;
}

void mostrarDiagonal(int** tablero1, int** tablero2, int n, string titulo, string alias1, string alias2, int numero, int contador, int x, int acum1, int acum2,int *numOk_tablero1, int *numOk_tablero2,int indice1,int indice2)
{

	
	Color(BLACK, DGREY);
	dibujarCuadro(1, 5, 118, 7); // sub titulos
	dibujarCuadro(1, 20, 118, 22); // sub titulos2
	dibujarCuadro(60, 5, 60, 22); // linea del centro
	dibujarCuadro(1, 1, 118, 26);// marco 
	dibujarCuadro(51, 2, 68, 4); // titulo

	Color(BLACK, WHITE);
	//gotoxy(53,3);cout << titulo;
	gotoxy(62, 9); cout << "Jugador 2: "<< alias2;
	gotoxy(62, 10); cout << "Aciertos: "<<indice2;
	gotoxy(62, 11); cout << "Lista de numeros: ";
	gotoxy(61, 12);
	for(int i=0;i<indice2;i++)
	{
		cout<<setw(3)<<numOk_tablero2[i];
	}
	gotoxy(2, 9); cout << "Jugador 1: " << alias1;
	gotoxy(2, 10); cout << "Aciertos: "<<indice1;
	gotoxy(2, 11); cout << "Lista de numeros: ";
	gotoxy(2, 12);
	for(int i=0;i<indice1;i++)
	{
		cout<<setw(3)<<numOk_tablero1[i];
	}
	Sleep(200);
	gotoxy(3, 6);cout << "Numero generado:"<< setw(3) << numero; 
	Sleep(200);
	gotoxy(62, 6); cout << "Contador de numeros: "<<contador; 
	Color(BLACK, LCYAN);
	if(x == 1)
	{
		gotoxy(62, 21); cout << "Acumulaste: "<<acum1;
		gotoxy(3, 21); cout << "Felicidades!!! "<<alias1;
	}
	else if(x == 2)
	{
		gotoxy(62, 21); cout << "Acumulaste: "<<acum2;
		gotoxy(3, 21); cout << "Felicidades!!! "<<alias2;
	}
	
	Color(BLACK, WHITE);
	gotoxy(3, 23); cout << "Todos los numeros que han salido: ";	

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			Sleep(15);
			if(tablero1[i][j]==0)
			{
				Color(RED, WHITE);
			}
			else
			{
				Color(BLACK, WHITE);
			}
			gotoxy(20 + j * 5, 14 + i); cout << setw(4) << tablero1[i][j];
			
		}
		cout << endl;
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			Sleep(15);
			if(tablero2[i][j]==0)
			{
				Color(RED, WHITE);
			}
			else
			{
				Color(BLACK, WHITE);
			}
			gotoxy(80 + j * 5, 14 + i); cout << setw(4) << tablero2[i][j];
		}
		cout << endl;
	}
	Color(BLACK, WHITE);
}

//funcion que dibuja cuadros
void dibujarCuadro(int x1,int y1,int x2,int y2)
{
	int i;

    for (i = x1 ; i< x2 ; i++){
		gotoxy(i,y1); printf("\304"); //linea horizontal superior
		gotoxy(i,y2); printf("\304"); //linea horizontal inferior
    }

    for (i = y1; i < y2; i++){
		gotoxy(x1,i); printf("\263"); //linea vertical izquierda
		gotoxy(x2,i); printf("\263"); //linea vertical derecha
	}

    gotoxy(x1,y1); printf("\332");
    gotoxy(x1,y2); printf("\300");
    gotoxy(x2,y1); printf("\277");
    gotoxy(x2,y2); printf("\331");
}

void gotoxy(int x,int y)
{
    HANDLE hcon;  
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
    COORD dwPos;  
    dwPos.X = x;  
    dwPos.Y= y;  
    SetConsoleCursorPosition(hcon,dwPos);  
}  

void textcolor(int n)
{ 
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), n); 
}

void Color(int Background, int Text){ 

	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE); 
	int    New_Color= Text + (Background * 16); 

	SetConsoleTextAttribute(Console, New_Color);
}

//funcion modalidad linea horizontal

void lineahorizontal(char*alias1,char*alias2){
	srand(time(NULL));
 	jugadorGanador jugador;
 	char modoJuego[30]  = {"Horizontal"};
	struct tm * time_info;
	struct tm date_info;
	time_t current_time;
	time_t current_date;
	fstream archivo;
     bool tabla1=false,tabla2=false;
    int **tablero1;
    int **tablero2;
    	string titulo = "Linea Horizontal";
    	int c=1;
    	int x=0;
    	int acum1=0,acum2=0;
    	 int *bolsa=new int[99];
    	   int numerosok1[9],indice1=0;
    int numerosok2[9],indice2=0;
    tablero1=pedirespaciohorizontal(3,9);
    tablero2=pedirespaciohorizontal(3,9);
    llenartablerohorizontal(tablero1,3,9);
    llenartablerohorizontal(tablero2,3,9);
    //cout<<endl<<"Alias 1"<<endl<<endl;
     mostrarhorizontal(tablero1, tablero2,3,9, titulo, alias1, alias2, 0, 0,0,0,0,0,0,0,0);
        	Color(BLACK, RED);
	gotoxy(53, 3); cout << "B"; Sleep(100);
	Color(BLACK, BLUE);
	gotoxy(54, 3); cout << "i"; Sleep(100);
	Color(BLACK, CYAN);
	gotoxy(55, 3); cout << "n"; Sleep(100);
	Color(BLACK, YELLOW);
	gotoxy(56, 3); cout << "g"; Sleep(100);
	Color(BLACK, MAGENTA);
	gotoxy(57, 3); cout << "o"; Sleep(100);
	Color(BLACK, WHITE);
	gotoxy(58, 3); cout << " "; Sleep(100);
	Color(BLACK, GREEN);
	gotoxy(59, 3); cout << "H"; Sleep(100);
	Color(BLACK, RED);
	gotoxy(60, 3); cout << "o"; Sleep(100);
	Color(BLACK, LBLUE);
	gotoxy(61, 3); cout << "r"; Sleep(100);
	Color(BLACK, LCYAN);
	gotoxy(62, 3); cout << "i"; Sleep(100);
	Color(BLACK, LGREEN);
	gotoxy(63, 3); cout << "z"; Sleep(100);
	Color(BLACK, RED);
	gotoxy(64, 3); cout << "o"; Sleep(100);
	Color(BLACK, YELLOW);
	gotoxy(65, 3); cout << "n"; Sleep(100);
	Color(BLACK, MAGENTA);
	gotoxy(66, 3); cout << "t"; Sleep(100);
	Color(BLACK, WHITE);
	gotoxy(67, 3); cout << "a"; Sleep(100);
	Color(BLACK, GREEN);
	gotoxy(68, 3); cout << "l"; Sleep(100);
	Color(BLACK, RED);
    //cout<<endl<<"Alias 2"<<endl<<endl;
    //meter los numeros del 1 al 100 en una bolsita
   //int sum1=0,sum2=0;
    for(int i=0;i<99;i++){
        bolsa[i]=i+1;
    }
    //revolver la bolsita
    shufflehorizontal(bolsa,99);
    //revisar que tablero cubre primeros los numeros
    
    //jugadorGanador jugador;
    for(int i=0;i<99;i++){
       
        tabla1=revisartablerohorizontal(bolsa[i],tablero1,3,9,numerosok1,indice1,acum1);
       
        tabla2=revisartablerohorizontal(bolsa[i],tablero2,3,9,numerosok2,indice2,acum2);
        //	numacum= unir(numerosok1,indice1,numerosok2,indice2);
        
       mostrarhorizontal(tablero1, tablero2,3,9, titulo, alias1, alias2, bolsa[i], c++,x,acum1,acum2,indice1,indice2,numerosok1,numerosok2);
       int *numacum;
	numacum=new int[27];
	int j;

        if(tabla1==true){
        		gotoxy(3,24);
		//unir los dos vectores en uno
		for (int i = 0; i < indice1; i++)
	{
		numacum[i]=numerosok1[i];
		}
		for (int i = indice1, j=0;j < indice2;i++, j++)
		{
			numacum[i]=numerosok2[j];
			
			}
			//mostrar numeros que han salido
				for (int i = 0; i < (indice1+indice2); i++)
	{
printf(" %d ", numacum[i]);
			}
			archivo.open("ganadores.dat", ios::binary|ios::out|ios::app);
			if(!archivo)
			{
				cerr<<"no se puede abrir el archivo "<<endl;
				cin.get();
			}
			else
			{
				
				jugador.contHorizontal++;
				if(strcmp(alias2,jugador.alias) && strcmp(modoJuego,jugador.modoJuego))
				{
					jugador.contHorizontal++;
				}
				strcpy(jugador.alias, alias1);
				strcpy(jugador.modoJuego, modoJuego);
				jugador.puntos=acum1;
				time(&current_time);
				time(&current_date);
				
				time_info = localtime(&current_time);
				date_info = * localtime(&current_time);
				
				strftime(jugador.timeString, sizeof(jugador.timeString), "%H:%M:%S", time_info);
				strftime(jugador.dateString, sizeof(jugador.dateString), "%d/%m/%Y", &date_info);
				
				archivo.write((char *)(&jugador), sizeof(jugadorGanador));
			}
			x = 1;
			archivo.close();
     	 	//gotoxy(3,25);system("pause");
				break;
		}
  
        if(tabla2==true){
        	gotoxy(3, 24);
 
		//unir los dos vectores en uno
		for (int i = 0; i < indice1; i++)
	{
		numacum[i]=numerosok1[i];
		}
		for (int i = indice1, j=0;j < indice2;i++, j++)
		{
			numacum[i]=numerosok2[j];
			
			}
			//mostrar numeros que han salido
				for (int i = 0; i < (indice1+indice2); i++)
	{
			printf(" %d ", numacum[i]);
			}
			archivo.open("ganadores.dat", ios::binary|ios::out|ios::app);
			if(!archivo)
			{
				cerr<<"no se puede abrir el archivo "<<endl;
				cin.get();
			}
			else
			{
				jugador.contHorizontal++;
				if(strcmp(alias2,jugador.alias) && strcmp(modoJuego,jugador.modoJuego))
				{
					jugador.contHorizontal++;
				}
				
				strcpy(jugador.alias, alias2);
				strcpy(jugador.modoJuego, modoJuego);
				jugador.puntos=acum2;
				time(&current_time);
				time(&current_date);
				
				time_info = localtime(&current_time);
				date_info = * localtime(&current_time);
				
				strftime(jugador.timeString, sizeof(jugador.timeString), "%H:%M:%S", time_info);
				strftime(jugador.dateString, sizeof(jugador.dateString), "%d/%m/%Y", &date_info);
				
				archivo.write((char *)(&jugador), sizeof(jugadorGanador));
			}
			x = 2;
			archivo.close();
		
				break;
		}
        
    }
    Color(BLACK, LCYAN);
      if(x == 2)
	{
		gotoxy(62, 21); cout << "Acumulaste: "<<acum2;
		gotoxy(3, 21); cout << "Felicidades!!! "<<alias2;
	}
	
		if(x == 1)
	{
		gotoxy(62, 21); cout << "Acumulaste: "<<acum1;
		gotoxy(3, 21); cout << "Felicidades!!! "<<alias1;
	}
	Color(BLACK, WHITE);
    	mostrarhorizontal(tablero1, tablero2,3,9, titulo, alias1, alias2, bolsa[c-1],c,x,acum1,acum2,indice1,indice2,numerosok1,numerosok2);
    		gotoxy(3,25);system("pause");
}


void shufflehorizontal(int *array,int n){
    if(n>1){
        int i;
        for(i=0;i<n-1;i++){
            int j=i+rand()/(RAND_MAX/(n-i)+1);
            int t=array[j];
            array[j]=array[i];
            array[i]=t;
        }
    }
}
int **pedirespaciohorizontal(int ren, int col){
    int **aux;
    aux=new int *[ren];
    for(int i=0;i<ren;i++)
        aux[i]=new int[col];
    return aux;
}
/*void imprimirtablero(int **mat,int ren, int col){
for(int i=0;i<ren;i++){
    for(int j=0;j<col;j++){
        cout<<setw(4)<<mat[i][j];
}
    cout<<endl;
}
}*/
void llenartablerohorizontal(int **mat,int ren, int col){
    int *vec;
    vec=new int[99];
    
    for(int i=0;i<99;i++){
        vec[i]=i+1;
    }
    shufflehorizontal(vec,99);//revuelve los 100 numeros
    int *aux;
    aux=new int[9];
    int inicio=0;
    int fin=5;
    
    for(int r=0;r<ren;r++){
    for(int i=0;i<9;i++){
        aux[i]=0;
    }
        int cont=0;
        
    for(int i=inicio;i<fin;i++){
        aux[cont]=vec[i];
        cont++;
    }
    shufflehorizontal(aux,9);
        for(int c=0;c<col;c++){
            mat[r][c]=aux[c];
        }//fin ciclo c
        inicio=fin;
        fin+=5;
        
    }//fin ciclo r
    
}
bool revisartablerohorizontal(int numero,int **m,int ren,int col,int *v,int  &indice,int &acum){
    bool exito=false;
    bool bandera;
    for(int i=0;i<ren;i++){
        for(int j=0;j<col;j++){
            if(m[i][j]==numero){
                //el numero si esta en el tablero
               // cout<<endl<<endl<<numero<<" Esta en el tablero\n";
                v[indice]=numero;
                indice++;
                acum=acum+numero;
                //imprimirtablero(m,3,9);
                m[i][j]=0;
                exito=revisarsiganahorizontal(m,3,9);
                if(exito==true){
                    return true;
                }
            }
    }
}
    return false;
}
bool revisarsiganahorizontal(int **m,int ren, int col){
    bool bandera=false;
    int cont;
    
    for(int i=0;i<ren;i++){
        cont=0;
        for(int j=0;j<col;j++){
            if(m[i][j]==0){
                cont++;
            }
            }
        if(cont==9){
            bandera=true;
            break;//rompe el ciclo de los renglones
        }
    }
    return bandera;
}
void mostrarhorizontal(int** tablero1, int** tablero2, int ren, int col, string titulo, string alias1, string alias2,int numero, int contador,int x,int acum1,int acum2, int indice1,int indice2,int*vector1,int*vector2)
{
	
	Color(BLACK, DGREY);
	dibujarCuadro(1, 5, 118,7); // sub titulos
	dibujarCuadro(1, 20, 118, 22); // sub titulos2
	dibujarCuadro(60, 5,60, 22); // linea del centro
	dibujarCuadro(1, 1, 118, 26);// marco 
	dibujarCuadro(51, 2, 70, 4); // titulo


	Color(BLACK, WHITE);
	//gotoxy(53,3);cout << titulo;
	//	for (int i = 0; i < numacum[27]; i++)
//	{
		
	gotoxy(62, 9); cout <<"Jugador 2: "<<  alias2;
	gotoxy(62, 10); cout << "Aciertos: "<<indice2;
	gotoxy(62, 11); cout << "Lista de numeros: ";
	gotoxy(61, 12);
	for (int i = 0; i < indice2; i++)
	{
		cout <<setw(3) <<vector2[i];
			}
			//sleep(200);
	gotoxy(3, 9); cout << "Jugador 1: "<< alias1;
	gotoxy(3, 10); cout << "Aciertos: "<<indice1;
	gotoxy(3, 11); cout << "Lista de numeros: ";
gotoxy(2, 12);
	for (int i = 0; i < indice1; i++)
	{
		cout <<setw(3) <<vector1[i];
			}
			//sleep(200);
	gotoxy(3, 6); cout << "Numero generado: "<<numero; 
	Sleep(200);
	gotoxy(62, 6); cout << "Contador de numeros: "<<contador; 
	Color(BLACK, LCYAN);
	
	
	Color(BLACK, WHITE);
	gotoxy(3, 23); cout << "Todos los numeros que han salido: ";
	
			
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j< 9; j++)
		{
		//	Sleep(25);
			if(tablero1[i][j]==0)
			{
				//printf("%d"),tablero2[i][j];
				Color(RED, WHITE);
			}
			else
			{
				Color(BLACK, WHITE);
			}
			gotoxy(10 + j * 5, 14 + i); printf(" %d ", tablero1[i][j]);
			
		}
		cout << endl;
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			Sleep(25);
			if(tablero2[i][j]==0)
			{
			//	printf("%d"),tablero2[i][j];
				Color(RED, WHITE);
			}
			else
			{
				Color(BLACK, WHITE);
			}
			gotoxy(70 + j * 5, 14 + i); printf(" %d ", tablero2[i][j]);
		}
		cout << endl;
	}
	Color(BLACK, WHITE);
	
}


void Colorhorizontal(int Background, int Text) 
{

	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	int    New_Color = Text + (Background * 16);

	SetConsoleTextAttribute(Console, New_Color);
}

void dibujarCuadrohorizontal(int x1, int y1, int x2, int y2)
{
	int i;

	for (i = x1; i < x2; i++) {
		gotoxy(i, y1); printf("\304"); //linea horizontal superior
		gotoxy(i, y2); printf("\304"); //linea horizontal inferior
	}

	for (i = y1; i < y2; i++) {
		gotoxy(x1, i); printf("\263"); //linea vertical izquierda
		gotoxy(x2, i); printf("\263"); //linea vertical derecha
	}

	gotoxy(x1, y1); printf("\332");
	gotoxy(x1, y2); printf("\300");
	gotoxy(x2, y1); printf("\277");
	gotoxy(x2, y2); printf("\331");
}

void gotoxyhorizontal(int x, int y)
{
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hcon, dwPos);
}

//Modo carta completa

void CuadradoCartaCompleta(string alias1, string alias2)
{
	jugadorGanador cuadrado;
	struct tm * time_info;
	struct tm date_info;
	time_t current_time;
	time_t current_date;
	
	fstream archivo;
	int **tablero1;
	int **tablero2;
	
	char tipojuego[20] ={"Abierto"};
	
	tablero1=pedirespacioCartaCompleta(3,9);
	tablero2=pedirespacioCartaCompleta(3,9);
	
	llenarCartaCompleta(tablero1,3,9);
	llenarCartaCompleta(tablero2,3,9);
	
	bool tabla1 = false, tabla2 = false;
	int numok_tablero1[100], indice1 = 0;
	int numok_tablero2[100], indice2 = 0;
	int acum1=0, acum2=0;
	int c=0;
	
	imprimirCartaCompleta(tablero1,tablero2,3,9,alias1,alias2,0,0,indice1,indice2,0,0);
	Color(BLACK,RED);
	gotoxy(50,3);cout<<"B"; Sleep(100);
	Color(BLACK,BLUE);
	gotoxy(51,3);cout<<"i"; Sleep(100);
	Color(BLACK,CYAN);
	gotoxy(52,3);cout<<"n"; Sleep(100);
	Color(BLACK,YELLOW);
	gotoxy(53,3);cout<<"g"; Sleep(100);
	Color(BLACK,MAGENTA);
	gotoxy(54,3);cout<<"o"; Sleep(100);
	Color(BLACK,WHITE);
	gotoxy(55,3);cout<<" "; Sleep(100);
	Color(BLACK,GREEN);
	gotoxy(56,3);cout<<"C"; Sleep(100);
	Color(BLACK,RED);
	gotoxy(57,3);cout<<"a"; Sleep(100);
	Color(BLACK,LBLUE);
	gotoxy(58,3);cout<<"r"; Sleep(100);
	Color(BLACK,LCYAN);
	gotoxy(59,3);cout<<"t"; Sleep(100);
	Color(BLACK,LGREEN);
	gotoxy(60,3);cout<<"a"; Sleep(100);
	Color(BLACK,RED);
	gotoxy(61,3);cout<<" "; Sleep(100);
	Color(BLACK,YELLOW);
	gotoxy(62,3);cout<<"C"; Sleep(100);
	Color(BLACK,BLUE);
	gotoxy(63,3);cout<<"o"; Sleep(100);
	Color(BLACK,RED);
	gotoxy(64,3);cout<<"m"; Sleep(100);
	Color(BLACK,BLUE);
	gotoxy(65,3);cout<<"p"; Sleep(100);
	Color(BLACK,CYAN);
	gotoxy(66,3);cout<<"l"; Sleep(100);
	Color(BLACK,YELLOW);
	gotoxy(67,3);cout<<"e"; Sleep(100);
	Color(BLACK,MAGENTA);
	gotoxy(68,3);cout<<"t"; Sleep(100);
	Color(BLACK,WHITE);
	gotoxy(69,3);cout<<"a"; Sleep(100);
	
	int *bolsa = new int[99];
	
	for(int i=0; i < 99; i++)
	{
		bolsa[i] = i + 1;
	}
	shuffle(bolsa,99);
	

	
	int *v3;
	v3 = new int[27];
	
	int startX = 40;
	int startY = 23;
	int x = startX;
	int y = startY;
	
	int maxRow = 15;
	int spaceX = 5;
	
	for(int i=0; i < 99; i++)
	{
		Sleep(200);	
		tabla1 = revisarCartaCompleta(bolsa[i],tablero1,3,9,numok_tablero1,indice1,acum1);
		tabla2 = revisarCartaCompleta(bolsa[i],tablero2,3,9,numok_tablero2,indice2,acum2);
		
		v3 = unirCartaCompleta(numok_tablero1,indice1,numok_tablero2,indice2);
		
		imprimirCartaCompleta(tablero1,tablero2,3,9,alias1,alias2,c++,bolsa[i],indice1,indice2,numok_tablero1,numok_tablero2);
		
		
					
		if (tabla1 == true)
		{
			Color(BLACK,LCYAN);
			gotoxy(3,21);cout << "Felicidades!!! "<< "<"<< alias1 << ">";
			gotoxy(62,21);cout << "Acumulaste: "<< acum1;
			Color(BLACK,WHITE);
			cout << endl << endl << endl;		
			for(int j=0;j < indice1 + indice2; j++)
			{
				gotoxy(x, y);
				cout << v3[j];
				x += spaceX;
				if (x >= startX + maxRow*spaceX) 
				{
					x = startX;
					y++;
				}
			}
				archivo.open("ganadores.dat", ios::binary|ios::out|ios::app);
				if(!archivo)
				{
					cerr << "No se puede abrir el archivo " << endl;
					cin.get();
				}else
				{
					
					cuadrado.contAbierto++;
					if(strcmp(alias1.c_str(),cuadrado.alias) && strcmp(tipojuego,cuadrado.modoJuego))
					{
						cuadrado.contAbierto++;
					}
					strcpy(cuadrado.alias, alias1.c_str());
					strcpy(cuadrado.modoJuego, tipojuego);
					cuadrado.puntos = acum1;
					time(&current_time);
					time(&current_date);
						
					time_info = localtime(&current_time);
					date_info = * localtime(&current_time);
						
					strftime(cuadrado.timeString, sizeof(cuadrado.timeString), "%H:%M:%S", time_info);
					strftime(cuadrado.dateString, sizeof(cuadrado.dateString), "%d/%m/%Y", &date_info);
					archivo.write((char *)(& cuadrado), sizeof(jugadorGanador));
					archivo.close();
				cout << "\t\t" <<endl;
				gotoxy(3,25);system("pause");
				break;
				}
		}
	
		
		if (tabla2 == true)
		{
			Color(BLACK,LCYAN);
			gotoxy(3,21);cout << "Felicidades!!! "<< "<"<< alias2 << ">";
			gotoxy(62,21);cout << "Acumulaste: "<< acum2;
			Color(BLACK,WHITE);
			cout << endl << endl << endl;
			for(int j=0;j < indice1 + indice2; j++)
			{
				gotoxy(x, y);
				cout << v3[j];
				x += spaceX;
				if (x >= startX + maxRow*spaceX) 
				{
					x = startX;
					y++;
				}
			}
				archivo.open("ganadores.dat", ios::binary|ios::out|ios::app);
				if(!archivo)
				{
					cerr << "No se puede abrir el archivo " << endl;
					cin.get();
				}else
				{
					
					cuadrado.contAbierto++;
					if(strcmp(alias1.c_str(),cuadrado.alias) && strcmp(tipojuego,cuadrado.modoJuego))
					{
						cuadrado.contAbierto++;
					}
					strcpy(cuadrado.alias, alias2.c_str());
					strcpy(cuadrado.modoJuego, tipojuego);
					cuadrado.puntos = acum2;
					time(&current_time);
					time(&current_date);
						
					time_info = localtime(&current_time);
					date_info = * localtime(&current_time);
						
					strftime(cuadrado.timeString, sizeof(cuadrado.timeString), "%H:%M:%S", time_info);
					strftime(cuadrado.dateString, sizeof(cuadrado.dateString), "%d/%m/%Y", &date_info);
					archivo.write((char *)(& cuadrado), sizeof(jugadorGanador));
					archivo.close();
				cout << "\t\t" <<endl;
				gotoxy(3,25);system("pause");
				break;
			}
		}
	}
}

bool revisarCartaCompleta(int numero,int **m,int ren, int col, int *vector, int &indice, int &acum){
	bool exito=false;
	for (int i=0; i<ren; i++){
		for (int j=0; j<col; j++){
			if (m[i][j]==numero){
				//Ese numero si esta en el tablero
				
				vector[indice]=numero;
				indice++;
				acum = acum + numero;
				m[i][j]=0;
			//	imprimirtablero(m,3,9);
				exito = revisarsiganaCartaCompleta(m,3,9);
				if (exito==true)
				{
					return true;
				}
					
			}//Fin if
		}//fin for j
	}//fin for i
	return false;
}//fin revisartablero


bool revisarsiganaCartaCompleta(int **m,int ren, int col){
	bool bandera=false;
	int suma;
	int contador=0;
	for (int i=0;i<ren;i++){
		suma=0;
		for (int j=0;j<col;j++){
			if(m[i][j] == 0){
				suma=suma+m[i][j];
				contador++;
			}
		}
		if (contador == 27){
			bandera=true;
			break;
		}
	}
	return bandera;
}

int *unirCartaCompleta(int*v1 ,int t1, int* v2, int t2)
{
	int *aux;
	aux = new int [t1 + t2];
	for(int i=0; i < t1; i++)
	{
		aux[i] = v1[i];
	}
	
	for(int i = t1; i < t2 + t1; i++)
	{
		aux[i] = v2[i - t1];
	}
	return aux;
}



void imprimirCartaCompleta(int **tablero1,int ** tablero2,int ren,int col, string alias1,string alias2, int contador, int numero,int indice1,int indice2, int*vector1, int * vector2)
{
	Color(BLACK,DGREY);
	dibujarCuadro(1,5,119,7); // sub titulos
	dibujarCuadro(1,20,119,22); // sub titulos2
	dibujarCuadro(60,5,60,22); // linea del centro
	dibujarCuadro(1,1,119,26);// marco 
	dibujarCuadro(48,2,71,4); // titulo
	

	Color(BLACK,WHITE);
	gotoxy(3,23);cout << "Todos los numeros que han salido: ";
	gotoxy(62,9);cout << "Jugador 2: " << alias2;
	gotoxy(3,11);cout << "Lista de numeros: ";
	
	int startX = 3;
	int startY = 12;
	int x = startX;
	int y = startY;
	
	int maxRow = 12;
	int spaceX = 5;
	for(int j=0;j < indice1; j++)
	{
		gotoxy(x, y);
		cout << vector1[j];
		x += spaceX;
		if (x >= startX + maxRow*spaceX) 
		{
			x = startX;
			y++;
		}
	}
	
	gotoxy(62,11);cout << "Lista de numeros: ";
	
	startX = 62;
	x= startX;
	startY = 12;
	y = startY;
	
	for(int j=0;j < indice2; j++)
	{
		gotoxy(x, y);
		cout << vector2[j];
		x += spaceX;
		if (x >= startX + maxRow*spaceX) 
		{
			x = startX;
			y++;
		}
	}
	gotoxy(62,10);cout << "Aciertos: " << indice2;
	gotoxy(3,9);cout << "Jugador 1: " << alias1;
	gotoxy(3,10);cout << "Aciertos: " << indice1;
	gotoxy(3,6);cout << "Numero generado: "<<numero;
	gotoxy(62,6);cout << "Contador de numeros: " << contador;	

	
	
	for(int i=0; i < ren; i++)
	{
		for (int j = 0; j < col; j++)
		{	
    		//Sleep(20);
    		if(tablero1[i][j]==0){
    			Color (RED,WHITE);
			}
			else
			{
				Color(BLACK, WHITE);
			}
			gotoxy(10 + j * 5,14 + i);printf(" %d ", tablero1[i][j]);//Sleep(15);//cout<< *(*(tablero1 + i) + j);
			
		}
		cout << endl;
	}
	

	for(int i=0; i < ren; i++)
	{
		for (int j = 0; j < col; j++)
		{
		//	Sleep(20);	
			if(tablero2[i][j]==0){
    			Color (RED,WHITE);
			}
			else
			{
				Color(BLACK, WHITE);
			}
    		gotoxy(70 + j * 5,14 + i);printf(" %d ", tablero2[i][j]);//Sleep(15);//cout <<*(*(tablero2 + i) + j);
		}
		cout << endl;
	}
	Color(BLACK, WHITE);
}


void llenarCartaCompleta(int **matriz, int ren,int col){
	int *vec;
	vec =new int [99];
	
	for (int i=0;i<99;i++){
		vec[i]=i+1;
	}
	
	shuffle(vec,99);
	
	int *aux;
	aux = new int [9];
		
	int inicio=0;
	int final=5;
		
	for (int r=0;r<ren;r++){
	
		for (int i=0; i < 9;i++){
			aux[i] = 0;
		}
		
		int contador=0;
		for (int i=inicio;i<final;i++){
			aux[contador++] = vec[i];
		}
	
		shuffle(aux,9);
		
		for (int c=0;c<col;c++){
			matriz[r][c]= aux[c];
		}
		
		inicio = final;
		final = final + 5;
	}
}


int **pedirespacioCartaCompleta(int ren,int col){
	int **aux;
	aux = new int *[ren];
	for (int i=0; i<ren; i++)
		aux[i]= new int[col];
	return aux;
}
