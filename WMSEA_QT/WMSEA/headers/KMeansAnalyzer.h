// KMeansAnalyzer.h
#ifndef KMEANSANALYZER_H
#define KMEANSANALYZER_H

#include <vector>
#include <string>

class KMeansAnalyzer {
public:
    KMeansAnalyzer();
    ~KMeansAnalyzer();

    // Charger une image satellite à partir d'un fichier
    bool loadImage(const std::string& imagePath);

    // Définir le nombre de clusters pour le K-Means
    void setNumClusters(int numClusters);

    // Effectuer le clustering K-Means
    void performKMeansClustering();

    // Obtenir l'image résultante après clustering
    std::vector<std::vector<int>> getClusteredImage() const;
};

#endif // KMEANSANALYZER_H
