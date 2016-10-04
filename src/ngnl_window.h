#pragma once

#include <stdio.h>
#include <QMainWindow>
#include <QDir>
#include <QGraphicsTextItem>
#include <QTimer>

#include "ui_ngnl.h"
#include "debug.h"
#include "background_grid.h"

const int DEFAULT_ANIM_INTERVAL = 200;

class NGNLWindow : public QMainWindow, private Ui::NGNLWindow {
Q_OBJECT
private:
    QString anims_root;
    QGraphicsScene scene;
    QTimer animTimer;
    bool animRuning;
    BackgroundGrid grid;
    QStringList animNames;

    QString path;

public:
    NGNLWindow() :
            anims_root(QCoreApplication::applicationDirPath() + "/../data/anims/"),
            animRuning(false),
            grid(10, 50, 50, 15, 15)
    {
        setupUi(this);

        animTimer.setInterval(DEFAULT_ANIM_INTERVAL);
//
//        load_anims();
//        grid._showBg = showBg->isChecked();
//        grid._showTex = showTex->isChecked();
//        grid._showBaseline = showBaseline->isChecked();
//        grid._showHitbox = showHitbox->isChecked();

        scene.addItem(&grid);
        graphicsView->setScene(&scene);

        connect(&animTimer, SIGNAL(timeout()), this, SLOT(anim_step()));

        show();

        on_filterAnim_textChanged("");
    }
void refresh_anim() {
    /*
if (animInfo.empty()) {
    grid.setImageFrames(NULL, NULL,0);
    return;

    frameNumber->setMaximum(animInfo._frames.size() - 1);
    Frame& frame = animInfo._frames[frameNumber->value()];

    TextureManager& manager = TextureManager::inst();
    Image& image = manager.get_image(animInfo._tex_name.c_str());
    grid.setImageFrames(&image, &animInfo._frames, frameNumber->value());

    APPLY_ALL(SET_VALUE)

    frame_x->setMaximum(image.getSize().x - 1);
    frame_y->setMaximum(image.getSize().y - 1);

    unDo->setEnabled(undoRedo.can_undo());
    reDo->setEnabled(undoRedo.can_redo());
    saveFrame->setEnabled(undoRedo.has_changes());
}

void load_anims() {
    animNames.clear();
    QStringList fileNames = QDir(anims_root).entryList();

    for (QString file : fileNames) {
        if (file.endsWith(".txt")) {
            animNames.push_back(file.left(file.size() - 4));
        }
    }
}
*/  }


public slots:

    void on_startAnimation_clicked(bool checked) {
        animRuning = checked;
    }

    void on_startAnimation_toggled(bool checked) {
        if (checked) {
            startAnimation->setText("Stop");
            animTimer.start();
        } else {
            startAnimation->setText("Start");
            animTimer.stop();
        }
    }

    void anim_step() {
//        if (!animInfo.empty()) {
//            frameNumber->setValue((frameNumber->value() + 1) % animInfo._frames.size());
//        }
        grid.life_step();
    }

//    void on_saveFrame_clicked() {
//        animInfo.save(FilePath(path.toUtf8().constData()));
//        undoRedo.notify_saved();
//        refresh_anim();
//    }

    void on_filterAnim_textChanged(QString filter) {
        filter = filter.trimmed();

        QStringList filterWords = filter.split(" ", QString::SkipEmptyParts);
        QStringList filteredNames;

        for (QString name : animNames) {
            bool addName = true;
            for (QString word : filterWords) {
                if (!name.contains(word)) {
                    addName = false;
                    break;
                }
            }
            if (addName) {
                filteredNames.append(name);
            }
        }
//
//        animationList->clear();
//        animationList->addItems(filteredNames);

        refresh_anim();
    }

    void on_clearFilter_clicked() {
//        filterAnim->clear();
    }

    void on_animationList_currentTextChanged(const QString& string) {
//        bool haveFile = !string.isEmpty();
//        frameNGNLs->setEnabled(haveFile);
//
//        undoRedo.initial_set();
//        if (haveFile) {
//            path = anims_root + string + ".txt";
//            animInfo.load(FilePath(path.toUtf8().constData()));
//
//            bool has_animation = animInfo._frames.size() != 1;
//            startAnimation->setChecked(has_animation && animRuning);
//            startAnimation->setEnabled(has_animation);
//
//            undoRedo.push_value(animInfo._frames);
//            undoRedo.notify_saved();
//        } else {
//            path = "";
//            animInfo.clear();
//        }
//
//        refresh_anim();
    }

    void on_speed_valueChanged(double value) {
        animTimer.setInterval(int(DEFAULT_ANIM_INTERVAL / value));
    }

    void on_frameNumber_valueChanged(int) {
        refresh_anim();
    }
    void on_unDo_clicked() {
//        animInfo._frames = undoRedo.do_undo();
//        grid.setFrame(&animInfo._frames, frameNumber->value());

        refresh_anim();
    }

    void on_reDo_clicked() {
//        animInfo._frames = undoRedo.do_redo();
//        grid.setFrame(&animInfo._frames, frameNumber->value());
//
        refresh_anim();
    }

    void on_showBg_stateChanged(int) {
//        grid._showBg = showBg->isChecked();
        grid.update();
    }

    void on_showBaseline_stateChanged(int){
//        grid._showBaseline = showBaseline->isChecked();
        grid.update();
    }
    void on_showTex_stateChanged(int){
//        grid._showTex = showTex->isChecked();
        grid.update();
    }

    void on_showHitbox_stateChanged(int){
//        grid._showHitbox = showHitbox->isChecked();
        grid.update();
    }
};
