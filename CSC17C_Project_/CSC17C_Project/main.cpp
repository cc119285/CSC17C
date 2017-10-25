/* 
  File:   main.cpp
  Author: Colleen Carleton
  Created on October 20, 2017, 11:00 AM
  Purpose: Program that allows the user to play a Random Color Puzzle game.
 * Based off a previous project, now including concepts from CSC17C, including
 * Linked Lists.
 * Linked lists are now used to hold scores
 */

//System Libraries
#include <iostream> //Input/output
#include <fstream>  //File input/output
#include <cstdlib>  //For random number seed
#include <ctime>    //Time
#include <cctype>   //Case conversions
#include <string>   //String library
#include <iomanip>  //Output manipulation
using namespace std;

//User Libraries
#include "Mode.h"
#include "SaveLoad.h"
#include "Exceptions.h"
#include "GmeInfo.h"
#include "QuitGames.h"
#include "Link.h"
#include "Object.h"

//Global Constants
//Such as PI, Vc, -> Math/Science values
//as well as conversions from system of units to 
//another

//Function Prototypes
void gmeInfo(); //Display game information
UsrInfo game(fstream &, fstream &, QuitGIn); //Play game
UsrInfo svdgame(fstream &, fstream &, QuitGIn); //Play saved game

void fillAry(Mode, int, int); //Fill puzzle with random characters

Link<Object> *fillLst(int); //Fills initial list of scores
void prntLst(Link<Object> *); //Prints list of scores
void destLst(Link<Object> *); //Deallocate memory for list
Link<Object> *endLst(Link<Object> *); //Find end of list
void addLst(Link<Object> *,const Object &); //Add a score to the end of the list
int findLst(Link<Object> *,const Object &); //Find the link containing a particular score
Link<Object> *fndLst(Link<Object> *,const Object &); //Get address of node containing a score
int cntLst(Link<Object> *); //returns how many elements are in the list
void addB4(Link<Object> *,const Object &, int);   //Add data before a node

//Executable code begins here!!!
int main(int argc, char** argv) {
    //Declare variables
    char choice; //Player's selection from the menu
    char cont;   //Does player want to continue?
    fstream binfile; //Binary file to store names and scores
    UsrInfo player; // Structure returned from function
    int numgms=0;  //Stores number of games played
    int numq=0;    //Holds quit games
    fstream savload; //Stores a saved game
    GmeInfo numg; //Used to check number of games played
    QuitGIn quits; //Stores number of quit games
    int quit2; //Temp storage for quit games
    int temp; //Temp variable
    Exeptns except; //Exceptions
    Link<Object> *lnkList; //Linked List to store scores
    
    //Open binfile for output
    binfile.open("scores.dat", ios::out | ios::binary);
    //Open save/load file for input. If user wants to save a game, it will be closed and reopened for output.
    savload.open("SaveLoad.txt", ios::in);
    
    //Set random number seed
    srand(static_cast<unsigned int>(time(0)));

    //Get player's choice
    cout<<"Welcome to the Random Color Puzzle!"<<endl;
    do {
            cout<<"Select an option:"<<endl;
            cout<<"Enter 1 for game instructions."<<endl;
            cout<<"Enter 2 to play the game."<<endl;
            cout<<"Enter 3 to load a saved game."<<endl;
            cout<<"Enter 4 to quit the game."<<endl;
            cin>>choice;
            
            try {
            
            switch (choice) {
                    case '1': gmeInfo(); break;
                    case '2': {player=game(binfile, savload, quits); numg++;}; break;
                    case '3': {player=svdgame(binfile, savload, quits); numg++;}; break;
                    default: cout<<"Thanks for playing!"<<endl; break;
            }
            
            
            }
            catch (Exeptns::quitgm) {
            //If game was quit, increment quit games
                numq++;
                quits++;
            }
            
            //Do they want to play again/continue?
            cout<<"Do you want to continue or play again? Enter y to continue, and n to quit."<<endl;
            cin>>cont;
    } while (cont==tolower('y'));
    
    //Close binary file
    binfile.close();
    //Open binary file for input
    binfile.open("scores.dat", ios::in | ios::binary);
    
    //Dynamically allocate memory for array
    numgms=numg.getInfo();
    quit2=quits.getQG();
    UsrInfo *ptr=nullptr;
    ptr=new UsrInfo[numgms];
    
    int numList=0;
    //Get first score
        numList=1;
    //Create list with first score
        lnkList=fillLst(numList);
    if (numgms>0) {
    //Until end of file, read in and output information
    binfile.read(reinterpret_cast<char *>(&player), sizeof(player));
    for (int i=1; i<=numgms; i++) {
        ptr->totScor=player.totScor;
        //Output information
        cout<<"Player name          Score"<<endl;
        cout<<setw(11)<<player.name<<"          "<<ptr->totScor<<endl;
        //Add scores to linked list
        addLst(lnkList,player.totScor);
        binfile.seekg(static_cast<long>(sizeof(player)), ios::beg);
        binfile.read(reinterpret_cast<char *>(&player), sizeof(player));
    }
    }
    
    //Output scores
     //cout<<"Scores"<<endl;
     //prntLst(lnkList);
    
    //Close binary file
    binfile.close();
    //Delete dynamic memory
    delete []ptr;
    ptr=nullptr;
    destLst(lnkList);

    //Exit
    return 0;
}

