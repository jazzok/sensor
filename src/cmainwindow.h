#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <QWidget>

#include <QPainter>
#include <QPaintEvent>
#include <QShowEvent>
#include <QDebug>

class CMainWindow : public QWidget
{
    Q_OBJECT

public:
    CMainWindow(QWidget *parent = nullptr);
    ~CMainWindow();

protected:
    virtual void showEvent  (QShowEvent     *event);
    virtual void paintEvent (QPaintEvent    *event);
    bool	eventFilter		(QObject        *object,
                             QEvent         *event);
    virtual void wheelEvent (QWheelEvent    *event);

private:
    QSize   sizeScreen;
    QRect   rectScreen;
    QPointF pointCenter;
    float   giverValue;
    float   currentValue;
    bool    init;
//
    void    drawDashBoard       (QPainter *painter);
    void    drawDial            (QPainter *painter);
    void    drawCurrentArrow    (QPainter *painter);
    void    drawGiverArrow      (QPainter *painter);
};
#endif // CMAINWINDOW_H
