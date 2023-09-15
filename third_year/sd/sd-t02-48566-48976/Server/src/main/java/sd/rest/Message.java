package sd.rest;

import javax.xml.bind.annotation.*;
import java.util.ArrayList;


@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "resultados", propOrder = {
        "resultado",
        "resultados"
})
@XmlRootElement(name = "message")

public class Message {
    String resultado;
    ArrayList<Ad> resultados;

    Message(String check, ResultadoSet adSet){
        this.resultado = check;
        this.resultados = (ArrayList<Ad>) adSet.getResultados();
    }

    public String getResultado() {
        return resultado;
    }

    public ArrayList<Ad> getResultados() {return resultados;}
}
