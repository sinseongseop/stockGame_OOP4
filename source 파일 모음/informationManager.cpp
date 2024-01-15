#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <random>
#include <fstream>
#include "information.h"
#include "informationManager.h"

using namespace std;

random_device rate_dv2;  // 하드웨어 기반 난수 생성기 (비결정적)
mt19937 influenceGen2(rate_dv2()); // 메르센 트위스터 엔진을 사용한 난수 생성기

//생성자

informationManager::informationManager(string enterpriseName) //기업이름을 제공하는 생성자
{
	this->enterpriseName = enterpriseName;
} 


informationManager::informationManager(string enterpriseName, string txtFileName) { //기업이름, Txt파일 이름을 제공하는 생성자 (파일 정보 읽어오고 이번턴 정보 선택 까지 한번에 실행)
	this->enterpriseName = enterpriseName;
	this->txtFileName = txtFileName;
	saveAllInformation(); // 메모장에 있는 모든 정보 저장
	selectThisTurnInformation(); // 이번턴에 사용할 정보 한개 랜덤 선택
} 

 //메소드

void informationManager::saveAllInformation() { // 메모장을 읽어서 모든 정보를 informationDB에 저장한다.
	string line;
	ifstream myfile(txtFileName); // 파일 객체 생성
	if (myfile.is_open()) {
		char delimiter = ','; //,를 기준으로 토큰 분리
		while (getline(myfile, line)) {
			vector<string> tokens;
			int pos = line.find(delimiter); // 구분자 위치 찾기
			while (pos != string::npos) {
				string token = line.substr(0, pos);
				tokens.push_back(token);
				line = line.substr(pos + 1);// 다음 토큰의 시작 위치
				pos = line.find(delimiter);
			}
			tokens.push_back(line);
			information newInfo = information(tokens[0], tokens[1], tokens[2], stoi(tokens[3]), tokens[4]); // 정보 객체 생성
			informationDB.push_back(newInfo); // 정보를 정보DB에 저장
		}
		myfile.close();
	}else{
		cout << "파일 열기 실패, error 프로그램 종료";
		exit(1);
	}
} 

void informationManager::selectThisTurnInformation() { //이번턴에 쓸 새로운 정보를 하나 랜덤하게 선택한다.
	uniform_int_distribution<int> distribution(0, informationDB.size()-1);
	int random_num = distribution(influenceGen2);
	thisTurnInformation = informationDB[random_num];
	informationDB.erase(informationDB.begin() + random_num);
} 

void informationManager::printInfo() { // 디버깅 용 메소드 (정보 확인)
	cout << "정보 DB 전부 출력 \n";
	for (int i = 0; i < informationDB.size(); i++) {
		informationDB[i].printinfo();
	}
}

void informationManager::printThisTurnInfo() { //(디버깅 용) 메소드 thisTurnInfo의 정보 출력
	thisTurnInformation.printinfo();
}

//기본적인 setter

void informationManager::setEnterpriseName(string enterpriseName) {
	this->enterpriseName = enterpriseName;
}

void informationManager::setTxtFileName(string fileName) {
	this->txtFileName = fileName;
}

//기본적인 getter

string informationManager::getEnterpriseName() {
	return enterpriseName;
}

string informationManager::getTxtFileName() {
	return txtFileName;
}

information& informationManager::getThisTurnInformation() {  //이번턴에 쓸 정보를 전달하는 메소드, 객체를 참조 전달 하는 것임을 주의
	return thisTurnInformation;
}

