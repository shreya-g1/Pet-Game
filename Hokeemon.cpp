//Hokeemon.cpp
//Shreya Gowda, CISP 400
//12/08/19

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// Specification A3 - Code Protection
class InvalidInput{
//class to check for invalid input 
//uses throw-try-catch method

  public:

  //exceptions
  class InvalidString{};

  void checkString(string d, const string* v, int n){
    //checks if input matches valid string options

    const string* valid=v;
    int num_valid=n;
    string data=d;
    bool contains=false;

    //checks to see if string matches another string from an array of valid strings
    for(int i=0; i<num_valid; i++){
      if(valid[i]==data){
        contains=true;
      }
    }

    //if not a matching string, throws exception
    if(!contains){    
      throw InvalidString();
    }
  }

};

// Specification C2 - Virtual Class Creature
class Creature{
  protected:
  static const int MAX_HUNGER=10;
  static const int MAX_BORED=20;
  int hunger;
  int boredom;
  int turns_happy;
  string mood;
  string name;

  // Specification C1 - PassTime()
  void passTime(){
    //when menu option chosen, increases hunger & boredom
    hunger++;
    boredom++;

    checkMood();
  }

  //Specification B2 - Moods
  void checkMood(){
    //sets mood based on boredom state
    if(boredom<=4){
      mood="HAPPY";
      turns_happy++;
    }
    else if(boredom<=9){
      mood="OK";
    }
    else if(boredom<=14){
      mood="FRUSTRATED";
    }
    else{
      mood="MAD";
    }
  }

  public:
  //constructor
  Creature(){
    hunger=rand()%6;
    boredom=rand()%6;
    turns_happy=0;
    name="";
    mood="";
    checkMood();
  }

  void setName(string n){
    name=n;
  }

  string getName(){
    return name;
  }

  bool checkDeath(){
    //checks if pet died of high hunger or boredom
    if(hunger>MAX_HUNGER||boredom>MAX_BORED){
      return true;
    }
    return false;
  }

  virtual void Listen()=0;  
  //tells you it’s current hunger and boredom states.

  virtual void Play()=0;
  //to reduce boredom by 4

  virtual void Feed()=0;
  //to reduce hunger by 4

  virtual ~Creature(){} 
  //virtual destructor for virtual class, so behavior is defined when object destoyed      

};

// Specification C3 - Child Class
class Berunda: public Creature{
  public:
  //constructor
  Berunda(){
    hunger=rand()%6;
    boredom=rand()%6;
    turns_happy=0;
    name="";
    mood="";
    checkMood();
  }

  // Specification A2 - Copy Constructor/Assignment Operator
  Berunda(const Berunda &obj){
    hunger=obj.hunger;
    boredom=obj.boredom;
    turns_happy=obj.turns_happy;
    mood=obj.mood;
    name=obj.name;
  }

  Berunda& operator=(const Berunda &obj){
    hunger=obj.hunger;
    boredom=obj.boredom;
    turns_happy=obj.turns_happy;
    mood=obj.mood;
    name=obj.name;

    return *this;
  }

  void Listen(){
    //listen function for berunda
    cout<<"My boredom is "<<boredom<<". I am "<<mood<<"."<<endl;
    cout<<"My hunger is "<<hunger<<"."<<endl;
    cout<<"I enjoy your companionship comrade!"<<endl;
    passTime();
  }

  void Play(){
    //play function for berunda
    passTime();
    cout<<"Caw! I like playing tug of war. Challenge me again sometime."<<endl;
    if(boredom<=4){
      boredom=0;
    }
    else{
      boredom-=4;
    }
  }

  void Feed(){
    //feed function for berunda
    passTime();
    cout<<"HA! A gold-encrusted mackarel. The only meal suitable for royalty. "<<endl;
    if(hunger<=4){
      hunger=0;
    }
    else{
      hunger-=4;
    }
  }
};

// Specification B3 - Second Child Class
class Chakora: public Creature{
  public:
  //constructor
  Chakora(){
    hunger=rand()%6;
    boredom=rand()%6;
    turns_happy=0;
    name="";
    mood="";
    checkMood();
  }

  //copy constructor
  Chakora(const Chakora &obj){
    hunger=obj.hunger;
    boredom=obj.boredom;
    turns_happy=obj.turns_happy;
    mood=obj.mood;
    name=obj.name;
  }

  //copy assignment operator
  Chakora& operator=(const Chakora &obj){
    hunger=obj.hunger;
    boredom=obj.boredom;
    turns_happy=obj.turns_happy;
    mood=obj.mood;
    name=obj.name;
    
    return *this;
  }

