package com.example.guess30l.models;

public class Stanza {
    private int id;
    private int numeroMaxGiocatori;
    private int actualPlayersNumber;
    private String nomeStanza;

    public Stanza(int id,int numeroMaxGiocatori, int actualPlayersNumber, String nomeStanza){
        this.id = id;
        this.numeroMaxGiocatori = numeroMaxGiocatori;
        this.actualPlayersNumber = actualPlayersNumber;
        this.nomeStanza = nomeStanza;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getNomeStanza() {
        return nomeStanza;
    }

    public void setNomeStanza(String nomeStanza) {
        this.nomeStanza = nomeStanza;
    }

    public int getNumeroMaxGiocatori() {
        return numeroMaxGiocatori;
    }

    public void setNumeroMaxGiocatori(int numeroMaxGiocatori) {
        this.numeroMaxGiocatori = numeroMaxGiocatori;
    }

    public int getActualPlayersNumber() {
        return actualPlayersNumber;
    }

    public void setActualPlayersNumber(int actualPlayersNumber) {
        this.actualPlayersNumber = actualPlayersNumber;
    }

}
