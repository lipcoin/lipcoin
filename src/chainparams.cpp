// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The LipCoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "arith_uint256.h"
#include "chainparams.h"
#include "consensus/merkle.h"

#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

#include "chainparamsseeds.h"

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = 200;
    txNew.vout[0].scriptPubKey = CScript() << ParseHex("194630194fd114ba2020490c26b3a49c8f13f8d45b8c857fbcbb8bc4a8e4d3eb4c10f3d4618ff08dce601bbf0f470216ae1b51850b4bcf21b179c48304ac7b03a1") << OP_CHECKSIG;
    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "LIPCOIN NETWORK";
    const CScript genesisOutputScript = CScript() << ParseHex("194630194fd114ba2020490c26b3a49c8f13f8d45b8c857fbcbb8bc4a8e4d3eb4c10f3d4618ff08dce601bbf0f470216ae1b51850b4bcf21b179c48304ac7b03a1") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}
class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nSubsidyHalvingInterval = 150000;
        consensus.powLimit = ArithToUint256(~arith_uint256(0) >> 20);
        consensus.nPowTargetTimespan = 7 * 24 * 60 * 60; // 1 week
        consensus.nPowTargetSpacing = 120 / 4;
        consensus.nTargetTimespan =  0.10 * 24 * 60 * 60; // 2.4 hours
        consensus.nTargetSpacing = 90; // 90 seconds
        consensus.nInterval = consensus.nTargetTimespan / consensus.nTargetSpacing;
        consensus.nDiffChangeTarget = 0;
        consensus.patchBlockRewardDuration = 10080;
        consensus.patchBlockRewardDuration2 = 10080;
        consensus.nTargetTimespanRe = 1*90; // 90 Seconds
        consensus.nTargetSpacingRe = 1*90; // 90 seconds
        consensus.nIntervalRe = consensus.nTargetTimespanRe / consensus.nTargetSpacingRe; // 1 block
        consensus.nAveragingInterval = 10; // 10 blocks
        consensus.multiAlgoTargetSpacing = 90*5; // NUM_ALGOS * 90 seconds
        consensus.multiAlgoTargetSpacingV4 = 90*5; // NUM_ALGOS * 90 seconds
        consensus.nAveragingTargetTimespan = consensus.nAveragingInterval * consensus.multiAlgoTargetSpacing; // 10* NUM_ALGOS * 90
        consensus.nAveragingTargetTimespanV4 = consensus.nAveragingInterval * consensus.multiAlgoTargetSpacingV4; // 10 * NUM_ALGOS * 90

        consensus.nMaxAdjustDown = 40; // 40% adjustment down
        consensus.nMaxAdjustUp = 20; // 20% adjustment up
        consensus.nMaxAdjustDownV3 = 16; // 16% adjustment down
        consensus.nMaxAdjustUpV3 = 8; // 8% adjustment up
        consensus.nMaxAdjustDownV4 = 16;
        consensus.nMaxAdjustUpV4 = 8;

        consensus.nMinActualTimespan = consensus.nAveragingTargetTimespan * (100 - consensus.nMaxAdjustUp) / 100;
        consensus.nMaxActualTimespan = consensus.nAveragingTargetTimespan * (100 + consensus.nMaxAdjustDown) / 100;
        consensus.nMinActualTimespanV3 = consensus.nAveragingTargetTimespan * (100 - consensus.nMaxAdjustUpV3) / 100;
        consensus.nMaxActualTimespanV3 = consensus.nAveragingTargetTimespan * (100 + consensus.nMaxAdjustDownV3) / 100;
        consensus.nMinActualTimespanV4 = consensus.nAveragingTargetTimespanV4 * (100 - consensus.nMaxAdjustUpV4) / 100;
        consensus.nMaxActualTimespanV4 = consensus.nAveragingTargetTimespanV4 * (100 + consensus.nMaxAdjustDownV4) / 100;

        consensus.nLocalTargetAdjustment = 4; //target adjustment per algo
        consensus.nLocalDifficultyAdjustment = 4; //difficulty adjustment per algo


        // LipCoin Hard Fork Block Heights
        consensus.multiAlgoDiffChangeTarget = 0;
        consensus.alwaysUpdateDiffChangeTarget = 0;
        consensus.workComputationChangeTarget = 0;
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 14112; // 14112 - 70% of 20160
        consensus.nMinerConfirmationWindow = 20160; // nPowTargetTimespan / nPowTargetSpacing 20160 main net - 1 week
        consensus.fRbfEnabled = false;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 27; //Add VERSIONBITS_NUM_BITS_TO_SKIP (12)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008
        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 12; //Add VERSIONBITS_NUM_BITS_TO_SKIP (12)
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1489997089; // March 24th, 2017 1490355345
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1521891345; // March 24th, 2018
        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 13; //Add VERSIONBITS_NUM_BITS_TO_SKIP (12)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1490355345; // March 24th, 2017 1490355345
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1521891345; // March 24th, 2018
        // Deployment of BIP65, BIP66, and BIP34.
        consensus.vDeployments[Consensus::DEPLOYMENT_NVERSIONBIPS].bit = 14; //Add VERSIONBITS_NUM_BITS_TO_SKIP (12)
        consensus.vDeployments[Consensus::DEPLOYMENT_NVERSIONBIPS].nStartTime = 1489997089; // March 24th, 2017 1490355345
        consensus.vDeployments[Consensus::DEPLOYMENT_NVERSIONBIPS].nTimeout = 1521891345;    // March 24th, 2018
        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");
        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0xc5822aca65f20102d785534aa734224ed0095ccb2b042a4a65f70bdddfabe5d4");
        pchMessageStart[0] = 0xbd;
        pchMessageStart[1] = 0xf4;
        pchMessageStart[2] = 0xd3;
        pchMessageStart[3] = 0xbf;
        nDefaultPort = 9329;
        nPruneAfterHeight = 100000;

        genesis = CreateGenesisBlock(1521095426, 17456, 0x1e0ffff0, 1, 200);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0xc5822aca65f20102d785534aa734224ed0095ccb2b042a4a65f70bdddfabe5d4"));
        assert(genesis.hashMerkleRoot == uint256S("0x79d2eb0cb26818c63e9826f0ab2e10118ceda7735528af1c95bc211dae947ea2"));

	vSeeds.push_back(CDNSSeedData("pool.lipcoins.org", "pool.lipcoins.org"));
        vSeeds.push_back(CDNSSeedData("node.lipcoins.org", "node.lipcoins.org"));
        vSeeds.push_back(CDNSSeedData("dnsseed.lipcoins.org", "dnsseed.lipcoins.org"));
	vSeeds.push_back(CDNSSeedData("lipcoin.network", "lipcoin.network"));
	base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,56);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,5);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,176);
        base58Prefixes[SECRET_KEY_OLD] = std::vector<unsigned char>(1,128);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            (     0, uint256S("0xc5822aca65f20102d785534aa734224ed0095ccb2b042a4a65f70bdddfabe5d4"))
        };

        chainTxData = ChainTxData{
            1521095426, // * UNIX timestamp of last known number of transactions
            1,  // * total number of transactions between genesis and that timestamp
               //   (the tx=... number in the SetBestChain debug.log lines)
            1  // * estimated number of transactions per second after that timestamp
        };
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 150000;
        consensus.powLimit = uint256S("00000000ffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 7 * 24 * 60 * 60; // 1 week
        consensus.nPowTargetSpacing = 120 / 4;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 15120; // 75% for testchains
        consensus.nMinerConfirmationWindow = 20160; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1456790400; // March 1st, 2016
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1493596800; // May 1st, 2017

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1462060800; // May 1st 2016
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1493596800; // May 1st 2017

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00000000000000000000000000000000000000000000001f057509eba81aed91");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x51389b520cb075395dccbb29f3980ed854137c45ffeba6b48174cbfb7e039515");

        pchMessageStart[0] = 0xc3;
        pchMessageStart[1] = 0xb4;
        pchMessageStart[2] = 0xc1;
        pchMessageStart[3] = 0xfc;
        nDefaultPort = 19329;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1521096026, 46103, 0x1e0ffff0, 1, 200);
        consensus.hashGenesisBlock = genesis.GetHash();
	assert(consensus.hashGenesisBlock == uint256S("0x51389b520cb075395dccbb29f3980ed854137c45ffeba6b48174cbfb7e039515"));
        assert(genesis.hashMerkleRoot == uint256S("0x79d2eb0cb26818c63e9826f0ab2e10118ceda7735528af1c95bc211dae947ea2"));
        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
	vSeeds.push_back(CDNSSeedData("testnet-seed.lipcoins.org", "testnet-seed.lipcoins.org"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;


        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            ( 0, uint256S("0x51389b520cb075395dccbb29f3980ed854137c45ffeba6b48174cbfb7e039515")),
        };

        chainTxData = ChainTxData{
            1521096026,
            1,
            1
        };

    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = 150;
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 14 * 24 * 60 * 60; // two weeks
        consensus.nPowTargetSpacing = 10 * 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 999999999999ULL;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");
        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");
        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0xbf;
        pchMessageStart[2] = 0xb5;
        pchMessageStart[3] = 0xda;
        nDefaultPort = 19330;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1521099033, 1027312, 0x1e0ffff0, 1, 200);
        consensus.hashGenesisBlock = genesis.GetHash();
        vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;

        checkpointData = (CCheckpointData){
            boost::assign::map_list_of
            ( 0, uint256S("0x3d6eb721821e32716ad2a9e86fb2c203aa5c61887dcdfaf528a72735efa3e944"))
        };

        chainTxData = ChainTxData{
            0,
            0,
            0
        };

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
    }

    void UpdateBIP9Parameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
    {
        consensus.vDeployments[d].nStartTime = nStartTime;
        consensus.vDeployments[d].nTimeout = nTimeout;
    }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = 0;

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
            return mainParams;
    else if (chain == CBaseChainParams::TESTNET)
            return testNetParams;
    else if (chain == CBaseChainParams::REGTEST)
            return regTestParams;
    else
        throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

void UpdateRegtestBIP9Parameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    regTestParams.UpdateBIP9Parameters(d, nStartTime, nTimeout);
}
 
