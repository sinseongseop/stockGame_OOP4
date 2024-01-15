#define MAX_LOANAMOUNT 3000000;
#include "Loan_Manager.h";

Loan_Manager::Loan_Manager() {
		this->deadline = 4;
	}

//매 턴마다 실행하는 정보 갱신 함수
//player의 현금보유액을 parameter로 받는다.
//deadline이 지났으면 true 반환 (강제 징수 실행)
//player가 대출을 가지고 있을 때만 실행한다.
bool Loan_Manager::update() { 
		
		if (this->loanAmount > 0) {
			//check deadline
			if (this->deadline > 0)
				this->deadline--;
			if (this->deadline == 0)
				return true;


			//update interestAmount
			this->interestAmount += (int)(this->loanAmount * this->interestRate / 100 );

		}
		return false;
	}

//강제 징수 함수
//현금 전액에 대해 대출 상환을 실행, 남은 잔액을 return
//만약 현금이 부족하다면 0 return (파산)
int Loan_Manager::collection(int player_cash) {
		return repayment(player_cash);
}


//상환 함수
//상환 금액을 parameter로 받는다
//상환은 이자액 -> 대출액(원금) 순으로 실행
//상환 금액이 이자액 + 대출액보다 많은 경우 차액을 return (혹은 0을 return)
int Loan_Manager::repayment(int repaymentAmount) {
		int buf = repaymentAmount;
		
		//이자액 상환
		if (this->interestAmount > buf) {//잔액이 이자액보다 부족한 경우
			this->interestAmount -= buf;
			return 0;
		}
		else {
			buf -= this->interestAmount;
			this->interestAmount = 0;
		}

		//원금 상환
		if (this->loanAmount > buf) {//상환액 잔액이 원금보다 부족한 경우
			this->loanAmount -= buf;
			return 0;
		}
		else { //원금까지 다 상환하고 금액이 남은 경우 (전액 상환)
			buf -= this->loanAmount;
			this->loanAmount = 0;
			this->deadline = 4; //deadline 초기화
		}

		return buf;
	}

//대출 함수
//대출 요청 액을 parameter로 받는다
//대출 불가능하다면 대출을 실행하지 않고 0 return;
//대출 가능하다면 대출을 실행하고 해당 금액을 return
int Loan_Manager::loan(int requested_loanAmount) {

		if (get_possibleLoanAmount() < requested_loanAmount) 
			return 0;
		
		else {
			this->interestRate += 5;
			this->loanAmount += requested_loanAmount;

			return requested_loanAmount;
		}
	}

	//대출 가능 금액 return 함수
int Loan_Manager::get_possibleLoanAmount() {
		int max = MAX_LOANAMOUNT;
		int possible_loanAmount = max - (this->loanAmount + this->interestAmount);
		

		if (possible_loanAmount <= 0)
			return 0;
		else
			return possible_loanAmount;
	}

	//대출액(원금) 반환
int Loan_Manager::get_loanAmount() {
		return this->loanAmount;
	}

	//이자액 반환
int Loan_Manager::get_interestAmount() {
		return this->interestAmount;
	}

	//이자율 반환
int Loan_Manager::get_interestRate() {
		return this->interestRate;
	}

int Loan_Manager::get_deadline() {
		return this->deadline;
	}


int Loan_Manager::get_MaxLimitMoney() { // 최대 대출 가능 금액 제한
	return MAX_LOANAMOUNT;
}