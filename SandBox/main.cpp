#include <thread>
#include <iostream>
#include <future>

typedef unsigned long long int ULL;
ULL Fact(std::future<int>&& fut)
{

	auto N = fut.get(); //It is waiting for a value to be set by the promise
	ULL result{ 1 };
	for (int i = 2; i <= N; ++i)
	{
		result *= i;
	}
	return result;
}

int main()
{
	std::promise<int> prms;
	std::future<int> fut = prms.get_future();
	std::future<ULL> fut_result = std::async(std::launch::async, Fact, std::move(fut));
	prms.set_value(5);
	std::cout << fut_result.get() << '\n'; //It is waiting for a value to be returned by the Fact function.

}
