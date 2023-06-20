#include "password_change.h"
#include "ui_password_change.h"

Password_Change::Password_Change(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Password_Change)
{
    ui->setupUi(this);
}

Password_Change::~Password_Change()
{
    delete ui;
}

/*******************************************************************************
 *
 * on_pushButton_clicked
 *
 * _____________________________________________________________________________
 * Verifies if new password is valid and stores it in class attribute.
 * _____________________________________________________________________________
 * POST-CONDITIONS:
 *   Outputs notification message and stores password if valid.
 * ****************************************************************************/
void Password_Change::on_pushButton_clicked()
{
    QMessageBox message;   // Notification message to be outputted to user

    // Add an 'Ok' button
    message.setStandardButtons(QMessageBox::Ok);
    message.setDefaultButton(QMessageBox::Ok);

    // Output a notification message if password-change was successful or unsuccessful
    if (oldPassword == ui->NewPasswordlineEdit->text())
    {
        message.setText("Your new password can not be the same as the current password.");
        message.exec();
    }
    else if (ui->NewPasswordlineEdit->text() != ui->ComfirmNewPasswordlineEdit->text())
    {
        message.setText("Your new password does not match");
        message.exec();
    }
    else if (ui->CurrentPasswordlineEdit->text() != oldPassword)
    {
        message.setText("Your current password does not match.");
        message.exec();
    }
    else
    {
        message.setText("Your password has been changed.");
        message.exec();

        // Store the new password and close the dialog
        newPassword = ui->ComfirmNewPasswordlineEdit->text();
        close();
    }
}

QString Password_Change::getNewPassword()
{
    return newPassword;
}

void Password_Change::setOldPassword(QString password)
{
    oldPassword = password;
}
