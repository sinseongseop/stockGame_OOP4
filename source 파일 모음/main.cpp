#include <iostream>
#include "player.h"
#include "portfolio.h"
#include "Button.h"
#include "Print.h"
#include "Window.h"
#include "Graph.h"
#include <SFML/Graphics.hpp>
#include "gameManager.h"

gameManager gm;

using namespace std;

// 전역 변수
int checkWindow = 0; // 화면 구분

// 화면 enum (화면 전환 하기 위함)
enum window
{
    HOME,
    PORTFOLIO,
    BANK,
    INFO,
};

// int, float enum
enum numberType
{
    INT,
    FLOAT,
};

// 표 전역 변수
const int numRows = 7;
const int numCols = 6;
const float cellSize = 50.0f;
const int initial_x = 50;
const int initial_y = 85;
int spaceSize[6] = { 160, 160, 120, 80, 60, 60 };
int sum[6] = { };

// 전역 변수
sf::RenderWindow window_H(sf::VideoMode(1200, 630), "Home"); // 창 생성
sf::RenderWindow Window_S;
sf::RenderWindow Window_B;
sf::RenderWindow Window_BInfo;
sf::RenderWindow Window_L; // 대출창
sf::RenderWindow Window_R; // 상환창
Window home; // Home 화면 생성
Window portfolio; // Portfolio 화면 생성
Window sell;
Window buy;
Window info;
Window bank;
Window Binfo;
Window loan;
Window repay;
// 매도, 매수 수량
int num = 0;
int loanAmount = 0;
int repayAmount = 0;

void clearAllWindow();

