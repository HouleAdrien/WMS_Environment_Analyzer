#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void LoadBaseImage();
    void loadClusterOfImage();
    void updateImagePath(const QString &newPath);
private:
    QLabel *baseImageLabel;
    QLabel *processedImageLabel;
    QPushButton *processButton;
    QString imagePath;

};

#endif // MAINWINDOW_H
