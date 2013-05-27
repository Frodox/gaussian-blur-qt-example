#include "jpegfilter.h"
#include "ui_jpegfilter.h"

#include <QDebug>

JpegFilter::JpegFilter(QWidget *parent) :
    QMainWindow(parent),
    ui_ (new Ui::JpegFilter) {
    ui_ -> setupUi(this);
    blur_parametres_is_set_ = false;
}


JpegFilter::~JpegFilter() {
    delete ui_;
}


void JpegFilter::SetFileNameOnTittle(const QString &file_name) {
    setWindowTitle(file_name);
}


void JpegFilter::on_action_open_triggered() {
    QString file_name = QFileDialog::getOpenFileName(this,
                                                     "Открыть изображение",
                                                     QDir::currentPath(),
                                                     tr("Изображения (*.jpg *.jpeg *.jpe)")
                                                     );
    if (true == file_name.isEmpty())
        return;
    else {
        SetFileNameOnTittle(file_name);
        SetInputImage(file_name);
    }
}


void JpegFilter::SetInputImage(const QString &file_name) {
    input_image_.load(file_name);
    ui_ -> image_input_ -> setPixmap(QPixmap::fromImage(input_image_.scaled(input_image_.size() / 1.5)));
}


void JpegFilter::on_action_save_triggered() {

}


void JpegFilter::on_action_save_as_triggered() {

}


void JpegFilter::on_action_settings_triggered() {
    SettingsDialog settings_dialog(this);
    settings_dialog.exec();
    radius_ = settings_dialog.GetBlurRadius();
    diviation_ = settings_dialog.GetDiviation();
    blur_parametres_is_set_ = true;
}


void JpegFilter::on_action_blur_image_triggered() {
    if (false == blur_parametres_is_set_) {
        SettingsDialog settings_dialog;
        settings_dialog.exec();
        diviation_ = settings_dialog.GetDiviation();
        radius_ = settings_dialog.GetBlurRadius();
    }

    GaussianBlur blur(radius_, diviation_);

    QImage output = blur.ApplyGaussianFilterToImage(input_image_);
    ui_ -> image_output_ -> setPixmap(QPixmap::fromImage(output.scaled(output.size() / 1.5)));
}

