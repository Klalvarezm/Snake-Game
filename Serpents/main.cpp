//Se agrega cstdlib para poder usar la limpieza de pantalla y conio.h para que detecte las entradas por teclado
//windows.h para el system pause
#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <windows.h>
using namespace std;
bool Juego_Terminado;
//const se coloca para que alto y ancho se mantengan constantes :v, osea que siempre van a valer 20
const int alto=20;
const int ancho=20;
int x,y,Comiposx,comiposy,puntos;
int cuerpox[40];
int cuerpoy[40];
int tamcuerpo;
//Enum es un tipo de dato, que mas o menos permite crear un tipo de dato propio
//Se piensa como una enumeracion de cadenas, osea cada palabra es una cadena que es posible asignarse a orden, puesto que es del tipo direccion
//Lo que va en los corchetes {} son las varialbes que podra tomar nuestro tipo de dato
//Osea que creamos un tipo de dato, y solo podemos usar los datos que van en los corchetes
//Igualmente Al usar enum para crear nuestro "tipo de dato" no lo podremos usar con CIN
//Osea no se podra usar cin para ingresar el dato, pero si cout, para mostrarlo en la salida.
enum direccion {Parar=0,Izquierda,Derecha,Arriba,Abajo};
direccion Orden;
//Esta funcion, es la que comienza el juego, pone a la serpiente en el centro (por eso x y son altura y ancho dividido en 2)
//pone los puntos en cero y busca colocar la comida en algun lugar aleatoreo
void Comenzar()
{
Juego_Terminado = false;
Orden = Parar;
//ubica a la serpiente en el centro
x=ancho/2;
y=alto/2;
//Ubica la comida en un valor al azar entre 0 y el valor de ancho -1 osea 29
Comiposx= rand() % ancho-1;
comiposy=rand() % alto-1;
puntos=0;
}

void dibujar()
{
system ("cls"); //Sirve para limpiar la pantalla, para que el juego siempre este en el mismo cuadro
//techo
for (int i=0;i<ancho + 2;i++)
cout<<"*";
cout<<endl;
//muros izq y der
for (int i=0;i < alto;i++)
	{
     for (int j=0;j < ancho;j++)
     {

	if (j==0)
	  {
	  cout<<"*";
	  }

	  /*
	if (j==ancho-1)
	{
	cout<<"*";
	}*/

	//Aqui se dibuja la cabeza de la serpiente (Solo en el if)
	if (i==y && j==x)
	{
	cout<<"v";
	}
	//Aqui se dibuja la comida (solo en el else if)
	else if (i==comiposy && j==Comiposx)
	{
	cout<<"¦";
	}
	else {
	 bool imprimir=false;
	  for (int k=0;k < tamcuerpo;k++)
	 {

	  if (cuerpox[k]==j && cuerpoy[k]==i)
	   {
	   cout << ":";
	   imprimir=true;
	   }

	 }
     	 if (!imprimir)
	     cout<<" ";

	    }

	if (j==ancho-1)
	{
	cout<<"*";
	}
	}
    cout<<endl;

	}
//piso

for (int i=0;i<ancho + 2;i++)
cout<<"*";

cout<<endl;

cout<<"Puntuacion : "<<puntos<<"\n";
}

//_kbhit detecta si se presiona una tecla del teclado (DUHH) y _getch, asigna una accion a cada tecla
//Orden es un dato del tipo direccion (por el enum), con los valores izquierda, derecha, arriba y abajo.
//estos se igualan ccnforme se presione una tecla

void entrada()
{
if (_kbhit())
 {

 switch (_getch())
  {

   case 'a':
	Orden= Izquierda;
   break;

   case 's':
	Orden= Abajo;
   break;

   case 'd':
		Orden= Derecha;
   break;

   case 'w':
		Orden= Arriba;
   break;
  }
 }
}
//aqui se le asignan a los valores del movimiento, un movimiento (valiendo la redundancia)
//y-- arriba y y++ abajo, por que el valor de y aumenta conforme baja el mapa
void logica()
{

int xanterior=cuerpox[0];
int yanterior=cuerpoy[0];
int anty,antx;
cuerpox[0]=x;
cuerpoy[0]=y;

//aqui se hace el cuerpo
for (int i=1;i<tamcuerpo;i++)
{

antx=cuerpox[i];
anty=cuerpoy[i];
cuerpox[i]=xanterior;
cuerpoy[i]=yanterior;
xanterior=antx;
yanterior=anty;

}
switch (Orden)
{
case Izquierda:
x--;
break;
case Abajo:
y++;
break;
case Derecha:
x++;
break;
case Arriba:
y--;
break;
default:
break;

}
//este sirve para cuando la cabeza "V" toque los bordes, el juego termine
if (x>ancho||x<0||y>alto||y<0)
Juego_Terminado = true;

//Detecta cuando uno come la comida :v(duhh x2)
//suma puntos y cambia posicion comida

	for (int i = 0; i < tamcuerpo; i++)
		if (cuerpox[i] == x && cuerpoy[i] == y)
			Juego_Terminado = true;


if (x==Comiposx&&y==comiposy)
{
puntos++;

Comiposx= rand() %ancho;
comiposy=rand() %alto;
	tamcuerpo++;
}
}

int main() {
Comenzar();
 //Juego_Terminado con el simbolo de exclamacion al incio, indica el el juego no esta terminado osea !Juego_Terminado o que Juego_Terminado==False
  while (!Juego_Terminado)
  {
   dibujar();
   entrada();
   logica();
   Sleep(100);
  }
 system("pause");
 return 0;
}
