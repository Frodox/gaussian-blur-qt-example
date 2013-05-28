#include "jpegfilter.h"
#include "ui_jpegfilter.h"


JpegFilter::JpegFilter(QWidget *parent) :
    QMainWindow(parent),
    ui_ (new Ui::JpegFilter) {
    ui_ -> setupUi(this);
    radius_ = 3;
    diviation_ = 1.000;
    blur_parametres_is_set_ = false;
}


JpegFilter::~JpegFilter() {
    delete ui_;
}


void JpegFilter::SetFileNameOnTittle(const QString &file_name) {
    setWindowTitle(file_name);
}


void JpegFilter::SetInputImage(const QString &file_name) {
    input_image_.load(file_name);
    QImage image  = input_image_.scaled(input_image_.size() / 1.5);
    ui_ -> label_input_ -> setPixmap(QPixmap::fromImage(image));
}


void JpegFilter::UpdateButtons() {
    bool input_is_loaded = ui_ -> label_input_ -> pixmap() -> isNull();
    bool output_is_set = ui_ -> label_output_ -> pixmap();
    if (false == input_is_loaded)
       ui_ -> action_blur_image -> setEnabled(true);
    ui_ -> action_save -> setEnabled(output_is_set);
    ui_ -> action_save_as -> setEnabled(output_is_set);
}


bool JpegFilter::SaveAs() {
    QString file_name = QFileDialog::getSaveFileName(this,
                                                     "Сохранить изображение",
                                                     QDir::currentPath(),
                                                     "Изображения (*.jpg *jpeg *.jpe)");
    if (true == file_name.isEmpty())
        return false;
    return Save(file_name);
}


bool JpegFilter::Save(const QString &file_name) {
    output_image_.save(file_name, "jpeg");
    ui_ -> status_bar_ -> showMessage(QString("Сохранено в %1").arg(file_name), 10);
    return true;
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
        ui_ -> label_output_ -> clear();
        UpdateButtons();
    }
}


void JpegFilter::on_action_save_triggered() {
    QString current_path = windowTitle();
    QString dir = QFileInfo(current_path).dir().path() + "/";
    QString suffix = QFileInfo(current_path).completeSuffix();
    Save(dir + "output." + suffix);
}


void JpegFilter::on_action_save_as_triggered() {
    SaveAs();
}


void JpegFilter::on_action_settings_triggered() {
    SettingsDialog settings_dialog(this);
    settings_dialog.SetBlurRadius(radius_);
    settings_dialog.SetDiviation(diviation_);
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
    ui_ -> status_bar_ -> showMessage("Подождите, изображение обрабатывается...");
    output_image_ = blur.ApplyGaussianFilterToImage(input_image_);
    ui_ -> status_bar_ -> clearMessage();
    QImage output = output_image_.scaled(output_image_.size() / 1.5);
    ui_ -> label_output_ -> setPixmap(QPixmap::fromImage(output));
    UpdateButtons();
}

