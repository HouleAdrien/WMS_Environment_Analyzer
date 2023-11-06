#include "headers/KMeansAnalyzer.h"

int main(int argc, char *argv[])
{
    KMeansAnalyzer kma = KMeansAnalyzer("../../data");
    kma.performKMeansClustering(10);
    kma.generateClusteredImages();
    return 0;
}
