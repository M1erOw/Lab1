#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createControls();

    Color_window = new QWidget();
    QPalette palette;
    palette.setColor(QPalette::Window, QColor(0, 0, 0));
    Color_window->setPalette(palette);
    Color_window->setAutoFillBackground(true);

    button = new QPushButton("Choose a color from the palette");
    ignoreButton = new QPushButton("Ignore errors");

    connect(button, SIGNAL(clicked()), this, SLOT(on_button_clicked()));
    connect(ignoreButton, SIGNAL(clicked()), this, SLOT(on_ignoreButton_clicked()));

    layout = new QGridLayout;
    layout->addWidget(Group, 0, 0);
    layout->addWidget(Color_window, 0, 1);
    layout->addWidget(ignoreButton, 1, 0);
    layout->addWidget(button, 1, 1);


    QWidget *window = new QWidget();
    window->setLayout(layout);
    window->setMinimumSize(500,400);
    setCentralWidget(window);
}

void MainWindow::custom_setValue()
{
    flag_rgb = 1;
    float r = R_slider->value();
    float g = G_slider->value();
    float b = rgb_B_slider->value();

    if(!flag_xyz)
    {
        float x = 0.412453 * (r / 255 * 100) + 0.357580  * (g / 255 * 100) + 0.180423 * (b / 255 * 100);
        float y = 0.212671 * (r / 255 * 100) + 0.715160  * (g / 255 * 100) + 0.072169 * (b / 255 * 100);
        float z = 0.019334 * (r / 255 * 100) + 0.119193  * (g / 255 * 100) + 0.950227 * (b / 255 * 100);

        if(x > 100 || x < 0)
        {
            errorMessage("Выход за пределы X");
        }
        if(y > 100 || y < 0)
        {
            errorMessage("Выход за пределы Y");
        }
        if(z > 100 || z < 0)
        {
            errorMessage("Выход за пределы Z");
        }

        X_SpinBox->setValue(round(x));
        Y_SpinBox->setValue(round(y));
        Z_SpinBox->setValue(round(z));
    }

    QPalette palette;
    palette.setColor(QPalette::Window, QColor(R_slider->value(), G_slider->value(),rgb_B_slider->value()));
    Color_window->setPalette(palette);
    Color_window->setAutoFillBackground(true);

    R_SpinBox->setValue(R_slider->value());
    G_SpinBox->setValue(G_slider->value());
    rgb_B_SpinBox->setValue(rgb_B_slider->value());
    flag_rgb = 0;
}

float MainWindow::function(float x)
{
    float a;
    if (x >= 0.008856)
        a = pow(x,1.0 / 3.0);
    else
        a = ((7.787 * x) + (16.0 / 116.0));
    return a;
}

float MainWindow::function2(float x)
{
    float a;
    if (x >= 0.0031308 )
        a = 1.055 * pow(x,1.0 / 2.4) - 0.055;
    else
        a = 12.92 * x;
    return a;
}

void MainWindow::custom_setValue1()
{
    flag_xyz = 1;
    float x = X_slider->value();
    float y = Y_slider->value();
    float z = Z_slider->value();

    if(!flag_lab)
    {
        float l = 116.0 * function(y / 100.0) - 16.0;

        float a = 500.0 * (function(x / 95.047) - function(y / 100.0));

        float b = 200.0 * (function(y / 100.0) - function(z / 108.883));


        if(l > 100 || l < 0)
        {
            errorMessage("Выход за пределы L");
        }
        if(a > 128 || a < -128)
        {
            errorMessage("Выход за пределы A");
        }
        if(b > 128 || b < -128)
        {
            errorMessage("Выход за пределы B(LAB)");
        }

        L_SpinBox->setValue(round(l));
        A_SpinBox->setValue(round(a));
        lab_B_SpinBox->setValue(round(b));
    }

    if(!flag_rgb)
    {
        float r = 225.0 * function(0.032406 * x - 0.015372 * y - 0.004986 * z);
        float g = 225.0 * function(-0.009689 * x + 0.018758 * y + 0.000415 * z);
        float rgb_b = 225.0 * function(0.000557 * x - 0.002040 * y + 0.010570 * z);

        if(rgb_b > 225 || rgb_b < 0)
        {
            errorMessage("Выход за пределы B(RGB)");
        }
        if(g > 225 || g < 0)
        {
            errorMessage("Выход за пределы G");
        }
        if(r > 225 || r < 0)
        {
            errorMessage("Выход за пределы R");
        }

        R_SpinBox->setValue(round(r));
        G_SpinBox->setValue(round(g));
        rgb_B_SpinBox->setValue(round(rgb_b));
    }

    X_SpinBox->setValue(X_slider->value());
    Y_SpinBox->setValue(Y_slider->value());
    Z_SpinBox->setValue(Z_slider->value());
    flag_xyz = 0;
}

