﻿
#include <chrono>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std::literals::chrono_literals;
using namespace std;

using std::cout;
using std::cin;
using std::endl;
//#define CONSTRUCT
class Tree
{
protected:
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;


	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr) :Data(Data), pLeft(pLeft), pRight(pRight)
		{
#ifdef CONSTRUCT
			cout << "Econstructor: \t" << this << endl;
#endif // DEBUG
		}

		~Element()
		{
#ifdef CONSTRUCT
			cout << "EDestructor: \t" << this << endl;
#endif CONSTRUCT
		}

		friend class Tree;
		friend class UniqueTree; //by initializing our abstract class friend allow access in main
	}*Root;

public:

	Element* getRoot()
	{
		return Root;
	}
	Tree()
	{
		Root = nullptr;
		cout << "TConstructor\t" << this << endl;
	}
	Tree(initializer_list<int> il) : Tree()
	{
		//begin() - return interator from begin contianer
		//end() - return interator from end contianer
		for (int const* it = il.begin(); it != il.end(); ++it)
		{
			insert(*it, Root);
		}
	}

	~Tree()
	{
		clearRec(Root);
		cout << "TDestructor\t" << this << endl;
	}
	void insert(int Data)
	{
		return insert(Data, Root);
	}
	void erase(int value) {
		/* Root =*/ eraseRec(value, Root);
	}
	int depth()const
	{
		return depthRec(this->Root);
	}
	void print()
	{
		return print(Root);
		cout << endl;
	}
	int sum() const
	{
		return sumRec(Root);
	}
	int count()const
	{
		return countRec(Root);
	}
	int minValue()const
	{
		return minValueRec(Root);
	}
	int maxValue()const
	{
		return maxValueRec(Root);
	}


	double avg()const
	{
		return (double)sumRec(Root) / countRec(Root);
	}
	void clear() {
		clearRec(Root);
		Root = nullptr;
	}

	// Method for balancing a tree from a sorted array
	void balanceTree()
	{
		vector<int> _values_sorted;
		MoveThroughArray(Root, _values_sorted);

		Root = _Balance_sorted_Tree_array(_values_sorted, 0, _values_sorted.size() - 1);

	}

	// Recursive method to move back and forth the tree in order to fill our array
	void MoveThroughArray(Element* Root, vector<int>& result)
	{
		if (Root == nullptr)
		{
			return;
		}
		MoveThroughArray(Root->pLeft, result);
		result.push_back(Root->Data);
		MoveThroughArray(Root->pRight, result);
	}

    void depth_print(int depth, int width = 8 )const
	{
		depth_print(this->Root, depth, width);
		cout << std::endl;
	}

	void tree_Print()const
	{
		tree_Print(depthRec(Root), depthRec(Root)*8);
		
	}
	//Method that check how long our tree are executed using ctime library (CLOCK_PER_SEC  - result in millisecond) clock_t and clock() function 
	bool isBalance() const
	{
		/*if (Root==nullptr) return 0;*/
		return  _balanceHeight(Root); /*!= -1;*/

	}

