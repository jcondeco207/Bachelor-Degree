package sd.rest;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class PostgreInterface {
    private Connection c = null;

    PostgreInterface(){
        try {
            String db = "jdbc:postgresql://"+PropertiesHandler.getValue("address")+":5432/"+PropertiesHandler.getValue("dbName");
            String username = PropertiesHandler.getValue("username");
            String password = PropertiesHandler.getValue("password");
            this.c = DriverManager.getConnection(db, username, password);
            System.out.println("\n[ CONNECTED WITH THE DATABASE ]");
            this.c.setAutoCommit(false);
        }
        catch (SQLException e) {
            System.out.println("\nCannot connect with the database.");
            e.printStackTrace();
        }
    }

    void Insert(String query){
        try{
            Statement q = this.c.createStatement();
            q.executeUpdate(query);
            q.close();
            this.c.commit();
            System.out.println("Data inserted successfully.");
        }
        catch (Exception e){
            System.out.println("Insert failed");
        }
    }

    List<String>SearchUsers(String query){
        List<String> registry = new ArrayList<String>();
        try{
            Statement q = this.c.createStatement();
            ResultSet results = q.executeQuery(query);
            this.c.commit();

            while(results.next()){
                String username = results.getString("username").strip();
                String alias = results.getString("alias").strip();

                String r = username +  " a.k.a.: " + alias;
                registry.add(r);
            }

            q.close();
        }
        catch (Exception e){
            System.out.println("Search failed");
            e.printStackTrace();
        }
        return registry;
    }

    List<Ad>Search(String query){
        List<Ad> registry = new ArrayList<Ad>();
        try{
            Statement q = this.c.createStatement();
            ResultSet results = q.executeQuery(query);
            this.c.commit();

            while(results.next()){
                String location = results.getString("location").strip();
                int price = results.getInt("price");
                String gender = results.getString("gender").strip();
                String date = results.getString("date").strip();
                String advertiser = results.getString("advertiser").strip();
                String typology = results.getString("typology").strip();
                String type = results.getString("type").strip();
                Boolean state = results.getBoolean("state");
                int aid = results.getInt("aid");
                String details = results.getString("description").strip();

                Ad r = new Ad(location, price, gender, date, advertiser, typology, type, state, aid, details);
                r.setState(state);
                registry.add(r);
            }

            q.close();
        }
        catch (Exception e){
            System.out.println("Search failed");
            e.printStackTrace();
        }

        return registry;
    }

    List<String>searchMsg(String query){
        List<String> registry = new ArrayList<String>();
        try{
            Statement q = this.c.createStatement();
            ResultSet results = q.executeQuery(query);
            this.c.commit();

            while(results.next()){
                String msg = results.getString("msg").strip();;
                String sender = results.getString("sender").strip();;
                registry.add(msg + " \n- " + sender);
            }

            q.close();
        }
        catch (Exception e){
            System.out.println("Search failed");
            e.printStackTrace();
        }

        return registry;
    }

    String getUsername(int id){
        List<String> registry = new ArrayList<String>();
        try{
            Statement q = this.c.createStatement();
            ResultSet results = q.executeQuery("select username from users where alias = (select advertiser from ads where aid = " + id + ")");
            this.c.commit();

            while(results.next()){
                String username = results.getString("username").strip();;
                registry.add(username);
            }

            q.close();
        }
        catch (Exception e){
            System.out.println("Search failed");
            e.printStackTrace();
        }

        return registry.get(0);
    }

    String getAlias(String username){
        List<String> registry = new ArrayList<String>();
        try{
            Statement q = this.c.createStatement();
            ResultSet results = q.executeQuery("select alias from users where username = '"+username+"'");
            this.c.commit();

            while(results.next()){
                String alias = results.getString("alias").strip();;
                registry.add(alias);
            }
            q.close();
        }
        catch (Exception e){
            System.out.println("Search failed");
            e.printStackTrace();
        }
        return registry.get(0);
    }

    Boolean checkUser(String username, String password){
        List<String> registry = new ArrayList<String>();
        boolean exists = false;
        try{
            Statement q = this.c.createStatement();
            ResultSet results = q.executeQuery("select * from users where username='" + username + "' and password = MD5('" + password  + "')");
            this.c.commit();
            while(results.next()){
                exists = true;
                break;
            }
            return exists;
        }
        catch (Exception e){
            System.out.println("Search failed");
            e.printStackTrace();
        }
        return false;
    }

    void updateValues(String query){
        try{
            Statement q = this.c.createStatement();
            q.executeUpdate(query);
            this.c.commit();
            q.close();
            System.out.println("Values updated");
        }
        catch (Exception e){
            System.out.println("Update failed");
            e.printStackTrace();
        }
    }

    void closeConnection(){
        try{
            if(!this.c.isClosed()){
                this.c.close();
                System.out.println("Connection with the database closed.");
            }
            else{
                System.out.println("Connection already closed.");
            }
        }
        catch (Exception e){
            System.out.println("Closing connection failed.");
        }
    }

    int getMaxID(String query){
        List<Integer> ids = new ArrayList<Integer>();
        try{
            Statement q = this.c.createStatement();
            ResultSet results = q.executeQuery(query);
            this.c.commit();

            while(results.next()){
                int aid = Integer.parseInt(results.getString("id"));
                ids.add(aid);
            }

            q.close();
        }
        catch (Exception e){
            System.out.println("Search failed");
            e.printStackTrace();
            return -1;
        }

        return ids.get(0);
    }

    int getPermission(String username){
        try{
            Statement q = this.c.createStatement();
            ResultSet results = q.executeQuery("select type from users where username = '" + username + "'");
            this.c.commit();

            results.next();
            return Integer.parseInt(results.getString("type"));
        }
        catch (Exception e){
            System.out.println("Search failed");
            e.printStackTrace();
            return -1;
        }
    }

    void changeState(Boolean newState, int aid){
        updateValues("update ads set  state ="+ newState +" where aid =" + aid);
    }

    void evolve(String username){
        updateValues("update users set  type ="+ 1 +" where username ='" + username + "'");
    }
}
