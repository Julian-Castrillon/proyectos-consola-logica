#include <iostream>
#include <string>
using namespace std;

struct nodo{
    int id;
    string nombreCancion;
    string artista;
    int duracion;
    string genero;
    nodo* siguiente;
};


void agregarCancion(nodo* &cabeza){
    if (cabeza->siguiente == NULL){
        cout << "Escirba el id de la cancion: \n";
        cin >> cabeza->id;
        cin.ignore();
        cout << "Escirba el nombre de la cancion: \n";
        getline(cin, cabeza->nombreCancion);
        cout << "Escirba el artista de la cancion: \n";
        getline(cin, cabeza->artista);
        cout << "Escirba la duracion de la cancion en segundos: \n";
        cin >> cabeza->duracion;
        cin.ignore();
        cout << "Escirba el genero de la cancion: \n";
        getline(cin, cabeza->genero);
        cout << "\n";

        nodo* cancion = new nodo();
        cabeza->siguiente = cancion;

        return ;
    }

    nodo* aux = cabeza;
    while(aux->siguiente != NULL){
        aux = aux->siguiente;
    }

    nodo* cancion = new nodo();
    aux->siguiente = cancion;
    cout << "Escirba el id de la cancion: \n";
    cin >> aux->id;
    cin.ignore();
    cout << "Escirba el nombre de la cancion: \n";
    getline(cin, aux->nombreCancion);
    cout << "Escirba el artista de la cancion: \n";
    getline(cin, aux->artista);
    cout << "Escirba la duracion de la cancion en segundos: \n";
    cin >> aux->duracion;
    cin.ignore();
    cout << "Escirba el genero de la cancion: \n";
    getline(cin, aux->genero);
    cout << "\n";

}

void mostrarPlaylist(nodo* cabeza){
    if ( cabeza== NULL) {
        cout << "La playlist esta vacia\n";
        return;
    }

    nodo* aux = cabeza;

    while (aux->siguiente != NULL){

        cout << "=== Cancion ===\n";
        cout << "Id: " << aux->id << "\n";
        cout << "Cancion: " << aux->nombreCancion << "\n";
        cout << "Artista: " << aux->artista << "\n";
        cout << "Duracion: " << aux->duracion << "\n";
        cout << "Genero: " << aux->genero << "\n";
        cout << "\n\n";
        aux = aux->siguiente;
    }

}


void BuscarCancion(nodo* cabeza){
    if ( cabeza == NULL) {
        cout << "La playlist esta vacia\n";
        return;
    }
    cout << "ingresa el nombre de la cancion: ";
    string cancionBuscada;
    getline(cin, cancionBuscada);
    cout <<"\n";

    cout << "Ingresa el artista de la cancion: ";
    string artistaBuscado;
    getline(cin, artistaBuscado);
    cout <<"\n";

    nodo* aux = cabeza;

    while (aux != NULL && aux->nombreCancion != cancionBuscada && aux->artista != artistaBuscado){
        aux = aux->siguiente;
    }

    if (aux == NULL){
        cout << "Cancion no encontrada\n";
        return;
    }

    cout << "=== Datos de la cancion que comenzaste a reproducir ===\n";
    cout << "Id: " << aux->id << "\n";
    cout << "Cancion: " << aux->nombreCancion << "\n";
    cout << "Artista: " << aux->artista << "\n";
    cout << "Duracion: " << aux->duracion << "\n";
    cout << "Genero: " << aux->genero << "\n";
    cout << "\n\n";


}


void eliminarCancion(nodo* &cabeza){
    if ( cabeza == NULL) {
        cout << "La playlist esta vacia\n";
        return;
    }


    cout << "Escirba el nombre de la cancion: ";
    string nombreCancionEliminar, artistaEliminar;
    getline(cin, nombreCancionEliminar);
    cout << "\nEscirba el artista de la cancion: ";
    getline(cin, artistaEliminar);
    cout << "\n";

    nodo* aux = cabeza;
    nodo* anterior = NULL;

    //Comprobarr si la cancion a eliminar es la primera y eliminarla seegun la longitud de la playlist o si no es avanzar aux para buscarla en el while
    if(cabeza->siguiente != NULL && cabeza->nombreCancion != nombreCancionEliminar && cabeza->artista != artistaEliminar){
        aux = aux->siguiente;
    }else if (cabeza->nombreCancion == nombreCancionEliminar && cabeza->artista == artistaEliminar && cabeza->siguiente == NULL){
        delete aux;
        cabeza = NULL;
        cout << "Haz eliminado la unica cancion de la playlist\n";
        return;
    }else if(cabeza->nombreCancion == nombreCancionEliminar && cabeza->artista == artistaEliminar && cabeza->siguiente != NULL){
        cout << "La cancion que vas a eliminar es la primera de la playlist\n";
        cout << "=== Los datos de la cancion eliminada son ===\n";
        cout << "Id: " << aux->id << "\n";
        cout << "Cancion: " << aux->nombreCancion << "\n";
        cout << "Artista: " << aux->artista << "\n";
        cout << "Duracion: " << aux->duracion << "\n";
        cout << "Genero: " << aux->genero << "\n";
        cout << "\n\n";

        cabeza = aux->siguiente;
        delete aux;
        return;
    }


    while (aux != NULL && aux->nombreCancion != nombreCancionEliminar && aux->artista != artistaEliminar){
        anterior = anterior->siguiente;
        aux = aux->siguiente;
    }

    if (aux == NULL){
        cout << "Cancion no encontrada\n";
        return;
    }

    cout << "=== Los datos de la cancion eliminada son ===\n";
    cout << "Id: " << aux->id << "\n";
    cout << "Cancion: " << aux->nombreCancion << "\n";
    cout << "Artista: " << aux->artista << "\n";
    cout << "Duracion: " << aux->duracion << "\n";
    cout << "Genero: " << aux->genero << "\n";
    cout << "\n\n";


    anterior->siguiente = aux->siguiente;
    delete aux;
    return;


}


