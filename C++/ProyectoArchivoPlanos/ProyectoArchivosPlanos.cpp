#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip> 

using namespace std;


struct semestre {
    string codigoMateria;
    string nombreMateria;
    double quiz1;
    double quiz2;
    double quiz3;
    double quiz4;
    semestre* siguiente;
};

struct pensun {
    string codigoMateria;
    string nombreMateria;
    pensun* siguiente;
};

struct materiasAprobadas {
    string nombreMateria;
    string codigoMateria;
    double notaFinal;
    materiasAprobadas* siguiente;
};

//funciones julian
void archivosAListas(ifstream& leerPensun, ifstream& leerSemestre, ifstream& leerMateriasAprobadas,
    pensun*& cabezaPensun, semestre*& cabezaSemestre, materiasAprobadas*& cabezaMateriasAprobadas) {

    string codigo, nombre;

    // Cargar Pensum
    if (leerPensun.peek() == EOF) {
        cout << "El archivo PensunAcademico.txt esta vacio\n";
    }
    else {
        while (leerPensun >> codigo >> nombre) {
            if (cabezaPensun->codigoMateria == "") {
                cabezaPensun->codigoMateria = codigo;
                cabezaPensun->nombreMateria = nombre;
                cabezaPensun->siguiente = NULL;
            }
            else {
                pensun* nuevo = new pensun();
                nuevo->codigoMateria = codigo;
                nuevo->nombreMateria = nombre;
                nuevo->siguiente = NULL;

                pensun* aux = cabezaPensun;
                while (aux->siguiente != NULL) {
                    aux = aux->siguiente;
                }
                aux->siguiente = nuevo;
            }
        }
    }

    // Cargar Semestre
    double quiz1, quiz2, quiz3, quiz4;
    if (leerSemestre.peek() == EOF) {
        cout << "El archivo SemestreAcademico.txt esta vacio\n";
    }
    else {
        while (leerSemestre >> codigo >> nombre >> quiz1 >> quiz2 >> quiz3 >> quiz4) {
            if (cabezaSemestre->codigoMateria == "") {
                cabezaSemestre->codigoMateria = codigo;
                cabezaSemestre->nombreMateria = nombre;
                cabezaSemestre->quiz1 = quiz1;
                cabezaSemestre->quiz2 = quiz2;
                cabezaSemestre->quiz3 = quiz3;
                cabezaSemestre->quiz4 = quiz4;
                cabezaSemestre->siguiente = NULL;
            }
            else {
                semestre* nuevo = new semestre();
                nuevo->codigoMateria = codigo;
                nuevo->nombreMateria = nombre;
                nuevo->quiz1 = quiz1;
                nuevo->quiz2 = quiz2;
                nuevo->quiz3 = quiz3;
                nuevo->quiz4 = quiz4;
                nuevo->siguiente = NULL;

                semestre* aux = cabezaSemestre;
                while (aux->siguiente != NULL) {
                    aux = aux->siguiente;
                }
                aux->siguiente = nuevo;
            }
        }
    }

    // Cargar Materias Aprobadas
    double notaFinal;
    if (leerMateriasAprobadas.peek() == EOF) {
        cout << "El archivo MateriasAprobadas.txt esta vacio\n";
    }
    else {
        while (leerMateriasAprobadas >> codigo >> nombre >> notaFinal) {
            if (cabezaMateriasAprobadas->codigoMateria == "") {
                cabezaMateriasAprobadas->codigoMateria = codigo;
                cabezaMateriasAprobadas->nombreMateria = nombre;
                cabezaMateriasAprobadas->notaFinal = notaFinal;
                cabezaMateriasAprobadas->siguiente = NULL;
            }
            else {
                materiasAprobadas* nuevo = new materiasAprobadas();
                nuevo->codigoMateria = codigo;
                nuevo->nombreMateria = nombre;
                nuevo->notaFinal = notaFinal;
                nuevo->siguiente = NULL;

                materiasAprobadas* aux = cabezaMateriasAprobadas;
                while (aux->siguiente != NULL) {
                    aux = aux->siguiente;
                }
                aux->siguiente = nuevo;
            }
        }
    }
}

