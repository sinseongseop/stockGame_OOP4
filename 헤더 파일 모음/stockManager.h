#ifndef _stockManager_
#define _stockManager_

#include <iostream>
#include <string>
#include <vector>
#include "stock.h"
#include "informationManager.h"

using namespace std;

class stockManager {
private:
	vector<stock> stockDB; // ��� �ֽ��� vector
	vector<informationManager> themaManger; //�׸� �Ŵ��� vector


public: // ������
	stockManager() { };
	stockManager(string fileName1, string fileName2, string fileName3);

public: // �޼ҵ�
	void printStockPrice(); // �� �ֽ��� �� �ְ����� �����ִ� �Լ�
	void updateStockPrice(); // ��� �ְ� ������Ʈ
	void calulateThemainfluence(); //�׸� ������ ���� �ְ� ���� ��� �� �ݿ�
	void cacluateRiverinfluence(int num);// external �������� ���� �ְ� ���� �ݿ�
	void updateNewInfo(); // ��� ������ ������Ʈ ��Ų��.
	
	void printAllStock(); // ��� �ֽĿ� ���� ���� ���(������)
	void printThemaInfo(); // �׸� ������ �����ش�. (����� Ȯ�ο�)


	// setter
	void addStock(string stockName, string stockThema, float stockPrice, string txtFileName);// �ֽ� �Ŵ����� �߰�
	void addthemaManger(string themaName, string fileName); // �׸� �޴����� �߰�
	
	//getter

	stock& getStock(int num); // ���ϴ� �ֽ��� �ϳ� ��ȯ ( ���� ��ȯ ���� ����)
	int getStocksNumber(); //�ֽ� ���� ��ȯ
	informationManager& getThemaManager(int i); //i��° thema manager ��ȯ

};

#endif