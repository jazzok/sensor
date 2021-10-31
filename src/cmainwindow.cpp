#include "cmainwindow.h"

/*
 *
 */
CMainWindow::CMainWindow(QWidget *parent) : QWidget(parent)
{
//
    giverValue = 0.0;
    currentValue = 0.0;
    init = false;

//
    sizeScreen = QSize(200,200);
    rectScreen = QRect(QPoint(0,0),sizeScreen);
    pointCenter = QPointF(rectScreen.width()/2,
                         rectScreen.height()/2);
    setFixedSize(sizeScreen);
//
    setWindowTitle(QString("Датчик"));
    setAutoFillBackground(true);
    setStyleSheet("background-image:url(://dashboard1.png)");
}

/*
 *
 */
CMainWindow::~CMainWindow()
{

}

/*
 *
 */
void CMainWindow::showEvent(QShowEvent* event)
{
    if (!event->spontaneous() && !init)
    {
        qDebug() << "run";
        init = true;
    }
}

/*
 *
 */
void CMainWindow::paintEvent(QPaintEvent *event)
{
     Q_UNUSED(event);
//    QPixmap bkgnd("://dashboard1.png");
//    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
//  Создаём объект отрисовщика
    QPainter painter(this);
    drawDashBoard(&painter);
    drawDial(&painter);
    drawGiverArrow(&painter);
    drawCurrentArrow(&painter);
    setPalette(palette);
}

/*
 *  Фильтр событий
 */
bool CMainWindow::eventFilter(QObject *object, QEvent *event)
{

    return QWidget::eventFilter(object, event);
}

/*
 *
 */
void CMainWindow::wheelEvent(QWheelEvent *event)
{
    QPoint numPixels = event->pixelDelta();
    QPoint numDegrees = event->angleDelta() / 8;
    if (!numPixels.isNull())
    {

    }
    else if (!numDegrees.isNull())
    {
        QPoint numSteps = numDegrees / 15;
        int step = 50;
        if (numSteps.ry()>0)
        {
            if (giverValue<3000) giverValue += step;
        }
        else
        {
            if (giverValue>0) giverValue -= step;
        }

    }
    update();
    event->accept();
}

/*
 *
 */