void listasArchivos(ofstream& escribirPensun, ofstream& escribirSemestre, ofstream& escribirMateriasAprobadas,
    pensun* cabezaPensun, semestre* cabezaSemestre, materiasAprobadas* cabezaMateriasAprobadas) {

    // Guardar Lista Pensum
    if (cabezaPensun == NULL || cabezaPensun->codigoMateria == "") {
        cout << "La lista pensum esta vacia, no se guardara nada en el archivo\n";
    }
    else {
        pensun* aux = cabezaPensun;
        while (aux != NULL) {
            escribirPensun << aux->codigoMateria << " " << aux->nombreMateria;
            if (aux->siguiente != NULL) escribirPensun << endl;
            aux = aux->siguiente;
        }
    }

    // Guardar Lista Semestre
    if (cabezaSemestre == NULL || cabezaSemestre->codigoMateria == "") {
        cout << "La lista semestre esta vacia, no se guardara nada en el archivo\n";
    }
    else {
        semestre* aux = cabezaSemestre;
        while (aux != NULL) {
            escribirSemestre << aux->codigoMateria << " " << aux->nombreMateria << " "
                << aux->quiz1 << " " << aux->quiz2 << " " << aux->quiz3 << " " << aux->quiz4;
            if (aux->siguiente != NULL) escribirSemestre << endl;
            aux = aux->siguiente;
        }
    }

    // Guardar Lista Materias Aprobadas
    if (cabezaMateriasAprobadas == NULL || cabezaMateriasAprobadas->codigoMateria == "") {
        cout << "La lista materias aprobadas esta vacia, no se guardara nada en el archivo\n";
    }
    else {
        materiasAprobadas* aux = cabezaMateriasAprobadas;
        while (aux != NULL) {
            escribirMateriasAprobadas << aux->nombreMateria << " " << aux->codigoMateria << " " << aux->notaFinal;
            if (aux->siguiente != NULL) escribirMateriasAprobadas << endl;
            aux = aux->siguiente;
        }
    }
}







//funciones menu
void inscribirMaterias(pensun* cabezaPensun, semestre*& cabezaSemestre) {
    if (cabezaPensun == NULL || cabezaPensun->codigoMateria == "") {
        cout << "No hay materias en el pensun para incribir.\n";
        return;
    }

    cout << "Materias disponibles en el pensun academico\n";
	cout << "Codigo - Nombre Materia\n";
    pensun* auxP = cabezaPensun;
    while (auxP != NULL) {
        cout << "[" << auxP->codigoMateria << "] " << auxP->nombreMateria << "\n";
        auxP = auxP->siguiente;
    }

    string codigoBuscar;
    cout << "\nIngrese el codigo de la materia que desea incribir: ";
    cin >> codigoBuscar;

    bool existeEnPensun = false;
    string nombreMateriaEncontrada = "";
    auxP = cabezaPensun;
    while (auxP != NULL) {
        if (auxP->codigoMateria == codigoBuscar) {
            existeEnPensun = true;
            nombreMateriaEncontrada = auxP->nombreMateria;
            break;
        }
        auxP = auxP->siguiente;
    }

    if (!existeEnPensun) {
        cout << "La materia no se encuentra en el pensun academico del sistema.\n";
        return;
    }

    semestre* auxS = cabezaSemestre;
    while (auxS != NULL && auxS->codigoMateria != "") {
        if (auxS->codigoMateria == codigoBuscar) {
            cout << "La materia ya se encuentra incrita en este semestre.\n";
            return;
        }
        auxS = auxS->siguiente;
    }

    if (cabezaSemestre->codigoMateria == "") {
        cabezaSemestre->codigoMateria = codigoBuscar;
        cabezaSemestre->nombreMateria = nombreMateriaEncontrada;
        cabezaSemestre->quiz1 = 0.0;
        cabezaSemestre->quiz2 = 0.0;
        cabezaSemestre->quiz3 = 0.0;
        cabezaSemestre->quiz4 = 0.0;
    }
    else {
        semestre* nuevoNode = new semestre();
        nuevoNode->codigoMateria = codigoBuscar;
        nuevoNode->nombreMateria = nombreMateriaEncontrada;
        nuevoNode->quiz1 = 0.0;
        nuevoNode->quiz2 = 0.0;
        nuevoNode->quiz3 = 0.0;
        nuevoNode->quiz4 = 0.0;
        nuevoNode->siguiente = NULL;

        auxS = cabezaSemestre;
        while (auxS->siguiente != NULL) {
            auxS = auxS->siguiente;
        }
        auxS->siguiente = nuevoNode;
    }
    cout << "Materia " << nombreMateriaEncontrada << " incrita con exito.\n";
}

