package main;

import java.io.*;
import java.net.InetAddress;
import java.nio.charset.StandardCharsets;
import java.util.*;

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


public class Admin {

    public static final String TEXT_GREEN = "\u001B[32m";
    public static final String TEXT_BLUE = "\u001B[34m";
    public static final String TEXT_RED = "\u001B[31m";
    public static final String TEXT_RESET = "\u001B[0m";

    private static boolean isIn = false;
    private static String user = null;
    private static String baseUrl = null;

    private static String regHost;
    private static String regPort;

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
     *
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
     *
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
     *
     * @param toDelete
     * @return
     * @throws IOException
     */
    public static Boolean purgeUser(String toDelete) throws IOException{
        final String params =  "{\"target\":\"" + toDelete + "\", \"action\":\"" + "purge" + "\",\"new_change\":\"" + "" + "\"}";
        String url =  "http://"+regHost+":"+regPort+"/sd/resultadoset/admin/change_state";
        String response = post(url, params);
        return response.contains("{\"resultado\":\"OK\",\"resultados\":[]}");
    }

    /**
     *
     * @param toEvolve
     * @return
     * @throws IOException
     */
    public static Boolean upgradeUser(String toEvolve) throws IOException{
        final String params =  "{\"target\":\"" + toEvolve + "\", \"action\":\"" + "upgrade" + "\",\"new_change\":\"" + "" + "\"}";
        String url =  "http://"+regHost+":"+regPort+"/sd/resultadoset/admin/change_state";
        String response = post(url, params);
        return response.contains("{\"resultado\":\"OK\",\"resultados\":[]}");
    }

    /**
     *
     * @param idToRmv
     * @return
     * @throws IOException
     */
    public static Boolean removeAd(int idToRmv) throws IOException{
        final String params =  "{\"target\":\"" + idToRmv + "\", \"action\":\"" + "apagar" + "\",\"new_change\":\"" + "" + "\"}";
        String url =  "http://"+regHost+":"+regPort+"/sd/resultadoset/admin/change_state";
        String response = post(url, params);
        return response.contains("{\"resultado\":\"OK\",\"resultados\":[]}");
    }

    /**
     *
     * @param idToRmv
     * @return
     * @throws IOException
     */
    public static Boolean deactivateAd(int idToRmv) throws IOException{
        final String params =  "{\"target\":\"" + idToRmv + "\", \"action\":\"" + "desativar" + "\",\"new_change\":\"" + "" + "\"}";
        String url =  "http://"+regHost+":"+regPort+"/sd/resultadoset/admin/change_state";
        String response = post(url, params);
        return response.contains("{\"resultado\":\"OK\",\"resultados\":[]}");
    }

    /**
     *
     * @param idToRmv
     * @return
     * @throws IOException
     */
    public static Boolean activateAd(int idToRmv) throws IOException{
        final String params =  "{\"target\":\"" + idToRmv + "\", \"action\":\"" + "ativar" + "\",\"new_change\":\"" + "" + "\"}";
        String url =  "http://"+regHost+":"+regPort+"/sd/resultadoset/admin/change_state";
        String response = post(url, params);
        return response.contains("{\"resultado\":\"OK\",\"resultados\":[]}");
    }

    /**
     *
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
     *
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
     *
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
     *
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
     *
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
     *
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
     *
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
     *
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
        return post(url, params);
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
     *
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
     *
     * @param ads
     * @return
     */
    public static List<String> toStringList(List<Ad> ads){
        ads.sort((a1, a2) -> a1.getState().compareTo(a2.getState()));
        List<String> strings = new ArrayList<>();
        for(Ad ad : ads){
            strings.add(ad.stringifinator2());
        }
        return strings;
    }

