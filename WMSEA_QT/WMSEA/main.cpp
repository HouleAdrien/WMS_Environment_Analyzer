#include "headers/KMeansAnalyzer.h"

int main(int argc, char *argv[])
{
    KMeansAnalyzer kma = KMeansAnalyzer("../../datasets/truemarblepartials/test2");

    kma.addClusterInitColor(Color(0,0,0));
    kma.addClusterInitColor(Color(128,128,128));
    kma.addClusterInitColor(Color(255,255,255));

    kma.addClusterInitColor(Color(255,0,0));
    kma.addClusterInitColor(Color(0,255,0));
    kma.addClusterInitColor(Color(0,0,255));

    kma.addClusterInitColor(Color(255,255,0));
    kma.addClusterInitColor(Color(0,255,255));
    kma.addClusterInitColor(Color(255,0,255));

	kma.addClusterInitColor(Color(255,255,128));
    kma.addClusterInitColor(Color(128,255,255));
    kma.addClusterInitColor(Color(255,128,255));

    kma.addClusterInitColor(Color(255,128,128));
    kma.addClusterInitColor(Color(128,255,128));
    kma.addClusterInitColor(Color(128,128,255));

    kma.performKMeansClustering(15,ADAPTATIVE,HSL);

    kma.generateClusteredImages();

    return 0;
}