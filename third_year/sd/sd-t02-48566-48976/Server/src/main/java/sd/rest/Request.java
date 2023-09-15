package sd.rest;

public class Request {
    Boolean new_change;
    String target;
    String action;

    public Request() {
    }

    public Request(Boolean new_change, String target, String action) {
        this.new_change = new_change;
        this.target = target;
        this.action = action;
    }

    public Boolean getNew_change() {
        return new_change;
    }

    public void setNew_change(Boolean new_change) {
        this.new_change = new_change;
    }

    public String getTarget() {
        return target;
    }

    public void setTarget(String target) {
        this.target = target;
    }

    public String getAction() {
        return action;
    }

    public void setAction(String action) {
        this.action = action;
    }
}
