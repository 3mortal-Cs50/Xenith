#include <bits/stdc++.h>
#include "Image_Class.h"
using namespace std;
Image GrayScale(Image img);
Image BlackAndWhite(Image img);
Image Invert(Image img);
Image Merge(Image img1, Image img2);
Image FlipV(Image img);
Image FlipH(Image img);
Image rFlipH(Image img);
Image ScaleDown(Image img, int wid, int hgt);
//=======================================//
//=======================================//
Image lighten(Image img)
{
  for (int i = 0; i < img.width; ++i)
  {
    for (int j = 0; j < img.height; ++j)
    {
      img(i, j, 0) -= img(i, j, 0) / 2;
      img(i, j, 1) -= img(i, j, 1) / 2;
      img(i, j, 2) -= img(i, j, 2) / 2;
    }
  }
  cout << "Done, Successfully\n";
  return img;
}
//=======================================//
//=======================================//
Image blue(Image img)
{
  for (int i = 0; i < img.width; ++i)
  {
    for (int j = 0; j < img.height; ++j)
    {
      for (int k = 0; k < 2; ++k)
      {
        img(i, j, k) -= .5 * img(i, j, k);
        if (img(i, j, k) > 255)
          img(i, j, k) = 255;
      }
    }
  }
  cout << "Done, Successfully\n";
  return img;
}
//=======================================//
//=======================================//
Image darken(Image img)
{
  for (int j = 0; j < img.height; ++j)
  {
    for (int i = 0; i < img.width; ++i)
    {
      for (int c = 0; c < 3; ++c)
        img(i, j, c) = min(255, img(i, j, c) + 80);
    }
  }
  return img;
}
//=======================================//
//=======================================//
Image GrayScale(Image img)
{
  for (int i = 0; i < img.width; ++i)
  {
    for (int j = 0; j < img.height; ++j)
    {
      int sum = img(i, j, 0) + img(i, j, 1) + img(i, j, 2);
      sum /= 3;
      img(i, j, 0) = sum;
      img(i, j, 1) = sum;
      img(i, j, 2) = sum;
    }
  }
  cout << "Done, Successfully\n";
  return img;
}
//=======================================//
//=======================================//
Image BlackAndWhite(Image img)
{
  for (int i = 0; i < img.width; ++i)
  {
    for (int j = 0; j < img.height; ++j)
    {
      int sum = 0.3 * img(i, j, 0) + 0.6 * img(i, j, 1) + 0.11 * img(i, j, 2);
      // int sum = img(i, j, 0) + img(i, j, 1) + img(i, j, 2);
      // sum /= 3;
      if (sum >= 128)
      {
        img(i, j, 0) = 255;
        img(i, j, 1) = 255;
        img(i, j, 2) = 255;
      }
      else
      {
        img(i, j, 0) = 0;
        img(i, j, 1) = 0;
        img(i, j, 2) = 0;
      }
    }
  }
  cout << "Done, Successfully\n";
  return img;
}
//=======================================//
//=======================================//
Image Invert(Image img)
{
  for (int i = 0; i < img.width; ++i)
  {
    for (int j = 0; j < img.height; ++j)
    {
      img(i, j, 0) = 255 - img(i, j, 0);
      img(i, j, 1) = 255 - img(i, j, 1);
      img(i, j, 2) = 255 - img(i, j, 2);
    }
  }
  cout << "Done, Successfully\n";
  return img;
}
//=======================================//
//=======================================//
Image Merge(Image img1, Image img2)
{
  int miniw = min(img1.width, img2.width);
  int minih = min(img1.height, img2.height);
  Image merged_img(miniw, minih);
  img1 = ScaleDown(img1, miniw, minih);
  img2 = ScaleDown(img2, miniw, minih);
  for (int i = 0; i < miniw; ++i)
  {
    for (int j = 0; j < minih; ++j)
    {
      merged_img(i, j, 0) = (img2(i, j, 0) + img1(i, j, 0)) / 2;
      merged_img(i, j, 1) = (img2(i, j, 1) + img1(i, j, 1)) / 2;
      merged_img(i, j, 2) = (img2(i, j, 2) + img1(i, j, 2)) / 2;
    }
  }
  cout << "Done, Successfully\n";
  return merged_img;
}
Image Merge2(Image img1, Image img2)
{
  int miniw = min(img1.width, img2.width);
  int minih = min(img1.height, img2.height);
  Image merged_img(miniw, minih);
  img1 = ScaleDown(img1, miniw, minih);
  img2 = ScaleDown(img2, miniw, minih);
  double ratio = 1 / (double)miniw;
  for (int j = 0; j < minih; ++j)
  {
    for (int i = 0; i < miniw; ++i)
    {
      merged_img(i, j, 0) = ratio * img2(i, j, 0) + (1 - ratio) * img1(i, j, 0);
      merged_img(i, j, 1) = ratio * img2(i, j, 1) + (1 - ratio) * img1(i, j, 1);
      merged_img(i, j, 2) = ratio * img2(i, j, 2) + (1 - ratio) * img1(i, j, 2);
    }
    ratio += 1 / (double)miniw;
  }
  cout << "Done, Successfully\n";
  return merged_img;
}
Image Merge3(Image img1, Image img2)
{
  int miniw = min(img1.width, img2.width);
  int minih = min(img1.height, img2.height);
  Image merged_img(miniw, minih);
  img1 = ScaleDown(img1, miniw, minih);
  img2 = ScaleDown(img2, miniw, minih);
  for (int j = 0; j < minih; ++j)
  {
    for (int i = 0; i < miniw; ++i)
    {
      merged_img(i, j, 0) = img2(i, j, 0, 0.5) + img1(i, j, 0, 0.5);
      merged_img(i, j, 1) = img2(i, j, 1, 0.5) + img1(i, j, 1, 0.5);
      merged_img(i, j, 2) = img2(i, j, 2, 0.5) + img1(i, j, 2, 0.5);
    }
  }
  cout << "Done, Successfully\n";
  return merged_img;
}
//=======================================//
Image Opacity(Image img)
{
  for (int j = 0; j < img.height; ++j)
  {
    for (int i = 0; i < img.width; ++i)
    {
      for (int k = 0; k < 3; ++k)
        img(i, j, k) = img(i, j, k, 0.2);
    }
  }
  cout << "Done, Successfully\n";
  return img;
}
//=======================================//
/*Kindda being ok with documenting*/
/*
Firstly I thought about a ratio wanted_res/curr_res (e.g,500/700).
It's 5/7, so every 7 pixels should be replaced with 5 pixels. but applying this was extremly hard to implement.
Then An idea popped into my head smt like that
1. Fill all wanted_res px
2. Color them with avg colors that represents the nearby pixels
*/
/*=======================================*/
Image ScaleDown(Image img, int wid, int hgt)
{
  Image new_img(wid, hgt);
  double xScaling = (double)img.width / wid;
  double yScaling = (double)img.height / hgt;
  for (int i = 0; i < new_img.width; i++)
  {
    for (int j = 0; j < new_img.height; j++)
    {
      new_img(i, j, 0) = img((int)(xScaling * i), (int)(yScaling * j), 0);
      new_img(i, j, 1) = img((int)(xScaling * i), (int)(yScaling * j), 1);
      new_img(i, j, 2) = img((int)(xScaling * i), (int)(yScaling * j), 2);
    }
  }
  return new_img;
}
//=======================================//
//=======================================//
Image FlipV(Image img)
{
  Image img1(img);
  for (int i = 0; i < img.width; ++i)
  {
    int k = 0;
    for (int j = img.height - 1; j >= 0; --j)
    {
      img1(i, k, 0) = img(i, j, 0);
      img1(i, k, 1) = img(i, j, 1);
      img1(i, k++, 2) = img(i, j, 2);
    }
  }
  cout << "Done, Successfully\n";
  return img1;
}
//=======================================//
//=======================================//
Image FlipH(Image img)
{
  img = rFlipH(img);
  cout << "Done, Successfully\n";
  return img;
}
//=======================================//
//=======================================//
Image rFlipH(Image img)
{
  Image img1(img);
  for (int j = 0; j < img.height; ++j)
  {
    int k = 0;
    for (int i = img.width - 1; i >= 0; --i)
    {
      img1(k, j, 0) = img(i, j, 0);
      img1(k, j, 1) = img(i, j, 1);
      img1(k++, j, 2) = img(i, j, 2);
    }
  }
  return img1;
}
Image R(Image &img)
{
  Image img1(img.height, img.width);
  for (int i = 0; i < img.width; ++i)
  {
    for (int j = 0; j < img.height; ++j)
    {
      img1(j, i, 0) = img(i, j, 0);
      img1(j, i, 1) = img(i, j, 1);
      img1(j, i, 2) = img(i, j, 2);
    }
  }
  img1 = rFlipH(img1);
  return img1;
}
Image Rotate(Image img, int deg)
{
  deg /= 90;
  while ((deg)--)
    img = R(img);
  return img;
}
//=======================================//
//=======================================//
Image Crop(Image img, int x1, int y1, int wdt, int hgt)
{
  Image img1(wdt, hgt);
  for (int i = x1; i < wdt + x1; ++i)
  {
    for (int j = y1; j < hgt + y1; ++j)
    {
      img1(i - x1, j - y1, 0) = img(i, j, 0);
      img1(i - x1, j - y1, 1) = img(i, j, 1);
      img1(i - x1, j - y1, 2) = img(i, j, 2);
    }
  }
  return img1;
}