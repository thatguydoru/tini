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

#ifndef __TINI_ALLOCATOR_H__
#define __TINI_ALLOCATOR_H__

#include <stddef.h>

typedef struct TiniAllocatorVTable {
	void* (*alloc)(void* self, size_t n, size_t size);
	void* (*realloc)(void* self, void* ptr, size_t n, size_t size);
	void (*free)(void* self, void* ptr);
} TiniAllocatorVTable;

typedef struct TiniAllocator {
	void*                self;
	TiniAllocatorVTable* vtable;
} TiniAllocator;

void* tini_alloc(TiniAllocator allocator, size_t n, size_t size);
void* tini_realloc(TiniAllocator allocator, void* ptr, size_t n, size_t size);
void tini_free(TiniAllocator allocator, void* ptr);

#endif
