#ifndef _information_
#define _information_

#include <string>

using namespace std;

class information { // 정보 클래스

private: //필드
	string infoTxt; //정보 txt
	string enterpriseName; // 기업명
	string thema; // 테마
	int grade =0; // 정보 등급
	string externalInfluence;// 다른 기업에 미치는 영향
	float ownPriveVariance=1; // 이 정보가 본인 기업의 가격에 미치는 영향 (price* privceVariance 로 계산) , 테마 정보의 경우 이 값 이용
	float externalPriceVariance = 1; // 이 정보가 관련 타 기업의 가격에 미치는 영향  (price* privceVariance 로 계산)

public: //생성자
	information() {}; // 기본 생성자
	information(string infoTxt, string enterpriseName, string thema, int grade, string extermalInfluence); // 기업 정보 필드를 생성할 때 초기화하는 생성자
	
public: //메소드
	
	void calculateChangeRate(); // 변동 비율 계산 (Own+ external 둘다 한번에 계산)
	void calculateOwnChangeRate(); // Own만 계산
	void calculateExternalChangeRate(); //External만 계산
	void printinfo(); //내부 필드 정보를 모두 보여 주는 함수(디버깅 확인용)
	

	// 기본적인 setter
	void setInfo(string infoTxt); 
	void setEnterpriseName(string enterpriseName); 
	void setThema(string thema);
	void setGrade(int grade);
	void setExternalInfluence(string externalInfluence);
	void setOwnPriceVariance(string ownPriceVariance);
	void setExternalPriceVariance(float externalPriceVariance);
	
	// 기본적인 getter
	string getInfo();
	string getEnterpriseName();
	string getThema();
	int getGrade();
	string getExternalInfluence();
	float getOwnPriceVariance();
	float getExternalPriceVariance();

};

#endif