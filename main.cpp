#include <iostream>
#include <QApplication>
#include <QMainWindow>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QGridLayout>
#include "Tools/ColorImage.h"
#include "Decale/DecaleDiskField2D.h"
#include "Decale/DecaleSquareField2D.h"
#include "Decale/DecaleRoundCornerSquareField2D.h"
#include "Deformer2D/Deformer2D.h"
#include "Deformer2D/Deformer2DMax.h"
#include "Deformer2D/Deformer2DContact.h"
#include "Deformer2D/Deformer2DBlendMax.h"
#include "Deformer2D/Deformer2DBinaryHardContact.h"
#include "Deformer2D/Deformer2DBinaryHardContactMax.h"
#include "SDField2D/SDField2DLinear.h"
#include "SDField2D/SDField2DDisk.h"
#include "Gamut/GamutDeformer2DBinaryHardContact.h"
#include "Gamut/GamutDeformer2DBinaryHardContactMax.h"
#include "Operator2D/Operator2DMax.h"
#include "Operator2D/Operator2DBinaryCleanIntersectionDistance.h"
#include "Operator2D/Operator2DBinaryCleanUnionDistance2D.h"
#include "Deformer2D/Deformer2DBlendContact.h"
#include "GUI-Decale/QWidgetMyDecale.h"
#include <math.h>
#include "Field2D/imagefield.h"
#include "Solver/mydecalsolver.h"
#include <QSerialPort>



//unsigned int wi_width=1024;
//unsigned int wi_height=740;

unsigned int wi_width=1920;
unsigned int wi_height=1080;

VectorOfDecaleFields fields;
VectorOfColorImages decaleImages;
VectorOfFields gamutComponentFields;
GamutField2D *gamut;
VectorOfDeformers deformers;


