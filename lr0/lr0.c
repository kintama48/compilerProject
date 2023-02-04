// 				Abdullah Baig
//   				 231485698

#include <stdio.h>
#include "string.h"
#include <stdlib.h>

#define MAX_STATES 7
#define MAX_SYMBOLS 5


int parse();
char pop1();
char pop2();
void get_stack1();
void get_stack2();
void push1(char to_push);
void push2(char to_push);
int convert_char(char chr);
char get_top1();


char stack1[50], stack2[50];
int stack1_pointer = -1, stack2_pointer = -1;

//
// change parse_table and ruleset to match your grammar
//
char *parse_table[MAX_STATES][MAX_SYMBOLS] = {{"S3", "S4", "_",      "1", "2"},
                                              {"_",  "_",  "Accept", "_", "_"},
                                              {"S3", "S4", "_",      "_", "5"},
                                              {"S3", "S4", "_",      "_", "6"},
                                              {"R3", "R3", "R3",     "_", "_"},
                                              {"R1", "R1", "R1",     "_", "_"},
                                              {"R2", "R2", "R2",     "_", "_"}};

char *ruleset[4][2] = {{"E'", "E"},
                       {"E",  "BB"},
                       {"B",  "cB"},
                       {"B",  "d"}};


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
        printf("String is accepted by the grammar\n");
    } else {
        printf("String is not accepted by the grammar\n");
    }
    return 0;
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
    for (int i = 0; (i <= stack1_pointer); i++) {
        printf("%c", stack1[i]);
    }
}

void get_stack2() {
    for (int i = stack2_pointer; i >= 0; i--) {
        printf("%c", stack2[i]);
    }
}


int convert_char(char chr) {
//    printf("%c\n", chr);
    switch (chr) {
        case 'c':
            return 0;
        case 'd':
            return 1;
        case '$':
            return 2;
        case 'E':
            return 3;
        case 'B':
            return 4;
        default:
            return -1;
    }
}

int parse() {
    char current_char = 0;
    int current_state = 0;
    char *temp;
    int repeat = 0;
    char next_state;
    int printed_stack = 0;

    printf("\n-------------------------------------------------------\n"
           "|--\tStack S1\t--|--\tInput S2\t--|--\tAction\t--|\n");
    push1('$');
    push1('0');

    while (current_char != '$') {
        if (printed_stack == 0){
            printf("-------------------------------------------------------\n");
            printf("\t\t");
            get_stack1();
            printf("\t\t\t\t");
            get_stack2();

            current_char = pop2();
            temp = parse_table[current_state][convert_char(current_char)];
            printf("\t\t\t\t%s\t\t\n\n", temp);
        } else {
            current_char = pop2();
            printed_stack = 0;
        }

        if (temp == NULL) {
            printf("Error: Invalid symbol %c detected\n", current_char);
            return 0;
        }

        if (temp[0] == 'S') {
            push1(current_char);
            push1(temp[1]);
            current_state = temp[1] - '0';
        } else if (temp[0] == 'R') {
            push2(current_char);
            while (temp[0] == 'R') {
                int rule_num = temp[1] - '0';
                for (int i = 0; i < (strlen(ruleset[rule_num][1]) * 2); i++) {
                    pop1();
                }

                if (repeat == 1) {
                    char reduce_by = ruleset[rule_num][0][0];
                    char stack1_top = get_top1() - '0';
                    push1(reduce_by);
                    next_state = parse_table[stack1_top][convert_char(reduce_by)][0];
                    push1(next_state);
                    repeat = 0;
                } else {
                    for (int i = 0; i < (strlen(ruleset[rule_num][1])); i++) {
                        char reduce_by = ruleset[rule_num][0][i];
                        char stack1_top = get_top1() - '0';
                        push1(reduce_by);
                        next_state = parse_table[stack1_top][convert_char(reduce_by)][0];
                        push1(next_state);
                        current_state = next_state - '0';
                    }
                }

                printf("-------------------------------------------------------\n");
                printf("\t\t");
                get_stack1();
                printf("\t\t\t\t");
                get_stack2();
                temp = parse_table[next_state - '0'][convert_char(current_char)];
                printf("\t\t\t\t%s\t\t\n\n", temp);
                printed_stack = 1;
                if (temp[0] == 'R') {
                    repeat = 1;
                }
            }
        } else if (strcmp(temp, "Accept") == 0) {
            return 1;
        } else if (temp[0] == '_') {
            return 0;
        } else {
            printf("Error: Invalid symbol %c detected\n", current_char);
            return 0;
        }
    }
    return 1;
}
