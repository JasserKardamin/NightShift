/********************************************************************************
** Form generated from reading UI file 'nightshift.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NIGHTSHIFT_H
#define UI_NIGHTSHIFT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NightShift
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *tab;

    void setupUi(QMainWindow *NightShift)
    {
        if (NightShift->objectName().isEmpty())
            NightShift->setObjectName("NightShift");
        NightShift->resize(1290, 643);
        NightShift->setStyleSheet(QString::fromUtf8("background-color:#1e1e1e;\n"
""));
        centralwidget = new QWidget(NightShift);
        centralwidget->setObjectName("centralwidget");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(280, 150, 751, 411));
        tabWidget->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        tabWidget->setStyleSheet(QString::fromUtf8("QTabWidget::pane { \n"
"	border-top: 1px solid #2c2c2c; \n"
"	border-left : 1px solid #2c2c2c ; \n"
"}\n"
"\n"
"QTabBar::tab {\n"
"	border: 1px solid #2c2c2c;\n"
"	color : white ; \n"
"	font-size : 13px ; \n"
"	background-color: #2f2f2f ; \n"
"	padding: 8px 70px 8px 15px; \n"
"}\n"
"\n"
"QTabBar::tab:selected {\n"
"	border : 1px solid #2c2c2c ;\n"
"	background-color: #1e1e1e;  \n"
"	border-bottom : 0 ;  \n"
"}\n"
"\n"
"QTabWidget::tab-bar {\n"
"    top :1px ;\n"
"}\n"
"\n"
"\n"
"QTabBar::tab:last {\n"
"   padding: 8px 15px 8px 15px;\n"
"}\n"
"\n"
""));
        tab = new QWidget();
        tab->setObjectName("tab");
        tabWidget->addTab(tab, QString());
        NightShift->setCentralWidget(centralwidget);

        retranslateUi(NightShift);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(NightShift);
    } // setupUi

    void retranslateUi(QMainWindow *NightShift)
    {
        NightShift->setWindowTitle(QCoreApplication::translate("NightShift", "NightShift", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("NightShift", "Page", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NightShift: public Ui_NightShift {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NIGHTSHIFT_H
