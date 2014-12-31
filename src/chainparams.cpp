// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"
#include "time.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"
#include "shareparams.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams(bool fSearchGenesis = true) {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x70;
        pchMessageStart[1] = 0x35;
        pchMessageStart[2] = 0x22;
        pchMessageStart[3] = 0x05;
        vAlertPubKey = ParseHex("0486bce1bac0d543f104cbff2bd23680056a3b9ea05e1137d2ff90eeb5e08472eb500322593a2cb06fbf8297d7beb6cd30cb90f98153b5b7cce1493749e41e0284");
        nDefaultPort = SHARE_DEFAULT_PORT;
        nRPCPort = SHARE_RPC_PORT;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);
        
        const char* pszTimestamp = SHARE_GENESIS_MESSAGE;
        CTransaction txNew;
        txNew.nTime = SHARE_GENESIS_TIMESTEMP;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].SetEmpty();
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = SHARE_GENESIS_TIMESTEMP;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = SHARE_GENESIS_NONCE;
        hashGenesisBlock = genesis.GetHash();

        if (fSearchGenesis && hashGenesisBlock != uint256(SHARE_GENESIS_HASH)) {
            printf("// MainNet Genesis Block\n");
            time_t curtime = time (NULL);
            genesis.nTime = curtime;
            genesis.vtx[0].nTime = curtime;
            genesis.hashMerkleRoot = genesis.BuildMerkleTree();
            FindGenesisBlock();
            printf("#define SHARE_GENESIS_TIMESTEMP %d\n", (int)curtime);
            printf("#define SHARE_GENESIS_NONCE %d\n", genesis.nNonce);
            printf("#define SHARE_GENESIS_HASH \"0x%s\"\n", genesis.GetHash().ToString().c_str());
            printf("#define SHARE_MERKLE_ROOT \"0x%s\"\n", genesis.hashMerkleRoot.ToString().c_str());
        }

        assert(!STRICT_CHECK || hashGenesisBlock == uint256(SHARE_GENESIS_HASH));
        assert(!STRICT_CHECK || genesis.hashMerkleRoot == uint256(SHARE_MERKLE_ROOT));

        base58Prefixes[PUBKEY_ADDRESS] = list_of(SHARE_PUBKEY_ADDRESS_PREFIX);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(SHARE_SCRIPT_ADDRESS_PREFIX);
        base58Prefixes[SECRET_KEY] =     list_of(SHARE_SECRET_KEY_PREFIX);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4);

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }

protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;

    void FindGenesisBlock() {
        CBigNum bnTarget;
        bnTarget.SetCompact(genesis.nBits);
        genesis.nNonce = 0;

        while (genesis.GetHash() > bnTarget.getuint256()) {
            genesis.nNonce++;
        }
    }
};
static CMainParams mainParams;

