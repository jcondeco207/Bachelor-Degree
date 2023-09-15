package sd.rest;

import org.glassfish.grizzly.http.server.HttpServer;
import org.glassfish.jersey.grizzly2.httpserver.GrizzlyHttpServerFactory;
import org.glassfish.jersey.server.ResourceConfig;
import java.io.IOException;
import java.net.InetAddress;
import java.net.URI;
import java.net.UnknownHostException;

public class MainAppServer {

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

    private static URI getBaseURI(String addr, int port) {
        return URI.create("http://"+addr+":"+port+"/sd/");
    }

    public static HttpServer startServer(String addr, int port) throws IOException {
        // ativar um servico com os REST resources existentes neste pacote:
        ResourceConfig rc = new ResourceConfig().packages("sd.rest");

        return GrizzlyHttpServerFactory.createHttpServer(getBaseURI(addr,port), rc);
    }

    public static void main(String[] args) throws IOException {
        showTitle();

        int regPort= 8080; // default port
        String address;

        try {
            address = InetAddress.getLocalHost().getHostAddress();
        }
        catch (UnknownHostException e) {
            address = "localhost";
        }

        if (args.length == 1) { // obrigar à presenca de um argumento
            System.out.println("A utilizar settings personalizados");
            regPort = Integer.parseInt(args[0]);
        }


        HttpServer httpServer = startServer(address, regPort);

        ResourceConfig rc = new ResourceConfig().packages("sd.rest");
        System.out.println("\n## A correr em: " + getBaseURI(address, regPort) + "resultadoset");
        System.out.println("\n## Hit enter to stop the server...");

        System.in.read();
        httpServer.stop();
    }

}
