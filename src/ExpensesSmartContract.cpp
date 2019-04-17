#include <ExpensesSmartContract.hpp>
ACTION ExpensesSmartContract::hi( name nm )
{
   /* fill in action body */
   print_f("Name : %\n",nm);
}

class [[eosio::contract]] employee_table : public contract
{
  public:
      using contract::contract;
      
      [[eosio::action]]
      void addemp( account_name const user, string employee_name )
      {
        
      }
      
      [[eosio::action]]
      void setsal( account_name const user, string employee_name, uint64_t salary)
      {
        
      }
      
      [[eosio::action]]
      void delemp( account_name const user, string employee_name)
      {
        
      }
      
      [[eosio::action]]
      void claimexp( account_name const user, string employee_name, uint64_t expenses)
      {
        
      }
      
      [[eosio::action]]
      void appexp( account_name const user)
      {
        
      }
      
      [[eosio::action]]
      void rejexp( account_name const user)
      {
        
      }
      
      [[eosio::action]]
      void paysal( account_name const user)
      {
        
      }
}