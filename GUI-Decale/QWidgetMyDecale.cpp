//
// Created by Loïc Barthe on 03/04/2020.
//

#include "QWidgetMyDecale.h"
#include <QGridLayout>
#include <iostream>
#include <QMouseEvent>
#include <QTimer>
#include <math.h>



QWidgetMyDecale::QWidgetMyDecale (int width, int height, Color bgColor) : QWidgetMyWidget() {

    /***********************************
    // Create the color image with a background color
    // Set the background color
    ***********************************/
    colorImage = new ColorImage (width, height);
    this->bgColor.setColor(bgColor);
    colorImage->setColor (bgColor);


}

void QWidgetMyDecale::setBgImage(const QString &fileName)
{
     colorImage = new ColorImage (fileName);


}

std::vector<bool> QWidgetMyDecale::lockedDecals;



int QWidgetMyDecale::getClosestDecalID(QPointF pointpos){


//        refx.push_back(point.position().x());
//        refy.push_back(point.position().y());
//        refposx.push_back(decales[0]->getPosx());
//        refposy.push_back(decales[0]->getPosy());
//        indexSelectedDecale = 0;

//        double dist = (refx.at(i)-refposx.at(i))*(refx.at(i)-refposx.at(i))+
//                        (refy.at(i)-refposy.at(i))*(refy.at(i)-refposy.at(i));

//        //std::cout<<"dist: "<<o<<" "<<" "<<dist<<std::endl;

//        double min = dist;
//        for (int j=1; j<decales.size(); j++) {

//            dist = (refx.at(i)-decales[j]->getPosx())*(refx.at(i)-decales[j]->getPosx())+
//                    (refy.at(i)-decales[j]->getPosy())*(refy.at(i)-decales[j]->getPosy());
//            if (dist < min){
//                refposx.at(i) = decales[j]->getPosx();
//                refposy.at(i) = decales[j]->getPosy();
//                indexSelectedDecale = j;

//                min = dist;
//            }
//            //std::cout<<"dist: "<<point.id()<<" "<<o<<"-"<<j<<" "<<indexSelectedDecale.at(o)<<" "<<min<<std::endl;
//        }

        refx = pointpos.x();
        refy = pointpos.y();
        refposx = decales[0]->getPosx();
        refposy = decales[0]->getPosy();
        indexSelectedDecale = 0;

        double dist = (refx-refposx)*(refx-refposx)+(refy-refposy)*(refy-refposy);
        double min = dist;
        for (int i=1; i<decales.size(); i++) {
            dist = (refx-decales[i]->getPosx())*(refx-decales[i]->getPosx())+(refy-decales[i]->getPosy())*(refy-decales[i]->getPosy());
            if (dist < min){
                refposx = decales[i]->getPosx();
                refposy = decales[i]->getPosy();
                indexSelectedDecale = i;
                min = dist;
            }
        }
        //std::cout<<"id: "<<indexSelectedDecale<<std::endl;
        return indexSelectedDecale;
}
int QWidgetMyDecale::getDecalID(QPointF mousepos)
{
    //auto mousepos = mev->position();

    //std::cout<<"get decal id: "<<std::endl;

    refx = mousepos.x();
    refy = mousepos.y();

    for(size_t i = 0; i<decales.size(); i++){
        //std::cout<<"decals: "<<decales.size()<<" "<<i<<std::endl;
        auto d = decales[i];
        auto dinitx = d->getPosx() - d->getSize();
        auto dinity = d->getPosy() - d->getSize();
        auto dfinx  = d->getPosx() + d->getSize();
        auto dfiny  = d->getPosy() + d->getSize();

        if((mousepos.x() > dinitx) and (mousepos.y() > dinity) and
           (mousepos.x() < dfinx) and (mousepos.y() < dfiny)){
            if(d->getDiscreteFieldValue(mousepos.x()-d->getCornerX(), mousepos.y()-d->getCornerY(), 0) > 0.5){
                //std::cout<<"inside decal: "<<std::endl;
                indexSelectedDecale = i;
                //std::cout<<"id: "<<indexSelectedDecale<<std::endl;

                //for solver getter
                lockedDecals[indexSelectedDecale] = true;

                //to smooth decal movement
                refposx = decales[i]->getPosx();
                refposy = decales[i]->getPosy();
                break;
            }else{
                 //std::cout<<"outside decal: "<<std::endl;
            }
        }else {
            indexSelectedDecale = -1;

            setLockedDecalsToFalse();
            //std::cout<<"no decal pressed: "<<std::endl;
        }
    }

    //std::cout<<"id: "<<indexSelectedDecale<<std::endl;
    return indexSelectedDecale;
}

