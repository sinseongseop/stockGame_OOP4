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
		cout << stockDB[i].getStockName() << " �� ����: " << stockDB[i].getStockPrice()<<'\n';
	}

}// �� �ֽ��� �� �ְ����� �����ִ� �Լ�

void stockManager::updateStockPrice() { // ��� �ֽ� ���� ������Ʈ & ������ ������Ʈ
	vector<long int> beforePrice;
	for (int i = 0; i < stockDB.size(); i++) {
		beforePrice.push_back(stockDB[i].getStockPrice());
	}

	for (int i = 0; i < stockDB.size(); i++) {
		stockDB[i].calculateOwninfluence(); //Own ������ ���� ���� ������Ʈ
		cacluateRiverinfluence(i); //External ������ ���� ���� ���� ������Ʈ
	}
	calulateThemainfluence();

	for (int i = 0; i < stockDB.size(); i++) {
		//cout << ( (float)(stockDB[i].getStockPrice() - beforePrice[i]) / (float)beforePrice[i])<<'\n'; //����� Ȯ�ο�
		stockDB[i].setFluctuationRate(((int)stockDB[i].getStockPrice()-beforePrice[i])/ (float)beforePrice[i] * 100);
	}


} // ��� �ְ� ������Ʈ

void stockManager::cacluateRiverinfluence(int stockNum) {
	information& thisTurnInfo = stockDB[stockNum].getInfo();
	for (int j = 0; j < stockDB.size(); j++) { // External ������ ���� ���� ���� ������Ʈ
		if (stockNum != j) {
			if (stockDB[j].getStockThema() == thisTurnInfo.getThema()) {
				stockDB[j].setStockPrice((long int)stockDB[j].getStockPrice() * thisTurnInfo.getExternalPriceVariance());
			}
		}
	}
}

void stockManager::calulateThemainfluence() { // �׸� ������ ���� �ְ� ���� ��� �� �ݿ�
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

void stockManager::updateNewInfo() { // ��� ������ ���ο� ������ ������Ʈ �Ѵ�.
	for (int i = 0; i < themaManger.size(); i++) {
		themaManger[i].selectThisTurnInformation();
	}
	for (int i = 0; i < stockDB.size(); i++) {
		stockDB[i].selectNewInfo();
	}
}

void stockManager::printAllStock() {
	cout << "�ֽ� ���� \n";
	for (int i = 0; i < stockDB.size(); i++) {
		stockDB[i].printstock();
	}

} // ��� �ֽĿ� ���� ���� ���(������)

void stockManager::printThemaInfo() { // �׸� ���� Ȯ�� (������)
	cout << "�׸� ���� \n";
	for (int i = 0; i < themaManger.size(); i++) {
		themaManger[i].printThisTurnInfo();
	}
}

void stockManager::addStock(string stockName, string stockThema, float stockPrice, string txtFileName) { // �ֽ� DB�� �ֽ� �߰�
	stock newStock = stock(stockName,stockThema,stockPrice,txtFileName);
	stockDB.push_back(newStock);
}

void stockManager::addthemaManger(string themaName, string fileName) { //themaMager �߰�
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