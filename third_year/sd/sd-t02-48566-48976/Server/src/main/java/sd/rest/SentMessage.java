package sd.rest;

public class SentMessage {
    String username;
    String destiny;
    String message;


    public SentMessage() {}

    public SentMessage(String username, String destiny, String message) {
        this.username = username;
        this.destiny = destiny;
        this.message = message;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getDestiny() {
        return destiny;
    }

    public void setDestiny(String destiny) {
        this.destiny = destiny;
    }

    public String getMessage() {
        return message;
    }

    public void setMessage(String message) {
        this.message = message;
    }
}

