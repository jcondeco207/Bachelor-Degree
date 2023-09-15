package work.rmi;

import java.rmi.RemoteException;
import java.security.NoSuchAlgorithmException;
import java.util.List;

public interface Ads extends java.rmi.Remote {
    public String newAd(String location, double price, String gender, String date, String advertiser, String typology, String type) throws java.rmi.RemoteException;

    public List<String> showActiveAds() throws java.rmi.RemoteException;

    public List<String> showAllAds() throws java.rmi.RemoteException;

    public List<String> showSearch(String type, double price, String gender, String location, boolean hasFilters) throws java.rmi.RemoteException;

    public List<String> searchBy(String query) throws java.rmi.RemoteException;

    public String sendMessage(String msg, String sender, int aid) throws java.rmi.RemoteException;

    public List<String> showAdMsgs(int aid) throws java.rmi.RemoteException;

    public List<String> showUserMsgs(String username) throws java.rmi.RemoteException;

    public Boolean signup(String username, String password, String alias) throws java.rmi.RemoteException;

    public Boolean signin(String username, String password) throws java.rmi.RemoteException;

    public String sendUserMsg(String msg, String sender, String username) throws java.rmi.RemoteException;

    public Boolean isSudo(String username) throws java.rmi.RemoteException;

    public Boolean activateAd(int aid) throws java.rmi.RemoteException;

    public Boolean deactivateAd(int aid) throws java.rmi.RemoteException;

    public Boolean upgradeUser(String username) throws java.rmi.RemoteException;

    public List<String> showUsers() throws java.rmi.RemoteException;

    public Boolean purgeUser(String toDelete) throws java.rmi.RemoteException;

    public Boolean removeAd(int aid) throws java.rmi.RemoteException;

    public String getAlias(String username) throws java.rmi.RemoteException;

}
