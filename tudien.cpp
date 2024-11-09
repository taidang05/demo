/*
Dang Ngoc Tai
23110304
*/
#include<bits/stdc++.h>
using namespace std;
template <typename T>
class Node_tree{
	public:
		T word;
		T meaning;
		Node_tree<T>* left;
		Node_tree<T>* right;
		int height;
	public:
		Node_tree(string w, string m) {
		    word = w;
		    meaning = m;
		    left = nullptr;
		    right = nullptr;
		    height = 1;
		    }
};
// cay nhi phan can bang
template <typename T>
class AVLTree{
	private:
		Node_tree<T>* root = nullptr;
	public:
		bool Is_empty()
		{
			return this->root == nullptr;
		}
		int Get_height(Node_tree<T>* node)
		{
			if(node == nullptr)
			{
				return 0; // nut la
			}
			return node->height;
		}
		void Update_height(Node_tree<T>* node)
		{
			if(node != nullptr)
			{
				node->height = 1 + max(Get_height(node->left), Get_height(node->right));
			}
		}
		int Get_balance(Node_tree<T>* node) {
        	if (node == nullptr || (node->left == nullptr && node->right == nullptr)) {
            	return 0;  // neu la ptr thi do can bang la 0
        	}
            return Get_height(node->left) - Get_height(node->right);  //do can bang
    	}
    	
        // TH: Left left (xoay phai)
        Node_tree<T>* Left_left(Node_tree<T>* x)
        {
        	Node_tree<T>* tmp = x->left;
        	Node_tree<T>* tmp1 = tmp->right;
        	tmp->right = x;
        	x->left = tmp1;
        	Update_height(x);
        	Update_height(tmp);
        	return tmp;
		}
		// TH: right right (xoay trai) 
		Node_tree<T>* Right_right(Node_tree<T>* x)
		{
			Node_tree<T>* tmp = x->right;
			Node_tree<T>* tmp1 = tmp->left;
			tmp->left = x;
			x->right = tmp1;
			Update_height(x);
			Update_height(tmp);
			return tmp;
		}
		
		// Chen 1 nut moi 
		void Insert(T word, T meaning)
		{
			root = Insert(root, word, meaning);
		}
		// ham de quy
		Node_tree<T>* Insert( Node_tree<T>* node, T word, T meaning)
		{
			if(node == nullptr)
			{
				return new Node_tree<T>(word, meaning);
			}
			if(word < node->word)
			{
				node->left = Insert(node->left, word, meaning);
			}
			else if(word > node->word)
			{
				node->right = Insert(node->right, word, meaning);
			}
			else return node;
			Update_height(node);
			int balance = Get_balance(node);
//			cout<<"hehe "<<node->data<<" "<<balance<<endl;
			//left left
			if(balance > 1 && word < node->left->word)
			{
				return Left_left(node); //xoay phai
			}
			//right right
			if(balance < -1 && word > node->right->word)
			{
				return Right_right(node);  // xoay trai
			}
			// left right
			if(balance > 1 && word > node->left->word)
			{
				node->left = Right_right(node->left);
				return Left_left(node);
			}
			//right left
			if(balance < -1 && word < node->right->word)
			{
				node->right = Left_left(node->right);
				return Right_right(node);
			}
			return node;
		}
		
