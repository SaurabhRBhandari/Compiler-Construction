#include "lexerDef.h"
#include "parserDef.h"
#include "utils.h"
#include "lexer.h"
#include "parser.h"
#include <time.h>

int main()
{
    // Initialize the states, transitions and lookup table
    initialize_states();
    initialize_transitions();
    initialize_lookup_table();

    // Initialize the grammer
    grammer G;
    grammer_init(&G);

    // Compute first and follow sets
    FirstAndFollow F = ComputeFirstAndFollowSets(G);

    // Create the parse table
    table T;
    createParseTable(F, &T);

    int choice;
    while (1)
    {
        yellow("\n\n0. For Exit\n");
        yellow("1. For Removal of Comments\n");
        yellow("2. For Printing Lexical Tokens List\n");
        yellow("3. For Parsing the Source Code and printing the Parse Tree\n");
        yellow("4. For Parsing the Source Code and printing total time taken\n");
        yellow("ENTER YOUR CHOICE: ");
        scanf("%d", &choice); // Take the choice from the user
        switch (choice)
        {
        case 0:
            // Exit the program
            yellow("Thank you for using SALAD compiler.\n");
            return 0;
        case 1:
            // Remove comments from the input file
            yellow("Enter the input file name: ");
            char file_name[100];
            scanf("%s", file_name);
            append_endline(file_name);
            yellow("Enter the output file name:") char output_file_name[100];
            scanf("%s", output_file_name);
            removeComments(file_name, output_file_name);
            yellow("Comments removed successfully\n");
            break;
        case 2:
            // Print the lexical tokens list
            yellow("Enter the input file name: ");
            char file_name2[100];
            scanf("%s", file_name2);
            append_endline(file_name2);
            FILE *fp = fopen(file_name2, "r");
            vector v = getStream(fp);
            fclose(fp);
            red("%-30s", "Line");
            red("%-30s", "Lexeme");
            red("%s\n", "Token");
            for (int i = 0; i < v->size; i++)
            {
                magenta("%-30d", get(v, i)->lc);
                green("%-30s", get(v, i)->lexeme);
                blue("%s\n", TOKENS[get(v, i)->tk]);
            }
            break;
        case 3:
            // Parse the source code and print the parse tree
            yellow("Enter the input file name: ");
            char file_name3[100];
            scanf("%s", file_name3);
            append_endline(file_name3);
            FILE *fp3 = fopen(file_name3, "r");
            yellow("Enter the output file name: ");
            char output_file_name3[100];
            scanf("%s", output_file_name3);
            FILE *f = fopen(output_file_name3, "w");
            vector v3 = getStream(fp3);
            fclose(fp3);
            parseTree *tree = parseInputSourceCode(T, F, &G, v3);
            fprintf(f, "%-30s", "Lexeme");
            fprintf(f, "%-30s", "Line Number");
            fprintf(f, "%-30s", "Token Name");
            fprintf(f, "%-30s", "Value");
            fprintf(f, "%-30s", "Parent Node Symbol");
            fprintf(f, "%-30s", "is Leaf?");
            fprintf(f, "%s\n", "Node Symbol");
            fprintf(f, "%-30s", "------");
            fprintf(f, "%-30s", "-----------");
            fprintf(f, "%-30s", "----------");
            fprintf(f, "%-30s", "-----");
            fprintf(f, "%-30s", "------------------");
            fprintf(f, "%-30s", "--------");
            fprintf(f, "%s\n", "-----------");
            printParseTree(tree, f);
            break;
        case 4:
            // Parse the source code and print the total time taken
            yellow("Enter the input file name: ");
            char file_name4[100];
            scanf("%s", file_name4);
            FILE *fp4 = fopen(file_name4, "r");
            append_endline(file_name4);
            clock_t start_time, end_time;
            double total_CPU_time, total_CPU_time_in_seconds;
            start_time = clock();
            vector v4 = getStream(fp4);
            fclose(fp4);
            parseInputSourceCode(T, F, &G, v4);
            end_time = clock();
            total_CPU_time = (double)(end_time - start_time);
            total_CPU_time_in_seconds = total_CPU_time / CLOCKS_PER_SEC;
            magenta("Total CPU time: %f\n", total_CPU_time);
            magenta("Total CPU time in seconds: %f\n", total_CPU_time_in_seconds);
            break;
        default:
            // Invalid choice
            yellow("Invalid choice\n");
            break;
        }
    }
    return 0;
}