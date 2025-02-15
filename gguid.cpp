// gguid.cpp : Defines the entry point for the application.
//

#include "gguid.h"

using namespace std;

int main() {
	//initialize guid
	GUID guid;
	HRESULT hr = CoCreateGuid(&guid);

	if (SUCCEEDED(hr)) {
		wchar_t* guid_string;
		
		if (StringFromCLSID(guid, &guid_string) == S_OK) {
			//print to console
			wcout << guid_string << endl;

			//free memory allocation
			CoTaskMemFree(guid_string);
		}
		else { return 1; } 
	}
	else { return 1; }

	return 0;
}
