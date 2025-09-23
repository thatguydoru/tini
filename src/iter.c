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

#include "iter.h"

void* tini_next(TiniIterator iterator) {
	return iterator.vtable->next(iterator.self);
}

size_t tini_count(TiniIterator iterator) {
	size_t count = 0;
	tini_foreach (void, _, iterator) {
		count++;
	}

	return count;
}

void* tini_find(TiniIterator iterator, void* target, bool (*test)(void* target, void* item)) {
	tini_foreach (void, item, iterator) {
		if (test(target, item)) {
			return item;
		}
	}

	return nullptr;
}

bool tini_all(TiniIterator iterator, bool (*test)(void* item)) {
	tini_foreach (void, item, iterator) {
		if (!test(item)) {
			return false;
		}
	}

	return true;
}
