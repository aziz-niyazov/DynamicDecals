//
// Created by Loïc Barthe on 03/04/2020.
//

#ifndef TEST_QWIDGETMYWIDGET_H
#define TEST_QWIDGETMYWIDGET_H

#include "QWidget"
#include <QTimer>
#include "../Solver/genericsolver.h"
#include "../Solver/mydecalsolver.h"
#include "../ui_mainwindow.h"


class QWidgetMyWidget : public QWidget {

public:

    QWidgetMyWidget();
    void setDecoration(Ui::MainWindow* ui);
    Ui::MainWindow* uiPointer; // Member variable to store the ui pointer

    void addButtons();

    QIcon IconReleasedButton;
    QIcon IconPressedButton1;
    QIcon IconPressedButton2;
    QIcon IconPressedButton3;
    QIcon IconPressedButton4;


protected:
    virtual void internal_preupdate_solve() = 0;
    virtual void innerPaintColorDecaleMouseUpdate() = 0;
    virtual void innerRemoveColorDecale() = 0;
    virtual void internal_solver_init() = 0;

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);


    int timerSet=0;
    bool isSolverPrepared = false;

    void timerHandler();
    bool needUpdate;

    QTimer *timer;

public slots:
    void handleButton1Clicked();
    void handleButton2Clicked();
    void handleButton3Clicked();
    void handleButton4Clicked();




};


#endif //TEST_QWIDGETMYWIDGET_H
