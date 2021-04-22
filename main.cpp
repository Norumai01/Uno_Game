/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

ECGR Team 1 UNO Project
https://service.mattel.com/instruction_sheets/42001pr.pdf

*******************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

vector <string> userNameList;
string userNameTemp;
const vector <string> cardNames{"Blue0", "Blue1", "Blue2", "Blue3", "Blue4", "Blue5", "Blue6", "Blue7", "Blue8", "Blue9", "BlueSkip", "BlueReverse", "BluePlus2", "Red0", "Red1", "Red2", "Red3", "Red4", "Red5", "Red6", "Red7", "Red8", "Red9", "RedSkip", "RedReverse", "RedPlus2", "Yellow0", "Yellow1", "Yellow2", "Yellow3", "Yellow4", "Yellow5", "Yellow6", "Yellow7", "Yellow8", "Yellow9", "YellowSkip", "YellowReverse", "YellowPlus2", "Green0", "Green1", "Green2", "Green3", "Green4", "Green5", "Green6", "Green7", "Green8", "Green9", "GreenSkip", "GreenReverse", "GreenPlus2", "WildPlus4", "WildPlus4", "Wild", "Wild"};
vector <string> tempDeck;
vector <string> deck;
vector <string> discardPile;
bool isUNO = false;
bool isUnoOut = false;
string activePlayer;
string userMove;
string winner;
int count = 0;
int i = 0;
int direction = 1;
int numberDraws = 0;

vector <string> user1Hand; //associate with userNameList index(0,1,2,3) in code
vector <string> user2Hand;
vector <string> user3Hand;
vector <string> user4Hand;

string colorSetting;
int numberSetting;
string topCard;

string CardColor(string card){
    string color;
    if(card.find("Yellow")<7){
        color = "Yellow";
    }
    else if(card.find("Blue")<7){
        color = "Blue";
    }
    else if(card.find("Red")<7){
        color = "Red";
    }
    else if(card.find("Green")<7){
        color = "Green";
    }
    return color;
}

int CardNumber(string card){
    int number = 0;
    if(card.find("1")<7){
        number = 1;
    }
    else if(card.find("2")<7){
        number = 2;
    }
    else if(card.find("3")<7){
        number = 3;
    }
    else if(card.find("4")<7){
        number = 4;
    }
    else if(card.find("5")<7){
        number = 5;
    }
    else if(card.find("6")<7){
        number = 6;
    }
    else if(card.find("7")<7){
        number = 7;
    }
    else if(card.find("8")<7){
        number = 8;
    }
    else if(card.find("9")<7){
        number = 9;
    }
    else if(card.find("0")<7){
        number = 0;
    }
    else if(card.find("Reverse")<14){
        number = 10;
    }
    else if(card.find("Skip")<14){
        number = 11;
    }
    else if(card.find("Plus2")<14){
        number = 12;
    }
    else if(card.find("Plus4")<14){
        number = 14;
    }
    else if(card.find("Wild")<14){
        number = 13;
    }
    
    return number;
}

void PrintColor(string colorPrint){
    
    colorPrint = CardColor(colorPrint);
    
    if(colorPrint == "Blue"){
        printf("\033[1;34m");
    }
    else if(colorPrint == "Green"){
        printf("\033[1;32m");
    }
    else if(colorPrint == "Yellow"){
        printf("\033[1;33m");
    }
    else if(colorPrint == "Red"){
        printf("\033[1;31m");
    }
    else{
        printf("\033[0m");
    }
}

void GetUserNames(){

        cout << "List the names of the players with a space in between and 'stop' at the end: ";
        cin >> userNameTemp;
        while(userNameTemp != "stop"){
            ++i;
            userNameList.push_back(userNameTemp);
            cin >> userNameTemp;
            }
        cout << endl << "There are " << i << " players. Let's begin!" << endl;
        count = i*100;
        activePlayer = userNameList.at(count%i);
    }
    
