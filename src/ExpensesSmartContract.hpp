using namespace eosio;
using namespace std;

struct employee_list
{
  uint64_t id;
  string employee_name;
  string eosio_account_name;
  uint64_t employee_salary;
  uint64_t pay_frequency;
  
  uint64_t primary_key() const{return id;}
}
typedef eosio::multi_index< eosio::name("employee list"), employee_list > employee_table;

