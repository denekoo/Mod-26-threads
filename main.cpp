#include "arr.h"


int main()
{
	int threads = 3;
	int size = 1000000;

	Arr array(threads, size);
	array.fill_array();
	array.one_trhead_summ();
	array.threads_sum_array(threads);


}