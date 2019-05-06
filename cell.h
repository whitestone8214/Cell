/*
	Copyright (C) 2019 Minho Jo <whitestone8214@gmail.com>
	
	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.
	
	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.
	
	You should have received a copy of the GNU Lesser General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <malloc.h>
#include <stdlib.h>
#include <unistd.h>
#include <libgen.h>
#include <stdarg.h>


#ifndef TURNED_ON_CELL
#define TURNED_ON_CELL

typedef struct cell cell;

struct cell {cell *previous; void *data; cell *next;};


cell *cell_create(void *initial_data);
int cell_length(cell *one_of_them);
cell *cell_nth(cell *one_of_them, int nth);
void cell_insert(cell *one_of_them, int as_nth, void *initial_data);
void cell_delete(cell *one_of_them, char unallocate_data);
cell *cell_delete_empties(cell *one_of_them);
void cell_delete_all(cell *one_of_them, char unallocate_data);

#endif
