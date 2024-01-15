#pragma once
#ifndef _loanManager_
#define _loanManager_

class Loan_Manager {
private:
	int loanAmount = 0;			//대출액(원금)
	int interestAmount = 0;		//이자액
	int interestRate = 0;		//이자율, 이자를 한번 받을 때마다 증가
	int deadline;			//기한, 4턴
public:
	Loan_Manager();

	//매 턴마다 실행하는 정보 갱신 함수
	//player의 현금보유액을 parameter로 받는다.
	//deadline이 지났으면 true 반환 (강제 징수 실행)
	//player가 대출을 가지고 있을 때만 실행한다.
	bool update();

	//강제 징수 함수
	//현금 전액에 대해 대출 상환을 실행, 남은 잔액을 return
	//만약 현금이 부족하다면 0 return (파산)
	int collection(int player_cash);

	//상환 함수
	//상환 금액을 parameter로 받는다
	//상환은 이자액 -> 대출액(원금) 순으로 실행
	//상환 금액이 이자액 + 대출액보다 많은 경우 차액을 return (혹은 0을 return)
	int repayment(int repaymentAmount);

	//대출 함수
	//대출 요청 액을 parameter로 받는다
	//대출 불가능하다면 대출을 실행하지 않고 0 return;
	//대출 가능하다면 대출을 실행하고 해당 금액을 return
	int loan(int requested_loanAmount);

	//대출 가능 금액 return 함수
	int get_possibleLoanAmount();

	//대출액(원금) 반환
	int get_loanAmount();

	//이자액 반환
	int get_interestAmount();

	//이자율 반환
	int get_interestRate();

	//deadline 반환
	int get_deadline();

	int get_MaxLimitMoney(); // 최대 대출 제한 금액

};

#endif