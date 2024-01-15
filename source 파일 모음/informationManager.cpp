#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <random>
#include <fstream>
#include "information.h"
#include "informationManager.h"

using namespace std;

random_device rate_dv2;  // �ϵ���� ��� ���� ������ (�������)
mt19937 influenceGen2(rate_dv2()); // �޸��� Ʈ������ ������ ����� ���� ������

//������

informationManager::informationManager(string enterpriseName) //����̸��� �����ϴ� ������
{
	this->enterpriseName = enterpriseName;
} 


informationManager::informationManager(string enterpriseName, string txtFileName) { //����̸�, Txt���� �̸��� �����ϴ� ������ (���� ���� �о���� �̹��� ���� ���� ���� �ѹ��� ����)
	this->enterpriseName = enterpriseName;
	this->txtFileName = txtFileName;
	saveAllInformation(); // �޸��忡 �ִ� ��� ���� ����
	selectThisTurnInformation(); // �̹��Ͽ� ����� ���� �Ѱ� ���� ����
} 

 //�޼ҵ�

void informationManager::saveAllInformation() { // �޸����� �о ��� ������ informationDB�� �����Ѵ�.
	string line;
	ifstream myfile(txtFileName); // ���� ��ü ����
	if (myfile.is_open()) {
		char delimiter = ','; //,�� �������� ��ū �и�
		while (getline(myfile, line)) {
			vector<string> tokens;
			int pos = line.find(delimiter); // ������ ��ġ ã��
			while (pos != string::npos) {
				string token = line.substr(0, pos);
				tokens.push_back(token);
				line = line.substr(pos + 1);// ���� ��ū�� ���� ��ġ
				pos = line.find(delimiter);
			}
			tokens.push_back(line);
			information newInfo = information(tokens[0], tokens[1], tokens[2], stoi(tokens[3]), tokens[4]); // ���� ��ü ����
			informationDB.push_back(newInfo); // ������ ����DB�� ����
		}
		myfile.close();
	}else{
		cout << "���� ���� ����, error ���α׷� ����";
		exit(1);
	}
} 

void informationManager::selectThisTurnInformation() { //�̹��Ͽ� �� ���ο� ������ �ϳ� �����ϰ� �����Ѵ�.
	uniform_int_distribution<int> distribution(0, informationDB.size()-1);
	int random_num = distribution(influenceGen2);
	thisTurnInformation = informationDB[random_num];
	informationDB.erase(informationDB.begin() + random_num);
} 

void informationManager::printInfo() { // ����� �� �޼ҵ� (���� Ȯ��)
	cout << "���� DB ���� ��� \n";
	for (int i = 0; i < informationDB.size(); i++) {
		informationDB[i].printinfo();
	}
}

void informationManager::printThisTurnInfo() { //(����� ��) �޼ҵ� thisTurnInfo�� ���� ���
	thisTurnInformation.printinfo();
}

//�⺻���� setter

void informationManager::setEnterpriseName(string enterpriseName) {
	this->enterpriseName = enterpriseName;
}

void informationManager::setTxtFileName(string fileName) {
	this->txtFileName = fileName;
}

//�⺻���� getter

string informationManager::getEnterpriseName() {
	return enterpriseName;
}

string informationManager::getTxtFileName() {
	return txtFileName;
}

information& informationManager::getThisTurnInformation() {  //�̹��Ͽ� �� ������ �����ϴ� �޼ҵ�, ��ü�� ���� ���� �ϴ� ������ ����
	return thisTurnInformation;
}

