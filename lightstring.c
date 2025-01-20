#pragma once
#include <malloc.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef struct String{
    char* text;
    int length;
}String;


String new_string_empty(int size){
    String s;
    s.text = (char*)malloc(sizeof(char)*size);
    if(s.text == NULL){
        printf("Could not allocate memory.");
        exit(-1);
    }
    s.length = size;
    return s;
}

String new_string(char* text){
    String s;
    s.text = text;
    s.length = strlen(text);
    return s;
}

void set_string(String* a, char* new, int length){
    free(a->text);
    a->text = new;
    a->length = length;
}

/// O(n) = n :DDDDDDDDDDDDDDDDDDDDDDDDDDD
void replace_string(String* a, char* old, char* new){
    int old_content_size = strlen(old);
    int new_content_size = strlen(new);

    int num_of_occurances = 0; 
    int* index_buffer = (int*)malloc(sizeof(int)*(a->length*2)); //Start & end point for indexes
    if(index_buffer == NULL){
        printf("Could not allocate memory.");
        exit(-1);
    }

    int currently_matching = 0;
    int start_buffer = -1;
    int end_buffer = -1;
    for(int i = 0; i < a->length; ++i){
        if(a->text[i] == old[currently_matching]){
            if(currently_matching == 0){
                start_buffer = i;
            }
            currently_matching += 1;
        }else{
            start_buffer = -1;
            end_buffer = -1;
            currently_matching = 0;
        }
        if(currently_matching == (old_content_size)){
            end_buffer = i;
            if((start_buffer != -1) && (end_buffer != -1)){
                index_buffer[num_of_occurances * 2] = start_buffer;
                index_buffer[num_of_occurances * 2 + 1] = end_buffer;
            }
            num_of_occurances += 1;
            currently_matching = 0;
        }
    }
    if(num_of_occurances == 0){ //End function early if no matches were found.
        return;
    }
    
    int char_size = (a->length-(num_of_occurances*old_content_size) + (num_of_occurances*new_content_size));
    char* new_text = malloc(sizeof(char)*char_size);
    if(new_text == NULL){
        printf("Could not allocate memory");
        exit(-1);
    }
    
    int p = 0;
    int current_index = 0;

    for(int i = 0; i < a->length; ++i){
        if(i == index_buffer[p*2]){
            for(int j = 0; j < new_content_size; ++j){
                new_text[current_index] = new[j];
                current_index += 1;
            }
            p += 1;
            i += old_content_size-1;
            continue;
        }
        new_text[current_index] = a->text[i];
        current_index += 1;
    }

    free(a->text);
    a->text = new_text;
    a->length = char_size;
    free(index_buffer);
}

String concat_string(char* a, char* b){
    int len_a = strlen(a);
    int len_b = strlen(b);
    char* new_text = (char*)malloc(sizeof(char)*(len_a+len_b));
    if(new_text == NULL){
        printf("Could not allocate memory");
        exit(-1);
    }
    memcpy(new_text,a,len_a);
    memcpy(&new_text[len_a],b,len_b);

    String string;
    string.text = new_text;
    string.length = (len_a+len_b);
    return string;
}