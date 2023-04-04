#ifndef XTP_TRADER_HPP
#define XTP_TRADER_HPP

#include "xtp_define.hpp"
#include "xtp_trader_api.h"

namespace broker
{
namespace xtp
{

class Trader : public XTP::API::TraderSpi
{
public:
    Trader(uint8_t client_id,
           const char* save_file_path,
           XTP_LOG_LEVEL log_level = XTP_LOG_LEVEL_DEBUG)
        : api_{XTP::API::TraderApi::CreateTraderApi(client_id, save_file_path, log_level)}
    {
        api_->RegisterSpi(this);
    }
    ~Trader()
    {
        api_->Release();
    }

    inline XTP::API::TraderApi* GetApi()
    {
        return api_;
    }

public:
    virtual void RegisterSpi(TraderSpi* spi)
    {
        return api_->RegisterSpi(spi);
    }

    // call it before login
    virtual void SetHeartBeatInterval(uint32_t interval)
    {
        api_->SetHeartBeatInterval(interval);
    }

    // call it before login
    virtual void SetSoftwareKey(const char* key)
    {
        api_->SetSoftwareKey(key);
    }

    // call it before login
    virtual void SetSoftwareVersion(const char* version)
    {
        api_->SetSoftwareVersion(version);
    }

    // call it before login
    virtual void SubscribePublicTopic(XTP_TE_RESUME_TYPE resume_type)
    {
        api_->SubscribePublicTopic(resume_type);
    }

    virtual uint64_t Login(const char* ip, int port, const char* user, const char* password, XTP_PROTOCOL_TYPE sock_type, const char* local_ip = NULL)
    {
        return api_->Login(ip, port, user, password, sock_type, local_ip);
    }

    virtual int LoginALGO(const char* ip, int port, const char* user, const char* password, XTP_PROTOCOL_TYPE sock_type, const char* local_ip = NULL)
    {
        return api_->LoginALGO(ip, port, user, password, sock_type, local_ip);
    }

    virtual int Logout(uint64_t session_id)
    {
        return api_->Logout(session_id);
    }

    virtual void Release()
    {
        api_->Release();
    }

    // call it after login; system account only
    virtual int ModifyUserTerminalInfo(const XTPUserTerminalInfoReq* info, uint64_t session_id)
    {
        return api_->ModifyUserTerminalInfo(info, session_id);
    }

    virtual uint64_t InsertOrder(XTPOrderInsertInfo* order, uint64_t session_id)
    {
        return api_->InsertOrder(order, session_id);
    }

    virtual uint64_t InsertOrderExtra(XTPOrderInsertInfo* order, uint64_t session_id)
    {
        return api_->InsertOrderExtra(order, session_id);
    }

    virtual uint64_t CancelOrder(const uint64_t order_xtp_id, uint64_t session_id)
    {
        return api_->CancelOrder(order_xtp_id, session_id);
    }

    virtual uint64_t FundTransfer(XTPFundTransferReq* fund_transfer, uint64_t session_id)
    {
        return api_->FundTransfer(fund_transfer, session_id);
    }

    virtual uint64_t CreditCashRepay(double amount, uint64_t session_id)
    {
        return api_->CreditCashRepay(amount, session_id);
    }

    virtual uint64_t CreditCashRepayDebtInterestFee(const char* debt_id, double amount, uint64_t session_id)
    {
        return api_->CreditCashRepayDebtInterestFee(debt_id, amount, session_id);
    }

    virtual uint64_t CreditSellStockRepayDebtInterestFee(XTPOrderInsertInfo* order, const char* debt_id, uint64_t session_id)
    {
        return api_->CreditSellStockRepayDebtInterestFee(order, debt_id, session_id);
    }

    virtual uint64_t InsertOptionCombinedOrder(XTPOptCombOrderInsertInfo* order, uint64_t session_id)
    {
        return api_->InsertOptionCombinedOrder(order, session_id);
    }

    virtual uint64_t InsertOptionCombinedOrderExtra(XTPOptCombOrderInsertInfo* order, uint64_t session_id)
    {
        return api_->InsertOptionCombinedOrderExtra(order, session_id);
    }

    virtual uint64_t CancelOptionCombinedOrder(const uint64_t order_xtp_id, uint64_t session_id)
    {
        return api_->CancelOptionCombinedOrder(order_xtp_id, session_id);
    }

