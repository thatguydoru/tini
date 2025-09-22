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
#include <string.h>

#include "std_alloc.h"

const TiniAllocatorVTable std_vtable = {
	tini_std_allocator_alloc,
	tini_std_allocator_realloc,
	tini_std_allocator_free
};

void* tini_std_allocator_alloc(void* _, size_t n, size_t size) {
	return calloc(n, size);
}

void* tini_std_allocator_realloc(void* _, void* ptr, size_t old_n, size_t n, size_t size) {
	if (old_n == n) {
		return ptr;
	}

	ptr = realloc(ptr, n * size);
	if (ptr != nullptr && n > old_n) {
		memset(ptr + n * size, 0, (n - old_n) * size);
	}

	return ptr;
}

void tini_std_allocator_free(void* _, void* ptr) {
	free(ptr);
}

TiniAllocator tini_std_allocator_as_allocator(TiniStdAllocator* allocator) {
	return (TiniAllocator){allocator, &std_vtable};
}