float MainWindow::function1(float x)
{
    float a;
    if (pow(x,3.0) >= 0.008856)
        a = pow(x,3.0);
    else
        a = (x - (16.0 / 116.0)) / 7.787;
    return a;
}

void MainWindow::custom_setValue2()
{
    flag_lab = 1;
    float l = L_slider->value();
    float a = A_slider->value();
    float b = lab_B_slider->value();

    if(!flag_xyz)
    {
        float x = function1((l + 16.0) / 116.0) * 95.047;
        float y = function1(a / 500.0 + ((l + 16.0) / 116.0)) * 100.0;
        float z = function1(((l + 16.0) / 116.0) - b / 200.0) * 108.883;

        if(x > 100 || x < 0)
        {
            errorMessage("Выход за пределы X");
        }
        if(y > 100 || y < 0)
        {
            errorMessage("Выход за пределы Y");
        }
        if(z > 100 || z < 0)
        {
            errorMessage("Выход за пределы Z");
        }

        X_SpinBox->setValue(round(x));
        Y_SpinBox->setValue(round(y));
        Z_SpinBox->setValue(round(z));
    }

    L_SpinBox->setValue(L_slider->value());
    A_SpinBox->setValue(A_slider->value());
    lab_B_SpinBox->setValue(lab_B_slider->value());
    flag_lab = 0;
}

