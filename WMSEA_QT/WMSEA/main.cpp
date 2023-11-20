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

   // kma.performKMeansClustering(11,ADAPTATIVE,HSL);

 //   kma.readClusterDataFile("../../datasets/truemarblepartials/test3/clusterData.txt");
  //  kma.displayClusters();

    vector<Color> colors;
    colors.push_back(Color(180,180,180));  //gray bare sparse vegetation
    colors.push_back(Color(0,100,0)); //green   tree cover
    colors.push_back(Color(255,187,34)); //ORANGE  shurbland
    colors.push_back(Color(255,255,76)); //YELLOW  grassland
    colors.push_back(Color(240,150,255)); //PINK cropland
    colors.push_back(Color(250,0,0));   //RED build up city ect
    colors.push_back(Color(240,240,240)); //WHITE    snow and ice
    colors.push_back(Color(0,100,200));  //BLUE   permanent water bodies (lakes rivers seaborders)
    colors.push_back(Color(0,150,160)); //GREEBLUE     herbaceous wetland (marais not mangroves)
    colors.push_back(Color(0,207,117)); //GREENMAGROVE  mangroves
    colors.push_back(Color(250,230,160)); //MOSS ad lichten
 
    ImageBase* image = new ImageBase(); image->load("../../datasets/truemarblepartials/comparaison/PGM.pgm");///test3/PGM.pgm");
    ImageBase* cimage = kma.colorizePgmImage(image,colors);
    cimage->save("../../datasets/truemarblepartials/comparaison/PGM.ppm");//test3/PGM.ppm"); 

    //kma.generateClusteredImages(true);
    //kma.writeClusterDataFile();

    return 0;
}