#include <string>
#include <iostream>
#include "libpq-fe.h"

static void exit_nicely(PGconn *conn)
{
    PQfinish(conn);
    exit(1);
}

int add(int argc, char **argv)
{
    // Connection to database
    const char *conninfo;
    PGconn *conn;
    PGresult *res;
    int nFields;
    int i, j;

    if (argc > 1) {
        conninfo = argv[1];
    }
    else {
        conninfo = "dbname = postgres";
    }

    /* Make a connection to the database */
    conn = PQconnectdb(conninfo);

    /* Check to see that the backend connection was successfully made */
    if (PQstatus(conn) != CONNECTION_OK)
    {
        fprintf(stderr, "%s", PQerrorMessage(conn));
        exit_nicely(conn);
    }

    /* Set always-secure search path, so malicious users can't take control. */
    res = PQexec(conn,
                 "SELECT pg_catalog.set_config('search_path', '', false)");
    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "SET failed: %s", PQerrorMessage(conn));
        PQclear(res);
        exit_nicely(conn);
    }

    /*
     * Should PQclear PGresult whenever it is no longer needed to avoid memory
     * leaks
     */
    PQclear(res);



    if (argc < 3) {
        std::cout << "Usage: qadmin add user <first name> <last name> <email> <department> <optional list of group names>" << std::endl;
        std::cout << "Usage: qadmin add group <group name> <department name>" << std::endl;
        std::cout << "Usage: qadmin add department <department name> <department head> <department building>" << std::endl;
        return 1;
    }

    std::string subcommand = argv[2];
    std::string args;
    std::string query = "INSERT INTO";

    if (subcommand == "user") {
        // qadmin add user <first name> <last name> <email> <department> <optional list of group names>
        
        query += "Users";

        std::string firstName = " " + *argv[3];
        std::string lastName = " " + *argv[4];
        std::string email = " " + *argv[5];
        std::string deptName = " " + *argv[6];
        if (argc > 7) {
            std::string listGroupNames = " " + *argv[7];
            args += firstName + lastName + email + deptName + listGroupNames;
        }
        else {
            args += firstName + lastName + email + deptName;
        }
    }
    else if (subcommand == "group") {
        // qadmin add group <group name> <department name>
        
        query += "Groups";

        std::string groupName = " " + *argv[3];
        std::string deptName = " " + *argv[4];

        args += groupName + deptName;
    }
    else if (subcommand == "department") {
        // qadmin add department <department name> <department head> <department building>

        query += "Departments";

        std::string deptName = " " + *argv[3];
        std::string deptHead = " " + *argv[4];
        std::string deptBuilding = " " + *argv[5];

        args += deptName + deptHead + deptBuilding;
    }
    else {
        std::cout << "Incorrect input. Check command syntax." << std::endl;
        return 1;
    }

    query += " (" + args + ") COMMIT";

    /* Start a transaction block */
    res = PQexec(conn, "BEGIN");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "BEGIN command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        exit_nicely(conn);
    }
    PQclear(res);

    const char* queryPtr = query.c_str(); // turns query into type of PQexec paramater

    /* Run query */
    res = PQexec(conn, queryPtr);
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "Query failed: %s", PQerrorMessage(conn));
        PQclear(res);
        exit_nicely(conn);
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

    return 0;
}

