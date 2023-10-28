#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QPen>
#include <QFont>
#include <QPoint>
#include <QEvent>
#include <QPushButton>
#include <QLabel>
#include <QImage>
#include <QPixmap>
#include <QPalette>
#include <QBrush>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap background("C:/Users/Sona/Desktop/math_game/pictures/background1");
    background = background.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, background);
    this->setPalette(palette);

    points = new QPushButton("0/5", this);
    points->setGeometry(50,610,83,42);

    restart = new QPushButton("Restart", this);
    restart->setGeometry(133,610,83,42);
    connect(restart, &QPushButton::clicked, this, &MainWindow::handelRestart);

    finish = new QPushButton("Finish", this);
    finish->setGeometry(216,610,83,42);
    connect(finish, &QPushButton::clicked, this, &MainWindow::handelFinish);

    title = new QLabel(this);
    title->setText("Complete the expression!");
    title->setGeometry(100,10,170,40);

    questionLine1 = new element[5];
    questionLine2 = new element[5];
    questionLine3 = new element[5];
    questionLine4 = new element[5];
    questionLine5 = new element[5];

    answerLine1 = new element[4];
    answerLine2 = new element[4];
    answerLine3 = new element[4];
    answerLine4 = new element[4];
    answerLine5 = new element[4];

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initilizeQuestion(element*  questionLine, QString firstOperant, QString operation, QString secondOperant, QString equal, QString result){
    questionLine[0].stringValue = firstOperant;
    questionLine[1].stringValue = operation;
    questionLine[2].stringValue = secondOperant;
    questionLine[3].stringValue = equal;
    questionLine[4].stringValue = result;

}

void MainWindow::coordinates(element& current, int x, int y, int size){
    current.x=x;
    current.y=y;
    current.size=size;
}

void MainWindow::initilizeAnswer(element* answerLine, QString first, QString second, QString third, QString fourth){
    answerLine[0].stringValue = first;
    answerLine[1].stringValue = second;
    answerLine[2].stringValue = third;
    answerLine[3].stringValue = fourth;
}

