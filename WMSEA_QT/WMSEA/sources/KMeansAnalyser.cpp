// KMeansAnalyzer.cpp
#include "../headers/KMeansAnalyzer.h"

KMeansAnalyzer::KMeansAnalyzer() {}

KMeansAnalyzer::~KMeansAnalyzer() {}

void KMeansAnalyzer::initClusters(int numClusters, float minDistanceMean) 
{
    srand(time(NULL));
    clusterValues.resize(numClusters);
    cout << "Initializing " << numClusters << " clusters with target mean-distance of " << minDistanceMean << endl;
    float mean = 999999999; int itCount = 0;
    do
    {
        clusters.clear();
        for(int i = 0; i < numClusters; i++)
        {
            Color c = Color();
            clusters.push_back(c);
        }
        mean = 0; int mcount = 0;
        for(int i = 0; i < numClusters; i++)
        {
            for(int j = 1; j < numClusters; j++)
            {
                mean += clusters.at(i).distance(clusters.at(j));
                mcount++;
            }
        }
        mean /= mcount;
        itCount++;
        cout << "|";
    } while(mean > minDistanceMean);
    cout << "Initialized clusters with a mean-distance of " << mean << " after " << itCount << endl; 
}

void KMeansAnalyzer::displayClusters()
{
    cout << "Clusters :" << endl;
    for(int c = 0 ; c < clusters.size(); c++)
    {
        cout << "  - " << clusters.at(c).r << " " << clusters.at(c).g << " " << clusters.at(c).b << endl;
    }
}

void KMeansAnalyzer::processImage(ImageBase* image)
{
    int clusterId; Color p; float minDistance;
    for(int i = 0; i < image->getSize();i++)
    {
        p = image->readColor(i);
        minDistance = 100000;
        for(int c = 0; c < clusters.size(); c++)
        {
            float d = clusters.at(c).distance(p);
            if(d < minDistance)
            {
                clusterId = c;
                minDistance = d;
            }
        }
        clusterValues.at(clusterId).push_back(p);
    }
}

void KMeansAnalyzer::performKMeansClustering(int numClusters) 
{
    initClusters(numClusters,25);
    displayClusters();

    ImageBase* currentImage = new ImageBase();

    cout << "Processing all " << imagesPathes.size() << " images" << endl;
    for(int i = 0; i < imagesPathes.size(); i++)
    {
        currentImage->load( imagesPathes.at(i).data());
        processImage(currentImage);
    }

    cout << "Reprocessing clusters" << endl;
    for(int c = 0; c < clusters.size();c++)
    {
        float r = 0; float g = 0; float b = 0;
        for(int i = 0; i < clusterValues.at(c).size();i++)
        {
            r += clusterValues.at(c).at(i).r;
            g += clusterValues.at(c).at(i).b;
            b += clusterValues.at(c).at(i).b;
        }
        r /= clusterValues.at(c).size();
        g /= clusterValues.at(c).size();
        b /= clusterValues.at(c).size();
        clusters.at(c) = Color(r,g,b);
    }

    displayClusters();
    cout << "Done" << endl;
}

std::vector<std::vector<int>> KMeansAnalyzer::getClusteredImage() const {
    // Implémentez la fonction pour obtenir l'image résultante après clustering.
    // Retournez les données des clusters ou l'image résultante.
}

// Vous pouvez également implémenter d'autres méthodes pour gérer les résultats et d'autres fonctionnalités.

