#include "qwidgetmyicon.h"
#include "QWidgetMyDecale.h"
#include <QTouchEvent>

QWidgetMyIcon::QWidgetMyIcon(const QPixmap pixmap)
{
    installEventFilter(this);

    //QPixmap pixmap(imagePath);

    iconLabel = new QLabel(this);
    iconLabel->setPixmap(pixmap);
    iconLabel->setFixedSize(pixmap.size());


    iconLabel->raise();

    iconLabel->setAlignment(Qt::AlignCenter);
    iconLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    //    iconLabel->setGeometry(1752,340, iconLabel->width(), iconLabel->height());
    qDebug() <<"constructor: "<< iconLabel->size();
}

void QWidgetMyIcon::changeIconPixmap(QPixmap pixmap)
{
    iconLabel->setPixmap(pixmap);
}

void QWidgetMyIcon::internal_preupdate_solve()
{

}

void QWidgetMyIcon::internal_solver_init()
{

}

void QWidgetMyIcon::innerPaintColorDecaleMouseUpdate()
{

}

void QWidgetMyIcon::innerRemoveColorDecale()
{

}


bool QWidgetMyIcon::event(QEvent *event){



//    if (event->type() == QEvent::TouchBegin)
//        {
//            QTouchEvent *touchEvent = static_cast<QTouchEvent*>(event);
//            if (touchEvent->touchPoints().size() == 1)
//            {
//                QPointF touchPoint = touchEvent->touchPoints().first().pos();

//                // Check if the touch point is within the boundaries of the icon
//                if (rect().contains(touchPoint.toPoint()))
//                {
//                    // Emit the signal only if the touch point is within the icon's boundaries
//                   qDebug() << "touched";
//                }
//            }
//        }









    if (event->type() == QEvent::TouchBegin)
    {

        emit iconPressed();
        return true;
    }
    else if (event->type() == QEvent::TouchEnd)
    {
        emit iconReleased();
        qDebug()<<"end";
        return true;
    }

    return QWidget::event(event); // Call base class implementation
}