/*****************************************************************************/
/***********************************
// Create all the Decales (including their images) and the Gamut
***********************************/
/*****************************************************************************/
void buildFields (){

    /***********************************
    // Controls the slop of the fallOff functions (Gamut and Decales)
    // n = 2 is the smoother, n > 2 makes it sharper
    **********************************/
    int n = 2;

/***********************************
// BEGIN GAMUT
***********************************/

    /***********************************
    // Create the gamut fields
    // ni : plane normalized normals
    // ci : disk centers
    **********************************/
    Vector2D n1(-1., 0.);
    Vector2D n2(0, -1);
    Vector2D n3(1, 0);
    Vector2D n4(0, 1);
    Vector2D n5(-1., 1.);
    n5.normalize();
    Vector2D c1((double) wi_width / 2., (double) wi_height / 2.);
    Vector2D c2(100., 100.);
    Vector2D c3((double) (wi_width - 100), 100);

    /***********************************
    // Radius of the FallOff function of the Gamut
    **********************************/
    double sizeFallOff = 80.;

    /***********************************
    // Create Gamut elements (plans and disk) as Signed Distance Fields (SDF)
    // Store them in a vector of fields
    ***********************************/
    gamutComponentFields.push_back(new SDField2DLinear(n1, 100.));
    gamutComponentFields.push_back(new SDField2DLinear(n2, 100.));
    gamutComponentFields.push_back(new SDField2DLinear(n3, -(double) (wi_width - 100)));
    gamutComponentFields.push_back(new SDField2DLinear(n4, -(double) (wi_height - 100)));
    gamutComponentFields.push_back(new SDField2DLinear(n5, -300));
    gamutComponentFields.push_back(new SDField2DDisk(c1, 90.));
    gamutComponentFields.push_back(new SDField2DDisk(c2, 200.));
    gamutComponentFields.push_back(new SDField2DDisk(c3, 120.));

    /***********************************
    // Combines the gamut elements (SDF) in a composition tree
    // to get the final SDF that will be used to build the gamut field
    ***********************************/
    //Field2D *gamutSDF = new Operator2DMax(gamutComponentFields);

   // QString path = "C:/Users/aniyazov/Pictures/interactive_decal_interface/Asset 68";
    QString path = "C:/Users/aniyazov/Pictures/interactive_decal_interface/demo-constraints-avengers-05";
    Field2D *gamutSDF = new ImageField(path);


    /***********************************
    // Build a Gamut field from the SDF (Gamut is of compact support)
    // the size for the falloff function is the size from the center to isosurface
    ***********************************/
    gamut = new GamutField2D(gamutSDF, 0, 0, wi_width, wi_height, sizeFallOff, n);

    /***********************************
    // Pre-computation of the gamut field values in a buffer of size wi_width*wi_height
    ***********************************/
    gamut->computeDiscreteField();

/***********************************
// END GAMUT
***********************************/


/***********************************
// BEGIN DECALS
***********************************/

    /***********************************
    // Different Decale sizes in pixels
    **********************************/
    double decaleSize0 = 100.;
    double decaleSize1 = 50.;
    double decaleSize2 = 90.;
    double decaleSize3 = 25.;
    double decaleSize4 = 150.;

    /***********************************
    // Create each Decale with its eventual rotation and its image
    // Store them in a vector of Decale fields and a vector of corresponding (by index) of Decale images
    ***********************************/
//    fields.push_back(new DecaleSquareField2D(780., 270., decaleSize0, n));
//    decaleImages.push_back(new ColorImage ("../Images/paysage-ponton-lac.jpeg"));
//    fields[0]->rotate(M_PI/8.);
//    fields[0]->scale(2.7, decaleImages[0]->getRatioHW()*2.7);

//    fields.push_back(new DecaleSquareField2D(333., 510., decaleSize0, n));
//    decaleImages.push_back(new ColorImage ("../Images/tigre-500.png"));
//    fields[1]->scale(1.88,decaleImages[1]->getRatioHW()*1.88);

//    fields.push_back(new DecaleSquareField2D(670., 520., decaleSize0, n));
//    decaleImages.push_back(new ColorImage ("../Images/clash-royale.jpeg"));
//    fields[2]->scale(0.55,decaleImages[2]->getRatioHW()*0.55);

//    fields.push_back(new DecaleDiskField2D(360., 290., decaleSize4, n));
//    decaleImages.push_back(new ColorImage ("../Images/palette-couleurs.png"));

//    fields.push_back(new DecaleDiskField2D (170.,360.,decaleSize2, n));
//    decaleImages.push_back(new ColorImage ("../Images/logoStorm.png"));
//    fields[4]->rotate(-M_PI/6.);

//    fields.push_back(new DecaleRoundCornerSquareField2D(290., 650., decaleSize1, M_PI/6, n));
//    decaleImages.push_back(new ColorImage ("../Images/i-mail.png"));

//    fields.push_back(new DecaleSquareField2D(290., 650., decaleSize1, n));
//    decaleImages.push_back(new ColorImage ("../Images/i-mail.png"));

//    fields.push_back(new DecaleSquareField2D(400., 650., decaleSize1, 1));
//    decaleImages.push_back(new ColorImage ("../Images/i-map.png"));

//    fields.push_back(new DecaleRoundCornerSquareField2D(510., 650., decaleSize1, M_PI/6, n));
//    decaleImages.push_back(new ColorImage ("../Images/i-meteo.png"));

//    fields.push_back(new DecaleRoundCornerSquareField2D(620., 650., decaleSize1, M_PI/6, n));
//    decaleImages.push_back(new ColorImage ("../Images/i-flower.png"));

//    fields.push_back(new DecaleRoundCornerSquareField2D(730., 650., decaleSize1, M_PI/6, n));
//    decaleImages.push_back(new ColorImage ("../Images/i-boussole.png"));

//    fields.push_back(new DecaleRoundCornerSquareField2D(840., 650., decaleSize4, M_PI/6, n));
//    decaleImages.push_back(new ColorImage ("../Images/i-message.png"));

//    std::cout<<"decal size: "<<fields[5]->getSize()<<std::endl;

//    fields.push_back(new DecaleRoundCornerSquareField2D(950., 650., decaleSize1, M_PI/6, n));
//    decaleImages.push_back(new ColorImage ("../Images/i-photo.png"));
//    fields[6]->rotate(-M_PI/6.);

//    fields.push_back(new DecaleDiskField2D (330.,140.,decaleSize3, n));
//    decaleImages.push_back(new ColorImage ("../Images/round-dropbox.png"));

//    fields.push_back(new DecaleDiskField2D (410.,140.,decaleSize3, n));
//    decaleImages.push_back(new ColorImage ("../Images/round-google.png"));

//    fields.push_back(new DecaleDiskField2D (490.,140.,decaleSize3, n));
//    decaleImages.push_back(new ColorImage ("../Images/round-whatsapp.png"));

    //avengers
//    fields.push_back(new DecaleDiskField2D (690.,140.,decaleSize0, n));
//    decaleImages.push_back(new ColorImage ("C:/Users/aniyazov/Pictures/interactive_decal_interface/avengers_demo/decals/decals_hulk"));

//    fields.push_back(new DecaleDiskField2D (490.,340.,decaleSize0, n));
//    decaleImages.push_back(new ColorImage ("C:/Users/aniyazov/Pictures/interactive_decal_interface/avengers_demo/decals/decals_thanos"));

//    fields.push_back(new DecaleDiskField2D (490.,320.,decaleSize0, n));
//    decaleImages.push_back(new ColorImage ("C:/Users/aniyazov/Pictures/interactive_decal_interface/avengers_demo/decals/decals_spiderman"));

//    fields.push_back(new DecaleDiskField2D (410.,200.,decaleSize0, n));
//    decaleImages.push_back(new ColorImage ("C:/Users/aniyazov/Pictures/interactive_decal_interface/avengers_demo/decals/decals_ultron"));

//    fields.push_back(new DecaleDiskField2D (490.,140.,decaleSize0, n));
//    decaleImages.push_back(new ColorImage ("C:/Users/aniyazov/Pictures/interactive_decal_interface/avengers_demo/decals/decals_ironman"));

//    fields.push_back(new DecaleDiskField2D(500., 650., decaleSize0, n));
//    decaleImages.push_back(new ColorImage ("C:/Users/aniyazov/Pictures/interactive_decal_interface/avengers_demo/decals/decals_captain-america1"));

//    fields.push_back(new DecaleDiskField2D(290., 650., decaleSize0, n));
//    decaleImages.push_back(new ColorImage ("C:/Users/aniyazov/Pictures/interactive_decal_interface/avengers_demo/decals/decals_apocalypse"));


//    fields.push_back(new DecaleDiskField2D (690.,140.,decaleSize0, n));
//    decaleImages.push_back(new ColorImage ("C:/Users/aniyazov/Pictures/interactive_decal_interface/avengers_demo/compressed/decals_hulk-min"));

//    fields.push_back(new DecaleDiskField2D (490.,340.,decaleSize0, n));
//    decaleImages.push_back(new ColorImage ("C:/Users/aniyazov/Pictures/interactive_decal_interface/avengers_demo/compressed/decals_thanos-min"));

//    fields.push_back(new DecaleDiskField2D (490.,320.,decaleSize0, n));
//    decaleImages.push_back(new ColorImage ("C:/Users/aniyazov/Pictures/interactive_decal_interface/avengers_demo/compressed/decals_spiderman-min"));

//    fields.push_back(new DecaleDiskField2D (410.,200.,decaleSize0, n));
//    decaleImages.push_back(new ColorImage ("C:/Users/aniyazov/Pictures/interactive_decal_interface/avengers_demo/compressed/decals_ultron-min"));

//    fields.push_back(new DecaleDiskField2D (490.,140.,decaleSize0, n));
//    decaleImages.push_back(new ColorImage ("C:/Users/aniyazov/Pictures/interactive_decal_interface/avengers_demo/compressed/decals_ironman-min"));

//    fields.push_back(new DecaleDiskField2D(500., 650., decaleSize0, n));
//    decaleImages.push_back(new ColorImage ("C:/Users/aniyazov/Pictures/interactive_decal_interface/avengers_demo/compressed/decals_captain-america1-min"));

//    fields.push_back(new DecaleDiskField2D(290., 650., decaleSize0, n));
//    decaleImages.push_back(new ColorImage ("C:/Users/aniyazov/Pictures/interactive_decal_interface/avengers_demo/compressed/decals_apocalypse-min"));


    fields.push_back(new DecaleDiskField2D (690.,140.,decaleSize1, n));
    decaleImages.push_back(new ColorImage ("C:/Users/aniyazov/Pictures/interactive_decal_interface/avengers_demo/100w/decals (1)"));

    fields.push_back(new DecaleDiskField2D (490.,340.,decaleSize1, n));
    decaleImages.push_back(new ColorImage ("C:/Users/aniyazov/Pictures/interactive_decal_interface/avengers_demo/100w/decals (2)"));

    fields.push_back(new DecaleDiskField2D (490.,320.,decaleSize1, n));
    decaleImages.push_back(new ColorImage ("C:/Users/aniyazov/Pictures/interactive_decal_interface/avengers_demo/100w/decals (3)"));

    fields.push_back(new DecaleDiskField2D (410.,200.,decaleSize1, n));
    decaleImages.push_back(new ColorImage ("C:/Users/aniyazov/Pictures/interactive_decal_interface/avengers_demo/100w/decals (7)"));

    fields.push_back(new DecaleDiskField2D (490.,140.,decaleSize1, n));
    decaleImages.push_back(new ColorImage ("C:/Users/aniyazov/Pictures/interactive_decal_interface/avengers_demo/100w/decals (10)"));

    fields.push_back(new DecaleDiskField2D(500., 650., decaleSize1, n));
    decaleImages.push_back(new ColorImage ("C:/Users/aniyazov/Pictures/interactive_decal_interface/avengers_demo/100w/decals (12)"));

    fields.push_back(new DecaleDiskField2D(290., 670., decaleSize1, n));
    decaleImages.push_back(new ColorImage ("C:/Users/aniyazov/Pictures/interactive_decal_interface/avengers_demo/100w/decals (4)"));

    fields.push_back(new DecaleDiskField2D(500., 620., decaleSize1, n));
    decaleImages.push_back(new ColorImage ("C:/Users/aniyazov/Pictures/interactive_decal_interface/avengers_demo/100w/decals (5)"));

    fields.push_back(new DecaleDiskField2D(600., 640., decaleSize1, n));
    decaleImages.push_back(new ColorImage ("C:/Users/aniyazov/Pictures/interactive_decal_interface/avengers_demo/100w/decals (6)"));

    fields.push_back(new DecaleDiskField2D(700., 400., decaleSize1, n));
    decaleImages.push_back(new ColorImage ("C:/Users/aniyazov/Pictures/interactive_decal_interface/avengers_demo/100w/decals (8)"));

    fields.push_back(new DecaleDiskField2D(800., 240., decaleSize1, n));
    decaleImages.push_back(new ColorImage ("C:/Users/aniyazov/Pictures/interactive_decal_interface/avengers_demo/100w/decals (9)"));

    fields.push_back(new DecaleDiskField2D(800., 500., decaleSize1, n));
    decaleImages.push_back(new ColorImage ("C:/Users/aniyazov/Pictures/interactive_decal_interface/avengers_demo/100w/decals (11)"));


    /***********************************
    // Pre-compute the field values of each Decale in a buffer
    ***********************************/
    for (int i = 0; i < fields.size(); i++) fields[i]->computeDiscreteField();

/***********************************
// END DECALS
***********************************/

/***********************************
// BEGIN DEFORMERS
***********************************/

    /***********************************
    // Create the deformers
    // Here: contact between Decales and rigid Gamut vs deformed in contact Decales
    // Deformers are stored in a vectors of Deformers
    // the Decales are added to the contact Derformer
    // the Decales are also added to the Gamut Deformer
    ***********************************/
    deformers.push_back(new Deformer2DContact(fields[0], 0, fields[1], 0));
    //deformers.push_back(new Deformer2DMax(fields[0], 0, fields[1], 0));
    for (int i = 2; i < fields.size(); i++) deformers[deformers.size()-1]->addField(fields[i], 0);

    //deformers.push_back(new GamutDeformer2DBinaryHardContact(gamut, fields[0], 1));
    deformers.push_back(new GamutDeformer2DBinaryHardContactMax(gamut, fields[0], 1));
    for (int i = 1; i < fields.size(); i++) deformers[deformers.size()-1]->addField(fields[i], 1);

    /***********************************
    //Apply the Deformers to the field values stored in the top buffers (the one with the larger index)
    //of all the Decales it deforms and store it for each Decale in a new buffer.
    ***********************************/
    for (int i = 0; i < deformers.size(); i++)  deformers[i]->applyToDiscreteFields();

/***********************************
// END DEFORMERS
***********************************/

/***********************************
// BEGIN Compute UV buffers for each Decale
***********************************/

    for (int i = 0; i < fields.size(); i++) fields[i]->computeDiscreteUVField(fields[i]->getNbDiscreteFields() - 1);

/***********************************
// END Compute UV buffers for each Decale
***********************************/
}



