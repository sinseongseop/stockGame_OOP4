#ifndef _information_
#define _information_

#include <string>

using namespace std;

class information { // ���� Ŭ����

private: //�ʵ�
	string infoTxt; //���� txt
	string enterpriseName; // �����
	string thema; // �׸�
	int grade =0; // ���� ���
	string externalInfluence;// �ٸ� ����� ��ġ�� ����
	float ownPriveVariance=1; // �� ������ ���� ����� ���ݿ� ��ġ�� ���� (price* privceVariance �� ���) , �׸� ������ ��� �� �� �̿�
	float externalPriceVariance = 1; // �� ������ ���� Ÿ ����� ���ݿ� ��ġ�� ����  (price* privceVariance �� ���)

public: //������
	information() {}; // �⺻ ������
	information(string infoTxt, string enterpriseName, string thema, int grade, string extermalInfluence); // ��� ���� �ʵ带 ������ �� �ʱ�ȭ�ϴ� ������
	
public: //�޼ҵ�
	
	void calculateChangeRate(); // ���� ���� ��� (Own+ external �Ѵ� �ѹ��� ���)
	void calculateOwnChangeRate(); // Own�� ���
	void calculateExternalChangeRate(); //External�� ���
	void printinfo(); //���� �ʵ� ������ ��� ���� �ִ� �Լ�(����� Ȯ�ο�)
	

	// �⺻���� setter
	void setInfo(string infoTxt); 
	void setEnterpriseName(string enterpriseName); 
	void setThema(string thema);
	void setGrade(int grade);
	void setExternalInfluence(string externalInfluence);
	void setOwnPriceVariance(string ownPriceVariance);
	void setExternalPriceVariance(float externalPriceVariance);
	
	// �⺻���� getter
	string getInfo();
	string getEnterpriseName();
	string getThema();
	int getGrade();
	string getExternalInfluence();
	float getOwnPriceVariance();
	float getExternalPriceVariance();

};

#endif