Link<Object> *fillLst(int n){
    //Think of this part as the constructor
    Link<Object> *front=new Link<Object>;//Allocate a link at the front of the list
    front->data=Object(n);       //Initialize with data
    front->linkPtr=NULL; //At the moment not pointing it to anything
    Link<Object> *next=front;    //Create a pointer to progress through the list

    //Create a second link
    Link<Object> *temp=new Link<Object>; //Allocate a new link
       temp->data=Object(n);        //Fill with data
       temp->linkPtr=NULL;  //Place at the end
       next->linkPtr=temp;  //Hook the new link to the end of the list
       next=temp;           //Move the pointer to the end

       return front;           //Return the front pointer to the list
}

void  prntLst(Link<Object> *front){
    Link<Object> *next=front;           //Create a pointer to the list
    do{
        cout<<next->data<<endl; //Print the contents of the link
        next=next->linkPtr;     //Go to the next link in the list
    }while(next!=NULL);         //Loop until reaching the end
}

void  destLst(Link<Object> *front){
    do{
       Link<Object> *temp=front->linkPtr;   //Point to the next link in the list
       delete front;                //Delete the front of the list
       front=temp;                  //Swap the front
    }while(front!=NULL);
}

Link<Object>  *endLst(Link<Object> *front){
    Link<Object> *temp=front,*next; //Declare pointers used to step through the list
    do{
        next=temp;          //Point to the current link with a swap
        temp=temp->linkPtr; //Point to the next link
    }while(temp!=NULL);     //Your done when you hit the end
    return next;
}

void   addLst(Link<Object> *front,const Object &data){
    Link<Object> *last=endLst(front);  //Find the last link
    Link<Object> *add=new Link<Object>;        //Create the new link
    add->data=data;            //Add the data
    add->linkPtr=NULL;         //Set the pointer to NULL
    last->linkPtr=add;         //Point to the new end of the list
}

int   findLst(Link<Object> *front,const Object &value){
    int n=0;                //Initialize the counter
    Link<Object> *temp=front;       //Prepare to traverse the Link<Object>ed list
    do{
        n++;                //Increment the counter
        if(temp->data==value)return n;//Return where the data is found
        temp=temp->linkPtr; //Move to the next link
    }while(temp!=NULL);     //End when reaching the end of the linked list
    return 0;               //Not found then return a 0;
}

Link<Object>  *fndLst(Link<Object> *front,const Object &value){
    Link<Object> *temp=front;       //Set the cursor to move through the list
    do{
        if(temp->data==value)return temp;  //Address of data match
        temp=temp->linkPtr;                //Next link in the list
    }while(temp!=NULL);                    //End of the list
    return NULL;                           //Not found
}

