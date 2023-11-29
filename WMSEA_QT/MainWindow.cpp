#include "MainWindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "WMSEA/headers/KMeansAnalyzer.h"
#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QHBoxLayout* imagesLayout = new QHBoxLayout;
    QVBoxLayout* mainLayout = new QVBoxLayout;
    QWidget* centralWidget = new QWidget;

    // Instantiate the labels and button
    baseImageLabel = new QLabel;
    processedImageLabel = new QLabel;
    processButton = new QPushButton("Process");
    QLineEdit* imagePathInput = new QLineEdit;

    const QSize fixedSize(300, 300);
    baseImageLabel->setFixedSize(fixedSize);
    processedImageLabel->setFixedSize(fixedSize);

    imagesLayout->addWidget(baseImageLabel);
    imagesLayout->addWidget(processedImageLabel);

    connect(processButton, SIGNAL(clicked()), this, SLOT(loadClusterOfImage()));

    connect(imagePathInput, SIGNAL(textChanged(const QString &)), this, SLOT(updateImagePath(const QString &)));

    mainLayout->addLayout(imagesLayout);
    mainLayout->addWidget(processButton);
    mainLayout->addWidget(imagePathInput);

    centralWidget->setLayout(mainLayout);
    this->setCentralWidget(centralWidget);

    LoadBaseImage();
}

MainWindow::~MainWindow()
{
    delete baseImageLabel;
    delete processedImageLabel;
    delete processButton;
}

void MainWindow::LoadBaseImage(){
    QPixmap pic(imagePath);
    pic = pic.scaled(baseImageLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    baseImageLabel->setPixmap(pic);
}


void MainWindow::loadClusterOfImage()
{
    KMeansAnalyzer kma;
    kma.readClusterDataFile("../datasets/truemarblepartials/clusterData.txt");
    const char * path = imagePath.toStdString().c_str();
    ImageBase* image = new ImageBase(); image->load((char*)path);
    image = kma.generateClusteredImage(image);
    image->save("test.ppm");
    QPixmap pic("test.ppm");
    pic = pic.scaled(processedImageLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    processedImageLabel->setPixmap(pic);
}

void MainWindow::updateImagePath(const QString &newPath)
{
    imagePath = newPath;
    LoadBaseImage();
}

