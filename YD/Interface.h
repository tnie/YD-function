#pragma once
#include <functional>
#include <vector>
#include "common.h"


using YDDATA2CALLBACK1 = std::function<void(QID qid, CBD cbd, int period, const std::vector<Dyna> data)>;

QID YDdata_subscribeDynaWithOrder(const char *code, YDDATA2CALLBACK1& cb, const char* order = nullptr, bool desc = false);



