#include <eosiolib/eosio.hpp>
#include <eosiolib/currency.hpp>

#include "employee.hpp"

using namespace eosio;

namespace eos42
{
  class expenses: public contract
  {
    private:
      employee_table all_employees;
    public:
      expenses(account_name const contract);

      /// @abi action
      void add(account_name const employee, eosio::asset const & max_payout);

      /// @abi action
      void update(account_name const employee, eosio::asset const & max_payout);

      /// @abi action
      void pay(account_name const payer, account_name const employee, eosio::asset const & payout, std::string const & memo);

      /// @abi action
      void remove(account_name const employee);
  };
}
