#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <queue>
#include <stack>
#include <vector>

using namespace std;


//Funcion para la sala de enemigos
void salaEnemigos  (int &saludGuerrero, bool &arma, stack<string> &enemigosEncontrados)
{

    //Genera un enemigo aleatorio
    int enemigo = rand() % 3 + 1;
    string nombreEnemigo = "";
    cout << "Un enemigo ha aparecido\n";
    if (enemigo == 1){
         nombreEnemigo = "Esqueleto";
    } else if (enemigo == 2){ 
        nombreEnemigo = "Ogro";
    } else if (enemigo == 3){ 
        nombreEnemigo = "Dragon";
    } 

    enemigosEncontrados.push(nombreEnemigo);

    //Opciones de combate
    cout << "Te debes enfrentar a un " << nombreEnemigo << "\n Que deseas hacer?\n";
    cout << "1. Atacar\n";
    cout << "2. Huir\n";
    if (arma == true){
        cout << "3. Usar arma\n";
    }

    //Reguistrar la opcion
    int opcion = 0;
    cin >> opcion;

    //Numero para manejar las probabilidades
    int probabilidad = rand() % 100 + 1;

    //Menu con probabilidades segun la opcion tomada
    if (opcion == 1){
        if (probabilidad <= 55){
            saludGuerrero -= 20;
            cout << "Te han lastimado pero ganaste el combate \n";
        } else if (probabilidad <= 95) {
            cout << "Has ganado el combate y saliste ileso\n";
        } else {
            cout << "Has perdido el combate y estas muerto\n";
            saludGuerrero = 0;
        }

    } else if (opcion == 3 && arma == true){
        cout << "Has utilizado una arma y saliste ileso\n";
        cout << "Tu arma ha sido destruida\n";
        arma = false;

    } else if (opcion == 2){
        if ( probabilidad <= 70){
            saludGuerrero -= 30;
            cout << "Te han lastimado pero lograste huir \n";
        } else if (probabilidad <= 90) {
            cout << "has logrado huir sin ningun rasguno\n";
        } else {
            cout << "El enemigo te ha masacrado y estas muerto por no defenderte\n";
            saludGuerrero = 0;
        }
        
    } else {
        cout << "Opcion no valida\n Haz muerto por no elegir una opcion\n";
        saludGuerrero = 0;
    }

}


//Funcion para la sala de descanso
void salaDescanso (int &saludGuerrero)
{
    cout << "Te encuentras en una sala de descanso\n\n";
    if (saludGuerrero < 95){
        saludGuerrero += 5;
        cout << "Has dormido y recuperaste 5 puntos de salud\n";
    }else {
        cout << "Has dormido y estas listo para continuar\n";
    }
}


//Funcion para la sala de objetos
void salaObjetos (int &saludGuerrero, bool &arma, stack<string> &objetosEncontrados){

    //Genera un numero para el objeto aleatorio
    int objeto = rand() % 3 + 1;
    string nombreObjeto = "";
    cout << "Te encuentras una sala con objetos\n";
    if (objeto == 1){
        nombreObjeto = "Pocion";
    } else if (objeto == 2){
        nombreObjeto = "Arma";
    } else if (objeto == 3){
     nombreObjeto = "Escudo"; 
    }

    objetosEncontrados.push(nombreObjeto);

    //Menu de opciones
    cout << "Has encontrado un " << nombreObjeto << "\n Que deseas hacer?\n";
    cout << "1. Tomar\n";
    cout << "2. Ignorar\n";

    //Registrar la opcion
    int opcion = 0;
    cin >> opcion;

    //Menu con actualizaciones segun el objeto recibido y manejando nivel de vida e inventario de armas
    if (opcion == 1){
        if (objeto == 1){ 
            if (saludGuerrero <=80){
                cout << "Has tomado la " << nombreObjeto << " y recuperaste 20 puntos de salud\n";
                saludGuerrero += 20;
            }else if ( saludGuerrero > 80 && saludGuerrero < 100 ){
                cout << "Has tomado la " << nombreObjeto << " y recuperaste tu vida total\n";
                saludGuerrero = 100;
            }else {
                cout << "Has tomado la " << nombreObjeto << " pero no puedes recuperar mas salud\n";
            }
        
        } else if (objeto == 2){ 
            if(arma){
                cout << "Te es imposible equipar 2 armas\n";
            } else {
                cout << "Has equipado un arma\n";
                arma = true; 
            }

        } else if (objeto == 3){ 
            if (saludGuerrero <=90){
                cout << "Has tomado el " << nombreObjeto << " y recuperaste 10 puntos de salud\n";
                saludGuerrero += 10;
            }else if ( saludGuerrero > 90 && saludGuerrero < 100 ){
                cout << "Has tomado el " << nombreObjeto << " y recuperaste tu vida total\n";
                saludGuerrero = 100;
            }else {
                cout << "Has tomado el " << nombreObjeto << " pero no puedes recuperar mas salud\n";
            }
        }
    }else if (opcion == 2){
        cout << "Has ignorado el objeto\n";
    } else {
        cout << "Opcion no valida\n Haz muerto por no elegir una opcion\n";
        saludGuerrero = 0;
    }
}


