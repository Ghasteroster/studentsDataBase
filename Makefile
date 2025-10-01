SRC := main.cpp

CPPC := g++
CPPFLAGS := -std=c++20
LDFLAGS := -lgtest -lgtest_main -pthread
TPST := typst compile --root .
ZTHR := zathura

.PHONY: all

all: run-src

run-src:
	@echo "Running.."
	@$(CPPC) $(CPPFLAGS) $(SRC) $(LDFLAGS) -o tests.out
	@./main.out --test
