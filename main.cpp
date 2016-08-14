#include <iostream>
#include <cstdlib>
#include <fstream>
#include <map>
#include <vector>


typedef std::vector<std::string> hand; //five cards, (first hald and second half)
typedef std::vector<std::string> file_line; //will read one line of the textfile and store
typedef std::map<char, int> frequency_table; // frequency table that will be recording

//function splits fileline into two hands
void split(file_line& fl, hand& h1, hand& h2){ 
  file_line::iterator iter;
  unsigned int counter = 1;
  for(iter = fl.begin(); iter != fl.end(); ++iter){
    if(counter <= (fl.size()/2)){
      h1.push_back(*iter);
    }else{
      h2.push_back(*iter);
    }
    counter++;
  }
}

void print_frequency_table(frequency_table& table){ //generate table and set frequency to 0
  frequency_table::iterator iter;
  for(iter = table.begin(); iter != table.end(); ++iter){
    std::cout << iter->first << " " << iter->second << '\n';
  }

}

//gets frequency of rank (first character in string), used for determining one, two pair, three/four of a kind, and full-house
void frequency_count(hand& check, frequency_table& table){
  hand::iterator iter;
  std::vector<char> ranks;
  std::string holder;
  for(iter = check.begin(); iter != check.end(); ++iter){
    holder = *iter;
    ranks.push_back(holder[0]);
  }
  std::vector<char>::iterator iter2;
  for(iter2 = ranks.begin(); iter2 != ranks.end(); ++iter2){
    frequency_table::iterator iter3 = table.find(*iter2);
    if(iter3 != table.end()){
      iter3->second += 1;
    }else{
      table.insert(std::make_pair(*iter2, 1));
    }
  }
  
}

//checks the frequency table for pairs, three of a kind, two pairs, full house, and quads
void check_frequency(frequency_table table){
  frequency_table::iterator iter;
  std::vector<int> freq_count;
  for(iter = table.begin(); iter != table.end(); ++iter){
    freq_count.push_back(iter->second);
  }
  std::vector<int>::iterator iter2;
  int two_count, three_count, four_count;
  two_count = three_count = four_count = 0;

  for(iter2 = freq_count.begin(); iter2 != freq_count.end(); ++iter2){
    int temp = *iter2;
    
    switch(temp){
    case 1:
      break;
    case 2:
      two_count++;
      break;
    case 3:
      three_count++;
      break;
    case 4:
      four_count++;
      break;
    default:
      std::cout << "It's broken you fucking idiot\n";
    }
   
  }

  
  if(two_count == 1 && three_count != 1){
    std::cout << "One pair detected\n";
  }else if(two_count == 2){
    std::cout << "Two pair detected\n";
  }else if(three_count == 1 && two_count != 1){
   std::cout << "Three of a kind detected\n";
  }else if(three_count == 1 && two_count == 1){
   std::cout << "Full house detected\n";
  }else if(four_count == 1){
   std::cout << "Four of a kind detected\n";
  }else{
    std::cout << "High card detected (potentially)\n";
  }

}

//gets suit (second character in string) and compares if same throughout
bool check_flush(hand& check){ 
  hand::iterator iter;
  std::vector<char> suits;
  std::string holder;
  for(iter = check.begin(); iter != check.end(); ++iter){ //get_suit
    holder = *iter;
    suits.push_back(holder[1]);
  }
  std::vector<char>::iterator iter2;
  bool is_flush = true;
  char comparison = suits[0];
  for(iter2 = suits.begin(); iter2 != suits.end(); ++iter2){
    if(comparison != *iter2){
      is_flush = false;
      break;
    }
    comparison = *iter2;
  }
  return is_flush;
}

int main(int argc, char** argv){
  hand hand1;
  hand hand2;
  file_line something;
  hand1.push_back("6C");
  hand1.push_back("6D");
  hand1.push_back("AH");
  hand1.push_back("3S");
  hand1.push_back("8D");
  std::cout << check_flush(hand1) << '\n';
  std::cout << '\n';
  frequency_table test1;
  frequency_count(hand1, test1);
  check_frequency(test1);

  return 0;
}
