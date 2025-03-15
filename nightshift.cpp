#include "nightshift.h"
#include "ui_nightshift.h"
#include <QResizeEvent>
#include <QVBoxLayout>
#include <QPlainTextEdit>
#include <QStack>


NightShift::NightShift(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::NightShift)
{
    //app config :
    QIcon appIcon(":/logo/assets/logo.png");
    ui->setupUi(this);
    this->showMaximized();
    this->setWindowIcon(appIcon) ;

    //tab widget config :

    // rendering the starting adding widget
    this->ui->tabWidget->setTabText(0, "+");


    //first tab config
    int widgetSize = this->ui->tabWidget->count() ;
    QWidget *FirstWidget = new QWidget();
    this->RenderTextArea(FirstWidget) ;
    this->ui->tabWidget->insertTab(widgetSize-1,FirstWidget ,"New File * ") ;
    this->ui->tabWidget->setCurrentIndex(widgetSize-1);

    //signals :
    connect(this->ui->tabWidget, &QTabWidget::currentChanged, this, &NightShift::AddTab);

}

NightShift::~NightShift()
{
    delete ui;
}


void NightShift::RenderTextArea(QWidget* newTabWidget) {
    QPlainTextEdit* textEdit = new QPlainTextEdit(newTabWidget);
    QFont jetBrainsFont("JetBrains Mono");

    textEdit->setStyleSheet(
        "QPlainTextEdit {"
        "   color: white;"
        "   font-size: 15px;"
        "   padding: 30px 30px 5px 30px;"
        "   border: 0;"
        "}"
        );

    textEdit->setTabStopDistance(40);
    textEdit->setPlaceholderText("Write your clean code here :) ");
    textEdit->setFont(jetBrainsFont);

    connect(textEdit, &QPlainTextEdit::textChanged, this, &NightShift::onTextChanged);

    QVBoxLayout* layout = new QVBoxLayout(newTabWidget);
    layout->addWidget(textEdit);
    layout->setContentsMargins(0, 0, 0, 0);
    newTabWidget->setLayout(layout);
}


void NightShift::onTextChanged() {

    QPlainTextEdit *textEdit = this->ui->tabWidget->currentWidget()->findChild<QPlainTextEdit *>();
    if (!textEdit) return;

    QString text = textEdit->toPlainText();
    QTextCursor cursor = textEdit->textCursor();
    int cursorPos = cursor.position();
    this->autocompletion(text,cursorPos,cursor,textEdit);
}



//adding a tab to the tab widget
void NightShift::AddTab(int index ){
    int TabwidgetSize = this->ui->tabWidget->count() ;

    if(index == TabwidgetSize-1){
        QWidget *newTabWidget = new QWidget();

        // to render my textarea I used a function name renderTextarea :
        this->RenderTextArea(newTabWidget) ;
        this->ui->tabWidget->insertTab( TabwidgetSize - 1 , newTabWidget,"New File * ") ;
        this->ui->tabWidget->setCurrentIndex(TabwidgetSize - 1 ) ;
    }

}


//resising the text field when I resize the window
void NightShift::resizeEvent(QResizeEvent *event)
{
    QSize windowSize = event->size();
    int margin = 70;
    int tabwidgetwidth = windowSize.width() * 0.86;
    int tabwidgetHeight = windowSize.height() - margin;
    int xPos = windowSize.width() - tabwidgetwidth;
    int yPos = margin;

    this->ui->tabWidget->setGeometry(xPos, yPos, tabwidgetwidth, tabwidgetHeight);


    QMainWindow::resizeEvent(event);
}


//typing autocompletion :
void NightShift::autocompletion(QString text ,int cursorPos , QTextCursor cursor , QPlainTextEdit *textEdit) {
    static QString previousText = "";
    bool isDeleting = (text.length() < previousText.length());
    previousText = text;

    if (isDeleting) return;

    if (cursorPos > 0 && text.length() >= cursorPos) {
        QChar insertedChar = text.at(cursorPos - 1);
        static const QHash<QChar, QChar> bracketPairs = {
            {'{', '}'},
            {'[', ']'},
            // {'(', ')'}
        };

        if (bracketPairs.contains(insertedChar)) {
            textEdit->insertPlainText(QString(bracketPairs[insertedChar]));
            if(insertedChar == '{') {
                cursor.movePosition(QTextCursor::Left);
            }
            textEdit->setTextCursor(cursor);
        }
    }
}