void QWidgetMyDecale::setLockedDecalsToFalse()
{
    for (size_t i = 0; i < lockedDecals.size() ; i++){
        lockedDecals[i] = false;
        //std::cout<<lockedDecals[i]<<std::endl;
    }
}




//bool QWidgetMyDecale::event(QEvent *event){
//    switch (event->type()) {
////    case QEvent::MouseButtonPress:{
////        QMouseEvent *m = static_cast<QMouseEvent *>(event);
////        //indexSelectedDecale = getDecalID(m->position());
////        return true;
////    }
////    case QEvent::MouseMove:{
////        QMouseEvent *m = static_cast<QMouseEvent *>(event);
////        //mouseMoveEvent(m);
////        return true;
////    }
////    case QEvent::MouseButtonRelease:{
////        setLockedDecalsToFalse();
////        innerRemoveColorDecale();
////        needUpdate = true;
////    }
//    case QEvent::TouchBegin:{
//        QTouchEvent *t = static_cast<QTouchEvent *>(event);
//        std::cout<<"TouchSequenceBegin: "<<t->points().count()<<std::endl;
//        istouchbegin = true;
//        return true;
//    }
//    case QEvent::TouchUpdate:{

//        //std::cout<<"TouchUpdate"<<std::endl;
//        QTouchEvent *t = static_cast<QTouchEvent *>(event);
//        //std::cout<<"size: "<<t->pointCount()<<std::endl;

//        //Touch add and release
//        for(int i = 0; i<t->pointCount(); i++){
//            auto point = t->points().at(i);



//            //On Touch Add
//            //detect new touch and assign touch id to decal id
////            if(point.pressPosition() == point.position() and istouchbegin){
//            if(istouchbegin){
//                //get declal id when touching
//                touchedDecalID = getDecalID(point.position());

//                std::cout<<"NEW TOUCH"<<std::endl;
//                std::cout<<"idx: "<<touchedDecalID<<" "<< point.id()<<std::endl;
//                //if touches on decal -> save the id
//                if(touchedDecalID >= 0){
//                    //key: decal id, value: decal position
//                    d.id = touchedDecalID;
//                    d.pos = QPointF(decales[touchedDecalID]->getPosx(), decales[touchedDecalID]->getPosy());
//                    //d.pos = QPointF(point.position().x(), point.position().y());
//                    decalsref.insert(point.id(), d);
//                }
//                istouchbegin = false;
//                prevPointCount+=1;
//                std::cout<<"size: "<<t->pointCount()<<std::endl;
//            }
//            //On Touch Release
//            if(t->pointCount() < prevPointCount){
//                std::cout<<"touch removed"<<std::endl;
//                std::cout<<"size: "<<t->pointCount()<<std::endl;
//                prevPointCount = t->pointCount();

//                //update decals touchmap
//                tempmap = decalsref;
//                decalsref.clear();
//                for(int k = 0; k<t->pointCount(); k++){
//                    auto pid = t->points().at(k).id();
//                    for(auto j = tempmap.begin();  j != tempmap.end(); j++){
//                        if(j.key() == pid){
//                            decalsref.insert(pid, tempmap.value(pid));
//                        }
//                    }
//                }
//                tempmap.clear();
//            }
//            //auto decalID = decalsref.value(point.id()).id;
//            //std::cout<<"-point: "<<point.id()<<" "<<touchedDecalID<<" "<<point.position().x()<<" "<<decalsref.size()<<std::endl;
//        }


//        std::cout<<"dtouches: "<<decalsref.size()<<std::endl;
//        //interaction with touched points when decals are touches
//        for(auto i = decalsref.begin(); i != decalsref.end(); i++){
//            auto p = t->pointById(i.key());
//            auto decalID = i.value().id;

//            if(decalID >= 0){
//                //getting decal position from map of decals
//                auto refvalx = i.value().pos.x();
//                auto refvaly = i.value().pos.y();

//                innerRemoveColorDecale();




//                int pid1 = -1, pid2 = -1;
//                for(auto j = decalsref.begin(); j!= decalsref.end(); j++){
//                    if(i!=j){
//                        if(i.value().id == j.value().id){
//                            foundTwoTouches = true;
//                            decalIDToScale = i.value().id;
//                            pid1 = i.key();
//                            pid2 = j.key();
//                        }
//                    }

//                }


//                if(foundTwoTouches){
////                    if(pid1==-1 or pid2==-1){
////                        std::cout<<"---------------------ERRROR"<<std::endl;
////                    }
//                    assert(pid1 != -1);
//                    assert(pid2 != -1);

