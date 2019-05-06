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

/* gcc -I. cell.c -shared -o libcell.so */


#include <cell.h>


cell *cell_create(void *initial_data) {
	cell *_cell = (cell *)malloc(sizeof(cell));
	if (_cell != NULL) {
		_cell->previous = NULL;
		_cell->data = initial_data;
		_cell->next = NULL;
	}
	
	return _cell;
}
int cell_length(cell *one_of_them) {
	if (one_of_them == NULL) return 0;
	
	cell *_cell = one_of_them;
	while (_cell->previous != NULL) _cell = _cell->previous;
	
	int _nth = 1;
	while (_cell->next != NULL) {_cell = _cell->next; _nth++;}
	
	return _nth;
}
cell *cell_nth(cell *one_of_them, int nth) {
	if (nth < -1) return NULL;
	
	int _length = cell_length(one_of_them);
	if (nth >= _length) return NULL;
	int _nth = nth;
	if (_nth == -1) _nth = _length - 1;
	
	cell *_cell = one_of_them;
	while (_cell->previous != NULL) _cell = _cell->previous;
	int _nth1 = 0;
	while (_cell->next != NULL) {
		if (_nth1 == _nth) break;
		_cell = _cell->next;
		_nth1++;
	}
	
	return _cell;
}
void cell_insert(cell *one_of_them, int as_nth, void *initial_data) {
	if (as_nth < -1) return;
	int _length = cell_length(one_of_them);
	if (as_nth > _length) return;
	
	int _nth = as_nth;
	if (_nth == -1) _nth = _length;
	cell *_cell = cell_create(initial_data);
	if (_nth >= 1) {
		cell *_cellLeft = cell_nth(one_of_them, _nth - 1);
		_cellLeft->next = _cell;
		_cell->previous = _cellLeft;
	}
	if (_nth < _length) {
		cell *_cellRight = cell_nth(one_of_them, _nth);
		_cellRight->previous = _cell;
		_cell->next = _cellRight;
	}
}
void cell_delete(cell *one_of_them, char unallocate_data) {
	if (one_of_them == NULL) return;
	
	cell *_cell = one_of_them;
	if (unallocate_data == 1) free(_cell->data);
	if (_cell->previous != NULL) _cell->previous->next = _cell->next;
	if (_cell->next != NULL) _cell->next->previous = _cell->previous;
	free(_cell);
}
cell *cell_delete_empties(cell *one_of_them) {
	if (one_of_them == NULL) return NULL;
	
	cell *_cell = cell_nth(one_of_them, 0);
	while (one_of_them != NULL) {
		if (_cell->data == NULL) {
			if (_cell->previous != NULL) {
				_cell = _cell->previous;
				cell_delete(_cell->next, 0);
			}
			else if (_cell->next != NULL) {
				_cell = _cell->next;
				cell_delete(_cell->previous, 0);
			}
			else {
				cell_delete(_cell, 0);
				return NULL;
			}
		}
		else {
			if (_cell->next == NULL) return cell_nth(_cell, 0);
			else _cell = _cell->next;
		}
	}
	
	return _cell;
}
void cell_delete_all(cell *one_of_them, char unallocate_data) {
	if (one_of_them == NULL) return;
	
	cell *_cell = one_of_them;
	while (_cell->previous != NULL) _cell = _cell->previous;
	while (_cell->next != NULL) {
		_cell = _cell->next;
		cell_delete(_cell->previous, unallocate_data);
		_cell->previous = NULL;
	}
	cell_delete(_cell, unallocate_data);
}
