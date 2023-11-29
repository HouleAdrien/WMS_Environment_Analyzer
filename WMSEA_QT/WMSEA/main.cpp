#include "headers/KMeansAnalyzer.h"

int main(int argc, char *argv[])
{
    KMeansAnalyzer kma = KMeansAnalyzer("../../datasets/Esa_Tile1_Sat_PPM");

    /*
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
    kma.addClusterInitColor(Color(128,255,255));*/

    //kma.addClusterInitColor(Color(255,128,255));

    //kma.addClusterInitColor(Color(255,128,128));
    //kma.addClusterInitColor(Color(128,255,128));
    //kma.addClusterInitColor(Color(128,128,255));

   // kma.performKMeansClustering(11,ADAPTATIVE,HSL);

    kma.readClusterDataFile("../../datasets/truemarblepartials/clusterData.txt");
  //  kma.displayClusters();

    kma.addLabelColor(Color(0,100,200)); //BLUE   permanent water bodies (lakes rivers seaborders) 
    kma.addLabelColor(Color(0,207,117)); //GREENMAGROVE  mangroves
    kma.addLabelColor(Color(255,187,34)); //ORANGE  shurbland
    kma.addLabelColor(Color(0,150,160)); //GREEBLUE     herbaceous wetland (marais not mangroves)
    kma.addLabelColor(Color(240,150,255)); //PINK cropland
    kma.addLabelColor(Color(250,0,0));   //RED build up city ect
    kma.addLabelColor(Color(240,240,240)); //WHITE    snow and ice
    kma.addLabelColor(Color(180,180,180));    //gray bare sparse vegetation
    kma.addLabelColor(Color(255,255,76)); //YELLOW  grassland
    kma.addLabelColor(Color(0,100,0)); //green   tree cover
    kma.addLabelColor(Color(250,230,160)); //MOSS ad lichten
    kma.addLabelColor(Color(0,0,0));  // NO LABEL
 
    //ImageBase* image = new ImageBase(); image->load("../../datasets/Esa_Tile1_Sat_PPM/results/ESA_WorldCover_10m_2021_V200_N63W018_Map.pgm");///truemarblepartials/comparaison/PGM.pgm");///test3/PGM.pgm");
    //ImageBase* cimage = kma.colorizePgmImage(image);
    //cimage->save("../../datasets/Esa_Tile1_Sat_PPM/ppms/ESA_WorldCover_10m_2021_V200_N63W018_Map.ppm");//datasets/truemarblepartials/comparaison/PGM.ppm");//test3/PGM.ppm"); 

    vector<float> confMatrix = kma.compareImagesGroup("../../IA/TrainData/Esa_tile1_ppms","../../datasets/Esa_Tile1_Sat_PPM/results/ppms");
    kma.displayMatrix(confMatrix,12);

    //kma.colorizePgmImages("../../datasets/Esa_Tile1_Sat_PPM/results"); //Colorize les images PGM avec le labelColors

    //kma.generateClusteredImages(true); //Genere les images clsterisees en PGM (true) ou PPM (false)
    //kma.writeClusterDataFile();

    return 0;
}