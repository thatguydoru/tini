#include <stdio.h>
#include <stdlib.h>

#include "chunks.h"

const TiniIteratorVTable chunk_iter_vtable = {tini_chunks_iterator_next};

bool tini_chunks_iterator_init(
    TiniChunksIterator* chunker, TiniIterator iterator, size_t chunk_size, TiniAllocator allocator
) {
	bool ok = tini_vec_with_capacity(&chunker->chunk, chunk_size, sizeof(void*), allocator);
	if (!ok) {
		return false;
	}
	chunker->iterator = iterator;
	chunker->chunk_size = chunk_size;

	return true;
}

void* tini_chunks_iterator_next(void* self) {
	TiniChunksIterator* this = self;
	if (this->chunk_size == 0) {
		return nullptr;
	}

	tini_vec_clear(&this->chunk);
	for (size_t i = 0; i < this->chunk_size; i++) {
		void* item = tini_next(this->iterator);
		if (item == nullptr) {
			if (this->chunk.slice.length == 0) {
				tini_vec_free(&this->chunk);
				return nullptr;
			}
			break;
		}
		tini_vec_push(&this->chunk, &item);
	}

	return &this->chunk.slice;
}

TiniIterator tini_chunks_iterator_as_iterator(TiniChunksIterator* chunker) {
	return (TiniIterator){chunker, &chunk_iter_vtable};
}

TiniIterator tini_chunks(TiniIterator iterator, size_t chunk_size, TiniAllocator allocator) {
	TiniChunksIterator* chunker = tini_alloc(allocator, 1, sizeof(TiniChunksIterator));
	if (!tini_chunks_iterator_init(chunker, iterator, chunk_size, allocator)) {
		puts("tini: chunks: failed to init chunks iterator");
		exit(1);
	}

	return tini_chunks_iterator_as_iterator(chunker);
}
