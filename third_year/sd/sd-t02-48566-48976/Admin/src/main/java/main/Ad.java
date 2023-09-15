package main;

public class Ad {
    String location;
    double price;
    String gender;
    String date;
    String advertiser;
    String typology;
    String type;
    Boolean state;

    String details;
    int aid;


    public Ad(String location, double price, String gender, String date, String advertiser, String typology, String type, Boolean state, int aid, String details) {
        this.location = location;
        this.price = price;
        this.gender = gender;
        this.date = date;
        this.advertiser = advertiser;
        this.typology = typology;
        this.type = type;
        this.state = state;
        this.aid = aid;
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

    public String getDetails() { return details; }

    public void setDetails(String details) { this.details = details; }

    public String stringifinator(){
        return "Ad > " + this.getAid() + " | " + this.getType() + " | " + this.getLocation() + " | " + this.getPrice() + " | " + this.getGender() + " | " + this.getDate() + " | " + this.getAdvertiser() + " | " + this.getTypology() + "\nDescrição: " + this.getDetails() + "\n";
    }

    public String stringifinator2(){
        String s = "Inativo";
        if(this.getState()){s="Ativo";}
        return "Ad > " + this.getAid() + " | " + this.getType() + " | " + this.getLocation() + " | " + this.getPrice() + " | " + this.getGender() + " | " + this.getDate() + " | " + this.getAdvertiser() + " | " + this.getTypology() + " | ESTADO: " + s + "\nDescrição: " + this.getDetails() + "\n";
    }
}