int list(int argc, char **argv)
{
    // Connection to database
    const char *conninfo;
    PGconn *conn;
    PGresult *res;
    int nFields;
    int i, j;

    if (argc > 1) {
        conninfo = argv[1];
    }
    else {
        conninfo = "dbname = postgres";
    }

    /* Make a connection to the database */
    conn = PQconnectdb(conninfo);

    /* Check to see that the backend connection was successfully made */
    if (PQstatus(conn) != CONNECTION_OK)
    {
        fprintf(stderr, "%s", PQerrorMessage(conn));
        exit_nicely(conn);
    }

    /* Set always-secure search path, so malicious users can't take control. */
    res = PQexec(conn,
                 "SELECT pg_catalog.set_config('search_path', '', false)");
    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "SET failed: %s", PQerrorMessage(conn));
        PQclear(res);
        exit_nicely(conn);
    }

    /*
     * Should PQclear PGresult whenever it is no longer needed to avoid memory
     * leaks
     */
    PQclear(res);



    if (argc < 3) {
        std::cout << "Usage: qadmin list <user|group|department>" << std::endl;
        return 1;
    }

    std::string subcommand = argv[2];

    if (subcommand == "user") {
        /* Fetch the data */
        res = PQexec(conn, "BEGIN; SELECT * FROM Users");
        if (PQresultStatus(res) != PGRES_COMMAND_OK)
        {
            fprintf(stderr, "Query failed: %s", PQerrorMessage(conn));
            PQclear(res);
            exit_nicely(conn);
        }
        
        /* Print out the attribute names */
        nFields = PQnfields(res);
        for (i = 0; i < nFields; i++) {
            printf("%-15s", PQfname(res, i));
        }
        printf("\n\n");

        /* Print out the rows */
        for (i = 0; i < PQntuples(res); i++) {
            for (j = 0; j < nFields; j++) {
                printf("%-15s", PQgetvalue(res, i, j));
            }
            printf("\n");
        }
        
        /* close the portal ... we don't bother to check for errors ... */
        res = PQexec(conn, "CLOSE myportal");
        PQclear(res);

        /* end the transaction */
        res = PQexec(conn, "END");
        PQclear(res);
    }
    else if (subcommand == "department") {
        /* Fetch the data */
        res = PQexec(conn, "BEGIN; SELECT * FROM Departments");
        if (PQresultStatus(res) != PGRES_COMMAND_OK)
        {
            fprintf(stderr, "Query failed: %s", PQerrorMessage(conn));
            PQclear(res);
            exit_nicely(conn);
        }
        
        /* Print out the attribute names */
        nFields = PQnfields(res);
        for (i = 0; i < nFields; i++) {
            printf("%-15s", PQfname(res, i));
        }
        printf("\n\n");

        /* Print out the rows */
        for (i = 0; i < PQntuples(res); i++) {
            for (j = 0; j < nFields; j++) {
                printf("%-15s", PQgetvalue(res, i, j));
            }
            printf("\n");
        }
        /* close the portal ... we don't bother to check for errors ... */
        res = PQexec(conn, "CLOSE myportal");
        PQclear(res);

        /* end the transaction */
        res = PQexec(conn, "END");
        PQclear(res);
    }
    else if (subcommand == "group") {
        /* Fetch the data */
        res = PQexec(conn, "BEGIN; SELECT * FROM Groups");
        if (PQresultStatus(res) != PGRES_COMMAND_OK)
        {
            fprintf(stderr, "Query failed: %s", PQerrorMessage(conn));
            PQclear(res);
            exit_nicely(conn);
        }
        
        /* Print out the attribute names */
        nFields = PQnfields(res);
        for (i = 0; i < nFields; i++) {
            printf("%-15s", PQfname(res, i));
        }
        printf("\n\n");

        /* Print out the rows */
        for (i = 0; i < PQntuples(res); i++) {
            for (j = 0; j < nFields; j++) {
                printf("%-15s", PQgetvalue(res, i, j));
            }
            printf("\n");
        }
        /* close the portal ... we don't bother to check for errors ... */
        res = PQexec(conn, "CLOSE myportal");
        PQclear(res);

        /* end the transaction */
        res = PQexec(conn, "END");
        PQclear(res);
    }
    else {
        std::cout << "Incorrect input. Check command syntax." << std::endl;
        return 1;
    }

    /* close the connection to the database and cleanup */
    PQfinish(conn);

    return 0;
}

