package work.rmi;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;
import java.util.List;


public class Impl extends UnicastRemoteObject implements Ads, java.io.Serializable {
    List<Ad> ads;
    PostgreInterface pgi;


    /**
     * Função responsável por verificar se um anúncio ativo existe
     *
     * @param id
     * @return
     * @throws RemoteException
     */
    boolean exists(int id) throws RemoteException {
        return searchBy("select * from ads where state=true and aid=" + id).size() > 0;
    }

    /**
     * Função responsável por verificar se um anúncio existe, independentemente do seu estado (ativo ou inativo)
     *
     * @param id
     * @return
     * @throws RemoteException
     */
    boolean existsAdmin(int id) throws RemoteException {
        return searchBy("select * from ads where aid=" + id).size() > 0;
    }

    /**
     * Função responsável por verificar se um username existe
     *
     * @param username
     * @return
     * @throws RemoteException
     */
    boolean existsUsername(String username) throws RemoteException {
        List<String> results = pgi.SearchUsers("select * from users where username='" + username + "'");
        return results.size() > 0;
    }

    public Impl(String address, String dbName, String username, String password) throws java.rmi.RemoteException {
        super();
        this.ads = new ArrayList<Ad>();
        this.pgi = new PostgreInterface("jdbc:postgresql://"+address+":5432/"+dbName+"", username, password);
    }

    /**
     * Função responsável pela criação de um anúncio
     *
     * @param  location
     * @param price
     * @param gender
     * @param date
     * @param advertiser
     * @param typology
     * @param type
     * @return
     * @throws java.rmi.RemoteException
     */
    public String newAd(String location, double price, String gender, String date, String advertiser, String typology, String type) throws java.rmi.RemoteException{
        System.out.println("[ ADIÇÃO DE ANÚNCIO ]");
        int id = this.pgi.getMaxID("select max(aid) as id from ads;") + 1;
        Ad ad = new Ad(location, price, gender, date, advertiser, typology, type, false, id);
        ads.add(ad);
        pgi.Insert("insert into ads values ('"+location+"' , "+price+", '"+gender+"', '"+date+"', '"+advertiser+"', '"+typology+"', '"+type+"', "+false+", "+id+");");
        return "Anúncio adicionado com sucesso com id = " + id;
    }

    /**
     * Função responsável por mostrar a lista de anúncios ativos
     *
     * @return
     * @throws java.rmi.RemoteException
     */
    public List<String> showActiveAds() throws java.rmi.RemoteException{
        System.out.println("[ PEDIDO DE ANÚNCIOS ATIVOS ]");

        List<Ad> results = pgi.Search("select * from ads where state=true");
        List<String> toSend = new ArrayList<>();
        for(Ad a : results){
            toSend.add(a.stringifinator());
        }
        return toSend;
    }

    /**
     * Função responsável por mostrar os anúncios ativos de acordo com os filtros inseridos pelo utilizador
     *
     * @return
     * @throws java.rmi.RemoteException
     */
    public List<String> showSearch(String type, double price, String gender, String location, boolean hasFilters) throws java.rmi.RemoteException{
        System.out.println("[ PEDIDO DE PESQUISA ]");
        String query = "select * from ads where state = true and type = '" + type + "'";
        if (hasFilters) {
            if(price != 0){
                query += " and price < " + price;
            }

            if(gender.length() > 0){
                query += " and gender = '" + gender + "'";
            }

            if(location.length() > 0){
                query += " and location = '" + location + "'";
            }
        }

        List<Ad> results = pgi.Search(query);
        List<String> toSend = new ArrayList<>();
        for(Ad a : results){
            toSend.add(a.stringifinator());
        }
        return toSend;
    }

    /**
     * Função resposnsável por mostrar anúncios de acordo com anunciante ou de acordo com o id do anúncio inserido pelo utilizador
     *
     * @param query
     * @return
     * @throws java.rmi.RemoteException
     */
    public List<String> searchBy(String query) throws java.rmi.RemoteException{
        System.out.println("[ PEDIDO DE PESQUISA ]");
        List<Ad> results = pgi.Search(query);
        List<String> toSend = new ArrayList<>();
        for(Ad a : results){
            toSend.add(a.stringifinator());
        }
        return toSend;
    }

    /**
     * Função responsável por enviar mensagens gerais de um anúncio
     *
     * @param msg
     * @param sender
     * @param aid
     * @return
     * @throws java.rmi.RemoteException
     */
    public String sendMessage(String msg, String sender, int aid) throws java.rmi.RemoteException{
        if(!exists(aid)){
            return "O anúncio pretendido não existe";
        }

        pgi.Insert("insert into messages values(" + aid + ", '" + sender + "', '" + msg + "')");
        pgi.Insert("insert into userMsg values('" + pgi.getUsername(aid) + "', '" + sender + "', '" + msg + "')");
        System.out.println("[ MENSAGEM PARA O ANÚNCI0 ENVIADA COM SUCESSO ]");
        return "Mensagem enviada com sucesso!";
    }

    /**
     * Função responsável por enviar mensagens para um utilizador
     *
     * @param msg
     * @param sender
     * @param username
     * @return
     * @throws java.rmi.RemoteException
     */
    public String sendUserMsg(String msg, String sender, String username) throws java.rmi.RemoteException{
        if(!existsUsername(username)){
            return "O utilizador pretendido não existe";
        }
        pgi.Insert("insert into userMsg values('" + username + "', '" + sender + "', '" + msg + "')");
        System.out.println("[ MENSAGEM PARA O USER ENVIADA COM SUCESSO ]");
        return "Mensagem enviada com sucesso!";
    }

