#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H

#include "base58.h"
#include "json/json_spirit_value.h"

class Distribution
{
protected:
    CBitcoinAddress addrShares;
    int64_t nBalance;

    CCoinAddress addrCoin;
    double dDividendAmount;

public:
    Distribution(CBitcoinAddress addrShares, int64_t nBalance, double dDividendAmount, unsigned char pubKeyAddress, unsigned char scriptAddress)
        : addrShares(addrShares), nBalance(nBalance), addrCoin(addrShares, pubKeyAddress, scriptAddress), dDividendAmount(dDividendAmount)
    {
    }

    const CBitcoinAddress GetShareAddress() const
    {
        return addrShares;
    }

    int64_t GetBalance() const
    {
        return nBalance;
    }

    const CCoinAddress GetCoinAddress() const
    {
        return addrCoin;
    }

    double GetDividendAmount() const
    {
        return dDividendAmount;
    }
};

typedef std::map<const CBitcoinAddress, int64_t> BalanceMap;
typedef std::vector<Distribution> DistributionVector;

class DividendDistributor
{
protected:
    BalanceMap mapBalance;
    double dTotalDistributed;
    unsigned char pubKeyAddress;
    unsigned char scriptAddress;

    DistributionVector vDistribution;

public:
    DividendDistributor(unsigned char pubKeyAddress, unsigned char scriptAddress) : mapBalance(), dTotalDistributed(0), pubKeyAddress(pubKeyAddress), scriptAddress(scriptAddress)
    {
    }

    DividendDistributor(const BalanceMap& mapBalance, unsigned char pubKeyAddress, unsigned char scriptAddress) : mapBalance(mapBalance), dTotalDistributed(0), pubKeyAddress(pubKeyAddress), scriptAddress(scriptAddress)
    {
    }

    void SetBalanceMap(const BalanceMap &mapBalance)
    {
        this->mapBalance = mapBalance;
    }

    void Distribute(double dDistributedAmount, double dMinimumPayout);
    void GenerateOutputs(int nTransactions, std::vector<json_spirit::Object> &vTransactionOuts) const;

    int GetTransactionCount(int nMaxDistributionPerTransaction) const;

    const DistributionVector& GetDistributions() const
    {
        return vDistribution;
    }

    int DistributionCount() const
    {
        return vDistribution.size();
    }

    const Distribution& GetDistribution(const CBitcoinAddress& addrShare) const
    {
        for (DistributionVector::const_iterator it = vDistribution.begin(); it != vDistribution.end(); ++it)
        {
            if (it->GetShareAddress() == addrShare)
                return *it;
        }
        throw std::runtime_error("Distribution not found");
    }

    double TotalDistributed() const
    {
        return dTotalDistributed;
    }
};

DividendDistributor GenerateDistribution(const BalanceMap &mapBalance, double dAmount, unsigned char pubKeyAddress, unsigned char scriptAddress);
json_spirit::Array SendDistribution(const DividendDistributor &distributor);
double GetMinimumDividendPayout();
int GetMaximumDistributionPerTransaction();
double GetDistributionBalance();

#endif
