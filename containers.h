/*
   Copyright 2025 James O. Torres

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#ifndef __TINI_CONTAINERS_H__
#define __TINI_CONTAINERS_H__

#include <stdbool.h>
#include <stddef.h>

#include "allocators.h"

#define tini_vec_t(T) TiniVec

#define tini_foreach(T, id, iter) for (T* id = tini_next(iter); id != NULL; id = tini_next(iter))

typedef struct TiniIteratorVTable {
	void* (*next)(void* self);
} TiniIteratorVTable;

typedef struct TiniIterator {
	void*               self;
	TiniIteratorVTable* vtable;
} TiniIterator;

void* tini_next(TiniIterator iterator);

typedef struct TiniVec {
	void*         items;
	size_t        length;
	size_t        capacity;
	size_t        item_size;
	TiniAllocator allocator;
} TiniVec;

bool tini_vec_with_capacity(TiniVec* vec, size_t capacity, size_t item_size, TiniAllocator allocator);
bool tini_vec_default(TiniVec* vec, size_t item_size, TiniAllocator allocator);
bool tini_vec_from_array(TiniVec* vec, void* array, size_t length, size_t item_size, TiniAllocator allocator);
bool tini_vec_push(TiniVec* vec, void* item);
bool tini_vec_extend(TiniVec* vec, const void* items, size_t length);
void* tini_vec_at(const TiniVec* vec, size_t index);
void tini_vec_free(TiniVec* vec);

typedef struct TiniVecIterator {
	TiniVec* vec;
	size_t   at;
} TiniVecIterator;

TiniVecIterator tini_vec_iterator_new(TiniVec* vec);
void* tini_vec_iterator_next(void* self);
TiniIterator tini_vec_iterator_as_iterator(TiniVecIterator* iterator);

typedef struct TiniVecRevIterator {
	TiniVec* vec;
	size_t   at;
} TiniVecRevIterator;

TiniVecRevIterator tini_vec_rev_iterator_new(TiniVec* vec);
void* tini_vec_rev_iterator_next(void* self);
TiniIterator tini_vec_rev_iterator_as_iterator(TiniVecIterator* iterator);

#endif
