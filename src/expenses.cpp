// Author: Phillip Hamnett
// Date: 23 September 2018
// Hackathon Team: The Salmon of Doubt

#include <eosiolib/eosio.hpp>
#include <eosiolib/crypto.h>
#include <eosiolib/transaction.hpp>

#include "employee.cpp"
#include "expenses.hpp"

using namespace eosio;

namespace eos42
{
  // Default Constructor
  expenses::expenses(account_name const contract) :
    eosio::contract(contract),
    all_employees(_self,N(employee))
  {}

  void expenses::add(account_name const name, eosio::asset const & max_payout)
  {
    require_auth(_self);
    all_employees.emplace(_self, [&](auto & employee)
        {
        employee.set_name(name);
        employee.set_max_payout(max_payout);
        });
  }

  void expenses::remove(account_name const name)
  {
    require_auth(name);
    auto employee = all_employees.find(name);
    eosio_assert(employee != all_employees.end(),"Sorry, this employee entry doesn't seem to exist");
    all_employees.erase(employee);
  }

  void expenses::pay(account_name const payer, account_name const payee, eosio::asset const & payout, std::string const & memo)
  {
    auto employee = all_employees.find(payee);
    eosio_assert(employee != all_employees.end(),"Sorry, this employee entry doesn't seem to exist");
    eosio_assert(payout > employee->get_max_payout(), "You are trying to pay out too much money to this employee, please speak to the boss");

    eosio::transaction transfer;
    transfer.actions.emplace_back(
        eosio::permission_level {_self, N(active) },
        N(eosio.token),
        N(transfer),
        std::make_tuple(
          payer,
          payee,
          payout,
          memo));
    transfer.send(payee,_self,true);
  }
}

// Standard apply function
extern "C"
{
  void apply( uint64_t receiver, uint64_t code, uint64_t action )
  {
    eos42::expenses thiscontract( receiver);
    switch( action )
    {
      case N(transfer):
        eosio_assert(code == N(eosio.token), "Nice try, but we are HACK PROOF");
        break;
      default:
        EOSIO_API( eos42::expenses, (add)(update)(pay)(remove))
    }
  }
}
