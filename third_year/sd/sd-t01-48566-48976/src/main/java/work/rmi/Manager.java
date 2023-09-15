package work.rmi;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.ConnectException;
import java.sql.SQLOutput;
import java.util.List;
import java.util.LinkedList;
import java.util.ArrayList;
import java.time.LocalDate;
import java.io.Console;

public class Manager {

    private static boolean isIn = false;
    private static String user = null;

    public static final String TEXT_GREEN = "\u001B[32m";
    public static final String TEXT_BLUE = "\u001B[34m";
    public static final String TEXT_RED = "\u001B[31m";
    public static final String TEXT_RESET = "\u001B[0m";

    /**
     * Função que imprime o menu na consola
     */
    static void showMenu(){
        System.out.println("\n/-------------------------------------------------------\\ ");
        System.out.print(TEXT_BLUE);
        System.out.println("   ____                         ____            _   ");
        System.out.println("  |  _ \\ ___   ___  _ __ ___   |  _ \\ ___ _ __ | |_ ");
        System.out.println("  | |_) / _ \\ / _ \\| '_ ` _ \\  | |_) / _ \\ '_ \\| __|");
        System.out.println("  |  _ < (_) | (_) | | | | | | |  _ <  __/ | | | |_ ");
        System.out.println("  |_| \\_\\___/ \\___/|_| |_| |_| |_| \\_\\___|_| |_|\\__|");
        System.out.print(TEXT_RESET);
        System.out.println("\n\\-------------------------------------------------------/\n\n");

        System.out.println("\nBEM VINDO(A) gestor\n\t => A qualquer momento insira o comando desejado\n\t => Para consultar os comandos disponíveis escreva 'help' ou '?'\n\t => Para sair escreva 'quit' \n\n");

    }

    /**
     * Função que mostra ao utilizador os comandos disponíveis no programa bem com o que executam
     */
    static void getHelp(){
        System.out.println("\nOs comandos disponiveis são os seguintes:");
        System.out.println("\n\t => 'sign in' - Inicia a sessão no sistema");
        System.out.println("\n\t => 'show ads' - Mostra os anúncios atualmente ativos");
        System.out.println("\n\t => 'show search' - Permite procurar com filtros");
        System.out.println("\n\t => 'search by name' - Permite procurar anúncios pelo nome do anunciante");
        System.out.println("\n\t => 'search by id' - Mostra os anúncios através do id inserido");
        System.out.println("\n\t => 'activate ad' - Muda o estado do anúncio para ativo do id inserido");
        System.out.println("\n\t => 'deactivate ad' - Muda o estado do anúncio para inativo do id inserido");
        System.out.println("\n\t => 'upgrade user' - Muda um utilizador cliente para gestor do id inserido");
        System.out.println("\n\t => 'check users' - Permite ver os utilizadores do sistema");
        System.out.println("\n\t => 'remove ad' - Remove um anúncio de acordo com o id inserido");
        System.out.println("\n\t => 'remove user' - Remove um utilizador de acordo com o username inserido");
        System.out.println("\n\t => 'logout' - Termina a sessão do utilizador no sistema");
        System.out.println("\n\t => 'help' ou '?' - Mostra este menu");
        System.out.println("\n\t => 'quit' - Termina o programa \n");
    }

    /**
     * Função que permite ao utilizador entrar com as suas credenciais
     *
     * @param obj
     * @return
     * @throws IOException
     */
    static boolean signIn(Ads obj) throws IOException{
        BufferedReader input = new BufferedReader(new InputStreamReader(System.in));
        Console read = System.console();

        System.out.print("\t => Username: ");
        String username = input.readLine();

        System.out.print("\t => Password: ");
        String password;
        if(read == null){
            password = input.readLine();
        }
        else{
            password = new String(read.readPassword());
        }


        if (obj.signin(username, password)) {
            isIn = true;
            user = username;
            System.out.println("\nBem vindo(a) " + username + "\n");
        }
        else{
            System.out.println("\nDados introduzidos incorretos\n");
        }
        return isIn;
    }

    /**
     * Função auxiliar para mostrar o conteúdo de uma lista linha a linha
     *
     * @param list
     * @param message
     */
    static void showList(List<String> list, String message){
        if(list.isEmpty()){
            System.out.println("Não existem anúncios ativos com as especificações pedidas.\n");
            return;
        }
        System.out.println("\n" + message);
        for(String a : list){
            System.out.println(a + "\n");
        }
        System.out.println();
    }

