#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
using namespace std;
//ESTA FUNCION EMULA LA FUNCION GOTOXY DE LA LIBRERIA CONIO.
void gotoxy(int x,int y){
    HANDLE ventana;
    ventana=GetStdHandle(STD_OUTPUT_HANDLE);
    COORD posicion;
    posicion.X=x;
    posicion.Y=y;
    SetConsoleCursorPosition(ventana,posicion);
}
char* leer_cadena(istream& is, char* x, int n){
    is.getline(x, n);
    return x;
}
int main()
{
    //DECLARACION DE VARIABLES.
    /*LAS SIGUIENTES VARIABLES TIPO CHAR SON PARA IMPRIMIR EN PANTALLA LAS LINEAS QUE FORMARAN EL CUADRO DE JUEGO
    CADA UNA ES UN ACRONIMO DE LA LINEA QUE REPERESENTAN, DE ESTE MODO ESI=ESQUINA SUPERIOR IZQUIERDA EII SERIA LA ESQUINA
    INFERIOR IZQUIERDA, LH=LINEA HORIZONTAL Y ASI CON LAS DEMAS.
    CUADRITO SE USA PARA IMPRIMIR LOS CUADRITOS QUE COMPONEN LA SERPIENTE.
    A,B SON PARA IDENTIFICAR QUE TECLA SE PULSA DURANTE LA EJECUCION DEL PROGRAMA.
    COMIDA ES UNA VARIABLE PARA IMPRIMIR LA COMIDA DE LA SERPIENTE.
    */
    char esi=201,esd=187,eii=200,eid=188,lh=205,lv=186,cuadrito=178,a,b,comida=155,bks=92;
    /*LA VARIABLE GAME SIRVE COMO INDICADOR PARA SABER EN QUE MOMENTO DEJAR DE MOVER A LA SERPIENTE.
    LAS VARIABLES X,Y SIRVEN PARA INDICAR EN QUE POSICION SE POSICIONA EL CURSOR AL USAR LA FUNCION GOTOXY.
    LA VARIABLE DIRECCION SE USA PARA SABER EN QUE DIRECCION SE MOVERA LA SERPIENTE.
    LA VARIABLE AUX ES UN AUXILIAR QUE SIRVE DE APOYO A LAS VARIABLES A,B.
    PCX,PCY SON VARIABLES QUE SIRVEN PARA INDICAR LA POSICION DE LA COMIDA DE LA SERPIENTE
    */
    int game=0,x=29,y,direccion=1,pcx,pcy,puntaje=0,pos=0,puntaant=0,velocidad=120;
    //vector
    int* posiciones=new int[10000];
    /*GENERACION DE NUMEROS ALEATORIOS USADOS PARA DIFERENTES FUNCIONES COMO POSICIONAR LA COMIDA DE LA SERPIENTE, DETERMINAR
    DONDE APARECE LA SERPIENTE POR PRIMERA VEZ ENTRE OTROS.
    */
    srand(time(0));
    y=rand()%36+5;
    pcx=rand()%50+29;
    pcy=rand()%36+5;
    //PRESENTACION JUEGO
    for(int v=0;v<6;v++){
        gotoxy(55,20);
        cout<<"       ---_ ......._-_--.    "<<endl;
        gotoxy(55,21);
        cout<<"      (|"<<bks<<" /      / /| "<<bks<<"  "<<bks<<"   "<<endl;
        gotoxy(55,22);
        cout<<"      /  /     .'  -=-'   `. "<<endl;
        gotoxy(55,23);
        cout<<"     /  /    .'             )"<<endl;
        gotoxy(55,24);
        cout<<"   _/  /   .'        _.)   / "<<endl;
        gotoxy(55,25);
        cout<<"  / o   o        _.-' /  .'  "<<endl;
        gotoxy(55,26);
        cout<<"  "<<bks<<"          _.-'    / .'*|  "<<endl;
        gotoxy(55,27);
        cout<<"   "<<bks<<"______.-'//    .'.' "<<bks<<"*|  "<<endl;
        gotoxy(55,28);
        cout<<"    "<<bks<<"|  "<<bks<<" | //   .'.' _ |*|  "<<endl;
        gotoxy(55,29);
        cout<<"     `   "<<bks<<"|//  .'.'_ _ _|*|  "<<endl;
        gotoxy(55,30);
        cout<<"      .  .// .'.' | _ _ "<<bks<<"*|  "<<endl;
        gotoxy(55,31);
        cout<<"      "<<bks<<"`-|"<<bks<<"_/ /    "<<bks<<" _ _ "<<bks<<"*"<<bks<<" "<<endl;
        gotoxy(55,32);
        cout<<"       `/'"<<bks<<"__/      "<<bks<<" _ _ "<<bks<<"*"<<bks<<""<<endl;
        gotoxy(55,33);
        cout<<"      /^|            "<<bks<<" _ _ "<<bks<<"*"<<endl;
        gotoxy(55,34);
        cout<<"     '  `             "<<bks<<" _ _ "<<bks<<""<<endl;
        gotoxy(55,35);
        cout<<"                       "<<bks<<"_    "<<endl;
        Sleep(200);
        system("cls");
        cout<<"           /^"<<bks<<"/^"<<bks<<"                                     "<<endl;
        cout<<"         _|__|  O|                                    "<<endl;
        cout<<""<<bks<<"/     /~     "<<bks<<"_/ "<<bks<<"                                   "<<endl;
        cout<<" "<<bks<<"____|__________/  "<<bks<<"                                 "<<endl;
        cout<<"        "<<bks<<"_______      "<<bks<<"                               "<<endl;
        cout<<"                `"<<bks<<"     "<<bks<<"                 "<<bks<<"            "<<endl;
        cout<<"                  |     |                  "<<bks<<"          "<<endl;
        cout<<"                 /      /                    "<<bks<<"        "<<endl;
        cout<<"                /     /                       "<<bks<<""<<bks<<"      "<<endl;
        cout<<"              /      /                         "<<bks<<" "<<bks<<"    "<<endl;
        cout<<"             /     /                            "<<bks<<"  "<<bks<<"  "<<endl;
        cout<<"           /     /             _----_            "<<bks<<"   "<<bks<<""<<endl;
        cout<<"          /     /           _-~      ~-_         |   |"<<endl;
        cout<<"         (      (        _-~    _--_    ~-_     _/   |"<<endl;
        cout<<"          "<<bks<<"      ~-____-~    _-~    ~-_    ~-_-~    / "<<endl;
        cout<<"            ~-_           _-~          ~-_       _-~  "<<endl;
        cout<<"               ~--______-~                ~-___-~     "<<endl;
        Sleep(200);
        system("cls");
    }
    gotoxy(5,12);
    cout<<"   SSSSSSSSSSSSSSS                                     kkkkkkkk                               "<<endl;
    gotoxy(5,13);
    cout<<" SS:::::::::::::::S                                    k::::::k                               "<<endl;
    gotoxy(5,14);
    cout<<"S:::::SSSSSS::::::S                                    k::::::k                               "<<endl;
    gotoxy(5,15);
    cout<<"S:::::S     SSSSSSS                                    k::::::k                               "<<endl;
    gotoxy(5,16);
    cout<<"S:::::S            nnnn  nnnnnnnn      aaaaaaaaaaaaa    k:::::k    kkkkkkk    eeeeeeeeeeee    "<<endl;
    gotoxy(5,17);
    cout<<"S:::::S            n:::nn::::::::nn    a::::::::::::a   k:::::k   k:::::k   ee::::::::::::ee  "<<endl;
    gotoxy(5,18);
    cout<<" S::::SSSS         n::::::::::::::nn   aaaaaaaaa:::::a  k:::::k  k:::::k   e::::::eeeee:::::ee"<<endl;
    gotoxy(5,19);
    cout<<"  SS::::::SSSSS    nn:::::::::::::::n           a::::a  k:::::k k:::::k   e::::::e     e:::::e"<<endl;
    gotoxy(5,20);
    cout<<"    SSS::::::::SS    n:::::nnnn:::::n    aaaaaaa:::::a  k::::::k:::::k    e:::::::eeeee::::::e"<<endl;
    gotoxy(5,21);
    cout<<"       SSSSSS::::S   n::::n    n::::n  aa::::::::::::a  k:::::::::::k     e:::::::::::::::::e "<<endl;
    gotoxy(5,22);
    cout<<"            S:::::S  n::::n    n::::n a::::aaaa::::::a  k:::::::::::k     e::::::eeeeeeeeeee  "<<endl;
    gotoxy(5,23);
    cout<<"            S:::::S  n::::n    n::::na::::a    a:::::a  k::::::k:::::k    e:::::::e           "<<endl;
    gotoxy(5,24);
    cout<<"SSSSSSS     S:::::S  n::::n    n::::na::::a    a:::::a k::::::k k:::::k   e::::::::e          "<<endl;
    gotoxy(5,25);
    cout<<"S::::::SSSSSS:::::S  n::::n    n::::na:::::aaaa::::::a k::::::k  k:::::k   e::::::::eeeeeeee  "<<endl;
    gotoxy(5,26);
    cout<<"S:::::::::::::::SS   n::::n    n::::n a::::::::::aa:::ak::::::k   k:::::k   ee:::::::::::::e  "<<endl;
    gotoxy(5,27);
    cout<<" SSSSSSSSSSSSSSS     nnnnnn    nnnnnn  aaaaaaaaaa  aaaakkkkkkkk    kkkkkkk    eeeeeeeeeeeeee  "<<endl;
    gotoxy(34,33);
    cout<<"PRESIONE UNA TECLA PARA CONTINUAR";
    getch();
    system("cls");
    //FIN PRESENTACION DEL JUEGO
    char* nombre_jugador=new char[10];
    gotoxy(36,13);
    cout<<"Por Favor Ingrese Su Nombre:\n";
    gotoxy(48,15);
    leer_cadena(cin,nombre_jugador,10);
    while(nombre_jugador[0]=='\0'){
        system("cls");
        gotoxy(40,13);
        cout<<"Ingrese Un Nombre Valido:\n";
        gotoxy(45,15);
        leer_cadena(cin,nombre_jugador,10);
    }
    system("cls");
    gotoxy(44,15);
    cout<<"Bienvenido "<<nombre_jugador;
    gotoxy(36,18);
    cout<<"PRESIONE UNA TECLA PARA CONTINUAR";
    getch();
    system("cls");
    //DECLARACION DE LA MATRIZ CUADRO DE JUEGO.
    char cuadro[39][52];
    //CREACION DEL CUADRO DE JUEGO.
    //AQUI SE MUESTRA LA ESQUINA SUPERIOR IZQUIERDA
    cuadro[0][0]=esi;
    cout<<"\t\t\t\t\t\t PUNTAJE\n\n\t\t\t\t\t\t    "<<puntaje<<"\n\n"<<"\t\t\t    "<<cuadro[0][0];
    //ESTE CICLO SE ENCARGA DE MOSTRAR LA LINEA SUPERIOR DEL CUADRO DE JUEGO
    for(int i=1;i<51;i++){
        cuadro[0][i]=lh;
        cout<<cuadro[0][i];
    }
    //AQUI SE MUESTRA LA ESQUINA SUPERIOR DERECHA
    cuadro[0][51]=esd;
    cout<<cuadro[0][51]<<endl;
    //CICLO QUE RECORRE LAS FILAS DE LA MATRIZ
    for(int j=1;j<37;j++){
        //CICLO QUE RECORRE LAS COLUMNAS DE LA MATRIZ
        for(int i=0;i<52;i++){
            /*AQUI SE PONE UNA LINEA VERTICAL EN LA PRIMERA Y ULTIMA COLUMNA DE LA MATRIZ
            Y LAS DEMAS COLUMNAS SE PONE UN ESPACIO EN BLANCO.
            */
            if(i==0){
                cuadro[j][i]=lv;
                cout<<"\t\t\t    "<<cuadro[j][i];
            }else{
                if(i==51){
                    cuadro[j][i]=lv;
                    cout<<cuadro[j][i]<<endl;
                }else{
                    cuadro[j][i]=32;
                    cout<<cuadro[j][i];
                }
            }
        }//FIN CICLO QUE RECORRE LAS COLUMNAS DE LA MATRIZ
    }//FIN CICLO QUE RECORRE LAS FILAS DE LA MATRIZ
    //AQUI SE IMPRIME LA ESQUINA INFERIOR IZQUIERDA
    cuadro[38][0]=eii;
    cout<<"\t\t\t    "<<cuadro[38][0];
    //CICLO PARA IMPRIMIR LA LINEA INFERIOR DEL CUADRO
    for(int i=1;i<51;i++){
        cuadro[38][i]=lh;
        cout<<cuadro[38][i];
    }
    //AQUI SE MUESTRA LA ESQUINA INFERIOR DERECHA
    cuadro[38][51]=eid;
    cout<<cuadro[38][51];
    //CICLO PARA EL MOVIMIENTO DE LA SERPIENTE
    while(game!=1){
        //AQUI SE IMPRIME POR PRIMERA VEZ LA COMIDA DE LA SERPIENTE
        gotoxy(pcx,pcy);
        cuadro[pcy-4][pcx-28]=comida;
        cout<<cuadro[pcy-4][pcx-28];
        //IF DIRECCION 1
        if(direccion==1){
            //CICLO MOVIMIENTO HORIZONTAL HACIA LA DERECHA
            while(x<79){
                // CONTROL DEL TECLADO
                /*EN ESTE PASO SE USA LA FUNCION KBHIT QUE RETORNA 0 SI NO SE
                HA PRESIONADO NINGUNA TECLA Y RETURNA 1 EN EL CASO CONTRARIO,
                ENTONCES EN CASO DE QUE SE HAYA PRESIONADO ALGUNA TECLA, ENTRARA
                EN EL IF DONDE DE INMEDIATO SE PASA EL VALOR QUE ESTABA EN EL BUFFER
                DEL TECLADO A UNA VARIABLE A POR MEDIO DE UN GETCH Y DESPUES TAMBIEN
                SE LE PASA ESE VALOR A UNA VARIABLE B, ESTO SE HACE PORQUE LAS TECLAS
                ESPECIALES COMO LAS FLECHAS DE DIRECCION, TIENEN UN VALOR DIFERENTE
                AL DE LAS TECLAS COMUNES EN ASCII YA QUE ES MAS LARGO Y NO SE PUEDE
                CAPTURAR EN UN SOLO GETCH, POR LO QUE SE USAN DOS PARA CAPTURAR EL VALOR
                DE LA TECLA.
                */
                if(kbhit()){
                    a=getch();
                    if(a==-32){
                        b=getch();
                    }
                    if(b==72){
                        direccion=4;
                        break;
                    }
                    if(b==80){
                        direccion=2;
                        break;
                    }
                }//FIN CONTROL DEL TECLADO
                //VERIFICACION CHOQUE SERPIENTE
                if(cuadro[y-4][x-28]==cuadrito){
                    game=1;
                    break;
                }
                if(x==78){
                    gotoxy(x,y);
                    cuadro[y-4][x-28]=cuadrito;
                    cout<<cuadro[y-4][x-28];
                    Sleep(velocidad);
                    gotoxy(x,y);
                    cuadro[y-4][x-28]=32;
                    cout<<cuadro[y-4][x-28];
                    if(kbhit()){
                        a=getch();
                        if(a==-32){
                            b=getch();
                        }
                        if(b==72){
                            direccion=4;
                            break;
                        }
                        if(b==80){
                            direccion=2;
                            break;
                        }
                    }
                    game=1;
                    break;
                }
                //FIN VERIFICACION CHOQUE SERPIENTE
                //VERIFICACION COMIDA DE LA SERPIENTE
                if((cuadro[y-4][x-28])==comida){
                    puntaje++;
                    velocidad-=1.2;
                    gotoxy(52,2);
                    cout<<puntaje;
                    pcx=rand()%50+29;
                    pcy=rand()%36+5;
                    while(cuadro[pcy-4][pcx-28]==cuadrito){
                        pcx=rand()%50+29;
                        pcy=rand()%36+5;
                    }
                    gotoxy(pcx,pcy);
                    cuadro[pcy-4][pcx-28]=comida;
                    cout<<cuadro[pcy-4][pcx-28];
                }//FIN VERIFICACION COMIDA SERPIENTE
                //IMPRESION DE LA SERPIENTE
                if(puntaje==0){
                    cuadro[y-4][x-28]=cuadrito;
                    gotoxy(x,y);
                    cout<<cuadro[y-4][x-28];
                    Sleep(velocidad);
                    gotoxy(x,y);
                    cuadro[y-4][x-28]=32;
                    cout<<cuadro[y-4][x-28];
                }
                else{
                    if(puntaant!=puntaje){
                        cuadro[y-4][x-28]=cuadrito;
                        gotoxy(x,y);
                        cout<<cuadro[y-4][x-28];
                        Sleep(velocidad);
                        posiciones[pos]=x;
                        pos++;
                        posiciones[pos]=y;
                        pos++;
                        posiciones[pos]=0;
                    }
                    else{
                        cuadro[y-4][x-28]=cuadrito;
                        gotoxy(x,y);
                        cout<<cuadro[y-4][x-28];
                        Sleep(velocidad);
                        posiciones[pos]=x;
                        pos++;
                        posiciones[pos]=y;
                        pos++;
                        posiciones[pos]=0;
                        int u=0;
                        while(posiciones[u]!=0){
                            u++;
                        }
                        gotoxy(posiciones[u-((2*puntaje)+2)],posiciones[u-((2*puntaje)+1)]);
                        cuadro[(posiciones[u-((2*puntaje)+1)])-4][(posiciones[u-((2*puntaje)+2)])-28]=32;
                        cout<<cuadro[(posiciones[u-((2*puntaje)+1)])-4][(posiciones[u-((2*puntaje)+2)])-28];
                    }
                }
                puntaant=puntaje;
                x++;
            }//FIN CICLO MOVIMIENTO HORIZONTAL HACIA LA DERECHA
        }//FIN IF DIRECCION 1
        //IF DIRECCION 2
        if(direccion==2){
            //CICLO MOVIMIENTO VERTICAL HACIA ABAJO
            while(y<41){
                //CONTROL DEL TECLADO
                if(kbhit()){
                    a=getch();
                    if(a==-32){
                        b=getch();
                    }
                    if(b==77){
                        direccion=1;
                        break;
                    }
                    if(b==75){
                        direccion=3;
                        break;
                    }
                }//FIN CONTROL DEL TECLADO
                //VERIFICACION CHOQUE SERPIENTE
                if(cuadro[y-4][x-28]==cuadrito){
                    game=1;
                    break;
                }
                if(y==40){
                    gotoxy(x,y);
                    cuadro[y-4][x-28]=cuadrito;
                    cout<<cuadro[y-4][x-28];
                    Sleep(velocidad);
                    gotoxy(x,y);
                    cuadro[y-4][x-28]=32;
                    cout<<cuadro[y-4][x-28];
                    if(kbhit()){
                        a=getch();
                        if(a==-32){
                            b=getch();
                        }
                        if(b==77){
                            direccion=1;
                            break;
                        }
                        if(b==75){
                            direccion=3;
                            break;
                        }
                    }
                    game=1;
                    break;
                }//FIN VERIFICACION CHOQUE SERPIENTE
                //VERIFICACION COMIDA DE LA SERPIENTE
                if((cuadro[y-4][x-28])==comida){
                    puntaje++;
                    velocidad-=1.2;
                    gotoxy(52,2);
                    cout<<puntaje;
                    pcx=rand()%50+29;
                    pcy=rand()%36+5;
                    while(cuadro[pcy-4][pcx-28]==cuadrito){
                        pcx=rand()%50+29;
                        pcy=rand()%36+5;
                    }
                    gotoxy(pcx,pcy);
                    cuadro[pcy-4][pcx-28]=comida;
                    cout<<cuadro[pcy-4][pcx-28];
                }//FIN VERIFICACION COMIDA SERPIENTE
                //IMPRESION DE LA SERPIENTE
                if(puntaje==0){
                    cuadro[y-4][x-28]=cuadrito;
                    gotoxy(x,y);
                    cout<<cuadro[y-4][x-28];
                    Sleep(velocidad);
                    gotoxy(x,y);
                    cuadro[y-4][x-28]=32;
                    cout<<cuadro[y-4][x-28];
                }
                else{
                    if(puntaant!=puntaje){
                        cuadro[y-4][x-28]=cuadrito;
                        gotoxy(x,y);
                        cout<<cuadro[y-4][x-28];
                        Sleep(velocidad);
                        posiciones[pos]=x;
                        pos++;
                        posiciones[pos]=y;
                        pos++;
                        posiciones[pos]=0;
                    }
                    else{
                        cuadro[y-4][x-28]=cuadrito;
                        gotoxy(x,y);
                        cout<<cuadro[y-4][x-28];
                        Sleep(velocidad);
                        posiciones[pos]=x;
                        pos++;
                        posiciones[pos]=y;
                        pos++;
                        posiciones[pos]=0;
                        int u=0;
                        while(posiciones[u]!=0){
                            u++;
                        }
                        gotoxy(posiciones[u-((2*puntaje)+2)],posiciones[u-((2*puntaje)+1)]);
                        cuadro[(posiciones[u-((2*puntaje)+1)])-4][(posiciones[u-((2*puntaje)+2)])-28]=32;
                        cout<<cuadro[(posiciones[u-((2*puntaje)+1)])-4][(posiciones[u-((2*puntaje)+2)])-28];
                    }
                }
                puntaant=puntaje;
                y++;
            }//FIN CICLO MOVIMIENTO VERTICAL HACIA ABAJO
        }//FIN IF DIRECCION 2
        //IF DIRECCION 3
        if(direccion==3){
            //CICLO MOVIMIENTO HORIZONTAL A LA IZQUIERDA
            while(x>28){
                // CONTROL DEL TECLADO
                if(kbhit()){
                    a=getch();
                    if(a==-32){
                        b=getch();
                    }
                    if(b==72){
                        direccion=4;
                        break;
                    }
                    if(b==80){
                        direccion=2;
                        break;
                    }
                }//FIN CONTROL DEL TECLADO
                //VERIFICACION CHOQUE SERPIENTE
                if(cuadro[y-4][x-28]==cuadrito){
                    game=1;
                    break;
                }
                if(x==29){
                    gotoxy(x,y);
                    cuadro[y-4][x-28]=cuadrito;
                    cout<<cuadro[y-4][x-28];
                    Sleep(velocidad);
                    gotoxy(x,y);
                    cuadro[y-4][x-28]=32;
                    cout<<cuadro[y-4][x-28];
                    if(kbhit()){
                        a=getch();
                        if(a==-32){
                            b=getch();
                        }
                        if(b==72){
                            direccion=4;
                            break;
                        }
                        if(b==80){
                            direccion=2;
                            break;
                        }
                    }
                    game=1;
                    break;
                }//FIN VERIFICACION CHOQUE SERPIENTE
                //VERIFICACION COMIDA DE LA SERPIENTE
                if((cuadro[y-4][x-28])==comida){
                    puntaje++;
                    velocidad-=1.2;
                    gotoxy(52,2);
                    cout<<puntaje;
                    pcx=rand()%50+29;
                    pcy=rand()%36+5;
                    while(cuadro[pcy-4][pcx-28]==cuadrito){
                        pcx=rand()%50+29;
                        pcy=rand()%36+5;
                    }
                    gotoxy(pcx,pcy);
                    cuadro[pcy-4][pcx-28]=comida;
                    cout<<cuadro[pcy-4][pcx-28];
                }//FIN VERIFICACION COMIDA SERPIENTE
                //IMPRESION DE LA SERPIENTE
                if(puntaje==0){
                    cuadro[y-4][x-28]=cuadrito;
                    gotoxy(x,y);
                    cout<<cuadro[y-4][x-28];
                    Sleep(velocidad);
                    gotoxy(x,y);
                    cuadro[y-4][x-28]=32;
                    cout<<cuadro[y-4][x-28];
                }
                else{
                    if(puntaant!=puntaje){
                        cuadro[y-4][x-28]=cuadrito;
                        gotoxy(x,y);
                        cout<<cuadro[y-4][x-28];
                        Sleep(velocidad);
                        posiciones[pos]=x;
                        pos++;
                        posiciones[pos]=y;
                        pos++;
                        posiciones[pos]=0;
                    }
                    else{
                        cuadro[y-4][x-28]=cuadrito;
                        gotoxy(x,y);
                        cout<<cuadro[y-4][x-28];
                        Sleep(velocidad);
                        posiciones[pos]=x;
                        pos++;
                        posiciones[pos]=y;
                        pos++;
                        posiciones[pos]=0;
                        int u=0;
                        while(posiciones[u]!=0){
                            u++;
                        }
                        gotoxy(posiciones[u-((2*puntaje)+2)],posiciones[u-((2*puntaje)+1)]);
                        cuadro[(posiciones[u-((2*puntaje)+1)])-4][(posiciones[u-((2*puntaje)+2)])-28]=32;
                        cout<<cuadro[(posiciones[u-((2*puntaje)+1)])-4][(posiciones[u-((2*puntaje)+2)])-28];
                    }
                }
                puntaant=puntaje;
                x--;
            }//FIN CICLO MOVIMIENTO HORIZONTAL A IZQUIERDA
        }//FIN IF DIRECCION 3
        //IF DIRECCION 4
        if(direccion==4){
            //CICLO MOVIMIENTO VERTICAL HACIA ARRIBA
            while(y>4){
                //CONTROL DEL TECLADO
                if(kbhit()){
                    a=getch();
                    if(a==-32){
                        b=getch();
                    }
                    if(b==77){
                        direccion=1;
                        break;
                    }
                    if(b==75){
                        direccion=3;
                        break;
                    }
                }//FIN CONTROL DEL TECLADO
                //VERIFICACION CHOQUE SERPIENTE
                if(cuadro[y-4][x-28]==cuadrito){
                    game=1;
                    break;
                }
                if(y==5){
                    gotoxy(x,y);
                    cuadro[y-4][x-28]=cuadrito;
                    cout<<cuadro[y-4][x-28];
                    Sleep(velocidad);
                    gotoxy(x,y);
                    cuadro[y-4][x-28]=32;
                    cout<<cuadro[y-4][x-28];
                    if(kbhit()){
                        a=getch();
                        if(a==-32){
                            b=getch();
                        }
                        if(b==77){
                            direccion=1;
                            break;
                        }
                        if(b==75){
                            direccion=3;
                            break;
                        }
                    }
                    game=1;
                    break;
                }//FIN VERIFICACION CHOQUE SERPIENTE
                //VERIFICACION COMIDA DE LA SERPIENTE
                if((cuadro[y-4][x-28])==comida){
                    puntaje++;
                    velocidad-=1.2;
                    gotoxy(52,2);
                    cout<<puntaje;
                    pcx=rand()%50+29;
                    pcy=rand()%36+5;
                    while(cuadro[pcy-4][pcx-28]==cuadrito){
                        pcx=rand()%50+29;
                        pcy=rand()%36+5;
                    }
                    gotoxy(pcx,pcy);
                    cuadro[pcy-4][pcx-28]=comida;
                    cout<<cuadro[pcy-4][pcx-28];
                }//FIN VERIFICACION COMIDA SERPIENTE
                //IMPRESION DE LA SERPIENTE
                if(puntaje==0){
                    cuadro[y-4][x-28]=cuadrito;
                    gotoxy(x,y);
                    cout<<cuadro[y-4][x-28];
                    Sleep(velocidad);
                    gotoxy(x,y);
                    cuadro[y-4][x-28]=32;
                    cout<<cuadro[y-4][x-28];
                }
                else{
                    if(puntaant!=puntaje){
                        cuadro[y-4][x-28]=cuadrito;
                        gotoxy(x,y);
                        cout<<cuadro[y-4][x-28];
                        Sleep(velocidad);
                        posiciones[pos]=x;
                        pos++;
                        posiciones[pos]=y;
                        pos++;
                        posiciones[pos]=0;
                    }
                    else{
                        cuadro[y-4][x-28]=cuadrito;
                        gotoxy(x,y);
                        cout<<cuadro[y-4][x-28];
                        Sleep(velocidad);
                        posiciones[pos]=x;
                        pos++;
                        posiciones[pos]=y;
                        pos++;
                        posiciones[pos]=0;
                        int u=0;
                        while(posiciones[u]!=0){
                            u++;
                        }
                        gotoxy(posiciones[u-((2*puntaje)+2)],posiciones[u-((2*puntaje)+1)]);
                        cuadro[(posiciones[u-((2*puntaje)+1)])-4][(posiciones[u-((2*puntaje)+2)])-28]=32;
                        cout<<cuadro[(posiciones[u-((2*puntaje)+1)])-4][(posiciones[u-((2*puntaje)+2)])-28];
                    }
                }
                puntaant=puntaje;
                y--;
            }//FIN CICLO MOVIMIENTO VERTICAL HACIA ARRIBA
        }//FIN IF DIRECCION 4
    }//FIN CICLO PARA EL MOVIMIENTO DE LA SERPIENTE
    system("cls");
    system("cls");
    cout<<"\n\n\n";
    cout<<"\t   ggggggggg   ggggg aaaaaaaaaaaaa      mmmmmmm    mmmmmmm       eeeeeeeeeeee    "<<endl;
    cout<<"\t  g:::::::::ggg::::g a::::::::::::a   mm:::::::m  m:::::::mm   ee::::::::::::ee  "<<endl;
    cout<<"\t g:::::::::::::::::g aaaaaaaaa:::::a m::::::::::mm::::::::::m e::::::eeeee:::::ee"<<endl;
    cout<<"\tg::::::ggggg::::::gg          a::::a m::::::::::::::::::::::me::::::e     e:::::e"<<endl;
    cout<<"\tg:::::g     g:::::g    aaaaaaa:::::a m:::::mmm::::::mmm:::::me:::::::eeeee::::::e"<<endl;
    cout<<"\tg:::::g     g:::::g  aa::::::::::::a m::::m   m::::m   m::::me:::::::::::::::::e "<<endl;
    cout<<"\tg:::::g     g:::::g a::::aaaa::::::a m::::m   m::::m   m::::me::::::eeeeeeeeeee  "<<endl;
    cout<<"\tg::::::g    g:::::ga::::a    a:::::a m::::m   m::::m   m::::me:::::::e           "<<endl;
    cout<<"\tg:::::::ggggg:::::ga::::a    a:::::a m::::m   m::::m   m::::me::::::::e          "<<endl;
    cout<<"\t g::::::::::::::::ga:::::aaaa::::::a m::::m   m::::m   m::::m e::::::::eeeeeeee  "<<endl;
    cout<<"\t  gg::::::::::::::g a::::::::::aa:::am::::m   m::::m   m::::m  ee:::::::::::::e  "<<endl;
    cout<<"\t    gggggggg::::::g  aaaaaaaaaa  aaaammmmmm   mmmmmm   mmmmmm    eeeeeeeeeeeeee  "<<endl;
    cout<<"\t            g:::::g                                                              "<<endl;
    cout<<"\tgggggg      g:::::g     ooooooooooo vvvvvvv           vvvvvvv eeeeeeeeeeee    rrrrr   rrrrrrrrr   "<<endl;
    cout<<"\tg:::::gg   gg:::::g   oo:::::::::::oov:::::v         v:::::vee::::::::::::ee  r::::rrr:::::::::r  "<<endl;
    cout<<"\tg:::::gg   gg:::::g  o:::::::::::::::ov:::::v       v:::::ve::::::eeeee:::::eer:::::::::::::::::r "<<endl;
    cout<<"\t g::::::ggg:::::::g  o:::::ooooo:::::o v:::::v     v:::::ve::::::e     e:::::err::::::rrrrr::::::r"<<endl;
    cout<<"\t  gg:::::::::::::g   o::::o     o::::o  v:::::v   v:::::v e:::::::eeeee::::::e r:::::r     r:::::r"<<endl;
    cout<<"\t    ggg::::::ggg     o::::o     o::::o   v:::::v v:::::v  e:::::::::::::::::e  r:::::r     rrrrrrr"<<endl;
    cout<<"\t       gggggg        o::::o     o::::o    v:::::v:::::v   e::::::eeeeeeeeeee   r:::::r            "<<endl;
    cout<<"\t\t\t     o::::o     o::::o     v:::::::::v    e:::::::e            r:::::r            "<<endl;
    cout<<"\t\t\t     o:::::ooooo:::::o      v:::::::v     e::::::::e           r:::::r            "<<endl;
    cout<<"\t\t\t     o:::::::::::::::o       v:::::v       e::::::::eeeeeeee   r:::::r            "<<endl;
    cout<<"\t\t\t      oo:::::::::::oo         v:::v         ee:::::::::::::e   r:::::r            "<<endl;
    cout<<"\t\t\t        ooooooooooo            vvv            eeeeeeeeeeeeee   rrrrrrr            "<<endl;
    ifstream entrada("puntajes.txt");
    char* lectura=new char[10];
    entrada>>lectura;
    int punthaje;
    entrada>>punthaje;
    if(puntaje>punthaje){
        cout<<"\n\n\n\n\n\n\n\t\t\t\tNUEVO RECORD"<<endl;
        cout<<"\n\n\t\t\t\t"<<nombre_jugador<<" Su Puntaje Fue:"<<puntaje<<"\n\n\t\t\t\tPRESIONE UNA TECLA PARA CONTINUAR";
        ofstream salida("puntajes.txt");
        salida<<nombre_jugador<<"\n"<<puntaje;
        getch();
    }else{
        cout<<"\n\n\n\n\n\t\t\t\t"<<nombre_jugador<<" Su Puntaje Fue:"<<puntaje;
        cout<<"\n\n\t\t\tNO HA PODIDO SUPERAR EL RECORD DE "<<lectura<<" QUE ES DE "<<punthaje;
        cout<<"\n\n\t\t\t\tPRESIONE UNA TECLA PARA CONTINUAR";
        getch();
    }
}//FIN DEL MAIN
