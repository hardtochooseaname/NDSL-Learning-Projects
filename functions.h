#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

/****** head files *****/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <readline/readline.h>


/****** macro definitions *****/
#define     MAX_LENGTH  100     // String of key or value
#define     MAX_NUM     200     // Number of key-value pairs in file
#define     KV_RECORDS  "key-value-records.txt"     // The file storing data


/****** variables declarations *****/
extern bool something_changed;


/****** functions declarations *****/
void load_record();
void save_changes();
void print_kv_pairs();

bool append_to_list();
void add_kv_pair();
void delete_kv_pair();
int search_kv_pair();

void interactive_mode();
void provide_help_im();


#endif
