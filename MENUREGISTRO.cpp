//MENU FICHEROS
//INGENIERIA FISICA
//PROGRAMACION II: ORIENTADA A OBJETOS
//Nombre: CHICUE GARCIA LIA NATALIA.
///C.C:1030687951

#include <iostream>
#include <iomanip>
#include <conio.h>
#include <cstring>
#include <windows.h>
#include <cstdlib>
#include <fstream>
#define MAXIMO 20


const char* LETRAS="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char* NUMEROS="0123456789";
const char* REAL="0123456789";
const char* ALFANUM ="ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789.#-";
const char* FECHA="0123456789/";
const char* FICHERO ="ALUMNOS.DAT";

using namespace std;

class Registro{
	private:
		long long codigo;
		char nombre[30];
		double nota;
		char direccion[31];
		char telefono[31];
		char fecha_nac[11];
		int estrato;
		double matricula;
	public:
	    void getdata();
	    void listar();
	    void putdata();
	    void consCodigo();//Buscar Por Codigo
	    void consNombre();//Buscar por Nombre
	    Registro Modificar();//No tengo que decirlo
	    void orCodigo();//Ordenar por codigo
	    void orNombre();//Ordenar por nombre
	    int Eliminar();//Eliminar Registro
};


//Mensajes del Menú
string mensaje [] = { "1. Adicionar      ",
                      "2. Listar         ",
					  "3. Consulta Codigo",
					  "4. Consulta Nombre",
					  "5. Modificar      ",
					  "6. Ordenar Codigo ",
					  "7. Ordenar Nombre ",
					  "8. Eliminar       ",
					  "0. Salir          "};


//Validacion de Cadena
void editcad(char *s, int max,const char *validos)
{
	char c;
	int i;
	s[0]=0; i=0;
	do{
	 	c=toupper(getch());
	 	switch(c){
	 			case 8:// <retroceso>
	 			if(i>0){
	 				i--;
					 putch(0*8);//retroceso
					 putch(' ');
					 putch(0*8);//retroceso
				 }
				 break;
				case 13:// tecla <intro>
				    s[i]=0;
					break;
				default:
				       if(i<max) 
				       if(strchr(validos,c)){
				       	putch(c);
				       	s[i++]=c;
					   }
			    }
		 }while(c!=13);
}
//VALIDACIONES
//Por Codigo     
long long getcodigo(int max){
     char s[15];
     editcad(s,max,NUMEROS);
		return(atoll(s));
	}
//Un Numero Entero
long getint(int max){
     char s[12];
     editcad(s,max,NUMEROS);
		return(atol(s));
     }
//Numero Real    
double getfloat(int max){
       char s[21];
       editcad(s,max,REAL);
    	return (atof (s));
	}

