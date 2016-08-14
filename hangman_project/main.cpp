#include <cctype>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

typedef std::map<char, bool> used_letters; //letter bank, true=used, false=unused
typedef std::vector<std::string> word_bank; //word_bank


/*utility functions to make game-loop cleaner*/
void to_lower(std::string& word){
  for(unsigned int i = 0; i < word.length(); ++i){
    word[i] = tolower(word[i]);
  }
  
}
/*functions pertaining to the key*/
used_letters generate_key(){
  used_letters list;
  for(unsigned int i = 0; i < 26; ++i){
    list.insert(std::make_pair((char)(i+97), false));
  }
  return list;
}

void print_key(used_letters li){
  for(used_letters::iterator it= li.begin(); it != li.end(); ++it){
    std::cout << it->first << ": " << it->second << '\n';
  }
}

void set_used(used_letters& li, char let_){
  used_letters::iterator it;
  it = li.find(let_);
  if(it != li.end()){
    it->second = true;
  }
}

bool letter_used(used_letters& li, char let_){
  used_letters::iterator it;
  it = li.find(let_);
  if(it != li.end()){
    if(it->second){
      return true;
    }else{
      return false;
    }
  }
  return false;
}



/*user/human input*/
char get_human_input(used_letters& li){
  char input;
  do{
    std::cout << "Enter a letter. ";
    std::cin >> input;
    std::cin.ignore();
  }while(isalpha(input) == 0 || letter_used(li, input));
  

  return input;
}

/*generate word_bank from text file*/
void generate_word_bank(word_bank& bank){
  std::ifstream word_file;
  std::string temp;
  word_file.open("words.txt");
  if(word_file.is_open()){
    while(!word_file.eof()){
      getline(word_file, temp);
      bank.push_back(temp);
    }
  }
  word_file.close();
}


/*basic game loop for players (and probably ai as well)*/
void game_loop(std::string word){
  int guesses = 0;
  int max_guesses = 5;
  bool solved = false;
  to_lower(word);
  const char* word_ = word.c_str();
  unsigned int length = strlen(word_);
  char* display = new char[length];
  used_letters letter_bank = generate_key();
  
  for(unsigned int i = 0; i < word.length(); ++i){
    display[i] = '-';
  }
 
  while(guesses != max_guesses && !solved){
    std::system("clear");
    std::cout << "You have " << (max_guesses - guesses) << " guesses left" << std::endl;
    bool no_guess = true;
    char guess = ' ';
    for(unsigned int j = 0; j < length; j++){
      std::cout << display[j];
      if(display[j] == '-'){
	no_guess = false;
      }
    }
    if(no_guess){
      solved = true;
      std::cout << "\nYou solved the puzzle. Good for you!" << '\n';
      break;
    }
    std::cout << '\n';
    guess = get_human_input(letter_bank);
    set_used(letter_bank, guess);
    bool is_letter = false;
    for(unsigned int k = 0; k < length; k++){
      if(word_[k] == guess){
	display[k] = guess;
	is_letter = true;
      }
    }
    if(!is_letter){
      guesses++;
    }
    
  }

  if(!solved){
    std::system("clear");
    std::cout << "The word was " << word << '\n';
    std::cout << "You didn't get the word\n";
    std::cout << "You're a fucking idiot you know?\n";
  }

  delete[] display;
}

int main(int argc, char** argv){
  word_bank test;
  generate_word_bank(test);

  srand(time(0));
  int seed = rand() % test.size();
  std::string word = test[seed];
  game_loop(word);
 
  return 0;
}