int main()
{
    srand(time(0));

    int saludGuerrero = 100;
    bool arma = false;

    //vector a ser transformado a una cola para el almacenamiento de salas usando el algoritmo FIFO
    vector<string> salas = { "salaEnemigos", "salaEnemigos", "salaObjetos", "salaEnemigos", "salaDescanso", "salaObjetos", "salaEnemigos", "salaEnemigos", "salaObjetos", "salaEnemigos", "salaDescanso", "salaObjetos", "salaEnemigos", "salaDescanso"};

    queue<string> colaSalas;

    //Pasamos el vector a la cola
    for (int i = 0; i < salas.size(); i++){
        colaSalas.push(salas[i]);
    }


    //Vector a ser tratado como pila para el almacenamiento de enemigos y objetos encontrados durante la aventura usando el algoritmo LIFO
    stack<string> objetosEncontrados;
    stack<string> enemigosEncontrados;


    //Inicio del juego
    cout << "Bienvenido al juego Aventura del guerrero\n";
    cout << "Presiona enter para avanzar\n\n";



    //While principal donde se correra el juego para aveanzar por las diferentes salas
    while (saludGuerrero > 0 and !colaSalas.empty())
    {
        cin.get();
        string sala = colaSalas.front();
        colaSalas.pop();
        if (sala == "salaEnemigos"){
            salaEnemigos(saludGuerrero, arma, enemigosEncontrados);
        }else if (sala == "salaObjetos"){
            salaObjetos(saludGuerrero, arma, objetosEncontrados);
        }else if (sala == "salaDescanso"){
            salaDescanso(saludGuerrero);
        }

        //Evaluamos si el guerrero se encuentra muerto
        if(saludGuerrero <= 0){
            cout << "Haz muerto\n";
            cout << "Perdiste el juego\n";
            return 0;
        }

        //Mostramos el estado del guerrero
        cout << "la vida del guerrero es de: " << saludGuerrero << "\n\n\n";
        cin.get();

    }

    //Sala final si logra salir de todas las salas
    cout << "Haz llegado a la sala final\n";
    //Se simula el procedimiento de salaEnemigos pero con diferentes porcentajes de probabilidad por ser la sala final
    cout << "Te debes enfrentar al P.T.A.S \n¿Que deseas hacer?\n";
    cout << "1. Atacar\n";
    cout << "2. Huir\n";
    if (arma == true){
        cout << "3. Usar arma\n";
    }


    int opcion;
    cin >> opcion;

    int probabilidad = rand() % 100 + 1;

    //Menu con probabilidades segun la opcion tomada
    if (opcion == 1){
        if (probabilidad <= 60){
            saludGuerrero -= 40;
            cout << "Te han lastimado pero ganaste el combate \n";
        } else if (probabilidad <= 70) {
            cout << "Has ganado el combate y saliste ileso\n";
        } else {
            cout << "Has perdido el combate y estas muerto\n";
            saludGuerrero = 0;
        }
    } else if (opcion == 3 && arma == true){
        cout << "Has utilizado una arma y saliste ileso\n";
        cout << "Tu arma ha sido destruida\n";
        arma = false;

    } else if (opcion == 2){
        cout << "El enemigo te ha masacrado y estas muerto por no defenderte\n";
        saludGuerrero = 0;
    } else {
        cout << "Opcion no valida\n Haz muerto por no elegir una opcion\n";
        saludGuerrero = 0;
    }

    cout << "\n\n\n";

    //Evaluamos si el guerrero se encuentra muerto
    if(saludGuerrero <= 0){
        cout << "Haz muerto\n";
        cout << "Perdiste el juego\n";
        return 0;
    }

    cout << "Haz ganado el juego\n";
    cout << "Enemigos encontrados: \n";

    //Mostramos los enemigos y objetos encontrados
    while (!enemigosEncontrados.empty()){
        cout << "- " << enemigosEncontrados.top() << "\n";
        enemigosEncontrados.pop();
    }

    cout << "\n\n\n";
    cout << "\nObjetos encontrados: \n";
    while (!objetosEncontrados.empty()){
        cout << "- " << objetosEncontrados.top() << "\n";
        objetosEncontrados.pop();
    }

    cout << "Felicitaciones guerrero\n";
    


    return 0;
}