class CTestNetParams : public CMainParams {
public:
    CTestNetParams(bool fSearchGenesis = true) : CMainParams(false) {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xcd;
        pchMessageStart[1] = 0xf2;
        pchMessageStart[2] = 0xc0;
        pchMessageStart[3] = 0xef;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("0471dc165db490094d35cde15b1f5d755fa6ad6f2b5ed0f340e3f17f57389c3c2af113a8cbcc885bde73305a553b5640c83021128008ddf882e856336269080496");
        nDefaultPort = SHARE_DEFAULT_PORT;
        nRPCPort = SHARE_RPC_PORT;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = SHARE_TEST_GENESIS_NONCE;

        hashGenesisBlock = genesis.GetHash();
        if (fSearchGenesis && hashGenesisBlock != uint256(SHARE_TEST_GENESIS_HASH)) {
            printf("// TestNet Genesis Block\n");
            FindGenesisBlock();
            printf("#define SHARE_TEST_GENESIS_NONCE %d\n", genesis.nNonce);
            printf("#define SHARE_TEST_GENESIS_HASH \"0x%s\"\n", genesis.GetHash().ToString().c_str());
        }
        assert(!STRICT_CHECK || hashGenesisBlock == uint256(SHARE_TEST_GENESIS_HASH));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = list_of(SHARE_TEST_PUBKEY_ADDRESS_PREFIX);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(SHARE_TEST_SCRIPT_ADDRESS_PREFIX);
        base58Prefixes[SECRET_KEY]     = list_of(SHARE_TEST_SECRET_KEY_PREFIX);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94);

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;

//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() : CTestNetParams(false) {
        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0xbf;
        pchMessageStart[2] = 0xb5;
        pchMessageStart[3] = 0xda;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1411111111;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = SHARE_REGRESSION_GENESIS_NONCE;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = SHARE_REGRESSION_PORT;
        strDataDir = "regtest";
        if (hashGenesisBlock != uint256(SHARE_REGRESSION_GENESIS_HASH)) {
            printf("// Regression Genesis Block\n");
            genesis.nBits  = bnProofOfWorkLimit.GetCompact();
            FindGenesisBlock();
            printf("#define SHARE_REGRESSION_GENESIS_NONCE %d\n", genesis.nNonce);
            printf("#define SHARE_REGRESSION_GENESIS_HASH \"0x%s\"\n", genesis.GetHash().ToString().c_str());
        }
        assert(!STRICT_CHECK || hashGenesisBlock == uint256(SHARE_REGRESSION_GENESIS_HASH));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

//
// BlackCoin network
//

class CMainCoinParams : public CMainParams {
public:
    CMainCoinParams() : CMainParams(false) {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x70;
        pchMessageStart[1] = 0x35;
        pchMessageStart[2] = 0x22;
        pchMessageStart[3] = 0x05;
        vAlertPubKey = ParseHex("0486bce1bac0d543f104cbff2bd23680056a3b9ea05e1137d2ff90eeb5e08472eb500322593a2cb06fbf8297d7beb6cd30cb90f98153b5b7cce1493749e41e0284");
        nDefaultPort = 15714;
        nRPCPort = 15715;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        //
        //CBlock(hash=000001faef25dec4fbcf906e6242621df2c183bf232f263d0ba5b101911e4563, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=12630d16a97f24b287c8c2594dda5fb98c9e6c70fc61d44191931ea2aa08dc90, nTime=1393221600, nBits=1e0fffff, nNonce=164482, vtx=1, vchBlockSig=)
        //  Coinbase(hash=12630d16a9, nTime=1393221600, ver=1, vin.size=1, vout.size=1, nLockTime=0)
        //    CTxIn(COutPoint(0000000000, 4294967295), coinbase 00012a24323020466562203230313420426974636f696e2041544d7320636f6d6520746f20555341)
        //    CTxOut(empty)
        //  vMerkleTree: 12630d16a9
        const char* pszTimestamp = "20 Feb 2014 Bitcoin ATMs come to USA";
        CTransaction txNew;
        txNew.nTime = 1393221600;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].SetEmpty();
        genesis.vtx.clear();
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1393221600;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 164482;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000001faef25dec4fbcf906e6242621df2c183bf232f263d0ba5b101911e4563"));
        assert(genesis.hashMerkleRoot == uint256("0x12630d16a97f24b287c8c2594dda5fb98c9e6c70fc61d44191931ea2aa08dc90"));

        vSeeds.push_back(CDNSSeedData("rat4.blackcoin.co", "seed.blackcoin.co"));
        vSeeds.push_back(CDNSSeedData("archon.darkfox.id.au", "foxy.seeds.darkfox.id.au"));
        vSeeds.push_back(CDNSSeedData("6.syllabear.us.to", "bcseed.syllabear.us.to"));

        base58Prefixes[PUBKEY_ADDRESS] = list_of(25);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(85);
        base58Prefixes[SECRET_KEY] =     list_of(153);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4);

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));
    }
    virtual Network NetworkID() const { return CChainParams::MAIN; }
};
static CMainCoinParams mainCoinParams;

//
// Testnet
//

class CTestNetCoinParams : public CMainCoinParams {
public:
    CTestNetCoinParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xcd;
        pchMessageStart[1] = 0xf2;
        pchMessageStart[2] = 0xc0;
        pchMessageStart[3] = 0xef;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("0471dc165db490094d35cde15b1f5d755fa6ad6f2b5ed0f340e3f17f57389c3c2af113a8cbcc885bde73305a553b5640c83021128008ddf882e856336269080496");
        nDefaultPort = 25714;
        nRPCPort = 25715;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 216178;
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000724595fb3b9609d441cbfb9577615c292abf07d996d3edabc48de843642d"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = list_of(111);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(196);
        base58Prefixes[SECRET_KEY]     = list_of(239);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94);

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetCoinParams testNetCoinParams;

static CChainParams *pCurrentParams = &mainParams;
static CChainParams *pCurrentCoinParams = &mainCoinParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

const CChainParams &CoinParams() {
    return *pCurrentCoinParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            pCurrentCoinParams = &mainCoinParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            pCurrentCoinParams = &testNetCoinParams;
            //pCurrentCoinParams = &mainCoinParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
