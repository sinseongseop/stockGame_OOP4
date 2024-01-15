#ifndef _stock_
#define _stock_

#include <iostream>
#include <string>
#include <vector>
#include "informationManager.h"
#include "information.h"

using namespace std;

class stock {
private: // 필드
	string stockName; // 주식명
	string stockThema; // 테마
	long int stockPrice=0; // 현재 주가
	int fluctuationRate=0; // 이전 라운드에 대한 최근 등락률
	informationManager infoManager; // 정보 매니저
	
public: // 생성자
	stock() {}; // 기본 생성자
	stock(string stockName, string stockThema, float stockPrice);
	stock(string stockName, string stockThema, float stockPrice, string txtFileName);

public: // 메소드
	void calculateOwninfluence(); // 주가변동 반영
	void selectNewInfo(); //infoManager의 새로운 정보 하나 뽑기
	
	void printstock(); //주식 정보 출력(디버깅용)

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
