#ifndef NIGHTSHIFT_H
#define NIGHTSHIFT_H

#include <QMainWindow>
#include <QTextCursor>
#include <QPlainTextEdit>

QT_BEGIN_NAMESPACE
namespace Ui {
class NightShift;
}
QT_END_NAMESPACE

class NightShift : public QMainWindow
{
    Q_OBJECT

private slots:
    void AddTab(int index) ;
    void onTextChanged();


public:
    NightShift(QWidget *parent = nullptr);
    ~NightShift();

protected:
    void resizeEvent(QResizeEvent *event) override;
    void RenderTextArea(QWidget* newTabWidget) ;
    void autocompletion(QString text ,int cursorPos , QTextCursor cursor , QPlainTextEdit *textEdit) ;

private:
    Ui::NightShift *ui;
};
#endif // NIGHTSHIFT_H
