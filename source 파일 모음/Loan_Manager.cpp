#define MAX_LOANAMOUNT 3000000;
#include "Loan_Manager.h";

Loan_Manager::Loan_Manager() {
		this->deadline = 4;
	}

//�� �ϸ��� �����ϴ� ���� ���� �Լ�
//player�� ���ݺ������� parameter�� �޴´�.
//deadline�� �������� true ��ȯ (���� ¡�� ����)
//player�� ������ ������ ���� ���� �����Ѵ�.
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

//���� ¡�� �Լ�
//���� ���׿� ���� ���� ��ȯ�� ����, ���� �ܾ��� return
//���� ������ �����ϴٸ� 0 return (�Ļ�)
int Loan_Manager::collection(int player_cash) {
		return repayment(player_cash);
}


//��ȯ �Լ�
//��ȯ �ݾ��� parameter�� �޴´�
//��ȯ�� ���ھ� -> �����(����) ������ ����
//��ȯ �ݾ��� ���ھ� + ����׺��� ���� ��� ������ return (Ȥ�� 0�� return)
int Loan_Manager::repayment(int repaymentAmount) {
		int buf = repaymentAmount;
		
		//���ھ� ��ȯ
		if (this->interestAmount > buf) {//�ܾ��� ���ھ׺��� ������ ���
			this->interestAmount -= buf;
			return 0;
		}
		else {
			buf -= this->interestAmount;
			this->interestAmount = 0;
		}

		//���� ��ȯ
		if (this->loanAmount > buf) {//��ȯ�� �ܾ��� ���ݺ��� ������ ���
			this->loanAmount -= buf;
			return 0;
		}
		else { //���ݱ��� �� ��ȯ�ϰ� �ݾ��� ���� ��� (���� ��ȯ)
			buf -= this->loanAmount;
			this->loanAmount = 0;
			this->deadline = 4; //deadline �ʱ�ȭ
		}

		return buf;
	}

//���� �Լ�
//���� ��û ���� parameter�� �޴´�
//���� �Ұ����ϴٸ� ������ �������� �ʰ� 0 return;
//���� �����ϴٸ� ������ �����ϰ� �ش� �ݾ��� return
int Loan_Manager::loan(int requested_loanAmount) {

		if (get_possibleLoanAmount() < requested_loanAmount) 
			return 0;
		
		else {
			this->interestRate += 5;
			this->loanAmount += requested_loanAmount;

			return requested_loanAmount;
		}
	}

	//���� ���� �ݾ� return �Լ�
int Loan_Manager::get_possibleLoanAmount() {
		int max = MAX_LOANAMOUNT;
		int possible_loanAmount = max - (this->loanAmount + this->interestAmount);
		

		if (possible_loanAmount <= 0)
			return 0;
		else
			return possible_loanAmount;
	}

	//�����(����) ��ȯ
int Loan_Manager::get_loanAmount() {
		return this->loanAmount;
	}

	//���ھ� ��ȯ
int Loan_Manager::get_interestAmount() {
		return this->interestAmount;
	}

	//������ ��ȯ
int Loan_Manager::get_interestRate() {
		return this->interestRate;
	}

int Loan_Manager::get_deadline() {
		return this->deadline;
	}


int Loan_Manager::get_MaxLimitMoney() { // �ִ� ���� ���� �ݾ� ����
	return MAX_LOANAMOUNT;
}