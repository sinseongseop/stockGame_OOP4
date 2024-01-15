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
	cout << "�ֽ� �̸�: " << stockName<<"\n";
	cout << "�׸�: " << stockThema<<"\n";
	cout << fixed << "����: " << stockPrice<<"\n";
	cout << "������: " << fluctuationRate<<"%\n";
	//cout << "����: " << this->infoManager.getThisTurnInformation().getInfo() << "\n";
}

void stock::selectNewInfo() {
	infoManager.selectThisTurnInformation();
} //infoManager�� ���ο� ���� �ϳ� �̱�


void stock::calculateOwninfluence() { // �ڱ� �ڽ� �ֽ� ������ ���� �ְ����� ���
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

information& stock::getInfo() { // stockManager�� stock�� ThisTurn������ ��ȯ
	return infoManager.getThisTurnInformation();

}