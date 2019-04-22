#include <EmployeeTable.hpp>
#include <EmployersTable.hpp>
#include <ExpensesTable.hpp>

class [[eosio::contract]] employee_table : public contract
{
  public:
      using contract::contract;
      
      [[eosio::action]]
      void addemp( eosio::name const user, 
                   eosio::name const account_name,
                   uint64_t const employee_salary,
                   uint64_t const pay_frequency)
      {
        require_auth(user);
        eosio::check(user!=employers_table.end(), "You must be an employer to perform this function");
        employee_table _employee_table(_self, _self.value);
        eosio::check(_employee_table.find(account_name.value)==_employee_table.end(), "Employee has already been added");
        employee_table.emplace(_self, [&](auto & entry)
            {
              entry.account_name = account_name;
              entry.employee_salary = employee_salary;
              entry.pay_frequency = pay_frequency;
            });
      }
      
      [[eosio::action]]
      void setsal( eosio::name const user, 
                   eosio::name const account_name, 
                   uint64_t salary)
      {
        require_auth(user);
        eosio::check(user!=employers_table.end(), "You must be an employer to perform this function");
        employee_table _employee_table(_self, _self.value);
         eosio::check(_employee_table.find(account_name.value)!=_employee_table.end(), "Employee must be added to assign a salary");
        _employee_table.modify(_employee_table.find(account_name), _self, [&](auto & entry)
            {
              entry.salary = employee_salary;
            });
      }
      
      [[eosio::action]]
      void delemp( eosio::name const user, 
                   eosio::name const account_name)
      {
        require_auth(user);
        eosio::check(user!=employers_table.end(), "You must be an employer to perform this function");
        employee_table _employee_table(_self, _self.value);
        eosio::check(_employee_table.find(account_name.value)!=_employee_table.end(), "Employee must be added to delete the employee");
        _employee_table.erase(_employee_table.find(account_name));
      }
      
      [[eosio::action]]
      void addexp( eosio::name const user,
                   string expense_name,
                   uint64_t expense_amount,
                   string expense_description)
      {
        require_auth(user);
        eosio::check(user!=employee_table.end(), "You must be a current employee to add an expense");
        expenses_table _expenses_table(_self, _self.value);
        _employee_table.emplace(_self, [&](auto & entry)
            {
              entry.id = _expenses_table.available_primary_key();
              entry.user = account_name;
              entry.expense_name = expense_name;
              entry.expense_amount = expense_amount;
              entry.expense_description = expense_description;
              approved = false;
              paid = false;
            });
      }
      
      [[eosio::action]]
      void appexp( eosio::name const user, uint64_t expense_id)
      {
        require_auth(user);
        eosio::check(user!=employers_table.end(), "You must be an employer to perform this function");
        expenses_table _expenses_table(_self, _self.value);
        eosio::check(expense_id!=_expenses_table.end()) "You must enter the id of an expense currently in the table"
        eosio::check(_expenses_table.find(expense_id).approved!=true) "This expense has already been approved"
        _expenses_table.modify(_expenses_table.find(expense_id), _self, [&] auto & entry)
            {
              approved = true;
            });
      }
      
      [[eosio::action]]
      void delexp( eosio::name const user, uint64_t expense_id)
      {
        require_auth(user);
        eosio::check(user!=employers_table.end(), "You must be an employer to perform this function");
        expenses_table _expenses_table(_self, _self.value);
        eosio::check(expense_id!=_expenses_table.end()) "You must enter the id of an expense currently in the table"
        _expenses_table.erase(_expenses_table.find(expense_id));
      }
      
      [[eosio::action]]
      void paysal( eosio::name const user)
      {
        require_auth(user);
        eosio::check(user!=employers_table.end(), "You must be an employer to perform this function");
        employee_table _employee_table(_self, _self.value);
        for (auto itr = _employee_table.begin(); itr != _employee_table.end(); ++itr)
        {
          eosio::action payout(eosio::permission_level{_self, N(active)},
            N(eosio.token), N(transfer),
            std::make_tuple(_self, itr->account_name, itr->employee_salary, std::string("EOS42 salary")));
          payout.send();
        }
      }
      
      [[eosio::action]]
      void payexp( eosio::name const user)
      {
        require_auth(user);
        eosio::check(user!=employers_table.end(), "You must be an employer to perform this function");
        expenses_table _expenses_table(_self, _self.value);
        auto itr = _expenses_table.begin();
        while (itr != _expenses_table.end())
        {
          if (itr->approved)
          {
            eosio::action payout(eosio::permission_level{_self, N(active)},
              N(eosio.token), N(transfer),
              std::make_tuple(_self, itr->account_name, itr->expense_amount, std::string("EOS42 expense - id "id")));
            payout.send();
            itr = _expenses_table.erase(itr);
          }
          else 
          {
            ++itr;
          }
        }
      }
}