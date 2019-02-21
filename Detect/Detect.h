#pragma once

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QImage>
#include <QMessageBox>
#include <QString>
#include <QFileDialog>

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\features2d\features2d.hpp>
#include <opencv2\legacy\legacy.hpp>
#include <opencv2\nonfree\nonfree.hpp>

using namespace cv;
using namespace std;

class Detect : public QMainWindow
{
	Q_OBJECT

public:
	Detect(QWidget *parent = Q_NULLPTR);

private:

	QLabel *ImgWindow;

	QLabel *Function1;
	QLabel *Function2;
	QLabel *Function3;
	QLabel *Function4;

	QLineEdit *SinglePic;
	QLineEdit *DoubPic1, *DoubPic2;
	QLineEdit *TripPic1, *TripPic2, *TripPic3;
	QLineEdit *QuadPic1, *QuadPic2, *QuadPic3, *QuadPic4;

	QPushButton *SgSelect;
	QPushButton *DbSelect1, *DbSelect2;
	QPushButton *TpSelect1, *TpSelect2, *TpSelect3;
	QPushButton *QdSelect1, *QdSelect2, *QdSelect3, *QdSelect4;

	QPushButton *Func1Act;
	QPushButton *Func2Act;
	QPushButton *Func3Act;
	QPushButton *Func4Act;

	string singleFile;
	string doubFile1, doubFile2;
	string tripFile1, tripFile2, tripFile3;
	string quadFile1, quadFile2, quadFile3, quadFile4;

	public slots:
	void selectSingle();
	void selectDoub1();
	void selectDoub2();
	void selectTrip1();
	void selectTrip2();
	void selectTrip3();
	void selectQuad1();
	void selectQuad2();
	void selectQuad3();
	void selectQuad4();

	void ComputeCorner();
	void DoubMatchPoints();
	void TripMatchPoints();
	void QuadMatchPoints();
};
