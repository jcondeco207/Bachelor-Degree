package sd.rest;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;

public class PropertiesHandler {
    public static String getValue(String key){
        try(InputStream in = new FileInputStream("src/main/resources/database.properties")){
            Properties p = new Properties();
            p.load(in);
            return p.getProperty(key);
        } catch (IOException e) {
            System.out.println("Ficheiro de propriedades não disponivel");
            throw new RuntimeException(e);
        }
    }
}
