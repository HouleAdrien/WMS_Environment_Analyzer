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

    void processImage(ImageBase* image);

    // Effectuer le clustering K-Means
    void performKMeansClustering(int numClusters);
    
    ImageBase* generateClusteredImage(ImageBase* input);
    void generateClusteredImages();
};

#endif // KMEANSANALYZER_H
