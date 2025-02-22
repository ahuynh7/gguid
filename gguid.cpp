#include "gguid.h"

using namespace std;

static wchar_t* generate_guid_string() {
	//initialize guid
	GUID guid;
	HRESULT hr = CoCreateGuid(&guid);

	if (SUCCEEDED(hr) == false) throw exception("Error generating GUID");

	const int LENGTH = 36;
	wchar_t* guid_string;
	wchar_t* formatted_guid_string = new wchar_t[LENGTH + 1];		//todo: use a smart pointer to manage memory instead

	if (StringFromCLSID(guid, &guid_string) == S_OK) {

		//substring to remove curly braces
		wcsncpy(formatted_guid_string, guid_string + 1, LENGTH);
		formatted_guid_string[LENGTH] = L'\0';

		//free original guid string
		CoTaskMemFree(guid_string);

		return formatted_guid_string;
	}
	else {
		delete[] formatted_guid_string;

		throw exception("Error parsing string from GUID");
	}
}

int main(int argc, char **argv) {
	//handle command line arguments
	CLI::App app;

	//flag to generate empty guid(s)
	bool empty_guid = false;
	app.add_flag("-e,--empty", empty_guid, "Generate empty GUID(s)");

	//option to generate multiple guids
	auto count_validator = CLI::Validator(
		[](string& input) {
			//validate input to be greater than 0 and less than or equal to 100
			if (stoi(input) > 0 || stoi(input) <= 100) return "";
			else throw CLI::ValidationError{ "Count must be greater than 0." };

		}, 
		"Validates the input to the count option.",
		"Count Validator");

	int count{ 1 };
	app.add_option("-c,--count", count, "Number of GUID(s) to generate")
		->capture_default_str()
		->transform(count_validator);

	CLI11_PARSE(app, argc, argv);

	if (empty_guid) {
		const string EMPTY_GUID_STRING = "00000000-0000-0000-0000-000000000000";

		for (int i = 0; i < count; i++) 
			cout << EMPTY_GUID_STRING << endl;

		return 0;
	}

	for (int i = 0; i < count; i++) {
		try {
			wchar_t* guid_string = generate_guid_string();

			wcout << guid_string << endl;

			delete[] guid_string;
		}
		catch (exception& e) {
			cerr << "Error generating GUID(s) with error: " << e.what() << endl;

			return 1;
		}
	}

	return 0;
}
