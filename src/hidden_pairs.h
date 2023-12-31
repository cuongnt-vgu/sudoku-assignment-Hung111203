#pragma once

#include "sudoku.h"

typedef struct HiddenPair_impl
{
    int value1;
    int value2;
    Cell *p_cell;
} HiddenPair;

int hidden_pairs(SudokuBoard *p_board);

int find_hidden_pairs_values(Cell **p_cells, int *hidden_pairs_values);

void find_hidden_pairs(Cell **p_cells, HiddenPair *p_hidden_pairs, int *p_counter);
bool is_hidden_pair(Cell **p_cells, int value1, int value2);
bool is_in_cell(Cell *p_cell, int value1, int value2);
bool is_candidate(Cell*cell, int value);