void render()
{
    clearAllWindow();


    //--------------------------------------------------------------
    // Home 화면
    //--------------------------------------------------------------
    
    // Portfolio 버튼 생성
    home.makeButton(170.0f, 463.0f, 130.0f, 70.0f, 'g', "Portfolio1"); // (위치x, 위치y, 크기x, 크기y)
    home.makeButton(173.0f, 466.0f, 124.0f, 64.0f, 'w', "Portfolio2");
    // Info 버튼 생성
    home.makeButton(450.0f, 463.0f, 130.0f, 70.0f, 'y', "Info1");
    home.makeButton(453.0f, 466.0f, 124.0f, 64.0f, 'w', "Info2");
    // Bank 버튼 생성
    home.makeButton(920.0f, 463.0f, 130.0f, 70.0f, 'r', "Bank1");
    home.makeButton(923.0f, 466.0f, 124.0f, 64.0f, 'w', "Bank2");
    // 중간 구분 선 그리기
    home.makeButton(740.0f, 20.0f, 1.0f, 520.0f, 'b', "MiddleLine");
    // 하단 선 그리기
    home.makeButton(0.0f, 560.0f, 1200.0f, 1.0f, 'b', "BottomLine");
    // Skip 버튼 생성
    home.makeButton(1101.0f, 575.0f, 76.0f, 41.0f, 'w', "Skip2");
    home.makeButton(1098.0f, 572.0f, 82.0f, 47.0f, 'p', "Skip1");
    // 글자 생성
    home.makePrint(70.0f, 20.0f, "< Stock >", 30); // < Stock >
    home.makePrint(780.0f, 20.0f, "< Loan Status >", 30); // < Loan Status >
    home.makePrint(195.0f, 481.0f, "Portfolio", 23); // Portfolio
    home.makePrint(498.0f, 481.0f, "Info", 23); // Information
    home.makePrint(962.0f, 481.0f, "Bank", 23); // Bank
    home.makePrint(780.0f, 130.0f, "Total Amount : " + to_string(gm.get_player().getLoanManager().get_loanAmount() + gm.get_player().getLoanManager().get_interestAmount()), 23); // 총금액
    home.makePrint(780.0f, 240.3f, "Principal : " + to_string(gm.get_player().getLoanManager().get_loanAmount()), 23); // 원금
    home.makePrint(780.0f, 350.0f, "Interest : " + to_string(gm.get_player().getLoanManager().get_interestAmount()), 23); // 현재이자

    int amount_sum = 0;
    for(int i=0 ;i<gm.get_stockManager().getStocksNumber(); i++)
        amount_sum += gm.get_player().getPortfoilo().get_ithInvestStruct(i).amount;

    home.makePrint(50, 575, "Asset :" + to_string(amount_sum + gm.get_player().getAsset()), 30); // Asset
    home.makePrint(450, 575, "Cash : " + to_string(gm.get_player().getAsset()), 30); // Cash

    if(gm.get_round() < 10)
        home.makePrint(980.0f, 575.0f, gm.get_round(), 30, INT, "round"); // round
    else
        home.makePrint(960.0f, 575.0f, gm.get_round(), 30, INT, "round"); // round

    home.makePrint(1000, 575, "Round", 30); // round
    home.makePrint(1120.0f, 580.0f, "Skip", 23); // Skip

    // Home 표 생성
    vector<int> spaceSize1 = { 140, 140, 160, 80, 60, 60 }; // 칸 너비 설정
    home.makeGraph(50, 85, 6, 7, spaceSize1, 50); // 표 생성

    // Home 표 글자 출력
    vector<int> space = { 30, 15, 13, 10, 15, 13 }; // 칼럼마다 글자 시작 위치 설정
    home.getGraph().printText(0, 0, "Company", space);
    home.getGraph().printText(1, 0, "Current Price", space);
    home.getGraph().printText(2, 0, "Fluctuation Rate", space);
    home.getGraph().printText(3, 0, "Number", space);
    for (int i = 1; i < home.getGraph().getY(); i++) {
        home.getGraph().printText(4, i, "Sell", space);
    }
    for (int i = 1; i < home.getGraph().getY(); i++) {
        home.getGraph().printText(5, i, "Buy", space);
    }
    // Home 표 버튼 생성
    for (int i = 1; i <= 6; i++) {
        home.getGraph().setButton_s(4, i);
        home.getGraph().setButton_b(5, i);
    }

    //차트의 값 출력
    for (int i = 0; i < gm.get_stockManager().getStocksNumber(); i++) {
        home.getGraph().printText(0, i+1, gm.get_stockManager().getStock(i).getStockName(), space);
        home.getGraph().printText(1, i+1, to_string(gm.get_stockManager().getStock(i).getStockPrice()), space);
        home.getGraph().printText(2, i+1, to_string((int)gm.get_stockManager().getStock(i).getFluctuationRate()) + "%", space);
        home.getGraph().printText(3, i + 1, to_string(gm.get_player().getPortfoilo().get_ithInvestStruct(i).NumberOfItem), space);
    }






    //--------------------------------------------------------------
    // Portfolio 화면
    //--------------------------------------------------------------
    
    // Home 버튼 생성
    portfolio.makeButton(1050.0f, 20.0f, 130.0f, 70.0f, 'B', "Home1"); // (위치x, 위치y, 크기x, 크기y)
    portfolio.makeButton(1053.0f, 23.0f, 124.0f, 64.0f, 'w', "Home2");
    // 글자 생성
    portfolio.makePrint(1080.0f, 33.0f, "Home", 30); // Home
    portfolio.makePrint(70.0f, 20.0f, "< Portfolio >", 30); // < Stock >

    // Portfolio 표 생성
    vector<int> spaceSize_p = { 140, 90, 160, 140, 140, 140 }; // 칸 너비 설정
    portfolio.makeGraph(190, 120, 6, 7, spaceSize_p, 50); // 표 생성

    // Portfolio 표 글자 출력
    vector<int> space_p = { 30, 15, 28, 10, 45, 35 }; // 칼럼마다 글자 시작 위치 설정
    portfolio.getGraph().printText(0, 0, "Company", space_p);
    portfolio.getGraph().printText(1, 0, "Number", space_p);
    portfolio.getGraph().printText(2, 0, "Buying Price", space_p);
    portfolio.getGraph().printText(3, 0, "Rate of Return", space_p);
    portfolio.getGraph().printText(4, 0, "Profit", space_p);
    portfolio.getGraph().printText(5, 0, "Amount", space_p);

    for (int i = 0; i < gm.get_stockManager().getStocksNumber(); i++) {
        InvestStruct buf;
        buf = gm.get_player().getPortfoilo().get_ithInvestStruct(i);
        portfolio.getGraph().printText(0, i + 1, buf.item, space);
        portfolio.getGraph().printText(1, i + 1, to_string(buf.NumberOfItem), space);
        portfolio.getGraph().printText(2, i + 1, to_string(buf.PurchasingPrice), space);
        portfolio.getGraph().printText(3, i + 1, to_string(buf.EarningsRate) + "%", space);
        portfolio.getGraph().printText(4, i + 1, to_string(buf.profit), space);
        portfolio.getGraph().printText(5, i + 1, to_string(buf.amount), space);
    }


    //--------------------------------------------------------------
    // Sell 화면
    //--------------------------------------------------------------
    
    // Sell 버튼 생성
    sell.makeButton(270.0f, 300.0f, 80.0f, 50.0f, 'p', "Sell1"); // (위치x, 위치y, 크기x, 크기y)
    sell.makeButton(273.0f, 303.0f, 74.0f, 44.0f, 'w', "Sell2");
    // 글자 생성
    sell.makePrint(70.0f, 30.0f, "Company : ", 20);
    sell.makePrint(70.0f, 80.0f, "Current Price : ", 20);
    sell.makePrint(70.0f, 130.0f, "Number : ", 20);
    sell.makePrint(70.0f, 180.0f, "Number of Selling : ", 20);
    sell.makePrint(296.0f, 312.0f, "Sell", 20);
    sell.makePrint(285.0f, 183.0f, num, 20, INT, "number");


    //--------------------------------------------------------------
    // Buy 화면
    //--------------------------------------------------------------
        // buy 버튼 생성
    buy.makeButton(270.0f, 300.0f, 80.0f, 50.0f, 'p', "Buy1"); // (위치x, 위치y, 크기x, 크기y)
    buy.makeButton(273.0f, 303.0f, 74.0f, 44.0f, 'w', "Buy2");
    // 글자 생성
    buy.makePrint(70.0f, 30.0f, "Company : ", 20);
    buy.makePrint(70.0f, 80.0f, "Current Price : ", 20);
    buy.makePrint(70.0f, 130.0f, "Number : ", 20);
    buy.makePrint(70.0f, 180.0f, "Number of Buying : ", 20);
    buy.makePrint(294.0f, 312.0f, "Buy", 20);
    buy.makePrint(285.0f, 183.0f, num, 20, INT, "number");

    //--------------------------------------------------------------
    // Info 화면
    //--------------------------------------------------------------
    int infoFontSize = 17;
    int titleFontSize = 23;
    int buyFontSize = 14;
    float titleX = 50.f;
    float infoX = 70.f;
    float buyX = 150.f;
    // 버튼 생성
    info.makeButton(1050.0f, 20.0f, 130.0f, 70.0f, 'B', "Home1"); // (위치x, 위치y, 크기x, 크기y)
    info.makeButton(1053.0f, 23.0f, 124.0f, 64.0f, 'w', "Home2");
    info.makeButton(buyX, 280.0f, 50.0f, 20.0f, 'c', "Buy1"); //(위치x, 위치y, 크기x, 크기y)
    info.makeButton(buyX + 3.f, 280.0f + 3.f, 50.0f - 6.0f, 20.0f - 6.0f, 'w', "Buy2"); //(위치x, 위치y, 크기x, 크기y)
    info.makeButton(buyX, 320.0f, 50.0f, 20.0f, 'c', "Buy3"); //(위치x, 위치y, 크기x, 크기y)
    info.makeButton(buyX + 3.f, 320.0f + 3.f, 50.0f - 6.0f, 20.0f - 6.0f, 'w', "Buy4"); //(위치x, 위치y, 크기x, 크기y)
    info.makeButton(buyX, 360.0f, 50.0f, 20.0f, 'c', "Buy5"); //(위치x, 위치y, 크기x, 크기y)
    info.makeButton(buyX + 3.f, 360.0f + 3.f, 50.0f - 6.0f, 20.0f - 6.0f, 'w', "Buy6"); //(위치x, 위치y, 크기x, 크기y)
    info.makeButton(buyX, 400.0f, 50.0f, 20.0f, 'c', "Buy7"); //(위치x, 위치y, 크기x, 크기y)
    info.makeButton(buyX + 3.f, 400.0f + 3.f, 50.0f - 6.0f, 20.0f - 6.0f, 'w', "Buy8"); //(위치x, 위치y, 크기x, 크기y)
    info.makeButton(buyX, 440.0f, 50.0f, 20.0f, 'c', "Buy9"); //(위치x, 위치y, 크기x, 크기y)
    info.makeButton(buyX + 3.f, 440.0f + 3.f, 50.0f - 6.0f, 20.0f - 6.0f, 'w', "Buy10"); //(위치x, 위치y, 크기x, 크기y)
    info.makeButton(buyX, 480.0f, 50.0f, 20.0f, 'c', "Buy11"); //(위치x, 위치y, 크기x, 크기y)
    info.makeButton(buyX + 3.f, 480.0f + 3.f, 50.0f - 6.0f, 20.0f - 6.0f, 'w', "Buy12"); //(위치x, 위치y, 크기x, 크기y)
    // 글자 생성
    info.makePrint(1080.0f, 33.0f, "Home", 30); // Home
    info.makePrint(20.f, 10.f, "-- INFO --", 30);
    info.makePrint(titleX, 60.f, "[ GENERAL ]", titleFontSize);
    info.makePrint(infoX, 100.f, "Info1 : " + gm.get_stockManager().getThemaManager(0).getThisTurnInformation().getInfo(), infoFontSize);
    info.makePrint(infoX, 140.f, "Info2 : " + gm.get_stockManager().getThemaManager(1).getThisTurnInformation().getInfo(), infoFontSize);
    info.makePrint(infoX, 180.f, "Info3 : " + gm.get_stockManager().getThemaManager(2).getThisTurnInformation().getInfo(), infoFontSize);
    info.makePrint(titleX, 240.f, "[ENTERPRISE]", titleFontSize);
    info.makePrint(infoX, 520.f, "Purchase Token : ", 15);
    if(gm.get_infoPurchase())
        info.makePrint(infoX + 115.0f, 520.f, "0", 15);
    else
        info.makePrint(infoX + 115.0f, 520.f, "1", 15);

    info.makePrint(infoX, 280.f, "A_BIO :", 20);
    info.makePrint(infoX, 320.f, "B_BIO :", 20);
    info.makePrint(infoX, 360.f, "A_Food :", 20);
    info.makePrint(infoX, 400.f, "B_Food :", 20);
    info.makePrint(infoX, 440.f, "A_IT : ", 20);
    info.makePrint(infoX, 480.f, "B_IT : ", 20);
    for (int i = 0; i < 6; i++) { // buy 버튼 위 텍스트
        if(gm.get_player().getPortfoilo().get_ithInvestStruct(i).infoUnlock == false)
            info.makePrint(buyX + 12.f, 280 + 40 * i,"lock", buyFontSize);
        else {
            info.makePrint(buyX + 6.f, 280 + 40 * i, "unlock", buyFontSize);
            info.makePrint(buyX + 60.f, 280 + 40 * i, gm.get_stockManager().getStock(i).getInfo().getInfo(), buyFontSize);
        }
    }

    //--------------------------------------------------------------
    // BInfo 화면
    //--------------------------------------------------------------
    // 버튼 생성
    Binfo.makeButton(260.0f, 260.0f, 80.0f, 50.0f, 'p', "Yes1");
    Binfo.makeButton(263.0f, 263.0f, 74.0f, 44.0f, 'w', "Yes2");
    // 글자 생성
    Binfo.makePrint(170.f, 60.f, "Cost : " + to_string(INFO_PURCHASING_PRICE), 40);
    Binfo.makePrint(180.f, 140.f, "Purchase?", 60);
    Binfo.makePrint(282.f, 268.f, "Yes", 25);

    //--------------------------------------------------------------
    // bank 화면
    //--------------------------------------------------------------
    int bankFontSize = 20;
    int bottomFontSize = 23;
    float bankX1 = 410.f;
    float bankX2 = 650.f;
    // 버튼 생성
    bank.makeButton(1050.0f, 20.0f, 130.0f, 70.0f, 'B', "Home1"); // (위치x, 위치y, 크기x, 크기y)
    bank.makeButton(1053.0f, 23.0f, 124.0f, 64.0f, 'w', "Home2");
    bank.makeButton((window_H.getSize().x - 200.0f) / 2, 470.0f, 90.0f, 40.0f, 'p', "Loan1");
    bank.makeButton((window_H.getSize().x - 200.0f) / 2 + 3.f, 473.0f, 84.0f, 34.0f, 'w', "Loan2");
    bank.makeButton((window_H.getSize().x + 40.0f) / 2, 470.0f, 90.0f, 40.0f, 'p', "Repay1");
    bank.makeButton((window_H.getSize().x + 40.0f) / 2 + 3.f, 473.0f, 84.0f, 34.0f, 'w', "Repay2");
    // 중간 선 그리기
    bank.makeButton(290.0f, 310.0f, 600.0f, 1.0f, 'b', "MiddleLine");
    // 텍스트 생성
    bank.makePrint(1080.0f, 33.0f, "Home", 30); // Home
    bank.makePrint(bankX1, 60.f, "Toatal Loan Amount", bankFontSize); // 총 대출 금액
    bank.makePrint(bankX1, 110.f, "Principle", bankFontSize); // 원금
    bank.makePrint(bankX1, 160.f, "Interest", bankFontSize); // 이자
    bank.makePrint(bankX1, 210.f, "Interest Rate", bankFontSize); // 이자율
    bank.makePrint(bankX1, 260.f, "Deadline", bankFontSize); // deadline
    bank.makePrint(bankX1, 330.f, "Remaining\nLoanable Amount", bankFontSize); // 남은 대출 가능 금액
    bank.makePrint(bankX1, 400.f, "Applied Interest Rate", bankFontSize); // 적용 이자율

    bank.makePrint(bankX2, 60.f, to_string(gm.get_player().getLoanManager().get_loanAmount() + gm.get_player().getLoanManager().get_interestAmount()), bankFontSize); // 총 대출 금액
    bank.makePrint(bankX2, 110.f, to_string(gm.get_player().getLoanManager().get_loanAmount()), bankFontSize); // 원금
    bank.makePrint(bankX2, 160.f, to_string(gm.get_player().getLoanManager().get_interestAmount()), bankFontSize); // 이자
    bank.makePrint(bankX2, 210.f, to_string(gm.get_player().getLoanManager().get_interestRate()) + "%", bankFontSize); // 이자율

    if(gm.get_player().getCheckLoan())
        bank.makePrint(bankX2, 260.f, to_string(gm.get_player().getLoanManager().get_deadline()) + " turn", bankFontSize); // deadline
    else
        bank.makePrint(bankX2, 260.f, "NULL", bankFontSize);

    bank.makePrint(bankX2, 340.f, to_string(gm.get_player().getLoanManager().get_possibleLoanAmount()), bankFontSize); // 남은 대출 가능 금액
    bank.makePrint(bankX2, 400.f, to_string(gm.get_player().getLoanManager().get_interestRate() + 5) + "%", bankFontSize); // 적용 이자율
    bank.makePrint(522.0f, 478.0f, "LOAN", bankFontSize); // 대출 버튼 위에 텍스트 출력
    bank.makePrint(636.0f, 478.0f, "REPAY", bankFontSize); // 상환 버튼 위에 텍스트 출력


    //--------------------------------------------------------------
    // Loan 화면
    //--------------------------------------------------------------
    float loanX1 = 100.f;
    float loanX2 = 400.f;
// 버튼 생성
    loan.makeButton(260.0f, 300.0f, 80.0f, 50.0f, 'p', "Loan1");
    loan.makeButton(263.0f, 303.0f, 74.0f, 44.0f, 'w', "Loan2");

    loan.makeButton(40.0f, 212.0f, 160.0f, 40.0f, 'y', "10,000_1");
    loan.makeButton(43.0f, 215.0f, 154.0f, 34.0f, 'w', "10,000_1");
    loan.makeButton(220.0f, 212.0f, 160.0f, 40.0f, 'y', "100,000_1");
    loan.makeButton(223.0f, 215.0f, 154.0f, 34.0f, 'w', "100,000_2");
    loan.makeButton(400.0f, 212.0f, 160.0f, 40.0f, 'y', "1,000,000_1");
    loan.makeButton(403.0f, 215.0f, 154.0f, 34.0f, 'w', "1,000,000_2");

    // 텍스트 생성
    loan.makePrint(276, 308, "Loan", 25); // Loan
    loan.makePrint(loanX1, 50.f, "Remaining Loanable Amount :", bankFontSize); // 남은 대출 가능 금액
    loan.makePrint(loanX1, 100.f, "Applied Interest Rate :", bankFontSize); // 적용 이자율
    loan.makePrint(loanX1, 150.f, "Requested Loan Amount :", bankFontSize); // 대출 희망 금액
    loan.makePrint(loanX2, 50.f, to_string(gm.get_player().getLoanManager().get_possibleLoanAmount()), bankFontSize); // 남은 대출 가능 금액
    loan.makePrint(loanX2, 100.f, to_string(gm.get_player().getLoanManager().get_interestRate() + 5) + "%", bankFontSize); // 적용 이자율

    loan.makePrint(70, 215, "+ 10,000", 25); // 남은 대출 가능 금액
    loan.makePrint(245, 215, "+ 100,000", 25); // 적용 이자율
    loan.makePrint(415, 215, "+ 1,000,000", 25); // 갚아야 할 총액
    loan.makePrint(loanX2, 150.f, loanAmount, bankFontSize, INT, "loanAmount"); // 갚아야 할 총액

    //--------------------------------------------------------------
    // Repay 화면
    //--------------------------------------------------------------
    // 버튼 생성
    repay.makeButton(260.0f, 300.0f, 80.0f, 50.0f, 'p', "Repay1");
    repay.makeButton(263.0f, 303.0f, 74.0f, 44.0f, 'w', "Repay2");

    repay.makeButton(40.0f, 212.0f, 160.0f, 40.0f, 'y', "10,000_1");
    repay.makeButton(43.0f, 215.0f, 154.0f, 34.0f, 'w', "10,000_1");
    repay.makeButton(220.0f, 212.0f, 160.0f, 40.0f, 'y', "100,000_1");
    repay.makeButton(223.0f, 215.0f, 154.0f, 34.0f, 'w', "100,000_2");
    repay.makeButton(400.0f, 212.0f, 160.0f, 40.0f, 'y', "1,000,000_1");
    repay.makeButton(403.0f, 215.0f, 154.0f, 34.0f, 'w', "1,000,000_2");

    // 텍스트 생성
    repay.makePrint(269, 308, "Repay", 25); // Repay
    repay.makePrint(loanX1, 50.f, "Principle :", bankFontSize); // 남은 대출 원금
    repay.makePrint(loanX1, 100.f, "Interest :", bankFontSize); // 남은 이자액
    repay.makePrint(loanX1, 150.f, "Requested Repay Amount :", bankFontSize); // 상환 희망 금액
    repay.makePrint(loanX2, 50.f, to_string(gm.get_player().getLoanManager().get_loanAmount()), bankFontSize); // 남은 대출 원금
    repay.makePrint(loanX2, 100.f, to_string(gm.get_player().getLoanManager().get_interestAmount()), bankFontSize); // 남은 대출 이자액

    repay.makePrint(70, 215, "+ 10,000", 25); // 남은 대출 가능 금액
    repay.makePrint(245, 215, "+ 100,000", 25); // 적용 이자율
    repay.makePrint(415, 215, "+ 1,000,000", 25); // 갚아야 할 총액
    repay.makePrint(loanX2, 150.f, repayAmount, bankFontSize, INT, "repayAmount"); // 상환액
}