void ShuffleDeck(){
    //empties discardPile and adds cards to deck in random order
    while(discardPile.size() != 0){
        int randTemp = rand()%discardPile.size();
        deck.push_back(discardPile.at(randTemp));
        discardPile.erase(discardPile.begin() + randTemp); // http://www.cplusplus.com/reference/vector/vector/erase/
    }
    
    if(deck.size() == 0){
        tempDeck = cardNames;
        for(int x = 0; x < cardNames.size(); ++x){
            int randTemp2 = rand()%tempDeck.size();
            deck.push_back(tempDeck.at(randTemp2));
            tempDeck.erase(tempDeck.begin() + randTemp2); // http://www.cplusplus.com/reference/vector/vector/erase/
        }
    }
}

void DealCards(){
    //every user gets seven cards from deck and moves one to the discard
    for(int x=0; x<7; ++x){
        //FIXME get a first card from deck
        user1Hand.push_back(deck.back());
        deck.pop_back();
        
        user2Hand.push_back(deck.back());
        deck.pop_back();
        
        user3Hand.push_back(deck.back());
        deck.pop_back();
        
        user4Hand.push_back(deck.back());
        deck.pop_back();
    }
    discardPile.push_back(deck.back());
    deck.pop_back();
    
    if(discardPile.back() == "Wild" || discardPile.back() == "WildPlus4" ){
        ShuffleDeck();
    }
    
    
    topCard = discardPile.back();                                   //
    cout << "The top of the discard pile is " << topCard << endl;
    
    colorSetting = CardColor(topCard);
    numberSetting = CardNumber(topCard);
}

void ShowUserHand(){
    //gets activePlayer and displays their list of cards
    cout << "Your cards are: ";
    switch(count%i){
        case 0:
            for(int x = 0; x<user1Hand.size(); ++x){
            PrintColor(user1Hand.at(x));
            cout << user1Hand.at(x) << " ";
            }
            printf("\033[0m");
            break;
        case 1:
            for(int x = 0; x<user2Hand.size(); ++x){
            PrintColor(user2Hand.at(x));
            cout << user2Hand.at(x) << " ";
            }
            printf("\033[0m");
            break;
        case 2:
            for(int x = 0; x<user3Hand.size(); ++x){
            PrintColor(user3Hand.at(x));
            cout << user3Hand.at(x) << " ";
            }
            printf("\033[0m");
            break;
        case 3:
            for(int x = 0; x<user4Hand.size(); ++x){
            PrintColor(user4Hand.at(x));
            cout << user4Hand.at(x) << " ";
            }
            printf("\033[0m");
            break;
        
    }
    cout << endl;
    
}

void DrawCard(){
    //gets the first index of deck, push_back userHand, deletes card from deck, checks cards in deck and shuffles if needed
    if(deck.size() == 0){
        ShuffleDeck();
    }
    switch(count%i){
        case 0:
            user1Hand.push_back(deck.back());
            deck.pop_back();
            break;
        case 1:
            user2Hand.push_back(deck.back());
            deck.pop_back();
            break;
        case 2:
            user3Hand.push_back(deck.back());
            deck.pop_back();
            break;
        case 3:
            user4Hand.push_back(deck.back());
            deck.pop_back();
            break;
    }
    ShowUserHand();
}

void ChangeActivePlayer(){
    //increments activePlayer down userNameList
    if(direction == 1){
        ++count;
    }
    else{
        --count;
    }
    activePlayer = userNameList.at(count%i);
}

void Skip(){
    ChangeActivePlayer();
}

void reverseCard(){
    if(direction == 1){ //initial and clockwise direction being changed to counter-cloclwise
        direction = 0;
    }
    else{
        direction = 1;//if counter-cloclwise changes to clockwise
    }
}