//                    auto p1 = t->pointById(pid1);
//                    auto p2 = t->pointById(pid2);


//                    double dist = (p1->position().x()-p2->position().x())*(p1->position().x()-p2->position().x())+
//                                  (p1->position().y()-p2->position().y())*(p1->position().y()-p2->position().y());

//                    double distInit = (p1->pressPosition().x()-p2->pressPosition().x())*
//                                      (p1->pressPosition().x()-p2->pressPosition().x())+
//                                      (p1->pressPosition().y()-p2->pressPosition().y())*
//                                      (p1->pressPosition().y()-p2->pressPosition().y());


//                    currentScale = decales[decalIDToScale]->getScalex();//or y. scale in both direction

//                    //previous scale is needed after touch release to start with last scaled decal
//                    scalefactor = prevscalefactor[decalIDToScale] * dist/distInit;

//                    std::cout<<"dist: "<<distInit<<" "<<dist<<" "<<scalefactor<<" "<<currentScale<<std::endl;


//                    if(scalefactor>0.0 and scalefactor<2.0 and scalefactor!=1){
//                        decales[decalIDToScale]->scale(scalefactor/currentScale, scalefactor/currentScale);
//                        //decales[decalIDToScale]->setSize(decales[decalIDToScale]->getSize()*scalefactor/currentScale);
//                    }

//                    if(decales[decalIDToScale]->hasToUpdateBuffersSize()){
//                        decales[decalIDToScale]->updateBuffersSize();
//                        decales[decalIDToScale]->updateDiscreteField(0);

//                        std::cout<<"decal size: "<<decales[decalIDToScale]->getSize()<<std::endl;
//                    }
//                    std::cout<<"current scale: "<<currentScale<<std::endl;
//                }else{
//                    std::cout<<"position"<<std::endl;
//                    decales[decalID]->setPosx(refvalx + p->position().x() - p->pressPosition().x());
//                    decales[decalID]->setPosy(refvaly + p->position().y() - p->pressPosition().y());
//                }

//             foundTwoTouches = false;
//            }

//        }
//        needUpdate = true;
//        return true;
//    }
//    case QEvent::TouchCancel:{
//      std::cout<<"touch cancel: "<<std::endl;
//    }
//    case QEvent::TouchEnd:{
//        std::cout<<"touch end: "<<std::endl;
//        istouchbegin = false;
//        touchedDecalID = -1;
//        decalsref.clear();
//        prevscalefactor[decalIDToScale] = currentScale;
//        foundTwoTouches = false;

//    }
//    default:
//        return QWidget::event(event);
//    }


//}


bool touchInsideArea(QRectF rect, QPointF touchpos){

    return rect.contains(touchpos);
}

QList<QTouchEvent::TouchPoint> activeTouchPoints;

void QWidgetMyDecale::handleTouchBegin(const QTouchEvent::TouchPoint &touchPoint)
{

   //to handle touches of constraints switch within the control area/box
    QRectF controlBox(QPointF(1741,301),QPointF(1896,735));
    if(touchInsideArea(controlBox, touchPoint.position())){
        qDebug() << "contraints switch by area";
//        QRectF gamutSwitchArea  (QPointF(1790,342),QPointF(1820,369));
//        QRectF minDistSwitchArea(QPointF(1790,448),QPointF(1820,476));
//        QRectF maxDistSwitchArea(QPointF(1790,560),QPointF(1820,582));
//        QRectF AlignSwitchArea  (QPointF(1790,666),QPointF(1820,690));

//        innerRemoveColorDecale();

//        if(touchInsideArea(gamutSwitchArea, touchPoint.position())){
//            MyDecalSolver::switchGamutConstraint = !MyDecalSolver::switchGamutConstraint;
//        }else if(touchInsideArea(minDistSwitchArea, touchPoint.position())){
//            MyDecalSolver::switchMinDistConstraint = !MyDecalSolver::switchMinDistConstraint;
//        }else if(touchInsideArea(maxDistSwitchArea, touchPoint.position())){
//            MyDecalSolver::switchMaxDistConstraint = !MyDecalSolver::switchMaxDistConstraint;
//        }else if(touchInsideArea(AlignSwitchArea, touchPoint.position())){
//            MyDecalSolver::switchAlignConstraint = !MyDecalSolver::switchAlignConstraint;
//        }
//        internal_solver_init();

    }else{//to handle touches on decals
       int touchedDecalId = getDecalID(touchPoint.position());
       if (touchedDecalId != -1) {
           touchToDecalMap.insert(touchPoint.id(), touchedDecalId);
          // activeTouchPoints.append(touchPoint);

           //store initial decal position to calculate proper offset between touch position and decal center position
           auto decalposition = QPointF(decales[touchedDecalId]->getPosx(), decales[touchedDecalId]->getPosy());
           initialDecalPositions.insert(touchedDecalId, decalposition);

           qDebug() << "Touch Begin - ID:" << touchPoint.id() << "Touch Pos:" << touchPoint.position()
                    << "Touched Decal ID:" << touchedDecalId << " Decal Pos:" << decalposition;
       }
   }


}