int   cntLst(Link<Object> *front){
    int n=0;            //Initialize the counter
    Link<Object> *temp=front;   //Set the cursor to the front
    do{
        n++;            //Increment the counter
        temp=temp->linkPtr;//Move to the next link
    }while(temp!=NULL); //Loop until the end is reached
    return n;           //Return the counter value
}

void  addB4(Link<Object> *front,const Object &data,int prevdat) {
   Link<Object> *nodePtr;
   Link<Object> *prevNod=nullptr;
    
    Link<Object> *add=new Link<Object>;
    add->data=data;
    nodePtr=front;
    
    for (int i=0; i<prevdat; i++) {
        prevNod=nodePtr;
        nodePtr=nodePtr->linkPtr;
    }
    
    if(prevNod == nullptr) {
        front=add;
        add->linkPtr=nodePtr;
    } else {
        prevNod->linkPtr = add;
        add->linkPtr=nodePtr;
    }
}

void gmeInfo() {
    //Declare Variable
    char a; //Stores player's choice

    cout<<"The Random Color Puzzle will create a unique puzzle of random colors every time you play it."<<endl;
    cout<<"The goal of the game is to reach the end of the puzzle (denoted by the character 'f' in the puzzle)."<<endl;
    cout<<"The rest of the characters making up the puzzle will represent colors, each of which has a different function."<<endl;
    do {
	cout<<"Enter 1 for the functions of the colors, 2 for controls, and 3 for information on modes.  Enter e if you are finished reading."<<endl;
	cin>>a;

	//Display info
	if (a=='1') {
	//Display character/color information
	cout<<"In the puzzle, there will be 8 different characters. 'c' marks the location of your character, and 'f' marks the ending point of the puzzle."<<endl;
	cout<<"The character 'b' stands for blue, which is water. You can cross it, unless the space you were standing on before was 'o', which represents orange."<<endl;
	cout<<"Furthermore, spaces marked 'y', for yellow, cannot be crossed, and if they are next to a blue space, you cannot cross the blue space either."<<endl;
	cout<<"Spaces marked 'p', for purple, and 'g', for green, have no effect. Spaces marked 'r' for red cannot be crossed."<<endl;
	cout<<"The color that will appear in each space will be chosen randomly."<<endl;
	} else if (a=='2') {
	cout<<"The controls for the game are simple, use the wasd keys to travel through the puzzle. To go up, press 'w'; to go down, press 's'; to go back a space, press 'a';";
	cout<<" and to go forward a space, press 'd'."<<endl;
        cout<<"In order to save the current puzzle and score, press the letter q."<<endl;
        cout<<"However, this will also end the current game. You can keep one puzzle saved at a time, and "<<endl;
        cout<<"can load this puzzle at the start of another game."<<endl;
	} else if (a=='3') {
	cout<<"At the beginning of the game, you will be asked to select a mode. There are 3 modes, easy, medium, and hard."<<endl;
	cout<<"Selecting easy means the puzzle created will have dimensions of 3x5."<<endl;
	cout<<"Selecting medium means the puzzle created will have dimensions of 5x5."<<endl;
	cout<<"Selecting hard means the puzzle created will have dimensions of 7x10."<<endl;
	}
    } while (a>='1' && a<='3');
}

