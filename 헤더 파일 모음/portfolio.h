#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include <iostream>
#include <string>
#include <vector>
#include "stockManager.h"

using namespace std;

#define UNLOOK_CONDITION 10

struct InvestStruct {
	string item;		// �ֽ� ���� ��
	int NumberOfItem;	// �ֽİ���
	int PurchasingPrice; // ���԰�
	int CurrentPrice;	// ���簡
	int profit;			//�򰡼���						= �� �ݾ� - ���԰� * �� ����
	int EarningsRate;	//���ͷ�						= (���簡 - ���԰�)/���԰� * 100
	int amount;			// �򰡱ݾ�						= ���簡 * ���� �ֽ�
	bool infoUnlock;	//�ش� �ֽ��� ���� ��� ����	(unlock�� ��� true)
														//���� unlock ���� : �ֽ��� UNLOOK_CONDITION �̻� ����, Ȥ�� ������ ����
};

class Portfolio
{

private:
	vector<InvestStruct> v;
	stockManager* stocks; //�ֽ� ���� manager�� ����Ű�� pointer


public:
	//constructor
	//�� ���� ���� ����ü setting
	Portfolio() {};

	//�ֽ� ���� �Լ�
	// �򰡼���, ���ͷ�, �򰡱ݾ� ���
	// ���Կ� �����ϸ� true, �����ϸ� false return
	bool purchase(string item, int NumberOfItem); 

	//�ֽ� �ŵ� �Լ�
	// �ŵ��� �ݾ� return
	// �ֽ� ���� ������ ���� �ŵ��Ϸ� �ϸ� -1 return
	int sell(string item, int NumberOfItem); 

	//�ʱ� ���� �Լ�
	// game manger�κ��� player ������ �ֽĽ��� manager ��ü pointer�� �޾ƿͼ� ����, �����Ѵ�.
	//�ֽ� ����, ������ manager�κ��� �޾ƿͼ� vector�� ����
	void initialize(stockManager* stocks);

	//update �Լ�
	//���� �ֽĽ��� manager pointer�� �����ؼ� �� item�� ���԰� ���� ������Ʈ
	void update();

	//i��° ������ infoUnlook �� ����
	//������ Ȯ���Ͽ� true, false�� �����Ѵ�.
	void checkInfoUnlook(int i);
	
	//i��° ������ infoUnlook �� ����
	void setInfoUnlook(int i, bool val);
	
	//i��° ������ infoUnlook �� ��ȯ
	bool getInfoUnlook(int i);

	//i��° ������ ����ü ��ȯ
	InvestStruct get_ithInvestStruct(int i);
	
};

#endif

