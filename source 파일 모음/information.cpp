#include "information.h"
#include <iostream>
#include <string>
#include <random>

using namespace std;

random_device rate_dv;  // 하드웨어 기반 난수 생성기 (비결정적)
mt19937 influenceGen(rate_dv()); // 메르센 트위스터 엔진을 사용한 난수 생성기

//생성자 

information::information(string infoTxt, string enterpriseName, string thema, int grade, string extermalInfluence) { //생성하면서 변동비율도 한번에 계산해줌
	this->infoTxt = infoTxt;
	this->enterpriseName = enterpriseName;
	this->thema = thema;
	this->grade = grade;
	this->externalInfluence = extermalInfluence;
	calculateChangeRate(); // 변동비율 계산
}

//메소드

void information::calculateChangeRate() { //Own+External 변화 비율 둘 다 계산
	calculateOwnChangeRate();
	calculateExternalChangeRate();
}


void information::calculateOwnChangeRate() {  // Own만 계산
	float changerate = 1;
	if (grade > 0) {
		changerate = 1 + 0.1 * grade; // 정보등급이 +3(최대 이면) 1.3배(30%p 상승)
	}
	else {
		changerate = 1 + 0.1 * grade;// 정보등급이 -3(최대 이면) 0.7배(30%p 하락)
	}
	
	uniform_real_distribution<double> owndis(-0.1, 0.1); // -10%p ~ 10%p 범위에서 랜덤 가중치 부여 
	double ownRandomRate = owndis(influenceGen);
	changerate += ownRandomRate; // 가중치 반영
	this->ownPriveVariance = changerate; // 우리 기업 반영
}

void information::calculateExternalChangeRate() { //External만 계산
	float changerate = 1;
	if (externalInfluence == "pos") {
		//cout << "pos \n"; // 디버깅 확인용
		changerate = 1 + 0.04 * abs(grade); //예시) 정보등급이 3(최대) 이고 Pos(호재)이면 1.12배 상승 (18%p 상승)
	}
	else if (externalInfluence == "neg") {
		//cout << "neg \n"; // 디버깅 확인용
		changerate = 1 - 0.04 * abs(grade); //예시) 정보등급이 3 이고 neg(악재)이면 0.88배로 변화 (6%p 하락)
	}
	else if (externalInfluence == "0") {
		//cout << "테마 정보\n"; // 디버깅 확인용
		return;
	}
	else	{
		cout << "pos와 neg , 0 말고 다른 문자 입력됨 \n"; // 디버깅 확인용
		return;
	}
	uniform_real_distribution<double> otherdis(-0.04, 0.04); // -4%p ~ 4%p 범위에서 랜덤 가중치 부여 
	double otherRandomRate = otherdis(influenceGen);
	changerate += otherRandomRate; // 가중치 반영
	this->externalPriceVariance = changerate; // 외부 기업 반영 
} 

void information::printinfo() { // 디버깅 확인용
	cout << "정보: " << this->infoTxt<<endl;
}


// 기본적인 setter

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

// 기본적인 getter
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




