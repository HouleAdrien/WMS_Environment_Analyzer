/******************************************************************************
* ICAR_Library
*
* Fichier : ImageBase.cpp
*
* Description : Voir le fichier .h
*
* Auteur : Mickael Pinto
*
* Mail : mickael.pinto@live.fr
*
* Date : Octobre 2012
*
*******************************************************************************/

#include "../headers/ImageBase.h"
#include "../headers/image_ppm.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>

ImageBase::ImageBase(void)
{
	isValid = false;
	init();
}

ImageBase::ImageBase(int imWidth, int imHeight, bool isColor)
{
	isValid = false;
	init();

	color = isColor;
	height = imHeight;
	width = imWidth;
	nTaille = height * width * (color ? 3 : 1);
	
	if(nTaille == 0){
		printf("La taille est nulle\n");
		return;
	}

	allocation_tableau(data, OCTET, nTaille);
	dataD = (double*)malloc(sizeof(double) * nTaille);
	isValid = true;
}


ImageBase::~ImageBase(void)
{
	reset();
}

void ImageBase::init()
{
	if(isValid)
	{
		free(data);
		free(dataD);
	}

	data = 0;
	dataD = 0;
	height = width = nTaille = 0;
	isValid = false;
}

void ImageBase::reset()
{
	if(isValid)
	{
		free(data);
		free(dataD);
	}
	isValid = false;
}

void ImageBase::load(char *filename)
{
	init();

	int l = strlen(filename);

	if(l <= 4) // Le fichier ne peut pas etre que ".pgm" ou ".ppm"
	{
		printf("Chargement de l'image impossible : Le nom de fichier n'est pas conforme, il doit comporter l'extension, et celle ci ne peut �tre que '.pgm' ou '.ppm'");
		exit(0);
	}

	int nbPixel = 0;

	if( strcmp(filename + l - 3, "pgm") == 0) // L'image est en niveau de gris
	{
		color = false;
		lire_nb_lignes_colonnes_image_pgm(filename, &height, &width);
		nbPixel = height * width;
  
		nTaille = nbPixel;
		allocation_tableau(data, OCTET, nTaille);
		lire_image_pgm(filename, data, nbPixel);
	}
	else if( strcmp(filename + l - 3, "ppm") == 0) // L'image est en couleur
	{
		color = true;
		lire_nb_lignes_colonnes_image_ppm(filename, &height, &width);
		nbPixel = height * width;

		nTaille = nbPixel * 3;
		allocation_tableau(data, OCTET, nTaille);
		lire_image_ppm(filename, data, nbPixel);
	}
	else 
	{
		printf("Chargement de l'image impossible : Le nom de fichier n'est pas conforme, il doit comporter l'extension, et celle ci ne peut �tre que .pgm ou .ppm");
		exit(0);
	}
	
	dataD = (double*)malloc(sizeof(double) * nTaille);

	isValid = true;
}

bool ImageBase::save(char *filename)
{
	if(!isValid)
	{
		printf("Sauvegarde de l'image impossible : L'image courante n'est pas valide");
		exit(0);
	}

	if(color)
		ecrire_image_ppm(filename, data,  height, width);
	else
		ecrire_image_pgm(filename, data,  height, width);

	return true;
}
unsigned char ImageBase::get(int i, int rgb)	
{
	if(color)
	{
		return data[ (i * 3) + rgb];
	}
	else
	{
		return data[i];
	}
}
unsigned char ImageBase::get(int x, int y, int rgb)	
{
	if(color)
	{
		return data[ ((x+(y*height)) * 3) + rgb];
	}
	else
	{
		return data[x + (y*height)];
	}
}
void ImageBase::set(int x, int y, int rgb,unsigned char value)
{
	if(color)
	{
		data[ ((x+(y*height)) * 3) + rgb] = min(max((int)value,0),256);
	}
	else
	{
		data[x + (y*height)] = min(max((int)value,0),256);
	}
}
void ImageBase::set(int i, int rgb,unsigned char value)
{
	if(color)
	{
		data[ (i * 3) + rgb] = min(max((int)value,0),256);
	}
	else
	{
		data[i] = min(max((int)value,0),256);
	}
}

Color ImageBase::readColor(int i)
{
	if(color)
	{
		return Color(
			data[ (i * 3)] ,
			data[ (i * 3) + 1] ,
			data[ (i * 3) + 2 ]);
	}
	else
	{
		return Color(data[i],data[i],data[i]);
	}
}

Color ImageBase::readColor(int x, int y)
{
	if(color)
	{
		return Color(
			data[ ((x+(y*height)) * 3)] ,
			data[ ((x+(y*height)) * 3) + 1] ,
			data[ ((x+(y*height)) * 3) + 2 ]);
	}
	else
	{
		return Color(data[x + (y*height)],data[x + (y*height)],data[x + (y*height)]);
	}
}

void ImageBase::setColor(int i, Color c)
{
	if(color)
	{
		data[ (i * 3)] = c.r;
		data[ (i * 3) + 1] = c.g;
		data[ (i * 3) + 2 ] = c.b;
	}
}
void ImageBase::setColor(int x, int y, Color c)
{
	if(color)
	{
		data[ ((x+(y*height)) * 3)] = c.r;
		data[ ((x+(y*height)) * 3) + 1] = c.g;
		data[ ((x+(y*height)) * 3) + 2 ] = c.b;
	}
}

