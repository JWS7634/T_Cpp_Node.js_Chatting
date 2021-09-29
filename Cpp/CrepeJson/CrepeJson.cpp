#include <string>
#include <CrepeJson.hpp>

using namespace std;

void CrepeJson::JsonCreate(string Ckey, string CValue)
{
	if(!DataCount)
	{
		Key = (string**)malloc(sizeof(string*));
		Value = (string**)malloc(sizeof(string*));
	}
	else
	{
		realloc(Key,sizeof(string*));
		realloc(Value,sizeof(string*));
	}
	Key[DataCount] = &Ckey;
	Value[DataCount] = &CValue;
	DataCount++;
}
const char* CrepeJson::JsonRead(string Ckey)
{
	for(int i = 0; i < DataCount; i++)
	{
		if(!(*Key[i]).compare(Ckey))
			return (*Value[i]).c_str();
	}
	return 0;
}
int CrepeJson::JsonUpdate(string Ckey, string CValue)
{
	for(int i = 0; i < DataCount; i++)
	{
		if(!(*Key[i]).compare(Ckey))
		{
			*Value[i] = CValue;
			return i;
		}
	}
	return -1;
}
int CrepeJson::JsonDelete(string Ckey)
{
	bool FindKey = false;
	for(int i = 0; i < DataCount; i++)
	{
		if(FindKey)
		{
			Key[i-1] = Key[i];
			Value[i-1] = Value[i];
		}
		else
		{
			if(!(*Key[i]).compare(Ckey))
				FindKey = true;
		}
	}
	if(!FindKey)
		return -1;
	free(Key[DataCount - 1]);
	free(Value[DataCount - 1]);
	DataCount--;
	return 1;
}
const char* CrepeJson::JsonExport()
{
	jsonCache.clear();
	if(!(DataCount > 0))
		return 0;
	jsonCache += "{\n";
	for (int i = 0; i < DataCount - 1; i++)
		jsonCache += "	\""+ *Key[i] +"\" : \"" + *Value[i] + "\",\n";
	jsonCache += "	\""+ *Key[DataCount - 1] +"\" : \"" + *Value[DataCount - 1] + "\"\n";
	jsonCache += "}";
	return jsonCache.c_str();
}