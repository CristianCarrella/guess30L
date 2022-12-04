#include "../Header/testDb.h"

void endConnection(PGconn *conn){
	PQfinish(conn);
}

//ritorna vero se esiste nel db sennò falso
bool loginQuery(PGconn *conn, char username[32], char password[16]){
	
	char queryString[512] = "SELECT * FROM utente WHERE username = '";
	strcat(queryString, username);
	strcat(queryString, "' AND passw = '");
	strcat(queryString, password);
	strcat(queryString, "'");
	
	printf("\nQUERY: %s ", queryString);
	
	PGresult * res = PQexec(conn, queryString);
    
    if (PQresultStatus(res) != PGRES_TUPLES_OK){
		printf("NON nel db\n");
	}
	else{
		printf("Presente nel db\n"); 
		int rows = PQntuples(res);
    	/* Se si vogliono visualizzare le informazioni di un utente
	    for(int i=0; i<rows; i++) {
	    	//stampa username, password, email, partitevinte, idstanza
	        printf("%s %s %s %s %s\n", PQgetvalue(res, i, 0), PQgetvalue(res, i, 1), PQgetvalue(res, i, 2), PQgetvalue(res, i, 3), PQgetvalue(res, i, 4));
	    } 
		*/     
		if(rows > 0){
			return true;
		}
		return false;
	}
	PQclear(res);
    return false;   
}
