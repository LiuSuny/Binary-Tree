
#include <chrono>
#include <iostream>
#include <queue>
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
		Element(int Data, Element* pLeft=nullptr, Element* pRight=nullptr) :Data(Data), pLeft(pLeft), pRight(pRight)
		{
#ifdef CONSTRUCT
			cout <<"Econstructor: \t" << this << endl;
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
	int depth_print() {
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
	int count()
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

	// Метод для балансировки дерева из отсортированного массива
   void balance()
	{
		vector<int> sorted_values;
		inOrderTraversal(Root, sorted_values);

	   Root = balance_from_sorted_array(sorted_values, 0, sorted_values.size() - 1);
	   
	}

	// Рекурсивный метод для обхода дерева в порядке in-order и заполнения массива
	void inOrderTraversal(Element* Root, vector<int>& result)
	{
		if (Root == nullptr) 
		{
			return;
		}
		inOrderTraversal(Root->pLeft, result);
		result.push_back(Root->Data);
		inOrderTraversal(Root->pRight, result);
	}
	void measurePerformance() 
	{
		// Measuring insert performance
		auto start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < 10000; i++)   insert(i);
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> duration = end - start;
		std::cout << "Insertion Time: " << duration.count() << " seconds" << std::endl;
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
			if (Root == nullptr) {
				return 0;
			}

		  /*    int leftDepth = depthRec(Root->pLeft);
			  int rightDepth = depthRec(Root->pRight);

			  return 1 + std::max(leftDepth, rightDepth);*/

			else return
			    //return pleft root if root on the pleft is greater than depth root on pRight + 1, then we added  count from our depth pleft (:) however if it is false then we obtain the result from the right side 
			    depthRec(Root->pLeft) + 1 > 
			    depthRec(Root->pRight) + 1 ? 
			    depthRec(Root->pLeft) + 1 :
			    depthRec(Root->pRight) + 1;

		}
	   
		//Balance method
		Element * balance_from_sorted_array(std::vector<int>& sorted, int start, int end) 
		{
			if (start > end)  return nullptr;
			
			int mid = (start + end) / 2;
			Element* Root = new Element(sorted[mid]);

			Root->pLeft = balance_from_sorted_array(sorted, start, mid - 1);
			Root->pRight = balance_from_sorted_array(sorted, mid + 1, end);

			return Root;
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

#define BASE_CHECK
//#define LIST_Binary

int main()
{
	setlocale(LC_ALL, "");



#ifdef BASE_CHECK 
	int n;
	cout << "Enter the size of Tree : "; cin >> n;
	Tree tree;

	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	tree.print();
	cout << endl;
   
	std::cout << "Min Value: " << tree.minValue() << std::endl;
	std::cout << "Max Value: " << tree.maxValue() << std::endl;
	std::cout << "Sum of Values: " << tree.sum() << std::endl;
	std::cout << "Count of Tree: " << tree.count() << std::endl;
	std::cout << "Average of Tree: " << tree.avg() << std::endl;
	std::cout << "Depth of Tree: " << tree.depth_print() << std::endl;
	
	//std::cout << "\nAfter balance of Tree: \n";  tree.balance();
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


	UniqueTree u_tree;
	for (int i = 0; i < n; i++)
	{
		u_tree.insert(rand() % 100);
	}
	tree.print();
	cout << endl;
	std::cout << "Min Value: " << u_tree.minValue() << std::endl;
	std::cout << "Max Value: " << u_tree.maxValue() << std::endl;
	std::cout << "Sum of Values: " << u_tree.sum() << std::endl;
	std::cout << "Count of Tree: " << u_tree.count() << std::endl;
	std::cout << "Average of Tree: " << u_tree.avg() << std::endl;
	std::cout << "Depth of Tree: " << u_tree.depth_print() << std::endl;
	
	
	//std::cout << "balance of Tree: \n"; u_tree.balance();
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
		       17,
		        18
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
	std::cout << "Depth of Tree: " << tree.depth_print() << endl;
	
	
	
	
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



	return 0;
}