void cancelarMaterias(semestre*& cabezaSemestre) {
    if (cabezaSemestre == NULL || cabezaSemestre->codigoMateria == "") {
        cout << "No tienes materias incritas actualmente.\n";
        return;
    }

    cout << "Materias incritas actualmente:\n" << endl;
    cout << "Codigo - Nombre Materia\n";
    semestre* aux = cabezaSemestre;
    while (aux != NULL) {
        cout << "[" << aux->codigoMateria << "] " << aux->nombreMateria << "\n";
        aux = aux->siguiente;
    }

    string codigoBuscar;
    cout << "\nIngrese el codigo de la materia que desea cancelar: ";
    cin >> codigoBuscar;

    semestre* actual = cabezaSemestre;
    semestre* anterior = NULL;
    bool encontrada = false;

    while (actual != NULL) {
        if (actual->codigoMateria == codigoBuscar) {
            encontrada = true;
            if (anterior == NULL) {
                if (actual->siguiente != NULL) {
                    cabezaSemestre = actual->siguiente;
                    delete actual;
                }
                else {
                    cabezaSemestre->codigoMateria = "";
                    cabezaSemestre->nombreMateria = "";
                    cabezaSemestre->quiz1 = cabezaSemestre->quiz2 = cabezaSemestre->quiz3 = cabezaSemestre->quiz4 = 0.0;
                }
            }
            else {
                anterior->siguiente = actual->siguiente;
                delete actual;
            }
            break;
        }
        anterior = actual;
        actual = actual->siguiente;
    }

    if (encontrada) {
        cout << "Se cancelo la materia con exito.\n";
    }
    else {
        cout << "No se encontro la materia con el codigo ingresado: " << codigoBuscar << endl;
    }
}

void agregarNotas(semestre* cabezaSemestre) {
    if (cabezaSemestre == NULL || cabezaSemestre->codigoMateria == "") {
        cout << "No hay materias incritas para asignar notas.\n";
        return;
    }

    string codigoBuscar;
    cout << "Ingrese el codigo de la materia a la que desea asinarle nota: ";
    cin >> codigoBuscar;

    semestre* aux = cabezaSemestre;
    bool encontrada = false;

    while (aux != NULL) {
        if (aux->codigoMateria == codigoBuscar) {
            encontrada = true;
            int numNota;
            cout << "Materia encontrada: " << aux->nombreMateria << "\n";
            cout << "Cual nota desea registrar? (Ingresar numero del 1 al 4): ";
            cin >> numNota;

            double calificacion;
            cout << "Ingrese la calificacion para la Nota (use punto (.) como separador" << numNota << ": ";
            cin >> calificacion;

            if (numNota == 1) aux->quiz1 = calificacion;
            else if (numNota == 2) aux->quiz2 = calificacion;
            else if (numNota == 3) aux->quiz3 = calificacion;
            else if (numNota == 4) aux->quiz4 = calificacion;
            else cout << "Numero de nota invalido (Debe ser de 1 a 4).\n";

            cout << "Nota agregada con exito.\n";
            break;
        }
        aux = aux->siguiente;
    }

    if (!encontrada) {
        cout << "Materia no encontrada en el semestre de ahora.\n";
    }
}

void mostrarMateriasInscritas(semestre* cabezaSemestre) {
    if (cabezaSemestre == NULL || cabezaSemestre->codigoMateria == "") {
        cout << "No tiene materias incritas en este semestre.\n";
        return;
    }

    cout << "Materias incritas \n";
    cout << left << setw(12) << "Codigo" << setw(50) << "Materia" << setw(10) << "Nota1" << setw(10) << "Nota2" << setw(10) << "Nota3" << setw(10) << "Nota4" << setw(10) << "Promedio" << endl;
    cout << "\n";

    semestre* aux = cabezaSemestre;
    while (aux != NULL) {
        double prom = (aux->quiz1 + aux->quiz2 + aux->quiz3 + aux->quiz4) / 4.0;
        cout << left << setw(12) << aux->codigoMateria
            << setw(50) << aux->nombreMateria
            << setw(10) << aux->quiz1
            << setw(10) << aux->quiz2
            << setw(10) << aux->quiz3
            << setw(10) << aux->quiz4
            << setw(10) << prom << endl;
        aux = aux->siguiente;
    }
}

