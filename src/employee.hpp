#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <eosiolib/asset.hpp>
#include <eosiolib/crypto.h>

namespace eos42
{
  /// @abi table employee i64
  class employee
  {
    private:
      account_name name;
      eosio::asset max_payout;
    public:
      employee();
      uint64_t primary_key() const;
      account_name get_name() const;
      eosio::asset get_max_payout() const;
      void set_name(uint64_t const _name);
      void set_max_payout(eosio::asset const & _max_payout);
      EOSLIB_SERIALIZE(employee, (name)(max_payout))
  };

  typedef eosio::multi_index<N(employee), employee> employee_table;
}

#endif
