#include "SQL.H"
#include "Sqlapi.h"
#include "Logger.h"
//#pragma unmanaged
SACommand * cmd = new SACommand();
SAConnection * con = new SAConnection();

SQL::SQL(void)
{
}
void SQL::Connect(char* DataBase,char* Acc,char* Password)
{
	try
	{
		con->Connect(DataBase,Acc,Password,SA_SQLServer_Client);
		cmd->setConnection(con);
	}
	catch(SAException &x)
	{
		MessageBoxA(NULL, x.ErrText(), "Can't connect to the database!", MB_OK);
	}
}
int SQL::GetFieldInt(char* Table, char* Field, const char* Optional, ...)
{
	char Buffer[1024];
	va_list pArguments;
    va_start(pArguments, Optional);
    vsprintf(Buffer, Optional, pArguments);
    va_end(pArguments);
    if (Optional)
	    this->Exec("SELECT %s FROM %s %s;", Field, Table, Buffer);
    else
		this->Exec("SELECT %s FROM %s;", Field, Table);
    if(cmd->isResultSet()) 
    {
	    cmd->FetchNext();
	    int Result = cmd->Field(Field).asLong();
	    return Result;
    }
	return 0;
    }

void SQL::Exec(const char* szQuery, ...)
{
	    char szBuffer[1024];
	    va_list pArguments;
	    va_start(pArguments, szQuery);
	    vsprintf(szBuffer, szQuery, pArguments);
	    va_end(pArguments);
	    cmd->setCommandText(szBuffer);
	    cmd->Execute();
		
}
int SQL::GetBufferQueryInt(char* Query,char* BuffName)
{
	int x = -1;
	cmd->setCommandText(Query);
	cmd->Execute();
	if(cmd->isResultSet())
	{
		cmd->FetchNext();
		 x = cmd->Field(BuffName).asLong();
	}
		return x;
}

SQL::~SQL(void)
{
}