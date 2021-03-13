#ifndef __LOADCATOON_H__
#define __LOADCATOON_H__

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QMap>


/*
	����:https://github.com/superlomo/CustomControls-Qt/blob/master/mainwindow.cpp
*/
struct Location
{
public:
	explicit Location(float _x, float _y) { x = _x; y = _y; }
	float x;
	float y;
};

class Loading : public QWidget
{
	Q_OBJECT
public:
	explicit Loading(QWidget *parent = nullptr);
	//����Բ�����
	void setDotCount(int);
	//���õ���ɫ
	void setDotColor(const QColor&);
	//��ʼ
	void start();
	//ֹͣ
	void stop();
	//����Բ�����ֱ��
	void setMaxDiameter(float);
	//����Բ����Сֱ��
	void setMinDiameter(float);

private:
	//ˢ�¼���
	int _index;
	//�����ɫ
	QColor _dotColor;
	//��ĸ���
	int _count;
	//Բ����Сֱ��
	float _minDiameter;
	//Բ�����ֱ��
	float _maxDiameter;
	//����Բ��
	void paintDot(QPainter &);
	//����
	int _i;
	//ʱ���� ��λ������(ms)
	int _interval;
	//��ʱ��
	QTimer timer;
	//��������߳�
	float _squareWidth;
	//Բ��ֱ��
	float _centerDistance;
	//ֱ���б�
	QList<float> radiiList;
	//Բ�������б�
	QList<Location> locationList;

	//����
	void caculate();

protected:
	void paintEvent(QPaintEvent *event);
	void resizeEvent(QResizeEvent *event);
signals:

public slots :

private slots :
	void refresh();
};

#endif // __LOADCATOON_H__