    virtual int ALGOUserEstablishChannel(const char* oms_ip, int oms_port, const char* user, const char* password, uint64_t session_id)
    {
        return api_->ALGOUserEstablishChannel(oms_ip, oms_port, user, password, session_id);
    }

    virtual int InsertAlgoOrder(uint32_t strategy_type, uint64_t client_strategy_id, char* strategy_param, uint64_t session_id)
    {
        return api_->InsertAlgoOrder(strategy_type, client_strategy_id, strategy_param, session_id);
    }

    virtual int CancelAlgoOrder(bool cancel_flag, uint64_t xtp_strategy_id, uint64_t session_id)
    {
        return api_->CancelAlgoOrder(cancel_flag, xtp_strategy_id, session_id);
    }

public:
    virtual const char* GetTradingDay()
    {
        return api_->GetTradingDay();
    }

    virtual XTPRI* GetApiLastError()
    {
        return api_->GetApiLastError();
    }

    virtual const char* GetApiVersion()
    {
        return api_->GetApiVersion();
    }

    virtual uint8_t GetClientIDByXTPID(uint64_t order_xtp_id)
    {
        return api_->GetClientIDByXTPID(order_xtp_id);
    }

    virtual const char* GetAccountByXTPID(uint64_t order_xtp_id)
    {
        return api_->GetAccountByXTPID(order_xtp_id);
    }

    virtual bool IsServerRestart(uint64_t session_id)
    {
        return api_->IsServerRestart(session_id);
    }

    // call it after login
    virtual int QueryAccountTradeMarket(uint64_t session_id, int request_id)
    {
        return api_->QueryAccountTradeMarket(session_id, request_id);
    }

    // call it after login
    virtual uint64_t GetANewOrderXTPID(uint64_t session_id)
    {
        return api_->GetANewOrderXTPID(session_id);
    }

    virtual int QueryOrderByXTPID(const uint64_t order_xtp_id, uint64_t session_id, int request_id)
    {
        return api_->QueryOrderByXTPID(order_xtp_id, session_id, request_id);
    }

    virtual int QueryOrders(const XTPQueryOrderReq* query_param, uint64_t session_id, int request_id)
    {
        return api_->QueryOrders(query_param, session_id, request_id);
    }

    virtual int QueryUnfinishedOrders(uint64_t session_id, int request_id)
    {
        return api_->QueryUnfinishedOrders(session_id, request_id);
    }

    virtual int QueryOrdersByPage(const XTPQueryOrderByPageReq* query_param, uint64_t session_id, int request_id)
    {
        return api_->QueryOrdersByPage(query_param, session_id, request_id);
    }

    virtual int QueryOrderByXTPIDEx(const uint64_t order_xtp_id, uint64_t session_id, int request_id)
    {
        return api_->QueryOrderByXTPIDEx(order_xtp_id, session_id, request_id);
    }

    virtual int QueryOrdersEx(const XTPQueryOrderReq* query_param, uint64_t session_id, int request_id)
    {
        return api_->QueryOrdersEx(query_param, session_id, request_id);
    }

    virtual int QueryUnfinishedOrdersEx(uint64_t session_id, int request_id)
    {
        return api_->QueryUnfinishedOrdersEx(session_id, request_id);
    }

    virtual int QueryOrdersByPageEx(const XTPQueryOrderByPageReq* query_param, uint64_t session_id, int request_id)
    {
        return api_->QueryOrdersByPageEx(query_param, session_id, request_id);
    }

    virtual int QueryTradesByXTPID(const uint64_t order_xtp_id, uint64_t session_id, int request_id)
    {
        return api_->QueryTradesByXTPID(order_xtp_id, session_id, request_id);
    }

    virtual int QueryTrades(XTPQueryTraderReq* query_param, uint64_t session_id, int request_id)
    {
        return api_->QueryTrades(query_param, session_id, request_id);
    }

    virtual int QueryTradesByPage(const XTPQueryTraderByPageReq* query_param, uint64_t session_id, int request_id)
    {
        return api_->QueryTradesByPage(query_param, session_id, request_id);
    }

    virtual int QueryPosition(const char* ticker, uint64_t session_id, int request_id, XTP_MARKET_TYPE market = XTP_MKT_INIT)
    {
        return api_->QueryPosition(ticker, session_id, request_id, market);
    }

