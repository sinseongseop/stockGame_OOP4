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
	string		name;					//player��
	int			asset;					//���� �ڻ�
	bool		checkLoan = false;		//���� ����
	Portfolio playerPortfolio; 
	Loan_Manager playerLoan_Manager;

public:
	Player() {};

	//�ֽ� ���� �Լ�
	//���Կ� �����ϸ� true, �����ϸ� false return
	bool purchase(string item, int NumberOfItem, int CurrentPrice);

	//�ֽ� �ŵ� �Լ�
	//�ŵ��� �����ϸ� true, �����ϸ� false return
	bool sell(string item, int NumberOfItem);

	//���� �Լ�
	//������ ���������� false ��ȯ, ���������� true ��ȯ
	bool loan(int requested_loanAmount);

	//���� ��ȯ �Լ�
	//��ȯ�� ���������� false ��ȯ, ���������� true ��ȯ
	bool repayment(int repaymentAmount);

	//�����ȯ ���� ��ü ������Ʈ (���� ¡��)
	//���� �ڵ� ����
	//���� ���� parameter�� �޴´�
	void Loan_ManagerUpdate(int RoundCounter);

	//��Ʈ������ ������Ʈ ���� �Լ�
	//���� ����
	void PortfolioUpdate();

	//��Ʈ������ �ʱ�ȭ �Լ�
	//�ֽĽ��� manager ��ü�� �ּҸ� paramter�� �޴´�.
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
