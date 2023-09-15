package sd.rest;

import jakarta.ws.rs.*;
import org.glassfish.jersey.server.ResourceConfig;
import java.time.LocalDate;
import java.util.List;


@Path(value = "/resultadoset")
public class ResultadoSetResource {

    private static ResultadoSet resultadoSetProcura;
    private static ResultadoSet resultadoSetOferta;

    private static int maxID;

    private PostgreInterface pgi;

    public ResultadoSetResource() {
        maxID = 0;
        ResourceConfig rc = new ResourceConfig().packages("sd.rest"); // maybe apagar
        pgi = new PostgreInterface();
    }

    /**
     * Devolve os anúncios ativos de acordo com os dados de pesquisa inseridos pelo cliente
     *
     * @param gender
     * @param details
     * @param contact
     * @param advertiser
     * @param location
     * @param typology
     * @param price
     * @param type
     * @param aid
     * @return
     */
    @Path("/adSearch")
    @GET
    @Produces({"application/json", "application/xml"})
    public synchronized Message getAdSet(@QueryParam("genero") String gender,
                                         @QueryParam("detalhes") String details,
                                         @QueryParam("contacto") String contact,
                                         @QueryParam("anunciante") String advertiser,
                                         @QueryParam("zona") String location,
                                         @QueryParam("tipo_alojamento") String typology,
                                         @QueryParam("preco") int price,
                                         @QueryParam("tipo") String type,
                                         @QueryParam("aid") int aid    ) {

        System.out.println("[ ACTION ]: GET_AD\n");
        String query = "select * from ads where state=true";

        if(gender != null){ query += " and gender= '" + gender + "'";}
        if(contact != null){ query += " and contact= '" + contact + "'";}
        if(advertiser != null){ query += " and advertiser= '" + advertiser.replace("+", " ") + "'";}
        if(location != null){ query += " and location= '%" + location + "%'";}
        if(typology != null){ query += " and typology = '" + typology + "'";}
        if(price != 0){ query += " and price < " + price;}
        if(type != null){ query += " and type = '" + type + "'";}
        if(details != null){ query += " and description like '%" + details + "%'";}
        if(aid != 0){ query += " and aid = " + aid;}

        ResultadoSet searchRes = new ResultadoSet();
        searchRes.resultados = this.pgi.Search(query);
        //System.out.println(query);
        Message message = new Message("ok", searchRes);

        return message;
    }

    /**
     * Devolve os anúncios de acordo com os dados de pesquisa inseridos pelo admin
     *
     * @param gender
     * @param details
     * @param contact
     * @param advertiser
     * @param location
     * @param typology
     * @param price
     * @param type
     * @param aid
     * @param state
     * @return
     */
    @Path("/admin/adSearch")
    @GET
    @Produces({"application/json", "application/xml"})
    public synchronized Message getAllAdSet(     @QueryParam("genero") String gender,
                                                 @QueryParam("detalhes") String details,
                                                 @QueryParam("contacto") String contact,
                                                 @QueryParam("anunciante") String advertiser,
                                                 @QueryParam("zona") String location,
                                                 @QueryParam("tipo_alojamento") String typology,
                                                 @QueryParam("preco") int price,
                                                 @QueryParam("tipo") String type,
                                                 @QueryParam("aid") int aid,
                                                 @QueryParam("state") Boolean state) {

        System.out.println("[ ACTION ]: GET_AD_ADMIN\n");
        String query = "select * from ads";

        if(gender != null || contact != null || advertiser != null || location != null || typology != null || price != 0 || type != null || details != null || aid != 0 || state != null){
            query += " where description like '%%'";
        }

        if(gender != null){ query += " and gender= '" + gender + "'";}
        if(contact != null){ query += " and contact= '" + contact + "'";}
        if(advertiser != null){ query += " and advertiser= '" + advertiser.replace("+", " ") + "'";}
        if(location != null){ query += " and location= '%" + location + "%'";}
        if(typology != null){ query += " and typology = '" + typology + "'";}
        if(price != 0){ query += " and price < " + price;}
        if(type != null){ query += " and type = '" + type + "'";}
        if(details != null){ query += " and description like '%" + details + "%'";}
        if(aid != 0){ query += " and aid = " + aid;}
        if(state != null){ query += " and state = " + state;}

        ResultadoSet searchRes = new ResultadoSet();
        searchRes.resultados = this.pgi.Search(query);
        //System.out.println(query);
        Message message = new Message("ok", searchRes);

        return message;
    }

    /**
     * Devolve ao cliente a lista de utilizadores
     * @return
     */
    @Path("/users")
    @GET
    @Produces({"application/json", "application/xml"})
    public synchronized MessageWithStrings getUsers() {

        System.out.println("[ ACTION ]: GET_USERS\n");
        String query = "select username,alias from users";

        UserSet searchRes = new UserSet();
        searchRes.resultados = pgi.SearchUsers(query);
        //System.out.println(query);
        MessageWithStrings message = new MessageWithStrings("ok", searchRes);

        return message;
    }

