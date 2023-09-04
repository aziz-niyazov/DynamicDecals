//
// Created by Loïc Barthe on 03/04/2020.
//

#include "QWidgetMyWidget.h"
#include <iostream>
#include <QMouseEvent>
#include <QPushButton>
#include <QPainter>
#include <QLabel>
#include <QPixmap>
#include "qwidgetmyicon.h"



QWidgetMyWidget::QWidgetMyWidget () : timerSet(0), QWidget () {

    timer = new QTimer();
    timer->setInterval(1000/30);
    connect(timer, &QTimer::timeout, this, &QWidgetMyWidget::timerHandler);
    //updating each frame at 30fps
    timer->start();

    setAttribute(Qt::WA_AcceptTouchEvents);



}

void setButtonIcon(QPushButton *button, QIcon icon){
    button->setIcon(icon);
    button->setIconSize(QSize(50, 50));
    button->setStyleSheet("border-radius: 10px;");
}

void QWidgetMyWidget::setUiPointer(Ui::MainWindow* ui) {
    uiPointer = ui;

    IconReleasedButton = QIcon("C:/Users/aniyazov/Pictures/interactive_decal_interface/buttonGrey.png");
    IconPressedButton1 = QIcon("C:/Users/aniyazov/Pictures/interactive_decal_interface/Asset 17");
    IconPressedButton2 = QIcon("C:/Users/aniyazov/Pictures/interactive_decal_interface/Asset 17");
    IconPressedButton3 = QIcon("C:/Users/aniyazov/Pictures/interactive_decal_interface/Asset 17");
    IconPressedButton4 = QIcon("C:/Users/aniyazov/Pictures/interactive_decal_interface/Asset 17");


    setButtonIcon(ui->pushButton_1, IconReleasedButton);
    setButtonIcon(ui->pushButton_2, IconReleasedButton);
    setButtonIcon(ui->pushButton_3, IconReleasedButton);
    setButtonIcon(ui->pushButton_4, IconReleasedButton);



    // Connect button signals to respective slots using uiPointer
    connect(ui->pushButton_1, &QPushButton::pressed, this, &QWidgetMyWidget::handleButton1Pressed);
    connect(ui->pushButton_2, &QPushButton::pressed, this, &QWidgetMyWidget::handleButton2Pressed);
    connect(ui->pushButton_3, &QPushButton::pressed, this, &QWidgetMyWidget::handleButton3Pressed);
    connect(ui->pushButton_4, &QPushButton::pressed, this, &QWidgetMyWidget::handleButton4Pressed);

    connect(ui->pushButton_1, &QPushButton::released, this, &QWidgetMyWidget::handleButton1Released);
    connect(ui->pushButton_2, &QPushButton::released, this, &QWidgetMyWidget::handleButton2Released);
    connect(ui->pushButton_3, &QPushButton::released, this, &QWidgetMyWidget::handleButton3Released);
    connect(ui->pushButton_4, &QPushButton::released, this, &QWidgetMyWidget::handleButton4Released);



}

