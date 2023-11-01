#include <iostream>
#include <queue>
using namespace std;




class Tree
{
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;


	public:
		Element(int Data, Element* pLeft=nullptr, Element* pRight=nullptr) :Data(Data), pLeft(pLeft), pRight(pRight)
		{
			cout <<"Econstructor: \t" << this << endl;
		}

		~Element()
		{
			cout << "EDestructor: \t" << this << endl;
		}

		friend class Tree;
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

	~Tree()
	{
		
		cout << "TDestructor\t" << this << endl;
	}

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

	void print(Element* Root)
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << "\t";
		print(Root->pRight);
	}

    // Min Tree
    int minValue() 
    {
        return minValueRec(Root);
    }

    int minValueRec(Element* Root) {
        if (Root->pLeft == nullptr) {
            return Root->Data;
        }
        return minValueRec(Root->pLeft);
    }

    // Max Tree
    int maxValue() 
    {
        return maxValueRec(Root);
    }

    int maxValueRec(Element* Root) 
    {
        if (Root->pRight == nullptr)
        {
            return Root->Data;
        }
        return minValueRec(Root->pRight);
    }


    // Sum of Tree
    int sum() {
        return sumRec(Root);
    }

    int sumRec(Element* Root) {
        if (Root == nullptr) {
            return 0;
        }
        return Root->Data + sumRec(Root->pLeft) + sumRec(Root->pRight);
    }

    // Number of Tree
    int count() {
        return countRec(Root);
    }

    int countRec(Element* Root) {
        if (Root == nullptr) {
            return 0;
        }
        return 1 + countRec(Root->pLeft) + countRec(Root->pRight);
    }


    // Clear Tree
    void clear() {
        clearRec(Root);
        Root = nullptr;
    }

    void clearRec(Element* Root) {
        if (Root != nullptr) {
            clearRec(Root->pLeft);
            clearRec(Root->pRight);
            delete Root;
        }
    }

    // erasing Tree with a given value
    void erase(int value) {
        Root = eraseRec(Root, value);
    }

    Element* eraseRec(Element* Root, int value) {
        if (Root == nullptr) {
            return Root;
        }

        if (value < Root->Data) {
            Root->pLeft = eraseRec(Root->pLeft, value);
        }
        else if (value > Root->Data) {
            Root->pRight = eraseRec(Root->pRight, value);
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
            Root->pRight = eraseRec(Root->pRight, temp->Data);
        }
        return Root;
    }

    Element* findMinValueTree(Element* Root) {
        while (Root->pLeft != nullptr) {
            Root = Root->pLeft;
        }
        return Root;
    }

    // Calculate tree depth
    int depth() {
        return depthRec(Root);
    }

    int depthRec(Element* Root) {
        if (Root == nullptr) {
            return 0;
        }

        int leftDepth = depthRec(Root->pLeft);
        int rightDepth = depthRec(Root->pRight);

        return 1 + std::max(leftDepth, rightDepth);
    }

};

void main()
{
	setlocale(LC_ALL, "");

	int n;
	cout << "Enter the size of Tree : "; cin >> n;
	Tree tree;

	for (int i = 0; i < n; i++)
	{
        tree.insert(rand() % 100, tree.getRoot());
	}
	tree.print(tree.getRoot());
	cout << endl;

    std::cout << "Min Value: " << tree.minValue() << std::endl;
    std::cout << "Max Value: " << tree.maxValue() << std::endl;
    std::cout << "Sum of Values: " << tree.sum() << std::endl;
    std::cout << "Count of Nodes: " << tree.count() << std::endl;
    std::cout << "Depth of Tree: " << tree.depth() << std::endl;
    std::cout << "After clearing Tree"<<"\n";
    tree.clear();
    std::cout <<endl;
   /* std::cout << "\nAfter erasing ";
    tree.erase(n);
    std::cout << "\n";*/
}