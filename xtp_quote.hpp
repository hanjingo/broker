#ifndef XTP_QUOTE_HPP
#define XTP_QUOTE_HPP

#include <string>

#include "xtp_define.hpp"
#include "xtp_quote_api.h"

namespace broker
{
namespace xtp
{

class Quote : public XTP::API::QuoteSpi
{
public:
    typedef enum LoginRet {
        LOGIN_RET_PARAM_INVALID = -3,
        LOGIN_RET_ALREADY_EXIST = -2,
        LOGIN_RET_ERROR = -1,
        LOGIN_RET_SUCCESS = 0,
    } LoginRet;

public:
    explicit Quote(uint8_t client_id,
                   const char* save_file_path,
                   XTP_LOG_LEVEL log_level = XTP_LOG_LEVEL_DEBUG)
        : api_{XTP::API::QuoteApi::CreateQuoteApi(client_id, save_file_path, log_level)}
    {
        api_->RegisterSpi(this);
    }
    virtual ~Quote()
    {
        api_->Release();
    }

public:
    virtual XTP::API::QuoteApi* GetApi()
    {
        return api_;
    }

    virtual XTPRI* GetApiLastError()
    {
        return api_->GetApiLastError();
    }

    virtual const char* GetApiVersion()
    {
        return api_->GetApiVersion();
    }

    virtual const char* GetTradingDay()
    {
        return api_->GetTradingDay();
    }

    virtual int QueryAllTickers(XTP_EXCHANGE_TYPE exchange_id)
    {
        return api_->QueryAllTickers(exchange_id);
    }

    virtual int QueryAllTickersFullInfo(XTP_EXCHANGE_TYPE exchange_id)
    {
        return api_->QueryAllTickersFullInfo(exchange_id);
    }

    virtual int QueryAllTickerPriceInfo()
    {
        return api_->QueryAllTickersPriceInfo();
    }

    virtual int QueryTickersPriceInfo(char* ticker[],
                                      int count,
                                      XTP_EXCHANGE_TYPE exchange_id)
    {
        return api_->QueryTickersPriceInfo(ticker, count, exchange_id);
    }

public:
    // call it before login
    virtual void SetHeartBeatInterval(uint32_t sec)
    {
        api_->SetHeartBeatInterval(sec);
    }

    // total_size = 4 * size; size in [64(default), 128]; call it before login
    virtual void SetUDPBufferSize(int mb)
    {
        api_->SetUDPBufferSize(mb);
    }

    // call it before login
    virtual void SetUDPParseThreadAffinityArray(int32_t cpu_no_array[], int32_t count)
    {
        return api_->SetUDPParseThreadAffinityArray(cpu_no_array, count);
    }

    // call it before login
    virtual void SetUDPRecvThreadAffinityArray(int32_t cpu_no_array[], int32_t count)
    {
        return api_->SetUDPRecvThreadAffinityArray(cpu_no_array, count);
    }

    // call it before login
    virtual void SetUDPSeqLogOutPutFlag(bool flag)
    {
        api_->SetUDPSeqLogOutPutFlag(flag);
    }

    virtual Quote::LoginRet Login(const char* ip,
                                  int port,
                                  const char* username,
                                  const char* passwd,
                                  XTP_PROTOCOL_TYPE proto,
                                  const char* local_ip = NULL)
    {
        return LoginRet(api_->Login(ip, port, username, passwd, proto, local_ip));
    }

    virtual Quote::LoginRet LoginToRebuildQuoteServer(const char* ip,
            int port,
            const char* username,
            const char* passwd,
            XTP_PROTOCOL_TYPE proto,
            const char* local_ip = NULL)
    {
        return LoginRet(api_->LoginToRebuildQuoteServer(ip, port, username, passwd,
                        proto, local_ip));
    }

    virtual int Logout()
    {
        return api_->Logout();
    }

    virtual int LogoutFromRebuildQuoteServer()
    {
        return api_->LogoutFromRebuildQuoteServer();
    }

    virtual int RequestRebuildQuote(XTPQuoteRebuildReq* req)
    {
        return api_->RequestRebuildQuote(req);
    }

