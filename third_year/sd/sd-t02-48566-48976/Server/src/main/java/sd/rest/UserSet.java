package sd.rest;

import java.util.ArrayList;
import java.util.List;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlRootElement;


@XmlAccessorType(XmlAccessType.FIELD)
@XmlRootElement(name = "userset")
public class UserSet {

    @XmlElement(required = true)
    protected List<String> resultados;

    public UserSet() {
        resultados = new ArrayList<String>();
    }


    public List<String> getResultados() {
        return this.resultados;
    }


    protected void add( String u ) {
        resultados.add( u );
    }

    protected int size() {
        return resultados.size();
    }

    public String toString() {
        return resultados.toString();
    }
}
