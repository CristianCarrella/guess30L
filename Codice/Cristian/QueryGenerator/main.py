import requests
import random

usrs = []
stanze = []
s = 0
NUM_OF_STANZE_AND_STARTING_USR = 20


# prima 20 utenti, poi le stanze e poi gli altri utenti

def generateUser(flag):
    global stanze, usrs, s, NUM_OF_STANZE_AND_STARTING_USR
    generated = False
    while not generated:
        response = requests.get("https://randomuser.me/api/")
        js = response.json()
        username = js['results'][0]['login']['username']
        password = js['results'][0]['login']['password']
        email = js['results'][0]['email']
        partiteVinte = random.randint(1, 50)
        usr = Utente(username, password, email, partiteVinte)
        if not usr in usrs:
            usrs.append(usr)
            generated = True

    if flag == 1:
        query = "INSERT INTO utente(username, passw, email, partiteVinte, idStanza) VALUES ('" + username + "', '" + password + "', '" + email + "', " + str(
            partiteVinte) + ", default);"
        print(query)
    else:
        if stanze[s].getNumeroMassimo() != 0:
            query = "INSERT INTO utente(username, passw, email, partiteVinte, idStanza) VALUES ('" + username + "', '" + password + "', '" + email + "', " + str(
                partiteVinte) + ", " + str(stanze[s].getId()) + ");"
            stanze[s].reduceNumeroMassimo()
            print(query)
        else:
            s = random.randint(0, NUM_OF_STANZE_AND_STARTING_USR)


class Utente:
    username = ""
    password = ""
    email = ""
    partiteV = 0

    def __init__(self, username, password, email, partiteV):
        self.username = username
        self.password = password
        self.email = email
        self.partiteV = partiteV

    def getUsername(self):
        return self.username


class Stanza:
    nomeStanza = ""
    password = ""
    admin = ""
    numeroMassimo = 0
    privato = ""
    id = 0

    def __init__(self, nomeStanza, password, admin, numeroMassimo, privato, id):
        self.nomeStanza = nomeStanza
        self.password = password
        self.admin = admin
        self.numeroMassimo = numeroMassimo
        self.privato = privato
        self.id = id

    def getNomeStanza(self):
        return self.nomeStanza

    def getPassword(self):
        return self.password

    def getAdmin(self):
        return self.admin

    def getNumeroMassimo(self):
        return self.numeroMassimo

    def reduceNumeroMassimo(self):
        self.numeroMassimo = self.numeroMassimo - 1

    def getPrivato(self):
        return self.privato

    def getId(self):
        return self.id


def main():
    global stanze, usrs, NUM_OF_STANZE_AND_STARTING_USR
    i = 0
    for j in range(NUM_OF_STANZE_AND_STARTING_USR):
        generateUser(1)

    for x in range(NUM_OF_STANZE_AND_STARTING_USR):
        response2 = requests.get("https://random-word-api.herokuapp.com/word")
        js2 = response2.json()
        nomeStanza = js2[0]
        numeroMassimo = random.randint(2, 8)
        if random.randint(0, 1) == 0:
            privato = "false"
        else:
            privato = "true"

        stanza = Stanza(nomeStanza, "password" + str(i), usrs[i].getUsername(), numeroMassimo, privato, i)
        stanze.append(stanza)
        query = "INSERT INTO stanza(idStanza, nomeStanza, numeroMax, privato, keyword, adminUsername) VALUES (default, '" + nomeStanza + "', '" + str(
            numeroMassimo) + "', " + privato + ", '" + "password" + str(i) + "', '" + usrs[i].getUsername() + "');"
        i = i + 1
        print(query)
    usrs.clear()
    print("\nEsegui dopo aver eseguito le query precedenti")
    
    for j in range(80):
        generateUser(2)


if __name__ == "__main__":
    main()