    virtual int SubscribeAllMarketData(XTP_EXCHANGE_TYPE exchange_id = XTP_EXCHANGE_UNKNOWN)
    {
        return api_->SubscribeAllMarketData(exchange_id);
    }

    virtual int UnSubscribeAllMarketData(XTP_EXCHANGE_TYPE exchange_id = XTP_EXCHANGE_UNKNOWN)
    {
        return api_->UnSubscribeAllMarketData(exchange_id);
    }

    virtual int SubscribeAllOptionMarketData(XTP_EXCHANGE_TYPE exchange_id = XTP_EXCHANGE_UNKNOWN)
    {
        return api_->SubscribeAllOptionMarketData(exchange_id);
    }

    virtual int UnSubscribeAllOptionMarketData(XTP_EXCHANGE_TYPE exchange_id = XTP_EXCHANGE_UNKNOWN)
    {
        return api_->UnSubscribeAllOptionMarketData(exchange_id);
    }

    virtual int SubscribeAllOptionOrderBook(XTP_EXCHANGE_TYPE exchange_id = XTP_EXCHANGE_UNKNOWN)
    {
        return api_->SubscribeAllOptionOrderBook(exchange_id);
    }

    virtual int UnSubscribeAllOptionOrderBook(XTP_EXCHANGE_TYPE exchange_id = XTP_EXCHANGE_UNKNOWN)
    {
        return api_->UnSubscribeAllOptionOrderBook(exchange_id);
    }

    virtual int SubscribeAllOptionTickByTick(XTP_EXCHANGE_TYPE exchange_id = XTP_EXCHANGE_UNKNOWN)
    {
        return api_->SubscribeAllOptionTickByTick(exchange_id);
    }

    virtual int UnSubscribeAllOptionTickByTick(XTP_EXCHANGE_TYPE exchange_id = XTP_EXCHANGE_UNKNOWN)
    {
        return api_->UnSubscribeAllOptionTickByTick(exchange_id);
    }

    virtual int SubscribeAllOrderBook(XTP_EXCHANGE_TYPE exchange_id = XTP_EXCHANGE_UNKNOWN)
    {
        return api_->SubscribeAllOrderBook(exchange_id);
    }

    virtual int UnSubscribeAllOrderBook(XTP_EXCHANGE_TYPE exchange_id = XTP_EXCHANGE_UNKNOWN)
    {
        return api_->UnSubscribeAllOrderBook(exchange_id);
    }

    virtual int SubscribeAllTickByTick(XTP_EXCHANGE_TYPE exchange_id = XTP_EXCHANGE_UNKNOWN)
    {
        return api_->SubscribeAllTickByTick(exchange_id);
    }

    virtual int UnSubscribeAllTickByTick(XTP_EXCHANGE_TYPE exchange_id = XTP_EXCHANGE_UNKNOWN)
    {
        return api_->UnSubscribeAllTickByTick(exchange_id);
    }

    virtual int SubscribeMarketData(char* ticker[],
                                    int count,
                                    XTP_EXCHANGE_TYPE exchange_id = XTP_EXCHANGE_UNKNOWN)
    {
        return api_->SubscribeMarketData(ticker, count, exchange_id);
    }

    virtual int UnSubscribeMarketData(char* ticker[],
                                      int count,
                                      XTP_EXCHANGE_TYPE exchange_id = XTP_EXCHANGE_UNKNOWN)
    {
        return api_->UnSubscribeMarketData(ticker, count, exchange_id);
    }

    virtual int SubscribeOrderBook(char* ticker[], int count, XTP_EXCHANGE_TYPE exchange_id)
    {
        return api_->SubscribeOrderBook(ticker, count, exchange_id);
    }

    virtual int UnSubscribeOrderBook(char* ticker[], int count, XTP_EXCHANGE_TYPE exchange_id)
    {
        return api_->UnSubscribeOrderBook(ticker, count, exchange_id);
    }

    virtual int SubscribeTickByTick(char* ticker[], int count, XTP_EXCHANGE_TYPE exchange_id)
    {
        return api_->SubscribeTickByTick(ticker, count, exchange_id);
    }