void MainWindow::paintEvent(QPaintEvent*){
    QPainter painter(this);

    brush[0] = QBrush(Qt::white);
    brush[1] = QBrush(Qt::gray);
    brush[2] = QBrush(Qt::green);
    brush[3] = QBrush(Qt::red);
    painter.setBrush(brush[0]);

    QPen pen;
    pen.setWidth(2);
    pen.setColor(Qt::black);
    painter.setPen(pen);

    QFont font;
    font.setBold(true);
    painter.setFont(font);

    for(int j = 0; j<5;j++){
        for(int i=0; i<5; i++){
            painter.drawRect((i+1)*50, j*110+53, 50, 50);
        }
        for(int i=0; i<4; i++){
            painter.drawRect(i*50+85, (j+1)*110, 35, 35);
        }
    }

    //initialization of the first question
    initilizeQuestion(questionLine1,"1","+","1","=","?");
    questionMarks[0] = 4;
    answers[0] = "2";
    for(int i=0; i<5; i++){
        coordinates(questionLine1[i],(i+1)*50,53,50);
        painter.drawText((i+1.5)*50,83,questionLine1[i].stringValue);
    }
    if (questionLine1[0].answerSelected) {
        painter.setBrush(brush[1]);
        painter.drawRect(questionLine1[questionMarks[0]].x, questionLine1[questionMarks[0]].y, questionLine1[questionMarks[0]].size, questionLine1[questionMarks[0]].size);
        painter.drawText(questionLine1[questionMarks[0]].x+23, questionLine1[questionMarks[0]].y+30,answerLine1[tempIndex[0]].stringValue);
        painter.drawRect(answerLine1[tempIndex[0]].x,answerLine1[tempIndex[0]].y,answerLine1[tempIndex[0]].size, answerLine1[tempIndex[0]].size);
    }
    if(finishClicked){
        if(answerLine1[tempIndex[0]].stringValue==answers[0]){
        painter.setBrush(brush[2]);
        }
        else{
        painter.setBrush(brush[3]);
        }
        painter.drawRect(questionLine1[questionMarks[0]].x, questionLine1[questionMarks[0]].y, questionLine1[questionMarks[0]].size, questionLine1[questionMarks[0]].size);
        painter.drawText(questionLine1[questionMarks[0]].x+23, questionLine1[questionMarks[0]].y+30,answerLine1[tempIndex[0]].stringValue);
        painter.drawRect(answerLine1[tempIndex[0]].x,answerLine1[tempIndex[0]].y,answerLine1[tempIndex[0]].size, answerLine1[tempIndex[0]].size);
    }

    initilizeAnswer(answerLine1,"1","4",answers[0],"3");
    for(int i=0; i<4; i++){
        coordinates(answerLine1[i],i*50+85,110,35);
        painter.drawText(i*50+100,130,answerLine1[i].stringValue);
    }

    //initialization of the second question
    initilizeQuestion(questionLine2,"1","+","?","=","10");
    questionMarks[1] = 2;
    answers[1] = "9";
    for(int i=0; i<5; i++){
        coordinates(questionLine2[i],(i+1)*50,163,50);
        painter.drawText((i+1.5)*50,193,questionLine2[i].stringValue);
    }
    if (questionLine2[0].answerSelected) {
        painter.setBrush(brush[1]);
        painter.drawRect(questionLine2[questionMarks[1]].x, questionLine2[questionMarks[1]].y, questionLine2[questionMarks[1]].size, questionLine2[questionMarks[1]].size);
        painter.drawText(questionLine2[questionMarks[1]].x+23, questionLine2[questionMarks[1]].y+30,answerLine2[tempIndex[1]].stringValue);
        painter.drawRect(answerLine2[tempIndex[1]].x,answerLine2[tempIndex[1]].y,answerLine2[tempIndex[1]].size, answerLine2[tempIndex[1]].size);
    }
    if(finishClicked){
        if(answerLine2[tempIndex[1]].stringValue==answers[1]){
        painter.setBrush(brush[2]);
        }
        else{
        painter.setBrush(brush[3]);
        }
        painter.drawRect(questionLine2[questionMarks[1]].x, questionLine2[questionMarks[1]].y, questionLine2[questionMarks[1]].size, questionLine2[questionMarks[1]].size);
        painter.drawText(questionLine2[questionMarks[1]].x+23, questionLine2[questionMarks[1]].y+30,answerLine2[tempIndex[1]].stringValue);
        painter.drawRect(answerLine2[tempIndex[1]].x,answerLine2[tempIndex[1]].y,answerLine2[tempIndex[1]].size, answerLine2[tempIndex[1]].size);
    }

    initilizeAnswer(answerLine2,"11","0","10",answers[1]);
    for(int i=0; i<4; i++){
       coordinates(answerLine2[i],i*50+85,220,35);
       painter.drawText(i*50+100,240,answerLine2[i].stringValue);
    }

    //initialization of the third question
    initilizeQuestion(questionLine3,"?","-","8","=","10");
    questionMarks[2] = 0;
    answers[2] = "18";
    for(int i=0; i<5; i++){
        coordinates(questionLine3[i],(i+1)*50,273,50);
        painter.drawText((i+1.5)*50,303,questionLine3[i].stringValue);
    }
    if (questionLine3[0].answerSelected) {
        painter.setBrush(brush[1]);
        painter.drawRect(questionLine3[questionMarks[2]].x, questionLine3[questionMarks[2]].y, questionLine3[questionMarks[2]].size, questionLine3[questionMarks[2]].size);
        painter.drawText(questionLine3[questionMarks[2]].x+23, questionLine3[questionMarks[2]].y+30,answerLine3[tempIndex[2]].stringValue);
        painter.drawRect(answerLine3[tempIndex[2]].x,answerLine3[tempIndex[2]].y,answerLine3[tempIndex[2]].size, answerLine3[tempIndex[1]].size);
    }
    if(finishClicked){
        if(answerLine3[tempIndex[2]].stringValue==answers[2]){
        painter.setBrush(brush[2]);
        }
        else{
        painter.setBrush(brush[3]);
        }
        painter.drawRect(questionLine3[questionMarks[2]].x, questionLine3[questionMarks[2]].y, questionLine3[questionMarks[2]].size, questionLine3[questionMarks[2]].size);
        painter.drawText(questionLine3[questionMarks[2]].x+23, questionLine3[questionMarks[2]].y+30,answerLine3[tempIndex[2]].stringValue);
        painter.drawRect(answerLine3[tempIndex[2]].x,answerLine3[tempIndex[2]].y,answerLine3[tempIndex[2]].size, answerLine3[tempIndex[1]].size);
    }
    initilizeAnswer(answerLine3,"12",answers[2],"8","22");
    for(int i=0; i<4; i++){
        coordinates(answerLine3[i],i*50+85,330,35);
        painter.drawText(i*50+100,350,answerLine3[i].stringValue);
    }

    //initialization of the fourth question
    initilizeQuestion(questionLine4,"40","-","19","=","?");
    questionMarks[3] = 4;
    answers[3] = "21";
    for(int i=0; i<5; i++){
        coordinates(questionLine4[i],(i+1)*50,383,50);
        painter.drawText((i+1.5)*50,413,questionLine4[i].stringValue);
    }
    if (questionLine4[0].answerSelected) {
        painter.setBrush(brush[1]);
        painter.drawRect(questionLine4[questionMarks[3]].x, questionLine4[questionMarks[3]].y, questionLine4[questionMarks[3]].size, questionLine4[questionMarks[3]].size);
        painter.drawText(questionLine4[questionMarks[3]].x+23, questionLine4[questionMarks[3]].y+30,answerLine4[tempIndex[3]].stringValue);
        painter.drawRect(answerLine4[tempIndex[3]].x,answerLine4[tempIndex[3]].y,answerLine4[tempIndex[3]].size, answerLine4[tempIndex[3]].size);
    }
    if(finishClicked){
        if(answerLine4[tempIndex[3]].stringValue==answers[3]){
        painter.setBrush(brush[2]);
        }
        else{
        painter.setBrush(brush[3]);
        }
        painter.drawRect(questionLine4[questionMarks[3]].x, questionLine4[questionMarks[3]].y, questionLine4[questionMarks[3]].size, questionLine4[questionMarks[3]].size);
        painter.drawText(questionLine4[questionMarks[3]].x+23, questionLine4[questionMarks[3]].y+30,answerLine4[tempIndex[3]].stringValue);
        painter.drawRect(answerLine4[tempIndex[3]].x,answerLine4[tempIndex[3]].y,answerLine4[tempIndex[3]].size, answerLine4[tempIndex[3]].size);
    }
    initilizeAnswer(answerLine4,"31",answers[3],"41","19");
    for(int i=0; i<4; i++){
        coordinates(answerLine4[i],i*50+85,440,35);
        painter.drawText(i*50+100,460,answerLine4[i].stringValue);
    }

    //initialization of the fifth question
    initilizeQuestion(questionLine5,"8","-","?","=","4");
    questionMarks[4] = 2;
    answers[4] = "4";
    for(int i=0; i<5; i++){
        coordinates(questionLine5[i],(i+1)*50,493,50);
        painter.drawText((i+1.5)*50,523,questionLine5[i].stringValue);
    }
    if (questionLine5[0].answerSelected) {
        painter.setBrush(brush[1]);
        painter.drawRect(questionLine5[questionMarks[4]].x, questionLine5[questionMarks[4]].y, questionLine5[questionMarks[4]].size, questionLine5[questionMarks[4]].size);
        painter.drawText(questionLine5[questionMarks[4]].x+23, questionLine5[questionMarks[4]].y+30,answerLine5[tempIndex[4]].stringValue);
        painter.drawRect(answerLine5[tempIndex[4]].x,answerLine5[tempIndex[4]].y,answerLine5[tempIndex[4]].size, answerLine5[tempIndex[4]].size);
    }
    if(finishClicked){
        if(answerLine5[tempIndex[4]].stringValue==answers[4]){
        painter.setBrush(brush[2]);
        }
        else{
        painter.setBrush(brush[3]);
        }
        painter.drawRect(questionLine5[questionMarks[4]].x, questionLine5[questionMarks[4]].y, questionLine5[questionMarks[4]].size, questionLine5[questionMarks[4]].size);
        painter.drawText(questionLine5[questionMarks[4]].x+23, questionLine5[questionMarks[4]].y+30,answerLine5[tempIndex[4]].stringValue);
        painter.drawRect(answerLine5[tempIndex[4]].x,answerLine5[tempIndex[4]].y,answerLine5[tempIndex[4]].size, answerLine5[tempIndex[4]].size);
    }
    initilizeAnswer(answerLine5,answers[4],"5","18","14");
    for(int i=0; i<4; i++){
        coordinates(answerLine5[i],i*50+85,550,35);
        painter.drawText(i*50+100,570,answerLine5[i].stringValue);
    }
}

