#include "EmployeeTable.hpp"
#include "EmployersTable.hpp"
#include "ExpensesTable.hpp"

class [[eosio::contract("expenses")]] expenses : public contract
{
  public:
	using contract::contract;
	TABLE expenses_list
	{
	        uint64_t expense_id;
	        eosio::name account_name;
	        string expense_name;
	        eosio::asset expense_amount;
	        string expense_description;
	        bool approved;

	        uint64_t primary_key() const{return expense_id;}
	        EOSLIB_SERIALIZE( expenses_list, (expense_id)(account_name)(expense_name)(expense_amount)(expense_description)(approved))
	};
	typedef eosio::multi_index< eosio::name("expenselist"), expenses_list > expenses_table;
	TABLE employer_list
	{
	        eosio::name account_name;

	        uint64_t primary_key() const{return account_name.value;}
	        EOSLIB_SERIALIZE( employer_list, (account_name) )
	};
	typedef eosio::multi_index< eosio::name("employerlist"), employer_list > employers_table;
	TABLE employee_list
	{
	        eosio::name account_name;
	        eosio::asset employee_salary;
	        uint64_t pay_frequency;
	        eosio::time_point last_payment;


	        uint64_t primary_key() const{return account_name.value;}
	        EOSLIB_SERIALIZE( employee_list, (account_name)(employee_salary)(pay_frequency)(last_payment) )
	};
	typedef eosio::multi_index< eosio::name("employeelist"), employee_list > employee_table;
	
	    ACTION addemployer(eosio::name const user, eosio::name const account_name)
	    {
	    	require_auth(_self);
	    	employers_table _employers_table(_self, _self.value);
	    	_employers_table.emplace(_self, [&](auto & entry)
	    			{
			       	entry.account_name = account_name;
			    	});
	    }
	    
      ACTION addemp( eosio::name const user, 
                   eosio::name const account_name,
                   eosio::asset const employee_salary,
                   uint64_t const pay_frequency)
      {
        require_auth(user);
        employee_table _employee_table(_self, _self.value);
        employers_table _employers_table(_self, _self.value);
        eosio::print("The arguments are  ", user, " ", account_name, " ", employee_salary.to_string(), " ", std::to_string(pay_frequency));
        eosio::check(_employers_table.find(user.value)!=_employers_table.end(), "4 You must be an employer to perform this function");
        eosio::check(_employee_table.find(account_name.value)==_employee_table.end(), "Employee has already been added");
        _employee_table.emplace(_self, [&](auto & entry)
            {
              entry.account_name = account_name;
              entry.employee_salary = employee_salary;
              entry.pay_frequency = pay_frequency;
            });
      }
      
      ACTION setsal( eosio::name const user, 
                   eosio::name const account_name, 
                   eosio::asset const employee_salary)
      {
        require_auth(user);
        employee_table _employee_table(_self, _self.value);
        employers_table _employers_table(_self, _self.value);
        eosio::check(_employers_table.find(user.value)!=_employers_table.end(), "5 You must be an employer to perform this function");
         eosio::check(_employee_table.find(account_name.value)!=_employee_table.end(), "Employee must be added to assign a salary");
        _employee_table.modify(_employee_table.find(account_name.value), _self, [&](auto & entry)
            {
              entry.employee_salary = employee_salary;
            });
      }
      
      ACTION delemp( eosio::name const user,
                   eosio::name const account_name)
      {
        require_auth(user);
        employee_table _employee_table(_self, _self.value);
        employers_table _employers_table(_self, _self.value);
        eosio::check(_employers_table.find(user.value)!=_employers_table.end(), "6 You must be an employer to perform this function");
        eosio::check(_employee_table.find(account_name.value)!=_employee_table.end(), "Employee must be added to delete the employee");
        _employee_table.erase(_employee_table.find(account_name.value));
      }
      
