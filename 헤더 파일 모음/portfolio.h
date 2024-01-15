#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include <iostream>
#include <string>
#include <vector>
#include "stockManager.h"

using namespace std;

#define UNLOOK_CONDITION 10

struct InvestStruct {
	string item;		// 주식 종목 명
	int NumberOfItem;	// 주식개수
	int PurchasingPrice; // 매입가
	int CurrentPrice;	// 현재가
	int profit;			//평가손익						= 평가 금액 - 매입가 * 총 개수
	int EarningsRate;	//수익률						= (현재가 - 매입가)/매입가 * 100
	int amount;			// 평가금액						= 현재가 * 보유 주식
	bool infoUnlock;	//해당 주식의 정보 언락 여부	(unlock된 경우 true)
														//정보 unlock 조건 : 주식을 UNLOOK_CONDITION 이상 보유, 혹은 별도로 구매
};

class Portfolio
{

private:
	vector<InvestStruct> v;
	stockManager* stocks; //주식 시장 manager를 가리키는 pointer


public:
	//constructor
	//각 종목에 대한 구조체 setting
	Portfolio() {};

	//주식 매입 함수
	// 평가손익, 수익률, 평가금액 계산
	// 매입에 성공하면 true, 실패하면 false return
	bool purchase(string item, int NumberOfItem); 

	//주식 매도 함수
	// 매도한 금액 return
	// 주식 보유 수보다 많이 매도하려 하면 -1 return
	int sell(string item, int NumberOfItem); 

	//초기 설정 함수
	// game manger로부터 player 생성시 주식시장 manager 객체 pointer를 받아와서 전달, 생성한다.
	//주식 종목, 개수도 manager로부터 받아와서 vector에 저장
	void initialize(stockManager* stocks);

	//update 함수
	//매턴 주식시장 manager pointer를 참조해서 각 item의 매입가 등을 업데이트
	void update();

	//i번째 종목의 infoUnlook 값 설정
	//조건을 확인하여 true, false로 산정한다.
	void checkInfoUnlook(int i);
	
	//i번째 종목의 infoUnlook 값 설정
	void setInfoUnlook(int i, bool val);
	
	//i번째 종목의 infoUnlook 값 반환
	bool getInfoUnlook(int i);

	//i번째 종목의 구조체 반환
	InvestStruct get_ithInvestStruct(int i);
	
};

#endif

