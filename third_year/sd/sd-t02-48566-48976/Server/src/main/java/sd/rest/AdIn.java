package sd.rest;

public class AdIn {
    String location;
    double price;
    String gender;
    String date;
    String advertiser;
    String typology;
    String type;
    String details;

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

    public String getDetails() {
        return details;
    }

    public void setDetails(String details) {
        this.details = details;
    }

    public AdIn(){
        this.location = null;
        this.price = (0.0);
        this.gender = null;
        this.date = null;
        this.advertiser = null;
        this.typology = null;
        this.type = null;
        this.details = null;
    }

    public AdIn(String location, String price, String gender, String date, String advertiser, String typology, String type, String details) {
        this.location = location;
        this.price = Double.parseDouble(price);
        this.gender = gender;
        this.date = date;
        this.advertiser = advertiser;
        this.typology = typology;
        this.type = type;
        this.details = details;
    }
}
