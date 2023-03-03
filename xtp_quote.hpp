#ifndef XTP_QUOTE_HPP
#define XTP_QUOTE_HPP

#include "xtp_quote_api.h"

namespace broker
{
namespace xtp
{

class Quote : public XTP::API::QuoteSpi
{

private:
    uint32_t heartbeat_interval_sec_ = 1;
    bool tcp_only_ = false;
};

}
}

#endif