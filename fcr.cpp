#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <dirent.h>

using namespace std;

bool is_csv(const string& filename);
void lscsv();

int main()
{
  lscsv();
  string namefile("");
  cout << "type the CSV filename" << endl;
  cin >> namefile;
  cin.ignore();
  
  
  ifstream file(namefile);
  if (!file.is_open())
    {
      cerr << "Failed to open the file" << endl;
      return 1;
    }

  // Create a map to hold the flashcards
  map<string, string> flashcards;

  string line;
  while (getline(file, line))
    {
      // Split the line by the comma delimiter
      size_t pos = line.find(',');
      string term = line.substr(0, pos);
      string definition = line.substr(pos + 1);
      flashcards[term] = definition;
    }
  file.close();

  
  for (const auto& flashcard : flashcards)
    {
      cout << flashcard.first;
      cin.get();
      cout << flashcard.second << endl;
    }

  return 0;
}




bool is_csv(const string& filename)
{
  return (filename.size() >= 4 &&
	  filename.substr(filename.size() - 4, 4) == ".csv");
}


void lscsv()
{
  DIR* dir = opendir(".");
  if (dir == NULL)
    {
      cerr << "Unable to open directory" << endl;
      //return 1;
    }
  struct dirent* entry;
  while ((entry = readdir(dir)) != NULL)
    {
      string filename(entry->d_name);
      if (is_csv(filename))
	{
	  cout << "\t"  << filename << endl;
	}
    }
  
  closedir(dir);

}
