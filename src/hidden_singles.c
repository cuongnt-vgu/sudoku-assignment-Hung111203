#include "hidden_singles.h"
#include <stdio.h>
#include <stdlib.h>
int hidden_singles(SudokuBoard *p_board)
{
    int hidden_single_cells_counter = 0;
    HiddenSingle hidden_single_cells[BOARD_SIZE * BOARD_SIZE];

    for(int i = 0; i < BOARD_SIZE; i++)
    {
        find_hidden_single(p_board->p_rows[i], hidden_single_cells, &hidden_single_cells_counter);
        find_hidden_single(p_board->p_cols[i], hidden_single_cells, &hidden_single_cells_counter);
        find_hidden_single(p_board->p_boxes[i], hidden_single_cells, &hidden_single_cells_counter);
    }

    for(int i = 0; i < hidden_single_cells_counter; i++)
    {
        
        set_candidates(hidden_single_cells[i].p_cell, (int*)(int[]){hidden_single_cells[i].value}, 1);
    }
    return hidden_single_cells_counter;
}






int find_hidden_single_values(Cell **p_cells, int *possible_values) 
{
    int number_of_hidden_singles = 0;
    int candidate_counter[BOARD_SIZE];


    for(int i = 0; i < 9; i++)
    {
        candidate_counter[i] = 0; 
    }
     for(int i = 0; i < BOARD_SIZE; i++)
    {
         if(p_cells[i]->num_candidates > 1) 
         {
            int* candidates = get_candidates(p_cells[i]);
            for(int j = 0; j < p_cells[i]->num_candidates; j ++) 
            {
                candidate_counter[candidates[j] - 1] += 1;
            } 
            free(candidates);
         }
    }
    
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        if (candidate_counter[i] == 1)
        {
            
            possible_values[number_of_hidden_singles] = i + 1;
            number_of_hidden_singles += 1; 
        }
    }
    return number_of_hidden_singles;
}


bool is_in_list_hidden_single(HiddenSingle *p_array, int size, Cell *a)
{
    for (int i = 0; i < size; i++){
        if (p_array[i].p_cell == a) 
            return false;
    }
    return true;
}


void find_hidden_single(Cell **p_cells, HiddenSingle *p_hidden_singles,int *p_counter)
{
    int hidden_single_values[BOARD_SIZE];
    for(int i = 0; i < BOARD_SIZE; i ++)
    {
        hidden_single_values[i] = 0;
    
    } 
    int num_values = find_hidden_single_values(p_cells, hidden_single_values); 

    for(int i = 0; i < num_values; i++) 
    {
        for(int j = 0 ; j < BOARD_SIZE; j ++)
        {
            if (p_cells[j]->num_candidates > 1) 
            {
                int *candidates = get_candidates(p_cells[j]); 
                for(int k = 0; k < p_cells[j]->num_candidates; k ++)
                {
                    if((candidates[k] == hidden_single_values[i]) && (is_in_list_hidden_single(p_hidden_singles, *p_counter, p_cells[j])) == true)
                    {    
                        p_hidden_singles[*p_counter].p_cell = p_cells[j];
                        p_hidden_singles[*p_counter].value = hidden_single_values[i];
                        (*p_counter) += 1;
                    } 
                }
                free(candidates);
            }
        }
    }
}

