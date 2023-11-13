// KMeansAnalyzer.h
#ifndef KMEANSANALYZER_H
#define KMEANSANALYZER_H

#include "ImageBase.h"
#include <filesystem> 
#include <iostream> 
#include <cstdlib>
#include <ctime>

#include <vector>
#include <string>

using namespace std;

class KMeansAnalyzer 
{
private:
    string imagesPath;
    vector<string> imagesPathes;

    vector<Color> clusters; 
    vector<vector<Color>> clusterValues;
    
const Color colors[20] = { 
    Color(0,0,0),
    Color(255,255,255),
    Color(0,0,255),
    Color(255,0,0),
    Color(0,255,0),
    Color(255,255,0),
    Color(255,0,255),
    Color(0,255,255),
    Color(255,128,128),
    Color(128,128,255),
    // Additional colors
    Color(128,0,0),         // Dark Red
    Color(128,128,0),       // Olive
    Color(0,128,0),         // Dark Green
    Color(128,0,128),       // Purple
    Color(0,128,128),       // Teal
    Color(0,0,128),         // Navy
    Color(192,192,192),     // Silver
    Color(128,128,128),     // Gray
    Color(255,165,0),       // Orange
    Color(255,192,203)      // Pink
};

    
public:
    KMeansAnalyzer();
    KMeansAnalyzer(string _path)
    {
        imagesPath = _path;
        if(filesystem::exists(imagesPath))
        {
            for(const auto & entry : filesystem::directory_iterator(imagesPath))
            {
                imagesPathes.push_back(entry.path().generic_string());
            }
        }else{cout << "Couldnt find path : " << imagesPath << endl; }
    }
    ~KMeansAnalyzer();

    void displayClusters();

    // Définir le nombre de clusters pour le K-Means
    void initClusters(int numClusters, float minDistanceMean);

    void processImage(ImageBase* image,float clusterMeaningForce = 0.1f);

    // Effectuer le clustering K-Means
    void performKMeansClustering(int numClusters);
    
    ImageBase* generateClusteredImage(ImageBase* input);
    void generateClusteredImages();
};

#endif // KMEANSANALYZER_H
