CREATE TABLE utente(
	username varchar(32) NOT NULL PRIMARY KEY,
	passw varchar(16) NOT NULL,
	email varchar(64) NOT NULL,
	partiteVinte integer DEFAULT 0,
	idStanza integer DEFAULT NULL
);

CREATE TABLE stanza(
	idStanza serial NOT NULL PRIMARY KEY,
	nomeStanza varchar(16) NOT NULL,
	numeroMax integer NOT NULL,
	privato bool DEFAULT 'false',
	keyword varchar(16) DEFAULT '',
	adminUsername varchar(32) NOT NULL
);

ALTER TABLE stanza ADD CONSTRAINT FK_Sadmin FOREIGN KEY (adminUsername) REFERENCES utente(username) ON DELETE CASCADE;
ALTER TABLE utente ADD CONSTRAINT FK_Ustanza FOREIGN KEY (idStanza) REFERENCES stanza(idStanza) ON DELETE SET NULL;

CREATE TABLE parola(
	word varchar(16) NOT NULL PRIMARY KEY
);