    virtual int QueryAsset(uint64_t session_id, int request_id)
    {
        return api_->QueryAsset(session_id, request_id);
    }

    virtual int QueryStructuredFund(XTPQueryStructuredFundInfoReq* query_param, uint64_t session_id, int request_id)
    {
        return api_->QueryStructuredFund(query_param, session_id, request_id);
    }

    virtual int QueryFundTransfer(XTPQueryFundTransferLogReq* query_param, uint64_t session_id, int request_id)
    {
        return api_->QueryFundTransfer(query_param, session_id, request_id);
    }

    virtual int QueryOtherServerFund(XTPFundQueryReq* query_param, uint64_t session_id, int request_id)
    {
        return api_->QueryOtherServerFund(query_param, session_id, request_id);
    }

    virtual int QueryETF(XTPQueryETFBaseReq* query_param, uint64_t session_id, int request_id)
    {
        return api_->QueryETF(query_param, session_id, request_id);
    }

    virtual int QueryETFTickerBasket(XTPQueryETFComponentReq* query_param, uint64_t session_id, int request_id)
    {
        return api_->QueryETFTickerBasket(query_param, session_id, request_id);
    }

    virtual int QueryIPOInfoList(uint64_t session_id, int request_id)
    {
        return api_->QueryIPOInfoList(session_id,  request_id);
    }

    virtual int QueryIPOQuotaInfo(uint64_t session_id, int request_id)
    {
        return api_->QueryIPOQuotaInfo(session_id, request_id);
    }

    virtual int QueryOptionAuctionInfo(XTPQueryOptionAuctionInfoReq* query_param, uint64_t session_id, int request_id)
    {
        return api_->QueryOptionAuctionInfo(query_param, session_id, request_id);
    }

    virtual int QueryCreditCashRepayInfo(uint64_t session_id, int request_id)
    {
        return api_->QueryCreditCashRepayInfo(session_id, request_id);
    }

    virtual int QueryCreditFundInfo(uint64_t session_id, int request_id)
    {
        return api_->QueryCreditFundInfo(session_id, request_id);
    }

    virtual int QueryCreditDebtInfo(uint64_t session_id, int request_id)
    {
        return api_->QueryCreditDebtInfo(session_id, request_id);
    }

    virtual int QueryCreditTickerDebtInfo(XTPClientQueryCrdDebtStockReq* query_param, uint64_t session_id, int request_id)
    {
        return api_->QueryCreditTickerDebtInfo(query_param, session_id,  request_id);
    }

    virtual int QueryCreditAssetDebtInfo(uint64_t session_id, int request_id)
    {
        return api_->QueryCreditAssetDebtInfo(session_id, request_id);
    }

    virtual int QueryCreditTickerAssignInfo(XTPClientQueryCrdPositionStockReq* query_param, uint64_t session_id, int request_id)
    {
        return api_->QueryCreditTickerAssignInfo(query_param, session_id, request_id);
    }

    virtual int QueryCreditExcessStock(XTPClientQueryCrdSurplusStkReqInfo* query_param, uint64_t session_id, int request_id)
    {
        return api_->QueryCreditExcessStock(query_param, session_id, request_id);
    }

    virtual int QueryMulCreditExcessStock(XTPClientQueryCrdSurplusStkReqInfo* query_param, uint64_t session_id, int request_id)
    {
        return api_->QueryMulCreditExcessStock(query_param, session_id, request_id);
    }

    virtual uint64_t CreditExtendDebtDate(XTPCreditDebtExtendReq* debt_extend, uint64_t session_id)
    {
        return api_->CreditExtendDebtDate(debt_extend, session_id);
    }

    virtual int QueryCreditExtendDebtDateOrders(uint64_t xtp_id, uint64_t session_id, int request_id)
    {
        return api_->QueryCreditExtendDebtDateOrders(xtp_id, session_id, request_id);
    }

    virtual int QueryCreditFundExtraInfo(uint64_t session_id, int request_id)
    {
        return api_->QueryCreditFundExtraInfo(session_id, request_id);
    }

    virtual int QueryCreditPositionExtraInfo(XTPClientQueryCrdPositionStockReq* query_param, uint64_t session_id, int request_id)
    {
        return api_->QueryCreditPositionExtraInfo(query_param, session_id, request_id);
    }

