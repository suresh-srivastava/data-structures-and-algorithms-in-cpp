//Trie.cpp : Program to implement trie.

#include<iostream>
#include<string>
using namespace std;

static const int maxSize = 26;

class Node
{
	public:
		Node *links[maxSize]; //links to the child node
		bool eok; //end of key

		Node() 
		{ 
			eok = false;
			for(int i=0; i<maxSize; i++)
				links[i] = NULL;
		}
};//End of class Node

class Trie 
{
	private:
		Node *root;

	private:
		void display(Node *ptr, string prefix);
		void destroy(Node *ptr);

	public:
		Trie();
		~Trie();
		void insert(string key);
		bool search(string key);
		bool startsWith(string prefix);
		void del(string key);
		void display();
};//End of class Trie

Trie::Trie()
{
	root = new Node();
}//End of Trie()

Trie::~Trie()
{
	destroy(root);
	root = NULL;
}//End of ~Trie()

void Trie::destroy(Node *ptr)
{
	for(int i=0; i<maxSize; i++)
	{
		if (ptr->links[i] != NULL)
		{
			//cout << char(i+'a') << " : " <<  ptr->links[i] << "\n";
			destroy(ptr->links[i]);
		}
	}
	//cout << "Deleting : " << ptr << "\n";
	delete ptr;
}//End of destroy()

void Trie::insert(string key)
{
	Node *ptr = root;

	for(int i=0; i<key.length(); i++)
	{
		//If letter of key is not there
		if(ptr->links[key[i]-'a'] == NULL)
		{
			ptr->links[key[i]-'a'] = new Node();
		}

		ptr = ptr->links[key[i]-'a']; //Move to the next child node
	}
	ptr->eok = true; //end of key
}//End of insert()

bool Trie::search(string key)
{
	Node *ptr = root;

	for(int i=0; i<key.length(); i++)
	{
		if(ptr->links[key[i]-'a'] == NULL)
		{
			//key is not in the Trie
			return false;
		}

		ptr = ptr->links[key[i]-'a']; //Move to the next child node
	}

	return ptr->eok;
}//End of search()

bool Trie::startsWith(string prefix)
{
	Node *ptr = root;

	for(int i=0; i<prefix.length(); i++)
	{
		if(ptr->links[prefix[i]-'a'] == NULL)
		{
			//No prefix
			return false;
		}

		ptr = ptr->links[prefix[i]-'a']; //Move to the next child node
	}

	//prefix found
	return true;
}//End of startsWith()

void Trie::display(Node *ptr, string prefix)
{
	if(ptr->eok)
		cout << prefix << "\n";

	for (int i=0; i<maxSize; i++) 
	{
		if(ptr->links[i] != NULL)
		{
			display(ptr->links[i], prefix+char('a'+i));
		}
	}
}//End of display()

void Trie::display()
{
	string str;
	display(root,str);
}//End of display()

void Trie::del(string key)
{
	Node *ptr = root;

	for(int i=0; i<key.length(); i++)
	{
		if(ptr->links[key[i]-'a'] == NULL)
		{
			cout << "key is not in the Trie\n";
			return;
		}
		ptr = ptr->links[key[i] - 'a']; //Move to the next child node
	}

	if(ptr->eok == false)
		cout << "key is not in the Trie\n";
	else
		ptr->eok = false;
}//End of del()

int main()
{
	Trie trie;

	trie.insert("lucknow");
	trie.insert("lucknowcity");
	trie.insert("luxembourg");
	trie.insert("lux");
    
	//Search in trie
	cout << "search(\"lucknowp\") : " << (trie.search("lucknowp") ? "True" : "False");
	cout << "\n";

	cout << "search(\"luxembourg\") : " << (trie.search("luxembourg") ? "True" : "False");
	cout << "\n";

	//Prefix in trie
	cout << "startsWith(\"luxe\") : " << (trie.startsWith("luxe") ? "True" : "False");
	cout << "\n";

	cout << "Trie keys are :\n";
	trie.display();

	//Deletion of key in trie
	trie.del("luxembourg");

	cout << "After deleting luxembourg, trie keys are :\n";
	trie.display();

	return 0;
}//End of main()