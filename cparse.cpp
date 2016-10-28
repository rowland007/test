#include <cstdio>
#include <vector>
#include <map>
#include <iostream>
#include <string>

//hi!

std::vector<std::string> v_grammar, v_dot, v_goto, v_temp, v_temp2, v_temp3;
std::vector< std::vector< std::string > > v_items;
//std::map<std::string, std::string> m_iSet;


void Augment();
void Items();
void GoTo(std::string goto_, unsigned i);
void Closure(std::string goto_, unsigned i, unsigned k);

int main()
{
	std::string check;
	std::string line;
	
	//read file and store input grammar into a vector
	while (std::cin)
	{
		std::getline (std::cin, line);
		v_grammar.push_back(line);
	}
	
	//call augment phase
	Augment();
	
	Items();
	
	//setup for GoTo function
	
	for (unsigned i = 0; i < v_items.size(); i++)
	{
		for (unsigned k = 0; k < v_items[i].size(); k++)
		{
		  //find next goto character
	      std::string goto_;
          std::string line = v_items[i][k];
          std::size_t found = line.find("@");
  
          //store next character after @
          goto_ = line.substr(found+1, 1);
		  //std::cout << "line: " << line <<std::endl;
          //std::cout << "goto: " << goto_ << std::endl;
          //std::cout << found <<std::endl;
		  
		  
		  //do not call GoTo on characters that have been seen as goto for this vector
		  if (v_temp.empty())
		  {
			  v_temp.push_back(goto_);
		      GoTo(goto_, i);
		  }
		  
		  for (unsigned j = 0; j <= v_temp.size(); j++)
		  {
		    if (goto_ == v_temp[j])
				break;
			
			if (j == v_temp.size()-1)
		    {
				v_temp.push_back(goto_);
	          GoTo(goto_, i);
			
		    }
		  }
		  
		}
	 }
	
	
	//print output
	std::cout << "Augmented Grammar\n"
              << "-----------------" << std::endl;
	for (unsigned i = 0; i < v_grammar.size(); i++)
	{
				
		std::cout << v_grammar[i] << std::endl;
	}
	
	std::cout << "Sets of LR(0) Items\n"
	          << "-------------------" << std::endl;
	
	  
	
	
	for (unsigned i = 0; i < v_items.size(); i += 2)
	{
		if (i == 0)
		  std::cout << "I" << i << ":" << std::endl;
		else
		  std::cout << "I" << i-1 << ":" << std::endl;
		
		for (unsigned k = 0; k != v_items[i].size(); k++)
		{
			std::cout << "   " << v_items[i][k] << std::endl;
		}
	}
}

//Augment the grammar by adjusting the first rule
void Augment()
{
	std::vector<std::string>::iterator i = v_grammar.begin();
	std::string old = v_grammar[0];
	std::string replace = "~->" + old;
	v_grammar.erase (v_grammar.begin());
	v_grammar.insert(i, replace);
}

void Items()
{
	
	//place @ into first spot in augmented grammar/store non terminal characters
	for (unsigned i = 0; i != v_grammar.size() - 1; i++)
	{
	  //place @ into first spot in augmented grammar
	  std::string line = v_grammar[i];
	  std::string add = "@";
	  line.insert(3, add);
	
	  //push into v_dot vector wtih @ in grammar
	  v_dot.push_back(line);
	  
	  
	  //store non terminal characters in v_temp2
	  if (isalpha(line[0]))
	  {
		 std::string front = line.substr(0,1);
		 
		 if ( v_temp2.empty() )
		    v_temp2.push_back(front);
		
		 else
		 {
		    for (unsigned k = 0; k <= v_temp2.size(); k++)
		    {
		      if (front == v_temp2[k])
				break;
		
			  if (k == v_temp2.size()-1)
			    v_temp2.push_back(front);	
		    }
		 }
	  }
	  //std::cout << v_temp2.size() << std::endl;
	  //std::cout << line << std::endl;
	}

	
	v_items.push_back(v_dot);
	
	//clear v_dot for future use
	v_dot.clear();
		
}


void GoTo(std::string goto_, unsigned i)
{
	std::cout << "goto: " << goto_ << std::endl;
    
	//loop through v_items["first"]
	for (unsigned k = 0; k < v_items[i].size(); k++)
	{
		//find next character after @
		std::string line = v_items[i][k];
		std::size_t found = line.find("@");
		std::string line2 = line.substr(found+1, 1);
		//std::cout << "line: " << line << std::endl;
		//std::cout << "line2: " << line2 << std::endl;
		
		//if the goto and the next character match, move @ one and store strings into a vector
		if (goto_ == line2)
		{ 
	      //move @ up one
		  line = line.erase(found, 1);
		  line = line.insert(found+1, "@");
		  found = line.find("@");
		//std::cout << "line: " << line << std::endl;
		
		  //if at end of string push onto vector
		  if (found == line.size()-1)
		  {
		  	v_dot.push_back(line);
			continue;
		  }
		  v_dot.push_back(line);
		  goto_ = line.substr(found+1, 1);
		  //std::cout << "goto: " << goto_ << std::endl;
		
		  /*
		  for (unsigned j = 0; j <= v_temp2.size(); j++)
		    {
		      if (goto_ == v_temp2[j])
			  {
				  std::cout << "goto: " << goto_ << std::endl;
				GoTo(goto_, i);
			  }
			  //if (j == v_temp2.size()-1)
			   // v_temp2.push_back(line);	
		    }*/
		
		}
	}
	
	//std::cout << v_dot[0] << std::endl;
	//v_items.push_back(v_temp3);
	//v_items.push_back(v_dot);
	//v_dot.clear();
	
	for (unsigned k = 0; k < v_dot.size(); k++)
	{
		std::cout << v_dot[k] << std::endl;
	}
	std::cout << "------------------------" <<std::endl;
/*
  //find next character after @
 for (unsigned i = 0 ; i < v_items.size(); i += 2)
  {
	for (unsigned k = 0; k < v_items[i].size(); k++)
	{
      std::string goto_;
      std::string line = v_items[i][k];
      std::size_t found = line.find("@");
  
      //store next character after @
      goto_ = line.substr(found+1, 1);
	  
      //std::string goto_line = "goto(" + goto_ + ")=";
	  //v_goto[k] = goto_line;
      Closure(goto_, i, k);
  
  
      //std::cout << "line: " << line <<std::endl;
      //std::cout << "goto: " << goto_ << std::endl;
      //std::cout << found <<std::endl;
	}
  }*/
}


void Closure(std::string goto_, unsigned i, unsigned k)
{
  std::string newLine;
  std::string line = v_items[i][k];
  std::size_t found = line.find("@");
  
  if (goto_ == line.substr(found+1, 1))
  {
	  newLine = v_grammar[k];
	  newLine.insert(found+1, "@");
  }
  
std::cout << i << k << " "<< "goto: " << goto_ << " " << line << " " << newLine<<std::endl;
	
}

