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

#ifndef __TINI_CONTAINERS_SLICE_H__
#define __TINI_CONTAINERS_SLICE_H__

#include <stddef.h>

#include "../iter.h"

#define tini_arrlen(x) sizeof(x) / sizeof(x[0])
#define tini_slice_t(T) TiniSlice

typedef struct TiniSlice {
	void*  items;
	size_t length;
	size_t item_size;
} TiniSlice;

TiniSlice tini_slice_new(void* items, size_t maxlen, size_t start, size_t end, size_t item_size);
void* tini_slice_at(const TiniSlice* slice, size_t index);

typedef struct TiniSliceIterator {
	TiniSlice* slice;
	size_t     at;
} TiniSliceIterator;

TiniSliceIterator tini_slice_iter(TiniSlice* slice);
TiniSliceIterator tini_slice_rev_iter(TiniSlice* slice);
void* tini_slice_iterator_next(void* self);
void* tini_slice_iterator_rev_next(void* self);
TiniIterator tini_slice_iterator_as_iterator(TiniSliceIterator* iterator);
TiniIterator tini_slice_iterator_as_rev_iterator(TiniSliceIterator* iterator);

#endif
