// Copyright (c) 2017 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_RPC_UTIL_H
#define BITCOIN_RPC_UTIL_H

#include <node/transaction.h>
#include <pubkey.h>
#include <script/standard.h>
#include <univalue.h>
#include <util/strencodings.h>
#include <rpc/protocol.h>

#include <boost/variant/static_visitor.hpp>

#include <string>
#include <vector>

class CKeyStore;
class CPubKey;
class CScript;

CPubKey HexToPubKey(const std::string& hex_in);
CPubKey AddrToPubKey(CKeyStore* const keystore, const std::string& addr_in);
CScript CreateMultisigRedeemscript(const int required, const std::vector<CPubKey>& pubkeys);

UniValue DescribeAddress(const CTxDestination& dest);

//! Parse a confirm target option and raise an RPC error if it is invalid.
unsigned int ParseConfirmTarget(const UniValue& value);

struct RPCArg {
    enum class Type {
        OBJ,
        ARR,
        STR,
        NUM,
        BOOL,
        OBJ_USER_KEYS, //!< Special type where the user must set the keys e.g. to define multiple addresses; as opposed to e.g. an options object where the keys are predefined
        AMOUNT,        //!< Special type representing a floating point amount (can be either NUM or STR)
        STR_HEX,       //!< Special type that is a STR with only hex chars
    };
    const std::string m_name; //!< The name of the arg (can be empty for inner args)
    const Type m_type;
    const std::vector<RPCArg> m_inner; //!< Only used for arrays or dicts
    const bool m_optional;

    RPCArg(const std::string& name, const Type& type, const bool optional)
        : m_name{name}, m_type{type}, m_optional{optional}
    {
        assert(type != Type::ARR && type != Type::OBJ);
    }

    RPCArg(const std::string& name, const Type& type, const std::vector<RPCArg>& inner, const bool optional)
        : m_name{name}, m_type{type}, m_inner{inner}, m_optional{optional}
    {
        assert(type == Type::ARR || type == Type::OBJ);
    }

    std::string ToString() const;

private:
    std::string ToStringObj() const;
};

class RPCHelpMan
{
public:
    RPCHelpMan(const std::string& name, const std::vector<RPCArg>& args)
        : m_name{name}, m_args{args}
    {
    }

    std::string ToString() const;

private:
    const std::string m_name;
    const std::vector<RPCArg> m_args;
};

RPCErrorCode RPCErrorFromTransactionError(TransactionError terr);
UniValue JSONRPCTransactionError(TransactionError terr, const std::string& err_string = "");

#endif // BITCOIN_RPC_UTIL_H
