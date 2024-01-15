#ifndef _stockManager_
#define _stockManager_

#include <iostream>
#include <string>
#include <vector>
#include "stock.h"
#include "informationManager.h"

using namespace std;

class stockManager {
private:
	vector<stock> stockDB; // 모든 주식의 vector
	vector<informationManager> themaManger; //테마 매니저 vector


public: // 생성자
	stockManager() { };
	stockManager(string fileName1, string fileName2, string fileName3);

public: // 메소드
	void printStockPrice(); // 각 주식의 현 주가들을 보여주는 함수
	void updateStockPrice(); // 모든 주가 업데이트
	void calulateThemainfluence(); //테마 정보로 인한 주가 변동 계산 후 반영
	void cacluateRiverinfluence(int num);// external 영향으로 인한 주가 변동 반영
	void updateNewInfo(); // 모든 정보를 업데이트 시킨다.
	
	void printAllStock(); // 모든 주식에 대한 정보 출력(디버깅용)
	void printThemaInfo(); // 테마 정보를 보여준다. (디버깅 확인용)


	// setter
	void addStock(string stockName, string stockThema, float stockPrice, string txtFileName);// 주식 매니저에 추가
	void addthemaManger(string themaName, string fileName); // 테마 메니저를 추가
	
	//getter

	stock& getStock(int num); // 원하는 주식을 하나 반환 ( 참조 반환 임을 주의)
	int getStocksNumber(); //주식 개수 반환
	informationManager& getThemaManager(int i); //i번째 thema manager 반환

};

#endif