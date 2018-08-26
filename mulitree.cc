	//	__________________________________________
	//	| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |  9 |
	//	| 9 | 7 | 5 | 5 | 2 | 9 | 9 | 9 | 2 | -1 |
	//	——————————————————————————————————————————
	//
	//
	//				    9
	//				/	|   \  \
	//			   0    5    6  7
	//				   / \       \
	//			      2   3       1
	//				 / \
	//			    4   8
	//

//Sample Input:

//10
//9 7 5 5 2 9 9 9 2 -1


#include <iostream>
#include <vector>
#include <list>
#include <memory>
#include <map>
#include <string>
#include <algorithm>
#include <ios>


//shared_from_this() std::enable_shared_from_this<Node>
struct Node// : std::enable_shared_from_this<Node> 
{

	std::shared_ptr<Node> parent;// = std::make_shared<Node>();
	std::vector<std::shared_ptr<Node>> children;
	int key, parentKey;

	Node() {}
	Node(int key_) : key(key_) {}

	std::shared_ptr<Node> &getParent() {
		return parent;
	}

	int getKey() {
		return key;
	}

	int getParentKey() {
		return parentKey;
	}

std::vector<std::shared_ptr<Node>> &getChildren() {
		return children;
	}
};

struct TreeHeight// : std::enable_shared_from_this<TreeHeight> 
{


	std::vector<std::shared_ptr<Node>> tree;
	std::shared_ptr<Node> root;

	std::shared_ptr<Node> &getRoot() {
		return root;
	}


	std::shared_ptr<Node> &getByKey(int key) {
		std::shared_ptr<Node> x = std::make_shared<Node>();
		for (auto &n : tree) {
			if (n->getKey() == key) {
				return n;
			}
		}
		return x;
	}


	void addNode(int key, int parentKey) {
		if (parentKey == -1) {
			root = std::make_shared<Node>(key);
			tree.push_back(root);
			//std::cout << "Added root with key " << key << std::endl;
		}
		else {
			std::shared_ptr<Node> current = std::make_shared<Node>(key);
			tree.push_back(current);
			current->parentKey = parentKey;
			//std::cout << "Added node with key " << key << std::endl;
		}
	}

	void setContacts() {
		for (auto &n : tree) {
			if (n != root) {
				n->parent = getByKey(n->getParentKey());
				n->getParent()->getChildren().push_back(n);
			}
		}
	}


	void viewTree() {
		std::string result;
		for (auto &n : tree) {
			std::cout << "Node with key " << n->getKey();

			if (n->getParent() != nullptr) {
				std::cout << ", parent - node with key " << n->getParent()->getKey();
			}
			else {
				std::cout << ", root node";
			}

			if (!n->getChildren().empty()) {
				std::cout << ", descendants - ";
				for (auto &ch : n->getChildren()) {
					std::cout << ch->getKey() << ", ";
				}
				std::cout << std::endl;
			}
			else {
				std::cout << ", no descendants" << std::endl;
			}
		}
	}

	int getHeight(const std::shared_ptr<Node> &node) {
		if (node == nullptr) return 0;

		int childrenCount = node->children.size();
		std::vector<int> heightes;
		for (int i = 0; i < childrenCount; i++) {
			heightes.push_back(getHeight(node->getChildren().at(i)));
		}
		if (!heightes.empty()) {
			return 1 + *std::max_element(heightes.begin(), heightes.end());
		}
		else {
			return 1;
		}

	}
};




int main() {
	//std::vector<int> v = { 9, 7, 5, 5, 2, 9, 9, 9, 2, -1 };

	
	int size;
	std::ios_base::sync_with_stdio(false);
	std::cin >> size;
	std::vector<int> v(size);

	for (size_t i = 0; i < size; ++i) {
		std::cin >> v[i];
	}
	

	std::shared_ptr<TreeHeight> t = std::make_shared<TreeHeight>();

	std::multimap<int, int> nodes;
	for (size_t i = 0; i < v.size(); i++)
		nodes.insert(std::pair<int, int>(i, v[i])); // key, parentKey

	for (auto &n : nodes) {
		t->addNode(n.first, n.second);
	}

	t->setContacts();

	//t->viewTree();

	std::cout << t->getHeight(t->getRoot()) << std::endl;

	return 0;
}

