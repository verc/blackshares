#ifndef SCANBALANCE_H
#define SCANBALANCE_H

#include "distribution.h"

void GetAddressBalances(unsigned int cutoffTime, BalanceMap& mapBalance);
bool ExtractAddresses(const CScript& scriptPubKey, txnouttype& typeRet, vector<CBitcoinAddress>& addressRet, int& nRequiredRet);
bool ExtractAddress(const CScript& scriptPubKey, CBitcoinAddress& addressRet);

#endif