private:
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr) return;
		if (Data < Root->Data) //if the our data is less than root(data)
		{
			//Here we check if our left side pointer is zero, if it is then we create new element and enter our data
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft); //Recussive function
		}
		else
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}

	}

	// erasing Tree with a given value
	/* Element**/ void eraseRec(int Data, Element*& Root) //Note with second pattern inrealizing our erase funct with adding &reference to our element that need inline element will not replace the previous position
	{
		/*  if (Root == nullptr) {
			  return Root;
		  }

		  if (Data < Root->Data) {
			  Root->pLeft = eraseRec(Data, Root->pLeft);
		  }
		  else if (Data > Root->Data) {
			  Root->pRight = eraseRec(Data, Root->pRight);
		  }
		  else {
			  if (Root->pLeft == nullptr) {
				  Element* temp = Root->pRight;
				  delete Root;
				  return temp;
			  }
			  else if (Root->pRight == nullptr) {
				  Element* temp = Root->pLeft;
				  delete Root;
				  return temp;
			  }

			  Element* temp = findMinValueTree(Root->pRight);
			  Root->Data = temp->Data;
			  Root->pRight = eraseRec(temp->Data, Root->pRight);
		  }
		  return Root;*/


		if (Root == nullptr)return;
		if (Data == Root->Data)
		{
			if (Root->pLeft == Root->pRight)
			{
				delete Root;
				Root = nullptr;
			}
			else
			{
				if (countRec(Root->pLeft) > countRec(Root->pRight))
				{
					Root->Data = maxValueRec(Root->pLeft);
					eraseRec(maxValueRec(Root->pLeft), Root->pLeft);
				}
				else
				{
					Root->Data = minValueRec(Root->pRight);
					eraseRec(minValueRec(Root->pRight), Root->pRight);
				}
			}
		}
		if (Root)eraseRec(Data, Root->pLeft);
		if (Root)eraseRec(Data, Root->pRight);
	}


	// Clear Tree
	void clearRec(Element* Root) {
		/* if (Root != nullptr)
		 {
			 clearRec(Root->pLeft);
			 clearRec(Root->pRight);
			 delete Root;
		 }*/

		 //Another different method realization
		if (Root == nullptr)return;
		clearRec(Root->pLeft);
		clearRec(Root->pRight);
		delete Root;
		Root = nullptr;
	}

	// Min Tree
	int minValueRec(Element* Root)const
	{
		if (Root == nullptr)return 0;
		/*if (Root->pLeft == nullptr) {
			return Root->Data;
		}
		return minValueRec(Root->pLeft);*/
		//Using tenary method to get our minvalue
		return Root->pLeft == nullptr ? Root->Data : minValueRec(Root->pLeft);
	}

	// Max Tree
	int maxValueRec(Element* Root)const
	{
		if (Root == nullptr)return 0;
		/* if (Root->pRight == nullptr)
		 {
			 return Root->Data;
		 }
		 return maxValueRec(Root->pRight);*/

		return Root->pRight == nullptr ? Root->Data : maxValueRec(Root->pRight);
	}

	// Sum of Tree
	int sumRec(Element* Root)const
	{
		if (Root == nullptr) {
			return 0;
		}
		else  return sumRec(Root->pLeft) + sumRec(Root->pRight) + Root->Data;
		//return Root == nullptr ? 0 : sumRec(Root->pLeft) + sumRec(Root->pRight) + Root->Data;
	}


	// Number of Tree
	int countRec(Element* Root)const

	{
		if (Root == nullptr) {
			return 0;
		}
		return 1 + countRec(Root->pLeft) + countRec(Root->pRight);
		// return Root == nullptr ? 0 : countRec(Root->pLeft) + countRec(Root->pRight) + 1;
	}

	void print(Element* Root)
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << "\t";
		print(Root->pRight);
	}

	Element* findMinValueTree(Element* Root) {
		while (Root->pLeft != nullptr) {
			Root = Root->pLeft;
		}
		return Root;
	}

	// Calculate tree depth
	int depthRec(Element* Root) const
	{
		//Note : if our Root of tree doesn't is not zero our depth root move to else statement
		/*if (Root == nullptr) {
			return 0;
		}*/
		//else return
		//    //return pleft root if root on the pleft is greater than depth root on pRight + 1, then we added  count from our depth pleft (:) however if it is false then we obtain the result from the right side 
		//    depthRec(Root->pLeft) + 1 > 
		//    depthRec(Root->pRight) + 1 ? 
		//    depthRec(Root->pLeft) + 1 :
		//    depthRec(Root->pRight) + 1;

		 /* int leftDepth = depthRec(Root->pLeft) +1;
		  int rightDepth = depthRec(Root->pRight)+1;

		  return leftDepth > rightDepth ? leftDepth : rightDepth;*/


		return Root == nullptr ? 0 : std::max(depthRec(Root->pLeft), depthRec(Root->pLeft)) + 1;
	}

	void depth_print(Element* Root, int depth, int width =8)const
	{
		if (Root == nullptr)return;
		if (depth == 0)
		{
			cout.width(width);
			cout << Root->Data;
			cout.width(width);
			cout << " ";

		}
		depth_print(Root->pLeft, depth - 1, width);
		depth_print(Root->pRight, depth - 1, width);
	}

	void tree_Print(int depth, int width) const
	{
		if (depth == -1)return;
		depth_print(this->depthRec(this->Root) - depth, width);
		cout << std::endl;
		cout << std::endl;
		cout << std::endl;
		cout << std::endl;
		tree_Print( depth - 1, width/2);
		

	}
	
	////Balance method
	Element* _Balance_sorted_Tree_array(vector<int>& sorted, int start, int end)
	{
		if (start > end)  return nullptr;
		int middle = (start + end) / 2;
		Element* Root = new Element(sorted[middle]);

		Root->pLeft = _Balance_sorted_Tree_array(sorted, start, middle - 1);
		Root->pRight = _Balance_sorted_Tree_array(sorted, middle + 1, end);

		return Root;
	}


	int  _balanceHeight(Element* Root) const
	{
		if (Root == nullptr) return 0;
		
		// checking left subtree
		int leftSubtreeHeight = _balanceHeight(Root->pLeft);
		if (leftSubtreeHeight == -1) return -1;
		// if left subtree is not balanced then the entire tree is also not balanced

		//checking right subtree
		int rightSubtreeHeight = _balanceHeight(Root->pRight);
		if (rightSubtreeHeight == -1) return -1;
		// if right subtree is not balanced then the entire          tree is also not balanced

		//checking the difference of left and right subtree for current node
		if (abs(leftSubtreeHeight - rightSubtreeHeight) > 1);
		{
			return -1;
		}
		//if it is balanced then return the height
		return std::max(leftSubtreeHeight, rightSubtreeHeight) + 1;



		/*int temp = Root->Data;
		while (abs(countRec(Root->pLeft) - countRec(Root->pLeft))>1)
		{
			temp = Root->Data;
			if (Root == nullptr) return;
			if (abs(countRec(Root->pLeft) - countRec(Root->pLeft)) < 2) return;
			else
			{
				eraseRec(temp, Root);
				insert(temp, Root);
			}
			_balanceHeight(Root->pLeft);
			_balanceHeight(Root->pRight);
		}*/
	}

	
};

