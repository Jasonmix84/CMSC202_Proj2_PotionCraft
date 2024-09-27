#include "Shop.h"

// This is the first file i need to make
//only shopScore uses cout nothing else uses cout

// Name: Shop() - Default Constructor
  // Desc: Used to build a new Player Shop
  // Preconditions - Requires default values (Name = Test, numIngredients = 0, Rank = F
  // Postconditions - Creates a new Player Shop
Shop::Shop(){
    m_shopName = "Test";
    m_numIngredients = 0;
    m_shopRank = 'F';
}

// Name: Shop(name) - Overloaded constructor
  // Desc - Used to build a new Player Shop (m_numIngredients = 0, m_shopRank = F)
  // Preconditions - Requires name
  // Postconditions - Creates a new Player Shop
Shop::Shop(string name){
    m_numIngredients = 0;
    m_shopRank = 'F';
    m_shopName = name;
}

// Name: GetName()
  // Desc - Getter for the Player Shop's name
  // Preconditions - Player Shop exists
  // Postconditions - Returns the name of the Player Shop
string Shop::GetName(){
    return m_shopName;
}

// Name: SetName(string)
  // Desc - Allows the user to change the name of the Player Shop
  // Preconditions - Player Shop exists
  // Postconditions - Sets name of Player Shop
void Shop::SetName(string name){
  m_shopName = name;
}

// Name: CheckIngredient(Ingredient)
  // Desc - Checks to see if the Shop has a ingredient
  // Preconditions - Shop already has ingredients
  // Postconditions - Returns index of ingredient if the Shop has it else -1
int Shop::CheckIngredient(Ingredient name){
  for (int i = 0; i < PROJ2_SIZE; i++){
    if (m_myIngredients[i].m_name == name.m_name){//name is m_ingredients[index]
      return i;
    }
  }
  return -1;
}

// Name: AddIngredient(string)
  // Desc - Inserts a ingredient into the Shop's list of ingredients.
  //        Increments m_numIngredients
  // Preconditions - Shop exists
  // Postconditions - Add a ingredient to the Shop's m_myIngredients with a quantity of 0
void Shop::AddIngredient(Ingredient ing){
  if (CheckIngredient(ing) == -1){
    m_myIngredients[m_numIngredients] = ing; // should add the shops array with the ingredients array
    m_numIngredients++; // increaase total number of items in shop
  }
}

// Name: IncrementQuantity(Ingredient)
  // Desc - Increases the quantity for an ingredient the Shop knows
  // Preconditions - Shop exists
  // Postconditions - Increases quantity of ingredient for the Shop
void Shop::IncrementQuantity(Ingredient obj){
    int loc = CheckIngredient(obj);//loc is an index
    int newLoc = 0;
  
    if (loc >= 0){
      m_myIngredients[loc].m_quantity++;
    }
    else{
      newLoc = CheckIngredient(obj);//newLoc is another index
      m_myIngredients[newLoc].m_quantity++;
    }
}
    
// Name: DecrementQuantity(Ingredient)
  // Desc - Reduces quantity from the Shop's inventory with true, if no quantity false
  // Preconditions - A Shop exists
  // Postconditions - Reduces quantity of ingredient for the Shop
bool Shop::DecrementQuantity(Ingredient obj){
  int loc = CheckIngredient(obj);
  if (m_myIngredients[loc].m_quantity >= 0){//decrements if there is more than one quantity
      m_myIngredients[loc].m_quantity--;
      return true;
    }
  else{//returns false so you cant combine ingredients
    return false;
  }
}

// Name: CheckQuantity(Ingredient)
  // Desc - Checks to see if quantity of two merge ingredients are available
  // Preconditions - Shop exists with ingredients
  // Postconditions - Returns true if both are available (including two of same ingredient)
bool Shop::CheckQuantity(Ingredient ing1, Ingredient ing2){
    int locIng1 = CheckIngredient(ing1);
    int locIng2 = CheckIngredient(ing2);
    if (locIng1 == locIng2){
      if (m_myIngredients[locIng1].m_quantity >= 2){//incase the two ingredients that want to be combined are the same make sure there is at least two
        return true;
      }
      else{
        return false;
      }
    }

    if (m_myIngredients[locIng1].m_quantity > 0 && m_myIngredients[locIng2].m_quantity > 0){//make sure both ingredients are greater than one before combining
      return true;
    }
    else{
      return false;
    }
    
}

// Name: GetIngredient(int)
  // Desc - Checks to see if the Shop has any ingredients
  // Preconditions - The Shop already has ingredients
  // Postconditions - Returns ingredient at specific index
Ingredient Shop::GetIngredient(int i){
  return m_myIngredients[i];
}

// Name: CalcRank()
  // Desc - Divides the total available ingredients, by the IngredientCount()
  // Updates the rank based on percentages
  //      0-29 = F, 30-49 = D, 50-69 = C, 70-89 = B, 90-99 = A, 100 = S
  // Preconditions - Shop exists and has a rank
  // Postconditions - m_shopRank will be updated
void Shop::CalcRank(){
  double rank = 0.0;
  rank = (double(IngredientCount())/double(PROJ2_SIZE)) * 100;//truncates the decimals leaves only the whole number
  if (rank < RANK_D){
    m_shopRank = 'F';
  }
  else if (rank < RANK_C && rank >= RANK_D){
    m_shopRank = 'D';
  }
  else if (rank < RANK_B && rank >= RANK_C){
    m_shopRank = 'C';
  }
  else if (rank < RANK_A && rank >= RANK_B){
    m_shopRank = 'B';
  }
  else if (rank < RANK_S && rank >= RANK_A){
    m_shopRank = 'A';
  }
  else{
    m_shopRank = 'S';
  }
}

// Name: GetRank()
  // Desc - Returns the current shop's rank
  // Preconditions - The shop exists
  // Postconditions - Returns the character indicating the rank of the shop
char Shop::GetRank(){
  CalcRank();
  return m_shopRank;
}

// Name: IngredientCount()
  // Desc - Loops through m_myIngredients to see how many ingredients have a quantity > 0
  // Preconditions - The shop exists, m_myIngredients populated
  // Postconditions - Returns the count of ingredients with a quantity > 0
int Shop::IngredientCount(){
  int userIng = 0;
  for (int i = 0; i < PROJ2_SIZE; i++){
    if (m_myIngredients[i].m_quantity > 0){//used to know how many different ingredients user has
      userIng++;
    } 
  }
  
  return userIng;
}

// Name: ShopScore()
  // Desc - Displays information about the shop: name, ingredients found, total available,
  //        percentage found, and rank
  // Preconditions - The shop exists, m_myIngredients populated
  // Postconditions - Displays name, ingredient count, total ingredients, percentage, and rank
void Shop::ShopScore(){
  double rank = 0.0;
  
  cout << "***The Potion Shop***" << endl;
  cout << "Owned by: " << GetName() << endl;
  cout << "There are " << PROJ2_SIZE << " available products." << endl;
  rank = (double(IngredientCount())/double(PROJ2_SIZE)) * 100;
  cout << "This shop has " << IngredientCount() << " products in stock." << endl;
  cout << "Which is " << rank << '%' << endl;
  cout << "Shop Rank: " << GetRank() << endl; 
}