    /* Sem a anotacao @Path, a escolha entre este metodo e o anterior faz-se pelo HTTP Method (GET/PUT)
     */
    @PUT
    @Consumes({"application/json", "application/xml"})
    public synchronized void putAdSet(ResultadoSet adSet) {
        this.resultadoSetProcura = resultadoSetProcura;
    }

    /**
     * Devolve o anúncio criado de acordo com os dados inseridos pelo cliente
     *
     * @param a
     * @return
     */
    @Path("/add")
    @POST
    @Consumes({"application/json", "application/xml"})
    @Produces({"application/json", "application/xml"})
    public synchronized Message addAd(AdIn a) throws Exception {

        System.out.println("[ ACTION ]: POST_AD\n");

        int id = this.pgi.getMaxID("select max(aid) as id from ads;") + 1;
        pgi.Insert("insert into ads values ('" + a.location + "' , " + a.price + ", '" + a.gender + "', '" + LocalDate.now().toString() + "', '" + a.advertiser + "', '" + a.typology + "', '" + a.type + "', " + false + ", " + id + ",'" + a.details + "');");

        ResultadoSet ok = new ResultadoSet();
        ok.resultados = searchBy("select * from ads where aid="+id);

        Message message = new Message("Anúncio inserido com sucesso", ok);
        AdPublisher.publish(a.advertiser + " publicou um novo anúncio com id " + id);
        return message;
    }

    /**
     * Efetua o login do utilizador
     *
     * @param u
     * @return
     */
    @Path("/login")
    @POST
    @Consumes({"application/json", "application/xml"})
    @Produces({"application/json", "application/xml"})
    public synchronized Message login(User u) {

        System.out.println("[ ACTION ]: POST_LOGIN\n");

        UserSet searchRes = new UserSet();
        Boolean check = pgi.checkUser(u.username, u.password);

        ResultadoSet ok = new ResultadoSet();
        Message message;
        if(check){
            message = new Message("OK", ok);
        }
        else {
            message = new Message("ERRO", ok);
        }

        return message;
    }

    /**
     * Efetua o login de um admin
     *
     * @param u
     * @return
     */
    @Path("/admin/login")
    @POST
    @Consumes({"application/json", "application/xml"})
    @Produces({"application/json", "application/xml"})
    public synchronized Message loginAdmin(User u) {

        System.out.println("[ ACTION ]: POST_LOGIN_ADMIN\n");
        System.out.println("Dados: " + u.username + " " + u.password);

        UserSet searchRes = new UserSet();
        Boolean check = pgi.checkUser(u.username, u.password) && (pgi.getPermission(u.username) == 1);

        ResultadoSet ok = new ResultadoSet();
        Message message;
        if(check){
            message = new Message("OK", ok);
        }
        else {
            message = new Message("ERRO", ok);
        }

        return message;
    }

    /**
     * Altera o estado de um anúncio
     *
     * @param r
     * @return
     */
    @Path("/admin/change_state")
    @POST
    @Consumes({"application/json", "application/xml"})
    @Produces({"application/json", "application/xml"})
    public synchronized Message changeState(Request r) {

        System.out.println("[ ACTION ]: POST_CHANGE_STATE\n");

        UserSet searchRes = new UserSet();
        Boolean check = false;
        ResultadoSet ok = new ResultadoSet();

        if(r.action.equals("apagar")){
            check = true;
            pgi.updateValues("delete from ads where aid= " + r.target);
            System.out.println("[ ANÚNCIO ELIMINADO ]");
        }
        else if (r.action.equals("ativar")) {
            check = true;
            pgi.changeState(true, Integer.parseInt(r.target));
            System.out.println("[ ANÚNCIO ATIVADO ]");
        }
        else if (r.action.equals("desativar")) {
            check = true;
            pgi.changeState(false, Integer.parseInt(r.target));
            System.out.println("[ ANÚNCIO DESATIVADO ]");
        }
        else if(r.action.equals("upgrade")){
            check = true;
            pgi.evolve(r.target);
            System.out.println("[ USER PROMOVIDO ]");
        }
        else if(r.action.equals("purge")){
            check = true;
            pgi.updateValues("delete from users where username = '" + r.target + "'");
            System.out.println("[ USER ELIMINADO ]");
        }

        Message message;
        if(check){
            message = new Message("OK", ok);
        }
        else {
            message = new Message("ERRO", ok);
        }

        return message;
    }

    /**
     * Regista um novo utilizador
     *
     * @param u
     * @return
     */
    @Path("/register")
    @POST
    @Consumes({"application/json", "application/xml"})
    @Produces({"application/json", "application/xml"})
    public synchronized Message signup(User u) {

        System.out.println("[ ACTION ]: POST_SIGNUP\n");

        UserSet searchRes = new UserSet();
        pgi.Insert("insert into users values('" + u.username + "', MD5('" + u.password + "'), " + 0 + ", '" + u.alias + "', '" + u.email + "')");
        System.out.println("[ SIGN UP "+u.username+" ]");

        ResultadoSet ok = new ResultadoSet();
        Message message = new Message("OK", ok);

        return message;
    }

