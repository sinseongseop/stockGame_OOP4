#include "information.h"
#include <iostream>
#include <string>
#include <random>

using namespace std;

random_device rate_dv;  // �ϵ���� ��� ���� ������ (�������)
mt19937 influenceGen(rate_dv()); // �޸��� Ʈ������ ������ ����� ���� ������

//������ 

information::information(string infoTxt, string enterpriseName, string thema, int grade, string extermalInfluence) { //�����ϸ鼭 ���������� �ѹ��� �������
	this->infoTxt = infoTxt;
	this->enterpriseName = enterpriseName;
	this->thema = thema;
	this->grade = grade;
	this->externalInfluence = extermalInfluence;
	calculateChangeRate(); // �������� ���
}

//�޼ҵ�

void information::calculateChangeRate() { //Own+External ��ȭ ���� �� �� ���
	calculateOwnChangeRate();
	calculateExternalChangeRate();
}


void information::calculateOwnChangeRate() {  // Own�� ���
	float changerate = 1;
	if (grade > 0) {
		changerate = 1 + 0.1 * grade; // ��������� +3(�ִ� �̸�) 1.3��(30%p ���)
	}
	else {
		changerate = 1 + 0.1 * grade;// ��������� -3(�ִ� �̸�) 0.7��(30%p �϶�)
	}
	
	uniform_real_distribution<double> owndis(-0.1, 0.1); // -10%p ~ 10%p �������� ���� ����ġ �ο� 
	double ownRandomRate = owndis(influenceGen);
	changerate += ownRandomRate; // ����ġ �ݿ�
	this->ownPriveVariance = changerate; // �츮 ��� �ݿ�
}

void information::calculateExternalChangeRate() { //External�� ���
	float changerate = 1;
	if (externalInfluence == "pos") {
		//cout << "pos \n"; // ����� Ȯ�ο�
		changerate = 1 + 0.04 * abs(grade); //����) ��������� 3(�ִ�) �̰� Pos(ȣ��)�̸� 1.12�� ��� (18%p ���)
	}
	else if (externalInfluence == "neg") {
		//cout << "neg \n"; // ����� Ȯ�ο�
		changerate = 1 - 0.04 * abs(grade); //����) ��������� 3 �̰� neg(����)�̸� 0.88��� ��ȭ (6%p �϶�)
	}
	else if (externalInfluence == "0") {
		//cout << "�׸� ����\n"; // ����� Ȯ�ο�
		return;
	}
	else	{
		cout << "pos�� neg , 0 ���� �ٸ� ���� �Էµ� \n"; // ����� Ȯ�ο�
		return;
	}
	uniform_real_distribution<double> otherdis(-0.04, 0.04); // -4%p ~ 4%p �������� ���� ����ġ �ο� 
	double otherRandomRate = otherdis(influenceGen);
	changerate += otherRandomRate; // ����ġ �ݿ�
	this->externalPriceVariance = changerate; // �ܺ� ��� �ݿ� 
} 

void information::printinfo() { // ����� Ȯ�ο�
	cout << "����: " << this->infoTxt<<endl;
}


// �⺻���� setter

void information::setInfo(string infoTxt) {
	this->infoTxt = infoTxt;
}

void information::setEnterpriseName(string enterpriseName) {
	this->enterpriseName = enterpriseName;
}
void information::setThema(string thema) {
	this->thema = thema;
}

void information::setGrade(int grade) {
	this->grade = grade;
}

void information::setExternalInfluence(string externalInfluence) {
	this->externalInfluence = externalInfluence;
}

void information::setOwnPriceVariance(string ownPriceVariance) {
	this->ownPriveVariance = ownPriveVariance;
}

void information::setExternalPriceVariance(float externalPriceVariance) {
	this->externalPriceVariance = externalPriceVariance;
}

// �⺻���� getter
string information::getInfo() {
	return this->infoTxt;
}

string information::getEnterpriseName() {
	return this->enterpriseName;
}

string information::getThema() {
	return this->thema;
}

int information::getGrade() {
	return this->grade;
}

string information::getExternalInfluence() {
	return this->externalInfluence;
}

float information::getOwnPriceVariance() {
	return this->ownPriveVariance;
}

float information::getExternalPriceVariance() {
	return this->externalPriceVariance;
}