    /**
     * Função responsável por mostrar as mensagens enviadas a um utilizador
     *
     * @param username
     * @return
     * @throws java.rmi.RemoteException
     */
    public List<String> showUserMsgs(String username) throws java.rmi.RemoteException{

        List<String> messages = pgi.searchMsg("select msg, sender from userMsg where username= '" + username + "'");
        System.out.println("[ LISTA DE MENSAGENS DE USER ]");
        return messages;
    }

    /**
     * Função responsável por mostrar todas as mensagens
     *
     * @param aid
     * @return
     * @throws java.rmi.RemoteException
     */
    public List<String> showAdMsgs(int aid) throws java.rmi.RemoteException{
        if(!exists(aid)){
            List <String> error = new ArrayList<String>();
            error.add("O anúncio pretendido não existe");
            return error;
        }

        List<String> messages = pgi.searchMsg("select msg,sender from messages where aid=" + aid);
        System.out.println("[ LISTA DE MENSAGENS DE ANÚNCIO ]");
        return messages;
    }

    /**
     * Função responsável por registar novos utilizadores
     *
     * @param username
     * @param password
     * @param alias
     * @return
     * @throws java.rmi.RemoteException
     */
    public Boolean signup(String username, String password, String alias) throws java.rmi.RemoteException{
        if(existsUsername(username)){
            return false;
        }
        pgi.Insert("insert into users values('" + username + "', MD5('" + password + "'), " + 0 + ", '" + alias + "')");
        System.out.println("[ SIGN UP "+username+" ]");
        return true;
    }

    /**
     * Função que verifica as credenciais do utilizador
     *
     * @param username
     * @param password
     * @return
     * @throws java.rmi.RemoteException
     */
    public Boolean signin(String username, String password) throws java.rmi.RemoteException{
        System.out.println("[ SIGN IN "+username+" ]");
        return pgi.checkUser(username, password);
    }

    /**
     * Função que verifica se o utilizador tem permissões de administrador
     *
     * @param username
     * @return
     * @throws java.rmi.RemoteException
     */
    public Boolean isSudo(String username) throws java.rmi.RemoteException{
        System.out.println("[ CHECK DE PERMISSÕES ]");
        return pgi.getPermission(username) == 1;
    }

    /**
     * Função responsável por mostrar todos os anúncios
     *
     * @return
     * @throws java.rmi.RemoteException
     */
    public List<String> showAllAds() throws java.rmi.RemoteException{
        List<Ad> results = pgi.Search("select * from ads order by state desc");
        List<String> toSend = new ArrayList<>();
        for(Ad a : results){
            toSend.add(a.stringifinator2());
        }

        System.out.println("[ PEDIDO DE TODOS OS ANÚNCIOS ]");
        return toSend;
    }

    /**
     * Função responsável por ativar anúncio
     *
     * @param aid
     * @return
     * @throws java.rmi.RemoteException
     */
    public Boolean activateAd(int aid) throws java.rmi.RemoteException {
        if(!existsAdmin(aid)){ return false; }
        pgi.changeState(true, aid);
        System.out.println("[ ANÚNCIO ATIVADO ]");
        return true;
    }

    /**
     * Função responsável por desativar um anúncio
     *
     * @param aid
     * @return
     * @throws java.rmi.RemoteException
     */
    public Boolean deactivateAd(int aid) throws java.rmi.RemoteException {
        if(!existsAdmin(aid)){ return false; }
        pgi.changeState(false, aid);
        System.out.println("[ ANÚNCIO DESATIVADO ]");
        return true;
    }

    /**
     * Função responsável por tornar um utilizador administrador
     *
     * @param username
     * @return
     * @throws java.rmi.RemoteException
     */
    public Boolean upgradeUser(String username) throws java.rmi.RemoteException{
        if(!existsUsername(username)){ return false; }
        pgi.evolve(username);
        System.out.println("[ USER PROMOVIDO ]");
        return true;
    }

    /**
     * Função responsável por mostrar todos os utilizadores registados
     *
     * @return
     * @throws java.rmi.RemoteException
     */
    public List<String> showUsers() throws java.rmi.RemoteException{
        List<String> results = pgi.SearchUsers("select username,alias from users");
        System.out.println("[ PEDIDO DE UTILIZADORES ATIVOS ]");
        return results;
    }

    /**
     * Função responsável por elmininar anúncio
     *
     * @param aid
     * @return
     * @throws java.rmi.RemoteException
     */
    public Boolean removeAd(int aid) throws java.rmi.RemoteException {
        if(!existsAdmin(aid)){ return false; }
        pgi.updateValues("delete from ads where aid= " + aid);
        System.out.println("[ ANÚNCIO ELIMINADO ]");
        return true;
    }

    /**
     * Função responsável por eliminar utilizador
     *
     * @param toDelete
     * @return
     * @throws java.rmi.RemoteException
     */
    public Boolean purgeUser(String toDelete) throws java.rmi.RemoteException {
        if(!existsUsername(toDelete) || isSudo(toDelete)){ return false; }
        pgi.updateValues("delete from users where username = '" + toDelete + "'");
        System.out.println("[ USER ELIMINADO ]");
        return true;
    }

    /**
     * Função que retorna o verdadeiro nome do utilizador com base no username
     *
     * @param username
     * @return
     * @throws java.rmi.RemoteException
     */
    public String getAlias(String username) throws java.rmi.RemoteException{
        System.out.println("[PEDIDO DE ALIAS]");
        if(!existsUsername(username)){
            return "Unknown";
        }
        return pgi.getAlias(username);
    }


}
