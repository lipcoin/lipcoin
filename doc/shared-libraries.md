Shared Libraries
================

## lipcoinconsensus

The purpose of this library is to make the verification functionality that is critical to LipCoin's consensus available to other applications, e.g. to language bindings.

### API

The interface is defined in the C header `lipcoinconsensus.h` located in  `src/script/lipcoinconsensus.h`.

#### Version

`lipcoinconsensus_version` returns an `unsigned int` with the API version *(currently at an experimental `0`)*.

#### Script Validation

`lipcoinconsensus_verify_script` returns an `int` with the status of the verification. It will be `1` if the input script correctly spends the previous output `scriptPubKey`.

##### Parameters
- `const unsigned char *scriptPubKey` - The previous output script that encumbers spending.
- `unsigned int scriptPubKeyLen` - The number of bytes for the `scriptPubKey`.
- `const unsigned char *txTo` - The transaction with the input that is spending the previous output.
- `unsigned int txToLen` - The number of bytes for the `txTo`.
- `unsigned int nIn` - The index of the input in `txTo` that spends the `scriptPubKey`.
- `unsigned int flags` - The script validation flags *(see below)*.
- `lipcoinconsensus_error* err` - Will have the error/success code for the operation *(see below)*.

##### Script Flags
- `lipcoinconsensus_SCRIPT_FLAGS_VERIFY_NONE`
- `lipcoinconsensus_SCRIPT_FLAGS_VERIFY_P2SH` - Evaluate P2SH ([BIP16](https://github.com/lipcoin/bips/blob/master/bip-0016.mediawiki)) subscripts
- `lipcoinconsensus_SCRIPT_FLAGS_VERIFY_DERSIG` - Enforce strict DER ([BIP66](https://github.com/lipcoin/bips/blob/master/bip-0066.mediawiki)) compliance
- `lipcoinconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY` - Enforce NULLDUMMY ([BIP147](https://github.com/lipcoin/bips/blob/master/bip-0147.mediawiki))
- `lipcoinconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY` - Enable CHECKLOCKTIMEVERIFY ([BIP65](https://github.com/lipcoin/bips/blob/master/bip-0065.mediawiki))
- `lipcoinconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY` - Enable CHECKSEQUENCEVERIFY ([BIP112](https://github.com/lipcoin/bips/blob/master/bip-0112.mediawiki))
- `lipcoinconsensus_SCRIPT_FLAGS_VERIFY_WITNESS` - Enable WITNESS ([BIP141](https://github.com/lipcoin/bips/blob/master/bip-0141.mediawiki))

##### Errors
- `lipcoinconsensus_ERR_OK` - No errors with input parameters *(see the return value of `lipcoinconsensus_verify_script` for the verification status)*
- `lipcoinconsensus_ERR_TX_INDEX` - An invalid index for `txTo`
- `lipcoinconsensus_ERR_TX_SIZE_MISMATCH` - `txToLen` did not match with the size of `txTo`
- `lipcoinconsensus_ERR_DESERIALIZE` - An error deserializing `txTo`
- `lipcoinconsensus_ERR_AMOUNT_REQUIRED` - Input amount is required if WITNESS is used

### Example Implementations
- [NLipCoin](https://github.com/NicolasDorier/NLipCoin/blob/master/NLipCoin/Script.cs#L814) (.NET Bindings)
- [node-liblipcoinconsensus](https://github.com/bitpay/node-liblipcoinconsensus) (Node.js Bindings)
- [java-liblipcoinconsensus](https://github.com/dexX7/java-liblipcoinconsensus) (Java Bindings)
- [lipcoinconsensus-php](https://github.com/Bit-Wasp/lipcoinconsensus-php) (PHP Bindings)