UsrInfo game(fstream &binfile, fstream &savload, QuitGIn quit) {
	//Declare variables
	int mode; //Stores mode
	fstream pzzlFil; //Opens puzzle-storing file
	char ch; //Stores the characters as they are input from the file
	char movmnt; //Stores character's movements
	char temp; //Holds character's temporary location (rows)
	char temp2; //Holds character's temporary location (columns)
        int rowsize; //Stores size of rows
        int colsize; //Stores size of columns
        int points=0; //Stores number of points
        int score=0; //Stores overall score
        const int SIZE=81; //Stores size of array to hold name/length of name
        char usrname[SIZE]; //Stores user's name
        Save saves; //Used to save game
        Exeptns exceptn; //Used to throw exceptions
        int cpr; //Stores position of c in puzzle (rows)
        int cpc; //stores position of c in puzzle (columns)
        int temp3;
        UsrInfo player; //Structure to store user's name and score
        
	//Get player's mode
	cout<<"Choose a mode to play: Enter 1 for Easy, 2 for Medium, and 3 for Hard."<<endl;
	cin>>mode;
	//Validate input
	while (mode<1 || mode>3) {
	cout<<"Enter only 1 (Easy), 2 (Medium), or 3 (Hard)."<<endl;
	cin>>mode;
	}
	
	//Set up array size based on mode
	if (mode==1) {
            Mode easy={3, 5};
            rowsize=easy.row;
            colsize=easy.col;
            //Fill Array
            fillAry(easy, rowsize, colsize);
	} else if (mode==2) {
            Mode medium={5, 5};
            rowsize=medium.row;
            colsize=medium.col;
            //Fill Array
            fillAry(medium, rowsize, colsize);
	} else if (mode==3) {
            Mode hard={7, 10};
            rowsize=hard.row;
            colsize=hard.col;
            //Fill Array
            fillAry(hard, rowsize, colsize);
	}

	//Open file for input
	pzzlFil.open("puzzle.txt", ios::in);
        
        //Create array to store the colors
        char coloray[rowsize][colsize];
        //Fill array
        for (int i=0; i<rowsize; i++) {
            for (int j=0; j<colsize; j++) {
                pzzlFil.get(ch);
                coloray[i][j]=ch;
            }
        }
        pzzlFil.clear(); pzzlFil.seekp(0, ios::beg); //Clear eof flag, return to beginning

	//Create second array to store character's position in array
	char charPos[rowsize][colsize]={'0'};
	charPos[0][0]='c';

	//Output the array, but with c in the character's position
	for (int i=0; i<rowsize; i++) {
		for (int j=0; j<colsize; j++) {
			if (charPos[i][j]=='c') {
				cout<<"c"<<" ";
                                pzzlFil.get(ch);
			} else if (i==rowsize-1 && j==colsize-1) {
                            cout<<"f"<<" ";
                        } else {
				pzzlFil.get(ch);
				cout<<ch<<" ";
			}
		}
		cout<<endl;
	}
        pzzlFil.clear(); pzzlFil.seekp(0, ios::beg); //Clear eof flag, return to beginning

	//Start game
        try {
	do {
		//Get user's first movement
		cout<<"Enter w, a, s, or d to move up, backwards, down, or forward one step."<<endl;
		cin>>movmnt;
                //If quitting game
                if (movmnt=='q') {
                    cout<<"Saving current puzzle and score to a file..."<<endl;
                    //Close and Open file for output
                    savload.close();
                    savload.open("SaveLoad.txt", ios::out);
                    //Get location of 'c'
                    for (int count=0; count<rowsize; count++) {
                        for (int count2=0; count2<colsize; count2++) {
                            if (charPos[count][count2]=='c') {
                                cpr=count;
                                cpc=count2;
                            }
                        }
                    }
                    //Call savegame
                    saves.savegm(pzzlFil, savload, rowsize, colsize, cpr, cpc, score);
                    savload.close();
                    //End current game
                    exceptn.quit();
                }
                //Otherwise
		while (movmnt!='w' && movmnt!='a' && movmnt!='s' && movmnt!='d') {
			cout<<"You can only move using w, a, s, or d."<<endl;
			cin>>movmnt;
		}
                points++; //Increment points

		//Move character according to user's input
		if (movmnt=='w') {
			for (int i=0; i<rowsize; i++) {
				for (int j=0; j<colsize; j++) {
					if (charPos[i][j]=='c') {
						temp=i; //Store position in rows
						temp2=j; //Store position in columns
					}
				}
			}

			//Input validation
			if (temp-1<0 || coloray[temp-1][temp2]=='r' || coloray[temp-1][temp2]=='y' || (coloray[temp][temp2]=='o' && coloray[temp-1][temp2]=='b')) {
				cout<<"Invalid movement."<<endl;
			} else {
			//Place 'c' in new location
			charPos[(temp-1)][temp2]='c';

			//Clear old location of 'c'
			charPos[temp][temp2]='0';
			}

		} else if (movmnt=='a') {
			for (int i=0; i<rowsize; i++) {
				for (int j=0; j<colsize; j++) {
					if (charPos[i][j]=='c') {
						temp=i; //Store position in rows
						temp2=j; //Store position in columns
					}
				}
			}

			//Input validation
			if (temp2-1<0 || coloray[temp][temp2-1]=='r' || coloray[temp][temp2-1]=='y' || (coloray[temp][temp2]=='o' && coloray[temp][temp2-1]=='b')) {
				cout<<"Invalid movement."<<endl;
			} else {
			//Place 'c' in new location
			charPos[temp][(temp2-1)]='c';

			//Clear old location of 'c'
			charPos[temp][temp2]='0';
			}

		} else if (movmnt=='s') {
			for (int i=0; i<rowsize; i++) {
				for (int j=0; j<colsize; j++) {
					if (charPos[i][j]=='c') {
						temp=i; //Store position in rows
						temp2=j; //Store position in columns
					}
				}
			}
			
			//Input validation
			if (temp+1>(rowsize-1) || coloray[temp+1][temp2]=='r' || coloray[temp+1][temp2]=='y' || (coloray[temp][temp2]=='o' && coloray[temp+1][temp2]=='b')) {
				cout<<"Invalid movement."<<endl;
			} else {
			//Place 'c' in new location
			charPos[(temp+1)][temp2]='c';

			//Clear old location of 'c'
			charPos[temp][temp2]='0';
			}
		} else {
			for (int i=0; i<rowsize; i++) {
				for (int j=0; j<colsize; j++) {
					if (charPos[i][j]=='c') {
						temp=i; //Store position in rows
						temp2=j; //Store position in columns
					}
				}
			}
			
			//Input validation
			if (temp2+1>(colsize-1) || coloray[temp][temp2+1]=='r' || coloray[temp][temp2+1]=='y' || (coloray[temp][temp2]=='o' && coloray[temp][temp2+1]=='b')) {
				cout<<"Invalid movement"<<endl;
			} else {
			//Place 'c' in new location
			charPos[temp][(temp2+1)]='c';

			//Clear old location of 'c'
			charPos[temp][temp2]='0';
			}

		}

		//Ouput new position in puzzle
		for (int i=0; i<rowsize; i++) {
			for (int j=0; j<colsize; j++) {
				if (charPos[i][j]=='c') {
					cout<<"c"<<" ";
                                        pzzlFil.get(ch);
				} else if (i==rowsize-1 && j==colsize-1) {
                                    cout<<"f"<<" ";
                                } else {
					pzzlFil.get(ch);
					cout<<ch<<" ";
				}
			}
			cout<<endl;
		}
                pzzlFil.clear(); pzzlFil.seekp(0, ios::beg); //Clear eof, return to beginning
                
                //Score
                if (rowsize==3) {
                temp3=15-points;
                score=temp3*5;
                } else if (rowsize==5) {
                temp3=35-points; 
                score=temp3*10;
                } else {
                temp3=65-points;
                score=temp3*20;
                }
		
	} while (charPos[(rowsize-1)][(colsize-1)]!='c');

	//Once they reach the end, congratulate them
	cout<<"Congratulations! You have reached the end of the puzzle!"<<endl;
        //Calculate score
        if (rowsize==3) {
            temp3=15-points;
            score=temp3*5;
            } else if (rowsize==5) {
            temp3=35-points; 
            score=temp3*10;
            } else {
            temp3=65-points;
            score=temp3*20;
            }
        //Display score
        cout<<"Your score was "<<score<<endl;
        //Put score in structure
        player.totScor=score;
        
        //Get user's name
        cin.ignore();
        cout<<"Enter a name of up to 80 characters."<<endl;
        cin.getline(usrname, SIZE);
        
        //Input to file
        binfile.write(usrname, sizeof(usrname));
        binfile.write(reinterpret_cast<char *>(&player.totScor), sizeof(player.totScor));
        
        //Close file
        pzzlFil.close();
        
        }
        catch (Exeptns::quitgm) {
            pzzlFil.close();
            cout<<"Game saved."<<endl;
            throw;
        }
        
        //Return player
        return player;
}

