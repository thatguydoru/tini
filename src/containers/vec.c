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

#include <string.h>

#include "vec.h"

const TiniIteratorVTable vec_fwd_iter_vtable = {tini_vec_iterator_next};
const TiniIteratorVTable vec_rev_iter_vtable = {tini_vec_iterator_rev_next};

bool ensure_capacity(TiniVec* vec) {
	if (vec->length < vec->capacity) {
		return true;
	}

	size_t capacity = vec->capacity * 2;
	void* realloced_items =
		tini_realloc(vec->allocator, vec->items, vec->capacity, capacity, vec->item_size);
	if (realloced_items == nullptr) {
		return false;
	}
	vec->items = realloced_items;
	vec->capacity = capacity;

	return true;
}

bool tini_vec_with_capacity(TiniVec* vec, size_t capacity, size_t item_size, TiniAllocator allocator) {
	*vec = (TiniVec){0};
	vec->items = tini_alloc(allocator, capacity, item_size);
	if (vec->items == nullptr) {
		return false;
	}
	vec->capacity = capacity;
	vec->item_size = item_size;
	vec->allocator = allocator;

	return true;
}

bool tini_vec_default(TiniVec* vec, size_t item_size, TiniAllocator allocator) {
	return tini_vec_with_capacity(vec, 8, item_size, allocator);
}

bool tini_vec_from_array(TiniVec* vec, void* array, size_t length, size_t item_size, TiniAllocator allocator) {
	if (!tini_vec_with_capacity(vec, length, item_size, allocator)) {
		return false;
	}

	memcpy(vec->items, array, length * item_size);
	vec->length = length;

	return true;
}

bool tini_vec_push(TiniVec* vec, void* item) {
	if (!ensure_capacity(vec)) {
		return false;
	}

	void* dest = vec->items + vec->length * vec->item_size;
	memcpy(dest, item, vec->item_size);
	vec->length++;

	return true;
}

bool tini_vec_extend(TiniVec* vec, const void* items, size_t length) {
	size_t capacity = vec->capacity + length;
	void* realloced_items =
		tini_realloc(vec->allocator, vec->items, vec->capacity, capacity, vec->item_size);
	if (realloced_items == nullptr) {
		return false;
	}

	void* dest = realloced_items + vec->length * vec->item_size;
	memcpy(dest, items, length);
	vec->items = realloced_items;
	vec->capacity = capacity;
	vec->length = vec->length + length;

	return true;
}

void* tini_vec_at(const TiniVec* vec, size_t index) {
	if (index >= vec->length) {
		return nullptr;
	}

	return vec->items + index * vec->item_size;
}

void tini_vec_free(TiniVec* vec) {
	tini_free(vec->allocator, vec->items);
	*vec = (TiniVec){0};
	vec->items = nullptr;
}

TiniVecIterator tini_vec_iter(TiniVec* vec) {
	return (TiniVecIterator){vec, 0};
}

TiniVecIterator tini_vec_iter_rev(TiniVec* vec) {
	return (TiniVecIterator){vec, vec->length};
}

void* tini_vec_iterator_next(void* self) {
	TiniVecIterator* this = self;
	if (this->at >= this->vec->length) {
		return nullptr;
	}

	void* item = tini_vec_at(this->vec, this->at);
	this->at++;

	return item;
}

void* tini_vec_iterator_rev_next(void* self) {
	TiniVecIterator* this = self;
	if (this->at == 0) {
		return nullptr;
	}

	void* item = tini_vec_at(this->vec, this->at - 1);
	this->at--;

	return item;
}

TiniIterator tini_vec_iterator_as_iterator(TiniVecIterator* iterator) {
	return (TiniIterator){iterator, &vec_fwd_iter_vtable};
}

TiniIterator tini_vec_iterator_as_rev_iterator(TiniVecIterator* iterator) {
	return (TiniIterator){iterator, &vec_rev_iter_vtable};
}
