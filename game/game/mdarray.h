#pragma once
#include <array>
template <class T, int S> 
class md_array
{
public:
	template<typename... Sizes>
	md_array(Sizes... sizes)
	{
		int args[] = { sizes... };
		int total = 0;
		for(int i = 0; i < S; i++)
		{
			this->sizes[i] = args[i];
			if(i == 0)
			{
				total = args[i];
			} else
			{
				total *= args[i];
			}
		}
		this->data = new T[total];
	};
	template<typename... Sizes>
	T& operator()(Sizes... indices)
	{
		int args[] = { indices... };
		int index = 0;
		int sizeOfTotal = 1;
		for(int i = S - 1; i >= 0; i--)
		{
			index += args[i] * sizeOfTotal;
			sizeOfTotal *= this->sizes[i];
		}
		return this->data[index];
	};
	template<typename... Sizes>
	const T& operator()(Sizes... indices) const
	{
		int args[] = { indices... };
		int index = 0;
		int sizeOfTotal = 1;
		for(int i = S - 1; i >= 0; i--)
		{
			index += args[i] * sizeOfTotal;
			sizeOfTotal *= this->sizes[i];
		}
		return this->data[index];
	};
	template<typename... Sizes>
	T& get(Sizes... indices)
	{
		int args[] = { indices... };
		int index = 0;
		int sizeOfTotal = 1;
		for(int i = S - 1; i >= 0; i--)
		{
			index += args[i] * sizeOfTotal;
			sizeOfTotal *= this->sizes[i];
		}
		return this->data[index];
	};

	template<typename... Sizes>
	const T& get(Sizes... indices) const
	{
		int args[] = { indices... };
		int index = 0;
		int sizeOfTotal = 1;
		for(int i = S - 1; i >= 0; i--)
		{
			index += args[i] * sizeOfTotal;
			sizeOfTotal *= this->sizes[i];
		}
		return this->data[index];
	};
	

	T& operator[](int i)
	{
		return this->data[i];
	}

	int getSize(int index) const
	{
		return this->sizes[index];
	}

private:

	std::array<int, S> sizes;
	T* data;
};