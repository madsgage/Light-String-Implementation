#pragma once
#include <malloc.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef struct String{
    char* text;
    int length;
}String;


String new_string(int size){
    String s;
    s.text = (char*)malloc(sizeof(char)*size);
    s.length = size;
    return s;
}

void set_string(String* a, char* new, int length){
    free(a->text);
    a->text = new;
    a->length = length;
}

/// O(n) = n :DDDDDDDDDDDDDDDDDDDDDDDDDDD
void replace_string(String* a, char* old, int old_size, char* new, int new_size){
    int num_of_occurances = 0; 
    int index_buffer[a->length * 2]; //Start & end point for indexes

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
        if(currently_matching == (old_size)){
            end_buffer = i;
            if((start_buffer != -1) && (end_buffer != -1)){
                index_buffer[num_of_occurances * 2] = start_buffer;
                index_buffer[num_of_occurances * 2 + 1] = end_buffer;
            }
            num_of_occurances += 1;
            currently_matching = 0;
        }
    }
    int char_size = (a->length-(num_of_occurances*old_size) + (num_of_occurances*new_size));
    char* new_text = malloc(sizeof(char)*char_size);
    
    int p = 0;
    int current_index = 0;

    for(int i = 0; i < a->length; ++i){
        if(i == index_buffer[p*2]){
            for(int j = 0; j < new_size; ++j){
                new_text[current_index] = new[j];
                current_index += 1;
            }
            p += 1;
            i += old_size-1;
            continue;
        }
        new_text[current_index] = a->text[i];
        current_index += 1;
    }

    free(a->text);
    a->text = new_text;
    a->length = char_size;
}

String concat_string(char* a, int len_a, char* b, int len_b){
    char* new_text = (char*)malloc(sizeof(char)*(len_a+len_b));
    memcpy(new_text,a,len_a);
    memcpy(&new_text[len_a],b,len_b);

    String string;
    string.text = new_text;
    string.length = (len_a+len_b);
    return string;
}