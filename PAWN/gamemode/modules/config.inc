#define SQL_HOST 						"localhost"
#define SQL_DB							"test"
#define SQL_USER 						"root"
#define SQL_PASS						"tuHaslo"

stock mysql_query_format(format_query[], va_args<>)
{
	new query[1024];

	va_format(query, sizeof(query), format_query, va_start<1>);
	mysql_query(query);

	return 1;
}

stock mysql_check()
{
    if(!mysql_ping())
    {
        ForeachEx(i, MAX_PLAYERS) KickWithWait(i);
        
        print("[MySQL] Utracono po³¹czenie. Ponawiam...");
        print("[MySQL] Próba nie powiod³a siê. [Zakoñczono]");
        
        SendRconCommand("hostname B³¹d bazy danych!!!");
        SendRconCommand("password errormessage");
        
        SetGameModeText("MYSQL ERROR");
    }
	
    return 1;
}