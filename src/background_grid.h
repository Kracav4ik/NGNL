#pragma once

#include <QGraphicsItem>
#include <QPainter>
#include <Vector>

using namespace std;

template<typename T>
class Matrix {
    vector<vector<T>> data;
public:
    int width;
    int height;

    Matrix(int w, int h)
            :
            data((unsigned int) w, vector<T>((unsigned int) h)),
            width(w),
            height(h) {}

    void set(int x, int y, const T& value) {
        data[x][y] = value;
    }

    T get(int x, int y) const {
        return data[x][y];
    }
};


class BackgroundGrid : public QGraphicsItem {
private:
    int _cellSize;
    int _globalOffsetX;
    int _globalOffsetY;
    int _frameIdx;
    Matrix<bool> grid;
public:
    bool _showBg;
    bool _showTex;
    bool _showBaseline;
    bool _showHitbox;

    explicit BackgroundGrid(int cellSize, int cellCountHor, int cellCountVert, int globalOffsetX, int globalOffsetY) :
            _cellSize(cellSize),
            _globalOffsetX(globalOffsetX),
            _globalOffsetY(globalOffsetY),
            _frameIdx(0),
            grid(cellCountHor, cellCountVert),
            _showBg(false),
            _showTex(false),
            _showBaseline(false),
            _showHitbox(false) {
        grid.set(10, 16, true);
        grid.set(20, 16, true);
        for (int i = 11; i <= 19; ++i) {
            grid.set(i, 24, true);
        }
        for (int i = 8; i <= 22; ++i) {
            grid.set(i, 13, true);
            grid.set(i, 26, true);
        }
        for (int j = 14; j <= 25; ++j) {
            grid.set(7, j, true);
            grid.set(23, j, true);
        }
    }

    QRectF boundingRect() const override {
        return QRectF(0, 0, _cellSize * grid.width + 1, _cellSize * grid.height + 1);
    }

    static int alive_count(int x, int y, const Matrix<bool>& grid) {
        int result = 0;
        for (int i = x - 1; i <= x + 1; ++i) {
            for (int j = y - 1; j <= y + 1; ++j) {
                if ((i >= 0 && i < grid.width) && (j >= 0 && j < grid.height) && !(y == j && x == i)) {
                    if (grid.get(i, j)) {
                        result++;
                    }
                }
            }
        }
        return result;
    }

    void life_step() {
        Matrix<bool> new_grid(grid.width, grid.height);
        for (int x = 0; x < grid.width; ++x) {
            for (int y = 0; y < grid.height; ++y) {
                int count = alive_count(x, y, grid);
                if (grid.get(x, y)) {
                    if (count == 3 || count == 2) {
                        new_grid.set(x, y, true);
                    }
                } else {
                    if (count == 3) {
                        new_grid.set(x, y, true);
                    }
                }
            }
        }
        grid = new_grid;
        update();
    }

    void _paintPixel(QPainter* painter, int frameX, int frameY, const QColor& c) const {
        int alpha = c.alpha();
        if (_showBg) {
            alpha = 255;
        }
        painter->setBrush(QColor(c.red(), c.green(), c.blue(), alpha));
        painter->drawRect(_cellSize * frameX, _cellSize * frameY, _cellSize, _cellSize);
    }

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override {
        painter->setPen(Qt::NoPen);
        painter->setBrush(QBrush(Qt::darkCyan, Qt::Dense5Pattern));
        painter->drawRect(boundingRect());

        for (int x = 0; x < grid.width; ++x) {
            for (int y = 0; y < grid.height; ++y) {
                if (grid.get(x, y)) {
                    _paintPixel(painter, x, y, Qt::black);
                }
            }
        }

        if (false) {
//            const Frame& _frame = (*_frames)[_frameIdx];
//            if (_showTex) {
//                for (unsigned int frameX = 0; frameX < _cellCountVert; frameX++) {
//                    for (unsigned int frameY = 0; frameY < _cellCountHor; frameY++) {
//                        unsigned int pixX = _frame.x() - _globalOffsetX + frameX + _frame.dx();
//                        unsigned int pixY = _frame.y() - _globalOffsetY + frameY + _frame.dy();
//                        _paintImagePixel(painter, frameX, frameY, pixX, pixY);
//                    }
//                }
//            } else {
//                for (unsigned int x = 0; x < _frame.w(); x++) {
//                    for (unsigned int y = 0; y < _frame.h(); y++) {
//                        unsigned int frameX = x + _globalOffsetX - _frame.dx();
//                        unsigned int frameY = y + _globalOffsetY - _frame.dy();
//                        if (frameX < 0 || frameY < 0 || frameX >= _cellCountHor || frameY >= _cellCountVert) {
//                            continue;
//                        }
//                        unsigned int pixX = _frame.x() + x;
//                        unsigned int pixY = _frame.y() + y;
//                        _paintImagePixel(painter, frameX, frameY, pixX, pixY);
//                    }
//                }
//            }

        }

        painter->setPen(Qt::black);
        for (int i = 0; i <= grid.height; i++) {
            int offset_y = _cellSize * i;
            painter->drawLine(0, offset_y, _cellSize * grid.width, offset_y);
        }
        for (int i = 0; i <= grid.width; i++) {
            int offset_x = _cellSize * i;
            painter->drawLine(offset_x, 0, offset_x, _cellSize * grid.height);
        }

//        if(_frames && _image){
//            const Frame& _frame = (*_frames)[_frameIdx];
//            QPen pen(Qt::green, 3);
//            pen.setJoinStyle(Qt::MiterJoin);
//            painter->setPen(pen);
//            painter->setBrush(Qt::NoBrush);
//            int rab_x = (_globalOffsetX) * _cellSize;
//            int rab_y = (_globalOffsetY) * _cellSize;
//            int x = rab_x - _frame.dx() * _cellSize;
//            int y = rab_y - _frame.dy() * _cellSize;
//            int w = _frame.w() * _cellSize;
//            int h = _frame.h() * _cellSize;
//            if (_showTex) {
//                painter->drawRect(x, y, w, h);
//            }
//            pen.setColor(Qt::red);
//            if (_showBaseline) {
//                painter->setPen(pen);
//                const Frame& frame = (*_frames)[0];
//                int x0 = (_globalOffsetX - frame.dx()) * _cellSize;
//                int y0 = (_globalOffsetY - frame.dy()) * _cellSize;
//                int w0 = frame.w() * _cellSize;
//                int h0 = frame.h() * _cellSize;
//                painter->drawLine(0, y0 + h0, _cellSize * _cellCountVert, y0 + h0);
//            }
//            pen.setColor(Qt::magenta);
//            if (_showHitbox) {
//                painter->setPen(pen);
//                painter->drawRect(rab_x, rab_y, int(RABBIT_SIZE.x/2) * _cellSize, int(RABBIT_SIZE.y/2) * _cellSize);
//            }
//        }
    }

};
