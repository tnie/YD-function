#pragma once
#include "common.h"
#include <memory>
// deprecated
class Quote_recv_callback
{
public:
    virtual void callback(QID qid, CBD cbd, int period, const void* dataptr, size_t size);
    // ÎªÁË¼æÈÝ
    void callback2(QID qid, CBD cbd, int period, const std::shared_ptr<Dyna> data);
    virtual ~Quote_recv_callback() = default;
};

typedef std::weak_ptr<Quote_recv_callback>          QUOTE_RECV_CALLBACK_PTR;

QID YDdata_subscribeDynaWithOrder(const char *code, QUOTE_RECV_CALLBACK_PTR cb, const char* order = nullptr, bool desc = false);