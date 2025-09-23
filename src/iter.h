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

#ifndef __TINI_ITER_H__
#define __TINI_ITER_H__

#include <stddef.h>

#include "preamble.h"
#include "allocator.h"

#define tini_foreach(T, id, iter) for (T* id = tini_next(iter); id != nullptr; id = tini_next(iter))

tini_interface_def(
    TiniIterator,
		void* (*next)(void* self);
);

void* tini_next(TiniIterator iterator);
size_t tini_count(TiniIterator iterator);
void* tini_find(TiniIterator iterator, void* target, bool(*test)(void* target, void* item));
bool tini_all(TiniIterator iterator, bool (*test)(void* item));

#endif
