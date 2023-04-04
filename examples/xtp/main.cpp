#include <iostream>
#include <cstring>
#include <chrono>
#include <iomanip>
#include <math.h>

#include "xtp_quote.hpp"
#include "xtp_trader.hpp"

#ifdef WIN32
#include "windows.h"
#else
#include <unistd.h>
#endif

#define PATH_BUF_LEN  1024

std::string Pwd()
{
    char buf[PATH_BUF_LEN] = { 0 };
    std::string str;

#ifdef WIN32
    GetModuleFileName(NULL, buf, PATH_BUF_LEN);

    str = buf;
    int idx = str.find_last_of('\\');
    if (idx > 0) {
        str = str.substr(0, idx);
    }
#else
    readlink("/proc/self/exe", buf, PATH_BUF_LEN);

    str = buf;
    int idx = str.find_last_of('/');
    if (idx > 0) {
        str = str.substr(0, idx);
    }
#endif

    return str;
}

void PrintErr(XTPRI* err)
{
    if (err->error_id == 0) {
        return;
    }

    std::cout << "get err.id=" << err->error_id << ", desc=" << err->error_msg << std::endl;
}


class MyQuote : public broker::xtp::Quote
{
public:
    explicit MyQuote(uint8_t client_id,
                     const char* save_file_path,
                     XTP_LOG_LEVEL log_level = XTP_LOG_LEVEL_DEBUG)
        : broker::xtp::Quote(client_id, save_file_path, log_level)
    {
    }

public:
    virtual void OnSubMarketData(XTPST* ticker, XTPRI* error_info, bool is_last) override
    {
        if (error_info->error_id != broker::xtp::ERR_CODE_OK) {
            std::cout << "sub market data fail with "
                      << " err_id=" << error_info->error_id
                      << " err_msg=" << error_info->error_msg << std::endl;
        }
    }

    virtual void OnQueryTickersPriceInfo(XTPTPI* ticker_info, XTPRI* error_info, bool is_last)
    {
        if (error_info->error_id != broker::xtp::ERR_CODE_OK) {
            std::cout << "query ticker price fail with "
                      << " err_id=" << error_info->error_id
                      << " err_msg=" << error_info->error_msg << std::endl;
        }

        std::cout << "exchange_id=" << (ticker_info->exchange_id == 1 ? "SH" : "SZ")
                  << ", ticker=" << ticker_info->ticker
                  << ", last_price=" << ticker_info->last_price
                  << std::endl;
    }

    virtual void OnDepthMarketData(XTPMD* market_data,
                                   int64_t bid1_qty[],
                                   int32_t bid1_count,
                                   int32_t max_bid1_count,
                                   int64_t ask1_qty[],
                                   int32_t ask1_count,
                                   int32_t max_ask1_count)
    {
        std::cout << "exchange_id=" << (market_data->exchange_id == 1 ? "SH" : "SZ")
                  << ", ticker=" << market_data->ticker
                  << ", last_price=" << market_data->last_price
                  << ", pre_close_price=" << market_data->pre_close_price
                  << ", open_price=" << market_data->open_price
                  << ", high_price=" << market_data->high_price
                  << ", low_price=" << market_data->low_price
                  << ", close_price=" << market_data->close_price

                  << ", time=" << market_data->data_time / int64_t(std::pow(10, 13))
                  << "-" << (market_data->data_time / int64_t(std::pow(10, 11))) % 100
                  << "-" << (market_data->data_time / int64_t(std::pow(10, 9))) % 100
                  << " " << (market_data->data_time / int64_t(std::pow(10, 7))) % 100
                  << ":" << (market_data->data_time / int64_t(std::pow(10, 5))) % 100
                  << ":" << (market_data->data_time / int64_t(std::pow(10, 3))) % 100
                  << "." << (market_data->data_time % int64_t(std::pow(10, 3)))
                  << std::endl;

    }
};

int main(int argc, char* argv[])
{
    std::cout << "xtp demo startup" << std::endl;

    MyQuote quote{ 1, Pwd().c_str() };
    PrintErr(quote.GetApiLastError());

    std::string quote_ip = "119.3.103.38";
    int quote_port = 6002;
    std::string quote_account = "253191001941";
    std::string quote_passwd = "Wd3fSTXq";

    // login
    if (quote.Login(quote_ip.c_str(), quote_port, quote_account.c_str(),
                    quote_passwd.c_str(), XTP_PROTOCOL_TCP)
            != broker::xtp::Quote::LoginRet::LOGIN_RET_SUCCESS) {
        PrintErr(quote.GetApiLastError());
        return 0;
    }
    std::cout << "login success" << std::endl;

    // subscribe sh stock market data
    char** sh_stock = new char* [1];
    sh_stock[0] = new char[XTP_TICKER_LEN];
    memcpy(sh_stock[0], std::string("601360").c_str(), XTP_TICKER_LEN);
    if (quote.SubscribeMarketData(sh_stock, 1, XTP_EXCHANGE_SH) != 0) {
        PrintErr(quote.GetApiLastError());
        return 0;
    }

    delete[] sh_stock[0];
    sh_stock[0] = NULL;
    delete[] sh_stock;
    sh_stock = NULL;
    std::cout << "subscribe sh stock finish" << std::endl;

    // subscribe sz stock market data
    char** sz_stock = new char* [1];
    sz_stock[0] = new char[XTP_TICKER_LEN];
    memcpy(sz_stock[0], std::string("002030").c_str(), XTP_TICKER_LEN);
    if (quote.SubscribeMarketData(sz_stock, 1, XTP_EXCHANGE_SZ) != 0) {
        PrintErr(quote.GetApiLastError());
        return 0;
    }

    delete[] sz_stock[0];
    sz_stock[0] = NULL;
    delete[] sz_stock;
    sz_stock = NULL;
    std::cout << "subscribe sz stock finish" << std::endl;

    // // query ticker
    // char** sh_stock_query = new char* [1];
    // sh_stock_query[0] = new char[XTP_TICKER_LEN];
    // memcpy(sh_stock_query[0], std::string("601360").c_str(), XTP_TICKER_LEN);
    // if (quote.QueryTickersPriceInfo(sh_stock_query, 1, XTP_EXCHANGE_SH) != broker::xtp::ERR_CODE_OK) {
    //     PrintErr(quote.GetApiLastError());
    //     return 0;
    // }

    // delete[] sh_stock_query[0];
    // sh_stock_query[0] = NULL;
    // delete[] sh_stock_query;
    // sh_stock_query = NULL;
    // std::cout << "query ticker finish" << std::endl;

    std::cin.get();
    return 0;
}
