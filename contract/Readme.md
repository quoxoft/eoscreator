new account smart contract on EOS
-------
#### Prerequisites
* Wallet must be unlock and have at least the following private keys



##### Create newaccount account
````bash

````

##### Cset contract
````bash
cleos set contract newaccount ./new_account -p newaccount
````

##### Set eosio.token contract to eosio.token account
````bash
cleos set contract eosio.token build/contracts/eosio.token -p eosio.token
````
