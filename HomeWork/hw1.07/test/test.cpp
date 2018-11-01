#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <iterator>
#include <vector>

using namespace std;


int main()
{
  ifstream File;
  File.open("test.txt");

  vector<string> s;
  string content = "P x P P";
  istringstream temp(content);
  vector<string> s((istream_iterator<string>(temp)),istream_iterator<string>());
  
  //char t = content[0];
  
  // switch(t)
  //  {
  //  case "ss":
  //    cout << "true" << endl;
  //   break;
  //  }

  

  //int *s;
  //int *ss = (int*)malloc(sizeof(int));

  //*ss = 12;
  
  //ss = (int*) realloc(ss,2*sizeof(int));

    //*(ss+1) = 3;

    
  // while(File >> t)
  //   {
  //     if(t.compare("CONTENT:") == 0 )
  // 	content += "\n";
  //     else
  // 	content += t;
  //   }
    
  for(int i = 0 ; i < s.size();i++)
    cout <<s.at(i);
  
 cout <<s.size() <<endl;
 cout <<content;
  
}
