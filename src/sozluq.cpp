/*
Ana pencere, menüler ve sekmeler 
Sekmeler içine en2trTab ve tr2enTab objeleri olacak 
*/

#include <QApplication>

#include "sozluq.h"

Sozluq::Sozluq(QWidget *parent)
        : QMainWindow(parent)
{

// menubar ve menüler 
menubar = new QMenuBar(this);
hakkindaMenu = new QMenu(trUtf8("Hakkında"));
sozluqHakkindaMenu = new QAction(trUtf8("SozluQ Hakkında"),menubar);
qtHakkindaMenu = new QAction(trUtf8("Qt Hakkında"),menubar);
cikisMenu = new QAction(trUtf8("Çıkış"),menubar);

menubar->addMenu(hakkindaMenu);
hakkindaMenu->addAction(sozluqHakkindaMenu);
hakkindaMenu->addAction(qtHakkindaMenu);
menubar->addAction(cikisMenu);


//sekmeler
sekmeler = new QTabWidget(this);
sekmeler->setGeometry(0,50,400,300);



en2trTab = new trOrEnTab("en2tr");
tr2enTab = new trOrEnTab("tr2en");
sekmeler->addTab(en2trTab,trUtf8("İngilizce->Türkçe"));
sekmeler->addTab(tr2enTab,trUtf8("Türkçe->İngilizce"));



//menubar ve sekmeleri ana pencereye ata
setCentralWidget(sekmeler);
setMenuBar(menubar);
setWindowTitle(tr(".: sozluQ :."));



// menü görevleri
QObject::connect(qtHakkindaMenu, SIGNAL(triggered()),
                     this, SLOT(slotQtHakkinda()));

QObject::connect(cikisMenu, SIGNAL(triggered()),
                     this, SLOT(slotCikis()));

QObject::connect(sozluqHakkindaMenu, SIGNAL(triggered()),
                     this, SLOT(slotSozluqHakkinda()));

}

void Sozluq::slotQtHakkinda(){
qApp->aboutQt();
}

void Sozluq::slotSozluqHakkinda(){
sh = new sozluqHakkinda(this);
sh->show();
}


void Sozluq::slotCikis(){
qApp->quit();
}


trOrEnTab::trOrEnTab(QString hangisi,QWidget *parent)
        : QWidget(parent)
{ //ingilizceden turkceye ceviri sekmesi



//arama kutusunu yerlestir
aramaKutusu = new QComboBox(this);
aramaKutusu->setGeometry(50,20,200,25);
aramaKutusu->setEditable(true);
aramaKutusu->setAutoCompletion(false);
aramaKutusu->setFocus();

//sonuc ekranini yerlestir
sonucEkrani = new QTextEdit(this);
sonucEkrani->setGeometry(10,50,275,400);
sonucEkrani->setReadOnly(true);


//arama kutusunun icini doldur
myDir.setPath(qApp->applicationDirPath());
myDir.cd("veri");


tr2enList.append("");
file.setFileName(myDir.absoluteFilePath(hangisi+"_liste"));
if (file.open(QIODevice::ReadOnly)) {
in.setDevice(&file);
}
while (!in.atEnd()) {
line = in.readLine();
tr2enList.append(line.toLower());
}
file.close();
tr2enList.sort();
aramaKutusu->addItems(tr2enList);

//en2tr dizinine git 
myDir.cd(hangisi);
}

void trOrEnTab::keyPressEvent(QKeyEvent *e){

if(e->key()==Qt::Key_Return) {
//Enter'a basilinca sonucu ekrana getir
//metnin ilk harfine uygun dil dosyasını açıp
//icinde eşlenen metin varsa ekrana getirir
//yoksa hata mesajı gösterilir

if(aramaKutusu->currentText().length()>0){

sonucEkrani->clear();

//ilk harfe gore dosya adini belirle
QString ilkHarf=aramaKutusu->currentText().at(0);
file.setFileName(myDir.absoluteFilePath(ilkHarf));


QString arama;
arama=aramaKutusu->currentText();
arama.append(":|:");
int count=0; //bulundu mu bulunmadi mi ?


//dosyayi ac
if (!file.open(QIODevice::ReadOnly)) {
sonucEkrani->insertHtml(trUtf8("Sonuç bulunadı :: Böyle bir içerik yok"));

}
else{
in.setDevice(&file);


//dosya icinde arama kutusundaki kelime bulundu mu ?
while (!in.atEnd()) {
line = in.readLine().toLower();

if (line.startsWith(arama.toLower())) {
count++;
line.replace(arama,"");
line.toUtf8();
sonucEkrani->insertHtml(line+"<hr/> <br />");
}
}
//eger sonuc bulunamamissa
if(count<1) sonucEkrani->insertPlainText(trUtf8("Sonuc Bulunamadı"));
file.close();
}

}
}
}




sozluqHakkinda::sozluqHakkinda(QWidget *parent)
        : QDialog(parent)
{ //sozluq hakkinda
hakkinda = new QLabel(this);
hakkinda->setText(trUtf8("<h3 align=\"center\"> SozluQ (alfa 1)</h3> <center>Türkçe İngilizce Sözlük <br />Qt 4.x kütüphaneleri kullanılarak yazılmıştır. <br />Uygulama GNU/GPL lisansı şartları altında dağıtılabilir.<br /> Sözlük veritabanı <br/><a href=\"http://forum.ceviz.net/showthread.php?s=&threadid=32684\">http://forum.ceviz.net/showthread.php?s=&threadid=32684</a> <br />adresinden alınmıştır<br /></center> "));
hakkinda->setGeometry(0,0,400,250);
hakkinda->setAlignment(Qt::AlignTop);
resize(400,250);

setWindowTitle(trUtf8(".: SozluQ Hakkında :."));
hakkinda->show();


}



void sozluqHakkinda::keyPressEvent(QKeyEvent *e){
//easter egg, kinder surpriz yumurta hesaabı

if((surprizYumurta.length()<1)&&(e->key()==Qt::Key_K)) {surprizYumurta="K";}

else if((surprizYumurta=="K") && (e->key()==Qt::Key_O)){ surprizYumurta="KO";}

else if((surprizYumurta=="KO") && (e->key()==Qt::Key_N)){ surprizYumurta="KON";}

else if((surprizYumurta=="KON") && (e->key()==Qt::Key_T)){ surprizYumurta="KONT";}

else { surprizYumurta="";}

if(surprizYumurta=="KONT") {
setWindowTitle("KONT ;-)");
surprizYumurta="";
}




}
