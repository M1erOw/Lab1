#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <QMainWindow>
#include <QSpinBox>
#include <QSlider>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QPalette>
#include <QColorDialog>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    void errorMessage(std::string msg);
    void createControls();
    float function(float x);
    float function1(float x);
    float function2(float x);

    bool flag_rgb = 0;
    bool flag_xyz = 0;
    bool flag_lab = 0;

    bool buttonFlag = 0;

    QWidget *Color_window;

    QGroupBox *Group;

    QLabel *R_Label;
    QLabel *G_Label;
    QLabel *rgb_B_Label;
    QLabel *X_Label;
    QLabel *Y_Label;
    QLabel *Z_Label;
    QLabel *L_Label;
    QLabel *A_Label;
    QLabel *lab_B_Label;

    QSpinBox *R_SpinBox;
    QSpinBox *G_SpinBox;
    QSpinBox *rgb_B_SpinBox;
    QSpinBox *X_SpinBox;
    QSpinBox *Y_SpinBox;
    QSpinBox *Z_SpinBox;
    QSpinBox *L_SpinBox;
    QSpinBox *A_SpinBox;
    QSpinBox *lab_B_SpinBox;

    QSlider *R_slider;
    QSlider *G_slider;
    QSlider *rgb_B_slider;
    QSlider *X_slider;
    QSlider *Y_slider;
    QSlider *Z_slider;
    QSlider *L_slider;
    QSlider *A_slider;
    QSlider *lab_B_slider;

    QGridLayout *layout;

    QPushButton *button;

    QPushButton *ignoreButton;
private slots:
    void on_button_clicked();
    void on_ignoreButton_clicked();
    void custom_setValue();
    void custom_setValue1();
    void custom_setValue2();
};
#endif // MAINWINDOW_H
