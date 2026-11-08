#include <iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

struct Image {
    unsigned int ImageData[400][400];
    int cols, rows, maxGray;
    string ImageFile;
    bool imageLoaded;
    bool imageModified;

    int loadImage(string ImageName) {
        cout << "Loading Image from " << ImageName<< endl;
        ifstream IN(ImageName);

        if (!IN.is_open())
            return -1;
        
        cout << "Loading Image" << endl;

        string MagicNumber, Comment;

        getline(IN, MagicNumber);
        getline(IN,Comment);

        IN >> cols >> rows >> maxGray;

        for (int r = 0; r < rows; r++)
            for (int c = 0; c < cols; c++)
                IN >> ImageData[r][c];

        if (IN.fail())
            return -2;

        IN.close();
        ImageFile = ImageName;
        cout << ImageFile << " " << "Loaded" << endl;
        imageLoaded = true;
        imageModified = false;
        return 0;
    }

    int saveImage() {

        ofstream COUT(ImageFile);
        if (!COUT.is_open())
            return -1;
        COUT << "P2\n# This is a comment\n"
            << cols << " " << rows << endl << maxGray << endl;
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++)
                COUT << ImageData[r][c] << " ";
            COUT << endl;
        }
        cout << " Saved" << endl;
        COUT.close();
        imageModified = false;
        return 0;
    }

    void horzontalFlip() {

        for (int r = 0; r < rows / 2; r++) {
            for (int c = 0; c < cols; c++) {
                int T = ImageData[r][c];
                ImageData[r][c] = ImageData[rows - r][c];
                ImageData[rows - r][c] = T;
            }
        }
        return;
    }

};

int main() {
    Image Img;
    Img.loadImage("C:\\Data\\Img.pgm");
    Img.horzontalFlip();
    Img.saveImage();
    return 0;
}
