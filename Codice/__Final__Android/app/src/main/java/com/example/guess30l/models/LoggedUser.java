package com.example.guess30l.models;

public class LoggedUser {
    String email, username;
    Integer idStanza, imgId, partiteVinte;
    Boolean adminStanza = false;

    public LoggedUser(String email, Integer idStanza, Integer imgId, Integer partiteVinte, String username){
        this.email = email;
        this.idStanza = idStanza;
        this.imgId = imgId;
        this.partiteVinte = partiteVinte;
        this.username = username;
    }

    public String getUsername() {
        return username;
    }
    public String getEmail() {
        return email;
    }
    public Integer getPartiteVinte() {
        return partiteVinte;
    }

    public void setAdminStanza(Boolean adminStanza) {
        this.adminStanza = adminStanza;
    }

    public Boolean isAdminStanza() {
        return adminStanza;
    }
}
