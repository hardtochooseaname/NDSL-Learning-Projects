#include "functions.h"


// Data structure of kv pair
typedef struct{
    char key[MAX_LENGTH];
    char value[MAX_NUM];
}KeyValuePair;

// Array to store all the kv pair
KeyValuePair kv_list[MAX_NUM];
// Count kv pairs in kv_list[]
int kv_num = 0;
// Flag whether any changes were made
bool something_changed = false;


// Load key-value records form local file into an array of key-value pairs
void load_record(char filename[])
{
    FILE *fp = fopen(filename, "r");
    if(fp == NULL){
        printf("Error: Record file not found!\n");
        return;
    }

    char line[MAX_LENGTH*2+1];
    char *key, *value;
    kv_num = 0;
    while(fgets(line, sizeof(line), fp)){
        // You must place the string returned by strtok in a char* variable
        // Only in this way can you avoid a 'egmentation fault'
        // I don't why
        key = strtok(line, ":");
        value = strtok(NULL, ":");
        if(key && value)
            append_to_list(key, value);
    }
        
    
    printf("Records successfully loaded.\n");
    fclose(fp);
}



// Save all the changes into local file
void save_changes()
{
    FILE *fp = fopen(KV_RECORDS, "w");

    char line[MAX_LENGTH];
    for(int i = 0; i < kv_num; i++)
        fprintf(fp, "%s:%s", kv_list[i].key, kv_list[i].value);
    
    printf("All changes saved.\n");
    fclose(fp);
}



// Add a key-value pair into the array
bool append_to_list(char *key, char *value)
{
    if(kv_num >= MAX_NUM){
        printf("Error: The number of key-value records has reached the upper limit\n");
        return false;
    }

    strcpy(kv_list[kv_num].key, key);
    strcpy(kv_list[kv_num].value, value);
    kv_num++;
    return true;
}



// Add a key-value pair provided in command line into records
void add_kv_pair(char *optarg)
{
    char *key, *value;
    key = strtok(optarg, ":");
    value = strtok(NULL, ":");

    
    if(key && value){       // The input is valid
        strcat(value, "\n");

        int i;
        if(key && (i = search_kv_pair(key)) > -1)   // The key already exists.
            if(strcmp(value, kv_list[i].value) == 0)
                printf("Guess what, the key-value pair already exists.\n");
            else{
                printf("Do you want to overwrite it or not(Y/n):\n");
                char *decision;
                decision = readline("> ");
                if(strcmp(decision, "Y") == 0 || strcmp(decision, "y") == 0){
                    strcpy(kv_list[i].value, value);
                    printf("Overwriting is done!\n");
                    something_changed = true;
                }
                else
                    printf("All right then. Nothing will be changed.\n");
            }
        else if(append_to_list(key, value) == true){
            printf("Ceated and added key-value pair %s:%s", key, value);
            something_changed = true;
        }
    }    
    else
        printf("Error: Invalid key-value pair format. Use '-a key:value'\n");
}



// Delete a key-value pair according to the key provided in command line
void delete_kv_pair(char *key)
{
    int i = 0;
    char value[MAX_LENGTH];
    while(i < kv_num && strcmp(kv_list[i].key, key) != 0)
        i++;
    if(i == kv_num)
        printf("Woops: %s is not a key that exist.\n", key);
    else{
        kv_num--;
        strcpy(value, kv_list[i].value);
        for(; i < kv_num; i++){
            strcpy(kv_list[i].key, kv_list[i+1].key);
            strcpy(kv_list[i].value, kv_list[i+1].value);
        }
        something_changed = true;
        printf("Successfully deleted %s:%s", key, value);
    }
}



// Print all the key-value pair records to stdout
void print_kv_pairs()
{
    for(int i = 0; i < kv_num; i++){
        printf("%s",kv_list[i].key);
        printf(":");
        printf("%s",kv_list[i].value);
    }
    printf("------------All key-value records printed.------------\n");
}



// Search a key-value pair according to the key provided in command line
int search_kv_pair(char *key)
{
    int i = 0;
    while(i < kv_num && strcmp(kv_list[i].key, key) != 0)
        i++;
    if(i == kv_num){
        printf("Key '%s' doesn't exist.\n", key);
        return -1;
    }
    else{
        printf("Found existed key-value pair: %s:%s", key, kv_list[i].value);
        return i;
    }     
}


// Enter the interactive interface
void interactive_mode()
{
    printf("Here is Interactive Mode. Enter 'help' to acquire usage.\n");
    char *line, *command, *arg;
    while(line = readline("> ")){
        command = strtok(line, " ");
        if(command == NULL){
            printf("None command was entered. Don't be kidding.\n");
            continue;
        }
        arg = strtok(NULL, " ");
        
        if(strcmp(command, "print") == 0)
            print_kv_pairs();
        else if(strcmp(command, "query") == 0)
            search_kv_pair(arg);
        else if(strcmp(command, "add") == 0)
            add_kv_pair(arg);
        else if(strcmp(command, "delete") == 0)
            delete_kv_pair(arg);
        else if(strcmp(command, "help") == 0)
            provide_help_im();
        else if(strcmp(command, "quit") == 0)
            break;      
        else
            printf("Error: Invalid command! Enter 'help' to acquire usage.\n");    
    }
}

void provide_help_im()
{
    printf("Enter 'add key:value' to add a key-value pair.\n");
    printf("Enter 'query key' to query the value of a key.\n");
    printf("Enter 'delete key' to delete a key-value pair.\n");
    printf("Enter 'print' to print all key-value pairs.\n");
    printf("Enter 'exit' to exit the program.\n");
}