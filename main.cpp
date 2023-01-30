#include <iostream>
#include <curl/curl.h>
#include <string>
#include <json.hpp>

using json = nlohmann::json;

int main(){
    auto c = curl_easy_init();
    if (c) {

        std::string res_data;

        std::string resultBody { };
        auto cb_write_data = [](char* ptr, size_t size, size_t nmemb, void* resultBody){
            *(static_cast<std::string*>(resultBody)) += std::string {ptr, size * nmemb};
            return size * nmemb;
        };
        curl_easy_setopt(c, CURLOPT_WRITEDATA, &resultBody);
        curl_easy_setopt(c, CURLOPT_WRITEFUNCTION, static_cast<size_t (*)(char*, size_t, size_t, void*)>(cb_write_data));
        /* preparing requests */
        curl_easy_setopt(c, CURLOPT_URL, "https://api.kraken.com/0/public/Depth?pair=XBTUSD");
        curl_easy_setopt(c, CURLOPT_VERBOSE, 1L);
        auto res = curl_easy_perform(c);
        if (res != CURLE_OK) {
            std::cerr << "Operation failed: " << curl_easy_strerror(res) << std::endl;
        }
        std::cout << "POST: " << std::endl;
        std::cout << "RESULT BODY:\n" << resultBody << std::endl;
        auto j1 = json::parse(resultBody);
        std::cout << "JSON: \n" << j1["result"] << std::endl;

        curl_easy_cleanup(c);
    }
    return 0;
}