void QWidgetMyDecale::handleTouchUpdate(const QTouchEvent::TouchPoint &touchPoint)
{

    int associatedDecalId = touchToDecalMap.value(touchPoint.id(), -1);
    if (associatedDecalId != -1){

        auto d = decales[associatedDecalId];
        innerRemoveColorDecale();

        auto initdecalposition = initialDecalPositions[associatedDecalId];
        d->setPosx(initdecalposition.x()+ touchPoint.position().x() - touchPoint.pressPosition().x());
        d->setPosy(initdecalposition.y()+ touchPoint.position().y() - touchPoint.pressPosition().y());

//       d->updateBuffersSize();
//       d->updateDiscreteField(0);
    }

}


void QWidgetMyDecale::handleTouchEnd(const QTouchEvent::TouchPoint &touchPoint)
{

    int associatedDecalId = touchToDecalMap.value(touchPoint.id(), -1);
    if (associatedDecalId != -1)
    {
        if (touchToDecalMap.contains(touchPoint.id()))
        {
            touchToDecalMap.remove(touchPoint.id());
        }
        if (initialDecalPositions.contains(associatedDecalId))
        {
            initialDecalPositions.remove(associatedDecalId);
        }

        // activeTouchPoints.removeAt(touchPoint.id());
        // activeTouchPoints.clear();


    }
    //qDebug() << " " <<initialDecalPositions.size() << " "<< touchToDecalMap.size();
}


bool QWidgetMyDecale::event(QEvent *event){
    if (event->type() == QEvent::TouchBegin ||
        event->type() == QEvent::TouchUpdate ||
        event->type() == QEvent::TouchEnd)
    {
        QTouchEvent *touchEvent = static_cast<QTouchEvent*>(event);
        QList<QTouchEvent::TouchPoint> touchPoints = touchEvent->points();

        for (const QTouchEvent::TouchPoint &touchPoint : touchPoints)
        {
            switch (static_cast<Qt::TouchPointState>(touchPoint.state()))
            {
                case Qt::TouchPointPressed:
                    handleTouchBegin(touchPoint);
                    break;

                case Qt::TouchPointMoved:
                    handleTouchUpdate(touchPoint);
                    needUpdate = true;
                    break;

                case Qt::TouchPointReleased:
                    handleTouchEnd(touchPoint);
                    break;

                default:
                    break;
            }
        }
        return true;
    }

    if(event->type() == QEvent::MouseButtonPress){
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent)
        {
            if (mouseEvent->button() == Qt::LeftButton)
            {
                qDebug() << "Mouse click position:" << mouseEvent->pos();
            }
        }
    }
    return QWidget::event(event);

}



void QWidgetMyDecale::mousePressEvent(QMouseEvent *event) {


//    refx = event->pos().x();
//    refy = event->pos().y();
//    refposx = decales[0]->getPosx();
//    refposy = decales[0]->getPosy();
//    indexSelectedDecale = 0;
//    double dist = (refx-refposx)*(refx-refposx)+(refy-refposy)*(refy-refposy);
//    double min = dist;
//    for (int i=1; i<decales.size(); i++) {
//        dist = (refx-decales[i]->getPosx())*(refx-decales[i]->getPosx())+(refy-decales[i]->getPosy())*(refy-decales[i]->getPosy());
//        if (dist < min){
//            refposx = decales[i]->getPosx();
//            refposy = decales[i]->getPosy();
//            indexSelectedDecale = i;
//            min = dist;
//        }
//    }

//    if (!timerSet) {
//        QTimer *timer = new QTimer(this);
//        connect(timer, &QTimer::timeout, this, &QWidgetMyDecale::update);
//        timer->start(1); //emits a timeout signal every 1 ms
//        timerSet = 1;
//    }
}

void QWidgetMyDecale::mouseMoveEvent(QMouseEvent *event) {

//    //if decal selected
//    if(indexSelectedDecale>=0){
//        std::cout<<"move id: "<<indexSelectedDecale<<std::endl;

//        innerRemoveColorDecale();
//        decales[indexSelectedDecale]->setPosx(refposx+event->pos().x()-refx);
//        decales[indexSelectedDecale]->setPosy(refposy+event->pos().y()-refy);

//        needUpdate = true;
//    }
}