//Funcion Para definir Color
void setcolor(int color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

//Dibuja un Menú de opciones
int menu(void)
{
	char opcion;
	int result;
	setcolor(0xA); // Fondo Azul, Texto Blanco
	system("CLS");
	setcolor(0xA);
    cout<<endl<<endl<<endl<<endl;
	cout<<"              ______________________ "<<endl;
	cout<<"             |----------------------|"<<endl;
	cout<<"             |       REGISTRO       |"<<endl;
	cout<<"             *----------------------*"<<endl;
	for(int i=0;i<9;i++)
	{
		cout<<"             |   ";
		cout<<mensaje[i]<<" |"<<endl;
	}
	cout<<"             *----------------------*"<<endl;
	setcolor(0xA);
	cout<<"\n \t Por Favor, Escoja su opcion: ";
	opcion=getche();
	result=opcion-'0';
	return(result);
	system("pause");
}

//Lee los datos y los guarda en archivo
void Registro::getdata(void){
	ofstream fout;
	Registro alumno;
	char resp;
	
	fout.open(FICHERO, ios::out | ios::binary | ios::app);
	if(!fout){
		cout<<"Error en creacion de archivo"<<endl;
		exit(1);
	}
	do{
		system("CLS");
	cout<<"\t \t  ______________________________________ "<<endl;
	cout<<"\t \t |--------------------------------------|"<<endl;
	cout<<"\t \t |           CAPTURA DE DATOS           |"<<endl;
	cout<<"\t \t |______________________________________|"<<endl;
	cout<<"\t \t |--------------------------------------|"<<endl;
	cout<<"\t Por favor, ingrese los siguientes datos para el registro"<<endl;
	cout<<endl;
	cout<<">Codigo       :";  cin>>alumno.codigo;	
	cout<<">Nombre       :";  editcad(alumno.nombre, 30, LETRAS);
	cout<<endl;	
	cout<<">Direccion    :";  editcad(alumno.direccion,30,ALFANUM);
	cout<<endl;
	cout<<">Telefono     :";  editcad(alumno.telefono,10,NUMEROS);	
	cout<<endl;
	cout<<">Fecha Nacimiento  (aa mm dd)   :"; editcad(alumno.fecha_nac,10,FECHA);
	cout<<endl;
	cout<<">Estrato      :"; cin>>alumno.estrato;
	cout<<">Matricula    :"; cin>>alumno.matricula;
	cout<<">Nota         :"; cin>>alumno.nota;
	cout<<endl;
	//Guarda Los Datos en un archivo
		fout.write((char*)&alumno, sizeof(Registro));
		cout<<"\n \t Desea agregar otro alumno? (S/N) " ;
		resp=toupper(getch());
	}while(resp=='S');
	fout.close();
}

//Listado de Registros
void Registro::listar(void)
{
	ifstream fin;
	//char slinea[81];
	Registro alumno;
	int i;
	
	fin.open(FICHERO, ios::in | ios::binary);
	if(!fin){
		cout<<"\n \n \t Error en creacion del Archivo: No Existe"<<endl;
		cout<<endl;
        system("pause");
		exit(1);
	}
	
	system("cls");
	cout<<endl<<endl;
	cout<<" _______________________________________________________________________ "<<endl;
	cout<<"|-----------------------------------------------------------------------|"<<endl;
	cout<<"| #REG. |     CODIGO      |         NOMBRE         |        NOTAS       |"<<endl;
	cout<<"|_______________________________________________________________________|"<<endl;
	cout<<"|-----------------------------------------------------------------------|"<<endl;
	
    i=0;
	while(!fin.eof()){
		fin.read((char*)&alumno, sizeof(Registro));
		if(!fin.eof()){ 
	    printf(" %3d       %10lld          %-30s %-10.2f \n", i+1,alumno.codigo,alumno.nombre,alumno.nota);
      }
     i++;
    }
    fin.close();
	getch();	
}

//Muestra los datos de un Registro (es lo mismo que el mostrar)
void Registro::putdata()
{
	system("cls");
	printf("\n");
	printf("\t ______________________________________\n");
	printf("\t --------------------------------------\n");
	printf("\t          REGISTRO ENCONTRADO             \n");
	printf("\t*------------------------------------*\n");
	printf("\t                                    \n");
	printf("\t   Codigo : %-10lld         \n", codigo);
	printf("\t                                    \n");
	printf("\t   Nombre : %-30s            \n", nombre);
	printf("\t                                    \n");
	printf("\t   Direccion : %-50s     \n", direccion);
	printf("\t                                    \n");
	printf("\t   Telefono : %-30s       \n", telefono);
    printf("\t                                    \n");
    printf("\t   Fecha De Nacimiento : %-20s\n", fecha_nac);
    printf("\t                                    \n");
    printf("\t   Estrato : %-10.2i       \n", estrato);
    printf("\t                                    \n");
    printf("\t   Matricula : %-5.1f \n", matricula);
    printf("\t                                    \n");
    printf("\t   Notas : %-10.2f             \n", nota);
	printf("\t                                    \n");	
}

//Consulta por Codigo
void Registro::consCodigo(void)
{
	ifstream fin;
	Registro alumno;
	long  clave;
	bool hallado;
	
	fin.open(FICHERO, ios::in | ios::binary);
	if(!fin){
		cout<<"Error en acceso al archivo"<<endl;
		exit(1);
	}
	
	cout<<endl;
	cout<<"\n\n Codigo a Buscar: "; clave=getcodigo(20);
	hallado=false;
	while(!fin.eof() && !hallado){
		fin.read((char*)&alumno, sizeof(Registro));
		if(clave == alumno.codigo){
			cout<<"------REGISTRO ENCONTRADO POR CODIGO------"<<endl;
			alumno.putdata();
			hallado = true;
			break;
		}
	}
	fin.close();
	if(!hallado){
		cout<<"\aATENCION!!!   ...Este Codigo NO Existe"<<endl;
	}
	system("pause");//getch()
}

//Buscar Por Nombre
void Registro::consNombre(void){
    ifstream fin;
	Registro alumno;
	Registro nombre1;
	bool hallado;
		fin.open(FICHERO, ios::in | ios::binary);
	if(!fin){
		cout<<"Error en acceso al archivo"<<endl;
		exit(1);
	}
	cout<<endl;
	cout<<"\n\n Nombre a Buscar: ";	editcad(nombre1.nombre, 30, LETRAS);
	hallado=false;
	while(!fin.eof()&&!hallado){
		fin.read((char*)&alumno, sizeof(Registro));
		if(strcmp(alumno.nombre,nombre1.nombre)==0){
            cout<<"------REGISTRO ENCONTRADO POR NOMBRE------"<<endl;
			alumno.putdata();
			hallado=true;
			break;
		}
	}
	fin.close();
	if(!hallado){
		cout<<"\aATENCION!!!   ...Este Codigo NO Existe"<<endl;
	}
	getch();
}

//Organizar por Codigo
void Registro::orCodigo(void){
	Registro aux,aux1;
	long curpos, length;
	int nr, tam;
	bool ordenado=false;
	fstream fs(FICHERO, ios::in | ios::out | ios::binary);
	if(!fs){
		cout<<"Error en acceso al archivo"<<endl;
		exit(1);
	}
	curpos=fs.tellg();
	fs.seekg(0L, ios::end);
	length=fs.tellg();
	fs.seekg(curpos,ios::beg);
	
	tam=sizeof(Registro);
	nr=(length / tam);
	
	while(!ordenado){
		ordenado=true;
		for(int i=0;i<(nr-1);i++){
			fs.seekg((long)i*tam,ios::beg);
			fs.read((char*)&aux,tam);
			fs.seekg((long)(i+1)*tam, ios::beg);
			fs.read((char*)&aux1,tam);
			if(aux.codigo>aux1.codigo){
				fs.seekp((long)i*tam,ios::beg);
				fs.write((char*)&aux1,tam);
				fs.seekp((long)(i+1)*tam, ios::beg);
				fs.write((char*)&aux, tam);
				ordenado=false;
				
			}
		}
	}
	fs.close();
}

//Organizar por Nombre
void Registro::orNombre(void){
	Registro aux,aux1;
	long curpos, length;
	int nr, tam;
	bool ordenado=false;
	
	fstream fs(FICHERO, ios::in | ios::out | ios::binary);
	if(!fs){
		cout<<"Error en acceso al archivo"<<endl;
		exit(1);
	}
	curpos=fs.tellg();
	fs.seekg(0L, ios::end);
	length=fs.tellg();
	fs.seekg(curpos,ios::beg);
	
	tam=sizeof(Registro);
	nr=(length / tam);
	
	while(!ordenado){
		ordenado=true;
		for(int i=0;i<(nr-1);i++){
			fs.seekg((long)i*tam,ios::beg);
			fs.read((char*)&aux,tam);
			fs.seekg((long)(i+1)*tam, ios::beg);
			fs.read((char*)&aux1,tam);
			if(strcmp(aux.nombre,aux1.nombre)>0){
				fs.seekp((long)i*tam,ios::beg);
				fs.write((char*)&aux1,tam);
				fs.seekp((long)(i+1)*tam, ios::beg);
				fs.write((char*)&aux, tam);
				ordenado=false;	
			}//IF
		}//FOR
	}//WHILE
	fs.close();
}


//Modificar
Registro Registro::Modificar(void){
   fstream fin;
   Registro alumno;
   bool hallado=false;
   long long clave;
   int pos;
   char r;
   fin.open(FICHERO, ios::in|ios::out|ios::binary);
   if(!fin){
        cout<<"Error en creacion de archivo"<<endl;
		exit(1);    
	    }
	cout<<"\n \n Codigo a Modificar: ";clave=getcodigo(20);
	pos=0;
	while(!fin.eof() && !hallado){
	        fin.read((char*)&alumno, sizeof(Registro));
			if(clave==alumno.codigo){
			        hallado=true;
					alumno.putdata();
					break;
					}//if
			pos++;
        }//while
        
		if(!hallado)
		{
		    cout<<"Codigo no encontrado. \n";
			system("PAUSE");
			}
			else
			{
			    cout<<"\nDesea modificar (S/N) "<<endl;
				r=toupper(getch());
				if(r=='S'){
				system("CLS");
				cout<<endl<<endl;
				cout<<"\nCodigo        : "; alumno.codigo=getcodigo(12);
				cout<<"\nNombre        : ";editcad(alumno.nombre,30,LETRAS);
				cout<<"\nDireccion     : "; editcad(alumno.direccion,30,ALFANUM);
				cout<<"\nTelefono      : "; editcad(alumno.telefono,10,NUMEROS);
				cout<<"\nFecha Nacimiento (dd/mm/aa): "; editcad(alumno.fecha_nac,10,FECHA);
				cout<<"\nEstrato       : "; alumno.estrato=getint(1);
				cout<<"\nMatricula     : "; alumno.matricula=getfloat(10);
				cout<<"\nNota          : "; alumno.nota=getfloat(3);
				cout<<endl<<endl;
				fin.seekp(pos*sizeof(Registro),ios::beg);
				fin.write((char*)&alumno, sizeof(Registro));
				fin.close();

               }//if(r)

         }
		 system("PAUSE");//if(hallado)

}


//Eliminar
int Registro::Eliminar(void){
	ofstream of;
	ofstream fout;
	fstream fin;
	Registro alumno;
	long long clave;
	char resp;
	fin.open(FICHERO, ios::binary | ios::in );
	fout.open("NUEVO.DAT", ios::binary| ios::out);
	cout<<endl;
	cout<<"\n \n Ingrese el codigo: "; clave=getcodigo(20);
		while(!fin.eof()){
		fin.read((char*)&alumno, sizeof(Registro));
		if(clave==alumno.codigo)
		{
                alumno.putdata();
				cout<<endl;
			cout<<"\n Desea eliminar? S/N ";
				resp=getche();
		
		if(resp=='s'||resp=='S')	
		{
            fin.seekg(0,ios::beg);
			while(!fin.eof()){
				fin.read((char*)&alumno, sizeof(Registro));
				if(clave!=alumno.codigo && !fin.eof())
				fout.write((char*)&alumno, sizeof(Registro));
			}
		
		}
		else
		{
            cout<<"El Codigo ingresado NO existe"<<endl;
        }
	fin.close();
			fout.close();
			remove(FICHERO);
			rename("NUEVO.DAT",FICHERO);		
       }
       else
       {
       	cout<<endl<<"\n \t El Codigo Ingresado No Existe"<<endl;
	   }

    }
}


/*CUERPO PRINCIPAL*/
using namespace std;
int main(int argc, char** argv) 
{
	Registro alumno;
	int opcion;
	char resp;
	bool salir = false;
	do{
		opcion=menu();
		switch (opcion){
			case 1:
				alumno.getdata();
				system("pause");
				break;
				
			case 2:
				alumno.listar();
				system("pause");
				break;
				
			case 3:
				alumno.consCodigo();
				break;
				
			case 4: 
                 alumno.consNombre();
                 system("pause");
                 break;
                 
            case 5:
                 alumno.Modificar();
                 system("pause");
                 break;
                 
            case 6:
                 alumno.orCodigo();
                 alumno.listar();
                 system("pause");
                 break;
            
            case 7:
                 alumno.orNombre();
                 alumno.listar();
                 system("pause");
                 break;
                 
            case 8:
                 alumno.Eliminar();
                 system("pause");
                 break;
	
			case 0:
				cout<<"\n\n Esta seguro de salir S/N?:";
				resp=toupper(getch());
				if(resp=='S')
				salir=true;
			    
		}//switch
		
	}while(!salir);
	
	return 0;
}
