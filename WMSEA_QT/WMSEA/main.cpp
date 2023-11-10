#include "headers/KMeansAnalyzer.h"

int main(int argc, char *argv[])
{
    KMeansAnalyzer kma = KMeansAnalyzer("../../datasets/truemarblepartials/test2");
    kma.performKMeansClustering(10);
    kma.generateClusteredImages();
    return 0;
}
