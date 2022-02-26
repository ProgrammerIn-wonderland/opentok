#include "alicenet.hpp"
#include <iostream>
#include <regex>
#include <nlohmann/json.hpp>

std::string get_str_between_two_str(const std::string &s, // https://stackoverflow.com/questions/18800796/c-get-string-between-two-delimiter-string
        const std::string &start_delim,
        const std::string &stop_delim)
{
    unsigned first_delim_pos = s.find(start_delim);
    unsigned end_pos_of_first_delim = first_delim_pos + start_delim.length();
    unsigned last_delim_pos = s.find(stop_delim);
 
    return s.substr(end_pos_of_first_delim,
            last_delim_pos - end_pos_of_first_delim);
}

using namespace std;
using namespace nlohmann;
int main(int argc, char *argv[]) {

    if (argc < 2) {
        cout << "no URL specified, please try again with a URL as an argument" << endl;
        return 0;
    }
	alicenet request; // get HTML page
	request.url = argv[1];
	request.type = "GET"; // Optional
	request.userAgent = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/74.0.3729.157 Safari/537.36";
	request.makeRequest();
    try {
        auto jsonData = json::parse(get_str_between_two_str(request.responseData,"window['SIGI_STATE']=",";window['SIGI_RETRY']")); // get & parse JSON from page
        cout <<(string) jsonData["ItemList"]["video"]["preloadList"][0]["url"]; // get URL from json and send it to stdout
    } catch (json::parse_error& e) {

        cerr << "Something went wrong :("<< endl << "details are provided below" << endl << endl;
        cerr << "message: " << e.what() << '\n'
                  << "exception id: " << e.id << '\n'
                  << "byte position of error: " << e.byte << std::endl;
    }



	
}

