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
	bool infoPurchase = false; // ���� ���� ����, �ϸ��� �ʱ�ȭ �ȴ�.

public:
	//-----------------------
	// ���� ���� �Լ�
	//-----------------------
	
	//���� ���� �Լ�
	void runWithConsole(); 
	//���� �ʱ� ���� �Լ�
	void initializeGame();
	//���� ���� �Լ�
	//������ ���� �Ǹ� ����
	void EndGame(); 
	//���� ����� ����
	void saveResult(); 

	//-----------------------
	//�� �� update �Լ�
	//-----------------------

	//���� ���������� udpate�� �����ϴ� �Լ�
	void turnUpdate();
	//turn�� 1 ���� ��Ų��.
	void increaseTurn(); 
	// �ֽİ� �� ���ο� ������ ������Ʈ �Ѵ�.
	void UpdateStockInfo();
	// player ������ ������Ʈ�Ѵ�.
	void UpdatePlayer();
	//player �Ļ꿩�θ� Ȯ��
	//�Ļ������� true ��ȯ
	bool checkPlayerBankruptcy();

	//-----------------------
	//ȭ�� graphic �Լ�
	//-----------------------

	//main ȭ�� ���
	void showMain(); 
	//��Ʈ������ ȭ�� ���
	void showPortfolio();
	//���� ���� ȭ�� ���
	void showBank();
	//���� ���� ȭ�� ���
	void showInfo(); 
	//menu ȭ�� ���
	void showMenu();

	//-----------------------
	//player ����
	//-----------------------

	//�ż� �Լ�
	void buyStock();
	//�ŵ� �Լ�
	void sellStock();
	//���� �Լ�
	void loan(Loan_Manager& gameLoanManager);
	// ��ȯ �Լ�
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
