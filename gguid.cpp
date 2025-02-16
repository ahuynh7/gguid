// gguid.cpp : Defines the entry point for the application.
//

#include "gguid.h"

using namespace std;

int main(int argc, char **argv) {
	//handle command line arguments
	CLI::App app;

	//flag to generate empty guid(s)
	bool empty_guid = false;
	app.add_flag("-e,--empty", empty_guid, "Generate empty GUID(s)");

	CLI11_PARSE(app, argc, argv);

	if (empty_guid) {
		const string empty_guid_string = "00000000-0000-0000-0000-000000000000";

		cout << empty_guid_string << endl;

		return 0;
	}

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
