using namespace eosio;
using namespace std;

TABLE employee_list
{
  eosio::name const account_name;
  uint64_t const employee_salary;
  uint64_t const pay_frequency;
  
  uint64_t primary_key() const{return account_name.value;}
}
typedef eosio::multi_index< eosio::name("employeelist"), employee_list > employee_table;

