package gestionfila;
import java.util.*;

//static: no es necesairo un objeto para su ejecucion. ¿De cual objeto estamos hablando?
//sin static: debe ser asignado a un objeto de la clase sietamAtencion para poder ser usado

public class sistemaAtencion {
    //Estoy creando las estructuras que usara nuestra logica
    private Queue<cliente> filaPrioritaria;
    private Queue<cliente> filaComun;
    private Stack<cliente> historial;
    
    //Los contadores que voy a usar con la logica
    private int turno, turnoActual, totalAtendidos, rechazosFilallena, rechazosCerrada, jornadaCerrada, turnoPrioridad, turnoAcPrioridad, totalReintegracion;
    Scanner sc = new Scanner(System.in);
    
    
    //El constructor para poder inicializar el objeto sistema lo inicializo con los valors uqe necesite
    public sistemaAtencion() {
        filaPrioritaria = new LinkedList<>();
        filaComun = new LinkedList<>();
        historial = new Stack<>();
        
        turno = 1;
        turnoActual = 1;
        totalAtendidos=0;
        rechazosFilallena=0;
        rechazosCerrada = 0;
        jornadaCerrada = 0;
        turnoPrioridad=1;
        turnoAcPrioridad=1;
        totalReintegracion = 1;

    }
    
   
    
    
    //Metodo para verificar si una persona es prioritaria
    private static boolean prioritario(int edad){
        boolean prioridad = false;
        if(edad > 60 ){
            prioridad = true;
        }
        return prioridad;
        
    }
    
    
    //metodo para pedir informacion de un cliente
    private void datos(cliente cliente){
        System.out.print("Ingrese el nombre del cliente: ");
        String nombre = sc.nextLine();
        cliente.setNombre(nombre);
        System.out.print("Ingrese el motivo de la consulta: ");
        String consulta = sc.nextLine();
        cliente.setMotivo(consulta);
        System.out.print("Ingrese la edad del cliente: ");
        int edad = sc.nextInt();
        cliente.setEdad(edad);
        //limpio el scanner para proximo uso
        sc.nextLine();
    }
    
    
    //metodo para ingrear usuarios (public para poder acceder desde el main y asignarselo al objeto sistema)
    public void ingresarCliente(cliente cliente){
        int salaEspera = filaPrioritaria.size() + filaComun.size();
        //evaluo si no han cerrado jornada
        if (jornadaCerrada == 0){ 
            //Evaluo si hay espacio en la sala de espera
            if( salaEspera <8){
                String nombre = cliente.getNombre();
                //Miro si es un retiro del historial o un usuario nuevo. con un solo elemento del objeto diferente de null basta
                if(nombre == null){
                    datos(cliente);
                }
            
                //evaluo su prioridad para saber donde lo asigno y que turno le doy
                int edad = cliente.getEdad();
                boolean prioridad = prioritario(edad);
            
                if(prioridad){
                    cliente.setTurno(turnoPrioridad);
                    turnoPrioridad++;
                    filaPrioritaria.add(cliente);
                    System.out.println("cliente añadido a la fila prioritaria. Turno prioritario: "+ cliente.getTurno());
                    System.out.println("");
                }else{
                    cliente.setTurno(turno);
                    turno++;
                    filaComun.add(cliente);
                    System.out.println("Cliente añadido a la fila comun. Turno: " + cliente.getTurno());
                    System.out.println("");
                }
            
            }else{
                System.out.println("La sala de espera esta llena");
                rechazosFilallena++;
            }
        }else{
            System.out.println("El sistema ya fue cerrado");
            rechazosCerrada++;
        }
    }
    
    
    //Metodo para atender clientes
    public void atenderCliente(){
        //evaluo si la fila prioridad tiene gente para atender y lo atiendo segun el caso
        if(!filaPrioritaria.isEmpty()){
            cliente cliente = filaPrioritaria.poll();
            historial.push(cliente);
            turnoAcPrioridad++;
            System.out.println("El cliente llamado " + cliente.getNombre() + " y con el turno prioritario numero " + cliente.getTurno() + " a sido atendido");
            System.out.println("Siguiente turno prioritario: " + turnoAcPrioridad);
            System.out.println("");
            totalAtendidos++;
            
        }else if(!filaComun.isEmpty()){
            cliente cliente = filaComun.poll();
            historial.push(cliente);
            turnoActual++;
            System.out.println("El cliente llamado " + cliente.getNombre() + " y con el turno numero " + cliente.getTurno() + " a sido atendido");
            System.out.println("Siguiente turno comun : " + turnoActual);
            System.out.println("");
            totalAtendidos++;
            
        }else{
            System.out.println("No hay nadie esperando ser atendido");
            System.out.println("");
        }
    }
    
