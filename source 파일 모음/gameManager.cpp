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

void gameManager::runWithConsole() {  //게임 구동
	initializeGame(); //필요한 초기 설정
	while (gameRun) {
		 
		// GUI 연동해서 게임 진행 코드 함수들
			
		//턴마다 업데이트
		
		turnUpdate();

		

		
		//메인 화면 print
		showMain();

		
		
		//player 동작
		int command = -1;
		while (command != 0) {
			showMenu();
			cout << "Select Menu : ";
			cin >> command;

			if (command < 0 || command > 3) {
				cout << "Errror : Wrong Input\n";
				continue;
			}

			//1. 플레이어 포트폴리오(매수,매도)
			if (command == 1) {
				//포트폴리오 출력
				showPortfolio();

				//매수, 매도 처리
				int buf_portfolio = -1;

				cout << "[Portfolio Menu]\n"
					<< "0. Main\n"
					<< "1. 주식 매수\n"
					<< "2. 주식 매도\n"
					<< ">> ";
				cin >> buf_portfolio;

				while(true) {
					if (buf_portfolio == 0) {
						break;
					}

					//매수 진행
					if (buf_portfolio == 1) {
						buyStock();
					}
					//매도 진행
					else if (buf_portfolio == 2) {
						sellStock();
					}
					//이상한 입력
					else
						cout << "Error:Wrong input\n";

					cout << "0. Main\n"
						<< "1. 주식 매수\n"
						<< "2. 주식 매도\n"
						<< ">> ";
					cin >> buf_portfolio;
				}
				
			}

			//2. 은행 (대출, 상환)
			else if (command == 2) {
				showBank();
			}
			
			//3. 투자 정보 조회
			else if (command == 3) {
				showInfo();
			}
		}
		
		
		if (turn == 10) { // 10턴이 끝나면 게임 종료
			gameRun = false;
		}


		EndGame(); //게임 결과 창 보여주기 + 결과 저장
	}
}

void gameManager::initializeGame() {  // 게임의 초기 정보 설정
	for (int i = 0; i < 3; i++) { // 테마 매니저 추가
		gameStockManager.addthemaManger(themaName[i], themaTxtFile[i]);
	}

	for (int i = 0; i < 6; i++) { //주식 추가
		gameStockManager.addStock(stockName[i],stockThema[i],startStockPrice, enterpriseTxtFile[i]);
	}

	//게임 플레이어 초기 설정
	player.setAsset(300000);
	player.setName("NewBie");
	player.Portfolioinitialize(&gameStockManager);
}

void gameManager::increaseTurn() {
	this->turn += 1;
} 

void gameManager::UpdateStockInfo() { // 정보를 업데이트하고 주식값들을 업데이트 한다.
	gameStockManager.updateStockPrice(); // 정보 반영해서 가격 변동
	gameStockManager.updateNewInfo(); //새로운 정보 취득
}

void gameManager::UpdatePlayer() {
	player.Loan_ManagerUpdate(turn); //LoanManager 갱신
	player.PortfolioUpdate(); //포트폴리오 갱신
}


void gameManager::EndGame() { 
	//주식 가치 합산
	int sum_amount = 0;
	for (int i = 0; i < gameStockManager.getStocksNumber(); i++)
		sum_amount += player.getPortfoilo().get_ithInvestStruct(i).amount;

	cout << "[Game End]\n";
	cout << "Asset : " << player.getAsset() << "\n";
	cout << "Overall Investment Assessment : " << sum_amount << "\n";
	cout << "Total : " << player.getAsset() + sum_amount << "\n";

	
	// record 출력
	// Record 달성확인
	// 달성했으면 saveResult() 호출해서 record txt.file 갱신
	
}

void gameManager::showMain() {
	cout << "---------------------- Main ----------------------\n";
	cout << "Round " << this->turn << "\n";

	//player 정보 printing
	cout << "[Player Info]\n";
	cout << "Name : " << player.getName() << "\n";
	cout << "Asset : " << player.getAsset() << "won";
	if (player.getCheckLoan() == true)
		cout << "(대출 포함)";
	cout << "\n";
	
	cout << "--------------------------------------------------\n";
	cout << "[주식 정보]\n";
	for (int i = 0; i < gameStockManager.getStocksNumber(); i++) {
		gameStockManager.getStock(i).printstock();
		cout << "\n";
	}
	cout << "--------------------------------------------------\n";
}

