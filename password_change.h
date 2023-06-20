#ifndef PASSWORD_CHANGE_H
#define PASSWORD_CHANGE_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class Password_Change;
}

/*********************************************************************
 * Password_Change Class
 *   Represents the dialog window responsible for allowing admins to
 *   change the administrator password.
 *********************************************************************/
class Password_Change : public QDialog
{
    Q_OBJECT

public:
    explicit Password_Change(QWidget *parent = nullptr);
    ~Password_Change();

    QString getNewPassword();
    void setOldPassword(QString password);

private slots:
    void on_pushButton_clicked();

private:
    Ui::Password_Change *ui;

    QString newPassword;  // the new password
    QString oldPassword;  // the current password
};

#endif // PASSWORD_CHANGE_H
