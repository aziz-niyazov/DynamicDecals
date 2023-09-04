//
// Created by Loïc Barthe on 03/04/2020.
//

#ifndef TEST_QWIDGETMYDECALE_H
#define TEST_QWIDGETMYDECALE_H

#include "QWidgetMyWidget.h"
#include "../Decale/DecaleScalarField2D.h"
#include "../Deformer2D/Deformer2D.h"
#include "../Tools/ColorImage.h"
#include <QLabel>
#include <QEvent>
#include <QTouchEvent>


class QWidgetMyDecale : public QWidgetMyWidget {

public:

    QWidgetMyDecale(int width, int height, Color bgColor);
    MyDecalSolver mysolver;

    void setBgImage(const QString &fileName);

    void setDecales (VectorOfDecaleFields decales);
    void setGamut (GamutField2D *gamut);
    void setGamutColor (Color gamutColor);
    void setGamutBlack ();

    void setDeformers (VectorOfDeformers deformers);
    void setDecaleImages(VectorOfColorImages decaleImages);
    void setLabel (QLabel *label);



    /**
     * Call the private innerPaintColorDecaleMouseUpdate() function for deforming and redrawing Decales in the Widget Pixmap.
     */
    void update();

    void prepareSolver(GamutField2D *gamut);
    static std::vector<bool> lockedDecals;


protected:


    void internal_preupdate_solve() override;
    void internal_solver_init() override;

    /**
     * Select the Decale closer to the mouse pointer.
     */
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    /**
     * Translate the Decale closer to the mouse pointer.
     * The moved Decale is cleared in the image
     * The position of the Decale is updated
     */
    void mouseMoveEvent(QMouseEvent *event);

    bool event(QEvent *event);//for touch

    void repaint();

    VectorOfDecaleFields decales;
    VectorOfDeformers deformers;
    ColorImage *colorImage;
    VectorOfColorImages decaleImages;
    GamutField2D *gamut;
    Color gamutColor;
    Color bgColor;

    QLabel *label;

    double refx;
    double refy;
    double refposx;
    double refposy;
    int indexSelectedDecale;
    std::vector<int> indexTouchedDecales;
    int touchedDecalID = -1;

    bool istouchbegin;
    QMap<QString, int> decalsrefmapx;
    QMap<QString, int> decalsrefmapy;

    struct Dec{
        int id;
        QPointF pos;
    };
    Dec d;

    QMap<int, Dec> decalsref;
    QMap<int, Dec> tempmap;
    int prevPointCount = 0;

    bool foundTwoTouches = false;
    double scalefactor = 1;
    std::vector<double> prevscalefactor;
    double currentScale = 1;
    int decalIDToScale = -1;


    // 0 for no swap // 1 for blending-contact // 2 for contact
    int deformerType;

    QMap<int, int> touchToDecalMap; // Maps touch IDs to decal IDs
   // QMap<int, DecaleScalarField2D> decalsIdToDecal; // Maps decal IDs to Decal objects

private:

    /**
     * Compute the deformed Decale buffers.
     * Compute the corresponding UV Decale buffers
     * Draw the Decale images in the Widget image
     * Update the Widget Pixmap
     */
    void innerPaintColorDecaleMouseUpdate() override;
    void innerRemoveColorDecale() override;
    //void innerPaintDecaleMouseUpdate() override;

    int getClosestDecalID(QPointF pos);
    int getTouchedDecalId(QPointF &touchPosition);

    //int getDecalID(QMouseEvent *ev);
    int getDecalID(QPointF pos);
    void setLockedDecalsToFalse();


    void handleTouchBegin(const QTouchEvent::TouchPoint &touchPoint);
    void handleTouchUpdate(const QTouchEvent::TouchPoint &touchPoint);
    void handleTouchEnd(const QTouchEvent::TouchPoint &touchPoint);

    QMap<int, QPointF> initialTouchPositions;
    QMap<int, QPointF> initialDecalPositions;

};


#endif //TEST_QWIDGETMYDECALE_H