void gameManager::showInfo() {
	cout << "---------------------- Info ----------------------\n";
	//테마 투자 정보
	gameStockManager.printThemaInfo();

	//기업 투자 정보
	for (int i = 0; i < gameStockManager.getStocksNumber(); i++) {
		cout << "[" << gameStockManager.getStock(i).getStockName() << "]\n";

		if(player.getPortfoilo().getInfoUnlook(i)) //정보가 오픈된 경우
			cout << gameStockManager.getStock(i).getInfo().getInfo() << "\n";
		else //오픈되지 않은 경우
			cout << "Locked\n";
	}
	
	if (infoPurchase)
		return;

	//정보 구매 처리
	int buf = -1;
	cout << "정보를 구매할 기업 번호를 입력(0 미구매) : ";
	cin >> buf;

	if (buf < 1 || buf > 6)
		return;

	while (player.getPortfoilo().getInfoUnlook(buf-1)) {
		cout << "이미 보유한 정보입니다. 다시 입력하세요 : ";
		cin >> buf;
	}

	
	player.setAsset(player.getAsset() - INFO_PURCHASING_PRICE);
	infoPurchase = true;
	player.getPortfoilo().setInfoUnlook(buf-1, true);
	cout << "구매된 정보 : " << gameStockManager.getStock(buf-1).getInfo().getInfo() << "\n";
	cout << "잔액 : " << player.getAsset() << "\n";
}

void gameManager::showMenu() {
	cout << "--------------------------------------------------\n";
	cout << "0. 턴 종료\n";
	cout << "1. 플레이어 포트폴리오(매수,매도)\n";
	cout << "2. 은행 (대출, 상환)\n";
	cout << "3. 투자 정보 조회\n";
	cout << "--------------------------------------------------\n";

}

void gameManager::showPortfolio() {
	cout << "-------------------- Portfolio --------------------\n";

	InvestStruct buf;
	for (int i = 0; i < gameStockManager.getStocksNumber(); i++) {
		buf = player.getPortfoilo().get_ithInvestStruct(i);
		
		//보유한 주식의 경우 출력
		if (buf.NumberOfItem > 0) {  
			cout << "[" << buf.item << "]\n";
			cout << buf.NumberOfItem << "주 보유 | 평가금액 " << buf.amount << "\n";
			cout << "매입가 " << buf.PurchasingPrice << " -> 현재가 " << buf.CurrentPrice << "\n";
			cout << "평가손익 " << buf.profit << "| 수익률 " << buf.EarningsRate << "%\n"; 
		}
	}

	cout << "---------------------------------------------------\n";
}

//매수 함수
void gameManager::buyStock() {
	//주식 목록 출력
	cout << "[목록]\n";
	for (int i = 0; i < gameStockManager.getStocksNumber(); i++) {
		cout << gameStockManager.getStock(i).getStockName() << " ";
	}
	cout << "\n";

	string name_buf;
	cout << "구매하려는 주식 명을 입력하시오 >> ";
	cin >> name_buf;
	
	

	//주식 검색
	int idx;
	for (idx = 0; idx < gameStockManager.getStocksNumber(); idx++) {
		if (name_buf.compare(gameStockManager.getStock(idx).getStockName()) == 0)
			break;
	}

	//주식명을 잘못 입력한 경우
	if (idx == gameStockManager.getStocksNumber()) {
		cout << "해당하는 주식이 없습니다\n";
		return;
	}

	cout << "구매할 수량을 입력하시오 >> ";
	int amount_buf = 0;
	cin >> amount_buf;

	if (amount_buf < 1) {
		cout << "너무 작은 수량을 입력했습니다\n";
		return;
	}

	bool purchasing = player.purchase(name_buf, amount_buf, gameStockManager.getStock(idx).getStockPrice());
		
	if (purchasing) {//매수 성공
		cout << "매수 체결 | 잔액 " << player.getAsset() << "won\n";
	}
	else  //매수 실패
		cout << "문제가 발생하여 매수에 실패했습니다.\n";
		
	
}

