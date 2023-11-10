/******************************************************************************
* ICAR_Library
*
* Fichier : ImageBase.h
*
* Description : Classe contennant quelques fonctionnalit�s de base
*
* Auteur : Mickael Pinto
*
* Mail : mickael.pinto@live.fr
*
* Date : Octobre 2012
*
*******************************************************************************/

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Color
{
	unsigned char r;
	unsigned char g;
	unsigned char b;

	double distance(Color c)
	{
		return sqrt(
				(r-c.r)*(r-c.r) +
				(g-c.g)*(g-c.g) +
				(b-c.b)*(b-c.b)
			);
	}

	unsigned char getY()
	{
		return (unsigned char)max(0,min(255,(int)(0.2989*r + 0.5866*g + 0.1145*b)));
	}

	unsigned char getCr()
	{
		return (unsigned char)max(0,min(255,(int)(0.5 * r - 0.4184 * g - 0.0816 * b) + 128));//((b-getY())/(double)(2-2*0.114*b)) + 128;
	}

	unsigned char getCb()
	{
		return (unsigned char)max(0,min(255,(int)(-0.1687 * r - 0.3313 * g + 0.5 * b) + 128));//((r-getY())/(double)(2-2*0.299*r))
	}

	Color()
	{
		r = rand() % 256;
		g = rand() % 256;
		b = rand() % 256;
	}

	Color(unsigned char _r, unsigned char _g, unsigned char _b)
	{
		r = _r; g = _g; b = _b;
	}

	void fromYCRCB(unsigned char y, unsigned char cr, unsigned char cb)
	{
	  r = (unsigned char)max(0,min(255,(int)(y + 1.402*(cr-128))));
	  g = (unsigned char)max(0,min(255,(int)(y - 0.4414*(cb-128) - 0.71414*(cr-128))));
	  b = (unsigned char)max(0,min(255,(int)(y + 1.772*(cb-128))));
	}
};

class ImageBase
{
	///////////// Enumerations
public:
	typedef enum { PLAN_R, PLAN_G, PLAN_B} PLAN;


	///////////// Attributs
protected:
	unsigned char *data;
	double *dataD;

	bool color;
	int height;
	int width;
	int nTaille;
	bool isValid;


	///////////// Constructeurs/Destructeurs
protected:
	void init();
	void reset();

public:
	ImageBase(void);
	ImageBase(int imWidth, int imHeight, bool isColor);
	~ImageBase(void);
	
	///////////// Methodes
protected:
	void copy(const ImageBase &copy);

public:
	int getHeight() { return height; };
	int getWidth() { return width; };
	int getSize() {return height * width;}
	int getTotalSize() { return nTaille; };
	int getValidity() { return isValid; };
	bool getColor() { return color; };
	unsigned char *getData() { return data; };
	void setData(unsigned char* dat){for(int i = 0; i < getSize(); ++i){data[i] = dat[i];}}

	void load(char *filename);
	bool save(char *filename);

	ImageBase *getPlan(PLAN plan);

	unsigned char get(int i, int rgb);
	unsigned char get(int x, int y, int rgb);
	void set(int x, int y, int rgb, unsigned char value);
	void set(int i, int rgb, unsigned char value);

	Color readColor(int i);
	Color readColor(int x, int y);

	void setColor(int i, Color c);
	void setColor(int x,int y, Color c);

  	double EQM(ImageBase* imgOut);
  	double PSNR(ImageBase* imgOut);

  	double EQMW(ImageBase* imgOut);
  	double WPSNR(ImageBase* imgOut);

	double entropy(int rgb);

	int* lineProfile(int rgb, int id);
	int* columnProfile(int rgb, int id);
  	int* histogram(int rgb);
  	double* DDP(int rgb);
  	double* repartition(int rgb);

  	void saveProfile(int* histo, int size, char* path);
  	void saveHistogram(int* histo,char* path);
	void saveDDP(double* ddp,char* path);

	unsigned char *operator[](int l);
};

