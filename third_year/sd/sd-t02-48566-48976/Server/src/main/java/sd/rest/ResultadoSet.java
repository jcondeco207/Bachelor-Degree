package sd.rest;

import java.util.ArrayList;
import java.util.List;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlRootElement;


@XmlAccessorType(XmlAccessType.FIELD)
@XmlRootElement(name = "retultadoSet")
public class ResultadoSet {

    @XmlElement(required = true)
    protected List<Ad> resultados;

    public ResultadoSet() {
        resultados = new ArrayList<Ad>();
    }


    public List<Ad> getResultados() {
        return this.resultados;
    }


    protected void add( Ad a) {
        resultados.add( a );
    }

    protected int size() {
        return resultados.size();
    }

    public String toString() {
        return resultados.toString();
    }
}