		// tim node nho nhat cua cay con ben phai
		Node_tree<T>* minValueNode(Node_tree<T>* node) {
		    Node_tree<T>* current = node;
		    while (current->left != nullptr)
		        current = current->left;
		    return current;
		}
		// xoa node
		void DeleteNode(T word)
		{
			root = DeleteNode(root, word);
		}
		Node_tree<T>* DeleteNode(Node_tree<T>* root, T word)
		{
			if(root == nullptr)
			return root;
			if (word < root->word)	root->left = DeleteNode(root->left, word);
			else if(word > root->word)	root->right = DeleteNode(root->right, word);
			else //node can xoa duoc tim thay
			{
				if(root->left == nullptr || root->right == nullptr)
				{
					Node_tree<T> * temp = root->left ? root->left : root->right;
					if(temp == nullptr)
					{
						temp = root;
						root = nullptr;
					}
					else
					{
						*root = *temp;
					}
					delete(temp);
				}
				else
				{
					Node_tree<T>* temp = minValueNode(root->right);
					root->word = temp->word;
					root->meaning = temp->meaning;
					root->right = DeleteNode(root->right, temp->word);
				}
			}
			
			Update_height(root);
			int balance = Get_balance(root);
			if(balance  > 1 && Get_balance(root->left) >= 0)
			{
				return Left_left(root);
			}
			if(balance > 1 && Get_balance(root->left) < 0)
			{
				root->left = Right_right(root->left);
				return Left_left(root);
			}
			if(balance < -1 && Get_balance(root->right) <= 0 )
			{
				return Right_right(root);
			}
			if(balance < -1 && Get_balance(root->right ) > 0 )
			{
				root->right = Left_left(root->right);
				return Right_right(root);
			}
			
			return root;
		}
		// tim 1 node 
		Node_tree<T>* Search_node(T word)
		{
			return Search_node(root, word);
		}
		Node_tree<T>* Search_node(Node_tree<T>* current, T word)
		{
			if(current == nullptr or current->word == word)
			{
				return current;
			}
			if(word < current->word)
			{
				return  Search_node(current->left, word);
			}
			return Search_node(current->right, word);
		}
		
		
//		print
		void Preorder(ofstream &outfile)
		{
			outfile << "Goc: "<< root->word<<endl;
			outfile << "{" <<endl;
			Preorder(root, outfile);
			outfile << "}" <<endl;
			outfile << endl;
		}
		void Preorder(Node_tree<T>* node, ofstream &outfile)
		{
			if(node != nullptr)
			{
				outfile << node->word << " : "<<node->meaning<<" ";
				if(node->left == nullptr) outfile << "NULL ";
				else outfile << node->left->word<<" ";
				if(node->right == nullptr) outfile << "NULL "<<endl;
				else outfile << node->right->word<<endl;
				Preorder(node->left, outfile);
				Preorder(node->right, outfile);
			}
		}		
		// chieu cao cua cay
		int Height_of_tree()
		{
			Update_height(this->root);
			return root->height;
		}
};

string Trim(const std::string &str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    size_t last = str.find_last_not_of(" \t\n\r");
    if (first == std::string::npos || last == std::string::npos) {
        return "";
    }
    return str.substr(first, last - first + 1);
}

int main()
{
	AVLTree<string> mytree;
	ifstream infile("../Realease/input.txt");
	string line;
	ofstream outfile("../Realease/23110304.txt");
	while(getline(infile, line))
	{
		istringstream iss(line);
		int choice;
		if(iss >> choice)
		{
			switch(choice){
				case 0:
					int n; iss >> n;
					while(n--)
					{
						string line1;
						getline(infile, line1);
						istringstream wordstream(line1);
						string english,vietnamese;
						getline(wordstream, english, ',');
						getline(wordstream, vietnamese);
						english = Trim(english);
						vietnamese = Trim(vietnamese);
						mytree.Insert(english, vietnamese);	
					}
					break;
				case 1:{
					string word;
					iss >> word;
					mytree.DeleteNode(word);					
					break;
				}
				case 2:{
					string english;
					iss >> english;
					Node_tree<string>* cur = mytree.Search_node(english);
					if (cur == nullptr) {
					    outfile << "The word "<<english<< " Not Found." << endl;
					}
					else {
					    outfile << "The word "<<english<<" means: "<<cur->meaning << endl;
					}
					break;
				}
				case 3:{
				    mytree.Preorder(outfile);
					break;
				}
				default:
					break;
			}
		}
	}
	infile.close();
	outfile.close();
	return 0;	
}	