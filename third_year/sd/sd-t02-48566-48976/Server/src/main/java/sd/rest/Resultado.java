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
        "aid"
})
@XmlRootElement(name = "resultado")
public class Resultado {

    @XmlElement(required = true)
    protected String data;

    @XmlElement(required = true)
    protected String genero;

    @XmlElement(required = true)
    protected String detalhes;

    @XmlElement(required = true)
    protected String contacto;

    @XmlElement(required = true)
    protected String anunciante;


    @XmlElement(required = true)
    protected String zona;

    @XmlElement(required = true)
    protected String tipo_alojamento;

    @XmlElement(required = true)
    protected String estado;

    @XmlElement(required = true)
    protected int preco;

    @XmlElement(required = true)
    protected int aid;

    @XmlElement(required = true)
    protected String tipo;

    public Resultado() {
    }

    public Resultado(String data, String genero, String detalhes, String contacto, String anunciante, String zona, String tipo_alojamento, int preco, String tipo){
        this.data = data;
        this.genero = genero;
        this.detalhes = detalhes;
        this.contacto = contacto;
        this.anunciante = anunciante;
        this.zona = zona;
        this.tipo_alojamento = tipo_alojamento;
        this.preco = preco;
        this.estado = "inativo";
        this.tipo = tipo;
        this.aid = 0;
    }


    public String getData() {
        return data;
    }

    public String getGenero() {
        return genero;
    }

    public String getDetalhes() {
        return detalhes;
    }

    public String getContacto() {
        return contacto;
    }

    public String getAnunciante() {
        return anunciante;
    }

    public String getZona() {
        return zona;
    }

    public String getTipo_alojamento() {
        return tipo_alojamento;
    }

    public int getPreco() {
        return preco;
    }

    public String getEstado() {
        return estado;
    }

    public int getAid() {
        return aid;
    }

    public void setData(String data) {
        this.data = data;
    }

    public void setGenero(String genero) {
        this.genero = genero;
    }

    public void setDetalhes(String detalhes) {
        this.detalhes = detalhes;
    }

    public void setContacto(String contacto) {
        this.contacto = contacto;
    }

    public void setAnunciante(String anunciante) {
        this.anunciante = anunciante;
    }

    public void setZona(String zona) {
        this.zona = zona;
    }

    public void setTipo_alojamento(String tipo_alojamento) {
        this.tipo_alojamento = tipo_alojamento;
    }

    public void setPreco(int preco) {
        this.preco = preco;
    }

    public void setEstado(String estado) {
        this.estado = estado;
    }

    public void setAid(int aid) {
        this.aid = aid;
    }
}
