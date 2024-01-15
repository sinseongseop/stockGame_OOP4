#pragma once
#ifndef _loanManager_
#define _loanManager_

class Loan_Manager {
private:
	int loanAmount = 0;			//�����(����)
	int interestAmount = 0;		//���ھ�
	int interestRate = 0;		//������, ���ڸ� �ѹ� ���� ������ ����
	int deadline;			//����, 4��
public:
	Loan_Manager();

	//�� �ϸ��� �����ϴ� ���� ���� �Լ�
	//player�� ���ݺ������� parameter�� �޴´�.
	//deadline�� �������� true ��ȯ (���� ¡�� ����)
	//player�� ������ ������ ���� ���� �����Ѵ�.
	bool update();

	//���� ¡�� �Լ�
	//���� ���׿� ���� ���� ��ȯ�� ����, ���� �ܾ��� return
	//���� ������ �����ϴٸ� 0 return (�Ļ�)
	int collection(int player_cash);

	//��ȯ �Լ�
	//��ȯ �ݾ��� parameter�� �޴´�
	//��ȯ�� ���ھ� -> �����(����) ������ ����
	//��ȯ �ݾ��� ���ھ� + ����׺��� ���� ��� ������ return (Ȥ�� 0�� return)
	int repayment(int repaymentAmount);

	//���� �Լ�
	//���� ��û ���� parameter�� �޴´�
	//���� �Ұ����ϴٸ� ������ �������� �ʰ� 0 return;
	//���� �����ϴٸ� ������ �����ϰ� �ش� �ݾ��� return
	int loan(int requested_loanAmount);

	//���� ���� �ݾ� return �Լ�
	int get_possibleLoanAmount();

	//�����(����) ��ȯ
	int get_loanAmount();

	//���ھ� ��ȯ
	int get_interestAmount();

	//������ ��ȯ
	int get_interestRate();

	//deadline ��ȯ
	int get_deadline();

	int get_MaxLimitMoney(); // �ִ� ���� ���� �ݾ�

};

#endif