void display_repay()
{
    // 화면에 그리기------------------------------------------------------------------------
    Window_R.clear(sf::Color::White);
    // 폰트 로드
    sf::Font font;
    if (!font.loadFromFile("tuffy.ttf")) {
        // 폰트를 로드할 수 없는 경우 처리
        cout << "Font Error" << endl;
        exit(1);
    }
    // Sell화면 클래스 그리기    
    // 버튼 그리기
    for (int i = 0; i < repay.getSizeOfV_Button(); i++) {
        Window_R.draw(repay.getButton(i).getButton());
    }
    // 글자 그리기
    for (int i = 0; i < repay.getSizeOfV_Print(); i++) {
        sf::Text text(repay.getPrint(i).getMessage(), font, repay.getPrint(i).getSize()); // 정보 구매 버튼 위 텍스트
        text.setPosition(repay.getPrint(i).getX(), repay.getPrint(i).getY());
        text.setFillColor(sf::Color::Black);
        Window_R.draw(text);
    }
}

void display_loan()
{
    // 화면에 그리기------------------------------------------------------------------------
    Window_L.clear(sf::Color::White);
    // 폰트 로드
    sf::Font font;
    if (!font.loadFromFile("tuffy.ttf")) {
        // 폰트를 로드할 수 없는 경우 처리
        cout << "Font Error" << endl;
        exit(1);
    }
    // Sell화면 클래스 그리기    
    // 버튼 그리기
    for (int i = 0; i < loan.getSizeOfV_Button(); i++) {
        Window_L.draw(loan.getButton(i).getButton());
    }
    // 글자 그리기
    for (int i = 0; i < loan.getSizeOfV_Print(); i++) {
        sf::Text text(loan.getPrint(i).getMessage(), font, loan.getPrint(i).getSize()); // 정보 구매 버튼 위 텍스트
        text.setPosition(loan.getPrint(i).getX(), loan.getPrint(i).getY());
        text.setFillColor(sf::Color::Black);
        Window_L.draw(text);
    }
}

