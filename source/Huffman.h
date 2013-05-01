#ifndef Huffman_h
#define Huffman_h


#include <map>
#include <vector>
#include <queue>


struct statistics
{
	int n_symbols;
    int n_bits;
    double entropy;
    double bps;
    statistics() : n_bits(0), n_symbols(0),
   		   entropy(0), bps(0) {}

};

class Huffman
{
public:
	Huffman(void) : m_tree (nullptr), m_encoding("") {};
	~Huffman(void);

	//void compress(const std::string s);
	void Encode(const std::string& s);
	void Stats();

private:
	struct Node
	{
		char character;
		int frequency;

		Node* left;
		Node* right;

		Node(char ch, int freq) : 
		    character(ch), 
		    frequency(freq), 
		    left(nullptr), 
		    right(nullptr) {}
		Node() : left(nullptr), right(nullptr) {}
	};

	struct CompareNode : public std::binary_function<Node*, 
	Node*, bool>
	{
		bool operator()(const Node* lhs, const Node* rhs) const
		{
			return lhs->frequency > rhs->frequency;
		}
	};

	// std::vector<std::pair<char, int>> m_freqTable;
	Node* BuildHuffmanTree(const std::string&);
	void GenerateEncodingTable(Node* tree, std::map<char, std::string>& tbl, std::string code);
	void DeleteTree(Node* n);

	Node* m_tree; // huffman tree, used to generate encoding table
        // character frequency table
	std::map<char, int> m_freq_table;	
	std::map<char, std::string> m_enc_table; // encoding table
	
	statistics m_stats;
	std::string m_encoding;

};

#endif
