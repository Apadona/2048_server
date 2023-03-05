#include "csscolors.hpp"

QString  QtCssColorBuilder::Build(QColor background_color, QColor foreground_color)
{
  return begin + QString::number(background_color.red()) + ','
         + QString::number(background_color.green()) + ','
         + QString::number(background_color.blue()) + middle
         + QString::number(foreground_color.red()) + ','
         + QString::number(foreground_color.green()) + ','
         + QString::number(foreground_color.blue()) + end;
}

void  _2048_CSSColors::Init()
{
  color_2              = QtCssColorBuilder::Build({ 222, 221, 217 }, { 47, 44, 40 });
  color_4              = QtCssColorBuilder::Build({ 201, 188, 135 }, { 47, 44, 40 });
  color_8              = QtCssColorBuilder::Build({ 217, 162, 91 }, { 98, 70, 95 });
  color_16             = QtCssColorBuilder::Build({ 171, 81, 51 }, { 98, 70, 95 });
  color_32             = QtCssColorBuilder::Build({ 227, 119, 95 }, { 98, 70, 95 });
  color_64             = QtCssColorBuilder::Build({ 245, 66, 66 }, { 98, 70, 95 });
  color_128            = QtCssColorBuilder::Build({ 245, 197, 66 }, { 98, 70, 95 });
  color_256            = QtCssColorBuilder::Build({ 163, 163, 7 }, { 98, 70, 95 });
  color_512            = QtCssColorBuilder::Build({ 199, 199, 2 }, { 98, 70, 95 });
  color_1024           = QtCssColorBuilder::Build({ 225, 250, 0 }, { 98, 70, 95 });
  color_2048           = QtCssColorBuilder::Build({ 245, 245, 0 }, { 98, 70, 95 });
  color_4098_and_upper = QtCssColorBuilder::Build({ 8, 7, 7 }, { 98, 70, 95 });
}

QString  _2048_CSSColors::GetBySlotValue(SlotValue value)
{
  if ((value == 2) || (value == 0))
  {
    return color_2;
  }

  if (value == 4)
  {
    return color_4;
  }

  if (value == 8)
  {
    return color_8;
  }

  if (value == 16)
  {
    return color_16;
  }

  if (value == 32)
  {
    return color_32;
  }

  if (value == 64)
  {
    return color_64;
  }

  if (value == 128)
  {
    return color_128;
  }

  if (value == 256)
  {
    return color_256;
  }

  if (value == 512)
  {
    return color_512;
  }

  if (value == 1024)
  {
    return color_1024;
  }

  if (value == 2048)
  {
    return color_2048;
  }

  if (value >= 4098)
  {
    return color_4098_and_upper;
  }
}

// QString _2048_CSSColors::color_2 = QtCssColorBuilder::Build({94,90,86}, {47,44,40});
// QString _2048_CSSColors::color_4 = QtCssColorBuilder::Build({93,88,78}, {47,44,40});
// QString _2048_CSSColors::color_8 = QtCssColorBuilder::Build({95,70,48}, {98,70,95});
// QString _2048_CSSColors::color_16 = QtCssColorBuilder::Build({96,60,40}, {98,70,95});
// QString _2048_CSSColors::color_32 = QtCssColorBuilder::Build({97,50,38}, {98,70,95});
// QString _2048_CSSColors::color_64 = QtCssColorBuilder::Build({97,37,23}, {98,70,95});
// QString _2048_CSSColors::color_128 = QtCssColorBuilder::Build({93,81,45}, {98,70,95});
// QString _2048_CSSColors::color_256 = QtCssColorBuilder::Build({93,80,39}, {98,70,95});
// QString _2048_CSSColors::color_512 = QtCssColorBuilder::Build({93,79,32}, {98,70,95});
// QString _2048_CSSColors::color_1024 = QtCssColorBuilder::Build({93,78,25}, {98,70,95});
// QString _2048_CSSColors::color_2048 = QtCssColorBuilder::Build({93,76,18}, {98,70,95});
// QString _2048_CSSColors::color_4098_and_upper = QtCssColorBuilder::Build({3,3,3}, {98,70,95});