    virtual int QueryOptionCombinedUnfinishedOrders(uint64_t session_id, int request_id)
    {
        return api_->QueryOptionCombinedUnfinishedOrders(session_id, request_id);
    }

    virtual int QueryOptionCombinedOrderByXTPID(const uint64_t order_xtp_id, uint64_t session_id, int request_id)
    {
        return api_->QueryOptionCombinedOrderByXTPID(order_xtp_id, session_id, request_id);
    }

    virtual int QueryOptionCombinedOrders(const XTPQueryOptCombOrderReq* query_param, uint64_t session_id, int request_id)
    {
        return api_->QueryOptionCombinedOrders(query_param, session_id, request_id);
    }

    virtual int QueryOptionCombinedOrdersByPage(const XTPQueryOptCombOrderByPageReq* query_param, uint64_t session_id, int request_id)
    {
        return api_->QueryOptionCombinedOrdersByPage(query_param, session_id, request_id);
    }

    virtual int QueryOptionCombinedUnfinishedOrdersEx(uint64_t session_id, int request_id)
    {
        return api_->QueryOptionCombinedUnfinishedOrdersEx(session_id, request_id);
    }

    virtual int QueryOptionCombinedOrderByXTPIDEx(const uint64_t order_xtp_id, uint64_t session_id, int request_id)
    {
        return api_->QueryOptionCombinedOrderByXTPIDEx(order_xtp_id, session_id, request_id);
    }

    virtual int QueryOptionCombinedOrdersEx(const XTPQueryOptCombOrderReq* query_param, uint64_t session_id, int request_id)
    {
        return api_->QueryOptionCombinedOrdersEx(query_param, session_id, request_id);
    }

    virtual int QueryOptionCombinedOrdersByPageEx(const XTPQueryOptCombOrderByPageReq* query_param, uint64_t session_id, int request_id)
    {
        return api_->QueryOptionCombinedOrdersByPageEx(query_param, session_id, request_id);
    }

    virtual int QueryOptionCombinedTradesByXTPID(const uint64_t order_xtp_id, uint64_t session_id, int request_id)
    {
        return api_->QueryOptionCombinedTradesByXTPID(order_xtp_id, session_id, request_id);
    }

    virtual int QueryOptionCombinedTrades(const XTPQueryOptCombTraderReq* query_param, uint64_t session_id, int request_id)
    {
        return api_->QueryOptionCombinedTrades(query_param, session_id, request_id);
    }

    virtual int QueryOptionCombinedTradesByPage(const XTPQueryOptCombTraderByPageReq* query_param, uint64_t session_id, int request_id)
    {
        return api_->QueryOptionCombinedTradesByPage(query_param, session_id, request_id);
    }

    virtual int QueryOptionCombinedPosition(const XTPQueryOptCombPositionReq* query_param, uint64_t session_id, int request_id)
    {
        return api_->QueryOptionCombinedPosition(query_param, session_id, request_id);
    }

    virtual int QueryOptionCombinedStrategyInfo(uint64_t session_id, int request_id)
    {
        return api_->QueryOptionCombinedStrategyInfo(session_id, request_id);
    }

    virtual int QueryOptionCombinedExecPosition(const XTPQueryOptCombExecPosReq* query_param, uint64_t session_id, int request_id)
    {
        return api_->QueryOptionCombinedExecPosition(query_param, session_id, request_id);
    }

    virtual int QueryStrategy(uint32_t strategy_type, uint64_t client_strategy_id, uint64_t xtp_strategy_id, uint64_t session_id, int32_t request_id)
    {
        return api_->QueryStrategy(strategy_type, client_strategy_id, xtp_strategy_id, session_id, request_id);
    }

    virtual uint64_t GetAlgorithmIDByOrder(uint64_t order_xtp_id, uint32_t order_client_id)
    {
        return api_->GetAlgorithmIDByOrder(order_xtp_id, order_client_id);
    }

public:
    virtual void OnDisconnected(uint64_t session_id, int reason) {};

    virtual void OnError(XTPRI* error_info) {};

    virtual void OnQueryAccountTradeMarket(int trade_location, XTPRI* error_info, int request_id, uint64_t session_id) {};

    virtual void OnOrderEvent(XTPOrderInfo* order_info, XTPRI* error_info, uint64_t session_id) {};

    virtual void OnTradeEvent(XTPTradeReport* trade_info, uint64_t session_id) {};

