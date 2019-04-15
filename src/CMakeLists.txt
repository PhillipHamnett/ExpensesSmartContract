project(ExpensesSmartContract)

set(EOSIO_WASM_OLD_BEHAVIOR "Off")
find_package(eosio.cdt)

add_contract( ExpensesSmartContract ExpensesSmartContract ExpensesSmartContract.cpp )
target_include_directories( ExpensesSmartContract PUBLIC ${CMAKE_SOURCE_DIR}/../include )
target_ricardian_directory( ExpensesSmartContract ${CMAKE_SOURCE_DIR}/../ricardian )