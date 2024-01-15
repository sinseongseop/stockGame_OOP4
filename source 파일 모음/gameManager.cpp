#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <random>
#include <fstream>
#include "player.h"
#include "stockManager.h"
#include "gameManager.h"
#include "Loan_Manager.h"

using namespace std;

string themaTxtFile[3] = { "thema1.txt","thema2.txt","thema3.txt" };
string themaName[3] = { "thema1","thema2","thema3" };
string enterpriseTxtFile[6] = { "A_bio.txt","B_bio.txt","A_food.txt","B_food.txt","A_tech.txt","B_tech.txt" };
string stockName[6] = { "A_BIO","B_BIO","A_Food","B_Food","A_IT","B_IT" };
string stockThema[6] = { "bio","bio","Food","Food","IT","IT" };
const float startStockPrice = 10000;

void gameManager::runWithConsole() {  //���� ����
	initializeGame(); //�ʿ��� �ʱ� ����
	while (gameRun) {
		 
		// GUI �����ؼ� ���� ���� �ڵ� �Լ���
			
		//�ϸ��� ������Ʈ
		
		turnUpdate();

		

		
		//���� ȭ�� print
		showMain();

		
		
		//player ����
		int command = -1;
		while (command != 0) {
			showMenu();
			cout << "Select Menu : ";
			cin >> command;

			if (command < 0 || command > 3) {
				cout << "Errror : Wrong Input\n";
				continue;
			}

			//1. �÷��̾� ��Ʈ������(�ż�,�ŵ�)
			if (command == 1) {
				//��Ʈ������ ���
				showPortfolio();

				//�ż�, �ŵ� ó��
				int buf_portfolio = -1;

				cout << "[Portfolio Menu]\n"
					<< "0. Main\n"
					<< "1. �ֽ� �ż�\n"
					<< "2. �ֽ� �ŵ�\n"
					<< ">> ";
				cin >> buf_portfolio;

				while(true) {
					if (buf_portfolio == 0) {
						break;
					}

					//�ż� ����
					if (buf_portfolio == 1) {
						buyStock();
					}
					//�ŵ� ����
					else if (buf_portfolio == 2) {
						sellStock();
					}
					//�̻��� �Է�
					else
						cout << "Error:Wrong input\n";

					cout << "0. Main\n"
						<< "1. �ֽ� �ż�\n"
						<< "2. �ֽ� �ŵ�\n"
						<< ">> ";
					cin >> buf_portfolio;
				}
				
			}

			//2. ���� (����, ��ȯ)
			else if (command == 2) {
				showBank();
			}
			
			//3. ���� ���� ��ȸ
			else if (command == 3) {
				showInfo();
			}
		}
		
		
		if (turn == 10) { // 10���� ������ ���� ����
			gameRun = false;
		}


		EndGame(); //���� ��� â �����ֱ� + ��� ����
	}
}

void gameManager::initializeGame() {  // ������ �ʱ� ���� ����
	for (int i = 0; i < 3; i++) { // �׸� �Ŵ��� �߰�
		gameStockManager.addthemaManger(themaName[i], themaTxtFile[i]);
	}

	for (int i = 0; i < 6; i++) { //�ֽ� �߰�
		gameStockManager.addStock(stockName[i],stockThema[i],startStockPrice, enterpriseTxtFile[i]);
	}

	//���� �÷��̾� �ʱ� ����
	player.setAsset(300000);
	player.setName("NewBie");
	player.Portfolioinitialize(&gameStockManager);
}

void gameManager::increaseTurn() {
	this->turn += 1;
} 

void gameManager::UpdateStockInfo() { // ������ ������Ʈ�ϰ� �ֽİ����� ������Ʈ �Ѵ�.
	gameStockManager.updateStockPrice(); // ���� �ݿ��ؼ� ���� ����
	gameStockManager.updateNewInfo(); //���ο� ���� ���
}

void gameManager::UpdatePlayer() {
	player.Loan_ManagerUpdate(turn); //LoanManager ����
	player.PortfolioUpdate(); //��Ʈ������ ����
}