int remove(int argc, char **argv)
{
    // Connection to database
    const char *conninfo;
    PGconn *conn;
    PGresult *res;
    int nFields;
    int i, j;

    if (argc > 1) {
        conninfo = argv[1];
    }
    else {
        conninfo = "dbname = postgres";
    }

    /* Make a connection to the database */
    conn = PQconnectdb(conninfo);

    /* Check to see that the backend connection was successfully made */
    if (PQstatus(conn) != CONNECTION_OK)
    {
        fprintf(stderr, "%s", PQerrorMessage(conn));
        exit_nicely(conn);
    }

    /* Set always-secure search path, so malicious users can't take control. */
    res = PQexec(conn,
                 "SELECT pg_catalog.set_config('search_path', '', false)");
    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "SET failed: %s", PQerrorMessage(conn));
        PQclear(res);
        exit_nicely(conn);
    }

    /*
     * Should PQclear PGresult whenever it is no longer needed to avoid memory
     * leaks
     */
    PQclear(res);



    if (argc < 3) {
        std::cout << "Usage: qadmin remove <user|group|department> <name>" << std::endl;
        return 1;
    }

    std::string removeType = argv[2];
    std::string args;
    std::string query;

    if (removeType == "user") {
        // qadmin remove user <first name> <last name>
        
        res = PQexec(conn, "BEGIN");
        if (PQresultStatus(res) != PGRES_COMMAND_OK)
        {
            fprintf(stderr, "Query failed: %s", PQerrorMessage(conn));
            PQclear(res);
            exit_nicely(conn);
        }
        PQclear(res);

        std::string firstName = argv[3];
        std::string lastName = argv[4];

        /* Setting data for update */
        query = "SELECT Deleted_Status FROM Users WHERE First_Name='" + userName + "' AND Last_Name='" + lastName + "' FOR UPDATE";
        const char* queryPtr = query.c_str(); // turns query into type of PQexec paramater

        res = PQexec(conn, queryPtr);
        if (PQresultStatus(res) != PGRES_COMMAND_OK)
        {
            fprintf(stderr, "Query failed: %s", PQerrorMessage(conn));
            PQclear(res);
            exit_nicely(conn);
        }
        PQclear(res);

        /* Running query */
        query = "UPDATE Users SET Deleted_Status=1 WHERE First_Name='" + userName + "' AND Last_Name='" + lastName + "' COMMIT";
        const char* queryPtr = query.c_str(); // turns query into type of PQexec paramater

        res = PQexec(conn, queryPtr);
        if (PQresultStatus(res) != PGRES_COMMAND_OK)
        {
            fprintf(stderr, "Query failed: %s", PQerrorMessage(conn));
            PQclear(res);
            exit_nicely(conn);
        }
        PQclear(res);

        /* close the portal ... we don't bother to check for errors ... */
        res = PQexec(conn, "CLOSE myportal");
        PQclear(res);

        /* end the transaction */
        res = PQexec(conn, "END");
        PQclear(res);
        
    }
    else if (removeType == "group") {
        // qadmin remove group <group name>
       
        res = PQexec(conn, "BEGIN");
        if (PQresultStatus(res) != PGRES_COMMAND_OK)
        {
            fprintf(stderr, "Query failed: %s", PQerrorMessage(conn));
            PQclear(res);
            exit_nicely(conn);
        }
        PQclear(res);

        std::string groupName = argv[3];

        /* Setting data for update */
        query = "SELECT Deleted_Status FROM Groups WHERE Group_Name='" + groupName + "' FOR UPDATE";
        const char* queryPtr = query.c_str(); // turns query into type of PQexec paramater

        res = PQexec(conn, queryPtr);
        if (PQresultStatus(res) != PGRES_COMMAND_OK)
        {
            fprintf(stderr, "Query failed: %s", PQerrorMessage(conn));
            PQclear(res);
            exit_nicely(conn);
        }
        PQclear(res);

        /* Running query */
        query = "UPDATE Groups SET Deleted_Status=1 WHERE Group_Name='" + groupName + "' COMMIT";
        const char* queryPtr = query.c_str(); // turns query into type of PQexec paramater

        res = PQexec(conn, queryPtr);
        if (PQresultStatus(res) != PGRES_COMMAND_OK)
        {
            fprintf(stderr, "Query failed: %s", PQerrorMessage(conn));
            PQclear(res);
            exit_nicely(conn);
        }
        PQclear(res);

        /* close the portal ... we don't bother to check for errors ... */
        res = PQexec(conn, "CLOSE myportal");
        PQclear(res);

        /* end the transaction */
        res = PQexec(conn, "END");
        PQclear(res);

    }
    else if (removeType == "department") {
        // qadmin remove department <department name>

        res = PQexec(conn, "BEGIN");
        if (PQresultStatus(res) != PGRES_COMMAND_OK)
        {
            fprintf(stderr, "Query failed: %s", PQerrorMessage(conn));
            PQclear(res);
            exit_nicely(conn);
        }
        PQclear(res);

        std::string deptName = argv[3];

        /* Setting data for update */
        query = "SELECT Deleted_Status FROM Departments WHERE Department_Name='" + deptName + "' FOR UPDATE";
        const char* queryPtr = query.c_str(); // turns query into type of PQexec paramater

        res = PQexec(conn, queryPtr);
        if (PQresultStatus(res) != PGRES_COMMAND_OK)
        {
            fprintf(stderr, "Query failed: %s", PQerrorMessage(conn));
            PQclear(res);
            exit_nicely(conn);
        }
        PQclear(res);

        /* Running query */
        query = "UPDATE Departments SET Deleted_Status=1 WHERE Department_Name='" + deptName + "' COMMIT";
        const char* queryPtr = query.c_str(); // turns query into type of PQexec paramater

        res = PQexec(conn, queryPtr);
        if (PQresultStatus(res) != PGRES_COMMAND_OK)
        {
            fprintf(stderr, "Query failed: %s", PQerrorMessage(conn));
            PQclear(res);
            exit_nicely(conn);
        }
        PQclear(res);

        /* close the portal ... we don't bother to check for errors ... */
        res = PQexec(conn, "CLOSE myportal");
        PQclear(res);

        /* end the transaction */
        res = PQexec(conn, "END");
        PQclear(res);
        
    }
    else {
        std::cout << "Incorrect input. Check command syntax." << std::endl;
        return 1;
    }

    /* close the connection to the database and cleanup */
    PQfinish(conn);

    return 0;
}