void CMainWindow::drawDashBoard(QPainter *painter)
{
    QPen pen =  painter->pen();
    QRectF rect;
    pen.setBrush(QBrush(QColor(Qt::black)));
    rect = QRectF(
                 0.0,
                 0.0,
                 sizeScreen.width(),
                 rectScreen.height()
                 );
     int startAngle = -45 * 16;
     int spanAngle = 270 * 16;
     //painter.drawArc(rectangle, startAngle, spanAngle);
     painter->drawEllipse(rect);
     int stepArc = 15;
     rect = QRectF(
                 0.0+stepArc,
                 0.0+stepArc,
                 sizeScreen.width()-stepArc*2,
                 sizeScreen.height()-stepArc*2
                 );
     painter->drawEllipse(rect);
     stepArc += 30;
     rect = QRectF(
                 0.0+stepArc,
                 0.0+stepArc,
                 sizeScreen.width()-stepArc*2,
                 sizeScreen.height()-stepArc*2
                 );
     painter->drawEllipse(rect);
     stepArc += 15;
     rect = QRectF(
                 0.0+stepArc,
                 0.0+stepArc,
                 sizeScreen.width()-stepArc*2,
                 sizeScreen.height()-stepArc*2
                 );
     painter->drawEllipse(rect);

 //  secondary - второстипенные линиии
     QList<QLineF> listSecondaryLines;
     QLineF secondaryLine;
     pen.setBrush(QBrush(QColor(Qt::black)));
     pen.setWidth(1);
     float startRadius = 85.0;
     float endRadius = 100.0;
     float angleArrow = giverValue / (3000/270) - 225;
     QPointF startPoint = QPointF(
                 pointCenter.rx() + startRadius*cos(M_PI*angleArrow/180),
                 pointCenter.ry() + startRadius*sin(M_PI*angleArrow/180)
                 );
     QPointF endPoint = QPointF(
                 pointCenter.rx() + endRadius*cos(M_PI*angleArrow/180),
                 pointCenter.ry() + endRadius*sin(M_PI*angleArrow/180)
                 );

     secondaryLine = QLineF(startPoint,endPoint);
     listSecondaryLines.append(secondaryLine);
     painter->drawLines(listSecondaryLines);

//
     QLineF line;

//  Основоные линии
     startRadius = 85.0;
     endRadius = 75.0;
     pen.setBrush(QBrush(QColor(Qt::black)));
     pen.setWidth(2);
     for (int i = -225; i<=45; i+=9)
     {
         float angleArrow = i ;
         startPoint = QPointF(
                 pointCenter.rx() + startRadius*cos(M_PI*angleArrow/180),
                 pointCenter.ry() + startRadius*sin(M_PI*angleArrow/180)
                 );
         endPoint = QPointF(
                 pointCenter.rx() + endRadius*cos(M_PI*angleArrow/180),
                 pointCenter.ry() + endRadius*sin(M_PI*angleArrow/180)
                 );
         line = QLineF(startPoint,endPoint);
         painter->drawLine(line);
     }

 //  Дополнительные линии
     startRadius = 85.0;
     endRadius = 80.0;
     pen.setBrush(QBrush(QColor(Qt::black)));
     pen.setWidth(1);
     //painter->setPen(QPen(QBrush(QColor(Qt::black)), 1));
     for (int i = -225; i<=45; i+=3)
     {
         float angleArrow = i ;
         startPoint = QPointF(
                 pointCenter.rx() + startRadius*cos(M_PI*angleArrow/180),
                 pointCenter.ry() + startRadius*sin(M_PI*angleArrow/180)
                 );
         endPoint = QPointF(
                 pointCenter.rx() + endRadius*cos(M_PI*angleArrow/180),
                 pointCenter.ry() + endRadius*sin(M_PI*angleArrow/180)
                 );
         line = QLineF(startPoint,endPoint);
         painter->drawLine(line);
     }

//  Линии со значениями
     startRadius = 85.0;
     endRadius = 80.0;
     pen.setBrush(QBrush(QColor(Qt::red)));
     pen.setWidth(2);
     for (int i = -220; i<=30; i+=30)
     {
         float angleArrow = i ;
         startPoint = QPointF(
                 pointCenter.rx() + startRadius*cos(M_PI*angleArrow/180),
                 pointCenter.ry() + startRadius*sin(M_PI*angleArrow/180)
                 );
         endPoint = QPointF(
                 pointCenter.rx() + endRadius*cos(M_PI*angleArrow/180),
                 pointCenter.ry() + endRadius*sin(M_PI*angleArrow/180)
                 );
         line = QLineF(startPoint,endPoint);
         painter->drawLine(line);
     }


}

/*
 *
 */
