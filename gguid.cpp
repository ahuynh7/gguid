// gguid.cpp : Defines the entry point for the application.
//

#include "gguid.h"

using namespace std;

static wchar_t* generate_guid_string() {
	//initialize guid
	GUID guid;
	HRESULT hr = CoCreateGuid(&guid);
	const int length = 36;

	if (SUCCEEDED(hr)) {
		wchar_t* guid_string;
		//todo: use a smart pointer to manage memory instead
		wchar_t* formatted_guid_string = new wchar_t[length + 1];

		if (StringFromCLSID(guid, &guid_string) == S_OK) {
			//substring to remove curly braces
			wcsncpy(formatted_guid_string, guid_string + 1, length);
			formatted_guid_string[length] = L'\0';

			//free original guid string
			CoTaskMemFree(guid_string);

			return formatted_guid_string;
		}
		//todo: throw more specific exceptions
		else {
			delete[] formatted_guid_string;

			throw exception();
		}
	}
	else throw exception();
}

int main(int argc, char **argv) {
	//handle command line arguments
	CLI::App app;

	//flag to generate empty guid(s)
	bool empty_guid = false;
	app.add_flag("-e,--empty", empty_guid, "Generate empty GUID(s)");

	//option to generate multiple guids
	auto count_validator = CLI::Validator(
		[](string &input) {
			//validate input to be greater than 0
			if (stoi(input) > 0) return "";
			else throw CLI::ValidationError{ "Count must be greater than 0." };

		}, "Validates the input to the count option.", "Count Validator"
	);

	int count{ 21 };
	app.add_option("-c,--count", count, "Number of GUID(s) to generate")
		->capture_default_str()
		->transform(count_validator);

	CLI11_PARSE(app, argc, argv);

	if (empty_guid) {
		const string empty_guid_string = "00000000-0000-0000-0000-000000000000";

		for (int i = 0; i < count; i++) 
			cout << empty_guid_string << endl;

		return 0;
	}

	for (int i = 0; i < count; i++) {
		try {
			wchar_t* guid_string = generate_guid_string();

			wcout << guid_string << endl;

			delete[] guid_string;
		}
		catch (exception& _) {
			cerr << "Error generating GUID(s)." << endl;

			return 1;
		}
	}

	return 0;
}
