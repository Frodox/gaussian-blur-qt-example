#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();
    int GetBlurRadius() const;
    double GetDiviation() const;
private:
    Ui::SettingsDialog *ui_;
};

#endif // SETTINGSDIALOG_H
