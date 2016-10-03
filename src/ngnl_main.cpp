#include <QApplication>

#include "ngnl_window.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    NGNLWindow* window = new NGNLWindow();
    return app.exec();
}
