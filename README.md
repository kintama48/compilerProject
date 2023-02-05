# INTRODUCTION:
The code provided is an implementation of LR(0) and LL(1) parsing algorithms. The code
uses a stack-based approach to parse a given input string against a predefined grammar. The code has
been implemented in C and uses several helper functions and data structures to implement the parsing
algorithm.
The parse_table variable is a 2D array of strings that represents the parse table for the given
grammar. The rows represent the states and the columns represent the symbols. Each entry in the table
represents the next action to be taken based on the current state and symbol.
The ruleset variable is a 2D array of strings that represents the production rules for the given
grammar. Each row represents a single production rule, with the left-hand side of the rule in the first
column and the right-hand side in the second column.
The stack1 and stack2 variables are character arrays that represent the two stacks used in the
parsing algorithm. The stack1 array is used to store the production rules and the stack2 array is used to
store the input string.
The stack1_pointer and stack2_pointer variables are integers that represent the current
position of the top of the stacks.
The main function takes in the input string as a command-line argument and calls the parse()
function to start the parsing process. If the input string is accepted by the grammar, the program prints
"String is accepted by the grammar", otherwise, it prints "String is not accepted by the grammar".

# FUNCTION DECLARATIONS:
●int parse(): This function is the main function that implements the LR(0) and LL(1) parsing
algorithms. It returns 1 if the input string is accepted by the grammar and 0 otherwise.

● char pop1(): This function pops the topmost symbol from stack1 and returns it.

● char pop2(): This function pops the topmost symbol from stack2 and returns it.

● void get_stack1(): This function prints the contents of stack1.

● void get_stack2(): This function prints the contents of stack2.

● void push1(char to_push): This function pushes the given character to stack1.

● void push2(char to_push): This function pushes the given character to stack2.

● int convert_char(char chr): This function converts the given character to its corresponding
integer value, which is used to look up the parse table entry. The function returns -1 if the
character is not a valid symbol in the grammar.

● char get_top1(): This function returns the topmost symbol in stack1.

● char get_top2(): This function returns the topmost symbol in stack2.


## LR(0) LOGIC:
● The LR(0) parsing algorithm is implemented in the parse() function. The function starts by
initializing the stack1 and stack2 pointers to -1. It then reads the input string and pushes it to
stack2. The function then enters a while loop that continues until the stack1 pointer becomes
-1.

● The function starts by reading the topmost symbol from stack1 and the current symbol from
stack2. It then looks up the corresponding parse table entry for the state represented by the
topmost symbol in stack1 and the current symbol in stack2.

● If the entry is an "Accept" symbol, the function returns 1 indicating that the input string is
accepted by the grammar. If the entry is an "_" symbol, the function returns 0 indicating that
the input string is not accepted by the grammar.

● If the entry is an "R" symbol, the function performs a reduction operation. The function pops
the topmost symbol from stack1 and pushes the corresponding right-hand side of the
production rule onto the stack.

● If the entry is an "S" symbol, the function performs a shift operation. The function pushes the
current symbol from stack2 onto stack1 and pops it from stack2.

# LL(1) LOGIC:

● The LL(1) parsing algorithm is implemented in the parse() function. The function starts by
initializing the stack1 and stack2 pointers to -1. It then reads the input string and pushes it to
stack2. The function then enters a while loop that continues until the stack1 pointer becomes
-1.

● The function starts by reading the topmost symbol from stack1 and the current symbol from
stack2. It then looks up the corresponding parse table entry for the state represented by the
topmost symbol in stack1 and the current symbol in stack2.

● If the entry is an "Accept" symbol, the function returns 1 indicating that the input string is
accepted by the grammar. If the entry is an "_" symbol, the function returns 0 indicating that
the input string is not accepted by the grammar.

● If the entry is an "R" symbol, the function performs a reduction operation. The function pops
the topmost symbol from stack1 and pushes the corresponding right-hand side of the
production rule onto the stack.

● If the entry is an "S" symbol, the function performs a shift operation. The function pushes the
current symbol from stack2 onto stack1 and pops it from stack2.

● The LL(1) parsing algorithm is implemented in the parse() function. The function starts by
initializing the stack1 and stack2 pointers to -1. It then reads the input string and pushes it to
stack2. The function then enters a while loop that continues until the stack1 pointer becomes
-1.

● The function starts by reading the topmost symbol from stack1 and the current symbol from
stack2. It then looks up the corresponding parse table entry for the state represented by the
topmost symbol in stack1 and the current symbol in stack2.

● If the entry is an "Accept" symbol, the function returns 1 indicating that the input string is
accepted by the grammar. If the entry is an "_" symbol, the function returns 0 indicating that
the input string is not accepted by the grammar.

● If the entry is an "R" symbol, the function performs a reduction operation. The function pops
the topmost symbol from stack1 and pushes the corresponding right-hand side of the
production rule onto the stack.

● If the entry is an "S" symbol, the function performs a shift operation. The function pushes the
current symbol from stack2 onto stack1 and pops it from stack2.
