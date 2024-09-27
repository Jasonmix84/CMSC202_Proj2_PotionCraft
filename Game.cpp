#include "Game.h"

// creates shop object
  Shop myShop; 
// Do this File Second

  // Name - Game() Default Constructor
  // Desc - Does nothing explicitly
  // Preconditions - None
  // Postconditions - None
  Game::Game(){} //Default Constructor
  // Name - LoadIngredients
  // Desc - Loads each ingredient into m_ingredients from file.
  //        Ingredient names can have spaces (check proj doc for delimiter help)
  // Preconditions - Requires file with valid ingredient data
  // Postconditions - m_ingredient is populated with ingredient structs
  void Game::LoadIngredients(){
    ifstream inputStream;
    inputStream.open(PROJ2_DATA);
    string itemName;
    string type;
    string ing1;
    string ing2;
    string line;
    int startingNum = 0;
    
    for (int i = 0; i < PROJ2_SIZE; i++){//go through each line of the file
      getline(inputStream, itemName, ',');
      
      getline(inputStream, type, ',');
      
      getline(inputStream, ing1, ',');
      
      getline(inputStream, ing2, '\n');
      
      m_ingredients[i] = Ingredient(itemName, type, ing1, ing2, startingNum);//create structs for each and populates array 

    }
    
    inputStream.close();
    //populate m_myingredients
    for (int i = 0; i < PROJ2_SIZE; i++){
      myShop.AddIngredient(m_ingredients[i]);
    }

  }
  // Name - StartGame()
  // Desc - Calls GameTitle then loads the file by calling LoadIngredients
  //        Manages the game itself continually calling the main menu until the main menu
  //        returns 5 (quit)
  // Preconditions - Player is placed in game
  // Postconditions - Continually checks to see if player has entered 5
  void Game::StartGame(){
    GameTitle();
    LoadIngredients();
    while(MainMenu() != 5){
      MainMenu();
    }
    cout << "Thanks for playing UMBC Potion Craft" << endl;
  }
  // Name: DisplayMyIngredients()
  // Desc - Displays the Shop's ingredients (Uses GetIngredient)
  // Preconditions - Player's Shop has ingredients
  // Postconditions - Displays a numbered list of ingredients
  void Game::DisplayIngredients(){
    for (int i = 0; i < PROJ2_SIZE; i++){
      cout << i+1 << ". " << m_ingredients[i].m_name << ' ' <<  myShop.GetIngredient(i).m_quantity << endl; //prints ingredient and the quantity
    }
  }
  // Name: MainMenu()
  // Desc - Displays and manages menu. Also checks win condition (Shop reaches S rank).
  // Preconditions - Player has a Shop
  // Postconditions - Returns number including exit
  int Game::MainMenu(){
    int choice = 0;
    string shopName;
    cout << "What is the name of your Shop?" << endl;
    cin >> shopName;
    //set shop name
    myShop.SetName(shopName);
    while (choice != 5 ){//end condition
      if (myShop.GetRank() == 'S'){
        cout << "You have successfully filled out your inventory :)" << endl;//end condition
        return 5;
      }
      cout << "What would you like to do in " << myShop.GetName() << "'s shop? " << endl;
      cout << "1. Display your Shop's Ingredients" << endl;
      cout << "2. Search for Natural Ingredients" << endl;
      cout << "3. Attempt to Merge Ingredients" << endl;
      cout << "4. See Score" << endl;
      cout << "5. Quit" << endl;
      cin >> choice; //take in user input

      if (choice == 1){
        DisplayIngredients();//prints the ingredients and their quantities
      }
      else if(choice == 2){
        SearchIngredients();//finding natural ingredients
      }
      else if(choice == 3){
        CombineIngredients(); //combine ingredients also calls other functions within it
      }
      else if(choice == 4){
        myShop.ShopScore();//gives you your rank and other info
      }
      else if (choice == 5){
        return 5;
      }
      else{
        cout << endl;
      }
    }
    return 5;
  }
  // Name: SearchIngredients()
  // Desc - Attempts to search for natural ingredients (must be type "natural")
  // Preconditions - Natural ingredients loaded
  // Postconditions - Increases quantity in Shop's possession of ingredients
  void Game::SearchIngredients(){
    int naturalNum = 0; //num of natural ingredeients
    int randNum = 0;
    

    for (int i = 0; i < PROJ2_SIZE; i++){
      if (m_ingredients[i].m_type == "natural"){
        naturalNum++;
      }//should in the end give the number of natural ingredients
    }
    

    randNum = (rand() % ((naturalNum-1) + (1 - 0)));
    Ingredient natIng = m_ingredients[randNum]; // should set the variable to the name of a random natural ingredient
    cout << natIng.m_name << " Found!" << endl;
    myShop.IncrementQuantity(m_ingredients[randNum]);

  }
  // Name: CombineIngredients()
  // Desc - Attempts to combine known ingredients. If combined, quantity of ingredient decreased
  // Preconditions - Shop is populated with ingredients
  // Postconditions - Increments quantity of item "made", decreases quantity of source items
  void Game::CombineIngredients(){
    int ing1 = 0;
    int ing2 = 0;
    string combIng1; //the name of the ingredient with index of ing1
    string combIng2;
    RequestIngredient(ing1);//sends in a 0 it will be changed tho to the ingredients index which is +1 more than the actual index
    RequestIngredient(ing2);
    if (myShop.CheckQuantity(myShop.GetIngredient(ing1-1), myShop.GetIngredient(ing2-1))){
      combIng1 = m_ingredients[ing1-1].m_name;
      combIng2 = m_ingredients[ing2-1].m_name;// I now have the name of the ingredients they requested

      int index = SearchRecipes(combIng1, combIng2); //gives me the index of the item that you can make with the two ingredients
      if (index == -1){
        return;
      }
      cout << combIng1 << " combined with " << combIng2 << " to make " << myShop.GetIngredient(index).m_name << endl; 
      
      myShop.IncrementQuantity(m_ingredients[index]); // increase number of this specific item 
      myShop.DecrementQuantity(m_ingredients[ing1-1]);
      myShop.DecrementQuantity(m_ingredients[ing2-1]);
    }
    else{
      cout << "Not enough ingredients to merge" << endl;
      return;
    }
  }
  // Name: RequestIngredient()
  // Desc - Requests ingredient to use to merge
  // Preconditions - Shop has ingredients to try and merge
  // Postconditions - Returns integer of item selected by user
  void Game::RequestIngredient(int &choice){
    //validating the choice they make and i just ask there choice and thats it.
      int checkChoice = 0;
      int count = 0;
      while (count < 1){
      cout << "Which ingredients would you like to merge?" << endl;
      cout << "To list known ingredients enter -1" << endl;
      cin >> checkChoice;
      if (checkChoice > 0 && checkChoice < PROJ2_SIZE + 1 ){
        choice = checkChoice;//this only makes sure its within the bounds but does not make sure you have enough of each ingredient
        count++;
      }
      else if (checkChoice == -1){
        DisplayIngredients();
      }
      else{
        cout << "Invalid Choice! Please pick a valid integer" << endl;
      }
      }
  } 
      
  // Name: SearchRecipes()
  // Desc - Searches recipes for two strings (name of item)
  // Preconditions - m_ingredients is populated
  // Postconditions - Returns int index of matching recipe
  int Game::SearchRecipes(string itemName1, string itemName2){
    for (int i = 0; i < PROJ2_SIZE; i++){
      if (m_ingredients[i].m_ingredient1 == itemName1 && m_ingredients[i].m_ingredient2 == itemName2){
        return i;
      }
      if (m_ingredients[i].m_ingredient1 == itemName2 && m_ingredients[i].m_ingredient2 == itemName1){//second case if given the ingredients in reverse
        return i;
      }
    }
    cout << "No items could be made from this combination" << endl;
    return -1;
  }