int assign(int argc, char **argv)
{
    // Connection to database
    const char *conninfo;
    PGconn *conn;
    PGresult *res;
    int nFields;
    int i, j;

    if (argc > 1) {
        conninfo = argv[1];
    }
    else {
        conninfo = "dbname = postgres";
    }

    /* Make a connection to the database */
    conn = PQconnectdb(conninfo);

    /* Check to see that the backend connection was successfully made */
    if (PQstatus(conn) != CONNECTION_OK)
    {
        fprintf(stderr, "%s", PQerrorMessage(conn));
        exit_nicely(conn);
    }

    /* Set always-secure search path, so malicious users can't take control. */
    res = PQexec(conn,
                 "SELECT pg_catalog.set_config('search_path', '', false)");
    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "SET failed: %s", PQerrorMessage(conn));
        PQclear(res);
        exit_nicely(conn);
    }

    /*
     * Should PQclear PGresult whenever it is no longer needed to avoid memory
     * leaks
     */
    PQclear(res);



    if (argc < 4) {
        std::cout << "Usage: qadmin assign <user_to_group|group_to_department> <name1> <name2>" << std::endl;
        return 1;
    }

    std::string assignType = argv[2];
    std::string name1 = argv[3];
    std::string name2 = argv[4];

    std::string query;

    if (assignType == "user_to_group") {
        std::string firstName = name1;
        std::string groupName = name2;

        /* Start a transaction block */
        res = PQexec(conn, "BEGIN");
        if (PQresultStatus(res) != PGRES_COMMAND_OK)
        {
            fprintf(stderr, "BEGIN command failed: %s", PQerrorMessage(conn));
            PQclear(res);
            exit_nicely(conn);
        }
        PQclear(res);

        query = "SELECT Groups_In FROM Users WHERE First_Name='" + firstName + "' FOR UPDATE";
        const char* queryPtr = query.c_str(); // turns query into type of PQexec paramater

        /* Run query */
        res = PQexec(conn, queryPtr);
        if (PQresultStatus(res) != PGRES_COMMAND_OK)
        {
            fprintf(stderr, "Query failed: %s", PQerrorMessage(conn));
            PQclear(res);
            exit_nicely(conn);
        }
        PQclear(res);

        query = "UPDATE Users SET Groups_In='" + groupName + "' WHERE First_Name='" + firstName + "' COMMIT";
        const char* queryPtr = query.c_str(); // turns query into type of PQexec paramater

        /* Run query */
        res = PQexec(conn, queryPtr);
        if (PQresultStatus(res) != PGRES_COMMAND_OK)
        {
            fprintf(stderr, "Query failed: %s", PQerrorMessage(conn));
            PQclear(res);
            exit_nicely(conn);
        }
        PQclear(res);
        
    }
    else if (assignType == "group_to_department") {
        std::string groupName = name1;
        std::string deptName = name2;

        /* Start a transaction block */
        res = PQexec(conn, "BEGIN");
        if (PQresultStatus(res) != PGRES_COMMAND_OK)
        {
            fprintf(stderr, "BEGIN command failed: %s", PQerrorMessage(conn));
            PQclear(res);
            exit_nicely(conn);
        }
        PQclear(res);

        query = "SELECT Department FROM Groups WHERE Group_Name='" + groupName + "' FOR UPDATE";
        const char* queryPtr = query.c_str(); // turns query into type of PQexec paramater

        /* Run query */
        res = PQexec(conn, queryPtr);
        if (PQresultStatus(res) != PGRES_COMMAND_OK)
        {
            fprintf(stderr, "Query failed: %s", PQerrorMessage(conn));
            PQclear(res);
            exit_nicely(conn);
        }
        PQclear(res);

        query = "UPDATE Groups SET Department='" + deptName + "' WHERE Group_Name='" + groupName + "' COMMIT";
        const char* queryPtr = query.c_str(); // turns query into type of PQexec paramater

        /* Run query */
        res = PQexec(conn, queryPtr);
        if (PQresultStatus(res) != PGRES_COMMAND_OK)
        {
            fprintf(stderr, "Query failed: %s", PQerrorMessage(conn));
            PQclear(res);
            exit_nicely(conn);
        }
        PQclear(res);
    }
    else {
        std::cout << "Incorrect input. Check command syntax." << std::endl;
        return 1;
    }

    /* close the portal ... we don't bother to check for errors ... */
    res = PQexec(conn, "CLOSE myportal");
    PQclear(res);

    /* end the transaction */
    res = PQexec(conn, "END");
    PQclear(res);

    /* close the connection to the database and cleanup */
    PQfinish(conn);

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
    
    if (argc < 2) {
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