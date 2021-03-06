
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

	Result CalculateTotalPrice(std::vector<Item> Stock)
	{
		//Loops around the basket vector and adds up the prices multipled by the amount.
		//Checks if it has enough items to qulaify for a discount and what discount that is.
		//Save discount just repaces the total with the dicount price.
		//Free dicount just removes the cost of however many there are free from the price.
		//Then changes the bool of if the delivery applies.
		Result Return;
		Item Info;
		for (size_t Items = 0; Items < Basket.size(); Items++)
		{
			for (int Check = 0; Check < Stock.size(); Check++)
			{
				if (Stock[Check].ID == Basket[Items].ID)
				{
					Info = Stock[Check];
					break;
				}
			}
			Return.Total += (Info.Price * Basket[Items].Amount);
			while ((Info.Discount_Quantitiy != 0) && (Basket[Items].Amount >= Info.Discount_Quantitiy))
			{
				if (Info.Save_Free == true)
				{
					Return.Total -= (Info.Price * Basket[Items].Amount);
					Return.Total += Info.Discount;
				}
				else
				{
					Return.Total -= Info.Price * Info.Discount;
				}
				Basket[Items].Amount -= Info.Discount_Quantitiy;
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
	//loops around the whole file line by line and compares each letter, seperates the characters based on commas.
	//ASSUMES FILE IS CORECTLY FORMMATED.
	//Adds each item to a vector to be used to check info on items.
	std::map<std::string, Item*> ID;
	std::ifstream File;
	File.open("Details.txt");
	if (!File)
		{
		std::cout << "There is no file containing the items and prices. Please corectly place it." << std::endl;
		return 0;
		}
	std::vector <Item> Stock;
	int Seperate ;
	Item Temp;
	std::string String;
	for (std::string line; std::getline(File, line); )
	{
	Seperate = 0;
	String = "";
		for (int Data = 0; Data < line.length()-1; Data++)
		{
			if (Seperate == 0)
			{
				if (line[Data]!=',')
				{
					String += (line[Data]);
				}
				else
				{
					Temp.ID = String;
					Seperate += 1;
					String = "";
					Data++;
				}
			}
			if (Seperate == 1)
			{
				if (line[Data] != ',')
				{
					String += (line[Data]);
				}
				else
				{
					Temp.Price = stof(String);
					Seperate += 1;
					String = "";
					Data++;
				}
			}
			if (Seperate == 2)
			{
				if (line[Data] != ',')
				{
					String += (line[Data]);
				}
				else
				{
					Temp.Discount_Quantitiy = stoi(String);
					Seperate += 1;
					String = "";
					Data++;
				}
			}
			if (Seperate == 3)
			{
				if (line[Data] != ',')
				{
					String += (line[Data]);
				}
				else
				{
					if (String == "save")
					{
						Temp.Save_Free = true;
					}
					if (String == "free")
					{
						Temp.Save_Free = false;
					}
					Seperate += 1;
					String = "";
					Data++;
				}
			}
			if (Seperate == 4)
			{
				if (line[Data] != ',')
				{
					String += (line[Data]);
				}
			}
		}
		Temp.Discount = stof(String);
		Stock.push_back(Temp);
	};
	File.close();
	float Delivery_Charge = 7;
	float Overall_Total;
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
	Result Checkout = Example.CalculateTotalPrice(Stock);
	std::cout << Checkout.Total << std::endl;
	std::cout << Checkout.Delivery_Charged*Delivery_Charge<< std::endl;
	Overall_Total = Checkout.Total + Checkout.Delivery_Charged*Delivery_Charge;
	std::cout << "----------" << std::endl;
	std::cout << Overall_Total << std::endl;
	return 0;
}