    /**
     *
     * @param params
     * @param path
     * @return
     */
    public static List<String> getUsers(List<String> params, String path){
        String url = baseUrl + path + getParams(params, true);
        System.out.println(url);
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
            System.out.println(json);

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
     *
     * @param params
     * @param path
     * @param state
     * @return
     */
    public static List<Ad> getAds(List<String> params, String path, Boolean state){
        if(state){ params.add("state=true"); }
        String url = baseUrl + path + getParams(params, true);
        List<Ad> l = new ArrayList<Ad>();
        try {
            HttpURLConnection server = (HttpURLConnection) new URL(url).openConnection();
            server.setRequestProperty("Content-Type", "application/json");
            server.setRequestMethod("GET");
            System.out.println(url);
            BufferedReader bridge = new BufferedReader( new InputStreamReader( server.getInputStream() ) );
            String results = bridge.readLine();
            bridge.close();

            JSONParser translator = new JSONParser();
            JSONObject json = (JSONObject) translator.parse(results);
            System.out.println(json);

            JSONArray ads = (JSONArray) json.get("resultados");
            System.out.println(ads);
            System.out.println(ads.size());

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
        String address = args[0];
        if(address.equals("localhost")){
            address = InetAddress.getLocalHost().getHostAddress();
        }

        regHost = address;
        regPort = "8080";  // porto do binder

        if (args.length != 2) { // requer 2 argumentos
            System.out.println("Usage: java Client registryHost registryPort argumentos");
            System.exit(1);
        }
        regHost = args[0];
        regPort = args[1];

        baseUrl = "http://"+regHost+":"+regPort+"/sd/resultadoset/";
        BufferedReader input = new BufferedReader(new InputStreamReader(System.in));

        try {
            showMenu();
            String request;

            if(!isIn){
                if(!signIn()){
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
                    signIn();
                }

                else if(request.equals("help") || request.equals("?")){
                    getHelp();
                }

                else if(request.equals("show ads")){
                    if(!isIn){if(!signIn()){continue;}}
                    int option = 1;

                    System.out.println("Deseja visualizar os inativos também? (Y/n)");
                    if(input.readLine().toLowerCase().equals("y")){
                        option = 2;
                    }

                    if(option == 1){
                        if(!isIn){if(!signIn()){continue;}}
                        showList(toStringList(getAds(new ArrayList<String>(), "admin/adSearch", true)), "Anúncios ativos:");
                    }
                    else{
                        showList(toStringList(getAds(new ArrayList<String>(), "admin/adSearch", false)), "Anúncios:");
                    }

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
                    String p3 = "", p4 = null, p5 = null;
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

                    showList(toStringList(getAds(list, "admin/adSearch", false)), "Resultados de Pesquisa:");
                }

                else if(request.equals("search by name")){
                    System.out.print("\t => Nome do anunciante: ");
                    String advertiser = input.readLine();

                    List<String> list = new ArrayList<>();
                    if(advertiser.length() > 0){
                        String adv = advertiser.replace(" ", "+");
                        list.add("anunciante=" + adv);
                    }
                    showList(toStringList(getAds(list, "adSearch", false)), "Anúncios de " + advertiser + ":");
                }

                else if(request.equals("search by id")){
                    System.out.print("\t => id: ");
                    String inId = input.readLine();
                    int id = 0;
                    List<String> list = new ArrayList<>();
                    if(inId.length() > 0){
                        //id = Integer.parseInt(inId);
                        list.add("aid=" + inId);
                    }
                    showList(toStringList(getAds(list, "adSearch", false)), "Anúncio " + inId + ":");
                }

                else if(request.equals("activate ad")){
                    System.out.print("\t => id: ");
                    String inId = input.readLine();
                    int id = 0;
                    if(inId.length() > 0){
                        id = Integer.parseInt(inId);
                    }

                    if(activateAd(id)){
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

                    if(deactivateAd(id)){
                        System.out.println("Estado alterado com sucesso\n");
                    }
                    else{
                        System.out.println("O anúncio desejado não se encontra disponível\n");
                    }
                }

                else if(request.equals("upgrade user")){
                    System.out.print("\t => username: ");
                    String toEvolve = input.readLine();
                    if(upgradeUser(toEvolve)){
                        System.out.println("\n" + toEvolve + " foi promovido a gestor\n");
                    }
                }

                else if(request.equals("check users")){
                    if(!isIn){if(!signIn()){continue;}}
                    showList(getUsers(new ArrayList<String>(), "users"), "Utilizadores:\n");
                }

                else if(request.equals("remove ad")){
                    System.out.print("\t => id: ");
                    String inId = input.readLine();
                    int idToRmv = 0;
                    if(inId.length() > 0) {
                        idToRmv = Integer.parseInt(inId);
                    }
                    if(removeAd(idToRmv)){
                        System.out.println("\nO anúncio " + idToRmv + " foi removido do sistema\n");
                    }
                    else{
                        System.out.println("\nNão foi possível remover o anúncio " + idToRmv);
                    }
                }

                else if(request.equals("remove user")){
                    System.out.print("\t => username: ");
                    String toDelete = input.readLine();
                    if(purgeUser(toDelete)){
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
        catch (Exception ex) {
            ex.printStackTrace();
        }

        input.close();
    }
}
