#include <iostream>
#include "portfolio.h"

using namespace std;

//string Portfolio::getItem() {
//
//}
//
//int Portfolio::getNumberOfItem() {
//
//}
//
//void Portfolio::setItem(string item) {
//
//}
//void Portfolio::setNumberOfItem(string item) {
//
//}



bool Portfolio::purchase(string item, int NumberOfItem)
{
	// 매입 성공
	for (int i = 0; i < v.size(); i++) {
		if (v[i].item == item) {
			v[i].PurchasingPrice = ((v[i].PurchasingPrice * v[i].NumberOfItem) 
				+ (stocks->getStock(i).getStockPrice() * NumberOfItem)) 
				/ (v[i].NumberOfItem + NumberOfItem);								//구매가 갱신
			v[i].NumberOfItem += NumberOfItem;										//보유개수 갱신

			v[i].amount = v[i].CurrentPrice * v[i].NumberOfItem;					//평가금액 갱신
			v[i].profit = v[i].amount - v[i].PurchasingPrice * v[i].NumberOfItem;	//평가손익 갱신 

			
			return true;
		}
	}
	
	//매입 실패
	return false;

}

int Portfolio::sell(string item, int NumberOfItem) {
	int plusAsset = -1;

	for (int i = 0; i < v.size(); i++) {
		if (v[i].item == item) {
			if (v[i].NumberOfItem < NumberOfItem)
				return -1;

			v[i].profit += NumberOfItem * (v[i].CurrentPrice - v[i].PurchasingPrice);
			plusAsset = NumberOfItem * v[i].CurrentPrice;
			v[i].NumberOfItem -= NumberOfItem;

			v[i].amount = v[i].CurrentPrice * v[i].NumberOfItem;							//평가금액 갱신
			v[i].profit = v[i].amount - v[i].PurchasingPrice * v[i].NumberOfItem;			//평가손익 갱신 


			if (v[i].NumberOfItem == 0)
				v[i].PurchasingPrice = 0;

			break;
		}
	}
	return plusAsset;
}

void Portfolio::initialize(stockManager* stocks) {
	this->stocks = stocks;

	for (int i = 0; i < stocks->getStocksNumber(); i++) {
		InvestStruct buf = { stocks->getStock(i).getStockName(), 0, 0, 0, 0, 0, 0, false};
		v.push_back(buf);
	}
	
	update();
}

void Portfolio::update() {
	for (int i = 0; i < v.size(); i++) {
		v[i].CurrentPrice = stocks->getStock(i).getStockPrice();				// 현재가 갱신
		v[i].amount = v[i].CurrentPrice * v[i].NumberOfItem;					//평가금액 갱신
		v[i].profit = v[i].amount - v[i].PurchasingPrice * v[i].NumberOfItem;	//평가손익 갱신 
		v[i].EarningsRate = (int)((((float)v[i].CurrentPrice - (float)v[i].PurchasingPrice) / (float)v[i].CurrentPrice) * 100); //수익률 갱신
		if (v[i].NumberOfItem == 0)
			v[i].EarningsRate = 0;
		
		//정보 언락 여부 갱신
		checkInfoUnlook(i);
	}
}

void Portfolio::checkInfoUnlook(int i) {
	if (v[i].NumberOfItem >= UNLOOK_CONDITION) 
		v[i].infoUnlock = true;
	else
		v[i].infoUnlock = false;
}

void Portfolio::setInfoUnlook(int i, bool val) {
	v[i].infoUnlock = val;
}

bool Portfolio::getInfoUnlook(int i) {
	return v[i].infoUnlock;
}

InvestStruct Portfolio::get_ithInvestStruct(int i) {
	return v[i];
}