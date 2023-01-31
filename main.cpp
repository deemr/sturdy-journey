#include <iostream>
#include <curl/curl.h>
#include <string>
#include <json.hpp>

#define XBT_ORDERBOOK_URL "https://api.kraken.com/0/public/Depth?pair=XBTUSD"
#define KRAKEN_SYSTEM_STATUS "https://api.kraken.com/0/public/SystemStatus"
using json = nlohmann::json;

class [[maybe_unused]] KrakenHTTP {
    static size_t cb_write_data(char* ptr, size_t size, size_t nmemb, void* resultBody){
        *(static_cast<std::string*>(resultBody)) += std::string {ptr, size * nmemb};
        return size * nmemb;
    };
public:
    KrakenHTTP() = default;
    static json pulse(std::string &data) {
        auto c = curl_easy_init();
        if (c) {
            std::string resultBody;
            curl_easy_setopt(c, CURLOPT_VERBOSE, 1L);
            curl_easy_setopt(c, CURLOPT_WRITEDATA, &resultBody);
            curl_easy_setopt(c, CURLOPT_WRITEFUNCTION, static_cast<size_t (*)(char*,size_t, size_t, void*)>(cb_write_data));
            curl_easy_setopt(c, CURLOPT_URL, KRAKEN_SYSTEM_STATUS);
            auto res = curl_easy_perform(c);
            if (res != CURLE_OK){
                std::cerr << "Operation failed: " << curl_easy_strerror(res) << std::endl;
                return 2;
            }
            data = std::string(resultBody.begin(), resultBody.end());
            curl_easy_cleanup(c);
            return res;
        }
        return 1;
    }
    static json top_of_book([[maybe_unused]] const std::string& symbol) {
        auto c = curl_easy_init();
        std::string resultBody;
        if (c) {
            curl_easy_setopt(c, CURLOPT_VERBOSE, 1L);
            curl_easy_setopt(c, CURLOPT_WRITEDATA, &resultBody);
            curl_easy_setopt(c, CURLOPT_WRITEFUNCTION,
                             static_cast<size_t (*)(char *, size_t, size_t, void *)>(cb_write_data));
            curl_easy_setopt(c, CURLOPT_URL, XBT_ORDERBOOK_URL);
            auto res = curl_easy_perform(c);
            if (res != CURLE_OK)
                std::cerr << "Operation failed: " << curl_easy_strerror(res) << std::endl;
            curl_easy_cleanup(c);
        }
        return json::parse(resultBody);
    }
};

int main(){
    std::string res;
    std::string dummy;
    if (KrakenHTTP::pulse(dummy) == 0){
        auto book = KrakenHTTP::top_of_book(("BTCUSD"));
        std::cout << book["result"]["XXBTZUSD"]["asks"].dump() << std::endl;
        std::cout << book["result"]["XXBTZUSD"]["bids"].dump() << std::endl;
        return 0;
    }
    return 1;
}