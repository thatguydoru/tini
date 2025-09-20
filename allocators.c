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

#include <stdlib.h>

#include "allocators.h"

static TiniAllocatorVTable std_vtable = {
	tini_std_allocator_alloc,
	tini_std_allocator_realloc,
	tini_std_allocator_free
};

inline void* tini_alloc(TiniAllocator allocator, size_t n, size_t size) {
	return allocator.vtable->alloc(allocator.self, n, size);
}

inline void* tini_realloc(TiniAllocator allocator, void* ptr, size_t n, size_t size) {
	return allocator.vtable->realloc(allocator.self, ptr, n, size);
}

inline void tini_free(TiniAllocator allocator, void* ptr) {
	return allocator.vtable->free(allocator.self, ptr);
}

void* tini_std_allocator_alloc(void* _, size_t n, size_t size) {
	return calloc(n, size);
}

void* tini_std_allocator_realloc(void* _, void* ptr, size_t n, size_t size) {
	return realloc(ptr, n * size);
}

void tini_std_allocator_free(void* _, void* ptr) {
	free(ptr);
}

TiniAllocator tini_std_allocator_as_allocator(TiniStdAllocator* allocator) {
	return (TiniAllocator){allocator, &std_vtable};
}
