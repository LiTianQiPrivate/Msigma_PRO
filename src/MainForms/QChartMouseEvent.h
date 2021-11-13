#ifndef QCHARTMOUSEEVENT_H
#define QCHARTMOUSEEVENT_H

#include <QObject>
#include <QtCharts/QChartGlobal>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QCandlestickSet>
#include <QtCharts/QPieSlice>
#include <QtCharts/QAbstractBarSeries>
#include <QtCharts/QPercentBarSeries>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QLegend>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtCore/QRandomGenerator>
#include <QtCharts/QBarCategoryAxis>
#include <QtWidgets/QApplication>
#include <QtCharts/QValueAxis>
#include <QChartView>
#include <QMouseEvent>
#include <QGraphicsSimpleTextItem>
#include <QGestureEvent>

QT_CHARTS_USE_NAMESPACE

class QChartMouseEvent : public QChartView
{
    Q_OBJECT

public:
    explicit QChartMouseEvent(QWidget *parent = nullptr);
    ~QChartMouseEvent();
signals:
    void mouseMoving(QPointF point);
    void mousePress(QPointF point);
    void mouseLeftRelease(QPointF point);
    void mouseRightRelease();
    void mouseLeave();

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void leaveEvent(QEvent* event);

private:
    bool m_isPress = false;
    double m_xMin,m_xMax,m_yMin,m_yMax = 0.0;
    QGraphicsSimpleTextItem* m_coordItem = NULL;
    QGraphicsSimpleTextItem* m_coordPointFront = NULL;
    QGraphicsSimpleTextItem* m_coordPointBack = NULL;
};

#endif // QCHARTMOUSEEVENT_H
