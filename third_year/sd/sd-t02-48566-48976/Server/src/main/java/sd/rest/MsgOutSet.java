package sd.rest;

import java.util.ArrayList;
import java.util.List;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlRootElement;


@XmlAccessorType(XmlAccessType.FIELD)
@XmlRootElement(name = "retultadoSet")
public class MsgOutSet {

    @XmlElement(required = true)
    protected List<MsgOut> resultados;

    public MsgOutSet() {
        resultados = new ArrayList<MsgOut>();
    }


    public List<MsgOut> getResultados() {
        return this.resultados;
    }


    protected void add( MsgOut a) {
        resultados.add( a );
    }

    protected int size() {
        return resultados.size();
    }

    public String toString() {
        return resultados.toString();
    }
}
