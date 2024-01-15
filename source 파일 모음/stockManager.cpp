#include <iostream>
#include <string>
#include <vector>
#include "stock.h"
#include "informationManager.h"
#include "stockManager.h"

using namespace std;


stockManager::stockManager(string fileName1, string fileName2, string fileName3) {
	addthemaManger("thema", fileName1);
	addthemaManger("thema", fileName2);
	addthemaManger("thema", fileName3);
}


void stockManager::printStockPrice() {
	for (int i = 0; i < stockDB.size(); i++) {
		cout << stockDB[i].getStockName() << " 의 가격: " << stockDB[i].getStockPrice()<<'\n';
	}

}// 각 주식의 현 주가들을 보여주는 함수

void stockManager::updateStockPrice() { // 모든 주식 가격 업데이트 & 변동률 업데이트
	vector<long int> beforePrice;
	for (int i = 0; i < stockDB.size(); i++) {
		beforePrice.push_back(stockDB[i].getStockPrice());
	}

	for (int i = 0; i < stockDB.size(); i++) {
		stockDB[i].calculateOwninfluence(); //Own 정보로 인한 영향 업데이트
		cacluateRiverinfluence(i); //External 정보로 인한 가격 영향 업데이트
	}
	calulateThemainfluence();

	for (int i = 0; i < stockDB.size(); i++) {
		//cout << ( (float)(stockDB[i].getStockPrice() - beforePrice[i]) / (float)beforePrice[i])<<'\n'; //디버깅 확인용
		stockDB[i].setFluctuationRate(((int)stockDB[i].getStockPrice()-beforePrice[i])/ (float)beforePrice[i] * 100);
	}


} // 모든 주가 업데이트

void stockManager::cacluateRiverinfluence(int stockNum) {
	information& thisTurnInfo = stockDB[stockNum].getInfo();
	for (int j = 0; j < stockDB.size(); j++) { // External 정보로 인한 가격 영향 업데이트
		if (stockNum != j) {
			if (stockDB[j].getStockThema() == thisTurnInfo.getThema()) {
				stockDB[j].setStockPrice((long int)stockDB[j].getStockPrice() * thisTurnInfo.getExternalPriceVariance());
			}
		}
	}
}

void stockManager::calulateThemainfluence() { // 테마 정보로 인한 주가 변동 계산 후 반영
	for (int i = 0; i < themaManger.size(); i++) {
		information& themaInfo = themaManger[i].getThisTurnInformation();
		string thisThema = themaInfo.getThema();
		float changeRate = themaInfo.getOwnPriceVariance();
		for (int j = 0; j< stockDB.size(); j++) {
			if (thisThema == stockDB[j].getStockThema()) {
				stockDB[j].setStockPrice((long int)stockDB[j].getStockPrice() * changeRate);
			}
		}
	}
}

void stockManager::updateNewInfo() { // 모든 정보를 새로운 정보로 업데이트 한다.
	for (int i = 0; i < themaManger.size(); i++) {
		themaManger[i].selectThisTurnInformation();
	}
	for (int i = 0; i < stockDB.size(); i++) {
		stockDB[i].selectNewInfo();
	}
}

void stockManager::printAllStock() {
	cout << "주식 정보 \n";
	for (int i = 0; i < stockDB.size(); i++) {
		stockDB[i].printstock();
	}

} // 모든 주식에 대한 정보 출력(디버깅용)

void stockManager::printThemaInfo() { // 테마 정보 확인 (디버깅용)
	cout << "테마 정보 \n";
	for (int i = 0; i < themaManger.size(); i++) {
		themaManger[i].printThisTurnInfo();
	}
}

void stockManager::addStock(string stockName, string stockThema, float stockPrice, string txtFileName) { // 주식 DB에 주식 추가
	stock newStock = stock(stockName,stockThema,stockPrice,txtFileName);
	stockDB.push_back(newStock);
}

void stockManager::addthemaManger(string themaName, string fileName) { //themaMager 추가
	themaManger.push_back(informationManager(themaName, fileName));
}

stock& stockManager::getStock(int num) {
	return stockDB[num];
}

int stockManager::getStocksNumber() {
	return stockDB.size();
}

informationManager& stockManager::getThemaManager(int i) {
	return this->themaManger[i];
}