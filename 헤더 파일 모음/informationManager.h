#ifndef _informationManager_
#define _informationManager_

#include <iostream>
#include <string>
#include <vector>
#include "information.h"

using namespace std;

class informationManager {
private: // 필드
	vector<information> informationDB; // 게임에서 나올 수 있는 모든 정보가 담겨 있음.
	information thisTurnInformation;  //이번 턴에 제공될 정보
	string enterpriseName; //기업명
	string txtFileName; // 정보가 저장되어있는 txt 파일명


public: //생성자
	informationManager() {};
	informationManager(string enterpriseName); //기업이름을 제공하는 생성자
	informationManager(string enterpriseName, string txtFileName); //기업이름, Txt파일 이름을 제공하는 생성자 (파일 정보 읽어오고 이번턴 정보 선택 까지 한번에 실행)

public: //메소드
	void saveAllInformation(); // 메모장을 읽어서 모든 정보를 informationDB에 저장한다.
	void selectThisTurnInformation(); //이번턴에 쓸 새로운 정보를 하나 랜덤하게 선택한다.
	void printInfo(); //정보 확인(디버깅 용)
	void printThisTurnInfo(); // ThisTurnInfo 정보를 보여 주는 함수(디버깅 확인용)


//기본적인 setter
	void setEnterpriseName(string enterpriseName);
	void setTxtFileName(string fileName);

//기본적인 getter

	string getEnterpriseName();
	string getTxtFileName();
	information& getThisTurnInformation(); //이번턴에 쓸 정보를 전달하는 메소드, 참조 전달임을 주의

};



#endif