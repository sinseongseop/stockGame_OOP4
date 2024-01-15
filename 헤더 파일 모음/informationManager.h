#ifndef _informationManager_
#define _informationManager_

#include <iostream>
#include <string>
#include <vector>
#include "information.h"

using namespace std;

class informationManager {
private: // �ʵ�
	vector<information> informationDB; // ���ӿ��� ���� �� �ִ� ��� ������ ��� ����.
	information thisTurnInformation;  //�̹� �Ͽ� ������ ����
	string enterpriseName; //�����
	string txtFileName; // ������ ����Ǿ��ִ� txt ���ϸ�


public: //������
	informationManager() {};
	informationManager(string enterpriseName); //����̸��� �����ϴ� ������
	informationManager(string enterpriseName, string txtFileName); //����̸�, Txt���� �̸��� �����ϴ� ������ (���� ���� �о���� �̹��� ���� ���� ���� �ѹ��� ����)

public: //�޼ҵ�
	void saveAllInformation(); // �޸����� �о ��� ������ informationDB�� �����Ѵ�.
	void selectThisTurnInformation(); //�̹��Ͽ� �� ���ο� ������ �ϳ� �����ϰ� �����Ѵ�.
	void printInfo(); //���� Ȯ��(����� ��)
	void printThisTurnInfo(); // ThisTurnInfo ������ ���� �ִ� �Լ�(����� Ȯ�ο�)


//�⺻���� setter
	void setEnterpriseName(string enterpriseName);
	void setTxtFileName(string fileName);

//�⺻���� getter

	string getEnterpriseName();
	string getTxtFileName();
	information& getThisTurnInformation(); //�̹��Ͽ� �� ������ �����ϴ� �޼ҵ�, ���� �������� ����

};



#endif