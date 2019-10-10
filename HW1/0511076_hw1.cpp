# include <iostream>
# include <fstream>
# include <queue>
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
    vector<int> chain;
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
    vector<int> GetMaxChainID();
    Node* GetRoot();

private:
    int size;
    int maxchainlen;
    Node* maxchainroot;
    Node* root;
    queue<Node*> Q;
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
	n->chain.clear();
	alpha.Insert_Node(n);
    }

    //alpha.Preorder_Print(alpha.GetRoot());
    alpha.ResetAllCount(alpha.GetRoot());
    alpha.CalChainLen(alpha.GetRoot());

    if (mode == 0) output << alpha.MaxChainLen() << endl;
    else if (mode == 1){
	output << alpha.MaxChainLen() << endl;
	output << endl;
	vector<int> ans = alpha.GetMaxChainID();
	for (vector<int>::iterator it = ans.begin(); it != ans.end(); ++it) output << *it << endl;
    }

    input.close();
    output.close();
    return 0;
}



/////////////////////////////////// implementation ///////////////////////////////////

Tree::Tree(){
    size = maxchainlen = 0;
    maxchainroot = root = NULL;
    while (!Q.empty()) Q.pop();
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
    if (!Q.empty() && leaf->leftID == Q.front()->ID){
        leaf->left = Q.front();
        Q.pop();
    }
    if (!Q.empty() && leaf->rightID == Q.front()->ID){
        leaf->right = Q.front();
        Q.pop();
    }
    if (!Q.empty() && leaf->leftID == Q.front()->ID){
        leaf->left = Q.front();
        Q.pop();
    }
    root = leaf;
    Q.push(leaf);
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
	    leaf->chain = leaf->left? leaf->left->chain: vector<int>();
	}
	else{
	    leaf->count = rightlen + 1;
	    leaf->chain = leaf->right? leaf->right->chain: vector<int>();
	}
	leaf->chain.push_back(leaf->ID);
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

vector<int> Tree::GetMaxChainID(){
    int leftlen = maxchainroot->left? maxchainroot->left->chain.size(): 0;
    int rightlen = maxchainroot->right? maxchainroot->right->chain.size(): 0;
    vector<int> ans;
    if (leftlen >= rightlen){
	for (int i = 0; i < leftlen; i++) ans.push_back(maxchainroot->left->chain[i]);
	ans.push_back(maxchainroot->ID);
	for (int i = rightlen-1; i >= 0; i--) ans.push_back(maxchainroot->right->chain[i]);
    }
    else{
        for (int i = 0; i < rightlen; i++) ans.push_back(maxchainroot->right->chain[i]);
        ans.push_back(maxchainroot->ID);
        for (int i = leftlen-1; i >= 0; i--) ans.push_back(maxchainroot->left->chain[i]);
    }
    return ans;
}

