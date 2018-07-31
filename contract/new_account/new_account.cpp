#include "new_account.hpp"
#include "abieos_numeric.hpp"
#include <eosiolib/print.hpp>
//#include <debug.hpp>

void new_account::transfer(account_name from, account_name to, eosio::asset quantity, std::string memo){
   if (from == _self || to != _self) {
        return;
    }
    eosio::print(memo);
    eosio_assert( quantity.is_valid(), "invalid quantity" );
    eosio_assert( quantity.amount > 0, "must transfer positive quantity" );
    //eosio_assert( quantity.symbol == CORE_SYMBOL, "only accept eos token" );

    std::size_t separator_pos = memo.find('-');
    eosio_assert(separator_pos != std::string::npos, "memo doesn't follow contract rules");

    std::size_t next_separator_pos = memo.find('-',separator_pos+1);
    eosio_assert(next_separator_pos != std::string::npos, "memo doesn't follow contract rules");

    // get account name
    std::string account_name_str = memo.substr(0, separator_pos);
    eosio_assert(account_name_str.length() == 12, "account name should be 12");
    account_name new_account_name = eosio::string_to_name(account_name_str.c_str());

    // get owner public key
    std::string owner_key_str = memo.substr(separator_pos + 1, next_separator_pos - separator_pos-1);
    eosio_assert(owner_key_str.length() == 53, "length of public key should be 53");
    const abieos::public_key owner_pubkey = abieos::string_to_public_key(owner_key_str);

    eosio::public_key owner_key;
    owner_key.type =0;
    std::copy(owner_pubkey.data.begin(), owner_pubkey.data.end(), owner_key.data.begin());
    eosio_assert( owner_key != eosio::public_key(), "public key should not be the default value" );

    // get active public key
    std::string active_key_str = memo.substr(next_separator_pos + 1);
    eosio_assert(active_key_str.length() == 53, "length of public key should be 53");
    const abieos::public_key active_pubkey = abieos::string_to_public_key(active_key_str);


    eosio::public_key active_key;
    owner_key.type =0;
    std::copy(active_pubkey.data.begin(), active_pubkey.data.end(), active_key.data.begin());
    eosio_assert( active_key != eosio::public_key(), "public key should not be the default value" );

    const eosio::asset ram_amount = convertbytes2eos(4 * 1024);
    const eosio::asset ram_replace_amount = convertbytes2eos(256);
    const eosio::asset stake_net(1000, CORE_SYMBOL);
    const eosio::asset stake_cpu(1000, CORE_SYMBOL);
    const eosio::asset remain_balance = quantity - stake_cpu - stake_net - ram_amount - ram_replace_amount;

    eosio_assert(remain_balance.amount >= 0, "Not enough balance to buy ram");

    key_weight owner_pubkey_weight = {
        .key = owner_key,
        .weight = 1,
    };
    key_weight active_pubkey_weight = {
        .key = active_key,
        .weight = 1,
    };
    authority owner_auth = authority{
        .threshold = 1,
        .keys = {owner_pubkey_weight},
        .accounts = {},
        .waits = {}
    };
    authority active_auth = authority{
        .threshold = 1,
        .keys = {active_pubkey_weight},
        .accounts = {},
        .waits = {}
    };
    newaccount new_account = newaccount{
        .creator = _self,
        .name = new_account_name,
        .owner = owner_auth,
        .active = active_auth
    };

    eosio::action(
        eosio::permission_level{ _self, N(active) },
            N(eosio), N(newaccount),
            std::make_tuple(_self, new_account_name, active_auth, owner_auth)
    ).send();


    eosio::action(
            eosio::permission_level{ _self, N(active)},
            N(eosio),
            N(buyram),
            std::make_tuple(_self, new_account_name, ram_amount)
    ).send();

    eosio::action(
        eosio::permission_level{ _self, N(active)},
        N(eosio),
        N(buyram),
        std::make_tuple(_self, new_account_name, ram_replace_amount)
    ).send();

    eosio::action(
            eosio::permission_level{ _self, N(active)},
            N(eosio),
            N(delegatebw),
            std::make_tuple(_self, new_account_name, stake_net, stake_cpu, true)
    ).send();

    if(remain_balance.amount > 0){
        eosio::action(
                eosio::permission_level{ _self, N(active)},
                N(eosio.token),
                N(transfer),
                std::make_tuple(_self, new_account_name, remain_balance, std::string("the remaining balance"))
        ).send();
    }
}

eosio::asset new_account::convertbytes2eos(uint32_t bytes){
    eosio::rammarket _rammarket(N(eosio), N(eosio));
    auto itr = _rammarket.find(S(4,RAMCORE));
    auto tmp = *itr;
    auto eosout = tmp.convert( eosio::asset(bytes,S(0,RAM)), CORE_SYMBOL );
    return eosout;
}
