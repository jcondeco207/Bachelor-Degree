package sd.rest;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlType;


@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "resultado", propOrder = {
        "username",
        "destiny",
        "message",
})
@XmlRootElement(name = "msg")

public class MsgOut {
    @XmlElement(required = true)
    String username;

    @XmlElement(required = true)
    String destiny;

    @XmlElement(required = true)
    String message;


    public MsgOut() {
        this.username = null;
        this.destiny = null;
        this.message = null;
    }

    public MsgOut(String username, String destiny, String message) {
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

