#include <QDebug>

#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
            QDialog(parent),
            ui_ (new Ui::SettingsDialog)
{
    ui_ -> setupUi(this);
}


SettingsDialog::~SettingsDialog() {
    delete ui_;
}


int SettingsDialog::GetBlurRadius() const
{
    // blur radius should be odd. so, use dirty hack
    int radius = ui_ -> size_box_ -> value();
    return radius + 1 - radius%2;
}


double SettingsDialog::GetDiviation() const
{
    return ui_ -> diviation_box_ -> value();
}


void SettingsDialog::SetBlurRadius(int radius)
{
    bool is_even = (0 == radius % 2) ? true : false;
    bool is_too_high = (radius > ui_->size_box_->maximum()) ? true : false;
    if ( is_even || is_too_high )
    {
        qDebug() << "incorrect radiused passed: " << radius << endl;
        return;
    }
    else {
        ui_ -> size_box_ -> setValue(radius);
    }
}


void SettingsDialog::SetDiviation(double diviation)
{
    if ((diviation < 0) || (diviation > ui_ -> diviation_box_ -> maximum()))
        return;
    else
        ui_ -> diviation_box_ -> setValue(diviation);
}
