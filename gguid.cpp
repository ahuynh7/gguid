// gguid.cpp : Defines the entry point for the application.
//

#include "gguid.h"

using namespace std;

int main() {
	//initialize guid
	GUID guid;
	HRESULT hr = CoCreateGuid(&guid);
	const int length = 36;

	if (SUCCEEDED(hr)) {
		wchar_t* guid_string;
		wchar_t* formatted_guid_string = new wchar_t[length + 1];

		if (StringFromCLSID(guid, &guid_string) == S_OK) {
			//substring to remove curly braces
			wcsncpy(formatted_guid_string, guid_string + 1, length);
			formatted_guid_string[length] = L'\0';

			//print to console
			wcout << formatted_guid_string << endl;

			//free memory allocation
			delete[] formatted_guid_string;
			CoTaskMemFree(guid_string);

		}
		else { return 1; } 
	}
	else { return 1; }

	return 0;
}
