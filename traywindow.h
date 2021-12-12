#ifndef TRAYWINDOW_H
#define TRAYWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QShortcut>
#include <QMessageBox>



QT_BEGIN_NAMESPACE
namespace Ui { class TrayWindow; }
QT_END_NAMESPACE

class TrayWindow : public QMainWindow
{
    Q_OBJECT

public:
    TrayWindow(QWidget *parent = nullptr);
    ~TrayWindow();

private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason);
    void        showAboutDialog();

private:
    Ui::TrayWindow *	ui;
    QSystemTrayIcon *	m_trayIcon;
    bool				m_bsystray_available = false;

    QMenu*      createTrayMenu();
    void        createTrayIcon(QIcon);
    void        setTrayWindowProperties(QIcon);
    inline bool isTrayAvailable();
};
#endif // TRAYWINDOW_H