void gameManager::EndGame() { 
	//�ֽ� ��ġ �ջ�
	int sum_amount = 0;
	for (int i = 0; i < gameStockManager.getStocksNumber(); i++)
		sum_amount += player.getPortfoilo().get_ithInvestStruct(i).amount;

	cout << "[Game End]\n";
	cout << "Asset : " << player.getAsset() << "\n";
	cout << "Overall Investment Assessment : " << sum_amount << "\n";
	cout << "Total : " << player.getAsset() + sum_amount << "\n";

	
	// record ���
	// Record �޼�Ȯ��
	// �޼������� saveResult() ȣ���ؼ� record txt.file ����
	
}

void gameManager::showMain() {
	cout << "---------------------- Main ----------------------\n";
	cout << "Round " << this->turn << "\n";

	//player ���� printing
	cout << "[Player Info]\n";
	cout << "Name : " << player.getName() << "\n";
	cout << "Asset : " << player.getAsset() << "won";
	if (player.getCheckLoan() == true)
		cout << "(���� ����)";
	cout << "\n";
	
	cout << "--------------------------------------------------\n";
	cout << "[�ֽ� ����]\n";
	for (int i = 0; i < gameStockManager.getStocksNumber(); i++) {
		gameStockManager.getStock(i).printstock();
		cout << "\n";
	}
	cout << "--------------------------------------------------\n";
}

void gameManager::showInfo() {
	cout << "---------------------- Info ----------------------\n";
	//�׸� ���� ����
	gameStockManager.printThemaInfo();

	//��� ���� ����
	for (int i = 0; i < gameStockManager.getStocksNumber(); i++) {
		cout << "[" << gameStockManager.getStock(i).getStockName() << "]\n";

		if(player.getPortfoilo().getInfoUnlook(i)) //������ ���µ� ���
			cout << gameStockManager.getStock(i).getInfo().getInfo() << "\n";
		else //���µ��� ���� ���
			cout << "Locked\n";
	}
	
	if (infoPurchase)
		return;

	//���� ���� ó��
	int buf = -1;
	cout << "������ ������ ��� ��ȣ�� �Է�(0 �̱���) : ";
	cin >> buf;

	if (buf < 1 || buf > 6)
		return;

	while (player.getPortfoilo().getInfoUnlook(buf-1)) {
		cout << "�̹� ������ �����Դϴ�. �ٽ� �Է��ϼ��� : ";
		cin >> buf;
	}

	
	player.setAsset(player.getAsset() - INFO_PURCHASING_PRICE);
	infoPurchase = true;
	player.getPortfoilo().setInfoUnlook(buf-1, true);
	cout << "���ŵ� ���� : " << gameStockManager.getStock(buf-1).getInfo().getInfo() << "\n";
	cout << "�ܾ� : " << player.getAsset() << "\n";
}

void gameManager::showMenu() {
	cout << "--------------------------------------------------\n";
	cout << "0. �� ����\n";
	cout << "1. �÷��̾� ��Ʈ������(�ż�,�ŵ�)\n";
	cout << "2. ���� (����, ��ȯ)\n";
	cout << "3. ���� ���� ��ȸ\n";
	cout << "--------------------------------------------------\n";

}

void gameManager::showPortfolio() {
	cout << "-------------------- Portfolio --------------------\n";

	InvestStruct buf;
	for (int i = 0; i < gameStockManager.getStocksNumber(); i++) {
		buf = player.getPortfoilo().get_ithInvestStruct(i);
		
		//������ �ֽ��� ��� ���
		if (buf.NumberOfItem > 0) {  
			cout << "[" << buf.item << "]\n";
			cout << buf.NumberOfItem << "�� ���� | �򰡱ݾ� " << buf.amount << "\n";
			cout << "���԰� " << buf.PurchasingPrice << " -> ���簡 " << buf.CurrentPrice << "\n";
			cout << "�򰡼��� " << buf.profit << "| ���ͷ� " << buf.EarningsRate << "%\n"; 
		}
	}

	cout << "---------------------------------------------------\n";
}

