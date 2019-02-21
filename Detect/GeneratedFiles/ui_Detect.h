/********************************************************************************
** Form generated from reading UI file 'Detect.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DETECT_H
#define UI_DETECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DetectClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *DetectClass)
    {
        if (DetectClass->objectName().isEmpty())
            DetectClass->setObjectName(QStringLiteral("DetectClass"));
        DetectClass->resize(600, 400);
        menuBar = new QMenuBar(DetectClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        DetectClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(DetectClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        DetectClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(DetectClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        DetectClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(DetectClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        DetectClass->setStatusBar(statusBar);

        retranslateUi(DetectClass);

        QMetaObject::connectSlotsByName(DetectClass);
    } // setupUi

    void retranslateUi(QMainWindow *DetectClass)
    {
        DetectClass->setWindowTitle(QApplication::translate("DetectClass", "Detect", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DetectClass: public Ui_DetectClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DETECT_H