//Defining the uniqueness of our Binary Tree adding more classes which inherit Tree class
class UniqueTree :public Tree
{

	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr) return;
		if (Data < Root->Data) //if the our data is less than root(data)
		{
			//Here we check if our left side pointer is zero, if it is then we create new element and enter our data
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft); //Recussive function
		}
		else if(Data > Root->Data) //Just these only statement if Data is greater that Root->Data has make our class unique
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}

	}

public:
	void insert(int Data)
	{
		insert(Data, Root);
	}

	
};


template <typename T> void measureTimePerform(const char msg[], const Tree& tree, T(Tree::*member_function)()const)
{
	cout << msg<<": ";
	clock_t start = clock();
	T value = (tree.*member_function)();
	clock_t end = clock();
	cout << ", Completed for " << double(start - end) / CLOCKS_PER_SEC << " second. \n";
}

//#define BASE_CHECK
//#define PERFORMANCE_CHECK
//#define LIST_Binary
#define BALANCE_CHECK
int main()
{
	setlocale(LC_ALL, "");



#ifdef BASE_CHECK 
	Tree tree;
	int n;
	std::cout << "Enter value not zero : "; cin >> n;
	clock_t start = clock();
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}

	clock_t end = clock();

	std::cout << "Binary Tree Completed for " << double(end - start) / CLOCKS_PER_SEC << " second. \n";

#ifdef PERFORMANCE_CHECK
	//tree.print();