void MainWindow::createControls()
{
    Group = new QGroupBox("Controls");

    R_Label = new QLabel("R:");
    G_Label = new QLabel("G:");
    rgb_B_Label = new QLabel("B:");
    X_Label = new QLabel("X:");
    Y_Label = new QLabel("Y:");
    Z_Label = new QLabel("Z:");
    L_Label = new QLabel("L:");
    A_Label = new QLabel("A:");
    lab_B_Label = new QLabel("B:");

    R_SpinBox = new QSpinBox;
    G_SpinBox = new QSpinBox;
    rgb_B_SpinBox = new QSpinBox;
    X_SpinBox = new QSpinBox;
    Y_SpinBox = new QSpinBox;
    Z_SpinBox = new QSpinBox;
    L_SpinBox = new QSpinBox;
    A_SpinBox = new QSpinBox;
    lab_B_SpinBox = new QSpinBox;

    R_slider = new QSlider(Qt::Horizontal);
    G_slider = new QSlider(Qt::Horizontal);
    rgb_B_slider = new QSlider(Qt::Horizontal);
    X_slider = new QSlider(Qt::Horizontal);
    Y_slider = new QSlider(Qt::Horizontal);
    Z_slider = new QSlider(Qt::Horizontal);
    L_slider = new QSlider(Qt::Horizontal);
    A_slider = new QSlider(Qt::Horizontal);
    lab_B_slider = new QSlider(Qt::Horizontal);

    R_slider->setTickPosition(QSlider::NoTicks);
    G_slider->setTickPosition(QSlider::NoTicks);
    rgb_B_slider->setTickPosition(QSlider::NoTicks);
    X_slider->setTickPosition(QSlider::NoTicks);
    Y_slider->setTickPosition(QSlider::NoTicks);
    Z_slider->setTickPosition(QSlider::NoTicks);
    L_slider->setTickPosition(QSlider::NoTicks);
    A_slider->setTickPosition(QSlider::NoTicks);
    lab_B_slider->setTickPosition(QSlider::NoTicks);

    R_SpinBox->setRange(0, 255);
    G_SpinBox->setRange(0, 255);
    rgb_B_SpinBox->setRange(0, 255);
    X_SpinBox->setRange(0, 100);
    Y_SpinBox->setRange(0, 100);
    Z_SpinBox->setRange(0, 100);
    L_SpinBox->setRange(0, 100);
    A_SpinBox->setRange(-128, 128);
    lab_B_SpinBox->setRange(-128, 128);

    R_SpinBox->setSingleStep(1);
    G_SpinBox->setSingleStep(1);
    rgb_B_SpinBox->setSingleStep(1);
    X_SpinBox->setSingleStep(1);
    Y_SpinBox->setSingleStep(1);
    Z_SpinBox->setSingleStep(1);
    L_SpinBox->setSingleStep(1);
    A_SpinBox->setSingleStep(1);
    lab_B_SpinBox->setSingleStep(1);

    R_slider->setRange( R_SpinBox->minimum(),
                       R_SpinBox->maximum());
    R_slider->setSingleStep(10);

    G_slider->setRange( G_SpinBox->minimum(),
                       G_SpinBox->maximum());
    G_slider->setSingleStep(10);

    rgb_B_slider->setRange( rgb_B_SpinBox->minimum(),
                           rgb_B_SpinBox->maximum());
    rgb_B_slider->setSingleStep(10);

    X_slider->setRange( X_SpinBox->minimum(),
                       X_SpinBox->maximum());
    X_slider->setSingleStep(10);

    Y_slider->setRange( Y_SpinBox->minimum(),
                       Y_SpinBox->maximum());
    Y_slider->setSingleStep(10);

    Z_slider->setRange( Z_SpinBox->minimum(),
                       Z_SpinBox->maximum());
    Z_slider->setSingleStep(10);

    L_slider->setRange( L_SpinBox->minimum(),
                       L_SpinBox->maximum());
    L_slider->setSingleStep(10);

    A_slider->setRange( A_SpinBox->minimum(),
                       A_SpinBox->maximum());
    A_slider->setSingleStep(10);

    lab_B_slider->setRange( lab_B_SpinBox->minimum(),
                           lab_B_SpinBox->maximum());
    lab_B_slider->setSingleStep(10);

    QObject::connect( R_SpinBox, SIGNAL(valueChanged(int)),
                     R_slider, SLOT(setValue(int)));

    QObject::connect( G_SpinBox, SIGNAL(valueChanged(int)),
                     G_slider, SLOT(setValue(int)));

    QObject::connect( rgb_B_SpinBox, SIGNAL(valueChanged(int)),
                     rgb_B_slider, SLOT(setValue(int)));

    QObject::connect( X_SpinBox, SIGNAL(valueChanged(int)),
                     X_slider, SLOT(setValue(int)));

    QObject::connect( Y_SpinBox, SIGNAL(valueChanged(int)),
                     Y_slider, SLOT(setValue(int)));

    QObject::connect( Z_SpinBox, SIGNAL(valueChanged(int)),
                     Z_slider, SLOT(setValue(int)));

    QObject::connect( L_SpinBox, SIGNAL(valueChanged(int)),
                     L_slider, SLOT(setValue(int)));

    QObject::connect( A_SpinBox, SIGNAL(valueChanged(int)),
                     A_slider, SLOT(setValue(int)));

    QObject::connect( lab_B_SpinBox, SIGNAL(valueChanged(int)),
                     lab_B_slider, SLOT(setValue(int)));

    QObject::connect( R_slider, SIGNAL(valueChanged(int)),
                     this, SLOT(custom_setValue()));

    QObject::connect( G_slider, SIGNAL(valueChanged(int)),
                     this, SLOT(custom_setValue()));

    QObject::connect( rgb_B_slider, SIGNAL(valueChanged(int)),
                     this, SLOT(custom_setValue()));

    QObject::connect( X_slider, SIGNAL(valueChanged(int)),
                     this, SLOT(custom_setValue1()));

    QObject::connect( Y_slider, SIGNAL(valueChanged(int)),
                     this, SLOT(custom_setValue1()));

    QObject::connect( Z_slider, SIGNAL(valueChanged(int)),
                     this, SLOT(custom_setValue1()));

    QObject::connect( L_slider, SIGNAL(valueChanged(int)),
                     this, SLOT(custom_setValue2()) );

    QObject::connect( A_slider, SIGNAL(valueChanged(int)),
                     this, SLOT(custom_setValue2()) );

    QObject::connect( lab_B_slider, SIGNAL(valueChanged(int)),
                     this, SLOT(custom_setValue2()));

    QGridLayout *controlsLayout1 = new QGridLayout;
    QGridLayout *controlsLayout2 = new QGridLayout;
    QGridLayout *controlsLayout3 = new QGridLayout;

    QGridLayout *controlsLayout = new QGridLayout;

    QGroupBox *group1 = new QGroupBox("RGB");
    QGroupBox *group2 = new QGroupBox("XYZ");
    QGroupBox *group3 = new QGroupBox("LAB");

    controlsLayout1->addWidget(R_Label, 0, 0);
    controlsLayout1->addWidget(G_Label, 1, 0);
    controlsLayout1->addWidget(rgb_B_Label, 2, 0);
    controlsLayout2->addWidget(X_Label, 0, 0);
    controlsLayout2->addWidget(Y_Label, 1, 0);
    controlsLayout2->addWidget(Z_Label, 2, 0);
    controlsLayout3->addWidget(L_Label, 0, 0);
    controlsLayout3->addWidget(A_Label, 1, 0);
    controlsLayout3->addWidget(lab_B_Label, 2, 0);

    controlsLayout1->addWidget(R_SpinBox, 0, 1);
    controlsLayout1->addWidget(G_SpinBox, 1, 1);
    controlsLayout1->addWidget(rgb_B_SpinBox, 2, 1);
    controlsLayout2->addWidget(X_SpinBox, 0, 1);
    controlsLayout2->addWidget(Y_SpinBox, 1, 1);
    controlsLayout2->addWidget(Z_SpinBox, 2, 1);
    controlsLayout3->addWidget(L_SpinBox, 0, 1);
    controlsLayout3->addWidget(A_SpinBox, 1, 1);
    controlsLayout3->addWidget(lab_B_SpinBox, 2, 1);

    controlsLayout1->addWidget(R_slider, 0, 2);
    controlsLayout1->addWidget(G_slider, 1, 2);
    controlsLayout1->addWidget(rgb_B_slider, 2, 2);
    controlsLayout2->addWidget(X_slider, 0, 2);
    controlsLayout2->addWidget(Y_slider, 1, 2);
    controlsLayout2->addWidget(Z_slider, 2, 2);
    controlsLayout3->addWidget(L_slider, 0, 2);
    controlsLayout3->addWidget(A_slider, 1, 2);
    controlsLayout3->addWidget(lab_B_slider, 2, 2);

    group1->setLayout(controlsLayout1);
    group2->setLayout(controlsLayout2);
    group3->setLayout(controlsLayout3);

    controlsLayout->addWidget(group1, 0, 0);
    controlsLayout->addWidget(group2, 1, 0);
    controlsLayout->addWidget(group3, 2, 0);

    Group->setLayout(controlsLayout);
}

void MainWindow::on_button_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white);
    QPalette palette;
    palette.setColor(QPalette::Window, color);
    Color_window->setPalette(palette);
    Color_window->setAutoFillBackground(true);
    int r,g,b;
    color.getRgb(&r,&g,&b);
    R_SpinBox->setValue(r);
    G_SpinBox->setValue(g);
    rgb_B_SpinBox->setValue(b);
}

void MainWindow::on_ignoreButton_clicked()
{
    if(buttonFlag)
    {
        buttonFlag = 0;
        ignoreButton->setText("Ignore errors");
    }
    else
    {
        buttonFlag = 1;
        ignoreButton->setText("Process errors");
    }
}

void MainWindow::errorMessage(std::string msg)
{
    if(!buttonFlag)
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::critical(this, QString::fromUtf8("Критическая ошибка"),
                      QString::fromUtf8(msg),
                                      QMessageBox::Abort | QMessageBox::Ignore);
        switch (reply){
        case QMessageBox::Abort:
            QApplication::quit();
            break;
        case QMessageBox::Ignore:
            break;
        default:
            break;
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

