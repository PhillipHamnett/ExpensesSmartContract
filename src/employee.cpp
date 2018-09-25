#include "employee.hpp"

namespace eos42
{
  employee::employee()
  {}

  uint64_t employee::primary_key() const
  {
    return get_name();
  }
  account_name employee::get_name() const
  {
    return name;
  }
  eosio::asset employee::get_max_payout() const
  {
    return max_payout;
  }
  void employee::set_name(uint64_t const _name)
  {
    name = _name;
  }
  void employee::set_max_payout(eosio::asset const & _max_payout)
  {
    max_payout = _max_payout;
  }

}

