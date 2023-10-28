#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QEvent>
#include <QMouseEvent>
#include <QVector>
#include <QPushButton>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct element{
    int x;
    int y;
    int size;
    QString stringValue;
    bool answerSelected = false;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent *eventPress);
    void initilizeQuestion(element*,QString,QString,QString,QString,QString);
    void coordinates(element&,int,int,int);
    void initilizeAnswer(element*,QString,QString,QString,QString);
    void handelFinish();
    void handelRestart();

private:
    Ui::MainWindow *ui;

    QPushButton* points;
    QPushButton* restart;
    QPushButton* finish;
    QLabel* title;

    element* questionLine1;
    element* questionLine2;
    element* questionLine3;
    element* questionLine4;
    element* questionLine5;

    element* answerLine1;
    element* answerLine2;
    element* answerLine3;
    element* answerLine4;
    element* answerLine5;

    QBrush brush[4];
    int count = 0;
    int tempIndex[5];
    int questionMarks[5];
    QString answers[5];
    bool finishClicked = false;
};
#endif // MAINWINDOW_H
