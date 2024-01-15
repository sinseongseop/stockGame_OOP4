#ifndef _stock_
#define _stock_

#include <iostream>
#include <string>
#include <vector>
#include "informationManager.h"
#include "information.h"

using namespace std;

class stock {
private: // �ʵ�
	string stockName; // �ֽĸ�
	string stockThema; // �׸�
	long int stockPrice=0; // ���� �ְ�
	int fluctuationRate=0; // ���� ���忡 ���� �ֱ� �����
	informationManager infoManager; // ���� �Ŵ���
	
public: // ������
	stock() {}; // �⺻ ������
	stock(string stockName, string stockThema, float stockPrice);
	stock(string stockName, string stockThema, float stockPrice, string txtFileName);

public: // �޼ҵ�
	void calculateOwninfluence(); // �ְ����� �ݿ�
	void selectNewInfo(); //infoManager�� ���ο� ���� �ϳ� �̱�
	
	void printstock(); //�ֽ� ���� ���(������)

	// setter
	void setStockName(string stockName);
	void setStockThema(string stockThema);
	void setStockPrice(float stockPrice);
	void setFluctuationRate(int fluctuationRate);
	void setInfoManager(string stockName, string txtFileName);

	// getter
	string getStockName();
	string getStockThema();
	long int getStockPrice();
	float getFluctuationRate();
	information& getInfo();
};
#endif