    public static void main(String args[]) throws IOException {
        String regHost = "localhost";
        String regPort = "1099";  // porto do binder

        BufferedReader input = new BufferedReader(new InputStreamReader(System.in));
        if (args.length != 2) { // requer 2 argumentos
            System.out.println("Usage: java Client registryHost registryPort argumentos");
            System.exit(1);
        }
        regHost = args[0];
        regPort = args[1];

        try {
            // objeto que fica associado ao proxy para objeto remoto
            Ads obj = (Ads) java.rmi.Naming.lookup("rmi://" + regHost + ":" + regPort + "/ads");

            showMenu();
            String request;

            if(!isIn){
                if(!signIn(obj)){
                    return;
                }

                if(!obj.isSudo(user)){
                    System.out.println("Não tem autorização para aceder ao programa.");
                    return;
                }
            }

            while (true) {
                System.out.print("Operação desejada: ");
                request = input.readLine().toLowerCase();

                if (request.strip().equals("quit")) {
                    break;
                }

                else if(request.equals("sign in")){
                    signIn(obj);
                }

                else if(request.equals("help") || request.equals("?")){
                    getHelp();
                }

                else if(request.equals("show ads")){
                    if(!isIn){if(!signIn(obj)){continue;}}
                    int option = 1;
                    if(obj.isSudo(user)){
                        System.out.println("Deseja visualizar os inativos também? (Y/n)");
                        if(input.readLine().toLowerCase().equals("y")){
                            option = 2;
                        }
                    }

                    if(option == 1){
                        showList(obj.showActiveAds(), "Anúncios ativos:");
                    }
                    else{
                        showList(obj.showAllAds(), "Anúncios:");
                    }

                }

                //Adicionar inativos também
                else if(request.equals("show search")){
                    System.out.print("Indique o tipo de anúncio:\n\t=> 1: Oferta\n\t=> 2: Procura\nOpção desejada: ");
                    String typeO = input.readLine();
                    int option = 0;
                    if(typeO.length() > 0){
                        option = Integer.parseInt(typeO);
                    }
                    String p1;
                    if(option == 1){ p1 = "oferta"; } else if(option == 2){ p1 = "procura"; } else{
                        System.out.println("Opção Inválida\n");
                        continue;
                    }

                    double p2 = 0;
                    String p3 = "", p4 = null;
                    boolean hasFilters = false;

                    System.out.println("\nDeseja aplicar filtros? (Y/n)");

                    if(input.readLine().toLowerCase().equals("y")){
                        hasFilters = true;
                        System.out.print("\t=> Preço: ");
                        String price = input.readLine();
                        if(price.length() > 0){
                            p2 = Double.parseDouble(price);
                        }

                        System.out.print("\t=> Género: \n\t=> 1: Masculino\n\t=> 2: Feminino \n\t=> 3: Outro\nOpção desejada: ");
                        String gender = input.readLine();
                        int o = 0;
                        if(gender.length() > 0){
                            o = Integer.parseInt(gender);
                        }
                        if(o == 1){ p3 = "masculino"; } else if(o == 2){ p3 = "feminino"; }

                        System.out.print("\t=> Localização: ");
                        p4 = input.readLine().toLowerCase();
                    }
                    List<String> list = obj.showSearch(p1,p2,p3,p4, hasFilters);
                    showList(list, "Resultados de pesquisa:");

                }

                else if(request.equals("search by name")){
                    System.out.print("\t => Nome do anunciante: ");
                    String advertiser = input.readLine();
                    showList(obj.searchBy("select * from ads where state=true and advertiser= '" + advertiser + "'"), "Anúncios de " + advertiser + ":");
                }

                else if(request.equals("search by id")){
                    System.out.print("\t => id: ");
                    String inId = input.readLine();
                    int id = 0;
                    if(inId.length() > 0){
                        id = Integer.parseInt(inId);
                        showList(obj.searchBy("select * from ads where aid="+ id ), "Anúncio " + id + ":");
                    }
                    else{
                        System.out.println("ID inválido.");
                    }

                }

                else if(request.equals("activate ad")){
                    System.out.print("\t => id: ");
                    String inId = input.readLine();
                    int id = 0;
                    if(inId.length() > 0){
                        id = Integer.parseInt(inId);
                    }

                    if(obj.activateAd(id)){
                        System.out.println("Estado alterado com sucesso\n");
                    }
                    else{
                        System.out.println("O anúncio desejado não se encontra disponível\n");
                    }
                }

                else if(request.equals("deactivate ad")){
                    System.out.print("\t => id: ");
                    String inId = input.readLine();
                    int id = 0;
                    if(inId.length() > 0){
                        id = Integer.parseInt(inId);
                    }

                    if(obj.deactivateAd(id)){
                        System.out.println("Estado alterado com sucesso\n");
                    }
                    else{
                        System.out.println("O anúncio desejado não se encontra disponível\n");
                    }
                }

                else if(request.equals("upgrade user")){
                    System.out.print("\t => username: ");
                    String toEvolve = input.readLine();
                    if(obj.upgradeUser(toEvolve)){
                        System.out.println("\n" + toEvolve + " foi promovido a gestor\n");
                    }
                }

                else if(request.equals("check users")){
                    showList(obj.showUsers(), "Utilizadores:\n");
                }

                else if(request.equals("remove ad")){
                    System.out.print("\t => id: ");
                    String inId = input.readLine();
                    int idToRmv = 0;
                    if(inId.length() > 0){
                        idToRmv = Integer.parseInt(inId);
                    }

                    if(obj.removeAd(idToRmv)){
                        System.out.println("\nO anúncio " + idToRmv + " foi removido do sistema\n");
                    }
                    else{
                        System.out.println("\nNão foi possível remover o anúncio " + idToRmv);
                    }
                }

                else if(request.equals("remove user")){
                    System.out.print("\t => username: ");
                    String toDelete = input.readLine();
                    if(obj.purgeUser(toDelete)){
                        System.out.println("\n" + toDelete + " foi removido do sistema\n");
                    }
                    else{
                        System.out.println("\nNão foi possível remover o utilizador " + toDelete);
                    }
                }

                else if(request.equals("logout")){
                    if(isIn == true){
                        isIn = false;
                        user = null;
                        System.out.println("Sessão terminada");
                    }
                    else{
                        System.out.println("Não existe nenhuma sessão iniciada");
                    }
                }

                else{
                    System.out.println("Comando não reconhecido\n\n");
                }
            }
        }
        catch(java.rmi.ConnectException e){
            System.out.println("O servidor ao qual tentou aceder não se encontra ativo\n\t => " + regHost + " porta: " + regPort);
        }
        catch (Exception ex) {
            ex.printStackTrace();
        }

        input.close();
    }
}
