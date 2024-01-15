#pragma once
#ifndef _GAMEMANAGER_
#define _GAMEMANAGER_

#include <iostream>
#include <string>
#include <vector>
#include "player.h"
#include "stockManager.h"

using namespace std;

#define INFO_PURCHASING_PRICE 10000

class gameManager {
private:
	int turn = 0;
	Player player;
	stockManager gameStockManager;
	bool gameRun = true;

	vector<bool> seeInfo;
	bool infoPurchase = false; // 정보 구매 여부, 턴마다 초기화 된다.

public:
	//-----------------------
	// 게임 구동 함수
	//-----------------------
	
	//게임 시작 함수
	void runWithConsole(); 
	//게임 초기 설정 함수
	void initializeGame();
	//게임 종료 함수
	//마지막 턴이 되면 실행
	void EndGame(); 
	//게임 결과를 저장
	void saveResult(); 

	//-----------------------
	//턴 당 update 함수
	//-----------------------

	//턴이 지날때마다 udpate를 실행하는 함수
	void turnUpdate();
	//turn을 1 증가 시킨다.
	void increaseTurn(); 
	// 주식값 및 새로운 정보로 업데이트 한다.
	void UpdateStockInfo();
	// player 정보를 업데이트한다.
	void UpdatePlayer();
	//player 파산여부를 확인
	//파산했으면 true 반환
	bool checkPlayerBankruptcy();

	//-----------------------
	//화면 graphic 함수
	//-----------------------

	//main 화면 출력
	void showMain(); 
	//포트폴리오 화면 출력
	void showPortfolio();
	//은행 정보 화면 출력
	void showBank();
	//투자 정보 화면 출력
	void showInfo(); 
	//menu 화면 출력
	void showMenu();

	//-----------------------
	//player 실행
	//-----------------------

	//매수 함수
	void buyStock();
	//매도 함수
	void sellStock();
	//대출 함수
	void loan(Loan_Manager& gameLoanManager);
	// 반환 함수
	void repayment(Loan_Manager& gameLoanManager);
	
	//-----------------------
	//etc
	//-----------------------
	
	stockManager& get_stockManager();
	Player& get_player();
	int get_round();
	bool get_infoPurchase();
	void set_infoPurchase(bool val);
	bool get_gameRun();
};



#endif
