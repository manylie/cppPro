#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QFileDialog>
#include <QUrl>

class MainWindow : public QMainWindow {
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openVideo(); // Slot para abrir un video

private:
    QWidget *mainWidget;
    QPushButton *openButton;    // Botón para abrir un video
    QMediaPlayer *player;       // Reproductor de media
    QVideoWidget *videoWidget;  // Widget de video
};

MainWindow::~MainWindow() {}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);

    // Crear el reproductor y el widget de video
    player = new QMediaPlayer(this);
    videoWidget = new QVideoWidget(this);

    // Conectar el reproductor con el widget de video
    player->setVideoOutput(videoWidget);

    // Crear un botón para abrir un video
    openButton = new QPushButton("Abrir Video", this);

    // Conectar el botón al slot openVideo
    connect(openButton, &QPushButton::clicked, this, &MainWindow::openVideo);

    // Crear un layout y agregar el botón y el widget de video
    QVBoxLayout *layout = new QVBoxLayout(mainWidget);
    layout->addWidget(videoWidget);
    layout->addWidget(openButton);
    mainWidget->setLayout(layout);
}

void MainWindow::openVideo() {
    // Abrir un cuadro de diálogo para seleccionar un archivo de video
    QString fileName = QFileDialog::getOpenFileName(this, tr("Abrir Video"), "", tr("Archivos de Video (*.mp4 *.avi *.mkv)"));

    if (!fileName.isEmpty()) {
        QUrl url = QUrl::fromLocalFile(fileName);  // Crear URL del archivo seleccionado
        player->setSource(url);  // Establecer la fuente del reproductor
        player->play();  // Reproducir el video
    }
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
