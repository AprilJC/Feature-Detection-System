#include "Detect.h"

void mergeImg(Mat & dst, Mat &src1, Mat &src2);

vector<Point2f> ComputeCorner1(int i, Mat& roi1);
vector<Point2f> ComputeCorner2(int i, Mat& roi1);
vector<Point2f> ComputeCorner3(int i, Mat& roi1);
vector<Point2f> ComputeCorner4(int i, Mat& roi1);

void SaveFiles1(int i, vector<Point2f>& corner1, string seq);
void SaveFiles2(int i, vector<Point2f>& corner1, string seq);
void SaveFiles3(int i, vector<Point2f>& corner1, string seq);
void SaveFiles4(int i, vector<Point2f>& corner1, string seq);

void SaveFiles11(int i, vector<Point2f>& corner1, string seq);
void SaveFiles22(int i, vector<Point2f>& corner1, string seq);
void SaveFiles33(int i, vector<Point2f>& corner1, string seq);
void SaveFiles44(int i, vector<Point2f>& corner1, string seq);

void MatchPoint1_2(int i, vector<int> letters, Mat& roi1, Mat& roi2, vector<KeyPoint>& keyPoint1, vector<KeyPoint>& keyPoint2);
void MatchPoint1_3(int i, vector<int> letters, Mat& roi1, Mat& roi2, vector<KeyPoint>& keyPoint1, vector<KeyPoint>& keyPoint2);
void MatchPoint1_4(int i, vector<int> letters, Mat& roi1, Mat& roi2, vector<KeyPoint>& keyPoint1, vector<KeyPoint>& keyPoint2);
void MatchPoint2_3(int i, vector<int> letters, Mat& roi1, Mat& roi2, vector<KeyPoint>& keyPoint1, vector<KeyPoint>& keyPoint2);
void MatchPoint2_4(int i, vector<int> letters, Mat& roi1, Mat& roi2, vector<KeyPoint>& keyPoint1, vector<KeyPoint>& keyPoint2);
void MatchPoint3_4(int i, vector<int> letters, Mat& roi1, Mat& roi2, vector<KeyPoint>& keyPoint1, vector<KeyPoint>& keyPoint2);
void MatchPoint1_2_3(int i, vector<int> letters, Mat& roi1, Mat& roi2, Mat& roi3, vector<KeyPoint>& keyPoint1, vector<KeyPoint>& keyPoint2, vector<KeyPoint>& keyPoint3);
void MatchPoint1_2_4(int i, vector<int> letters, Mat& roi1, Mat& roi2, Mat& roi3, vector<KeyPoint>& keyPoint1, vector<KeyPoint>& keyPoint2, vector<KeyPoint>& keyPoint3);
void MatchPoint1_3_4(int i, vector<int> letters, Mat& roi1, Mat& roi2, Mat& roi3, vector<KeyPoint>& keyPoint1, vector<KeyPoint>& keyPoint2, vector<KeyPoint>& keyPoint3);
void MatchPoint2_3_4(int i, vector<int> letters, Mat& roi1, Mat& roi2, Mat& roi3, vector<KeyPoint>& keyPoint1, vector<KeyPoint>& keyPoint2, vector<KeyPoint>& keyPoint3);
void MatchPoint1_2_3_4(int i, vector<int> letters, Mat& roi1, Mat& roi2, Mat& roi3, Mat& roi4, vector<KeyPoint>& keyPoint1, vector<KeyPoint>& keyPoint2, vector<KeyPoint>& keyPoint3, vector<KeyPoint>& keyPoint4);

void Drawlines1_2(int i, string seq1, string seq2, ofstream& outfile, Mat&outImg, vector<KeyPoint>& keyPoint1, vector<KeyPoint>& keyPoint2);
void Drawlines1_3(int i, string seq1, string seq2, ofstream& outfile, Mat&outImg, vector<KeyPoint>& keyPoint1, vector<KeyPoint>& keyPoint2);
void Drawlines1_4(int i, string seq1, string seq2, ofstream& outfile, Mat&outImg, vector<KeyPoint>& keyPoint1, vector<KeyPoint>& keyPoint2);
void Drawlines2_3(int i, string seq1, string seq2, ofstream& outfile, Mat&outImg, vector<KeyPoint>& keyPoint1, vector<KeyPoint>& keyPoint2);
void Drawlines2_4(int i, string seq1, string seq2, ofstream& outfile, Mat&outImg, vector<KeyPoint>& keyPoint1, vector<KeyPoint>& keyPoint2);
void Drawlines3_4(int i, string seq1, string seq2, ofstream& outfile, Mat&outImg, vector<KeyPoint>& keyPoint1, vector<KeyPoint>& keyPoint2);

Detect::Detect(QWidget *parent)
	: QMainWindow(parent)
{
	move(200, 10);
	setFixedSize(1200, 905);

	ImgWindow = new QLabel(this);
	ImgWindow->move(10, 15);
	ImgWindow->setFixedSize(1180, 780);

	
	QImage image;
	if (!image.load("E:\\Biyesheji\\Detect\\Wallpaper.jpg"))
	{
	QMessageBox::information(this, tr("Failed to open the JPG"), tr("Failed to open the JPG!"));
	}
	QImage newImage = image.scaled(ImgWindow->width(), ImgWindow->height(), Qt::KeepAspectRatio);
	ImgWindow->setPixmap(QPixmap::fromImage(newImage));
	

	Function1 = new QLabel("Gen_cors", this);
	Function1->move(10, 800);
	Function2 = new QLabel("Doub_mth", this);
	Function2->move(10, 825);
	Function3 = new QLabel("Trip_mth", this);
	Function3->move(10, 850);
	Function4 = new QLabel("Quad_mth", this);
	Function4->move(10, 875);

	SinglePic = new QLineEdit(this);
	SinglePic->setFixedSize(800, 20);
	SinglePic->move(100, 802);
	DoubPic1 = new QLineEdit(this);
	DoubPic1->setFixedSize(395, 20);
	DoubPic1->move(100, 827);
	DoubPic2 = new QLineEdit(this);
	DoubPic2->setFixedSize(395, 20);
	DoubPic2->move(505, 827);
	TripPic1 = new QLineEdit(this);
	TripPic1->setFixedSize(260, 20);
	TripPic1->move(100, 852);
	TripPic2 = new QLineEdit(this);
	TripPic2->setFixedSize(260, 20);
	TripPic2->move(370, 852);
	TripPic3 = new QLineEdit(this);
	TripPic3->setFixedSize(260, 20);
	TripPic3->move(640, 852);
	QuadPic1 = new QLineEdit(this);
	QuadPic1->setFixedSize(191, 20);
	QuadPic1->move(100, 877);
	QuadPic2 = new QLineEdit(this);
	QuadPic2->setFixedSize(191, 20);
	QuadPic2->move(303, 877);
	QuadPic3 = new QLineEdit(this);
	QuadPic3->setFixedSize(191, 20);
	QuadPic3->move(506, 877);
	QuadPic4 = new QLineEdit(this);
	QuadPic4->setFixedSize(191, 20);
	QuadPic4->move(709, 877);

	SgSelect = new QPushButton(this);
	SgSelect->move(910, 800);
	SgSelect->setFixedSize(230, 23);
	SgSelect->setText("Pic");
	DbSelect1 = new QPushButton(this);
	DbSelect1->move(910, 825);
	DbSelect1->setFixedSize(110, 23);
	DbSelect1->setText("Pic1");
	DbSelect2 = new QPushButton(this);
	DbSelect2->move(1030, 825);
	DbSelect2->setFixedSize(110, 23);
	DbSelect2->setText("Pic2");
	TpSelect1 = new QPushButton(this);
	TpSelect1->move(910, 850);
	TpSelect1->setFixedSize(70, 23);
	TpSelect1->setText("Pic1");
	TpSelect2 = new QPushButton(this);
	TpSelect2->move(990, 850);
	TpSelect2->setFixedSize(70, 23);
	TpSelect2->setText("Pic2");
	TpSelect3 = new QPushButton(this);
	TpSelect3->move(1070, 850);
	TpSelect3->setFixedSize(70, 23);
	TpSelect3->setText("Pic3");
	QdSelect1 = new QPushButton(this);
	QdSelect1->move(910, 875);
	QdSelect1->setFixedSize(50, 23);
	QdSelect1->setText("Pic1");
	QdSelect2 = new QPushButton(this);
	QdSelect2->move(970, 875);
	QdSelect2->setFixedSize(50, 23);
	QdSelect2->setText("Pic2");
	QdSelect3 = new QPushButton(this);
	QdSelect3->move(1030, 875);
	QdSelect3->setFixedSize(50, 23);
	QdSelect3->setText("Pic3");
	QdSelect4 = new QPushButton(this);
	QdSelect4->move(1090, 875);
	QdSelect4->setFixedSize(50, 23);
	QdSelect4->setText("Pic4");

	Func1Act = new QPushButton(this);
	Func1Act->move(1150, 800);
	Func1Act->setFixedSize(40, 23);
	Func1Act->setText("Go!");
	Func2Act = new QPushButton(this);
	Func2Act->move(1150, 825);
	Func2Act->setFixedSize(40, 23);
	Func2Act->setText("Go!");
	Func3Act = new QPushButton(this);
	Func3Act->move(1150, 850);
	Func3Act->setFixedSize(40, 23);
	Func3Act->setText("Go!");
	Func4Act = new QPushButton(this);
	Func4Act->move(1150, 875);
	Func4Act->setFixedSize(40, 23);
	Func4Act->setText("Go!");

	connect(SgSelect, SIGNAL(clicked()), this, SLOT(selectSingle()));
	connect(DbSelect1, SIGNAL(clicked()), this, SLOT(selectDoub1()));
	connect(DbSelect2, SIGNAL(clicked()), this, SLOT(selectDoub2()));
	connect(TpSelect1, SIGNAL(clicked()), this, SLOT(selectTrip1()));
	connect(TpSelect2, SIGNAL(clicked()), this, SLOT(selectTrip2()));
	connect(TpSelect3, SIGNAL(clicked()), this, SLOT(selectTrip3()));
	connect(QdSelect1, SIGNAL(clicked()), this, SLOT(selectQuad1()));
	connect(QdSelect2, SIGNAL(clicked()), this, SLOT(selectQuad2()));
	connect(QdSelect3, SIGNAL(clicked()), this, SLOT(selectQuad3()));
	connect(QdSelect4, SIGNAL(clicked()), this, SLOT(selectQuad4()));

	connect(Func1Act, SIGNAL(clicked()), this, SLOT(ComputeCorner()));
	connect(Func2Act, SIGNAL(clicked()), this, SLOT(DoubMatchPoints()));
	connect(Func3Act, SIGNAL(clicked()), this, SLOT(TripMatchPoints()));
	connect(Func4Act, SIGNAL(clicked()), this, SLOT(QuadMatchPoints()));
}

void Detect::selectSingle()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Choose file"), "E:/Biyesheji/Detection/Detection", tr("JPG(*jpg)"));
	SinglePic->setText(filename);
	singleFile = filename.toStdString();
}

void Detect::selectDoub1()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Choose file"), "E:/Biyesheji/Detection/Detection", tr("JPG(*jpg)"));
	DoubPic1->setText(filename);
	doubFile1 = filename.toStdString();
}

void Detect::selectDoub2()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Choose file"), "E:/Biyesheji/Detection/Detection", tr("JPG(*jpg)"));
	DoubPic2->setText(filename);
	doubFile2 = filename.toStdString();
}

void Detect::selectTrip1()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Choose file"), "E:/Biyesheji/Detection/Detection", tr("JPG(*jpg)"));
	TripPic1->setText(filename);
	tripFile1 = filename.toStdString();
}

void Detect::selectTrip2()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Choose file"), "E:/Biyesheji/Detection/Detection", tr("JPG(*jpg)"));
	TripPic2->setText(filename);
	tripFile2 = filename.toStdString();
}

void Detect::selectTrip3()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Choose file"), "E:/Biyesheji/Detection/Detection", tr("JPG(*jpg)"));
	TripPic3->setText(filename);
	tripFile3 = filename.toStdString();
}

void Detect::selectQuad1()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Choose file"), "E:/Biyesheji/Detection/Detection", tr("JPG(*jpg)"));
	QuadPic1->setText(filename);
	quadFile1 = filename.toStdString();
}

void Detect::selectQuad2()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Choose file"), "E:/Biyesheji/Detection/Detection", tr("JPG(*jpg)"));
	QuadPic2->setText(filename);
	quadFile2 = filename.toStdString();
}

void Detect::selectQuad3()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Choose file"), "E:/Biyesheji/Detection/Detection", tr("JPG(*jpg)"));
	QuadPic3->setText(filename);
	quadFile3 = filename.toStdString();
}

void Detect::selectQuad4()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Choose file"), "E:/Biyesheji/Detection/Detection", tr("JPG(*jpg)"));
	QuadPic4->setText(filename);
	quadFile4 = filename.toStdString();
}

void Detect::ComputeCorner()
{
	string img = singleFile;
	string seq = img.substr(img.find(".") - 1, 1);


	//---------------读取图像，预处理---------------------//
	Mat Img1 = imread(img); //读取图像
	if (Img1.empty())
	{
		QMessageBox::information(this, tr(seq.c_str()), tr(img.c_str()));
		//QMessageBox::information(this, tr("Can not load image!"), tr("Can not load image!"));
		return;
	}
	vector<Mat> new_image1, new_image2;
	split(Img1, new_image1);
	Img1 = new_image1.at(0);//取单通道图像1
	QMessageBox::information(this, tr("Finished color dividing."), tr("Finished color dividing."));
	//--------------读取区域数据进行记录------------//
	ifstream infile;   //输入流
	ofstream outfile;   //输出流

	infile.open("E:\\Biyesheji\\Detection\\Detection\\corner" + seq + ".txt", ios::in); //打开数据文件
	if (!infile.is_open())
		QMessageBox::information(this, tr("Open file failure!"), tr("Open file failure!")); //文件不存在
	string out;
	double data1[200], data2[200], data3[200], data4[200];
	while (!infile.eof())
	{
		for (int i = 0; i < 200; i++)
		{
			infile >> data1[i] >> data2[i] >> data3[i] >> data4[i];
		}
	}  //读取数据并存储在data中
	QMessageBox::information(this, tr("Finished reading areas."), tr("Finished reading areas."));
	//-----------------区域划分----------------//

	outfile.open("E:\\Biyesheji\\Detection\\Detection\\result" + seq + ".txt", ios::out);   //每次写都定位的文件结尾，不会丢失原来的内容，用out则会丢失原来的内容
	if (!outfile.is_open())
		QMessageBox::information(this, tr("Open file failure!"), tr("Open file failure!")); //输出文件不存在
	double a, b, c, d;
	vector<Point2f> corners(800);
	Mat Img = Img1.clone();
	Mat roi1;   //循环前预定义

	int total;
	if (seq == "1") {
		total = 106;
		string files;
		files = "E:\\Biyesheji\\Detection\\Detection\\match corner\\result";
		fstream fout1(files + seq + "1(1&2).txt", ios::out | ios::trunc);
		fstream fout2(files + seq + "2(1&2).txt", ios::out | ios::trunc);
		fstream fout3(files + seq + "3(1&2).txt", ios::out | ios::trunc);
		fstream fout4(files + seq + "4(1&2).txt", ios::out | ios::trunc);
		fstream fout5(files + seq + "1(1&3).txt", ios::out | ios::trunc);
		fstream fout6(files + seq + "2(1&3).txt", ios::out | ios::trunc);
		fstream fout7(files + seq + "3(1&3).txt", ios::out | ios::trunc);
		fstream fout8(files + seq + "4(1&3).txt", ios::out | ios::trunc);
		fstream fout9(files + seq + "1(1&4).txt", ios::out | ios::trunc);
		fstream fout10(files + seq + "2(1&4).txt", ios::out | ios::trunc);
		fstream fout11(files + seq + "3(1&4).txt", ios::out | ios::trunc);
		fstream fout12(files + seq + "4(1&4).txt", ios::out | ios::trunc);
	}
	else if (seq == "2") {
		total = 106;
		string files;
		files = "E:\\Biyesheji\\Detection\\Detection\\match corner\\result";
		fstream fout1(files + seq + "1(1&2).txt", ios::out | ios::trunc);
		fstream fout2(files + seq + "2(1&2).txt", ios::out | ios::trunc);
		fstream fout3(files + seq + "3(1&2).txt", ios::out | ios::trunc);
		fstream fout4(files + seq + "4(1&2).txt", ios::out | ios::trunc);
		fstream fout5(files + seq + "1(2&3).txt", ios::out | ios::trunc);
		fstream fout6(files + seq + "2(2&3).txt", ios::out | ios::trunc);
		fstream fout7(files + seq + "3(2&3).txt", ios::out | ios::trunc);
		fstream fout8(files + seq + "4(2&3).txt", ios::out | ios::trunc);
		fstream fout9(files + seq + "1(2&4).txt", ios::out | ios::trunc);
		fstream fout10(files + seq + "2(2&4).txt", ios::out | ios::trunc);
		fstream fout11(files + seq + "3(2&4).txt", ios::out | ios::trunc);
		fstream fout12(files + seq + "4(2&4).txt", ios::out | ios::trunc);
	}
	else if (seq == "3") {
		total = 94;
		string files;
		files = "E:\\Biyesheji\\Detection\\Detection\\match corner\\result";
		fstream fout1(files + seq + "1(1&3).txt", ios::out | ios::trunc);
		fstream fout2(files + seq + "2(1&3).txt", ios::out | ios::trunc);
		fstream fout3(files + seq + "3(1&3).txt", ios::out | ios::trunc);
		fstream fout4(files + seq + "4(1&3).txt", ios::out | ios::trunc);
		fstream fout5(files + seq + "1(2&3).txt", ios::out | ios::trunc);
		fstream fout6(files + seq + "2(2&3).txt", ios::out | ios::trunc);
		fstream fout7(files + seq + "3(2&3).txt", ios::out | ios::trunc);
		fstream fout8(files + seq + "4(2&3).txt", ios::out | ios::trunc);
		fstream fout9(files + seq + "1(3&4).txt", ios::out | ios::trunc);
		fstream fout10(files + seq + "2(3&4).txt", ios::out | ios::trunc);
		fstream fout11(files + seq + "3(3&4).txt", ios::out | ios::trunc);
		fstream fout12(files + seq + "4(3&4).txt", ios::out | ios::trunc);
	}
	else if (seq == "4") {
		total = 93;
		string files;
		files = "E:\\Biyesheji\\Detection\\Detection\\match corner\\result";
		fstream fout1(files + seq + "1(1&4).txt", ios::out | ios::trunc);
		fstream fout2(files + seq + "2(1&4).txt", ios::out | ios::trunc);
		fstream fout3(files + seq + "3(1&4).txt", ios::out | ios::trunc);
		fstream fout4(files + seq + "4(1&4).txt", ios::out | ios::trunc);
		fstream fout5(files + seq + "1(2&4).txt", ios::out | ios::trunc);
		fstream fout6(files + seq + "2(2&4).txt", ios::out | ios::trunc);
		fstream fout7(files + seq + "3(2&4).txt", ios::out | ios::trunc);
		fstream fout8(files + seq + "4(2&4).txt", ios::out | ios::trunc);
		fstream fout9(files + seq + "1(3&4).txt", ios::out | ios::trunc);
		fstream fout10(files + seq + "2(3&4).txt", ios::out | ios::trunc);
		fstream fout11(files + seq + "3(3&4).txt", ios::out | ios::trunc);
		fstream fout12(files + seq + "4(3&4).txt", ios::out | ios::trunc);
	}

	if (seq == "1") {
		total = 106;
		string files;
		files = "E:\\Biyesheji\\Detection\\Detection\\match corner\\result";
		fstream fout1(files + seq + "1(1&2&3).txt", ios::out | ios::trunc);
		fstream fout2(files + seq + "2(1&2&3).txt", ios::out | ios::trunc);
		fstream fout3(files + seq + "3(1&2&3).txt", ios::out | ios::trunc);
		fstream fout4(files + seq + "4(1&2&3).txt", ios::out | ios::trunc);
		fstream fout5(files + seq + "1(1&3&4).txt", ios::out | ios::trunc);
		fstream fout6(files + seq + "2(1&3&4).txt", ios::out | ios::trunc);
		fstream fout7(files + seq + "3(1&3&4).txt", ios::out | ios::trunc);
		fstream fout8(files + seq + "4(1&3&4).txt", ios::out | ios::trunc);
		fstream fout9(files + seq + "1(1&2&3&4).txt", ios::out | ios::trunc);
		fstream fout10(files + seq + "2(1&2&3&4).txt", ios::out | ios::trunc);
		fstream fout11(files + seq + "3(1&2&3&4).txt", ios::out | ios::trunc);
		fstream fout12(files + seq + "4(1&2&3&4).txt", ios::out | ios::trunc);
		fstream fout13(files + seq + "1(1&2&4).txt", ios::out | ios::trunc);
		fstream fout14(files + seq + "2(1&2&4).txt", ios::out | ios::trunc);
		fstream fout15(files + seq + "3(1&2&4).txt", ios::out | ios::trunc);
		fstream fout16(files + seq + "4(1&2&4).txt", ios::out | ios::trunc);
	}
	else if (seq == "2") {
		total = 106;
		string files;
		files = "E:\\Biyesheji\\Detection\\Detection\\match corner\\result";
		fstream fout1(files + seq + "1(1&2&3).txt", ios::out | ios::trunc);
		fstream fout2(files + seq + "2(1&2&3).txt", ios::out | ios::trunc);
		fstream fout3(files + seq + "3(1&2&3).txt", ios::out | ios::trunc);
		fstream fout4(files + seq + "4(1&2&3).txt", ios::out | ios::trunc);
		fstream fout5(files + seq + "1(2&3&4).txt", ios::out | ios::trunc);
		fstream fout6(files + seq + "2(2&3&4).txt", ios::out | ios::trunc);
		fstream fout7(files + seq + "3(2&3&4).txt", ios::out | ios::trunc);
		fstream fout8(files + seq + "4(2&3&4).txt", ios::out | ios::trunc);
		fstream fout9(files + seq + "1(1&2&3&4).txt", ios::out | ios::trunc);
		fstream fout10(files + seq + "2(1&2&3&4).txt", ios::out | ios::trunc);
		fstream fout11(files + seq + "3(1&2&3&4).txt", ios::out | ios::trunc);
		fstream fout12(files + seq + "4(1&2&3&4).txt", ios::out | ios::trunc);
		fstream fout13(files + seq + "1(1&2&4).txt", ios::out | ios::trunc);
		fstream fout14(files + seq + "2(1&2&4).txt", ios::out | ios::trunc);
		fstream fout15(files + seq + "3(1&2&4).txt", ios::out | ios::trunc);
		fstream fout16(files + seq + "4(1&2&4).txt", ios::out | ios::trunc);
	}
	else if (seq == "3") {
		total = 94;
		string files;
		files = "E:\\Biyesheji\\Detection\\Detection\\match corner\\result";
		fstream fout1(files + seq + "1(1&2&3).txt", ios::out | ios::trunc);
		fstream fout2(files + seq + "2(1&2&3).txt", ios::out | ios::trunc);
		fstream fout3(files + seq + "3(1&2&3).txt", ios::out | ios::trunc);
		fstream fout4(files + seq + "4(1&2&3).txt", ios::out | ios::trunc);
		fstream fout5(files + seq + "1(2&3&4).txt", ios::out | ios::trunc);
		fstream fout6(files + seq + "2(2&3&4).txt", ios::out | ios::trunc);
		fstream fout7(files + seq + "3(2&3&4).txt", ios::out | ios::trunc);
		fstream fout8(files + seq + "4(2&3&4).txt", ios::out | ios::trunc);
		fstream fout9(files + seq + "1(1&2&3&4).txt", ios::out | ios::trunc);
		fstream fout10(files + seq + "2(1&2&3&4).txt", ios::out | ios::trunc);
		fstream fout11(files + seq + "3(1&2&3&4).txt", ios::out | ios::trunc);
		fstream fout12(files + seq + "4(1&2&3&4).txt", ios::out | ios::trunc);
		fstream fout13(files + seq + "1(1&3&4).txt", ios::out | ios::trunc);
		fstream fout14(files + seq + "2(1&3&4).txt", ios::out | ios::trunc);
		fstream fout15(files + seq + "3(1&3&4).txt", ios::out | ios::trunc);
		fstream fout16(files + seq + "4(1&3&4).txt", ios::out | ios::trunc);
	}
	else if (seq == "4") {
		total = 93;
		string files;
		files = "E:\\Biyesheji\\Detection\\Detection\\match corner\\result";
		fstream fout1(files + seq + "1(1&3&4).txt", ios::out | ios::trunc);
		fstream fout2(files + seq + "2(1&3&4).txt", ios::out | ios::trunc);
		fstream fout3(files + seq + "3(1&3&4).txt", ios::out | ios::trunc);
		fstream fout4(files + seq + "4(1&3&4).txt", ios::out | ios::trunc);
		fstream fout5(files + seq + "1(2&3&4).txt", ios::out | ios::trunc);
		fstream fout6(files + seq + "2(2&3&4).txt", ios::out | ios::trunc);
		fstream fout7(files + seq + "3(2&3&4).txt", ios::out | ios::trunc);
		fstream fout8(files + seq + "4(2&3&4).txt", ios::out | ios::trunc);
		fstream fout9(files + seq + "1(1&2&3&4).txt", ios::out | ios::trunc);
		fstream fout10(files + seq + "2(1&2&3&4).txt", ios::out | ios::trunc);
		fstream fout11(files + seq + "3(1&2&3&4).txt", ios::out | ios::trunc);
		fstream fout12(files + seq + "4(1&2&3&4).txt", ios::out | ios::trunc);
		fstream fout13(files + seq + "1(1&2&4).txt", ios::out | ios::trunc);
		fstream fout14(files + seq + "2(1&2&4).txt", ios::out | ios::trunc);
		fstream fout15(files + seq + "3(1&2&4).txt", ios::out | ios::trunc);
		fstream fout16(files + seq + "4(1&2&4).txt", ios::out | ios::trunc);
	}
	for (int i = 0; i < total; i++)
	{
		a = data1[i];
		b = data2[i];
		c = data3[i];
		d = data4[i];
		cv::Rect rect(a, b, c, d); //划分区域
		int cols = Img.cols, rows = Img.rows;
		if (cols - 1 - rect.x < rect.width || rows - 1 - rect.y < rect.height)
			return; //ROI越界，返回
		roi1 = Img(Rect(rect.x, rect.y, rect.width, rect.height));
		Mat copyImage;
		copyImage = roi1.clone();

		//------------利用goodFeaturesToTrack函数检测角点-----//

		//goodFeaturesToTrack函数参数设置

		vector<Point2f> corner(200);

		if (seq == "1") corner = ComputeCorner1(i, roi1);
		else if (seq == "2") corner = ComputeCorner2(i, roi1);
		else if (seq == "3") corner = ComputeCorner3(i, roi1);
		else if (seq == "4") corner = ComputeCorner4(i, roi1);

		//----------画图-----------------//
		outfile << "** Number of corners detected in area " << i << ":" << corner.size() << endl;
		vector<Point2f> corner1(corner.size());
		for (int j = 0; j < corner.size(); j++)
		{
			outfile << "点" << j << "\t" << "(" << corner[j].x + a << "," << corner[j].y + b << ")" << "\t" << endl;
			corner1[j] = Point2f(corner[j].x + a, corner[j].y + b);
			corners.push_back(corner1[j]);
		}
		if (seq == "1") {
			SaveFiles1(i, corner1, seq);
			SaveFiles11(i, corner1, seq);
		}
		else if (seq == "2") {
			SaveFiles2(i, corner1, seq);
			SaveFiles22(i, corner1, seq);
		}
		else if (seq == "3") {
			SaveFiles3(i, corner1, seq);
			SaveFiles33(i, corner1, seq);
		}
		else if (seq == "4") {
			SaveFiles4(i, corner1, seq);
			SaveFiles44(i, corner1, seq);
		}

	}

	int r = 5;
	for (int l = 0; l < corners.size(); l++)
	{
		circle(Img, corners[l], r, Scalar(0, 0, 255), 4, 8);
	}

	//显示图像并保存
	string wt_img = "E:/Biyesheji/Detection/Detection/detected picture/Detected" + seq + ".jpg";
	imwrite(wt_img, Img);

	QImage image;
	if (!image.load(QString::fromStdString(wt_img)))
	{
		QMessageBox::information(this, tr("Failed to open the JPG!"), tr("Failed to open the JPG!"));
	}
	QImage newImage = image.scaled(ImgWindow->width(), ImgWindow->height(), Qt::KeepAspectRatio);
	ImgWindow->setPixmap(QPixmap::fromImage(newImage));
}

void Detect::DoubMatchPoints()
{
	string seq1, seq2;

	seq1 = doubFile1.substr(doubFile1.find(".") - 1, 1);
	seq2 = doubFile2.substr(doubFile2.find(".") - 1, 1);

	//---------------读取图像，预处理---------------------//
	Mat Img1 = imread("E:\\Biyesheji\\Detection\\Detection\\detected picture\\Detected" + seq1 + ".jpg"); //读取图像
	Mat Img2 = imread("E:\\Biyesheji\\Detection\\Detection\\detected picture\\Detected" + seq2 + ".jpg"); //读取图像

	if (Img1.empty())
	{
		QMessageBox::information(this, tr("Can not load image!"), tr("Can not load image!"));
	}
	if (Img2.empty())
	{
		QMessageBox::information(this, tr("Can not load image!"), tr("Can not load image!"));
	}

	//--------------读取区域数据进行记录------------//
	ifstream infiles, infile;   //输入流
	ofstream& function(ofstream &outfile);
	infile.open("E:\\Biyesheji\\Detection\\Detection\\match area\\corner" + seq1 + "(" + seq1 + "&" + seq2 + ").txt", ios::in); //打开数据文件1
	infiles.open("E:\\Biyesheji\\Detection\\Detection\\match area\\corner" + seq2 + "(" + seq1 + "&" + seq2 + ").txt", ios::in);//打开数据文件2
	if (!infile.is_open())
		QMessageBox::information(this, tr("Open file failure!"), tr("Open file failure!"));
	if (!infiles.is_open())
		QMessageBox::information(this, tr("Open file failure!"), tr("Open file failure!"));
	string out;
	double data1[200], data2[200], data3[200], data4[200];
	double data5[200], data6[200], data7[200], data8[200];
	QMessageBox::information(this, tr("Finish reading files."), tr("Finish reading files."));

	int total;
	if (seq1 == "1" && seq2 == "2") total = 95;
	else if (seq1 == "1" && seq2 == "3") total = 85;
	else if (seq1 == "1" && seq2 == "4") total = 93;
	else if (seq1 == "2" && seq2 == "3") total = 93;
	else if (seq1 == "2" && seq2 == "4") total = 85;
	else if (seq1 == "3" && seq2 == "4") total = 75;

	while (!infile.eof())
	{
		for (int i = 0; i < total; i++)   //1&3
		{
			infile >> data1[i] >> data2[i] >> data3[i] >> data4[i];
		}
	}
	while (!infiles.eof())
	{
		for (int i = 0; i < total; i++)   //1&3
		{
			infiles >> data5[i] >> data6[i] >> data7[i] >> data8[i];
		}
	}  //读取数据并存储在data中
	QMessageBox::information(this, tr("Reading datas finished."), tr("Reading datas finished."));
	string filename;
	filename = "E:\\Biyesheji\\Detection\\Detection\\match result\\";
	ofstream outfile(filename + "match result" + seq1 + "&" + seq2 + ".txt", ios::out);
	if (!outfile.is_open())
		QMessageBox::information(this, tr("Open file failure!"), tr("Open file failure!"));
	//---------------------区域划分及处理-------------------//
	Mat outImg;
	mergeImg(outImg, Img1, Img2);
	double a, b, c, d, e, f, g, h;
	Mat Img_1 = Img1.clone(), Img_2 = Img2.clone();
	Mat roi1, roi2;

	for (int i = 0; i < total; i++)
	{
		a = data1[i];
		b = data2[i];
		c = data3[i];
		d = data4[i];
		e = data5[i];
		f = data6[i];
		g = data7[i];
		h = data8[i];

		vector<int> letters;
		letters.push_back(a);
		letters.push_back(b);
		letters.push_back(e);
		letters.push_back(f);

		cv::Rect rect1(a, b, c, d); //划分区域
		int cols1 = Img_1.cols, rows1 = Img_1.rows;
		if (cols1 - 1 - rect1.x < rect1.width || rows1 - 1 - rect1.y < rect1.height)
			return; //ROI越界，返回
		roi1 = Img_1(Rect(rect1.x, rect1.y, rect1.width, rect1.height));
		Mat copyImage1;
		copyImage1 = roi1.clone();

		cv::Rect rect2(e, f, g, h); //划分区域
		int cols2 = Img_2.cols, rows2 = Img_2.rows;
		if (cols2 - 1 - rect2.x < rect2.width || rows2 - 1 - rect2.y < rect2.height)
			return; //ROI越界，返回
		roi2 = Img_2(Rect(rect2.x, rect2.y, rect2.width, rect2.height));
		Mat copyImage2;
		copyImage2 = roi2.clone();

		//cout << "Dividing areas finished" << endl;
		//------------区域内检测角点，根据x坐标进行分类-----//
		vector<KeyPoint> keyPoint1(200), keyPoint2(200);

		if (seq1 == "1" && seq2 == "2") MatchPoint1_2(i, letters, roi1, roi2, keyPoint1, keyPoint2);
		else if (seq1 == "1" && seq2 == "3") MatchPoint1_3(i, letters, roi1, roi2, keyPoint1, keyPoint2);
		else if (seq1 == "1" && seq2 == "4") MatchPoint1_4(i, letters, roi1, roi2, keyPoint1, keyPoint2);
		else if (seq1 == "2" && seq2 == "3") MatchPoint2_3(i, letters, roi1, roi2, keyPoint1, keyPoint2);
		else if (seq1 == "2" && seq2 == "4") MatchPoint2_4(i, letters, roi1, roi2, keyPoint1, keyPoint2);
		else if (seq1 == "3" && seq2 == "4") MatchPoint3_4(i, letters, roi1, roi2, keyPoint1, keyPoint2);
		else;

		//cout << "Detecting finished" << endl;
		//----------画图-----------------//

		for (int k = 0; k < keyPoint1.size(); k++) {
			keyPoint1[k].pt.x = keyPoint1[k].pt.x + a;
			keyPoint1[k].pt.y = keyPoint1[k].pt.y + b;
		}
		for (int k = 0; k < keyPoint2.size(); k++) {
			keyPoint2[k].pt.x = keyPoint2[k].pt.x + e + Img1.cols;
			keyPoint2[k].pt.y = keyPoint2[k].pt.y + f;
		}
		outfile << "total match points in area" << i << ":" << keyPoint1.size() << endl;
		if (seq1 == "1" && seq2 == "2") Drawlines1_2(i, seq1, seq2, outfile, outImg, keyPoint1, keyPoint2);
		else if (seq1 == "1" && seq2 == "3") Drawlines1_3(i, seq1, seq2, outfile, outImg, keyPoint1, keyPoint2);
		else if (seq1 == "1" && seq2 == "4") Drawlines1_4(i, seq1, seq2, outfile, outImg, keyPoint1, keyPoint2);
		else if (seq1 == "2" && seq2 == "3") Drawlines2_3(i, seq1, seq2, outfile, outImg, keyPoint1, keyPoint2);
		else if (seq1 == "2" && seq2 == "4") Drawlines2_4(i, seq1, seq2, outfile, outImg, keyPoint1, keyPoint2);
		else if (seq1 == "3" && seq2 == "4") Drawlines3_4(i, seq1, seq2, outfile, outImg, keyPoint1, keyPoint2);
		else;

	}

	//--------------------显示结果--------------------//
	string wt_img = "E:/Biyesheji/Detection/Detection/Match picture/match" + seq1 + "&" + seq2 + ".jpg";
	imwrite(wt_img, outImg);

	QImage image;
	if (!image.load(QString::fromStdString(wt_img)))
	{
		QMessageBox::information(this, tr("Failed to open the JPG!"), tr("Failed to open the JPG!"));
	}
	QImage newImage = image.scaled(ImgWindow->width(), ImgWindow->height(), Qt::KeepAspectRatio);
	ImgWindow->setPixmap(QPixmap::fromImage(newImage));
}

void Detect::TripMatchPoints()
{
	string seq1, seq2, seq3;

	seq1 = tripFile1.substr(tripFile1.find(".") - 1, 1);
	seq2 = tripFile2.substr(tripFile2.find(".") - 1, 1);
	seq3 = tripFile3.substr(tripFile3.find(".") - 1, 1);

	//---------------读取图像，预处理---------------------//
	Mat Img1 = imread("E:\\Biyesheji\\Detection\\Detection\\detected picture\\Detected" + seq1 + ".jpg"); //读取图像
	Mat Img2 = imread("E:\\Biyesheji\\Detection\\Detection\\detected picture\\Detected" + seq2 + ".jpg"); //读取图像
	Mat Img3 = imread("E:\\Biyesheji\\Detection\\Detection\\detected picture\\Detected" + seq3 + ".jpg"); //读取图像

	if (Img1.empty() || Img2.empty() || Img3.empty())
	{
		QMessageBox::information(this, tr("Can not load image!"), tr("Can not load image!"));
	}

	//--------------读取区域数据进行记录------------//
	ifstream infile1, infile2, infile3;   //输入流
	ofstream& function(ofstream &outfile);   //输出流
	infile1.open("E:\\Biyesheji\\Detection\\Detection\\match area\\corner" + seq1 + "(" + seq1 + "&" + seq2 + "&" + seq3 + ").txt", ios::in);//打开数据文件1
	infile2.open("E:\\Biyesheji\\Detection\\Detection\\match area\\corner" + seq2 + "(" + seq1 + "&" + seq2 + "&" + seq3 + ").txt", ios::in);//打开数据文件2
	infile3.open("E:\\Biyesheji\\Detection\\Detection\\match area\\corner" + seq3 + "(" + seq1 + "&" + seq2 + "&" + seq3 + ").txt", ios::in);//打开数据文件3
	if (!infile1.is_open())
		QMessageBox::information(this, tr("Open file1 failure!"), tr("Open file1 failure!"));
	if (!infile2.is_open())
		QMessageBox::information(this, tr("Open file2 failure!"), tr("Open file2 failure!"));
	if (!infile3.is_open())
		QMessageBox::information(this, tr("Open file3 failure!"), tr("Open file3 failure!"));
	string out;
	double data1[200], data2[200], data3[200], data4[200];
	double data5[200], data6[200], data7[200], data8[200];
	double data9[200], data10[200], data11[200], data12[200];
	QMessageBox::information(this, tr("Finish reading files."), tr("Finish reading files."));

	int total;
	if (seq1 == "1" && seq2 == "2" && seq3 == "3") total = 85;
	else if (seq1 == "1" && seq2 == "2"&& seq3 == "4") total = 85;
	else if (seq1 == "1" && seq2 == "3"&& seq3 == "4") total = 75;
	else if (seq1 == "2" && seq2 == "3"&& seq3 == "4") total = 75;


	while (!infile1.eof())
	{
		for (int i = 0; i < total; i++)
		{
			infile1 >> data1[i] >> data2[i] >> data3[i] >> data4[i];
		}
	}
	while (!infile2.eof())
	{
		for (int i = 0; i < total; i++)
		{
			infile2 >> data5[i] >> data6[i] >> data7[i] >> data8[i];
		}
	}
	while (!infile3.eof()) {
		for (int i = 0; i < total; i++)
		{
			infile3 >> data9[i] >> data10[i] >> data11[i] >> data12[i];
		}
	} //读取数据并存储在data中
	QMessageBox::information(this, tr("Reading datas finished."), tr("Reading datas finished."));
	string filename;
	filename = "E:\\Biyesheji\\Detection\\Detection\\match result\\";

	ofstream outfile(filename + "match result" + seq1 + "&" + seq2 + "&" + seq3 + ".txt", ios::out);
	if (!outfile.is_open())
		QMessageBox::information(this, tr("Open file failure!"), tr("Open file failure!"));
	//---------------------区域划分及处理-------------------//
	Mat outImg;
	mergeImg(outImg, Img1, Img2);
	double a, b, c, d, e, f, g, h, r, s, t, u;
	Mat Img_1 = Img1.clone(), Img_2 = Img2.clone(), Img_3 = Img3.clone();
	Mat roi1, roi2, roi3;

	for (int i = 0; i < total; i++)
	{
		a = data1[i];
		b = data2[i];
		c = data3[i];
		d = data4[i];
		e = data5[i];
		f = data6[i];
		g = data7[i];
		h = data8[i];
		r = data9[i];
		s = data10[i];
		t = data11[i];
		u = data12[i];

		vector<int> letters;
		letters.push_back(a);
		letters.push_back(b);
		letters.push_back(e);
		letters.push_back(f);
		letters.push_back(r);
		letters.push_back(s);

		cv::Rect rect1(a, b, c, d); //划分区域
		int cols1 = Img_1.cols, rows1 = Img_1.rows;
		if (cols1 - 1 - rect1.x < rect1.width || rows1 - 1 - rect1.y < rect1.height)
			return; //ROI越界，返回
		roi1 = Img_1(Rect(rect1.x, rect1.y, rect1.width, rect1.height));
		Mat copyImage1;
		copyImage1 = roi1.clone();

		cv::Rect rect2(e, f, g, h); //划分区域
		int cols2 = Img_2.cols, rows2 = Img_2.rows;
		if (cols2 - 1 - rect2.x < rect2.width || rows2 - 1 - rect2.y < rect2.height)
			return; //ROI越界，返回
		roi2 = Img_2(Rect(rect2.x, rect2.y, rect2.width, rect2.height));
		Mat copyImage2;
		copyImage2 = roi2.clone();

		cv::Rect rect3(r, s, t, u); //划分区域
		int cols3 = Img_3.cols, rows3 = Img_3.rows;
		if (cols3 - 1 - rect3.x < rect3.width || rows3 - 1 - rect3.y < rect3.height)
			return; //ROI越界，返回
		roi3 = Img_3(Rect(rect3.x, rect3.y, rect3.width, rect3.height));
		Mat copyImage3;
		copyImage3 = roi3.clone();

		//------------区域内检测角点，根据x坐标进行分类-----//
		vector<KeyPoint> keyPoint1(200), keyPoint2(200), keyPoint3(200);

		if (seq1 == "1" && seq2 == "2" && seq3 == "3") MatchPoint1_2_3(i, letters, roi1, roi2, roi3, keyPoint1, keyPoint2, keyPoint3);
		else if (seq1 == "1" && seq2 == "2" && seq3 == "4") MatchPoint1_2_4(i, letters, roi1, roi2, roi3, keyPoint1, keyPoint2, keyPoint3);
		else if (seq1 == "1" && seq2 == "3" && seq3 == "4") MatchPoint1_3_4(i, letters, roi1, roi2, roi3, keyPoint1, keyPoint2, keyPoint3);
		else if (seq1 == "2" && seq2 == "3" && seq3 == "4") MatchPoint2_3_4(i, letters, roi1, roi2, roi3, keyPoint1, keyPoint2, keyPoint3);
		else;

		//----------画图-----------------//

		for (int k = 0; k < keyPoint1.size(); k++) {
			keyPoint1[k].pt.x = keyPoint1[k].pt.x + a;
			keyPoint1[k].pt.y = keyPoint1[k].pt.y + b;
		}
		for (int k = 0; k < keyPoint2.size(); k++) {
			keyPoint2[k].pt.x = keyPoint2[k].pt.x + e;
			keyPoint2[k].pt.y = keyPoint2[k].pt.y + f;
		}
		for (int k = 0; k < keyPoint3.size(); k++) {
			keyPoint3[k].pt.x = keyPoint3[k].pt.x + r;
			keyPoint3[k].pt.y = keyPoint3[k].pt.y + s;
		}

		outfile << "total match points in area" << i << ":" << keyPoint1.size() << endl;
		for (int k = 0; k < keyPoint1.size(); k++) {
			for (int l = 0; l < keyPoint2.size(); l++) {
				for (int m = 0; m < keyPoint3.size(); m++) {
					if (keyPoint1[k].class_id == keyPoint2[l].class_id && keyPoint2[l].class_id == keyPoint3[m].class_id) {
						outfile << "Corner" << seq1 << ":" << keyPoint1[k].pt << "\t" << "Match" << "\t" << "Corner" << seq2 << ":" << keyPoint2[l].pt << "\t" << "Match" << "\t" << "Corner" << seq3 << ":" << keyPoint3[m].pt << endl;
					}
				}
			}
		}

	}

	//--------------------显示结果--------------------//
	QMessageBox::information(this, tr("Finish the match."), tr("Finish the match."));
}

void Detect::QuadMatchPoints()
{
	string seq1, seq2, seq3, seq4;

	seq1 = quadFile1.substr(quadFile1.find(".") - 1, 1);
	seq2 = quadFile2.substr(quadFile2.find(".") - 1, 1);
	seq3 = quadFile3.substr(quadFile3.find(".") - 1, 1);
	seq4 = quadFile4.substr(quadFile4.find(".") - 1, 1);

	//---------------读取图像，预处理---------------------//
	Mat Img1 = imread("E:\\Biyesheji\\Detection\\Detection\\detected picture\\Detected" + seq1 + ".jpg"); //读取图像
	Mat Img2 = imread("E:\\Biyesheji\\Detection\\Detection\\detected picture\\Detected" + seq2 + ".jpg"); //读取图像
	Mat Img3 = imread("E:\\Biyesheji\\Detection\\Detection\\detected picture\\Detected" + seq3 + ".jpg"); //读取图像
	Mat Img4 = imread("E:\\Biyesheji\\Detection\\Detection\\detected picture\\Detected" + seq4 + ".jpg"); //读取图像

	if (Img1.empty() || Img2.empty() || Img3.empty() || Img3.empty())
	{
		QMessageBox::information(this, tr("Can not load image!"), tr("Can not load image!"));
	}

	//--------------读取区域数据进行记录------------//
	ifstream infile1, infile2, infile3, infile4;   //输入流
	ofstream& function(ofstream &outfile);   //输出流
	infile1.open("E:\\Biyesheji\\Detection\\Detection\\match area\\corner" + seq1 + "(" + seq1 + "&" + seq2 + "&" + seq3 + "&" + seq4 + ").txt", ios::in);//打开数据文件1
	infile2.open("E:\\Biyesheji\\Detection\\Detection\\match area\\corner" + seq2 + "(" + seq1 + "&" + seq2 + "&" + seq3 + "&" + seq4 + ").txt", ios::in);//打开数据文件2
	infile3.open("E:\\Biyesheji\\Detection\\Detection\\match area\\corner" + seq3 + "(" + seq1 + "&" + seq2 + "&" + seq3 + "&" + seq4 + ").txt", ios::in);//打开数据文件3
	infile4.open("E:\\Biyesheji\\Detection\\Detection\\match area\\corner" + seq4 + "(" + seq1 + "&" + seq2 + "&" + seq3 + "&" + seq4 + ").txt", ios::in);//打开数据文件4
	if (!infile1.is_open())
		QMessageBox::information(this, tr("Open file failure!"), tr("Open file failure!"));
	if (!infile2.is_open())
		QMessageBox::information(this, tr("Open file failure!"), tr("Open file failure!"));
	if (!infile3.is_open())
		QMessageBox::information(this, tr("Open file failure!"), tr("Open file failure!"));
	if (!infile4.is_open())
		QMessageBox::information(this, tr("Open file failure!"), tr("Open file failure!"));
	string out;
	double data1[200], data2[200], data3[200], data4[200];
	double data5[200], data6[200], data7[200], data8[200];
	double data9[200], data10[200], data11[200], data12[200];
	double data13[200], data14[200], data15[200], data16[200];
	QMessageBox::information(this, tr("Finish reading files."), tr("Finish reading files."));

	int total;
	total = 75;

	while (!infile1.eof() && !infile2.eof() && !infile3.eof() && !infile4.eof()) {
		for (int i = 0; i < total; i++)
		{
			infile1 >> data1[i] >> data2[i] >> data3[i] >> data4[i];
			infile2 >> data5[i] >> data6[i] >> data7[i] >> data8[i];
			infile3 >> data9[i] >> data10[i] >> data11[i] >> data12[i];
			infile4 >> data13[i] >> data14[i] >> data15[i] >> data16[i];
		}
	}
	//读取数据并存储在data中
	QMessageBox::information(this, tr("Reading datas finished."), tr("Reading datas finished."));
	string filename;
	filename = "E:\\Biyesheji\\Detection\\Detection\\match result\\";

	ofstream outfile(filename + "match result" + seq1 + "&" + seq2 + "&" + seq3 + "&" + seq4 + ".txt", ios::out);
	ofstream outfile1(filename + "1.txt", ios::out);
	ofstream outfile2(filename + "2.txt", ios::out);
	ofstream outfile3(filename + "3.txt", ios::out);
	ofstream outfile4(filename + "4.txt", ios::out);

	if (!outfile.is_open())
		QMessageBox::information(this, tr("Open file failure."), tr("Open file failure."));
	//---------------------区域划分及处理-------------------//
	Mat outImg;
	mergeImg(outImg, Img1, Img2);
	double a, b, c, d, e, f, g, h, r, j, k, l, m, n, o, p;
	Mat Img_1 = Img1.clone(), Img_2 = Img2.clone(), Img_3 = Img3.clone(), Img_4 = Img4.clone();
	Mat roi1, roi2, roi3, roi4;

	for (int i = 0; i < total; i++)
	{
		a = data1[i];
		b = data2[i];
		c = data3[i];
		d = data4[i];
		e = data5[i];
		f = data6[i];
		g = data7[i];
		h = data8[i];
		r = data9[i];
		j = data10[i];
		k = data11[i];
		l = data12[i];
		m = data13[i];
		n = data14[i];
		o = data15[i];
		p = data16[i];

		vector<int> letters;
		letters.push_back(a);
		letters.push_back(b);
		letters.push_back(e);
		letters.push_back(f);
		letters.push_back(r);
		letters.push_back(j);
		letters.push_back(m);
		letters.push_back(n);

		cv::Rect rect1(a, b, c, d); //划分区域
		int cols1 = Img_1.cols, rows1 = Img_1.rows;
		if (cols1 - 1 - rect1.x < rect1.width || rows1 - 1 - rect1.y < rect1.height)
			return; //ROI越界，返回
		roi1 = Img_1(Rect(rect1.x, rect1.y, rect1.width, rect1.height));
		Mat copyImage1;
		copyImage1 = roi1.clone();

		cv::Rect rect2(e, f, g, h); //划分区域
		int cols2 = Img_2.cols, rows2 = Img_2.rows;
		if (cols2 - 1 - rect2.x < rect2.width || rows2 - 1 - rect2.y < rect2.height)
			return; //ROI越界，返回
		roi2 = Img_2(Rect(rect2.x, rect2.y, rect2.width, rect2.height));
		Mat copyImage2;
		copyImage2 = roi2.clone();

		cv::Rect rect3(r, j, k, l); //划分区域
		int cols3 = Img_3.cols, rows3 = Img_3.rows;
		if (cols3 - 1 - rect3.x < rect3.width || rows3 - 1 - rect3.y < rect3.height)
			return; //ROI越界，返回
		roi3 = Img_3(Rect(rect3.x, rect3.y, rect3.width, rect3.height));
		Mat copyImage3;
		copyImage3 = roi3.clone();

		cv::Rect rect4(m, n, o, p); //划分区域
		int cols4 = Img_4.cols, rows4 = Img_4.rows;
		if (cols4 - 1 - rect4.x < rect4.width || rows4 - 1 - rect4.y < rect4.height)
			return; //ROI越界，返回
		roi4 = Img_4(Rect(rect4.x, rect4.y, rect4.width, rect4.height));
		Mat copyImage4;
		copyImage4 = roi4.clone();
		//------------区域内检测角点，根据x坐标进行分类-----//
		vector<KeyPoint> keyPoint1(200), keyPoint2(200), keyPoint3(200), keyPoint4(200);
		MatchPoint1_2_3_4(i, letters, roi1, roi2, roi3, roi4, keyPoint1, keyPoint2, keyPoint3, keyPoint4);


		//----------画图-----------------//

		for (int k = 0; k < keyPoint1.size(); k++) {
			keyPoint1[k].pt.x = keyPoint1[k].pt.x + a;
			keyPoint1[k].pt.y = keyPoint1[k].pt.y + b;
		}
		for (int k = 0; k < keyPoint2.size(); k++) {
			keyPoint2[k].pt.x = keyPoint2[k].pt.x + e;
			keyPoint2[k].pt.y = keyPoint2[k].pt.y + f;
		}
		for (int k = 0; k < keyPoint3.size(); k++) {
			keyPoint3[k].pt.x = keyPoint3[k].pt.x + r;
			keyPoint3[k].pt.y = keyPoint3[k].pt.y + j;
		}
		for (int k = 0; k < keyPoint4.size(); k++) {
			keyPoint4[k].pt.x = keyPoint4[k].pt.x + m;
			keyPoint4[k].pt.y = keyPoint4[k].pt.y + n;
		}
		outfile << "total match points in area" << i << ":" << keyPoint1.size() << endl;
		for (int k = 0; k < keyPoint1.size(); k++) {
			for (int l = 0; l < keyPoint2.size(); l++) {
				for (int m = 0; m < keyPoint3.size(); m++) {
					for (int x = 0; x < keyPoint4.size(); x++) {
						if (keyPoint1[k].class_id == keyPoint2[l].class_id && keyPoint3[m].class_id == keyPoint4[x].class_id &&keyPoint2[l].class_id == keyPoint3[m].class_id) {
							outfile << seq1 << ":" << keyPoint1[k].pt << "\t" << "Match" << "\t" << seq2 << ":" << keyPoint2[k].pt << "\t" << "Match" << "\t" << seq3 << ":" << keyPoint3[m].pt << "\t" << "Match" << "\t" << seq4 << ":" << keyPoint4[x].pt << endl;
							outfile1 << keyPoint1[k].pt.x << "," << keyPoint1[k].pt.y << "," << endl;
							outfile2 << keyPoint2[k].pt.x << "," << keyPoint2[k].pt.y << "," << endl;
							outfile3 << keyPoint3[k].pt.x << "," << keyPoint3[k].pt.y << "," << endl;
							outfile4 << keyPoint4[k].pt.x << "," << keyPoint4[k].pt.y << "," << endl;
						}
					}
				}
			}
		}

	}

	//--------------------显示结果--------------------//
	QMessageBox::information(this, tr("Finish the match."), tr("Finish the match."));
}

void mergeImg(Mat & dst, Mat &src1, Mat &src2)
{
	int rows = src1.rows;
	int cols = src1.cols + src2.cols;
	CV_Assert(src1.type() == src2.type());
	dst.create(rows, cols, src1.type());
	src1.copyTo(dst(Rect(0, 0, src1.cols, src1.rows)));
	src2.copyTo(dst(Rect(src1.cols, 0, src2.cols, src2.rows)));
}

vector<Point2f> ComputeCorner1(int i, Mat& roi1)
{
	vector<Point2f> corner(200);

	double minDistance = 1;
	int blockSize = 3;
	double qualityLevel = 0.5;
	bool useHarrisDetector = false;
	double k = 0.04;

	if (i >= 0 && i <= 26) {
		int max_cornerNum = 2;
		double qualityLevel = 0.5;
		if (i == 4 || i == 9 || i == 10 || i == 11 || i == 22 || i == 24) {
			int max_cornerNum1 = 2;
			double qualityLevel1 = 0.0005;
			double minDistance1 = 1;
			int blockSize1 = 5;
			bool useHarrisDetector1 = false;
			double k1 = 0.04;
			goodFeaturesToTrack(roi1, corner, max_cornerNum1, qualityLevel1, minDistance1, Mat(), blockSize1, useHarrisDetector1, k1);
		}
		else if (i == 17 || i == 23 || i == 18) {
			int blockSize1 = 5;
			double qualityLevel1 = 0.5;
			goodFeaturesToTrack(roi1, corner, max_cornerNum, qualityLevel1, minDistance, Mat(), blockSize1, useHarrisDetector, k);
		}
		else if (i == 25) {
			int blockSize1 = 5;
			double qualityLevel1 = 0.0005;
			goodFeaturesToTrack(roi1, corner, max_cornerNum, qualityLevel1, minDistance, Mat(), blockSize1, useHarrisDetector, k);
		}
		else {
			goodFeaturesToTrack(roi1, corner, max_cornerNum, qualityLevel, minDistance, Mat(), blockSize, useHarrisDetector, k);
		}
	}

	if (i >= 27 && i <= 54) {
		int max_cornerNum = 4;
		double qualityLevel = 0.5;
		if (i == 28) {
			double qualityLevel1 = 0.0005;
			double minDistance1 = 5;
			goodFeaturesToTrack(roi1, corner, max_cornerNum, qualityLevel1, minDistance1, Mat(), blockSize, useHarrisDetector, k);
		}
		else if (i == 30) {
			double qualityLevel1 = 0.0005;
			double minDistance1 = 3;
			int blockSize1 = 5;
			goodFeaturesToTrack(roi1, corner, max_cornerNum, qualityLevel1, minDistance1, Mat(), blockSize1, useHarrisDetector, k);
		}
		else if (i == 34 || i == 36 || i == 44) {
			double qualityLevel1 = 0.0005;
			int blockSize1 = 5;
			goodFeaturesToTrack(roi1, corner, max_cornerNum, qualityLevel1, minDistance, Mat(), blockSize1, useHarrisDetector, k);
		}
		else if (i == 45 || i == 46) {
			double minDistance1 = 5;
			int blockSize1 = 5;
			goodFeaturesToTrack(roi1, corner, max_cornerNum, qualityLevel, minDistance1, Mat(), blockSize1, useHarrisDetector, k);
		}
		else if (i == 32) {
			Mat kernel(3, 3, CV_32F, Scalar(-1));
			Mat dst1;
			kernel.at<float>(1, 1) = 8.9;//锐化
			filter2D(roi1, dst1, roi1.depth(), kernel);
			int max_cornerNum1 = 5;
			double qualityLevel1 = 0.0005;
			double minDistance1 = 5;
			int blockSize1 = 5;
			goodFeaturesToTrack(dst1, corner, max_cornerNum1, qualityLevel1, minDistance1, Mat(), blockSize1, useHarrisDetector, k);
		}
		else if (i == 29 || i == 43) {
			int blockSize1 = 5;
			goodFeaturesToTrack(roi1, corner, max_cornerNum, qualityLevel, minDistance, Mat(), blockSize1, useHarrisDetector, k);
		}
		else if (i == 48) {
			Mat kernel(3, 3, CV_32F, Scalar(-1));
			Mat dst1;
			kernel.at<float>(1, 1) = 8.9;
			filter2D(roi1, dst1, roi1.depth(), kernel);
			double qualityLevel1 = 0.0005;
			int blockSize1 = 5;
			goodFeaturesToTrack(dst1, corner, max_cornerNum, qualityLevel1, minDistance, Mat(), blockSize1, useHarrisDetector, k);
			corner[1].x = corner[1].x + 5;
			corner[1].y = corner[1].y - 10;
		}
		else if (i == 49) {
			int max_cornerNum1 = 2;
			double qualityLevel1 = 0.0005;
			int blockSize1 = 5;
			goodFeaturesToTrack(roi1, corner, max_cornerNum1, qualityLevel1, minDistance, Mat(), blockSize1, useHarrisDetector, k);
		}
		else if (i == 50) {
			Mat kernel(3, 3, CV_32F, Scalar(-1));
			Mat dst1;
			kernel.at<float>(1, 1) = 8.9;//锐化
			filter2D(roi1, dst1, roi1.depth(), kernel);
			double qualityLevel1 = 0.0005;
			double minDistance1 = 3;
			int blockSize1 = 5;
			goodFeaturesToTrack(dst1, corner, max_cornerNum, qualityLevel1, minDistance1, Mat(), blockSize1, useHarrisDetector, k);
			corner[0].x = corner[0].x + 5;
			corner[3].x = corner[3].x + 5;
		}
		else if (i == 52) {
			Mat kernel(3, 3, CV_32F, Scalar(-1));
			Mat dst1;
			kernel.at<float>(1, 1) = 8.9;//锐化
			filter2D(roi1, dst1, roi1.depth(), kernel);
			double qualityLevel1 = 0.0005;
			int blockSize1 = 5;
			goodFeaturesToTrack(dst1, corner, max_cornerNum, qualityLevel1, minDistance, Mat(), blockSize1, useHarrisDetector, k);
			corner[2].x = corner[2].x - 6;
		}

		else if (i == 31 || i == 33 || i == 53 || i == 51 || i == 47) {
			Mat kernel(3, 3, CV_32F, Scalar(-1));
			Mat dst1;
			kernel.at<float>(1, 1) = 8.9;//锐化
			filter2D(roi1, dst1, roi1.depth(), kernel);
			int max_cornerNum1 = 2;
			double qualityLevel1 = 0.0005;
			int blockSize1 = 5;
			goodFeaturesToTrack(dst1, corner, max_cornerNum1, qualityLevel1, minDistance, Mat(), blockSize1, useHarrisDetector, k);
		}
		else if (i == 54) {
			Mat kernel(3, 3, CV_32F, Scalar(-1));
			Mat dst1;
			kernel.at<float>(1, 1) = 8.9;//锐化
			filter2D(roi1, dst1, roi1.depth(), kernel);
			double qualityLevel1 = 0.0005;
			double minDistance1 = 5;
			int blockSize1 = 5;
			goodFeaturesToTrack(dst1, corner, max_cornerNum, qualityLevel1, minDistance1, Mat(), blockSize1, useHarrisDetector, k);
		}
		else {
			goodFeaturesToTrack(roi1, corner, max_cornerNum, qualityLevel, minDistance, Mat(), blockSize, useHarrisDetector, k);
		}
	}

	if (i >= 55 && i <= 94) {
		int max_cornerNum = 1;
		double qualityLevel = 0.5;
		if (i == 68) {
			double qualityLevel1 = 0.0005;
			int blockSize1 = 5;
			goodFeaturesToTrack(roi1, corner, max_cornerNum, qualityLevel1, minDistance, Mat(), blockSize1, useHarrisDetector, k);
		}
		else
			goodFeaturesToTrack(roi1, corner, max_cornerNum, qualityLevel, minDistance, Mat(), blockSize, useHarrisDetector, k);

	}

	if (i >= 95 && i <= 105) {
		int max_cornerNum = 2;
		double qualityLevel = 0.5;
		if (i == 96 || i == 99 || i == 103) {
			double qualityLevel1 = 0.0005;
			int blockSize1 = 5;
			goodFeaturesToTrack(roi1, corner, max_cornerNum, qualityLevel1, minDistance, Mat(), blockSize1, useHarrisDetector, k);
		}
		else {
			goodFeaturesToTrack(roi1, corner, max_cornerNum, qualityLevel, minDistance, Mat(), blockSize, useHarrisDetector, k);
		}
	}

	return corner;
}

vector<Point2f> ComputeCorner2(int i, Mat& roi1)
{
	vector<Point2f> corner(200);

	double minDistance = 1;
	int blockSize = 3;
	double qualityLevel = 0.5;
	bool useHarrisDetector = false;
	double k = 0.04;

	if (i >= 0 && i <= 26) {
		int max_cornerNum = 2;
		if (i == 22) {
			int blockSize1 = 5;
			double qualityLevel1 = 0.0005;
			goodFeaturesToTrack(roi1, corner, max_cornerNum, qualityLevel1, minDistance, Mat(), blockSize1, useHarrisDetector, k);
		}
		else if (i == 20 || i == 18)
		{
			int blockSize1 = 5;
			double qualityLevel1 = 0.0005;
			double minDistance1 = 5;
			goodFeaturesToTrack(roi1, corner, max_cornerNum, qualityLevel1, minDistance1, Mat(), blockSize1, useHarrisDetector, k);
		}
		else if (i == 16) {
			Mat kernel(3, 3, CV_32F, Scalar(-1));
			Mat dst1;
			kernel.at<float>(1, 1) = 8.9;
			filter2D(roi1, dst1, roi1.depth(), kernel);
			int blockSize1 = 5;
			double qualityLevel1 = 0.0005;
			double minDistance1 = 5;
			goodFeaturesToTrack(dst1, corner, max_cornerNum, qualityLevel1, minDistance1, Mat(), blockSize1, useHarrisDetector, k);
		}
		else if (i == 21) {
			Mat kernel(3, 3, CV_32F, Scalar(-1));
			Mat dst1;
			kernel.at<float>(1, 1) = 8.9;
			filter2D(roi1, dst1, roi1.depth(), kernel);
			double qualityLevel1 = 0.0005;
			goodFeaturesToTrack(dst1, corner, max_cornerNum, qualityLevel1, minDistance, Mat(), blockSize, useHarrisDetector, k);
		}
		else if (i == 25) {
			Mat kernel(3, 3, CV_32F, Scalar(-1));
			Mat dst1;
			kernel.at<float>(1, 1) = 8.9;
			filter2D(roi1, dst1, roi1.depth(), kernel);
			int min_Thresh = 50;
			int max_Thresh = 250;
			Canny(dst1, dst1, min_Thresh, max_Thresh * 2, 3);
			double qualityLevel1 = 0.0005;
			int blockSize1 = 5;
			goodFeaturesToTrack(dst1, corner, max_cornerNum, qualityLevel1, minDistance, Mat(), blockSize1, useHarrisDetector, k);
		}
		else
		{
			goodFeaturesToTrack(roi1, corner, max_cornerNum, qualityLevel, minDistance, Mat(), blockSize, useHarrisDetector, k);
		}
	}

	if (i >= 27 && i <= 54) {
		int max_cornerNum = 4;
		if (i == 27 || i == 31 || i == 33 || i == 43 || i == 49 || i == 51) {
			Mat kernel(3, 3, CV_32F, Scalar(-1));
			Mat dst1;
			kernel.at<float>(1, 1) = 8.9;
			filter2D(roi1, dst1, roi1.depth(), kernel);
			double qualityLevel1 = 0.0005;
			if (i == 51) {
				blur(dst1, dst1, Size(3, 3));
				goodFeaturesToTrack(dst1, corner, max_cornerNum, qualityLevel1, minDistance, Mat(), blockSize, useHarrisDetector, k);
			}
			else if (i == 49) {
				blur(dst1, dst1, Size(5, 5));
				double minDistance1 = 5;
				goodFeaturesToTrack(dst1, corner, max_cornerNum, qualityLevel1, minDistance1, Mat(), blockSize, useHarrisDetector, k);
			}
			else if (i == 43) {
				double minDistance1 = 5;
				goodFeaturesToTrack(dst1, corner, max_cornerNum, qualityLevel1, minDistance1, Mat(), blockSize, useHarrisDetector, k);
			}
			else {
				goodFeaturesToTrack(dst1, corner, max_cornerNum, qualityLevel1, minDistance, Mat(), blockSize, useHarrisDetector, k);
			}
		}
		else if (i == 28 || i == 30 || i == 36 || i == 44 || i == 50 || i == 52 || i == 48 || i == 46) {
			Mat kernel(3, 3, CV_32F, Scalar(-1));
			Mat dst1;
			kernel.at<float>(1, 1) = 8.9;
			filter2D(roi1, dst1, roi1.depth(), kernel);
			int max_cornerNum1 = 2;
			double qualityLevel1 = 0.0005;
			if (i == 48) {
				blur(dst1, dst1, Size(3, 3));
				goodFeaturesToTrack(dst1, corner, max_cornerNum1, qualityLevel1, minDistance, Mat(), blockSize, useHarrisDetector, k);
			}
			else {
				goodFeaturesToTrack(dst1, corner, max_cornerNum1, qualityLevel1, minDistance, Mat(), blockSize, useHarrisDetector, k);
			}
		}
		else if (i == 29 || i == 41 || i == 47) {
			int blockSize1 = 5;
			double qualityLevel1 = 0.0005;
			goodFeaturesToTrack(roi1, corner, max_cornerNum, qualityLevel1, minDistance, Mat(), blockSize1, useHarrisDetector, k);
		}
		else if (i == 45) {
			Mat kernel(3, 3, CV_32F, Scalar(-1));
			Mat dst1;
			kernel.at<float>(1, 1) = 8.9;
			filter2D(roi1, dst1, roi1.depth(), kernel);
			double minDistance1 = 5;
			goodFeaturesToTrack(dst1, corner, max_cornerNum, qualityLevel, minDistance1, Mat(), blockSize, useHarrisDetector, k);
			corner[2].y = corner[2].y - 12;
		}
		else if (i == 35) {
			Mat kernel(3, 3, CV_32F, Scalar(-1));
			Mat dst1;
			kernel.at<float>(1, 1) = 8.9;
			filter2D(roi1, dst1, roi1.depth(), kernel);
			double qualityLevel1 = 0.0005;
			goodFeaturesToTrack(dst1, corner, max_cornerNum, qualityLevel1, minDistance, Mat(), blockSize, useHarrisDetector, k);
			corner[0].x = corner[0].x + 6;
			corner[0].y = corner[0].y + 16;
		}
		else if (i == 53) {
			Mat kernel(3, 3, CV_32F, Scalar(-1));
			Mat dst1;
			kernel.at<float>(1, 1) = 8.9;
			filter2D(roi1, dst1, roi1.depth(), kernel);
			int max_cornerNum1 = 3;
			double qualityLevel1 = 0.0005;
			double minDistance1 = 5;
			goodFeaturesToTrack(dst1, corner, max_cornerNum1, qualityLevel1, minDistance1, Mat(), blockSize, useHarrisDetector, k);
		}
		else {
			goodFeaturesToTrack(roi1, corner, max_cornerNum, qualityLevel, minDistance, Mat(), blockSize, useHarrisDetector, k);
		}
	}

	if (i >= 55 && i <= 94) {
		int max_cornerNum = 1;
		goodFeaturesToTrack(roi1, corner, max_cornerNum, qualityLevel, minDistance, Mat(), blockSize, useHarrisDetector, k);
	}

	if (i >= 95 && i <= 105) {
		int max_cornerNum = 2;
		if (i == 97 || i == 101 || i == 105) {
			Mat kernel(3, 3, CV_32F, Scalar(-1));
			Mat dst1;
			kernel.at<float>(1, 1) = 8.9;
			filter2D(roi1, dst1, roi1.depth(), kernel);
			int blockSize1 = 5;
			double qualityLevel1 = 0.0005;
			double minDistance1 = 5;
			goodFeaturesToTrack(dst1, corner, max_cornerNum, qualityLevel1, minDistance1, Mat(), blockSize1, useHarrisDetector, k);
		}
		else if (i == 99) {
			Mat kernel(3, 3, CV_32F, Scalar(-1));
			Mat dst1;
			kernel.at<float>(1, 1) = 8.9;
			filter2D(roi1, dst1, roi1.depth(), kernel);
			int min_Thresh = 50;
			int max_Thresh = 250;
			Canny(dst1, dst1, min_Thresh, max_Thresh * 2, 3);
			double qualityLevel1 = 0.0005;
			int blockSize1 = 5;
			goodFeaturesToTrack(dst1, corner, max_cornerNum, qualityLevel1, minDistance, Mat(), blockSize1, useHarrisDetector, k);
		}
		else if (i == 98 || i == 100) {
			int blockSize1 = 5;
			double qualityLevel1 = 0.0005;
			goodFeaturesToTrack(roi1, corner, max_cornerNum, qualityLevel1, minDistance, Mat(), blockSize1, useHarrisDetector, k);
		}
		else {
			goodFeaturesToTrack(roi1, corner, max_cornerNum, qualityLevel, minDistance, Mat(), blockSize, useHarrisDetector, k);
		}
	}

	return corner;
}

vector<Point2f> ComputeCorner3(int i, Mat& roi1)
{
	vector<Point2f> corner(200);

	double minDistance = 1;
	int blockSize = 3;
	double qualityLevel = 0.5;
	bool useHarrisDetector = false;
	double k = 0.04;

	if (i >= 0 && i <= 23) {
		int max_cornerNum = 2;
		if (i == 5) {
			Mat kernel(3, 3, CV_32F, Scalar(-1));
			Mat dst1;
			kernel.at<float>(1, 1) = 8.9;
			filter2D(roi1, dst1, roi1.depth(), kernel);
			blur(dst1, dst1, Size(3, 3));
			goodFeaturesToTrack(dst1, corner, max_cornerNum, qualityLevel, minDistance, Mat(), blockSize, useHarrisDetector, k);
		}
		else if (i == 13 || i == 16) {
			int blockSize1 = 5;
			double qualityLevel1 = 0.0005;
			goodFeaturesToTrack(roi1, corner, max_cornerNum, qualityLevel1, minDistance, Mat(), blockSize1, useHarrisDetector, k);
		}
		else if (i == 15) {
			Mat kernel(3, 3, CV_32F, Scalar(-1));
			Mat dst1;
			kernel.at<float>(1, 1) = 8.9;
			filter2D(roi1, dst1, roi1.depth(), kernel);
			goodFeaturesToTrack(dst1, corner, max_cornerNum, qualityLevel, minDistance, Mat(), blockSize, useHarrisDetector, k);
		}
		else if (i == 23) {
			int max_cornerNum1 = 1;
			goodFeaturesToTrack(roi1, corner, max_cornerNum1, qualityLevel, minDistance, Mat(), blockSize, useHarrisDetector, k);
		}
		else {
			goodFeaturesToTrack(roi1, corner, max_cornerNum, qualityLevel, minDistance, Mat(), blockSize, useHarrisDetector, k);
		}
	}

	if (i >= 24 && i <= 48) {
		int max_cornerNum = 4;
		if (i == 24 || i == 28 || i == 38 || i == 42) {
			Mat kernel(3, 3, CV_32F, Scalar(-1));
			Mat dst1;
			kernel.at<float>(1, 1) = 8.9;
			filter2D(roi1, dst1, roi1.depth(), kernel);
			int max_cornerNum1 = 2;
			if (i == 38) {
				double minDistance1 = 3;
				goodFeaturesToTrack(dst1, corner, max_cornerNum1, qualityLevel, minDistance1, Mat(), blockSize, useHarrisDetector, k);
			}
			else {
				goodFeaturesToTrack(dst1, corner, max_cornerNum1, qualityLevel, minDistance, Mat(), blockSize, useHarrisDetector, k);
			}
		}
		else if (i == 43 || i == 41 || i == 37) {
			Mat kernel(3, 3, CV_32F, Scalar(-1));
			Mat dst1;
			kernel.at<float>(1, 1) = 8.9;
			filter2D(roi1, dst1, roi1.depth(), kernel);
			double minDistance1 = 4;
			goodFeaturesToTrack(dst1, corner, max_cornerNum, qualityLevel, minDistance1, Mat(), blockSize, useHarrisDetector, k);
		}
		else if (i == 25 || i == 27) {
			int blockSize1 = 5;
			double qualityLevel1 = 0.0005;
			goodFeaturesToTrack(roi1, corner, max_cornerNum, qualityLevel1, minDistance, Mat(), blockSize1, useHarrisDetector, k);
		}
		else if (i == 44) {
			int blockSize1 = 5;
			double qualityLevel1 = 0.0005;
			int max_cornerNum1 = 2;
			goodFeaturesToTrack(roi1, corner, max_cornerNum1, qualityLevel1, minDistance, Mat(), blockSize1, useHarrisDetector, k);
		}
		else if (i == 46) {
			Mat kernel(3, 3, CV_32F, Scalar(-1));
			Mat dst1;
			kernel.at<float>(1, 1) = 8.9;
			filter2D(roi1, dst1, roi1.depth(), kernel);
			blur(dst1, dst1, Size(3, 3));
			double qualityLevel1 = 0.0005;
			int max_cornerNum1 = 2;
			goodFeaturesToTrack(dst1, corner, max_cornerNum1, qualityLevel1, minDistance, Mat(), blockSize, useHarrisDetector, k);
		}
		else if (i == 47) {
			Mat kernel(3, 3, CV_32F, Scalar(-1));
			Mat dst1;
			kernel.at<float>(1, 1) = 8.9;
			filter2D(roi1, dst1, roi1.depth(), kernel);
			blur(dst1, dst1, Size(3, 3));
			double minDistance1 = 8;
			goodFeaturesToTrack(dst1, corner, max_cornerNum, qualityLevel, minDistance1, Mat(), blockSize, useHarrisDetector, k);
			corner[0].x = corner[0].x - 10;
			corner[0].y = corner[0].y + 13;
			corner[1].x = corner[1].x - 15;
			corner[1].y = corner[1].y + 5;
		}
		else {
			goodFeaturesToTrack(roi1, corner, max_cornerNum, qualityLevel, minDistance, Mat(), blockSize, useHarrisDetector, k);
		}
	}

	if (i >= 49 && i <= 83) {
		int max_cornerNum = 1;
		if (i == 59 || i == 79) {
			int blockSize1 = 5;
			double qualityLevel1 = 0.0005;
			goodFeaturesToTrack(roi1, corner, max_cornerNum, qualityLevel1, minDistance, Mat(), blockSize1, useHarrisDetector, k);
		}
		else
		{
			goodFeaturesToTrack(roi1, corner, max_cornerNum, qualityLevel, minDistance, Mat(), blockSize, useHarrisDetector, k);
		}
	}

	if (i >= 84 && i <= 93) {
		int max_cornerNum = 2;
		if (i == 84) {
			blur(roi1, roi1, Size(3, 3));
			double qualityLevel1 = 0.0005;
			int blockSize1 = 5;
			goodFeaturesToTrack(roi1, corner, max_cornerNum, qualityLevel1, minDistance, Mat(), blockSize1, useHarrisDetector, k);
		}
		else if (i == 87 || i == 85) {
			Mat kernel(3, 3, CV_32F, Scalar(-1));
			Mat dst1;
			kernel.at<float>(1, 1) = 8.9;
			filter2D(roi1, dst1, roi1.depth(), kernel);
			double minDistance1 = 4;
			goodFeaturesToTrack(dst1, corner, max_cornerNum, qualityLevel, minDistance1, Mat(), blockSize, useHarrisDetector, k);
		}
		else if (i == 86) {
			int blockSize1 = 5;
			double qualityLevel1 = 0.0005;
			goodFeaturesToTrack(roi1, corner, max_cornerNum, qualityLevel1, minDistance, Mat(), blockSize1, useHarrisDetector, k);
		}
		else {
			goodFeaturesToTrack(roi1, corner, max_cornerNum, qualityLevel, minDistance, Mat(), blockSize, useHarrisDetector, k);
		}
	}

	return corner;
}

vector<Point2f> ComputeCorner4(int i, Mat& roi1)
{
	vector<Point2f> corner(200);

	double minDistance = 1;
	int blockSize = 3;
	double qualityLevel = 0.5;
	bool useHarrisDetector = false;
	double k = 0.04;

	if (i >= 0 && i <= 22) {
		int max_cornerNum = 2;
		if (i == 10 || i == 21) {
			int blockSize1 = 5;
			double qualityLevel1 = 0.0005;
			goodFeaturesToTrack(roi1, corner, max_cornerNum, qualityLevel1, minDistance, Mat(), blockSize1, useHarrisDetector, k);
		}
		else
			goodFeaturesToTrack(roi1, corner, max_cornerNum, qualityLevel, minDistance, Mat(), blockSize, useHarrisDetector, k);
	}

	if (i >= 23 && i <= 47) {
		int max_cornerNum = 4;
		if (i == 24 || i == 28 || i == 30 || i == 40 || i == 42) {
			int blockSize1 = 5;
			double qualityLevel1 = 0.0005;
			goodFeaturesToTrack(roi1, corner, max_cornerNum, qualityLevel1, minDistance, Mat(), blockSize1, useHarrisDetector, k);
		}
		else if (i == 29) {
			int max_cornerNum1 = 2;
			goodFeaturesToTrack(roi1, corner, max_cornerNum1, qualityLevel, minDistance, Mat(), blockSize, useHarrisDetector, k);
		}
		else if (i == 34) {
			Mat kernel(3, 3, CV_32F, Scalar(-1));
			Mat dst1;
			kernel.at<float>(1, 1) = 8.9;
			filter2D(roi1, dst1, roi1.depth(), kernel);
			double qualityLevel1 = 0.0005;
			double minDistance1 = 5;
			goodFeaturesToTrack(dst1, corner, max_cornerNum, qualityLevel1, minDistance1, Mat(), blockSize, useHarrisDetector, k);
			corner[0].x = corner[0].x - 2;
			corner[0].y = corner[0].y - 3;
		}
		else if (i == 45 || i == 44) {
			Mat kernel(3, 3, CV_32F, Scalar(-1));
			Mat dst1;
			kernel.at<float>(1, 1) = 8.9;
			filter2D(roi1, dst1, roi1.depth(), kernel);
			int min_Thresh = 50;
			int max_Thresh = 250;
			Canny(dst1, dst1, min_Thresh, max_Thresh * 2, 3);
			if (i == 45) {
				double minDistance1 = 6;
				int max_cornerNum1 = 2;
				goodFeaturesToTrack(dst1, corner, max_cornerNum1, qualityLevel, minDistance1, Mat(), blockSize, useHarrisDetector, k);
			}
			else if (i == 44) {
				double qualityLevel1 = 0.0005;
				double minDistance1 = 10;
				goodFeaturesToTrack(dst1, corner, max_cornerNum, qualityLevel1, minDistance1, Mat(), blockSize, useHarrisDetector, k);
				corner[1].x = corner[1].x - 5;
				corner[1].y = corner[1].y - 5;
				corner[3].x = corner[3].x - 4;
				corner[3].y = corner[3].y - 6;
			}
		}
		else if (i == 46) {
			Mat kernel(3, 3, CV_32F, Scalar(-1));
			Mat dst1;
			kernel.at<float>(1, 1) = 8.9;
			filter2D(roi1, dst1, roi1.depth(), kernel);
			blur(dst1, dst1, Size(3, 3));
			double qualityLevel1 = 0.0005;
			double minDistance1 = 10;
			goodFeaturesToTrack(dst1, corner, max_cornerNum, qualityLevel1, minDistance1, Mat(), blockSize, useHarrisDetector, k);
			corner[1].x = corner[1].x + 6;
			corner[1].y = corner[1].y - 5;
			corner[2].x = corner[2].x - 3;
			corner[2].y = corner[2].y - 3;
		}
		else {
			goodFeaturesToTrack(roi1, corner, max_cornerNum, qualityLevel, minDistance, Mat(), blockSize, useHarrisDetector, k);
		}
	}

	if (i >= 48 && i <= 82) {
		int max_cornerNum = 1;
		if (i == 63 || i == 64) {
			Mat kernel(3, 3, CV_32F, Scalar(-1));
			Mat dst1;
			kernel.at<float>(1, 1) = 8.9;
			filter2D(roi1, dst1, roi1.depth(), kernel);
			goodFeaturesToTrack(dst1, corner, max_cornerNum, qualityLevel, minDistance, Mat(), blockSize, useHarrisDetector, k);
		}
		else
			goodFeaturesToTrack(roi1, corner, max_cornerNum, qualityLevel, minDistance, Mat(), blockSize, useHarrisDetector, k);
	}

	if (i >= 83 && i <= 92) {
		int max_cornerNum = 2;
		if (i == 85 || i == 91) {
			Mat kernel(3, 3, CV_32F, Scalar(-1));
			Mat dst1;
			kernel.at<float>(1, 1) = 8.9;
			filter2D(roi1, dst1, roi1.depth(), kernel);
			goodFeaturesToTrack(dst1, corner, max_cornerNum, qualityLevel, minDistance, Mat(), blockSize, useHarrisDetector, k);
		}
		else if (i == 83 || i == 86 || i == 88 || i == 89 || i == 92) {
			Mat kernel(3, 3, CV_32F, Scalar(-1));
			Mat dst1;
			kernel.at<float>(1, 1) = 8.9;
			filter2D(roi1, dst1, roi1.depth(), kernel);
			int blockSize1 = 5;
			double qualityLevel1 = 0.0005;
			if (i == 89 || i == 86 || i == 92) {
				blur(dst1, dst1, Size(3, 3));
			}
			goodFeaturesToTrack(dst1, corner, max_cornerNum, qualityLevel1, minDistance, Mat(), blockSize1, useHarrisDetector, k);
		}
		else if (i == 84) {
			Mat kernel(3, 3, CV_32F, Scalar(-1));
			Mat dst1;
			kernel.at<float>(1, 1) = 8.9;
			filter2D(roi1, dst1, roi1.depth(), kernel);
			double qualityLevel1 = 0.0005;
			goodFeaturesToTrack(dst1, corner, max_cornerNum, qualityLevel1, minDistance, Mat(), blockSize, useHarrisDetector, k);
			corner[1].x = corner[1].x - 5;
			corner[1].y = corner[1].y - 5;
		}
		else if (i == 90) {
			int blockSize1 = 5;
			double qualityLevel1 = 0.0005;
			goodFeaturesToTrack(roi1, corner, max_cornerNum, qualityLevel1, minDistance, Mat(), blockSize1, useHarrisDetector, k);
		}
		else {
			goodFeaturesToTrack(roi1, corner, max_cornerNum, qualityLevel, minDistance, Mat(), blockSize, useHarrisDetector, k);
		}
	}

	return corner;
}

void SaveFiles1(int i, vector<Point2f>& corner1, string seq) {
	ofstream outfile1, outfile2, outfile3, outfile4;
	ofstream outfile5, outfile6, outfile7, outfile8;
	ofstream outfile9, outfile10, outfile11, outfile12;
	string files;
	files = "E:\\Biyesheji\\Detection\\Detection\\match corner\\result";
	outfile1.open(files + seq + "1(1&2).txt", ios::app); outfile2.open(files + seq + "2(1&2).txt", ios::app);
	outfile3.open(files + seq + "3(1&2).txt", ios::app); outfile4.open(files + seq + "4(1&2).txt", ios::app);
	outfile5.open(files + seq + "1(1&3).txt", ios::app); outfile6.open(files + seq + "2(1&3).txt", ios::app);
	outfile7.open(files + seq + "3(1&3).txt", ios::app); outfile8.open(files + seq + "4(1&3).txt", ios::app);
	outfile9.open(files + seq + "1(1&4).txt", ios::app); outfile10.open(files + seq + "2(1&4).txt", ios::app);
	outfile11.open(files + seq + "3(1&4).txt", ios::app); outfile12.open(files + seq + "4(1&4).txt", ios::app);
	if (i == 1) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile9 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 2 && i < 5) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile1 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile9 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 5 && i < 24) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile1 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile5 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile9 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 24 && i < 27) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile1 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile5 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 27 && i < 30) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile10 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 30 && i < 33) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile2 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile10 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 33 && i < 52) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile2 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile6 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile10 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 52 && i < 55) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile2 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile6 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i == 57) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile11 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 58 && i < 60) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile3 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile11 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 60 && i < 80) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile3 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile7 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile11 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 80 && i < 82) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile3 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile7 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i == 82) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile11 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 83 && i < 84) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile3 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile11 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 84 && i < 94) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile3 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile7 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile11 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i == 94) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile3 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile7 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 95 && i<97) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile12 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 97 && i<98) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile4 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile12 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 98 && i < 105) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile4 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile8 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile12 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i == 105) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile4 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile8 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
}

void SaveFiles11(int i, vector<Point2f>& corner1, string seq) {
	ofstream outfile1, outfile2, outfile3, outfile4;
	ofstream outfile5, outfile6, outfile7, outfile8;
	ofstream outfile9, outfile10, outfile11, outfile12;
	ofstream outfile13, outfile14, outfile15, outfile16;
	string files;
	files = "E:\\Biyesheji\\Detection\\Detection\\match corner\\result";
	outfile1.open(files + seq + "1(1&2&3).txt", ios::app); outfile2.open(files + seq + "2(1&2&3).txt", ios::app);
	outfile3.open(files + seq + "3(1&2&3).txt", ios::app); outfile4.open(files + seq + "4(1&2&3).txt", ios::app);
	outfile5.open(files + seq + "1(1&3&4).txt", ios::app); outfile6.open(files + seq + "2(1&3&4).txt", ios::app);
	outfile7.open(files + seq + "3(1&3&4).txt", ios::app); outfile8.open(files + seq + "4(1&3&4).txt", ios::app);
	outfile13.open(files + seq + "1(1&2&4).txt", ios::app); outfile14.open(files + seq + "2(1&2&4).txt", ios::app);
	outfile15.open(files + seq + "3(1&2&4).txt", ios::app); outfile16.open(files + seq + "4(1&2&4).txt", ios::app);
	outfile9.open(files + seq + "1(1&2&3&4).txt", ios::app); outfile10.open(files + seq + "2(1&2&3&4).txt", ios::app);
	outfile11.open(files + seq + "3(1&2&3&4).txt", ios::app); outfile12.open(files + seq + "4(1&2&3&4).txt", ios::app);
	if (i >= 2 && i < 5) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile13 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 5 && i < 24) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile1 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile5 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile9 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile13 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 24 && i < 27) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile1 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 30 && i < 33) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile14 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 33 && i < 52) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile2 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile6 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile10 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile14 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 52 && i < 55) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile2 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 58 && i < 60) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile15 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 60 && i < 80) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile3 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile7 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile11 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile15 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 80 && i < 82) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile3 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i == 83) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile15 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 84 && i < 94) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile3 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile7 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile10 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile15 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i == 94) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile3 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i == 97) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile16 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 98 && i < 105) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile4 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile8 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile12 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile16 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i == 105) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile4 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
}

void SaveFiles2(int i, vector<Point2f>& corner1, string seq) {
	ofstream outfile1, outfile2, outfile3, outfile4;
	ofstream outfile5, outfile6, outfile7, outfile8;
	ofstream outfile9, outfile10, outfile11, outfile12;
	string files;
	files = "E:\\Biyesheji\\Detection\\Detection\\match corner\\result";
	outfile1.open(files + seq + "1(1&2).txt", ios::app);
	outfile2.open(files + seq + "2(1&2).txt", ios::app);
	outfile3.open(files + seq + "3(1&2).txt", ios::app);
	outfile4.open(files + seq + "4(1&2).txt", ios::app);
	outfile5.open(files + seq + "1(2&3).txt", ios::app);
	outfile6.open(files + seq + "2(2&3).txt", ios::app);
	outfile7.open(files + seq + "3(2&3).txt", ios::app);
	outfile8.open(files + seq + "4(2&3).txt", ios::app);
	outfile9.open(files + seq + "1(2&4).txt", ios::app);
	outfile10.open(files + seq + "2(2&4).txt", ios::app);
	outfile11.open(files + seq + "3(2&4).txt", ios::app);
	outfile12.open(files + seq + "4(2&4).txt", ios::app);
	if (i >= 0 && i < 3) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile1 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile9 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 3 && i < 22) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile1 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile9 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile5 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 22 && i < 25) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile1 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile5 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 25 && i < 26) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile5 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 27 && i < 30) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile2 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile10 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 30 && i < 49) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile2 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile6 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile10 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 49 && i < 52) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile2 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile6 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 52 && i < 55) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile6 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 55 && i < 57) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile3 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile11 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 57 && i < 77) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile3 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile7 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile11 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 77 && i < 79) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile3 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile7 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i == 79) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile7 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 82 && i < 83) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile3 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile11 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 83 && i < 93) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile3 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile7 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile11 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 93 && i < 94) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile3 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile7 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i == 94) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile7 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 95 && i<96) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile4 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile12 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 96 && i<103) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile4 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile8 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile12 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 103 && i < 104) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile4 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile8 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 104 && i < 106) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile8 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
}

void SaveFiles22(int i, vector<Point2f>& corner1, string seq) {
	ofstream outfile1, outfile2, outfile3, outfile4;
	ofstream outfile5, outfile6, outfile7, outfile8;
	ofstream outfile9, outfile10, outfile11, outfile12;
	ofstream outfile13, outfile14, outfile15, outfile16;
	string files;
	files = "E:\\Biyesheji\\Detection\\Detection\\match corner\\result";
	outfile1.open(files + seq + "1(1&2&3).txt", ios::app); outfile2.open(files + seq + "2(1&2&3).txt", ios::app);
	outfile3.open(files + seq + "3(1&2&3).txt", ios::app); outfile4.open(files + seq + "4(1&2&3).txt", ios::app);
	outfile5.open(files + seq + "1(2&3&4).txt", ios::app); outfile6.open(files + seq + "2(2&3&4).txt", ios::app);
	outfile7.open(files + seq + "3(2&3&4).txt", ios::app); outfile8.open(files + seq + "4(2&3&4).txt", ios::app);
	outfile13.open(files + seq + "1(1&2&4).txt", ios::app); outfile14.open(files + seq + "2(1&2&4).txt", ios::app);
	outfile15.open(files + seq + "3(1&2&4).txt", ios::app); outfile16.open(files + seq + "4(1&2&4).txt", ios::app);
	outfile9.open(files + seq + "1(1&2&3&4).txt", ios::app); outfile10.open(files + seq + "2(1&2&3&4).txt", ios::app);
	outfile11.open(files + seq + "3(1&2&3&4).txt", ios::app); outfile12.open(files + seq + "4(1&2&3&4).txt", ios::app);
	if (i >= 0 && i < 3) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile13 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 3 && i < 22) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile1 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile5 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile9 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile13 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 22 && i < 25) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile1 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 27 && i < 30) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile14 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 30 && i < 49) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile2 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile6 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile10 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile14 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 49 && i < 52) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile2 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 55 && i < 57) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile15 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 57 && i < 77) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile3 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile7 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile11 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile15 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 77 && i < 79) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile3 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i == 82) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile15 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 83 && i < 93) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile3 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile7 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile10 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile15 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i == 93) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile3 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i == 95) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile16 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 96 && i < 103) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile4 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile8 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile12 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile16 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i == 103) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile4 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
}

void SaveFiles3(int i, vector<Point2f>& corner1, string seq) {
	ofstream outfile1, outfile2, outfile3, outfile4;
	ofstream outfile5, outfile6, outfile7, outfile8;
	ofstream outfile9, outfile10, outfile11, outfile12;
	string files;
	files = "E:\\Biyesheji\\Detection\\Detection\\match corner\\result";
	outfile1.open(files + seq + "1(1&3).txt", ios::app);
	outfile2.open(files + seq + "2(1&3).txt", ios::app);
	outfile3.open(files + seq + "3(1&3).txt", ios::app);
	outfile4.open(files + seq + "4(1&3).txt", ios::app);
	outfile5.open(files + seq + "1(2&3).txt", ios::app);
	outfile6.open(files + seq + "2(2&3).txt", ios::app);
	outfile7.open(files + seq + "3(2&3).txt", ios::app);
	outfile8.open(files + seq + "4(2&3).txt", ios::app);
	outfile9.open(files + seq + "1(3&4).txt", ios::app);
	outfile10.open(files + seq + "2(3&4).txt", ios::app);
	outfile11.open(files + seq + "3(3&4).txt", ios::app);
	outfile12.open(files + seq + "4(3&4).txt", ios::app);
	if (i >= 0 && i < 19) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile1 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile5 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile9 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 19 && i < 22) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile1 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile5 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i == 22) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile5 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 24 && i < 43) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile2 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile6 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile10 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 43 && i < 46) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile2 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile6 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 46 && i < 49) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile6 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 49 && i < 69) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile3 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile7 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile11 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 69 && i < 71) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile3 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile7 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i == 71) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile7 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 72 && i < 82) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile3 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile7 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile11 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i == 82) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile3 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile7 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i == 83) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile7 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 84 && i < 91) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile4 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile8 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile12 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i == 91) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile4 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile8 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 92 && i < 94) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile8 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i == 94) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile7 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
}

void SaveFiles33(int i, vector<Point2f>& corner1, string seq) {
	ofstream outfile1, outfile2, outfile3, outfile4;
	ofstream outfile5, outfile6, outfile7, outfile8;
	ofstream outfile9, outfile10, outfile11, outfile12;
	ofstream outfile13, outfile14, outfile15, outfile16;
	string files;
	files = "E:\\Biyesheji\\Detection\\Detection\\match corner\\result";
	outfile1.open(files + seq + "1(1&2&3).txt", ios::app); outfile2.open(files + seq + "2(1&2&3).txt", ios::app);
	outfile3.open(files + seq + "3(1&2&3).txt", ios::app); outfile4.open(files + seq + "4(1&2&3).txt", ios::app);
	outfile5.open(files + seq + "1(2&3&4).txt", ios::app); outfile6.open(files + seq + "2(2&3&4).txt", ios::app);
	outfile7.open(files + seq + "3(2&3&4).txt", ios::app); outfile8.open(files + seq + "4(2&3&4).txt", ios::app);
	outfile13.open(files + seq + "1(1&3&4).txt", ios::app); outfile14.open(files + seq + "2(1&3&4).txt", ios::app);
	outfile15.open(files + seq + "3(1&3&4).txt", ios::app); outfile16.open(files + seq + "4(1&3&4).txt", ios::app);
	outfile9.open(files + seq + "1(1&2&3&4).txt", ios::app); outfile10.open(files + seq + "2(1&2&3&4).txt", ios::app);
	outfile11.open(files + seq + "3(1&2&3&4).txt", ios::app); outfile12.open(files + seq + "4(1&2&3&4).txt", ios::app);
	if (i >= 0 && i < 19) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile1 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile5 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile9 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile13 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 19 && i < 22) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile1 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 24 && i < 43) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile2 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile6 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile10 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile14 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 43 && i < 46) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile2 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 49 && i < 69) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile3 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile7 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile11 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile15 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 69 && i < 71) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile3 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 72 && i < 82) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile3 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile7 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile10 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile15 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i == 82) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile3 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 84 && i < 91) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile4 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile8 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile12 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile16 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i == 91) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile4 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
}

void SaveFiles4(int i, vector<Point2f>& corner1, string seq) {
	ofstream outfile1, outfile2, outfile3, outfile4;
	ofstream outfile5, outfile6, outfile7, outfile8;
	ofstream outfile9, outfile10, outfile11, outfile12;
	string files;
	files = "E:\\Biyesheji\\Detection\\Detection\\match corner\\result";
	outfile1.open(files + seq + "1(1&4).txt", ios::app);
	outfile2.open(files + seq + "2(1&4).txt", ios::app);
	outfile3.open(files + seq + "3(1&4).txt", ios::app);
	outfile4.open(files + seq + "4(1&4).txt", ios::app);
	outfile5.open(files + seq + "1(2&4).txt", ios::app);
	outfile6.open(files + seq + "2(2&4).txt", ios::app);
	outfile7.open(files + seq + "3(2&4).txt", ios::app);
	outfile8.open(files + seq + "4(2&4).txt", ios::app);
	outfile9.open(files + seq + "1(3&4).txt", ios::app);
	outfile10.open(files + seq + "2(3&4).txt", ios::app);
	outfile11.open(files + seq + "3(3&4).txt", ios::app);
	outfile12.open(files + seq + "4(3&4).txt", ios::app);
	if (i == 0) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile1 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 1 && i < 4) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile1 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile5 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 4 && i < 23) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile1 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile5 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile9 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i == 22) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile5 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 23 && i < 26) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile2 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 26 && i < 29) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile2 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile6 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 29 && i < 48) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile6 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile2 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile10 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i == 48) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile3 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 49 && i < 51) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile3 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile7 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 51 && i < 71) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile3 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile7 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile11 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i == 71) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile3 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i == 72) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile3 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile7 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 73 && i < 83) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile3 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile7 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile11 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 83 && i < 85) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile4 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i == 85) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile4 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile8 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 86 && i < 93) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile4 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile8 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile12 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
}

void SaveFiles44(int i, vector<Point2f>& corner1, string seq) {
	ofstream outfile1, outfile2, outfile3, outfile4;
	ofstream outfile5, outfile6, outfile7, outfile8;
	ofstream outfile9, outfile10, outfile11, outfile12;
	ofstream outfile13, outfile14, outfile15, outfile16;
	string files;
	files = "E:\\Biyesheji\\Detection\\Detection\\match corner\\result";
	outfile1.open(files + seq + "1(1&2&4).txt", ios::app); outfile2.open(files + seq + "2(1&2&4).txt", ios::app);
	outfile3.open(files + seq + "3(1&2&4).txt", ios::app); outfile4.open(files + seq + "4(1&2&4).txt", ios::app);
	outfile5.open(files + seq + "1(2&3&4).txt", ios::app); outfile6.open(files + seq + "2(2&3&4).txt", ios::app);
	outfile7.open(files + seq + "3(2&3&4).txt", ios::app); outfile8.open(files + seq + "4(2&3&4).txt", ios::app);
	outfile13.open(files + seq + "1(1&3&4).txt", ios::app); outfile14.open(files + seq + "2(1&3&4).txt", ios::app);
	outfile15.open(files + seq + "3(1&3&4).txt", ios::app); outfile16.open(files + seq + "4(1&3&4).txt", ios::app);
	outfile9.open(files + seq + "1(1&2&3&4).txt", ios::app); outfile10.open(files + seq + "2(1&2&3&4).txt", ios::app);
	outfile11.open(files + seq + "3(1&2&3&4).txt", ios::app); outfile12.open(files + seq + "4(1&2&3&4).txt", ios::app);
	if (i >= 1 && i < 4) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile1 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 4 && i < 23) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile1 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile5 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile9 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile13 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 26 && i < 29) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile2 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 29 && i < 48) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile2 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile6 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile10 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile14 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 51 && i < 71) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile3 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile7 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile11 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile15 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 49 && i < 51) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile3 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i == 71) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile3 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 72 && i < 83) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile3 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile7 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile10 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile15 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i == 85) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile4 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
	else if (i >= 86 && i < 93) {
		for (int j = 0; j < corner1.size(); j++) {
			outfile4 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile8 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile12 << corner1[j].x << "\t" << corner1[j].y << endl;
			outfile16 << corner1[j].x << "\t" << corner1[j].y << endl;
		}
	}
}

void MatchPoint1_2(int i, vector<int> letters, Mat& roi1, Mat& roi2, vector<KeyPoint>& keyPoint1, vector<KeyPoint>& keyPoint2)
{
	vector<KeyPoint> keyPoints1(200), keyPoints2(200);//循环前预定义

	int a = letters[0];
	int b = letters[1];
	int e = letters[2];
	int f = letters[3];

	if (i<25) {
		ifstream infile1, infile2;
		string filename;
		filename = "E:\\Biyesheji\\Detection\\Detection\\match corner\\";
		infile1.open(filename + "result11(1&2).txt", ios::in);
		infile2.open(filename + "result21(1&2).txt", ios::in);
		double x1[200], y1[200], x2[200], y2[200];
		while (!infile1.eof()) {
			for (int j = 0; j < 50; j++)
			{
				infile1 >> x1[j] >> y1[j];
			}
		}
		while (!infile2.eof()) {
			for (int j = 0; j < 50; j++)
			{
				infile2 >> x2[j] >> y2[j];
			}
		}
		GoodFeaturesToTrackDetector Detector(2);  //最大点数,值越大，点越多
		Detector.detect(roi1, keyPoint1);
		keyPoint1[0].pt.x = x1[2 * i] - a; keyPoint1[0].pt.y = y1[2 * i] - b;
		keyPoint1[1].pt.x = x1[2 * i + 1] - a; keyPoint1[1].pt.y = y1[2 * i + 1] - b;
		if (keyPoint1[0].pt.x < keyPoint1[1].pt.x) {
			keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
		}
		else if (keyPoint1[0].pt.x > keyPoint1[1].pt.x) {
			keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
		}
		else if (keyPoint1[0].pt.x == keyPoint1[1].pt.x) {
			if (keyPoint1[0].pt.y > keyPoint1[1].pt.y) {
				keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
			}
			else
				keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
		}
		Detector.detect(roi2, keyPoint2);
		keyPoint2[0].pt.x = x2[2 * i] - e; keyPoint2[0].pt.y = y2[2 * i] - f;
		keyPoint2[1].pt.x = x2[2 * i + 1] - e; keyPoint2[1].pt.y = y2[2 * i + 1] - f;
		if (keyPoint2[0].pt.x < keyPoint2[1].pt.x) {
			keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
		}
		else if (keyPoint2[0].pt.x > keyPoint2[1].pt.x) {
			keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
		}
		else if (keyPoint2[0].pt.x == keyPoint2[1].pt.x) {
			if (keyPoint2[0].pt.y > keyPoint2[1].pt.y) {
				keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
			}
			else
				keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
		}

	}

	else if (i >= 25 && i < 50) {
		ifstream infile1, infile2;
		string filename;
		filename = "E:\\Biyesheji\\Detection\\Detection\\match corner\\";
		infile1.open(filename + "result12(1&2).txt", ios::in);
		infile2.open(filename + "result22(1&2).txt", ios::in);
		double x1[200], y1[200], x2[200], y2[200];
		while (!infile1.eof()) {
			for (int j = 0; j < 76; j++)
			{
				infile1 >> x1[j] >> y1[j];
			}
		}
		while (!infile2.eof()) {
			for (int j = 0; j < 76; j++)
			{
				infile2 >> x2[j] >> y2[j];
			}
		}
		if (i % 2 == 1) {
			GoodFeaturesToTrackDetector Detector(4);
			Detector.detect(roi1, keyPoint1);
			int p = (i - 25) / 2;
			keyPoint1[0].pt.x = x1[6 * p] - a; keyPoint1[0].pt.y = y1[6 * p] - b;
			keyPoint1[1].pt.x = x1[6 * p + 1] - a; keyPoint1[1].pt.y = y1[6 * p + 1] - b;
			keyPoint1[2].pt.x = x1[6 * p + 2] - a; keyPoint1[2].pt.y = y1[6 * p + 2] - b;
			keyPoint1[3].pt.x = x1[6 * p + 3] - a; keyPoint1[3].pt.y = y1[6 * p + 3] - b;
			if (keyPoint1[0].pt.x >= keyPoint1[1].pt.x&&keyPoint1[0].pt.x >= keyPoint1[1].pt.x&&keyPoint1[0].pt.x >= keyPoint1[3].pt.x) {
				keyPoint1[0].class_id = 1;
				if (keyPoint1[1].pt.x >= keyPoint1[2].pt.x&&keyPoint1[1].pt.x >= keyPoint1[3].pt.x) {
					keyPoint1[1].class_id = 2;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 3;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 3;
						keyPoint1[2].class_id = 4;
					}
				}
				else if (keyPoint1[1].pt.x <= keyPoint1[2].pt.x&&keyPoint1[1].pt.x <= keyPoint1[3].pt.x) {
					keyPoint1[1].class_id = 4;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 2;
						keyPoint1[3].class_id = 3;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 3;
					}
				}
				else {
					keyPoint1[1].class_id = 3;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 2;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 4;
					}
				}
			}
			else if (keyPoint1[1].pt.x >= keyPoint1[0].pt.x&&keyPoint1[1].pt.x >= keyPoint1[2].pt.x&&keyPoint1[1].pt.x >= keyPoint1[3].pt.x) {
				keyPoint1[1].class_id = 1;
				if (keyPoint1[0].pt.x >= keyPoint1[2].pt.x&&keyPoint1[0].pt.x >= keyPoint1[3].pt.x) {
					keyPoint1[0].class_id = 2;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 3;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 3;
						keyPoint1[2].class_id = 4;
					}
				}
				else if (keyPoint1[0].pt.x <= keyPoint1[2].pt.x&&keyPoint1[01].pt.x <= keyPoint1[3].pt.x) {
					keyPoint1[0].class_id = 4;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 2;
						keyPoint1[3].class_id = 3;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 3;
					}
				}
				else {
					keyPoint1[0].class_id = 3;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 2;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 4;
					}
				}
			}
			else if (keyPoint1[2].pt.x >= keyPoint1[0].pt.x&&keyPoint1[2].pt.x >= keyPoint1[1].pt.x&&keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
				keyPoint1[2].class_id = 1;
				if (keyPoint1[0].pt.x >= keyPoint1[1].pt.x&&keyPoint1[0].pt.x >= keyPoint1[3].pt.x) {
					keyPoint1[0].class_id = 2;
					if (keyPoint1[1].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[1].class_id = 3;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 3;
						keyPoint1[1].class_id = 4;
					}
				}
				else if (keyPoint1[0].pt.x <= keyPoint1[1].pt.x&&keyPoint1[0].pt.x <= keyPoint1[3].pt.x) {
					keyPoint1[0].class_id = 4;
					if (keyPoint1[1].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[1].class_id = 2;
						keyPoint1[3].class_id = 3;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[1].class_id = 3;
					}
				}
				else {
					keyPoint1[0].class_id = 3;
					if (keyPoint1[1].pt.x > keyPoint1[3].pt.x) {
						keyPoint1[1].class_id = 2;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[1].class_id = 4;
					}
				}
			}
			else if (keyPoint1[3].pt.x >= keyPoint1[0].pt.x&&keyPoint1[3].pt.x >= keyPoint1[1].pt.x&&keyPoint1[3].pt.x >= keyPoint1[2].pt.x) {
				keyPoint1[3].class_id = 1;
				if (keyPoint1[0].pt.x >= keyPoint1[1].pt.x&&keyPoint1[0].pt.x >= keyPoint1[2].pt.x) {
					keyPoint1[0].class_id = 2;
					if (keyPoint1[1].pt.x >= keyPoint1[2].pt.x) {
						keyPoint1[1].class_id = 3;
						keyPoint1[2].class_id = 4;
					}
					else {
						keyPoint1[2].class_id = 3;
						keyPoint1[1].class_id = 4;
					}
				}
				else if (keyPoint1[0].pt.x <= keyPoint1[1].pt.x&&keyPoint1[0].pt.x <= keyPoint1[2].pt.x) {
					keyPoint1[0].class_id = 4;
					if (keyPoint1[1].pt.x >= keyPoint1[2].pt.x) {
						keyPoint1[1].class_id = 2;
						keyPoint1[2].class_id = 3;
					}
					else {
						keyPoint1[2].class_id = 2;
						keyPoint1[1].class_id = 3;
					}
				}
				else {
					keyPoint1[0].class_id = 3;
					if (keyPoint1[1].pt.x >= keyPoint1[2].pt.x) {
						keyPoint1[1].class_id = 2;
						keyPoint1[2].class_id = 4;
					}
					else {
						keyPoint1[2].class_id = 2;
						keyPoint1[1].class_id = 4;
					}
				}
			}
			for (int k = 0; k < 4; k++) {
				for (int j = k + 1; j < 4; j++) {
					if (keyPoint1[k].pt.x == keyPoint1[j].pt.x) {
						int max = keyPoint1[k].class_id;
						if (keyPoint1[k].pt.y > keyPoint1[j].pt.y&&keyPoint2[k].class_id < keyPoint1[j].class_id) {
							keyPoint1[j].class_id = keyPoint1[j].class_id;
							keyPoint1[k].class_id = max;
						}
						else if (keyPoint1[k].pt.y < keyPoint1[j].pt.y&&keyPoint1[k].class_id < keyPoint1[j].class_id) {
							keyPoint1[k].class_id = keyPoint1[j].class_id;
							keyPoint1[j].class_id = max;
						}
						else if (keyPoint1[k].pt.y > keyPoint1[j].pt.y&&keyPoint1[k].class_id > keyPoint1[j].class_id) {
							keyPoint1[k].class_id = keyPoint1[j].class_id;
							keyPoint1[j].class_id = max;
						}
						else if (keyPoint1[k].pt.y < keyPoint1[j].pt.y&&keyPoint1[k].class_id > keyPoint1[j].class_id) {
							keyPoint1[j].class_id = keyPoint1[j].class_id;
							keyPoint1[k].class_id = max;
						}
					}
				}
			}
			Detector.detect(roi2, keyPoint2);
			keyPoint2[0].pt.x = x2[6 * p] - e; keyPoint2[0].pt.y = y2[6 * p] - f;
			keyPoint2[1].pt.x = x2[6 * p + 1] - e; keyPoint2[1].pt.y = y2[6 * p + 1] - f;
			keyPoint2[2].pt.x = x2[6 * p + 2] - e; keyPoint2[2].pt.y = y2[6 * p + 2] - f;
			keyPoint2[3].pt.x = x2[6 * p + 3] - e; keyPoint2[3].pt.y = y2[6 * p + 3] - f;
			if (keyPoint2[0].pt.x >= keyPoint2[1].pt.x&&keyPoint2[0].pt.x >= keyPoint2[2].pt.x&&keyPoint2[0].pt.x >= keyPoint2[3].pt.x) {
				keyPoint2[0].class_id = 1;
				if (keyPoint2[1].pt.x >= keyPoint2[2].pt.x&&keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
					keyPoint2[1].class_id = 2;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 3;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 3;
						keyPoint2[2].class_id = 4;
					}
				}
				else if (keyPoint2[1].pt.x <= keyPoint2[2].pt.x&&keyPoint2[1].pt.x <= keyPoint2[3].pt.x) {
					keyPoint2[1].class_id = 4;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 2;
						keyPoint2[3].class_id = 3;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[2].class_id = 3;
					}
				}
				else {
					keyPoint2[1].class_id = 3;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 2;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[2].class_id = 4;
					}
				}
			}
			else if (keyPoint2[1].pt.x >= keyPoint2[0].pt.x&&keyPoint2[1].pt.x >= keyPoint2[2].pt.x&&keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
				keyPoint2[1].class_id = 1;
				if (keyPoint2[0].pt.x >= keyPoint2[2].pt.x&&keyPoint2[0].pt.x >= keyPoint2[3].pt.x) {
					keyPoint2[0].class_id = 2;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 3;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 3;
						keyPoint2[2].class_id = 4;
					}
				}
				else if (keyPoint2[0].pt.x <= keyPoint2[2].pt.x&&keyPoint1[01].pt.x <= keyPoint2[3].pt.x) {
					keyPoint2[0].class_id = 4;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 2;
						keyPoint2[3].class_id = 3;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[2].class_id = 3;
					}
				}
				else {
					keyPoint2[0].class_id = 3;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 2;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 4;
					}
				}
			}
			else if (keyPoint2[2].pt.x >= keyPoint2[0].pt.x&&keyPoint2[2].pt.x >= keyPoint2[1].pt.x&&keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
				keyPoint2[2].class_id = 1;
				if (keyPoint2[0].pt.x >= keyPoint2[1].pt.x&&keyPoint2[0].pt.x >= keyPoint2[3].pt.x) {
					keyPoint2[0].class_id = 2;
					if (keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[1].class_id = 3;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 3;
						keyPoint2[1].class_id = 4;
					}
				}
				else if (keyPoint2[0].pt.x <= keyPoint2[1].pt.x&&keyPoint2[0].pt.x <= keyPoint2[3].pt.x) {
					keyPoint2[0].class_id = 4;
					if (keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[1].class_id = 2;
						keyPoint2[3].class_id = 3;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[1].class_id = 3;
					}
				}
				else {
					keyPoint2[0].class_id = 3;
					if (keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[1].class_id = 2;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[1].class_id = 4;
					}
				}
			}
			else if (keyPoint2[3].pt.x >= keyPoint2[0].pt.x&&keyPoint2[3].pt.x >= keyPoint2[1].pt.x&&keyPoint2[3].pt.x >= keyPoint2[2].pt.x) {
				keyPoint2[3].class_id = 1;
				if (keyPoint2[0].pt.x >= keyPoint2[1].pt.x&&keyPoint2[0].pt.x >= keyPoint2[2].pt.x) {
					keyPoint2[0].class_id = 2;
					if (keyPoint2[1].pt.x >= keyPoint2[2].pt.x) {
						keyPoint2[1].class_id = 3;
						keyPoint2[2].class_id = 4;
					}
					else {
						keyPoint2[2].class_id = 3;
						keyPoint2[1].class_id = 4;
					}
				}
				else if (keyPoint2[0].pt.x <= keyPoint2[1].pt.x&&keyPoint2[0].pt.x <= keyPoint2[2].pt.x) {
					keyPoint2[0].class_id = 4;
					if (keyPoint2[1].pt.x >= keyPoint2[2].pt.x) {
						keyPoint2[1].class_id = 2;
						keyPoint2[2].class_id = 3;
					}
					else {
						keyPoint2[2].class_id = 2;
						keyPoint2[1].class_id = 3;
					}
				}
				else {
					keyPoint2[0].class_id = 3;
					if (keyPoint2[1].pt.x >= keyPoint2[2].pt.x) {
						keyPoint2[1].class_id = 2;
						keyPoint2[2].class_id = 4;
					}
					else {
						keyPoint2[2].class_id = 2;
						keyPoint2[1].class_id = 4;
					}
				}
			}
			for (int k = 0; k < 4; k++) {
				for (int j = k + 1; j < 4; j++) {
					if (keyPoint2[k].pt.x == keyPoint2[j].pt.x) {
						int max = keyPoint2[k].class_id;
						if (keyPoint2[k].pt.y > keyPoint2[j].pt.y&&keyPoint2[k].class_id < keyPoint2[j].class_id) {
							keyPoint2[j].class_id = keyPoint2[j].class_id;
							keyPoint2[k].class_id = max;
						}
						else if (keyPoint2[k].pt.y < keyPoint2[j].pt.y&&keyPoint2[k].class_id < keyPoint2[j].class_id) {
							keyPoint2[k].class_id = keyPoint2[j].class_id;
							keyPoint2[j].class_id = max;
						}
						else if (keyPoint2[k].pt.y > keyPoint2[j].pt.y&&keyPoint2[k].class_id > keyPoint2[j].class_id) {
							keyPoint2[k].class_id = keyPoint2[j].class_id;
							keyPoint2[j].class_id = max;
						}
						else if (keyPoint2[k].pt.y < keyPoint2[j].pt.y&&keyPoint2[k].class_id > keyPoint2[j].class_id) {
							keyPoint2[j].class_id = keyPoint2[j].class_id;
							keyPoint2[k].class_id = max;
						}
					}
				}
			}
		}
		else {
			int p = (i - 25) / 2;
			GoodFeaturesToTrackDetector Detector(2);
			Detector.detect(roi1, keyPoint1);
			keyPoint1[0].pt.x = x1[6 * p + 4] - a; keyPoint1[0].pt.y = y1[6 * p + 4] - b;
			keyPoint1[1].pt.x = x1[6 * p + 5] - a; keyPoint1[1].pt.y = y1[6 * p + 5] - b;
			if (keyPoint1[0].pt.x < keyPoint1[1].pt.x) {
				keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
			}
			else if (keyPoint1[0].pt.x > keyPoint1[1].pt.x) {
				keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
			}
			else if (keyPoint1[0].pt.x == keyPoint1[1].pt.x) {
				if (keyPoint1[0].pt.y > keyPoint1[1].pt.y) {
					keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
				}
				else
					keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
			}

			Detector.detect(roi2, keyPoint2);
			keyPoint2[0].pt.x = x2[6 * p + 4] - e; keyPoint2[0].pt.y = y2[6 * p + 4] - f;
			keyPoint2[1].pt.x = x2[6 * p + 5] - e; keyPoint2[1].pt.y = y2[6 * p + 5] - f;
			if (keyPoint2[0].pt.x < keyPoint2[1].pt.x) {
				keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
			}
			else if (keyPoint2[0].pt.x > keyPoint2[1].pt.x) {
				keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
			}
			else if (keyPoint2[0].pt.x == keyPoint2[1].pt.x) {
				if (keyPoint2[0].pt.y > keyPoint2[1].pt.y) {
					keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
				}
				else
					keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
			}
		}
	}
	else if (i >= 50 && i < 86) {
		int p = i - 50;
		ifstream infile1, infile2;
		string filename;
		filename = "E:\\Biyesheji\\Detection\\Detection\\match corner\\";
		infile1.open(filename + "result13(1&2).txt", ios::in);
		infile2.open(filename + "result23(1&2).txt", ios::in);
		double x1[200], y1[200], x2[200], y2[200];
		while (!infile1.eof()) {
			for (int j = 0; j < 36; j++)
			{
				infile1 >> x1[j] >> y1[j];
			}
		}
		while (!infile2.eof()) {
			for (int j = 0; j < 36; j++)
			{
				infile2 >> x2[j] >> y2[j];
			}
		}
		GoodFeaturesToTrackDetector Detector(1);
		Detector.detect(roi1, keyPoint1);
		Detector.detect(roi2, keyPoint2);
		keyPoint1[0].pt.x = x1[p] - a; keyPoint1[0].pt.y = y1[p] - b;
		keyPoint2[0].pt.x = x2[p] - e; keyPoint2[0].pt.y = y2[p] - f;
		keyPoint1[0].class_id = i;
		keyPoint2[0].class_id = i;
	}
	else {
		ifstream infile1, infile2;
		string filename;
		filename = "E:\\Biyesheji\\Detection\\Detection\\match corner\\";
		infile1.open(filename + "result14(1&2).txt", ios::in);
		infile2.open(filename + "result24(1&2).txt", ios::in);
		double x1[200], y1[200], x2[200], y2[200];
		while (!infile1.eof()) {
			for (int j = 0; j < 18; j++)
			{
				infile1 >> x1[j] >> y1[j];
			}
		}
		while (!infile2.eof()) {
			for (int j = 0; j < 18; j++)
			{
				infile2 >> x2[j] >> y2[j];
			}
		}
		int p = i - 86;
		GoodFeaturesToTrackDetector Detector(2);
		Detector.detect(roi1, keyPoint1);
		keyPoint1[0].pt.x = x1[p * 2] - a; keyPoint1[0].pt.y = y1[p * 2] - b;
		keyPoint1[1].pt.x = x1[p * 2 + 1] - a; keyPoint1[1].pt.y = y1[p * 2 + 1] - b;
		if (keyPoint1[0].pt.x < keyPoint1[1].pt.x) {
			keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
		}
		else if (keyPoint1[0].pt.x > keyPoint1[1].pt.x) {
			keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
		}
		else if (keyPoint1[0].pt.x == keyPoint1[1].pt.x) {
			if (keyPoint1[0].pt.y > keyPoint1[1].pt.y) {
				keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
			}
			else
				keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
		}
		Detector.detect(roi2, keyPoint2);
		keyPoint2[0].pt.x = x2[p * 2] - e; keyPoint2[0].pt.y = y2[p * 2] - f;
		keyPoint2[1].pt.x = x2[p * 2 + 1] - e; keyPoint2[1].pt.y = y2[p * 2 + 1] - f;
		if (keyPoint2[0].pt.x < keyPoint2[1].pt.x) {
			keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
		}
		else if (keyPoint2[0].pt.x > keyPoint2[1].pt.x) {
			keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
		}
		else if (keyPoint2[0].pt.x == keyPoint2[1].pt.x) {
			if (keyPoint2[0].pt.y > keyPoint2[1].pt.y) {
				keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
			}
			else
				keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
		}
	}
}

void MatchPoint1_3(int i, vector<int> letters, Mat& roi1, Mat& roi2, vector<KeyPoint>& keyPoint1, vector<KeyPoint>& keyPoint2)
{
	vector<KeyPoint> keyPoints1(200), keyPoints2(200);//循环前预定义

	int a = letters[0];
	int b = letters[1];
	int e = letters[2];
	int f = letters[3];

	if (i<22) {
		ifstream infile1, infile2;
		string filename;
		filename = "E:\\Biyesheji\\Detection\\Detection\\match corner\\";
		infile1.open(filename + "result11(1&3).txt", ios::in);
		infile2.open(filename + "result31(1&3).txt", ios::in);
		double x1[200], y1[200], x2[200], y2[200];
		while (!infile1.eof()) {
			for (int j = 0; j < 44; j++)
			{
				infile1 >> x1[j] >> y1[j];
			}
		}
		while (!infile2.eof()) {
			for (int j = 0; j < 44; j++)
			{
				infile2 >> x2[j] >> y2[j];
			}
		}
		GoodFeaturesToTrackDetector Detector(2);  //最大点数,值越大，点越多
		Detector.detect(roi1, keyPoint1);
		keyPoint1[0].pt.x = x1[2 * i] - a; keyPoint1[0].pt.y = y1[2 * i] - b;
		keyPoint1[1].pt.x = x1[2 * i + 1] - a; keyPoint1[1].pt.y = y1[2 * i + 1] - b;
		if (keyPoint1[0].pt.x < keyPoint1[1].pt.x) {
			keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
		}
		else if (keyPoint1[0].pt.x > keyPoint1[1].pt.x) {
			keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
		}
		else if (keyPoint1[0].pt.x == keyPoint1[1].pt.x) {
			if (keyPoint1[0].pt.y > keyPoint1[1].pt.y) {
				keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
			}
			else
				keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
		}
		Detector.detect(roi2, keyPoint2);
		keyPoint2[0].pt.x = x2[2 * i] - e; keyPoint2[0].pt.y = y2[2 * i] - f;
		keyPoint2[1].pt.x = x2[2 * i + 1] - e; keyPoint2[1].pt.y = y2[2 * i + 1] - f;
		if (keyPoint2[0].pt.x < keyPoint2[1].pt.x) {
			keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
		}
		else if (keyPoint2[0].pt.x > keyPoint2[1].pt.x) {
			keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
		}
		else if (keyPoint2[0].pt.x == keyPoint2[1].pt.x) {
			if (keyPoint2[0].pt.y > keyPoint2[1].pt.y) {
				keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
			}
			else
				keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
		}

	}
	else if (i >= 22 && i < 44) {
		ifstream infile1, infile2;
		string filename;
		filename = "E:\\Biyesheji\\Detection\\Detection\\match corner\\";
		infile1.open(filename + "result12(1&3).txt", ios::in);
		infile2.open(filename + "result32(1&3).txt", ios::in);
		double x1[200], y1[200], x2[200], y2[200];
		while (!infile1.eof()) {
			for (int j = 0; j < 65; j++)
			{
				infile1 >> x1[j] >> y1[j];
			}
		}
		while (!infile2.eof()) {
			for (int j = 0; j < 65; j++)
			{
				infile2 >> x2[j] >> y2[j];
			}
		}
		if (i % 2 == 1) {
			GoodFeaturesToTrackDetector Detector(4);
			Detector.detect(roi1, keyPoint1);
			int p = (i - 22) / 2;
			keyPoint1[0].pt.x = x1[6 * p + 2] - a; keyPoint1[0].pt.y = y1[6 * p + 2] - b;
			keyPoint1[1].pt.x = x1[6 * p + 3] - a; keyPoint1[1].pt.y = y1[6 * p + 3] - b;
			keyPoint1[2].pt.x = x1[6 * p + 4] - a; keyPoint1[2].pt.y = y1[6 * p + 4] - b;
			keyPoint1[3].pt.x = x1[6 * p + 5] - a; keyPoint1[3].pt.y = y1[6 * p + 5] - b;
			if (keyPoint1[0].pt.x >= keyPoint1[1].pt.x&&keyPoint1[0].pt.x >= keyPoint1[1].pt.x&&keyPoint1[0].pt.x >= keyPoint1[3].pt.x) {
				keyPoint1[0].class_id = 1;
				if (keyPoint1[1].pt.x >= keyPoint1[2].pt.x&&keyPoint1[1].pt.x >= keyPoint1[3].pt.x) {
					keyPoint1[1].class_id = 2;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 3;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 3;
						keyPoint1[2].class_id = 4;
					}
				}
				else if (keyPoint1[1].pt.x <= keyPoint1[2].pt.x&&keyPoint1[1].pt.x <= keyPoint1[3].pt.x) {
					keyPoint1[1].class_id = 4;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 2;
						keyPoint1[3].class_id = 3;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 3;
					}
				}
				else {
					keyPoint1[1].class_id = 3;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 2;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 4;
					}
				}
			}
			else if (keyPoint1[1].pt.x >= keyPoint1[0].pt.x&&keyPoint1[1].pt.x >= keyPoint1[2].pt.x&&keyPoint1[1].pt.x >= keyPoint1[3].pt.x) {
				keyPoint1[1].class_id = 1;
				if (keyPoint1[0].pt.x >= keyPoint1[2].pt.x&&keyPoint1[0].pt.x >= keyPoint1[3].pt.x) {
					keyPoint1[0].class_id = 2;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 3;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 3;
						keyPoint1[2].class_id = 4;
					}
				}
				else if (keyPoint1[0].pt.x <= keyPoint1[2].pt.x&&keyPoint1[01].pt.x <= keyPoint1[3].pt.x) {
					keyPoint1[0].class_id = 4;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 2;
						keyPoint1[3].class_id = 3;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 3;
					}
				}
				else {
					keyPoint1[0].class_id = 3;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 2;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 4;
					}
				}
			}
			else if (keyPoint1[2].pt.x >= keyPoint1[0].pt.x&&keyPoint1[2].pt.x >= keyPoint1[1].pt.x&&keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
				keyPoint1[2].class_id = 1;
				if (keyPoint1[0].pt.x >= keyPoint1[1].pt.x&&keyPoint1[0].pt.x >= keyPoint1[3].pt.x) {
					keyPoint1[0].class_id = 2;
					if (keyPoint1[1].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[1].class_id = 3;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 3;
						keyPoint1[1].class_id = 4;
					}
				}
				else if (keyPoint1[0].pt.x <= keyPoint1[1].pt.x&&keyPoint1[0].pt.x <= keyPoint1[3].pt.x) {
					keyPoint1[0].class_id = 4;
					if (keyPoint1[1].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[1].class_id = 2;
						keyPoint1[3].class_id = 3;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[1].class_id = 3;
					}
				}
				else {
					keyPoint1[0].class_id = 3;
					if (keyPoint1[1].pt.x > keyPoint1[3].pt.x) {
						keyPoint1[1].class_id = 2;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[1].class_id = 4;
					}
				}
			}
			else if (keyPoint1[3].pt.x >= keyPoint1[0].pt.x&&keyPoint1[3].pt.x >= keyPoint1[1].pt.x&&keyPoint1[3].pt.x >= keyPoint1[2].pt.x) {
				keyPoint1[3].class_id = 1;
				if (keyPoint1[0].pt.x >= keyPoint1[1].pt.x&&keyPoint1[0].pt.x >= keyPoint1[2].pt.x) {
					keyPoint1[0].class_id = 2;
					if (keyPoint1[1].pt.x >= keyPoint1[2].pt.x) {
						keyPoint1[1].class_id = 3;
						keyPoint1[2].class_id = 4;
					}
					else {
						keyPoint1[2].class_id = 3;
						keyPoint1[1].class_id = 4;
					}
				}
				else if (keyPoint1[0].pt.x <= keyPoint1[1].pt.x&&keyPoint1[0].pt.x <= keyPoint1[2].pt.x) {
					keyPoint1[0].class_id = 4;
					if (keyPoint1[1].pt.x >= keyPoint1[2].pt.x) {
						keyPoint1[1].class_id = 2;
						keyPoint1[2].class_id = 3;
					}
					else {
						keyPoint1[2].class_id = 2;
						keyPoint1[1].class_id = 3;
					}
				}
				else {
					keyPoint1[0].class_id = 3;
					if (keyPoint1[1].pt.x >= keyPoint1[2].pt.x) {
						keyPoint1[1].class_id = 2;
						keyPoint1[2].class_id = 4;
					}
					else {
						keyPoint1[2].class_id = 2;
						keyPoint1[1].class_id = 4;
					}
				}
			}
			for (int k = 0; k < 4; k++) {
				for (int j = k + 1; j < 4; j++) {
					if (keyPoint1[k].pt.x == keyPoint1[j].pt.x) {
						int max = keyPoint1[k].class_id;
						if (keyPoint1[k].pt.y > keyPoint1[j].pt.y&&keyPoint2[k].class_id < keyPoint1[j].class_id) {
							keyPoint1[j].class_id = keyPoint1[j].class_id;
							keyPoint1[k].class_id = max;
						}
						else if (keyPoint1[k].pt.y < keyPoint1[j].pt.y&&keyPoint1[k].class_id < keyPoint1[j].class_id) {
							keyPoint1[k].class_id = keyPoint1[j].class_id;
							keyPoint1[j].class_id = max;
						}
						else if (keyPoint1[k].pt.y > keyPoint1[j].pt.y&&keyPoint1[k].class_id > keyPoint1[j].class_id) {
							keyPoint1[k].class_id = keyPoint1[j].class_id;
							keyPoint1[j].class_id = max;
						}
						else if (keyPoint1[k].pt.y < keyPoint1[j].pt.y&&keyPoint1[k].class_id > keyPoint1[j].class_id) {
							keyPoint1[j].class_id = keyPoint1[j].class_id;
							keyPoint1[k].class_id = max;
						}
					}
				}
			}
			Detector.detect(roi2, keyPoint2);
			keyPoint2[0].pt.x = x2[6 * p + 2] - e; keyPoint2[0].pt.y = y2[6 * p + 2] - f;
			keyPoint2[1].pt.x = x2[6 * p + 3] - e; keyPoint2[1].pt.y = y2[6 * p + 3] - f;
			keyPoint2[2].pt.x = x2[6 * p + 4] - e; keyPoint2[2].pt.y = y2[6 * p + 4] - f;
			keyPoint2[3].pt.x = x2[6 * p + 5] - e; keyPoint2[3].pt.y = y2[6 * p + 5] - f;
			if (keyPoint2[0].pt.x >= keyPoint2[1].pt.x&&keyPoint2[0].pt.x >= keyPoint2[2].pt.x&&keyPoint2[0].pt.x >= keyPoint2[3].pt.x) {
				keyPoint2[0].class_id = 1;
				if (keyPoint2[1].pt.x >= keyPoint2[2].pt.x&&keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
					keyPoint2[1].class_id = 2;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 3;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 3;
						keyPoint2[2].class_id = 4;
					}
				}
				else if (keyPoint2[1].pt.x <= keyPoint2[2].pt.x&&keyPoint2[1].pt.x <= keyPoint2[3].pt.x) {
					keyPoint2[1].class_id = 4;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 2;
						keyPoint2[3].class_id = 3;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[2].class_id = 3;
					}
				}
				else {
					keyPoint2[1].class_id = 3;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 2;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[2].class_id = 4;
					}
				}
			}
			else if (keyPoint2[1].pt.x >= keyPoint2[0].pt.x&&keyPoint2[1].pt.x >= keyPoint2[2].pt.x&&keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
				keyPoint2[1].class_id = 1;
				if (keyPoint2[0].pt.x >= keyPoint2[2].pt.x&&keyPoint2[0].pt.x >= keyPoint2[3].pt.x) {
					keyPoint2[0].class_id = 2;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 3;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 3;
						keyPoint2[2].class_id = 4;
					}
				}
				else if (keyPoint2[0].pt.x <= keyPoint2[2].pt.x&&keyPoint1[01].pt.x <= keyPoint2[3].pt.x) {
					keyPoint2[0].class_id = 4;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 2;
						keyPoint2[3].class_id = 3;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[2].class_id = 3;
					}
				}
				else {
					keyPoint2[0].class_id = 3;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 2;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 4;
					}
				}
			}
			else if (keyPoint2[2].pt.x >= keyPoint2[0].pt.x&&keyPoint2[2].pt.x >= keyPoint2[1].pt.x&&keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
				keyPoint2[2].class_id = 1;
				if (keyPoint2[0].pt.x >= keyPoint2[1].pt.x&&keyPoint2[0].pt.x >= keyPoint2[3].pt.x) {
					keyPoint2[0].class_id = 2;
					if (keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[1].class_id = 3;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 3;
						keyPoint2[1].class_id = 4;
					}
				}
				else if (keyPoint2[0].pt.x <= keyPoint2[1].pt.x&&keyPoint2[0].pt.x <= keyPoint2[3].pt.x) {
					keyPoint2[0].class_id = 4;
					if (keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[1].class_id = 2;
						keyPoint2[3].class_id = 3;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[1].class_id = 3;
					}
				}
				else {
					keyPoint2[0].class_id = 3;
					if (keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[1].class_id = 2;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[1].class_id = 4;
					}
				}
			}
			else if (keyPoint2[3].pt.x >= keyPoint2[0].pt.x&&keyPoint2[3].pt.x >= keyPoint2[1].pt.x&&keyPoint2[3].pt.x >= keyPoint2[2].pt.x) {
				keyPoint2[3].class_id = 1;
				if (keyPoint2[0].pt.x >= keyPoint2[1].pt.x&&keyPoint2[0].pt.x >= keyPoint2[2].pt.x) {
					keyPoint2[0].class_id = 2;
					if (keyPoint2[1].pt.x >= keyPoint2[2].pt.x) {
						keyPoint2[1].class_id = 3;
						keyPoint2[2].class_id = 4;
					}
					else {
						keyPoint2[2].class_id = 3;
						keyPoint2[1].class_id = 4;
					}
				}
				else if (keyPoint2[0].pt.x <= keyPoint2[1].pt.x&&keyPoint2[0].pt.x <= keyPoint2[2].pt.x) {
					keyPoint2[0].class_id = 4;
					if (keyPoint2[1].pt.x >= keyPoint2[2].pt.x) {
						keyPoint2[1].class_id = 2;
						keyPoint2[2].class_id = 3;
					}
					else {
						keyPoint2[2].class_id = 2;
						keyPoint2[1].class_id = 3;
					}
				}
				else {
					keyPoint2[0].class_id = 3;
					if (keyPoint2[1].pt.x >= keyPoint2[2].pt.x) {
						keyPoint2[1].class_id = 2;
						keyPoint2[2].class_id = 4;
					}
					else {
						keyPoint2[2].class_id = 2;
						keyPoint2[1].class_id = 4;
					}
				}
			}
			for (int k = 0; k < 4; k++) {
				for (int j = k + 1; j < 4; j++) {
					if (keyPoint2[k].pt.x == keyPoint2[j].pt.x) {
						int max = keyPoint2[k].class_id;
						if (keyPoint2[k].pt.y > keyPoint2[j].pt.y&&keyPoint2[k].class_id < keyPoint2[j].class_id) {
							keyPoint2[j].class_id = keyPoint2[j].class_id;
							keyPoint2[k].class_id = max;
						}
						else if (keyPoint2[k].pt.y < keyPoint2[j].pt.y&&keyPoint2[k].class_id < keyPoint2[j].class_id) {
							keyPoint2[k].class_id = keyPoint2[j].class_id;
							keyPoint2[j].class_id = max;
						}
						else if (keyPoint2[k].pt.y > keyPoint2[j].pt.y&&keyPoint2[k].class_id > keyPoint2[j].class_id) {
							keyPoint2[k].class_id = keyPoint2[j].class_id;
							keyPoint2[j].class_id = max;
						}
						else if (keyPoint2[k].pt.y < keyPoint2[j].pt.y&&keyPoint2[k].class_id > keyPoint2[j].class_id) {
							keyPoint2[j].class_id = keyPoint2[j].class_id;
							keyPoint2[k].class_id = max;
						}
					}
				}
			}
		}
		else {
			int p = (i - 22) / 2;
			GoodFeaturesToTrackDetector Detector(2);
			Detector.detect(roi1, keyPoint1);
			if (keyPoint1.size() != 2) {
				keyPoints1[0].pt.x = x1[p * 2 + 1] - e; keyPoint2[0].pt.y = y1[p * 2 + 1] - f;
				keyPoint1.push_back(keyPoints2[0]);
			}
			keyPoint1[0].pt.x = x1[6 * p] - a; keyPoint1[0].pt.y = y1[6 * p] - b;
			keyPoint1[1].pt.x = x1[6 * p + 1] - a; keyPoint1[1].pt.y = y1[6 * p + 1] - b;
			if (keyPoint1[0].pt.x < keyPoint1[1].pt.x) {
				keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
			}
			else if (keyPoint1[0].pt.x > keyPoint1[1].pt.x) {
				keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
			}
			else if (keyPoint1[0].pt.x == keyPoint1[1].pt.x) {
				if (keyPoint1[0].pt.y > keyPoint1[1].pt.y) {
					keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
				}
				else
					keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
			}

			Detector.detect(roi2, keyPoint2);
			if (keyPoint2.size() != 2) {
				keyPoints2[0].pt.x = x2[p * 2 + 1] - e; keyPoint2[0].pt.y = y2[p * 2 + 1] - f;
				keyPoint2.push_back(keyPoints2[0]);
			}
			keyPoint2[0].pt.x = x2[6 * p] - e; keyPoint2[0].pt.y = y2[6 * p] - f;
			keyPoint2[1].pt.x = x2[6 * p + 1] - e; keyPoint2[1].pt.y = y2[6 * p + 1] - f;
			if (keyPoint2[0].pt.x < keyPoint2[1].pt.x) {
				keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
			}
			else if (keyPoint2[0].pt.x > keyPoint2[1].pt.x) {
				keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
			}
			else if (keyPoint2[0].pt.x == keyPoint2[1].pt.x) {
				if (keyPoint2[0].pt.y > keyPoint2[1].pt.y) {
					keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
				}
				else
					keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
			}
		}
	}
	else if (i >= 44 && i < 77) {
		int p = i - 44;
		ifstream infile1, infile2;
		string filename;
		filename = "E:\\Biyesheji\\Detection\\Detection\\match corner\\";
		infile1.open(filename + "result13(1&3).txt", ios::in);
		infile2.open(filename + "result33(1&3).txt", ios::in);
		double x1[200], y1[200], x2[200], y2[200];
		while (!infile1.eof()) {
			for (int j = 0; j < 33; j++)
			{
				infile1 >> x1[j] >> y1[j];
			}
		}
		while (!infile2.eof()) {
			for (int j = 0; j < 33; j++)
			{
				infile2 >> x2[j] >> y2[j];
			}
		}
		GoodFeaturesToTrackDetector Detector(1);
		Detector.detect(roi1, keyPoint1);
		Detector.detect(roi2, keyPoint2);
		keyPoint1[0].pt.x = x1[p] - a; keyPoint1[0].pt.y = y1[p] - b;
		keyPoint2[0].pt.x = x2[p] - e; keyPoint2[0].pt.y = y2[p] - f;
		keyPoint1[0].class_id = i;
		keyPoint2[0].class_id = i;
	}
	else if (i >= 77 && i<85) {
		ifstream infile1, infile2;
		string filename;
		filename = "E:\\Biyesheji\\Detection\\Detection\\match corner\\";
		infile1.open(filename + "result14(1&3).txt", ios::in);
		infile2.open(filename + "result34(1&3).txt", ios::in);
		double x1[200], y1[200], x2[200], y2[200];
		while (!infile1.eof()) {
			for (int j = 0; j < 16; j++)
			{
				infile1 >> x1[j] >> y1[j];
			}
		}
		while (!infile2.eof()) {
			for (int j = 0; j < 16; j++)
			{
				infile2 >> x2[j] >> y2[j];
			}
		}
		int p = i - 77;
		GoodFeaturesToTrackDetector Detector(2);
		Detector.detect(roi1, keyPoint1);
		if (keyPoint1.size() != 2) {
			keyPoints1[0].pt.x = x1[p * 2 + 1] - e; keyPoint1[0].pt.y = y2[p * 2 + 1] - f;
			keyPoint1.push_back(keyPoints1[0]);
		}
		keyPoint1[0].pt.x = x1[p * 2] - a; keyPoint1[0].pt.y = y1[p * 2] - b;
		keyPoint1[1].pt.x = x1[p * 2 + 1] - a; keyPoint1[1].pt.y = y1[p * 2 + 1] - b;
		if (keyPoint1[0].pt.x < keyPoint1[1].pt.x) {
			keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
		}
		else if (keyPoint1[0].pt.x > keyPoint1[1].pt.x) {
			keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
		}
		else if (keyPoint1[0].pt.x == keyPoint1[1].pt.x) {
			if (keyPoint1[0].pt.y > keyPoint1[1].pt.y) {
				keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
			}
			else
				keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
		}
		Detector.detect(roi2, keyPoint2);
		if (keyPoint2.size() != 2) {
			keyPoints2[0].pt.x = x2[p * 2 + 1] - e; keyPoint2[0].pt.y = y2[p * 2 + 1] - f;
			keyPoint2.push_back(keyPoints2[0]);
		}
		keyPoint2[0].pt.x = x2[p * 2] - e; keyPoint2[0].pt.y = y2[p * 2] - f;
		keyPoint2[1].pt.x = x2[p * 2 + 1] - e; keyPoint2[1].pt.y = y2[p * 2 + 1] - f;
		if (keyPoint2[0].pt.x < keyPoint2[1].pt.x) {
			keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
		}
		else if (keyPoint2[0].pt.x > keyPoint2[1].pt.x) {
			keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
		}
		else if (keyPoint2[0].pt.x == keyPoint2[1].pt.x) {
			if (keyPoint2[0].pt.y > keyPoint2[1].pt.y) {
				keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
			}
			else
				keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
		}
	}
}

void MatchPoint1_4(int i, vector<int> letters, Mat& roi1, Mat& roi2, vector<KeyPoint>& keyPoint1, vector<KeyPoint>& keyPoint2)
{
	vector<KeyPoint> keyPoints1(200), keyPoints2(200);//循环前预定义

	int a = letters[0];
	int b = letters[1];
	int e = letters[2];
	int f = letters[3];

	if (i<23) {
		ifstream infile1, infile2;
		string filename;
		filename = "E:\\Biyesheji\\Detection\\Detection\\match corner\\";
		infile1.open(filename + "result11(1&4).txt", ios::in);
		infile2.open(filename + "result41(1&4).txt", ios::in);
		double x1[200], y1[200], x2[200], y2[200];
		while (!infile1.eof()) {
			for (int j = 0; j < 46; j++)
			{
				infile1 >> x1[j] >> y1[j];
			}
		}
		while (!infile2.eof()) {
			for (int j = 0; j < 46; j++)
			{
				infile2 >> x2[j] >> y2[j];
			}
		}
		GoodFeaturesToTrackDetector Detector(2);  //最大点数,值越大，点越多
		Detector.detect(roi1, keyPoint1);
		keyPoint1[0].pt.x = x1[2 * i] - a; keyPoint1[0].pt.y = y1[2 * i] - b;
		keyPoint1[1].pt.x = x1[2 * i + 1] - a; keyPoint1[1].pt.y = y1[2 * i + 1] - b;
		if (keyPoint1[0].pt.x < keyPoint1[1].pt.x) {
			keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
		}
		else if (keyPoint1[0].pt.x > keyPoint1[1].pt.x) {
			keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
		}
		else if (keyPoint1[0].pt.x == keyPoint1[1].pt.x) {
			if (keyPoint1[0].pt.y > keyPoint1[1].pt.y) {
				keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
			}
			else
				keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
		}
		Detector.detect(roi2, keyPoint2);
		keyPoint2[0].pt.x = x2[2 * i] - e; keyPoint2[0].pt.y = y2[2 * i] - f;
		keyPoint2[1].pt.x = x2[2 * i + 1] - e; keyPoint2[1].pt.y = y2[2 * i + 1] - f;
		if (keyPoint2[0].pt.x < keyPoint2[1].pt.x) {
			keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
		}
		else if (keyPoint2[0].pt.x > keyPoint2[1].pt.x) {
			keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
		}
		else if (keyPoint2[0].pt.x == keyPoint2[1].pt.x) {
			if (keyPoint2[0].pt.y > keyPoint2[1].pt.y) {
				keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
			}
			else
				keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
		}

	}

	else if (i >= 23 && i < 48) {
		ifstream infile1, infile2;
		string filename;
		filename = "E:\\Biyesheji\\Detection\\Detection\\match corner\\";
		infile1.open(filename + "result12(1&4).txt", ios::in);
		infile2.open(filename + "result42(1&4).txt", ios::in);
		double x1[200], y1[200], x2[200], y2[200];
		while (!infile1.eof()) {
			for (int j = 0; j < 73; j++)
			{
				infile1 >> x1[j] >> y1[j];
			}
		}
		while (!infile2.eof()) {
			for (int j = 0; j < 73; j++)
			{
				infile2 >> x2[j] >> y2[j];
			}
		}
		if (i == 23) {
			int p = i - 23;
			GoodFeaturesToTrackDetector Detector(1);
			Detector.detect(roi1, keyPoint1);
			Detector.detect(roi2, keyPoint2);
			keyPoint1[0].pt.x = x1[p] - a; keyPoint1[0].pt.y = y1[p] - b;
			keyPoint2[0].pt.x = x2[p] - e; keyPoint2[0].pt.y = y2[p] - f;
			keyPoint1[0].class_id = i;
			keyPoint2[0].class_id = i;
		}
		else if (i % 2 == 0) {
			GoodFeaturesToTrackDetector Detector(4);
			Detector.detect(roi1, keyPoint1);
			while (keyPoint1.size() != 4) {
				keyPoint1.push_back(keyPoints1[0]);
			}
			int p = (i - 23) / 2;
			keyPoint1[0].pt.x = x1[6 * p + 1] - a; keyPoint1[0].pt.y = y1[6 * p + 1] - b;
			keyPoint1[1].pt.x = x1[6 * p + 2] - a; keyPoint1[1].pt.y = y1[6 * p + 2] - b;
			keyPoint1[2].pt.x = x1[6 * p + 3] - a; keyPoint1[2].pt.y = y1[6 * p + 3] - b;
			keyPoint1[3].pt.x = x1[6 * p + 4] - a; keyPoint1[3].pt.y = y1[6 * p + 4] - b;
			if (keyPoint1[0].pt.x >= keyPoint1[1].pt.x&&keyPoint1[0].pt.x >= keyPoint1[1].pt.x&&keyPoint1[0].pt.x >= keyPoint1[3].pt.x) {
				keyPoint1[0].class_id = 1;
				if (keyPoint1[1].pt.x >= keyPoint1[2].pt.x&&keyPoint1[1].pt.x >= keyPoint1[3].pt.x) {
					keyPoint1[1].class_id = 2;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 3;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 3;
						keyPoint1[2].class_id = 4;
					}
				}
				else if (keyPoint1[1].pt.x <= keyPoint1[2].pt.x&&keyPoint1[1].pt.x <= keyPoint1[3].pt.x) {
					keyPoint1[1].class_id = 4;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 2;
						keyPoint1[3].class_id = 3;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 3;
					}
				}
				else {
					keyPoint1[1].class_id = 3;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 2;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 4;
					}
				}
			}
			else if (keyPoint1[1].pt.x >= keyPoint1[0].pt.x&&keyPoint1[1].pt.x >= keyPoint1[2].pt.x&&keyPoint1[1].pt.x >= keyPoint1[3].pt.x) {
				keyPoint1[1].class_id = 1;
				if (keyPoint1[0].pt.x >= keyPoint1[2].pt.x&&keyPoint1[0].pt.x >= keyPoint1[3].pt.x) {
					keyPoint1[0].class_id = 2;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 3;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 3;
						keyPoint1[2].class_id = 4;
					}
				}
				else if (keyPoint1[0].pt.x <= keyPoint1[2].pt.x&&keyPoint1[01].pt.x <= keyPoint1[3].pt.x) {
					keyPoint1[0].class_id = 4;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 2;
						keyPoint1[3].class_id = 3;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 3;
					}
				}
				else {
					keyPoint1[0].class_id = 3;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 2;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 4;
					}
				}
			}
			else if (keyPoint1[2].pt.x >= keyPoint1[0].pt.x&&keyPoint1[2].pt.x >= keyPoint1[1].pt.x&&keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
				keyPoint1[2].class_id = 1;
				if (keyPoint1[0].pt.x >= keyPoint1[1].pt.x&&keyPoint1[0].pt.x >= keyPoint1[3].pt.x) {
					keyPoint1[0].class_id = 2;
					if (keyPoint1[1].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[1].class_id = 3;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 3;
						keyPoint1[1].class_id = 4;
					}
				}
				else if (keyPoint1[0].pt.x <= keyPoint1[1].pt.x&&keyPoint1[0].pt.x <= keyPoint1[3].pt.x) {
					keyPoint1[0].class_id = 4;
					if (keyPoint1[1].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[1].class_id = 2;
						keyPoint1[3].class_id = 3;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[1].class_id = 3;
					}
				}
				else {
					keyPoint1[0].class_id = 3;
					if (keyPoint1[1].pt.x > keyPoint1[3].pt.x) {
						keyPoint1[1].class_id = 2;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[1].class_id = 4;
					}
				}
			}
			else if (keyPoint1[3].pt.x >= keyPoint1[0].pt.x&&keyPoint1[3].pt.x >= keyPoint1[1].pt.x&&keyPoint1[3].pt.x >= keyPoint1[2].pt.x) {
				keyPoint1[3].class_id = 1;
				if (keyPoint1[0].pt.x >= keyPoint1[1].pt.x&&keyPoint1[0].pt.x >= keyPoint1[2].pt.x) {
					keyPoint1[0].class_id = 2;
					if (keyPoint1[1].pt.x >= keyPoint1[2].pt.x) {
						keyPoint1[1].class_id = 3;
						keyPoint1[2].class_id = 4;
					}
					else {
						keyPoint1[2].class_id = 3;
						keyPoint1[1].class_id = 4;
					}
				}
				else if (keyPoint1[0].pt.x <= keyPoint1[1].pt.x&&keyPoint1[0].pt.x <= keyPoint1[2].pt.x) {
					keyPoint1[0].class_id = 4;
					if (keyPoint1[1].pt.x >= keyPoint1[2].pt.x) {
						keyPoint1[1].class_id = 2;
						keyPoint1[2].class_id = 3;
					}
					else {
						keyPoint1[2].class_id = 2;
						keyPoint1[1].class_id = 3;
					}
				}
				else {
					keyPoint1[0].class_id = 3;
					if (keyPoint1[1].pt.x >= keyPoint1[2].pt.x) {
						keyPoint1[1].class_id = 2;
						keyPoint1[2].class_id = 4;
					}
					else {
						keyPoint1[2].class_id = 2;
						keyPoint1[1].class_id = 4;
					}
				}
			}
			for (int k = 0; k < 4; k++) {
				for (int j = k + 1; j < 4; j++) {
					if (keyPoint1[k].pt.x == keyPoint1[j].pt.x) {
						int max = keyPoint1[k].class_id;
						if (keyPoint1[k].pt.y > keyPoint1[j].pt.y&&keyPoint2[k].class_id < keyPoint1[j].class_id) {
							keyPoint1[j].class_id = keyPoint1[j].class_id;
							keyPoint1[k].class_id = max;
						}
						else if (keyPoint1[k].pt.y < keyPoint1[j].pt.y&&keyPoint1[k].class_id < keyPoint1[j].class_id) {
							keyPoint1[k].class_id = keyPoint1[j].class_id;
							keyPoint1[j].class_id = max;
						}
						else if (keyPoint1[k].pt.y > keyPoint1[j].pt.y&&keyPoint1[k].class_id > keyPoint1[j].class_id) {
							keyPoint1[k].class_id = keyPoint1[j].class_id;
							keyPoint1[j].class_id = max;
						}
						else if (keyPoint1[k].pt.y < keyPoint1[j].pt.y&&keyPoint1[k].class_id > keyPoint1[j].class_id) {
							keyPoint1[j].class_id = keyPoint1[j].class_id;
							keyPoint1[k].class_id = max;
						}
					}
				}
			}
			Detector.detect(roi2, keyPoint2);
			while (keyPoint2.size() != 4) {
				keyPoint2.push_back(keyPoints2[0]);
			}
			keyPoint2[0].pt.x = x2[6 * p + 1] - e; keyPoint2[0].pt.y = y2[6 * p + 1] - f;
			keyPoint2[1].pt.x = x2[6 * p + 2] - e; keyPoint2[1].pt.y = y2[6 * p + 2] - f;
			keyPoint2[2].pt.x = x2[6 * p + 3] - e; keyPoint2[2].pt.y = y2[6 * p + 3] - f;
			keyPoint2[3].pt.x = x2[6 * p + 4] - e; keyPoint2[3].pt.y = y2[6 * p + 4] - f;
			if (keyPoint2[0].pt.x >= keyPoint2[1].pt.x&&keyPoint2[0].pt.x >= keyPoint2[2].pt.x&&keyPoint2[0].pt.x >= keyPoint2[3].pt.x) {
				keyPoint2[0].class_id = 1;
				if (keyPoint2[1].pt.x >= keyPoint2[2].pt.x&&keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
					keyPoint2[1].class_id = 2;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 3;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 3;
						keyPoint2[2].class_id = 4;
					}
				}
				else if (keyPoint2[1].pt.x <= keyPoint2[2].pt.x&&keyPoint2[1].pt.x <= keyPoint2[3].pt.x) {
					keyPoint2[1].class_id = 4;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 2;
						keyPoint2[3].class_id = 3;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[2].class_id = 3;
					}
				}
				else {
					keyPoint2[1].class_id = 3;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 2;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[2].class_id = 4;
					}
				}
			}
			else if (keyPoint2[1].pt.x >= keyPoint2[0].pt.x&&keyPoint2[1].pt.x >= keyPoint2[2].pt.x&&keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
				keyPoint2[1].class_id = 1;
				if (keyPoint2[0].pt.x >= keyPoint2[2].pt.x&&keyPoint2[0].pt.x >= keyPoint2[3].pt.x) {
					keyPoint2[0].class_id = 2;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 3;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 3;
						keyPoint2[2].class_id = 4;
					}
				}
				else if (keyPoint2[0].pt.x <= keyPoint2[2].pt.x&&keyPoint1[01].pt.x <= keyPoint2[3].pt.x) {
					keyPoint2[0].class_id = 4;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 2;
						keyPoint2[3].class_id = 3;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[2].class_id = 3;
					}
				}
				else {
					keyPoint2[0].class_id = 3;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 2;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 4;
					}
				}
			}
			else if (keyPoint2[2].pt.x >= keyPoint2[0].pt.x&&keyPoint2[2].pt.x >= keyPoint2[1].pt.x&&keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
				keyPoint2[2].class_id = 1;
				if (keyPoint2[0].pt.x >= keyPoint2[1].pt.x&&keyPoint2[0].pt.x >= keyPoint2[3].pt.x) {
					keyPoint2[0].class_id = 2;
					if (keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[1].class_id = 3;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 3;
						keyPoint2[1].class_id = 4;
					}
				}
				else if (keyPoint2[0].pt.x <= keyPoint2[1].pt.x&&keyPoint2[0].pt.x <= keyPoint2[3].pt.x) {
					keyPoint2[0].class_id = 4;
					if (keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[1].class_id = 2;
						keyPoint2[3].class_id = 3;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[1].class_id = 3;
					}
				}
				else {
					keyPoint2[0].class_id = 3;
					if (keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[1].class_id = 2;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[1].class_id = 4;
					}
				}
			}
			else if (keyPoint2[3].pt.x >= keyPoint2[0].pt.x&&keyPoint2[3].pt.x >= keyPoint2[1].pt.x&&keyPoint2[3].pt.x >= keyPoint2[2].pt.x) {
				keyPoint2[3].class_id = 1;
				if (keyPoint2[0].pt.x >= keyPoint2[1].pt.x&&keyPoint2[0].pt.x >= keyPoint2[2].pt.x) {
					keyPoint2[0].class_id = 2;
					if (keyPoint2[1].pt.x >= keyPoint2[2].pt.x) {
						keyPoint2[1].class_id = 3;
						keyPoint2[2].class_id = 4;
					}
					else {
						keyPoint2[2].class_id = 3;
						keyPoint2[1].class_id = 4;
					}
				}
				else if (keyPoint2[0].pt.x <= keyPoint2[1].pt.x&&keyPoint2[0].pt.x <= keyPoint2[2].pt.x) {
					keyPoint2[0].class_id = 4;
					if (keyPoint2[1].pt.x >= keyPoint2[2].pt.x) {
						keyPoint2[1].class_id = 2;
						keyPoint2[2].class_id = 3;
					}
					else {
						keyPoint2[2].class_id = 2;
						keyPoint2[1].class_id = 3;
					}
				}
				else {
					keyPoint2[0].class_id = 3;
					if (keyPoint2[1].pt.x >= keyPoint2[2].pt.x) {
						keyPoint2[1].class_id = 2;
						keyPoint2[2].class_id = 4;
					}
					else {
						keyPoint2[2].class_id = 2;
						keyPoint2[1].class_id = 4;
					}
				}
			}
			for (int k = 0; k < 4; k++) {
				for (int j = k + 1; j < 4; j++) {
					if (keyPoint2[k].pt.x == keyPoint2[j].pt.x) {
						int max = keyPoint2[k].class_id;
						if (keyPoint2[k].pt.y > keyPoint2[j].pt.y&&keyPoint2[k].class_id < keyPoint2[j].class_id) {
							keyPoint2[j].class_id = keyPoint2[j].class_id;
							keyPoint2[k].class_id = max;
						}
						else if (keyPoint2[k].pt.y < keyPoint2[j].pt.y&&keyPoint2[k].class_id < keyPoint2[j].class_id) {
							keyPoint2[k].class_id = keyPoint2[j].class_id;
							keyPoint2[j].class_id = max;
						}
						else if (keyPoint2[k].pt.y > keyPoint2[j].pt.y&&keyPoint2[k].class_id > keyPoint2[j].class_id) {
							keyPoint2[k].class_id = keyPoint2[j].class_id;
							keyPoint2[j].class_id = max;
						}
						else if (keyPoint2[k].pt.y < keyPoint2[j].pt.y&&keyPoint2[k].class_id > keyPoint2[j].class_id) {
							keyPoint2[j].class_id = keyPoint2[j].class_id;
							keyPoint2[k].class_id = max;
						}
					}
				}
			}
		}
		else {
			int p = (i - 23) / 2;
			GoodFeaturesToTrackDetector Detector(2);
			Detector.detect(roi1, keyPoint1);
			if (keyPoint1.size() != 2) {
				keyPoints1[0].pt.x = x1[p * 2 + 1] - e; keyPoint2[0].pt.y = y1[p * 2 + 1] - f;
				keyPoint1.push_back(keyPoints2[0]);
			}
			keyPoint1[0].pt.x = x1[6 * p + 5] - a; keyPoint1[0].pt.y = y1[6 * p + 5] - b;
			keyPoint1[1].pt.x = x1[6 * p + 6] - a; keyPoint1[1].pt.y = y1[6 * p + 6] - b;
			if (keyPoint1[0].pt.x < keyPoint1[1].pt.x) {
				keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
			}
			else if (keyPoint1[0].pt.x > keyPoint1[1].pt.x) {
				keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
			}
			else if (keyPoint1[0].pt.x == keyPoint1[1].pt.x) {
				if (keyPoint1[0].pt.y > keyPoint1[1].pt.y) {
					keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
				}
				else
					keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
			}

			Detector.detect(roi2, keyPoint2);
			if (keyPoint2.size() != 2) {
				keyPoints2[0].pt.x = x2[p * 2 + 1] - e; keyPoint2[0].pt.y = y2[p * 2 + 1] - f;
				keyPoint2.push_back(keyPoints2[0]);
			}
			keyPoint2[0].pt.x = x2[6 * p + 5] - e; keyPoint2[0].pt.y = y2[6 * p + 5] - f;
			keyPoint2[1].pt.x = x2[6 * p + 6] - e; keyPoint2[1].pt.y = y2[6 * p + 6] - f;
			if (keyPoint2[0].pt.x < keyPoint2[1].pt.x) {
				keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
			}
			else if (keyPoint2[0].pt.x > keyPoint2[1].pt.x) {
				keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
			}
			else if (keyPoint2[0].pt.x == keyPoint2[1].pt.x) {
				if (keyPoint2[0].pt.y > keyPoint2[1].pt.y) {
					keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
				}
				else
					keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
			}
		}
	}
	else if (i >= 48 && i < 83) {
		int p = i - 48;
		ifstream infile1, infile2;
		string filename;
		filename = "E:\\Biyesheji\\Detection\\Detection\\match corner\\";
		infile1.open(filename + "result13(1&4).txt", ios::in);
		infile2.open(filename + "result43(1&4).txt", ios::in);
		double x1[200], y1[200], x2[200], y2[200];
		while (!infile1.eof()) {
			for (int j = 0; j < 35; j++)
			{
				infile1 >> x1[j] >> y1[j];
			}
		}
		while (!infile2.eof()) {
			for (int j = 0; j < 35; j++)
			{
				infile2 >> x2[j] >> y2[j];
			}
		}
		GoodFeaturesToTrackDetector Detector(1);
		Detector.detect(roi1, keyPoint1);
		Detector.detect(roi2, keyPoint2);
		keyPoint1[0].pt.x = x1[p] - a; keyPoint1[0].pt.y = y1[p] - b;
		keyPoint2[0].pt.x = x2[p] - e; keyPoint2[0].pt.y = y2[p] - f;
		keyPoint1[0].class_id = i;
		keyPoint2[0].class_id = i;
	}

	else if (i >= 83 && i<93) {
		ifstream infile1, infile2;
		string filename;
		filename = "E:\\Biyesheji\\Detection\\Detection\\match corner\\";
		infile1.open(filename + "result14(1&4).txt", ios::in);
		infile2.open(filename + "result44(1&4).txt", ios::in);
		double x1[200], y1[200], x2[200], y2[200];
		while (!infile1.eof()) {
			for (int j = 0; j < 20; j++)
			{
				infile1 >> x1[j] >> y1[j];
			}
		}
		while (!infile2.eof()) {
			for (int j = 0; j < 20; j++)
			{
				infile2 >> x2[j] >> y2[j];
			}
		}
		int p = i - 83;
		GoodFeaturesToTrackDetector Detector(2);
		Detector.detect(roi1, keyPoint1);
		if (keyPoint1.size() != 2) {
			keyPoints1[0].pt.x = x1[p * 2 + 1] - e; keyPoint1[0].pt.y = y2[p * 2 + 1] - f;
			keyPoint1.push_back(keyPoints1[0]);
		}
		keyPoint1[0].pt.x = x1[p * 2] - a; keyPoint1[0].pt.y = y1[p * 2] - b;
		keyPoint1[1].pt.x = x1[p * 2 + 1] - a; keyPoint1[1].pt.y = y1[p * 2 + 1] - b;
		if (keyPoint1[0].pt.x < keyPoint1[1].pt.x) {
			keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
		}
		else if (keyPoint1[0].pt.x > keyPoint1[1].pt.x) {
			keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
		}
		else if (keyPoint1[0].pt.x == keyPoint1[1].pt.x) {
			if (keyPoint1[0].pt.y > keyPoint1[1].pt.y) {
				keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
			}
			else
				keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
		}
		Detector.detect(roi2, keyPoint2);
		if (keyPoint2.size() != 2) {
			keyPoints2[0].pt.x = x2[p * 2 + 1] - e; keyPoint2[0].pt.y = y2[p * 2 + 1] - f;
			keyPoint2.push_back(keyPoints2[0]);
		}
		keyPoint2[0].pt.x = x2[p * 2] - e; keyPoint2[0].pt.y = y2[p * 2] - f;
		keyPoint2[1].pt.x = x2[p * 2 + 1] - e; keyPoint2[1].pt.y = y2[p * 2 + 1] - f;
		if (keyPoint2[0].pt.x < keyPoint2[1].pt.x) {
			keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
		}
		else if (keyPoint2[0].pt.x > keyPoint2[1].pt.x) {
			keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
		}
		else if (keyPoint2[0].pt.x == keyPoint2[1].pt.x) {
			if (keyPoint2[0].pt.y > keyPoint2[1].pt.y) {
				keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
			}
			else
				keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
		}
	}
}

void MatchPoint2_3(int i, vector<int> letters, Mat& roi1, Mat& roi2, vector<KeyPoint>& keyPoint1, vector<KeyPoint>& keyPoint2)
{
	vector<KeyPoint> keyPoints1(200), keyPoints2(200);//循环前预定义

	int a = letters[0];
	int b = letters[1];
	int e = letters[2];
	int f = letters[3];

	if (i<23) {
		ifstream infile1, infile2;
		string filename;
		filename = "E:\\Biyesheji\\Detection\\Detection\\match corner\\";
		infile1.open(filename + "result21(2&3).txt", ios::in);
		infile2.open(filename + "result31(2&3).txt", ios::in);
		double x1[200], y1[200], x2[200], y2[200];
		while (!infile1.eof()) {
			for (int j = 0; j < 46; j++)
			{
				infile1 >> x1[j] >> y1[j];
			}
		}
		while (!infile2.eof()) {
			for (int j = 0; j < 46; j++)
			{
				infile2 >> x2[j] >> y2[j];
			}
		}
		GoodFeaturesToTrackDetector Detector(2);  //最大点数,值越大，点越多
		Detector.detect(roi1, keyPoint1);
		while (keyPoint1.size() != 2) {
			keyPoint1.push_back(keyPoints1[0]);
		}
		keyPoint1[0].pt.x = x1[2 * i] - a; keyPoint1[0].pt.y = y1[2 * i] - b;
		keyPoint1[1].pt.x = x1[2 * i + 1] - a; keyPoint1[1].pt.y = y1[2 * i + 1] - b;
		if (keyPoint1[0].pt.x < keyPoint1[1].pt.x) {
			keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
		}
		else if (keyPoint1[0].pt.x > keyPoint1[1].pt.x) {
			keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
		}
		else if (keyPoint1[0].pt.x == keyPoint1[1].pt.x) {
			if (keyPoint1[0].pt.y > keyPoint1[1].pt.y) {
				keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
			}
			else
				keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
		}
		Detector.detect(roi2, keyPoint2);
		while (keyPoint2.size() != 2) {
			keyPoint2.push_back(keyPoints2[0]);
		}
		keyPoint2[0].pt.x = x2[2 * i] - e; keyPoint2[0].pt.y = y2[2 * i] - f;
		keyPoint2[1].pt.x = x2[2 * i + 1] - e; keyPoint2[1].pt.y = y2[2 * i + 1] - f;
		if (keyPoint2[0].pt.x < keyPoint2[1].pt.x) {
			keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
		}
		else if (keyPoint2[0].pt.x > keyPoint2[1].pt.x) {
			keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
		}
		else if (keyPoint2[0].pt.x == keyPoint2[1].pt.x) {
			if (keyPoint2[0].pt.y > keyPoint2[1].pt.y) {
				keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
			}
			else
				keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
		}

	}

	else if (i >= 23 && i < 48) {
		ifstream infile1, infile2;
		string filename;
		filename = "E:\\Biyesheji\\Detection\\Detection\\match corner\\";
		infile1.open(filename + "result22(2&3).txt", ios::in);
		infile2.open(filename + "result32(2&3).txt", ios::in);
		double x1[200], y1[200], x2[200], y2[200];
		while (!infile1.eof()) {
			for (int j = 0; j < 72; j++)
			{
				infile1 >> x1[j] >> y1[j];
			}
		}
		while (!infile2.eof()) {
			for (int j = 0; j < 72; j++)
			{
				infile2 >> x2[j] >> y2[j];
			}
		}
		if (i == 46) {
			int p = (i - 23) / 2;
			GoodFeaturesToTrackDetector Detector(3);
			Detector.detect(roi1, keyPoint1);
			while (keyPoint1.size() != 3) {
				keyPoint1.push_back(keyPoints1[0]);
			}
			keyPoint1[0].pt.x = x1[6 * p + 2] - a; keyPoint1[0].pt.y = y1[6 * p + 2] - b;
			keyPoint1[1].pt.x = x1[6 * p + 3] - a; keyPoint1[1].pt.y = y1[6 * p + 3] - b;
			keyPoint1[2].pt.x = x1[6 * p + 4] - a; keyPoint1[2].pt.y = y1[6 * p + 4] - b;
			if (keyPoint1[0].pt.x >= keyPoint1[1].pt.x&&keyPoint1[0].pt.x >= keyPoint1[2].pt.x) {
				keyPoint1[0].class_id = 1;
				if (keyPoint1[1].pt.x > keyPoint1[2].pt.x) {
					keyPoint1[1].class_id = 2;
					keyPoint1[2].class_id = 3;
				}
				else if (keyPoint1[1].pt.x < keyPoint1[2].pt.x) {
					keyPoint1[2].class_id = 2;
					keyPoint1[1].class_id = 3;
				}
				else {
					if (keyPoint1[1].pt.y > keyPoint1[2].pt.y) {
						keyPoint1[1].class_id = 2;
						keyPoint1[2].class_id = 3;
					}
					else {
						keyPoint1[2].class_id = 2;
						keyPoint1[1].class_id = 3;
					}
				}
			}
			else if (keyPoint1[0].pt.x <= keyPoint1[1].pt.x&&keyPoint1[0].pt.x <= keyPoint1[2].pt.x) {
				keyPoint1[0].class_id = 3;
				if (keyPoint1[1].pt.x > keyPoint1[2].pt.x) {
					keyPoint1[1].class_id = 1;
					keyPoint1[2].class_id = 2;
				}
				else if (keyPoint1[1].pt.x < keyPoint1[2].pt.x) {
					keyPoint1[2].class_id = 1;
					keyPoint1[1].class_id = 2;
				}
				else {
					if (keyPoint1[1].pt.y > keyPoint1[2].pt.y) {
						keyPoint1[1].class_id = 1;
						keyPoint1[2].class_id = 2;
					}
					else {
						keyPoint1[2].class_id = 1;
						keyPoint1[1].class_id = 2;
					}
				}
			}
			else {
				keyPoint1[0].class_id = 2;
				if (keyPoint1[1].pt.x > keyPoint1[2].pt.x) {
					keyPoint1[1].class_id = 1;
					keyPoint1[2].class_id = 3;
				}
				else if (keyPoint1[1].pt.x < keyPoint1[2].pt.x) {
					keyPoint1[2].class_id = 1;
					keyPoint1[1].class_id = 3;
				}
				else {
					if (keyPoint1[1].pt.y > keyPoint1[2].pt.y) {
						keyPoint1[1].class_id = 1;
						keyPoint1[2].class_id = 3;
					}
					else {
						keyPoint1[2].class_id = 1;
						keyPoint1[1].class_id = 3;
					}
				}
			}
			Detector.detect(roi2, keyPoint2);
			while (keyPoint2.size() != 3) {
				keyPoint2.push_back(keyPoints2[0]);
			}
			keyPoint2[0].pt.x = x2[6 * p + 2] - e; keyPoint2[0].pt.y = y2[6 * p + 2] - f;
			keyPoint2[1].pt.x = x2[6 * p + 3] - e; keyPoint2[1].pt.y = y2[6 * p + 3] - f;
			keyPoint2[2].pt.x = x2[6 * p + 4] - e; keyPoint2[2].pt.y = y2[6 * p + 4] - f;
			if (keyPoint2[0].pt.x >= keyPoint2[1].pt.x&&keyPoint2[0].pt.x >= keyPoint2[2].pt.x) {
				keyPoint2[0].class_id = 1;
				if (keyPoint2[1].pt.x > keyPoint2[2].pt.x) {
					keyPoint2[1].class_id = 2;
					keyPoint2[2].class_id = 3;
				}
				else if (keyPoint2[1].pt.x < keyPoint2[2].pt.x) {
					keyPoint2[2].class_id = 2;
					keyPoint2[1].class_id = 3;
				}
				else {
					if (keyPoint2[1].pt.y > keyPoint2[2].pt.y) {
						keyPoint2[1].class_id = 2;
						keyPoint2[2].class_id = 3;
					}
					else {
						keyPoint2[2].class_id = 2;
						keyPoint2[1].class_id = 3;
					}
				}
			}
			else if (keyPoint2[0].pt.x <= keyPoint2[1].pt.x&&keyPoint2[0].pt.x <= keyPoint2[2].pt.x) {
				keyPoint2[0].class_id = 3;
				if (keyPoint2[1].pt.x > keyPoint2[2].pt.x) {
					keyPoint2[1].class_id = 1;
					keyPoint2[2].class_id = 2;
				}
				else if (keyPoint2[1].pt.x < keyPoint2[2].pt.x) {
					keyPoint2[2].class_id = 1;
					keyPoint2[1].class_id = 2;
				}
				else {
					if (keyPoint2[1].pt.y > keyPoint2[2].pt.y) {
						keyPoint2[1].class_id = 1;
						keyPoint2[2].class_id = 2;
					}
					else {
						keyPoint2[2].class_id = 1;
						keyPoint2[1].class_id = 2;
					}
				}
			}
			else {
				keyPoint2[0].class_id = 2;
				if (keyPoint2[1].pt.x > keyPoint2[2].pt.x) {
					keyPoint2[1].class_id = 1;
					keyPoint2[2].class_id = 3;
				}
				else if (keyPoint2[1].pt.x < keyPoint2[2].pt.x) {
					keyPoint2[2].class_id = 1;
					keyPoint2[1].class_id = 3;
				}
				else {
					if (keyPoint2[1].pt.y > keyPoint2[2].pt.y) {
						keyPoint2[1].class_id = 1;
						keyPoint2[2].class_id = 3;
					}
					else {
						keyPoint2[2].class_id = 1;
						keyPoint2[1].class_id = 3;
					}
				}
			}
		}
		else if (i == 47) {
			GoodFeaturesToTrackDetector Detector(1);
			Detector.detect(roi1, keyPoint1);
			Detector.detect(roi2, keyPoint2);
			keyPoint1[0].pt.x = x1[71] - a; keyPoint1[0].pt.y = y1[71] - b;
			keyPoint2[0].pt.x = x2[71] - e; keyPoint2[0].pt.y = y2[71] - f;
			keyPoint1[0].class_id = i;
			keyPoint2[0].class_id = i;
		}
		else if (i % 2 == 0) {
			GoodFeaturesToTrackDetector Detector(4);
			Detector.detect(roi1, keyPoint1);
			while (keyPoint1.size() != 4) {
				keyPoint1.push_back(keyPoints1[0]);
			}
			int p = (i - 23) / 2;
			keyPoint1[0].pt.x = x1[6 * p + 2] - a; keyPoint1[0].pt.y = y1[6 * p + 2] - b;
			keyPoint1[1].pt.x = x1[6 * p + 3] - a; keyPoint1[1].pt.y = y1[6 * p + 3] - b;
			keyPoint1[2].pt.x = x1[6 * p + 4] - a; keyPoint1[2].pt.y = y1[6 * p + 4] - b;
			keyPoint1[3].pt.x = x1[6 * p + 5] - a; keyPoint1[3].pt.y = y1[6 * p + 5] - b;
			if (keyPoint1[0].pt.x >= keyPoint1[1].pt.x&&keyPoint1[0].pt.x >= keyPoint1[1].pt.x&&keyPoint1[0].pt.x >= keyPoint1[3].pt.x) {
				keyPoint1[0].class_id = 1;
				if (keyPoint1[1].pt.x >= keyPoint1[2].pt.x&&keyPoint1[1].pt.x >= keyPoint1[3].pt.x) {
					keyPoint1[1].class_id = 2;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 3;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 3;
						keyPoint1[2].class_id = 4;
					}
				}
				else if (keyPoint1[1].pt.x <= keyPoint1[2].pt.x&&keyPoint1[1].pt.x <= keyPoint1[3].pt.x) {
					keyPoint1[1].class_id = 4;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 2;
						keyPoint1[3].class_id = 3;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 3;
					}
				}
				else {
					keyPoint1[1].class_id = 3;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 2;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 4;
					}
				}
			}
			else if (keyPoint1[1].pt.x >= keyPoint1[0].pt.x&&keyPoint1[1].pt.x >= keyPoint1[2].pt.x&&keyPoint1[1].pt.x >= keyPoint1[3].pt.x) {
				keyPoint1[1].class_id = 1;
				if (keyPoint1[0].pt.x >= keyPoint1[2].pt.x&&keyPoint1[0].pt.x >= keyPoint1[3].pt.x) {
					keyPoint1[0].class_id = 2;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 3;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 3;
						keyPoint1[2].class_id = 4;
					}
				}
				else if (keyPoint1[0].pt.x <= keyPoint1[2].pt.x&&keyPoint1[01].pt.x <= keyPoint1[3].pt.x) {
					keyPoint1[0].class_id = 4;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 2;
						keyPoint1[3].class_id = 3;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 3;
					}
				}
				else {
					keyPoint1[0].class_id = 3;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 2;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 4;
					}
				}
			}
			else if (keyPoint1[2].pt.x >= keyPoint1[0].pt.x&&keyPoint1[2].pt.x >= keyPoint1[1].pt.x&&keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
				keyPoint1[2].class_id = 1;
				if (keyPoint1[0].pt.x >= keyPoint1[1].pt.x&&keyPoint1[0].pt.x >= keyPoint1[3].pt.x) {
					keyPoint1[0].class_id = 2;
					if (keyPoint1[1].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[1].class_id = 3;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 3;
						keyPoint1[1].class_id = 4;
					}
				}
				else if (keyPoint1[0].pt.x <= keyPoint1[1].pt.x&&keyPoint1[0].pt.x <= keyPoint1[3].pt.x) {
					keyPoint1[0].class_id = 4;
					if (keyPoint1[1].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[1].class_id = 2;
						keyPoint1[3].class_id = 3;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[1].class_id = 3;
					}
				}
				else {
					keyPoint1[0].class_id = 3;
					if (keyPoint1[1].pt.x > keyPoint1[3].pt.x) {
						keyPoint1[1].class_id = 2;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[1].class_id = 4;
					}
				}
			}
			else if (keyPoint1[3].pt.x >= keyPoint1[0].pt.x&&keyPoint1[3].pt.x >= keyPoint1[1].pt.x&&keyPoint1[3].pt.x >= keyPoint1[2].pt.x) {
				keyPoint1[3].class_id = 1;
				if (keyPoint1[0].pt.x >= keyPoint1[1].pt.x&&keyPoint1[0].pt.x >= keyPoint1[2].pt.x) {
					keyPoint1[0].class_id = 2;
					if (keyPoint1[1].pt.x >= keyPoint1[2].pt.x) {
						keyPoint1[1].class_id = 3;
						keyPoint1[2].class_id = 4;
					}
					else {
						keyPoint1[2].class_id = 3;
						keyPoint1[1].class_id = 4;
					}
				}
				else if (keyPoint1[0].pt.x <= keyPoint1[1].pt.x&&keyPoint1[0].pt.x <= keyPoint1[2].pt.x) {
					keyPoint1[0].class_id = 4;
					if (keyPoint1[1].pt.x >= keyPoint1[2].pt.x) {
						keyPoint1[1].class_id = 2;
						keyPoint1[2].class_id = 3;
					}
					else {
						keyPoint1[2].class_id = 2;
						keyPoint1[1].class_id = 3;
					}
				}
				else {
					keyPoint1[0].class_id = 3;
					if (keyPoint1[1].pt.x >= keyPoint1[2].pt.x) {
						keyPoint1[1].class_id = 2;
						keyPoint1[2].class_id = 4;
					}
					else {
						keyPoint1[2].class_id = 2;
						keyPoint1[1].class_id = 4;
					}
				}
			}
			for (int k = 0; k < 4; k++) {
				for (int j = k + 1; j < 4; j++) {
					if (keyPoint1[k].pt.x == keyPoint1[j].pt.x) {
						int max = keyPoint1[k].class_id;
						if (keyPoint1[k].pt.y > keyPoint1[j].pt.y&&keyPoint2[k].class_id < keyPoint1[j].class_id) {
							keyPoint1[j].class_id = keyPoint1[j].class_id;
							keyPoint1[k].class_id = max;
						}
						else if (keyPoint1[k].pt.y < keyPoint1[j].pt.y&&keyPoint1[k].class_id < keyPoint1[j].class_id) {
							keyPoint1[k].class_id = keyPoint1[j].class_id;
							keyPoint1[j].class_id = max;
						}
						else if (keyPoint1[k].pt.y > keyPoint1[j].pt.y&&keyPoint1[k].class_id > keyPoint1[j].class_id) {
							keyPoint1[k].class_id = keyPoint1[j].class_id;
							keyPoint1[j].class_id = max;
						}
						else if (keyPoint1[k].pt.y < keyPoint1[j].pt.y&&keyPoint1[k].class_id > keyPoint1[j].class_id) {
							keyPoint1[j].class_id = keyPoint1[j].class_id;
							keyPoint1[k].class_id = max;
						}
					}
				}
			}
			Detector.detect(roi2, keyPoint2);
			while (keyPoint2.size() != 4) {
				keyPoint2.push_back(keyPoints2[0]);
			}
			keyPoint2[0].pt.x = x2[6 * p + 2] - e; keyPoint2[0].pt.y = y2[6 * p + 2] - f;
			keyPoint2[1].pt.x = x2[6 * p + 3] - e; keyPoint2[1].pt.y = y2[6 * p + 3] - f;
			keyPoint2[2].pt.x = x2[6 * p + 4] - e; keyPoint2[2].pt.y = y2[6 * p + 4] - f;
			keyPoint2[3].pt.x = x2[6 * p + 5] - e; keyPoint2[3].pt.y = y2[6 * p + 5] - f;
			if (keyPoint2[0].pt.x >= keyPoint2[1].pt.x&&keyPoint2[0].pt.x >= keyPoint2[2].pt.x&&keyPoint2[0].pt.x >= keyPoint2[3].pt.x) {
				keyPoint2[0].class_id = 1;
				if (keyPoint2[1].pt.x >= keyPoint2[2].pt.x&&keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
					keyPoint2[1].class_id = 2;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 3;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 3;
						keyPoint2[2].class_id = 4;
					}
				}
				else if (keyPoint2[1].pt.x <= keyPoint2[2].pt.x&&keyPoint2[1].pt.x <= keyPoint2[3].pt.x) {
					keyPoint2[1].class_id = 4;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 2;
						keyPoint2[3].class_id = 3;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[2].class_id = 3;
					}
				}
				else {
					keyPoint2[1].class_id = 3;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 2;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[2].class_id = 4;
					}
				}
			}
			else if (keyPoint2[1].pt.x >= keyPoint2[0].pt.x&&keyPoint2[1].pt.x >= keyPoint2[2].pt.x&&keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
				keyPoint2[1].class_id = 1;
				if (keyPoint2[0].pt.x >= keyPoint2[2].pt.x&&keyPoint2[0].pt.x >= keyPoint2[3].pt.x) {
					keyPoint2[0].class_id = 2;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 3;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 3;
						keyPoint2[2].class_id = 4;
					}
				}
				else if (keyPoint2[0].pt.x <= keyPoint2[2].pt.x&&keyPoint1[01].pt.x <= keyPoint2[3].pt.x) {
					keyPoint2[0].class_id = 4;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 2;
						keyPoint2[3].class_id = 3;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[2].class_id = 3;
					}
				}
				else {
					keyPoint2[0].class_id = 3;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 2;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 4;
					}
				}
			}
			else if (keyPoint2[2].pt.x >= keyPoint2[0].pt.x&&keyPoint2[2].pt.x >= keyPoint2[1].pt.x&&keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
				keyPoint2[2].class_id = 1;
				if (keyPoint2[0].pt.x >= keyPoint2[1].pt.x&&keyPoint2[0].pt.x >= keyPoint2[3].pt.x) {
					keyPoint2[0].class_id = 2;
					if (keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[1].class_id = 3;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 3;
						keyPoint2[1].class_id = 4;
					}
				}
				else if (keyPoint2[0].pt.x <= keyPoint2[1].pt.x&&keyPoint2[0].pt.x <= keyPoint2[3].pt.x) {
					keyPoint2[0].class_id = 4;
					if (keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[1].class_id = 2;
						keyPoint2[3].class_id = 3;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[1].class_id = 3;
					}
				}
				else {
					keyPoint2[0].class_id = 3;
					if (keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[1].class_id = 2;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[1].class_id = 4;
					}
				}
			}
			else if (keyPoint2[3].pt.x >= keyPoint2[0].pt.x&&keyPoint2[3].pt.x >= keyPoint2[1].pt.x&&keyPoint2[3].pt.x >= keyPoint2[2].pt.x) {
				keyPoint2[3].class_id = 1;
				if (keyPoint2[0].pt.x >= keyPoint2[1].pt.x&&keyPoint2[0].pt.x >= keyPoint2[2].pt.x) {
					keyPoint2[0].class_id = 2;
					if (keyPoint2[1].pt.x >= keyPoint2[2].pt.x) {
						keyPoint2[1].class_id = 3;
						keyPoint2[2].class_id = 4;
					}
					else {
						keyPoint2[2].class_id = 3;
						keyPoint2[1].class_id = 4;
					}
				}
				else if (keyPoint2[0].pt.x <= keyPoint2[1].pt.x&&keyPoint2[0].pt.x <= keyPoint2[2].pt.x) {
					keyPoint2[0].class_id = 4;
					if (keyPoint2[1].pt.x >= keyPoint2[2].pt.x) {
						keyPoint2[1].class_id = 2;
						keyPoint2[2].class_id = 3;
					}
					else {
						keyPoint2[2].class_id = 2;
						keyPoint2[1].class_id = 3;
					}
				}
				else {
					keyPoint2[0].class_id = 3;
					if (keyPoint2[1].pt.x >= keyPoint2[2].pt.x) {
						keyPoint2[1].class_id = 2;
						keyPoint2[2].class_id = 4;
					}
					else {
						keyPoint2[2].class_id = 2;
						keyPoint2[1].class_id = 4;
					}
				}
			}
			for (int k = 0; k < 4; k++) {
				for (int j = k + 1; j < 4; j++) {
					if (keyPoint2[k].pt.x == keyPoint2[j].pt.x) {
						int max = keyPoint2[k].class_id;
						if (keyPoint2[k].pt.y > keyPoint2[j].pt.y&&keyPoint2[k].class_id < keyPoint2[j].class_id) {
							keyPoint2[j].class_id = keyPoint2[j].class_id;
							keyPoint2[k].class_id = max;
						}
						else if (keyPoint2[k].pt.y < keyPoint2[j].pt.y&&keyPoint2[k].class_id < keyPoint2[j].class_id) {
							keyPoint2[k].class_id = keyPoint2[j].class_id;
							keyPoint2[j].class_id = max;
						}
						else if (keyPoint2[k].pt.y > keyPoint2[j].pt.y&&keyPoint2[k].class_id > keyPoint2[j].class_id) {
							keyPoint2[k].class_id = keyPoint2[j].class_id;
							keyPoint2[j].class_id = max;
						}
						else if (keyPoint2[k].pt.y < keyPoint2[j].pt.y&&keyPoint2[k].class_id > keyPoint2[j].class_id) {
							keyPoint2[j].class_id = keyPoint2[j].class_id;
							keyPoint2[k].class_id = max;
						}
					}
				}
			}
		}
		else if (i % 2 != 0) {
			int p = (i - 23) / 2;
			GoodFeaturesToTrackDetector Detector(2);
			Detector.detect(roi1, keyPoint1);
			if (keyPoint1.size() != 2) {
				keyPoints1[0].pt.x = x1[p * 2 + 1] - e; keyPoint2[0].pt.y = y1[p * 2 + 1] - f;
				keyPoint1.push_back(keyPoints2[0]);
			}
			keyPoint1[0].pt.x = x1[6 * p] - a; keyPoint1[0].pt.y = y1[6 * p] - b;
			keyPoint1[1].pt.x = x1[6 * p + 1] - a; keyPoint1[1].pt.y = y1[6 * p + 1] - b;
			if (keyPoint1[0].pt.x < keyPoint1[1].pt.x) {
				keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
			}
			else if (keyPoint1[0].pt.x > keyPoint1[1].pt.x) {
				keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
			}
			else if (keyPoint1[0].pt.x == keyPoint1[1].pt.x) {
				if (keyPoint1[0].pt.y > keyPoint1[1].pt.y) {
					keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
				}
				else
					keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
			}

			Detector.detect(roi2, keyPoint2);
			if (keyPoint2.size() != 2) {
				keyPoints2[0].pt.x = x2[p * 2 + 1] - e; keyPoint2[0].pt.y = y2[p * 2 + 1] - f;
				keyPoint2.push_back(keyPoints2[0]);
			}
			keyPoint2[0].pt.x = x2[6 * p] - e; keyPoint2[0].pt.y = y2[6 * p] - f;
			keyPoint2[1].pt.x = x2[6 * p + 1] - e; keyPoint2[1].pt.y = y2[6 * p + 1] - f;
			if (keyPoint2[0].pt.x < keyPoint2[1].pt.x) {
				keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
			}
			else if (keyPoint2[0].pt.x > keyPoint2[1].pt.x) {
				keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
			}
			else if (keyPoint2[0].pt.x == keyPoint2[1].pt.x) {
				if (keyPoint2[0].pt.y > keyPoint2[1].pt.y) {
					keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
				}
				else
					keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
			}
		}
	}

	else if (i >= 48 && i < 83) {
		int p = i - 48;
		ifstream infile1, infile2;
		string filename;
		filename = "E:\\Biyesheji\\Detection\\Detection\\match corner\\";
		infile1.open(filename + "result23(2&3).txt", ios::in);
		infile2.open(filename + "result33(2&3).txt", ios::in);
		double x1[200], y1[200], x2[200], y2[200];
		while (!infile1.eof()) {
			for (int j = 0; j < 35; j++)
			{
				infile1 >> x1[j] >> y1[j];
			}
		}
		while (!infile2.eof()) {
			for (int j = 0; j < 35; j++)
			{
				infile2 >> x2[j] >> y2[j];
			}
		}
		GoodFeaturesToTrackDetector Detector(1);
		Detector.detect(roi1, keyPoint1);
		Detector.detect(roi2, keyPoint2);
		keyPoint1[0].pt.x = x1[p] - a; keyPoint1[0].pt.y = y1[p] - b;
		keyPoint2[0].pt.x = x2[p] - e; keyPoint2[0].pt.y = y2[p] - f;
		keyPoint1[0].class_id = i;
		keyPoint2[0].class_id = i;
	}

	else if (i >= 83 && i<93) {
		ifstream infile1, infile2;
		string filename;
		filename = "E:\\Biyesheji\\Detection\\Detection\\match corner\\";
		infile1.open(filename + "result24(2&3).txt", ios::in);
		infile2.open(filename + "result34(2&3).txt", ios::in);
		double x1[200], y1[200], x2[200], y2[200];
		while (!infile1.eof()) {
			for (int j = 0; j < 20; j++)
			{
				infile1 >> x1[j] >> y1[j];
			}
		}
		while (!infile2.eof()) {
			for (int j = 0; j < 20; j++)
			{
				infile2 >> x2[j] >> y2[j];
			}
		}
		int p = i - 83;
		GoodFeaturesToTrackDetector Detector(2);
		Detector.detect(roi1, keyPoint1);
		if (keyPoint1.size() != 2) {
			keyPoints1[0].pt.x = x1[p * 2 + 1] - e; keyPoint1[0].pt.y = y2[p * 2 + 1] - f;
			keyPoint1.push_back(keyPoints1[0]);
		}
		keyPoint1[0].pt.x = x1[p * 2] - a; keyPoint1[0].pt.y = y1[p * 2] - b;
		keyPoint1[1].pt.x = x1[p * 2 + 1] - a; keyPoint1[1].pt.y = y1[p * 2 + 1] - b;
		if (keyPoint1[0].pt.x < keyPoint1[1].pt.x) {
			keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
		}
		else if (keyPoint1[0].pt.x > keyPoint1[1].pt.x) {
			keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
		}
		else if (keyPoint1[0].pt.x == keyPoint1[1].pt.x) {
			if (keyPoint1[0].pt.y > keyPoint1[1].pt.y) {
				keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
			}
			else
				keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
		}
		Detector.detect(roi2, keyPoint2);
		if (keyPoint2.size() != 2) {
			keyPoints2[0].pt.x = x2[p * 2 + 1] - e; keyPoint2[0].pt.y = y2[p * 2 + 1] - f;
			keyPoint2.push_back(keyPoints2[0]);
		}
		keyPoint2[0].pt.x = x2[p * 2] - e; keyPoint2[0].pt.y = y2[p * 2] - f;
		keyPoint2[1].pt.x = x2[p * 2 + 1] - e; keyPoint2[1].pt.y = y2[p * 2 + 1] - f;
		if (keyPoint2[0].pt.x < keyPoint2[1].pt.x) {
			keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
		}
		else if (keyPoint2[0].pt.x > keyPoint2[1].pt.x) {
			keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
		}
		else if (keyPoint2[0].pt.x == keyPoint2[1].pt.x) {
			if (keyPoint2[0].pt.y > keyPoint2[1].pt.y) {
				keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
			}
			else
				keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
		}
	}
}

void MatchPoint2_4(int i, vector<int> letters, Mat& roi1, Mat& roi2, vector<KeyPoint>& keyPoint1, vector<KeyPoint>& keyPoint2)
{
	vector<KeyPoint> keyPoints1(200), keyPoints2(200);//循环前预定义

	int a = letters[0];
	int b = letters[1];
	int e = letters[2];
	int f = letters[3];

	if (i<22) {
		ifstream infile1, infile2;
		string filename;
		filename = "E:\\Biyesheji\\Detection\\Detection\\match corner\\";
		infile1.open(filename + "result21(2&4).txt", ios::in);
		infile2.open(filename + "result41(2&4).txt", ios::in);
		double x1[200], y1[200], x2[200], y2[200];
		while (!infile1.eof()) {
			for (int j = 0; j < 44; j++)
			{
				infile1 >> x1[j] >> y1[j];
			}
		}
		while (!infile2.eof()) {
			for (int j = 0; j < 44; j++)
			{
				infile2 >> x2[j] >> y2[j];
			}
		}
		GoodFeaturesToTrackDetector Detector(2);  //最大点数,值越大，点越多
		Detector.detect(roi1, keyPoint1);
		while (keyPoint1.size() != 2) {
			keyPoint1.push_back(keyPoints1[0]);
		}
		keyPoint1[0].pt.x = x1[2 * i] - a; keyPoint1[0].pt.y = y1[2 * i] - b;
		keyPoint1[1].pt.x = x1[2 * i + 1] - a; keyPoint1[1].pt.y = y1[2 * i + 1] - b;
		if (keyPoint1[0].pt.x < keyPoint1[1].pt.x) {
			keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
		}
		else if (keyPoint1[0].pt.x > keyPoint1[1].pt.x) {
			keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
		}
		else if (keyPoint1[0].pt.x == keyPoint1[1].pt.x) {
			if (keyPoint1[0].pt.y > keyPoint1[1].pt.y) {
				keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
			}
			else
				keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
		}
		Detector.detect(roi2, keyPoint2);
		while (keyPoint2.size() != 2) {
			keyPoint2.push_back(keyPoints2[0]);
		}
		keyPoint2[0].pt.x = x2[2 * i] - e; keyPoint2[0].pt.y = y2[2 * i] - f;
		keyPoint2[1].pt.x = x2[2 * i + 1] - e; keyPoint2[1].pt.y = y2[2 * i + 1] - f;
		if (keyPoint2[0].pt.x < keyPoint2[1].pt.x) {
			keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
		}
		else if (keyPoint2[0].pt.x > keyPoint2[1].pt.x) {
			keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
		}
		else if (keyPoint2[0].pt.x == keyPoint2[1].pt.x) {
			if (keyPoint2[0].pt.y > keyPoint2[1].pt.y) {
				keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
			}
			else
				keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
		}

	}

	else if (i >= 22 && i < 44) {
		ifstream infile1, infile2;
		string filename;
		filename = "E:\\Biyesheji\\Detection\\Detection\\match corner\\";
		infile1.open(filename + "result22(2&4).txt", ios::in);
		infile2.open(filename + "result42(2&4).txt", ios::in);
		double x1[200], y1[200], x2[200], y2[200];
		while (!infile1.eof()) {
			for (int j = 0; j < 66; j++)
			{
				infile1 >> x1[j] >> y1[j];
			}
		}
		while (!infile2.eof()) {
			for (int j = 0; j < 66; j++)
			{
				infile2 >> x2[j] >> y2[j];
			}
		}
		if (i % 2 == 0) {
			GoodFeaturesToTrackDetector Detector(4);
			Detector.detect(roi1, keyPoint1);
			while (keyPoint1.size() != 4) {
				keyPoint1.push_back(keyPoints1[0]);
			}
			int p = (i - 22) / 2;
			keyPoint1[0].pt.x = x1[6 * p] - a; keyPoint1[0].pt.y = y1[6 * p] - b;
			keyPoint1[1].pt.x = x1[6 * p + 1] - a; keyPoint1[1].pt.y = y1[6 * p + 1] - b;
			keyPoint1[2].pt.x = x1[6 * p + 2] - a; keyPoint1[2].pt.y = y1[6 * p + 2] - b;
			keyPoint1[3].pt.x = x1[6 * p + 3] - a; keyPoint1[3].pt.y = y1[6 * p + 3] - b;
			if (keyPoint1[0].pt.x >= keyPoint1[1].pt.x&&keyPoint1[0].pt.x >= keyPoint1[1].pt.x&&keyPoint1[0].pt.x >= keyPoint1[3].pt.x) {
				keyPoint1[0].class_id = 1;
				if (keyPoint1[1].pt.x >= keyPoint1[2].pt.x&&keyPoint1[1].pt.x >= keyPoint1[3].pt.x) {
					keyPoint1[1].class_id = 2;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 3;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 3;
						keyPoint1[2].class_id = 4;
					}
				}
				else if (keyPoint1[1].pt.x <= keyPoint1[2].pt.x&&keyPoint1[1].pt.x <= keyPoint1[3].pt.x) {
					keyPoint1[1].class_id = 4;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 2;
						keyPoint1[3].class_id = 3;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 3;
					}
				}
				else {
					keyPoint1[1].class_id = 3;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 2;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 4;
					}
				}
			}
			else if (keyPoint1[1].pt.x >= keyPoint1[0].pt.x&&keyPoint1[1].pt.x >= keyPoint1[2].pt.x&&keyPoint1[1].pt.x >= keyPoint1[3].pt.x) {
				keyPoint1[1].class_id = 1;
				if (keyPoint1[0].pt.x >= keyPoint1[2].pt.x&&keyPoint1[0].pt.x >= keyPoint1[3].pt.x) {
					keyPoint1[0].class_id = 2;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 3;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 3;
						keyPoint1[2].class_id = 4;
					}
				}
				else if (keyPoint1[0].pt.x <= keyPoint1[2].pt.x&&keyPoint1[01].pt.x <= keyPoint1[3].pt.x) {
					keyPoint1[0].class_id = 4;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 2;
						keyPoint1[3].class_id = 3;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 3;
					}
				}
				else {
					keyPoint1[0].class_id = 3;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 2;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 4;
					}
				}
			}
			else if (keyPoint1[2].pt.x >= keyPoint1[0].pt.x&&keyPoint1[2].pt.x >= keyPoint1[1].pt.x&&keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
				keyPoint1[2].class_id = 1;
				if (keyPoint1[0].pt.x >= keyPoint1[1].pt.x&&keyPoint1[0].pt.x >= keyPoint1[3].pt.x) {
					keyPoint1[0].class_id = 2;
					if (keyPoint1[1].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[1].class_id = 3;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 3;
						keyPoint1[1].class_id = 4;
					}
				}
				else if (keyPoint1[0].pt.x <= keyPoint1[1].pt.x&&keyPoint1[0].pt.x <= keyPoint1[3].pt.x) {
					keyPoint1[0].class_id = 4;
					if (keyPoint1[1].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[1].class_id = 2;
						keyPoint1[3].class_id = 3;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[1].class_id = 3;
					}
				}
				else {
					keyPoint1[0].class_id = 3;
					if (keyPoint1[1].pt.x > keyPoint1[3].pt.x) {
						keyPoint1[1].class_id = 2;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[1].class_id = 4;
					}
				}
			}
			else if (keyPoint1[3].pt.x >= keyPoint1[0].pt.x&&keyPoint1[3].pt.x >= keyPoint1[1].pt.x&&keyPoint1[3].pt.x >= keyPoint1[2].pt.x) {
				keyPoint1[3].class_id = 1;
				if (keyPoint1[0].pt.x >= keyPoint1[1].pt.x&&keyPoint1[0].pt.x >= keyPoint1[2].pt.x) {
					keyPoint1[0].class_id = 2;
					if (keyPoint1[1].pt.x >= keyPoint1[2].pt.x) {
						keyPoint1[1].class_id = 3;
						keyPoint1[2].class_id = 4;
					}
					else {
						keyPoint1[2].class_id = 3;
						keyPoint1[1].class_id = 4;
					}
				}
				else if (keyPoint1[0].pt.x <= keyPoint1[1].pt.x&&keyPoint1[0].pt.x <= keyPoint1[2].pt.x) {
					keyPoint1[0].class_id = 4;
					if (keyPoint1[1].pt.x >= keyPoint1[2].pt.x) {
						keyPoint1[1].class_id = 2;
						keyPoint1[2].class_id = 3;
					}
					else {
						keyPoint1[2].class_id = 2;
						keyPoint1[1].class_id = 3;
					}
				}
				else {
					keyPoint1[0].class_id = 3;
					if (keyPoint1[1].pt.x >= keyPoint1[2].pt.x) {
						keyPoint1[1].class_id = 2;
						keyPoint1[2].class_id = 4;
					}
					else {
						keyPoint1[2].class_id = 2;
						keyPoint1[1].class_id = 4;
					}
				}
			}
			for (int k = 0; k < 4; k++) {
				for (int j = k + 1; j < 4; j++) {
					if (keyPoint1[k].pt.x == keyPoint1[j].pt.x) {
						int max = keyPoint1[k].class_id;
						if (keyPoint1[k].pt.y > keyPoint1[j].pt.y&&keyPoint2[k].class_id < keyPoint1[j].class_id) {
							keyPoint1[j].class_id = keyPoint1[j].class_id;
							keyPoint1[k].class_id = max;
						}
						else if (keyPoint1[k].pt.y < keyPoint1[j].pt.y&&keyPoint1[k].class_id < keyPoint1[j].class_id) {
							keyPoint1[k].class_id = keyPoint1[j].class_id;
							keyPoint1[j].class_id = max;
						}
						else if (keyPoint1[k].pt.y > keyPoint1[j].pt.y&&keyPoint1[k].class_id > keyPoint1[j].class_id) {
							keyPoint1[k].class_id = keyPoint1[j].class_id;
							keyPoint1[j].class_id = max;
						}
						else if (keyPoint1[k].pt.y < keyPoint1[j].pt.y&&keyPoint1[k].class_id > keyPoint1[j].class_id) {
							keyPoint1[j].class_id = keyPoint1[j].class_id;
							keyPoint1[k].class_id = max;
						}
					}
				}
			}
			Detector.detect(roi2, keyPoint2);
			while (keyPoint2.size() != 4) {
				keyPoint2.push_back(keyPoints2[0]);
			}
			keyPoint2[0].pt.x = x2[6 * p] - e; keyPoint2[0].pt.y = y2[6 * p] - f;
			keyPoint2[1].pt.x = x2[6 * p + 1] - e; keyPoint2[1].pt.y = y2[6 * p + 1] - f;
			keyPoint2[2].pt.x = x2[6 * p + 2] - e; keyPoint2[2].pt.y = y2[6 * p + 2] - f;
			keyPoint2[3].pt.x = x2[6 * p + 3] - e; keyPoint2[3].pt.y = y2[6 * p + 3] - f;
			if (keyPoint2[0].pt.x >= keyPoint2[1].pt.x&&keyPoint2[0].pt.x >= keyPoint2[2].pt.x&&keyPoint2[0].pt.x >= keyPoint2[3].pt.x) {
				keyPoint2[0].class_id = 1;
				if (keyPoint2[1].pt.x >= keyPoint2[2].pt.x&&keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
					keyPoint2[1].class_id = 2;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 3;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 3;
						keyPoint2[2].class_id = 4;
					}
				}
				else if (keyPoint2[1].pt.x <= keyPoint2[2].pt.x&&keyPoint2[1].pt.x <= keyPoint2[3].pt.x) {
					keyPoint2[1].class_id = 4;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 2;
						keyPoint2[3].class_id = 3;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[2].class_id = 3;
					}
				}
				else {
					keyPoint2[1].class_id = 3;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 2;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[2].class_id = 4;
					}
				}
			}
			else if (keyPoint2[1].pt.x >= keyPoint2[0].pt.x&&keyPoint2[1].pt.x >= keyPoint2[2].pt.x&&keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
				keyPoint2[1].class_id = 1;
				if (keyPoint2[0].pt.x >= keyPoint2[2].pt.x&&keyPoint2[0].pt.x >= keyPoint2[3].pt.x) {
					keyPoint2[0].class_id = 2;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 3;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 3;
						keyPoint2[2].class_id = 4;
					}
				}
				else if (keyPoint2[0].pt.x <= keyPoint2[2].pt.x&&keyPoint1[01].pt.x <= keyPoint2[3].pt.x) {
					keyPoint2[0].class_id = 4;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 2;
						keyPoint2[3].class_id = 3;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[2].class_id = 3;
					}
				}
				else {
					keyPoint2[0].class_id = 3;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 2;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 4;
					}
				}
			}
			else if (keyPoint2[2].pt.x >= keyPoint2[0].pt.x&&keyPoint2[2].pt.x >= keyPoint2[1].pt.x&&keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
				keyPoint2[2].class_id = 1;
				if (keyPoint2[0].pt.x >= keyPoint2[1].pt.x&&keyPoint2[0].pt.x >= keyPoint2[3].pt.x) {
					keyPoint2[0].class_id = 2;
					if (keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[1].class_id = 3;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 3;
						keyPoint2[1].class_id = 4;
					}
				}
				else if (keyPoint2[0].pt.x <= keyPoint2[1].pt.x&&keyPoint2[0].pt.x <= keyPoint2[3].pt.x) {
					keyPoint2[0].class_id = 4;
					if (keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[1].class_id = 2;
						keyPoint2[3].class_id = 3;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[1].class_id = 3;
					}
				}
				else {
					keyPoint2[0].class_id = 3;
					if (keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[1].class_id = 2;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[1].class_id = 4;
					}
				}
			}
			else if (keyPoint2[3].pt.x >= keyPoint2[0].pt.x&&keyPoint2[3].pt.x >= keyPoint2[1].pt.x&&keyPoint2[3].pt.x >= keyPoint2[2].pt.x) {
				keyPoint2[3].class_id = 1;
				if (keyPoint2[0].pt.x >= keyPoint2[1].pt.x&&keyPoint2[0].pt.x >= keyPoint2[2].pt.x) {
					keyPoint2[0].class_id = 2;
					if (keyPoint2[1].pt.x >= keyPoint2[2].pt.x) {
						keyPoint2[1].class_id = 3;
						keyPoint2[2].class_id = 4;
					}
					else {
						keyPoint2[2].class_id = 3;
						keyPoint2[1].class_id = 4;
					}
				}
				else if (keyPoint2[0].pt.x <= keyPoint2[1].pt.x&&keyPoint2[0].pt.x <= keyPoint2[2].pt.x) {
					keyPoint2[0].class_id = 4;
					if (keyPoint2[1].pt.x >= keyPoint2[2].pt.x) {
						keyPoint2[1].class_id = 2;
						keyPoint2[2].class_id = 3;
					}
					else {
						keyPoint2[2].class_id = 2;
						keyPoint2[1].class_id = 3;
					}
				}
				else {
					keyPoint2[0].class_id = 3;
					if (keyPoint2[1].pt.x >= keyPoint2[2].pt.x) {
						keyPoint2[1].class_id = 2;
						keyPoint2[2].class_id = 4;
					}
					else {
						keyPoint2[2].class_id = 2;
						keyPoint2[1].class_id = 4;
					}
				}
			}
			for (int k = 0; k < 4; k++) {
				for (int j = k + 1; j < 4; j++) {
					if (keyPoint2[k].pt.x == keyPoint2[j].pt.x) {
						int max = keyPoint2[k].class_id;
						if (keyPoint2[k].pt.y > keyPoint2[j].pt.y&&keyPoint2[k].class_id < keyPoint2[j].class_id) {
							keyPoint2[j].class_id = keyPoint2[j].class_id;
							keyPoint2[k].class_id = max;
						}
						else if (keyPoint2[k].pt.y < keyPoint2[j].pt.y&&keyPoint2[k].class_id < keyPoint2[j].class_id) {
							keyPoint2[k].class_id = keyPoint2[j].class_id;
							keyPoint2[j].class_id = max;
						}
						else if (keyPoint2[k].pt.y > keyPoint2[j].pt.y&&keyPoint2[k].class_id > keyPoint2[j].class_id) {
							keyPoint2[k].class_id = keyPoint2[j].class_id;
							keyPoint2[j].class_id = max;
						}
						else if (keyPoint2[k].pt.y < keyPoint2[j].pt.y&&keyPoint2[k].class_id > keyPoint2[j].class_id) {
							keyPoint2[j].class_id = keyPoint2[j].class_id;
							keyPoint2[k].class_id = max;
						}
					}
				}
			}
		}
		else if (i % 2 != 0) {
			int p = (i - 23) / 2;
			GoodFeaturesToTrackDetector Detector(2);
			Detector.detect(roi1, keyPoint1);
			if (keyPoint1.size() != 2) {
				keyPoints1[0].pt.x = x1[p * 2 + 1] - e; keyPoint2[0].pt.y = y1[p * 2 + 1] - f;
				keyPoint1.push_back(keyPoints2[0]);
			}
			keyPoint1[0].pt.x = x1[6 * p + 4] - a; keyPoint1[0].pt.y = y1[6 * p + 4] - b;
			keyPoint1[1].pt.x = x1[6 * p + 5] - a; keyPoint1[1].pt.y = y1[6 * p + 5] - b;
			if (keyPoint1[0].pt.x < keyPoint1[1].pt.x) {
				keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
			}
			else if (keyPoint1[0].pt.x > keyPoint1[1].pt.x) {
				keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
			}
			else if (keyPoint1[0].pt.x == keyPoint1[1].pt.x) {
				if (keyPoint1[0].pt.y > keyPoint1[1].pt.y) {
					keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
				}
				else
					keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
			}

			Detector.detect(roi2, keyPoint2);
			if (keyPoint2.size() != 2) {
				keyPoints2[0].pt.x = x2[p * 2 + 1] - e; keyPoint2[0].pt.y = y2[p * 2 + 1] - f;
				keyPoint2.push_back(keyPoints2[0]);
			}
			keyPoint2[0].pt.x = x2[6 * p + 4] - e; keyPoint2[0].pt.y = y2[6 * p + 4] - f;
			keyPoint2[1].pt.x = x2[6 * p + 5] - e; keyPoint2[1].pt.y = y2[6 * p + 5] - f;
			if (keyPoint2[0].pt.x < keyPoint2[1].pt.x) {
				keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
			}
			else if (keyPoint2[0].pt.x > keyPoint2[1].pt.x) {
				keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
			}
			else if (keyPoint2[0].pt.x == keyPoint2[1].pt.x) {
				if (keyPoint2[0].pt.y > keyPoint2[1].pt.y) {
					keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
				}
				else
					keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
			}
		}
	}

	else if (i >= 44 && i < 77) {
		int p = i - 44;
		ifstream infile1, infile2;
		string filename;
		filename = "E:\\Biyesheji\\Detection\\Detection\\match corner\\";
		infile1.open(filename + "result23(2&4).txt", ios::in);
		infile2.open(filename + "result43(2&4).txt", ios::in);
		double x1[200], y1[200], x2[200], y2[200];
		while (!infile1.eof()) {
			for (int j = 0; j < 33; j++)
			{
				infile1 >> x1[j] >> y1[j];
			}
		}
		while (!infile2.eof()) {
			for (int j = 0; j < 33; j++)
			{
				infile2 >> x2[j] >> y2[j];
			}
		}
		GoodFeaturesToTrackDetector Detector(1);
		Detector.detect(roi1, keyPoint1);
		Detector.detect(roi2, keyPoint2);
		keyPoint1[0].pt.x = x1[p] - a; keyPoint1[0].pt.y = y1[p] - b;
		keyPoint2[0].pt.x = x2[p] - e; keyPoint2[0].pt.y = y2[p] - f;
		keyPoint1[0].class_id = i;
		keyPoint2[0].class_id = i;
	}

	else if (i >= 77 && i<85) {
		ifstream infile1, infile2;
		string filename;
		filename = "E:\\Biyesheji\\Detection\\Detection\\match corner\\";
		infile1.open(filename + "result24(2&4).txt", ios::in);
		infile2.open(filename + "result44(2&4).txt", ios::in);
		double x1[200], y1[200], x2[200], y2[200];
		while (!infile1.eof()) {
			for (int j = 0; j < 16; j++)
			{
				infile1 >> x1[j] >> y1[j];
			}
		}
		while (!infile2.eof()) {
			for (int j = 0; j < 16; j++)
			{
				infile2 >> x2[j] >> y2[j];
			}
		}
		int p = i - 77;
		GoodFeaturesToTrackDetector Detector(2);
		Detector.detect(roi1, keyPoint1);
		if (keyPoint1.size() != 2) {
			keyPoints1[0].pt.x = x1[p * 2 + 1] - e; keyPoint1[0].pt.y = y2[p * 2 + 1] - f;
			keyPoint1.push_back(keyPoints1[0]);
		}
		keyPoint1[0].pt.x = x1[p * 2] - a; keyPoint1[0].pt.y = y1[p * 2] - b;
		keyPoint1[1].pt.x = x1[p * 2 + 1] - a; keyPoint1[1].pt.y = y1[p * 2 + 1] - b;
		if (keyPoint1[0].pt.x < keyPoint1[1].pt.x) {
			keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
		}
		else if (keyPoint1[0].pt.x > keyPoint1[1].pt.x) {
			keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
		}
		else if (keyPoint1[0].pt.x == keyPoint1[1].pt.x) {
			if (keyPoint1[0].pt.y > keyPoint1[1].pt.y) {
				keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
			}
			else
				keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
		}
		Detector.detect(roi2, keyPoint2);
		if (keyPoint2.size() != 2) {
			keyPoints2[0].pt.x = x2[p * 2 + 1] - e; keyPoint2[0].pt.y = y2[p * 2 + 1] - f;
			keyPoint2.push_back(keyPoints2[0]);
		}
		keyPoint2[0].pt.x = x2[p * 2] - e; keyPoint2[0].pt.y = y2[p * 2] - f;
		keyPoint2[1].pt.x = x2[p * 2 + 1] - e; keyPoint2[1].pt.y = y2[p * 2 + 1] - f;
		if (keyPoint2[0].pt.x < keyPoint2[1].pt.x) {
			keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
		}
		else if (keyPoint2[0].pt.x > keyPoint2[1].pt.x) {
			keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
		}
		else if (keyPoint2[0].pt.x == keyPoint2[1].pt.x) {
			if (keyPoint2[0].pt.y > keyPoint2[1].pt.y) {
				keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
			}
			else
				keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
		}
	}
}

void MatchPoint3_4(int i, vector<int> letters, Mat& roi1, Mat& roi2, vector<KeyPoint>& keyPoint1, vector<KeyPoint>& keyPoint2)
{
	vector<KeyPoint> keyPoints1(200), keyPoints2(200);//循环前预定义

	int a = letters[0];
	int b = letters[1];
	int e = letters[2];
	int f = letters[3];

	if (i<19) {
		ifstream infile1, infile2;
		string filename;
		filename = "E:\\Biyesheji\\Detection\\Detection\\match corner\\";
		infile1.open(filename + "result31(3&4).txt", ios::in);
		infile2.open(filename + "result41(3&4).txt", ios::in);   //导入目标角点坐标
		double x1[200], y1[200], x2[200], y2[200];
		while (!infile1.eof()) {
			for (int j = 0; j < 38; j++)
			{
				infile1 >> x1[j] >> y1[j];
			}
		}
		while (!infile2.eof()) {
			for (int j = 0; j < 38; j++)
			{
				infile2 >> x2[j] >> y2[j];
			}
		}
		GoodFeaturesToTrackDetector Detector(2);
		Detector.detect(roi1, keyPoint1);   //检测角点
		while (keyPoint1.size() != 2) {
			keyPoint1.push_back(keyPoints1[0]);
		}
		keyPoint1[0].pt.x = x1[2 * i] - a; keyPoint1[0].pt.y = y1[2 * i] - b;
		keyPoint1[1].pt.x = x1[2 * i + 1] - a; keyPoint1[1].pt.y = y1[2 * i + 1] - b;    //目标角点在区域内坐标
		if (keyPoint1[0].pt.x < keyPoint1[1].pt.x) {
			keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
		}
		else if (keyPoint1[0].pt.x > keyPoint1[1].pt.x) {
			keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
		}
		else if (keyPoint1[0].pt.x == keyPoint1[1].pt.x) {
			if (keyPoint1[0].pt.y > keyPoint1[1].pt.y) {
				keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
			}
			else
				keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
		}                                                             //进行角点分类

		Detector.detect(roi2, keyPoint2);
		while (keyPoint2.size() != 2) {
			keyPoint2.push_back(keyPoints2[0]);
		}
		keyPoint2[0].pt.x = x2[2 * i] - e; keyPoint2[0].pt.y = y2[2 * i] - f;
		keyPoint2[1].pt.x = x2[2 * i + 1] - e; keyPoint2[1].pt.y = y2[2 * i + 1] - f;
		if (keyPoint2[0].pt.x < keyPoint2[1].pt.x) {
			keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
		}
		else if (keyPoint2[0].pt.x > keyPoint2[1].pt.x) {
			keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
		}
		else if (keyPoint2[0].pt.x == keyPoint2[1].pt.x) {
			if (keyPoint2[0].pt.y > keyPoint2[1].pt.y) {
				keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
			}
			else
				keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
		}

	}

	else if (i >= 19 && i < 38) {
		ifstream infile1, infile2;
		string filename;
		filename = "E:\\Biyesheji\\Detection\\Detection\\match corner\\";
		infile1.open(filename + "result32(3&4).txt", ios::in);
		infile2.open(filename + "result42(3&4).txt", ios::in);
		double x1[200], y1[200], x2[200], y2[200];
		while (!infile1.eof()) {
			for (int j = 0; j < 56; j++)
			{
				infile1 >> x1[j] >> y1[j];
			}
		}
		while (!infile2.eof()) {
			for (int j = 0; j < 56; j++)
			{
				infile2 >> x2[j] >> y2[j];
			}
		}
		if (i % 2 == 0) {
			GoodFeaturesToTrackDetector Detector(4);
			Detector.detect(roi1, keyPoint1);
			while (keyPoint1.size() != 4) {
				keyPoint1.push_back(keyPoints1[0]);
			}
			int p = (i - 19) / 2;
			keyPoint1[0].pt.x = x1[6 * p + 2] - a; keyPoint1[0].pt.y = y1[6 * p + 2] - b;
			keyPoint1[1].pt.x = x1[6 * p + 3] - a; keyPoint1[1].pt.y = y1[6 * p + 3] - b;
			keyPoint1[2].pt.x = x1[6 * p + 4] - a; keyPoint1[2].pt.y = y1[6 * p + 4] - b;
			keyPoint1[3].pt.x = x1[6 * p + 5] - a; keyPoint1[3].pt.y = y1[6 * p + 5] - b;
			if (keyPoint1[0].pt.x >= keyPoint1[1].pt.x&&keyPoint1[0].pt.x >= keyPoint1[1].pt.x&&keyPoint1[0].pt.x >= keyPoint1[3].pt.x) {
				keyPoint1[0].class_id = 1;
				if (keyPoint1[1].pt.x >= keyPoint1[2].pt.x&&keyPoint1[1].pt.x >= keyPoint1[3].pt.x) {
					keyPoint1[1].class_id = 2;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 3;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 3;
						keyPoint1[2].class_id = 4;
					}
				}
				else if (keyPoint1[1].pt.x <= keyPoint1[2].pt.x&&keyPoint1[1].pt.x <= keyPoint1[3].pt.x) {
					keyPoint1[1].class_id = 4;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 2;
						keyPoint1[3].class_id = 3;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 3;
					}
				}
				else {
					keyPoint1[1].class_id = 3;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 2;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 4;
					}
				}
			}
			else if (keyPoint1[1].pt.x >= keyPoint1[0].pt.x&&keyPoint1[1].pt.x >= keyPoint1[2].pt.x&&keyPoint1[1].pt.x >= keyPoint1[3].pt.x) {
				keyPoint1[1].class_id = 1;
				if (keyPoint1[0].pt.x >= keyPoint1[2].pt.x&&keyPoint1[0].pt.x >= keyPoint1[3].pt.x) {
					keyPoint1[0].class_id = 2;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 3;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 3;
						keyPoint1[2].class_id = 4;
					}
				}
				else if (keyPoint1[0].pt.x <= keyPoint1[2].pt.x&&keyPoint1[01].pt.x <= keyPoint1[3].pt.x) {
					keyPoint1[0].class_id = 4;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 2;
						keyPoint1[3].class_id = 3;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 3;
					}
				}
				else {
					keyPoint1[0].class_id = 3;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 2;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 4;
					}
				}
			}
			else if (keyPoint1[2].pt.x >= keyPoint1[0].pt.x&&keyPoint1[2].pt.x >= keyPoint1[1].pt.x&&keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
				keyPoint1[2].class_id = 1;
				if (keyPoint1[0].pt.x >= keyPoint1[1].pt.x&&keyPoint1[0].pt.x >= keyPoint1[3].pt.x) {
					keyPoint1[0].class_id = 2;
					if (keyPoint1[1].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[1].class_id = 3;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 3;
						keyPoint1[1].class_id = 4;
					}
				}
				else if (keyPoint1[0].pt.x <= keyPoint1[1].pt.x&&keyPoint1[0].pt.x <= keyPoint1[3].pt.x) {
					keyPoint1[0].class_id = 4;
					if (keyPoint1[1].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[1].class_id = 2;
						keyPoint1[3].class_id = 3;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[1].class_id = 3;
					}
				}
				else {
					keyPoint1[0].class_id = 3;
					if (keyPoint1[1].pt.x > keyPoint1[3].pt.x) {
						keyPoint1[1].class_id = 2;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[1].class_id = 4;
					}
				}
			}
			else if (keyPoint1[3].pt.x >= keyPoint1[0].pt.x&&keyPoint1[3].pt.x >= keyPoint1[1].pt.x&&keyPoint1[3].pt.x >= keyPoint1[2].pt.x) {
				keyPoint1[3].class_id = 1;
				if (keyPoint1[0].pt.x >= keyPoint1[1].pt.x&&keyPoint1[0].pt.x >= keyPoint1[2].pt.x) {
					keyPoint1[0].class_id = 2;
					if (keyPoint1[1].pt.x >= keyPoint1[2].pt.x) {
						keyPoint1[1].class_id = 3;
						keyPoint1[2].class_id = 4;
					}
					else {
						keyPoint1[2].class_id = 3;
						keyPoint1[1].class_id = 4;
					}
				}
				else if (keyPoint1[0].pt.x <= keyPoint1[1].pt.x&&keyPoint1[0].pt.x <= keyPoint1[2].pt.x) {
					keyPoint1[0].class_id = 4;
					if (keyPoint1[1].pt.x >= keyPoint1[2].pt.x) {
						keyPoint1[1].class_id = 2;
						keyPoint1[2].class_id = 3;
					}
					else {
						keyPoint1[2].class_id = 2;
						keyPoint1[1].class_id = 3;
					}
				}
				else {
					keyPoint1[0].class_id = 3;
					if (keyPoint1[1].pt.x >= keyPoint1[2].pt.x) {
						keyPoint1[1].class_id = 2;
						keyPoint1[2].class_id = 4;
					}
					else {
						keyPoint1[2].class_id = 2;
						keyPoint1[1].class_id = 4;
					}
				}
			}
			for (int k = 0; k < 4; k++) {
				for (int j = k + 1; j < 4; j++) {
					if (keyPoint1[k].pt.x == keyPoint1[j].pt.x) {
						int max = keyPoint1[k].class_id;
						if (keyPoint1[k].pt.y > keyPoint1[j].pt.y&&keyPoint2[k].class_id < keyPoint1[j].class_id) {
							keyPoint1[j].class_id = keyPoint1[j].class_id;
							keyPoint1[k].class_id = max;
						}
						else if (keyPoint1[k].pt.y < keyPoint1[j].pt.y&&keyPoint1[k].class_id < keyPoint1[j].class_id) {
							keyPoint1[k].class_id = keyPoint1[j].class_id;
							keyPoint1[j].class_id = max;
						}
						else if (keyPoint1[k].pt.y > keyPoint1[j].pt.y&&keyPoint1[k].class_id > keyPoint1[j].class_id) {
							keyPoint1[k].class_id = keyPoint1[j].class_id;
							keyPoint1[j].class_id = max;
						}
						else if (keyPoint1[k].pt.y < keyPoint1[j].pt.y&&keyPoint1[k].class_id > keyPoint1[j].class_id) {
							keyPoint1[j].class_id = keyPoint1[j].class_id;
							keyPoint1[k].class_id = max;
						}
					}
				}
			}
			Detector.detect(roi2, keyPoint2);
			while (keyPoint2.size() != 4) {
				keyPoint2.push_back(keyPoints2[0]);
			}
			keyPoint2[0].pt.x = x2[6 * p + 2] - e; keyPoint2[0].pt.y = y2[6 * p + 2] - f;
			keyPoint2[1].pt.x = x2[6 * p + 3] - e; keyPoint2[1].pt.y = y2[6 * p + 3] - f;
			keyPoint2[2].pt.x = x2[6 * p + 4] - e; keyPoint2[2].pt.y = y2[6 * p + 4] - f;
			keyPoint2[3].pt.x = x2[6 * p + 5] - e; keyPoint2[3].pt.y = y2[6 * p + 5] - f;
			if (keyPoint2[0].pt.x >= keyPoint2[1].pt.x&&keyPoint2[0].pt.x >= keyPoint2[2].pt.x&&keyPoint2[0].pt.x >= keyPoint2[3].pt.x) {
				keyPoint2[0].class_id = 1;
				if (keyPoint2[1].pt.x >= keyPoint2[2].pt.x&&keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
					keyPoint2[1].class_id = 2;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 3;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 3;
						keyPoint2[2].class_id = 4;
					}
				}
				else if (keyPoint2[1].pt.x <= keyPoint2[2].pt.x&&keyPoint2[1].pt.x <= keyPoint2[3].pt.x) {
					keyPoint2[1].class_id = 4;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 2;
						keyPoint2[3].class_id = 3;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[2].class_id = 3;
					}
				}
				else {
					keyPoint2[1].class_id = 3;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 2;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[2].class_id = 4;
					}
				}
			}
			else if (keyPoint2[1].pt.x >= keyPoint2[0].pt.x&&keyPoint2[1].pt.x >= keyPoint2[2].pt.x&&keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
				keyPoint2[1].class_id = 1;
				if (keyPoint2[0].pt.x >= keyPoint2[2].pt.x&&keyPoint2[0].pt.x >= keyPoint2[3].pt.x) {
					keyPoint2[0].class_id = 2;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 3;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 3;
						keyPoint2[2].class_id = 4;
					}
				}
				else if (keyPoint2[0].pt.x <= keyPoint2[2].pt.x&&keyPoint1[01].pt.x <= keyPoint2[3].pt.x) {
					keyPoint2[0].class_id = 4;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 2;
						keyPoint2[3].class_id = 3;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[2].class_id = 3;
					}
				}
				else {
					keyPoint2[0].class_id = 3;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 2;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 4;
					}
				}
			}
			else if (keyPoint2[2].pt.x >= keyPoint2[0].pt.x&&keyPoint2[2].pt.x >= keyPoint2[1].pt.x&&keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
				keyPoint2[2].class_id = 1;
				if (keyPoint2[0].pt.x >= keyPoint2[1].pt.x&&keyPoint2[0].pt.x >= keyPoint2[3].pt.x) {
					keyPoint2[0].class_id = 2;
					if (keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[1].class_id = 3;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 3;
						keyPoint2[1].class_id = 4;
					}
				}
				else if (keyPoint2[0].pt.x <= keyPoint2[1].pt.x&&keyPoint2[0].pt.x <= keyPoint2[3].pt.x) {
					keyPoint2[0].class_id = 4;
					if (keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[1].class_id = 2;
						keyPoint2[3].class_id = 3;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[1].class_id = 3;
					}
				}
				else {
					keyPoint2[0].class_id = 3;
					if (keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[1].class_id = 2;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[1].class_id = 4;
					}
				}
			}
			else if (keyPoint2[3].pt.x >= keyPoint2[0].pt.x&&keyPoint2[3].pt.x >= keyPoint2[1].pt.x&&keyPoint2[3].pt.x >= keyPoint2[2].pt.x) {
				keyPoint2[3].class_id = 1;
				if (keyPoint2[0].pt.x >= keyPoint2[1].pt.x&&keyPoint2[0].pt.x >= keyPoint2[2].pt.x) {
					keyPoint2[0].class_id = 2;
					if (keyPoint2[1].pt.x >= keyPoint2[2].pt.x) {
						keyPoint2[1].class_id = 3;
						keyPoint2[2].class_id = 4;
					}
					else {
						keyPoint2[2].class_id = 3;
						keyPoint2[1].class_id = 4;
					}
				}
				else if (keyPoint2[0].pt.x <= keyPoint2[1].pt.x&&keyPoint2[0].pt.x <= keyPoint2[2].pt.x) {
					keyPoint2[0].class_id = 4;
					if (keyPoint2[1].pt.x >= keyPoint2[2].pt.x) {
						keyPoint2[1].class_id = 2;
						keyPoint2[2].class_id = 3;
					}
					else {
						keyPoint2[2].class_id = 2;
						keyPoint2[1].class_id = 3;
					}
				}
				else {
					keyPoint2[0].class_id = 3;
					if (keyPoint2[1].pt.x >= keyPoint2[2].pt.x) {
						keyPoint2[1].class_id = 2;
						keyPoint2[2].class_id = 4;
					}
					else {
						keyPoint2[2].class_id = 2;
						keyPoint2[1].class_id = 4;
					}
				}
			}
			for (int k = 0; k < 4; k++) {
				for (int j = k + 1; j < 4; j++) {
					if (keyPoint2[k].pt.x == keyPoint2[j].pt.x) {
						int max = keyPoint2[k].class_id;
						if (keyPoint2[k].pt.y > keyPoint2[j].pt.y&&keyPoint2[k].class_id < keyPoint2[j].class_id) {
							keyPoint2[j].class_id = keyPoint2[j].class_id;
							keyPoint2[k].class_id = max;
						}
						else if (keyPoint2[k].pt.y < keyPoint2[j].pt.y&&keyPoint2[k].class_id < keyPoint2[j].class_id) {
							keyPoint2[k].class_id = keyPoint2[j].class_id;
							keyPoint2[j].class_id = max;
						}
						else if (keyPoint2[k].pt.y > keyPoint2[j].pt.y&&keyPoint2[k].class_id > keyPoint2[j].class_id) {
							keyPoint2[k].class_id = keyPoint2[j].class_id;
							keyPoint2[j].class_id = max;
						}
						else if (keyPoint2[k].pt.y < keyPoint2[j].pt.y&&keyPoint2[k].class_id > keyPoint2[j].class_id) {
							keyPoint2[j].class_id = keyPoint2[j].class_id;
							keyPoint2[k].class_id = max;
						}
					}
				}
			}
		}
		else if (i % 2 != 0) {
			int p = (i - 19) / 2;
			GoodFeaturesToTrackDetector Detector(2);
			Detector.detect(roi1, keyPoint1);
			if (keyPoint1.size() != 2) {
				keyPoints1[0].pt.x = x1[p * 2 + 1] - e; keyPoint2[0].pt.y = y1[p * 2 + 1] - f;
				keyPoint1.push_back(keyPoints2[0]);
			}
			keyPoint1[0].pt.x = x1[6 * p] - a; keyPoint1[0].pt.y = y1[6 * p] - b;
			keyPoint1[1].pt.x = x1[6 * p + 1] - a; keyPoint1[1].pt.y = y1[6 * p + 1] - b;
			if (keyPoint1[0].pt.x < keyPoint1[1].pt.x) {
				keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
			}
			else if (keyPoint1[0].pt.x > keyPoint1[1].pt.x) {
				keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
			}
			else if (keyPoint1[0].pt.x == keyPoint1[1].pt.x) {
				if (keyPoint1[0].pt.y > keyPoint1[1].pt.y) {
					keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
				}
				else
					keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
			}

			Detector.detect(roi2, keyPoint2);
			if (keyPoint2.size() != 2) {
				keyPoints2[0].pt.x = x2[p * 2 + 1] - e; keyPoint2[0].pt.y = y2[p * 2 + 1] - f;
				keyPoint2.push_back(keyPoints2[0]);
			}
			keyPoint2[0].pt.x = x2[6 * p] - e; keyPoint2[0].pt.y = y2[6 * p] - f;
			keyPoint2[1].pt.x = x2[6 * p + 1] - e; keyPoint2[1].pt.y = y2[6 * p + 1] - f;
			if (keyPoint2[0].pt.x < keyPoint2[1].pt.x) {
				keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
			}
			else if (keyPoint2[0].pt.x > keyPoint2[1].pt.x) {
				keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
			}
			else if (keyPoint2[0].pt.x == keyPoint2[1].pt.x) {
				if (keyPoint2[0].pt.y > keyPoint2[1].pt.y) {
					keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
				}
				else
					keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
			}
		}
	}

	else if (i >= 38 && i < 68) {
		int p = i - 38;
		ifstream infile1, infile2;
		string filename;
		filename = "E:\\Biyesheji\\Detection\\Detection\\match corner\\";
		infile1.open(filename + "result33(3&4).txt", ios::in);
		infile2.open(filename + "result43(3&4).txt", ios::in);
		double x1[200], y1[200], x2[200], y2[200];
		while (!infile1.eof()) {
			for (int j = 0; j < 30; j++)
			{
				infile1 >> x1[j] >> y1[j];
			}
		}
		while (!infile2.eof()) {
			for (int j = 0; j < 30; j++)
			{
				infile2 >> x2[j] >> y2[j];
			}
		}
		GoodFeaturesToTrackDetector Detector(1);
		Detector.detect(roi1, keyPoint1);
		Detector.detect(roi2, keyPoint2);
		keyPoint1[0].pt.x = x1[p] - a; keyPoint1[0].pt.y = y1[p] - b;
		keyPoint2[0].pt.x = x2[p] - e; keyPoint2[0].pt.y = y2[p] - f;
		keyPoint1[0].class_id = i;
		keyPoint2[0].class_id = i;
	}

	else if (i >= 68 && i < 75) {
		ifstream infile1, infile2;
		string filename;
		filename = "E:\\Biyesheji\\Detection\\Detection\\match corner\\";
		infile1.open(filename + "result34(3&4).txt", ios::in);
		infile2.open(filename + "result44(3&4).txt", ios::in);
		double x1[200], y1[200], x2[200], y2[200];
		while (!infile1.eof()) {
			for (int j = 0; j < 14; j++)
			{
				infile1 >> x1[j] >> y1[j];
			}
		}
		while (!infile2.eof()) {
			for (int j = 0; j < 14; j++)
			{
				infile2 >> x2[j] >> y2[j];
			}
		}
		int p = i - 68;
		GoodFeaturesToTrackDetector Detector(2);
		Detector.detect(roi1, keyPoint1);
		if (keyPoint1.size() != 2) {
			keyPoints1[0].pt.x = x1[p * 2 + 1] - e; keyPoint1[0].pt.y = y2[p * 2 + 1] - f;
			keyPoint1.push_back(keyPoints1[0]);
		}
		keyPoint1[0].pt.x = x1[p * 2] - a; keyPoint1[0].pt.y = y1[p * 2] - b;
		keyPoint1[1].pt.x = x1[p * 2 + 1] - a; keyPoint1[1].pt.y = y1[p * 2 + 1] - b;
		if (keyPoint1[0].pt.x < keyPoint1[1].pt.x) {
			keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
		}
		else if (keyPoint1[0].pt.x > keyPoint1[1].pt.x) {
			keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
		}
		else if (keyPoint1[0].pt.x == keyPoint1[1].pt.x) {
			if (keyPoint1[0].pt.y > keyPoint1[1].pt.y) {
				keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
			}
			else
				keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
		}
		Detector.detect(roi2, keyPoint2);
		if (keyPoint2.size() != 2) {
			keyPoints2[0].pt.x = x2[p * 2 + 1] - e; keyPoint2[0].pt.y = y2[p * 2 + 1] - f;
			keyPoint2.push_back(keyPoints2[0]);
		}
		keyPoint2[0].pt.x = x2[p * 2] - e; keyPoint2[0].pt.y = y2[p * 2] - f;
		keyPoint2[1].pt.x = x2[p * 2 + 1] - e; keyPoint2[1].pt.y = y2[p * 2 + 1] - f;
		if (keyPoint2[0].pt.x < keyPoint2[1].pt.x) {
			keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
		}
		else if (keyPoint2[0].pt.x > keyPoint2[1].pt.x) {
			keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
		}
		else if (keyPoint2[0].pt.x == keyPoint2[1].pt.x) {
			if (keyPoint2[0].pt.y > keyPoint2[1].pt.y) {
				keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
			}
			else
				keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
		}
	}
}

void Drawlines1_2(int i, string seq1, string seq2, ofstream& outfile, Mat&outImg, vector<KeyPoint>& keyPoint1, vector<KeyPoint>& keyPoint2)
{
	for (int k = 0; k < keyPoint1.size(); k++) {
		for (int l = 0; l < keyPoint2.size(); l++) {
			if (keyPoint1[k].class_id == keyPoint2[l].class_id) {
				outfile << "Corner in pic" << seq1 << ":" << keyPoint1[k].pt << "\t" << "Match" << "\t" << "Corner in pic" << seq2 << ":" << keyPoint2[k].pt << endl;
				if (i < 25)
					line(outImg, keyPoint1[k].pt, keyPoint2[l].pt, Scalar(255, 0, 0));
				else if (i >= 25 && i < 50)
					line(outImg, keyPoint1[k].pt, keyPoint2[l].pt, Scalar(0, 255, 0));
				else if (i >= 50 && i < 86)
					line(outImg, keyPoint1[k].pt, keyPoint2[l].pt, Scalar(0, 0, 255));
				else
					line(outImg, keyPoint1[k].pt, keyPoint2[l].pt, Scalar(0, 255, 255));

			}
		}
	}  //连线
}

void Drawlines1_3(int i, string seq1, string seq2, ofstream& outfile, Mat&outImg, vector<KeyPoint>& keyPoint1, vector<KeyPoint>& keyPoint2)
{
	for (int k = 0; k < keyPoint1.size(); k++) {
		for (int l = 0; l < keyPoint2.size(); l++) {
			if (keyPoint1[k].class_id == keyPoint2[l].class_id) {
				outfile << "Corner in pic" << seq1 << ":" << keyPoint1[k].pt << "\t" << "Match" << "\t" << "Corner in pic" << seq2 << ":" << keyPoint2[k].pt << endl;
				if (i < 22)
					line(outImg, keyPoint1[k].pt, keyPoint2[l].pt, Scalar(255, 0, 0));
				else if (i >= 22 && i < 44)
					line(outImg, keyPoint1[k].pt, keyPoint2[l].pt, Scalar(0, 255, 0));
				else if (i >= 45 && i < 77)
					line(outImg, keyPoint1[k].pt, keyPoint2[l].pt, Scalar(0, 0, 255));
				else
					line(outImg, keyPoint1[k].pt, keyPoint2[l].pt, Scalar(0, 255, 255));
			}
		}
	}  //连线
}

void Drawlines1_4(int i, string seq1, string seq2, ofstream& outfile, Mat&outImg, vector<KeyPoint>& keyPoint1, vector<KeyPoint>& keyPoint2)
{
	for (int k = 0; k < keyPoint1.size(); k++) {
		for (int l = 0; l < keyPoint2.size(); l++) {
			if (keyPoint1[k].class_id == keyPoint2[l].class_id) {
				outfile << "Corner in pic" << seq1 << ":" << keyPoint1[k].pt << "\t" << "Match" << "\t" << "Corner in pic" << seq2 << ":" << keyPoint2[k].pt << endl;
				if (i < 23)
					line(outImg, keyPoint1[k].pt, keyPoint2[l].pt, Scalar(255, 0, 0));
				else if (i >= 23 && i < 48)
					line(outImg, keyPoint1[k].pt, keyPoint2[l].pt, Scalar(0, 255, 0));
				else if (i >= 48 && i < 83)
					line(outImg, keyPoint1[k].pt, keyPoint2[l].pt, Scalar(0, 0, 255));
				else
					line(outImg, keyPoint1[k].pt, keyPoint2[l].pt, Scalar(0, 255, 255));
			}
		}
	}  //连线
}

void Drawlines2_3(int i, string seq1, string seq2, ofstream& outfile, Mat&outImg, vector<KeyPoint>& keyPoint1, vector<KeyPoint>& keyPoint2)
{
	for (int k = 0; k < keyPoint1.size(); k++) {
		for (int l = 0; l < keyPoint2.size(); l++) {
			if (keyPoint1[k].class_id == keyPoint2[l].class_id) {
				outfile << "Corner in pic" << seq1 << ":" << keyPoint1[k].pt << "\t" << "Match" << "\t" << "Corner in pic" << seq2 << ":" << keyPoint2[k].pt << endl;
				if (i < 23)
					line(outImg, keyPoint1[k].pt, keyPoint2[l].pt, Scalar(255, 0, 0));
				else if (i >= 23 && i < 48)
					line(outImg, keyPoint1[k].pt, keyPoint2[l].pt, Scalar(0, 255, 0));
				else if (i >= 48 && i < 83)
					line(outImg, keyPoint1[k].pt, keyPoint2[l].pt, Scalar(0, 0, 255));
				else
					line(outImg, keyPoint1[k].pt, keyPoint2[l].pt, Scalar(0, 255, 255));
			}
		}
	}  //连线
}

void Drawlines2_4(int i, string seq1, string seq2, ofstream& outfile, Mat&outImg, vector<KeyPoint>& keyPoint1, vector<KeyPoint>& keyPoint2)
{
	for (int k = 0; k < keyPoint1.size(); k++) {
		for (int l = 0; l < keyPoint2.size(); l++) {
			if (keyPoint1[k].class_id == keyPoint2[l].class_id) {
				outfile << "Corner in pic" << seq1 << ":" << keyPoint1[k].pt << "\t" << "Match" << "\t" << "Corner in pic" << seq2 << ":" << keyPoint2[k].pt << endl;
				if (i < 22)
					line(outImg, keyPoint1[k].pt, keyPoint2[l].pt, Scalar(255, 0, 0));
				else if (i >= 22 && i < 44)
					line(outImg, keyPoint1[k].pt, keyPoint2[l].pt, Scalar(0, 255, 0));
				else if (i >= 44 && i < 77)
					line(outImg, keyPoint1[k].pt, keyPoint2[l].pt, Scalar(0, 0, 255));
				else
					line(outImg, keyPoint1[k].pt, keyPoint2[l].pt, Scalar(0, 255, 255));
			}
		}
	}  //连线
}

void Drawlines3_4(int i, string seq1, string seq2, ofstream& outfile, Mat&outImg, vector<KeyPoint>& keyPoint1, vector<KeyPoint>& keyPoint2)
{
	for (int k = 0; k < keyPoint1.size(); k++) {
		for (int l = 0; l < keyPoint2.size(); l++) {
			if (keyPoint1[k].class_id == keyPoint2[l].class_id) {
				outfile << "Corner in pic" << seq1 << ":" << keyPoint1[k].pt << "\t" << "Match" << "\t" << "Corner in pic" << seq2 << ":" << keyPoint2[k].pt << endl;
				if (i < 19)
					line(outImg, keyPoint1[k].pt, keyPoint2[l].pt, Scalar(255, 0, 0));
				else if (i >= 19 && i < 38)
					line(outImg, keyPoint1[k].pt, keyPoint2[l].pt, Scalar(0, 255, 0));
				else if (i >= 38 && i < 68)
					line(outImg, keyPoint1[k].pt, keyPoint2[l].pt, Scalar(0, 0, 255));
				else
					line(outImg, keyPoint1[k].pt, keyPoint2[l].pt, Scalar(0, 255, 255));
			}
		}
	}  //连线
}

void MatchPoint1_2_3(int i, vector<int> letters, Mat& roi1, Mat& roi2, Mat& roi3, vector<KeyPoint>& keyPoint1, vector<KeyPoint>& keyPoint2, vector<KeyPoint>& keyPoint3) {
	vector<KeyPoint> keyPoints1(200), keyPoints2(200);//循环前预定义

	int a = letters[0];
	int b = letters[1];
	int e = letters[2];
	int f = letters[3];
	int c = letters[4];
	int d = letters[5];

	if (i<22) {
		ifstream infile1, infile2, infile3;
		string filename;
		filename = "E:\\Biyesheji\\Detection\\Detection\\match corner\\";
		infile1.open(filename + "result11(1&2&3).txt", ios::in);
		infile2.open(filename + "result21(1&2&3).txt", ios::in);
		infile3.open(filename + "result31(1&2&3).txt", ios::in);//导入目标角点坐标
		double x1[200], y1[200], x2[200], y2[200], x3[200], y3[200];
		while (!infile1.eof()) {
			for (int j = 0; j < 44; j++)
			{
				infile1 >> x1[j] >> y1[j];
			}
		}
		while (!infile2.eof()) {
			for (int j = 0; j < 44; j++)
			{
				infile2 >> x2[j] >> y2[j];
			}
		}
		while (!infile3.eof()) {
			for (int j = 0; j < 44; j++)
			{
				infile3 >> x3[j] >> y3[j];
			}
		}
		GoodFeaturesToTrackDetector Detector(2);
		Detector.detect(roi1, keyPoint1);   //检测角点
		while (keyPoint1.size() != 2) {
			keyPoint1.push_back(keyPoints1[0]);
		}
		keyPoint1[0].pt.x = x1[2 * i] - a; keyPoint1[0].pt.y = y1[2 * i] - b;
		keyPoint1[1].pt.x = x1[2 * i + 1] - a; keyPoint1[1].pt.y = y1[2 * i + 1] - b;    //目标角点在区域内坐标
		if (keyPoint1[0].pt.x < keyPoint1[1].pt.x) {
			keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
		}
		else if (keyPoint1[0].pt.x > keyPoint1[1].pt.x) {
			keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
		}
		else if (keyPoint1[0].pt.x == keyPoint1[1].pt.x) {
			if (keyPoint1[0].pt.y > keyPoint1[1].pt.y) {
				keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
			}
			else
				keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
		}                                                             //进行角点分类

		Detector.detect(roi2, keyPoint2);
		while (keyPoint2.size() != 2) {
			keyPoint2.push_back(keyPoints2[0]);
		}
		keyPoint2[0].pt.x = x2[2 * i] - e; keyPoint2[0].pt.y = y2[2 * i] - f;
		keyPoint2[1].pt.x = x2[2 * i + 1] - e; keyPoint2[1].pt.y = y2[2 * i + 1] - f;
		if (keyPoint2[0].pt.x < keyPoint2[1].pt.x) {
			keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
		}
		else if (keyPoint2[0].pt.x > keyPoint2[1].pt.x) {
			keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
		}
		else if (keyPoint2[0].pt.x == keyPoint2[1].pt.x) {
			if (keyPoint2[0].pt.y > keyPoint2[1].pt.y) {
				keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
			}
			else
				keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
		}

		Detector.detect(roi3, keyPoint3);
		while (keyPoint3.size() != 2) {
			keyPoint3.push_back(keyPoint2[0]);
		}
		keyPoint3[0].pt.x = x3[2 * i] - c; keyPoint3[0].pt.y = y3[2 * i] - d;
		keyPoint3[1].pt.x = x3[2 * i + 1] - c; keyPoint2[1].pt.y = y3[2 * i + 1] - d;
		if (keyPoint3[0].pt.x < keyPoint3[1].pt.x) {
			keyPoint3[0].class_id = 1;  keyPoint3[1].class_id = 2;
		}
		else if (keyPoint3[0].pt.x > keyPoint3[1].pt.x) {
			keyPoint3[0].class_id = 2;  keyPoint3[1].class_id = 1;
		}
		else if (keyPoint3[0].pt.x == keyPoint3[1].pt.x) {
			if (keyPoint3[0].pt.y > keyPoint3[1].pt.y) {
				keyPoint3[0].class_id = 1;  keyPoint3[1].class_id = 2;
			}
			else
				keyPoint3[0].class_id = 2;  keyPoint3[1].class_id = 1;
		}
	}

	else if (i >= 22 && i < 44) {
		ifstream infile1, infile2, infile3;
		string filename;
		filename = "E:\\Biyesheji\\Detection\\Detection\\match corner\\";
		infile1.open(filename + "result12(1&2&3).txt", ios::in);
		infile2.open(filename + "result22(1&2&3).txt", ios::in);
		infile3.open(filename + "result32(1&2&3).txt", ios::in);//导入目标角点坐标
		double x1[200], y1[200], x2[200], y2[200], x3[200], y3[200];
		while (!infile1.eof()) {
			for (int j = 0; j < 66; j++) {
				infile1 >> x1[j] >> y1[j];
			}
		}
		while (!infile2.eof()) {
			for (int j = 0; j < 66; j++) {
				infile2 >> x2[j] >> y2[j];
			}
		}
		while (!infile3.eof()) {
			for (int j = 0; j < 66; j++) {
				infile3 >> x3[j] >> y3[j];
			}
		}
		if (i % 2 != 0) {
			GoodFeaturesToTrackDetector Detector(4);
			Detector.detect(roi1, keyPoint1);
			while (keyPoint1.size() != 4) {
				keyPoint1.push_back(keyPoints1[0]);
			}
			int p = (i - 22) / 2;
			keyPoint1[0].pt.x = x1[6 * p + 2] - a; keyPoint1[0].pt.y = y1[6 * p + 2] - b;
			keyPoint1[1].pt.x = x1[6 * p + 3] - a; keyPoint1[1].pt.y = y1[6 * p + 3] - b;
			keyPoint1[2].pt.x = x1[6 * p + 4] - a; keyPoint1[2].pt.y = y1[6 * p + 4] - b;
			keyPoint1[3].pt.x = x1[6 * p + 5] - a; keyPoint1[3].pt.y = y1[6 * p + 5] - b;
			if (keyPoint1[0].pt.x >= keyPoint1[1].pt.x&&keyPoint1[0].pt.x >= keyPoint1[1].pt.x&&keyPoint1[0].pt.x >= keyPoint1[3].pt.x) {
				keyPoint1[0].class_id = 1;
				if (keyPoint1[1].pt.x >= keyPoint1[2].pt.x&&keyPoint1[1].pt.x >= keyPoint1[3].pt.x) {
					keyPoint1[1].class_id = 2;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 3;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 3;
						keyPoint1[2].class_id = 4;
					}
				}
				else if (keyPoint1[1].pt.x <= keyPoint1[2].pt.x&&keyPoint1[1].pt.x <= keyPoint1[3].pt.x) {
					keyPoint1[1].class_id = 4;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 2;
						keyPoint1[3].class_id = 3;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 3;
					}
				}
				else {
					keyPoint1[1].class_id = 3;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 2;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 4;
					}
				}
			}
			else if (keyPoint1[1].pt.x >= keyPoint1[0].pt.x&&keyPoint1[1].pt.x >= keyPoint1[2].pt.x&&keyPoint1[1].pt.x >= keyPoint1[3].pt.x) {
				keyPoint1[1].class_id = 1;
				if (keyPoint1[0].pt.x >= keyPoint1[2].pt.x&&keyPoint1[0].pt.x >= keyPoint1[3].pt.x) {
					keyPoint1[0].class_id = 2;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 3;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 3;
						keyPoint1[2].class_id = 4;
					}
				}
				else if (keyPoint1[0].pt.x <= keyPoint1[2].pt.x&&keyPoint1[01].pt.x <= keyPoint1[3].pt.x) {
					keyPoint1[0].class_id = 4;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 2;
						keyPoint1[3].class_id = 3;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 3;
					}
				}
				else {
					keyPoint1[0].class_id = 3;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 2;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 4;
					}
				}
			}
			else if (keyPoint1[2].pt.x >= keyPoint1[0].pt.x&&keyPoint1[2].pt.x >= keyPoint1[1].pt.x&&keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
				keyPoint1[2].class_id = 1;
				if (keyPoint1[0].pt.x >= keyPoint1[1].pt.x&&keyPoint1[0].pt.x >= keyPoint1[3].pt.x) {
					keyPoint1[0].class_id = 2;
					if (keyPoint1[1].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[1].class_id = 3;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 3;
						keyPoint1[1].class_id = 4;
					}
				}
				else if (keyPoint1[0].pt.x <= keyPoint1[1].pt.x&&keyPoint1[0].pt.x <= keyPoint1[3].pt.x) {
					keyPoint1[0].class_id = 4;
					if (keyPoint1[1].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[1].class_id = 2;
						keyPoint1[3].class_id = 3;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[1].class_id = 3;
					}
				}
				else {
					keyPoint1[0].class_id = 3;
					if (keyPoint1[1].pt.x > keyPoint1[3].pt.x) {
						keyPoint1[1].class_id = 2;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[1].class_id = 4;
					}
				}
			}
			else if (keyPoint1[3].pt.x >= keyPoint1[0].pt.x&&keyPoint1[3].pt.x >= keyPoint1[1].pt.x&&keyPoint1[3].pt.x >= keyPoint1[2].pt.x) {
				keyPoint1[3].class_id = 1;
				if (keyPoint1[0].pt.x >= keyPoint1[1].pt.x&&keyPoint1[0].pt.x >= keyPoint1[2].pt.x) {
					keyPoint1[0].class_id = 2;
					if (keyPoint1[1].pt.x >= keyPoint1[2].pt.x) {
						keyPoint1[1].class_id = 3;
						keyPoint1[2].class_id = 4;
					}
					else {
						keyPoint1[2].class_id = 3;
						keyPoint1[1].class_id = 4;
					}
				}
				else if (keyPoint1[0].pt.x <= keyPoint1[1].pt.x&&keyPoint1[0].pt.x <= keyPoint1[2].pt.x) {
					keyPoint1[0].class_id = 4;
					if (keyPoint1[1].pt.x >= keyPoint1[2].pt.x) {
						keyPoint1[1].class_id = 2;
						keyPoint1[2].class_id = 3;
					}
					else {
						keyPoint1[2].class_id = 2;
						keyPoint1[1].class_id = 3;
					}
				}
				else {
					keyPoint1[0].class_id = 3;
					if (keyPoint1[1].pt.x >= keyPoint1[2].pt.x) {
						keyPoint1[1].class_id = 2;
						keyPoint1[2].class_id = 4;
					}
					else {
						keyPoint1[2].class_id = 2;
						keyPoint1[1].class_id = 4;
					}
				}
			}
			for (int k = 0; k < 4; k++) {
				for (int j = k + 1; j < 4; j++) {
					if (keyPoint1[k].pt.x == keyPoint1[j].pt.x) {
						int max = keyPoint1[k].class_id;
						if (keyPoint1[k].pt.y > keyPoint1[j].pt.y&&keyPoint2[k].class_id < keyPoint1[j].class_id) {
							keyPoint1[j].class_id = keyPoint1[j].class_id;
							keyPoint1[k].class_id = max;
						}
						else if (keyPoint1[k].pt.y < keyPoint1[j].pt.y&&keyPoint1[k].class_id < keyPoint1[j].class_id) {
							keyPoint1[k].class_id = keyPoint1[j].class_id;
							keyPoint1[j].class_id = max;
						}
						else if (keyPoint1[k].pt.y > keyPoint1[j].pt.y&&keyPoint1[k].class_id > keyPoint1[j].class_id) {
							keyPoint1[k].class_id = keyPoint1[j].class_id;
							keyPoint1[j].class_id = max;
						}
						else if (keyPoint1[k].pt.y < keyPoint1[j].pt.y&&keyPoint1[k].class_id > keyPoint1[j].class_id) {
							keyPoint1[j].class_id = keyPoint1[j].class_id;
							keyPoint1[k].class_id = max;
						}
					}
				}
			}

			Detector.detect(roi2, keyPoint2);
			while (keyPoint2.size() != 4) {
				keyPoint2.push_back(keyPoints2[0]);
			}
			keyPoint2[0].pt.x = x2[6 * p + 2] - e; keyPoint2[0].pt.y = y2[6 * p + 2] - f;
			keyPoint2[1].pt.x = x2[6 * p + 3] - e; keyPoint2[1].pt.y = y2[6 * p + 3] - f;
			keyPoint2[2].pt.x = x2[6 * p + 4] - e; keyPoint2[2].pt.y = y2[6 * p + 4] - f;
			keyPoint2[3].pt.x = x2[6 * p + 5] - e; keyPoint2[3].pt.y = y2[6 * p + 5] - f;
			if (keyPoint2[0].pt.x >= keyPoint2[1].pt.x&&keyPoint2[0].pt.x >= keyPoint2[2].pt.x&&keyPoint2[0].pt.x >= keyPoint2[3].pt.x) {
				keyPoint2[0].class_id = 1;
				if (keyPoint2[1].pt.x >= keyPoint2[2].pt.x&&keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
					keyPoint2[1].class_id = 2;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 3;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 3;
						keyPoint2[2].class_id = 4;
					}
				}
				else if (keyPoint2[1].pt.x <= keyPoint2[2].pt.x&&keyPoint2[1].pt.x <= keyPoint2[3].pt.x) {
					keyPoint2[1].class_id = 4;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 2;
						keyPoint2[3].class_id = 3;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[2].class_id = 3;
					}
				}
				else {
					keyPoint2[1].class_id = 3;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 2;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[2].class_id = 4;
					}
				}
			}
			else if (keyPoint2[1].pt.x >= keyPoint2[0].pt.x&&keyPoint2[1].pt.x >= keyPoint2[2].pt.x&&keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
				keyPoint2[1].class_id = 1;
				if (keyPoint2[0].pt.x >= keyPoint2[2].pt.x&&keyPoint2[0].pt.x >= keyPoint2[3].pt.x) {
					keyPoint2[0].class_id = 2;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 3;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 3;
						keyPoint2[2].class_id = 4;
					}
				}
				else if (keyPoint2[0].pt.x <= keyPoint2[2].pt.x&&keyPoint1[01].pt.x <= keyPoint2[3].pt.x) {
					keyPoint2[0].class_id = 4;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 2;
						keyPoint2[3].class_id = 3;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[2].class_id = 3;
					}
				}
				else {
					keyPoint2[0].class_id = 3;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 2;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 4;
					}
				}
			}
			else if (keyPoint2[2].pt.x >= keyPoint2[0].pt.x&&keyPoint2[2].pt.x >= keyPoint2[1].pt.x&&keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
				keyPoint2[2].class_id = 1;
				if (keyPoint2[0].pt.x >= keyPoint2[1].pt.x&&keyPoint2[0].pt.x >= keyPoint2[3].pt.x) {
					keyPoint2[0].class_id = 2;
					if (keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[1].class_id = 3;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 3;
						keyPoint2[1].class_id = 4;
					}
				}
				else if (keyPoint2[0].pt.x <= keyPoint2[1].pt.x&&keyPoint2[0].pt.x <= keyPoint2[3].pt.x) {
					keyPoint2[0].class_id = 4;
					if (keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[1].class_id = 2;
						keyPoint2[3].class_id = 3;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[1].class_id = 3;
					}
				}
				else {
					keyPoint2[0].class_id = 3;
					if (keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[1].class_id = 2;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[1].class_id = 4;
					}
				}
			}
			else if (keyPoint2[3].pt.x >= keyPoint2[0].pt.x&&keyPoint2[3].pt.x >= keyPoint2[1].pt.x&&keyPoint2[3].pt.x >= keyPoint2[2].pt.x) {
				keyPoint2[3].class_id = 1;
				if (keyPoint2[0].pt.x >= keyPoint2[1].pt.x&&keyPoint2[0].pt.x >= keyPoint2[2].pt.x) {
					keyPoint2[0].class_id = 2;
					if (keyPoint2[1].pt.x >= keyPoint2[2].pt.x) {
						keyPoint2[1].class_id = 3;
						keyPoint2[2].class_id = 4;
					}
					else {
						keyPoint2[2].class_id = 3;
						keyPoint2[1].class_id = 4;
					}
				}
				else if (keyPoint2[0].pt.x <= keyPoint2[1].pt.x&&keyPoint2[0].pt.x <= keyPoint2[2].pt.x) {
					keyPoint2[0].class_id = 4;
					if (keyPoint2[1].pt.x >= keyPoint2[2].pt.x) {
						keyPoint2[1].class_id = 2;
						keyPoint2[2].class_id = 3;
					}
					else {
						keyPoint2[2].class_id = 2;
						keyPoint2[1].class_id = 3;
					}
				}
				else {
					keyPoint2[0].class_id = 3;
					if (keyPoint2[1].pt.x >= keyPoint2[2].pt.x) {
						keyPoint2[1].class_id = 2;
						keyPoint2[2].class_id = 4;
					}
					else {
						keyPoint2[2].class_id = 2;
						keyPoint2[1].class_id = 4;
					}
				}
			}
			for (int k = 0; k < 4; k++) {
				for (int j = k + 1; j < 4; j++) {
					if (keyPoint2[k].pt.x == keyPoint2[j].pt.x) {
						int max = keyPoint2[k].class_id;
						if (keyPoint2[k].pt.y > keyPoint2[j].pt.y&&keyPoint2[k].class_id < keyPoint2[j].class_id) {
							keyPoint2[j].class_id = keyPoint2[j].class_id;
							keyPoint2[k].class_id = max;
						}
						else if (keyPoint2[k].pt.y < keyPoint2[j].pt.y&&keyPoint2[k].class_id < keyPoint2[j].class_id) {
							keyPoint2[k].class_id = keyPoint2[j].class_id;
							keyPoint2[j].class_id = max;
						}
						else if (keyPoint2[k].pt.y > keyPoint2[j].pt.y&&keyPoint2[k].class_id > keyPoint2[j].class_id) {
							keyPoint2[k].class_id = keyPoint2[j].class_id;
							keyPoint2[j].class_id = max;
						}
						else if (keyPoint2[k].pt.y < keyPoint2[j].pt.y&&keyPoint2[k].class_id > keyPoint2[j].class_id) {
							keyPoint2[j].class_id = keyPoint2[j].class_id;
							keyPoint2[k].class_id = max;
						}
					}
				}
			}

			Detector.detect(roi3, keyPoint3);
			while (keyPoint3.size() != 4) {
				keyPoint3.push_back(keyPoints2[0]);
			}
			keyPoint3[0].pt.x = x2[6 * p + 2] - c; keyPoint3[0].pt.y = y2[6 * p + 2] - d;
			keyPoint3[1].pt.x = x2[6 * p + 3] - c; keyPoint3[1].pt.y = y2[6 * p + 3] - d;
			keyPoint3[2].pt.x = x2[6 * p + 4] - c; keyPoint3[2].pt.y = y2[6 * p + 4] - d;
			keyPoint3[3].pt.x = x2[6 * p + 5] - c; keyPoint3[3].pt.y = y2[6 * p + 5] - d;
			if (keyPoint3[0].pt.x >= keyPoint3[1].pt.x&&keyPoint3[0].pt.x >= keyPoint3[2].pt.x&&keyPoint3[0].pt.x >= keyPoint3[3].pt.x) {
				keyPoint3[0].class_id = 1;
				if (keyPoint3[1].pt.x >= keyPoint3[2].pt.x&&keyPoint3[1].pt.x >= keyPoint3[3].pt.x) {
					keyPoint3[1].class_id = 2;
					if (keyPoint3[2].pt.x >= keyPoint3[3].pt.x) {
						keyPoint3[2].class_id = 3;
						keyPoint3[3].class_id = 4;
					}
					else {
						keyPoint3[3].class_id = 3;
						keyPoint3[2].class_id = 4;
					}
				}
				else if (keyPoint3[1].pt.x <= keyPoint3[2].pt.x&&keyPoint3[1].pt.x <= keyPoint3[3].pt.x) {
					keyPoint3[1].class_id = 4;
					if (keyPoint3[2].pt.x >= keyPoint3[3].pt.x) {
						keyPoint3[2].class_id = 2;
						keyPoint3[3].class_id = 3;
					}
					else {
						keyPoint3[3].class_id = 2;
						keyPoint3[2].class_id = 3;
					}
				}
				else {
					keyPoint3[1].class_id = 3;
					if (keyPoint3[2].pt.x >= keyPoint3[3].pt.x) {
						keyPoint3[2].class_id = 2;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint3[3].class_id = 2;
						keyPoint3[2].class_id = 4;
					}
				}
			}
			else if (keyPoint3[1].pt.x >= keyPoint3[0].pt.x&&keyPoint3[1].pt.x >= keyPoint3[2].pt.x&&keyPoint3[1].pt.x >= keyPoint3[3].pt.x) {
				keyPoint3[1].class_id = 1;
				if (keyPoint3[0].pt.x >= keyPoint3[2].pt.x&&keyPoint3[0].pt.x >= keyPoint3[3].pt.x) {
					keyPoint3[0].class_id = 2;
					if (keyPoint3[2].pt.x >= keyPoint3[3].pt.x) {
						keyPoint3[2].class_id = 3;
						keyPoint3[3].class_id = 4;
					}
					else {
						keyPoint3[3].class_id = 3;
						keyPoint3[2].class_id = 4;
					}
				}
				else if (keyPoint3[0].pt.x <= keyPoint3[2].pt.x&&keyPoint1[01].pt.x <= keyPoint3[3].pt.x) {
					keyPoint3[0].class_id = 4;
					if (keyPoint3[2].pt.x >= keyPoint3[3].pt.x) {
						keyPoint3[2].class_id = 2;
						keyPoint3[3].class_id = 3;
					}
					else {
						keyPoint3[3].class_id = 2;
						keyPoint3[2].class_id = 3;
					}
				}
				else {
					keyPoint3[0].class_id = 3;
					if (keyPoint3[2].pt.x >= keyPoint3[3].pt.x) {
						keyPoint3[2].class_id = 2;
						keyPoint3[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 4;
					}
				}
			}
			else if (keyPoint3[2].pt.x >= keyPoint3[0].pt.x&&keyPoint3[2].pt.x >= keyPoint3[1].pt.x&&keyPoint3[2].pt.x >= keyPoint3[3].pt.x) {
				keyPoint3[2].class_id = 1;
				if (keyPoint3[0].pt.x >= keyPoint3[1].pt.x&&keyPoint3[0].pt.x >= keyPoint3[3].pt.x) {
					keyPoint3[0].class_id = 2;
					if (keyPoint3[1].pt.x >= keyPoint3[3].pt.x) {
						keyPoint3[1].class_id = 3;
						keyPoint3[3].class_id = 4;
					}
					else {
						keyPoint3[3].class_id = 3;
						keyPoint3[1].class_id = 4;
					}
				}
				else if (keyPoint3[0].pt.x <= keyPoint3[1].pt.x&&keyPoint3[0].pt.x <= keyPoint3[3].pt.x) {
					keyPoint3[0].class_id = 4;
					if (keyPoint3[1].pt.x >= keyPoint3[3].pt.x) {
						keyPoint3[1].class_id = 2;
						keyPoint3[3].class_id = 3;
					}
					else {
						keyPoint3[3].class_id = 2;
						keyPoint3[1].class_id = 3;
					}
				}
				else {
					keyPoint3[0].class_id = 3;
					if (keyPoint3[1].pt.x >= keyPoint3[3].pt.x) {
						keyPoint3[1].class_id = 2;
						keyPoint3[3].class_id = 4;
					}
					else {
						keyPoint3[3].class_id = 2;
						keyPoint3[1].class_id = 4;
					}
				}
			}
			else if (keyPoint3[3].pt.x >= keyPoint3[0].pt.x&&keyPoint3[3].pt.x >= keyPoint3[1].pt.x&&keyPoint3[3].pt.x >= keyPoint3[2].pt.x) {
				keyPoint3[3].class_id = 1;
				if (keyPoint3[0].pt.x >= keyPoint3[1].pt.x&&keyPoint3[0].pt.x >= keyPoint3[2].pt.x) {
					keyPoint3[0].class_id = 2;
					if (keyPoint3[1].pt.x >= keyPoint3[2].pt.x) {
						keyPoint3[1].class_id = 3;
						keyPoint3[2].class_id = 4;
					}
					else {
						keyPoint3[2].class_id = 3;
						keyPoint3[1].class_id = 4;
					}
				}
				else if (keyPoint3[0].pt.x <= keyPoint3[1].pt.x&&keyPoint3[0].pt.x <= keyPoint3[2].pt.x) {
					keyPoint3[0].class_id = 4;
					if (keyPoint3[1].pt.x >= keyPoint3[2].pt.x) {
						keyPoint3[1].class_id = 2;
						keyPoint3[2].class_id = 3;
					}
					else {
						keyPoint3[2].class_id = 2;
						keyPoint3[1].class_id = 3;
					}
				}
				else {
					keyPoint3[0].class_id = 3;
					if (keyPoint3[1].pt.x >= keyPoint3[2].pt.x) {
						keyPoint3[1].class_id = 2;
						keyPoint3[2].class_id = 4;
					}
					else {
						keyPoint3[2].class_id = 2;
						keyPoint3[1].class_id = 4;
					}
				}
			}
			for (int k = 0; k < 4; k++) {
				for (int j = k + 1; j < 4; j++) {
					if (keyPoint3[k].pt.x == keyPoint3[j].pt.x) {
						int max = keyPoint3[k].class_id;
						if (keyPoint3[k].pt.y > keyPoint3[j].pt.y&&keyPoint3[k].class_id < keyPoint3[j].class_id) {
							keyPoint3[j].class_id = keyPoint3[j].class_id;
							keyPoint3[k].class_id = max;
						}
						else if (keyPoint3[k].pt.y < keyPoint3[j].pt.y&&keyPoint3[k].class_id < keyPoint3[j].class_id) {
							keyPoint3[k].class_id = keyPoint3[j].class_id;
							keyPoint3[j].class_id = max;
						}
						else if (keyPoint3[k].pt.y > keyPoint3[j].pt.y&&keyPoint3[k].class_id > keyPoint3[j].class_id) {
							keyPoint3[k].class_id = keyPoint3[j].class_id;
							keyPoint3[j].class_id = max;
						}
						else if (keyPoint3[k].pt.y < keyPoint3[j].pt.y&&keyPoint3[k].class_id > keyPoint3[j].class_id) {
							keyPoint3[j].class_id = keyPoint3[j].class_id;
							keyPoint3[k].class_id = max;
						}
					}
				}
			}

		}
		else if (i % 2 == 0) {
			int p = (i - 22) / 2;
			GoodFeaturesToTrackDetector Detector(2);
			Detector.detect(roi1, keyPoint1);
			if (keyPoint1.size() != 2) {
				keyPoints1[0].pt.x = x1[p * 2 + 1] - e; keyPoint2[0].pt.y = y1[p * 2 + 1] - f;
				keyPoint1.push_back(keyPoints2[0]);
			}
			keyPoint1[0].pt.x = x1[6 * p] - a; keyPoint1[0].pt.y = y1[6 * p] - b;
			keyPoint1[1].pt.x = x1[6 * p + 1] - a; keyPoint1[1].pt.y = y1[6 * p + 1] - b;
			if (keyPoint1[0].pt.x < keyPoint1[1].pt.x) {
				keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
			}
			else if (keyPoint1[0].pt.x > keyPoint1[1].pt.x) {
				keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
			}
			else if (keyPoint1[0].pt.x == keyPoint1[1].pt.x) {
				if (keyPoint1[0].pt.y > keyPoint1[1].pt.y) {
					keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
				}
				else
					keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
			}

			Detector.detect(roi2, keyPoint2);
			if (keyPoint2.size() != 2) {
				keyPoints2[0].pt.x = x2[p * 2 + 1] - e; keyPoint2[0].pt.y = y2[p * 2 + 1] - f;
				keyPoint2.push_back(keyPoints2[0]);
			}
			keyPoint2[0].pt.x = x2[6 * p] - e; keyPoint2[0].pt.y = y2[6 * p] - f;
			keyPoint2[1].pt.x = x2[6 * p + 1] - e; keyPoint2[1].pt.y = y2[6 * p + 1] - f;
			if (keyPoint2[0].pt.x < keyPoint2[1].pt.x) {
				keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
			}
			else if (keyPoint2[0].pt.x > keyPoint2[1].pt.x) {
				keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
			}
			else if (keyPoint2[0].pt.x == keyPoint2[1].pt.x) {
				if (keyPoint2[0].pt.y > keyPoint2[1].pt.y) {
					keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
				}
				else
					keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
			}

			Detector.detect(roi3, keyPoint3);
			if (keyPoint3.size() != 2) {
				keyPoints2[0].pt.x = x2[p * 2 + 1] - i; keyPoint3[0].pt.y = y2[p * 2 + 1] - d;
				keyPoint3.push_back(keyPoints2[0]);
			}
			keyPoint3[0].pt.x = x2[6 * p] - c; keyPoint3[0].pt.y = y2[6 * p] - d;
			keyPoint3[1].pt.x = x2[6 * p + 1] - c; keyPoint3[1].pt.y = y2[6 * p + 1] - d;
			if (keyPoint3[0].pt.x < keyPoint3[1].pt.x) {
				keyPoint3[0].class_id = 1;  keyPoint3[1].class_id = 2;
			}
			else if (keyPoint3[0].pt.x > keyPoint3[1].pt.x) {
				keyPoint3[0].class_id = 2;  keyPoint3[1].class_id = 1;
			}
			else if (keyPoint3[0].pt.x == keyPoint3[1].pt.x) {
				if (keyPoint3[0].pt.y > keyPoint3[1].pt.y) {
					keyPoint3[0].class_id = 1;  keyPoint3[1].class_id = 2;
				}
				else
					keyPoint3[0].class_id = 2;  keyPoint3[1].class_id = 1;
			}

		}
	}

	else if (i >= 44 && i < 77) {
		int p = i - 44;
		ifstream infile1, infile2, infile3;
		string filename;
		filename = "E:\\Biyesheji\\Detection\\Detection\\match corner\\";
		infile1.open(filename + "result13(1&2&3).txt", ios::in);
		infile2.open(filename + "result23(1&2&3).txt", ios::in);
		infile3.open(filename + "result33(1&2&3).txt", ios::in);//导入目标角点坐标
		double x1[200], y1[200], x2[200], y2[200], x3[200], y3[200];
		while (!infile1.eof()) {
			for (int j = 0; j < 33; j++)
			{
				infile1 >> x1[j] >> y1[j];
			}
		}
		while (!infile2.eof()) {
			for (int j = 0; j < 33; j++)
			{
				infile2 >> x2[j] >> y2[j];
			}
		}
		while (!infile3.eof()) {
			for (int j = 0; j < 33; j++)
			{
				infile3 >> x3[j] >> y3[j];
			}
		}
		GoodFeaturesToTrackDetector Detector(1);
		Detector.detect(roi1, keyPoint1);
		Detector.detect(roi2, keyPoint2);
		Detector.detect(roi3, keyPoint3);
		keyPoint1[0].pt.x = x1[p] - a; keyPoint1[0].pt.y = y1[p] - b;
		keyPoint2[0].pt.x = x2[p] - e; keyPoint2[0].pt.y = y2[p] - f;
		keyPoint3[0].pt.x = x3[p] - c; keyPoint3[0].pt.y = y3[p] - d;
		keyPoint1[0].class_id = i;
		keyPoint2[0].class_id = i;
		keyPoint3[0].class_id = i;
	}

	else if (i >= 77 && i < 85) {
		ifstream infile1, infile2, infile3;
		string filename;
		filename = "E:\\Biyesheji\\Detection\\Detection\\match corner\\";
		infile1.open(filename + "result14(1&2&3).txt", ios::in);
		infile2.open(filename + "result24(1&2&3).txt", ios::in);
		infile3.open(filename + "result34(1&2&3).txt", ios::in);//导入目标角点坐标
		double x1[200], y1[200], x2[200], y2[200], x3[200], y3[200];
		while (!infile1.eof()) {
			for (int j = 0; j < 16; j++)
			{
				infile1 >> x1[j] >> y1[j];
			}
		}
		while (!infile2.eof()) {
			for (int j = 0; j < 16; j++)
			{
				infile2 >> x2[j] >> y2[j];
			}
		}
		while (!infile3.eof()) {
			for (int j = 0; j < 16; j++)
			{
				infile3 >> x3[j] >> y3[j];
			}
		}
		int p = i - 77;
		GoodFeaturesToTrackDetector Detector(2);
		Detector.detect(roi1, keyPoint1);
		if (keyPoint1.size() != 2) {
			keyPoints1[0].pt.x = x1[p * 2 + 1] - e; keyPoint1[0].pt.y = y2[p * 2 + 1] - f;
			keyPoint1.push_back(keyPoints1[0]);
		}
		keyPoint1[0].pt.x = x1[p * 2] - a; keyPoint1[0].pt.y = y1[p * 2] - b;
		keyPoint1[1].pt.x = x1[p * 2 + 1] - a; keyPoint1[1].pt.y = y1[p * 2 + 1] - b;
		if (keyPoint1[0].pt.x < keyPoint1[1].pt.x) {
			keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
		}
		else if (keyPoint1[0].pt.x > keyPoint1[1].pt.x) {
			keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
		}
		else if (keyPoint1[0].pt.x == keyPoint1[1].pt.x) {
			if (keyPoint1[0].pt.y > keyPoint1[1].pt.y) {
				keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
			}
			else
				keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
		}

		Detector.detect(roi2, keyPoint2);
		if (keyPoint2.size() != 2) {
			keyPoints2[0].pt.x = x2[p * 2 + 1] - e; keyPoint2[0].pt.y = y2[p * 2 + 1] - f;
			keyPoint2.push_back(keyPoints2[0]);
		}
		keyPoint2[0].pt.x = x2[p * 2] - e; keyPoint2[0].pt.y = y2[p * 2] - f;
		keyPoint2[1].pt.x = x2[p * 2 + 1] - e; keyPoint2[1].pt.y = y2[p * 2 + 1] - f;
		if (keyPoint2[0].pt.x < keyPoint2[1].pt.x) {
			keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
		}
		else if (keyPoint2[0].pt.x > keyPoint2[1].pt.x) {
			keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
		}
		else if (keyPoint2[0].pt.x == keyPoint2[1].pt.x) {
			if (keyPoint2[0].pt.y > keyPoint2[1].pt.y) {
				keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
			}
			else
				keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
		}

		Detector.detect(roi3, keyPoint3);
		if (keyPoint3.size() != 2) {
			keyPoints2[0].pt.x = x3[p * 2 + 1] - c; keyPoint3[0].pt.y = y3[p * 2 + 1] - d;
			keyPoint3.push_back(keyPoints2[0]);
		}
		keyPoint3[0].pt.x = x3[p * 2] - c; keyPoint3[0].pt.y = y3[p * 2] - d;
		keyPoint3[1].pt.x = x3[p * 2 + 1] - c; keyPoint3[1].pt.y = y3[p * 2 + 1] - d;
		if (keyPoint3[0].pt.x < keyPoint3[1].pt.x) {
			keyPoint3[0].class_id = 1;  keyPoint3[1].class_id = 2;
		}
		else if (keyPoint3[0].pt.x > keyPoint3[1].pt.x) {
			keyPoint3[0].class_id = 2;  keyPoint3[1].class_id = 1;
		}
		else if (keyPoint3[0].pt.x == keyPoint3[1].pt.x) {
			if (keyPoint3[0].pt.y > keyPoint3[1].pt.y) {
				keyPoint3[0].class_id = 1;  keyPoint3[1].class_id = 2;
			}
			else
				keyPoint3[0].class_id = 2;  keyPoint3[1].class_id = 1;
		}
	}
}

void MatchPoint1_2_4(int i, vector<int> letters, Mat& roi1, Mat& roi2, Mat& roi3, vector<KeyPoint>& keyPoint1, vector<KeyPoint>& keyPoint2, vector<KeyPoint>& keyPoint3) {
	vector<KeyPoint> keyPoints1(200), keyPoints2(200);//循环前预定义

	int a = letters[0];
	int b = letters[1];
	int e = letters[2];
	int f = letters[3];
	int c = letters[4];
	int d = letters[5];

	if (i<22) {
		ifstream infile1, infile2, infile3;
		string filename;
		filename = "E:\\Biyesheji\\Detection\\Detection\\match corner\\";
		infile1.open(filename + "result11(1&2&4).txt", ios::in);
		infile2.open(filename + "result21(1&2&4).txt", ios::in);
		infile3.open(filename + "result41(1&2&4).txt", ios::in);//导入目标角点坐标
		double x1[200], y1[200], x2[200], y2[200], x3[200], y3[200];
		while (!infile1.eof()) {
			for (int j = 0; j < 44; j++)
			{
				infile1 >> x1[j] >> y1[j];
			}
		}
		while (!infile2.eof()) {
			for (int j = 0; j < 44; j++)
			{
				infile2 >> x2[j] >> y2[j];
			}
		}
		while (!infile3.eof()) {
			for (int j = 0; j < 44; j++)
			{
				infile3 >> x3[j] >> y3[j];
			}
		}
		GoodFeaturesToTrackDetector Detector(2);
		Detector.detect(roi1, keyPoint1);   //检测角点
		while (keyPoint1.size() != 2) {
			keyPoint1.push_back(keyPoints1[0]);
		}
		keyPoint1[0].pt.x = x1[2 * i] - a; keyPoint1[0].pt.y = y1[2 * i] - b;
		keyPoint1[1].pt.x = x1[2 * i + 1] - a; keyPoint1[1].pt.y = y1[2 * i + 1] - b;    //目标角点在区域内坐标
		if (keyPoint1[0].pt.x < keyPoint1[1].pt.x) {
			keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
		}
		else if (keyPoint1[0].pt.x > keyPoint1[1].pt.x) {
			keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
		}
		else if (keyPoint1[0].pt.x == keyPoint1[1].pt.x) {
			if (keyPoint1[0].pt.y > keyPoint1[1].pt.y) {
				keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
			}
			else
				keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
		}                                                             //进行角点分类

		Detector.detect(roi2, keyPoint2);
		while (keyPoint2.size() != 2) {
			keyPoint2.push_back(keyPoints2[0]);
		}
		keyPoint2[0].pt.x = x2[2 * i] - e; keyPoint2[0].pt.y = y2[2 * i] - f;
		keyPoint2[1].pt.x = x2[2 * i + 1] - e; keyPoint2[1].pt.y = y2[2 * i + 1] - f;
		if (keyPoint2[0].pt.x < keyPoint2[1].pt.x) {
			keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
		}
		else if (keyPoint2[0].pt.x > keyPoint2[1].pt.x) {
			keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
		}
		else if (keyPoint2[0].pt.x == keyPoint2[1].pt.x) {
			if (keyPoint2[0].pt.y > keyPoint2[1].pt.y) {
				keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
			}
			else
				keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
		}

		Detector.detect(roi3, keyPoint3);
		while (keyPoint3.size() != 2) {
			keyPoint3.push_back(keyPoints2[0]);
		}
		keyPoint3[0].pt.x = x3[2 * i] - c; keyPoint3[0].pt.y = y3[2 * i] - d;
		keyPoint3[1].pt.x = x3[2 * i + 1] - c; keyPoint3[1].pt.y = y3[2 * i + 1] - d;
		if (keyPoint3[0].pt.x < keyPoint3[1].pt.x) {
			keyPoint3[0].class_id = 1;  keyPoint3[1].class_id = 2;
		}
		else if (keyPoint3[0].pt.x > keyPoint3[1].pt.x) {
			keyPoint3[0].class_id = 2;  keyPoint3[1].class_id = 1;
		}
		else if (keyPoint3[0].pt.x == keyPoint3[1].pt.x) {
			if (keyPoint3[0].pt.y > keyPoint3[1].pt.y) {
				keyPoint3[0].class_id = 1;  keyPoint3[1].class_id = 2;
			}
			else
				keyPoint3[0].class_id = 2;  keyPoint3[1].class_id = 1;
		}
	}

	else if (i >= 22 && i < 44) {
		ifstream infile1, infile2, infile3;
		string filename;
		filename = "E:\\Biyesheji\\Detection\\Detection\\match corner\\";
		infile1.open(filename + "result12(1&2&4).txt", ios::in);
		infile2.open(filename + "result22(1&2&4).txt", ios::in);
		infile3.open(filename + "result42(1&2&4).txt", ios::in);//导入目标角点坐标
		double x1[200], y1[200], x2[200], y2[200], x3[200], y3[200];
		while (!infile1.eof()) {
			for (int j = 0; j < 66; j++) {
				infile1 >> x1[j] >> y1[j];
			}
		}
		while (!infile2.eof()) {
			for (int j = 0; j < 66; j++) {
				infile2 >> x2[j] >> y2[j];
			}
		}
		while (!infile3.eof()) {
			for (int j = 0; j < 72; j++) {
				infile3 >> x3[j] >> y3[j];
			}
		}
		if (i % 2 == 0) {
			GoodFeaturesToTrackDetector Detector(4);
			Detector.detect(roi1, keyPoint1);
			while (keyPoint1.size() != 4) {
				keyPoint1.push_back(keyPoints1[0]);
			}
			int p = (i - 22) / 2;
			keyPoint1[0].pt.x = x1[6 * p] - a; keyPoint1[0].pt.y = y1[6 * p] - b;
			keyPoint1[1].pt.x = x1[6 * p + 1] - a; keyPoint1[1].pt.y = y1[6 * p + 1] - b;
			keyPoint1[2].pt.x = x1[6 * p + 2] - a; keyPoint1[2].pt.y = y1[6 * p + 2] - b;
			keyPoint1[3].pt.x = x1[6 * p + 3] - a; keyPoint1[3].pt.y = y1[6 * p + 3] - b;
			if (keyPoint1[0].pt.x >= keyPoint1[1].pt.x&&keyPoint1[0].pt.x >= keyPoint1[1].pt.x&&keyPoint1[0].pt.x >= keyPoint1[3].pt.x) {
				keyPoint1[0].class_id = 1;
				if (keyPoint1[1].pt.x >= keyPoint1[2].pt.x&&keyPoint1[1].pt.x >= keyPoint1[3].pt.x) {
					keyPoint1[1].class_id = 2;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 3;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 3;
						keyPoint1[2].class_id = 4;
					}
				}
				else if (keyPoint1[1].pt.x <= keyPoint1[2].pt.x&&keyPoint1[1].pt.x <= keyPoint1[3].pt.x) {
					keyPoint1[1].class_id = 4;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 2;
						keyPoint1[3].class_id = 3;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 3;
					}
				}
				else {
					keyPoint1[1].class_id = 3;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 2;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 4;
					}
				}
			}
			else if (keyPoint1[1].pt.x >= keyPoint1[0].pt.x&&keyPoint1[1].pt.x >= keyPoint1[2].pt.x&&keyPoint1[1].pt.x >= keyPoint1[3].pt.x) {
				keyPoint1[1].class_id = 1;
				if (keyPoint1[0].pt.x >= keyPoint1[2].pt.x&&keyPoint1[0].pt.x >= keyPoint1[3].pt.x) {
					keyPoint1[0].class_id = 2;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 3;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 3;
						keyPoint1[2].class_id = 4;
					}
				}
				else if (keyPoint1[0].pt.x <= keyPoint1[2].pt.x&&keyPoint1[01].pt.x <= keyPoint1[3].pt.x) {
					keyPoint1[0].class_id = 4;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 2;
						keyPoint1[3].class_id = 3;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 3;
					}
				}
				else {
					keyPoint1[0].class_id = 3;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 2;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 4;
					}
				}
			}
			else if (keyPoint1[2].pt.x >= keyPoint1[0].pt.x&&keyPoint1[2].pt.x >= keyPoint1[1].pt.x&&keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
				keyPoint1[2].class_id = 1;
				if (keyPoint1[0].pt.x >= keyPoint1[1].pt.x&&keyPoint1[0].pt.x >= keyPoint1[3].pt.x) {
					keyPoint1[0].class_id = 2;
					if (keyPoint1[1].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[1].class_id = 3;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 3;
						keyPoint1[1].class_id = 4;
					}
				}
				else if (keyPoint1[0].pt.x <= keyPoint1[1].pt.x&&keyPoint1[0].pt.x <= keyPoint1[3].pt.x) {
					keyPoint1[0].class_id = 4;
					if (keyPoint1[1].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[1].class_id = 2;
						keyPoint1[3].class_id = 3;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[1].class_id = 3;
					}
				}
				else {
					keyPoint1[0].class_id = 3;
					if (keyPoint1[1].pt.x > keyPoint1[3].pt.x) {
						keyPoint1[1].class_id = 2;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[1].class_id = 4;
					}
				}
			}
			else if (keyPoint1[3].pt.x >= keyPoint1[0].pt.x&&keyPoint1[3].pt.x >= keyPoint1[1].pt.x&&keyPoint1[3].pt.x >= keyPoint1[2].pt.x) {
				keyPoint1[3].class_id = 1;
				if (keyPoint1[0].pt.x >= keyPoint1[1].pt.x&&keyPoint1[0].pt.x >= keyPoint1[2].pt.x) {
					keyPoint1[0].class_id = 2;
					if (keyPoint1[1].pt.x >= keyPoint1[2].pt.x) {
						keyPoint1[1].class_id = 3;
						keyPoint1[2].class_id = 4;
					}
					else {
						keyPoint1[2].class_id = 3;
						keyPoint1[1].class_id = 4;
					}
				}
				else if (keyPoint1[0].pt.x <= keyPoint1[1].pt.x&&keyPoint1[0].pt.x <= keyPoint1[2].pt.x) {
					keyPoint1[0].class_id = 4;
					if (keyPoint1[1].pt.x >= keyPoint1[2].pt.x) {
						keyPoint1[1].class_id = 2;
						keyPoint1[2].class_id = 3;
					}
					else {
						keyPoint1[2].class_id = 2;
						keyPoint1[1].class_id = 3;
					}
				}
				else {
					keyPoint1[0].class_id = 3;
					if (keyPoint1[1].pt.x >= keyPoint1[2].pt.x) {
						keyPoint1[1].class_id = 2;
						keyPoint1[2].class_id = 4;
					}
					else {
						keyPoint1[2].class_id = 2;
						keyPoint1[1].class_id = 4;
					}
				}
			}
			for (int k = 0; k < 4; k++) {
				for (int j = k + 1; j < 4; j++) {
					if (keyPoint1[k].pt.x == keyPoint1[j].pt.x) {
						int max = keyPoint1[k].class_id;
						if (keyPoint1[k].pt.y > keyPoint1[j].pt.y&&keyPoint2[k].class_id < keyPoint1[j].class_id) {
							keyPoint1[j].class_id = keyPoint1[j].class_id;
							keyPoint1[k].class_id = max;
						}
						else if (keyPoint1[k].pt.y < keyPoint1[j].pt.y&&keyPoint1[k].class_id < keyPoint1[j].class_id) {
							keyPoint1[k].class_id = keyPoint1[j].class_id;
							keyPoint1[j].class_id = max;
						}
						else if (keyPoint1[k].pt.y > keyPoint1[j].pt.y&&keyPoint1[k].class_id > keyPoint1[j].class_id) {
							keyPoint1[k].class_id = keyPoint1[j].class_id;
							keyPoint1[j].class_id = max;
						}
						else if (keyPoint1[k].pt.y < keyPoint1[j].pt.y&&keyPoint1[k].class_id > keyPoint1[j].class_id) {
							keyPoint1[j].class_id = keyPoint1[j].class_id;
							keyPoint1[k].class_id = max;
						}
					}
				}
			}

			Detector.detect(roi2, keyPoint2);
			while (keyPoint2.size() != 4) {
				keyPoint2.push_back(keyPoints2[0]);
			}
			keyPoint2[0].pt.x = x2[6 * p] - e; keyPoint2[0].pt.y = y2[6 * p] - f;
			keyPoint2[1].pt.x = x2[6 * p + 1] - e; keyPoint2[1].pt.y = y2[6 * p + 1] - f;
			keyPoint2[2].pt.x = x2[6 * p + 2] - e; keyPoint2[2].pt.y = y2[6 * p + 2] - f;
			keyPoint2[3].pt.x = x2[6 * p + 3] - e; keyPoint2[3].pt.y = y2[6 * p + 3] - f;
			if (keyPoint2[0].pt.x >= keyPoint2[1].pt.x&&keyPoint2[0].pt.x >= keyPoint2[2].pt.x&&keyPoint2[0].pt.x >= keyPoint2[3].pt.x) {
				keyPoint2[0].class_id = 1;
				if (keyPoint2[1].pt.x >= keyPoint2[2].pt.x&&keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
					keyPoint2[1].class_id = 2;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 3;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 3;
						keyPoint2[2].class_id = 4;
					}
				}
				else if (keyPoint2[1].pt.x <= keyPoint2[2].pt.x&&keyPoint2[1].pt.x <= keyPoint2[3].pt.x) {
					keyPoint2[1].class_id = 4;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 2;
						keyPoint2[3].class_id = 3;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[2].class_id = 3;
					}
				}
				else {
					keyPoint2[1].class_id = 3;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 2;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[2].class_id = 4;
					}
				}
			}
			else if (keyPoint2[1].pt.x >= keyPoint2[0].pt.x&&keyPoint2[1].pt.x >= keyPoint2[2].pt.x&&keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
				keyPoint2[1].class_id = 1;
				if (keyPoint2[0].pt.x >= keyPoint2[2].pt.x&&keyPoint2[0].pt.x >= keyPoint2[3].pt.x) {
					keyPoint2[0].class_id = 2;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 3;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 3;
						keyPoint2[2].class_id = 4;
					}
				}
				else if (keyPoint2[0].pt.x <= keyPoint2[2].pt.x&&keyPoint1[01].pt.x <= keyPoint2[3].pt.x) {
					keyPoint2[0].class_id = 4;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 2;
						keyPoint2[3].class_id = 3;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[2].class_id = 3;
					}
				}
				else {
					keyPoint2[0].class_id = 3;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 2;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 4;
					}
				}
			}
			else if (keyPoint2[2].pt.x >= keyPoint2[0].pt.x&&keyPoint2[2].pt.x >= keyPoint2[1].pt.x&&keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
				keyPoint2[2].class_id = 1;
				if (keyPoint2[0].pt.x >= keyPoint2[1].pt.x&&keyPoint2[0].pt.x >= keyPoint2[3].pt.x) {
					keyPoint2[0].class_id = 2;
					if (keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[1].class_id = 3;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 3;
						keyPoint2[1].class_id = 4;
					}
				}
				else if (keyPoint2[0].pt.x <= keyPoint2[1].pt.x&&keyPoint2[0].pt.x <= keyPoint2[3].pt.x) {
					keyPoint2[0].class_id = 4;
					if (keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[1].class_id = 2;
						keyPoint2[3].class_id = 3;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[1].class_id = 3;
					}
				}
				else {
					keyPoint2[0].class_id = 3;
					if (keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[1].class_id = 2;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[1].class_id = 4;
					}
				}
			}
			else if (keyPoint2[3].pt.x >= keyPoint2[0].pt.x&&keyPoint2[3].pt.x >= keyPoint2[1].pt.x&&keyPoint2[3].pt.x >= keyPoint2[2].pt.x) {
				keyPoint2[3].class_id = 1;
				if (keyPoint2[0].pt.x >= keyPoint2[1].pt.x&&keyPoint2[0].pt.x >= keyPoint2[2].pt.x) {
					keyPoint2[0].class_id = 2;
					if (keyPoint2[1].pt.x >= keyPoint2[2].pt.x) {
						keyPoint2[1].class_id = 3;
						keyPoint2[2].class_id = 4;
					}
					else {
						keyPoint2[2].class_id = 3;
						keyPoint2[1].class_id = 4;
					}
				}
				else if (keyPoint2[0].pt.x <= keyPoint2[1].pt.x&&keyPoint2[0].pt.x <= keyPoint2[2].pt.x) {
					keyPoint2[0].class_id = 4;
					if (keyPoint2[1].pt.x >= keyPoint2[2].pt.x) {
						keyPoint2[1].class_id = 2;
						keyPoint2[2].class_id = 3;
					}
					else {
						keyPoint2[2].class_id = 2;
						keyPoint2[1].class_id = 3;
					}
				}
				else {
					keyPoint2[0].class_id = 3;
					if (keyPoint2[1].pt.x >= keyPoint2[2].pt.x) {
						keyPoint2[1].class_id = 2;
						keyPoint2[2].class_id = 4;
					}
					else {
						keyPoint2[2].class_id = 2;
						keyPoint2[1].class_id = 4;
					}
				}
			}
			for (int k = 0; k < 4; k++) {
				for (int j = k + 1; j < 4; j++) {
					if (keyPoint2[k].pt.x == keyPoint2[j].pt.x) {
						int max = keyPoint2[k].class_id;
						if (keyPoint2[k].pt.y > keyPoint2[j].pt.y&&keyPoint2[k].class_id < keyPoint2[j].class_id) {
							keyPoint2[j].class_id = keyPoint2[j].class_id;
							keyPoint2[k].class_id = max;
						}
						else if (keyPoint2[k].pt.y < keyPoint2[j].pt.y&&keyPoint2[k].class_id < keyPoint2[j].class_id) {
							keyPoint2[k].class_id = keyPoint2[j].class_id;
							keyPoint2[j].class_id = max;
						}
						else if (keyPoint2[k].pt.y > keyPoint2[j].pt.y&&keyPoint2[k].class_id > keyPoint2[j].class_id) {
							keyPoint2[k].class_id = keyPoint2[j].class_id;
							keyPoint2[j].class_id = max;
						}
						else if (keyPoint2[k].pt.y < keyPoint2[j].pt.y&&keyPoint2[k].class_id > keyPoint2[j].class_id) {
							keyPoint2[j].class_id = keyPoint2[j].class_id;
							keyPoint2[k].class_id = max;
						}
					}
				}
			}

			Detector.detect(roi3, keyPoint3);
			while (keyPoint3.size() != 4) {
				keyPoint3.push_back(keyPoints2[0]);
			}
			keyPoint3[0].pt.x = x2[6 * p] - c; keyPoint3[0].pt.y = y2[6 * p] - d;
			keyPoint3[1].pt.x = x2[6 * p + 1] - c; keyPoint3[1].pt.y = y2[6 * p + 1] - d;
			keyPoint3[2].pt.x = x2[6 * p + 2] - c; keyPoint3[2].pt.y = y2[6 * p + 2] - d;
			keyPoint3[3].pt.x = x2[6 * p + 3] - c; keyPoint3[3].pt.y = y2[6 * p + 3] - d;
			if (keyPoint3[0].pt.x >= keyPoint3[1].pt.x&&keyPoint3[0].pt.x >= keyPoint3[2].pt.x&&keyPoint3[0].pt.x >= keyPoint3[3].pt.x) {
				keyPoint3[0].class_id = 1;
				if (keyPoint3[1].pt.x >= keyPoint3[2].pt.x&&keyPoint3[1].pt.x >= keyPoint3[3].pt.x) {
					keyPoint3[1].class_id = 2;
					if (keyPoint3[2].pt.x >= keyPoint3[3].pt.x) {
						keyPoint3[2].class_id = 3;
						keyPoint3[3].class_id = 4;
					}
					else {
						keyPoint3[3].class_id = 3;
						keyPoint3[2].class_id = 4;
					}
				}
				else if (keyPoint3[1].pt.x <= keyPoint3[2].pt.x&&keyPoint3[1].pt.x <= keyPoint3[3].pt.x) {
					keyPoint3[1].class_id = 4;
					if (keyPoint3[2].pt.x >= keyPoint3[3].pt.x) {
						keyPoint3[2].class_id = 2;
						keyPoint3[3].class_id = 3;
					}
					else {
						keyPoint3[3].class_id = 2;
						keyPoint3[2].class_id = 3;
					}
				}
				else {
					keyPoint3[1].class_id = 3;
					if (keyPoint3[2].pt.x >= keyPoint3[3].pt.x) {
						keyPoint3[2].class_id = 2;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint3[3].class_id = 2;
						keyPoint3[2].class_id = 4;
					}
				}
			}
			else if (keyPoint3[1].pt.x >= keyPoint3[0].pt.x&&keyPoint3[1].pt.x >= keyPoint3[2].pt.x&&keyPoint3[1].pt.x >= keyPoint3[3].pt.x) {
				keyPoint3[1].class_id = 1;
				if (keyPoint3[0].pt.x >= keyPoint3[2].pt.x&&keyPoint3[0].pt.x >= keyPoint3[3].pt.x) {
					keyPoint3[0].class_id = 2;
					if (keyPoint3[2].pt.x >= keyPoint3[3].pt.x) {
						keyPoint3[2].class_id = 3;
						keyPoint3[3].class_id = 4;
					}
					else {
						keyPoint3[3].class_id = 3;
						keyPoint3[2].class_id = 4;
					}
				}
				else if (keyPoint3[0].pt.x <= keyPoint3[2].pt.x&&keyPoint1[01].pt.x <= keyPoint3[3].pt.x) {
					keyPoint3[0].class_id = 4;
					if (keyPoint3[2].pt.x >= keyPoint3[3].pt.x) {
						keyPoint3[2].class_id = 2;
						keyPoint3[3].class_id = 3;
					}
					else {
						keyPoint3[3].class_id = 2;
						keyPoint3[2].class_id = 3;
					}
				}
				else {
					keyPoint3[0].class_id = 3;
					if (keyPoint3[2].pt.x >= keyPoint3[3].pt.x) {
						keyPoint3[2].class_id = 2;
						keyPoint3[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 4;
					}
				}
			}
			else if (keyPoint3[2].pt.x >= keyPoint3[0].pt.x&&keyPoint3[2].pt.x >= keyPoint3[1].pt.x&&keyPoint3[2].pt.x >= keyPoint3[3].pt.x) {
				keyPoint3[2].class_id = 1;
				if (keyPoint3[0].pt.x >= keyPoint3[1].pt.x&&keyPoint3[0].pt.x >= keyPoint3[3].pt.x) {
					keyPoint3[0].class_id = 2;
					if (keyPoint3[1].pt.x >= keyPoint3[3].pt.x) {
						keyPoint3[1].class_id = 3;
						keyPoint3[3].class_id = 4;
					}
					else {
						keyPoint3[3].class_id = 3;
						keyPoint3[1].class_id = 4;
					}
				}
				else if (keyPoint3[0].pt.x <= keyPoint3[1].pt.x&&keyPoint3[0].pt.x <= keyPoint3[3].pt.x) {
					keyPoint3[0].class_id = 4;
					if (keyPoint3[1].pt.x >= keyPoint3[3].pt.x) {
						keyPoint3[1].class_id = 2;
						keyPoint3[3].class_id = 3;
					}
					else {
						keyPoint3[3].class_id = 2;
						keyPoint3[1].class_id = 3;
					}
				}
				else {
					keyPoint3[0].class_id = 3;
					if (keyPoint3[1].pt.x >= keyPoint3[3].pt.x) {
						keyPoint3[1].class_id = 2;
						keyPoint3[3].class_id = 4;
					}
					else {
						keyPoint3[3].class_id = 2;
						keyPoint3[1].class_id = 4;
					}
				}
			}
			else if (keyPoint3[3].pt.x >= keyPoint3[0].pt.x&&keyPoint3[3].pt.x >= keyPoint3[1].pt.x&&keyPoint3[3].pt.x >= keyPoint3[2].pt.x) {
				keyPoint3[3].class_id = 1;
				if (keyPoint3[0].pt.x >= keyPoint3[1].pt.x&&keyPoint3[0].pt.x >= keyPoint3[2].pt.x) {
					keyPoint3[0].class_id = 2;
					if (keyPoint3[1].pt.x >= keyPoint3[2].pt.x) {
						keyPoint3[1].class_id = 3;
						keyPoint3[2].class_id = 4;
					}
					else {
						keyPoint3[2].class_id = 3;
						keyPoint3[1].class_id = 4;
					}
				}
				else if (keyPoint3[0].pt.x <= keyPoint3[1].pt.x&&keyPoint3[0].pt.x <= keyPoint3[2].pt.x) {
					keyPoint3[0].class_id = 4;
					if (keyPoint3[1].pt.x >= keyPoint3[2].pt.x) {
						keyPoint3[1].class_id = 2;
						keyPoint3[2].class_id = 3;
					}
					else {
						keyPoint3[2].class_id = 2;
						keyPoint3[1].class_id = 3;
					}
				}
				else {
					keyPoint3[0].class_id = 3;
					if (keyPoint3[1].pt.x >= keyPoint3[2].pt.x) {
						keyPoint3[1].class_id = 2;
						keyPoint3[2].class_id = 4;
					}
					else {
						keyPoint3[2].class_id = 2;
						keyPoint3[1].class_id = 4;
					}
				}
			}
			for (int k = 0; k < 4; k++) {
				for (int j = k + 1; j < 4; j++) {
					if (keyPoint3[k].pt.x == keyPoint3[j].pt.x) {
						int max = keyPoint3[k].class_id;
						if (keyPoint3[k].pt.y > keyPoint3[j].pt.y&&keyPoint3[k].class_id < keyPoint3[j].class_id) {
							keyPoint3[j].class_id = keyPoint3[j].class_id;
							keyPoint3[k].class_id = max;
						}
						else if (keyPoint3[k].pt.y < keyPoint3[j].pt.y&&keyPoint3[k].class_id < keyPoint3[j].class_id) {
							keyPoint3[k].class_id = keyPoint3[j].class_id;
							keyPoint3[j].class_id = max;
						}
						else if (keyPoint3[k].pt.y > keyPoint3[j].pt.y&&keyPoint3[k].class_id > keyPoint3[j].class_id) {
							keyPoint3[k].class_id = keyPoint3[j].class_id;
							keyPoint3[j].class_id = max;
						}
						else if (keyPoint3[k].pt.y < keyPoint3[j].pt.y&&keyPoint3[k].class_id > keyPoint3[j].class_id) {
							keyPoint3[j].class_id = keyPoint3[j].class_id;
							keyPoint3[k].class_id = max;
						}
					}
				}
			}

		}
		else if (i % 2 != 0) {
			int p = (i - 22) / 2;
			GoodFeaturesToTrackDetector Detector(2);
			Detector.detect(roi1, keyPoint1);
			if (keyPoint1.size() != 2) {
				keyPoints1[0].pt.x = x1[p * 2 + 1] - e; keyPoint2[0].pt.y = y1[p * 2 + 1] - f;
				keyPoint1.push_back(keyPoints2[0]);
			}
			keyPoint1[0].pt.x = x1[6 * p + 4] - a; keyPoint1[0].pt.y = y1[6 * p + 4] - b;
			keyPoint1[1].pt.x = x1[6 * p + 5] - a; keyPoint1[1].pt.y = y1[6 * p + 5] - b;
			if (keyPoint1[0].pt.x < keyPoint1[1].pt.x) {
				keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
			}
			else if (keyPoint1[0].pt.x > keyPoint1[1].pt.x) {
				keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
			}
			else if (keyPoint1[0].pt.x == keyPoint1[1].pt.x) {
				if (keyPoint1[0].pt.y > keyPoint1[1].pt.y) {
					keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
				}
				else
					keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
			}

			Detector.detect(roi2, keyPoint2);
			if (keyPoint2.size() != 2) {
				keyPoints2[0].pt.x = x2[p * 2 + 1] - e; keyPoint2[0].pt.y = y2[p * 2 + 1] - f;
				keyPoint2.push_back(keyPoints2[0]);
			}
			keyPoint2[0].pt.x = x2[6 * p + 4] - e; keyPoint2[0].pt.y = y2[6 * p + 4] - f;
			keyPoint2[1].pt.x = x2[6 * p + 5] - e; keyPoint2[1].pt.y = y2[6 * p + 5] - f;
			if (keyPoint2[0].pt.x < keyPoint2[1].pt.x) {
				keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
			}
			else if (keyPoint2[0].pt.x > keyPoint2[1].pt.x) {
				keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
			}
			else if (keyPoint2[0].pt.x == keyPoint2[1].pt.x) {
				if (keyPoint2[0].pt.y > keyPoint2[1].pt.y) {
					keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
				}
				else
					keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
			}

			Detector.detect(roi3, keyPoint3);
			if (keyPoint3.size() != 2) {
				keyPoints2[0].pt.x = x2[p * 2 + 1] - c; keyPoint3[0].pt.y = y2[p * 2 + 1] - d;
				keyPoint3.push_back(keyPoints2[0]);
			}
			keyPoint3[0].pt.x = x2[6 * p + 4] - c; keyPoint3[0].pt.y = y2[6 * p + 4] - d;
			keyPoint3[1].pt.x = x2[6 * p + 5] - c; keyPoint3[1].pt.y = y2[6 * p + 5] - d;
			if (keyPoint3[0].pt.x < keyPoint3[1].pt.x) {
				keyPoint3[0].class_id = 1;  keyPoint3[1].class_id = 2;
			}
			else if (keyPoint3[0].pt.x > keyPoint3[1].pt.x) {
				keyPoint3[0].class_id = 2;  keyPoint3[1].class_id = 1;
			}
			else if (keyPoint3[0].pt.x == keyPoint3[1].pt.x) {
				if (keyPoint3[0].pt.y > keyPoint3[1].pt.y) {
					keyPoint3[0].class_id = 1;  keyPoint3[1].class_id = 2;
				}
				else
					keyPoint3[0].class_id = 2;  keyPoint3[1].class_id = 1;
			}

		}
	}

	else if (i >= 44 && i < 77) {
		int p = i - 44;
		ifstream infile1, infile2, infile3;
		string filename;
		filename = "E:\\Biyesheji\\Detection\\Detection\\match corner\\";
		infile1.open(filename + "result13(1&2&4).txt", ios::in);
		infile2.open(filename + "result23(1&2&4).txt", ios::in);
		infile3.open(filename + "result43(1&2&4).txt", ios::in);//导入目标角点坐标
		double x1[200], y1[200], x2[200], y2[200], x3[200], y3[200];
		while (!infile1.eof()) {
			for (int j = 0; j < 33; j++)
			{
				infile1 >> x1[j] >> y1[j];
			}
		}
		while (!infile2.eof()) {
			for (int j = 0; j < 33; j++)
			{
				infile2 >> x2[j] >> y2[j];
			}
		}
		while (!infile3.eof()) {
			for (int j = 0; j < 33; j++)
			{
				infile3 >> x3[j] >> y3[j];
			}
		}
		GoodFeaturesToTrackDetector Detector(1);
		Detector.detect(roi1, keyPoint1);
		Detector.detect(roi2, keyPoint2);
		Detector.detect(roi3, keyPoint3);
		keyPoint1[0].pt.x = x1[p] - a; keyPoint1[0].pt.y = y1[p] - b;
		keyPoint2[0].pt.x = x2[p] - e; keyPoint2[0].pt.y = y2[p] - f;
		keyPoint3[0].pt.x = x3[p] - c; keyPoint3[0].pt.y = y3[p] - d;
		keyPoint1[0].class_id = i;
		keyPoint2[0].class_id = i;
		keyPoint3[0].class_id = i;
	}

	else if (i >= 77 && i < 85) {
		ifstream infile1, infile2, infile3;
		string filename;
		filename = "E:\\Biyesheji\\Detection\\Detection\\match corner\\";
		infile1.open(filename + "result14(1&2&4).txt", ios::in);
		infile2.open(filename + "result24(1&2&4).txt", ios::in);
		infile3.open(filename + "result44(1&2&4).txt", ios::in);//导入目标角点坐标
		double x1[200], y1[200], x2[200], y2[200], x3[200], y3[200];
		while (!infile1.eof()) {
			for (int j = 0; j < 16; j++)
			{
				infile1 >> x1[j] >> y1[j];
			}
		}
		while (!infile2.eof()) {
			for (int j = 0; j < 16; j++)
			{
				infile2 >> x2[j] >> y2[j];
			}
		}
		while (!infile3.eof()) {
			for (int j = 0; j < 16; j++)
			{
				infile3 >> x3[j] >> y3[j];
			}
		}
		int p = i - 77;
		GoodFeaturesToTrackDetector Detector(2);
		Detector.detect(roi1, keyPoint1);
		if (keyPoint1.size() != 2) {
			keyPoints1[0].pt.x = x1[p * 2 + 1] - e; keyPoint1[0].pt.y = y2[p * 2 + 1] - f;
			keyPoint1.push_back(keyPoints1[0]);
		}
		keyPoint1[0].pt.x = x1[p * 2] - a; keyPoint1[0].pt.y = y1[p * 2] - b;
		keyPoint1[1].pt.x = x1[p * 2 + 1] - a; keyPoint1[1].pt.y = y1[p * 2 + 1] - b;
		if (keyPoint1[0].pt.x < keyPoint1[1].pt.x) {
			keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
		}
		else if (keyPoint1[0].pt.x > keyPoint1[1].pt.x) {
			keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
		}
		else if (keyPoint1[0].pt.x == keyPoint1[1].pt.x) {
			if (keyPoint1[0].pt.y > keyPoint1[1].pt.y) {
				keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
			}
			else
				keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
		}

		Detector.detect(roi2, keyPoint2);
		if (keyPoint2.size() != 2) {
			keyPoints2[0].pt.x = x2[p * 2 + 1] - e; keyPoint2[0].pt.y = y2[p * 2 + 1] - f;
			keyPoint2.push_back(keyPoints2[0]);
		}
		keyPoint2[0].pt.x = x2[p * 2] - e; keyPoint2[0].pt.y = y2[p * 2] - f;
		keyPoint2[1].pt.x = x2[p * 2 + 1] - e; keyPoint2[1].pt.y = y2[p * 2 + 1] - f;
		if (keyPoint2[0].pt.x < keyPoint2[1].pt.x) {
			keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
		}
		else if (keyPoint2[0].pt.x > keyPoint2[1].pt.x) {
			keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
		}
		else if (keyPoint2[0].pt.x == keyPoint2[1].pt.x) {
			if (keyPoint2[0].pt.y > keyPoint2[1].pt.y) {
				keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
			}
			else
				keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
		}

		Detector.detect(roi3, keyPoint3);
		if (keyPoint3.size() != 2) {
			keyPoint3.push_back(keyPoint2[0]);
		}
		keyPoint3[0].pt.x = x3[p * 2] - c; keyPoint3[0].pt.y = y3[p * 2] - d;
		keyPoint3[1].pt.x = x3[p * 2 + 1] - c; keyPoint3[1].pt.y = y3[p * 2 + 1] - d;
		if (keyPoint3[0].pt.x < keyPoint3[1].pt.x) {
			keyPoint3[0].class_id = 1;  keyPoint3[1].class_id = 2;
		}
		else if (keyPoint3[0].pt.x > keyPoint3[1].pt.x) {
			keyPoint3[0].class_id = 2;  keyPoint3[1].class_id = 1;
		}
		else if (keyPoint3[0].pt.x == keyPoint3[1].pt.x) {
			if (keyPoint3[0].pt.y > keyPoint3[1].pt.y) {
				keyPoint3[0].class_id = 1;  keyPoint3[1].class_id = 2;
			}
			else
				keyPoint3[0].class_id = 2;  keyPoint3[1].class_id = 1;
		}
	}
}

void MatchPoint2_3_4(int i, vector<int> letters, Mat& roi1, Mat& roi2, Mat& roi3, vector<KeyPoint>& keyPoint1, vector<KeyPoint>& keyPoint2, vector<KeyPoint>& keyPoint3) {
	vector<KeyPoint> keyPoints1(200), keyPoints2(200);//循环前预定义

	int a = letters[0];
	int b = letters[1];
	int e = letters[2];
	int f = letters[3];
	int c = letters[4];
	int d = letters[5];

	if (i<19) {
		ifstream infile1, infile2, infile3;
		string filename;
		filename = "E:\\Biyesheji\\Detection\\Detection\\match corner\\";
		infile1.open(filename + "result21(2&3&4).txt", ios::in);
		infile2.open(filename + "result31(2&3&4).txt", ios::in);
		infile3.open(filename + "result41(2&3&4).txt", ios::in);//导入目标角点坐标
		double x1[200], y1[200], x2[200], y2[200], x3[200], y3[200];
		while (!infile1.eof()) {
			for (int j = 0; j < 38; j++)
			{
				infile1 >> x1[j] >> y1[j];
			}
		}
		while (!infile2.eof()) {
			for (int j = 0; j < 38; j++)
			{
				infile2 >> x2[j] >> y2[j];
			}
		}
		while (!infile3.eof()) {
			for (int j = 0; j < 38; j++)
			{
				infile3 >> x3[j] >> y3[j];
			}
		}
		GoodFeaturesToTrackDetector Detector(2);
		Detector.detect(roi1, keyPoint1);   //检测角点
		while (keyPoint1.size() != 2) {
			keyPoint1.push_back(keyPoints1[0]);
		}
		keyPoint1[0].pt.x = x1[2 * i] - a; keyPoint1[0].pt.y = y1[2 * i] - b;
		keyPoint1[1].pt.x = x1[2 * i + 1] - a; keyPoint1[1].pt.y = y1[2 * i + 1] - b;    //目标角点在区域内坐标
		if (keyPoint1[0].pt.x < keyPoint1[1].pt.x) {
			keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
		}
		else if (keyPoint1[0].pt.x > keyPoint1[1].pt.x) {
			keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
		}
		else if (keyPoint1[0].pt.x == keyPoint1[1].pt.x) {
			if (keyPoint1[0].pt.y > keyPoint1[1].pt.y) {
				keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
			}
			else
				keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
		}                                                             //进行角点分类

		Detector.detect(roi2, keyPoint2);
		while (keyPoint2.size() != 2) {
			keyPoint2.push_back(keyPoints2[0]);
		}
		keyPoint2[0].pt.x = x2[2 * i] - e; keyPoint2[0].pt.y = y2[2 * i] - f;
		keyPoint2[1].pt.x = x2[2 * i + 1] - e; keyPoint2[1].pt.y = y2[2 * i + 1] - f;
		if (keyPoint2[0].pt.x < keyPoint2[1].pt.x) {
			keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
		}
		else if (keyPoint2[0].pt.x > keyPoint2[1].pt.x) {
			keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
		}
		else if (keyPoint2[0].pt.x == keyPoint2[1].pt.x) {
			if (keyPoint2[0].pt.y > keyPoint2[1].pt.y) {
				keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
			}
			else
				keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
		}

		Detector.detect(roi3, keyPoint3);
		while (keyPoint3.size() != 2) {
			keyPoint3.push_back(keyPoints1[0]);
		}
		keyPoint3[0].pt.x = x3[2 * i] - c; keyPoint3[0].pt.y = y3[2 * i] - d;
		keyPoint3[1].pt.x = x3[2 * i + 1] - c; keyPoint2[1].pt.y = y3[2 * i + 1] - d;
		if (keyPoint3[0].pt.x < keyPoint3[1].pt.x) {
			keyPoint3[0].class_id = 1;  keyPoint3[1].class_id = 2;
		}
		else if (keyPoint3[0].pt.x > keyPoint3[1].pt.x) {
			keyPoint3[0].class_id = 2;  keyPoint3[1].class_id = 1;
		}
		else if (keyPoint3[0].pt.x == keyPoint3[1].pt.x) {
			if (keyPoint3[0].pt.y > keyPoint3[1].pt.y) {
				keyPoint3[0].class_id = 1;  keyPoint3[1].class_id = 2;
			}
			else
				keyPoint3[0].class_id = 2;  keyPoint3[1].class_id = 1;
		}
	}

	else if (i >= 19 && i < 38) {
		ifstream infile1, infile2, infile3;
		string filename;
		filename = "E:\\Biyesheji\\Detection\\Detection\\match corner\\";
		infile1.open(filename + "result22(2&3&4).txt", ios::in);
		infile2.open(filename + "result32(2&3&4).txt", ios::in);
		infile3.open(filename + "result42(2&3&4).txt", ios::in);//导入目标角点坐标
		double x1[200], y1[200], x2[200], y2[200], x3[200], y3[200];
		while (!infile1.eof()) {
			for (int j = 0; j < 56; j++) {
				infile1 >> x1[j] >> y1[j];
			}
		}
		while (!infile2.eof()) {
			for (int j = 0; j < 56; j++) {
				infile2 >> x2[j] >> y2[j];
			}
		}
		while (!infile3.eof()) {
			for (int j = 0; j < 56; j++) {
				infile3 >> x3[j] >> y3[j];
			}
		}
		if (i % 2 == 0) {
			GoodFeaturesToTrackDetector Detector(4);
			Detector.detect(roi1, keyPoint1);
			while (keyPoint1.size() != 4) {
				keyPoint1.push_back(keyPoints1[0]);
			}
			int p = (i - 19) / 2;
			keyPoint1[0].pt.x = x1[6 * p + 2] - a; keyPoint1[0].pt.y = y1[6 * p + 2] - b;
			keyPoint1[1].pt.x = x1[6 * p + 3] - a; keyPoint1[1].pt.y = y1[6 * p + 3] - b;
			keyPoint1[2].pt.x = x1[6 * p + 4] - a; keyPoint1[2].pt.y = y1[6 * p + 4] - b;
			keyPoint1[3].pt.x = x1[6 * p + 5] - a; keyPoint1[3].pt.y = y1[6 * p + 5] - b;
			if (keyPoint1[0].pt.x >= keyPoint1[1].pt.x&&keyPoint1[0].pt.x >= keyPoint1[1].pt.x&&keyPoint1[0].pt.x >= keyPoint1[3].pt.x) {
				keyPoint1[0].class_id = 1;
				if (keyPoint1[1].pt.x >= keyPoint1[2].pt.x&&keyPoint1[1].pt.x >= keyPoint1[3].pt.x) {
					keyPoint1[1].class_id = 2;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 3;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 3;
						keyPoint1[2].class_id = 4;
					}
				}
				else if (keyPoint1[1].pt.x <= keyPoint1[2].pt.x&&keyPoint1[1].pt.x <= keyPoint1[3].pt.x) {
					keyPoint1[1].class_id = 4;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 2;
						keyPoint1[3].class_id = 3;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 3;
					}
				}
				else {
					keyPoint1[1].class_id = 3;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 2;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 4;
					}
				}
			}
			else if (keyPoint1[1].pt.x >= keyPoint1[0].pt.x&&keyPoint1[1].pt.x >= keyPoint1[2].pt.x&&keyPoint1[1].pt.x >= keyPoint1[3].pt.x) {
				keyPoint1[1].class_id = 1;
				if (keyPoint1[0].pt.x >= keyPoint1[2].pt.x&&keyPoint1[0].pt.x >= keyPoint1[3].pt.x) {
					keyPoint1[0].class_id = 2;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 3;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 3;
						keyPoint1[2].class_id = 4;
					}
				}
				else if (keyPoint1[0].pt.x <= keyPoint1[2].pt.x&&keyPoint1[01].pt.x <= keyPoint1[3].pt.x) {
					keyPoint1[0].class_id = 4;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 2;
						keyPoint1[3].class_id = 3;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 3;
					}
				}
				else {
					keyPoint1[0].class_id = 3;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 2;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 4;
					}
				}
			}
			else if (keyPoint1[2].pt.x >= keyPoint1[0].pt.x&&keyPoint1[2].pt.x >= keyPoint1[1].pt.x&&keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
				keyPoint1[2].class_id = 1;
				if (keyPoint1[0].pt.x >= keyPoint1[1].pt.x&&keyPoint1[0].pt.x >= keyPoint1[3].pt.x) {
					keyPoint1[0].class_id = 2;
					if (keyPoint1[1].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[1].class_id = 3;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 3;
						keyPoint1[1].class_id = 4;
					}
				}
				else if (keyPoint1[0].pt.x <= keyPoint1[1].pt.x&&keyPoint1[0].pt.x <= keyPoint1[3].pt.x) {
					keyPoint1[0].class_id = 4;
					if (keyPoint1[1].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[1].class_id = 2;
						keyPoint1[3].class_id = 3;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[1].class_id = 3;
					}
				}
				else {
					keyPoint1[0].class_id = 3;
					if (keyPoint1[1].pt.x > keyPoint1[3].pt.x) {
						keyPoint1[1].class_id = 2;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[1].class_id = 4;
					}
				}
			}
			else if (keyPoint1[3].pt.x >= keyPoint1[0].pt.x&&keyPoint1[3].pt.x >= keyPoint1[1].pt.x&&keyPoint1[3].pt.x >= keyPoint1[2].pt.x) {
				keyPoint1[3].class_id = 1;
				if (keyPoint1[0].pt.x >= keyPoint1[1].pt.x&&keyPoint1[0].pt.x >= keyPoint1[2].pt.x) {
					keyPoint1[0].class_id = 2;
					if (keyPoint1[1].pt.x >= keyPoint1[2].pt.x) {
						keyPoint1[1].class_id = 3;
						keyPoint1[2].class_id = 4;
					}
					else {
						keyPoint1[2].class_id = 3;
						keyPoint1[1].class_id = 4;
					}
				}
				else if (keyPoint1[0].pt.x <= keyPoint1[1].pt.x&&keyPoint1[0].pt.x <= keyPoint1[2].pt.x) {
					keyPoint1[0].class_id = 4;
					if (keyPoint1[1].pt.x >= keyPoint1[2].pt.x) {
						keyPoint1[1].class_id = 2;
						keyPoint1[2].class_id = 3;
					}
					else {
						keyPoint1[2].class_id = 2;
						keyPoint1[1].class_id = 3;
					}
				}
				else {
					keyPoint1[0].class_id = 3;
					if (keyPoint1[1].pt.x >= keyPoint1[2].pt.x) {
						keyPoint1[1].class_id = 2;
						keyPoint1[2].class_id = 4;
					}
					else {
						keyPoint1[2].class_id = 2;
						keyPoint1[1].class_id = 4;
					}
				}
			}
			for (int k = 0; k < 4; k++) {
				for (int j = k + 1; j < 4; j++) {
					if (keyPoint1[k].pt.x == keyPoint1[j].pt.x) {
						int max = keyPoint1[k].class_id;
						if (keyPoint1[k].pt.y > keyPoint1[j].pt.y&&keyPoint2[k].class_id < keyPoint1[j].class_id) {
							keyPoint1[j].class_id = keyPoint1[j].class_id;
							keyPoint1[k].class_id = max;
						}
						else if (keyPoint1[k].pt.y < keyPoint1[j].pt.y&&keyPoint1[k].class_id < keyPoint1[j].class_id) {
							keyPoint1[k].class_id = keyPoint1[j].class_id;
							keyPoint1[j].class_id = max;
						}
						else if (keyPoint1[k].pt.y > keyPoint1[j].pt.y&&keyPoint1[k].class_id > keyPoint1[j].class_id) {
							keyPoint1[k].class_id = keyPoint1[j].class_id;
							keyPoint1[j].class_id = max;
						}
						else if (keyPoint1[k].pt.y < keyPoint1[j].pt.y&&keyPoint1[k].class_id > keyPoint1[j].class_id) {
							keyPoint1[j].class_id = keyPoint1[j].class_id;
							keyPoint1[k].class_id = max;
						}
					}
				}
			}

			Detector.detect(roi2, keyPoint2);
			while (keyPoint2.size() != 4) {
				keyPoint2.push_back(keyPoints2[0]);
			}
			keyPoint2[0].pt.x = x2[6 * p + 2] - e; keyPoint2[0].pt.y = y2[6 * p + 2] - f;
			keyPoint2[1].pt.x = x2[6 * p + 3] - e; keyPoint2[1].pt.y = y2[6 * p + 3] - f;
			keyPoint2[2].pt.x = x2[6 * p + 4] - e; keyPoint2[2].pt.y = y2[6 * p + 4] - f;
			keyPoint2[3].pt.x = x2[6 * p + 5] - e; keyPoint2[3].pt.y = y2[6 * p + 5] - f;
			if (keyPoint2[0].pt.x >= keyPoint2[1].pt.x&&keyPoint2[0].pt.x >= keyPoint2[2].pt.x&&keyPoint2[0].pt.x >= keyPoint2[3].pt.x) {
				keyPoint2[0].class_id = 1;
				if (keyPoint2[1].pt.x >= keyPoint2[2].pt.x&&keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
					keyPoint2[1].class_id = 2;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 3;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 3;
						keyPoint2[2].class_id = 4;
					}
				}
				else if (keyPoint2[1].pt.x <= keyPoint2[2].pt.x&&keyPoint2[1].pt.x <= keyPoint2[3].pt.x) {
					keyPoint2[1].class_id = 4;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 2;
						keyPoint2[3].class_id = 3;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[2].class_id = 3;
					}
				}
				else {
					keyPoint2[1].class_id = 3;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 2;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[2].class_id = 4;
					}
				}
			}
			else if (keyPoint2[1].pt.x >= keyPoint2[0].pt.x&&keyPoint2[1].pt.x >= keyPoint2[2].pt.x&&keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
				keyPoint2[1].class_id = 1;
				if (keyPoint2[0].pt.x >= keyPoint2[2].pt.x&&keyPoint2[0].pt.x >= keyPoint2[3].pt.x) {
					keyPoint2[0].class_id = 2;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 3;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 3;
						keyPoint2[2].class_id = 4;
					}
				}
				else if (keyPoint2[0].pt.x <= keyPoint2[2].pt.x&&keyPoint1[01].pt.x <= keyPoint2[3].pt.x) {
					keyPoint2[0].class_id = 4;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 2;
						keyPoint2[3].class_id = 3;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[2].class_id = 3;
					}
				}
				else {
					keyPoint2[0].class_id = 3;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 2;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 4;
					}
				}
			}
			else if (keyPoint2[2].pt.x >= keyPoint2[0].pt.x&&keyPoint2[2].pt.x >= keyPoint2[1].pt.x&&keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
				keyPoint2[2].class_id = 1;
				if (keyPoint2[0].pt.x >= keyPoint2[1].pt.x&&keyPoint2[0].pt.x >= keyPoint2[3].pt.x) {
					keyPoint2[0].class_id = 2;
					if (keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[1].class_id = 3;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 3;
						keyPoint2[1].class_id = 4;
					}
				}
				else if (keyPoint2[0].pt.x <= keyPoint2[1].pt.x&&keyPoint2[0].pt.x <= keyPoint2[3].pt.x) {
					keyPoint2[0].class_id = 4;
					if (keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[1].class_id = 2;
						keyPoint2[3].class_id = 3;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[1].class_id = 3;
					}
				}
				else {
					keyPoint2[0].class_id = 3;
					if (keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[1].class_id = 2;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[1].class_id = 4;
					}
				}
			}
			else if (keyPoint2[3].pt.x >= keyPoint2[0].pt.x&&keyPoint2[3].pt.x >= keyPoint2[1].pt.x&&keyPoint2[3].pt.x >= keyPoint2[2].pt.x) {
				keyPoint2[3].class_id = 1;
				if (keyPoint2[0].pt.x >= keyPoint2[1].pt.x&&keyPoint2[0].pt.x >= keyPoint2[2].pt.x) {
					keyPoint2[0].class_id = 2;
					if (keyPoint2[1].pt.x >= keyPoint2[2].pt.x) {
						keyPoint2[1].class_id = 3;
						keyPoint2[2].class_id = 4;
					}
					else {
						keyPoint2[2].class_id = 3;
						keyPoint2[1].class_id = 4;
					}
				}
				else if (keyPoint2[0].pt.x <= keyPoint2[1].pt.x&&keyPoint2[0].pt.x <= keyPoint2[2].pt.x) {
					keyPoint2[0].class_id = 4;
					if (keyPoint2[1].pt.x >= keyPoint2[2].pt.x) {
						keyPoint2[1].class_id = 2;
						keyPoint2[2].class_id = 3;
					}
					else {
						keyPoint2[2].class_id = 2;
						keyPoint2[1].class_id = 3;
					}
				}
				else {
					keyPoint2[0].class_id = 3;
					if (keyPoint2[1].pt.x >= keyPoint2[2].pt.x) {
						keyPoint2[1].class_id = 2;
						keyPoint2[2].class_id = 4;
					}
					else {
						keyPoint2[2].class_id = 2;
						keyPoint2[1].class_id = 4;
					}
				}
			}
			for (int k = 0; k < 4; k++) {
				for (int j = k + 1; j < 4; j++) {
					if (keyPoint2[k].pt.x == keyPoint2[j].pt.x) {
						int max = keyPoint2[k].class_id;
						if (keyPoint2[k].pt.y > keyPoint2[j].pt.y&&keyPoint2[k].class_id < keyPoint2[j].class_id) {
							keyPoint2[j].class_id = keyPoint2[j].class_id;
							keyPoint2[k].class_id = max;
						}
						else if (keyPoint2[k].pt.y < keyPoint2[j].pt.y&&keyPoint2[k].class_id < keyPoint2[j].class_id) {
							keyPoint2[k].class_id = keyPoint2[j].class_id;
							keyPoint2[j].class_id = max;
						}
						else if (keyPoint2[k].pt.y > keyPoint2[j].pt.y&&keyPoint2[k].class_id > keyPoint2[j].class_id) {
							keyPoint2[k].class_id = keyPoint2[j].class_id;
							keyPoint2[j].class_id = max;
						}
						else if (keyPoint2[k].pt.y < keyPoint2[j].pt.y&&keyPoint2[k].class_id > keyPoint2[j].class_id) {
							keyPoint2[j].class_id = keyPoint2[j].class_id;
							keyPoint2[k].class_id = max;
						}
					}
				}
			}

			Detector.detect(roi3, keyPoint3);
			while (keyPoint3.size() != 4) {
				keyPoint3.push_back(keyPoints2[0]);
			}
			keyPoint3[0].pt.x = x2[6 * p + 2] - c; keyPoint3[0].pt.y = y2[6 * p + 2] - d;
			keyPoint3[1].pt.x = x2[6 * p + 3] - c; keyPoint3[1].pt.y = y2[6 * p + 3] - d;
			keyPoint3[2].pt.x = x2[6 * p + 4] - c; keyPoint3[2].pt.y = y2[6 * p + 4] - d;
			keyPoint3[3].pt.x = x2[6 * p + 5] - c; keyPoint3[3].pt.y = y2[6 * p + 5] - d;
			if (keyPoint3[0].pt.x >= keyPoint3[1].pt.x&&keyPoint3[0].pt.x >= keyPoint3[2].pt.x&&keyPoint3[0].pt.x >= keyPoint3[3].pt.x) {
				keyPoint3[0].class_id = 1;
				if (keyPoint3[1].pt.x >= keyPoint3[2].pt.x&&keyPoint3[1].pt.x >= keyPoint3[3].pt.x) {
					keyPoint3[1].class_id = 2;
					if (keyPoint3[2].pt.x >= keyPoint3[3].pt.x) {
						keyPoint3[2].class_id = 3;
						keyPoint3[3].class_id = 4;
					}
					else {
						keyPoint3[3].class_id = 3;
						keyPoint3[2].class_id = 4;
					}
				}
				else if (keyPoint3[1].pt.x <= keyPoint3[2].pt.x&&keyPoint3[1].pt.x <= keyPoint3[3].pt.x) {
					keyPoint3[1].class_id = 4;
					if (keyPoint3[2].pt.x >= keyPoint3[3].pt.x) {
						keyPoint3[2].class_id = 2;
						keyPoint3[3].class_id = 3;
					}
					else {
						keyPoint3[3].class_id = 2;
						keyPoint3[2].class_id = 3;
					}
				}
				else {
					keyPoint3[1].class_id = 3;
					if (keyPoint3[2].pt.x >= keyPoint3[3].pt.x) {
						keyPoint3[2].class_id = 2;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint3[3].class_id = 2;
						keyPoint3[2].class_id = 4;
					}
				}
			}
			else if (keyPoint3[1].pt.x >= keyPoint3[0].pt.x&&keyPoint3[1].pt.x >= keyPoint3[2].pt.x&&keyPoint3[1].pt.x >= keyPoint3[3].pt.x) {
				keyPoint3[1].class_id = 1;
				if (keyPoint3[0].pt.x >= keyPoint3[2].pt.x&&keyPoint3[0].pt.x >= keyPoint3[3].pt.x) {
					keyPoint3[0].class_id = 2;
					if (keyPoint3[2].pt.x >= keyPoint3[3].pt.x) {
						keyPoint3[2].class_id = 3;
						keyPoint3[3].class_id = 4;
					}
					else {
						keyPoint3[3].class_id = 3;
						keyPoint3[2].class_id = 4;
					}
				}
				else if (keyPoint3[0].pt.x <= keyPoint3[2].pt.x&&keyPoint1[01].pt.x <= keyPoint3[3].pt.x) {
					keyPoint3[0].class_id = 4;
					if (keyPoint3[2].pt.x >= keyPoint3[3].pt.x) {
						keyPoint3[2].class_id = 2;
						keyPoint3[3].class_id = 3;
					}
					else {
						keyPoint3[3].class_id = 2;
						keyPoint3[2].class_id = 3;
					}
				}
				else {
					keyPoint3[0].class_id = 3;
					if (keyPoint3[2].pt.x >= keyPoint3[3].pt.x) {
						keyPoint3[2].class_id = 2;
						keyPoint3[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 4;
					}
				}
			}
			else if (keyPoint3[2].pt.x >= keyPoint3[0].pt.x&&keyPoint3[2].pt.x >= keyPoint3[1].pt.x&&keyPoint3[2].pt.x >= keyPoint3[3].pt.x) {
				keyPoint3[2].class_id = 1;
				if (keyPoint3[0].pt.x >= keyPoint3[1].pt.x&&keyPoint3[0].pt.x >= keyPoint3[3].pt.x) {
					keyPoint3[0].class_id = 2;
					if (keyPoint3[1].pt.x >= keyPoint3[3].pt.x) {
						keyPoint3[1].class_id = 3;
						keyPoint3[3].class_id = 4;
					}
					else {
						keyPoint3[3].class_id = 3;
						keyPoint3[1].class_id = 4;
					}
				}
				else if (keyPoint3[0].pt.x <= keyPoint3[1].pt.x&&keyPoint3[0].pt.x <= keyPoint3[3].pt.x) {
					keyPoint3[0].class_id = 4;
					if (keyPoint3[1].pt.x >= keyPoint3[3].pt.x) {
						keyPoint3[1].class_id = 2;
						keyPoint3[3].class_id = 3;
					}
					else {
						keyPoint3[3].class_id = 2;
						keyPoint3[1].class_id = 3;
					}
				}
				else {
					keyPoint3[0].class_id = 3;
					if (keyPoint3[1].pt.x >= keyPoint3[3].pt.x) {
						keyPoint3[1].class_id = 2;
						keyPoint3[3].class_id = 4;
					}
					else {
						keyPoint3[3].class_id = 2;
						keyPoint3[1].class_id = 4;
					}
				}
			}
			else if (keyPoint3[3].pt.x >= keyPoint3[0].pt.x&&keyPoint3[3].pt.x >= keyPoint3[1].pt.x&&keyPoint3[3].pt.x >= keyPoint3[2].pt.x) {
				keyPoint3[3].class_id = 1;
				if (keyPoint3[0].pt.x >= keyPoint3[1].pt.x&&keyPoint3[0].pt.x >= keyPoint3[2].pt.x) {
					keyPoint3[0].class_id = 2;
					if (keyPoint3[1].pt.x >= keyPoint3[2].pt.x) {
						keyPoint3[1].class_id = 3;
						keyPoint3[2].class_id = 4;
					}
					else {
						keyPoint3[2].class_id = 3;
						keyPoint3[1].class_id = 4;
					}
				}
				else if (keyPoint3[0].pt.x <= keyPoint3[1].pt.x&&keyPoint3[0].pt.x <= keyPoint3[2].pt.x) {
					keyPoint3[0].class_id = 4;
					if (keyPoint3[1].pt.x >= keyPoint3[2].pt.x) {
						keyPoint3[1].class_id = 2;
						keyPoint3[2].class_id = 3;
					}
					else {
						keyPoint3[2].class_id = 2;
						keyPoint3[1].class_id = 3;
					}
				}
				else {
					keyPoint3[0].class_id = 3;
					if (keyPoint3[1].pt.x >= keyPoint3[2].pt.x) {
						keyPoint3[1].class_id = 2;
						keyPoint3[2].class_id = 4;
					}
					else {
						keyPoint3[2].class_id = 2;
						keyPoint3[1].class_id = 4;
					}
				}
			}
			for (int k = 0; k < 4; k++) {
				for (int j = k + 1; j < 4; j++) {
					if (keyPoint3[k].pt.x == keyPoint3[j].pt.x) {
						int max = keyPoint3[k].class_id;
						if (keyPoint3[k].pt.y > keyPoint3[j].pt.y&&keyPoint3[k].class_id < keyPoint3[j].class_id) {
							keyPoint3[j].class_id = keyPoint3[j].class_id;
							keyPoint3[k].class_id = max;
						}
						else if (keyPoint3[k].pt.y < keyPoint3[j].pt.y&&keyPoint3[k].class_id < keyPoint3[j].class_id) {
							keyPoint3[k].class_id = keyPoint3[j].class_id;
							keyPoint3[j].class_id = max;
						}
						else if (keyPoint3[k].pt.y > keyPoint3[j].pt.y&&keyPoint3[k].class_id > keyPoint3[j].class_id) {
							keyPoint3[k].class_id = keyPoint3[j].class_id;
							keyPoint3[j].class_id = max;
						}
						else if (keyPoint3[k].pt.y < keyPoint3[j].pt.y&&keyPoint3[k].class_id > keyPoint3[j].class_id) {
							keyPoint3[j].class_id = keyPoint3[j].class_id;
							keyPoint3[k].class_id = max;
						}
					}
				}
			}

		}
		else if (i % 2 != 0) {
			int p = (i - 19) / 2;
			GoodFeaturesToTrackDetector Detector(2);
			Detector.detect(roi1, keyPoint1);
			if (keyPoint1.size() != 2) {
				keyPoints1[0].pt.x = x1[p * 2 + 1] - e; keyPoint2[0].pt.y = y1[p * 2 + 1] - f;
				keyPoint1.push_back(keyPoints2[0]);
			}
			keyPoint1[0].pt.x = x1[6 * p] - a; keyPoint1[0].pt.y = y1[6 * p] - b;
			keyPoint1[1].pt.x = x1[6 * p + 1] - a; keyPoint1[1].pt.y = y1[6 * p + 1] - b;
			if (keyPoint1[0].pt.x < keyPoint1[1].pt.x) {
				keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
			}
			else if (keyPoint1[0].pt.x > keyPoint1[1].pt.x) {
				keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
			}
			else if (keyPoint1[0].pt.x == keyPoint1[1].pt.x) {
				if (keyPoint1[0].pt.y > keyPoint1[1].pt.y) {
					keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
				}
				else
					keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
			}

			Detector.detect(roi2, keyPoint2);
			if (keyPoint2.size() != 2) {
				keyPoints2[0].pt.x = x2[p * 2 + 1] - e; keyPoint2[0].pt.y = y2[p * 2 + 1] - f;
				keyPoint2.push_back(keyPoints2[0]);
			}
			keyPoint2[0].pt.x = x2[6 * p] - e; keyPoint2[0].pt.y = y2[6 * p] - f;
			keyPoint2[1].pt.x = x2[6 * p + 1] - e; keyPoint2[1].pt.y = y2[6 * p + 1] - f;
			if (keyPoint2[0].pt.x < keyPoint2[1].pt.x) {
				keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
			}
			else if (keyPoint2[0].pt.x > keyPoint2[1].pt.x) {
				keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
			}
			else if (keyPoint2[0].pt.x == keyPoint2[1].pt.x) {
				if (keyPoint2[0].pt.y > keyPoint2[1].pt.y) {
					keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
				}
				else
					keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
			}

			Detector.detect(roi3, keyPoint3);
			if (keyPoint3.size() != 2) {
				keyPoints2[0].pt.x = x2[p * 2 + 1] - c; keyPoint3[0].pt.y = y2[p * 2 + 1] - d;
				keyPoint3.push_back(keyPoints2[0]);
			}
			keyPoint3[0].pt.x = x2[6 * p] - c; keyPoint3[0].pt.y = y2[6 * p] - d;
			keyPoint3[1].pt.x = x2[6 * p + 1] - c; keyPoint3[1].pt.y = y2[6 * p + 1] - d;
			if (keyPoint3[0].pt.x < keyPoint3[1].pt.x) {
				keyPoint3[0].class_id = 1;  keyPoint3[1].class_id = 2;
			}
			else if (keyPoint3[0].pt.x > keyPoint3[1].pt.x) {
				keyPoint3[0].class_id = 2;  keyPoint3[1].class_id = 1;
			}
			else if (keyPoint3[0].pt.x == keyPoint3[1].pt.x) {
				if (keyPoint3[0].pt.y > keyPoint3[1].pt.y) {
					keyPoint3[0].class_id = 1;  keyPoint3[1].class_id = 2;
				}
				else
					keyPoint3[0].class_id = 2;  keyPoint3[1].class_id = 1;
			}

		}
	}

	else if (i >= 38 && i < 68) {
		int p = i - 38;
		ifstream infile1, infile2, infile3;
		string filename;
		filename = "E:\\Biyesheji\\Detection\\Detection\\match corner\\";
		infile1.open(filename + "result23(2&3&4).txt", ios::in);
		infile2.open(filename + "result33(2&3&4).txt", ios::in);
		infile3.open(filename + "result43(2&3&4).txt", ios::in);//导入目标角点坐标
		double x1[200], y1[200], x2[200], y2[200], x3[200], y3[200];
		while (!infile1.eof()) {
			for (int j = 0; j < 30; j++)
			{
				infile1 >> x1[j] >> y1[j];
			}
		}
		while (!infile2.eof()) {
			for (int j = 0; j < 30; j++)
			{
				infile2 >> x2[j] >> y2[j];
			}
		}
		while (!infile3.eof()) {
			for (int j = 0; j < 30; j++)
			{
				infile3 >> x3[j] >> y3[j];
			}
		}
		GoodFeaturesToTrackDetector Detector(1);
		Detector.detect(roi1, keyPoint1);
		Detector.detect(roi2, keyPoint2);
		Detector.detect(roi3, keyPoint3);
		keyPoint1[0].pt.x = x1[p] - a; keyPoint1[0].pt.y = y1[p] - b;
		keyPoint2[0].pt.x = x2[p] - e; keyPoint2[0].pt.y = y2[p] - f;
		keyPoint3[0].pt.x = x3[p] - c; keyPoint3[0].pt.y = y3[p] - d;
		keyPoint1[0].class_id = i;
		keyPoint2[0].class_id = i;
		keyPoint3[0].class_id = i;
	}

	else if (i >= 68 && i < 75) {
		ifstream infile1, infile2, infile3;
		string filename;
		filename = "E:\\Biyesheji\\Detection\\Detection\\match corner\\";
		infile1.open(filename + "result24(2&3&4).txt", ios::in);
		infile2.open(filename + "result34(2&3&4).txt", ios::in);
		infile3.open(filename + "result44(2&3&4).txt", ios::in);//导入目标角点坐标
		double x1[200], y1[200], x2[200], y2[200], x3[200], y3[200];
		while (!infile1.eof()) {
			for (int j = 0; j < 14; j++)
			{
				infile1 >> x1[j] >> y1[j];
			}
		}
		while (!infile2.eof()) {
			for (int j = 0; j < 14; j++)
			{
				infile2 >> x2[j] >> y2[j];
			}
		}
		while (!infile3.eof()) {
			for (int j = 0; j < 14; j++)
			{
				infile3 >> x3[j] >> y3[j];
			}
		}
		int p = i - 68;
		GoodFeaturesToTrackDetector Detector(2);
		Detector.detect(roi1, keyPoint1);
		if (keyPoint1.size() != 2) {
			keyPoints1[0].pt.x = x1[p * 2 + 1] - e; keyPoint1[0].pt.y = y2[p * 2 + 1] - f;
			keyPoint1.push_back(keyPoints1[0]);
		}
		keyPoint1[0].pt.x = x1[p * 2] - a; keyPoint1[0].pt.y = y1[p * 2] - b;
		keyPoint1[1].pt.x = x1[p * 2 + 1] - a; keyPoint1[1].pt.y = y1[p * 2 + 1] - b;
		if (keyPoint1[0].pt.x < keyPoint1[1].pt.x) {
			keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
		}
		else if (keyPoint1[0].pt.x > keyPoint1[1].pt.x) {
			keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
		}
		else if (keyPoint1[0].pt.x == keyPoint1[1].pt.x) {
			if (keyPoint1[0].pt.y > keyPoint1[1].pt.y) {
				keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
			}
			else
				keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
		}

		Detector.detect(roi2, keyPoint2);
		if (keyPoint2.size() != 2) {
			keyPoints2[0].pt.x = x2[p * 2 + 1] - e; keyPoint2[0].pt.y = y2[p * 2 + 1] - f;
			keyPoint2.push_back(keyPoints2[0]);
		}
		keyPoint2[0].pt.x = x2[p * 2] - e; keyPoint2[0].pt.y = y2[p * 2] - f;
		keyPoint2[1].pt.x = x2[p * 2 + 1] - e; keyPoint2[1].pt.y = y2[p * 2 + 1] - f;
		if (keyPoint2[0].pt.x < keyPoint2[1].pt.x) {
			keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
		}
		else if (keyPoint2[0].pt.x > keyPoint2[1].pt.x) {
			keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
		}
		else if (keyPoint2[0].pt.x == keyPoint2[1].pt.x) {
			if (keyPoint2[0].pt.y > keyPoint2[1].pt.y) {
				keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
			}
			else
				keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
		}

		Detector.detect(roi3, keyPoint3);
		if (keyPoint3.size() != 2) {
			keyPoints2[0].pt.x = x3[p * 2 + 1] - c; keyPoint3[0].pt.y = y3[p * 2 + 1] - d;
			keyPoint3.push_back(keyPoints2[0]);
		}
		keyPoint3[0].pt.x = x3[p * 2] - c; keyPoint3[0].pt.y = y3[p * 2] - d;
		keyPoint3[1].pt.x = x3[p * 2 + 1] - c; keyPoint3[1].pt.y = y3[p * 2 + 1] - d;
		if (keyPoint3[0].pt.x < keyPoint3[1].pt.x) {
			keyPoint3[0].class_id = 1;  keyPoint3[1].class_id = 2;
		}
		else if (keyPoint3[0].pt.x > keyPoint3[1].pt.x) {
			keyPoint3[0].class_id = 2;  keyPoint3[1].class_id = 1;
		}
		else if (keyPoint3[0].pt.x == keyPoint3[1].pt.x) {
			if (keyPoint3[0].pt.y > keyPoint3[1].pt.y) {
				keyPoint3[0].class_id = 1;  keyPoint3[1].class_id = 2;
			}
			else
				keyPoint3[0].class_id = 2;  keyPoint3[1].class_id = 1;
		}
	}
}

void MatchPoint1_3_4(int i, vector<int> letters, Mat& roi1, Mat& roi2, Mat& roi3, vector<KeyPoint>& keyPoint1, vector<KeyPoint>& keyPoint2, vector<KeyPoint>& keyPoint3) {
	vector<KeyPoint> keyPoints1(200), keyPoints2(200);//循环前预定义

	int a = letters[0];
	int b = letters[1];
	int e = letters[2];
	int f = letters[3];
	int c = letters[4];
	int d = letters[5];

	if (i<19) {
		ifstream infile1, infile2, infile3;
		string filename;
		filename = "E:\\Biyesheji\\Detection\\Detection\\match corner\\";
		infile1.open(filename + "result11(1&3&4).txt", ios::in);
		infile2.open(filename + "result31(1&3&4).txt", ios::in);
		infile3.open(filename + "result41(1&3&4).txt", ios::in);//导入目标角点坐标
		double x1[200], y1[200], x2[200], y2[200], x3[200], y3[200];
		while (!infile1.eof()) {
			for (int j = 0; j < 38; j++)
			{
				infile1 >> x1[j] >> y1[j];
			}
		}
		while (!infile2.eof()) {
			for (int j = 0; j < 38; j++)
			{
				infile2 >> x2[j] >> y2[j];
			}
		}
		while (!infile3.eof()) {
			for (int j = 0; j < 38; j++)
			{
				infile3 >> x3[j] >> y3[j];
			}
		}
		GoodFeaturesToTrackDetector Detector(2);
		Detector.detect(roi1, keyPoint1);   //检测角点
		while (keyPoint1.size() != 2) {
			keyPoint1.push_back(keyPoints1[0]);
		}
		keyPoint1[0].pt.x = x1[2 * i] - a; keyPoint1[0].pt.y = y1[2 * i] - b;
		keyPoint1[1].pt.x = x1[2 * i + 1] - a; keyPoint1[1].pt.y = y1[2 * i + 1] - b;    //目标角点在区域内坐标
		if (keyPoint1[0].pt.x < keyPoint1[1].pt.x) {
			keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
		}
		else if (keyPoint1[0].pt.x > keyPoint1[1].pt.x) {
			keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
		}
		else if (keyPoint1[0].pt.x == keyPoint1[1].pt.x) {
			if (keyPoint1[0].pt.y > keyPoint1[1].pt.y) {
				keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
			}
			else
				keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
		}                                                             //进行角点分类

		Detector.detect(roi2, keyPoint2);
		while (keyPoint2.size() != 2) {
			keyPoint2.push_back(keyPoints2[0]);
		}
		keyPoint2[0].pt.x = x2[2 * i] - e; keyPoint2[0].pt.y = y2[2 * i] - f;
		keyPoint2[1].pt.x = x2[2 * i + 1] - e; keyPoint2[1].pt.y = y2[2 * i + 1] - f;
		if (keyPoint2[0].pt.x < keyPoint2[1].pt.x) {
			keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
		}
		else if (keyPoint2[0].pt.x > keyPoint2[1].pt.x) {
			keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
		}
		else if (keyPoint2[0].pt.x == keyPoint2[1].pt.x) {
			if (keyPoint2[0].pt.y > keyPoint2[1].pt.y) {
				keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
			}
			else
				keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
		}

		Detector.detect(roi3, keyPoint3);
		while (keyPoint3.size() != 2) {
			keyPoint3.push_back(keyPoints1[0]);
		}
		keyPoint3[0].pt.x = x3[2 * i] - c; keyPoint3[0].pt.y = y3[2 * i] - d;
		keyPoint3[1].pt.x = x3[2 * i + 1] - c; keyPoint3[1].pt.y = y3[2 * i + 1] - d;
		if (keyPoint3[0].pt.x < keyPoint3[1].pt.x) {
			keyPoint3[0].class_id = 1;  keyPoint3[1].class_id = 2;
		}
		else if (keyPoint3[0].pt.x > keyPoint3[1].pt.x) {
			keyPoint3[0].class_id = 2;  keyPoint3[1].class_id = 1;
		}
		else if (keyPoint3[0].pt.x == keyPoint3[1].pt.x) {
			if (keyPoint3[0].pt.y > keyPoint3[1].pt.y) {
				keyPoint3[0].class_id = 1;  keyPoint3[1].class_id = 2;
			}
			else
				keyPoint3[0].class_id = 2;  keyPoint3[1].class_id = 1;
		}
	}

	else if (i >= 19 && i < 38) {
		ifstream infile1, infile2, infile3;
		string filename;
		filename = "E:\\Biyesheji\\Detection\\Detection\\match corner\\";
		infile1.open(filename + "result12(1&3&4).txt", ios::in);
		infile2.open(filename + "result32(1&3&4).txt", ios::in);
		infile3.open(filename + "result42(1&3&4).txt", ios::in);//导入目标角点坐标
		double x1[200], y1[200], x2[200], y2[200], x3[200], y3[200];
		while (!infile1.eof()) {
			for (int j = 0; j < 56; j++) {
				infile1 >> x1[j] >> y1[j];
			}
		}
		while (!infile2.eof()) {
			for (int j = 0; j < 56; j++) {
				infile2 >> x2[j] >> y2[j];
			}
		}
		while (!infile3.eof()) {
			for (int j = 0; j < 56; j++) {
				infile3 >> x3[j] >> y3[j];
			}
		}
		if (i % 2 == 0) {
			GoodFeaturesToTrackDetector Detector(4);
			Detector.detect(roi1, keyPoint1);
			while (keyPoint1.size() != 4) {
				keyPoint1.push_back(keyPoints1[0]);
			}
			int p = (i - 19) / 2;
			keyPoint1[0].pt.x = x1[6 * p + 2] - a; keyPoint1[0].pt.y = y1[6 * p + 2] - b;
			keyPoint1[1].pt.x = x1[6 * p + 3] - a; keyPoint1[1].pt.y = y1[6 * p + 3] - b;
			keyPoint1[2].pt.x = x1[6 * p + 4] - a; keyPoint1[2].pt.y = y1[6 * p + 4] - b;
			keyPoint1[3].pt.x = x1[6 * p + 5] - a; keyPoint1[3].pt.y = y1[6 * p + 5] - b;
			if (keyPoint1[0].pt.x >= keyPoint1[1].pt.x&&keyPoint1[0].pt.x >= keyPoint1[1].pt.x&&keyPoint1[0].pt.x >= keyPoint1[3].pt.x) {
				keyPoint1[0].class_id = 1;
				if (keyPoint1[1].pt.x >= keyPoint1[2].pt.x&&keyPoint1[1].pt.x >= keyPoint1[3].pt.x) {
					keyPoint1[1].class_id = 2;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 3;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 3;
						keyPoint1[2].class_id = 4;
					}
				}
				else if (keyPoint1[1].pt.x <= keyPoint1[2].pt.x&&keyPoint1[1].pt.x <= keyPoint1[3].pt.x) {
					keyPoint1[1].class_id = 4;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 2;
						keyPoint1[3].class_id = 3;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 3;
					}
				}
				else {
					keyPoint1[1].class_id = 3;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 2;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 4;
					}
				}
			}
			else if (keyPoint1[1].pt.x >= keyPoint1[0].pt.x&&keyPoint1[1].pt.x >= keyPoint1[2].pt.x&&keyPoint1[1].pt.x >= keyPoint1[3].pt.x) {
				keyPoint1[1].class_id = 1;
				if (keyPoint1[0].pt.x >= keyPoint1[2].pt.x&&keyPoint1[0].pt.x >= keyPoint1[3].pt.x) {
					keyPoint1[0].class_id = 2;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 3;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 3;
						keyPoint1[2].class_id = 4;
					}
				}
				else if (keyPoint1[0].pt.x <= keyPoint1[2].pt.x&&keyPoint1[01].pt.x <= keyPoint1[3].pt.x) {
					keyPoint1[0].class_id = 4;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 2;
						keyPoint1[3].class_id = 3;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 3;
					}
				}
				else {
					keyPoint1[0].class_id = 3;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 2;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 4;
					}
				}
			}
			else if (keyPoint1[2].pt.x >= keyPoint1[0].pt.x&&keyPoint1[2].pt.x >= keyPoint1[1].pt.x&&keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
				keyPoint1[2].class_id = 1;
				if (keyPoint1[0].pt.x >= keyPoint1[1].pt.x&&keyPoint1[0].pt.x >= keyPoint1[3].pt.x) {
					keyPoint1[0].class_id = 2;
					if (keyPoint1[1].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[1].class_id = 3;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 3;
						keyPoint1[1].class_id = 4;
					}
				}
				else if (keyPoint1[0].pt.x <= keyPoint1[1].pt.x&&keyPoint1[0].pt.x <= keyPoint1[3].pt.x) {
					keyPoint1[0].class_id = 4;
					if (keyPoint1[1].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[1].class_id = 2;
						keyPoint1[3].class_id = 3;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[1].class_id = 3;
					}
				}
				else {
					keyPoint1[0].class_id = 3;
					if (keyPoint1[1].pt.x > keyPoint1[3].pt.x) {
						keyPoint1[1].class_id = 2;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[1].class_id = 4;
					}
				}
			}
			else if (keyPoint1[3].pt.x >= keyPoint1[0].pt.x&&keyPoint1[3].pt.x >= keyPoint1[1].pt.x&&keyPoint1[3].pt.x >= keyPoint1[2].pt.x) {
				keyPoint1[3].class_id = 1;
				if (keyPoint1[0].pt.x >= keyPoint1[1].pt.x&&keyPoint1[0].pt.x >= keyPoint1[2].pt.x) {
					keyPoint1[0].class_id = 2;
					if (keyPoint1[1].pt.x >= keyPoint1[2].pt.x) {
						keyPoint1[1].class_id = 3;
						keyPoint1[2].class_id = 4;
					}
					else {
						keyPoint1[2].class_id = 3;
						keyPoint1[1].class_id = 4;
					}
				}
				else if (keyPoint1[0].pt.x <= keyPoint1[1].pt.x&&keyPoint1[0].pt.x <= keyPoint1[2].pt.x) {
					keyPoint1[0].class_id = 4;
					if (keyPoint1[1].pt.x >= keyPoint1[2].pt.x) {
						keyPoint1[1].class_id = 2;
						keyPoint1[2].class_id = 3;
					}
					else {
						keyPoint1[2].class_id = 2;
						keyPoint1[1].class_id = 3;
					}
				}
				else {
					keyPoint1[0].class_id = 3;
					if (keyPoint1[1].pt.x >= keyPoint1[2].pt.x) {
						keyPoint1[1].class_id = 2;
						keyPoint1[2].class_id = 4;
					}
					else {
						keyPoint1[2].class_id = 2;
						keyPoint1[1].class_id = 4;
					}
				}
			}
			for (int k = 0; k < 4; k++) {
				for (int j = k + 1; j < 4; j++) {
					if (keyPoint1[k].pt.x == keyPoint1[j].pt.x) {
						int max = keyPoint1[k].class_id;
						if (keyPoint1[k].pt.y > keyPoint1[j].pt.y&&keyPoint2[k].class_id < keyPoint1[j].class_id) {
							keyPoint1[j].class_id = keyPoint1[j].class_id;
							keyPoint1[k].class_id = max;
						}
						else if (keyPoint1[k].pt.y < keyPoint1[j].pt.y&&keyPoint1[k].class_id < keyPoint1[j].class_id) {
							keyPoint1[k].class_id = keyPoint1[j].class_id;
							keyPoint1[j].class_id = max;
						}
						else if (keyPoint1[k].pt.y > keyPoint1[j].pt.y&&keyPoint1[k].class_id > keyPoint1[j].class_id) {
							keyPoint1[k].class_id = keyPoint1[j].class_id;
							keyPoint1[j].class_id = max;
						}
						else if (keyPoint1[k].pt.y < keyPoint1[j].pt.y&&keyPoint1[k].class_id > keyPoint1[j].class_id) {
							keyPoint1[j].class_id = keyPoint1[j].class_id;
							keyPoint1[k].class_id = max;
						}
					}
				}
			}

			Detector.detect(roi2, keyPoint2);
			while (keyPoint2.size() != 4) {
				keyPoint2.push_back(keyPoints2[0]);
			}
			keyPoint2[0].pt.x = x2[6 * p + 2] - e; keyPoint2[0].pt.y = y2[6 * p + 2] - f;
			keyPoint2[1].pt.x = x2[6 * p + 3] - e; keyPoint2[1].pt.y = y2[6 * p + 3] - f;
			keyPoint2[2].pt.x = x2[6 * p + 4] - e; keyPoint2[2].pt.y = y2[6 * p + 4] - f;
			keyPoint2[3].pt.x = x2[6 * p + 5] - e; keyPoint2[3].pt.y = y2[6 * p + 5] - f;
			if (keyPoint2[0].pt.x >= keyPoint2[1].pt.x&&keyPoint2[0].pt.x >= keyPoint2[2].pt.x&&keyPoint2[0].pt.x >= keyPoint2[3].pt.x) {
				keyPoint2[0].class_id = 1;
				if (keyPoint2[1].pt.x >= keyPoint2[2].pt.x&&keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
					keyPoint2[1].class_id = 2;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 3;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 3;
						keyPoint2[2].class_id = 4;
					}
				}
				else if (keyPoint2[1].pt.x <= keyPoint2[2].pt.x&&keyPoint2[1].pt.x <= keyPoint2[3].pt.x) {
					keyPoint2[1].class_id = 4;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 2;
						keyPoint2[3].class_id = 3;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[2].class_id = 3;
					}
				}
				else {
					keyPoint2[1].class_id = 3;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 2;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[2].class_id = 4;
					}
				}
			}
			else if (keyPoint2[1].pt.x >= keyPoint2[0].pt.x&&keyPoint2[1].pt.x >= keyPoint2[2].pt.x&&keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
				keyPoint2[1].class_id = 1;
				if (keyPoint2[0].pt.x >= keyPoint2[2].pt.x&&keyPoint2[0].pt.x >= keyPoint2[3].pt.x) {
					keyPoint2[0].class_id = 2;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 3;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 3;
						keyPoint2[2].class_id = 4;
					}
				}
				else if (keyPoint2[0].pt.x <= keyPoint2[2].pt.x&&keyPoint1[01].pt.x <= keyPoint2[3].pt.x) {
					keyPoint2[0].class_id = 4;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 2;
						keyPoint2[3].class_id = 3;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[2].class_id = 3;
					}
				}
				else {
					keyPoint2[0].class_id = 3;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 2;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 4;
					}
				}
			}
			else if (keyPoint2[2].pt.x >= keyPoint2[0].pt.x&&keyPoint2[2].pt.x >= keyPoint2[1].pt.x&&keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
				keyPoint2[2].class_id = 1;
				if (keyPoint2[0].pt.x >= keyPoint2[1].pt.x&&keyPoint2[0].pt.x >= keyPoint2[3].pt.x) {
					keyPoint2[0].class_id = 2;
					if (keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[1].class_id = 3;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 3;
						keyPoint2[1].class_id = 4;
					}
				}
				else if (keyPoint2[0].pt.x <= keyPoint2[1].pt.x&&keyPoint2[0].pt.x <= keyPoint2[3].pt.x) {
					keyPoint2[0].class_id = 4;
					if (keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[1].class_id = 2;
						keyPoint2[3].class_id = 3;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[1].class_id = 3;
					}
				}
				else {
					keyPoint2[0].class_id = 3;
					if (keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[1].class_id = 2;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[1].class_id = 4;
					}
				}
			}
			else if (keyPoint2[3].pt.x >= keyPoint2[0].pt.x&&keyPoint2[3].pt.x >= keyPoint2[1].pt.x&&keyPoint2[3].pt.x >= keyPoint2[2].pt.x) {
				keyPoint2[3].class_id = 1;
				if (keyPoint2[0].pt.x >= keyPoint2[1].pt.x&&keyPoint2[0].pt.x >= keyPoint2[2].pt.x) {
					keyPoint2[0].class_id = 2;
					if (keyPoint2[1].pt.x >= keyPoint2[2].pt.x) {
						keyPoint2[1].class_id = 3;
						keyPoint2[2].class_id = 4;
					}
					else {
						keyPoint2[2].class_id = 3;
						keyPoint2[1].class_id = 4;
					}
				}
				else if (keyPoint2[0].pt.x <= keyPoint2[1].pt.x&&keyPoint2[0].pt.x <= keyPoint2[2].pt.x) {
					keyPoint2[0].class_id = 4;
					if (keyPoint2[1].pt.x >= keyPoint2[2].pt.x) {
						keyPoint2[1].class_id = 2;
						keyPoint2[2].class_id = 3;
					}
					else {
						keyPoint2[2].class_id = 2;
						keyPoint2[1].class_id = 3;
					}
				}
				else {
					keyPoint2[0].class_id = 3;
					if (keyPoint2[1].pt.x >= keyPoint2[2].pt.x) {
						keyPoint2[1].class_id = 2;
						keyPoint2[2].class_id = 4;
					}
					else {
						keyPoint2[2].class_id = 2;
						keyPoint2[1].class_id = 4;
					}
				}
			}
			for (int k = 0; k < 4; k++) {
				for (int j = k + 1; j < 4; j++) {
					if (keyPoint2[k].pt.x == keyPoint2[j].pt.x) {
						int max = keyPoint2[k].class_id;
						if (keyPoint2[k].pt.y > keyPoint2[j].pt.y&&keyPoint2[k].class_id < keyPoint2[j].class_id) {
							keyPoint2[j].class_id = keyPoint2[j].class_id;
							keyPoint2[k].class_id = max;
						}
						else if (keyPoint2[k].pt.y < keyPoint2[j].pt.y&&keyPoint2[k].class_id < keyPoint2[j].class_id) {
							keyPoint2[k].class_id = keyPoint2[j].class_id;
							keyPoint2[j].class_id = max;
						}
						else if (keyPoint2[k].pt.y > keyPoint2[j].pt.y&&keyPoint2[k].class_id > keyPoint2[j].class_id) {
							keyPoint2[k].class_id = keyPoint2[j].class_id;
							keyPoint2[j].class_id = max;
						}
						else if (keyPoint2[k].pt.y < keyPoint2[j].pt.y&&keyPoint2[k].class_id > keyPoint2[j].class_id) {
							keyPoint2[j].class_id = keyPoint2[j].class_id;
							keyPoint2[k].class_id = max;
						}
					}
				}
			}

			Detector.detect(roi3, keyPoint3);
			while (keyPoint3.size() != 4) {
				keyPoint3.push_back(keyPoints2[0]);
			}
			keyPoint3[0].pt.x = x2[6 * p + 2] - c; keyPoint3[0].pt.y = y2[6 * p + 2] - d;
			keyPoint3[1].pt.x = x2[6 * p + 3] - c; keyPoint3[1].pt.y = y2[6 * p + 3] - d;
			keyPoint3[2].pt.x = x2[6 * p + 4] - c; keyPoint3[2].pt.y = y2[6 * p + 4] - d;
			keyPoint3[3].pt.x = x2[6 * p + 5] - c; keyPoint3[3].pt.y = y2[6 * p + 5] - d;
			if (keyPoint3[0].pt.x >= keyPoint3[1].pt.x&&keyPoint3[0].pt.x >= keyPoint3[2].pt.x&&keyPoint3[0].pt.x >= keyPoint3[3].pt.x) {
				keyPoint3[0].class_id = 1;
				if (keyPoint3[1].pt.x >= keyPoint3[2].pt.x&&keyPoint3[1].pt.x >= keyPoint3[3].pt.x) {
					keyPoint3[1].class_id = 2;
					if (keyPoint3[2].pt.x >= keyPoint3[3].pt.x) {
						keyPoint3[2].class_id = 3;
						keyPoint3[3].class_id = 4;
					}
					else {
						keyPoint3[3].class_id = 3;
						keyPoint3[2].class_id = 4;
					}
				}
				else if (keyPoint3[1].pt.x <= keyPoint3[2].pt.x&&keyPoint3[1].pt.x <= keyPoint3[3].pt.x) {
					keyPoint3[1].class_id = 4;
					if (keyPoint3[2].pt.x >= keyPoint3[3].pt.x) {
						keyPoint3[2].class_id = 2;
						keyPoint3[3].class_id = 3;
					}
					else {
						keyPoint3[3].class_id = 2;
						keyPoint3[2].class_id = 3;
					}
				}
				else {
					keyPoint3[1].class_id = 3;
					if (keyPoint3[2].pt.x >= keyPoint3[3].pt.x) {
						keyPoint3[2].class_id = 2;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint3[3].class_id = 2;
						keyPoint3[2].class_id = 4;
					}
				}
			}
			else if (keyPoint3[1].pt.x >= keyPoint3[0].pt.x&&keyPoint3[1].pt.x >= keyPoint3[2].pt.x&&keyPoint3[1].pt.x >= keyPoint3[3].pt.x) {
				keyPoint3[1].class_id = 1;
				if (keyPoint3[0].pt.x >= keyPoint3[2].pt.x&&keyPoint3[0].pt.x >= keyPoint3[3].pt.x) {
					keyPoint3[0].class_id = 2;
					if (keyPoint3[2].pt.x >= keyPoint3[3].pt.x) {
						keyPoint3[2].class_id = 3;
						keyPoint3[3].class_id = 4;
					}
					else {
						keyPoint3[3].class_id = 3;
						keyPoint3[2].class_id = 4;
					}
				}
				else if (keyPoint3[0].pt.x <= keyPoint3[2].pt.x&&keyPoint1[01].pt.x <= keyPoint3[3].pt.x) {
					keyPoint3[0].class_id = 4;
					if (keyPoint3[2].pt.x >= keyPoint3[3].pt.x) {
						keyPoint3[2].class_id = 2;
						keyPoint3[3].class_id = 3;
					}
					else {
						keyPoint3[3].class_id = 2;
						keyPoint3[2].class_id = 3;
					}
				}
				else {
					keyPoint3[0].class_id = 3;
					if (keyPoint3[2].pt.x >= keyPoint3[3].pt.x) {
						keyPoint3[2].class_id = 2;
						keyPoint3[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 4;
					}
				}
			}
			else if (keyPoint3[2].pt.x >= keyPoint3[0].pt.x&&keyPoint3[2].pt.x >= keyPoint3[1].pt.x&&keyPoint3[2].pt.x >= keyPoint3[3].pt.x) {
				keyPoint3[2].class_id = 1;
				if (keyPoint3[0].pt.x >= keyPoint3[1].pt.x&&keyPoint3[0].pt.x >= keyPoint3[3].pt.x) {
					keyPoint3[0].class_id = 2;
					if (keyPoint3[1].pt.x >= keyPoint3[3].pt.x) {
						keyPoint3[1].class_id = 3;
						keyPoint3[3].class_id = 4;
					}
					else {
						keyPoint3[3].class_id = 3;
						keyPoint3[1].class_id = 4;
					}
				}
				else if (keyPoint3[0].pt.x <= keyPoint3[1].pt.x&&keyPoint3[0].pt.x <= keyPoint3[3].pt.x) {
					keyPoint3[0].class_id = 4;
					if (keyPoint3[1].pt.x >= keyPoint3[3].pt.x) {
						keyPoint3[1].class_id = 2;
						keyPoint3[3].class_id = 3;
					}
					else {
						keyPoint3[3].class_id = 2;
						keyPoint3[1].class_id = 3;
					}
				}
				else {
					keyPoint3[0].class_id = 3;
					if (keyPoint3[1].pt.x >= keyPoint3[3].pt.x) {
						keyPoint3[1].class_id = 2;
						keyPoint3[3].class_id = 4;
					}
					else {
						keyPoint3[3].class_id = 2;
						keyPoint3[1].class_id = 4;
					}
				}
			}
			else if (keyPoint3[3].pt.x >= keyPoint3[0].pt.x&&keyPoint3[3].pt.x >= keyPoint3[1].pt.x&&keyPoint3[3].pt.x >= keyPoint3[2].pt.x) {
				keyPoint3[3].class_id = 1;
				if (keyPoint3[0].pt.x >= keyPoint3[1].pt.x&&keyPoint3[0].pt.x >= keyPoint3[2].pt.x) {
					keyPoint3[0].class_id = 2;
					if (keyPoint3[1].pt.x >= keyPoint3[2].pt.x) {
						keyPoint3[1].class_id = 3;
						keyPoint3[2].class_id = 4;
					}
					else {
						keyPoint3[2].class_id = 3;
						keyPoint3[1].class_id = 4;
					}
				}
				else if (keyPoint3[0].pt.x <= keyPoint3[1].pt.x&&keyPoint3[0].pt.x <= keyPoint3[2].pt.x) {
					keyPoint3[0].class_id = 4;
					if (keyPoint3[1].pt.x >= keyPoint3[2].pt.x) {
						keyPoint3[1].class_id = 2;
						keyPoint3[2].class_id = 3;
					}
					else {
						keyPoint3[2].class_id = 2;
						keyPoint3[1].class_id = 3;
					}
				}
				else {
					keyPoint3[0].class_id = 3;
					if (keyPoint3[1].pt.x >= keyPoint3[2].pt.x) {
						keyPoint3[1].class_id = 2;
						keyPoint3[2].class_id = 4;
					}
					else {
						keyPoint3[2].class_id = 2;
						keyPoint3[1].class_id = 4;
					}
				}
			}
			for (int k = 0; k < 4; k++) {
				for (int j = k + 1; j < 4; j++) {
					if (keyPoint3[k].pt.x == keyPoint3[j].pt.x) {
						int max = keyPoint3[k].class_id;
						if (keyPoint3[k].pt.y > keyPoint3[j].pt.y&&keyPoint3[k].class_id < keyPoint3[j].class_id) {
							keyPoint3[j].class_id = keyPoint3[j].class_id;
							keyPoint3[k].class_id = max;
						}
						else if (keyPoint3[k].pt.y < keyPoint3[j].pt.y&&keyPoint3[k].class_id < keyPoint3[j].class_id) {
							keyPoint3[k].class_id = keyPoint3[j].class_id;
							keyPoint3[j].class_id = max;
						}
						else if (keyPoint3[k].pt.y > keyPoint3[j].pt.y&&keyPoint3[k].class_id > keyPoint3[j].class_id) {
							keyPoint3[k].class_id = keyPoint3[j].class_id;
							keyPoint3[j].class_id = max;
						}
						else if (keyPoint3[k].pt.y < keyPoint3[j].pt.y&&keyPoint3[k].class_id > keyPoint3[j].class_id) {
							keyPoint3[j].class_id = keyPoint3[j].class_id;
							keyPoint3[k].class_id = max;
						}
					}
				}
			}

		}
		else if (i % 2 != 0) {
			int p = (i - 19) / 2;
			GoodFeaturesToTrackDetector Detector(2);
			Detector.detect(roi1, keyPoint1);
			if (keyPoint1.size() != 2) {
				keyPoints1[0].pt.x = x1[p * 2 + 1] - e; keyPoint2[0].pt.y = y1[p * 2 + 1] - f;
				keyPoint1.push_back(keyPoints2[0]);
			}
			keyPoint1[0].pt.x = x1[6 * p] - a; keyPoint1[0].pt.y = y1[6 * p] - b;
			keyPoint1[1].pt.x = x1[6 * p + 1] - a; keyPoint1[1].pt.y = y1[6 * p + 1] - b;
			if (keyPoint1[0].pt.x < keyPoint1[1].pt.x) {
				keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
			}
			else if (keyPoint1[0].pt.x > keyPoint1[1].pt.x) {
				keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
			}
			else if (keyPoint1[0].pt.x == keyPoint1[1].pt.x) {
				if (keyPoint1[0].pt.y > keyPoint1[1].pt.y) {
					keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
				}
				else
					keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
			}

			Detector.detect(roi2, keyPoint2);
			if (keyPoint2.size() != 2) {
				keyPoints2[0].pt.x = x2[p * 2 + 1] - e; keyPoint2[0].pt.y = y2[p * 2 + 1] - f;
				keyPoint2.push_back(keyPoints2[0]);
			}
			keyPoint2[0].pt.x = x2[6 * p] - e; keyPoint2[0].pt.y = y2[6 * p] - f;
			keyPoint2[1].pt.x = x2[6 * p + 1] - e; keyPoint2[1].pt.y = y2[6 * p + 1] - f;
			if (keyPoint2[0].pt.x < keyPoint2[1].pt.x) {
				keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
			}
			else if (keyPoint2[0].pt.x > keyPoint2[1].pt.x) {
				keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
			}
			else if (keyPoint2[0].pt.x == keyPoint2[1].pt.x) {
				if (keyPoint2[0].pt.y > keyPoint2[1].pt.y) {
					keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
				}
				else
					keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
			}

			Detector.detect(roi3, keyPoint3);
			if (keyPoint3.size() != 2) {
				keyPoints2[0].pt.x = x2[p * 2 + 1] - c; keyPoint3[0].pt.y = y2[p * 2 + 1] - d;
				keyPoint3.push_back(keyPoints2[0]);
			}
			keyPoint3[0].pt.x = x2[6 * p] - c; keyPoint3[0].pt.y = y2[6 * p] - d;
			keyPoint3[1].pt.x = x2[6 * p + 1] - c; keyPoint3[1].pt.y = y2[6 * p + 1] - d;
			if (keyPoint3[0].pt.x < keyPoint3[1].pt.x) {
				keyPoint3[0].class_id = 1;  keyPoint3[1].class_id = 2;
			}
			else if (keyPoint3[0].pt.x > keyPoint3[1].pt.x) {
				keyPoint3[0].class_id = 2;  keyPoint3[1].class_id = 1;
			}
			else if (keyPoint3[0].pt.x == keyPoint3[1].pt.x) {
				if (keyPoint3[0].pt.y > keyPoint3[1].pt.y) {
					keyPoint3[0].class_id = 1;  keyPoint3[1].class_id = 2;
				}
				else
					keyPoint3[0].class_id = 2;  keyPoint3[1].class_id = 1;
			}

		}
	}

	else if (i >= 38 && i < 68) {
		int p = i - 38;
		ifstream infile1, infile2, infile3;
		string filename;
		filename = "E:\\Biyesheji\\Detection\\Detection\\match corner\\";
		infile1.open(filename + "result13(1&3&4).txt", ios::in);
		infile2.open(filename + "result33(1&3&4).txt", ios::in);
		infile3.open(filename + "result43(1&3&4).txt", ios::in);//导入目标角点坐标
		double x1[200], y1[200], x2[200], y2[200], x3[200], y3[200];
		while (!infile1.eof()) {
			for (int j = 0; j < 30; j++)
			{
				infile1 >> x1[j] >> y1[j];
			}
		}
		while (!infile2.eof()) {
			for (int j = 0; j < 30; j++)
			{
				infile2 >> x2[j] >> y2[j];
			}
		}
		while (!infile3.eof()) {
			for (int j = 0; j < 30; j++)
			{
				infile3 >> x3[j] >> y3[j];
			}
		}
		GoodFeaturesToTrackDetector Detector(1);
		Detector.detect(roi1, keyPoint1);
		Detector.detect(roi2, keyPoint2);
		Detector.detect(roi3, keyPoint3);
		keyPoint1[0].pt.x = x1[p] - a; keyPoint1[0].pt.y = y1[p] - b;
		keyPoint2[0].pt.x = x2[p] - e; keyPoint2[0].pt.y = y2[p] - f;
		keyPoint3[0].pt.x = x3[p] - c; keyPoint3[0].pt.y = y3[p] - d;
		keyPoint1[0].class_id = i;
		keyPoint2[0].class_id = i;
		keyPoint3[0].class_id = i;
	}

	else if (i >= 68 && i < 75) {
		ifstream infile1, infile2, infile3;
		string filename;
		filename = "E:\\Biyesheji\\Detection\\Detection\\match corner\\";
		infile1.open(filename + "result14(1&3&4).txt", ios::in);
		infile2.open(filename + "result34(1&3&4).txt", ios::in);
		infile3.open(filename + "result44(1&3&4).txt", ios::in);//导入目标角点坐标
		double x1[200], y1[200], x2[200], y2[200], x3[200], y3[200];
		while (!infile1.eof()) {
			for (int j = 0; j < 14; j++)
			{
				infile1 >> x1[j] >> y1[j];
			}
		}
		while (!infile2.eof()) {
			for (int j = 0; j < 14; j++)
			{
				infile2 >> x2[j] >> y2[j];
			}
		}
		while (!infile3.eof()) {
			for (int j = 0; j < 14; j++)
			{
				infile3 >> x3[j] >> y3[j];
			}
		}
		int p = i - 68;
		GoodFeaturesToTrackDetector Detector(2);
		Detector.detect(roi1, keyPoint1);
		if (keyPoint1.size() != 2) {
			keyPoints1[0].pt.x = x1[p * 2 + 1] - e; keyPoint1[0].pt.y = y2[p * 2 + 1] - f;
			keyPoint1.push_back(keyPoints1[0]);
		}
		keyPoint1[0].pt.x = x1[p * 2] - a; keyPoint1[0].pt.y = y1[p * 2] - b;
		keyPoint1[1].pt.x = x1[p * 2 + 1] - a; keyPoint1[1].pt.y = y1[p * 2 + 1] - b;
		if (keyPoint1[0].pt.x < keyPoint1[1].pt.x) {
			keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
		}
		else if (keyPoint1[0].pt.x > keyPoint1[1].pt.x) {
			keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
		}
		else if (keyPoint1[0].pt.x == keyPoint1[1].pt.x) {
			if (keyPoint1[0].pt.y > keyPoint1[1].pt.y) {
				keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
			}
			else
				keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
		}

		Detector.detect(roi2, keyPoint2);
		if (keyPoint2.size() != 2) {
			keyPoints2[0].pt.x = x2[p * 2 + 1] - e; keyPoint2[0].pt.y = y2[p * 2 + 1] - f;
			keyPoint2.push_back(keyPoints2[0]);
		}
		keyPoint2[0].pt.x = x2[p * 2] - e; keyPoint2[0].pt.y = y2[p * 2] - f;
		keyPoint2[1].pt.x = x2[p * 2 + 1] - e; keyPoint2[1].pt.y = y2[p * 2 + 1] - f;
		if (keyPoint2[0].pt.x < keyPoint2[1].pt.x) {
			keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
		}
		else if (keyPoint2[0].pt.x > keyPoint2[1].pt.x) {
			keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
		}
		else if (keyPoint2[0].pt.x == keyPoint2[1].pt.x) {
			if (keyPoint2[0].pt.y > keyPoint2[1].pt.y) {
				keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
			}
			else
				keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
		}

		Detector.detect(roi3, keyPoint3);
		if (keyPoint3.size() != 2) {
			keyPoint3.push_back(keyPoints2[0]);
		}
		keyPoint3[0].pt.x = x3[p * 2] - c; keyPoint3[0].pt.y = y3[p * 2] - d;
		keyPoint3[1].pt.x = x3[p * 2 + 1] - c; keyPoint3[1].pt.y = y3[p * 2 + 1] - d;
		if (keyPoint3[0].pt.x < keyPoint3[1].pt.x) {
			keyPoint3[0].class_id = 1;  keyPoint3[1].class_id = 2;
		}
		else if (keyPoint3[0].pt.x > keyPoint3[1].pt.x) {
			keyPoint3[0].class_id = 2;  keyPoint3[1].class_id = 1;
		}
		else if (keyPoint3[0].pt.x == keyPoint3[1].pt.x) {
			if (keyPoint3[0].pt.y > keyPoint3[1].pt.y) {
				keyPoint3[0].class_id = 1;  keyPoint3[1].class_id = 2;
			}
			else
				keyPoint3[0].class_id = 2;  keyPoint3[1].class_id = 1;
		}
	}
}

void MatchPoint1_2_3_4(int i, vector<int> letters, Mat& roi1, Mat& roi2, Mat& roi3, Mat& roi4, vector<KeyPoint>& keyPoint1, vector<KeyPoint>& keyPoint2, vector<KeyPoint>& keyPoint3, vector<KeyPoint>& keyPoint4) {
	vector<KeyPoint> keyPoints1(200), keyPoints2(200);//循环前预定义

	int a = letters[0];
	int b = letters[1];
	int e = letters[2];
	int f = letters[3];
	int c = letters[4];
	int d = letters[5];
	int m = letters[6];
	int n = letters[7];

	if (i<19) {
		ifstream infile1, infile2, infile3, infile4;
		string filename;
		filename = "E:\\Biyesheji\\Detection\\Detection\\match corner\\";
		infile1.open(filename + "result11(1&3&4).txt", ios::in);
		infile2.open(filename + "result21(2&3&4).txt", ios::in);
		infile3.open(filename + "result31(1&3&4).txt", ios::in);
		infile4.open(filename + "result41(1&3&4).txt", ios::in);//导入目标角点坐标
		double x1[200], y1[200], x2[200], y2[200], x3[200], y3[200], x4[200], y4[200];
		while (!infile1.eof()) {
			for (int j = 0; j < 38; j++)
			{
				infile1 >> x1[j] >> y1[j];
			}
		}
		while (!infile2.eof()) {
			for (int j = 0; j < 38; j++)
			{
				infile2 >> x2[j] >> y2[j];
			}
		}
		while (!infile3.eof()) {
			for (int j = 0; j < 38; j++)
			{
				infile3 >> x3[j] >> y3[j];
			}
		}
		while (!infile4.eof()) {
			for (int j = 0; j < 38; j++)
			{
				infile4 >> x4[j] >> y4[j];
			}
		}
		GoodFeaturesToTrackDetector Detector(2);
		Detector.detect(roi1, keyPoint1);   //检测角点
		while (keyPoint1.size() != 2) {
			keyPoint1.push_back(keyPoints1[0]);
		}
		keyPoint1[0].pt.x = x1[2 * i] - a; keyPoint1[0].pt.y = y1[2 * i] - b;
		keyPoint1[1].pt.x = x1[2 * i + 1] - a; keyPoint1[1].pt.y = y1[2 * i + 1] - b;    //目标角点在区域内坐标
		if (keyPoint1[0].pt.x < keyPoint1[1].pt.x) {
			keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
		}
		else if (keyPoint1[0].pt.x > keyPoint1[1].pt.x) {
			keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
		}
		else if (keyPoint1[0].pt.x == keyPoint1[1].pt.x) {
			if (keyPoint1[0].pt.y > keyPoint1[1].pt.y) {
				keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
			}
			else
				keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
		}                                                             //进行角点分类

		Detector.detect(roi2, keyPoint2);
		while (keyPoint2.size() != 2) {
			keyPoint2.push_back(keyPoints2[0]);
		}
		keyPoint2[0].pt.x = x2[2 * i] - e; keyPoint2[0].pt.y = y2[2 * i] - f;
		keyPoint2[1].pt.x = x2[2 * i + 1] - e; keyPoint2[1].pt.y = y2[2 * i + 1] - f;
		if (keyPoint2[0].pt.x < keyPoint2[1].pt.x) {
			keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
		}
		else if (keyPoint2[0].pt.x > keyPoint2[1].pt.x) {
			keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
		}
		else if (keyPoint2[0].pt.x == keyPoint2[1].pt.x) {
			if (keyPoint2[0].pt.y > keyPoint2[1].pt.y) {
				keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
			}
			else
				keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
		}

		Detector.detect(roi3, keyPoint3);
		while (keyPoint3.size() != 2) {
			keyPoint3.push_back(keyPoints1[0]);
		}
		keyPoint3[0].pt.x = x3[2 * i] - c; keyPoint3[0].pt.y = y3[2 * i] - d;
		keyPoint3[1].pt.x = x3[2 * i + 1] - c; keyPoint3[1].pt.y = y3[2 * i + 1] - d;
		if (keyPoint3[0].pt.x < keyPoint3[1].pt.x) {
			keyPoint3[0].class_id = 1;  keyPoint3[1].class_id = 2;
		}
		else if (keyPoint3[0].pt.x > keyPoint3[1].pt.x) {
			keyPoint3[0].class_id = 2;  keyPoint3[1].class_id = 1;
		}
		else if (keyPoint3[0].pt.x == keyPoint3[1].pt.x) {
			if (keyPoint3[0].pt.y > keyPoint3[1].pt.y) {
				keyPoint3[0].class_id = 1;  keyPoint3[1].class_id = 2;
			}
			else
				keyPoint3[0].class_id = 2;  keyPoint3[1].class_id = 1;
		}
		Detector.detect(roi4, keyPoint4);   //检测角点
		while (keyPoint4.size() != 2) {
			keyPoint4.push_back(keyPoints1[0]);
		}
		keyPoint4[0].pt.x = x1[2 * i] - m; keyPoint4[0].pt.y = y1[2 * i] - n;
		keyPoint4[1].pt.x = x1[2 * i + 1] - m; keyPoint4[1].pt.y = y1[2 * i + 1] - n;    //目标角点在区域内坐标
		if (keyPoint4[0].pt.x < keyPoint4[1].pt.x) {
			keyPoint4[0].class_id = 1;  keyPoint4[1].class_id = 2;
		}
		else if (keyPoint4[0].pt.x > keyPoint4[1].pt.x) {
			keyPoint4[0].class_id = 2;  keyPoint4[1].class_id = 1;
		}
		else if (keyPoint4[0].pt.x == keyPoint4[1].pt.x) {
			if (keyPoint4[0].pt.y > keyPoint4[1].pt.y) {
				keyPoint4[0].class_id = 1;  keyPoint4[1].class_id = 2;
			}
			else
				keyPoint4[0].class_id = 2;  keyPoint4[1].class_id = 1;
		}                                                             //进行角点分类

	}

	else if (i >= 19 && i < 38) {
		ifstream infile1, infile2, infile3, infile4;
		string filename;
		filename = "E:\\Biyesheji\\Detection\\Detection\\match corner\\";
		infile1.open(filename + "result12(1&3&4).txt", ios::in);
		infile2.open(filename + "result22(2&3&4).txt", ios::in);
		infile3.open(filename + "result32(1&3&4).txt", ios::in);
		infile4.open(filename + "result42(1&3&4).txt", ios::in);//导入目标角点坐标
		double x1[200], y1[200], x2[200], y2[200], x3[200], y3[200], x4[200], y4[200];
		while (!infile1.eof()) {
			for (int j = 0; j < 56; j++) {
				infile1 >> x1[j] >> y1[j];
			}
		}
		while (!infile2.eof()) {
			for (int j = 0; j < 56; j++) {
				infile2 >> x2[j] >> y2[j];
			}
		}
		while (!infile3.eof()) {
			for (int j = 0; j < 56; j++) {
				infile3 >> x3[j] >> y3[j];
			}
		}
		while (!infile4.eof()) {
			for (int j = 0; j < 56; j++) {
				infile4 >> x4[j] >> y4[j];
			}
		}
		if (i % 2 == 0) {
			GoodFeaturesToTrackDetector Detector(4);
			Detector.detect(roi1, keyPoint1);
			while (keyPoint1.size() != 4) {
				keyPoint1.push_back(keyPoints1[0]);
			}
			int p = (i - 19) / 2;
			keyPoint1[0].pt.x = x1[6 * p + 2] - a; keyPoint1[0].pt.y = y1[6 * p + 2] - b;
			keyPoint1[1].pt.x = x1[6 * p + 3] - a; keyPoint1[1].pt.y = y1[6 * p + 3] - b;
			keyPoint1[2].pt.x = x1[6 * p + 4] - a; keyPoint1[2].pt.y = y1[6 * p + 4] - b;
			keyPoint1[3].pt.x = x1[6 * p + 5] - a; keyPoint1[3].pt.y = y1[6 * p + 5] - b;
			if (keyPoint1[0].pt.x >= keyPoint1[1].pt.x&&keyPoint1[0].pt.x >= keyPoint1[1].pt.x&&keyPoint1[0].pt.x >= keyPoint1[3].pt.x) {
				keyPoint1[0].class_id = 1;
				if (keyPoint1[1].pt.x >= keyPoint1[2].pt.x&&keyPoint1[1].pt.x >= keyPoint1[3].pt.x) {
					keyPoint1[1].class_id = 2;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 3;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 3;
						keyPoint1[2].class_id = 4;
					}
				}
				else if (keyPoint1[1].pt.x <= keyPoint1[2].pt.x&&keyPoint1[1].pt.x <= keyPoint1[3].pt.x) {
					keyPoint1[1].class_id = 4;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 2;
						keyPoint1[3].class_id = 3;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 3;
					}
				}
				else {
					keyPoint1[1].class_id = 3;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 2;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 4;
					}
				}
			}
			else if (keyPoint1[1].pt.x >= keyPoint1[0].pt.x&&keyPoint1[1].pt.x >= keyPoint1[2].pt.x&&keyPoint1[1].pt.x >= keyPoint1[3].pt.x) {
				keyPoint1[1].class_id = 1;
				if (keyPoint1[0].pt.x >= keyPoint1[2].pt.x&&keyPoint1[0].pt.x >= keyPoint1[3].pt.x) {
					keyPoint1[0].class_id = 2;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 3;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 3;
						keyPoint1[2].class_id = 4;
					}
				}
				else if (keyPoint1[0].pt.x <= keyPoint1[2].pt.x&&keyPoint1[01].pt.x <= keyPoint1[3].pt.x) {
					keyPoint1[0].class_id = 4;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 2;
						keyPoint1[3].class_id = 3;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 3;
					}
				}
				else {
					keyPoint1[0].class_id = 3;
					if (keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[2].class_id = 2;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 4;
					}
				}
			}
			else if (keyPoint1[2].pt.x >= keyPoint1[0].pt.x&&keyPoint1[2].pt.x >= keyPoint1[1].pt.x&&keyPoint1[2].pt.x >= keyPoint1[3].pt.x) {
				keyPoint1[2].class_id = 1;
				if (keyPoint1[0].pt.x >= keyPoint1[1].pt.x&&keyPoint1[0].pt.x >= keyPoint1[3].pt.x) {
					keyPoint1[0].class_id = 2;
					if (keyPoint1[1].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[1].class_id = 3;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 3;
						keyPoint1[1].class_id = 4;
					}
				}
				else if (keyPoint1[0].pt.x <= keyPoint1[1].pt.x&&keyPoint1[0].pt.x <= keyPoint1[3].pt.x) {
					keyPoint1[0].class_id = 4;
					if (keyPoint1[1].pt.x >= keyPoint1[3].pt.x) {
						keyPoint1[1].class_id = 2;
						keyPoint1[3].class_id = 3;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[1].class_id = 3;
					}
				}
				else {
					keyPoint1[0].class_id = 3;
					if (keyPoint1[1].pt.x > keyPoint1[3].pt.x) {
						keyPoint1[1].class_id = 2;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[1].class_id = 4;
					}
				}
			}
			else if (keyPoint1[3].pt.x >= keyPoint1[0].pt.x&&keyPoint1[3].pt.x >= keyPoint1[1].pt.x&&keyPoint1[3].pt.x >= keyPoint1[2].pt.x) {
				keyPoint1[3].class_id = 1;
				if (keyPoint1[0].pt.x >= keyPoint1[1].pt.x&&keyPoint1[0].pt.x >= keyPoint1[2].pt.x) {
					keyPoint1[0].class_id = 2;
					if (keyPoint1[1].pt.x >= keyPoint1[2].pt.x) {
						keyPoint1[1].class_id = 3;
						keyPoint1[2].class_id = 4;
					}
					else {
						keyPoint1[2].class_id = 3;
						keyPoint1[1].class_id = 4;
					}
				}
				else if (keyPoint1[0].pt.x <= keyPoint1[1].pt.x&&keyPoint1[0].pt.x <= keyPoint1[2].pt.x) {
					keyPoint1[0].class_id = 4;
					if (keyPoint1[1].pt.x >= keyPoint1[2].pt.x) {
						keyPoint1[1].class_id = 2;
						keyPoint1[2].class_id = 3;
					}
					else {
						keyPoint1[2].class_id = 2;
						keyPoint1[1].class_id = 3;
					}
				}
				else {
					keyPoint1[0].class_id = 3;
					if (keyPoint1[1].pt.x >= keyPoint1[2].pt.x) {
						keyPoint1[1].class_id = 2;
						keyPoint1[2].class_id = 4;
					}
					else {
						keyPoint1[2].class_id = 2;
						keyPoint1[1].class_id = 4;
					}
				}
			}
			for (int k = 0; k < 4; k++) {
				for (int j = k + 1; j < 4; j++) {
					if (keyPoint1[k].pt.x == keyPoint1[j].pt.x) {
						int max = keyPoint1[k].class_id;
						if (keyPoint1[k].pt.y > keyPoint1[j].pt.y&&keyPoint2[k].class_id < keyPoint1[j].class_id) {
							keyPoint1[j].class_id = keyPoint1[j].class_id;
							keyPoint1[k].class_id = max;
						}
						else if (keyPoint1[k].pt.y < keyPoint1[j].pt.y&&keyPoint1[k].class_id < keyPoint1[j].class_id) {
							keyPoint1[k].class_id = keyPoint1[j].class_id;
							keyPoint1[j].class_id = max;
						}
						else if (keyPoint1[k].pt.y > keyPoint1[j].pt.y&&keyPoint1[k].class_id > keyPoint1[j].class_id) {
							keyPoint1[k].class_id = keyPoint1[j].class_id;
							keyPoint1[j].class_id = max;
						}
						else if (keyPoint1[k].pt.y < keyPoint1[j].pt.y&&keyPoint1[k].class_id > keyPoint1[j].class_id) {
							keyPoint1[j].class_id = keyPoint1[j].class_id;
							keyPoint1[k].class_id = max;
						}
					}
				}
			}

			Detector.detect(roi2, keyPoint2);
			while (keyPoint2.size() != 4) {
				keyPoint2.push_back(keyPoints2[0]);
			}
			keyPoint2[0].pt.x = x2[6 * p + 2] - e; keyPoint2[0].pt.y = y2[6 * p + 2] - f;
			keyPoint2[1].pt.x = x2[6 * p + 3] - e; keyPoint2[1].pt.y = y2[6 * p + 3] - f;
			keyPoint2[2].pt.x = x2[6 * p + 4] - e; keyPoint2[2].pt.y = y2[6 * p + 4] - f;
			keyPoint2[3].pt.x = x2[6 * p + 5] - e; keyPoint2[3].pt.y = y2[6 * p + 5] - f;
			if (keyPoint2[0].pt.x >= keyPoint2[1].pt.x&&keyPoint2[0].pt.x >= keyPoint2[2].pt.x&&keyPoint2[0].pt.x >= keyPoint2[3].pt.x) {
				keyPoint2[0].class_id = 1;
				if (keyPoint2[1].pt.x >= keyPoint2[2].pt.x&&keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
					keyPoint2[1].class_id = 2;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 3;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 3;
						keyPoint2[2].class_id = 4;
					}
				}
				else if (keyPoint2[1].pt.x <= keyPoint2[2].pt.x&&keyPoint2[1].pt.x <= keyPoint2[3].pt.x) {
					keyPoint2[1].class_id = 4;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 2;
						keyPoint2[3].class_id = 3;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[2].class_id = 3;
					}
				}
				else {
					keyPoint2[1].class_id = 3;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 2;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[2].class_id = 4;
					}
				}
			}
			else if (keyPoint2[1].pt.x >= keyPoint2[0].pt.x&&keyPoint2[1].pt.x >= keyPoint2[2].pt.x&&keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
				keyPoint2[1].class_id = 1;
				if (keyPoint2[0].pt.x >= keyPoint2[2].pt.x&&keyPoint2[0].pt.x >= keyPoint2[3].pt.x) {
					keyPoint2[0].class_id = 2;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 3;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 3;
						keyPoint2[2].class_id = 4;
					}
				}
				else if (keyPoint2[0].pt.x <= keyPoint2[2].pt.x&&keyPoint1[01].pt.x <= keyPoint2[3].pt.x) {
					keyPoint2[0].class_id = 4;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 2;
						keyPoint2[3].class_id = 3;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[2].class_id = 3;
					}
				}
				else {
					keyPoint2[0].class_id = 3;
					if (keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[2].class_id = 2;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 4;
					}
				}
			}
			else if (keyPoint2[2].pt.x >= keyPoint2[0].pt.x&&keyPoint2[2].pt.x >= keyPoint2[1].pt.x&&keyPoint2[2].pt.x >= keyPoint2[3].pt.x) {
				keyPoint2[2].class_id = 1;
				if (keyPoint2[0].pt.x >= keyPoint2[1].pt.x&&keyPoint2[0].pt.x >= keyPoint2[3].pt.x) {
					keyPoint2[0].class_id = 2;
					if (keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[1].class_id = 3;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 3;
						keyPoint2[1].class_id = 4;
					}
				}
				else if (keyPoint2[0].pt.x <= keyPoint2[1].pt.x&&keyPoint2[0].pt.x <= keyPoint2[3].pt.x) {
					keyPoint2[0].class_id = 4;
					if (keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[1].class_id = 2;
						keyPoint2[3].class_id = 3;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[1].class_id = 3;
					}
				}
				else {
					keyPoint2[0].class_id = 3;
					if (keyPoint2[1].pt.x >= keyPoint2[3].pt.x) {
						keyPoint2[1].class_id = 2;
						keyPoint2[3].class_id = 4;
					}
					else {
						keyPoint2[3].class_id = 2;
						keyPoint2[1].class_id = 4;
					}
				}
			}
			else if (keyPoint2[3].pt.x >= keyPoint2[0].pt.x&&keyPoint2[3].pt.x >= keyPoint2[1].pt.x&&keyPoint2[3].pt.x >= keyPoint2[2].pt.x) {
				keyPoint2[3].class_id = 1;
				if (keyPoint2[0].pt.x >= keyPoint2[1].pt.x&&keyPoint2[0].pt.x >= keyPoint2[2].pt.x) {
					keyPoint2[0].class_id = 2;
					if (keyPoint2[1].pt.x >= keyPoint2[2].pt.x) {
						keyPoint2[1].class_id = 3;
						keyPoint2[2].class_id = 4;
					}
					else {
						keyPoint2[2].class_id = 3;
						keyPoint2[1].class_id = 4;
					}
				}
				else if (keyPoint2[0].pt.x <= keyPoint2[1].pt.x&&keyPoint2[0].pt.x <= keyPoint2[2].pt.x) {
					keyPoint2[0].class_id = 4;
					if (keyPoint2[1].pt.x >= keyPoint2[2].pt.x) {
						keyPoint2[1].class_id = 2;
						keyPoint2[2].class_id = 3;
					}
					else {
						keyPoint2[2].class_id = 2;
						keyPoint2[1].class_id = 3;
					}
				}
				else {
					keyPoint2[0].class_id = 3;
					if (keyPoint2[1].pt.x >= keyPoint2[2].pt.x) {
						keyPoint2[1].class_id = 2;
						keyPoint2[2].class_id = 4;
					}
					else {
						keyPoint2[2].class_id = 2;
						keyPoint2[1].class_id = 4;
					}
				}
			}
			for (int k = 0; k < 4; k++) {
				for (int j = k + 1; j < 4; j++) {
					if (keyPoint2[k].pt.x == keyPoint2[j].pt.x) {
						int max = keyPoint2[k].class_id;
						if (keyPoint2[k].pt.y > keyPoint2[j].pt.y&&keyPoint2[k].class_id < keyPoint2[j].class_id) {
							keyPoint2[j].class_id = keyPoint2[j].class_id;
							keyPoint2[k].class_id = max;
						}
						else if (keyPoint2[k].pt.y < keyPoint2[j].pt.y&&keyPoint2[k].class_id < keyPoint2[j].class_id) {
							keyPoint2[k].class_id = keyPoint2[j].class_id;
							keyPoint2[j].class_id = max;
						}
						else if (keyPoint2[k].pt.y > keyPoint2[j].pt.y&&keyPoint2[k].class_id > keyPoint2[j].class_id) {
							keyPoint2[k].class_id = keyPoint2[j].class_id;
							keyPoint2[j].class_id = max;
						}
						else if (keyPoint2[k].pt.y < keyPoint2[j].pt.y&&keyPoint2[k].class_id > keyPoint2[j].class_id) {
							keyPoint2[j].class_id = keyPoint2[j].class_id;
							keyPoint2[k].class_id = max;
						}
					}
				}
			}

			Detector.detect(roi3, keyPoint3);
			while (keyPoint3.size() != 4) {
				keyPoint3.push_back(keyPoints2[0]);
			}
			keyPoint3[0].pt.x = x2[6 * p + 2] - c; keyPoint3[0].pt.y = y2[6 * p + 2] - d;
			keyPoint3[1].pt.x = x2[6 * p + 3] - c; keyPoint3[1].pt.y = y2[6 * p + 3] - d;
			keyPoint3[2].pt.x = x2[6 * p + 4] - c; keyPoint3[2].pt.y = y2[6 * p + 4] - d;
			keyPoint3[3].pt.x = x2[6 * p + 5] - c; keyPoint3[3].pt.y = y2[6 * p + 5] - d;
			if (keyPoint3[0].pt.x >= keyPoint3[1].pt.x&&keyPoint3[0].pt.x >= keyPoint3[2].pt.x&&keyPoint3[0].pt.x >= keyPoint3[3].pt.x) {
				keyPoint3[0].class_id = 1;
				if (keyPoint3[1].pt.x >= keyPoint3[2].pt.x&&keyPoint3[1].pt.x >= keyPoint3[3].pt.x) {
					keyPoint3[1].class_id = 2;
					if (keyPoint3[2].pt.x >= keyPoint3[3].pt.x) {
						keyPoint3[2].class_id = 3;
						keyPoint3[3].class_id = 4;
					}
					else {
						keyPoint3[3].class_id = 3;
						keyPoint3[2].class_id = 4;
					}
				}
				else if (keyPoint3[1].pt.x <= keyPoint3[2].pt.x&&keyPoint3[1].pt.x <= keyPoint3[3].pt.x) {
					keyPoint3[1].class_id = 4;
					if (keyPoint3[2].pt.x >= keyPoint3[3].pt.x) {
						keyPoint3[2].class_id = 2;
						keyPoint3[3].class_id = 3;
					}
					else {
						keyPoint3[3].class_id = 2;
						keyPoint3[2].class_id = 3;
					}
				}
				else {
					keyPoint3[1].class_id = 3;
					if (keyPoint3[2].pt.x >= keyPoint3[3].pt.x) {
						keyPoint3[2].class_id = 2;
						keyPoint1[3].class_id = 4;
					}
					else {
						keyPoint3[3].class_id = 2;
						keyPoint3[2].class_id = 4;
					}
				}
			}
			else if (keyPoint3[1].pt.x >= keyPoint3[0].pt.x&&keyPoint3[1].pt.x >= keyPoint3[2].pt.x&&keyPoint3[1].pt.x >= keyPoint3[3].pt.x) {
				keyPoint3[1].class_id = 1;
				if (keyPoint3[0].pt.x >= keyPoint3[2].pt.x&&keyPoint3[0].pt.x >= keyPoint3[3].pt.x) {
					keyPoint3[0].class_id = 2;
					if (keyPoint3[2].pt.x >= keyPoint3[3].pt.x) {
						keyPoint3[2].class_id = 3;
						keyPoint3[3].class_id = 4;
					}
					else {
						keyPoint3[3].class_id = 3;
						keyPoint3[2].class_id = 4;
					}
				}
				else if (keyPoint3[0].pt.x <= keyPoint3[2].pt.x&&keyPoint1[01].pt.x <= keyPoint3[3].pt.x) {
					keyPoint3[0].class_id = 4;
					if (keyPoint3[2].pt.x >= keyPoint3[3].pt.x) {
						keyPoint3[2].class_id = 2;
						keyPoint3[3].class_id = 3;
					}
					else {
						keyPoint3[3].class_id = 2;
						keyPoint3[2].class_id = 3;
					}
				}
				else {
					keyPoint3[0].class_id = 3;
					if (keyPoint3[2].pt.x >= keyPoint3[3].pt.x) {
						keyPoint3[2].class_id = 2;
						keyPoint3[3].class_id = 4;
					}
					else {
						keyPoint1[3].class_id = 2;
						keyPoint1[2].class_id = 4;
					}
				}
			}
			else if (keyPoint3[2].pt.x >= keyPoint3[0].pt.x&&keyPoint3[2].pt.x >= keyPoint3[1].pt.x&&keyPoint3[2].pt.x >= keyPoint3[3].pt.x) {
				keyPoint3[2].class_id = 1;
				if (keyPoint3[0].pt.x >= keyPoint3[1].pt.x&&keyPoint3[0].pt.x >= keyPoint3[3].pt.x) {
					keyPoint3[0].class_id = 2;
					if (keyPoint3[1].pt.x >= keyPoint3[3].pt.x) {
						keyPoint3[1].class_id = 3;
						keyPoint3[3].class_id = 4;
					}
					else {
						keyPoint3[3].class_id = 3;
						keyPoint3[1].class_id = 4;
					}
				}
				else if (keyPoint3[0].pt.x <= keyPoint3[1].pt.x&&keyPoint3[0].pt.x <= keyPoint3[3].pt.x) {
					keyPoint3[0].class_id = 4;
					if (keyPoint3[1].pt.x >= keyPoint3[3].pt.x) {
						keyPoint3[1].class_id = 2;
						keyPoint3[3].class_id = 3;
					}
					else {
						keyPoint3[3].class_id = 2;
						keyPoint3[1].class_id = 3;
					}
				}
				else {
					keyPoint3[0].class_id = 3;
					if (keyPoint3[1].pt.x >= keyPoint3[3].pt.x) {
						keyPoint3[1].class_id = 2;
						keyPoint3[3].class_id = 4;
					}
					else {
						keyPoint3[3].class_id = 2;
						keyPoint3[1].class_id = 4;
					}
				}
			}
			else if (keyPoint3[3].pt.x >= keyPoint3[0].pt.x&&keyPoint3[3].pt.x >= keyPoint3[1].pt.x&&keyPoint3[3].pt.x >= keyPoint3[2].pt.x) {
				keyPoint3[3].class_id = 1;
				if (keyPoint3[0].pt.x >= keyPoint3[1].pt.x&&keyPoint3[0].pt.x >= keyPoint3[2].pt.x) {
					keyPoint3[0].class_id = 2;
					if (keyPoint3[1].pt.x >= keyPoint3[2].pt.x) {
						keyPoint3[1].class_id = 3;
						keyPoint3[2].class_id = 4;
					}
					else {
						keyPoint3[2].class_id = 3;
						keyPoint3[1].class_id = 4;
					}
				}
				else if (keyPoint3[0].pt.x <= keyPoint3[1].pt.x&&keyPoint3[0].pt.x <= keyPoint3[2].pt.x) {
					keyPoint3[0].class_id = 4;
					if (keyPoint3[1].pt.x >= keyPoint3[2].pt.x) {
						keyPoint3[1].class_id = 2;
						keyPoint3[2].class_id = 3;
					}
					else {
						keyPoint3[2].class_id = 2;
						keyPoint3[1].class_id = 3;
					}
				}
				else {
					keyPoint3[0].class_id = 3;
					if (keyPoint3[1].pt.x >= keyPoint3[2].pt.x) {
						keyPoint3[1].class_id = 2;
						keyPoint3[2].class_id = 4;
					}
					else {
						keyPoint3[2].class_id = 2;
						keyPoint3[1].class_id = 4;
					}
				}
			}
			for (int k = 0; k < 4; k++) {
				for (int j = k + 1; j < 4; j++) {
					if (keyPoint3[k].pt.x == keyPoint3[j].pt.x) {
						int max = keyPoint3[k].class_id;
						if (keyPoint3[k].pt.y > keyPoint3[j].pt.y&&keyPoint3[k].class_id < keyPoint3[j].class_id) {
							keyPoint3[j].class_id = keyPoint3[j].class_id;
							keyPoint3[k].class_id = max;
						}
						else if (keyPoint3[k].pt.y < keyPoint3[j].pt.y&&keyPoint3[k].class_id < keyPoint3[j].class_id) {
							keyPoint3[k].class_id = keyPoint3[j].class_id;
							keyPoint3[j].class_id = max;
						}
						else if (keyPoint3[k].pt.y > keyPoint3[j].pt.y&&keyPoint3[k].class_id > keyPoint3[j].class_id) {
							keyPoint3[k].class_id = keyPoint3[j].class_id;
							keyPoint3[j].class_id = max;
						}
						else if (keyPoint3[k].pt.y < keyPoint3[j].pt.y&&keyPoint3[k].class_id > keyPoint3[j].class_id) {
							keyPoint3[j].class_id = keyPoint3[j].class_id;
							keyPoint3[k].class_id = max;
						}
					}
				}
			}

			Detector.detect(roi4, keyPoint4);
			while (keyPoint4.size() != 4) {
				keyPoint4.push_back(keyPoints1[0]);
			}
			keyPoint4[0].pt.x = x1[6 * p + 2] - m; keyPoint4[0].pt.y = y1[6 * p + 2] - n;
			keyPoint4[1].pt.x = x1[6 * p + 3] - m; keyPoint4[1].pt.y = y1[6 * p + 3] - n;
			keyPoint4[2].pt.x = x1[6 * p + 4] - m; keyPoint4[2].pt.y = y1[6 * p + 4] - n;
			keyPoint4[3].pt.x = x1[6 * p + 5] - m; keyPoint4[3].pt.y = y1[6 * p + 5] - n;
			if (keyPoint4[0].pt.x >= keyPoint4[1].pt.x&&keyPoint4[0].pt.x >= keyPoint4[1].pt.x&&keyPoint4[0].pt.x >= keyPoint4[3].pt.x) {
				keyPoint4[0].class_id = 1;
				if (keyPoint4[1].pt.x >= keyPoint4[2].pt.x&&keyPoint4[1].pt.x >= keyPoint4[3].pt.x) {
					keyPoint4[1].class_id = 2;
					if (keyPoint4[2].pt.x >= keyPoint4[3].pt.x) {
						keyPoint4[2].class_id = 3;
						keyPoint4[3].class_id = 4;
					}
					else {
						keyPoint4[3].class_id = 3;
						keyPoint4[2].class_id = 4;
					}
				}
				else if (keyPoint4[1].pt.x <= keyPoint4[2].pt.x&&keyPoint4[1].pt.x <= keyPoint4[3].pt.x) {
					keyPoint4[1].class_id = 4;
					if (keyPoint4[2].pt.x >= keyPoint4[3].pt.x) {
						keyPoint4[2].class_id = 2;
						keyPoint4[3].class_id = 3;
					}
					else {
						keyPoint4[3].class_id = 2;
						keyPoint4[2].class_id = 3;
					}
				}
				else {
					keyPoint4[1].class_id = 3;
					if (keyPoint4[2].pt.x >= keyPoint4[3].pt.x) {
						keyPoint4[2].class_id = 2;
						keyPoint4[3].class_id = 4;
					}
					else {
						keyPoint4[3].class_id = 2;
						keyPoint4[2].class_id = 4;
					}
				}
			}
			else if (keyPoint4[1].pt.x >= keyPoint4[0].pt.x&&keyPoint4[1].pt.x >= keyPoint4[2].pt.x&&keyPoint4[1].pt.x >= keyPoint4[3].pt.x) {
				keyPoint4[1].class_id = 1;
				if (keyPoint4[0].pt.x >= keyPoint4[2].pt.x&&keyPoint4[0].pt.x >= keyPoint4[3].pt.x) {
					keyPoint4[0].class_id = 2;
					if (keyPoint4[2].pt.x >= keyPoint4[3].pt.x) {
						keyPoint4[2].class_id = 3;
						keyPoint4[3].class_id = 4;
					}
					else {
						keyPoint4[3].class_id = 3;
						keyPoint4[2].class_id = 4;
					}
				}
				else if (keyPoint4[0].pt.x <= keyPoint4[2].pt.x&&keyPoint4[01].pt.x <= keyPoint4[3].pt.x) {
					keyPoint4[0].class_id = 4;
					if (keyPoint4[2].pt.x >= keyPoint4[3].pt.x) {
						keyPoint4[2].class_id = 2;
						keyPoint4[3].class_id = 3;
					}
					else {
						keyPoint4[3].class_id = 2;
						keyPoint4[2].class_id = 3;
					}
				}
				else {
					keyPoint4[0].class_id = 3;
					if (keyPoint4[2].pt.x >= keyPoint4[3].pt.x) {
						keyPoint4[2].class_id = 2;
						keyPoint4[3].class_id = 4;
					}
					else {
						keyPoint4[3].class_id = 2;
						keyPoint4[2].class_id = 4;
					}
				}
			}
			else if (keyPoint4[2].pt.x >= keyPoint4[0].pt.x&&keyPoint4[2].pt.x >= keyPoint4[1].pt.x&&keyPoint4[2].pt.x >= keyPoint4[3].pt.x) {
				keyPoint4[2].class_id = 1;
				if (keyPoint4[0].pt.x >= keyPoint4[1].pt.x&&keyPoint4[0].pt.x >= keyPoint4[3].pt.x) {
					keyPoint4[0].class_id = 2;
					if (keyPoint4[1].pt.x >= keyPoint4[3].pt.x) {
						keyPoint4[1].class_id = 3;
						keyPoint4[3].class_id = 4;
					}
					else {
						keyPoint4[3].class_id = 3;
						keyPoint4[1].class_id = 4;
					}
				}
				else if (keyPoint4[0].pt.x <= keyPoint4[1].pt.x&&keyPoint4[0].pt.x <= keyPoint4[3].pt.x) {
					keyPoint4[0].class_id = 4;
					if (keyPoint4[1].pt.x >= keyPoint4[3].pt.x) {
						keyPoint4[1].class_id = 2;
						keyPoint4[3].class_id = 3;
					}
					else {
						keyPoint4[3].class_id = 2;
						keyPoint4[1].class_id = 3;
					}
				}
				else {
					keyPoint4[0].class_id = 3;
					if (keyPoint4[1].pt.x > keyPoint4[3].pt.x) {
						keyPoint4[1].class_id = 2;
						keyPoint4[3].class_id = 4;
					}
					else {
						keyPoint4[3].class_id = 2;
						keyPoint4[1].class_id = 4;
					}
				}
			}
			else if (keyPoint4[3].pt.x >= keyPoint4[0].pt.x&&keyPoint4[3].pt.x >= keyPoint4[1].pt.x&&keyPoint4[3].pt.x >= keyPoint4[2].pt.x) {
				keyPoint4[3].class_id = 1;
				if (keyPoint4[0].pt.x >= keyPoint4[1].pt.x&&keyPoint4[0].pt.x >= keyPoint4[2].pt.x) {
					keyPoint4[0].class_id = 2;
					if (keyPoint4[1].pt.x >= keyPoint4[2].pt.x) {
						keyPoint4[1].class_id = 3;
						keyPoint4[2].class_id = 4;
					}
					else {
						keyPoint4[2].class_id = 3;
						keyPoint4[1].class_id = 4;
					}
				}
				else if (keyPoint4[0].pt.x <= keyPoint4[1].pt.x&&keyPoint4[0].pt.x <= keyPoint4[2].pt.x) {
					keyPoint4[0].class_id = 4;
					if (keyPoint4[1].pt.x >= keyPoint4[2].pt.x) {
						keyPoint4[1].class_id = 2;
						keyPoint4[2].class_id = 3;
					}
					else {
						keyPoint4[2].class_id = 2;
						keyPoint4[1].class_id = 3;
					}
				}
				else {
					keyPoint4[0].class_id = 3;
					if (keyPoint4[1].pt.x >= keyPoint4[2].pt.x) {
						keyPoint4[1].class_id = 2;
						keyPoint4[2].class_id = 4;
					}
					else {
						keyPoint4[2].class_id = 2;
						keyPoint4[1].class_id = 4;
					}
				}
			}
			for (int k = 0; k < 4; k++) {
				for (int j = k + 1; j < 4; j++) {
					if (keyPoint4[k].pt.x == keyPoint4[j].pt.x) {
						int max = keyPoint4[k].class_id;
						if (keyPoint4[k].pt.y > keyPoint4[j].pt.y&&keyPoint2[k].class_id < keyPoint4[j].class_id) {
							keyPoint4[j].class_id = keyPoint4[j].class_id;
							keyPoint4[k].class_id = max;
						}
						else if (keyPoint4[k].pt.y < keyPoint4[j].pt.y&&keyPoint4[k].class_id < keyPoint4[j].class_id) {
							keyPoint4[k].class_id = keyPoint4[j].class_id;
							keyPoint4[j].class_id = max;
						}
						else if (keyPoint4[k].pt.y > keyPoint4[j].pt.y&&keyPoint4[k].class_id > keyPoint4[j].class_id) {
							keyPoint4[k].class_id = keyPoint4[j].class_id;
							keyPoint4[j].class_id = max;
						}
						else if (keyPoint4[k].pt.y < keyPoint4[j].pt.y&&keyPoint4[k].class_id > keyPoint4[j].class_id) {
							keyPoint4[j].class_id = keyPoint4[j].class_id;
							keyPoint4[k].class_id = max;
						}
					}
				}
			}

		}
		else if (i % 2 != 0) {
			int p = (i - 19) / 2;
			GoodFeaturesToTrackDetector Detector(2);
			Detector.detect(roi1, keyPoint1);
			if (keyPoint1.size() != 2) {
				keyPoints1[0].pt.x = x1[p * 2 + 1] - e; keyPoint2[0].pt.y = y1[p * 2 + 1] - f;
				keyPoint1.push_back(keyPoints2[0]);
			}
			keyPoint1[0].pt.x = x1[6 * p] - a; keyPoint1[0].pt.y = y1[6 * p] - b;
			keyPoint1[1].pt.x = x1[6 * p + 1] - a; keyPoint1[1].pt.y = y1[6 * p + 1] - b;
			if (keyPoint1[0].pt.x < keyPoint1[1].pt.x) {
				keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
			}
			else if (keyPoint1[0].pt.x > keyPoint1[1].pt.x) {
				keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
			}
			else if (keyPoint1[0].pt.x == keyPoint1[1].pt.x) {
				if (keyPoint1[0].pt.y > keyPoint1[1].pt.y) {
					keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
				}
				else
					keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
			}

			Detector.detect(roi2, keyPoint2);
			if (keyPoint2.size() != 2) {
				keyPoints2[0].pt.x = x2[p * 2 + 1] - e; keyPoint2[0].pt.y = y2[p * 2 + 1] - f;
				keyPoint2.push_back(keyPoints2[0]);
			}
			keyPoint2[0].pt.x = x2[6 * p] - e; keyPoint2[0].pt.y = y2[6 * p] - f;
			keyPoint2[1].pt.x = x2[6 * p + 1] - e; keyPoint2[1].pt.y = y2[6 * p + 1] - f;
			if (keyPoint2[0].pt.x < keyPoint2[1].pt.x) {
				keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
			}
			else if (keyPoint2[0].pt.x > keyPoint2[1].pt.x) {
				keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
			}
			else if (keyPoint2[0].pt.x == keyPoint2[1].pt.x) {
				if (keyPoint2[0].pt.y > keyPoint2[1].pt.y) {
					keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
				}
				else
					keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
			}

			Detector.detect(roi3, keyPoint3);
			if (keyPoint3.size() != 2) {
				keyPoints2[0].pt.x = x2[p * 2 + 1] - i; keyPoint3[0].pt.y = y2[p * 2 + 1] - d;
				keyPoint3.push_back(keyPoints2[0]);
			}
			keyPoint3[0].pt.x = x2[6 * p] - c; keyPoint3[0].pt.y = y2[6 * p] - d;
			keyPoint3[1].pt.x = x2[6 * p + 1] - c; keyPoint3[1].pt.y = y2[6 * p + 1] - d;
			if (keyPoint3[0].pt.x < keyPoint3[1].pt.x) {
				keyPoint3[0].class_id = 1;  keyPoint3[1].class_id = 2;
			}
			else if (keyPoint3[0].pt.x > keyPoint3[1].pt.x) {
				keyPoint3[0].class_id = 2;  keyPoint3[1].class_id = 1;
			}
			else if (keyPoint3[0].pt.x == keyPoint3[1].pt.x) {
				if (keyPoint3[0].pt.y > keyPoint3[1].pt.y) {
					keyPoint3[0].class_id = 1;  keyPoint3[1].class_id = 2;
				}
				else
					keyPoint3[0].class_id = 2;  keyPoint3[1].class_id = 1;
			}

			Detector.detect(roi4, keyPoint4);
			if (keyPoint4.size() != 2) {
				keyPoints1[0].pt.x = x1[p * 2 + 1] - e; keyPoint2[0].pt.y = y1[p * 2 + 1] - f;
				keyPoint4.push_back(keyPoints2[0]);
			}
			keyPoint4[0].pt.x = x1[6 * p] - m; keyPoint4[0].pt.y = y1[6 * p] - n;
			keyPoint4[1].pt.x = x1[6 * p + 1] - m; keyPoint4[1].pt.y = y1[6 * p + 1] - n;
			if (keyPoint4[0].pt.x < keyPoint4[1].pt.x) {
				keyPoint4[0].class_id = 1;  keyPoint4[1].class_id = 2;
			}
			else if (keyPoint4[0].pt.x > keyPoint4[1].pt.x) {
				keyPoint4[0].class_id = 2;  keyPoint4[1].class_id = 1;
			}
			else if (keyPoint4[0].pt.x == keyPoint4[1].pt.x) {
				if (keyPoint4[0].pt.y > keyPoint4[1].pt.y) {
					keyPoint4[0].class_id = 1;  keyPoint4[1].class_id = 2;
				}
				else
					keyPoint4[0].class_id = 2;  keyPoint4[1].class_id = 1;
			}

		}
	}

	else if (i >= 38 && i < 68) {
		int p = i - 38;
		ifstream infile1, infile2, infile3, infile4;
		string filename;
		filename = "E:\\Biyesheji\\Detection\\Detection\\match corner\\";
		infile1.open(filename + "result13(1&3&4).txt", ios::in);
		infile2.open(filename + "result23(2&3&4).txt", ios::in);
		infile3.open(filename + "result33(1&3&4).txt", ios::in);
		infile4.open(filename + "result43(1&3&4).txt", ios::in);//导入目标角点坐标
		double x1[200], y1[200], x2[200], y2[200], x3[200], y3[200], x4[200], y4[200];;
		while (!infile1.eof()) {
			for (int j = 0; j < 30; j++)
			{
				infile1 >> x1[j] >> y1[j];
			}
		}
		while (!infile2.eof()) {
			for (int j = 0; j < 30; j++)
			{
				infile2 >> x2[j] >> y2[j];
			}
		}
		while (!infile3.eof()) {
			for (int j = 0; j < 30; j++)
			{
				infile3 >> x3[j] >> y3[j];
			}
		}
		while (!infile4.eof()) {
			for (int j = 0; j < 30; j++)
			{
				infile4 >> x4[j] >> y4[j];
			}
		}
		GoodFeaturesToTrackDetector Detector(1);
		Detector.detect(roi1, keyPoint1);
		Detector.detect(roi2, keyPoint2);
		Detector.detect(roi3, keyPoint3);
		Detector.detect(roi4, keyPoint4);
		keyPoint1[0].pt.x = x1[p] - a; keyPoint1[0].pt.y = y1[p] - b;
		keyPoint2[0].pt.x = x2[p] - e; keyPoint2[0].pt.y = y2[p] - f;
		keyPoint3[0].pt.x = x3[p] - c; keyPoint3[0].pt.y = y3[p] - d;
		keyPoint4[0].pt.x = x4[p] - m; keyPoint4[0].pt.y = y4[p] - n;
		keyPoint1[0].class_id = i;
		keyPoint2[0].class_id = i;
		keyPoint3[0].class_id = i;
		keyPoint4[0].class_id = i;
	}

	else if (i >= 68 && i < 75) {
		ifstream infile1, infile2, infile3, infile4;
		string filename;
		filename = "E:\\Biyesheji\\Detection\\Detection\\match corner\\";
		infile1.open(filename + "result14(1&3&4).txt", ios::in);
		infile2.open(filename + "result24(2&3&4).txt", ios::in);
		infile3.open(filename + "result34(1&3&4).txt", ios::in);
		infile4.open(filename + "result44(1&3&4).txt", ios::in);//导入目标角点坐标
		double x1[200], y1[200], x2[200], y2[200], x3[200], y3[200], x4[200], y4[200];
		while (!infile1.eof()) {
			for (int j = 0; j < 14; j++)
			{
				infile1 >> x1[j] >> y1[j];
			}
		}
		while (!infile2.eof()) {
			for (int j = 0; j < 14; j++)
			{
				infile2 >> x2[j] >> y2[j];
			}
		}
		while (!infile3.eof()) {
			for (int j = 0; j < 14; j++)
			{
				infile3 >> x3[j] >> y3[j];
			}
		}
		while (!infile4.eof()) {
			for (int j = 0; j < 14; j++)
			{
				infile4 >> x4[j] >> y4[j];
			}
		}
		int p = i - 68;
		GoodFeaturesToTrackDetector Detector(2);
		Detector.detect(roi1, keyPoint1);
		if (keyPoint1.size() != 2) {
			keyPoints1[0].pt.x = x1[p * 2 + 1] - e; keyPoint1[0].pt.y = y2[p * 2 + 1] - f;
			keyPoint1.push_back(keyPoints1[0]);
		}
		keyPoint1[0].pt.x = x1[p * 2] - a; keyPoint1[0].pt.y = y1[p * 2] - b;
		keyPoint1[1].pt.x = x1[p * 2 + 1] - a; keyPoint1[1].pt.y = y1[p * 2 + 1] - b;
		if (keyPoint1[0].pt.x < keyPoint1[1].pt.x) {
			keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
		}
		else if (keyPoint1[0].pt.x > keyPoint1[1].pt.x) {
			keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
		}
		else if (keyPoint1[0].pt.x == keyPoint1[1].pt.x) {
			if (keyPoint1[0].pt.y > keyPoint1[1].pt.y) {
				keyPoint1[0].class_id = 1;  keyPoint1[1].class_id = 2;
			}
			else
				keyPoint1[0].class_id = 2;  keyPoint1[1].class_id = 1;
		}

		Detector.detect(roi2, keyPoint2);
		if (keyPoint2.size() != 2) {
			keyPoints2[0].pt.x = x2[p * 2 + 1] - e; keyPoint2[0].pt.y = y2[p * 2 + 1] - f;
			keyPoint2.push_back(keyPoints2[0]);
		}
		keyPoint2[0].pt.x = x2[p * 2] - e; keyPoint2[0].pt.y = y2[p * 2] - f;
		keyPoint2[1].pt.x = x2[p * 2 + 1] - e; keyPoint2[1].pt.y = y2[p * 2 + 1] - f;
		if (keyPoint2[0].pt.x < keyPoint2[1].pt.x) {
			keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
		}
		else if (keyPoint2[0].pt.x > keyPoint2[1].pt.x) {
			keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
		}
		else if (keyPoint2[0].pt.x == keyPoint2[1].pt.x) {
			if (keyPoint2[0].pt.y > keyPoint2[1].pt.y) {
				keyPoint2[0].class_id = 1;  keyPoint2[1].class_id = 2;
			}
			else
				keyPoint2[0].class_id = 2;  keyPoint2[1].class_id = 1;
		}

		Detector.detect(roi3, keyPoint3);
		if (keyPoint3.size() != 2) {
			keyPoint3.push_back(keyPoints2[0]);
		}
		keyPoint3[0].pt.x = x3[p * 2] - c; keyPoint3[0].pt.y = y3[p * 2] - d;
		keyPoint3[1].pt.x = x3[p * 2 + 1] - c; keyPoint3[1].pt.y = y3[p * 2 + 1] - d;
		if (keyPoint3[0].pt.x < keyPoint3[1].pt.x) {
			keyPoint3[0].class_id = 1;  keyPoint3[1].class_id = 2;
		}
		else if (keyPoint3[0].pt.x > keyPoint3[1].pt.x) {
			keyPoint3[0].class_id = 2;  keyPoint3[1].class_id = 1;
		}
		else if (keyPoint3[0].pt.x == keyPoint3[1].pt.x) {
			if (keyPoint3[0].pt.y > keyPoint3[1].pt.y) {
				keyPoint3[0].class_id = 1;  keyPoint3[1].class_id = 2;
			}
			else
				keyPoint3[0].class_id = 2;  keyPoint3[1].class_id = 1;
		}


		Detector.detect(roi4, keyPoint4);
		if (keyPoint4.size() != 2) {
			keyPoints1[0].pt.x = x1[p * 2 + 1] - e; keyPoint4[0].pt.y = y2[p * 2 + 1] - f;
			keyPoint4.push_back(keyPoints1[0]);
		}
		keyPoint4[0].pt.x = x1[p * 2] - m; keyPoint4[0].pt.y = y1[p * 2] - n;
		keyPoint4[1].pt.x = x1[p * 2 + 1] - m; keyPoint4[1].pt.y = y1[p * 2 + 1] - n;
		if (keyPoint4[0].pt.x < keyPoint4[1].pt.x) {
			keyPoint4[0].class_id = 1;  keyPoint4[1].class_id = 2;
		}
		else if (keyPoint4[0].pt.x > keyPoint4[1].pt.x) {
			keyPoint4[0].class_id = 2;  keyPoint4[1].class_id = 1;
		}
		else if (keyPoint4[0].pt.x == keyPoint4[1].pt.x) {
			if (keyPoint4[0].pt.y > keyPoint4[1].pt.y) {
				keyPoint4[0].class_id = 1;  keyPoint4[1].class_id = 2;
			}
			else
				keyPoint4[0].class_id = 2;  keyPoint4[1].class_id = 1;
		}

	}
}