void QWidgetMyWidget::setDecoration(Ui::MainWindow *ui)
{
     uiPointer = ui;

     QString backgroundImagePath = "C:/Users/aniyazov/Pictures/interactive_decal_interface/Asset 23"; // Replace with the path to your image file
     QString stylesheet = QString("background-image: url('%1');").arg(backgroundImagePath);
     uiPointer->background_2->setStyleSheet(stylesheet);
     uiPointer->background_2->setAttribute(Qt::WA_TransparentForMouseEvents);


}
void QWidgetMyWidget::addButtons()
{
//    QPixmap pixmap("C:/Users/aniyazov/Pictures/interactive_decal_interface/buttonGrey"); // Replace with the actual path to your image

//    QLabel *iconLabel = new QLabel(this);
//    iconLabel->setPixmap(pixmap);
//    iconLabel->setAlignment(Qt::AlignCenter);
//    iconLabel->setGeometry(1752,340, iconLabel->width(), iconLabel->height());


//    QPixmap PixmapPressedButton1("C:/Users/aniyazov/Pictures/interactive_decal_interface/Asset 17");
//    QPixmap PixmapPressedButton2("C:/Users/aniyazov/Pictures/interactive_decal_interface/Asset 18");
//    QPixmap PixmapPressedButton3("C:/Users/aniyazov/Pictures/interactive_decal_interface/Asset 19");
//    QPixmap PixmapPressedButton4("C:/Users/aniyazov/Pictures/interactive_decal_interface/Asset 20");
//    QPixmap PixmapReleased("C:/Users/aniyazov/Pictures/interactive_decal_interface/buttonGrey");

    QPixmap PixmapPressedButtonYellow("C:/Users/aniyazov/Pictures/interactive_decal_interface/yellow_on");
    QPixmap PixmapPressedButtonGreen("C:/Users/aniyazov/Pictures/interactive_decal_interface/green_on");
    QPixmap PixmapPressedButtonBlue("C:/Users/aniyazov/Pictures/interactive_decal_interface/blue_on");
    QPixmap PixmapPressedButtonViolet("C:/Users/aniyazov/Pictures/interactive_decal_interface/violet_on");

    QPixmap PixmapReleasedButtonYellow("C:/Users/aniyazov/Pictures/interactive_decal_interface/yellow_off");
    QPixmap PixmapReleasedButtonGreen("C:/Users/aniyazov/Pictures/interactive_decal_interface/green_off");
    QPixmap PixmapReleasedButtonBlue("C:/Users/aniyazov/Pictures/interactive_decal_interface/blue_off");
    QPixmap PixmapReleasedButtonViolet("C:/Users/aniyazov/Pictures/interactive_decal_interface/violet_off");



    QList<QWidgetMyIcon*> myicons;
    for(int i = 0; i < 4; i++){
        QWidgetMyIcon *icon;
        if(i == 0){
//            icon = new QWidgetMyIcon("C:/Users/aniyazov/Pictures/interactive_decal_interface/buttonGrey", 50);
            icon = new QWidgetMyIcon(PixmapReleasedButtonYellow);
        }else if (i==1){
            icon = new QWidgetMyIcon(PixmapReleasedButtonGreen);
        }else if (i==2){
              icon = new QWidgetMyIcon(PixmapReleasedButtonBlue);
        }else if (i==3){
              icon = new QWidgetMyIcon(PixmapReleasedButtonViolet);
        }

        if(icon != NULL){
            icon->setFixedSize(icon->iconLabel->size());
            myicons.append(icon);
            icon->setParent(this);
            qDebug() <<"icon size: "<< icon->size();
        }







        auto x = 1770;
       // auto x = 0;
       // auto y = 342 + (i*107);
        auto y = 300 + (i*107);
        icon->setGeometry(x, y, icon->width(), icon->height());


    //  Connect to signals
        connect(icon, &QWidgetMyIcon::iconPressed, this, [=]() {
            qDebug() << "Mouse pressed on myIcon" << i;
            innerRemoveColorDecale();

            if (i == 0){
                icon->changeIconPixmap(PixmapPressedButtonYellow);
                MyDecalSolver::switchGamutConstraint = true;
            }
            else if (i == 1){
                icon->changeIconPixmap(PixmapPressedButtonGreen);
                MyDecalSolver::switchMinDistConstraint = true;
            }
            else if (i == 2){
                icon->changeIconPixmap(PixmapPressedButtonBlue);
                MyDecalSolver::switchMaxDistConstraint = true;
            }
            else if (i == 3){
                icon->changeIconPixmap(PixmapPressedButtonViolet);
                MyDecalSolver::switchAlignConstraint = true;
            }
            internal_solver_init();
            needUpdate = true;
        });

        connect(icon, &QWidgetMyIcon::iconReleased, this, [=]() {
            qDebug() << "Mouse released on myIcon" <<i;
            if (i == 0){
                icon->changeIconPixmap(PixmapReleasedButtonYellow);
                MyDecalSolver::switchGamutConstraint = false;
            }
            else if (i == 1){
                icon->changeIconPixmap(PixmapReleasedButtonGreen);
                MyDecalSolver::switchMinDistConstraint = false;
            }
            else if (i == 2){
                icon->changeIconPixmap(PixmapReleasedButtonBlue);
                MyDecalSolver::switchMaxDistConstraint = false;
            }
            else if (i == 3){
                icon->changeIconPixmap(PixmapReleasedButtonViolet);
                MyDecalSolver::switchAlignConstraint = false;
            }
//            //set grey icon
//            icon->changeIconPixmap(PixmapReleased);
            internal_solver_init();

            needUpdate = true;

        });
    }



//    QVBoxLayout *layout = new QVBoxLayout(this);
//    layout->addWidget(myIcon);




}




