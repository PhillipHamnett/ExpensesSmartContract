project(expenses)

set(EOSIO_WASM_OLD_BEHAVIOR "Off")
find_package(eosio.cdt)

add_contract( expenses expenses expenses.cpp ExpensesTable.cpp EmployersTable.cpp EmployeeTable.cpp )
target_include_directories( expenses PUBLIC ${CMAKE_SOURCE_DIR}/../include )
target_ricardian_directory( expenses ${CMAKE_SOURCE_DIR}/../ricardian )
