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

#include "slice.h"

const TiniIteratorVTable slice_fwd_iter_vtable = {tini_slice_iterator_next};
const TiniIteratorVTable slice_rev_iter_vtable = {tini_slice_iterator_rev_next};

TiniSlice tini_slice_new(void* items, size_t maxlen, size_t start, size_t end, size_t item_size) {
	if (start > end) {
		start = 0;
		end = 0;
	}

	start = start <= maxlen ? start : maxlen;
	end = end <= maxlen ? end : maxlen;

	return (TiniSlice){items + start * item_size, end - start, item_size};
}

void* tini_slice_at(const TiniSlice* slice, size_t index) {
	if (index >= slice->length) {
		return nullptr;
	}

	return slice->items + index * slice->item_size;
}

TiniSliceIterator tini_slice_iter(TiniSlice* slice) {
	return (TiniSliceIterator){slice, 0};
}

TiniSliceIterator tini_slice_rev_iter(TiniSlice* slice) {
	return (TiniSliceIterator){slice, slice->length};
}

void* tini_slice_iterator_next(void* self) {
	TiniSliceIterator* this = self;
	if (this->at >= this->slice->length) {
		return nullptr;
	}

	void* item = tini_slice_at(this->slice, this->at);
	this->at++;

	return item;
}

void* tini_slice_iterator_rev_next(void* self) {
	TiniSliceIterator* this = self;
	if (this->at == 0) {
		return nullptr;
	}

	void* item = tini_slice_at(this->slice, this->at - 1);
	this->at--;

	return item;
}

TiniIterator tini_slice_iterator_as_iterator(TiniSliceIterator* iterator) {
	return (TiniIterator){iterator, &slice_fwd_iter_vtable};
}

TiniIterator tini_slice_iterator_as_rev_iterator(TiniSliceIterator* iterator) {
	return (TiniIterator){iterator, &slice_rev_iter_vtable};
}
