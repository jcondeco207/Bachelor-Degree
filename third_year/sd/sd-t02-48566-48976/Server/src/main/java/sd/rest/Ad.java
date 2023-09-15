package sd.rest;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlType;



@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "resultado", propOrder = {
        "data",
        "genero",
        "detalhes",
        "contacto",
        "anunciante",
        "zona",
        "tipo_alojamento",
        "preco",
        "aid",
        "contact",
        "details"
})
@XmlRootElement(name = "ad")

public class Ad {

    @XmlElement(required = true)
    String location;

    @XmlElement(required = true)
    double price;

    @XmlElement(required = true)
    String gender;

    @XmlElement(required = true)
    String date;

    @XmlElement(required = true)
    String advertiser;

    @XmlElement(required = true)
    String typology;

    @XmlElement(required = true)
    String type;

    @XmlElement(required = true)
    Boolean state;

    @XmlElement(required = true)
    int aid;

    @XmlElement(required = true)
    String contact;

    @XmlElement(required = true)
    String details;

    public Ad(){
        this.location = null;
        this.price = 0;
        this.gender = null;
        this.date = null;
        this.advertiser = null;
        this.typology = null;
        this.type = null;
        this.state = false;
        this.aid = 0;
        this.contact = null;
        this.details = null;
    }
    public Ad(String location, double price, String gender, String date, String advertiser, String typology, String type, Boolean state, int aid, String details) {
        this.location = location;
        this.price = price;
        this.gender = gender;
        this.date = date;
        this.advertiser = advertiser;
        this.typology = typology;
        this.type = type;
        this.state = false;
        this.aid = aid;
        this.contact = contact;
        this.details = details;
    }

    public String getLocation() {
        return location;
    }

    public void setLocation(String location) {
        this.location = location;
    }

    public double getPrice() {
        return price;
    }

    public void setPrice(double price) {
        this.price = price;
    }

    public String getGender() {
        return gender;
    }

    public void setGender(String gender) {
        this.gender = gender;
    }

    public String getDate() {
        return date;
    }

    public void setDate(String date) {
        this.date = date;
    }

    public String getAdvertiser() {
        return advertiser;
    }

    public void setAdvertiser(String advertiser) {
        this.advertiser = advertiser;
    }

    public String getTypology() {
        return typology;
    }

    public void setTypology(String typology) {
        this.typology = typology;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public Boolean getState() {
        return state;
    }

    public void setState(Boolean state) {
        this.state = state;
    }

    public int getAid() {
        return aid;
    }

    public void setAid(int aid) {
        this.aid = aid;
    }

    public String getContact() {return contact;}

    public void setContact(String contact) {this.contact = contact;}

    public String getDetails() {return details;}

    public void setDetails(String details) {this.details = details;}

    public String stringifinator(){
        return "Ad > " + this.getAid() + " | " + this.getType() + " | " + this.getLocation() + " | " + this.getPrice() + " | " + this.getGender() + " | " + this.getDate() + " | " + this.getAdvertiser() + " | " + this.getTypology() + " | " + this.getContact();
    }

    public String stringifinator2(){
        String s = "Inativo";
        if(this.getState()){s="Ativo";}
        return "Ad > " + this.getAid() + " | " + this.getType() + " | " + this.getLocation() + " | " + this.getPrice() + " | " + this.getGender() + " | " + this.getDate() + " | " + this.getAdvertiser() + " | " + this.getTypology() + " | " + this.getContact() + " | ESTADO: " + s;
    }

}