    virtual void OnCancelOrderError(XTPOrderCancelInfo* cancel_info, XTPRI* error_info, uint64_t session_id) {};

    virtual void OnQueryOrder(XTPQueryOrderRsp* order_info, XTPRI* error_info, int request_id, bool is_last, uint64_t session_id) {};

    virtual void OnQueryOrderEx(XTPOrderInfoEx* order_info, XTPRI* error_info, int request_id, bool is_last, uint64_t session_id) {};

    virtual void OnQueryOrderByPage(XTPQueryOrderRsp* order_info, int64_t req_count, int64_t order_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) {};

    virtual void OnQueryOrderByPageEx(XTPOrderInfoEx* order_info, int64_t req_count, int64_t order_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) {};

    virtual void OnQueryTrade(XTPQueryTradeRsp* trade_info, XTPRI* error_info, int request_id, bool is_last, uint64_t session_id) {};

    virtual void OnQueryTradeByPage(XTPQueryTradeRsp* trade_info, int64_t req_count, int64_t trade_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) {};

    virtual void OnQueryPosition(XTPQueryStkPositionRsp* position, XTPRI* error_info, int request_id, bool is_last, uint64_t session_id) {};

    virtual void OnQueryAsset(XTPQueryAssetRsp* asset, XTPRI* error_info, int request_id, bool is_last, uint64_t session_id) {};

    virtual void OnQueryStructuredFund(XTPStructuredFundInfo* fund_info, XTPRI* error_info, int request_id, bool is_last, uint64_t session_id) {};

    virtual void OnQueryFundTransfer(XTPFundTransferNotice* fund_transfer_info, XTPRI* error_info, int request_id, bool is_last, uint64_t session_id) {};

    virtual void OnFundTransfer(XTPFundTransferNotice* fund_transfer_info, XTPRI* error_info, uint64_t session_id) {};

    virtual void OnQueryOtherServerFund(XTPFundQueryRsp* fund_info, XTPRI* error_info, int request_id, uint64_t session_id) {};

    virtual void OnQueryETF(XTPQueryETFBaseRsp* etf_info, XTPRI* error_info, int request_id, bool is_last, uint64_t session_id) {};

    virtual void OnQueryETFBasket(XTPQueryETFComponentRsp* etf_component_info, XTPRI* error_info, int request_id, bool is_last, uint64_t session_id) {};

    virtual void OnQueryIPOInfoList(XTPQueryIPOTickerRsp* ipo_info, XTPRI* error_info, int request_id, bool is_last, uint64_t session_id) {};

    virtual void OnQueryIPOQuotaInfo(XTPQueryIPOQuotaRsp* quota_info, XTPRI* error_info, int request_id, bool is_last, uint64_t session_id) {};

    virtual void OnQueryOptionAuctionInfo(XTPQueryOptionAuctionInfoRsp* option_info, XTPRI* error_info, int request_id, bool is_last, uint64_t session_id) {};

    virtual void OnCreditCashRepay(XTPCrdCashRepayRsp* cash_repay_info, XTPRI* error_info, uint64_t session_id) {};

    virtual void OnCreditCashRepayDebtInterestFee(XTPCrdCashRepayDebtInterestFeeRsp* cash_repay_info, XTPRI* error_info, uint64_t session_id) {};

    virtual void OnQueryCreditCashRepayInfo(XTPCrdCashRepayInfo* cash_repay_info, XTPRI* error_info, int request_id, bool is_last, uint64_t session_id) {};

    virtual void OnQueryCreditFundInfo(XTPCrdFundInfo* fund_info, XTPRI* error_info, int request_id, uint64_t session_id) {};

    virtual void OnQueryCreditDebtInfo(XTPCrdDebtInfo* debt_info, XTPRI* error_info, int request_id, bool is_last, uint64_t session_id) {};

    virtual void OnQueryCreditTickerDebtInfo(XTPCrdDebtStockInfo* debt_info, XTPRI* error_info, int request_id, bool is_last, uint64_t session_id) {};

    virtual void OnQueryCreditAssetDebtInfo(double remain_amount, XTPRI* error_info, int request_id, uint64_t session_id) {};

    virtual void OnQueryCreditTickerAssignInfo(XTPClientQueryCrdPositionStkInfo* assign_info, XTPRI* error_info, int request_id, bool is_last, uint64_t session_id) {};

