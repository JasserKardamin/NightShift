#ifndef NIGHTSHIFT_H
#define NIGHTSHIFT_H

#include <lua.hpp>
#include "luaplugins.h"

#include <QMainWindow>
#include <QTextCursor>
#include <QPlainTextEdit>
#include <QResizeEvent>
#include <QVBoxLayout>
#include <QStack>
#include <QTextBlock>



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
    void LuaTextformater();


public:
    NightShift(QWidget *parent = nullptr);
    ~NightShift();

protected:
    void resizeEvent(QResizeEvent *event) override;
    void RenderTextArea(QWidget* newTabWidget ) ;

private:
    Ui::NightShift *ui;
    luaPlugins *luaFile ;
    lua_State *L;
};
#endif // NIGHTSHIFT_H
