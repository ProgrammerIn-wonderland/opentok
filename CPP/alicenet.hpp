#include <cstddef>
#include <cstring>
#include <iostream>
#include <iterator>
#include <string>
#include <type_traits>
#include <curl/curl.h>
#include <stdexcept>
#include <vector>
#include <map>


#pragma comment(lib, "curl")

class alicenet {       // The class
	public:             // Access specifier
		std::string url;
        std::map<std::string, std::string> headers;
		std::string type;
        std::string postOptions;
		std::string userAgent;
		std::string authentication;
        std::string responseData;
        long responseCode;
        std::map<std::string, std::string> responseHeaders;
        double timeElapsed;
	

		void makeRequest();

};

inline size_t writeFunction(void *ptr, size_t size, size_t nmemb, std::string* data) {
    data->append((char*) ptr, size * nmemb);
    return size * nmemb;
}

inline std::vector<std::string> makeHeaderStringIntoVector(std::string header_string) {

    std::vector<std::string> result;
    size_t pos = 0;
    while ((pos = header_string.find("\n")) != std::string::npos) {
        result.push_back(header_string.substr(0, pos));
        header_string.erase(0, pos + 1);
    }

    return result;

}

inline std::map<std::string, std::string> makeHeaderVectorIntoMap(std::vector<std::string> header_vector) {
    std::map<std::string, std::string>  result;
    
    for (std::string header: header_vector) {
        size_t pos = 0;
        while ((pos = header.find(": ")) != std::string::npos) {
            std::string headerp1 = header.substr(0, pos); 
            header.erase(0, pos + 2);
            result[headerp1] = header;
        }
    }
    return result;

}

inline void alicenet::makeRequest() {
	if (userAgent.empty()) 
		userAgent = "curl/7.42.0";
	auto curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
		if (!authentication.empty())
        	curl_easy_setopt(curl, CURLOPT_USERPWD, authentication.c_str());
        curl_easy_setopt(curl, CURLOPT_USERAGENT, userAgent.c_str());
        curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
        if (type == "POST") 
			curl_easy_setopt(curl, CURLOPT_POST, 1L);
		if (!postOptions.empty())
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postOptions.c_str());
        if (!headers.empty()) {
            struct curl_slist* headersList = NULL;
            for (auto header: headers) {
                std::string headerstring = header.first + ": " + header.second; // make the header string
                headersList = curl_slist_append(headersList, headerstring.c_str());
            }
        }
        
        std::string response_string;
        std::string header_string;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);
        
        CURLcode curlPref =  curl_easy_perform(curl);

        char* url;
        long response_code = 0;
        double elapsed;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
        curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &elapsed);
        curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &url);
        
        

        if (curlPref != CURLE_OK) {
            std::cerr << "CURL failed to execute: " << curl_easy_strerror(curlPref);
            throw curl_easy_strerror(curlPref);
        }

        curl_easy_cleanup(curl);
        curl = NULL;
		responseData = response_string;
        responseCode = response_code;
        responseHeaders = makeHeaderVectorIntoMap(makeHeaderStringIntoVector(header_string));
        timeElapsed = elapsed;
    }
}