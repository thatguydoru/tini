#include <stdio.h>

#include "src/allocators/std_alloc.h" // tini/allocators/std_alloc.h
#include "src/containers/slice.h" // tini/containers/array.h
#include "src/containers/vec.h" // tini/containers/vec.h

bool bigger_than_three(void* item) {
	int* n = item;

	return *n > 3;
}

bool int_eq(void* target, void* item) {
	int* a = target;
	int* b = item;

	return *a == *b;
}

int main(void) {
	TiniStdAllocator std_alloc;
	TiniAllocator alloca = tini_std_allocator_as_allocator(&std_alloc);

	int nums[] = {1, 2, 3, 4, 5};
	tini_vec_t(int) vec_nums;
	tini_vec_from_array(&vec_nums, nums, tini_arrlen(nums), sizeof(int), alloca);

	TiniVecIterator rev = tini_vec_iter_rev(&vec_nums);
	TiniIterator iter = tini_vec_iterator_as_rev_iterator(&rev);
	tini_foreach (int, num, iter) {
		printf("%d ", *num);
	}
	putchar('\n');

	rev = tini_vec_iter_rev(&vec_nums);
	iter = tini_vec_iterator_as_rev_iterator(&rev);
	printf("all: %d\n", tini_all(iter, bigger_than_three));

	rev = tini_vec_iter(&vec_nums);
	iter = tini_vec_iterator_as_iterator(&rev);
	printf("equal count? %d\n", tini_count(iter) == tini_arrlen(nums));

	rev = tini_vec_iter(&vec_nums);
	iter = tini_vec_iterator_as_iterator(&rev);
	int target = 3;
	printf("find? %d\n", *(int*)tini_find(iter, &target, int_eq) == target);

	tini_vec_free(&vec_nums);

	tini_slice_t(int) sliced = tini_slice_new(nums, tini_arrlen(nums), 5, 4, sizeof(int));
	TiniSliceIterator rev_slice = tini_slice_rev_iter(&sliced);
	iter = tini_slice_iterator_as_rev_iterator(&rev_slice);
	tini_foreach (int, num, iter) {
		printf("%d ", *num);
	}
	putchar('\n');

	return 0;
}