UsrInfo svdgame(fstream &binfile, fstream &savload, QuitGIn quit) {
	//Declare variables
	int mode; //Stores mode
	char ch; //Stores the characters as they are input from the file
	char movmnt; //Stores character's movements
	char temp; //Holds character's temporary location (rows)
	char temp2; //Holds character's temporary location (columns)
        int rowsize; //Stores size of rows
        int colsize; //Stores size of columns
        int points=0; //Stores number of points
        int score=0; //Stores overall score
        const int SIZE=81; //Stores size of array to hold name/length of name
        char usrname[SIZE]; //Stores user's name
        Save saves; //Used to save game
        Exeptns exceptn; //Used to throw exceptions
        int cpr; //Stores position of c in puzzle (rows)
        int cpc; //stores position of c in puzzle (columns)
        fstream pzzlFil; //Opens puzzle-storing file
        Load loadedg; //Stores info from loaded game
        int temp3;
        
        pzzlFil.open("puzzle.txt", ios::in);
        
        //Get saved game info
        loadedg=saves.loadgm(pzzlFil, savload);
	//Set rowsize and colsize
        if (loadedg.mode==1) {
            rowsize=3;
            colsize=5;
        } else if (loadedg.mode==2) {
            rowsize=5;
            colsize=5;
        } else {
            rowsize=7;
            colsize=10;
        }
        
        //Create array to store the colors
        char coloray[rowsize][colsize];
        //Fill array
        savload.get(ch); //Skips first character in file
        for (int i=0; i<rowsize; i++) {
            for (int j=0; j<colsize; j++) {
                savload.get(ch); //Get character from file
                coloray[i][j]=ch; //Places character in array
                pzzlFil.put(ch); //Places character in file
            }
        }
        savload.clear(); savload.seekp(0, ios::beg); //Clear eof flag, return to beginning
        pzzlFil.clear(); pzzlFil.seekp(0, ios::beg); //Clear eof flag, return to beginning

	//Create second array to store character's position in array
	char charPos[rowsize][colsize]={'0'};
	charPos[loadedg.rowpos][loadedg.colpos]='c';
        
	//Output the array, but with c in the character's position
	for (int i=0; i<rowsize; i++) {
		for (int j=0; j<colsize; j++) {
			if (charPos[i][j]=='c') {
				cout<<"c"<<" ";
                                pzzlFil.get(ch);
			} else if (i==rowsize-1 && j==colsize-1) {
                            cout<<"f"<<" ";
                        } else {
				pzzlFil.get(ch);
				cout<<ch<<" ";
			}
		}
		cout<<endl;
	}
        pzzlFil.clear(); pzzlFil.seekp(0, ios::beg); //Clear eof flag, return to beginning

	//Start game
        try {
	do {
		//Get user's first movement
		cout<<"Enter w, a, s, or d to move up, backwards, down, or forward one step."<<endl;
		cin>>movmnt;
                if (movmnt=='q') {
                    cout<<"Saving current puzzle and score to a file..."<<endl;
                    //Close and Open file for output
                    savload.close();
                    savload.open("SaveLoad.txt", ios::out);
                    //Get location of 'c'
                    for (int count=0; count<rowsize; count++) {
                        for (int count2=0; count2<colsize; count2++) {
                            if (charPos[count][count2]=='c') {
                                cpr=count;
                                cpc=count2;
                            }
                        }
                    }
                    //Call savegame
                    saves.savegm(pzzlFil, savload, rowsize, colsize, cpr, cpc, score);
                    savload.close();
                    //End current game
                    exceptn.quit();
                }
		while (movmnt!='w' && movmnt!='a' && movmnt!='s' && movmnt!='d') {
			cout<<"You can only move using w, a, s, or d."<<endl;
			cin>>movmnt;
		}
                points++; //Increment points

		//Move character according to user's input
		if (movmnt=='w') {
			for (int i=0; i<rowsize; i++) {
				for (int j=0; j<colsize; j++) {
					if (charPos[i][j]=='c') {
						temp=i; //Store position in rows
						temp2=j; //Store position in columns
					}
				}
			}

			//Input validation
			if (temp-1<0 || coloray[temp-1][temp2]=='r' || coloray[temp-1][temp2]=='y' || (coloray[temp][temp2]=='o' && coloray[temp-1][temp2]=='b')) {
				cout<<"Invalid movement."<<endl;
			} else {
			//Place 'c' in new location
			charPos[(temp-1)][temp2]='c';

			//Clear old location of 'c'
			charPos[temp][temp2]='0';
			}

		} else if (movmnt=='a') {
			for (int i=0; i<rowsize; i++) {
				for (int j=0; j<colsize; j++) {
					if (charPos[i][j]=='c') {
						temp=i; //Store position in rows
						temp2=j; //Store position in columns
					}
				}
			}

			//Input validation
			if (temp2-1<0 || coloray[temp][temp2-1]=='r' || coloray[temp][temp2-1]=='y' || (coloray[temp][temp2]=='o' && coloray[temp][temp2-1]=='b')) {
				cout<<"Invalid movement."<<endl;
			} else {
			//Place 'c' in new location
			charPos[temp][(temp2-1)]='c';

			//Clear old location of 'c'
			charPos[temp][temp2]='0';
			}

		} else if (movmnt=='s') {
			for (int i=0; i<rowsize; i++) {
				for (int j=0; j<colsize; j++) {
					if (charPos[i][j]=='c') {
						temp=i; //Store position in rows
						temp2=j; //Store position in columns
					}
				}
			}
			
			//Input validation
			if (temp+1>(rowsize-1) || coloray[temp+1][temp2]=='r' || coloray[temp+1][temp2]=='y' || (coloray[temp][temp2]=='o' && coloray[temp+1][temp2]=='b')) {
				cout<<"Invalid movement."<<endl;
			} else {
			//Place 'c' in new location
			charPos[(temp+1)][temp2]='c';

			//Clear old location of 'c'
			charPos[temp][temp2]='0';
			}
		} else {
			for (int i=0; i<rowsize; i++) {
				for (int j=0; j<colsize; j++) {
					if (charPos[i][j]=='c') {
						temp=i; //Store position in rows
						temp2=j; //Store position in columns
					}
				}
			}
			
			//Input validation
			if (temp2+1>(colsize-1) || coloray[temp][temp2+1]=='r' || coloray[temp][temp2+1]=='y' || (coloray[temp][temp2]=='o' && coloray[temp][temp2+1]=='b')) {
				cout<<"Invalid movement"<<endl;
			} else {
			//Place 'c' in new location
			charPos[temp][(temp2+1)]='c';

			//Clear old location of 'c'
			charPos[temp][temp2]='0';
			}

		}

		//Ouput new position in puzzle
		for (int i=0; i<rowsize; i++) {
			for (int j=0; j<colsize; j++) {
				if (charPos[i][j]=='c') {
					cout<<"c"<<" ";
                                        pzzlFil.get(ch);
				} else if (i==rowsize-1 && j==colsize-1) {
                                    cout<<"f"<<" ";
                                } else {
					pzzlFil.get(ch);
					cout<<ch<<" ";
				}
			}
			cout<<endl;
		}
                pzzlFil.clear(); pzzlFil.seekp(0, ios::beg); //Clear eof, return to beginning
                
                //Score
                if (rowsize==3) {
                temp3=15-points;
                score=temp3*5;
                } else if (rowsize==5) {
                temp3=35-points; 
                score=temp3*10;
                } else {
                temp3=65-points;
                score=temp3*20;
                }

	} while (charPos[(rowsize-1)][(colsize-1)]!='c');

	//Once they reach the end, congratulate them
	cout<<"Congratulations! You have reached the end of the puzzle!"<<endl;
        //Calculate score
        if (rowsize==3) {
            temp3=15-points;
            score=temp3*5;
            } else if (rowsize==5) {
            temp3=35-points; 
            score=temp3*10;
            } else {
            temp3=65-points;
            score=temp3*20;
            }
        //Display score
        cout<<"Your score was "<<score<<endl;
        //Put score in structure
        UsrInfo player;
        player.totScor=score;
        
        //Get user's name
        cin.ignore();
        cout<<"Enter a name of up to 80 characters."<<endl;
        cin.getline(usrname, SIZE);
        
        //Input to file
        binfile.write(usrname, sizeof(usrname));
        binfile.write(reinterpret_cast<char *>(&player.totScor), sizeof(player.totScor));
        
        //Close file
        savload.close();
        
        //Return player
        return player;
        }
        catch (Exeptns::quitgm) {
            pzzlFil.close();
            cout<<"Game saved."<<endl;
            throw;
        }
}

