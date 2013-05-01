#include <iostream>
#include <vector>
#include <cmath>

#include "common.h"
#include "Huffman.h"
#include "Arithmetic.h"

using namespace std;

int main(int argc, char **argv)
{
	/*
		compress data stream with both encoding schemes
		1) figure out what to use as data stream, input file?, array?
		2) write code for both compression schemes
		3) analyse compression efficiency by comparing entropy.
	*/
	if (argc < 2)
	{
		cout << "<program> dataset_1 dataset_2 dataset_3 ..." << endl;
		return 1;
	}
	
	vector<string> filenames;
	for (int i = 1; i < argc; ++i)
		filenames.push_back(string(argv[i]));
	//cout << filenames[0] << endl;
	//string dset = read_file(filenames[0]);
	//cout << dset.size() << endl;
	
	// perform encoding and print statistics for every file
	for (auto i = filenames.begin(); i != filenames.end(); ++i)
	{
		string dataset = read_file(*i);
		double filesize = ceil(dataset.size() / 1024.00);
		Huffman huff = Huffman();
		Arithmetic arith = Arithmetic();


		huff.Encode(dataset);
		cout << " [" << *i << " " << filesize << " KB"<<"]" << endl;
		cout << "    [-] Huffman" << endl;
		huff.Stats();

		// arith.Encode(dataset);
		cout << "    [-] Arithmetic" << endl;
		cout << endl << endl;
	}


	// use large string as input

	string s1 = "Lorem ipsum dolor sit amet, consectetur adipiscing \
elit. Nam semper dolor ac justo aliquam eget congue \
arcu accumsan. Aliquam et turpis ante, nec \
sollicitudin elit. Praesent eget faucibus enim. In \
ut mollis massa. Vivamus sodales tellus sed turpis \
eleifend auctor. Fusce a ipsum in nunc lacinia \
consectetur at nec ligula. Nulla facilisi. Quisque \
et mauris non massa consequat tincidunt sit amet in \
turpis. Donec congue iaculis elit et tempor. Vivamus \
sed ipsum et sapien rhoncus gravida eget ut magna.";
	// instantiate new huffman class

	string s2 = "fffffeeeeeeeeeccccccccccccbbbbbbbbbbbbbddddddddddddddddaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
	string s3 = "AAAAAAAAAAAAAAABBBBBBBCCCCCCDDDDDDEEEEE";	
	return 0;
}