void display_Binfo()
{
    // 화면에 그리기------------------------------------------------------------------------
    Window_BInfo.clear(sf::Color::White);
    // 폰트 로드
    sf::Font font;
    if (!font.loadFromFile("tuffy.ttf")) {
        // 폰트를 로드할 수 없는 경우 처리
        cout << "Font Error" << endl;
        exit(1);
    }
    // Sell화면 클래스 그리기    
    // 버튼 그리기
    for (int i = 0; i < Binfo.getSizeOfV_Button(); i++) {
        Window_BInfo.draw(Binfo.getButton(i).getButton());
    }
    // 글자 그리기
    for (int i = 0; i < Binfo.getSizeOfV_Print(); i++) {
        sf::Text text(Binfo.getPrint(i).getMessage(), font, Binfo.getPrint(i).getSize()); // 정보 구매 버튼 위 텍스트
        text.setPosition(Binfo.getPrint(i).getX(), Binfo.getPrint(i).getY());
        text.setFillColor(sf::Color::Black);
        Window_BInfo.draw(text);
    }
}

void display_sell()
{
    // 화면에 그리기------------------------------------------------------------------------
    Window_S.clear(sf::Color::White);
    // 폰트 로드
    sf::Font font;
    if (!font.loadFromFile("tuffy.ttf")) {
        // 폰트를 로드할 수 없는 경우 처리
        cout << "Font Error" << endl;
        exit(1);
    }
    // Sell화면 클래스 그리기    
    // 버튼 그리기
    for (int i = 0; i < sell.getSizeOfV_Button(); i++) {
        Window_S.draw(sell.getButton(i).getButton());
    }
    // 글자 그리기
    for (int i = 0; i < sell.getSizeOfV_Print(); i++) {
        sf::Text text(sell.getPrint(i).getMessage(), font, sell.getPrint(i).getSize()); // 정보 구매 버튼 위 텍스트
        text.setPosition(sell.getPrint(i).getX(), sell.getPrint(i).getY());
        text.setFillColor(sf::Color::Black);
        Window_S.draw(text);
    }
}

