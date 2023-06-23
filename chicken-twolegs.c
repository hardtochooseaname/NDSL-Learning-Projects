#include "functions.h"

int main(int argc, char* argv[])
{
    // Load key-value records from specified file
    load_record(KV_RECORDS);

    
    if(argc == 1)   // Enter the interactive interface if no argument was input
        interactive_mode();
    else{           // Parse the command line input and implement according operations
        int option;
        while((option = getopt(argc, argv, ":a:d:s:l")) != -1){
            switch (option)
            {
            case 'a':
                add_kv_pair(optarg);
                break;
            case 'd':
                delete_kv_pair(optarg);
                break;
            case 's':
                search_kv_pair(optarg);
                break;
            case 'l':
                print_kv_pairs();
                break;
            case ':':
                printf("Error: Necessary argument missed!\n");
                break;
            case '?':
                printf("Error: Unkown option!\n");
                break;
            }
        }        
    }


    // If any changes were made, save them.
    if(something_changed ==  true)
        save_changes();
}



