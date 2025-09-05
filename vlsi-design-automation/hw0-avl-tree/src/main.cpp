#include <iostream>
#include <fstream>
#include <string>

#include "lib.h"

using namespace std;

int main()
{
    cout << "Welcome to Carter's AVL tree!";

    Tree usrTree;

    //user Input Buffers
    string inputFile;
    int singleNum;
    int selection = 0;

    for(;;)
    {
        selection = 0;
        cout << "Please select an Option:\n(1) Create Tree\n(2) Insert Node\n(3) Search Tree\n(4) Traversal\n(5) Exit" << endl;
        cin >> selection;
        switch (selection)
        {
        case 1:
        {
            //Create Tree
            cout << "Enter input file name:" << endl;
            cin >> inputFile;
            ifstream inFile (inputFile);
            while (inFile >> singleNum)
                usrTree.insert(singleNum);
            cout << "Creating Tree: ";
            usrTree.printPreOrder();
            break;
        }        
        case 2:
            //Insert Node
            cout << "Enter value to add:" << endl;
            cin >> singleNum;
            usrTree.insert(singleNum);
            cout << "Inserting Node: ";
            usrTree.printPreOrder();
            break;
        
        case 3:
            //Search tree
            cout << "Enter value to search:" << endl;
            cin >> singleNum;
            if(usrTree.search(singleNum))
                cout << "Value is in tree" << endl;
            else
                cout << "Value is not in tree" << endl;
            break;
        
        case 4:
            //Traversal
            cout << "Select Traversal:\n(1) Pre-Order\n(2) In-Order\n(3) Post-Order" << endl;
            cin >> singleNum;
            switch(singleNum){
                case 1:
                    //pre-Order
                    usrTree.printPreOrder();
                    break;
                case 2:
                    //in-order
                    usrTree.printInOrder();
                    break;
                case 3:
                    //post-order
                    usrTree.printPostOrder();
                    break;
                default:
                    cout << "Invalid Selection" << endl;
                    break;
            }
            cout << endl;
            break;

        case 5:
            //exit
            cout << "Exiting";
            return 0;
            break;
            
        default:
            cout << "Invalid Selection" << endl;
            break;
        }
    }
}
;
