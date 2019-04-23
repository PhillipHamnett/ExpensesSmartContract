#ifndef EXPENSESTABLE_HPP_
#define EXPENSESTABLE_HPP_

#include <eosio/eosio.hpp>
#include <eosio/asset.hpp>

using namespace eosio;
using namespace std;

TABLE expenses_list
{
   uint64_t expense_id;
   eosio::name account_name;
   string expense_name;
   eosio::asset expense_amount;
   string expense_description;
   bool approved;
   
   uint64_t primary_key() const{return expense_id;}
};
typedef eosio::multi_index< eosio::name("expenselist"), expenses_list > expenses_table;

#endif /* EXPENSESTABLE_HPP_ */