void fillAry(Mode ezmedhd, int rowsize, int colsize) {
	//declare variables
	int random; //Stores random number
        fstream pzzl1; //Opens file for output
        
        //Create Array
	char puzzle[rowsize][colsize];
	
	//Fill array with random colors
	for (int i=0; i<rowsize; i++) {
		for (int j=0; j<colsize; j++) {
			//Get random number
			random=rand()%6+1; //Random number from 1-8

			//Get character
			if (random==1) {
				puzzle[i][j]='y'; //If 1
			} else if (random==2) {
				puzzle[i][j]='b'; //If 2
			} else if (random==3) {
				puzzle[i][j]='p'; //If 3
			} else if (random==4) {
				puzzle[i][j]='g'; //If 4
			} else if (random==5) {
				puzzle[i][j]='o'; //If 5
			} else if (random==6) {
				puzzle[i][j]='g'; //If 6
			} else if (random==7) {
                            puzzle[i][j]='r'; //If 7
                        } else {
                            puzzle[i][j]='p';
                        }
		}
	}
        
        //Preventing finish being blocked off
        if ((puzzle[(rowsize-1)][(colsize-2)]=='r' || puzzle[(rowsize-1)][(colsize-2)]=='y' || puzzle[(rowsize-1)][(colsize-2)]=='b') && (puzzle[rowsize-2][colsize-1]=='r' || puzzle[rowsize-2][colsize-1]=='y' || puzzle[rowsize-2][colsize-1]=='b')) {
            puzzle[rowsize-1][colsize-2]='g';
        }
        //Preventing start from being blocked off
        if ((puzzle[0][1]=='r' || puzzle[0][1]=='y') && (puzzle[1][0]=='r' || puzzle[1][0]=='y')) {
            puzzle[0][1]='p';
        }
        if (puzzle[0][0]=='o') {
            if (puzzle[0][1]=='b' && puzzle[1][0]=='b') {
                puzzle[0][0]='g';
            } else if ((puzzle[0][1]=='b' && puzzle[1][0]=='r') || (puzzle[0][1]=='b' && puzzle[1][0]=='y')) {
                puzzle[0][0]='p';
            }
        }
        
        //Change last element in array to f
	puzzle[(rowsize-1)][(colsize-1)]='f';
        
        //Write array to file
	pzzl1.open("puzzle.txt", ios::out);
	for (int i=0; i<rowsize; i++) {
		for (int j=0; j<colsize; j++) {
			pzzl1.put(puzzle[i][j]);
		}
	}
        
        //Close file for output
	pzzl1.close();
}