void display_buy()
{
    // 화면에 그리기------------------------------------------------------------------------
    Window_B.clear(sf::Color::White);
    // 폰트 로드
    sf::Font font;
    if (!font.loadFromFile("tuffy.ttf")) {
        // 폰트를 로드할 수 없는 경우 처리
        cout << "Font Error" << endl;
        exit(1);
    }
    // Buy화면 클래스 그리기    
    // 버튼 그리기
    for (int i = 0; i < buy.getSizeOfV_Button(); i++) {
        Window_B.draw(buy.getButton(i).getButton());
    }
    // 글자 그리기
    for (int i = 0; i < buy.getSizeOfV_Print(); i++) {
        sf::Text text(buy.getPrint(i).getMessage(), font, buy.getPrint(i).getSize()); // 정보 구매 버튼 위 텍스트
        text.setPosition(buy.getPrint(i).getX(), buy.getPrint(i).getY());
        text.setFillColor(sf::Color::Black);
        Window_B.draw(text);
    }
}

void display()
{
    // 화면에 그리기------------------------------------------------------------------------
    window_H.clear(sf::Color::White);
    // 폰트 로드
    sf::Font font;
    if (!font.loadFromFile("tuffy.ttf")) {
        // 폰트를 로드할 수 없는 경우 처리
        cout << "Font Error" << endl;
        exit(1);
    }
    if (checkWindow == HOME) {
        // Home화면 클래스 그리기    
        // Home 표 그리기
        // 가로 선 그리기
        for (int i = 0; i <= home.getGraph().getY(); ++i) {
            window_H.draw(home.getGraph().getLine_H(i));
        }
        // 세로 선 그리기
        for (int j = 0; j <= home.getGraph().getX(); ++j) {
            window_H.draw(home.getGraph().getLine_V(j));

        }
        //cout << home.getGraph().getPrint(0).getSize() << endl;
        // Home 표 값 출력하기
        for (int i = 0; i < home.getGraph().getSizeOfPrints(); i++) {
            sf::Text text(home.getGraph().getPrint(i).getMessage(), font, home.getGraph().getPrint(i).getSize());
            text.setPosition(home.getGraph().getPrint(i).getX(), home.getGraph().getPrint(i).getY());
            text.setFillColor(sf::Color::Black);
            window_H.draw(text);
        }
        // 버튼 그리기
        for (int i = 0; i < home.getSizeOfV_Button(); i++) {
            window_H.draw(home.getButton(i).getButton());
        }
        // 글자 그리기
        for (int i = 0; i < home.getSizeOfV_Print(); i++) {
            sf::Text text(home.getPrint(i).getMessage(), font, home.getPrint(i).getSize());
            text.setPosition(home.getPrint(i).getX(), home.getPrint(i).getY());
            text.setFillColor(sf::Color::Black);
            window_H.draw(text);
        }
    }
    else if (checkWindow == PORTFOLIO) {
        // Portfolio화면 클래스 그리기    
        window_H.clear(sf::Color::White);
        // 버튼 그리기
        for (int i = 0; i < portfolio.getSizeOfV_Button(); i++) {
            window_H.draw(portfolio.getButton(i).getButton());
        }
        // 글자 그리기
        for (int i = 0; i < portfolio.getSizeOfV_Print(); i++) {
            sf::Text text(portfolio.getPrint(i).getMessage(), font, portfolio.getPrint(i).getSize());
            text.setPosition(portfolio.getPrint(i).getX(), portfolio.getPrint(i).getY());
            text.setFillColor(sf::Color::Black);
            window_H.draw(text);
        }
    // Portfolio 표 그리기
        // 가로 선 그리기
        for (int i = 0; i <= portfolio.getGraph().getY(); ++i) {
            window_H.draw(portfolio.getGraph().getLine_H(i));
        }
        // 세로 선 그리기
        for (int j = 0; j <= portfolio.getGraph().getX(); ++j) {
            window_H.draw(portfolio.getGraph().getLine_V(j));

        }
        // Portfolio 표 값 출력하기
        for (int i = 0; i < portfolio.getGraph().getSizeOfPrints(); i++) {
            sf::Text text(portfolio.getGraph().getPrint(i).getMessage(), font, portfolio.getGraph().getPrint(i).getSize());
            text.setPosition(portfolio.getGraph().getPrint(i).getX(), portfolio.getGraph().getPrint(i).getY());
            text.setFillColor(sf::Color::Black);
            window_H.draw(text);
        }
    }
    else if (checkWindow == INFO) {
        // Info화면 클래스 그리기
        window_H.clear(sf::Color::White);
        // 버튼 그리기
        for (int i = 0; i < info.getSizeOfV_Button(); i++) {
            window_H.draw(info.getButton(i).getButton());
        }
        // 글자 그리기
        for (int i = 0; i < info.getSizeOfV_Print(); i++) {
            sf::Text text(info.getPrint(i).getMessage(), font, info.getPrint(i).getSize());
            text.setPosition(info.getPrint(i).getX(), info.getPrint(i).getY());
            text.setFillColor(sf::Color::Black);
            window_H.draw(text);
        }
    }
    else if (checkWindow == BANK) {
        // Bank화면 클래스 그리기
        window_H.clear(sf::Color::White);
        // 버튼 그리기
        for (int i = 0; i < bank.getSizeOfV_Button(); i++) {
            window_H.draw(bank.getButton(i).getButton());
        }
        // 글자 그리기
        for (int i = 0; i < bank.getSizeOfV_Print(); i++) {
            sf::Text text(bank.getPrint(i).getMessage(), font, bank.getPrint(i).getSize());
            text.setPosition(bank.getPrint(i).getX(), bank.getPrint(i).getY());
            text.setFillColor(sf::Color::Black);
            window_H.draw(text);
        }
    }
    // 공통 버튼 그리기
    for (int i = home.getSizeOfV_Button() - 1; i > home.getSizeOfV_Button() - 4; i--) {
        window_H.draw(home.getButton(i).getButton());
    }
    // 공통 글자 그리기
    for (int i = home.getSizeOfV_Print() - 1; i > home.getSizeOfV_Print() - 6; i--) {
        sf::Text text(home.getPrint(i).getMessage(), font, home.getPrint(i).getSize());
        text.setPosition(home.getPrint(i).getX(), home.getPrint(i).getY());
        text.setFillColor(sf::Color::Black);
        window_H.draw(text);
    }
    window_H.display();
}

