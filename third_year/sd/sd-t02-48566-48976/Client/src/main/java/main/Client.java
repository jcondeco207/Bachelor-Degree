package main;

import java.io.*;
import java.net.InetAddress;
import java.nio.charset.StandardCharsets;
import java.util.List;
import java.util.ArrayList;
import java.time.LocalDate;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;


public class Client {

    public static final String TEXT_GREEN = "\u001B[32m";
    public static final String TEXT_BLUE = "\u001B[34m";
    public static final String TEXT_RED = "\u001B[31m";
    public static final String TEXT_RESET = "\u001B[0m";

    private static boolean isIn = false;
    private static String user = null;
    private static String baseUrl = null;

    private static String regHost = "localhost";
    private static String regPort = "8080";  // porto do binder

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

        System.out.println("\nBEM VINDO(A)\n\t => A qualquer momento insira o comando desejado\n\t => Para consultar os comandos disponíveis escreva 'help' ou '?'\n\t => Para sair escreva 'quit' \n\n");

    }

    /**
     * Função que mostra ao utilizador os comandos disponíveis no programa bem com o que executam
     */
    static void getHelp(){
        System.out.println("\nOs comandos disponiveis são os seguintes:");
        System.out.println("\n\t => 'sign in' - Inicia a sessão no sistema");
        System.out.println("\n\t => 'sign up' - Regista utilizador no sistema");
        System.out.println("\n\t => 'add' - Permite adicionar anúncios");
        System.out.println("\n\t => 'show ads' - Mostra os anúncios atualmente ativos");
        System.out.println("\n\t => 'show search' - Permite procurar com filtros");
        System.out.println("\n\t => 'search by name' - Permite procurar anúncios pelo nome do anunciante");
        System.out.println("\n\t => 'search by id' - Mostra os anúncios através do id inserido");
        System.out.println("\n\t => 'send msg' ou 'send message' - Envia uma mensagem para um anúncio ou para um utilizador");
        System.out.println("\n\t => 'check msg' ou 'check message' - Permite ver as mensagens de um anúncio ou de um utilizador");
        System.out.println("\n\t => 'check users' - Permite ver os utilizadores do sistema");
        System.out.println("\n\t => 'logout' - Termina a sessão do utilizador no sistema");
        System.out.println("\n\t => 'help' ou '?' - Mostra este menu");
        System.out.println("\n\t => 'quit' - Termina o programa \n");
    }


    /**
     * Post Event
     * @param url
     * @param params
     * @return
     * @throws IOException
     */
    public static String post(String url, String params) throws IOException {

        URL urlObj = new URL(url);
        HttpURLConnection postCon = (HttpURLConnection) urlObj.openConnection();
        postCon.setRequestMethod("POST");

        postCon.setRequestProperty("Content-Type", "application/json");
        postCon.setDoOutput(true);

        OutputStream osObj = postCon.getOutputStream();
        osObj.write(params.getBytes());

        osObj.flush();
        osObj.close();

        String response = "";
        try (BufferedReader br = new BufferedReader(new InputStreamReader(postCon.getInputStream(), StandardCharsets.UTF_8))) {
            String responseLine;
            while ((responseLine = br.readLine()) != null) {
                response += responseLine.trim();
            }
        }
        return response;
    }

    /**
     * Post para login
     * @param username
     * @param password
     * @return
     * @throws IOException
     */
    static boolean postSign(String username, String password) throws IOException {
        final String params =  "{\"username\":\"" + username + "\",\"password\":\"" + password + "\"}";
        String url =  "http://"+regHost+":"+regPort+"/sd/resultadoset/login";
        String response = post(url, params);
        return response.contains("{\"resultado\":\"OK\",\"resultados\":[]}");
    }

    /**
     * Post para Msg
     * @param destiny
     * @param username
     * @param message
     * @param url
     * @return
     * @throws IOException
     */
    static boolean postMessage(String destiny, String username, String message, String url) throws IOException {
        final String params =  "{\"destiny\":\"" + destiny + "\", \"username\":\"" + username + "\",\"message\":\"" + message + "\"}";
        String response = post(url, params);
        return response.contains("{\"resultado\":\"Mensagem entregue\",\"resultados\":[]}");
    }

    /**
     * Função que envia mensagens para um utilizador
     * @param msg
     * @param sender
     * @param destiny
     * @return
     * @throws IOException
     */
    static String sendUserMsg(String msg, String sender, String destiny) throws IOException {
        if(postMessage(destiny, sender, msg, "http://"+regHost+":"+regPort+"/sd/resultadoset/send_msg/user")){
            return "Mensagem enviada com sucesso!";
        }
        return "Mensagem não entregue. (T-T)";
    }

    /**
     * Função que envia mensagens para um anúncio
     * @param msg
     * @param sender
     * @param id
     * @return
     * @throws IOException
     */
    static String sendAdMsg(String msg, String sender, int id) throws IOException {
        if(postMessage(String.valueOf(id), sender, msg, "http://"+regHost+":"+regPort+"/sd/resultadoset/send_msg/ad")){
            return "Mensagem enviada com sucesso!";
        }
        return "Mensagem não entregue. (T-T)";
    }

    /**
     * Função que mostra a lista de mensagens de um utilizador
     * @param username
     * @return
     * @throws IOException
     * @throws ParseException
     */
    static List<String> showUserMsgs(String username) throws IOException, ParseException {
        List<String> l = new ArrayList<>();
        final String params =  "{\"destiny\":\"" + "" + "\", \"username\":\"" + username + "\",\"message\":\"" + "user" + "\"}";
        String response = post("http://"+regHost+":"+regPort+"/sd/resultadoset/check_msg", params);

        JSONParser translator = new JSONParser();
        JSONObject json = (JSONObject) translator.parse(response);

        JSONArray msg = (JSONArray) json.get("resultados");

        for(int i = 0; i < msg.size(); i++){
            String info = (String) msg.get(i);
            l.add(info);
        }

        return msg;
    }

    /**
     * Função que mostra a lista de mensagens de um anúncio
     * @param aid
     * @return
     * @throws IOException
     * @throws ParseException
     */
    static List<String> showAdMsgs(int aid) throws IOException, ParseException{
        List<String> l = new ArrayList<>();
        final String params =  "{\"destiny\":\"" + aid + "\", \"username\":\"" + "" + "\",\"message\":\"" + "ads" + "\"}";
        String response = post("http://"+regHost+":"+regPort+"/sd/resultadoset/check_msg", params);

        JSONParser translator = new JSONParser();
        JSONObject json = (JSONObject) translator.parse(response);

        JSONArray msg = (JSONArray) json.get("resultados");

        for(int i = 0; i < msg.size(); i++){
            String info = (String) msg.get(i);
            l.add(info);
        }
        return msg;
    }

    /**
     * Função para obter o alias
     * @param username
     * @return
     * @throws IOException
     * @throws ParseException
     */
    static String getAlias(String username) throws IOException, ParseException {
        final String params =  "{\"username\":\"" + username + "\"}";
        String url =  "http://"+regHost+":"+regPort+"/sd/resultadoset/alias";
        String response = post(url, params);

        JSONParser translator = new JSONParser();
        JSONObject json = (JSONObject) translator.parse(response);

        return (String) json.get("resultado");
    }

    /**
     * Função para fazer o registo do utilizador
     * @param username
     * @param password
     * @param alias
     * @param email
     * @return
     * @throws IOException
     */
    static boolean signup(String username, String password, String alias, String email) throws IOException {
        final String params =  "{\"username\":\"" + username + "\",\"password\":\"" + password + "\",\"alias\":\"" + alias + "\",\"email\":\"" + email +"\"}";
        String url =  "http://"+regHost+":"+regPort+"/sd/resultadoset/register";
        String response = post(url, params);
        return response.contains("{\"resultado\":\"OK\",\"resultados\":[]}");
    }

    /**
     * Função que cria anúncio
     * @param location
     * @param price
     * @param gender
     * @param date
     * @param advertiser
     * @param typology
     * @param type
     * @param details
     * @return
     * @throws IOException
     */
    static String newAd(String location, double price, String gender, String date, String advertiser, String typology, String type, String details) throws IOException {
        final String params = "{\"location\":\"" + location + "\",\"price\":\"" + price + "\",\"gender\":\"" + gender + "\",\"date\":\"" + date + "\",\"advertiser\":\"" + advertiser + "\",\"typology\":\"" + typology + "\",\"type\":\"" + type + "\",\"details\":\"" + details + "\"}";
        String url =  "http://"+regHost+":"+regPort+"/sd/resultadoset/add";
        post(url, params);
        return "Anúncio submetido com sucesso";
    }

    /**
     * Função que permite ao utilizador entrar com as suas credenciais
     * @param
     * @return
     * @throws IOException
     */
    static boolean signIn() throws IOException{
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

        if (postSign(username, password)) {
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
     * Função que obtem os parâmetros
     * @param params
     * @param isGet
     * @return
     */
    public static String getParams(List<String> params, boolean isGet){
        String toReturn;
        if(params.size() == 0){return "";}
        if(isGet){toReturn = "?";} else{ toReturn="";}
        for(String p : params){
            toReturn += p;
            if(params.indexOf(p) != (params.size() -1)){toReturn += "&";}
        }
        return toReturn;
    }

    /**
     * Função que retorna lista de anúncios devidamente formatada
     * @param ads
     * @return
     */
    public static List<String> toStringList(List<Ad> ads){
        List<String> strings = new ArrayList<>();
        for(Ad ad : ads){
            strings.add(ad.stringifinator());
        }
        return strings;
    }

    /**
     * Função que obtem os utilizadores
     * @param params
     * @param path
     * @return
     */
    public static List<String> getUsers(List<String> params, String path){
        String url = baseUrl + path + getParams(params, true);
        List<String> l = new ArrayList<String>();

        try {
            HttpURLConnection server = (HttpURLConnection) new URL(url).openConnection();
            server.setRequestProperty("Content-Type", "application/json");
            server.setRequestMethod("GET");

            BufferedReader bridge = new BufferedReader( new InputStreamReader( server.getInputStream() ) );
            String results = bridge.readLine();
            bridge.close();

            JSONParser translator = new JSONParser();
            JSONObject json = (JSONObject) translator.parse(results);

            JSONArray ads = (JSONArray) json.get("resultados");

            for(int i = 0; i < ads.size(); i++){
                String info = (String) ads.get(i);
                l.add(info);
            }
        }
        catch(Exception e){
            System.out.println("[ GET_EVENT FAILED ]");
        }
        return l;
    }

    /**
     * Função que obtem anúncios
     * @param params
     * @param path
     * @return
     */
    public static List<Ad> getAds(List<String> params, String path){
        String url = baseUrl + path + getParams(params, true);
        List<Ad> l = new ArrayList<Ad>();
        try {
            HttpURLConnection server = (HttpURLConnection) new URL(url).openConnection();
            server.setRequestProperty("Content-Type", "application/json");
            server.setRequestMethod("GET");
            BufferedReader bridge = new BufferedReader( new InputStreamReader( server.getInputStream() ) );
            String results = bridge.readLine();
            bridge.close();

            JSONParser translator = new JSONParser();
            JSONObject json = (JSONObject) translator.parse(results);

            JSONArray ads = (JSONArray) json.get("resultados");

            for(int i = 0; i < ads.size(); i++){
                JSONObject info = (JSONObject) ads.get(i);
                Ad ad = new Ad( info.get("location").toString(),
                        Double.parseDouble(info.get("price").toString()),
                        info.get("gender").toString(),
                        info.get("date").toString(),
                        info.get("advertiser").toString(),
                        info.get("typology").toString(),
                        info.get("type").toString(),
                        Boolean.parseBoolean(info.get("state").toString()),
                        Integer.parseInt(info.get("aid").toString()),
                        info.get("details").toString()
                );
                l.add(ad);
            }
        }
        catch(Exception e){
            System.out.println("[ GET_EVENT FAILED ]");
        }
        return l;
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

    public static void main(String args[]) throws IOException, ParseException {

        if (args.length != 2) { // requer 2 argumentos
            System.out.println("Usage: java Client registryHost registryPort argumentos");
            System.exit(1);
        }

        String address = args[0];
        if(address.equals("localhost")){
            address = InetAddress.getLocalHost().getHostAddress();
        }

        regHost = address;
        regPort = args[1];

        baseUrl = "http://"+regHost+":"+regPort+"/sd/resultadoset/";
        BufferedReader input = new BufferedReader(new InputStreamReader(System.in));
        AdsSubscriber as = new AdsSubscriber();
        as.start();
        System.out.println("Working Directory = " + System.getProperty("user.dir"));

        try {
            showMenu();

            String request;

            while (true) {
                System.out.print("Operação desejada: ");
                request = input.readLine().toLowerCase();

                if (request.strip().equals("quit")) {
                    break;
                }
                else if(request.equals("sign in")){
                    signIn();
                }
                else if(request.equals("sign up")){

                    System.out.print("\t => Primeiro e último nome: ");
                    String alias = input.readLine();

                    System.out.print("\t => Password: ");
                    String password = input.readLine();

                    System.out.print("\t => Username: ");
                    String username = input.readLine();

                    System.out.print("\t => Email: ");
                    String email = input.readLine();

                    boolean no = false;
                    // => Registo
                    while(!signup(username, password, alias, email)){
                        System.out.println("O nome de utilizador já existe, deseja tentar novamente? (Y/n)");
                        if(input.readLine().toLowerCase().equals("y")){
                            System.out.print("\t => Nova tentativa: ");
                            username = input.readLine();
                        }
                        else{
                            no = true;
                            break;
                        }
                    }

                    if(!no){
                        isIn = true;
                        user = username;
                    }

                    System.out.println();
                }

                else if(request.equals("help") || request.equals("?")){
                    getHelp();
                }

                else if (request.equals("add")) {
                    if(!isIn){if(!signIn()){continue;}}
                    String location, gender, advertiser, typology, type, details;
                    int price;

                    System.out.print("\t=> Localização: ");
                    location = input.readLine();

                    System.out.print("\t=> Preço: ");
                    price = Integer.parseInt(input.readLine());

                    System.out.print("\t=> Género: ");
                    gender = input.readLine().toLowerCase();

                    advertiser = getAlias(user);

                    System.out.print("\t=> Tipologia: ");
                    typology = input.readLine();

                    System.out.print("\t=> Tipo: ");
                    type = input.readLine();

                    System.out.print("\t=> Detalhes: ");
                    details = input.readLine();

                    if(location == null || gender == null || typology == null || type == null || details == null){
                        System.out.println("Erro, anúncio incompleto, preencha todos os campos requeridos.");
                        continue;
                    }

                    System.out.println(newAd(location, price, gender.strip().toLowerCase(), LocalDate.now().toString(),advertiser,typology,type.strip().toLowerCase(), details.strip().toLowerCase()));
                    System.out.println();
                }

                else if(request.equals("show ads")){
                    if(!isIn){if(!signIn()){continue;}}
                    showList(toStringList(getAds(new ArrayList<String>(), "adSearch")), "Anúncios ativos:");
                }

                else if(request.equals("show search")){
                    System.out.print("Indique o tipo de anúncio:\n\t=> 1: Oferta\n\t=> 2: Procura\nOpção desejada: ");
                    List<String> list = new ArrayList<>();
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
                    list.add("tipo=" + p1);

                    int p2 = 0;
                    String p3 = "", p4 = null, p5=null;
                    boolean hasFilters = false;

                    System.out.println("\nDeseja aplicar filtros? (Y/n)");

                    if(input.readLine().toLowerCase().equals("y")){
                        hasFilters = true;
                        System.out.print("\t=> Preço: ");
                        String price = input.readLine();
                        if(price.length() > 0){
                            p2 = Integer.parseInt(price);
                            list.add("preco=" + p2);
                        }

                        System.out.print("\t=> Género: \n\t=> 1: Masculino\n\t=> 2: Feminino \n\t=> 3: Outro\nOpção desejada: ");
                        String gender = input.readLine();
                        int o = 0;
                        if(gender.length() > 0){
                            o = Integer.parseInt(gender);

                        }
                        if(o == 1){ p3 = "masculino"; list.add("genero=" + p3);} else if(o == 2){ p3 = "feminino"; list.add("genero=" + p1); }

                        System.out.print("\t=> Localização: ");
                        p4 = input.readLine().toLowerCase();
                        if(p4.length() != 0){
                            list.add("zona=" + p4);
                        }

                        System.out.print("\t=> Descrição: ");
                        p5 = input.readLine().toLowerCase();
                        if(p5.length() != 0){
                            list.add("detalhes=" + p5);
                        }
                    }

                    showList(toStringList(getAds(list, "adSearch")), "Resultados de Pesquisa:");
                }

                else if(request.equals("search by name")){
                    System.out.print("\t => Nome do anunciante: ");
                    String advertiser = input.readLine();

                    List<String> list = new ArrayList<>();
                    if(advertiser.length() > 0){
                        String adv = advertiser.replace(" ", "+");
                        list.add("anunciante=" + adv);
                    }
                    showList(toStringList(getAds(list, "adSearch")), "Anúncios de " + advertiser + ":");
                }

                else if(request.equals("search by id")){
                    System.out.print("\t => id: ");
                    String inId = input.readLine();
                    int id = 0;
                    List<String> list = new ArrayList<>();
                    if(inId.length() > 0){
                        list.add("aid=" + inId);
                    }
                    showList(toStringList(getAds(list, "adSearch")), "Anúncio " + inId + ":");
                }

                else if(request.equals("send msg") || request.equals("send mensagem")){
                    if(!isIn){if(!signIn()){continue;}}

                    System.out.print("Indique o tipo de mensagens:\n\t=> 1: Utilizador\n\t=> 2: Anúncio\nOpção desejada: ");
                    String o = input.readLine();
                    int option = 0;
                    if(o.length() > 0){
                        option = Integer.parseInt(o);
                    }

                    if(option == 1){
                        System.out.print("\t => Destino: ");
                        String destiny = input.readLine();

                        System.out.print("\t => Mensagem: ");
                        String msg = input.readLine();

                        String sender = getAlias(user);
                        System.out.println(sendUserMsg(msg, sender, destiny) + "\n");
                    }

                    else if(option == 2){
                        System.out.print("\t => id: ");

                        String inId = input.readLine();
                        int id = 0;
                        if(inId.length() > 0){
                            id = Integer.parseInt(inId);
                        }

                        System.out.print("\t => Mensagem: ");
                        String msg = input.readLine();

                        String sender = getAlias(user);

                        System.out.println(sendAdMsg(msg, sender, id) + "\n");
                    }
                    else{
                        System.out.println("Opção inválida.");
                    }
                }

                else if(request.equals("check messages") || request.equals("check msg")){
                    System.out.print("Indique o tipo de mensagens:\n\t=> 1: Utilizador\n\t=> 2: Anúncio\nOpção desejada: ");
                    String o = input.readLine();
                    int option = 0;
                    if(o.length() > 0){
                        option = Integer.parseInt(o);
                    }

                    if(option == 1){
                        if(!isIn){if(!signIn()){continue;}}
                        showList(showUserMsgs(user), ("Mensagens do utilizador " + user + ":\n"));
                    }

                    else if(option == 2){
                        System.out.print("\t => id: ");

                        String inId = input.readLine();
                        int id = 0;
                        if(inId.length() > 0){
                            id = Integer.parseInt(inId);
                        }

                        showList(showAdMsgs(id), ("Mensagens para o anúncio " + id + ":\n"));
                    }
                }

                else if(request.equals("check users")){
                    if(!isIn){if(!signIn()){continue;}}
                    showList(getUsers(new ArrayList<String>(), "users"), "Utilizadores:\n");
                }

                else if(request.equals("logout")){
                    if(isIn == true){
                        isIn = false;
                        user = null;
                        System.out.println("Sessão terminada\n");
                    }
                    else{
                        System.out.println("Não existe nenhuma sessão iniciada\n");
                    }
                }

                else{
                    System.out.println("Comando não reconhecido\n\n");
                }
            }
        }
        catch (Exception ex) {
            ex.printStackTrace();
        }

        input.close();
    }
}
