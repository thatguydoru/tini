#include <stdio.h>

#include "allocators/std_alloc.h"
#include "containers/vec.h"

#define MAX_NUMS 5

int main(void) {
	TiniStdAllocator std_alloc;
	TiniAllocator alloca = tini_std_allocator_as_allocator(&std_alloc);

	int nums[MAX_NUMS] = {1, 2, 3, 4, 5};
	tini_vec_t(int) vec_nums;
	tini_vec_from_array(&vec_nums, nums, MAX_NUMS, sizeof(int), alloca);

	TiniVecIterator rev = tini_vec_iterator_rev_new(&vec_nums);
	TiniIterator iter = tini_vec_iterator_as_rev_iterator(&rev);

	tini_foreach (int, num, iter) {
		printf("%d ", *num);
	}

	tini_vec_free(&vec_nums);

	return 0;
}
