#include <iostream>
#include <algorithm>
#include <queue>
#include <string>
#include <cmath>

#include "Huffman.h"
#include "common.h"

using namespace std;


/*
Huffman algorithm
1. generate the table of frequencies
determine:
- file size (number of bytes etc, number of characters)
- alphabet size (number of unique bytes, unique characters)
- symbol frequency
2. build the encoding tree
- put all of the leaf nodes in a priority queue based on their weights
- do the following until the priority queue is empty:
- delete the smallest two nodes.
- create a new node with these deleted nodes as children.
- set the parent pointers of the deleted nodes in the table.
- set the child type of the deleted nodes in the table.
3. encoding the characters
	- recurse through the tree in depth-first order, 
	and collect the bits as a path from the root (0 left 1 right)
	- build character : prefix code table


4. calculate entropy:
    entropy is the smallest number of bits neeed, on the average,
    to represent a symbol ( the average on all the symbols code
    lengths).
*/


Huffman::~Huffman(void)
{
	DeleteTree(m_tree);
}

void Huffman::Encode(const string& s)
{
    m_stats.n_symbols = s.size();
	if (m_tree != nullptr)
		DeleteTree(m_tree);

	m_tree = BuildHuffmanTree(s);
	m_enc_table.clear();
	GenerateEncodingTable(m_tree, m_enc_table, "");
	
	// perform actual encoding
	/*for (auto it = s.begin(); it != s.end(); ++it)
	    m_encoding += m_enc_table[*it];*/

	// caculate total bits
	for(auto it = m_enc_table.begin(); 
		it != m_enc_table.end(); 
		++it)
	    m_stats.n_bits += it->second.size() * m_freq_table[it->first];
	//	cout << it->first << "\t" << it->second << endl;

	// calculate entropy
	// summation of probabilites & log2
	// -SUM[s in symbols] (p(s) *log2(p(s)))
	for (auto it = m_freq_table.begin(); 
		it != m_freq_table.end(); ++it)
	{
	    double p_i = (double)it->second / s.size();
	    m_stats.entropy -= p_i * Log2(p_i);
	}

	// calculate bps (bits per symbol)
	m_stats.bps = (double)m_stats.n_bits / m_stats.n_symbols;
}

void Huffman::Stats()
{
    cout << "\t        symbols: " << m_stats.n_symbols << endl;
    cout << "\t        entropy: " << m_stats.entropy << endl;
    cout << "\tbits-per-symbol: " << m_stats.bps << endl;
    cout << "\t number-of-bits: " << m_stats.n_bits << endl;
    cout << "\tcompressed size: " << ceil(m_stats.n_bits / 8192.0) << " KB" << endl << endl;
}

Huffman::Node* Huffman::BuildHuffmanTree(const string& s)
{
	// const auto sz = s.length();

	//std::map<char, int> freq; // character frequency table
	std::priority_queue<Node*, std::vector<Node*>, CompareNode> pq_symbols;
	
	for (auto i = s.begin(); i != s.end(); ++i)
		m_freq_table[*i]++;

	//typedef map<char, int>::iterator iter;
	for(auto it = m_freq_table.begin(); 
		it != m_freq_table.end(); 
		++it)
		pq_symbols.push(new Node(it->first, it->second));


	while (pq_symbols.size() != 1)
	{
		Node* node = new Node();

		node->left = pq_symbols.top();
		pq_symbols.pop();

		node->right = pq_symbols.top();
		pq_symbols.pop();

		node->frequency = node->left->frequency + node->right->frequency;

		node->character = '\0'; 

		pq_symbols.push(node);
	}
	//cout << pq_symbols.size() << endl;
	Node* tree = pq_symbols.top();
	pq_symbols.pop();

	return tree;
}

void Huffman::GenerateEncodingTable(Node* tree, map<char, string>& tbl, string code)
{
	// check if leaf
	// true: store bit string "", return 
	//
	if (tree != nullptr)
	{
		if (tree->character != '\0')
		{
			tbl[tree->character] = code;
		}
		GenerateEncodingTable(tree->left, tbl, code + "0");
		GenerateEncodingTable(tree->right, tbl, code + "1");
	}
}

void Huffman::DeleteTree(Node* n)
{
	if (n != nullptr)
	{
		DeleteTree(n->left);
		DeleteTree(n->right);
		delete n;
	}
}
