#include <iostream>
#include <string>
#include "player.h"


using namespace std;

string Player::getName()
{
	return this->name;
}

int Player::getAsset()
{
	return this->asset;
}

bool Player::getCheckLoan()
{
	return this->checkLoan;
}

void Player::setName(string name)
{
	this->name = name;
}

void Player::setAsset(int asset) {
	this->asset = asset;
}

bool Player::purchase(string item, int NumberOfItem, int CurrentPrice) {

	//������ ������ ���
	if (this->asset < (NumberOfItem * CurrentPrice))
		return false;

	//������ ������ ���
	if (playerPortfolio.purchase(item, NumberOfItem)) {
		this->asset -= NumberOfItem * CurrentPrice;
		return true;
	}

	return false;
}

bool Player::sell(string item, int NumberOfItem) {
	int sellAmount = playerPortfolio.sell(item, NumberOfItem);

	if (sellAmount <= 0) //�ŵ� ����
		return false;

	else {
		asset += sellAmount;
		return true;
	}
}

bool Player::loan(int requested_loanAmount) {
	int loanAmount = playerLoan_Manager.loan(requested_loanAmount);

	//���� ���� 
	if (loanAmount == 0)
		return false;

	//���� ����
	else {
		asset += loanAmount;
		checkLoan = true;
		return true;
	}
}

bool Player::repayment(int repaymentAmount) {
	//��ȯ ���� (���� ����)
	if (repaymentAmount > this->asset)
		return false;

	else {
		asset -= repaymentAmount;
		asset += playerLoan_Manager.repayment(repaymentAmount);
		return true;
	}
}

void Player::Loan_ManagerUpdate(int RoundCounter) {
	if (checkLoan == true) {
		int updateValue = playerLoan_Manager.update();

		//���� ¡�� ����
		if (updateValue || RoundCounter == 10)
			asset = playerLoan_Manager.collection(asset);
	}
}

void Player::PortfolioUpdate() {
	playerPortfolio.update();
}

void Player::Portfolioinitialize(stockManager* stocks) {
	playerPortfolio.initialize(stocks);
}

Portfolio& Player::getPortfoilo() {
	return this->playerPortfolio;
}

Loan_Manager& Player::getLoanManager() {
	return this->playerLoan_Manager;
}

void Player::setcheckLoan(bool check) {
	this->checkLoan = check;
}