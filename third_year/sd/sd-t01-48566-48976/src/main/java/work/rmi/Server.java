package work.rmi;

import java.io.BufferedReader;
import java.io.Console;
import java.io.InputStreamReader;

public class Server {
    public static final String TEXT_GREEN = "\u001B[32m";
    public static final String TEXT_RED = "\u001B[31m";
    public static final String TEXT_BLUE = "\u001B[34m";
    public static final String TEXT_RESET = "\u001B[0m";

    static void showTitle(){
        System.out.println("\n/-------------------------------------\\ ");
        System.out.print(TEXT_BLUE);
        System.out.println("    ____                           ");
        System.out.println("   / ___|  ___ _ ____   _____ _ __ ");
        System.out.println("   \\___ \\ / _ \\ '__\\ \\ / / _ \\ '__|");
        System.out.println("    ___) |  __/ |   \\ V /  __/ |  ");
        System.out.println("   |____/ \\___|_|    \\_/ \\___|_|   ");
        System.out.print(TEXT_RESET);
        System.out.println("\n\\-------------------------------------/\n\n");
    }

    public static void main(String[] args) {

        int regPort= 1099; // default RMIRegistry port
        String regHost="localhost";
        String address="localhost";
        String dbName="Ads";
        String username="";
        String password="";


        if (args.length < 1 || args.length > 3) { // obrigar à presenca de um argumento
            System.out.println("Usage: java work.rmi.Server registryPort\n\nor\n\nUsage: java work.rmi.Server registryPort registryHost DataBaseName");     //Alterar package depois
            System.exit(1);
        }


        try {
            // ATENÇÃO: este porto é relativo ao binder e não ao servidor RMI
            regPort = Integer.parseInt(args[0]);
            if(args.length == 3 && args[1] != null && args[2] != null) {
                address = args[1];
                dbName = args[2];
            }

            BufferedReader input = new BufferedReader(new InputStreamReader(System.in));
            Console read = System.console();

            showTitle();

            System.out.print("\t => Username: ");
            username = input.readLine();

            System.out.print("\t => Password: ");
            if(read == null){
                password = input.readLine();
            }
            else{
                password = new String(read.readPassword());
            }

            // criar um Objeto Remoto
            Ads obj = new Impl(address, dbName, username, password);

            // Serviço de Nomes
            /**
             * Se quiser substituir o processo rmiregisty...
             * pode ativar o servidor de nomes neste mesmo processo (antes do bind)
             */
            java.rmi.registry.LocateRegistry.createRegistry(regPort);

            // usar o Registry local (mesma máquina) e porto regPort
            //java.rmi.registry.Registry registry = java.rmi.registry.LocateRegistry.getRegistry(regPort);

            // Bind. Args: nome do serviço e objeto remoto
            //registry.rebind("ads", obj);


	        //OUTRO MODO, indicando o servidor remoto para o serviço de nomes
	        java.rmi.Naming.rebind("rmi://"+regHost+":"+regPort+"/ads", obj);


            System.out.println("\n[ " + TEXT_GREEN + "RMI OBJECT BOUND TO SERVICE IN REGISTRY" + TEXT_RESET + " ]");

            System.out.println("[" + TEXT_GREEN + " SERVER ONLINE " + TEXT_RESET + "]\n");

            System.in.read();

            System.out.println("[" + TEXT_RED + " SERVER OFFLINE " + TEXT_RESET + "]\n");
        }
        catch (Exception ex) {
            ex.printStackTrace();
        }
    }

}