    virtual int UnSubscribeTickByTick(char* ticker[], int count, XTP_EXCHANGE_TYPE exchange_id)
    {
        return api_->UnSubscribeTickByTick(ticker, count, exchange_id);
    }

public:
    virtual void OnDisconnected(int reason) {};

    virtual void OnError(XTPRI* error_info) {};

    virtual void OnSubMarketData(XTPST* ticker, XTPRI* error_info, bool is_last) { };

    virtual void OnUnSubMarketData(XTPST* ticker, XTPRI* error_info, bool is_last) {};

    virtual void OnDepthMarketData(XTPMD* market_data,
                                   int64_t bid1_qty[],
                                   int32_t bid1_count,
                                   int32_t max_bid1_count,
                                   int64_t ask1_qty[],
                                   int32_t ask1_count,
                                   int32_t max_ask1_count) {};

    virtual void OnSubOrderBook(XTPST* ticker, XTPRI* error_info, bool is_last) {};

    virtual void OnUnSubOrderBook(XTPST* ticker, XTPRI* error_info, bool is_last) {};

    virtual void OnOrderBook(XTPOB* order_book) {};

    virtual void OnSubTickByTick(XTPST* ticker, XTPRI* error_info, bool is_last) {};

    virtual void OnUnSubTickByTick(XTPST* ticker, XTPRI* error_info, bool is_last) {};

    virtual void OnTickByTick(XTPTBT* tbt_data) {};

    virtual void OnSubscribeAllMarketData(XTP_EXCHANGE_TYPE exchange_id, XTPRI* error_info) {};

    virtual void OnUnSubscribeAllMarketData(XTP_EXCHANGE_TYPE exchange_id, XTPRI* error_info) {};

    virtual void OnSubscribeAllOrderBook(XTP_EXCHANGE_TYPE exchange_id, XTPRI* error_info) {};

    virtual void OnUnSubscribeAllOrderBook(XTP_EXCHANGE_TYPE exchange_id, XTPRI* error_info) {};

    virtual void OnSubscribeAllTickByTick(XTP_EXCHANGE_TYPE exchange_id, XTPRI* error_info) {};

    virtual void OnUnSubscribeAllTickByTick(XTP_EXCHANGE_TYPE exchange_id, XTPRI* error_info) {};

    virtual void OnQueryAllTickers(XTPQSI* ticker_info, XTPRI* error_info, bool is_last) {};

    virtual void OnQueryTickersPriceInfo(XTPTPI* ticker_info, XTPRI* error_info, bool is_last) {};

    virtual void OnSubscribeAllOptionMarketData(XTP_EXCHANGE_TYPE exchange_id, XTPRI* error_info) {};

    virtual void OnUnSubscribeAllOptionMarketData(XTP_EXCHANGE_TYPE exchange_id, XTPRI* error_info) {};

    virtual void OnSubscribeAllOptionOrderBook(XTP_EXCHANGE_TYPE exchange_id, XTPRI* error_info) {};

    virtual void OnUnSubscribeAllOptionOrderBook(XTP_EXCHANGE_TYPE exchange_id, XTPRI* error_info) {};

    virtual void OnSubscribeAllOptionTickByTick(XTP_EXCHANGE_TYPE exchange_id, XTPRI* error_info) {};

    virtual void OnUnSubscribeAllOptionTickByTick(XTP_EXCHANGE_TYPE exchange_id, XTPRI* error_info) {};

    virtual void OnQueryAllTickersFullInfo(XTPQFI* ticker_info, XTPRI* error_info, bool is_last) {};

    virtual void OnRebuildQuoteServerDisconnected(int reason) {};

    virtual void OnRequestRebuildQuote(XTPQuoteRebuildResultRsp* rebuild_result) {};

    virtual void OnRebuildTickByTick(XTPTBT* tbt_data) {};

    virtual void OnRebuildMarketData(XTPMD* md_data) {};

private:
    XTP::API::QuoteApi* api_;
};

}
}

#endif