ImageBase *ImageBase::getPlan(PLAN plan)
{
	if( !isValid || !color ) {
		printf("L'image courante n'est pas valide ou pas en couleur\n");
		return 0;
	}

	ImageBase *greyIm = new ImageBase(width, height, false);
	
	switch(plan)
	{
	case PLAN_R:
		planR(greyIm->data, data, height * width);
		break;
	case PLAN_G:
		planV(greyIm->data, data, height * width);
		break;
	case PLAN_B:
		planB(greyIm->data, data, height * width);
		break;
	default:
		printf("Il n'y a que 3 plans, les valeurs possibles ne sont donc que 'PLAN_R', 'PLAN_G', et 'PLAN_B'");
		exit(0);
		break;
	}

	return greyIm;
}

double ImageBase::EQM(ImageBase* imgOut)
{
	double r = 0; double g = 0; double b = 0;

	for(int i = 0; i < this->getSize(); i++)
	{
		Color cIn = this->readColor(i);
		Color cOut = imgOut->readColor(i);
		
		r += (cIn.r - cOut.r) * (cIn.r - cOut.r) ;
		g += (cIn.g - cOut.g) * (cIn.g - cOut.g) ;
		b += (cIn.b - cOut.b) * (cIn.b - cOut.b) ;
	}

	int tIn = this->getSize() ;

	r /= tIn;
	g /= tIn;
	b /= tIn;

	return (r+g+b) / 3.0;
}

double ImageBase::PSNR(ImageBase* imgOut)
{
	return 10 * log10((255*255) / EQM(imgOut));
}

double ImageBase::EQMW(ImageBase* imgOut)
{
	return 0;
}

double ImageBase::WPSNR(ImageBase* imgOut)
{
	return 10 * log10((255*255) / EQMW(imgOut));
}

double ImageBase::entropy(int rgb)
{
	int* histo = histogram(rgb);

	double e = 0;
	for(int i = 0; i < 256;i++)
	{
		double v = histo[i] / (double)getSize();
		if(v <= 0){continue;}
		e += (-1) * (v * log2(v));
	}

	return e;
}

int* ImageBase::lineProfile(int rgb, int id)
{
	int* histo = new int[getWidth()];

	for(int x = 0; x < getWidth(); ++x)
	{
		histo[x] = get(x,id,rgb);
	}

	return histo;
}

int*  ImageBase::columnProfile(int rgb, int id)
{
	int* histo = new int[getHeight()];

	for(int y = 0; y < getHeight(); ++y)
	{
		histo[y] = get(id,y,rgb);
	}

	return histo;
}

int* ImageBase::histogram(int rgb)
{
	int* histo = new int[256];
	for(int i = 0; i < 256;i++){ histo[i] = 0;}

	for(int x = 0; x < getHeight(); ++x)
	{
		for(int y = 0; y < getWidth(); ++y)
		{
			histo[get(x,y,rgb)]++;
		}
	}

	return histo;
}

double* ImageBase::DDP(int rgb)
{
	int* histo = histogram(rgb);
	double* ddp = new double[256];

	for(int i = 0; i < 256; i++)
	{
		ddp[i] = histo[i] / (double)getSize();
	}

	return ddp;
}

double* ImageBase::repartition(int rgb)
{
	int* histo = histogram(rgb);
	double* ddp = new double[256];

	ddp[0] = histo[0] / (double)getSize();
	for(int i = 1; i < 256; i++)
	{
		ddp[i] = ddp[i-1] + (histo[i] / (double)getSize());
	}

	return ddp;
}

void  ImageBase::saveProfile(int* histo, int size, char* path)
{
	ofstream flux(path);
	for(int i = 0; i < size;i++)	{	flux << i << " " << histo[i] << std::endl;}
}

void ImageBase::saveHistogram(int* histo,char* path)
{
	ofstream flux(path);
	for(int i = 0; i < 256;i++)	{	flux << i << " " << histo[i] << std::endl;}
}

void ImageBase::saveDDP(double* ddp,char* path)
{
	ofstream flux(path);
	for(int i = 0; i < 256;i++)	{	flux << i << " " << ddp[i] << std::endl;}
}

void ImageBase::copy(const ImageBase &copy)
{
	reset();
	
	isValid = false;
	init();
	
	color = copy.color;
	height = copy.height;
	width = copy.width;
	nTaille = copy.nTaille;
	isValid = copy.isValid;
	
	if(nTaille == 0)
		return;
	
	allocation_tableau(data, OCTET, nTaille);
	dataD = (double*)malloc(sizeof(double) * nTaille);
	isValid = true;

	for(int i = 0; i < nTaille; ++i)
	{
		data[i] = copy.data[i];
		dataD[i] = copy.dataD[i];
	}

}

unsigned char *ImageBase::operator[](int l)
{
	if(!isValid)
	{
		printf("L'image courante n'est pas valide");
		exit(0);
	}
	
	if((!color && l >= height) || (color && l >= height*3))
	{
		printf("L'indice se trouve en dehors des limites de l'image");
		exit(0);
	}
	
	return data+l*width;
}