void QWidgetMyWidget::timerHandler()
{
    if(isSolverPrepared and needUpdate){
       // std::cout<<"timer"<<std::endl;
        internal_preupdate_solve();

        innerPaintColorDecaleMouseUpdate();
        needUpdate = false;


    }
}

void QWidgetMyWidget::handleButton1Clicked() {
//    uiPointer->pushButton_1->setChecked(true);
//    uiPointer->pushButton_2->setChecked(false);
//    uiPointer->pushButton_3->setChecked(false);
//    uiPointer->pushButton_4->setChecked(false);



//    QIcon icon("C:/Users/aniyazov/Pictures/interactive_decal_interface/buttonGrey.png");
//    QIcon pressedIcon("C:/Users/aniyazov/Pictures/interactive_decal_interface/Asset 17");

    MyDecalSolver::switchGamutConstraint = !MyDecalSolver::switchGamutConstraint;
    qDebug() << "Button Gamut Clicked!" << MyDecalSolver::switchGamutConstraint;
    internal_solver_init();


//    if(MyDecalSolver::switchGamutConstraint){
//        uiPointer->pushButton_1->setIcon(pressedIcon);
//    }else{
//         uiPointer->pushButton_1->setIcon(icon);
//    }
    // Add your custom code here
}

void QWidgetMyWidget::handleButton2Clicked() {
    MyDecalSolver::switchMinDistConstraint = !MyDecalSolver::switchMinDistConstraint;
    qDebug() << "Button MinDist Clicked!" << MyDecalSolver::switchMinDistConstraint;
    internal_solver_init();
    needUpdate = true;
    // Add your custom code here
}

void QWidgetMyWidget::handleButton3Clicked() {
    MyDecalSolver::switchMaxDistConstraint = !MyDecalSolver::switchMaxDistConstraint;
    qDebug() << "Button MaxDist Clicked!";
    internal_solver_init();
    // Add your custom code here
}

void QWidgetMyWidget::handleButton4Clicked() {
    MyDecalSolver::switchAlignConstraint = !MyDecalSolver::switchAlignConstraint;
    qDebug() << "Button Alignement Clicked!";
    internal_solver_init();
    // Add your custom code here
}

//button pressed

void QWidgetMyWidget::handleButton1Pressed()
{
    uiPointer->pushButton_1->setIcon(IconPressedButton1);
    MyDecalSolver::switchGamutConstraint = true;
    qDebug() << "Button Gamut Clicked!" << MyDecalSolver::switchGamutConstraint;
    internal_solver_init();

}
void QWidgetMyWidget::handleButton2Pressed()
{
    uiPointer->pushButton_2->setIcon(IconPressedButton2);
}
void QWidgetMyWidget::handleButton3Pressed()
{
    uiPointer->pushButton_3->setIcon(IconPressedButton3);
}

void QWidgetMyWidget::handleButton4Pressed()
{
    uiPointer->pushButton_4->setIcon(IconPressedButton4);
}

//button released
void QWidgetMyWidget::handleButton1Released()
{
    uiPointer->pushButton_1->setIcon(IconReleasedButton);
    MyDecalSolver::switchGamutConstraint = false;
    qDebug() << "Button Gamut Clicked!" << MyDecalSolver::switchGamutConstraint;
    internal_solver_init();
}
void QWidgetMyWidget::handleButton2Released()
{
    uiPointer->pushButton_2->setIcon(IconReleasedButton);
}
void QWidgetMyWidget::handleButton3Released()
{
    uiPointer->pushButton_3->setIcon(IconReleasedButton);
}
void QWidgetMyWidget::handleButton4Released()
{
    uiPointer->pushButton_4->setIcon(IconReleasedButton);
}




void QWidgetMyWidget::mousePressEvent(QMouseEvent *event) {

    //int xm = event->x();
    //int xm = 0;

    //std::cout << "coucou souris " << xm << std::endl;
    std::cout << "(x,y) = " << event->pos().x() << "  "<< event->pos().y()<<std::endl;
}

void QWidgetMyWidget::mouseMoveEvent(QMouseEvent *event) {

    //int xm = event->x();
    //int xm = 0;

    //std::cout << "coucou souris " << xm << std::endl;
    std::cout << "(x,y) = " << event->pos().x() << "  "<< event->pos().y()<<std::endl;
    repaint();//update() in general, use repaint for animation only
}


