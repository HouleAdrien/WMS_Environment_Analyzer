// KMeansAnalyzer.cpp
#include "../headers/KMeansAnalyzer.h"

KMeansAnalyzer::KMeansAnalyzer() {}

KMeansAnalyzer::~KMeansAnalyzer() {}

void KMeansAnalyzer::initClusters(int numClusters, float minDistanceMean) 
{
    if(clustersInitColors.size() > 0)
    {
        for(Color c : clustersInitColors) {clusters.push_back(c);}
            cout << "Initialized " << clusters.size() << " clusters with user-given colors" << endl;
    }
    else
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
            if(itCount%10 == 0){
                cout << "|";
            }
        } while(mean < minDistanceMean);
        cout << "Initialized clusters with a mean-distance of " << mean << " after " << itCount << endl; 
    }
    for(Color c : clusters)
    {
        Color p = Color(c.r,c.g,c.b);
        p.toHSL();
        clustersHSL.push_back(p);
    }
}

void KMeansAnalyzer::displayClusters()
{
    cout << "Clusters :" << endl;
    for(int c = 0 ; c < clusters.size(); c++)
    {
        cout << "  - " << (int)clusters.at(c).r << " " << (int)clusters.at(c).g << " " << (int)clusters.at(c).b << endl;
    }
}

int KMeansAnalyzer::getClosestCluster(Color p, ClusteringColorMode ccm)
{
    int clusterId = 0;

    if(ccm == HSL){p.toHSL();}

    float minDistance = 100000;
    for(int c = 0; c < clusters.size(); c++)
    {
        float d = 0;
        switch(ccm)
        {
            case RGB:
                d = clusters.at(c).distance(p);
                break;
            case HSL:
                d = clustersHSL.at(c).hslDistance(p);
                break;
        }
        if(d < minDistance)
        {
            clusterId = c;
            minDistance = d;
        }
    }

    return clusterId;
}

void KMeansAnalyzer::processImage(ImageBase* image,ClusteringMethod cm, ClusteringColorMode ccm,float clusterMeaningForce ) 
{
    int clusterId; Color p;
    for(int i = 0; i < image->getSize();i++)
    {
        p = image->readColor(i);
        clusterId = getClosestCluster(p,ccm);
        switch(cm)
        {
            case BASE: break;
            case ADAPTATIVE:
                //clusterValues.at(clusterId).push_back(p);
                float r = clusters.at(clusterId).r; float g = clusters.at(clusterId).g; float b= clusters.at(clusterId).b;
            /*  cout << "--------------------------------------------------------------------------------"<<endl;
                cout << r << endl;
                cout << clusterMeaningForce << endl;
                cout << (float)p.r * clusterMeaningForce << endl;
                cout << (r + ((float)p.r * clusterMeaningForce)) << endl;
                cout << (r + ((float)p.r * clusterMeaningForce)) / (1+clusterMeaningForce) << endl;
                cin >> r;*/                 
                clusters.at(clusterId).r = (r + ((float)p.r * clusterMeaningForce)) / (1+clusterMeaningForce);
                clusters.at(clusterId).g = (g + ((float)p.g * clusterMeaningForce)) / (1+clusterMeaningForce);
                clusters.at(clusterId).b = (b + ((float)p.b * clusterMeaningForce)) / (1+clusterMeaningForce);

                clustersHSL.at(clusterId) = Color(clusters.at(clusterId).r ,clusters.at(clusterId).g,clusters.at(clusterId).b);
                clustersHSL.at(clusterId).toHSL();
                break;
        }

    }
}

void KMeansAnalyzer::performKMeansClustering(int numClusters,ClusteringMethod cm, ClusteringColorMode ccm) 
{
    initClusters(numClusters,200);
    
    displayClusters();

    ImageBase* currentImage = new ImageBase();

    cout << "Processing all " << imagesPathes.size() << " images" << endl;
    for(int i = 0; i < imagesPathes.size(); i++)
    {
        currentImage->load( imagesPathes.at(i).data());
        processImage(currentImage,cm,ccm,0.1f);
    }

   /* cout << "Reprocessing clusters" << endl;
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
    } */

    displayClusters();
    cout << "Done" << endl;
}

ImageBase* KMeansAnalyzer::generateClusteredImage(ImageBase* input, bool pgm)
{
    ImageBase* output = new ImageBase(input->getWidth(), input->getHeight(), !pgm);
    Color p; float minDistance; int clusterId;
    for(int i = 0; i < input->getSize();i++)
    {
        p = input->readColor(i);
        minDistance = 100000;
        for(int c = 0; c < clusters.size(); c++)
        {
            float d = clusters.at(c).distance(p);
            if(d < minDistance)
            {
                clusterId = c;
                minDistance = d;
            }
            if(pgm)
            {
                output->set(i,0,clusterId);
            }
            else
            {
                output->setColor(i,colors[clusterId]);
            }
        }
    }

    return output;
}

void KMeansAnalyzer::generateClusteredImages(bool pgm)
{
    filesystem::create_directory(imagesPath + "/results");
    ImageBase* currentImage = new ImageBase();
    cout << "Clustering all " << imagesPathes.size() << " images" << endl;
    for(int i = 0; i < imagesPathes.size(); i++)
    {
        currentImage->load( imagesPathes.at(i).data());
        ImageBase* cImage = generateClusteredImage(currentImage,pgm);

        string nam = imagesPathes.at(i).substr(imagesPathes.at(i).find_last_of("/\\") + 1);
        size_t dotPosition = nam.find_last_of('.');
        nam = nam.substr(0, dotPosition);
        string cp = imagesPath + "/results/" + nam + (pgm ? ".pgm" : ".ppm");
        
        cImage->save(cp.data());
        free(cImage);
    }
}

ImageBase* KMeansAnalyzer::colorizePgmImage(ImageBase* image, vector<Color> colors)
{
    ImageBase* output = new ImageBase(image->getWidth(),image->getHeight(),true);
    for(int i = 0; i < image->getSize();i++)
    {
        output->setColor(i,colors.at(image->get(i,0)));
    }
    return output;
}

void KMeansAnalyzer::colorizePgmImages()
{
    
}

void KMeansAnalyzer::writeClusterDataFile()
{
    string cp = imagesPath + "/results/clusterData.txt";
    ofstream myfile;
    myfile.open (cp);
    for(int i = 0 ; i < clusters.size();i++)
    {
        myfile << (int)clusters.at(i).r << " ";
        myfile << (int)clusters.at(i).g << " ";
        myfile << (int)clusters.at(i).b << "\n" ;
    }
    myfile.close();
}

 void KMeansAnalyzer::readClusterDataFile(string path)
 {
    string line;
    ifstream myfile (path);
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            vector<int> dat;
            std::istringstream iss(line);

            int value;
            while (iss >> value) {
                dat.push_back(value);
            }
            Color color = Color(dat.at(0),dat.at(1),dat.at(2));
            clusters.push_back(color);
        }
        myfile.close();
    }
    else{cout << "Couldn't read file " << path << endl;}
 }

// Vous pouvez également implémenter d'autres méthodes pour gérer les résultats et d'autres fonctionnalités.

