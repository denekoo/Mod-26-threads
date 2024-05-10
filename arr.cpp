#include "arr.h"

int Arr::random_gen()
{
	int n = 100;
	int num = std::rand() % n;
	return num;
}

void Arr::fill_array()
{
	std::srand(std::time(nullptr));
 
	for (int i = 0; i < m_array_size; ++i)
	{
		m_array.push_back(random_gen());
	}
}

void Arr::print_array(std::vector <int> array)
{
	size_t array_size = array.size();

	for (size_t i = 0; i < array_size; ++i)
	{
		std::cout << array[i] << " ";
	}
	std::cout << std::endl;
}

void Arr:: print_basic_array()
{
	print_array(m_array);
}

void Arr::part_arr()
{
	if (m_array_size <= m_threads_count)
	{
		std::cout << "Error: small array size or too many threads.";
		return;
	}

	int part_size = 0;
	part_size = m_array_size / m_threads_count;
	int counter = m_threads_count;
	int remain = m_array_size % m_threads_count;
	int j = 0;
	
	while (counter > 0)
	{
		if (m_array_size % m_threads_count != 0 && counter == 1)
		{
			part_size += remain;
		}
		std::vector<int> temp_vec;
		for (int i = 0; i < part_size; ++i)///
		{
			temp_vec.push_back(m_array[i + j]);
		}
		j += part_size;
		m_arr_vec.push_back(temp_vec);
		temp_vec.clear();
		--counter;
	}
}

void Arr:: print_parts()
{
	size_t count_parts = m_arr_vec.size();
	for (size_t i = 0; i < count_parts; ++i)
	{
		print_array(m_arr_vec[i]);
	}
}

/////////////// 

void Arr:: one_trhead_summ ()
{
	unsigned int start_time = std::clock();
	std::vector<int>::const_iterator it;
	it = m_array.begin();
	int sum = 0;
	while (it != m_array.end())
	{
		sum += *it;
		++it;
	}

	unsigned int end_time = std::clock();
	unsigned int duration_time = end_time - start_time;
	std::cout << "array sum is: " << sum << std::endl;
	std::cout << "time is: " << duration_time << "ms" << std::endl;
}


void  Arr::array_sum(int start_index, int end_index)
{
	std::mutex mutex;
	int sum = 0;
	for (int i = start_index; i <= end_index; ++i)
	{
		sum += m_array[i];
	}
	mutex.lock();
	m_summ += sum;
	mutex.unlock();
}

void Arr:: threads_sum_array(int threads_count)
{
	
	unsigned int start_time = std::clock();
	std::vector<std::thread> threads;
	int start_index = 0;
	int end_index = 0;
	int array_part = m_array_size / threads_count;
	m_summ = 0; 
	for (int i = 0; i < m_threads_count; ++i)
	{
		if( i == m_threads_count - 1)
		{
			end_index = start_index + array_part + m_array_size % threads_count - 1;
		}
		else
		{
			end_index = start_index + array_part - 1;
		}

		std::thread t (&Arr::array_sum, this, start_index, end_index);
		threads.push_back(std::move(t));
		start_index = end_index + 1;
	}
	for (auto& t : threads)
	{
		if (t.joinable())
			t.join();
	}
	std::cout << "summ is: " << m_summ << std::endl;
	unsigned int end_time = std::clock();
	unsigned int duration_time = end_time - start_time;
	std::cout << "time is: " << duration_time << "ms" << std::endl;
}


