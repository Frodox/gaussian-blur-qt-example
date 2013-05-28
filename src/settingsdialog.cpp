#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui_ (new Ui::SettingsDialog) {
    ui_ -> setupUi(this);
}


SettingsDialog::~SettingsDialog() {
    delete ui_;
}


int SettingsDialog::GetBlurRadius() const {
    return ui_ -> size_box_ -> value();
}


double SettingsDialog::GetDiviation() const {
    return ui_ -> diviation_box_ -> value();
}


void SettingsDialog::SetBlurRadius(int radius) {
    if ((1 == radius % 2) || (radius > ui_ -> size_box_ -> maximum()))
        return;
    else
        ui_ -> size_box_ -> setValue(radius);
}


void SettingsDialog::SetDiviation(double diviation) {
    if ((diviation < 0) || (diviation > ui_ -> diviation_box_ -> maximum()))
        return;
    else
        ui_ -> diviation_box_ -> setValue(diviation);
}