  void Listen(){
    //listen function for chakora
    cout<<"My boredom is "<<boredom<<". I am "<<mood<<"."<<endl;
    cout<<"My hunger is "<<hunger<<"."<<endl;
    cout<<"I am happy you are spending time with me! Chirp chirp"<<endl;
    passTime();
  }

  void Play(){
    //play function for chakora
    passTime();
    cout<<"Yay! This is fun! I love jigsaw puzzles."<<endl;
    if(boredom<=4){
      boredom=0;
    }
    else{
      boredom-=4;
    }
  }

  void Feed(){
    //feed function for chakora
    passTime();
    cout<<"Mmmm, moonflower seeds. My favorite! Thank you."<<endl;
    if(hunger<=4){
      hunger=0;
    }
    else{
      hunger-=4;
    }
  }
};

//Function Prototypes
void Intro(Creature** pet_ptr);
string Menu();

int main() {
  Creature* pet;
  string opt="";
  srand(time(0));
  bool dead=false;

  Intro(&pet);

  //menu options behavior. if user quits or pet is dead, exits game.
  while(opt!="4"&&!dead){
    //gets menu option
    cout<<endl;
    opt=Menu();
    cout<<endl;
    
    //menu options behaviors: 1=listen, 2=play, 3=feed
    if(opt=="1"){
      pet->Listen();
    }
    if(opt=="2"){
      pet->Play();
    }
    if(opt=="3"){
      pet->Feed();
    }

    //for nice display, clears screen
    if(opt!="1"&&opt!="4"){
      cout<<"Press enter to continue >>";
      cin.ignore();
      system("clear");
      cout<<"Hokeemon"<<endl;
    }

    //checks for death after each turn
    dead=pet->checkDeath();
  }

  //displays message if pet died
  if(dead){
    cout<<endl<<"I'm sorry, you're hokeemon has gone unconcious due to negligence."<<endl<<" It has been taken to emergency care."<<endl;
  }

  //program closing statement
  cout<<"Thanks for playing Hokeemon!"<<endl;
  delete pet;
}

string Menu(){
  //displays menu and validates input

  const int NUM_VAL_INPUTS=4;
  const string VALID_INPUTS[NUM_VAL_INPUTS]={"1","2","3","4"};
  string user_input;
  InvalidInput check;

  //menu displayed
  cout<<"Menu"<<endl;
  cout<<"(1) Listen"<<endl;
  cout<<"(2) Play"<<endl;
  cout<<"(3) Feed"<<endl;
  cout<<"(4) Quit"<<endl;

  // Specification B1 - Validate Input
  while(user_input!=VALID_INPUTS[0]&&user_input!=VALID_INPUTS[1]&&user_input!=VALID_INPUTS[2]&&user_input!=VALID_INPUTS[3]){
    try{
      //gets input
      cout<<"enter: ";
      getline(cin, user_input);

      //checks for exceptions using InvalidInput class
      check.checkString(user_input, VALID_INPUTS, NUM_VAL_INPUTS);
    }
    catch(InvalidInput::InvalidString){
      cout<<"Invalid input. Choose a number from the menu."<<endl;
    }
  }

  return user_input;
}

void Intro(Creature** pet_ptr){
  //greetings & choosing a pet

  const int NUM_PET_TYPES=2;
  const int PET_TYPE_WORD_LENGTH=7;
  string VALID_PET_TYPES[NUM_PET_TYPES]={"berunda", "chakora"};
  string pet_type="";
  string name="";
  InvalidInput check;

  //Program Greeting
  cout<<"Hokeemon"<<endl<<endl;
  cout<<"Raise Your Own Magical Creature."<<endl<<endl;
  cout<<"Press enter to begin >>";
  cin.ignore();
  system("clear");

  //display pet types
  cout<<"Hokeemon"<<endl<<endl;
  cout<<"Creature type: Berunda or Chakora? "<<endl;

  //validates pet type and catches exceptions
  while(pet_type!=VALID_PET_TYPES[0]&&pet_type!=VALID_PET_TYPES[1]){
    try{
      //gets input
      getline(cin, pet_type);

      //making input lowercase
      for(int i=0; i<PET_TYPE_WORD_LENGTH; i++){
        pet_type[i]=tolower(pet_type[i]);
      }

      //checks for exceptions using InvalidInput class
      check.checkString(pet_type, VALID_PET_TYPES, NUM_PET_TYPES);
    }
    catch(InvalidInput::InvalidString){
      cout<<"That is not one of the options please retype."<<endl;
    }
  }

  //sets creature to specific type (child class)
  if(pet_type=="berunda"){
    *pet_ptr=new Berunda();
  }
  if(pet_type=="chakora"){
    *pet_ptr=new Chakora();
  }

  cout<<endl;

  // Specification A1 - Critter Name
  cout<<"Name your critter"<<endl;
  getline(cin, name);
  (*pet_ptr)->setName(name);
}
