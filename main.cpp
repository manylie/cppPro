#include <QApplication>
#include <QMainWindow>
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QGridLayout>
#include <QLineEdit>
#include <QMessageBox>
class MainWindow : public QMainWindow {
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QWidget* mainWidget;
    QPlainTextEdit* snipText;
    QGridLayout* layout;
    QLineEdit* l1;
    QLineEdit* l2;
    QPushButton* saveButton;
    QLineEdit* impText(const QString &tx, QGridLayout *lay, int x ,int y);
    void saveSnippetToJson();
};
MainWindow::~MainWindow() {}
QLineEdit* MainWindow:: impText(const QString &tx, QGridLayout *lay, int x ,int y){
    QLineEdit *line = new QLineEdit(tx,this);
    lay->addWidget(line,x,y);
    return line;
}
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {
    mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);
    layout = new QGridLayout(this);
    l1 = impText("name",layout,0,0);
    l2 = impText("hotkey",layout,0,1);
    snipText = new QPlainTextEdit(this);
    layout->addWidget(snipText,1,0,1,2);

    // Agregar un botón para guardar el snippet
    saveButton = new QPushButton("Agregar al JSON", this);
    layout->addWidget(saveButton,2,0,1,2);
    mainWidget->setLayout(layout);

    // Conectar la señal del botón al slot para guardar el snippet
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::saveSnippetToJson);
}

void MainWindow::saveSnippetToJson() {
    QString plainText = snipText->toPlainText();
    QStringList lines = plainText.split("\n");

    // Crear el array 'body' en formato JSON
    QJsonArray bodyArray;
    for (const QString &line : lines) {
        bodyArray.append(line);
    }

    // Crear el objeto JSON para el snippet
    QJsonObject snippetObject;
    snippetObject["prefix"] = l2->text();
    snippetObject["body"] = bodyArray;
    snippetObject["description"] = "manu aqui";

    // Leer el archivo JSON existente
    QString pathJson = "C:/Users/manuel/AppData/Roaming/Code/User/snippets/cpp.json";
    QFile file(pathJson);
    QJsonObject jsonObj;

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QByteArray jsonData = file.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(jsonData);
        jsonObj = doc.object();
        file.close();
    }

    // Agregar el nuevo snippet al archivo JSON
    jsonObj[l1->text()] = snippetObject;

    // Guardar el archivo JSON actualizado
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QJsonDocument doc(jsonObj);
        file.write(doc.toJson(QJsonDocument::Indented));
        file.close();
        QMessageBox::information(this,"exito","exito: snipet Creado");

    }else{
        QMessageBox::critical(this,"error","no se pudo intentelo mas tarde");
    }
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
