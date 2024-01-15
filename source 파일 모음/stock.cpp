#include <iostream>
#include <string>
#include <random>
#include "information.h"
#include "informationManager.h"
#include "stock.h"

using namespace std;

stock::stock(string stockName, string stockThema, float stockPrice) {
	this->stockName = stockName;
	this->stockThema = stockThema;
	this->stockPrice = stockPrice;
	this->fluctuationRate = 0;

}

stock::stock(string stockName, string stockThema, float stockPrice, string txtFileName) {
	this->stockName = stockName;
	this->stockThema = stockThema;
	this->stockPrice = stockPrice;
	this->fluctuationRate = 0;
	this->infoManager = informationManager(stockName,txtFileName);
}

void stock::printstock() {
	cout << "주식 이름: " << stockName<<"\n";
	cout << "테마: " << stockThema<<"\n";
	cout << fixed << "가격: " << stockPrice<<"\n";
	cout << "변동률: " << fluctuationRate<<"%\n";
	//cout << "정보: " << this->infoManager.getThisTurnInformation().getInfo() << "\n";
}

void stock::selectNewInfo() {
	infoManager.selectThisTurnInformation();
} //infoManager의 새로운 정보 하나 뽑기


void stock::calculateOwninfluence() { // 자기 자신 주식 정보로 인한 주가변동 계산
	information& thisTurnInfo = infoManager.getThisTurnInformation();
	this->stockPrice *= thisTurnInfo.getOwnPriceVariance();
}

// setter
void stock::setStockName(string stockName) {
	this->stockName = stockName;
}

void stock::setStockThema(string stockThema) {
	this->stockThema = stockThema;
}

void stock::setStockPrice(float stockPrice) {
	this->stockPrice = stockPrice;
}

void stock::setFluctuationRate(int fluctuationRate) {
	this->fluctuationRate = fluctuationRate;
}

void stock::setInfoManager(string stockName, string txtFileName) {
	this->infoManager = informationManager(stockName, txtFileName);
}


//getter
string stock::getStockName() {
	return stockName;
}

string stock::getStockThema() {
	return stockThema;
}

long int stock::getStockPrice() {
	return stockPrice;
}

float stock::getFluctuationRate() {
	return fluctuationRate;
}

information& stock::getInfo() { // stockManager로 stock의 ThisTurn정보를 반환
	return infoManager.getThisTurnInformation();

}