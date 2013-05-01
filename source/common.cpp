#include <fstream>
#include <string>
#include <utility>
#include <cmath>
#include "common.h"

using namespace std;

double Log2(double n)
{
	return log(n) / log(2);
}

bool compare(const pair<char, int>& x, const pair<char, int>& y)
{
	return x.second < y.second;
}

std::string read_file(const std::string filename)
{
	std::ifstream in(filename, std::ios::in | std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}
