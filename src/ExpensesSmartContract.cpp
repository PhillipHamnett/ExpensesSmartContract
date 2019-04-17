#include <ExpensesSmartContract.hpp>

class [[eosio::contract]] employee_table : public contract
{
  public:
      using contract::contract;
      
      [[eosio::action]]
      void addemp( eosio::name const user, eosio::name const account_name )
      {
        require_auth(user);
        eosio::check(user!=employers.end(), "You must be an employer to perform this function");
        employee_table _employee_table(_self, _self.value);
        eosio::check(_employee_table.find(account_name.value)==_employee_table.end(), "Employee has already been added");
        employee_table.emplace(_self, [&](auto & entry)
            {
              entry.employee_name = employee_name;
            });
      }
      
      [[eosio::action]]
      void setsal( eosio::name const user, eosio::name const account_name, uint64_t salary)
      {
        require_auth(user);
        eosio::check(user!=employers.end(), "You must be an employer to perform this function");
        employee_table _employee_table(_self, _self.value);
         eosio::check(_employee_table.find(account_name.value)!=_employee_table.end(), "Employee must be added to assign a salary");
        _employee_table.modify(_employee_table.find(account_name), _self, [&](auto & entry)
            {
              entry.salary = employee_salary;
            });
      }
      
      [[eosio::action]]
      void delemp( eosio::name const user, eosio::name const account_name)
      {
        require_auth(user);
        eosio::check(user!=employers.end(), "You must be an employer to perform this function");
        employee_table _employee_table(_self, _self.value);
        eosio::check(_employee_table.find(account_name.value)!=_employee_table.end(), "Employee must be added to delete the employee");
        _employee_table.erase(_employee_table.find(account_name));
      }
      
      [[eosio::action]]
      void addexp( eosio::name const user, eosio::name const account_name, vector<uint64_t> expenses)
      {
        
      }
      
      [[eosio::action]]
      void appexp( eosio::name const user)
      {
        
      }
      
      [[eosio::action]]
      void rejexp( eosio::name const user)
      {
        
      }
      
      [[eosio::action]]
      void paysal( eosio::name const user)
      {
        
      }
}