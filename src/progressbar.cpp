#include "progressbar.h"
#include "ui_progressbar.h"

ProgressBar::ProgressBar(QWidget *parent) :
    QDialog(parent),
    ui_ (new Ui::ProgressBar) {
    ui_ -> setupUi(this);
    progress_ = 0;
}

ProgressBar::~ProgressBar() {
    delete ui_;
}

void ProgressBar::SetMaximum(int maximum_value) {
  ui_ -> progress_bar_ -> setMaximum(maximum_value);
}

void ProgressBar::slotSetValueOnProgressBar(int progress) {
    progress_ += progress;
    ui_ -> progress_bar_ -> setValue(progress_);
}

void ProgressBar::on_ProgressBar_rejected() {
  ui_ -> progress_bar_ -> setValue(0);
}


