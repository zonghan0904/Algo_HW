# include <iostream>
# include <fstream>
# include <map>
# include <vector>

using namespace std;

/////////////////////////////////// declaration ///////////////////////////////////

struct Node{
    int ID;
    char ch;
    Node* left;
    int leftID;
    Node* right;
    int rightID;
    int count;
};

class Tree{
public:
    Tree();
    ~Tree();
    void Insert_Node(Node*);
    void Preorder_Print(Node*);     // test whether the tree work.
    int MaxChainLen();  
    void ResetAllCount(Node*); 
    void CalChainLen(Node*);
    int LeftLen(Node*);
    int RightLen(Node*);
    bool Is_Vowel(Node*);
    void DestroyRecursive(Node*);
    void PrintMaxChainID(fstream&);
    void PrintHeadSide(fstream&, Node*);
    void PrintEndSide(fstream&, Node*);
    Node* GetRoot();

private:
    int size;
    int maxchainlen;
    Node* maxchainroot;
    Node* root;
    map<int, Node*> M;
};

/////////////////////////////////// main ///////////////////////////////////

int main(int argc, char** argv){
    if (argc != 3){
	//cout << "usage: ./<excute file> <input file> <outputfile>\n";
	return 1;
    }
    
    fstream input, output;
    input.open(argv[1], fstream::in);
    if (!input){
	//cerr << "Could't find the " << argv[1] << " file.\n";
	return 1;
    }
    output.open(argv[2], fstream::out);
    if (!output){
	//cerr << "could't create the " << argv[2] << " file.\n";
	return 1;
    }

    int s, mode;
    input >> s >> mode;

    Tree alpha;
    for (int i = 0; i < s; i++){
	Node* n = new Node();
	input >> n->ID;
	input >> n->ch;
	input >> n->leftID;
	input >> n->rightID;
	n->left = NULL;
	n->right = NULL;
	n->count = 0;
	alpha.Insert_Node(n);
    }

    //alpha.Preorder_Print(alpha.GetRoot());
    alpha.ResetAllCount(alpha.GetRoot());
    alpha.CalChainLen(alpha.GetRoot());

    if (mode == 0) output << alpha.MaxChainLen() << endl;
    else if (mode == 1){
	output << alpha.MaxChainLen() << endl;
	output << endl;
        alpha.PrintMaxChainID(output);
    }

    input.close();
    output.close();
    return 0;
}



/////////////////////////////////// implementation ///////////////////////////////////

Tree::Tree(){
    size = maxchainlen = 0;
    maxchainroot = root = NULL;
    M.clear();
}

Tree::~Tree(){
    DestroyRecursive(root);
    maxchainroot = root = NULL;
}

void Tree::DestroyRecursive(Node* ptr){
    if (ptr){
        DestroyRecursive(ptr->left);
        DestroyRecursive(ptr->right);
        delete ptr;
    }
}

void Tree::Preorder_Print(Node* leaf){
    cout << leaf->ch << " ";
    if (leaf->left != NULL) Preorder_Print(leaf->left);
    if (leaf->right != NULL) Preorder_Print(leaf->right);
}

void Tree::Insert_Node(Node* leaf){
    map<int, Node*>::iterator it_left = M.find(leaf->leftID);
    map<int, Node*>::iterator it_right = M.find(leaf->rightID);
    if (it_left != M.end()){
        leaf->left = it_left->second;
        M.erase(it_left);
    }
    if (it_right != M.end()){
        leaf->right = it_right->second;
        M.erase(it_right);
    }
    root = leaf;
    M.insert(pair<int, Node*>(leaf->ID, leaf));
    size++;
}

Node* Tree::GetRoot(){
    return root;
}

int Tree::MaxChainLen(){
    return maxchainlen;
}

void Tree::CalChainLen(Node* leaf){ 
    if (leaf->left) CalChainLen(leaf->left);
    if (leaf->right) CalChainLen(leaf->right);
    int leftlen = LeftLen(leaf);
    int rightlen = RightLen(leaf);
    if (Is_Vowel(leaf)){
	if (maxchainlen < leftlen + rightlen){
	    maxchainlen = leftlen + rightlen;
	    maxchainroot = leaf;
	}
	if (leftlen >= rightlen){
	    leaf->count = leftlen + 1;
	}
	else{
	    leaf->count = rightlen + 1;
	}
    }
}

int Tree::LeftLen(Node* leaf){
    if (leaf->left) return leaf->left->count;
    else return 0;
}

int Tree::RightLen(Node* leaf){
    if (leaf->right) return leaf->right->count;
    else return 0;
}

bool Tree::Is_Vowel(Node* leaf){
    if (leaf->ch == 'a' || leaf->ch == 'e' || leaf->ch == 'i' ||
	leaf->ch == 'o' || leaf->ch == 'u'	                )
	return true;
    else return false;
}

void Tree::ResetAllCount(Node* leaf){ 
    maxchainlen = 0;
    leaf->count = 0;
    if (leaf->left) ResetAllCount(leaf->left);
    if (leaf->right) ResetAllCount(leaf->right);
}

void Tree::PrintMaxChainID(fstream& output){
    if (LeftLen(maxchainroot) >= RightLen(maxchainroot)){
	PrintHeadSide(output, maxchainroot->left);
	output << maxchainroot->ID << endl;
	PrintEndSide(output, maxchainroot->right);
    }
    else{
	PrintHeadSide(output, maxchainroot->right);
	output << maxchainroot->ID << endl;
	PrintEndSide(output, maxchainroot->left);
    }
}

void Tree::PrintHeadSide(fstream& output, Node* leaf){
    int leftlen = LeftLen(leaf);
    int rightlen = RightLen(leaf);
    if (leftlen > 0 || rightlen > 0){
	leftlen >= rightlen? PrintHeadSide(output, leaf->left): PrintHeadSide(output, leaf->right);
    }
    output << leaf->ID << endl;
}

void Tree::PrintEndSide(fstream& output, Node* leaf){
    int leftlen = LeftLen(leaf);
    int rightlen = RightLen(leaf);
    output << leaf->ID << endl;
    if (leftlen > 0 || rightlen > 0){
        leftlen >= rightlen? PrintEndSide(output, leaf->left): PrintEndSide(output, leaf->right);
    }
}

