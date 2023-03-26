#pragma once

#include "gamelogic.hpp"

#include <QString>
#include <QColor>

class QtCssColorBuilder
{
public:
    static QString  Build(QColor background_color, QColor foreground_color);

private:
    inline static const QString  begin  = " QLabel { background-color : rgb(";
    inline static const QString  middle = "); color: rgb(";
    inline static const QString  end    = "); }";
};

class _2048_CSSColors
{
public:
    static void  Init();

    static QString  GetBySlotValue(SlotValue value);

    // colors used when user has entered a valid or an invalid name.

    static QString  GetErrorColor();

    static QString  GetValidationColor();

private:
    inline static QString  color_2;
    inline static QString  color_4;
    inline static QString  color_8;
    inline static QString  color_16;
    inline static QString  color_32;
    inline static QString  color_64;
    inline static QString  color_128;
    inline static QString  color_256;
    inline static QString  color_512;
    inline static QString  color_1024;
    inline static QString  color_2048;
    inline static QString  color_4098_and_upper;

    // message colors.
    inline static QString  error_color;
    inline static QString  validation_color;
};
