using namespace eosio;
using namespace std;

TABLE expenses_list
{
   uint64_t id;
   eosio::name account_name;
   string expense_name;
   eosio::asset expense_amount;
   string expense_description;
   bool approved;
   
   uint64_t primary_key() const{return id.value;}
}
typedef eosio::multi_index< eosio::name("expenselist"), expenses_list > expenses_table;