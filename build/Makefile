EXPENSES_ABI:= expenses.abi
EXPENSES:= expenses.wast

BASE:=..

EXPENSES_DIR:= $(BASE)/expenses

EXPENSES_ABI:=$(EXPENSES_DIR)/$(EXPENSES_ABI)
EXPENSES:=$(EXPENSES_DIR)/$(EXPENSES)

SRCDIR:= $(BASE)/src

EXPENSES_SRC:= expenses.cpp employee.cpp
EXPENSES_SRC:= $(addprefix $(SRCDIR)/,$(EXPENSES_SRC))

all: $(EXPENSES) $(EXPENSES_ABI)

clean:
	rm -rf $(EXPENSES_DIR)

$(EXPENSES_DIR):
	mkdir -p $@

$(EXPENSES): $(EXPENSES_SRC) | $(EXPENSES_DIR)
	eosiocpp -o $@ $(INCLUDES) $<

$(EXPENSES_ABI): $(EXPENSES_SRC) | $(EXPENSES_DIR)
	eosiocpp -g $@ $(INCLUDES) $<
