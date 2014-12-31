/* Begin required definitions */

// Number of blocks in PoW phase
#define LAST_POW_BLOCK 10000
// Block reward per block
#define POW_BLOCK_REWARD 10000
// Reward per coin per year in satoschis
#define COIN_YEAR_REWARD 1000000 // 1% per year

// Port for network communication
#define SHARE_DEFAULT_PORT 96342
#define SHARE_RPC_PORT 96343
#define SHARE_REGRESSION_PORT 18444

// Key prefixes in base58 encoding
#define SHARE_PUBKEY_ADDRESS_PREFIX 36
#define SHARE_SCRIPT_ADDRESS_PREFIX 96
#define SHARE_SECRET_KEY_PREFIX 164

// TestNet Key prefixes in base58 encoding
#define SHARE_TEST_PUBKEY_ADDRESS_PREFIX 112
#define SHARE_TEST_SCRIPT_ADDRESS_PREFIX 197
#define SHARE_TEST_SECRET_KEY_PREFIX 240

// Change message in order to trigger genesis block generation
#define SHARE_GENESIS_MESSAGE "December 30 2014: Bitcoin Donations Can Now Fund Mine-Detecting 'Super Rats'"

// Set to false only while generating automatic definitions
#define STRICT_CHECK true

/* End required definitions */


/* Begin automatically generated definitions */
// MainNet Genesis Block
#define SHARE_GENESIS_TIMESTEMP 1419999841
#define SHARE_GENESIS_NONCE 97050
#define SHARE_GENESIS_HASH "0x0000044322572342c3f9d90682ce133d7ec6262a0f8e0edfe541aff717ff1d5f"
#define SHARE_MERKLE_ROOT "0xa2487e2208c6778aca91f9e4946221741d4de2ec34963f863ff0723d7f752446"
// TestNet Genesis Block
#define SHARE_TEST_GENESIS_NONCE 33509
#define SHARE_TEST_GENESIS_HASH "0x0000d8934b5ce6b3090cea849af3594e0a382e360b307578e23ddac59ecd4506"
// Regression Genesis Block
#define SHARE_REGRESSION_GENESIS_NONCE 0
#define SHARE_REGRESSION_GENESIS_HASH "0x3ffbc41eeabaa58cb952be5b4387874eca5e5db4e60535e2d55c221574dc0098"
/* End automatically generated definitions */