//매도 함수
void gameManager::sellStock() {
	//주식 목록 출력
	cout << "[목록]\n";
	for (int i = 0; i < gameStockManager.getStocksNumber(); i++) {
		if (player.getPortfoilo().get_ithInvestStruct(i).NumberOfItem > 0)
			cout << player.getPortfoilo().get_ithInvestStruct(i).item << " ";
	}
	cout << "\n";

	string name_buf;
	cout << "판매하려는 주식 명을 입력하시오 >> ";
	cin >> name_buf;

	//주식 검색
	int idx;
	for (idx = 0; idx < gameStockManager.getStocksNumber(); idx++) {
		if (name_buf.compare(gameStockManager.getStock(idx).getStockName()) == 0)
			break;
	}

	//주식명을 잘못 입력한 경우
	if (idx == gameStockManager.getStocksNumber()) {
		cout << "해당하는 주식이 없습니다\n";
		return;
	}

	cout << "판매할 수량을 입력하시오 >> ";
	int amount_buf = 0;
	cin >> amount_buf;

	bool selling = player.sell(name_buf, amount_buf);


	if (selling) {//매도 성공
		cout << "매도 채결 | 잔액 " << player.getAsset() << "won\n";
	}
	else  //매도 실패
		cout << "문제가 발생하여 매도에 실패했습니다.\n";

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


void gameManager::showBank() {// 은행정보 표시
	cout << "----------------------Loan Info ----------------------\n";
	Loan_Manager& gameLoanManager = player.getLoanManager();

	if (player.getCheckLoan() == false) {
		cout << " 대출 내역이 없습니다. \n";
	}
	else {
		cout << "총 대출 금액 : " << gameLoanManager.get_loanAmount() + gameLoanManager.get_interestAmount() << "won\n";
		cout << "원금: " << gameLoanManager.get_loanAmount() << "won\n";
		cout << "이자: " << gameLoanManager.get_interestAmount() << "won\n";
		cout << "이자율: " << gameLoanManager.get_interestRate() << "%\n";
		cout << "deadline: " << gameLoanManager.get_deadline() << "day\n";
	}

	cout << "-----------------------------------------------------\n";
	cout << "남은 대출 가능 금액 : " << gameLoanManager.get_MaxLimitMoney() - gameLoanManager.get_loanAmount() << "won\n";
	cout << "적용 이자율:" << gameLoanManager.get_interestRate() + 5 << "%\n";

	bool menuRun = true;
	while (menuRun) {
		int inputBuffer;

		cout << "0. 메인 화면으로 \n";
		cout << "1. 대출 \n";
		cout << "2. 상환 \n";
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
			cout << "잘못된 번호 입력. 다시 입력해주세요. \n";
			break;
		}

		cout << "잔액 : " << player.getAsset();

	}


}


void gameManager::loan(Loan_Manager& gameLoanManager) {
	int LoanMoney = 0;
	cout << "대출할 금액을 입력해주세요.(대출을 원하지 않을시 0 입력) :";
	cin >> LoanMoney;

	if (LoanMoney <= 0) {
		return;
	}

	if (LoanMoney > (gameLoanManager.get_MaxLimitMoney() - gameLoanManager.get_loanAmount())) {
		cout << gameLoanManager.get_MaxLimitMoney() - gameLoanManager.get_loanAmount() << "won까지만 대출이 가능합니다.\n";
		cout << gameLoanManager.get_MaxLimitMoney() - gameLoanManager.get_loanAmount() << "won을 대출합니다.\n";
		LoanMoney = gameLoanManager.get_MaxLimitMoney() - gameLoanManager.get_loanAmount();
	}
	else {
		cout << LoanMoney << "won을 대출 합니다.\n";
	}
	player.loan(LoanMoney);
}

void gameManager::repayment(Loan_Manager& gameLoanManager) {
	if (player.getCheckLoan() == false) {
		cout << "대출 내역이 없습니다. \n";
	}
	else {
		int repayMoney = 0;
		cout << "플레이어의 자산: " << player.getAsset() << "won\n";
		cout << "총 대출 금액: " << gameLoanManager.get_loanAmount() + gameLoanManager.get_interestAmount() << "won\n";
		cout << "상환 희망 금액: ";
		cin >> repayMoney;

		if (repayMoney > player.getAsset()) {
			cout << "플레이어의 자산 보다 많은 금액을 상환 할 수는 없습니다." << "\n";
			return;
		}

		if (repayMoney > gameLoanManager.get_loanAmount() + gameLoanManager.get_interestAmount()) {
			cout << gameLoanManager.get_loanAmount() + gameLoanManager.get_interestAmount() << "won을 상환 합니다.\n";
			repayMoney = gameLoanManager.get_loanAmount() + gameLoanManager.get_interestAmount();
		}
		else {
			cout << repayMoney << "won을 상환 합니다.\n";
		}
		player.repayment(repayMoney);

		if (gameLoanManager.get_loanAmount() + gameLoanManager.get_interestAmount() <= 0) {
			player.setcheckLoan(false);
		}
	}
}



void gameManager::turnUpdate() {
	
	
	if (checkPlayerBankruptcy() || turn > 9)	//파산확인
		gameRun = false;
	increaseTurn();					//턴 증가
	UpdateStockInfo();				//정보 및 주식값 업데이트
	UpdatePlayer();					//player 정보 업데이트
	infoPurchase = false;			//정보 구매 여부 초기화
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