void QWidgetMyDecale::mouseDoubleClickEvent(QMouseEvent *event){

    //repaint();
    /***********************************
    ***********************************
    // Test rotation and scale
    ***********************************
    ***********************************/
//    colorImage->clearDecaleColorImage(decales[0], decaleImages[0], gamut,
//                                      gamutColor, bgColor);
//    decales[0]->scale(2, 2);
//    //decales[0]->rotate(M_PI/10.);

//    if (decales[0]->hasToUpdateBuffersSize()){
//        decales[0]->updateBuffersSize();
//        decales[0]->updateDiscreteField(0);
//    }

}






void QWidgetMyDecale::repaint() {

    //innerPaintColorDecaleMouseUpdate();
}


void QWidgetMyDecale::update() {

    innerPaintColorDecaleMouseUpdate();
}

void QWidgetMyDecale::prepareSolver(GamutField2D *gamut)
{
    isSolverPrepared = true;
    //solver
    std::cout<<"---1 - Creating mysolver"<<std::endl;
    //MyDecalSolver mysolver;
    std::cout<<"---2 - Setting decals"<<std::endl;
    mysolver.setDecales(decales);
    mysolver.setGamut(gamut);
    std::cout<<"---3 - Calling solver update"<<std::endl;
    mysolver.init();
    std::cout<<"---4 - Calling solver solve"<<std::endl;
    mysolver.solve();

}
void QWidgetMyDecale::internal_preupdate_solve()
{
    mysolver.solve();
}

void QWidgetMyDecale::internal_solver_init(){
     mysolver.init();
     //mysolver.solve();
}

void QWidgetMyDecale::setDecales (VectorOfDecaleFields decales) {

    this->decales = decales;
    //setting clicked decals for solver getter
    lockedDecals.resize(decales.size());
    setLockedDecalsToFalse();

    //previous scale factor of decals when changing the scale on touch
    prevscalefactor.resize(decales.size());
    for (size_t i = 0; i < prevscalefactor.size() ; i++){
        prevscalefactor[i] = 1;
    }

}

void  QWidgetMyDecale::setDeformers (VectorOfDeformers deformers) {

    this->deformers = deformers;
    this->deformerType = deformerType = 0;
}

void QWidgetMyDecale::setLabel (QLabel *label){

    this->label = label;
}

void QWidgetMyDecale::setDecaleImages(VectorOfColorImages decaleImages) {

    this->decaleImages = decaleImages;

}

void QWidgetMyDecale::setGamut(GamutField2D *gamut) {

    this->gamut = gamut;
}

void QWidgetMyDecale::innerPaintColorDecaleMouseUpdate() {


    /***********************************
    // Re-Compute the existing deformed Decale buffer fields with the current decale positions
    ***********************************/
    for (int i=0;i<deformers.size();i++)
        deformers[i]->applyToExistingDiscreteFields(i+1);

    /***********************************
    // Compute the corresponding UV buffers per Decale
    ***********************************/
    for (int i=0;i<decales.size();i++)
        decales[i]->updateDiscreteUVField(decales[i]->getNbDiscreteFields()-1);
        //decales[i]->computeDiscreteUVField(decales[i]->getNbDiscreteFields()-1);


    /***********************************
    // update the image with the decale images
    ***********************************/
    for (int i=0; i<decaleImages.size();i++) {
        colorImage->addColorImageWithDecaleUV(decales[i], decaleImages[i]);

    }
    /***********************************
    // update the Widget image
    ***********************************/
    label->setPixmap(colorImage->getQPixmap());

    //std::cout<<"repaint "<<decales.size()<<std::endl;
}

void QWidgetMyDecale::innerRemoveColorDecale()
{
    for (int i=0; i<decaleImages.size();i++)
        colorImage->clearDecaleColorImage(decales[i], decaleImages[i], gamut,gamutColor, bgColor);
}

void QWidgetMyDecale::setGamutColor(Color gamutColor) {

    this->gamutColor.setColor(gamutColor);
    /***********************************
    // Color the Gamut area with the color gamutColor
    ***********************************/
    colorImage->setColorGamut (gamut,gamutColor);
}

void QWidgetMyDecale::setGamutBlack()
{
//    auto gamutColor = Color(1.,1.,1.);
//    this->gamutColor.setColor(gamutColor);
    /***********************************
    // Color the Gamut area with the color gamutColor
    ***********************************/
//    colorImage->setColorGamut (gamut,gamutColor);
    colorImage->setBlackGamut(gamut);
}