    virtual void OnQueryCreditExcessStock(XTPClientQueryCrdSurplusStkRspInfo* stock_info, XTPRI* error_info, int request_id, uint64_t session_id) {};

    virtual void OnQueryMulCreditExcessStock(XTPClientQueryCrdSurplusStkRspInfo* stock_info, XTPRI* error_info, int request_id, uint64_t session_id, bool is_last) {};

    virtual void OnCreditExtendDebtDate(XTPCreditDebtExtendNotice* debt_extend_info, XTPRI* error_info, uint64_t session_id) {};

    virtual void OnQueryCreditExtendDebtDateOrders(XTPCreditDebtExtendNotice* debt_extend_info, XTPRI* error_info, int request_id, bool is_last, uint64_t session_id) {};

    virtual void OnQueryCreditFundExtraInfo(XTPCrdFundExtraInfo* fund_info, XTPRI* error_info, int request_id, uint64_t session_id) {};

    virtual void OnQueryCreditPositionExtraInfo(XTPCrdPositionExtraInfo* fund_info, XTPRI* error_info, int request_id, bool is_last, uint64_t session_id) {};

    virtual void OnOptionCombinedOrderEvent(XTPOptCombOrderInfo* order_info, XTPRI* error_info, uint64_t session_id) {};

    virtual void OnOptionCombinedTradeEvent(XTPOptCombTradeReport* trade_info, uint64_t session_id) {};

    virtual void OnCancelOptionCombinedOrderError(XTPOptCombOrderCancelInfo* cancel_info, XTPRI* error_info, uint64_t session_id) {};

    virtual void OnQueryOptionCombinedOrders(XTPQueryOptCombOrderRsp* order_info, XTPRI* error_info, int request_id, bool is_last, uint64_t session_id) {};

    virtual void OnQueryOptionCombinedOrdersEx(XTPOptCombOrderInfoEx* order_info, XTPRI* error_info, int request_id, bool is_last, uint64_t session_id) {};

    virtual void OnQueryOptionCombinedOrdersByPage(XTPQueryOptCombOrderRsp* order_info, int64_t req_count, int64_t order_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) {};

    virtual void OnQueryOptionCombinedOrdersByPageEx(XTPOptCombOrderInfoEx* order_info, int64_t req_count, int64_t order_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) {};

    virtual void OnQueryOptionCombinedTrades(XTPQueryOptCombTradeRsp* trade_info, XTPRI* error_info, int request_id, bool is_last, uint64_t session_id) {};

    virtual void OnQueryOptionCombinedTradesByPage(XTPQueryOptCombTradeRsp* trade_info, int64_t req_count, int64_t trade_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) {};

    virtual void OnQueryOptionCombinedPosition(XTPQueryOptCombPositionRsp* position_info, XTPRI* error_info, int request_id, bool is_last, uint64_t session_id) {};

    virtual void OnQueryOptionCombinedStrategyInfo(XTPQueryCombineStrategyInfoRsp* strategy_info, XTPRI* error_info, int request_id, bool is_last, uint64_t session_id) {};

    virtual void OnQueryOptionCombinedExecPosition(XTPQueryOptCombExecPosRsp* position_info, XTPRI* error_info, int request_id, bool is_last, uint64_t session_id) {};

    virtual void OnQueryStrategy(XTPStrategyInfoStruct* strategy_info, char* strategy_param, XTPRI* error_info, int32_t request_id, bool is_last, uint64_t session_id) {};

    virtual void OnStrategyStateReport(XTPStrategyStateReportStruct* strategy_state, uint64_t session_id) {};

    virtual void OnALGOUserEstablishChannel(char* user, XTPRI* error_info, uint64_t session_id) {};

    virtual void OnInsertAlgoOrder(XTPStrategyInfoStruct* strategy_info, XTPRI* error_info, uint64_t session_id) {};

    virtual void OnCancelAlgoOrder(XTPStrategyInfoStruct* strategy_info, XTPRI* error_info, uint64_t session_id) {};

    virtual void OnAlgoDisconnected(int reason) {};

    virtual void OnAlgoConnected() {};

    virtual void OnStrategySymbolStateReport(XTPStrategySymbolStateReport* strategy_symbol_state, uint64_t session_id) {};

private:
    XTP::API::TraderApi* api_;
};

}
}

#endif