void Plus2(){
        ChangeActivePlayer();// changes activePlayer to player who draws 2 cards
        string answer;
        
        ShowUserHand();
        
        cout << endl << "It is "<< activePlayer << "'s turn. Do you have a draw card? (y/n): ";
        cin >> answer;
        
        if(answer == "n"){
         DrawCard();//Draw 1
         DrawCard();//Draw 2
        }
        else{
            numberDraws += 2;
            reverseCard();
            ChangeActivePlayer();
            reverseCard();
        }
}

void Wild(){
    string coloranswer;
    cout << "What would you like to change the color to? : ";
    cin >> coloranswer;
    
    while (coloranswer != "Green" && coloranswer != "Red" && coloranswer != "Blue" && coloranswer != "Yellow"){
       cout << endl << "That is not a valid color. Try again : "; 
       cin >> coloranswer;
    }
    
    colorSetting = coloranswer;
}

void Plus4(){
    Wild();
    //part two of function
    
        ChangeActivePlayer();// changes activePlayer to player who draws 4 cards
        string answer;
        
        cout << "It is "<< activePlayer << "'s turn. Do you have a draw card? (y/n): ";
        
        cin >> answer;
        
        if(answer == "n"){
         DrawCard();//Draw 1
         DrawCard();//Draw 2  
         DrawCard();//Draw 3
         DrawCard();//Draw 4
        }
        else{
            numberDraws += 4;
            reverseCard();
            ChangeActivePlayer();
            reverseCard();
        }
}

int PlayCardFromHand(){
    /* This one is going to be pretty complex. It needs to:
        - ask the user for input, and call ShowUserHand if asked
        - check if valid play (both in hand and on deck)
        - allow users to call UNO
        - do the action for each specific card(which could be its own function call)
            - number card
                // adds card to discardPile, removes from userHand
            - skip
                // calls ChangeActivePlayer
            - wild
                // allows user to input color which changes the color of the card until the next play
            - draw 2
                // adds two cards from the deck (run DrawCard twice) to the next player unless they have another addition card
            - reverse
                // reverses userNameList and all of the hands
            - wild draw 4
                // user input color, add four to next player unless^
    */
    
    string userPlay;
    vector<string> userHand;
    bool cardInHand = false;
    bool cardValidPlay = false;
    
    ShowUserHand();
    
    string numberDisplay;
    
    if(numberSetting < 10){
        numberDisplay = to_string(numberSetting); //research
    }
    else if(numberSetting == 10){
        numberDisplay = "Reverse";
    }
    else if(numberSetting == 11){
        numberDisplay = "Skip";
    }
    else if(numberSetting == 12){
        numberDisplay = "Plus2";
    }
    else if(numberSetting == 13){
        numberDisplay = "Wild";
    }
    else if(numberSetting == 14){
        numberDisplay = "WildPlus4";
    }
    
    cout << endl << colorSetting << endl << numberDisplay << endl; //testing
    
    switch(count%i){
        case 0:
            userHand = user1Hand;
            break;
        case 1:
            userHand = user2Hand;
            break;
        case 2:
            userHand = user3Hand;
            break;
        case 3:
            userHand = user4Hand;
            break;
    }
    
    cout << endl << "Type the card you would like to play: ";
    cin >> userPlay;
    
   
   for(int x = 0; x < userHand.size(); ++x){
        if(userHand.at(x) == userPlay){
            cardInHand = true;
            cout << "Card is in hand." << endl;
        }
    }
    
    if(cardInHand == false){
        cout << "Card is not in hand." << endl;
        return 0;
    }
    
   for(int x=0; x < userHand.size(); ++x){
        if((userHand.at(x) == userPlay) && ((CardColor(userPlay) == colorSetting) || (CardNumber(userPlay) == numberSetting)||(CardNumber(userPlay) == 14)||(CardNumber(userPlay) == 13))){
            topCard = userPlay;
            discardPile.push_back(userPlay);
            userHand.erase(userHand.begin() + x);
            cout << "You have played " << userPlay << "." << endl;
            cardValidPlay = true;
        }
    }
    
    if(cardValidPlay == false){
        cout << "The card is not a valid play." << endl;
        return 0;
    }
    
    cout << endl << endl;
    
    colorSetting = CardColor(userPlay);
    numberSetting = CardNumber(userPlay);
    
    printf("\033[0;36m");
    
    cout << "The top card is now ";
    PrintColor(topCard);
    cout << topCard << endl;
    
    printf("\033[0m");
    
    switch(count%i){
        case 0:
            user1Hand = userHand;
            break;
        case 1:
            user2Hand = userHand;
            break;
        case 2:
            user3Hand = userHand;
            break;
        case 3:
            user4Hand = userHand;
            break;
    }
    
    if(numberSetting == 10){
        reverseCard();
    }
    else if (numberSetting == 12){
        Plus2();
    }
    else if (numberSetting == 13){
        Wild();
    }
    else if (numberSetting == 14){
        Plus4();
    }
    
    if (numberSetting == 11){
        Skip();
    }
    
    if((userHand.size() == 1) && (isUNO == false)){
        char userInput;
        cout << "You forgot to call UNO!" << endl << "Did someone in the room say UNO? (y/n): ";
        cin >> userInput;
        
        if(userInput == 'y'){
            DrawCard();
            DrawCard();
            DrawCard();
            DrawCard();
        }
        else if(userInput == 'n'){
            isUNO = true;
        }
        
        
    }
    
    if(userHand.size() == 0){
        cout << endl << "You have played your last card. You won this round. Congrats!" << endl;
        isUnoOut = true;
        winner = activePlayer;
    }
    
    return 1;
    
    //isUNO = true; //THIS IS FOR TESTING ONLY REMOVE
    // clear screen here
}