void mostrarMateriasAprobadas(materiasAprobadas* cabezaMateriasAprobadas) {
    if (cabezaMateriasAprobadas == NULL || cabezaMateriasAprobadas->codigoMateria == "") {
        cout << "No registra ninguna materia aprovada aun.\n";
        return;
    }

    cout << "Materias Aprobadas\n";
    cout << left << setw(12) << "Codigo" << setw(35) << "Nombre Materia" << setw(10) << "Nota Final" << endl;
    cout << "\n";

    materiasAprobadas* aux = cabezaMateriasAprobadas;
    while (aux != NULL) {
        cout << left << setw(12) << aux->codigoMateria
            << setw(35) << aux->nombreMateria
            << setw(10) << aux->notaFinal << endl;
        aux = aux->siguiente;
    }
}

void mostrarPensumRestante(pensun* cabezaPensun) {
    if (cabezaPensun == NULL || cabezaPensun->codigoMateria == "") {
        cout << "Felicidades! No quedan materias pendientes en el pensun.\n";
        return;
    }

    cout << "--- Pensun Academico Restante ---\n";
    pensun* aux = cabezaPensun;
    while (aux != NULL) {
        cout << "[" << aux->codigoMateria << "] " << aux->nombreMateria << "\n";
        aux = aux->siguiente;
    }
}


void cerrarSemestre(pensun*& cabezaPensun, semestre*& cabezaSemestre, materiasAprobadas*& cabezaMateriasAprobadas) {

    if (cabezaSemestre == NULL || cabezaSemestre->codigoMateria == "") {
        cout << "No se cursaron materias en el semestre, no se puede cerrar el semestre\n";
        return;
    }

    semestre* auxSemestre = cabezaSemestre;

    int materiasAprobadasContador = 0;
    int totalMateriasSemestre = 0;

    cout << "\n--- Evaluando notas del semestre ---\n";

    while (auxSemestre != NULL) {
        totalMateriasSemestre++;
        double notaFinal = (auxSemestre->quiz1 + auxSemestre->quiz2 + auxSemestre->quiz3 + auxSemestre->quiz4) / 4.0;

        if (notaFinal >= 3.0) {
            cout << ">> Aprovaste la materia: " << auxSemestre->nombreMateria << " con un promedio de: " << notaFinal << "\n";
            materiasAprobadasContador++;

            if (cabezaMateriasAprobadas->codigoMateria == "") {
                cabezaMateriasAprobadas->codigoMateria = auxSemestre->codigoMateria;
                cabezaMateriasAprobadas->nombreMateria = auxSemestre->nombreMateria;
                cabezaMateriasAprobadas->notaFinal = notaFinal;
            }
            else {
                materiasAprobadas* nuevo = new materiasAprobadas();
                nuevo->nombreMateria = auxSemestre->nombreMateria;
                nuevo->codigoMateria = auxSemestre->codigoMateria;
                nuevo->notaFinal = notaFinal;
                nuevo->siguiente = NULL;

                materiasAprobadas* auxMA = cabezaMateriasAprobadas;
                while (auxMA->siguiente != NULL) {
                    auxMA = auxMA->siguiente;
                }
                auxMA->siguiente = nuevo;
            }

            pensun* actualP = cabezaPensun;
            pensun* anteriorP = NULL;
            while (actualP != NULL) {
                if (actualP->codigoMateria == auxSemestre->codigoMateria) {
                    if (anteriorP == NULL) {
                        if (actualP->siguiente != NULL) {
                            cabezaPensun = actualP->siguiente;
                        }
                        else {
                            cabezaPensun->codigoMateria = "";
                            cabezaPensun->nombreMateria = "";
                        }
                    }
                    else {
                        anteriorP->siguiente = actualP->siguiente;
                        delete actualP;
                    }
                    break;
                }
                anteriorP = actualP;
                actualP = actualP->siguiente;
            }
        }
        else {
            cout << ">> No Aprovaste la materia: " << auxSemestre->nombreMateria << " con un promedio de: " << notaFinal << "\n";
        }
        auxSemestre = auxSemestre->siguiente;
    }

    cout << "RESUMEN DEL SEMESTRE:\n";
    cout << "Materias cursadas: " << totalMateriasSemestre << "\n";
    cout << "Materias aprovadas: " << materiasAprobadasContador << "\n";

    if (materiasAprobadasContador > (totalMateriasSemestre / 2)) {
        cout << "ESTADO: Felicidades! Aprobo el semestre academico.\n";
    }
    else {
        cout << "ESTADO: Reprobo el semestre academico (No cumplo con el minimo de materias aprovadas).\n";
    }
    

    semestre* nxt;
    while (cabezaSemestre != NULL) {
        nxt = cabezaSemestre->siguiente;
        delete cabezaSemestre;
        cabezaSemestre = nxt;
    }
    cabezaSemestre = new semestre();
    cabezaSemestre->codigoMateria = "";
    cabezaSemestre->siguiente = NULL;

    cout << "\nSemestre finalizado con exito en memoria.\n";
}