int contarCanciones(nodo *cabeza){
    if ( cabeza == NULL) {
        cout << "La playlist esta vacia\n";
        return 0;
    }

    nodo* aux = cabeza;
    int contador = 1;

    while (aux->siguiente != NULL){
        contador++;
        aux = aux->siguiente;
    }

    return contador;
}


void invertirPlaylist(nodo* &cabeza){

    //Evalua si cabeza es nula para evitar errores al intentar invertir una playlist vacia
    if ( cabeza == NULL) {
        cout << "La playlist esta vacia\n";
        return;
    }else if (cabeza->siguiente == NULL){
        cout << "La playlist solo tiene una cancion, no se puede invertir\n";
        return;
    }

    cout << "\nLa playlist antes de invertir es: \n";
    mostrarPlaylist(cabeza);
    cout << "\n\n";

    int totalCanciones = contarCanciones(cabeza);

    /*Creo punteros....
    nodo *cabezaOriginal = cabeza;
    nodo *auxiliarAdelantado = cabeza ->siguiente;


    while (totalCanciones != 0){
        while(auxiliarAdelantado->siguiente != NULL && auxiliar){
            auxiliarAdelantado = auxiliarAdelantado->siguiente;
        }
    }*/

}



void ordenarPlaylist(){
    cout << "Funcion en construccion\n";
}



 void Extra(){
    cout << "Funcion en construccion\n";
 }


int main(){
    int opcion = 0;
    int canciones = 0;

    cout << "=== Bienvenido a la playlist ===\n" << endl;
    cout << "Para iniciar la playlist debes crear por lo menos una cancion\n";

    nodo* cabeza = new nodo();
    agregarCancion(cabeza);


    do{      

        cout << "=== Menu ===\n" << endl;
        cout << "1. Agregar cancion\n";
        cout << "2. Mostrar playlist\n";
        cout << "3. Buscar cancion\n";
        cout << "4. Eliminar cancion\n";
        cout << "5. Contar canciones\n";
        cout << "6. Invertir playlist\n";
        cout << "7. Ordenar playlist\n";
        cout << "8. Extra\n";
        cout << "9. Salir\n";
        cout << "Ingrese una opcion: "; 
        cin >> opcion;
        cin.ignore();

        
        switch (opcion){
            case 1: 
                cout << "\n=== Agregar una cancion ===\n" << endl;
                agregarCancion(cabeza); break;
            case 2: 
                cout << "\n=== Mostrar playlist ===\n" << endl;
                mostrarPlaylist(cabeza); break;
            case 3: 
                cout << "\n=== Buscar una cancion ===\n" << endl;
                BuscarCancion(cabeza); break;
            case 4: 
                cout << "\n=== Eliminar una cancion = ==\n" << endl;
                eliminarCancion(cabeza); break;
            case 5: 
                cout << "\n=== Contar canciones ===\n" << endl;
                canciones = contarCanciones(cabeza);
                cout << "La playlist tiene " << canciones << " canciones\n";
                break;
            case 6: 
                cout << "\n=== Invertir playlist ===\n" << endl;
                invertirPlaylist(cabeza); break;
            case 7: 
                cout << "\n=== Ordenar playlist ===\n" << endl;
                ordenarPlaylist(); break;
            case 8: 
                cout << "\n=== Extra ===\n" << endl;
                Extra(); break;
            case 9: 
                cout << "\n=== Saliste del programa ===\n" << endl;
                break;
            default: 
                cout << "\n=== Opcion no valida ===\n" << endl;
                break;
        }

        if (cabeza == NULL){
            cout << "haz perdido el acceso a la playlist y debes comenzar una nueva\n";
            nodo* cabeza = new nodo();
        }

    }while (opcion != 9);

    
    
    return 0;
}