void MainWindow::mousePressEvent(QMouseEvent *eventPress)
{
    QPoint pos = eventPress->pos();
    for(int i=0;i<5;i++){

        //first question
        if(pos.x()>answerLine1[i].x && pos.x()<answerLine1[i].x+answerLine1[i].size && pos.y()>answerLine1[i].y && pos.y()<answerLine1[i].y+answerLine1[i].size && !questionLine1[0].answerSelected){
            questionLine1[0].answerSelected = true;
            tempIndex[0] = i;
            if(answerLine1[i].stringValue == answers[0]){
                count++;
            }
        }

        //second question
        if(pos.x()>answerLine2[i].x && pos.x()<answerLine2[i].x+answerLine2[i].size && pos.y()>answerLine2[i].y && pos.y()<answerLine2[i].y+answerLine2[i].size && !questionLine2[0].answerSelected && questionLine1[0].answerSelected){
            questionLine2[0].answerSelected = true;
            tempIndex[1] = i;
            if(answerLine2[i].stringValue == answers[1]){
                count++;
            }
        }

        //third question
        if(pos.x()>answerLine3[i].x && pos.x()<answerLine3[i].x+answerLine3[i].size && pos.y()>answerLine3[i].y && pos.y()<answerLine3[i].y+answerLine3[i].size && !questionLine3[0].answerSelected && questionLine2[0].answerSelected){
            questionLine3[0].answerSelected = true;
            tempIndex[2] = i;
            if(answerLine3[i].stringValue == answers[2]){
                count++;
            }
        }

        //fourth question
        if(pos.x()>answerLine4[i].x && pos.x()<answerLine4[i].x+answerLine4[i].size && pos.y()>answerLine4[i].y && pos.y()<answerLine4[i].y+answerLine4[i].size && !questionLine4[0].answerSelected && questionLine3[0].answerSelected){
            questionLine4[0].answerSelected = true;
            tempIndex[3] = i;
            if(answerLine4[i].stringValue == answers[3]){
                count++;
            }
        }

        //fifth question
        if(pos.x()>answerLine5[i].x && pos.x()<answerLine5[i].x+answerLine5[i].size && pos.y()>answerLine5[i].y && pos.y()<answerLine5[i].y+answerLine5[i].size && !questionLine5[0].answerSelected && questionLine4[0].answerSelected){
            questionLine5[0].answerSelected = true;
            tempIndex[4] = i;
            if(answerLine5[i].stringValue == answers[4]){
                count++;
            }
        }
    }

    update();
}

void MainWindow::handelFinish(){
    points->setText(QString::number(count)+"/5");
    finishClicked = true;
    update();
}

void MainWindow::handelRestart(){
    count=0;
    points->setText(QString::number(count)+"/5");
    finishClicked = false;
    questionLine1[0].answerSelected = false;
    questionLine2[0].answerSelected = false;
    questionLine3[0].answerSelected = false;
    questionLine4[0].answerSelected = false;
    questionLine5[0].answerSelected = false;
    update();
}