void CMainWindow::drawDial(QPainter *painter)
{
    QPointF point;
    QFont font = painter->font();
    font.setPixelSize(10);
    painter->setFont(font);
//
    QPen pen = painter->pen();
    pen.setBrush(QBrush(QColor(Qt::black)));
    pen.setWidth(1);

    QSize size = QSize(20,10);

    QRectF rect = QRectF(point, size);
    QList<QRectF> listRectF;
    QFontMetricsF fontMetrics = painter->fontMetrics();
    QRectF borderRect = fontMetrics.tightBoundingRect(QString("3000"));

//  Корректировка
    int corrX = 0;
    int corrY = 0;
// 12
    corrX = 0;
    corrY = 75;
    point = QPointF(
                pointCenter.rx() - corrX - borderRect.width() / 2.0,
                pointCenter.ry() - corrY + borderRect.height() / 2.0);
    rect = QRectF(point, size);
    listRectF.append(rect);

// 1 - 11
    corrX = 40;
    corrY = 50;
    point = QPointF(
                pointCenter.rx() - corrX - borderRect.width() / 2.0,
                pointCenter.ry() - corrY - borderRect.height() / 2.0);
    rect = QRectF(point, size);
    listRectF.append(rect);

    point = QPointF(
                pointCenter.rx() + corrX - borderRect.width() / 2.0,
                pointCenter.ry() - corrY - borderRect.height() / 2.0);
    rect = QRectF(point, size);
    listRectF.append(rect);

// 2 - 10
    corrX = 60;
    corrY = 25;
    point = QPointF(
                pointCenter.rx() - corrX - borderRect.width() / 2.0,
                pointCenter.ry() - corrY - borderRect.height() / 2.0);
    rect = QRectF(point, size);
    listRectF.append(rect);

    point = QPointF(
                pointCenter.rx() + corrX - borderRect.width() / 2.0,
                pointCenter.ry() - corrY - borderRect.height() / 2.0);
    rect = QRectF(point, size);
    listRectF.append(rect);

// 3 - 9
    corrX = 65;
    corrY = 0;
    point = QPointF(
                pointCenter.rx() - corrX - borderRect.width() / 2.0,
                pointCenter.ry() - corrY - borderRect.height() / 2.0);
    rect = QRectF(point, size);
    listRectF.append(rect);

    point = QPointF(
                pointCenter.rx() + corrX - borderRect.width() / 2.0,
                pointCenter.ry() - corrY - borderRect.height() / 2.0);
    rect = QRectF(point, size);
    listRectF.append(rect);

// 4 - 8
    corrX = 60;
    corrY = -25;
    point = QPointF(
                pointCenter.rx() - corrX - borderRect.width() / 2.0,
                pointCenter.ry() - corrY - borderRect.height() / 2.0);
    rect = QRectF(point, size);
    listRectF.append(rect);

    point = QPointF(
                pointCenter.rx() + corrX - borderRect.width() / 2.0,
                pointCenter.ry() - corrY - borderRect.height() / 2.0);
    rect = QRectF(point, size);
    listRectF.append(rect);

// 5 - 7
    corrX = 40;
    corrY = -50;
    point = QPointF(
                pointCenter.rx() - corrX - borderRect.width() / 2.0,
                pointCenter.ry() - corrY - borderRect.height() / 2.0);
    rect = QRectF(point, size);
    listRectF.append(rect);

    point = QPointF(
                pointCenter.rx() + corrX - borderRect.width() / 2.0,
                pointCenter.ry() - corrY - borderRect.height() / 2.0);
    rect = QRectF(point, size);
    listRectF.append(rect);
    /*
    painter->drawText(
                rect,
                Qt::AlignCenter,
                QString("3000"),
                &borderRect
                );
        */
    painter->drawRects(listRectF);
}

/*
 *
 */
void CMainWindow::drawCurrentArrow(QPainter *painter)
{
    QLineF line;
    float startRadius = 85.0;
    float endRadius = 100.0;
    float angleArrow = giverValue / (3000/270) - 225;
    QPointF startPoint = QPointF(
                pointCenter.rx() + startRadius*cos(M_PI*angleArrow/180),
                pointCenter.ry() + startRadius*sin(M_PI*angleArrow/180)
                );
    QPointF endPoint = QPointF(
                pointCenter.rx() + endRadius*cos(M_PI*angleArrow/180),
                pointCenter.ry() + endRadius*sin(M_PI*angleArrow/180)
                );

    line = QLineF(startPoint,endPoint);
    painter->drawLine(line);
}

/*
 *
 */
void CMainWindow::drawGiverArrow(QPainter *painter)
{
    //  secondary - второстипенные линиии
    QLineF line;
    float startRadius = 40.0;
    float endRadius = 55.0;
    float angleArrow = giverValue / (3000/270) - 225;
    QPointF startPoint = QPointF(
                pointCenter.rx() + startRadius*cos(M_PI*angleArrow/180),
                pointCenter.ry() + startRadius*sin(M_PI*angleArrow/180)
                );
    QPointF endPoint = QPointF(
                pointCenter.rx() + endRadius*cos(M_PI*angleArrow/180),
                pointCenter.ry() + endRadius*sin(M_PI*angleArrow/180)
                );

    line = QLineF(startPoint,endPoint);
    painter->drawLine(line);
}
