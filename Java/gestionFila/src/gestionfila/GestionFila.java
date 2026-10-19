package gestionfila;
import java.util.Scanner;


public class GestionFila {
    
    private static int menu (){
        Scanner sc = new Scanner(System.in);
        int opc;
        
        System.out.println("=====Menu======");
        System.out.println("1. Ingresar cliente ");
        System.out.println("2. Atender cliente");
        System.out.println("3. Deshacer ultima atencion");
        System.out.println("4. Mostrar filas ");
        System.out.println("5. Cerrar jornada");
        System.out.println("6. Cerrar sistema y obtener informe");
        System.out.print("Ingrese una opcion: ");
        opc = sc.nextInt();
        System.out.println("");
        return opc;
    }

   
    
    public static void main(String[] args) {
       int opc;
       //creo el objeto e incializo sistema
       sistemaAtencion sistema = new sistemaAtencion();
       //Aca estoy manejando el ciclo para repetir el menu 
       do{
           opc = menu();
           
           switch (opc){
               case 1:
                   cliente cliente = new cliente();
                   sistema.ingresarCliente(cliente);
                   break;
               case 2:
                   sistema.atenderCliente();
                   break;
               case 3:
                   sistema.ultimaAtencion();
                   break;
               case 4:
                   sistema.imprimirfilas();
                   break;
               case 5:
                   sistema.cerrarJornada();
                   break;
               case 6:
                   sistema.reporteFinal();
                   break;
               default:
                   System.out.println("opcion invalida");
                   break;
           }
           
       }while( opc!=6 );
    }
    
}