    //deshacer ultima atencion
    public void ultimaAtencion(){
        //hago la pregunta esta vacia?  si hay espacio en ls filas y si la jornada aun esta activa
        int salaEspera = filaPrioritaria.size() + filaComun.size();
        //Debo separarlos para saber cual contador debo aumentar
        if (jornadaCerrada==0){
            if(salaEspera <8){
                if(!historial.isEmpty()){
                    if (totalReintegracion < 4){
                        cliente cliente = historial.pop();
                        System.out.println("Regresando al cliente "+ cliente.getNombre() + " a la fila");
                        ingresarCliente(cliente);
                        totalAtendidos--; 
                        totalReintegracion++;
                    }else{
                        System.out.println("Ya reintegraste mas de tres veces, no se puede realizar esta accion");
                    }
                }else{
                    System.out.println("No se atendio a nadie recientemente ");
                    System.out.println("");
                }
            }else{
                System.out.println("La sala de espera esta llena no se puede realizar la devolucion");
                rechazosFilallena++;
            }
        }else{
            System.out.println("El sistema ya fue cerrado");
            rechazosCerrada++;
            System.out.println("");
        }
    }
    
    //imprimir una cola
    private static void imprimirCola(Queue<cliente> cola){
        //Miro si contiene elementos
        if(!cola.isEmpty()){
            //c : cola una variable de tipo cliente que me va a recorrer la cola hasta que esta este vacia (no es necesario eliminarla)
            System.out.print("-> "); //inidico que ahi es la cabeza por asi decirlo debido a como recorre el for each (primera posicion)
            for(cliente c : cola){
                System.out.print("[" + c.getNombre() + "]" + " ");
            }
            System.out.println("");
        }else{
            System.out.println("Vacia");
            System.out.println("");
        }
    }
    
    private static void imprimirPila(Stack<cliente> pila){
        //Miro si contiene elementos
        if(!pila.isEmpty()){
            //c : pila una variable de tipo cliente que me va a recorrer la pila hasta que esta este vacia (no es necesario eliminarla)
            for(cliente c : pila){
                System.out.print("[" + c.getNombre() + "]" + " ");
            }
            //funciona igual que con el imprimir cola, siempre inicia en posicion 1 el for ech, enonces muestro cual es la cabeza.
            System.out.print("<-");
        }else{
            System.out.println("Vacia");
            System.out.println("");
        }
    }
    
    public void imprimirfilas(){
        System.out.println("===Fila comun===");
        imprimirCola(filaComun);
        System.out.println("===Fila prioritaria===");
        imprimirCola(filaPrioritaria);
        System.out.println("===Historial===");
        imprimirPila(historial);
        System.out.println("");
        System.out.println("");
    } 
            
    //cerrar jornada solo cambio la variable a 1 para que las validaciones de los demas meetodos haagn su trabajo
    public void cerrarJornada(){
        System.out.println("===Jornada laboral cerrada con exito====");
        int pendientes = filaPrioritaria.size() + filaComun.size();
        System.out.println("Clientes pendientes por atender: " + pendientes);
        System.out.println("");
        System.out.println("");
        
        jornadaCerrada = 1;
    }
    
    public void reporteFinal(){
        System.out.println("==Sistema Cerrado===");
        System.out.println("Reporte Final ");
        System.out.println("Clientes atendidos: " + totalAtendidos);
        System.out.println("Usuarios rechazados por fila llena: "+ rechazosFilallena);
        System.out.println("Usuarios rechazados por sistema cerrado: "+ rechazosCerrada);
        System.out.println("");
        if(!filaPrioritaria.isEmpty()){
            System.out.println("Clientes que no pudieron ser atendidos de la fila prioridad:");
            imprimirCola(filaPrioritaria);
        }else{
            System.out.println("No quedaron clientes prioritarios esperando ser atendidos");
        }
        
        if(!filaComun.isEmpty()){
            System.out.println("Clientes que no pudieron ser atendidos de la fila general:");
            imprimirCola(filaComun);
        }else{
            System.out.println("No quedaron clientes generales esperando ser atendidos");
        }
        
        if(!historial.isEmpty()){
            cliente c = historial.peek();
            System.out.print("El ultimo cliente atendido fue: " + c.getNombre() );
        }else{
            System.out.println("No quedaron clientes registrados en el historial el dia de hoy");
        }
    }
}