    /**
     * Devolve o nome de um utilizador
     *
     * @param u
     * @return
     */
    @Path("/alias")
    @POST
    @Consumes({"application/json", "application/xml"})
    @Produces({"application/json", "application/xml"})
    public synchronized Message getAlias(User u) {

        System.out.println("[ ACTION ]: POST_ALIAS\n");
        UserSet searchRes = new UserSet();
        String alias;

        if(!existsUsername(u.getUsername())){
            alias = "Unknown";
        }
        else{
            alias = pgi.getAlias(u.getUsername());
        }

        ResultadoSet ok = new ResultadoSet();
        Message message = new Message(alias, ok);

        return message;
    }

    /**
     * Envia uma mensagem para um utilizador
     *
     * @param m
     * @return
     */
    @Path("/send_msg/user")
    @POST
    @Consumes({"application/json", "application/xml"})
    @Produces({"application/json", "application/xml"})
    public synchronized Message sendMsg(SentMessage m) {

        System.out.println("[ ACTION ]: POST_MSG\n");
        Boolean check = true;

        if(!existsUsername(m.destiny)){
            check = false;
        }
        else{
            pgi.Insert("insert into userMsg values('" + m.destiny + "', '" + m.username + "', '" + m.message + "')");
            check = true;
        }

        ResultadoSet ok = new ResultadoSet();
        Message message;
        if(check){
            message = new Message("Mensagem entregue", ok);
        }
        else {
            message = new Message("Mensagem não enviada", ok);
        }

        return message;
    }


    /**
     * Envia uma mensagem para um anúncio
     *
     * @param m
     * @return
     */
    @Path("/send_msg/ad")
    @POST
    @Consumes({"application/json", "application/xml"})
    @Produces({"application/json", "application/xml"})
    public synchronized Message sendMsgAd(SentMessage m) throws Exception {

        System.out.println("[ ACTION ]: POST_MSG_AD\n");
        Boolean check = true;

        if(!exists(Integer.parseInt(m.destiny))){
            check = false;
        }
        else{
            pgi.Insert("insert into messages values(" + m.destiny + ", '" + m.username + "', '" + m.message + "')");
            pgi.Insert("insert into userMsg values('" + pgi.getUsername(Integer.parseInt(m.destiny)) + "', '" + m.username + "', '" + m.message + "')");
            check = true;
        }

        ResultadoSet ok = new ResultadoSet();
        Message message;
        if(check){
            message = new Message("Mensagem entregue", ok);
            AdPublisher.publish(m.username + " enviou uma mensagem para o anúncio " + m.getDestiny());
        }
        else {
            message = new Message("Mensagem não enviada", ok);
        }

        return message;
    }

    /**
     * Devolve ao cliente o conjunto de mensagens relativas a um anúncio/utilizador
     *
     * @param m
     * @return
     */
    @Path("/check_msg")
    @POST
    @Consumes({"application/json", "application/xml"})
    @Produces({"application/json", "application/xml"})
    public synchronized MessageWithStrings getMsg(SentMessage m) {

        System.out.println("[ ACTION ]: CHECK_MSG\n");
        MessageWithStrings message;

        if(m.message.equals("ads") && exists(Integer.parseInt(m.destiny))) {
            UserSet searchRes = new UserSet();
            searchRes.resultados = pgi.searchMsg("select msg,sender from messages where aid=" + m.destiny);
            System.out.println("[ LISTA DE MENSAGENS DE ANÚNCIO ]");
            message = new MessageWithStrings("OK", searchRes);
        }
        else if(m.message.equals("user")){
            UserSet searchRes = new UserSet();
            searchRes.resultados = pgi.searchMsg("select msg, sender from userMsg where username= '" + m.username + "'");
            System.out.println("[ LISTA DE MENSAGENS DE USER ]");
            message = new MessageWithStrings("OK", searchRes);
        }
        else{
            message = new MessageWithStrings("ERRO", null);
        }

        return message;
    }

    /**
     * Verifica se existe o utilizador 'username'
     *
     * @param username
     * @return
     */
    boolean existsUsername(String username){
        List<String> results = pgi.SearchUsers("select * from users where username='" + username + "'");
        return results.size() > 0;
    }

    /**
     * Verifica se o anúncio com o id 'id' existe
     *
     * @param id
     * @return
     */
    boolean exists(int id)  {
        return searchBy("select * from ads where state=true and aid=" + id).size() > 0;
    }

    /**
     * Devolve uma lista de anúncios resultante da query
     *
     * @param query
     * @return
     */
    public List<Ad> searchBy(String query) {
        List<Ad> results = pgi.Search(query);
        return results;
    }
}

