#include "nightshift.h"
#include "ui_nightshift.h"


NightShift::NightShift(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::NightShift)
{
    //app config :
    QIcon appIcon(":/logo/assets/logo.png"); // loading icon
    QString LuaPath = QCoreApplication::applicationDirPath() + "/plugin.lua"; // lua formater config
    this->L = this->luaFile->InitLua(LuaPath);  //lua initalize :

    ui->setupUi(this);
    this->showMaximized();
    this->setWindowIcon(appIcon) ;


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
    //freeing the lua space :
    lua_close(L);
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

    connect(textEdit, &QPlainTextEdit::textChanged, this, &NightShift::LuaTextformater);

    QVBoxLayout* layout = new QVBoxLayout(newTabWidget);
    layout->addWidget(textEdit);
    layout->setContentsMargins(0, 0, 0, 0);
    newTabWidget->setLayout(layout);
}


// lua cpp documentation :

void NightShift::LuaTextformater() {

    // Find the current QPlainTextEdit
    QPlainTextEdit *textEdit = this->ui->tabWidget->currentWidget()->findChild<QPlainTextEdit *>();
    QString content = textEdit->toPlainText();

    // Save the current cursor position
    QTextCursor cursor = textEdit->textCursor();
    int cursorPosition = cursor.position();

    int cursorRow = cursor.blockNumber();
    int cursorColumn = cursor.positionInBlock();
    QString currentLine = cursor.block().text();

    //blocking infinite loops:
    disconnect(textEdit, &QPlainTextEdit::textChanged, this, &NightShift::LuaTextformater);


    //lua function config
    lua_getglobal(this->L, "format_text"); // format_text to change !

    if (!lua_isfunction(this->L, -1)) {
        qDebug() << "Lua function 'format_text' not found or not a function";
        return;
    }

    lua_pushstring(this->L, content.toUtf8().constData());
    lua_pushinteger(this->L, cursorRow);
    lua_pushinteger(this->L, cursorColumn);
    lua_pushstring(this->L, currentLine.toUtf8().constData());

    if (lua_pcall(this->L, 4, 1, 0) != LUA_OK) {
        qDebug() << "Lua error:" << lua_tostring(this->L, -1);
        return;
    }

    const char *result = lua_tostring(this->L, -1);
    if (result) {
        textEdit->setPlainText(QString::fromUtf8(result));

        // Restore the cursor position
        cursor.setPosition(cursorPosition);
        textEdit->setTextCursor(cursor);
    } else {
        qDebug() << "Lua function returned nil";
    }

    // Reconnect the signal
    connect(textEdit, &QPlainTextEdit::textChanged, this, &NightShift::LuaTextformater);
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



