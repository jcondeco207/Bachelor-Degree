package sd.rest;

public class User {
    String username;
    String password;
    String alias;
    String email;

    public User(){
        this.username = null;
        this.password = null;
        this.alias = null;
        this.email = null;
    }

    public User(String username, String password) {
        this.username = username;
        this.password = password;
    }

    public User(String username, String password, String alias, String email) {
        this.username = username;
        this.password = password;
        this.alias = alias;
        this.email = email;
    }


    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getAlias() { return alias; }

    public void setAlias(String alias) { this.alias = alias; }
}
