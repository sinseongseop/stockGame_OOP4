#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <string>
#include "Loan_Manager.h"
#include "portfolio.h"
#include "stockManager.h";

using namespace std;

class Player
{
private:
	string		name;					//player명
	int			asset;					//현금 자산
	bool		checkLoan = false;		//대출 여부
	Portfolio playerPortfolio; 
	Loan_Manager playerLoan_Manager;

public:
	Player() {};

	//주식 매입 함수
	//매입에 성공하면 true, 실패하면 false return
	bool purchase(string item, int NumberOfItem, int CurrentPrice);

	//주식 매도 함수
	//매도에 성공하면 true, 실패하면 false return
	bool sell(string item, int NumberOfItem);

	//대출 함수
	//대출이 실패했으면 false 반환, 성공했으면 true 반환
	bool loan(int requested_loanAmount);

	//대출 상환 함수
	//상환이 실패했으면 false 반환, 성공했으면 true 반환
	bool repayment(int repaymentAmount);

	//대출상환 관리 객체 업데이트 (강제 징수)
	//매턴 자동 실행
	//라운드 수를 parameter로 받는다
	void Loan_ManagerUpdate(int RoundCounter);

	//포트폴리오 업데이트 실행 함수
	//매턴 실행
	void PortfolioUpdate();

	//포트폴리오 초기화 함수
	//주식시장 manager 객체의 주소를 paramter로 받는다.
	void Portfolioinitialize(stockManager* stocks);

	string getName();
	int getAsset();
	bool getCheckLoan();
	Portfolio& getPortfoilo();

	void setName(string name);
	void setAsset(int asset);
	void setcheckLoan(bool check);

	Loan_Manager& getLoanManager();
};

#endif
