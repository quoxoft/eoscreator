Simple voting smart contract on EOS
-------
#### Prerequisites
* Wallet must be unlock and have at least the following private keys

	**5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3**
	
	**5Jmsawgsp1tQ3GD6JyGCwy1dcvqKZgX6ugMVMdjirx85iv5VyPR**

##### Create eoscreator account
````bash

````

##### Ceate eosio.token account
````bash
cleos create account eosio eosio.token EOS7ijWCBmoXBi3CgtK7DJxentZZeTkeUnaSDvyro9dq7Sd1C3dC4 EOS7ijWCBmoXBi3CgtK7DJxentZZeTkeUnaSDvyro9dq7Sd1C3dC4
````

##### Set eosio.token contract to eosio.token account
````bash
cleos set contract eosio.token build/contracts/eosio.token -p eosio.token
````

##### Create simplevoting account
````bash
cleos create account eosio simplevoting EOS7ijWCBmoXBi3CgtK7DJxentZZeTkeUnaSDvyro9dq7Sd1C3dC4 EOS7ijWCBmoXBi3CgtK7DJxentZZeTkeUnaSDvyro9dq7Sd1C3dC4
````

##### Set simple.volting contract to simplevoting account
````bash
cleos set contract simplevoting ./simple.volting -p simplevoting
````

##### Create native EOS token
````bash
cleos push action eosio.token create '[ "eosio", "1000000000.0000 SYS", 0, 0, 0]' -p eosio.token
````

##### Create alice account
````bash
cleos create account eosio alice EOS7ijWCBmoXBi3CgtK7DJxentZZeTkeUnaSDvyro9dq7Sd1C3dC4 EOS7ijWCBmoXBi3CgtK7DJxentZZeTkeUnaSDvyro9dq7Sd1C3dC4
````

##### Create bob account
````bash
cleos create account eosio bob EOS7ijWCBmoXBi3CgtK7DJxentZZeTkeUnaSDvyro9dq7Sd1C3dC4 EOS7ijWCBmoXBi3CgtK7DJxentZZeTkeUnaSDvyro9dq7Sd1C3dC4
````
##### Create candidate1, candidate2, candidate3,candidate4 account
````bash
cleos create account eosio candidate1 
EOS7ijWCBmoXBi3CgtK7DJxentZZeTkeUnaSDvyro9dq7Sd1C3dC4 EOS7ijWCBmoXBi3CgtK7DJxentZZeTkeUnaSDvyro9dq7Sd1C3dC4

cleos create account eosio candidate2 
EOS7ijWCBmoXBi3CgtK7DJxentZZeTkeUnaSDvyro9dq7Sd1C3dC4 EOS7ijWCBmoXBi3CgtK7DJxentZZeTkeUnaSDvyro9dq7Sd1C3dC4

cleos create account eosio candidate3
EOS7ijWCBmoXBi3CgtK7DJxentZZeTkeUnaSDvyro9dq7Sd1C3dC4 EOS7ijWCBmoXBi3CgtK7DJxentZZeTkeUnaSDvyro9dq7Sd1C3dC4

cleos create account eosio candidate4
EOS7ijWCBmoXBi3CgtK7DJxentZZeTkeUnaSDvyro9dq7Sd1C3dC4 EOS7ijWCBmoXBi3CgtK7DJxentZZeTkeUnaSDvyro9dq7Sd1C3dC4
...
````

##### Issue 1000 EOS to alice
````bash
cleos push action eosio.token issue '[ "alice", "1000.0000 SYS", "" ]' -p eosio
````

##### Issue 1000 EOS to bob
````bash
cleos push action eosio.token issue '[ "bob", "1000.0000 SYS", "" ]' -p eosio
````

##### Allow simple.volting contract to make transfers on alice behalf (to stake)
````bash
cleos set account permission alice active '{"threshold": 1,"keys": [{"key": "EOS7ijWCBmoXBi3CgtK7DJxentZZeTkeUnaSDvyro9dq7Sd1C3dC4","weight": 1}],"accounts": [{"permission":{"actor":"simplevoting","permission":"active"},"weight":1}]}' owner -p alice
````

##### Allow simple.volting  contract to make transfers on bob behalf (to stake)
````bash
cleos set account permission bob active '{"threshold": 1,"keys": [{"key": "EOS7ijWCBmoXBi3CgtK7DJxentZZeTkeUnaSDvyro9dq7Sd1C3dC4","weight": 1}],"accounts": [{"permission":{"actor":"simplevoting","permission":"active"},"weight":1}]}' owner -p bob
````

##### Allow simple.volting  contract to have permission to make transition
````bash
cleos set account permission simplevoting active '{"threshold": 1,"keys": [{"key": "EOS7ijWCBmoXBi3CgtK7DJxentZZeTkeUnaSDvyro9dq7Sd1C3dC4","weight": 1}],"accounts": [{"permission":{"actor":"simplevoting","permission":"eosio.code"},"weight":1}]}' owner -p simplevoting
````
##### Users : Candidate1,2,3,4 register to become a candidate
````bash
cleos push action simplevoting regcandidate '["candidate1", "EOS7ijWCBmoXBi3CgtK7DJxentZZeTkeUnaSDvyro9dq7Sd1C3dC4", "lecle.com"]' -p candidate1
````

````bash
cleos push action simplevoting regcandidate '["candidate2", "EOS7ijWCBmoXBi3CgtK7DJxentZZeTkeUnaSDvyro9dq7Sd1C3dC4", "lecle.com"]' -p candidate2
````

````bash
cleos push action simplevoting regcandidate '["candidate3", "EOS7ijWCBmoXBi3CgtK7DJxentZZeTkeUnaSDvyro9dq7Sd1C3dC4", "lecle.com"]' -p candidate3
````

````bash
cleos push action simplevoting regcandidate '["candidate4", "EOS7ijWCBmoXBi3CgtK7DJxentZZeTkeUnaSDvyro9dq7Sd1C3dC4", "lecle.com"]' -p candidate4
````

##### Alice votes 50 EOS for cadidate2 into the simplevoting contract, Remember the token will be freezed until the end of voting
````bash
cleos push action simplevoting votcandidate '["alice", "", ["candidate2"], "50.0000 SYS"]' -p alice
````

##### Bob votes 75 EOS for cadidate1,2 into the simplevoting contract
````bash
cleos push action simplevoting votcandidate '["bob", "", ["candidate1", "candidate2"], "75.0000 SYS"]' -p bob
````

##### Balance of the accounts after vote, also check balance after the end of voting section.
````bash
cleos get account alice
````

````bash
cleos get account bob
````

##### Check voters infor
````bash
cleos get table simplevoting simplevoting voters
````

##### Check candidates infor
````bash
cleos get table simplevoting simplevoting candidates
````
