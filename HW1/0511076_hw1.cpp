# include <iostream>
# include <fstream>
# include <queue>

using namespace std;

/////////////////////////////////// declaration ///////////////////////////////////

struct Node{
    int ID;
    char ch;
    Node* left;
    int leftID;
    Node* right;
    int rightID;
};

class Tree{
public:
    Tree();
    ~Tree();
    void Insert_Node(Node*);
    int MaxChainLen(int);
    void Preorder_Print(Node*);
    void Inorder_Traversal(Node);   //test whether the tree work.
    bool Is_Vowel(Node);
    void DestroyRecursive(Node*);
    Node* GetRoot();

private:
    int size;
    int chainlen;
    Node* root;
    queue<Node*> Q;
};

/////////////////////////////////// main ///////////////////////////////////

int main(int argc, char** argv){
    if (argc != 3){
	cout << "usage: ./<excute file> <input file> <outputfile>\n";
	return 1;
    }
    
    fstream input, output;
    input.open(argv[1], fstream::in);
    if (!input){
	cerr << "Could't find the " << argv[1] << " file.\n";
	return 1;
    }
    output.open(argv[2], fstream::out);
    if (!output){
	cerr << "could't create the " << argv[2] << " file.\n";
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
	n->right= NULL;
	alpha.Insert_Node(n);
    }
    //alpha.Preorder_Print(alpha.GetRoot());

    return 0;
}



/////////////////////////////////// implementation ///////////////////////////////////

Tree::Tree(){
    size = chainlen = 0;
    root = NULL;
    while (!Q.empty()) Q.pop();
}

Tree::~Tree(){
    DestroyRecursive(root);
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







