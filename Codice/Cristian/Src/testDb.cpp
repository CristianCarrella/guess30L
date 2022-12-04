#include "../Header/testDb.h"

void do_exit(PGconn *conn, PGresult *res) {
    
    fprintf(stderr, "%s\n", PQerrorMessage(conn));    

    PQclear(res);
    PQfinish(conn);    
    
}


void dbConnect(){
    PGconn *conn = PQconnectdb("host=host.docker.internal user=postgres dbname=postgres port=49153 password=postgrespw");

    if (PQstatus(conn) == CONNECTION_BAD) {
        
        fprintf(stderr, "Connection to database failed: %s\n",
            PQerrorMessage(conn));
            
        PQfinish(conn);
    }
	
    PGresult *res = PQexec(conn, "DROP TABLE IF EXISTS Cars");
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        do_exit(conn, res);
    }
    
    PQclear(res);
    
    res = PQexec(conn, "CREATE TABLE Cars(Id INTEGER PRIMARY KEY," \
        "Name VARCHAR(20), Price INT)");
        
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        do_exit(conn, res); 
    }
    
    PQclear(res);
    
    res = PQexec(conn, "INSERT INTO Cars VALUES(1,'Audi',52642)");
        
    if (PQresultStatus(res) != PGRES_COMMAND_OK) 
        do_exit(conn, res);     
    
    PQclear(res);    
    PQfinish(conn);

}