//�ż� �Լ�
void gameManager::buyStock() {
	//�ֽ� ��� ���
	cout << "[���]\n";
	for (int i = 0; i < gameStockManager.getStocksNumber(); i++) {
		cout << gameStockManager.getStock(i).getStockName() << " ";
	}
	cout << "\n";

	string name_buf;
	cout << "�����Ϸ��� �ֽ� ���� �Է��Ͻÿ� >> ";
	cin >> name_buf;
	
	

	//�ֽ� �˻�
	int idx;
	for (idx = 0; idx < gameStockManager.getStocksNumber(); idx++) {
		if (name_buf.compare(gameStockManager.getStock(idx).getStockName()) == 0)
			break;
	}

	//�ֽĸ��� �߸� �Է��� ���
	if (idx == gameStockManager.getStocksNumber()) {
		cout << "�ش��ϴ� �ֽ��� �����ϴ�\n";
		return;
	}

	cout << "������ ������ �Է��Ͻÿ� >> ";
	int amount_buf = 0;
	cin >> amount_buf;

	if (amount_buf < 1) {
		cout << "�ʹ� ���� ������ �Է��߽��ϴ�\n";
		return;
	}

	bool purchasing = player.purchase(name_buf, amount_buf, gameStockManager.getStock(idx).getStockPrice());
		
	if (purchasing) {//�ż� ����
		cout << "�ż� ü�� | �ܾ� " << player.getAsset() << "won\n";
	}
	else  //�ż� ����
		cout << "������ �߻��Ͽ� �ż��� �����߽��ϴ�.\n";
		
	
}

//�ŵ� �Լ�
void gameManager::sellStock() {
	//�ֽ� ��� ���
	cout << "[���]\n";
	for (int i = 0; i < gameStockManager.getStocksNumber(); i++) {
		if (player.getPortfoilo().get_ithInvestStruct(i).NumberOfItem > 0)
			cout << player.getPortfoilo().get_ithInvestStruct(i).item << " ";
	}
	cout << "\n";

	string name_buf;
	cout << "�Ǹ��Ϸ��� �ֽ� ���� �Է��Ͻÿ� >> ";
	cin >> name_buf;

	//�ֽ� �˻�
	int idx;
	for (idx = 0; idx < gameStockManager.getStocksNumber(); idx++) {
		if (name_buf.compare(gameStockManager.getStock(idx).getStockName()) == 0)
			break;
	}

	//�ֽĸ��� �߸� �Է��� ���
	if (idx == gameStockManager.getStocksNumber()) {
		cout << "�ش��ϴ� �ֽ��� �����ϴ�\n";
		return;
	}

	cout << "�Ǹ��� ������ �Է��Ͻÿ� >> ";
	int amount_buf = 0;
	cin >> amount_buf;

	bool selling = player.sell(name_buf, amount_buf);


	if (selling) {//�ŵ� ����
		cout << "�ŵ� ä�� | �ܾ� " << player.getAsset() << "won\n";
	}
	else  //�ŵ� ����
		cout << "������ �߻��Ͽ� �ŵ��� �����߽��ϴ�.\n";

}

bool gameManager::checkPlayerBankruptcy() {
	if (player.getAsset() == 0)
		return true;
	
	/*int sum_amount = 0;
	for (int i = 0; i < gameStockManager.getStocksNumber(); i++)
		sum_amount += player.getPortfoilo().get_ithInvestStruct(i).amount;
	sum_amount += player.getAsset();
	
	if (sum_amount == 0)
		return true;*/


	return false;
}