void SumPoints(){
    // adds the points from the other player's hands
    string x;
    cout << "Would you like to play using scoring (y/n)" << endl;
    cin >> x;
    if(x == "n"){
        cout << "Ok" << endl;
    }
    else{
    ShowUserHand();
    cout << "Points Scored" << endl;
    cout << "All number cards (0-9) - Face Value" << endl;
    cout << "Draw 2, Reverse, Skip - 20 Points" << endl;
    cout << "Wild, Wild Draw 4 - 50 Points" << endl;
    cout << "Use paper to track the score" << endl;
    }
}

void CheckIfUNO(){
    vector<string> userHand;
    switch(count%i){
        case 0:
            userHand = user1Hand;
            break;
        case 1:
            userHand = user2Hand;
            break;
        case 2:
            userHand = user3Hand;
            break;
        case 3:
            userHand = user4Hand;
            break;
    }
    if(userHand.size() == 2){
        cout << "You called UNO!" << endl;
        isUNO = true;
    }
}

int main(){

    srand(time(0)); 
    string playAgain = "y";

while(playAgain == "y"){
    GetUserNames();
    ShuffleDeck();
    DealCards();
    
    while((isUNO == false) || (isUnoOut == false)){
        //users can draw a card or play a card (and then call UNO)
        
        
        cout << "It is " << activePlayer << "'s turn." << endl;
        cout << "What would you like to do? (view / draw / play / UNO): ";
        cin >> userMove;
        if(userMove == "view"){
            ShowUserHand();
            //isUNO = true; //THIS IS FOR TESTING  the while loop REMOVE
        }
        else if(userMove == "draw"){
            DrawCard();
        }
        else if(userMove == "play"){
            if (PlayCardFromHand() != 0){
            ChangeActivePlayer();
                
            }
        }
        else if(userMove == "UNO"){
            CheckIfUNO();
        }
        else{
            cout << "Invalid move, please try again." << endl;
        }
        
        
    }
    
    SumPoints();
    
    cout << "Would you like to play again? (y/n): ";
    cin >> playAgain;
    
}
    cout << "The final winner is " << winner << "!" << endl;
    
     

    return 0;
}




