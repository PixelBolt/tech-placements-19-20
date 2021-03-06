
#include "stdafx.h"
#include <vector>
#include <iostream>
#include <map>
#include <fstream>
#include <sstream>

// Data type for passing several types back from function.
typedef struct {
	float Total = 0;
	bool Delivery_Charged = true;
}Result;

//Data type for collecting relevent info to add to vector, rather than just have a vetor of vectors or arrays.
typedef struct {
	std::string ID;
	int Amount;
}Order;

//Data type for passing around all info of the items.
typedef struct{
	std::string ID;
	float Price;
	int Discount_Quantitiy;
	bool Save_Free;
	float Discount;

}Item;

//Main class for basket to instantiate the shopping time.
class UniDays {
public:
	// Loop around the basket given - if it already exists then ust incriment the amount, if not add it.
	//Basket is a publice variable, so doesn't return anything.
	std::vector <Order> Basket;
	void AddtoBasket(std::string Choice)
	{
		bool Exist = false;
		for (size_t Items = 0; Items < Basket.size(); Items++)
		{
			if (Basket[Items].ID == Choice)
			{
				Basket[Items].Amount += 1;
				Exist = true;
			}
		}
		if (Exist == false)
		{
			Basket.push_back(Order{ Choice,1 });
		}

	};

	Result CalculateTotalPrice(std::map<std::string, Item*>ID)
	{
		//Loops around the basket vector and adds up the prices multipled by the amount.
		//Checks if it has enough items to qulaify for a discount and what discount that is.
		//Save discount just repaces the total with the dicount price.
		//Free dicount just removes the cost of however many there are free from the price.
		//Then changes the bool of if the delivery applies.
		Result Return;
		for (size_t Items = 0; Items < Basket.size(); Items++)
		{
			Return.Total += (ID[Basket[Items].ID]->Price*Basket[Items].Amount);
			while ((ID[Basket[Items].ID]->Discount_Quantitiy != 0) && (Basket[Items].Amount >= ID[Basket[Items].ID]->Discount_Quantitiy))
			{
				if (ID[Basket[Items].ID]->Save_Free == true)
				{
					Return.Total -= (ID[Basket[Items].ID]->Price*Basket[Items].Amount);
					Return.Total += ID[Basket[Items].ID]->Discount;
				}
				else
				{
					Return.Total -= ID[Basket[Items].ID]->Price* ID[Basket[Items].ID]->Discount;
				}
				Basket[Items].Amount -= ID[Basket[Items].ID]->Discount_Quantitiy;
			}
		}
		if (Return.Total >= 50)
		{
			Return.Delivery_Charged = false;
		}
		return(Return);
	};
};
int main()
{
	int Delivery_Charge = 7;
	float Overall_Total;
	//Maps the item ID to it's values
	std::map<std::string, Item*> ID;
	ID["A"] = new Item{ "A",8.00,0,true,0 };
	ID["B"] = new Item{ "B",12.00,2,true,20.00 };
	ID["C"] = new Item{ "C",4.00,3,true,10.00 };
	ID["D"] = new Item{ "D",7.00,2,false,1 };
	ID["E"] = new Item{ "E",5.00,3,false,1 };
	//instantiating the class and running the functions, as well as printing results.
	UniDays Example;
	Example.AddtoBasket("A");
	Example.AddtoBasket("B");
	Example.AddtoBasket("B");
	Example.AddtoBasket("C");
	Example.AddtoBasket("C");
	Example.AddtoBasket("C");
	Example.AddtoBasket("D");
	Example.AddtoBasket("D");
	Example.AddtoBasket("E");
	Example.AddtoBasket("E");
	Result Checkout = Example.CalculateTotalPrice(ID);
	std::cout << Checkout.Total << std::endl;
	std::cout << Checkout.Delivery_Charged*Delivery_Charge<< std::endl;
	Overall_Total = Checkout.Total + Checkout.Delivery_Charged*Delivery_Charge;
	std::cout << "----------" << std::endl;
	std::cout << Overall_Total << std::endl;
	return 0;
}

