/************************************************************************
Program:			
Author:				Anthony Rawls
Class:				
Instructor:		
Date:					
Description:	 
Input:
Output:

Compilation instructions:
Usage:
Known bugs/missing features:

Modifications:
Date                Comment
----    	------------------------------------------------
1Nov2016	Modified global variable names to easier identity that they are globals
1Nov2016	Removed unused AKA commented code
************************************************************************/
#include <cstdio>
#include <vector>
#include <map>
#include <iostream>
#include <string>

//Declare global variables
std::vector<std::string> g_vGrammar;	///< This vector is used for 
std::vector<std::string> g_vDot;			///< This vector is used for 
std::vector<std::string> g_vGoto;			///< This vector is used for 
std::vector<std::string> g_vTemp;			///< This vector is used for 
std::vector<std::string> g_vTemp2;		///< This vector is used for 
std::vector<std::string> g_vTemp3;		///< This vector is used for 
std::vector< std::vector< std::string > > g_vItems;	///< This vector within a vector is used for 

//Function prototypes
void Augment();
void Items();
void GoTo(std::string, unsigned);
void Closure(std::string, unsigned, unsigned);

int main()
{
	std::string szCheck;	///< This string is used for 
	std::string szLine;		///< This string is used for
	
	//read file and store input grammar into a vector
	while (std::cin)
	{
		std::getline (std::cin, szLine);
		g_vGrammar.push_back(szLine);
	}
	
	//call augment phase
	Augment();
	
	Items();
	
	//setup for GoTo function
	for (unsigned i = 0; i < g_vItems.size(); i++)
	{
		for (unsigned k = 0; k < g_vItems[i].size(); k++)
		{
			//find next goto character
	    std::string goto_;
      std::string szLine = g_vItems[i][k];
      std::size_t found = szLine.find("@");
  
      //store next character after @
      goto_ = szLine.substr(found+1, 1);		  
		  
		  //do not call GoTo on characters that have been seen as goto for this vector
		  if (g_vTemp.empty())
		  {
			  g_vTemp.push_back(goto_);
		    GoTo(goto_, i);
		  }
		  
		  for (unsigned j = 0; j <= g_vTemp.size(); j++)
		  {
		    if (goto_ == g_vTemp[j])
				break;
			
				if (j == g_vTemp.size()-1)
		  	{
					g_vTemp.push_back(goto_);
	        GoTo(goto_, i);
			
		  	}
		  } 
		}
	 }
	
	
	//print output
	std::cout << "Augmented Grammar\n"
            << "-----------------" << std::endl;
	for (unsigned i = 0; i < g_vGrammar.size(); i++)
	{
		std::cout << g_vGrammar[i] << std::endl;
	}
	
	std::cout << "Sets of LR(0) Items\n"
	          << "-------------------" << std::endl;	
	
	for (unsigned i = 0; i < g_vItems.size(); i += 2)
	{
		if (i == 0)
		  std::cout << "I" << i << ":" << std::endl;
		else
		  std::cout << "I" << i-1 << ":" << std::endl;
		for (unsigned k = 0; k != g_vItems[i].size(); k++)
		{
			std::cout << "   " << g_vItems[i][k] << std::endl;
		}
	}
}


/// Augment the grammar by adjusting the first rule
void Augment()
{
	std::vector<std::string>::iterator i = g_vGrammar.begin();
	std::string old = g_vGrammar[0];
	std::string replace = "~->" + old;
	g_vGrammar.erase (g_vGrammar.begin());
	g_vGrammar.insert(i, replace);
}

/// Items does this:
void Items()
{	
	//place @ into first spot in augmented grammar/store non terminal characters
	for (unsigned i = 0; i != g_vGrammar.size() - 1; i++)
	{
	  //place @ into first spot in augmented grammar
	  std::string line = g_vGrammar[i];
	  std::string add = "@";
	  line.insert(3, add);
	
	  //push into g_vDot vector wtih @ in grammar
	  g_vDot.push_back(line);
	  
	  //store non terminal characters in g_vTemp2
	  if (isalpha(line[0]))
	  {
		 std::string front = line.substr(0,1);
		 
		 if ( g_vTemp2.empty() )
		    g_vTemp2.push_back(front);
		 else
		 {
		    for (unsigned k = 0; k <= g_vTemp2.size(); k++)
		    {
		      if (front == g_vTemp2[k])
						break;
				  if (k == g_vTemp2.size()-1)
				    g_vTemp2.push_back(front);	
		    }
			}
	  }
	}
	g_vItems.push_back(g_vDot);
	
	//clear g_vDot for future use
	g_vDot.clear();	
}

/// GoTo is used for:
/// @param goto_ Is a string used to 
/// @param i Is an unsigned type used for 
void GoTo(std::string goto_, unsigned i)
{
	std::cout << "goto: " << goto_ << std::endl;
    
	//loop through g_vItems["first"]
	for (unsigned k = 0; k < g_vItems[i].size(); k++)
	{
		//find next character after @
		std::string line = g_vItems[i][k];
		std::size_t found = line.find("@");
		std::string line2 = line.substr(found+1, 1);
		
		//if the goto and the next character match, move @ one and store strings into a vector
		if (goto_ == line2)
		{ 
	    //move @ up one
		  line = line.erase(found, 1);
		  line = line.insert(found+1, "@");
		  found = line.find("@");
		
		  //if at end of string push onto vector
		  if (found == line.size()-1)
		  {
		  	g_vDot.push_back(line);
				continue;
		  }
		  g_vDot.push_back(line);
		  goto_ = line.substr(found+1, 1);		
		}
	}	
	for (unsigned k = 0; k < g_vDot.size(); k++)
	{
		std::cout << g_vDot[k] << std::endl;
	}
	std::cout << "------------------------" <<std::endl;
}

/// Closure does this:
/// @param i Is an unsigned type used for 
/// @param k Is an unsigned type used for 
void Closure(std::string goto_, unsigned i, unsigned k)
{
  std::string newLine;
  std::string line = g_vItems[i][k];
  std::size_t found = line.find("@");
  
  if (goto_ == line.substr(found+1, 1))
  {
	  newLine = g_vGrammar[k];
	  newLine.insert(found+1, "@");
  }
	std::cout << i << k << " "<< "goto: " << goto_ << " " << line << " " << newLine<<std::endl;
}