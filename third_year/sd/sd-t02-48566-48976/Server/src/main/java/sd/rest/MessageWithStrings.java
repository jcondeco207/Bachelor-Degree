package sd.rest;

import javax.xml.bind.annotation.*;
import java.util.ArrayList;


@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "resultados", propOrder = {
        "resultado",
        "resultados"
})
@XmlRootElement(name = "message")

public class MessageWithStrings {
    String resultado;
    ArrayList<String> resultados;

    MessageWithStrings(String check, UserSet adSet){
        this.resultado = check;
        this.resultados = (ArrayList<String>) adSet.getResultados();
    }

    public String getResultado() {
        return resultado;
    }

    public ArrayList<String> getResultados() {return resultados;}
}
