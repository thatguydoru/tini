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

#ifndef __TINI_ALLOCATORS_STD_ALLOC_H__
#define __TINI_ALLOCATORS_STD_ALLOC_H__

#include "../allocator.h"

typedef struct TiniStdAllocator{} TiniStdAllocator;

void* tini_std_allocator_alloc(void* self, size_t n, size_t size);
void* tini_std_allocator_realloc(void* self, void* ptr, size_t old_n, size_t n, size_t size);
void tini_std_allocator_free(void* self, void* ptr);
TiniAllocator tini_std_allocator_as_allocator(TiniStdAllocator* allocator);

#endif
