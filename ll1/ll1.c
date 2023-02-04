// 			Abdullah Baig
// 			  231485698

#include <stdio.h>
#include "string.h"
#include <stdlib.h>

#define MAX_STATES 4
#define MAX_SYMBOLS 4


int parse();
char pop1();
char pop2();
void get_stack1();
void get_stack2();
void push1(char to_push);
void push2(char to_push);
int convert_char(char chr);
char get_top1();
char get_top2();
int check_tops();
void print_stacks(char* temp, char* temp2);

char stack1[50], stack2[50];
int stack1_pointer = -1, stack2_pointer = -1;

//
// change parse_table and ruleset to match your grammar
//
int parse_table[MAX_STATES][MAX_SYMBOLS] = {{0, 0, 0, -1},
                                            {1, 1, 1, 1},
                                            {2, 3, 3, 3},
                                            {-1, 5, 4, 5}};

char *ruleset[6][2] = {{"S", "Aa"},
                       {"A",  "BD"},
                       {"B",  "b"},
                       {"B",  "epsilon"},
                       {"D",  "d"},
                       {"D",  "epsilon"}};

char* action;
char next_state;


int main(int argc, char *argv[]) {
    if(argc != 2){
        printf("Incorrect number of arguments!\n");

        exit(0);
    }

    stack1_pointer = -1;
    stack2_pointer = -1;

    char *input_string = argv[1];

    // push input string to stack 2
    for (int i = (strlen(input_string) - 1); i >= 0; i--) {
        push2(input_string[i]);
    }

    int flag = parse();

    if (flag == 1) {
        printf("\nString is accepted by the grammar\n");
    } else {
        printf("\nString is not accepted by the grammar\n");
    }
    return 0;
}


int parse() {
    char stack1_top;
    char stack2_top;

    printf("\n-------------------------------------------------------\n"
           "|--\tS1\t--|--\tS2\t--|--\t\tAction\t\t--|\n");

    push1('$');
    push1('S');

    goto start;

    start:
    if (check_tops() == 1) {
        goto accepted;
    }


    stack1_top = get_top1();
    stack2_top = get_top2();

    if (stack1_top == stack2_top) {
        goto start;
    }

    next_state = parse_table[convert_char(stack1_top)][convert_char(stack2_top)];

    if (next_state == -1) {
        goto rejected;
    }

    action = ruleset[next_state][1];

    if (strcmp(action, "epsilon") == 0) {
        pop1();
        goto start;
    }

    print_stacks(action, ruleset[next_state][0]);
    pop1();

    for (int i=strlen(action)-1; i>=0; i--) {
        push1(action[i]);
    }

    goto start;

    rejected:
    return 0;
    accepted:
    print_stacks("", "");
    return 1;
}

int check_tops() {
    char top1 = get_top1();
    char top2 = get_top2();
    if (top1 == '$' && top2 == '$') {
        return 1;
    } else if (top1 == top2) {
        print_stacks("", "");
        pop1();
        pop2();
        return 2;
    }
    return 0;
}

char get_top2() {
    return stack2[stack2_pointer];
}

void print_stacks(char* temp, char* temp2) {
    printf("-------------------------------------------------------\n");
    printf("\t");
    get_stack1();
    printf("\t\t\t");
    get_stack2();
    if (strcmp(temp2, temp) == 0) {
        printf("\t\t\t%s\t\n\n", temp2);
    } else {
        printf("\t\t\t%s ----> %s\t\n\n", temp2, temp);
    }
}

char get_top1() {
    return stack1[stack1_pointer];
}

void push1(char to_push) {
    stack1_pointer += 1;
    stack1[stack1_pointer] = to_push;
}

void push2(char to_push) {
    stack2_pointer += 1;
    stack2[stack2_pointer] = to_push;
}

char pop1() {
    char rtn_data = stack1[stack1_pointer];
    stack1_pointer -= 1;
    return rtn_data;
}

char pop2() {
    char rtn_data = stack2[stack2_pointer];
    stack2_pointer -= 1;
    return rtn_data;
}

void get_stack1() {
    for (int i = stack1_pointer; i >= 0; i--) {
        printf("%c", stack1[i]);
    }
}

void get_stack2() {
    for (int i = stack2_pointer; i >= 0; i--) {
        printf("%c", stack2[i]);
    }
}


int convert_char(char chr) {
    switch (chr) {
        case 'b':
            return 0;
        case 'a':
            return 1;
        case 'd':
            return 2;
        case '$':
            return 3;
        case 'S':
            return 0;
        case 'A':
            return 1;
        case 'B':
            return 2;
        case 'D':
            return 3;
        default:
            return -1;
    }
}
