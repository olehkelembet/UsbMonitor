#include "traywindow.h"
#include "ui_traywindow.h"
#include "usbmanager.h"




TrayWindow::TrayWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TrayWindow)
    , m_trayIcon(new QSystemTrayIcon(this))
{
    ui->setupUi(this);

    m_bsystray_available = QSystemTrayIcon::isSystemTrayAvailable();
    createTrayMenu();
    QIcon appIcon = QIcon(":/icons/usb.png");
    createTrayIcon(appIcon);
    setTrayWindowProperties(appIcon);

    /*QThread* thread = QThread::create([]{UsbManager u;});
    thread->start();*/
}

TrayWindow::~TrayWindow()
{
    delete ui;
}

QMenu* TrayWindow::createTrayMenu()
{
    QAction* showAction = new QAction("&Show", this);
    showAction->setShortcut(Qt::Key_S);
    connect(showAction, &QAction::triggered, qApp, [&] {show();});

    QAction* hideAction = new QAction("&Hide", this);
    hideAction->setShortcut(Qt::Key_H);
    connect(hideAction, &QAction::triggered, qApp, [&] {hide();});

    QAction* aboutAction = new QAction("&About", this);
    aboutAction->setShortcut(Qt::Key_A);
    connect(aboutAction, &QAction::triggered, this, &TrayWindow::showAboutDialog);

    QAction* quitAction = new QAction("&Quit", this);
    quitAction->setShortcut(Qt::Key_Q);
    //connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
    connect(quitAction, &QAction::triggered, qApp, [&] {mediator->notify(this, APP_QUIT); QCoreApplication::quit();});

    QMenu* menu = new QMenu(this);
    menu->addAction(showAction);
    menu->addAction(hideAction);
    menu->addAction(aboutAction);
    menu->addAction(quitAction);

    return menu;
}

void TrayWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
  switch (reason)
  {
    case QSystemTrayIcon::Trigger:
      break;
    default:
      break;
  }
}

void TrayWindow::setTrayWindowProperties(QIcon icon)
{
    QCoreApplication::setApplicationName("UsbMonitor");
    QCoreApplication::setApplicationVersion("1.0");
    QApplication::setStyle("Fusion");
    setWindowTitle("UsbMonitor");
    setWindowIcon(icon);

    new QShortcut(QKeySequence(Qt::Key_Escape), this, &QCoreApplication::quit);
    new QShortcut(QKeySequence(Qt::Key_S), this, [&]{show();});
    new QShortcut(QKeySequence(Qt::Key_H), this, [&]{hide();});
}

void TrayWindow::createTrayIcon(QIcon icon)
{
    QMenu *menu = createTrayMenu();
    m_trayIcon->setContextMenu(menu);
    m_trayIcon->setToolTip(QString("UsbMonitor"));
    m_trayIcon->setIcon(icon);

    connect(m_trayIcon, &QSystemTrayIcon::activated, this, &TrayWindow::iconActivated);
    m_trayIcon->show();


    if (!isTrayAvailable())
    {
      QMessageBox::information(this, "Information", "Your system tray isn't available!\nApplication will quit now.");
      QCoreApplication::quit();
    }
}

bool TrayWindow::isTrayAvailable()
{
  return m_bsystray_available;
}

void TrayWindow::showAboutDialog()
{
  QMessageBox::about(this, "About", "Program for monitoring usb devices");
}
