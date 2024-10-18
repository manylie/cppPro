#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QProcess>
#include <QDebug>
#include <QFileDialog>
#include <QLineEdit>

class MainWindow : public QMainWindow
{
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void b1Clicked();
    void b2Clicked();
    void b3Clicked();
    void b4Clicked();
    void b5Clicked();
    void b6Clicked();
private:
    QLabel* l1;
    QLabel* lb2;
    QPushButton* btn1;
    QLineEdit* lineGit;
    QLineEdit* fileX;
    QLineEdit* inex2;
    QWidget *mainWidget;
    QVBoxLayout *layout;
    QHBoxLayout *l2;
    QHBoxLayout *l3;
    QHBoxLayout *l4;
    QHBoxLayout *l5;
    QHBoxLayout *l6;
    QLabel* myLabel(const QString &text, QLayout *layout);
    QPushButton* newBtnX(const QString &text,void(MainWindow::*slot)() ,QLayout *layout);
    QLineEdit* lineX(const QString &text, QLayout *layout);
};
MainWindow::~MainWindow(){}
QLabel* MainWindow:: myLabel(const QString &text, QLayout *layout){
    QLabel *label = new QLabel (text,this);
    layout->addWidget(label);
    return label;
}
QLineEdit* MainWindow::lineX(const QString &text, QLayout *layout){
    QLineEdit *label = new QLineEdit (text,this);
    layout->addWidget(label);
    return label;
}
QPushButton* MainWindow::newBtnX(const QString &text, void (MainWindow::*slot)(), QLayout *layout){
    QPushButton *button= new QPushButton(text,this);
    connect(button, &QPushButton::clicked,this, slot);
    layout->addWidget(button);
    return button;
}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Crear el widget central
    mainWidget = new QWidget(this);  // Cambiar el nombre a 'mainWidget'
    setCentralWidget(mainWidget);

    layout = new QVBoxLayout();
    l2 = new QHBoxLayout();
    l3 = new QHBoxLayout();
    l4 = new QHBoxLayout();
    l5 = new QHBoxLayout();
    l6 = new QHBoxLayout();
    layout->addLayout(l2);
    lb2=myLabel("path",layout);
    layout->addLayout(l6);
    layout->addLayout(l3);
    layout->addLayout(l4);
    layout->addLayout(l5);
    l1 = myLabel("<a href=\"https://github.com/manylie/cppPro/commits/master\">View Commits</a>",l2);
    l1->setOpenExternalLinks(true);
    newBtnX("file",&MainWindow::b2Clicked,l2);
    fileX=lineX("main.cpp",l4);
    btn1=newBtnX("addFile",&MainWindow::b1Clicked,l4);    
    btn1->setEnabled(0);
    lineGit=lineX("githb.com/repositorio",l6);
    newBtnX("online",&MainWindow::b6Clicked,l6);
    inex2=lineX("miRamax",l3);
    newBtnX("branch",&MainWindow::b5Clicked,l3);  
    newBtnX("commit",&MainWindow::b4Clicked,l5);
    newBtnX("push",&MainWindow::b3Clicked,l5);
    mainWidget->setLayout(layout);
}
void MainWindow::b6Clicked()
{
    QProcess process;
    QString tx= lineGit->text();
    process.start("git",QStringList()<<"remote" << "add" << "origin" <<tx);
    if (!process.waitForFinished()){
        qDebug()<<"error al ejecutar git remote"<< process.errorString();
        return;
    }
    QString output = process.readAllStandardOutput();
    QString errorOutput= process.readAllStandardError();
    if(!errorOutput.isEmpty()){
        QMessageBox::information(this,"Exito","Exito:"+ errorOutput);

    }else{
        QMessageBox::information(this,"Exito", output);
        
    }     
}
void MainWindow::b5Clicked()
{
    QProcess process;
    QString tx= inex2->text();
    process.start("git",QStringList()<<"checkout" << "-b" <<tx);
    if (!process.waitForFinished()){
        qDebug()<<"error al ejecutar git init"<< process.errorString();
        return;
    }
    QString output = process.readAllStandardOutput();
    QString errorOutput= process.readAllStandardError();
    if(!errorOutput.isEmpty()){
        QMessageBox::information(this,"Exito","Exito:"+ errorOutput);

    }else{
        QMessageBox::information(this,"Exito", output);
        
    }     
}
void MainWindow::b4Clicked()
{
    QProcess process;
    QString tx= "manuPro";
    process.start("git",QStringList()<<"commit" << "-m" <<tx);
    if (!process.waitForFinished()){
        qDebug()<<"error al ejecutar git init"<< process.errorString();
        return;
    }
    QString output = process.readAllStandardOutput();
    QString errorOutput= process.readAllStandardError();
    if(!errorOutput.isEmpty()){
        QMessageBox::information(this,"Error","Error:"+ errorOutput);

    }else{
        QMessageBox::information(this,"Exito", output);
        
    }     
}

void MainWindow::b3Clicked()
{
    QProcess process;
    QString tx=inex2->text();
    process.start("git",QStringList()<<"push" << "-u" << "origin" <<tx);
    if (!process.waitForFinished()){
        qDebug()<<"error al ejecutar git init"<< process.errorString();
        return;
    }
    QString output = process.readAllStandardOutput();
    QString errorOutput= process.readAllStandardError();
    if(!errorOutput.isEmpty()){
        QMessageBox::information(this,"Exito","Exito:"+ errorOutput);

    }else{
        QMessageBox::information(this,"Exito", output);
        
    }  
    QString workingDir = lb2->text(); 
    QString gitFolderPath = QDir(workingDir).filePath(".git");
    QDir gitDir(gitFolderPath);
    if (gitDir.exists()) {
        if (!gitDir.removeRecursively()) {
            QMessageBox::critical(this, "Error", "Error al eliminar la carpeta .git.");
        } else {
            QMessageBox::information(this, "Éxito", ".git eliminado con éxito.");
        }
    } 
       
}
void MainWindow::b2Clicked(){
    QString folder = QFileDialog::getExistingDirectory(this,"Select Folder");
    
    if (!folder.isEmpty()){
        lb2->setText(folder);
        btn1->setEnabled(1);
        QProcess process;
        QString workinDir=folder;
        process.setWorkingDirectory(workinDir);
        process.start("git",QStringList()<<"init");
        if (!process.waitForFinished()){
            qDebug()<<"error al ejecutar git init"<< process.errorString();
            return;
        }
        QString output = process.readAllStandardOutput();
        QString errorOutput= process.readAllStandardError();
        if(!errorOutput.isEmpty()){
            QMessageBox::critical(this,"Error","Error:"+ errorOutput);

        }else{
            QMessageBox::information(this,"Exito", output);
            
        }
            
        }
}

void MainWindow::b1Clicked()
{
    QProcess process;
    QString tx =lb2->text()+"/"+fileX->text();  // Nombre del archivo
    if (tx.isEmpty()) {
        QMessageBox::warning(this, "Error", "No se ha especificado ningún archivo.");
        return;
    }

    process.start("git", QStringList() << "add" << tx);
    if (!process.waitForFinished()){
        qDebug()<<"error al git init"<< process.errorString();
        return;
    }
    QString output = process.readAllStandardOutput();
    QString errorOutput= process.readAllStandardError();
    if(!errorOutput.isEmpty()){
        QMessageBox::critical(this,"Error","Error:"+ errorOutput);

    }else{
        QMessageBox::information(this,"Exito", output);
        
    }     
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}