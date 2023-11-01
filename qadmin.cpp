
#include <string>
#include <iostream>
#include "libpq-fe.h"

int add(int argc, char **argv)
{

    /*
    CREATE A QUERY VARIABLE
    query = "SELECT * FROM..."
    then pass that to PQexec(conn, query) <- make sure its char array type with strCopy()
*/

    /*
        Separate queries
        
        BEGIN

        SELECT * FROM ...
        WHERE ...
        FOR UPDATE

        UPDATE ... WHERE ...

        COMMIT
    
    
    */
    if (argc < 3) {
        std::cout << "Usage: qadmin add user <first name> <last name> <email> <department> <optional list of group names" << std::endl;
        std::cout << "Usage: qadmin add group <group name> <department name>" << std::endl;
        std::cout << "Usage: qadmin add department <department name> <department head> <department building>" << std::endl;
        return 1;
    }

    std::string subcommand = argv[2];

    if (subcommand == "user") {
        for (int i = 3; i < argc; i++) {
            // qadmin add user <first name> <last name> <email> <department> <optional list of group names>
            // Q: do stuff to add argv[i] to database somehow
        }
    }
    else if (subcommand == "group") {
        for (int i = 3; i < argc; i++) {
            // qadmin add group <group name> <department name>
            // Q: do stuff to add argv[i] to database somehow
        }
    }
    else if (subcommand == "department") {
        for (int i = 3; i < argc; i++) {
            // qadmin add department <department name> <department head> <department building>
            // Q: do stuff to add argv[i] to database somehow
        }
    }
    else {
        std::cout << "Incorrect input. Check command syntax." << std::endl;
        return 1;
    }

    return 0;
}

int list(int argc, char **argv)
{
    if (argc < 3) {
        std::cout << "Usage: qadmin list <user|group|department>" << std::endl;
        return 1;
    }

    std::string subcommand = argv[2];

    if (subcommand == "user") {
        for (int i = 3; i < argc; i++) {
            // Q: cout << do stuff to print all users
        }
    }
    else if (subcommand == "department") {
        for (int i = 3; i < argc; i++) {
            // Q: cout << do stuff to print all departments
        }
    }
    else if (subcommand == "group") {
        for (int i = 3; i < argc; i++) {
            // Q: cout << do stuff to print all groups
        }
    }
    else {
        std::cout << "Incorrect input. Check command syntax." << std::endl;
        return 1;
    }

    return 0;
}

int remove(int argc, char **argv)
{
    if (argc < 3) {
        std::cout << "Usage: qadmin remove <user|group|department> <name>" << std::endl;
        return 1;
    }

    std::string removeType = argv[2];

    if (removeType == "user") {
        // qadmin remove user <first name> <last name>
        // Q: replace data with a "deleted_at" timestamp for soft delete
        
        std::string userName = argv[3];
    }
    else if (removeType == "group") {
        // qadmin remove group <group name>
        // Q: replace data with a "deleted_at" timestamp for soft delete
        
        std::string groupName = argv[3];
    }
    else if (removeType == "department") {
        // qadmin remove department <department name>
        // Q: replace data with a "deleted_at" timestamp for soft delete
        
        std::string deptName = argv[3];
    }
    else {
        std::cout << "Incorrect input. Check command syntax." << std::endl;
        return 1;
    }

    return 0;
}

int assign(int argc, char **argv)
{
    if (argc < 4) {
        std::cout << "Usage: qadmin assign <user_to_group|group_to_department> <name1> <name2>" << std::endl;
        return 1;
    }

    std::string assignType = argv[2];
    std::string name1 = argv[3];
    std::string name2 = argv[4];

    if (assignType == "user_to_group") {
        std::string userName = argv[3];
        std::string groupName = argv[4];

        // Q: add userName to groupName
    }
    else if (assignType == "group_to_department") {
        std::string groupName = argv[3];
        std::string deptName = argv[4];

        // Q: add deptName to roupName
    }
    else {
        std::cout << "Incorrect input. Check command syntax." << std::endl;
        return 1;
    }

    return 0;
}