//cout << endl;
	start = clock();
	std::cout << "Min Value: " << tree.minValue() << "\t";
	end = clock();
	std::cout << "Min Completed for " << double(end - start) / CLOCKS_PER_SEC << " second. \n";
	///////////////////////////////////////////////////////////////////////////////////
	start = clock();
	std::cout << "Max Value: " << tree.maxValue() << "\t";
	end = clock();
	std::cout << "Max Completed for " << double(end - start) / CLOCKS_PER_SEC << " second. \n";
	///////////////////////////////////////////////////////////////////////////////////
	start = clock();
	std::cout << "Sum of Values: " << tree.sum() << "\t";
	end = clock();
	std::cout << "Sum Completed for " << double(end - start) / CLOCKS_PER_SEC << " second. \n";
	///////////////////////////////////////////////////////////////////////////////////
	start = clock();
	std::cout << "Count of Tree: " << tree.count() << "\t";
	end = clock();
	std::cout << "Count Completed for " << double(end - start) / CLOCKS_PER_SEC << " second. \n";
	///////////////////////////////////////////////////////////////////////////////////
	start = clock();
	std::cout << "Average of Tree: " << tree.avg() << "\t";
	end = clock();
	std::cout << "Average Completed for " << double(end - start) / CLOCKS_PER_SEC << " second. \n";
	///////////////////////////////////////////////////////////////////////////////////
	start = clock();
	std::cout << "Depth of Tree: " << tree.depth() << "\t";
	end = clock();
	std::cout << "depth tree Completed for " << double(end - start) / CLOCKS_PER_SEC << " second. \n";

	tree.balanceTree();
	tree.tree_Print();
	//tree.print();
  //  std::cout << "\n";
   //tree.clear();
	//int value;
	//cout << "Input element to erase: "; cin >> value;
	//tree.erase(value);// Abiity to erase a value from particular position 
	//std::cout << "\nAfter erasing ";
	//tree.print();
	////tree.measurePerformance();
	//std::cout << "\n";
	cout << "===================\n";
#endif // PERFORMANCE_CHECK

	/*
	measureTimePerform("Min value of Tree ", tree, &Tree::minValue);
	measureTimePerform("Max value of Tree ", tree, &Tree::maxValue);
	measureTimePerform("sum value of Tree ", tree, &Tree::sum);
	measureTimePerform("count value of Tree ", tree, &Tree::count);
	measureTimePerform("average value of Tree ", tree, &Tree::avg);
	measureTimePerform("depth value of Tree ", tree, &Tree::depth_print);*/

	UniqueTree u_tree;
	//u_tree.measurePerformance();
	clock_t begin = clock();
	for (int i = 0; i < n; i++)
	{
		u_tree.insert(rand() % 100);
	}
	clock_t finish = clock();
	std::cout << "Unique Binary Tree Completed for " << double(finish - begin) / CLOCKS_PER_SEC << " second. \n";
	//tree.print();
	//cout << endl;
	begin = clock();
	std::cout << "Min Value: " << u_tree.minValue() << "\t";
	finish = clock();
	std::cout << "Min Completed for " << double(finish - begin) / CLOCKS_PER_SEC << " second. \n";
	///////////////////////////////////////////////////////////////////////////////////
	begin = clock();
	std::cout << "Max Value: " << u_tree.maxValue() << "\t";
	finish = clock();
	std::cout << "Max Completed for " << double(finish - begin) / CLOCKS_PER_SEC << " second. \n";
	///////////////////////////////////////////////////////////////////////////////////
	begin = clock();
	std::cout << "Sum of Values: " << u_tree.sum() << "\t";
	finish = clock();
	std::cout << "Sum Completed for " << double(finish - begin) / CLOCKS_PER_SEC << " second. \n";
	///////////////////////////////////////////////////////////////////////////////////
	begin = clock();
	std::cout << "Count of Tree: " << u_tree.count() << "\t";
	finish = clock();
	std::cout << "Count Completed for " << double(finish - begin) / CLOCKS_PER_SEC << " second. \n";
	///////////////////////////////////////////////////////////////////////////////////
	begin = clock();
	std::cout << "Average of Tree: " << u_tree.avg() << "\t";
	finish = clock();
	std::cout << "Average Completed for " << double(finish - begin) / CLOCKS_PER_SEC << " second. \n";
	///////////////////////////////////////////////////////////////////////////////////
	begin = clock();
	std::cout << "Depth of Tree: " << u_tree.depth_print() << "\t";
	finish = clock();
	std::cout << "depth tree Completed for " << double(finish - begin) / CLOCKS_PER_SEC << " second. \n";
	///////////////////////////////////////////////////////////////////////////////////////
	std::cout << "\nAfter balance of Tree: \n";
	/*std::cout <<*/ u_tree.balanceTree();
	//tree.print();
	//  std::cout << "\n";
	//tree.clear();
	//int value;
	//cout << "Input element to erase: "; cin >> value;
	//u_tree.erase(value);// Abiity to erase a value from particular position 
	//std::cout << "\nAfter erasing ";
	//u_tree.print();
	////u_tree.measurePerformance();
	//std::cout << "\n";
