#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

map<char, string> codes;

vector< pair<char, int> > FrequencyDect(string s)
{
    map<char, int> mp;
    for (size_t i = 0; i < s.size(); i++)
    {
        mp[s[i]]++;
    }
    vector< pair<char, int> > v;
    for (map<char, int>::iterator it = mp.begin(); it != mp.end(); it++)
    {
        v.push_back(make_pair(it->first, it->second));
    }
    return v;
}

// A Huffman tree node
struct MinHeapNode
{

    // One of the input characters
    char data;

    // Frequency of the character
    unsigned freq;

    // Left and right child
    MinHeapNode *left, *right;

    MinHeapNode(char data, unsigned freq)

    {

        left = right = NULL;
        this->data = data;
        this->freq = freq;
    }
};

// Prints huffman codes from
// the root of Huffman Tree.
// void printCodes(struct MinHeapNode *root, string str)
// {
//     if (!root)
//         return;

//     if (root->data != '$')
//         cout << root->data << ": " << str << "\n";

//     printCodes(root->left, str + "0");
//     printCodes(root->right, str + "1");
// }

void storeCodes(struct MinHeapNode *root, string str)
{
    if (root == NULL)
        return;
    if (root->data != '$')
        codes[root->data] = str;
    storeCodes(root->left, str + "0");
    storeCodes(root->right, str + "1");
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void HuffmanCodes(char data[], int freq[], int size)
{
    struct MinHeapNode *left, *right, *top;

    // Create a min heap & inserts all characters of data[]

    vector<MinHeapNode *> buildMinHeap;

    for (int i = 0; i < size; i++)
    {
        buildMinHeap.push_back(new MinHeapNode(data[i], freq[i]));
    }

    for (int i = 0; i < size - 1; i++)
    {
        for (int j = size - 1; j > i; j--)
        {
            if (buildMinHeap[j]->freq < buildMinHeap[j - 1]->freq)
            {
                swap(buildMinHeap[j], buildMinHeap[j - 1]);
            }
        }
    }
    // Iterate while size of heap doesn't become 1
    while (buildMinHeap.size() != 1)
    {
        left = buildMinHeap[0];
        buildMinHeap.erase(buildMinHeap.begin());

        right = buildMinHeap[0];
        buildMinHeap.erase(buildMinHeap.begin());

        top = new MinHeapNode('$', left->freq + right->freq);

        top->left = left;
        top->right = right;

        buildMinHeap.push_back(top);

        int n = buildMinHeap.size();

        for (int i = 0; i < n - 1; i++)
        {
            for (int j = n - 1; j > i; j--)
            {
                if (buildMinHeap[j]->freq < buildMinHeap[j - 1]->freq)
                {
                    swap(buildMinHeap[j], buildMinHeap[j - 1]);
                }
            }
        }
        storeCodes(buildMinHeap[0], "");
        // printCodes(buildMinHeap[0], "");
    }
     if(buildMinHeap.size() == 1){
        right = buildMinHeap[0];
        buildMinHeap.erase(buildMinHeap.begin());
        top = new MinHeapNode('$', right->freq);
        top->right = right;
        buildMinHeap.push_back(top);
        storeCodes(buildMinHeap[0], "");
    }

}

int binaryToDecimal(string n)
{
    int decimal = 0;
    int power = 0;
    for (int i = n.size() - 1; i >= 0; i--)
    {
        if (n[i] == '1')
        {
            decimal += pow(2, power);
        }
        power++;
    }
    return decimal;
}

int main()
{
    string s = "lXgrZQvoURVTMhLbVVcHWOyugszQQQQQQ";
    vector< pair<char, int> > freq = FrequencyDect(s);
    int size = freq.size();
    char *arr = new char[size];
    int *frequency = new int[size];
    for (int i = 0; i < size; i++)
    {
        arr[i] = freq[i].first;
        frequency[i] = freq[i].second;
    }
    HuffmanCodes(arr, frequency, size);

    string encodedString;
    for (int i = 0; i < s.size(); i++)
    {
        char i_char = s[i];
        encodedString += codes[i_char];
    }
    string last15Bits = encodedString;
    if (encodedString.size() > 15)
        last15Bits = encodedString.substr(encodedString.size() - 15);
    int decimal = binaryToDecimal(last15Bits);
    cout << last15Bits << endl;
    cout << decimal << endl;

    return 0;
}