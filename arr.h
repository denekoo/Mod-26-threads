#pragma once
#include <vector>
#include <cstdlib> // for std::rand()
#include <ctime>
#include <iostream>
#include <ctime>
#include<thread>


class Arr
{
private:
	std::vector <int> m_array;
	int m_threads_count;
	int m_array_size;
	std::vector<std::vector<int>> m_arr_vec;
	int m_summ = 0;

public:
	Arr(int threads, int array_size) : m_threads_count(threads), m_array_size(array_size)  {}

	int random_gen();
	void fill_array();
	void print_array(std::vector <int> array);
	void print_basic_array();
	void part_arr();
	void print_parts();

	void array_sum(int start_index, int end_index);
	void one_trhead_summ();
	void threads_sum_array(int threads_count);


};