/**
 * TODO: Implement any other commands as needed
 */

/** 
 * Argument Parsing:
 * 
 * To access the n-th argument as a string:
 * * std::string argument = std::string{argv[n]};
 * 
 * To access the n-th argument as an integer:
 * * Use conversion functions here: https://en.cppreference.com/w/cpp/string/basic_string/stol
 */

int main(int argc, char **argv)
{

    const char *conninfo;
    PGconn     *conn;
    PGresult   *res;
    int         nFields;
    int         i,
                j;

    /*
     * If the user supplies a parameter on the command line, use it as the
     * conninfo string; otherwise default to setting dbname=postgres and using
     * environment variables or defaults for all other connection parameters.
     */
    if (argc > 1)
        conninfo = argv[1];
    else
        conninfo = "dbname = postgres";

    /* Make a connection to the database */
    conn = PQconnectdb(conninfo);

    /* Check to see that the backend connection was successfully made */
    if (PQstatus(conn) != CONNECTION_OK)
    {
        fprintf(stderr, "%s", PQerrorMessage(conn));
    }

    /* Set always-secure search path, so malicious users can't take control. */
    res = PQexec(conn,
                 "SELECT pg_catalog.set_config('search_path', '', false)");
    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "SET failed: %s", PQerrorMessage(conn));
        PQclear(res);
    }

    /*
     * Should PQclear PGresult whenever it is no longer needed to avoid memory
     * leaks
     */
    PQclear(res);

    /*
     * Our test case here involves using a cursor, for which we must be inside
     * a transaction block.  We could do the whole thing with a single
     * PQexec() of "select * from pg_database", but that's too trivial to make
     * a good example.
     */

    /* Start a transaction block */
    res = PQexec(conn, "BEGIN");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "BEGIN command failed: %s", PQerrorMessage(conn));
        PQclear(res);
    }
    PQclear(res);

    /*
     * Fetch rows from pg_database, the system catalog of databases
     */
    res = PQexec(conn, "DECLARE myportal CURSOR FOR select * from pg_database");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "DECLARE CURSOR failed: %s", PQerrorMessage(conn));
        PQclear(res);
    }
    PQclear(res);

    res = PQexec(conn, "FETCH ALL in myportal");
    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "FETCH ALL failed: %s", PQerrorMessage(conn));
        PQclear(res);
    }

    /* first, print out the attribute names */
    nFields = PQnfields(res);
    for (i = 0; i < nFields; i++)
        printf("%-15s", PQfname(res, i));
    printf("\n\n");

    /* next, print out the rows */
    for (i = 0; i < PQntuples(res); i++)
    {
        for (j = 0; j < nFields; j++)
            printf("%-15s", PQgetvalue(res, i, j));
        printf("\n");
    }

    PQclear(res);

    /* close the portal ... we don't bother to check for errors ... */
    res = PQexec(conn, "CLOSE myportal");
    PQclear(res);

    /* end the transaction */
    res = PQexec(conn, "END");
    PQclear(res);

    /* close the connection to the database and cleanup */
    PQfinish(conn);

    /**
     * argc -> Number of arguments, the first argument is the name of the
     * program itself, the following values
     * (argv[1], argv[2], ... argv[argc - 1]) are the arguments passed to
     * qadmin arg1 arg2 arg3 ...
     *
     * argv is the array of char* value each of which is a pointer to
     * the start of a string containing the value of the argument
     *
     */

    if (argc < 2)
    {
        std::cout << "Too few arguments provided" << std::endl;
        return 1;
    }

    std::string subcommand{argv[1]};

    if (subcommand == "add")
    {
        return add(argc, argv);
    }
    else if (subcommand == "list")
    {
        return list(argc, argv);
    }
    else if (subcommand == "remove")
    {
        return remove(argc, argv);
    }
    else if (subcommand == "assign")
    {
        return assign(argc, argv);
    }



    return 0;
}