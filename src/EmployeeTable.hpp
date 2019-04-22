using namespace eosio;
using namespace std;

TABLE employee_list
{
  eosio::name account_name;
  eosio::asset employee_salary;
  uint64_t const pay_frequency;
  eosio::time_point last_payment;
  
  
  uint64_t primary_key() const{return account_name.value;}
}
typedef eosio::multi_index< eosio::name("employeelist"), employee_list > employee_table;

