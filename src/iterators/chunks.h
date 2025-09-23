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

#ifndef __TINI_ITERATORS_CHUNKS_H__
#define __TINI_ITERATORS_CHUNKS_H__

#include "../iter.h"
#include "../containers/vec.h"
#include "../containers/slice.h"

typedef struct TiniChunksIterator {
    TiniIterator      iterator;
    tini_vec_t(void*) chunk;
    size_t            chunk_size;
} TiniChunksIterator;

bool tini_chunks_iterator_init(TiniChunksIterator* chunker, TiniIterator iterator, size_t chunk_size, TiniAllocator allocator);
void* tini_chunks_iterator_next(void* self);
TiniIterator tini_chunks_iterator_as_iterator(TiniChunksIterator* chunker);
TiniIterator tini_chunks(TiniIterator iterator, size_t chunk_size, TiniAllocator allocator);

#endif