      ACTION addexp( eosio::name const user,
                   string const expense_name,
                   eosio::asset const expense_amount,
                   string const expense_description)
      {
        require_auth(user);
        employee_table _employee_table(_self, _self.value);
        eosio::check(_employee_table.find(user.value)!=_employee_table.end(), "You must be a current employee to add an expense");
        expenses_table _expenses_table(_self, _self.value);
        _expenses_table.emplace(_self, [&](auto & entry)
            {
              entry.expense_id = _expenses_table.available_primary_key();
              entry.account_name = user;
              entry.expense_name = expense_name;
              entry.expense_amount = expense_amount;
              entry.expense_description = expense_description;
              entry.approved = false;
            });
      }
      
      ACTION appexp( eosio::name const user, uint64_t const expense_id)
      {
        require_auth(user);
        employers_table _employers_table(_self, _self.value);
        expenses_table _expenses_table(_self, _self.value);
        eosio::check(_employers_table.find(user.value)!=_employers_table.end(), "1 You must be an employer to perform this function");
        eosio::check(_expenses_table.find(expense_id)!=_expenses_table.end(), "You must enter the id of an expense currently in the table");
        eosio::check(_expenses_table.find(expense_id)->approved!=true, "This expense has already been approved");
        _expenses_table.modify(_expenses_table.find(expense_id), _self, [&](auto & entry)
            {
              entry.approved = true;
            });
      }
      
      ACTION delexp( eosio::name const user, uint64_t const expense_id)
      {
        require_auth(user);
        employers_table _employers_table(_self, _self.value);
        expenses_table _expenses_table(_self, _self.value);
        eosio::check(_employers_table.find(user.value)!=_employers_table.end(), "2 You must be an employer to perform this function");
        eosio::check(_expenses_table.find(expense_id)!=_expenses_table.end(), "You must enter the id of an expense currently in the table");
        _expenses_table.erase(_expenses_table.find(expense_id));
      }
      
      ACTION paysal( eosio::name const user)
      {
        require_auth(user);
        employee_table _employee_table(_self, _self.value);
        employers_table _employers_table(_self, _self.value);
        eosio::check(_employers_table.find(user.value)!=_employers_table.end(), "3 You must be an employer to perform this function");
        for (auto itr = _employee_table.begin(); itr != _employee_table.end(); ++itr)
        {
          eosio::action payout(eosio::permission_level{_self, eosio::name("active")},
            eosio::name("eosio.token"), eosio::name("transfer"),
            std::make_tuple(_self, itr->account_name, itr->employee_salary, std::string("EOS42 salary")));
          payout.send();
        }
      }
      
      ACTION payexp( eosio::name const user)
      {
        eosio::print("HIYA");
        require_auth(user);
        expenses_table _expenses_table(_self, _self.value);
        employers_table _employers_table(_self, _self.value);
        eosio::print("Comparing ", user, " to the results from the employers table in scope ", _self);
        eosio::check(_employers_table.find(user.value)!=_employers_table.end(), "You (" + user.to_string() + ") must be an employer to perform this function");
        auto itr = _expenses_table.begin();
        while (itr != _expenses_table.end())
        {
          if (itr->approved)
          {
            eosio::action payout(eosio::permission_level{_self, eosio::name("active")},
              eosio::name("eosio.token"), eosio::name("transfer"),
              std::make_tuple(_self, itr->account_name, itr->expense_amount, std::string("EOS42 expense - id id")));
            payout.send();
            itr = _expenses_table.erase(itr);
          }
          else 
          {
            ++itr;
          }
        }
      }
};

extern "C" 
{
  void apply( uint64_t receiver, uint64_t code, uint64_t action)
  {
    switch ( action ) 
    {
      default:
        EOSIO_DISPATCH_HELPER(expenses, (addemp)(addemployer)(addexp)(appexp)(delemp)(delexp)(payexp)(paysal)(setsal));
        break;
    }
  }
}