#endif // BASE_CHECK 

	
	
#ifdef LIST_Binary
			  ////USING INITIALIZING_LIST TO INITIATE OUR CODE 
	Tree tree =
	{
					   50,

			   25,                    75,

		   16,     32,        64,              80,
		       17
		        
	};

	tree.print();

	std::cout << "\nMin Value: " << tree.minValue() << std::endl;
	std::cout << "Max Value: " << tree.maxValue() << std::endl;
	std::cout << "Sum of Values: " << tree.sum() << std::endl;
	std::cout << "Count of Tree: " << tree.count() << std::endl;
	std::cout << "Average of Tree: " << tree.avg() << std::endl;
	/*tree.balance();
	std::cout << "\nAfter balance of Tree \n"; */

   /* int value;
	cout << "\nEnter a value: "; cin >> value;
	tree.erase(value);*/
	std::cout << "Depth of Tree: " << tree.depth() << endl;
	
	/*int depth;
	cout << "Enter depth print you wish to enter "; cin >> depth;
	tree.depth_print(depth);*/
	tree.balanceTree();
	tree.tree_Print();


	
	// tree.balance();
	//tree.print();
   /* tree.measurePerformance();
	std::cout << "\n";*/
	////tree.clear();
	//int value;
	//cout << "Input element to erase: "; cin >> value;
	//tree.erase(value);// Abiity to erase a value from particular position 
	//tree.print();
	//std::cout << "\nAfter erasing ";
	//tree.print();
	//std::cout << "\n";  
#endif // LIST_Binary


#ifdef BALANCE_CHECK

	Tree tree = { 55, 34, 21, 13, 28, 87, 67 };

	clock_t start = clock();
	clock_t end = clock();

	start = clock();
	std::cout << "Min Value: " << tree.minValue() << "\t";
	end = clock();
	std::cout << "Min Completed for " << double(end - start) / CLOCKS_PER_SEC << " second. \n";
	///////////////////////////////////////////////////////////////////////////////////
	start = clock();
	std::cout << "Max Value: " << tree.maxValue() << "\t";
	end = clock();
	std::cout << "Max Completed for " << double(end - start) / CLOCKS_PER_SEC << " second. \n";
	///////////////////////////////////////////////////////////////////////////////////
	start = clock();
	std::cout << "Sum of Values: " << tree.sum() << "\t";
	end = clock();
	std::cout << "Sum Completed for " << double(end - start) / CLOCKS_PER_SEC << " second. \n";
	///////////////////////////////////////////////////////////////////////////////////
	start = clock();
	std::cout << "Count of Tree: " << tree.count() << "\t";
	end = clock();
	std::cout << "Count Completed for " << double(end - start) / CLOCKS_PER_SEC << " second. \n";
	///////////////////////////////////////////////////////////////////////////////////
	start = clock();
	std::cout << "Average of Tree: " << tree.avg() << "\t";
	end = clock();
	std::cout << "Average Completed for " << double(end - start) / CLOCKS_PER_SEC << " second. \n";
	///////////////////////////////////////////////////////////////////////////////////
	start = clock();
	std::cout << "Depth of Tree: " << tree.depth() << "\t";
	end = clock();
	std::cout << "depth tree Completed for " << double(end - start) / CLOCKS_PER_SEC << " second. \n";
	tree.balanceTree();
    tree.tree_Print();
	
	int value;
   cout << "\nEnter a value you like to erase from tree: "; cin >> value;
   tree.erase(value);

   tree.balanceTree();
   tree.tree_Print();
#endif // BALANCE_CHECK



	return 0;
}



