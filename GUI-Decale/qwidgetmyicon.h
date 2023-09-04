#ifndef QWIDGETMYICON_H
#define QWIDGETMYICON_H

#include <QLabel>
#include "QWidgetMyWidget.h"

class QWidgetMyIcon: public QWidgetMyWidget
{
    Q_OBJECT
public:
   QWidgetMyIcon(const QPixmap pixmap);
   void changeIconPixmap(QPixmap);
   QLabel* iconLabel;


signals:
    void iconPressed();
    void iconReleased();


protected:

    void internal_preupdate_solve() override;
    void internal_solver_init() override;
    void innerPaintColorDecaleMouseUpdate() override;
    void innerRemoveColorDecale() override;

    bool event(QEvent *event) override;//for touch


};


#endif // QWIDGETMYICON_H
