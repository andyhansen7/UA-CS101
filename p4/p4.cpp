/* Project 4 -  Huffan Tree Decoding
 * By Andy Hansen
 * 4/4/2020
 *CS101-001
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

//#define _DEBUG_

using namespace std;

class HuffmanTreeNode
{
public:
    HuffmanTreeNode(int value)
        : _value(value), _ascii(value),  _internal(value > 127)
    {
        #ifdef _DEBUG_
            cout << (_internal ? "Internal" : "External");
            cout << "HuffmanTreeNode object created with value " << value << endl;
        #endif
    }

    void SetParent(HuffmanTreeNode* parent)
    {
        _parent = parent;
    }

    void SetLeftChild(HuffmanTreeNode* child)
    {
        _lChild = child;
    }

    void SetRightChild(HuffmanTreeNode* child)
    {
        _rChild = child;
    }

    HuffmanTreeNode* GetParent()
    {
        return _parent;
    }

    HuffmanTreeNode* GetLeftChild()
    {
        return _lChild;
    }

    HuffmanTreeNode* GetRightChild()
    {
        return _rChild;
    }

    void SetBinId(string ID)
    {
        _binId = ID;
    }

    int GetValue()
    {
        return _value;
    }

    char GetCharacter()
    {
        return _ascii;
    }

    string GetBinId()
    {
        return _binId;
    }

    bool GetInternal()
    {
        return _internal;
    }

private:
    int _value = 0;
    char _ascii = '\0';
    bool _internal = false;
    string _binId = "";

    HuffmanTreeNode* _parent = NULL;
    HuffmanTreeNode* _lChild = NULL;
    HuffmanTreeNode* _rChild = NULL;
};

class HuffmanTree
{
public:
    HuffmanTree()
    {
        #ifdef _DEBUG_
            cout << "HuffmanTree object created." << endl;
        #endif
    }

    // reads integers into inorder array
    void ReadInOrder(string text)
    {
        stringstream ss;
        string tmp;
        int found;

        ss << text;

        #ifdef _DEBUG_
            cout << "Function ReadInOrder() called." << endl;
        #endif

        // scan ints into array
        while(!ss.eof())
        {
            ss >> tmp;

            if(stringstream(tmp) >> found)
            {
                _inorder[_inorderCount] = found;
                _inorderCount++;

                #ifdef _DEBUG_
                    cout << "\tInOrder added " << found << " to index " << _inorderCount - 1 << endl;
                #endif
            }

            tmp = "";
        }

        _inorderRead = true;
    }

    // reads integers into postorder array 
    void ReadPostOrder(string text)
    {
        stringstream ss;
        string tmp;
        int found;

        ss << text;

        #ifdef _DEBUG_
            cout << "Function ReadPostOrder() called." << endl;
        #endif

        // scan ints into array
        while(!ss.eof())
        {
            ss >> tmp;

            if(stringstream(tmp) >> found)
            {
                _postorder[_postorderCount] = found;
                _postorderCount++;

                #ifdef _DEBUG_
                    cout << "\tPostOrder added " << found << " to index " << _postorderCount - 1 << endl;
                #endif
            }

            tmp = "";
        }

        _postorderRead = true;
    }

    // builds a huffman tree using the private postorder and inorder arrays
    bool Build()
    {
        #ifdef _DEBUG_
            cout << "Function Build() called." << endl;
        #endif

        if(!_postorderRead || !_inorderRead)
        {
            Warn("Both transversals must be loaded before creating the tree. Aborting Build()");
            return false;
        }
        else if(_postorderCount != _inorderCount)
        {
            Warn("The provided transversals did not have the same number of values. Aborting Build()");
            return false;
        }
        else
        {
            _count = _inorderCount;

            _head = BuildSubTree(_inorder, _postorder, 0, _inorderCount);

            #ifdef _DEBUG_
                cout << "Inorder transversal:" << endl;
                PrintInOrder(_head);
                cout << endl << "Postorder transversal:" << endl;
                PrintPostOrder(_head);
                cout << endl;
            #endif

            AssignKeys(_head->GetLeftChild(), "");

            #ifdef _DEBUG_
                cout << "Binary string IDs:" << endl;
                PrintIds(_head);
            #endif

            return true;
        }
    }

    // recursive function called to build branches of the tree by Build()
    HuffmanTreeNode* BuildSubTree(int inorder[], int postorder[], int inorderStart, int inorderEnd)
    {
        // base case
        if(inorderStart > inorderEnd) return NULL;

        HuffmanTreeNode* node = new HuffmanTreeNode(postorder[_count]);

        #ifdef _DEBUG_
            cout << "Created node for value " << postorder[_count] << endl;
        #endif

        _count--;

        // if there are no children to add, return node
        if(inorderStart == inorderEnd) return node;

        // find the index of the node in the inorder transversal    
        int index = GetIndex(inorder, inorderStart, inorderEnd, node->GetValue());

        // recursive function call
        node->SetRightChild(BuildSubTree(inorder, postorder, index + 1, inorderEnd));
        node->SetLeftChild(BuildSubTree(inorder, postorder, inorderStart, index - 1));

        return node;
    }

    // return the index of matchin value in array
    int GetIndex(int array[], int start, int end, int value)
    {
        int i;
        for(i = start; i < end; i++)
        {
            if(array[i] == value) break;
        }
        return i;
    }

    // assign binary keys to each node using inorder transversal
    void AssignKeys(HuffmanTreeNode* node, string id)
    {
        // Left Parent Right

        // base case
        if(node == NULL) return;

        AssignKeys(node->GetLeftChild(), id + "0");
        node->SetBinId(id);
        AssignKeys(node->GetRightChild(), id + "1");
    }

    // decode the provided text by finding each node in the string, and replacing its string identifier with a character
    string Decode(string text)
    {
        string textcopy = text;
        string decoded = "";
        int count = 0;

        #ifdef _DEBUG_
            cout << "Function Decode() called." << endl;
        #endif

        while(true)
        {
            // base case
            if(count == int(textcopy.length())) break;

            string tmp = textcopy.substr(0, count+1);
            
            char add = FindInTree(tmp, _head);

            if(add != '\0')
            {
                decoded += add;
                textcopy = textcopy.substr(count+1);
                #ifdef _DEBUG_
                    cout << "Letter " << add << " found, new string is " << textcopy << endl;
                #endif
                count = 0;
            }
            else
            {
                count++;
            }
            
        }
        return decoded;
    }

    // return character from string id in tree, if one is found, using inorder transversal
    char FindInTree(string ID, HuffmanTreeNode* node)
    {
        // Left Parent Right

        // base case
        if(node == NULL) return '\0';

        char left = FindInTree(ID, node->GetLeftChild());
        char parent = (node->GetInternal() ? '\0' : (ID.compare(node->GetBinId()) == 0 ? node->GetCharacter() : '\0'));
        char right = FindInTree(ID, node->GetRightChild());

        if(left != '\0') return left;
        if(parent != '\0') return parent;
        if(right != '\0') return right;

        return '\0';
    }
    
private:
    HuffmanTreeNode* _head = NULL;

    int _inorder[5000];
    int _postorder[5000];

    int _inorderCount = 0;
    int _postorderCount = 0;
    int _count;

    bool _inorderRead = false;
    bool _postorderRead = false;

    // function to warn user of errors
    void Warn(string message)
    {
        cout << "[WARNING] " << message << endl;
    }

    // prints inorder transversal, for testing purposes
    void PrintInOrder(HuffmanTreeNode* node)
    {
        // Left Parent Right

        // base case
        if(node == NULL) return;

        PrintInOrder(node->GetLeftChild());
        if(node->GetInternal()) cout << node->GetValue() << " ";
        else cout << node->GetCharacter() << " ";
        PrintInOrder(node->GetRightChild());
    }

    // prints postorder transversal, for testing purposes
    void PrintPostOrder(HuffmanTreeNode* node)
    {
        // Left Right Parent

        // base case
        if(node == NULL) return;

        PrintPostOrder(node->GetLeftChild());
        PrintPostOrder(node->GetRightChild());
        if(node->GetInternal())cout << node->GetValue() << " ";
        else cout << node->GetCharacter() << " ";
    }

    // prints the binary identifier of every letter, using inorder transversal
    void PrintIds(HuffmanTreeNode* node)
    {
        // Left Parent Right

        // base case
        if(node == NULL) return;

        PrintIds(node->GetLeftChild());
        if(!node->GetInternal() && node != _head) cout << node->GetCharacter() << ": " << node->GetBinId() << endl;
        PrintIds(node->GetRightChild());
    }
};

string RemoveNewLines(string str)
{

    string s = str;
    std::string::size_type i = 0;

    while (i < s.length()) {
        i = s.find('\n', i);
        if (i == string::npos) break;
        s.erase(i);
    }

    return s;
}

int main(int argc, char** argv)
{
    if(argc < 4)
    {
        cout << "The program was executed with insufficient arguments. Terminating..." << endl;
        return 0;
    }
    else 
    {
        HuffmanTree* tree = new HuffmanTree();
        ifstream inorder;
        ifstream postorder;
        ifstream encoded;

        inorder.open(argv[1]);
        postorder.open(argv[2]);
        encoded.open(argv[3]);

        if(!inorder.is_open() || !postorder.is_open() || !encoded.is_open())
        {
            cout << "One or more of the specified files could not be opened for reading. Terminating..." << endl;
            return 0;
        }
        else
        {
            string inorderText = "";
            string postorderText = "";
            string encodedText = "";
            string tmp;

            while( getline(inorder, tmp) ) inorderText += tmp;
            while( getline(postorder, tmp) ) postorderText += tmp;
            while( getline(encoded, tmp) ) encodedText += tmp;

            inorder.close();
            postorder.close();
            encoded.close();

            tree->ReadInOrder(inorderText);
            tree->ReadPostOrder(postorderText);

            // we don't want newlines messing up the tree
            inorderText = RemoveNewLines(inorderText);
            postorderText = RemoveNewLines(postorderText);
            encodedText = RemoveNewLines(encodedText);

            if(tree->Build())
            {
                cout << tree->Decode(encodedText) << endl;
            }
        
            return 0;
        }
    }
}