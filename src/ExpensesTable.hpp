using namespace eosio;
using namespace std;

TABLE expenses_list
{
   uint64_t id;
   eosio::name const account_name;
   string expense_name;
   uint64_t expense_amount;
   string expense_description;
   bool approved;
   bool paid;
   
   uint64_t primary_key() const{return account_name.value;}
}
typedef eosio::multi_index< eosio::name("expenselist"), expenses_list > expenses_table;