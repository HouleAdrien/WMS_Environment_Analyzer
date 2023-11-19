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

    //kma.addClusterInitColor(Color(255,128,255));

    //kma.addClusterInitColor(Color(255,128,128));
    //kma.addClusterInitColor(Color(128,255,128));
    //kma.addClusterInitColor(Color(128,128,255));

    kma.performKMeansClustering(11,ADAPTATIVE,HSL);

 //   kma.readClusterDataFile("../../datasets/truemarblepartials/test3/clusterData.txt");
  //  kma.displayClusters();

 /*   vector<Color> colors;
    colors.push_back(Color(50,50,50));  //gray
    colors.push_back(Color(50,200,50)); //green
    colors.push_back(Color(255,140,0)); //ORANGE
    colors.push_back(Color(255,255,50)); //YELLOW
    colors.push_back(Color(250,0,250)); //PINK
    colors.push_back(Color(255,0,0));   //RED
    colors.push_back(Color(250,250,250)); //WHITE
    colors.push_back(Color(30,30,220));  //BLUE
    colors.push_back(Color(30,117,115)); //GREEBLUE
    colors.push_back(Color(30,200,170)); //GREENMAGROVE
    colors.push_back(Color(200,200,130)); //MOSS

    ImageBase* image = new ImageBase(); image->load("../../datasets/truemarblepartials/test3/PGM.pgm");
    ImageBase* cimage = kma.colorizePgmImage(image,colors);
    cimage->save("../../datasets/truemarblepartials/test3/PGM.ppm"); */

    kma.generateClusteredImages(true);
    kma.writeClusterDataFile();

    return 0;
}