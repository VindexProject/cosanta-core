// Copyright (c) 2018 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <logging.h>
#include <util/system.h>
#include <walletinitinterface.h>

#include <stdio.h>

class DummyWalletInit : public WalletInitInterface {
public:

    bool HasWalletSupport() const override {return false;}
    void AddWalletOptions() const override;
    bool ParameterInteraction() const override {return true;}
    void RegisterRPC(CRPCTable &) const override {}
    bool Verify() const override {return true;}
    bool Open() const override {LogPrintf("No wallet support compiled in!\n"); return true;}
    void Start(CScheduler& scheduler) const override {}
    void Flush() const override {}
    void Stop() const override {}
    void Close() const override {}

    // Dash Specific WalletInitInterface InitCoinJoinSettings
    void AutoLockMasternodeCollaterals() const override {}
    void InitCoinJoinSettings() const override {}
    void InitKeePass() const override {}
    bool InitAutoBackup() const override {return true;}
};

void DummyWalletInit::AddWalletOptions() const
{
    std::vector<std::string> opts = {"-createwalletbackups=<n>", "-disablewallet", "-instantsendnotify=<cmd>",
        "-keypool=<n>", "-rescan=<mode>", "-salvagewallet", "-spendzeroconfchange", "-upgradewallet",
        "-wallet=<path>", "-walletbackupsdir=<dir>", "-walletbroadcast", "-walletdir=<dir>",
        "-walletnotify=<cmd>", "-zapwallettxes=<mode>", "-discardfee=<amt>", "-fallbackfee=<amt>",
        "-mintxfee=<amt>", "-paytxfee=<amt>", "-txconfirmtarget=<n>", "-hdseed=<hex>", "-mnemonic=<text>",
        "-mnemonicpassphrase=<text>", "-usehd", "-keepass", "-keepassid=<id>", "-keepasskey=<key>",
        "-keepassname=<name>", "-keepassport=<port>", "-enablecoinjoin", "-coinjoinamount=<n>",
        "-coinjoinautostart", "-coinjoindenomsgoal=<n>", "-coinjoindenomshardcap=<n>", "-coinjoinmultisession",
        "-coinjoinrounds=<n>", "-coinjoinsessions=<n>", "-dblogsize=<n>", "-flushwallet", "-privdb",
        "-walletrejectlongchains"};
    gArgs.AddHiddenArgs(opts);
}

const WalletInitInterface& g_wallet_init_interface = DummyWalletInit();
