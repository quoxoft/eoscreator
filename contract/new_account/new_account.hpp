
#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/types.hpp>
#include <eosiolib/action.hpp>
#include <eosiolib/symbol.hpp>
#include <eosiolib/crypto.h>
#include <eosiolib/public_key.hpp>
#include "exchange_state.hpp"
#include "exchange_state.cpp"
#include <cstring>


class new_account : public eosio::contract {
  public:
    new_account( account_name _self):contract(_self){};
    //@abi action
    void transfer(account_name from, account_name to, eosio::asset quantity, std::string memo);
  
  private:
    eosio::asset convertbytes2eos(uint32_t bytes);


    struct permission_level_weight {
        eosio::permission_level permission;
        weight_type weight;

        EOSLIB_SERIALIZE(permission_level_weight, (permission)(weight))
    };

    struct key_weight {
        eosio::public_key key;
        weight_type weight;

        EOSLIB_SERIALIZE(key_weight, (key)(weight))
    };

    struct wait_weight {
        uint32_t wait_sec;
        weight_type weight;

        EOSLIB_SERIALIZE(wait_weight, (wait_sec)(weight))
    };

    struct authority {
        uint32_t threshold;
        std::vector<key_weight> keys;
        std::vector<permission_level_weight> accounts;
        std::vector<wait_weight> waits;

        EOSLIB_SERIALIZE(authority, (threshold)(keys)(accounts)(waits))
    };

    struct newaccount {
        account_name creator;
        account_name name;
        authority owner;
        authority active;
    };
};


#define EOSIO_ABI_EX(TYPE, MEMBERS)                                            \
extern "C" {                                                                 \
  void apply(uint64_t receiver, uint64_t code, uint64_t action) {              \
    if (action == N(onerror)) {                                                \
      /* onerror is only valid if it is for the "eosio" code account and       \
       * authorized by "eosio"'s "active permission */                         \
      eosio_assert(code == N(eosio), "onerror action's are only valid from "   \
                                     "the \"eosio\" system account");          \
    }                                                                          \
    auto self = receiver;                                                      \
    if (code == self || code == N(eosio.token) || action == N(onerror)) {      \
      TYPE thiscontract(self);                                                 \
      switch (action) { EOSIO_API(TYPE, MEMBERS) }                             \
      /* does not allow destructor of thiscontract to run: eosio_exit(0); */   \
    }                                                                          \
  }                                                                            \
}

EOSIO_ABI_EX(new_account, (transfer))