int main() {
    ifstream leerPensun("PensunAcademico.txt");
    ifstream leerSemestre("SemestreAcademico.txt");
    ifstream leerMateriasAprobadas("MateriasAprobadas.txt");

    if (!leerPensun || !leerSemestre || !leerMateriasAprobadas) {
        cout << "Creando base de datos inicial de archivos (.txt)..." << endl;
        ofstream crearP("PensunAcademico.txt", ios::app);
        ofstream crearS("SemestreAcademico.txt", ios::app);
        ofstream crearM("MateriasAprobadas.txt", ios::app);
        crearP.close(); crearS.close(); crearM.close();

        leerPensun.open("PensunAcademico.txt");
        leerSemestre.open("SemestreAcademico.txt");
        leerMateriasAprobadas.open("MateriasAprobadas.txt");
    }

    semestre* cabezaSemestre = new semestre();
    cabezaSemestre->codigoMateria = "";
    cabezaSemestre->siguiente = NULL;

    pensun* cabezaPensun = new pensun();
    cabezaPensun->codigoMateria = "";
    cabezaPensun->siguiente = NULL;

    materiasAprobadas* cabezaMateriasAprobadas = new materiasAprobadas();
    cabezaMateriasAprobadas->codigoMateria = "";
    cabezaMateriasAprobadas->siguiente = NULL;

    archivosAListas(leerPensun, leerSemestre, leerMateriasAprobadas, cabezaPensun, cabezaSemestre, cabezaMateriasAprobadas);

    leerPensun.close();
    leerSemestre.close();
    leerMateriasAprobadas.close();

    int opcion = 0;

    while (opcion != 8) {
        cout << "\nSISTEMA ACADEMICO\n";
        cout << "1) Incribir materias\n";
        cout << "2) Cancelar materias\n";
        cout << "3) Agregar notas\n";
        cout << "4) Mostrar materias incritas\n";
        cout << "5) Mostrar materias aprovadas\n";
        cout << "6) Mostrar pensun academico restante\n";
        cout << "7) Finalizar / Cerrar semestre\n";
        cout << "8) Salir y Guardar cambios\n" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            cout << "Incribir materias\n" << endl;
            inscribirMaterias(cabezaPensun, cabezaSemestre);
            break;
        case 2:
            cout << "Cancelar materias\n" << endl;
            cancelarMaterias(cabezaSemestre);
            break;
        case 3:
            cout << "Agregar notas\n" << endl;
            agregarNotas(cabezaSemestre);
            break;
        case 4:
            cout << "Mostrar materias incritas\n" << endl;
            mostrarMateriasInscritas(cabezaSemestre);
            break;
        case 5:
            cout << "Mostrar materias aprovadas\n" << endl;
            mostrarMateriasAprobadas(cabezaMateriasAprobadas);
            break;
        case 6:
            cout << "Mostrar pensun academico restant\n" << endl;
            mostrarPensumRestante(cabezaPensun);
            break;
        case 7:
            cout << "finalizando semestre\n" << endl;
            cerrarSemestre(cabezaPensun, cabezaSemestre, cabezaMateriasAprobadas);
            break;
        case 8:
            cout << "\nSaliendo del programa y fuardando\n" << endl;
            break;
        default:
            cout << "\nOpcion no valida\n" << endl;
            break;
        }
    }

    ofstream escribirPensun("PensunAcademico.txt");
    ofstream escribirSemestre("SemestreAcademico.txt");
    ofstream escribirMateriasAprobadas("MateriasAprobadas.txt");

    cout << "Guardando cambios en archivos .txt de manera persistente...\n";
    listasArchivos(escribirPensun, escribirSemestre, escribirMateriasAprobadas, cabezaPensun, cabezaSemestre, cabezaMateriasAprobadas);

    escribirPensun.close();
    escribirSemestre.close();
    escribirMateriasAprobadas.close();

    cout << "Proceso terminado exitosamente!\n";
    return 0;
}