void gameManager::showBank() {// �������� ǥ��
	cout << "----------------------Loan Info ----------------------\n";
	Loan_Manager& gameLoanManager = player.getLoanManager();

	if (player.getCheckLoan() == false) {
		cout << " ���� ������ �����ϴ�. \n";
	}
	else {
		cout << "�� ���� �ݾ� : " << gameLoanManager.get_loanAmount() + gameLoanManager.get_interestAmount() << "won\n";
		cout << "����: " << gameLoanManager.get_loanAmount() << "won\n";
		cout << "����: " << gameLoanManager.get_interestAmount() << "won\n";
		cout << "������: " << gameLoanManager.get_interestRate() << "%\n";
		cout << "deadline: " << gameLoanManager.get_deadline() << "day\n";
	}

	cout << "-----------------------------------------------------\n";
	cout << "���� ���� ���� �ݾ� : " << gameLoanManager.get_MaxLimitMoney() - gameLoanManager.get_loanAmount() << "won\n";
	cout << "���� ������:" << gameLoanManager.get_interestRate() + 5 << "%\n";

	bool menuRun = true;
	while (menuRun) {
		int inputBuffer;

		cout << "0. ���� ȭ������ \n";
		cout << "1. ���� \n";
		cout << "2. ��ȯ \n";
		cout << ">> ";
		cin >> inputBuffer;

		switch (inputBuffer)
		{
		case 0:
			menuRun = false;
			break;
		case 1:
			loan(gameLoanManager);
			break;
		case 2:
			repayment(gameLoanManager);
			break;
		default:
			cout << "�߸��� ��ȣ �Է�. �ٽ� �Է����ּ���. \n";
			break;
		}

		cout << "�ܾ� : " << player.getAsset();

	}


}


void gameManager::loan(Loan_Manager& gameLoanManager) {
	int LoanMoney = 0;
	cout << "������ �ݾ��� �Է����ּ���.(������ ������ ������ 0 �Է�) :";
	cin >> LoanMoney;

	if (LoanMoney <= 0) {
		return;
	}

	if (LoanMoney > (gameLoanManager.get_MaxLimitMoney() - gameLoanManager.get_loanAmount())) {
		cout << gameLoanManager.get_MaxLimitMoney() - gameLoanManager.get_loanAmount() << "won������ ������ �����մϴ�.\n";
		cout << gameLoanManager.get_MaxLimitMoney() - gameLoanManager.get_loanAmount() << "won�� �����մϴ�.\n";
		LoanMoney = gameLoanManager.get_MaxLimitMoney() - gameLoanManager.get_loanAmount();
	}
	else {
		cout << LoanMoney << "won�� ���� �մϴ�.\n";
	}
	player.loan(LoanMoney);
}

void gameManager::repayment(Loan_Manager& gameLoanManager) {
	if (player.getCheckLoan() == false) {
		cout << "���� ������ �����ϴ�. \n";
	}
	else {
		int repayMoney = 0;
		cout << "�÷��̾��� �ڻ�: " << player.getAsset() << "won\n";
		cout << "�� ���� �ݾ�: " << gameLoanManager.get_loanAmount() + gameLoanManager.get_interestAmount() << "won\n";
		cout << "��ȯ ��� �ݾ�: ";
		cin >> repayMoney;

		if (repayMoney > player.getAsset()) {
			cout << "�÷��̾��� �ڻ� ���� ���� �ݾ��� ��ȯ �� ���� �����ϴ�." << "\n";
			return;
		}

		if (repayMoney > gameLoanManager.get_loanAmount() + gameLoanManager.get_interestAmount()) {
			cout << gameLoanManager.get_loanAmount() + gameLoanManager.get_interestAmount() << "won�� ��ȯ �մϴ�.\n";
			repayMoney = gameLoanManager.get_loanAmount() + gameLoanManager.get_interestAmount();
		}
		else {
			cout << repayMoney << "won�� ��ȯ �մϴ�.\n";
		}
		player.repayment(repayMoney);

		if (gameLoanManager.get_loanAmount() + gameLoanManager.get_interestAmount() <= 0) {
			player.setcheckLoan(false);
		}
	}
}



void gameManager::turnUpdate() {
	
	
	if (checkPlayerBankruptcy() || turn > 9)	//�Ļ�Ȯ��
		gameRun = false;
	increaseTurn();					//�� ����
	UpdateStockInfo();				//���� �� �ֽİ� ������Ʈ
	UpdatePlayer();					//player ���� ������Ʈ
	infoPurchase = false;			//���� ���� ���� �ʱ�ȭ
}

Player& gameManager::get_player() {
	return this->player;
}

stockManager& gameManager::get_stockManager() {
	return this->gameStockManager;
}

int gameManager::get_round() {
	return this->turn;
}

bool gameManager::get_infoPurchase() {
	return this->infoPurchase;
}

void gameManager::set_infoPurchase(bool val) {
	this->infoPurchase = val;
}

bool gameManager::get_gameRun() {
	return this->gameRun;
}