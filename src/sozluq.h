#ifndef SOZLUQ_H
#define SOZLUQ_H

#include <QWidget>
#include <QTabBar>
#include <QTabWidget>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QKeyEvent>
#include <QComboBox>
#include <QTextEdit>
#include <QTextStream>
#include <QFile>
#include <QDir>
#include <QLabel>
#include <QDialog>


class trOrEnTab : public QWidget
{
Q_OBJECT
public:
trOrEnTab(QString hangisi="en2tr",QWidget *parent=0);

QDir myDir;
QString line;
QTextStream in;
QFile file;
QStringList tr2enList;

QComboBox *aramaKutusu;

QTextEdit *sonucEkrani;

protected:
void keyPressEvent (QKeyEvent *e);

};




class sozluqHakkinda : public QDialog
{
Q_OBJECT
public:
sozluqHakkinda(QWidget *parent=0);

QString surprizYumurta;
QLabel *hakkinda;
protected:
void keyPressEvent (QKeyEvent *e);

};


class Sozluq : public QMainWindow
{
Q_OBJECT
public:
Sozluq( QWidget *parent=0);


QMenuBar *menubar;

QMenu *hakkindaMenu;
QAction *sozluqHakkindaMenu;
QAction *qtHakkindaMenu;
QAction *cikisMenu;

QTabWidget *sekmeler;

trOrEnTab *en2trTab;
trOrEnTab *tr2enTab;

sozluqHakkinda *sh;
public slots:
void slotQtHakkinda();
void slotSozluqHakkinda();
void slotCikis();

};

#endif