/*****************************************************************************/
/***********************************
// main : create the Qapp, create the Widget and its components, create the fields (Gamut and Decales)
// set the Widget elements and initialize the Widget image
***********************************/
/*****************************************************************************/
int main(int argc, char** argv)
{

     QApplication app(argc, argv);

      QMainWindow mainWindow;
      Ui::MainWindow *ui = new Ui::MainWindow; // Instantiate the generated UI class

      ui->setupUi(&mainWindow); // Set up the UI components

     // Get the list of available screens
     QList<QScreen *> screens = QGuiApplication::screens();

     QWidgetMyDecale myWidget (wi_width, wi_height, Color(0.,0.,0.));
     //myWidget.setBgImage("C:/Users/aniyazov/Pictures/interactive_decal_interface/Asset 22");


     QLabel  *label  = new QLabel(&myWidget);


//     myWidget.setLayout(gridLayout);
     myWidget.setLabel(label);

     buildFields();

     myWidget.setDecoration(ui);
     myWidget.setDecales(fields);
     myWidget.setDeformers(deformers);
     myWidget.setDecaleImages(decaleImages);
     myWidget.setGamut(gamut);
     myWidget.setGamutColor(Color(1.,1.,1.));
     myWidget.prepareSolver(gamut);
     //myWidget.setUiPointer(ui);
     myWidget.addButtons();


     /***********************************
     // Compute the Widget image
     ***********************************/
     myWidget.update();

//     QGridLayout *gridLayout = new QGridLayout;
//     gridLayout->addWidget(&myWidget);

     // Create a central widget and set the layout
//     QWidget* centralWidget = new QWidget;
//     centralWidget->setLayout(gridLayout);

     // Set the central widget of the main window
    // mainWindow.setCentralWidget(&myWidget);



    QVBoxLayout *containerLayout = new QVBoxLayout(ui->widget); // Create a layout for the container
    containerLayout->addWidget(&myWidget);




//    // Connect the clicked signal of pushButton1 to a lambda function
//        QObject::connect(ui->pushButton_1, &QPushButton::clicked, [&]() {
//            ui->pushButton_1->setChecked(true);
//            ui->pushButton_2->setChecked(false);
//            ui->pushButton_3->setChecked(false);
//            ui->pushButton_4->setChecked(false);

//            MyDecalSolver::switchGamutConstraint = !MyDecalSolver::switchGamutConstraint;

//            ui->pushButton_1->isChecked();
//            qDebug() << "Button Gamut Clicked!" << MyDecalSolver::switchGamutConstraint;

//            // Add your custom code here
//        });
//        QObject::connect(ui->pushButton_2, &QPushButton::clicked, [&]() {

//            // Add your custom code here
//            MyDecalSolver::switchMinDistConstraint = !MyDecalSolver::switchMinDistConstraint;
//             qDebug() << "Button MinDist Clicked!" <<  MyDecalSolver::switchMinDistConstraint;
//        });
//        QObject::connect(ui->pushButton_3, &QPushButton::clicked, [&]() {
//            qDebug() << "Button MaxDist Clicked!";
//            // Add your custom code here
//            MyDecalSolver::switchMaxDistConstraint = !MyDecalSolver::switchMaxDistConstraint;
//        });

//        QObject::connect(ui->pushButton_4, &QPushButton::clicked, [&]() {
//            qDebug() << "Button Alignement Clicked!";
//            // Add your custom code here
//            MyDecalSolver::switchAlignConstraint = !MyDecalSolver::switchAlignConstraint;
//        });



    // Assuming there are at least two screens
    if (screens.size() >= 1) {
         QScreen *secondScreen =  screens.at(1);
          if (screens.size() >= 3){
             secondScreen = screens.at(2); // Get the 3rd screen
          }


        // Get the available geometry of the second screen
        QRect availableGeometry = secondScreen->availableGeometry();

        mainWindow.setGeometry(availableGeometry);
        mainWindow.showFullScreen();
    }else{
          mainWindow.show();
    }





     return app.exec();



//    QApplication app(argc, argv);
////    app.setAttribute(Qt::AA_SynthesizeMouseForUnhandledTouchEvents, false );
////    app.setAttribute(Qt::AA_SynthesizeTouchForUnhandledMouseEvents, false );

//    // Get the list of available screens
//    QList<QScreen *> screens = QGuiApplication::screens();

//    QWidgetMyDecale myWidget (wi_width, wi_height, Color(0.,0.,0.));
//    //myWidget.setBgImage("C:/Users/aniyazov/Pictures/interactive_decal_interface/mainWindow_binaryImageTest");

//    QLabel  *label  = new QLabel(&myWidget);
//    QGridLayout *gridLayout = new QGridLayout;

//    gridLayout->addWidget(label);

//    myWidget.setLayout(gridLayout);
//    myWidget.setLabel(label);

//    buildFields();

//    myWidget.setDecales(fields);
//    myWidget.setDeformers(deformers);
//    myWidget.setDecaleImages(decaleImages);
//    myWidget.setGamut(gamut);
//    myWidget.setGamutColor(Color(1.,1.,1.));
//    myWidget.prepareSolver(gamut);

//    /***********************************
//    // Compute the Widget image
//    ***********************************/
//    myWidget.update();

///*
//    mainWindow.setCentralWidget(&myWidget);
//    mainWindow.show()*/;

//    // Assuming there are at least two screens
//    if (screens.size() >= 3) {
//        QScreen *secondScreen = screens.at(2); // Get the 3rd screen

//        // Get the available geometry of the second screen
//        QRect availableGeometry = secondScreen->availableGeometry();

//        myWidget.setGeometry(availableGeometry);
//        myWidget.showFullScreen();
//    }else{
//          myWidget.show();
//    }


//    return app.exec();
}