void event()
{
    while (window_H.isOpen()) {
        sf::Event event;
        while (window_H.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window_H.close();
            }
            //----------------------------------------------------------------------------- 버튼 눌렀을 때 새로운 창 띄우기
            if (checkWindow == HOME) {
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    // 마우스 왼쪽 버튼이 눌렸을 때의 마우스 좌표
                    sf::Vector2f mousePosition = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);

                    // Portfolio 버튼 클릭했을 때 Portfolio 화면으로 업데이트
                    if (home.findButton("Portfolio1").clickButton(mousePosition)) {
                        checkWindow = PORTFOLIO;
                    }

                    // Info 버튼 클릭했을 때 Info 화면 띄우기
                    if (home.findButton("Info1").clickButton(mousePosition)) {
                        checkWindow = INFO;
                    }

                    // Bank 버튼 클릭했을 때 Bank 화면 띄우기
                    if (home.findButton("Bank1").clickButton(mousePosition)) {
                        checkWindow = BANK;
                    }

                    // Skip 버튼 클릭 시 Home 화면 업데이트
                    if (home.findButton("Skip1").clickButton(mousePosition)) {
                        gm.turnUpdate();
                        
                        //게임 종료 조건 (10턴 초과, 파산)을 체크해서 조건 달성 시 게임 종료, 종료 화면 띄우기
                        if (!gm.get_gameRun()) {
                            //console 출력
                            //cout << "Name : " << gm.get_player().getName() << "\n";
                            if (gm.get_player().getAsset() == 0)
                                cout << "You Bankrupted!!\n\n";
                                
                            else{
                                cout << "Cash : " << gm.get_player().getAsset() << "\n";

                                int sum_amount = 0;
                                for (int i = 0; i < gm.get_stockManager().getStocksNumber(); i++)
                                    sum_amount += gm.get_player().getPortfoilo().get_ithInvestStruct(i).amount;
                                cout << "Investment Amount : " << sum_amount << "\n";
                                cout << "Total asset : " << sum_amount + gm.get_player().getAsset() << "\n";
                            }
                            exit(0);
                        }

                        render();

                        
                    }

                    // 표에서 Sell, Buy 버튼 클릭했을 때 매수, 매도 창 띄우기
                    num = 0;
                    for (int i = 0; i < 6; i++) {
                        if (home.getGraph().clickGraph(mousePosition, i, 0)) {
                            Window_S.create(sf::VideoMode(600, 400), "Sell");

                            //선택 기업 정보 출력
                            render();
                            sell.makePrint(170.0f, 30.0f, gm.get_stockManager().getStock(i).getStockName(), 20);
                            sell.makePrint(190.0f, 80.0f, to_string(gm.get_stockManager().getStock(i).getStockPrice()), 20);
                            sell.makePrint(155.0f, 130.0f, to_string(gm.get_player().getPortfoilo().get_ithInvestStruct(i).NumberOfItem), 20);

                            //왼쪽 세모 생성
                            sf::ConvexShape leftTriangle(3);
                            leftTriangle.setPoint(0, sf::Vector2f(270.f, 215.f));
                            leftTriangle.setPoint(1, sf::Vector2f(250.f, 195.f));
                            leftTriangle.setPoint(2, sf::Vector2f(270.f, 175.f));
                            leftTriangle.setFillColor(sf::Color::Yellow);


                            // 오른쪽 세모 생성
                            sf::ConvexShape rightTriangle(3);
                            rightTriangle.setPoint(0, sf::Vector2f(315.f, 215.f));
                            rightTriangle.setPoint(1, sf::Vector2f(335.f, 195.f));
                            rightTriangle.setPoint(2, sf::Vector2f(315.f, 175.f));
                            rightTriangle.setFillColor(sf::Color::Yellow);


                            while (Window_S.isOpen()) {
                                sf::Event newEvent;
                                while (Window_S.pollEvent(newEvent)) {
                                    if (newEvent.type == sf::Event::Closed) {
                                        Window_S.close();
                                    }
                                    else if (newEvent.type == sf::Event::MouseButtonPressed && newEvent.mouseButton.button == sf::Mouse::Left) {
                                        // 왼쪽 세모를 클릭하면 숫자 감소
                                        sf::Vector2f mousePosition = sf::Vector2f(newEvent.mouseButton.x, newEvent.mouseButton.y);
                                        if (leftTriangle.getGlobalBounds().contains(mousePosition) && num > 0) {
                                            num--;
                                        }
                                        else if (rightTriangle.getGlobalBounds().contains(mousePosition)) {
                                            num++;
                                        }
                                        // Sell버튼 눌렀을 시 창 종료 및 업데이트
                                        if (sell.findButton("Sell1").clickButton(mousePosition)) {
                                            gm.get_player().sell(gm.get_stockManager().getStock(i).getStockName(), num);
                                            num = 0;
                                            render();
                                            Window_S.close();
                                        }
                                    }
                                    sell.findPrint("number").changeNum(num);
                                }
                                display_sell();
                                // 세모 그리기
                                Window_S.draw(leftTriangle);
                                Window_S.draw(rightTriangle);
                                Window_S.display();
                            }
                            
                        }
                        if (home.getGraph().clickGraph(mousePosition, i, 1)) {
                            Window_B.create(sf::VideoMode(600, 400), "Buy");

                            //선택 기업 정보 출력
                            render();
                            buy.makePrint(170.0f, 30.0f, gm.get_stockManager().getStock(i).getStockName(), 20);
                            buy.makePrint(190.0f, 80.0f, to_string(gm.get_stockManager().getStock(i).getStockPrice()), 20);
                            buy.makePrint(155.0f, 130.0f, to_string(gm.get_player().getPortfoilo().get_ithInvestStruct(i).NumberOfItem), 20);


                            //왼쪽 세모 생성
                            sf::ConvexShape leftTriangle(3);
                            leftTriangle.setPoint(0, sf::Vector2f(270.f, 215.f));
                            leftTriangle.setPoint(1, sf::Vector2f(250.f, 195.f));
                            leftTriangle.setPoint(2, sf::Vector2f(270.f, 175.f));
                            leftTriangle.setFillColor(sf::Color::Yellow);


                            // 오른쪽 세모 생성
                            sf::ConvexShape rightTriangle(3);
                            rightTriangle.setPoint(0, sf::Vector2f(315.f, 215.f));
                            rightTriangle.setPoint(1, sf::Vector2f(335.f, 195.f));
                            rightTriangle.setPoint(2, sf::Vector2f(315.f, 175.f));
                            rightTriangle.setFillColor(sf::Color::Yellow);


                            while (Window_B.isOpen()) {
                                sf::Event newEvent;
                                while (Window_B.pollEvent(newEvent)) {
                                    if (newEvent.type == sf::Event::Closed) {
                                        Window_B.close();
                                    }
                                    else if (newEvent.type == sf::Event::MouseButtonPressed && newEvent.mouseButton.button == sf::Mouse::Left) {
                                        // 왼쪽 세모를 클릭하면 숫자 감소
                                        sf::Vector2f mousePosition = sf::Vector2f(newEvent.mouseButton.x, newEvent.mouseButton.y);
                                        if (leftTriangle.getGlobalBounds().contains(mousePosition) && num > 0) {
                                            num--;
                                        }
                                        else if (rightTriangle.getGlobalBounds().contains(mousePosition)) {
                                            num++;
                                        }
                                        // Buy버튼 눌렀을 시 창 종료 및 업데이트
                                        if (buy.findButton("Buy1").clickButton(mousePosition)) {
                                            gm.get_player().purchase(gm.get_stockManager().getStock(i).getStockName(), num, gm.get_stockManager().getStock(i).getStockPrice());
                                            num = 0;
                                            render();
                                            Window_B.close();
                                        }
                                    }
                                    buy.findPrint("number").changeNum(num);
                                }
                                display_buy();
                                // 세모 그리기
                                Window_B.draw(leftTriangle);
                                Window_B.draw(rightTriangle);
                                Window_B.display();
                            }
                        }
                    }

                    //// Bank 버튼 눌렀을 때 Bank 버튼 지우기
                    //if (home.findButton("Bank1").clickButton(mousePosition)) {
                    //    home.removeButton("Bank1");
                    //    home.removeButton("Bank2");
                    //}
                }
            }
            if (checkWindow == PORTFOLIO) {
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    // 마우스 왼쪽 버튼이 눌렸을 때의 마우스 좌표
                    sf::Vector2f mousePosition = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);

                    // Home 버튼 클릭했을 때 Home 화면으로 업데이트
                    if (portfolio.findButton("Home1").clickButton(mousePosition)) {
                        checkWindow = HOME;
                    }
                }
            }
            if (checkWindow == INFO) {
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    // 마우스 왼쪽 버튼이 눌렸을 때의 마우스 좌표
                    sf::Vector2f mousePosition = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);

                    // Home 버튼 클릭했을 때 Home 화면으로 업데이트
                    if (info.findButton("Home1").clickButton(mousePosition)) {
                        checkWindow = HOME;
                    }
                    // Buy 버튼 클릭했을 때 Buy 화면 띄움
                    if (info.findButton("Buy1").clickButton(mousePosition) && !gm.get_infoPurchase() && !gm.get_player().getPortfoilo().getInfoUnlook(0)) {
                         Window_BInfo.create(sf::VideoMode(600, 400), "unlook_Info");

                        while (Window_BInfo.isOpen()) {
                            sf::Event newEvent;
                            while (Window_BInfo.pollEvent(newEvent)) {
                                if (newEvent.type == sf::Event::Closed) {
                                    Window_BInfo.close();
                                }
                                else if (newEvent.type == sf::Event::MouseButtonPressed && newEvent.mouseButton.button == sf::Mouse::Left) {
                                    // Buy버튼 클릭 시 정보 구매
                                    sf::Vector2f mousePosition = sf::Vector2f(newEvent.mouseButton.x, newEvent.mouseButton.y);
                                    if (Binfo.findButton("Yes1").clickButton(mousePosition)) {

                                        gm.get_player().getPortfoilo().setInfoUnlook(0, true);
                                        gm.set_infoPurchase(true);
                                        gm.get_player().setAsset(gm.get_player().getAsset() - INFO_PURCHASING_PRICE);
                                        render();
                                        Window_BInfo.close();

                                    }
                                }
                            }
                            display_Binfo();
                            Window_BInfo.display();
                        }
                    }
                    // Buy 버튼 클릭했을 때 Buy 화면 띄움
                    if (info.findButton("Buy3").clickButton(mousePosition) && !gm.get_infoPurchase() && !gm.get_player().getPortfoilo().getInfoUnlook(1)) {
                        Window_BInfo.create(sf::VideoMode(600, 400), "Buy_Info");
                        while (Window_BInfo.isOpen()) {
                            sf::Event newEvent;
                            while (Window_BInfo.pollEvent(newEvent)) {
                                if (newEvent.type == sf::Event::Closed) {
                                    Window_BInfo.close();
                                }
                                else if (newEvent.type == sf::Event::MouseButtonPressed && newEvent.mouseButton.button == sf::Mouse::Left) {
                                    // Buy버튼 클릭 시 정보 구매
                                    sf::Vector2f mousePosition = sf::Vector2f(newEvent.mouseButton.x, newEvent.mouseButton.y);
                                    if (Binfo.findButton("Yes1").clickButton(mousePosition)) {
                                        gm.get_player().getPortfoilo().setInfoUnlook(1, true);
                                        gm.set_infoPurchase(true);
                                        gm.get_player().setAsset(gm.get_player().getAsset() - INFO_PURCHASING_PRICE);
                                        render();
                                        Window_BInfo.close();
                                    }
                                }
                            }
                            display_Binfo();
                            Window_BInfo.display();
                        }
                    }
                    // Buy 버튼 클릭했을 때 Buy 화면 띄움
                    if (info.findButton("Buy5").clickButton(mousePosition) && !gm.get_infoPurchase() && !gm.get_player().getPortfoilo().getInfoUnlook(2)) {
                        Window_BInfo.create(sf::VideoMode(600, 400), "Buy_Info");
                        while (Window_BInfo.isOpen()) {
                            sf::Event newEvent;
                            while (Window_BInfo.pollEvent(newEvent)) {
                                if (newEvent.type == sf::Event::Closed) {
                                    Window_BInfo.close();
                                }
                                else if (newEvent.type == sf::Event::MouseButtonPressed && newEvent.mouseButton.button == sf::Mouse::Left) {
                                    // Buy버튼 클릭 시 정보 구매
                                    sf::Vector2f mousePosition = sf::Vector2f(newEvent.mouseButton.x, newEvent.mouseButton.y);
                                    if (Binfo.findButton("Yes1").clickButton(mousePosition)) {
                                        gm.get_player().getPortfoilo().setInfoUnlook(2, true);
                                        gm.set_infoPurchase(true);
                                        gm.get_player().setAsset(gm.get_player().getAsset() - INFO_PURCHASING_PRICE);
                                        render();
                                        Window_BInfo.close();
                                    }
                                }
                            }
                            display_Binfo();
                            Window_BInfo.display();
                        }
                    }
                    // Buy 버튼 클릭했을 때 Buy 화면 띄움
                    if (info.findButton("Buy7").clickButton(mousePosition) && !gm.get_infoPurchase() && !gm.get_player().getPortfoilo().getInfoUnlook(3)) {
                        Window_BInfo.create(sf::VideoMode(600, 400), "Buy_Info");
                        while (Window_BInfo.isOpen()) {
                            sf::Event newEvent;
                            while (Window_BInfo.pollEvent(newEvent)) {
                                if (newEvent.type == sf::Event::Closed) {
                                    Window_BInfo.close();
                                }
                                else if (newEvent.type == sf::Event::MouseButtonPressed && newEvent.mouseButton.button == sf::Mouse::Left) {
                                    // Buy버튼 클릭 시 정보 구매
                                    sf::Vector2f mousePosition = sf::Vector2f(newEvent.mouseButton.x, newEvent.mouseButton.y);
                                    if (Binfo.findButton("Yes1").clickButton(mousePosition)) {
                                        gm.get_player().getPortfoilo().setInfoUnlook(3, true);
                                        gm.set_infoPurchase(true);
                                        gm.get_player().setAsset(gm.get_player().getAsset() - INFO_PURCHASING_PRICE);
                                        render();
                                        Window_BInfo.close();
                                    }
                                }
                            }
                            display_Binfo();
                            Window_BInfo.display();
                        }
                    }
                    // Buy 버튼 클릭했을 때 Buy 화면 띄움
                    if (info.findButton("Buy9").clickButton(mousePosition) && !gm.get_infoPurchase() && !gm.get_player().getPortfoilo().getInfoUnlook(4)) {
                        Window_BInfo.create(sf::VideoMode(600, 400), "Buy_Info");
                        while (Window_BInfo.isOpen()) {
                            sf::Event newEvent;
                            while (Window_BInfo.pollEvent(newEvent)) {
                                if (newEvent.type == sf::Event::Closed) {
                                    Window_BInfo.close();
                                }
                                else if (newEvent.type == sf::Event::MouseButtonPressed && newEvent.mouseButton.button == sf::Mouse::Left) {
                                    // Buy버튼 클릭 시 정보 구매
                                    sf::Vector2f mousePosition = sf::Vector2f(newEvent.mouseButton.x, newEvent.mouseButton.y);
                                    if (Binfo.findButton("Yes1").clickButton(mousePosition)) {
                                        gm.get_player().getPortfoilo().setInfoUnlook(4, true);
                                        gm.set_infoPurchase(true);
                                        gm.get_player().setAsset(gm.get_player().getAsset() - INFO_PURCHASING_PRICE);
                                        render();
                                        Window_BInfo.close();
                                    }
                                }
                            }
                            display_Binfo();
                            Window_BInfo.display();
                        }
                    }
                    // Buy 버튼 클릭했을 때 Buy 화면 띄움
                    if (info.findButton("Buy11").clickButton(mousePosition) && !gm.get_infoPurchase() && !gm.get_player().getPortfoilo().getInfoUnlook(5)) {
                        Window_BInfo.create(sf::VideoMode(600, 400), "Buy_Info");
                        while (Window_BInfo.isOpen()) {
                            sf::Event newEvent;
                            while (Window_BInfo.pollEvent(newEvent)) {
                                if (newEvent.type == sf::Event::Closed) {
                                    Window_BInfo.close();
                                }
                                else if (newEvent.type == sf::Event::MouseButtonPressed && newEvent.mouseButton.button == sf::Mouse::Left) {
                                    // Buy버튼 클릭 시 정보 구매
                                    sf::Vector2f mousePosition = sf::Vector2f(newEvent.mouseButton.x, newEvent.mouseButton.y);
                                    if (Binfo.findButton("Yes1").clickButton(mousePosition)) {
                                        gm.get_player().getPortfoilo().setInfoUnlook(5, true);
                                        gm.set_infoPurchase(true);
                                        gm.get_player().setAsset(gm.get_player().getAsset() - INFO_PURCHASING_PRICE);
                                        render();
                                        Window_BInfo.close();
                                    }
                                }
                            }
                            display_Binfo();
                            Window_BInfo.display();
                        }
                    }
                }
            }
            if (checkWindow == BANK) {
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    // 마우스 왼쪽 버튼이 눌렸을 때의 마우스 좌표
                    sf::Vector2f mousePosition = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);

                    // Home 버튼 클릭했을 때 Home 화면으로 업데이트
                    if (bank.findButton("Home1").clickButton(mousePosition)) {
                        checkWindow = HOME;
                    }
                    // Loan 버튼 클릭했을 때 Loan 화면으로 업데이트
                    if (bank.findButton("Loan1").clickButton(mousePosition)) {
                        Window_L.create(sf::VideoMode(600, 400), "Loan");
                        loanAmount = 0;
                        while (Window_L.isOpen()) {
                            sf::Event newEvent;
                            while (Window_L.pollEvent(newEvent)) {
                                if (newEvent.type == sf::Event::Closed) {
                                    Window_L.close();
                                }
                                else if (newEvent.type == sf::Event::MouseButtonPressed && newEvent.mouseButton.button == sf::Mouse::Left) {
                                    // Buy버튼 클릭 시 정보 구매
                                    sf::Vector2f mousePosition = sf::Vector2f(newEvent.mouseButton.x, newEvent.mouseButton.y);
                                    if (loan.findButton("Loan1").clickButton(mousePosition)) {
                                        gm.get_player().loan(loanAmount);
                                            
                                        loanAmount = 0;
                                        render();
                                        Window_L.close();
                                    }
                                    if (loan.findButton("10,000_1").clickButton(mousePosition)) {
                                        loanAmount += 10000;
                                    }
                                    if (loan.findButton("100,000_1").clickButton(mousePosition)) {
                                        loanAmount += 100000;
                                    }
                                    if (loan.findButton("1,000,000_1").clickButton(mousePosition)) {
                                        loanAmount += 1000000;
                                    }
                                }
                                loan.findPrint("loanAmount").changeNum(loanAmount);
                            }
                            display_loan();
                            Window_L.display();
                        }
                    }
                    // Repay 버튼 클릭했을 때 Repay 화면으로 업데이트
                    if (bank.findButton("Repay1").clickButton(mousePosition)) {
                        Window_R.create(sf::VideoMode(600, 400), "Repay");
                        repayAmount = 0;
                        while (Window_R.isOpen()) {
                            sf::Event newEvent;
                            while (Window_R.pollEvent(newEvent)) {
                                if (newEvent.type == sf::Event::Closed) {
                                    Window_R.close();
                                }
                                else if (newEvent.type == sf::Event::MouseButtonPressed && newEvent.mouseButton.button == sf::Mouse::Left) {
                                    // Buy버튼 클릭 시 정보 구매
                                    sf::Vector2f mousePosition = sf::Vector2f(newEvent.mouseButton.x, newEvent.mouseButton.y);
                                    if (repay.findButton("Repay1").clickButton(mousePosition)) {
                                        gm.get_player().repayment(repayAmount);
                                        repayAmount = 0;
                                        render();
                                        Window_R.close();
                                    }
                                    if (repay.findButton("10,000_1").clickButton(mousePosition)) {
                                        repayAmount += 10000;
                                    }
                                    if (repay.findButton("100,000_1").clickButton(mousePosition)) {
                                        repayAmount += 100000;
                                    }
                                    if (repay.findButton("1,000,000_1").clickButton(mousePosition)) {
                                        repayAmount += 1000000;
                                    }
                                }
                                repay.findPrint("repayAmount").changeNum(repayAmount);
                            }
                            display_repay();
                            Window_R.display();
                        }
                    }
                }
            }
        }
        display();
    }
}

void clearAllWindow() {
    home.clear_print();
    portfolio.clear_print();
    sell.clear_print();
    buy.clear_print();
    info.clear_print();
    bank.clear_print();
    Binfo.clear_print();
    loan.clear_print();
    repay.clear_print();
}

int main()
{
    

    gm.initializeGame();
    gm.turnUpdate();



    render();
    event();

	return 0;
}
