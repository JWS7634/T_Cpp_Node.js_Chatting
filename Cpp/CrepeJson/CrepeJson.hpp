#ifndef CREPEJSON_HPP_
#define CREPEJSON_HPP_

#include <string>

using namespace std;

class CrepeJson
{
	public:
		// Create the Json Datas
		void JsonCreate(string Ckey, string CValue);
		// return the Json Value by const char*
		// if data is not exist return 0
		const char* JsonRead(string Ckey);
		// Update the Json Value
		// if Key is not exist return -1
		// if Update success return index of data
		int JsonUpdate(string Ckey, string CValue);
		// Delete the Json Data by Json Key
		// return index of data
		int JsonDelete(string Ckey);
		// return the Full Json data by const char*
		const char* JsonExport();
	private:
		int DataCount = 0;
		string jsonCache = string();
		string** Key;
		string** Value;
};

#endif