#include <iostream>
#include <time.h>
#include <fstream>
#include <vector>
using namespace std;

// Functions need't to be seamless, except red(t), green(t), blue(t), if you want to time-loop!
// Une des grandes diagonales du cube a ses 2 coins aux coordonnées (0, 0, 0) et (sizeMap, sizeMap, sizeMap).

int saturation(int result = 0, int mini = 0, int maxi = 255) { // https://fr.wikipedia.org/wiki/Portable_pixmap#PPM
    mini = max(0,mini);
    maxi = min(maxi, 65535);
    result = max(mini,result);
    result = min(maxi,result);
    return result;
}

int red(vector<int>& parametersR, int x = 0, int y = 0, int z = 0, int t = 0, int mini = 0, int maxi = 256) {
    int result = x;
    return saturation(result);
}
int green(vector<int>& parametersG, int x = 0, int y = 0, int z = 0, int t = 0, int mini = 0, int maxi = 256) {
    int result = y;
    return saturation(result);
}
int blue(vector<int>& parametersB, int x = 0, int y = 0, int z = 0, int t = 0, int mini = 0, int maxi = 256) {
    int result = z;
    return saturation(result);
}
// If singleImage, 0 is black. // Multiple images not supported yet.
int RVoidColor() {
// return 256;
    return 0;
}
int GVoidColor() {
    // return 256;
    return 0;
}
int BVoidColor() {
    // return 256;
    return 0;
}

int main() {
    srand (time(NULL));
    cout << "CubeMapGenerator." << endl;
    int sizeMap = 256;
    cout << "SizeMap: " << sizeMap  << endl;
    int timeTotal = 3 * sizeMap;
    const int MAXPGM = 65535; // Format PGM : https://fr.wikipedia.org/wiki/Portable_pixmap
    // const int WHITE = 65535; // Maximum.
    const int WHITE = 255; // Usual RGB images.
    int t = 0;
    bool singleImage = true; // False not supported yet.
    string filePrefix = "map"; // Multiple images not supported yet.
    string file = "CubeMap.ppm";
    vector<int> parametersR = {0};
    vector<int> parametersG = {0};
    vector<int> parametersB = {0};
// Void , top or up, Void , Void
// left , front , right, back
// Void , bottom or down, Void, Void
// (0, 0, 0) at the bottom left of front.
    ofstream destroyInsideFile(file.c_str(), ios_base::out);
    destroyInsideFile.close();

    ofstream outfile(file.c_str(), ios_base::app);

    if (!outfile) {
        cerr << "Error writing in file: " << file << "!" << endl;
        return -1;
    } else {
        outfile << "P3" << endl;
        outfile << sizeMap * 4 << " " << sizeMap * 3 << endl;
        outfile << WHITE << endl;
        for (int v=1; v<(sizeMap +1) ; ++v) {
            cout << "\r" << v << "/" << timeTotal;
            for (int i=1; i<sizeMap +1 ; ++i) {
                outfile << RVoidColor() << " " << GVoidColor() << " " << BVoidColor() << endl;
            }
            outfile << " " << endl;
            // TOP:
            for (int i=1; i<sizeMap +1; ++i) {
                outfile << red(parametersR, i, v, sizeMap, t, 0, WHITE ) << " " << green(parametersG, i, v, sizeMap, t, 0, WHITE ) << " " << blue(parametersB, i, v, sizeMap, t, 0, WHITE ) << endl;
            }
            outfile << " " << endl;
            for (int i=1; i<(sizeMap) +1; ++i) {
                outfile << RVoidColor() << " " << GVoidColor() << " " << BVoidColor() << endl;
            }
            outfile << " " << endl;
            for (int i=1; i<(sizeMap) +1 ; ++i) {
                outfile << RVoidColor() << " " << GVoidColor() << " " << BVoidColor() << endl;
            }
            outfile << " " << endl;
        }
        outfile << " " << endl;
        outfile << " " << endl;
        for (int v=1; v<(sizeMap +1) ; ++v) {
            cout << "\r" << sizeMap + v << "/" << timeTotal;
            // LEFT:
            for (int i=1; i<sizeMap +1 ; ++i) {
                outfile << red(parametersR, 0, i, sizeMap -v, t, 0, WHITE ) << " " << green(parametersG, 0, i, sizeMap -v, t, 0, WHITE ) << " " << blue(parametersB, 0, v, sizeMap -v, t, 0, WHITE ) << endl;
            }
            outfile << " " << endl;
            // FRONT:
            for (int i=1; i<sizeMap +1 ; ++i) {
                outfile << red(parametersR, i, sizeMap,  sizeMap-v, t, 0, WHITE ) << " " << green(parametersG, i, sizeMap,  sizeMap-v, 0, WHITE ) << " " << blue(parametersB, i, sizeMap,  sizeMap-v, t, 0, WHITE ) << endl;
            }
            outfile << " " << endl;
            // RIGHT:
            for (int i=1; i<(sizeMap +1) ; ++i) {
                outfile << red(parametersR, sizeMap, sizeMap -i, sizeMap-v, t, 0, WHITE ) << " " << green(parametersG, sizeMap, sizeMap -i, sizeMap-v, t, 0, WHITE ) << " " << blue(parametersB, sizeMap, sizeMap -i, sizeMap-v, t, 0, WHITE ) << endl;
            }
            outfile<< " " << endl;
            // BACK:
            for (int i=1; i<(sizeMap +1) ; ++i) {
                outfile << red(parametersR, sizeMap -i, 0, sizeMap-v, t, 0, WHITE ) << " " << green(parametersG, sizeMap -i, 0, sizeMap-v, t, 0, WHITE ) << " " << blue(parametersB, sizeMap -i, 0, sizeMap-v, t, 0, WHITE ) << endl;
            }
            outfile << " " << endl;
        }
        outfile<< " " << endl;
        outfile << " " << endl;
        for (int v=1; v<(sizeMap +1) ; ++v) {
            cout << "\r" << (2 * sizeMap) + v << "/" << timeTotal;
            for (int i=1; i<sizeMap +1 ; ++i) {
                outfile << RVoidColor() << " " << GVoidColor() << " " << BVoidColor() << endl;
            }
            outfile << " " << endl;
            // BOTTOM:
            for (int i=1; i<sizeMap +1 ; ++i) {
                outfile << red(parametersR, i, sizeMap-v, 0, t, 0, WHITE) << " " << green(parametersG, i, sizeMap-v, 0, t, 0, WHITE) << " " << blue(parametersB, i, sizeMap-v, 0, t, 0, WHITE) << endl;
            }
            outfile << " " << endl;
            for (int i=1; i<(sizeMap +1) ; ++i) {
                outfile << RVoidColor() << " " << GVoidColor() << " " << BVoidColor() << endl;
            }
            outfile << " " << endl;
            for (int i=1; i<(sizeMap +1) ; ++i) {
                outfile << RVoidColor() << " " << GVoidColor() << " " << BVoidColor() << endl;
            }
            outfile << " " << endl;
        }
        outfile.close();
    }

    cout << "\n" << file << endl;
    cout << "Ok!" << endl;
    return 0;
}
